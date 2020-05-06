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

#include "ConverterBase.h"

#include "GeomUtils.h"
#include "UnhandledRepresentationException.h"
#include "PlacementConverter.h"
#include "ProfileConverter.h"
#include "SplineConverter.h"

#include "BlueFramework/Core/Diagnostics/log.h"


namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {

			/*! \brief Converter functionality for \c IfcCurve's subtypes
			*
			* \param IfcEntityTypesT The IFC version templates
			*/
			template <
				class IfcEntityTypesT
			>
			class CurveConverterT : public ConverterBaseT<IfcEntityTypesT>
			{
			public:
				//! Constructor
				CurveConverterT(
					std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
					std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc)
					:
					ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
					placementConverter(pc)
				{
				}

				//! Virtual destructor
				virtual ~CurveConverterT()
				{

				}

				/*! \brief Converts an \c IfcCurve to an array of segments to be rendered on screen.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] loops					The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				*
				* \note Calls the other overload CurveConverterT::convertIfcCurve with empty \c IfcTrimmingSelect-s.
				*/
				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve> ifcCurve,
					std::vector<carve::geom::vector<3>>& loops,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim2Vec;
					convertIfcCurve(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
				}

				/*! \brief Converts an \c IfcCurve to an array of segments to be rendered on screen.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] targetVec				The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*
				* \note See https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometryresource/lexical/ifccurve.htm
				*/
				void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim2Vec,
					const bool senseAgreement) const
				{
					// get the scaling factors from unit converter
					double length_factor = UnitConvert()->getLengthInMeterFactor();
					double plane_angle_factor = UnitConvert()->getAngleInRadianFactor();

					// log to the console
					#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing " << ifcCurve->getErrorLog();
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
						std::shared_ptr<typename IfcEntityTypesT::IfcAlignmentCurve> alignment_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignmentCurve>(bounded_curve);
						if (alignment_curve) 
						{
							// **************************************************************************************************************************** //
							// Step 1: Get segment information from horizontal and vertical alignments.
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignment_curve->Horizontal.lock();

							if (!horizontal)
							{
								BLUE_LOG(error) << alignment_curve->getErrorLog() << ": No IfcAlignment2DHorizontal specified";
								return;
							}

							// StartDistAlong type IfcLengthMeasure [0:1]
							double horStartDistAlong = 0.0;
							double hStartDistAlong = horizontal->StartDistAlong.get();

							if (hStartDistAlong) {
								horStartDistAlong = hStartDistAlong * length_factor;
							}

							// Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if (horizontal->Segments.empty()) {
								BLUE_LOG(error) << "No segments in " << horizontal->getErrorLog();
								return;
							}

							// is it going to be only a horizontal alignment?
							bool bOnlyHorizontal = false;
							//std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVertical>
							auto vertical = alignment_curve->Vertical;
							if (!vertical) {
								// there is no vertical alignment
								BLUE_LOG(info) << "No IfcAlignment2DVertical in " << alignment_curve->getErrorLog();
								bOnlyHorizontal = true;
							}
							else
							{
								// vertical alignment is there
								if (vertical->Segments.empty()) {
									BLUE_LOG(error) << "No segments in " << vertical->getErrorLog();
									return;
								}
							}

							// start at the beginning of the alignment
							double dCurrentDistAlong = 0.; 
							// the stations at which a point of the tesselation has to be calcuated - to be converted and fill the targetVec
							std::vector<double> stations;  

							std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment>>::iterator itHorizontalSegment = horizontal->Segments.begin();
							std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment>>::iterator   itVerticalSegment;
							if(!bOnlyHorizontal)
								itVerticalSegment = vertical->Segments.begin();

							double dHorizontalSegStart = 0.; // the end station of the last element in the horizontal ( i.e. the start station of current itHorizotnalSegment )
							double dVerticalSegStart = 0.; // similar for vertical

							// Iterate over horizontal segments
							while (itHorizontalSegment != horizontal->Segments.end())
							{
								// IfcAlignment2DHorizontalSegment
								//   TangentialContinuity type IfcBoolean [0:1], // ignored
								//   StartTag type IfcLabel [0:1],				 // ignored
								//   EndTag type IfcLabel [0:1],				 // ignored
								//   CurveGeometry type IfcCurveSegment2D [1:1]
								std::shared_ptr<typename IfcEntityTypesT::IfcCurveSegment2D> horCurveGeometry = (*itHorizontalSegment)->CurveGeometry.lock();

								// Get and interpret information from IfcCurveSegment2D.
								if (!horCurveGeometry) {
									BLUE_LOG(error) << "No curve geometry in " << (*itHorizontalSegment)->getErrorLog();
									return;
								}

								// SegmentLength type IfcPositiveLengthMeasure [1:1]
								if (horCurveGeometry->SegmentLength <= 0) {
									BLUE_LOG(error) << "Curve segment length is " << std::to_string(horCurveGeometry->SegmentLength) << " in " << horCurveGeometry->getErrorLog();
									return;
								}
								double dHorizontalSegLength = horCurveGeometry->SegmentLength * length_factor;
								double dHorizontalSegEnd = dHorizontalSegStart + dHorizontalSegLength;

								// Step 2: Get horizontal segment type and store the number and length of fragments.
								// the values are needed for calculation of points
								double dFragmentLength = 0.;
								int    nFragments = 0;

								// Segment types: IfcLineSegment2D, IfcCircularArcSegment2D and IfcTransitionCurveSegment2D
								// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifccurvesegment2d.htm
								std::shared_ptr<typename IfcEntityTypesT::IfcLineSegment2D> line_segment_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLineSegment2D>(horCurveGeometry);
								std::shared_ptr<typename IfcEntityTypesT::IfcCircularArcSegment2D> circular_arc_segment_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircularArcSegment2D>(horCurveGeometry);
								std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcTransitionCurveSegment2D>(horCurveGeometry);
								
								// Set number of fragments (number of stations to be added within segment) according to segment type.
								// depending on the (smallest) segment radius.
								double dHorizontalRadius = 0.;
								if (line_segment_2D) {
									dHorizontalRadius = 0.;
								}
								else if (circular_arc_segment_2D) {
									dHorizontalRadius = circular_arc_segment_2D->Radius;
								}
								else if (trans_curve_segment_2D) {
									double dStartRadius = INFINITY, dEndRadius = INFINITY;
									if (trans_curve_segment_2D->StartRadius)
										dStartRadius = trans_curve_segment_2D->StartRadius;
									if (trans_curve_segment_2D->EndRadius)
										dEndRadius = trans_curve_segment_2D->EndRadius;
									dHorizontalRadius = std::min(dStartRadius, dEndRadius);
									if (dHorizontalRadius == INFINITY)
									{
										BLUE_LOG(warning) << trans_curve_segment_2D->getErrorLog() << ": A straight disgusised as a transition curve.";
										dHorizontalRadius = 0.;
									}
								}
								else
								{
									BLUE_LOG(error) << (*itHorizontalSegment)->getErrorLog() << ": Could not determine tesselation values.";
									return;
								}

								dHorizontalRadius *= length_factor;
								nFragments = GeomSettings()->getNumberOfSegmentsForTesselation(dHorizontalRadius);
								dFragmentLength = dHorizontalSegLength / (double)(nFragments);
								// Step 2 finished: We have the necessary information from the horizontal element

								// Step 3: Get vertical segment type and store number and length of fragments.
								double dOverlapStart = dHorizontalSegStart, dOverlapEnd = dHorizontalSegEnd; // where does the overlap happen?
								if (  !bOnlyHorizontal // if there is a vertical alignment
									&& itVerticalSegment != vertical->Segments.end()) // the vertical alignment may be shorter than horizontal
								{
									// check, if the current vertical segment overlaps the horizontal
									bool bLoop = true;
									double dVerticalSegLength = 0.;
									double dVerticalSegEnd = 0.;

									while (bLoop)
									{
										// StartDistAlong type IfcLengthMeasure [1:1]
										dVerticalSegStart = (*itVerticalSegment)->StartDistAlong * length_factor;

										// HorizontalLength type IfcPositiveLengthMeasure [1:1]
										if ((*itVerticalSegment)->HorizontalLength <= 0.0) {
											BLUE_LOG(error) << (*itVerticalSegment)->getErrorLog() << ": Invalid horizontal length.";
											return;
										}
										dVerticalSegLength = (*itVerticalSegment)->HorizontalLength * length_factor;
										dVerticalSegEnd = dVerticalSegStart + dVerticalSegLength;

										// check the plausibility
										//  itHorizontalSeg: dHorizontalSegStart +---+ dHorizontalSegEnd
										//  itVerticalSeg:   dVerticalSegStart   +---+ dVerticalSegEnd
										//                          +-------+  itHorizontalSeg    
										//  itVerticalSeg:  
										//      1:        +------+								<------- the only case, where we need to count up the iterator of vertical segments
										//      2:            +-----+
										//      3:              +-------+
										//      4:             +------------------+
										//      5:                  +-------+
										//      6:                       +-+
										//      7:                        +-------+
										//      8:                               +---------+    <------- should never ever happen

										// option 1 & 2 - bLoop stays on true
										// - these elements should have been considered with previous horizontal element

										// options 3 through 7
										if (dVerticalSegEnd > dHorizontalSegStart)
											bLoop = false;

										// option 8
										if (dVerticalSegStart > dHorizontalSegEnd)
										{
											BLUE_LOG(error) << (*itVerticalSegment)->getErrorLog() << ": Invalid sequence of vertical elements.";
											return;
										}

										// take the next element
										if ( bLoop )
											itVerticalSegment++;
									} // while( bLoop )

									// Segment types: IfcAlignment2DVerSegCircularArc, IfcAlignment2DVerSegLine, IfcAlignment2DVerSegParabolicArc.
									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
										std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>(itVerticalSegment->lock());
									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegLine> v_seg_line_2D =
										std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>(itVerticalSegment->lock());
									std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
										std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc>(itVerticalSegment->lock());

									// Set number of fragments (number of stations to be added within segment) according to segment type.
									// depending on the segment radius.
									double dVerticalRadius = 0.;
									if (v_seg_line_2D) {
										dVerticalRadius = 0.;
									}
									else if (v_seg_circ_arc_2D) {
										dVerticalRadius = v_seg_circ_arc_2D->Radius;
									}
									else if (v_seg_par_arc_2D) {
										dVerticalRadius = v_seg_par_arc_2D->ParabolaConstant;
									}
									else
									{
										BLUE_LOG(error) << (*itVerticalSegment)->getErrorLog() << ": Could not determine tesselation values.";
										return;
									}

									dVerticalRadius *= length_factor;

									// determine tesselation density
									int nVerFragments = GeomSettings()->getNumberOfSegmentsForTesselation(dVerticalRadius);
									double dVerFragmentsLength = dVerticalSegLength / (double)(nVerFragments);

									// Select greater accuracy / more fragments / smaller fragments.
									nFragments = std::max(nFragments, nVerFragments);
									dFragmentLength = std::min(dFragmentLength, dVerFragmentsLength);

									// determine the overlap area
									dOverlapStart = std::max(dOverlapStart, dVerticalSegStart);
									dOverlapEnd   = std::min(dOverlapEnd  , dVerticalSegEnd);
								}

								double newStationDistAlong = dOverlapStart;

								// Add stations according to length of fragments until the end of the overlapping area.
								while (newStationDistAlong < dOverlapEnd)
								{
									stations.push_back(newStationDistAlong);
									newStationDistAlong += dFragmentLength;
								}
								// the last point may be closer to the end as is the difference between the rest of the points, but who cares?

								// Length along alignment that has been covered.
								dCurrentDistAlong = dOverlapEnd;

								// If the overlap finishes at the end of the horizontal segment, take the next one
								if ( dOverlapEnd >= dHorizontalSegEnd )
								{
									itHorizontalSegment++;
									dHorizontalSegStart = dHorizontalSegEnd; // save the end station of itHorizontalSegment for the next iteration
								}
								// vice versa
								else
								{
									if(itVerticalSegment != vertical->Segments.end())
										itVerticalSegment++;
								}

							} // end of horizontal / vertical segments while iteration
							// add the last station
							stations.push_back(dHorizontalSegStart);

							carve::geom::vector<3> targetPoint3D;
							carve::geom::vector<3> targetDirection3D;
							std::vector<carve::geom::vector<3>> curve_points;
							
							// attach the curve points
							for (auto& it_station : stations)
							{
								// call the placement converter that handles the geometry and calculates the 3D point along a curve
								placementConverter->convertBoundedCurveDistAlongToPoint3D(alignment_curve, it_station, true, targetPoint3D, targetDirection3D);
								curve_points.push_back(targetPoint3D);
							}
							GeomUtils::appendPointsToCurve(curve_points, targetVec);

							// add the first point to segments
							placementConverter->convertBoundedCurveDistAlongToPoint3D(alignment_curve, stations.at(0), true, targetPoint3D, targetDirection3D);
							segmentStartPoints.push_back(targetPoint3D);

							// end
							return;
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

							SplineConverterT<typename IfcEntityTypesT>::convertIfcBSplineCurve(bspline_curve, splinePoints, targetVec);
							return;

							// TO DO: Implement IfcBSplineCurveWithKnots
							// TO DO: IfcRationalBSplineCurveWithKnots

						} // end if IfcBSplineCurve

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
								if ( !segment_vec.empty() ) {
									GeomUtils::appendPointsToCurve(segment_vec, targetVec);
								}
							}
							return;
						} // end if IfcCompositeCurve

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
							if ( !poly_line->Points.empty() ) {
								std::vector<carve::geom::vector<3>> loop;
								convertIfcPolyline(poly_line, loop);

								segmentStartPoints.push_back(loop.at(0));
								targetVec.insert(targetVec.end(), loop.begin(), loop.end());
							}
							return;
						} // end if IfcPolyline

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

							// call recursively with trimmings
							convertIfcCurve(basis_curve, basis_curve_points, segmentStartPoints,
								curve_trim1_vec, curve_trim2_vec, trimmed_sense_agreement);
							GeomUtils::appendPointsToCurve(basis_curve_points, targetVec);
							return;
						}

						// the rest makes a return
						BLUE_LOG(warning) << bounded_curve->getErrorLog() << ": Not supported";
					} // end IfcBoundedCurve

					// ************************************************************************************************************************	//
					//	IfcConic SUPTYPE of IfcCurve																							//
					//	ABSTRACT SUPERTYPE of IfcCircle, IfcEllipse																				//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcConic> conic =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcConic>(ifcCurve);
					if (conic) {
						// determine position
						typename IfcEntityTypesT::IfcAxis2Placement conic_placement = conic->Position;
						carve::math::Matrix conic_position_matrix(carve::math::Matrix::IDENT());

						switch (conic_placement.which()) {
						case 0: // class IfcAxis2Placement2D;
							placementConverter->convertIfcAxis2Placement2D(
								conic_placement.get<0>().lock(),
								conic_position_matrix);
							break;
						case 1: // class IfcAxis2Placement3D;
							placementConverter->convertIfcAxis2Placement3D(
								conic_placement.get<1>().lock(),
								conic_position_matrix);
							break;
						default:
							BLUE_LOG(error) << conic->getErrorLog() << ": no position found.";
							break;
						} //end switch (conic_placement.which())

						// (1/2) IfcCircle SUBTYPE OF IfcConic
						std::shared_ptr<typename IfcEntityTypesT::IfcCircle> circle =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircle>(conic);
						if (circle) {
							// Get radius
							double circle_radius = 0.0;
							if (circle->Radius) {
								circle_radius = circle->Radius * length_factor;
							}
							else {
								BLUE_LOG(error) << circle->getErrorLog() << ": No radius!";
								return;
							}

							carve::geom::vector<3> circle_center =
								conic_position_matrix * carve::geom::VECTOR(0, 0, 0);

							double trim_angle1 = 0.0;
							double trim_angle2 = M_PI * 2.0;

							// Check for trimming begin
							if (trim1Vec.size() > 0) {
								BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Check for trimming begin.";
								auto first = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select) { return select->which() == 1; });
								if (first != trim1Vec.end() && *first) {
									BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming begin as IfcParameterValue.";
									typename IfcEntityTypesT::IfcParameterValue trim_par1 = (*first)->get<1>();
									trim_angle1 = trim_par1 * plane_angle_factor;
								}
								else {
									first = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select) { return select->which() == 0; });
									if (first != trim1Vec.end() && (*first) != nullptr) {
										BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming begin as IfcCartesianPoint.";
										try {
											std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point1 = (*first)->get<0>().lock();

											BLUE_LOG(trace) << trim_point1->getErrorLog();
											carve::geom::vector<3> trim_point;
											placementConverter->convertIfcCartesianPoint(trim_point1, trim_point);

											trim_angle1 = getAngleOnCircle(circle_center,
												circle_radius,
												trim_point);
										}
										catch (...) {
											BLUE_LOG(error) << "Processing " << circle->getErrorLog() << ": Exception occured!";
											return;
										}
									}
									else {
										BLUE_LOG(warning) << "Processing " << circle->getErrorLog() << ": No trimming begin.";
									}
								}
							}
							else {
								BLUE_LOG(warning) << "Processing " << circle->getErrorLog() << ": trim1vec is empty!";
							}

							if (trim2Vec.size() > 0) {
								// check for trimming end
								BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Check for trimming end.";
								auto first = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select) { return select->which() == 1; });
								if (first != trim2Vec.end()) {
									BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming end as IfcParameterValue.";
									typename IfcEntityTypesT::IfcParameterValue trim_par2 = (*first)->get<1>();
									trim_angle1 = trim_par2 * plane_angle_factor;
								}
								else {
									first = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select) { return select->which() == 0; });
									if (first != trim2Vec.end()) {
										BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming end as IfcCartesianPoint.";

										try {
											std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point2 = (*first)->get<0>().lock();

											BLUE_LOG(trace) << trim_point2->getErrorLog();
											carve::geom::vector<3> trim_point;
											placementConverter->convertIfcCartesianPoint(trim_point2, trim_point);

											trim_angle2 = getAngleOnCircle(circle_center,
												circle_radius,
												trim_point);
										}
										catch (...) {
											BLUE_LOG(error) << "Processing " << circle->getErrorLog() << ": Exception occured!";
											return;
										}
									}
									else {
										BLUE_LOG(warning) << "Processing " << circle->getErrorLog() << ": No trimming end.";
									}
								}
							}
							else {
								BLUE_LOG(warning) << "Processing " << circle->getErrorLog() << ": trim2vec is empty!";
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

							// correct for -2*PI <= angle <= 2*PI
							if (opening_angle > 0) {
								GeomSettings()->normalizeAngle(opening_angle, 0., M_TWOPI);
							}
							else {
								GeomSettings()->normalizeAngle(opening_angle, -M_TWOPI, 0.);
							}

							int num_segments = GeomSettings()->getNumberOfSegmentsForTesselation( circle_radius, abs(opening_angle) );

							const double circle_center_x = 0.0;
							const double circle_center_y = 0.0;
							std::vector<carve::geom::vector<2> > circle_points;
							ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
								circle_points, circle_radius, 
								start_angle, opening_angle, 
								circle_center_x, circle_center_y, 
								num_segments);

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
								segmentStartPoints.push_back(carve::geom::VECTOR(
									circle_points.at(0).x,
									circle_points.at(0).y,
									0));
							}

							return;
						} // end if IfcCircle

						// (2/2) IfcEllipse SUBTYPE OF IfcConic
						std::shared_ptr<typename IfcEntityTypesT::IfcEllipse> ellipse =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEllipse>(conic);
						if (ellipse) {
							if (ellipse->SemiAxis1) {
								if (ellipse->SemiAxis2) {

									double xRadius = ellipse->SemiAxis1 * length_factor;
									double yRadius = ellipse->SemiAxis2 * length_factor;

									double radiusMax = std::max(xRadius, yRadius);
									double radiusMin = std::min(xRadius, yRadius);
									int num_segments = GeomSettings()->getNumberOfSegmentsForTesselation(radiusMin);
									double deltaAngle = GeomSettings()->getAngleLength(radiusMin);

									// todo: implement clipping
									if( !trim1Vec.empty() || !trim2Vec.empty() )
										BLUE_LOG(warning) << ellipse->getErrorLog() << ": Trimming not supported";

									std::vector<carve::geom::vector<3> > ellipse_points;
									double angle = 0.0;
									for (int i = 0; i < num_segments; ++i) {
										ellipse_points.push_back(carve::geom::vector<3>(
											carve::geom::VECTOR(
												xRadius * cos(angle),
												yRadius * sin(angle),
												0)));
										angle += deltaAngle;
									}

									// apply position
									for (unsigned int i = 0; i < ellipse_points.size(); ++i) {
										carve::geom::vector<3>& point = ellipse_points.at(i);
										point = conic_position_matrix * point;
									}
									GeomUtils::appendPointsToCurve(ellipse_points, targetVec);
									segmentStartPoints.push_back(ellipse_points.at(0));
								}
							}
							return;
						} // end if ellipse

						// the rest makes a return
						BLUE_LOG(warning) << conic->getErrorLog() << ": Not supported";
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
						placementConverter->convertIfcCartesianPoint(ifc_line_point, line_origin);

						std::shared_ptr<typename IfcEntityTypesT::IfcVector> line_vec = line->Dir.lock();
						if (!line_vec) {
							BLUE_LOG(error) << line->getErrorLog() << ": No direction specified";
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
								placementConverter->convertIfcCartesianPoint(ifc_trim_point, trim_point);

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
								placementConverter->convertIfcCartesianPoint(ifc_trim_point, trim_point);

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
						segmentStartPoints.push_back(line_origin);
						return;
					} // end if IfcLine

					// ************************************************************************************************************************	//
					//	IfcOffsetCurve SUPTYPE of IfcCurve																						//
					//	ABSTRACT SUPERTYPE OF IfcOffsetCurve2D, IfcOffsetCurve3D, IfcOffsetCurveByDistances										//
					// ************************************************************************************************************************	//
					// TODO: IMPLEMENT OFFSETCURVE, PCURVE, SURFACECURVE
					std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve> offset_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve>(ifcCurve);
					if (offset_curve) {
						BLUE_LOG(warning) << offset_curve->getErrorLog() << ": Not supported";
						return;
						/*
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
						*/
					} // end if IfcOffsetCurve

					// ************************************************************************************************************************	//
					//	IfcPcurve SUPTYPE of IfcCurve																							//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcPcurve> p_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPcurve>(ifcCurve);
					if (p_curve)
					{
						BLUE_LOG(warning) << p_curve->getErrorLog() << ": Not supported";
						return;
						// TO DO: implement
					} // end if IfcPcurve

					// ************************************************************************************************************************	//
					//	IfcSurfaceCurve SUPTYPE of IfcCurve																						//
					//	ABSTRACT SUPERTYPE OF IfcIntersectionCurve, IfcSeamCurve																//
					// ************************************************************************************************************************	//
					std::shared_ptr<typename IfcEntityTypesT::IfcSurfaceCurve> surface_curve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurfaceCurve>(ifcCurve);
					if (surface_curve)
					{
						BLUE_LOG(warning) << surface_curve->getErrorLog() << ": Not supported";
						return;
						/*
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
						*/
					} // end if IfcSurfaceCurve

					BLUE_LOG(warning) << ifcCurve->getErrorLog() << ": Not supported";
					return;
				} // end convertIfcCurve (function)

				/*! \brief Calls CurveConverterT::convertIfcCurve and converts the results to 2D.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] loops					The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				*
				* \note Calls the other overload CurveConverterT::convertIfcCurve2D with empty \c IfcTrimmingSelect-s.
				*/
				void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& loops,
					std::vector<carve::geom::vector<2>>& segmentStartPoints) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim2Vec;
					convertIfcCurve2D(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
				}

				/*! \brief Calls CurveConverterT::convertIfcCurve and converts the results to 2D.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] targetVec				The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*
				* \note Calls the CurveConverterT::convertIfcCurve and converts the results to 2D.
				*/
				void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& targetVec,
					std::vector<carve::geom::vector<2>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement) const
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

				/*! \brief Converts \c IfcPolyline to a series of points.
				*
				* This function is called from CurveConverterT::convertIfcCurve but is provided for simplicity reasons.
				*
				* \param[in] ifcpolyline			The \c IfcPolyline to be converted.
				* \param[out] loop					The series of points.
				*/
				void convertIfcPolyline(const std::shared_ptr<typename IfcEntityTypesT::IfcPolyline>& ifcpolyline,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> points;
					points.resize(ifcpolyline->Points.size());
					std::transform(
						ifcpolyline->Points.begin(),
						ifcpolyline->Points.end(),
						points.begin(),
						[](auto& it) { return it.lock(); }
					);
					convertIfcCartesianPointVector(points, loop);
				}

				/*! \brief Converts \c IfcLoop and its subtypes to a series of points.
				*
				* \param[in] ifcloop				The \c IfcLoop to be converted.
				* \param[out] loop					The series of points.
				*
				* \note The function disregards topological relationships.
				* \note The function is not fully implemented.
				*
				* \internal TODO.
				*/
				void convertIfcLoop(const std::shared_ptr<typename IfcEntityTypesT::IfcLoop>& ifcloop,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					const std::shared_ptr<typename IfcEntityTypesT::IfcPolyLoop> polyLoop =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyLoop>(ifcloop);
					if (polyLoop) 
					{
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>> ifcPoints;
						ifcPoints.resize(polyLoop->Polygon.size());
						std::transform(
							polyLoop->Polygon.begin(),
							polyLoop->Polygon.end(),
							ifcPoints.begin(),
							[](auto &it) { return it.lock(); });

						convertIfcCartesianPointVectorSkipDuplicates(ifcPoints, loop);

						// If first and last point have same coordinates, remove last point
						while (loop.size() > 2) {
							carve::geom3d::Vector& first = loop.front();
							carve::geom3d::Vector& last = loop.back();

							if (abs(first.x - last.x) < 0.00000001) {
								if (abs(first.y - last.y) < 0.00000001) {
									if (abs(first.z - last.z) < 0.00000001) {
										loop.pop_back();
										continue;
									}
								}
							}
							break;
						}
						return;
					} // end if polyloop

					std::shared_ptr<typename IfcEntityTypesT::IfcEdgeLoop> edgeLoop =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeLoop>(ifcloop);
					if (edgeLoop) 
					{
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge>> edgeList;
						edgeList.resize(edgeLoop->EdgeList.size());
						std::transform(
							edgeLoop->EdgeList.begin(),
							edgeLoop->EdgeList.end(),
							edgeList.begin(),
							[](auto &it) {return it.lock(); });

						// go through every edge in the edge list
						for (auto& it_edge = edgeList.begin(); it_edge != edgeList.end(); ++it_edge) {
							// edge loop consists of many oriented edges
							std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge> orientedEdge = (*it_edge);
							// which are described by the type of its edge element object
							std::shared_ptr<typename IfcEntityTypesT::IfcEdge>& edgeElement = orientedEdge->EdgeElement.lock();

							std::shared_ptr<typename IfcEntityTypesT::IfcEdgeCurve> edgeCurve =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeCurve>(edgeElement);

							if (edgeCurve) {
								std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& curveGeom = edgeCurve->EdgeGeometry.lock();
								std::vector<carve::geom::vector<3>> segmentStartPoints;

								convertIfcCurve(curveGeom, loop, segmentStartPoints);

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

				/*! \brief Converts an array of \c IfcCartesianPoint-s to a series of points.
				*
				* \param[in] points				The array of \c IfcCartesianPoint-s to be converted.
				* \param[out] loop				The series of points.
				*/
				void convertIfcCartesianPointVector(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points,
					std::vector<carve::geom::vector<3>>& loop) const
				{
					carve::geom::vector<3> point = carve::geom::VECTOR(0., 0., 0.);
					loop.reserve(loop.size() + points.size());
					for ( auto& it = points.begin(); it != points.end(); ++it )
					{
						placementConverter->convertIfcCartesianPoint(*it, point);
						loop.push_back(point);
					}
				} // end convertIfcCartesianPointVector

				/*! \brief Converts an array of \c IfcCartesianPoint-s to a series of points.
				*
				* \param[in] points				The array of \c IfcCartesianPoint-s to be converted.
				* \param[out] loop				The series of points.
				*
				* \note The function is not fully implemented.
				*
				* \internal TODO.
				*/
				void convertIfcCartesianPointVectorSkipDuplicates(
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints,
					std::vector<carve::geom::vector<3> >& loop) const
				{
					carve::geom::vector<3>  vertex_previous;

					for ( auto& it_cp = ifcPoints.begin(); it_cp != ifcPoints.end(); ++it_cp) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = (*it_cp);

						carve::geom::vector<3>  vertex(carve::geom::VECTOR(0.,0.,0.));
						placementConverter->convertIfcCartesianPoint(*it_cp, vertex);

						// skip duplicate vertices
						if (it_cp != ifcPoints.begin()) {
							if (abs(vertex.x - vertex_previous.x) < 0.00000001) {
								if (abs(vertex.y - vertex_previous.y) < 0.00000001) {
									if (abs(vertex.z - vertex_previous.z) < 0.00000001) {
										// TODO: is it better to report degenerated loops, or to just omit them?
										BLUE_LOG(warning) << "Duplicate point in polyloop. IfcPoint #" << cp->getId();
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

				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;

			}; // end class
		}; // end namespace IfcGeometryConverter
	}; // end namespace Core
}; // end namespace OIP


#endif
