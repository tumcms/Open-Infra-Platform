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

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {
			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT
			>
				class CurveConverterT
			{
			public:
				CurveConverterT(std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<IfcUnitConverterT> unitConverter)
					:
					geomSettings(geomSettings),
					unitConverter(unitConverter)
				{
				}

				virtual ~CurveConverterT()
				{

				}

				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve> ifcCurve,
					std::vector<carve::geom::vector<3>>& loops,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim2Vec;
					convertIfcCurve(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
				}

				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve> ifcCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim1Vec,
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim2Vec,
					bool senseAgreement) const
				{
					double length_factor = unitConverter->getLengthInMeterFactor();
					double plane_angle_factor = unitConverter->getAngleInRadianFactor();
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing IfcCurve #" << ifcCurve->getId();
#endif
					/*	CurveConverter.h (IFC 4x1)

					IfcCurve

					IfcBoundedCurve				https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcboundedcurve.htm
						IfcAlignmentCurve
						IfcBsplineCurve
							IfcBsplineCurveWithKnots*
								IfcRationalBsplineCurveWithKnots*
						IfcCompositeCurve
							IfcCompositeCurveOnSurface*
						IfcIndexedPolycurve*
						IfcPolyline
						IfcTrimmedCurve

					IfcConic					https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcconic.htm
						IfcCircle
						IfcEllipse

					IfcLine						https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcline.htm

					IfcOffsetCurve				https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcoffsetcurve.htm
						IfcOffsetCurve2D*
						IfcOffsetCurve3D*
						IfcOffsetCurveByDistances*

					IfcPcurve*					https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcpcurve.htm

					IfcSurfaceCurve				https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcsurfacecurve.htm
						IfcIntersectionCurve*
						IfcSeamCurve*

					Functions

					*: not implemented in CurveConverter.h

					*/

					// ************************************************************************************************************************************	//
					//	IfcBoundedCurve SUBTYPE of IfcCurve																									//
					//	ABSTRACT SUPERTYPE of IfcAlignmentCurve, IfcBsplineCurve, IfcCompositeCurve, IfcIndexedPolycurve, IfcPolyline, IfcIfcTrimmedCurve	//
					// ************************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> bounded_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(ifcCurve);
					if (bounded_curve)
					{
						// (1/6) IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignmentCurve> alignment_curve =
							std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignmentCurve>(bounded_curve);
						if (alignment_curve) {

							// Step 1: Get segment information from horizontal and vertical alignments.

							std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DHorizontal> horizontal = alignment_curve->Horizontal.lock();

							if (!horizontal)
							{
								BLUE_LOG(error) << "No IfcAlignment2DHorizontal in IfcAlignmentCurve.";
								return;
							}

							// StartDistAlong type IfcLengthMeasure [0:1]
							double horStartDistAlong = 0.0;
							double hStartDistAlong = horizontal->StartDistAlong;

							if (hStartDistAlong) {
								horStartDistAlong = hStartDistAlong * length_factor;
							}

							// Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if (horizontal->Segments.empty()) {
								BLUE_LOG(error) << "Not enough segments in IfcAlignment2DHorizontal. (Segment ID: " << horizontal->getId() << ").";
								return;
							}

							auto vertical = alignment_curve->Vertical;
							if (!vertical) {
								BLUE_LOG(warning) << "No IfcAlignment2DVertical in IfcAlignmentCurve (Segment ID: " << vertical->getId() << ").";
								// TO DO: Handle as horizontal alignment only.
							}

							double startDistAlong = 0.;
							double fragmentsLength = 0.;
							std::vector<double> stations;
							// Set first station to beginning of first segment.
							stations.push_back(startDistAlong);
							double overlappingLengthOfSegments = 0.;

							bool isShorterSegmentHorizontal = false;
							auto it_horizontal_segment = horizontal->Segments.begin();
							auto it_vertical_segment = vertical->Segments.begin();

							auto ver_end_it = vertical->Segments.end();

							// Iterate over horizontal and vertical segments
							while (it_horizontal_segment != horizontal->Segments.end() && it_vertical_segment != vertical->Segments.end())
							{
								//IfcAlignment2DHorizontalSegment (TangentialContinuity type IfcBoolean [0:1], StartTag type IfcLabel [0:1], EndTag type IfcLabel [0:1], CurveGeometry type IfcCurveSegment2D [1:1])
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcCurveSegment2D> horCurveGeometry =
									(*it_horizontal_segment)->CurveGeometry.lock();

								// Get and interpret information from IfcCurveSegment2D.
								if (!horCurveGeometry) {
									BLUE_LOG(error) << "No curve geometry in IfcAlignment2DHorizontalSegment (Segment ID: " << (*it_horizontal_segment)->getId() << ").";
									return;
								}

								// SegmentLength type IfcPositiveLengthMeasure [1:1]
								if (horCurveGeometry->SegmentLength <= 0) {
									BLUE_LOG(error) << "No curve segment length in IfcCurveSegment2D (Segment ID: " << (*it_horizontal_segment)->getId() << ").";
									return;
								}
								double dHorizontalSegLength = horCurveGeometry->SegmentLength * length_factor;

								// Step 2: Get horizontal segment type and store number and length of fragments.

								// Segment types: IfcLineSegment2D, IfcCircularArcSegment2D and IfcTransitionCurveSegment2D
								// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifccurvesegment2d.htm
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcLineSegment2D> line_segment_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcLineSegment2D>(horCurveGeometry);
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcCircularArcSegment2D> circular_arc_segment_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcCircularArcSegment2D>(horCurveGeometry);
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcTransitionCurveSegment2D>(horCurveGeometry);

								double nHorFragmentsLength = 0.;
								int nHorFragments = 0;

								// Set number of fragments (number of points to be added between stations) according to segment type.
								if (line_segment_2D) {
									nHorFragments = 0;
									nHorFragmentsLength = dHorizontalSegLength;
								}
								if (circular_arc_segment_2D) {
									nHorFragments = geomSettings->min_num_vertices_per_arc;
									nHorFragmentsLength = dHorizontalSegLength / nHorFragments;
								}
								if (trans_curve_segment_2D) {
									nHorFragments = geomSettings->min_num_vertices_per_arc;
									nHorFragmentsLength = dHorizontalSegLength / nHorFragments;
								}

								// Step 3: Get vertical segment type and store number and length of fragments.

								int nVerFragments = 0;
								double nVerFragmentsLength = 0.;

								// StartDistAlong type IfcLengthMeasure [1:1]
								// cannot be checked this way because it is an IfcLengthMeasure, not IfcPositiveLengthMeasure
								if ((*it_vertical_segment)->StartDistAlong < 0.0) {
									BLUE_LOG(error) << "No start distance along in IfcAlignment2DVerticalSegment (Segment ID: " << (*it_vertical_segment)->getId() << ").";
									return;
								}
								double dVerDistAlong = (*it_vertical_segment)->StartDistAlong * length_factor;

								// HorizontalLength type IfcPositiveLengthMeasure [1:1]
								if ((*it_vertical_segment)->HorizontalLength < 0.0) {
									BLUE_LOG(error) << "No horizontal length in IfcAlignment2DVerticalSegment (Segment ID: " << (*it_vertical_segment)->getId() << ").";
									return;
								}
								double dVerticalSegmentLength = (*it_vertical_segment)->HorizontalLength * length_factor;

								// Segment types: IfcAlignment2DVerSegCircularArc, IfcAlignment2DVerSegLine, IfcAlignment2DVerSegParabolicArc.
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegCircularArc>(it_vertical_segment->lock());
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegLine> ver_seg_line_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegLine>(it_vertical_segment->lock());
								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
									std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegParabolicArc>(it_vertical_segment->lock());

								// Set number of fragments (number of stations to be added within segment) according to segment type.
								if (v_seg_circ_arc_2D) {
									nVerFragments = geomSettings->min_num_vertices_per_arc;
									nVerFragmentsLength = dVerticalSegmentLength / nVerFragments;
								}
								if (ver_seg_line_2D) {
									nVerFragments = 0;
									nVerFragmentsLength = dVerticalSegmentLength;
								}
								if (v_seg_par_arc_2D) {
									nVerFragments = geomSettings->min_num_vertices_per_arc;
									nVerFragmentsLength = dVerticalSegmentLength / nVerFragments;
								}

								// Select greater accuracy/smaller fragments.
								if (nVerFragmentsLength < nHorFragmentsLength)
								{
									fragmentsLength = nVerFragmentsLength;
								}
								else
								{
									fragmentsLength = nHorFragmentsLength;
								}

								// Select smaller segment length.
								if (dVerticalSegmentLength < dHorizontalSegLength)
								{
									overlappingLengthOfSegments = dVerticalSegmentLength;
									isShorterSegmentHorizontal = false;
								}
								else
								{
									overlappingLengthOfSegments = dHorizontalSegLength;
									isShorterSegmentHorizontal = true;
								}


								double newStationDistAlong = startDistAlong;

								// Add stations according to length of fragments until the end of the shorter segment.
								while (newStationDistAlong <= overlappingLengthOfSegments + startDistAlong)
								{
									newStationDistAlong += fragmentsLength;
									stations.push_back(newStationDistAlong);
								}

								// Length along alignment that has been covered.
								startDistAlong += overlappingLengthOfSegments;

								// If shorter segment is horizontal, take next horizontal segment but keep current vertical segment.
								if (isShorterSegmentHorizontal)
								{
									it_horizontal_segment++;
								}
								// vice versa
								else
								{
									it_vertical_segment++;
								}

							} // end of vertical segments iteration

							carve::geom::vector<3> targetPoint3D;
							carve::geom::vector<3> targetDirection3D;
							std::vector<carve::geom::vector<3>> curve_points;

							for (auto it_station : stations)
							{
								PlacementConverterT<IfcEntityTypesT>::convertAlignmentCurveDistAlongToPoint3D(alignment_curve, it_station, targetPoint3D, targetDirection3D);
								curve_points.push_back(targetPoint3D);
							}
							GeomUtils::appendPointsToCurve(curve_points, targetVec);
						} // end if IfcAlignmentCurve


						// (2/6) IfcBSplineCurve SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcBSplineCurve> bspline_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineCurve>(bounded_curve);
						if (bspline_curve) {

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> points;
							points.resize(bspline_curve->ControlPointsList.size());

							std::transform(
								bspline_curve->ControlPointsList.begin(),
								bspline_curve->ControlPointsList.end(),
								points.begin(),
								[](auto &it) {return it.lock(); });

							std::vector<carve::geom::vector<3>> splinePoints;
							splinePoints.resize(points.size());
							convertIfcCartesianPointVector(points, splinePoints);

							SplineConverterT<typename IfcEntityTypesT, IfcUnitConverterT>::convertIfcBSplineCurve(bspline_curve, splinePoints, targetVec);
							return;

							// TO DO: Implement IfcBSplineCurveWithKnots
							// TO DO: IfcRationalBSplineCurveWithKnots

						} // endif bsplinecurve

						// (3/6) IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurve> composite_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeCurve>(bounded_curve);
						if (composite_curve) {

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> > segments;
							segments.resize(composite_curve->Segments.size());

							std::transform(
								composite_curve->Segments.begin(),
								composite_curve->Segments.end(),
								segments.begin(),
								[](auto &it) { return it.lock(); });

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> >::iterator it_segments =
								segments.begin();

							for (; it_segments != segments.end(); ++it_segments) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> segment = (*it_segments);
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve> segment_curve = segment->ParentCurve.lock();

								std::vector<carve::geom::vector<3>> segment_vec;
								convertIfcCurve(segment_curve, segment_vec, segmentStartPoints);
								if (segment_vec.size() > 0) {
									GeomUtils::appendPointsToCurve(segment_vec, targetVec);
								}
							}
							return;
						} // endif composite curve

						/* TO DO: IMPLEMENT
						// (4/6) IfcIndexedPolyline SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcIndexedPolyline> index_poly_line =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcIndexedPolyline>(bounded_curve);
						if (index_poly_line)
						{
							// TO DO: implement
						}*/

						// (5/6) IfcPolyline SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> poly_line =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(bounded_curve);
						if (poly_line) {
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> > points;
							points.resize(poly_line->Points.size());
							std::transform(
								poly_line->Points.begin(),
								poly_line->Points.end(),
								points.begin(),
								[](auto &it) {return it.lock(); });

							if (points.size() > 0) {
								convertIfcCartesianPointVector(points, targetVec);
								segmentStartPoints.push_back(carve::geom::VECTOR(
									points[0]->Coordinates[0] * length_factor,
									points[0]->Coordinates[1] * length_factor,
									0));
							}
							return;
						} // endif points

						// (6/6) IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcTrimmedCurve> trimmed_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcTrimmedCurve>(bounded_curve);
						if (trimmed_curve) {
							std::shared_ptr<typename IfcEntityTypesT::IfcCurve> basis_curve = trimmed_curve->BasisCurve.lock();
							std::vector<carve::geom::vector<3> > basis_curve_points;

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> curve_trim1_vec;
							curve_trim1_vec.resize(trimmed_curve->Trim1.size());
							std::transform(trimmed_curve->Trim1.begin(),
								trimmed_curve->Trim1.end(),
								curve_trim1_vec.begin(), [](auto it) { return std::make_shared<decltype(it)>(it); });

							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> curve_trim2_vec;
							curve_trim2_vec.resize(trimmed_curve->Trim2.size());
							std::transform(trimmed_curve->Trim2.begin(),
								trimmed_curve->Trim2.end(),
								curve_trim2_vec.begin(), [](auto it) { return std::make_shared<decltype(it)>(it); });

							bool trimmed_sense_agreement = trimmed_curve->SenseAgreement;

							convertIfcCurve(basis_curve, basis_curve_points, segmentStartPoints,
								curve_trim1_vec, curve_trim2_vec, trimmed_sense_agreement);
							GeomUtils::appendPointsToCurve(basis_curve_points, targetVec);
							return;
						}

					} // end IfcBoundedCurve

					// ************************************************************************************************************************	//
					//	IfcConic SUPTYPE of IfcCurve																							//
					//	ABSTRACT SUPERTYPE of IfcCircle, IfcEllipse																				//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcConic> conic =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcConic>(ifcCurve);
					if (conic) {
#ifdef _DEBUG
						BLUE_LOG(trace) << "Processing IfcConic #" << conic->getId();
#endif
						typename IfcEntityTypesT::IfcAxis2Placement conic_placement = conic->Position;
						carve::math::Matrix conic_position_matrix(carve::math::Matrix::IDENT());

						switch (conic_placement.which()) {
						case 0: // class IfcAxis2Placement2D;
							PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement2D(
								conic_placement.get<0>().lock(),
								conic_position_matrix,
								length_factor);
							break;
						case 1: // class IfcAxis2Placement3D;
							PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(
								conic_placement.get<1>().lock(),
								conic_position_matrix,
								length_factor);
							break;
						default:
							BLUE_LOG(warning) << "#" << conic->getId() << "=IfcConic no position found.";
							break;
						}

						// (1/2) IfcCircle SUBTYPE OF IfcConic
						std::shared_ptr<typename IfcEntityTypesT::IfcCircle> circle =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircle>(conic);
						if (circle) {
#ifdef _DEBUG
							BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId();
#endif
							// Get radius
							double circle_radius = 0.0;
							if (circle->Radius) {
								circle_radius = circle->Radius * length_factor;
							}
							else {
								BLUE_LOG(warning) << "IfcCircle #" << circle->getId() << ": No radius!";
							}

							carve::geom::vector<3> circle_center =
								conic_position_matrix * carve::geom::VECTOR(0, 0, 0);

							double trim_angle1 = 0.0;
							double trim_angle2 = M_PI * 2.0;

							// Check for trimming begin
							if (trim1Vec.size() > 0) {
								BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Check for trimming begin.";
								auto first = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select) { return select->which() == 1; });
								if (first != trim1Vec.end() && *first) {
									BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Found trimming begin as IfcParameterValue.";
									typename IfcEntityTypesT::IfcParameterValue trim_par1 = (*first)->get<1>();
									trim_angle1 = trim_par1 * plane_angle_factor;
								}
								else {
									first = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select) { return select->which() == 0; });
									if (first != trim1Vec.end() && (*first) != nullptr) {
										BLUE_LOG(trace) << "blub" << circle->getId();
										BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Found trimming begin.";
										try {
											EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint> trim_point1_ref = (*first)->get<0>();
											std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point1 = trim_point1_ref.lock();

											BLUE_LOG(trace) << "IfcCartesianPoint #" << trim_point1->getId();
											carve::geom::vector<3> trim_point;
											convertIfcCartesianPoint(trim_point1, trim_point);

											trim_angle1 = getAngleOnCircle(circle_center,
												circle_radius,
												trim_point);
										}
										catch (...) {
											BLUE_LOG(error) << "Exception occured!";
											return;
										}
									}
									else {
										BLUE_LOG(warning) << "Processing IfcCircle #" << circle->getId() << ": No trimming begin.";
									}
								}
							}
							else {
								BLUE_LOG(warning) << "Processing IfcCircle #" << circle->getId() << ": trim1vec is empty!";
							}

							if (trim2Vec.size() > 0) {
								// check for trimming end
								BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Check for trimming end.";
								auto first = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select) { return select->which() == 1; });
								if (first != trim2Vec.end()) {
									BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Found trimming end as IfcParameterValue.";
									typename IfcEntityTypesT::IfcParameterValue trim_par2 = (*first)->get<1>();
									trim_angle1 = trim_par2 * plane_angle_factor;
								}
								else {
									first = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select) { return select->which() == 0; });
									if (first != trim2Vec.end()) {
										BLUE_LOG(trace) << "Processing IfcCircle #" << circle->getId() << ": Found trimming end as IfcCartesianPoint.";
										std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point2 = (*first)->get<0>().lock();
										carve::geom::vector<3> trim_point;
										convertIfcCartesianPoint(trim_point2, trim_point);

										trim_angle2 = getAngleOnCircle(circle_center,
											circle_radius,
											trim_point);
									}
									else {
										BLUE_LOG(warning) << "Processing IfcCircle #" << circle->getId() << ": No trimming end.";
									}
								}
							}
							else {
								BLUE_LOG(warning) << "Processing IfcCircle #" << circle->getId() << ": trim2vec is empty!";
							}

							double start_angle = trim_angle1;
							double opening_angle = 0.0;

							if (senseAgreement) {
								if (trim_angle1 < trim_angle2) {
									opening_angle = trim_angle2 - trim_angle1;
								}
								else {
									// circle passes 0 angle
									opening_angle = trim_angle2 - trim_angle1 + 2.0*M_PI;
								}
							}
							else {
								if (trim_angle1 > trim_angle2) {
									opening_angle = trim_angle2 - trim_angle1;
								}
								else {
									// circle passes 0 angle
									opening_angle = trim_angle2 - trim_angle1 - 2.0*M_PI;
								}
							}

							if (opening_angle > 0) {
								while (opening_angle > 2.0*M_PI) {
									opening_angle -= 2.0*M_PI;
								}
							}
							else {
								while (opening_angle < -2.0*M_PI) {
									opening_angle += 2.0*M_PI;
								}
							}

							int num_segments = geomSettings->num_vertices_per_circle
								* (abs(opening_angle) / (2.0*M_PI));

							if (num_segments < geomSettings->min_num_vertices_per_arc) {
								num_segments = geomSettings->min_num_vertices_per_arc;
							}

							const double circle_center_x = 0.0;
							const double circle_center_y = 0.0;
							std::vector<carve::geom::vector<2> > circle_points;
							ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>::addArcWithEndPoint(circle_points, circle_radius, start_angle,
								opening_angle, circle_center_x,
								circle_center_y, num_segments);

							if (circle_points.size() > 0) {
								// apply position
								for (unsigned int i = 0; i < circle_points.size(); ++i) {
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
						} // end if circle

						// (2/2) IfcEllipse SUBTYPE OF IfcConic
						std::shared_ptr<typename IfcEntityTypesT::IfcEllipse> ellipse =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEllipse>(conic);
						if (ellipse) {
							if (ellipse->SemiAxis1) {
								if (ellipse->SemiAxis2) {

									double xRadius = ellipse->SemiAxis1 * length_factor;
									double yRadius = ellipse->SemiAxis2 * length_factor;

									double radiusMax = std::max(xRadius, yRadius);
									int num_segments = geomSettings->num_vertices_per_circle;
									// TODO: adapt to model size and complexity

									// todo: implement clipping

									std::vector<carve::geom::vector<3> > circle_points;
									double angle = 0.0;
									for (int i = 0; i < num_segments; ++i) {
										circle_points.push_back(carve::geom::vector<3>(
											carve::geom::VECTOR(xRadius * cos(angle),
												yRadius * sin(angle),
												0)));
										angle += 2.0*M_PI / double(num_segments);
									}

									// apply position
									for (unsigned int i = 0; i < circle_points.size(); ++i) {
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
						} // end if ellipse

					} // end if conic

					// ************************************************************************************************************************	//
					//	IfcLine SUPTYPE of IfcCurve																								//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcLine> line =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLine>(ifcCurve);
					if (line)
					{

						// Part 1: Get information from IfcLine. 

						// Get IfcLine attributes: line point and line direction. 
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_line_point = line->Pnt.lock();
						carve::geom::vector<3> line_origin;
						convertIfcCartesianPoint(ifc_line_point, line_origin);

						std::shared_ptr<typename IfcEntityTypesT::IfcVector> line_vec = line->Dir.lock();
						if (!line_vec) {
							return;
						}
						// Get IfcVector attributes: line orientation and magnitude. 

						// Orientation type IfcDirection
						auto ifc_line_direction = line_vec->Orientation;

						// Get IfcDirection attribute: direction ratios. 
						std::vector<double> direction_ratios(ifc_line_direction->DirectionRatios.size());
						for (int i = 0; i < direction_ratios.size(); ++i) {
							direction_ratios[i] = ifc_line_direction->DirectionRatios[i];
						}

						carve::geom::vector<3> line_direction;
						if (direction_ratios.size() > 1) {
							if (direction_ratios.size() > 2) {
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

						// Magnitude type IfcLengthMeasure
						double line_magnitude = line_vec->Magnitude * length_factor;

						// Part 2: Trimming

						// Check for trimming at beginning of line
						double start_parameter = 0.0;
						typename IfcEntityTypesT::IfcParameterValue trim_par1;
						auto first_par_val = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select_ptr) { return select_ptr->which() == 1; });
						if (first_par_val != trim1Vec.end()) {
							trim_par1 = (*first_par_val)->get<1>();
							start_parameter = trim_par1;
							line_origin = line_origin + line_direction * start_parameter;
						}
						else {
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
							auto first_point = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select_ptr) { return select_ptr->which() == 0; });
							if (first_point != trim1Vec.end() && *first_point) {
								ifc_trim_point = (*first_point)->get<0>().lock();
								carve::geom::vector<3> trim_point;
								convertIfcCartesianPoint(ifc_trim_point, trim_point);

								carve::geom::vector<3> closest_point_on_line;
								GeomUtils::closestPointOnLine(trim_point, line_origin,
									line_direction, closest_point_on_line);

								if ((closest_point_on_line - trim_point).length() < 0.0001) {
									// trimming point is on the line
									line_origin = trim_point;
								}
							}
						}

						// Check for trimming at end of line
						carve::geom::vector<3> line_end;
						typename IfcEntityTypesT::IfcParameterValue trim_par2;
						first_par_val = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select_ptr) { return select_ptr->which() == 1; });

						if (first_par_val != trim2Vec.end()) {
							trim_par2 = (*first_par_val)->get<1>();
							line_magnitude = trim_par2 * length_factor;
							line_end = line_origin + line_direction * line_magnitude;
						}
						else {
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
							auto first_point = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select_ptr) { return select_ptr->which() == 0; });

							if (first_point != trim2Vec.end() && *first_point) {
								ifc_trim_point = (*first_point)->get<0>().lock();
								carve::geom::vector<3> trim_point;
								convertIfcCartesianPoint(ifc_trim_point, trim_point);

								carve::geom::vector<3> closest_point_on_line;
								GeomUtils::closestPointOnLine(trim_point, line_origin,
									line_direction, closest_point_on_line);

								if ((closest_point_on_line - trim_point).length() < 0.0001) {
									// trimming point is on the line
									line_end = trim_point;
								}
							}
						}

						// Part 3: Add line points
						std::vector<carve::geom::vector<3> > points_vec;
						points_vec.push_back(line_origin);
						points_vec.push_back(line_end);

						GeomUtils::appendPointsToCurve(points_vec, targetVec);

						// if( segment_start_points != NULL )
						{
							segmentStartPoints.push_back(line_origin);
						}
						return;
					} // end if line

					// ************************************************************************************************************************	//
					//	IfcOffsetCurve SUPTYPE of IfcCurve																						//
					//	ABSTRACT SUPERTYPE OF IfcOffsetCurve2D, IfcOffsetCurve3D, IfcOffsetCurveByDistances										//
					// ************************************************************************************************************************	//
					/* TODO: IMPLEMENT OFFSETCURVE, PCURVE, SURFACECURVE
					std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve> offset_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve>(ifcCurve);
					if (offset_curve) {

						// (1/3) IfcOffsetCurve2D SUBTYPE OF IfcOffsetCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve2D> offset_curve_2d =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve2D>(offset_curve);
						if (offset_curve_2d) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcOffsetCurve2D not implemented" << std::endl;
#endif
							return;
						}

						// (2/3) IfcOffsetCurve3D SUBTYPE OF IfcOffsetCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve3D> offset_curve_3d =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve3D>(offset_curve);
						if (offset_curve_3d) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcOffsetCurve3D not implemented" << std::endl;
#endif
							return;
						}

						// (3/3) IfcOffsetCurveByDistances SUBTYPE OF IfcOffsetCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurveByDistances> offset_curve_dist =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurveByDistances>(offset_curve);
						if (offset_curve_dist) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcOffsetCurveByDistances not implemented" << std::endl;
#endif
							return;
						}
					}

					// ************************************************************************************************************************	//
					//	IfcPcurve SUPTYPE of IfcCurve																							//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcPcurve> p_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPcurve>(ifcCurve);
					if (p_curve)
					{
						// TO DO: implement
					}

					// ************************************************************************************************************************	//
					//	IfcSurfaceCurve SUPTYPE of IfcCurve																						//
					//	ABSTRACT SUPERTYPE OF IfcIntersectionCurve, IfcSeamCurve																//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcSurfaceCurve> surface_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfaceCurve>(ifcCurve);
					if (surface_curve)
					{
						// (1/2) IfcIntersectionCurve SUBTYPE OF IfcSurfaceCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcIntersectionCurve> intersection_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcIntersectionCurve>(ifcCurve);
						if (intersection_curve)
						{
							// TO DO: implement
						}

						// (2/2) IfcSeamCurve SUBTYPE OF IfcSurfaceCurve
						std::shared_ptr<typename IfcEntityTypesT::IfcSeamCurve> seam_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSeamCurve>(ifcCurve);
						if (seam_curve)
						{
							// TO DO: implement
						}

					} // endif surface curve */
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processed IfcCurve #" << ifcCurve->getId();
#endif
				}

				// ************************************************************************************************************************	//
				//	Functions			
				//	convertIfcCurve2D, convertIfcCartesianPoint (+ related functions), getAngleOnCircle
				// ************************************************************************************************************************	//

				// Function 1: Convert 2D IfcCurve (overloaded). 

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

					for (int i = 0; i < target_vec_3d.size(); ++i) {
						carve::geom::vector<3>& point_3d = target_vec_3d[i];
						targetVec.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
					for (int i = 0; i < segment_start_points_3d.size(); ++i) {
						carve::geom::vector<3>& point_3d = segment_start_points_3d[i];
						segmentStartPoints.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
				} //end convertIfcCurve2D

				// Function 2a: Convert IfcPolyline.
				void convertIfcPolyline(const std::shared_ptr<typename IfcEntityTypesT::IfcPolyline>& polyLine,
					std::vector<carve::geom::vector<3>>& loop) const
				{
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing IfcPolyline #" << polyLine->getId();
#endif
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> points;
					points.resize(polyLine->Points.size());
					std::transform(
						polyLine->Points.begin(),
						polyLine->Points.end(),
						points.begin(),
						[](auto& it) { return it.lock(); }
					);
					convertIfcCartesianPointVector(points, loop);
				}

				// Function 2b: Convert IfcLoop.
				void convertIfcLoop(const std::shared_ptr<typename IfcEntityTypesT::IfcLoop>& loop,
					std::vector<carve::geom::vector<3>>& loopPoints) const
				{
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing IfcLoop #" << loop->getId();
#endif
					const std::shared_ptr<typename IfcEntityTypesT::IfcPolyLoop> polyLoop =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyLoop>(loop);

					if (polyLoop) {
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> ifcPoints;
						ifcPoints.resize(polyLoop->Polygon.size());

						std::transform(
							polyLoop->Polygon.begin(),
							polyLoop->Polygon.end(),
							ifcPoints.begin(),
							[](auto &it) { return it.lock(); });

						convertIfcCartesianPointVectorSkipDuplicates(ifcPoints, loopPoints);

						// If first and last point have same coordinates, remove last point
						while (loopPoints.size() > 2) {
							carve::geom3d::Vector& first = loopPoints.front();
							carve::geom3d::Vector& last = loopPoints.back();

							if (abs(first.x - last.x) < 0.00000001) {
								if (abs(first.y - last.y) < 0.00000001) {
									if (abs(first.z - last.z) < 0.00000001) {
										loopPoints.pop_back();
										continue;
									}
								}
							}
							break;
						}
						return;
					} // end if polyloop

					std::shared_ptr<typename IfcEntityTypesT::IfcEdgeLoop> edgeLoop =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeLoop>(loop);

					if (edgeLoop) {
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge>> edgeList;
						edgeList.resize(edgeLoop->EdgeList.size());

						std::transform(
							edgeLoop->EdgeList.begin(),
							edgeLoop->EdgeList.end(),
							edgeList.begin(),
							[](auto &it) {return it.lock(); });

						// go through every edge in the edge list
						for (auto it_edge = edgeList.begin(); it_edge != edgeList.end(); ++it_edge) {
							// edge loop consists of many oriented edges
							std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge> orientedEdge = (*it_edge);
							// which are described by the type of its edge element object
							std::shared_ptr<typename IfcEntityTypesT::IfcEdge>& edgeElement = orientedEdge->EdgeElement.lock();

							std::shared_ptr<typename IfcEntityTypesT::IfcEdgeCurve> edgeCurve =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeCurve>(edgeElement);

							if (edgeCurve) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& curveGeom = edgeCurve->EdgeGeometry.lock();
								std::vector<carve::geom::vector<3>> segmentStartPoints;

								convertIfcCurve(curveGeom, loopPoints, segmentStartPoints);

								continue;
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcSubedge> subEdge =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSubedge>(edgeElement);

							if (subEdge) {
								std::cout << "ERROR\t| IfcSubedge not implemented" << std::endl;
								BLUE_LOG(warning) << "Developer Warning: IfcSubedge not implemented.";
								continue;
							}

							std::cout << "ERROR\t| Entity " << orientedEdge->classname() << " not handled" << std::endl;
							BLUE_LOG(warning) << "Developer Warning: Entity " << orientedEdge->classname() << " not handled.";

							// every edge consists of one start and end vertex
							std::shared_ptr<typename IfcEntityTypesT::IfcVertex>& edgeStartVertex = edgeElement->EdgeStart.lock();
							std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> edgeStartVertexPoint =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(edgeStartVertex);

							if (edgeStartVertexPoint)
							{
								if (edgeStartVertexPoint->VertexGeometry)
								{
									std::shared_ptr<typename IfcEntityTypesT::IfcPoint>& startPoint =
										edgeStartVertexPoint->VertexGeometry.lock();
									std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifcPoint =
										std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(startPoint);
									if (!ifcPoint)
									{
										// TODO: could be also  IfcPointOnCurve, IfcPointOnSurface
										BLUE_LOG(warning) << "Developer Warning: Not yet implemented!";
										continue;
									}
									// TODO: implement
								}
							}

						}
					} // end if edge loop
				} // end convertIfcLoop

				// Function 2c: Convert IfcCartesianPoint (overloaded). 
				void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
					carve::geom::vector<3> & point) const
				{
					double length_factor = unitConverter->getLengthInMeterFactor();

					if (ifcPoint->Coordinates.size() > 2) {
						double x = ifcPoint->Coordinates[0] * length_factor;
						double y = ifcPoint->Coordinates[1] * length_factor;
						double z = ifcPoint->Coordinates[2] * length_factor;

						point = carve::geom::VECTOR(x, y, z);
					}
					else if (ifcPoint->Coordinates.size() > 1) {
						double x = ifcPoint->Coordinates[0] * length_factor;
						double y = ifcPoint->Coordinates[1] * length_factor;

						point = carve::geom::VECTOR(x, y, 0.0);
					}
				}

				static void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
					carve::geom::vector<3> & point,
					double lengthFactor)
				{
					if (ifcPoint->Coordinates.size() > 2) {
						double x = ifcPoint->Coordinates[0] * lengthFactor;
						double y = ifcPoint->Coordinates[1] * lengthFactor;
						double z = ifcPoint->Coordinates[2] * lengthFactor;

						point = carve::geom::VECTOR(x, y, z);
					}
					else if (ifcPoint->Coordinates.size() > 1) {
						double x = ifcPoint->Coordinates[0] * lengthFactor;
						double y = ifcPoint->Coordinates[1] * lengthFactor;

						point = carve::geom::VECTOR(x, y, 0.0);
					}
				}

				// Function 2d: Convert IfcCartesianPoint vector.
				void convertIfcCartesianPointVector(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					const double length_factor = unitConverter->getLengthInMeterFactor();
					const unsigned int num_points = points.size();

					for (unsigned int i_point = 0; i_point < num_points; ++i_point)
					{
						if (points[i_point]->Coordinates.size() > 2) {
							double x = points[i_point]->Coordinates[0] * length_factor;
							double y = points[i_point]->Coordinates[1] * length_factor;
							double z = points[i_point]->Coordinates[2] * length_factor;

							loop.push_back(carve::geom::VECTOR(x, y, z));
						}
						else if (points[i_point]->Coordinates.size() > 1) {

							double x = points[i_point]->Coordinates[0] * length_factor;
							double y = points[i_point]->Coordinates[1] * length_factor;

							loop.push_back(carve::geom::VECTOR(x, y, 0.0));
						}
						else {
							std::cout << "convertIfcCartesianPointVector: ifc_pt->Coordinates.size() != 2"
								<< std::endl;
						}
					}
				}

				// Function 2e: Convert IfcCartesianPoint vector and skip duplicates.
				void convertIfcCartesianPointVectorSkipDuplicates(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints,
					std::vector<carve::geom::vector<3> >& loop) const
				{
					const double length_factor = unitConverter->getLengthInMeterFactor();
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >::const_iterator it_cp; // iterates over points
					int i = 0;
					carve::geom::vector<3>  vertex_previous;

					for (it_cp = ifcPoints.begin(); it_cp != ifcPoints.end(); ++it_cp, ++i) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = (*it_cp);
						const int cp_id = cp->getId();

						double x = 0.0, y = 0.0, z = 0.0;

						if (cp->Coordinates.size() > 2) {
							x = cp->Coordinates[0] * length_factor;
							y = cp->Coordinates[1] * length_factor;
							z = cp->Coordinates[2] * length_factor;
						}
						else if (cp->Coordinates.size() > 1) {

							x = cp->Coordinates[0] * length_factor;
							y = cp->Coordinates[1] * length_factor;
						}

						carve::geom::vector<3>  vertex(carve::geom::VECTOR(x, y, z));

						// skip duplicate vertices
						if (it_cp != ifcPoints.begin()) {
							if (abs(vertex.x - vertex_previous.x) < 0.00000001) {
								if (abs(vertex.y - vertex_previous.y) < 0.00000001) {
									if (abs(vertex.z - vertex_previous.z) < 0.00000001) {
										// TODO: is it better to report degenerated loops, or to just omit them?
										BLUE_LOG(warning) << "Duplicate point in polyloop. IfcPoint #" << it_cp->get()->getId();
										//continue;
									}
								}
							}
						}
						loop.push_back(vertex);
						vertex_previous = vertex;
					}
				}

				// Function 3: Get angle on circle (returns angle if the given point lies on the circle; if not, -1 is returned). 
				static double getAngleOnCircle(const carve::geom::vector<3>& circleCenter,
					double circleRadius,
					const carve::geom::vector<3>& trimPoint)
				{
					double result_angle = -1.0;
					carve::geom::vector<3> center_trim_point = trimPoint - circleCenter;
					if (abs(center_trim_point.length() - circleRadius) < 0.0001) {
						carve::geom::vector<3> center_trim_point_direction = center_trim_point;
						center_trim_point_direction.normalize();
						double cos_angle = carve::geom::dot(center_trim_point_direction, carve::geom::vector<3>(carve::geom::VECTOR(1.0, 0, 0)));

						if (abs(cos_angle) < 0.0001) {
							if (center_trim_point.y > 0) {
								result_angle = M_PI_2;
							}
							else if (center_trim_point.y < 0) {
								result_angle = M_PI * 1.5;
							}
						}
						else {
							if (center_trim_point.y > 0) {
								result_angle = acos(cos_angle);
							}
							else if (center_trim_point.y < 0) {
								result_angle = 2.0*M_PI - acos(cos_angle);
							}
						}
					}
					return result_angle;
				}

			protected:
				std::shared_ptr<GeometrySettings>	geomSettings;
				std::shared_ptr<IfcUnitConverterT>	unitConverter;
			}; // end class
		}; // end namespace IfcGeometryConverter
	}; // end namespace Core
}; // end namespace OIP


#endif
