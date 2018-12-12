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

#include <BlueFramework/Core/Diagnostics/log.h>

#include "OpenInfraPlatform/ExpressBinding/vectorUtilites.h"

#include "OpenInfraPlatform/IFC4X2_DRAFT_1/model/Model.h"

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

							// TODO 1: For errors/warnings, add segment ID (or other information) -> int m_id member of IfcAlignment1x1Entity getId()
							// TODO 2: Calculate coordinates
							// Ifc4x1 = IfcAlignment1x1
							// check if already implemented: OIP->OIP.Infrastructure->OIP->Infrastructure->Alignment
						{
							// Declaration of station struct
							struct Station {
							public:
								double distAlong;				// horizontal distance along
								double x, y, z;					// 3D-coordinates of station
								int    fragmentscount;			// number of fragments within a segment according to segment type (see below)
								double fragmentslength;			// length of fragments within a segment 
								enum   segmentType { isLine, isCircArc, isTrans, isParArc } segType;

								//Default constructor
								Station() = default;

								Station(double distAlong, double x, double y, double z, int fragmentscount, double fragmentslength, segmentType type)
									:distAlong(distAlong), x(x), y(y), z(z), fragmentscount(fragmentscount), fragmentslength(fragmentslength), segType(type)
								{
								}
							};

							// (A) IfcAlignment2DHorizontal
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignment_curve->m_Horizontal;
							if(!horizontal) {
								BLUE_LOG(error) << "No IfcAlignment2DHorizontal in IfcAlignmentCurve.";
								return;
							}

							// m_StartDistAlong type IfcLengthMeasure [0:1]
							double dStartDistanceAlong = 0.; // if omited (standard), it is set to zero
							typename IfcEntityTypesT::IfcLengthMeasure& horStartDistAlong = horizontal->m_StartDistAlong;
							if(horStartDistAlong)
								dStartDistanceAlong = horStartDistAlong.m_value * length_factor;

							// m_Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if(horizontal->m_Segments.empty()) {
								BLUE_LOG(error) << "No segments in IfcAlignment2DHorizontal.";
								return;
							}

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment> > horSegments =
								horizontal->m_Segments;

							if(horSegments.size() < 1) {
								BLUE_LOG(error) << "Not enough segments in IfcAlignment2DHorizontal.";
								return;
							}

							// Declare stations vector that combines horizontal and vertical stations
						    std::vector<Station> stations;

							// Declaration of horizontal stations and fragments vectors.

							std::vector<Station> horStations;
							int nHorFragments = 0;

							// Definition of horizontal distance along.
							double dHorStartDistanceAlong = 0.; // todo: Add dStartDistanceAlong to DistanceAlong Vertical;

							// Iterate over horizontal segments.
							for(auto it_segment : horSegments) {

								//IfcAlignment2DHorizontalSegment (m_TangentialContinuity type IfcBoolean [0:1], m_StartTag type IfcLabel [0:1], m_EndTag type IfcLabel [0:1], m_CurveGeometry type IfcCurveSegment2D [1:1])

								/* Uncomment if needed:
								std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> h_tangential_continuity =
									it_segment->m_TangentialContinuity;
								std::shared_ptr<typename IfcEntityTypesT::IfcLabel> h_start_tag =
									it_segment->m_StartTag;
								std::shared_ptr<typename IfcEntityTypesT::IfcLabel> h_end_tag =
									it_segment->m_EndTag; */

								std::shared_ptr<typename IfcEntityTypesT::IfcCurveSegment2D> horCurveGeometry =
									it_segment->m_CurveGeometry;

								// IfcCurveSegment2D
								if(!horCurveGeometry) {
									BLUE_LOG(error) << "No curve geometry in IfcAlignment2DHorizontalSegment (Segment ID: " << it_segment->getId() << ")."; // TODO for all warnings/errors (inherits from IfcAlignment1x1Entity);
									return;
								}

								// Check for curve_seg_start_point, curve_seg_start_direction, curve_seg_length

								// m_StartPoint type IfcCartesianPoint [1:1]
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> curveSegStartPoint =
									horCurveGeometry->m_StartPoint;
								if(!curveSegStartPoint) {
									BLUE_LOG(error) << "No curve segment start point in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// m_StartDirection type IfcPlaneAngleMeasure [1:1]
							    typename IfcEntityTypesT::IfcPlaneAngleMeasure& curveSegStartDirection = horCurveGeometry->m_StartDirection;
								if(!curveSegStartDirection) {
									BLUE_LOG(error) << "No curve segment start direction in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// m_SegmentLength type IfcPositiveLengthMeasure [1:1]
								typename IfcEntityTypesT::IfcPositiveLengthMeasure& curveSegLength = horCurveGeometry->m_SegmentLength;
								if(!(curveSegLength > 0)) {
									BLUE_LOG(error) << "No curve segment length in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// Interpret curve_seg_start_point, curve_seg_start_direction, curve_seg_length
								double xStart = 0., yStart = 0.;
								xStart = curveSegStartPoint->m_Coordinates[0]->m_value * length_factor;
								yStart = curveSegStartPoint->m_Coordinates[1]->m_value * length_factor;
								dHorStartDistanceAlong = dHorStartDistanceAlong + curveSegLength;
								double dStartDirection = curveSegStartDirection * plane_angle_factor;

								// Segment types: IfcLineSegment2D, IfcCircularArcSegment2D and IfcTransitionCurveSegment2D: inherit m_StartPoint, m_StartDirection, m_SegmentLength from IfcCurveSegment2D
								// http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifccurvesegment2d.htm
								std::shared_ptr<typename IfcEntityTypesT::IfcLineSegment2D> line_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcLineSegment2D>(horCurveGeometry);

								std::shared_ptr<typename IfcEntityTypesT::IfcCircularArcSegment2D> circular_arc_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircularArcSegment2D>(horCurveGeometry);

								std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
									dynamic_pointer_cast<typename IfcEntityTypesT::IfcTransitionCurveSegment2D>(horCurveGeometry);

								// Set amount of fragments (number of points to be added between stations) according to segment type
								// Vector of stations 

								if(line_segment_2D) {
									nHorFragments = 0;
								    horStations.push_back(Station(dHorStartDistanceAlong, xStart, yStart, 0, nHorFragments, dHorStartDistanceAlong, Station::isLine));
								}

								if (circular_arc_segment_2D || trans_curve_segment_2D) {
									nHorFragments = m_geomSettings->m_min_num_vertices_per_arc;
								    double fragmentLength = dHorStartDistanceAlong / nHorFragments;
								    if (circular_arc_segment_2D)
									    horStations.push_back(Station(dHorStartDistanceAlong, xStart, yStart, 0, nHorFragments, fragmentLength, Station::isCircArc));
								    if (trans_curve_segment_2D)
									    horStations.push_back(Station(dHorStartDistanceAlong, xStart, yStart, 0, nHorFragments, fragmentLength, Station::isTrans));

								}
							} // end for each horizontal segment

							// (B) IfcAlignment2DVertical
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVertical> vertical = alignment_curve->m_Vertical;
							if(!vertical) {
								BLUE_LOG(warning) << "No IfcAlignment2DVertical in IfcAlignmentCurve.";
								// Handle as horizontal alignment only.
							}
							else {
								// m_Segments type IfcAlignment2DVerticalSegment L[1:?]
								if(vertical->m_Segments.empty()) {
									BLUE_LOG(error) << "No segments in IfcAlignment2DVertical.";
									return;
								}

								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment> > verSegments =
									vertical->m_Segments;

								if(verSegments.size() < 1) {
									BLUE_LOG(error) << "Not enough segments in IfcAlignment2DVertical.";
									return;
								}

								// Declaration of vertical stations and accuracy vectors.
								std::vector<Station> verStations;
								int nVerFragments = 0;

								// Iterate over vertical segments.
								auto it_segment = verSegments.begin();

								for (auto it_segment : verSegments) {

									// IfcAlignment2DVerticalSegment (m_TangentialContinuity type IfcBoolean [0:1], m_StartTag type IfcLabel [0:1], m_EndTag type IfcLabel [0:1])	

									/* Uncomment if needed.
									std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > v_tangential_continuity =
										it_segment->m_TangentialContinuity;
									std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLabel> > v_start_tag =
										it_segment->m_StartTag;
									std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLabel> > v_end_tag =
										it_segment->m_EndTag; */

										// Check for verDistAlong, verHorizontalLength, verStartHeight, verStartGradient

										// m_StartDistAlong type IfcLengthMeasure [1:1]
									typename IfcEntityTypesT::IfcLengthMeasure& verDistAlong = it_segment->m_StartDistAlong;
									if(verDistAlong > 0) {
										BLUE_LOG(error) << "No start distance along in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_HorizontalLength type IfcPositiveLengthMeasure [1:1]
									typename IfcEntityTypesT::IfcPositiveLengthMeasure& verHorizontalLength = it_segment->m_HorizontalLength;
									if(verHorizontalLength > 0) {
										BLUE_LOG(error) << "No horizontal length in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_StartHeight type IfcLengthMeasure [1:1]
									typename IfcEntityTypesT::IfcLengthMeasure& verStartHeight = it_segment->m_StartHeight;
									if(verStartHeight > 0) {
										BLUE_LOG(error) << "No start height in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// m_StartGradient type IfcRatioMeasure [1:1]
									typename IfcEntityTypesT::IfcRatioMeasure& verStartGradient = it_segment->m_StartGradient;
									if(verStartGradient > 0) {
										BLUE_LOG(error) << "No start gradient in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									// Interpret verDistAlong, verHorizontalLength, verStartHeight, verStartGradient
									double dVerDistAlong = verDistAlong * length_factor;
									double zStart = verStartHeight * length_factor;
									double dVerHorizontalLength = verHorizontalLength * length_factor;
									double dVerStartGradient = verStartGradient;

									// Segment types: IfcAlignment2DVerSegCircularArc, IfcAlignment2DVerSegLine, IfcAlignment2DVerSegParabolicArc (all inherit m_TangentialContinuity, m_StartTag, m_EndTag, m_StartDistAlong, m_HorizontalLength, m_StartHeight, m_StartGradient from IfcAlignment2DVerticalSegment)

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>(it_segment);

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegLine> ver_seg_line_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>(it_segment);

									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc>(it_segment);

									// Set number of fragments (number of stations to be added within segment) according to segment type
									// Vector of stations 

									if (v_seg_circ_arc_2D || v_seg_par_arc_2D) {
										nVerFragments = m_geomSettings->m_min_num_vertices_per_arc;
									    double fragmentLength = dVerDistAlong / nVerFragments;
									    if (v_seg_circ_arc_2D)
										    verStations.push_back(Station(dVerDistAlong, 0, 0, zStart, nVerFragments, fragmentLength, Station::isCircArc));

									    if (v_seg_par_arc_2D)
										    verStations.push_back(Station(dVerDistAlong, 0, 0, zStart, nVerFragments, fragmentLength, Station::isParArc));
								    }

									if(ver_seg_line_2D) {
										nVerFragments = 0;
									    verStations.push_back(Station(dVerDistAlong, 0, 0, zStart, nVerFragments, dVerDistAlong, Station::isLine));
									}

									

								} // end for each vertical segment


								// (C) Interpretation: Combine IfcAlignment2DHorizontal & IfcAlignment2DVertical to get 3D-coordinates

								// 1. Stations: Combine h_stations, v_stations, sort and remove duplicates

								int it_s = 0;
								int it_h = 0;
								int it_v = 0;
																
								while(it_h <= horStations.size()) {
									double dHorDistAlong = horStations[it_h].distAlong;
									double dHorFragmentsCount = horStations[it_h].fragmentscount;

									while(it_v <= verStations.size()) {
										double dVerDistAlong = verStations[it_v].distAlong;
										double dVerFragmentsCount = verStations[it_v].fragmentscount;

										// If stations are close, use horizontal distance along from horizontal alignment.
										if(abs(dHorDistAlong - dVerDistAlong) <= 0.00000001) {
											stations[it_s].distAlong = dHorDistAlong;

											// Copy greater amount of fragments.
											if(dHorFragmentsCount >= dVerFragmentsCount) {
												stations[it_s].fragmentscount = dHorFragmentsCount;
											}
											else {
												stations[it_s].fragmentscount = dVerFragmentsCount;
											}

											it_h++;
											it_v++;
										}

										// If stations are not close, horizontal is first:
										else if(dHorDistAlong < dVerDistAlong) {
											stations[it_s].distAlong = dHorDistAlong;

											// Copy greater amount of fragments. Compare h_station to overlapping previous v_station.
											if(dHorFragmentsCount >= verStations[it_v - 1].fragmentscount) {
												stations[it_s].fragmentscount = dHorFragmentsCount;
											}
											else {
												stations[it_s].fragmentscount = verStations[it_v - 1].fragmentscount;
											}
											it_h++;
										}

										// If stations are not close, vertical is first:
										else {
											stations[it_s].distAlong = dVerDistAlong;

											// Copy greater amount of fragments. Compare v_station to overlapping previous h_station.
											if(dVerFragmentsCount >= horStations[it_h - 1].fragmentscount) {
												stations[it_s].fragmentscount = dVerFragmentsCount;
											}
											else {
												stations[it_s].fragmentscount = horStations[it_h - 1].fragmentscount;
											}
											it_v++;

										}
										it_s++;
									}
								}
							}

							// 2. Add stations according to amount of fragments.
							std::vector<Station> allStations;
							allStations[0] = stations[0];
							int nCounter = 1;

							for(int it_stations = 1; it_stations <= stations.size(); it_stations++) {
								// If amount of fragments = 0 (e.g. line segment)
								if(stations[it_stations - 1].fragmentscount == 0) {
									allStations[nCounter].distAlong = stations[it_stations].distAlong; //distance along
									allStations[nCounter].fragmentslength = std::abs(allStations[nCounter].distAlong - allStations[nCounter - 1].distAlong); // fragment length
									nCounter++;
								}
								// If amount of fragments != 0 (e.g. circular arc, parabolic arc,...)
								else {
									double station_length = std::abs(stations[it_stations].distAlong - stations[it_stations - 1].distAlong);
									double station_increment = station_length / stations[it_stations].fragmentscount;

									for(int it = 1; it <= stations[it_stations].fragmentscount; it++) {
										nCounter++;
									    /// What is this supposed to do?
									    // allStations[nCounter] = 0;
										allStations[nCounter].distAlong = allStations[nCounter - 1].distAlong + station_increment; // distance along
										allStations[nCounter].fragmentslength = station_increment; // fragment length
									}
								}
							}//end of stations iteration

							// 3. Calculate coordinates *** TO DO ***

							// Iterate over all stations.
							for(auto it_all : allStations) {

								// switch(it_all.segType) {
								// case(isLine)
								// case(isCircArc)
								// case(isTrans)
								// case(isParArc)
								// }

							}//end of allStations iteration

							// Create curve points vector to store coordinates (x,y,z) for each station
							//std::vector< carve::geom::vector<3> > curve_points = carve::geom::VECTOR(x, y, z);; // todo check
							// curve_points.x=
							//curve_points_x = curve_points[0];
							//curve_points_y = curve_points[1];
							//curve_points_z = curve_points[2];
							//
							//// 4. Add points to curve
							//segmentStartPoints.push_back(curve_points[0]);
							//GeomUtils::appendPointsToCurve(curve_points, targetVec);

							// Additional members -> necessary for coordinate calculations.

							/*if(line_segment_2D)

							if(circular_arc_segment_2D)
								{
									// m_Radius type IfcPositiveLengthMeasure [1:1]
									std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> > circ_arc_radius =
										circular_arc_segment_2D->m_Radius;
									if(!circ_arc_radius) {
										BLUE_LOG(error) << "No radius in IfcCircularArcSegment2D";
										return;
									}

									// m_IsCCW type IfcBoolean [1:1]
									std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > circ_arc_is_CCW =
										circular_arc_segment_2D->m_IsCCW;
									if(!circ_arc_is_CCW) {
										BLUE_LOG(error) << "No direction information for IfcCircularArcSegment2D (counterclockwise/clockwise)";
										return;
									}

							}

							if(ver_seg_line_2D)

							if(v_seg_circ_arc_2D) {

								// m_Radius type IfcPositiveLengthMeasure [1:1]
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> > v_seg_circ_arc_radius =
									v_seg_circ_arc_2D->m_Radius;
								if(!v_seg_circ_arc_radius) {
									BLUE_LOG(error) << "No radius in IfcAlignment2DVerSegCircularArc"
										return;
								}

								// m_IsConvex type IfcBoolean [1:1]
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > v_seg_circ_arc_is_convex =
									v_seg_circ_arc_2D->m_IsConvex;
								if(!v_seg_circ_arc_is_convex) {
									BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegCircularArc (convex/concave)"
										return;
								}

							if(v_seg_par_arc_2D)
							{
								// m_ParabolaConstant type IfcPositiveLengthMeasure [1:1]
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> > v_seg_par_arc_const =
									v_seg_par_arc_2D->m_ParabolaConstant;
								if(!v_seg_par_arc_const) {
									BLUE_LOG(error) << "No parabola constant in IfcAlignment2DVerSegParabolicArc"
										return;
								}

								// m_IsConvex type IfcBoolean [1:1]
								std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcBoolean> > v_seg_par_arc_is_convex =
									v_seg_par_arc_2D->m_IsConvex;
								if(!v_seg_par_arc_is_convex) {
									BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegParabolicArc (convex/concave)"
										return;
								}
							}*/
							return;
						}


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
							bool trimmed_sense_agreement = *(trimmed_curve->m_SenseAgreement);

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
								circle_radius = (circle->m_Radius) * length_factor;
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
									double xRadius = ellipse->m_SemiAxis1*length_factor;
									double yRadius = ellipse->m_SemiAxis2*length_factor;

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
							direction_ratios[i] = *(ifc_line_direction->m_DirectionRatios[i]);
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

					    double line_magnitude_value = line_vec->m_Magnitude * length_factor;

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
