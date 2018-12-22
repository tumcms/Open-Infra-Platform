/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 *
 * - modfied by Michael Kern (September 2014)
*/

// visual studio
#pragma once
// unix
#ifndef CURVECONVERTER_H
#define CURVECONVERTER_H

#define _USE_MATH_DEFINES 
#include <math.h>

#include "CarveHeaders.h"

#include "GeomUtils.h"
#include "UnhandledRepresentationException.h"
#include "PlacementConverter.h"
#include "ProfileConverter.h"
#include "GeometrySettings.h"
#include "SplineConverter.h"


#include "OpenInfraPlatform/ExpressBinding/vectorUtilites.h"

/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace IfcGeometryConverter {
		template<
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>
			class CurveConverterT {
			public:
				CurveConverterT(std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<IfcUnitConverterT> unitConverter)
					:
					m_geomSettings(geomSettings),
					m_unitConverter(unitConverter)
				{
				}

				virtual ~CurveConverterT()
				{

				}

				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<3>>& loops,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim2Vec;
					convertIfcCurve(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
				}

				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim1Vec,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim2Vec,
					bool senseAgreement) const
				{
					double length_factor = m_unitConverter->getLengthInMeterFactor();
					double plane_angle_factor = m_unitConverter->getAngleInRadianFactor();

					// IfcCurve ABSTRACT SUPERTYPE OF (ONEOF(IfcBoundedCurve, IfcConic, IfcLine, IfcOffsetCurve2D, IfcOffsetCurve3D, IfcPCurve))
					std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> bounded_curve =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(ifcCurve);

					// IfcBoundedCurve ABSTRACT SUPERTYPE OF (ONEOF(IfcCompositeCurve, IfcAlignmentCurve, IfcPolyline, IfcTrimmedCurve, IfcBSplineCurve)
					if(bounded_curve) {
						// IfcCompositeCurve (SUBTYPE OF (IfcBoundedCurve))
						std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurve> composite_curve =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeCurve>(bounded_curve);

						if(composite_curve) {

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> > segments =
								composite_curve->m_Segments;
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> >::iterator it_segments =
								segments.begin();
							for(; it_segments != segments.end(); ++it_segments) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> segment = (*it_segments);
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve> segment_curve = segment->m_ParentCurve;

								std::vector<carve::geom::vector<3>> segment_vec;
								convertIfcCurve(segment_curve, segment_vec, segmentStartPoints);
								if(segment_vec.size() > 0) {
									GeomUtils::appendPointsToCurve(segment_vec, targetVec);
								}
							}
							return;
						}

						// IfcAlignmentCurve (SUBTYPE OF (IfcBoundedCurve)) with (IfcAlignment2DHorizontal, OPTIONAL: IfcAlignment2DVertical)
						std::shared_ptr<typename IfcEntityTypesT::IfcAlignmentCurve> alignment_curve =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignmentCurve>(ifcCurve);

						if(alignment_curve)

						{
							//	********************************************************************************************
							//	PART 1/4. Class Definitions.
							//	********************************************************************************************

							// Base classes.
							class Station {
							public:
								double distAlong_;	// horizontal distance along.
								double x_, y_, z_;	// 3D-coordinates of station.

								Station(double distAlong, double x, double y, double z)
									: distAlong_(distAlong), x_(x), y_(y), z_(z)
								{
								}
								~Station() {}
							};

							class Segment {
							public:
								std::vector<Station> segmentStations_;									// vector of all stations within segment (horizontalSegmentStations or verticalSegmentStations)
								enum segmentType { isLine, isCircArc, isTrans, isParArc } segType_;		// segment type.
								int fragmentsCount_ = 0;												// number of fragments within segment. 
								double fragmentsLength_;												// length of one fragment within segment.

								Segment(std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
									: segmentStations_(segmentStations), segType_(segType), fragmentsCount_(fragmentsCount), fragmentsLength_(fragmentsLength)
								{
								}
								~Segment() {}

								void addStation(double newStationDistAlong) // TODO: function needs iterator position to know which segmentStations_
								{
									segmentStations_.push_back(Station(newStationDistAlong, 0, 0, 0));
								}

								void addStation(double newStationDistAlong, double z)
								{
									segmentStations_.push_back(Station(newStationDistAlong, 0, 0, z));
								}

								void addStation(double newStationDistAlong, double x, double y)
								{
									segmentStations_.push_back(Station(newStationDistAlong, x, y, 0));
								}

								void addStation(double newStationDistAlong, double x, double y, double z)
								{
									segmentStations_.push_back(Station(newStationDistAlong, x, y, z));
								}

								void insertStationAtSecondToLast(double newStationDistAlong)
								{
									int size = segmentStations_.size();
									segmentStations_.insert(size - 1, Station(newStationDistAlong, x, y, z));
								}
							};

							// Horizontal alignment classes.
							class HorizontalAlignment {
							public:
								double dStartDistanceAlong_ = 0.;			// If not received, it is set to zero.
								std::vector<HorizontalSegment> horizontalSegments_;

								HorizontalAlignment(double dStartDistanceAlong, std::vector<HorizontalSegment> horizontalSegments)
									: dStartDistanceAlong_(dStartDistanceAlong), horizontalSegments_(horizontalSegments)
								{
								};
								~HorizontalAlignment() {};
							};

							class HorizontalSegment : public Segment {
								double startX_;
								double startY_;
								double startDirection_;
								double segmentLength_;

								HorizontalSegment(double startX, double startY, double startDirection, double segmentLength, // members of HorizontalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: Segment(segmentStations, segType, fragmentsCount, fragmentsLength),
									startX_(startX), startY_(startY), startDirection_(startDirection), segmentLength_(segmentLength)
								{
								}
								~HorizontalSegment() {};
							};

							class HorizontalLineSegment : public HorizontalSegment {
								HorizontalLineSegment(double startX, double startY, double startDirection, double segmentLength, // members of HorizontalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: HorizontalSegment(startX, startY, startDirection, segmentLength, segmentStations, segType, fragmentsCount, fragmentsLength)
								{
								}
								~HorizontalLineSegment() {};
							};

							class HorizontalCircArcSegment : public HorizontalSegment {
								double radius_;
								bool isCCW_;

								HorizontalCircArcSegment(double radius, bool isCCW, // members of HorizontalCircArcSegment
									double startX, double startY, double startDirection, double segmentLength, // members of HorizontalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: HorizontalSegment(startX, startY, startDirection, segmentLength, segmentStations, segType, fragmentsCount, fragmentsLength),
									radius_(radius), isCCW_(isCCW));

									~HorizontalCircArcSegment() {};
							};

							class HorizontalTransCurveSegment : public HorizontalSegment {
								double startRadius_;
								double endRadius_;
								bool isStartRadiusCCW_;
								bool isEndRadiusCCW_;
								enum transitionCurveType { BIQUADRATICPARABOLA, BLOSSCURVE, CLOTHOIDCURVE, COSINECURVE, CUBICPARABOLA, SINECURVE } transCurveType_;

								HorizontalTransCurveSegment(double startRadius_, double endRadius_, bool isStartRadiusCCW_, bool isEndRadiusCCW_, transitionCurveType transCurveType_, // members of HorizontalTransCurveSegment
									double startX, double startY, double startDirection, double segmentLength, // members of HorizontalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: HorizontalSegment(startX, startY, startDirection, segmentLength, segmentStations, segType, fragmentsCount, fragmentsLength),
									startRadius_(startRadius), endRadius_(endRadius), isStartRadiusCCW_(isStartRadiusCCW), isEndRadiusCCW_(isEndRadiusCCW), transCurveType_(transCurveType)
								{
								}

								~HorizontalTransCurveSegment() {};
							};

							// Vertical alignment classes
							class VerticalAlignment {
							public:
								double dStartDistanceAlong_ = 0.;	// If not received, it is set to zero.
								std::vector<VerticalSegment> verticalSegments_;

								VerticalAlignment(double dStartDistanceAlong, std::vector<VerticalSegment> verticalSegments)
									: dStartDistanceAlong_(dStartDistanceAlong), verticalSegments_(verticalSegments)
								{
								}
								~VerticalAlignment() {};
							};

							class VerticalSegment : public Segment {
								double startZ_;
								double startDistAlong_;
								double horizontalLength_;
								double startGradient_;

								VerticalSegment(double startZ, double startDistAlong, double horizontalLength, double startGradient, // members of VerticalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: Segment(segmentStations, segType, fragmentsCount, fragmentsLength),
									startZ_(startZ), startDistAlong_(startDistAlong), horizontalLength_(horizontalLength), startGradient_(startGradient)
								{
								}
								~VerticalSegment() {};
							};

							class VerticalLineSegment : public VerticalSegment {
								VerticalLineSegment(double startZ, double startDistAlong, double horizontalLength, double startGradient, // members of VerticalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: VerticalSegment(startZ, startDistAlong, horizontalLength, startGradient, segmentStations, segType, fragmentsCount, fragmentsLength)
								{
								}
								~VerticalLineSegment() {};
							};

							class VerticalCircArcSegment : public VerticalSegment {
								double radius_;
								bool isConvex_;

								VerticalCircArcSegment(double radius, bool isCCW, // members of VerticalCircArcSegment
									double startZ, double startDistAlong, double horizontalLength, double startGradient, // members of VerticalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: VerticalSegment(startZ, startDistAlong, horizontalLength, startGradient, segmentStations, segType, fragmentsCount, fragmentsLength),
									radius_(radius), isConvex_(isConvex)
								{
								}
								~VerticalCircArcSegment() {};
							};

							class VerticalParabolicArcSegment : public VerticalSegment {
								double parabolaConstant_;
								bool isConvex_;

								VerticalParabolicArcSegment(double parabolaConstant, bool isConvex, // members of VerticalParabolicArcSegment
									double startZ, double startDistAlong, double horizontalLength, double startGradient, // members of VerticalSegment
									std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength) // members of Segment
									: VerticalSegment(startZ, startDistAlong, horizontalLength, startGradient, segmentStations, segType, fragmentsCount, fragmentsLength),
									parabolaConstant_(parabolaConstant), isConvex_(isConvex)
								{
								}
								~VerticalParabolicArcSegment() {};
							};

							// **********************************************************************************************************
							// PART 2/4. IfcAlignment2DHorizontal.
							//
							//		Step 1: Get segment information and store in horizontal station vector.
							//		Step 2: Get segment type information and additional members and store in horizontal segments vector.
							// **********************************************************************************************************

							// Step 1: Get segment information and store in horizontal station vector.

							// Declaration of necessary objects and vectors.
							HorizontalAlignment horizontalAlignment;
							std::vector<HorizontalSegment> HorSegmentsVec;

							// Get information from alignment.
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignment_curve->m_Alignment2DHorizontal;
							if(!horizontal) {
								BLUE_LOG(error) << "No IfcAlignment2DHorizontal in IfcAlignmentCurve. (Segment ID: " << horizontal->getId() << ")."; // TO DO: Check ID
								return;
							}

							// m_StartDistAlong type IfcLengthMeasure [0:1]
							std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> horStartDistAlong = horizontal->m_StartDistAlong;
							if(horStartDistAlong) {
								horizontalAlignment.dStartDistanceAlong_ = horStartDistAlong->m_value * length_factor;
							}

							// m_Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if(!horizontal->m_Segments) {
								BLUE_LOG(error) << "Not enough segments in IfcAlignment2DHorizontal. (Segment ID: " << m_Segments->getId() << ")."; // TO DO: Check ID
								return;
							}

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment> > horSegments =
								horizontal->m_Segments;

							if(horSegments.size() < 1) {
								BLUE_LOG(error) << "Not enough segments in IfcAlignment2DHorizontal. (Segment ID: " << horSegments->getId() << ")."; // TO DO: Check ID
								return;
							}

							// Iterate over horizontal segments
							auto it_segment = horSegments.begin();
							for(auto it_segment : horSegments) {

								//IfcAlignment2DHorizontalSegment (m_TangentialContinuity type IfcBoolean [0:1], m_StartTag type IfcLabel [0:1], m_EndTag type IfcLabel [0:1], m_CurveGeometry type IfcCurveSegment2D [1:1])

								std::shared_ptr<typename IfcEntityTypesT::IfcCurveSegment2D> horCurveGeometry =
									it_segment->m_CurveGeometry;

								// IfcCurveSegment2D
								if(!horCurveGeometry) {
									BLUE_LOG(error) << "No curve geometry in IfcAlignment2DHorizontalSegment (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// m_StartPoint type IfcCartesianPoint [1:1]
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> curveSegStartPoint =
									horCurveGeometry->m_StartPoint;
								if(!curveSegStartPoint) {
									BLUE_LOG(error) << "No curve segment start point in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// m_StartDirection type IfcPlaneAngleMeasure [1:1]
								std::shared_ptr<typename IfcEntityTypesT::IfcPlaneAngleMeasure> curveSegStartDirection =
									horCurveGeometry->m_StartDirection;
								if(!curveSegStartDirection) {
									BLUE_LOG(error) << "No curve segment start direction in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// m_SegmentLength type IfcPositiveLengthMeasure [1:1]
								std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> curveSegLength =
									horCurveGeometry->m_SegmentLength;
								if(!curveSegLength) {
									BLUE_LOG(error) << "No curve segment length in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// Interpret curve_seg_start_point, curve_seg_start_direction and curve_seg_length.
								double xStart = 0., yStart = 0.;
								xStart = curveSegStartPoint->m_Coordinates[0]->m_value * length_factor;
								yStart = curveSegStartPoint->m_Coordinates[1]->m_value * length_factor;
								double dStartDirection = curveSegStartDirection->m_value * plane_angle_factor;
								double dSegLength = curveSegLength->m_value * length_factor;

								// Store information in station object.
								Station horizontalStation(dStartDistanceAlong, xStart, yStart, 0);

								// Step 2: Get segment type information and additional members and store in horizontal segments vector.

								// Get segment types information: IfcLineSegment2D, IfcCircularArcSegment2D and IfcTransitionCurveSegment2D: inherit m_StartPoint, m_StartDirection, m_SegmentLength from IfcCurveSegment2D.
								// http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifccurvesegment2d.htm
								std::shared_ptr<typename IfcEntityTypesT::IfcLineSegment2D> line_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcLineSegment2D>(horCurveGeometry);

								std::shared_ptr<typename IfcEntityTypesT::IfcCircularArcSegment2D> circular_arc_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircularArcSegment2D>(horCurveGeometry);

								std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcTransitionCurveSegment2D>(horCurveGeometry);

								// Set number of fragments (number of points to be added between stations) according to segment type.

								if(line_segment_2D) {
									int nHorFragments = 0;
									// insert HorizontalLineSegment(double startX, double startY, double startDirection, double segmentLength,
									// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
									HorizontalLineSegment horizontalLineSegment(xStart, yStart, dStartDirection, dSegLength, { horizontalStation }, isLine, nHorFragments, dSegLength)
										HorSegmentsVec.push_back(horizontalLineSegment);
								}

								if(circular_arc_segment_2D) {
									int nHorFragments = m_geomSettings->m_min_num_vertices_per_arc;
									double nHorFragmentsLength = dSegLength / nHorFragments;
									// m_Radius type IfcPositiveLengthMeasure [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> circ_arc_radius =
										circular_arc_segment_2D->m_Radius;
									if(!circ_arc_radius) {
										BLUE_LOG(error) << "No radius in IfcCircularArcSegment2D (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									double d_circ_arc_radius = circ_arc_radius->m_value * length_factor;

									// m_IsCCW type IfcBoolean [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> circ_arc_is_CCW =
										circular_arc_segment_2D->m_IsCCW;
									if(!circ_arc_is_CCW) {
										BLUE_LOG(error) << "No direction information for IfcCircularArcSegment2D (counterclockwise/clockwise) (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									bool b_circ_arc_is_CCW = circ_arc_is_CCW->m_value;

									// insert HorizontalCircArcSegment(double radius, bool isCCW,
									// double startX, double startY, double startDirection, double segmentLength,
									// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
									HorizontalCircArcSegment horizontalCircArcSegment(d_circ_arc_radius, b_circ_arc_is_CCW, xStart, yStart,
										dStartDirection, dSegLength, { horizontalStation }, isCircArc, nHorFragments, nHorFragmentsLength)
										HorSegmentsVec.push_back(horizontalCircArcSegment);
								}

								if(trans_curve_segment_2D) {
									nHorFragments = m_geomSettings->m_min_num_vertices_per_arc;
									double nHorFragmentsLength = dSegLength / nHorFragments;

									// m_StartRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature) 
									std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> trans_start_radius =
										trans_curve_segment_2D->m_StartRadius;
									if(!trans_start_radius) {
										BLUE_LOG(warning) << "IfcTransitionCurve: Start radius NIL, interpreted as infinite. (Segment ID: " << it_segment->getId() << ").";
										double d_trans_start_radius = 0;
									}
									else {
										double d_trans_start_radius = trans_start_radius->m_value * length_factor;
									}

									// m_EndRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
									std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> trans_end_radius =
										trans_curve_segment_2D->m_EndRadius;
									if(!trans_end_radius) {
										BLUE_LOG(warning) << "IfcTransitionCurve: End radius NIL, interpreted as infinite. (Segment ID: " << it_segment->getId() << ").";
										d_trans_end_radius = 0;
									}
									else {
										double d_trans_end_radius = trans_end_radius->m_value * length_factor;
									}

									// m_IsStartRadiusCCW type IfcBoolean
									std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> trans_is_start_ccw =
										trans_curve_segment_2D->m_IsStartRadiusCCW;
									if(!trans_is_start_ccw) {
										BLUE_LOG(error) << "No direction information for start of IfcTransitionCurveSegment2D (counterclockwise/clockwise). (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									bool b_trans_is_start_ccw = trans_is_start_ccw->m_value;

									// m_IsEndRadiusCCW type IfcBoolean
									std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> trans_is_end_ccw =
										trans_curve_segment_2D->m_IsEndRadiusCCW;
									if(!trans_is_end_ccw) {
										BLUE_LOG(error) << "No direction information for end of IfcTransitionCurveSegment2D (counterclockwise/clockwise). (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									bool b_trans_is_end_ccw = trans_is_end_ccw->m_value;

									// m_TransitionCurveType type IfcTransitionCurveType
									std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveType> trans_curve_type =
										trans_curve_segment_2D->m_TransitionCurveType;
									if(!trans_curve_type) {
										BLUE_LOG(error) << "No curve type for IfcTransitionCurveSegment2D. (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									transitionCurveType t_trans_curve_type = trans_curve_type->m_enum;

									// insert HorizontalTransCurveSegment(double startRadius_, double endRadius_, bool isStartRadiusCCW_, bool isEndRadiusCCW_, 
									// transitionCurveType transCurveType_, double startX, double startY, double startDirection, double segmentLength,
									// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
									HorizontalTransCurveSegment horizontalTransCurveSegment(d_trans_start_radius, d_trans_end_radius, b_trans_is_start_ccw,
										b_trans_is_end_ccw, t_trans_curve_type, xStart, yStart, dStartDirection, dSegLength, { horizontalStation }, isTrans, nHorFragments, nHorFragmentsLength);
									HorSegmentsVec.push_back(horizontalTransCurveSegment);
								}

							} // end of HorSegmentsVec iteration

							horizontalAlignment.horizontalSegments_ = HorSegmentsVec;

							// *******************************************************************************************************
							// PART 3/4. IfcAlignment2DVertical.
							//
							//		Step 1: Get segment information and store in vertical station vector.
							//		Step 2: Get segment type information and additional members and store in vertical segments vector.
							// *******************************************************************************************************

							// Step 1: Get information segment information and store in vertical station vector.

							// Declaration of necessary objects and vectors.
							VerticalAlignment verticalAlignment;
							std::vector<VerticalSegment> VerSegmentsVec;

							// Get information.
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVertical> vertical = alignment_curve->m_Alignment2DVertical;
							if(!vertical) {
								BLUE_LOG(warning) << "No IfcAlignment2DVertical in IfcAlignmentCurve (Segment ID: " << vertical->getId() << ")."; // TO DO: Check ID
																																				  // Handle as horizontal alignment only.
							}
							else {
								// m_Segments type IfcAlignment2DVerticalSegment L[1:?]
								if(!vertical->m_Segments) {
									BLUE_LOG(error) << "No segments in IfcAlignment2DVertical. (Segment ID: " << m_Segments->getId() << ")."; // TO DO: Check ID
									return;
								}

								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment> > verSegments =
									vertical->m_Segments;

								if(verSegments < 1) {
									BLUE_LOG(error) << "Not enough segments in IfcAlignment2DVertical. (Segment ID: " << verSegments>getId() << ")."; // TO DO: Check ID
									return;
								}

								// Declaration of vertical stations and accuracy vectors.
								int nVerFragments = 0;

								// Iterate over vertical segments.
								auto it_segment = verSegments.begin();

								for(; it_segment != verSegments.end(); ++it_segment) {

									// IfcAlignment2DVerticalSegment (m_TangentialContinuity type IfcBoolean [0:1], m_StartTag type IfcLabel [0:1], m_EndTag type IfcLabel [0:1])	

									// Check for verDistAlong, verHorizontalLength, verStartHeight, verStartGradient

									// m_StartDistAlong type IfcLengthMeasure [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> verDistAlong =
										it_segment->m_StartDistAlong;
									if(!verDistAlong) {
										BLUE_LOG(error) << "No start distance along in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_HorizontalLength type IfcPositiveLengthMeasure [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> verHorizontalLength =
										it_segment->m_HorizontalLength;
									if(!verHorizontalLength) {
										BLUE_LOG(error) << "No horizontal length in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_StartHeight type IfcLengthMeasure [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> verStartHeight =
										it_segment->m_StartHeight;
									if(!verStartHeight) {
										BLUE_LOG(error) << "No start height in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_StartGradient type IfcRatioMeasure [1:1]
									std::shared_ptr<typename IfcEntityTypesT::IfcRatioMeasure> verStartGradient =
										it_segment->m_StartGradient;
									if(!verStartGradient) {
										BLUE_LOG(error) << "No start gradient in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// Interpret verDistAlong, verHorizontalLength, verStartHeight, verStartGradient
									double dVerDistAlong = verDistAlong->m_value * length_factor;
									double zStart = verStartHeight->m_value * length_factor;
									double dVerHorizontalLength = verHorizontalLength->m_value * length_factor;
									double dVerStartGradient = verStartGradient->m_value;

									// Store information in vertical stations vector.
									Station verticalStation(dVerDistAlong, 0, 0, zStart);

									// Step 2: Get segment type information and additional members and store in vertical segments vector.

									// Segment types: IfcAlignment2DVerSegCircularArc, IfcAlignment2DVerSegLine, IfcAlignment2DVerSegParabolicArc (all inherit m_TangentialContinuity, 
									// m_StartTag, m_EndTag, m_StartDistAlong, m_HorizontalLength, m_StartHeight, m_StartGradient from IfcAlignment2DVerticalSegment)

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>(it_segment);

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegLine> ver_seg_line_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>(it_segment);

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc>(it_segment);

									// Set number of fragments (number of stations to be added within segment) according to segment type.

									if(v_seg_circ_arc_2D) {
										nVerFragments = m_geomSettings->m_min_num_vertices_per_arc;
										double nVerFragmentsLength = dVerHorizontalLength / nVerFragments;

										// copied from 4. Interpretation, todo: delete there
										// m_Radius type IfcPositiveLengthMeasure [1:1] 
										std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> > v_seg_circ_arc_radius =
											v_seg_circ_arc_2D->m_Radius;
										if(!v_seg_circ_arc_radius) {
											BLUE_LOG(error) << "No radius in IfcAlignment2DVerSegCircularArc" (Segment ID : " << it_segment->getId() << ").";
												return;
										}
										double d_ver_seg_circ_arc_radius = v_seg_circ_arc_radius->m_value * length_factor;

										// m_IsConvex type IfcBoolean [1:1]
										std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > v_seg_circ_arc_is_convex =
											v_seg_circ_arc_2D->m_IsConvex;
										if(!v_seg_circ_arc_is_convex) {
											BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegCircularArc (convex/concave)" (Segment ID : " << it_segment->getId() << ").";
												return;
										}
										bool b_ver_seg_circ_arc_is_convex = v_seg_circ_arc_is_convex->m_value;

										// insert VerticalCircArcSegment(double radius, bool isCCW,
										// double startZ, double startDistAlong, double horizontalLength, double startGradient,
										// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
										VerticalCircArcSegment verticalCircArcSegment(d_ver_seg_circ_arc_radius, b_ver_seg_circ_arc_is_convex, zStart, dVerDistAlong,
											dVerHorizontalLength, dVerStartGradient, { verticalStation }, isCircArc, nVerFragments, nVerFragmentsLength);
										VerSegmentsVec.push_back(verticalCircArcSegment);
									}

									if(ver_seg_line_2D) {
										nVerFragments = 0;

										// insert VerticalLineSegment(double startZ, double startDistAlong, double horizontalLength, double startGradient,
										// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
										VerticalLineSegment verticalLineSegment(zStart, dVerDistAlong, dVerHorizontalLength, dVerStartGradient,
										{ verticalStation }, isLine, nVerFragments, dVerHorizontalLength);
										VerSegmentsVec.push_back(verticalLineSegment);
									}

									if(v_seg_par_arc_2D) {
										nVerFragments = m_geomSettings->m_min_num_vertices_per_arc;
										double nVerFragmentsLength = dVerHorizontalLength / nVerFragments;

										// Copied from 4. Interpretation, todo: delete there
										// m_ParabolaConstant type IfcPositiveLengthMeasure [1:1]
										std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> > v_seg_par_arc_const =
											v_seg_par_arc_2D->m_ParabolaConstant;
										if(!v_seg_par_arc_const) {
											BLUE_LOG(error) << "No parabola constant in IfcAlignment2DVerSegParabolicArc" (Segment ID : " << it_segment->getId() << ").";
												return;
										}
										double d_ver_seg_par_arc_const = v_seg_par_arc_const->m_value * length_factor;

										// m_IsConvex type IfcBoolean [1:1]
										std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > v_seg_par_arc_is_convex =
											v_seg_par_arc_2D->m_IsConvex;
										if(!v_seg_par_arc_is_convex) {
											BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegParabolicArc (convex/concave)" (Segment ID : " << it_segment->getId() << ").";
												return;
										}
										bool b_ver_seg_par_arc_is_convex = v_seg_par_arc_is_convex->m_value;

										// insert VerticalParabolicArcSegment(double parabolaConstant, bool isConvex,
										// double startZ, double startDistAlong, double horizontalLength, double startGradient,
										// std::vector<Station> segmentStations, segmentType segType, int fragmentsCount, double fragmentsLength)
										VerticalParabolicArcSegment verticalParabolicArcSegment(d_ver_seg_par_arc_const, b_ver_seg_par_arc_is_convex,
											zStart, dVerDistAlong, dVerHorizontalLength, dVerStartGradient, { verticalStation }, isParArc, nVerFragments, nVerFragmentsLength);
										VerSegmentsVec.push_back(verticalParabolicArcSegment);
									}
								} // end of VerSegmentsVec iteration

								  // Add vertical segments vector to verticalAlignment.
								verticalAlignment.verticalSegments_ = VerSegmentsVec;

								//	********************************************************************************************
								//	PART 4/4. Interpretation.
								//
								//		Step 1: Combine horizontal and vertical stations.
								//		Step 2: Calculate coordinates.
								//		Step 3: Create curve points vector with coordinates (x,y,z) for each station.
								//	********************************************************************************************

								// Step 1: Combine horizontal and vertical stations.

								// Declare necessary iterators, objects and vectors.
								std::vector<Station> AllStationsVec;
								std::vector<Segment> AllSegmentsVec;

								int it_h = 0; // iterator for horizontal segments vector: HorSegmentsVec
								int it_v = 0; // iterator for vertical segments vector: VerSegmentsVec

											  // Find out where to start adding stations. (Assuming horizontal and vertical alignment start at the same distance along!)
								double segmentStart = horizontalAlignment.dStartDistanceAlong_;

								// Iterate over horizontal and vertical segments, add stations according to fragments, sort and remove duplicate stations.
								int horizontalSegmentsVecSize = horizontalAlignment.horizontalSegments_.size();
								int verticalSegmentsVecSize = verticalAlignment.verticalSegments_.size();
								while(it_h <= horizontalSegmentsVecSize) {

									double dHorDistAlong = horizontalAlignment.horizontalSegments_[it_h].dStartDistanceAlong_; // Horizontal segment's start distance along
									double dHorFragmentsLength = horizontalAlignment.horizontalSegments_[it_h].fragmentsLength_; // Horizontal segment's length of fragments

									while(it_v <= verticalSegmentsVecSize) {

										double dVerDistAlong = verticalAlignment.verticalSegments_[it_v].dStartDistanceAlong_; // Vertical segment's start distance along
										double dVerFragmentsLength = verticalAlignment.verticalSegments_[it_v].fragmentsLength_; // Vertical segment's length of fragments

																																 // If segment start stations are not close, copy horizontal to vertical and vice-versa - but only where segments overlap.
										if(abs(dHorDistAlong - dVerDistAlong) <= 0.00000001)) {

										// Check which station is missing.
										if(dHorDistAlong<dVerDistAlong)
											verticalAlignment.verticalSegments_[it_v].insertStationAtSecondToLast(dHorDistAlong);
										else
											horizontalAlignment.horizontalSegments_[it_h].insertStationAtSecondToLast(dVerDistAlong);
										}
										else {
											// TODO: set greater value to smaller value for distAlong (e.g. function delete station) and adapt other values such as length
										}

										// Compare length of fragments, choose smaller value (-> more accurate representation).
										double dFragmentsLength = (dVerFragmentsLength > dHorFragmentsLength) ? dHorFragmentsLength : dVerFragmentsLength;

										// Find end of shorter segment.
										bool shorterSegmentIsVertical = horizontalSegmentEnd >= verticalSegmentEnd ? true : false;
										double horizontalSegmentEnd = dHorDistAlong + horizontalAlignment.horizontalSegments_[it_h].segmentLength_;
										double verticalSegmentEnd = dVerDistAlong + verticalAlignment.verticalSegments_[it_v].horizontalLength_;
										double shorterSegmentEnd = shorterSegmentIsVertical ? verticalSegmentEnd : horizontalSegmentEnd;

										// Create equidistant stations between startDistanceAlong and shorterSegmentEnd.
										double distance = segmentStart;
										while(distance < shorterSegmentEnd) {
											distance += dFragmentsLength;
											horizontalAlignment.horizontalSegments_[it_h].addStation(distance);
											verticalAlignment.verticalSegments_[it_v].addStation(distance);
										}

										// Add last station separately to guarantee existence.
										horizontalAlignment.horizontalSegments_[it_h].addStation(shorterSegmentEnd);
										verticalAlignment.verticalSegments_[it_v].addStation(shorterSegmentEnd);

										// In next iteration step, the end of the shorter segment here is where we continue to add stations in the longer segment.
										segmentStart = shorterSegmentEnd;

										// Proceed to next segment - depending on which is shorter.
										shorterSegmentIsVertical ? it_v++ : it_h++;

									} // end while it_v
								} // end while it_h

								  // Step 2: Calculate coordinates.
								  // Horizontal segments: x,y information. Vertical segments: z information. Calculate missing coordinates for each and combine via shared distance along.

								  // HORIZONTAL.

								  // Iterate over horizontal segments. Calculate coordinates according to segment type and segmentStations_.
								std::vector<HorizontalSegment>::iterator it_hor_segments = horizontalAlignment.horizontalSegments_.begin();
								for(; it_hor_segments != horizontalAlignment.horizontalSegments_.end(); ++it_hor_segments) {

									// Get segment start station.
									Station startStation = it_hor_segments.segmentStations_[0];
									double segmentLength = it_hor_segments.segmentLength_;

									// HORIZONTAL LINE SEGMENT.
									HorizontalLineSegment horizontalLineSeg =
										dynamic_pointer_cast<HorizontalLineSegment>(it_hor_segments);
									if(horizontalLineSeg) {

										// Iterate over stations in line segment.
										std::vector<Station>::iterator it_hor_stations = it_segment.segmentStations_.begin();
										for(; it_hor_stations != it_segment.segmentStations_.end(); ++it_hor_stations) {
											if(it_hor_stations.x_ == 0) { // Skip calculation if x,y coordinate is already there.
												it_hor_stations.x_ = startStation.x_ + segmentLength * cos(it_hor_segments.startDirection_);
												it_hor_stations.y_ = startStation.y_ + segmentLength * sin(it_hor_segments.startDirection_);
											}
										} // end stations iteration
									} // end if horizontalLineSeg

									  // HORIZONTAL CIRCULAR ARC SEGMENT.
									HorizontalCircArcSegment horizontalCircArcSeg =
										dynamic_pointer_cast<HorizontalCircArcSegment>(it_hor_segments);
									if(horizontalCircArcSeg) {
										// Get start station x,y , startDirection, radius and isCCW.
										double startStationX = horizontalCircArcSeg.segmentStations_[0].x_;
										double startStationY = horizontalCircArcSeg.segmentStations_[0].y_;
										double startDirection = horizontalCircArcSeg.startDirection_;
										double radius = horizontalCircArcSeg.radius_;
										bool isCCW = horizontalCircArcSeg.isCCW_;

										// Calculate circle center, given start point and direction (angle between tangent and x-axis).
										double radiusDirection = 0.;
										isCCW ? radiusDirection = startDirection + M_PI / 2 : radiusDirection = startDirection - M_PI / 2;
										double centerX = startCoords[0] + cos(radiusDirection) * radius;
										double centerY = startCoords[1] + sin(radiusDirection) * radius;

										// Angle between x-axis and vector(start, center).
										double angleAlpha = atan2(startStationY - centerY, startStationX - centerX);
										
										// Iterate over stations in circular arc segment.
										std::vector<Station>::iterator it_hor_stations = it_segment.segmentStations_.begin();
										for(; it_hor_stations != it_segment.segmentStations_.end(); ++it_hor_stations) {

											// Skip calculation if x,y coordinate is already there.
											if(it_hor_stations.x_ == 0) {

												// Calculate distance from start station to current station along alignment.
												double distanceStartToStation = it_hor_stations.distAlong_ - startStation.distAlong_;
												// Angle between x-axis and current station according to circle direction.
												if(clockwise) {
													angleBeta = angleAlpha - distanceStartToStation / radius;
												}
												else {
													angleBeta = angleAlpha + distanceStartToStation / radius;
												}
												// End coordinates.
												it_hor_stations.x_ = centerX + radius * cos(angleBeta);
												it_hor_stations.y_ = centerY + radius * sin(angleBeta);
											}

											/*buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getPosition(const double lerpParameter) const {
											// std::cout << "lerpParameter from getPos Arc: " << lerpParameter << std::endl;
											BLUE_ASSERT(lerpParameter >= 0.0, "Invalid lerp paramter.");
											BLUE_ASSERT(lerpParameter <= 1.0, "Invalid lerp paramter.");

											buw::Vector2d v1 = start_ - center_;
											buw::Vector2d v2 = end_ - center_;

											double alpha = 0;

											if (clockWise_)
											alpha = buw::calculateAngleBetweenVectors(v2, v1) * lerpParameter;
											else
											alpha = buw::calculateAngleBetweenVectors(v1, v2) * lerpParameter;

											if (clockWise_)
											v2 = Rotate(-alpha, v1);
											else
											v2 = Rotate(alpha, v1);

											return center_ + v2;
											}*/

										} // end if horizontalCircArcSeg

										  // HORIZONTAL TRANSITION CURVE SEGMENT.
										HorizontalTransCurveSegment horizontalTransCurveSeg =
											dynamic_pointer_cast<HorizontalTransCurveSegment>(it_hor_segments);

										if(horizontalTransCurveSeg) {
											// Calculation according to transition curve type: http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifctransitioncurvetype.htm
											double l = horizontalTransCurveSeg.segmentStations_[0].distAlong_;//distAlong;
											double L = horizontalTransCurveSeg.segmentLength_;
											double R = horizontalTransCurveSeg.endRadius_;

											// todo: set default?
											switch ( horizontalTransCurveSeg.transCurveType_ );

											case(BIQUADRATICPARABOLA):
												// Iterate over stations in horizontalTransCurveSegment.
												std::vector<Station>::iterator it_hor_stations = it_segment.segmentStations_.begin();
												for(; it_hor_stations != it_segment.segmentStations_.end(); ++it_hor_stations) {

													double l = it_hor_stations.distAlong_;
													// Skip calculation if x,y coordinate is already there.
													if(it_hor_stations.x_ == 0) {
														// x coordinate:
														double x = l;
														// y coordinate:
														if(x <= L / 2) {
															double y = pow(x, 4) / (6 * R * L * L);
														}
														else if(L / 2 < x && x <= L) {
															double y = -(pow(x, 4) / (6 * R * pow(L, 2)) + (2 * pow(x, 3)) / (3 * R * L)
																- pow(x, 2) / (2 * R) + (L * x) / (6 * R) - pow(L, 2) / (48 * R);
														}
													}
													// End coordinates.
													it_hor_stations.x_ = x;
													it_hor_stations.y_ = y;
												} // end stations iteration
												break;
											case(BLOSSCURVE):
												// Iterate over stations in horizontalTransCurveSegment.
												std::vector<Station>::iterator it_hor_stations = it_segment.segmentStations_.begin();
												for(; it_hor_stations != it_segment.segmentStations_.end(); ++it_hor_stations) {

													double l = it_hor_stations.distAlong_;
													// Skip calculation if x,y coordinate is already there.
													if(it_hor_stations.x_ == 0) {
														double teta = pow(l, 3) / (R * pow(L, 2)) - pow(l, 4) / (2 * R * pow(L, 3));
														// todo: integral? for loop
														double x = cos(teta) * l;
													}
												}
												break;
											case(CLOTHOIDCURVE):
												break;
											case(COSINECURVE):
												break;
											case(CUBICPARABOLA):
												break;
											case(SINECURVE):
												phi = (2 * //PI * l) / L;
													it_hor_segments.x_ = l*[1 - pow(L,2) / 32 *//PI^4*R^2]-(L^3/3840*PI^5*R^2)*[3*phi^5 - 20*phi^3 + 30*phi - (240-60*phi^2)*sin(phi)+30*cos(phi)*sin(phi)+120*phi*cos(phi)];
													it_hor_segments.y_ =
													break;

										} // end if horizontalTransCurveSeg
									} // end iteration over horizontal stations
								} // end iteration over horizontal segments

								  // VERTICAL.

								  // Iterate over vertical segments. Calculate z coordinates according to segment type and segmentStations_.
								std::vector<VerticalSegment>::iterator it_ver_segments = verticalAlignment.verticalSegments_.begin();
								for(; it_ver_segments != verticalAlignment.verticalSegments_.end(); ++it_ver_segments) {

									// Get start station.
									Station startStation = it_ver_segments.segmentStations_[0];

									// Iterate over stations in each segment.
									std::vector<Station>::iterator it_ver_stations = verticalAlignment.verticalSegments_.segmentStations_.begin();
									for(; it_ver_stations != verticalAlignment.verticalSegments_.segmentStations_.end(); ++it_ver_stations) {

										// VERTICAL LINE SEGMENT.
										VerticalLineSegment verticalLineSeg =
											dynamic_pointer_cast<VerticalLineSegment>(it_hor_segments);

										if(verticalLineSeg) {

											if(it_ver_stations.z_ == 0) { // Skip calculation if z coordinate is already there.
												startGradient = verticalLineSeg.startGradient_; // startGradient = dz/dx
												double distanceToStartStation = it_ver_stations.distAlong_ - it_hor_segments.startDistAlong_;
												it_ver_stations.z_ = startGradient * distanceToStartStation;
											} // end if z == 0
										} // end if verticalLineSeg

										  // VERTICAL CIRCULAR ARC SEGMENT.
										VerticalCircArcSegment verticalCircArcSeg =
											dynamic_pointer_cast<VerticalCircArcSegment>(it_hor_segments);

										if(verticalCircArcSeg) {

											// Calculate circle centre.
											distAlongCentre = verticalCircArcSeg.startDistAlong_ - verticalCircArcSeg.radius_ * verticalCircArcSeg.startDistAlong_ / sqrt(1 + verticalCircArcSeg.startGradient_ ^ 2);
											centreZ = verticalCircArcSeg.startZ_ + verticalCircArcSeg.radius_ * verticalCircArcSeg.startDistAlong_ / sqrt(1 + verticalCircArcSeg.startGradient_ ^ 2);

											// Calculate z coordinate for any point along horizontal length.
											if(it_ver_stations.z_ == 0) { // Skip calculation if z coordinate is already there.
												if(verticalCircArcSeg.isConvex_ == true) {
													it_ver_stations.z_ = verticalCircArcSeg.startDistAlong_ + sqrt(verticalCircArcSeg.radius_ ^ 2 - (verticalCircArcSeg.horizontalLength_ - distAlongCentre) ^ 2); // Crest (decreasing gradiant)
												else
													it_ver_stations.z_ = verticalCircArcSeg.startDistAlong_ - sqrt(verticalCircArcSeg.radius_ ^ 2 - (verticalCircArcSeg.horizontalLength_ - distAlongCentre) ^ 2); // Sag (increasing gradiant)
												} // end isConvex
											} // end z == 0
										} // end if verticalCircArcSeg

										  // PARABOLIC ARC SEGMENT
										VerticalParabolicArcSegment verticalParabolicArcSeg =
											dynamic_pointer_cast<VerticalParabolicArcSegment>(it_hor_segments);

										if(verticalParabolicArcSeg) {

											if(it_ver_stations.z_ == 0) { // Skip calculation if z coordinate is already there.
												double parabol_radius = verticalParabolicArcSeg.isConvex_ == true ? verticalParabolicArcSeg.parabolaConstant_ : -verticalParabolicArcSeg.parabolaConstant_; //***TO DO*** Check syntax in this line
												parabol_grad = (verticalParabolicArcSeg.horizontalLength_ - verticalParabolicArcSeg.startDistAlong_) / (parabol_radius + verticalParabolicArcSeg.startGradient_);
												it_ver_stations.z_ = (verticalParabolicArcSeg.horizontalLength_ - verticalParabolicArcSeg.startDistAlong_) * (parabol_grad + verticalParabolicArcSeg.startGradient_) / 2 + verticalParabolicArcSeg.startZ_;)
											} // end z == 0
										} // end if verticalParabolicArcSeg
									} // end vertical stations iteration
								} // end vertical segments iteration

								  // Step 3: Curve points vector with coordinates (x,y,z) for each station.

								  // Create curve points vector to store coordinates (x,y,z) for each station
								std::vector<carve::geom::vector<3> > curve_points;

								// Copy x,y,z information to curve_points vector:
								// Iterate over both lists of Segments

								auto it_hor_seg = horSegments.begin();
								auto it_ver_seg = verSegments.begin();

								for(; it_hor_seg != horSegments.end() && it_ver_seg != verSegments.end();
									it_hor_seg++, it_ver_seg++) {

									auto it_hor_stations = it_hor_seg.segmentStations_.begin();
									auto it_ver_stations = it_ver_seg.segmentStations_.begin();

									for(; it_hor_stations != it_hor_seg.segmentStations_.end() && it_ver_stations != it_ver_seg.segmentStations_.end();
										it_hor_stations++, it_ver_stations++) {

										curve_points.push_back({ it_hor_stations.x_, it_hor_stations.y_, it_ver_stations.z_ });
									}

								} // end of both segments iteration

								  // Add points to curve 
								segmentStartPoints.push_back(curve_points[0]);
								GeomUtils::appendPointsToCurve(curve_points, targetVec);

								return;

							} // end of IfcAlignmentCurve

								// IfcPolyline (SUBTYPE OF (IfcBoundedCurve)) 
								std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> poly_line =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(ifcCurve);
							if(poly_line) {
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& points = poly_line->m_Points;
								if(points.size() > 0) {
									convertIfcCartesianPointVector(points, targetVec);
									segmentStartPoints.push_back(carve::geom::VECTOR(
										points[0]->m_Coordinates[0]->m_value*length_factor,
										points[0]->m_Coordinates[1]->m_value*length_factor,
										0));
								}
								return;
							}

							// IfcTrimmedCurve (SUBTYPE OF(IfcBoundedCurve))
							std::shared_ptr<typename IfcEntityTypesT::IfcTrimmedCurve> trimmed_curve =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcTrimmedCurve>(bounded_curve);
							if(trimmed_curve) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve> basis_curve = trimmed_curve->m_BasisCurve;
								std::vector<carve::geom::vector<3> > basis_curve_points;

								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > curve_trim1_vec =
									trimmed_curve->m_Trim1;
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > curve_trim2_vec =
									trimmed_curve->m_Trim2;
								bool trimmed_sense_agreement = trimmed_curve->m_SenseAgreement;

								convertIfcCurve(basis_curve, basis_curve_points, segmentStartPoints,
									curve_trim1_vec, curve_trim2_vec, trimmed_sense_agreement);
								GeomUtils::appendPointsToCurve(basis_curve_points, targetVec);
								return;
							}

							// IfcBSplineCurve (SUBTYPE OF(IfcBoundedCurve))
							std::shared_ptr<typename IfcEntityTypesT::IfcBSplineCurve> bspline_curve =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineCurve>(bounded_curve);
							if(bspline_curve) {
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points =
									bspline_curve->m_ControlPointsList;

								std::vector<carve::geom::vector<3>> splinePoints;
								splinePoints.reserve(points.size());
								convertIfcCartesianPointVector(points, splinePoints);

								SplineConverterT<typename IfcEntityTypesT, IfcUnitConverterT>::convertIfcBSplineCurve(bspline_curve, splinePoints, targetVec);
								return;
							}
							throw UnhandledRepresentationException<IfcEntityTypesT>(bounded_curve);
						}

						// IfcConic
						std::shared_ptr<typename IfcEntityTypesT::IfcConic> conic =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcConic>(ifcCurve);
						if(conic) {
							// ENTITY IfcConic ABSTRACT SUPERTYPE OF(ONEOF(IfcCircle, IfcEllipse))
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement> conic_placement = conic->m_Position;
							carve::math::Matrix conic_position_matrix(carve::math::Matrix::IDENT());

							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(conic_placement);

							if(axis2placement2d) {
								PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement2D(axis2placement2d,
									conic_position_matrix, length_factor);
							}
							else if(dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(conic_placement)) {
								std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(conic_placement);

								PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(axis2placement3d,
									conic_position_matrix, length_factor);
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcCircle> circle =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircle>(conic);
							if(circle) {
								double circle_radius = 0.0;
								if(circle->m_Radius) {
									circle_radius = dynamic_pointer_cast<typename IfcEntityTypesT::IfcLengthMeasure>(circle->m_Radius)->m_value*length_factor;
								}

								carve::geom::vector<3> circle_center =
									conic_position_matrix*carve::geom::VECTOR(0, 0, 0);

								double trim_angle1 = 0.0;
								double trim_angle2 = M_PI*2.0;

								// check for trimming begin
								std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par1;
								if(trim1Vec.size() > 0) {
									if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_par1)) {
										trim_angle1 = trim_par1->m_value * plane_angle_factor;
									}
									else {
										std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point1;
										if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_point1)) {
											carve::geom::vector<3> trim_point;
											convertIfcCartesianPoint(trim_point1, trim_point);

											trim_angle1 = getAngleOnCircle(circle_center,
												circle_radius,
												trim_point);
										}
									}
								}

								if(trim2Vec.size() > 0) {
									// check for trimming end
									std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par2;
									if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, trim_par2)) {
										trim_angle2 = trim_par2->m_value * plane_angle_factor;
									}
									else {
										std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
										if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, ifc_trim_point)) {
											carve::geom::vector<3> trim_point;
											convertIfcCartesianPoint(ifc_trim_point, trim_point);
											trim_angle2 = getAngleOnCircle(circle_center,
												circle_radius,
												trim_point);
										}
									}
								}

								double start_angle = trim_angle1;
								double opening_angle = 0;

								if(senseAgreement) {
									if(trim_angle1 < trim_angle2) {
										opening_angle = trim_angle2 - trim_angle1;
									}
									else {
										// circle passes 0 angle
										opening_angle = trim_angle2 - trim_angle1 + 2.0*M_PI;
									}
								}
								else {
									if(trim_angle1 > trim_angle2) {
										opening_angle = trim_angle2 - trim_angle1;
									}
									else {
										// circle passes 0 angle
										opening_angle = trim_angle2 - trim_angle1 - 2.0*M_PI;
									}
								}

								if(opening_angle > 0) {
									while(opening_angle > 2.0*M_PI) {
										opening_angle -= 2.0*M_PI;
									}
								}
								else {
									while(opening_angle < -2.0*M_PI) {
										opening_angle += 2.0*M_PI;
									}
								}

								int num_segments = m_geomSettings->m_num_vertices_per_circle
									* (abs(opening_angle) / (2.0*M_PI));

								if(num_segments < m_geomSettings->m_min_num_vertices_per_arc) {
									num_segments = m_geomSettings->m_min_num_vertices_per_arc;
								}

								const double circle_center_x = 0.0;
								const double circle_center_y = 0.0;
								std::vector<carve::geom::vector<2> > circle_points;
								ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>::addArcWithEndPoint(circle_points, circle_radius, start_angle,
									opening_angle, circle_center_x,
									circle_center_y, num_segments);

								if(circle_points.size() > 0) {
									// apply position
									for(unsigned int i = 0; i < circle_points.size(); ++i) {
										carve::geom::vector<2>&  point = circle_points.at(i);
										carve::geom::vector<3> point3d(carve::geom::VECTOR(point.x, point.y, 0));
										point3d = conic_position_matrix * point3d;
										point.x = point3d.x;
										point.y = point3d.y;
									}

									GeomUtils::appendPointsToCurve(circle_points, targetVec);
									segmentStartPoints.push_back(carve::geom::VECTOR(circle_points.at(0).x,
										circle_points.at(0).y,
										0));
								}

								return;
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcEllipse> ellipse =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcEllipse>(conic);
							if(ellipse) {
								if(ellipse->m_SemiAxis1) {
									if(ellipse->m_SemiAxis2) {
										double xRadius = ellipse->m_SemiAxis1->m_value*length_factor;
										double yRadius = ellipse->m_SemiAxis2->m_value*length_factor;

										double radiusMax = std::max(xRadius, yRadius);
										int num_segments = m_geomSettings->m_num_vertices_per_circle;
										// TODO: adapt to model size and complexity

										// todo: implement clipping

										std::vector<carve::geom::vector<3> > circle_points;
										double angle = 0;
										for(int i = 0; i < num_segments; ++i) {
											circle_points.push_back(carve::geom::vector<3>(
												carve::geom::VECTOR(xRadius * cos(angle),
													yRadius * sin(angle),
													0)));
											angle += 2.0*M_PI / double(num_segments);
										}

										// apply position
										for(unsigned int i = 0; i < circle_points.size(); ++i) {
											carve::geom::vector<3>& point = circle_points.at(i);
											point = conic_position_matrix * point;
										}
										GeomUtils::appendPointsToCurve(circle_points, targetVec);

										//if( segmentStartPoints != NULL )
										{
											carve::geom::vector<3> pt0 = circle_points.at(0);
											segmentStartPoints.push_back(pt0);
										}
									}
								}
								return;
							}
							throw UnhandledRepresentationException<IfcEntityTypesT>(conic);
						}

						// IfcLine
						std::shared_ptr<typename IfcEntityTypesT::IfcLine> line =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcLine>(ifcCurve);
						if(line) {
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_line_point = line->m_Pnt;
							carve::geom::vector<3> line_origin;
							convertIfcCartesianPoint(ifc_line_point, line_origin);

							// line: lambda(u) = line_point + u*line_direction
							std::shared_ptr<typename IfcEntityTypesT::IfcVector> line_vec = line->m_Dir;
							if(!line_vec) {
								return;
							}
							std::shared_ptr<typename IfcEntityTypesT::IfcDirection> ifc_line_direction = line_vec->m_Orientation;

							std::vector<double> direction_ratios(ifc_line_direction->m_DirectionRatios.size());
							for(int i = 0; i < direction_ratios.size(); ++i) {
								direction_ratios[i] = ifc_line_direction->m_DirectionRatios[i];
							}

							carve::geom::vector<3> line_direction;
							if(direction_ratios.size() > 1) {
								if(direction_ratios.size() > 2) {
									line_direction = carve::geom::VECTOR(direction_ratios[0],
										direction_ratios[1],
										direction_ratios[2]);
								}
								else {
									line_direction = carve::geom::VECTOR(direction_ratios[0],
										direction_ratios[1], 0);
								}
							}
							line_direction.normalize();

							std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> line_magnitude = line_vec->m_Magnitude;
							double line_magnitude_value = line_magnitude->m_value*length_factor;

							// check for trimming at beginning of line
							double start_parameter = 0.0;
							std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par1;
							if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_par1)) {
								start_parameter = trim_par1->m_value;
								line_origin = line_origin + line_direction * start_parameter;
							}
							else {
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
								if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, ifc_trim_point)) {
									carve::geom::vector<3> trim_point;
									convertIfcCartesianPoint(ifc_trim_point, trim_point);

									carve::geom::vector<3> closest_point_on_line;
									GeomUtils::closestPointOnLine(trim_point, line_origin,
										line_direction, closest_point_on_line);

									if((closest_point_on_line - trim_point).length() < 0.0001) {
										// trimming point is on the line
										line_origin = trim_point;
									}
								}
							}
							// check for trimming at end of line
							carve::geom::vector<3> line_end;
							std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par2;
							if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, trim_par2)) {
								line_magnitude_value = trim_par2->m_value * length_factor;
								line_end = line_origin + line_direction * line_magnitude_value;
							}
							else {
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
								if(OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, ifc_trim_point)) {
									carve::geom::vector<3> trim_point;
									convertIfcCartesianPoint(ifc_trim_point, trim_point);

									carve::geom::vector<3> closest_point_on_line;
									GeomUtils::closestPointOnLine(trim_point, line_origin,
										line_direction, closest_point_on_line);

									if((closest_point_on_line - trim_point).length() < 0.0001) {
										// trimming point is on the line
										line_end = trim_point;
									}
								}
							}

							std::vector<carve::geom::vector<3> > points_vec;
							points_vec.push_back(line_origin);
							points_vec.push_back(line_end);

							GeomUtils::appendPointsToCurve(points_vec, targetVec);

							//if( segment_start_points != NULL )
							{
								segmentStartPoints.push_back(line_origin);
							}
							return;
						}

						// IfcOffsetCurve2D
						std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve2D> offset_curve_2d =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve2D>(ifcCurve);
						if(offset_curve_2d) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcOffsetCurve2D not implemented" << std::endl;
#endif
							return;
						}

						// IfcOffsetCurve3D
						std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve3D> offset_curve_3d =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve3D>(ifcCurve);
						if(offset_curve_3d) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcOffsetCurve3D not implemented" << std::endl;
#endif
							return;
						}

						// IfcPCurve: ***** TO DO *****
						/*std::shared_ptr<IfcPcurve> pcurve = dynamic_pointer_cast<IfcPcurve>(ifcCurve);
						if( pcurve )
						{
						// TODO: implement
						return;
						}*/
						throw UnhandledRepresentationException<IfcEntityTypesT>(ifcCurve);
					}

				// Functions
				void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& loops,
					std::vector<carve::geom::vector<2>>& segmentStartPoints) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim2Vec;
					convertIfcCurve2D(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
				}

				void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& targetVec,
					std::vector<carve::geom::vector<2>>& segmentStartPoints,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					bool senseAgreement) const
				{
					std::vector<carve::geom::vector<3>> target_vec_3d;
					std::vector<carve::geom::vector<3>> segment_start_points_3d;

					convertIfcCurve(ifcCurve, target_vec_3d, segment_start_points_3d,
						trim1Vec, trim2Vec, senseAgreement);

					for(int i = 0; i < target_vec_3d.size(); ++i) {
						carve::geom::vector<3>& point_3d = target_vec_3d[i];
						targetVec.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
					for(int i = 0; i < segment_start_points_3d.size(); ++i) {
						carve::geom::vector<3>& point_3d = segment_start_points_3d[i];
						segmentStartPoints.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
				}

				void convertIfcPolyline(const std::shared_ptr<typename IfcEntityTypesT::IfcPolyline>& polyLine,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					convertIfcCartesianPointVector(polyLine->m_Points, loop);
				}

				void convertIfcLoop(const std::shared_ptr<typename IfcEntityTypesT::IfcLoop>& loop,
					std::vector<carve::geom::vector<3>>& loopPoints) const
				{
					const std::shared_ptr<typename IfcEntityTypesT::IfcPolyLoop> polyLoop =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyLoop>(loop);
					if(polyLoop) {
						const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& ifcPoints = polyLoop->m_Polygon;
						convertIfcCartesianPointVectorSkipDuplicates(ifcPoints, loopPoints);

						// if first and last point have same coordinates, remove last point
						while(loopPoints.size() > 2) {
							carve::geom3d::Vector& first = loopPoints.front();
							carve::geom3d::Vector& last = loopPoints.back();

							if(abs(first.x - last.x) < 0.00000001) {
								if(abs(first.y - last.y) < 0.00000001) {
									if(abs(first.z - last.z) < 0.00000001) {
										loopPoints.pop_back();
										continue;
									}
								}
							}
							break;
						}
						return;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcEdgeLoop> edgeLoop =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeLoop>(loop);
					if(edgeLoop) {
						//std::vector<carve::geom::vector<3>> edgePoints;

						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge>>& edgeList = edgeLoop->m_EdgeList;
						// go through every edge in the edge list
						for(auto it_edge = edgeList.begin(); it_edge != edgeList.end(); ++it_edge) {
							// edge loop consists of many oriented edges
							std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge> orientedEdge = (*it_edge);
							// which are described by the type of its edge element object
							std::shared_ptr<typename IfcEntityTypesT::IfcEdge>& edgeElement = orientedEdge->m_EdgeElement;

							std::shared_ptr<typename IfcEntityTypesT::IfcEdgeCurve> edgeCurve =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeCurve>(edgeElement);

							if(edgeCurve) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& curveGeom = edgeCurve->m_EdgeGeometry;
								std::vector<carve::geom::vector<3>> segmentStartPoints;

								convertIfcCurve(curveGeom, loopPoints, segmentStartPoints);

								continue;
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcSubedge> subEdge =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSubedge>(edgeElement);

							if(subEdge) {
								std::cout << "ERROR\t| IfcSubedge not implemented" << std::endl;
								continue;
							}

							std::cout << "ERROR\t| Entity " << orientedEdge->classname() << " not handled" << std::endl;

							// every edge consists of one start and end vertex
							//std::shared_ptr<typename IfcEntityTypesT::IfcVertex>& edgeStartVertex = edgeElement->m_EdgeStart;
							//std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> edgeStartVertexPoint =
							//	dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(edgeStartVertex);
							//
							//if (edgeStartVertexPoint)
							//{
							//	if (edgeStartVertexPoint->m_VertexGeometry)
							//	{
							//		std::shared_ptr<typename IfcEntityTypesT::IfcPoint>& startPoint =
							//			edgeStartVertexPoint->m_VertexGeometry;
							//		std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifcPoint =
							//			dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(startPoint);
							//		if (!ifc_point)
							//		{
							//			// TODO: could be also  IfcPointOnCurve, IfcPointOnSurface
							//			continue;
							//		}
							//		// TODO: implement
							//	}
							//}

						}
					}
				}

				void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
					carve::geom::vector<3> & point) const
				{
					double length_factor = m_unitConverter->getLengthInMeterFactor();
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords1 = ifcPoint->m_Coordinates;
					if(coords1.size() > 2) {
						double x = coords1[0]->m_value * length_factor;
						double y = coords1[1]->m_value * length_factor;
						double z = coords1[2]->m_value * length_factor;

						point = carve::geom::VECTOR(x, y, z);
					}
					else if(coords1.size() > 1) {
						// round to 0.1 mm
						double x = coords1[0]->m_value * length_factor;
						double y = coords1[1]->m_value * length_factor;

						point = carve::geom::VECTOR(x, y, 0.0);
					}
				}

				void convertIfcCartesianPointVector(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					const double length_factor = m_unitConverter->getLengthInMeterFactor();
					const unsigned int num_points = points.size();
					for(unsigned int i_point = 0; i_point < num_points; ++i_point) {
						const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords =
							points[i_point]->m_Coordinates;

						if(coords.size() > 2) {
							double x = coords[0]->m_value * length_factor;
							double y = coords[1]->m_value * length_factor;
							double z = coords[2]->m_value * length_factor;

							loop.push_back(carve::geom::VECTOR(x, y, z));
						}
						else if(coords.size() > 1) {

							double x = coords[0]->m_value * length_factor;
							double y = coords[1]->m_value * length_factor;

							loop.push_back(carve::geom::VECTOR(x, y, 0.0));
						}
						else {
							std::cout << "convertIfcCartesianPointVector: ifc_pt->m_Coordinates.size() != 2"
								<< std::endl;
						}
					}
				}

				// @brief: returns the corresponding angle (radian, 0 is to the right) if the given point lies on the circle. If the point does not lie on the circle, -1 is returned.
				static double getAngleOnCircle(const carve::geom::vector<3>& circleCenter,
					double circleRadius,
					const carve::geom::vector<3>& trimPoint)
				{
					double result_angle = -1.0;
					carve::geom::vector<3> center_trim_point = trimPoint - circleCenter;
					if(abs(center_trim_point.length() - circleRadius) < 0.0001) {
						carve::geom::vector<3> center_trim_point_direction = center_trim_point;
						center_trim_point_direction.normalize();
						double cos_angle = carve::geom::dot(center_trim_point_direction, carve::geom::vector<3>(carve::geom::VECTOR(1.0, 0, 0)));

						if(abs(cos_angle) < 0.0001) {
							if(center_trim_point.y > 0) {
								result_angle = M_PI_2;
							}
							else if(center_trim_point.y < 0) {
								result_angle = M_PI*1.5;
							}
						}
						else {
							if(center_trim_point.y > 0) {
								result_angle = acos(cos_angle);
							}
							else if(center_trim_point.y < 0) {
								result_angle = 2.0*M_PI - acos(cos_angle);
							}
						}
					}
					return result_angle;
				}

				void convertIfcCartesianPointVectorSkipDuplicates(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints,
					std::vector<carve::geom::vector<3> >& loop) const
				{
					const double length_factor = m_unitConverter->getLengthInMeterFactor();
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >::const_iterator it_cp;
					int i = 0;
					carve::geom::vector<3>  vertex_previous;
					for(it_cp = ifcPoints.begin(); it_cp != ifcPoints.end(); ++it_cp, ++i) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = (*it_cp);
						const int cp_id = cp->getId();
						double x = 0.0, y = 0.0, z = 0.0;
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords = cp->m_Coordinates;

						if(coords.size() > 2) {
							x = coords[0]->m_value * length_factor;
							y = coords[1]->m_value * length_factor;
							z = coords[2]->m_value * length_factor;
						}
						else if(coords.size() > 1) {

							x = coords[0]->m_value * length_factor;
							y = coords[1]->m_value * length_factor;
						}

						carve::geom::vector<3>  vertex(carve::geom::VECTOR(x, y, z));

						// skip duplicate vertices
						if(it_cp != ifcPoints.begin()) {
							if(abs(vertex.x - vertex_previous.x) < 0.00000001) {
								if(abs(vertex.y - vertex_previous.y) < 0.00000001) {
									if(abs(vertex.z - vertex_previous.z) < 0.00000001) {
										// TODO: is it better to report degenerated loops, or to just omit them?
										continue;
									}
								}
							}
						}
						loop.push_back(vertex);
						vertex_previous = vertex;
					}
				}

				static void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
					carve::geom::vector<3> & point,
					double lengthFactor)
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>>& coords1 = ifcPoint->m_Coordinates;
					if(coords1.size() > 2) {
						double x = coords1[0]->m_value * lengthFactor;
						double y = coords1[1]->m_value * lengthFactor;
						double z = coords1[2]->m_value * lengthFactor;

						point = carve::geom::VECTOR(x, y, z);
					}
					else if(coords1.size() > 1) {
						// round to 0.1 mm
						double x = coords1[0]->m_value * lengthFactor;
						double y = coords1[1]->m_value * lengthFactor;

						point = carve::geom::VECTOR(x, y, 0.0);
					}
				}

			protected:
				std::shared_ptr<GeometrySettings>	m_geomSettings;
				std::shared_ptr<IfcUnitConverterT>	m_unitConverter;
			};
		}
	}


#endif
