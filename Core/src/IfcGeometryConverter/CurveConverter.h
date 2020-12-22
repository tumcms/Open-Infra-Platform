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
				 * \param[in] ifcCurve		The \c IfcCurve to be converted.
				 * \param[in] pos			The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData		A pointer to be filled with the relevant data.
				 *
				 * \note Calls the other overload CurveConverterT::convertIfcCurve with corresponding input parameters. Adds their result to itemData.
				 */
				void convertIfcCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					std::vector<carve::geom::vector<3>> loops;
					std::vector<carve::geom::vector<3>> segment_start_points;
					convertIfcCurve(ifcCurve, loops, segment_start_points);

					std::shared_ptr<carve::input::PolylineSetData> polylineData = std::make_shared<carve::input::PolylineSetData>();
					polylineData->beginPolyline();
					for (int i = 0; i < loops.size(); ++i) {
						polylineData->addVertex(pos * loops.at(i));
						polylineData->addPolylineIndex(i);
					}
					itemData->polylines.push_back(polylineData);
				}

				/*! \brief Converts an \c IfcCurve to an array of segments to be rendered on screen.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] loops					The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				*
				* \note Calls the other overload CurveConverterT::convertIfcCurve with empty \c IfcTrimmingSelect-s.
				*/
				void convertIfcCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<3>>& loops,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const throw(...)
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
				void convertIfcCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// (1/6) IfcBoundedCurve SUBTYPE of IfcCurve
					if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcBoundedCurve>())
					{
						return convertIfcBoundedCurve(ifcCurve.as<typename IfcEntityTypesT::IfcBoundedCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
					
					// (2/6) IfcConic SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcConic>())
					{
						return convertIfcConic(ifcCurve.as<typename IfcEntityTypesT::IfcConic>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
				
					// (3/6) IfcLine SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcLine>())
					{
						return convertIfcLine(ifcCurve.as<typename IfcEntityTypesT::IfcLine>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
					
					// (4/6) IfcOffsetCurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcOffsetCurve>())
					{
						return convertIfcOffsetCurve(ifcCurve.as<typename IfcEntityTypesT::IfcOffsetCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
					
					// (5/6) IfcPcurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcPcurve>())
					{
						return convertIfcPcurve(ifcCurve.as<typename IfcEntityTypesT::IfcPcurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
					
					// (6/6) IfcSurfaceCurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcSurfaceCurve>())
					{
						return convertIfcSurfaceCurve(ifcCurve.as<typename IfcEntityTypesT::IfcSurfaceCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// the rest we do not support
					throw oip::UnhandledException(ifcCurve);
				} // end convertIfcCurve (function)

				/*! \brief Calls CurveConverterT::convertIfcCurve and converts the results to 2D.
				*
				* \param[in] ifcCurve				The \c IfcCurve to be converted.
				* \param[out] loops					The loops (?)
				* \param[out] segmentStartPoints	The starting points of separate segments (?)
				*
				* \note Calls the other overload CurveConverterT::convertIfcCurve2D with empty \c IfcTrimmingSelect-s.
				*/
				void convertIfcCurve2D(const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& loops,
					std::vector<carve::geom::vector<2>>& segmentStartPoints
				) const throw(...)
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
				void convertIfcCurve2D(const EXPRESSReference<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
					std::vector<carve::geom::vector<2>>& targetVec,
					std::vector<carve::geom::vector<2>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
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

				/**********************************************************************************************/
				/*! \brief Converts an \c IfcBoundedCurve to a tesselated curve.
				* \param[in] polycurve				A pointer to data from \c IfcBoundedCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*/
				// (1/6) IfcBoundedCurve SUBTYPE of IfcCurve
				void convertIfcBoundedCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve>& bounded_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					//	ABSTRACT SUPERTYPE of IfcAlignmentCurve, IfcBsplineCurve, IfcCompositeCurve, IfcIndexedPolycurve, IfcPolyline, IfcIfcTrimmedCurve	//
					// (1/6) IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve
					if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcAlignmentCurve>())
					{
						return convertIfcAlignmentCurve(bounded_curve.as<typename IfcEntityTypesT::IfcAlignmentCurve>(), targetVec, segmentStartPoints);
					} // end if IfcAlignmentCurve


					// (2/6) IfcBSplineCurve SUBTYPE OF IfcBoundedCurve
					else if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcBSplineCurve>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve> bspline_curve = bounded_curve.as<typename IfcEntityTypesT::IfcBSplineCurve>();
						
						SplineConverterT<IfcEntityTypesT> splineConverter(GeomSettings(), UnitConvert(), placementConverter);
						// splineConverter.convertIfcBSplineCurve can handle IfcBSplineCurveWithKnots and IfcRationalBsplineWithKnots, 
						// both are subtypes of IfcBSplineCurve
						splineConverter.convertIfcBSplineCurve(bspline_curve, targetVec);
						return;
					} // end if IfcBSplineCurve

					// (3/6) IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
					else if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcCompositeCurve>()) {
						return convertIfcCompositeCurve(bounded_curve.as<typename IfcEntityTypesT::IfcCompositeCurve>(), targetVec, segmentStartPoints);
					} // end if IfcCompositeCurve

					// (4/6) IfcIndexedPolyCurve SUBTYPE OF IfcBoundedCurve
					else if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcIndexedPolyCurve>())
					{
						return convertIfcIndexedPolyCurve(
							bounded_curve.as<typename IfcEntityTypesT::IfcIndexedPolyCurve>(),
							targetVec, segmentStartPoints,
							trim1Vec, trim2Vec, senseAgreement
						);
					} // end if IfcIndexedPolyCurve

					// (5/6) IfcPolyline SUBTYPE OF IfcBoundedCurve
					else if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcPolyline>()) {
						if (!bounded_curve.as<typename IfcEntityTypesT::IfcPolyline>()->Points.empty()) {
							std::vector<carve::geom::vector<3>> loop = convertIfcPolyline(bounded_curve.as<typename IfcEntityTypesT::IfcPolyline>());

							segmentStartPoints.push_back(loop.at(0));
							targetVec.insert(targetVec.end(), loop.begin(), loop.end());
						}
						return;
					} // end if IfcPolyline

					// (6/6) IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
					else if (bounded_curve.isOfType<typename IfcEntityTypesT::IfcTrimmedCurve>()) {
						return convertIfcTrimmedCurve(bounded_curve.as<typename IfcEntityTypesT::IfcTrimmedCurve>(), targetVec, segmentStartPoints);
					} // end if IfcTrimmedCurve
					
					else {
						// the rest we do not support
						throw oip::UnhandledException( bounded_curve );
					}
				}

				// (1/6) IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates the 3D point along a curve.
				* \param[in] polycurve				A pointer to data from c\ IfcAlignmentCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcAlignmentCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignment_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const throw(...) 
				{
					// the stations at which a point of the tesselation has to be calcuated - to be converted and fill the targetVec
					std::vector<double> stations = getStationsForTessellationOfIfcAlignmentCurve(alignment_curve);

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
				}

				// (3/6) IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates curve segments and appends them to the curve.
				* \param[in] polycurve				A pointer to data from \c IfcCompositeCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcCompositeCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCompositeCurve>& composite_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const throw(...)
				{
					for (auto &segment: composite_curve->Segments) {
						std::vector<carve::geom::vector<3>> segment_vec;

						convertIfcCurve(segment->ParentCurve, segment_vec, segmentStartPoints);
						if (!segment_vec.empty()) {
							GeomUtils::appendPointsToCurve(segment_vec, targetVec);
						}
					}
				}

				// (4/6) IfcIndexedPolyCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] polycurve				A pointer to data from \c IfcIndexedPolyCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*/
				void convertIfcIndexedPolyCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcIndexedPolyCurve>& polycurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4/ADD1/HTML/schema/ifcgeometryresource/lexical/ifcindexedpolycurve.htm
					//	ENTITY IfcIndexedPolyCurve
					//		SUBTYPE OF(IfcBoundedCurve);
					//		Points: IfcCartesianPointList;
					//		Segments: OPTIONAL LIST[1:? ] OF IfcSegmentIndexSelect;
					//		SelfIntersect: OPTIONAL IfcBoolean;
					//	WHERE
					//		Consecutive : (SIZEOF(Segments) = 0) OR IfcConsecutiveSegments(Segments);
					//	END_ENTITY;

					// check input
					if (polycurve.expired())
						throw oip::ReferenceExpiredException(polycurve);

					// get the points
					std::vector<carve::geom::vector<3>> points = convertIfcCartesianPointList(polycurve->Points);

					// are segments there?
					if (polycurve->Segments)
					{
						try
						{
							std::vector<carve::geom::vector<3>> loop;
							for (const auto& seg : polycurve->Segments.get())
							{
								std::vector<carve::geom::vector<3>> loop_intern = convertIfcSegmentIndexSelect(seg, points);
								// skips same points
								GeomUtils::appendPointsToCurve(loop_intern, loop);
							}

							// add the calculated points to the return values
							GeomUtils::appendPointsToCurve(loop, targetVec);
							segmentStartPoints.push_back(loop[0]);
						}
						catch (const oip::InconsistentModellingException& ex) {
							throw oip::InconsistentModellingException(polycurve, ex.what());
						}
					}
					else
					{
						// no segments are there -> it's just a polyline ..
						GeomUtils::appendPointsToCurve(points, targetVec);
						segmentStartPoints.push_back(points[0]);
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] segmentIndexSelect		A pointer to data from IfcSegmentIndexSelect.
				* \param[in] points					The series of points passed from IfcIndexedPolyCurve.
				* return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcSegmentIndexSelect(
					const typename IfcEntityTypesT::IfcSegmentIndexSelect & segmentIndexSelect,
					const std::vector<carve::geom::vector<3>>& points)const throw(...)
				{
					switch (segmentIndexSelect.which())
					{
					case 0:
					{
						// TYPE IfcArcIndex = LIST [3:3] OF IfcPositiveInteger;
						return convertIfcArcIndex(segmentIndexSelect.get<0>(), points);
					}
					case 1:
					{
						// TYPE IfcLineIndex = LIST [2:?] OF IfcPositiveInteger;
						return convertIfcLineIndex(segmentIndexSelect.get<1>(), points);
					}
					default:
						throw oip::UnhandledException();
					}
				}

				// (1/2) TYPE IfcArcIndex = LIST [3:3] OF IfcPositiveInteger;
				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] lineSegment			A pointer to data from IfcLineIndex.
				* \param[in] points					The series of points passed from IfcIndexedPolyCurve.
				* return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcLineIndex(
					const typename IfcEntityTypesT::IfcLineIndex &lineSegment,
					const std::vector<carve::geom::vector<3>>& points) const throw(...)
				{
					if (lineSegment.size() < 2)
						throw oip::InconsistentModellingException("The number of indices for one of IfcLineIndex is less than 2!");

					std::vector<carve::geom::vector<3>> loop;
					for (const auto& i : lineSegment)
					{
						loop.push_back(points[i - 1]); //EXPRESS count from 1, C++ from 0
					}
					return loop;
				}
				// (2/2) TYPE IfcLineIndex = LIST [2:?] OF IfcPositiveInteger;
				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] arcSegment				A pointer to data from IfcArcIndex.
				* \param[in] points					The series of points passed from IfcIndexedPolyCurve.
				* return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcArcIndex(
					const typename IfcEntityTypesT::IfcArcIndex &arcSegment,
					const std::vector<carve::geom::vector<3>>& points) const throw(...)
				{
					if (arcSegment.size() != 3)
						throw oip::InconsistentModellingException("The number of indices for one of IfcArcIndex is not 3!");

					carve::geom::vector<3> arcStart = points[arcSegment[0] - 1];
					carve::geom::vector<3> arcMid = points[arcSegment[1] - 1];
					carve::geom::vector<3> arcEnd = points[arcSegment[2] - 1];

					//Converting a 3D to a 2D problem to then find the circle from three points on the plane.
					// see https://math.stackexchange.com/questions/1379217/3-points-in-3d-space-to-find-the-center-of-an-arc-or-circle

					//Start by finding the normal vector to the plane defined by the three points
					//n=unitvector(A×B+B×C+C×A)
					carve::geom::vector<3> normalVector = carve::geom::cross(arcStart, arcMid) + carve::geom::cross(arcMid, arcEnd) + carve::geom::cross(arcEnd, arcStart);
					normalVector.normalize();
					//u=(C−A)×n
					carve::geom::vector<3> firstOrthogonalDirection = carve::geom::cross(arcEnd - arcStart, normalVector);
					firstOrthogonalDirection.normalize();
					//v=n×u
					carve::geom::vector<3> secondOrthogonalDirection = carve::geom::cross(normalVector, firstOrthogonalDirection);
					secondOrthogonalDirection.normalize();

					//Calculate distance of the plane to the origin
					double distance = (normalVector.x * arcStart.x) + (normalVector.y * arcStart.y) + (normalVector.z * arcStart.z);

					//Convert the problem into a 2D problem
					carve::math::Matrix rotationMatrix = carve::math::Matrix(
						firstOrthogonalDirection.x, secondOrthogonalDirection.x, 0., 0.,
						firstOrthogonalDirection.y, secondOrthogonalDirection.y, 0., 0.,
						firstOrthogonalDirection.z, secondOrthogonalDirection.z, 1., 0.,
						0., 0., 0., 1.);

					carve::geom::vector<2> arcStart2D = convert3Dto2D(rotationMatrix, arcStart);
					carve::geom::vector<2> arcMid2D = convert3Dto2D(rotationMatrix, arcMid);
					carve::geom::vector<2> arcEnd2D = convert3Dto2D(rotationMatrix, arcEnd);

					//Calculating arc in 2D 
					double yDeltaA = arcMid2D.y - arcStart2D.y;
					double xDeltaA = arcMid2D.x - arcStart2D.x;
					double yDeltaB = arcEnd2D.y - arcMid2D.y;
					double xDeltaB = arcEnd2D.x - arcMid2D.x;

					if (xDeltaA != 0. && xDeltaB != 0.) {
						double aSlope = yDeltaA / xDeltaA;
						double bSlope = yDeltaB / xDeltaB;

						double centerOfCircleX = (aSlope*bSlope*(arcStart2D.y - arcEnd2D.y) + bSlope * (arcStart2D.x + arcMid2D.x)
							- aSlope * (arcMid2D.x + arcEnd2D.x)) / (2. * (bSlope - aSlope));

						double centerOfCircleY = -(centerOfCircleX - (arcStart2D.x + arcMid2D.x) * 0.5) / aSlope + (arcStart2D.y + arcMid2D.y) * 0.5;

						carve::geom::vector<2> radiusVector = carve::geom::VECTOR(arcStart2D.x - centerOfCircleX, arcStart2D.y - centerOfCircleY);
						double radius = radiusVector.length();

						double theta1 = std::atan2(arcStart2D.y - centerOfCircleY, arcStart2D.x - centerOfCircleX);
						double theta2 = std::atan2(arcEnd2D.y - centerOfCircleY, arcEnd2D.x - centerOfCircleX);

						double opening_angle = (theta2 - theta1);

						// correct for -2*PI <= angle <= 2*PI
						if (opening_angle > 0) {
							GeomSettings()->normalizeAngle(opening_angle, 0., M_TWOPI);
						}
						else {
							GeomSettings()->normalizeAngle(opening_angle, -M_TWOPI, 0.);
						}

						int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(radius, abs(opening_angle));

						std::vector<carve::geom::vector<2> > circle_points;
						ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
							circle_points, radius,
							theta1, opening_angle,
							centerOfCircleX, centerOfCircleY,
							num_segments);

						//std::vector<carve::geom::vector<3>> arcPoints;
						std::vector<carve::geom::vector<3>> loop_intern;
						loop_intern.push_back(arcStart);
						for (int i = 1; i < circle_points.size(); i++) {

							loop_intern.push_back(carve::geom::VECTOR(
								normalVector.x * distance + firstOrthogonalDirection.x * circle_points[i].x + secondOrthogonalDirection.x * circle_points[i].y,
								normalVector.y * distance + firstOrthogonalDirection.y * circle_points[i].x + secondOrthogonalDirection.y * circle_points[i].y,
								normalVector.z * distance + firstOrthogonalDirection.z * circle_points[i].x + secondOrthogonalDirection.z * circle_points[i].y));
						}
						return loop_intern;
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] conversionMatrix		A pointer to data from IfcIndexedPolyCurve.
				* \param[in] vector3D				Vector in 3D
				* return							Converted vector in 2D.
				*/
				carve::geom::vector<2> convert3Dto2D(const carve::math::Matrix&  conversionMatrix, const carve::geom::vector<3>& vector3D) const throw(...) {
					return carve::geom::VECTOR((conversionMatrix._11 * vector3D.x + conversionMatrix._12 * vector3D.y + conversionMatrix._13 * vector3D.z),
						(conversionMatrix._21 * vector3D.x + conversionMatrix._22 * vector3D.y + conversionMatrix._23 * vector3D.z));
				}

				// (5/6) IfcPolyline SUBTYPE OF IfcBoundedCurve
				/*! \brief Converts \c IfcPolyline to a series of points.
				 *
				 * \param[in] ifcpolyline			The \c IfcPolyline to be converted.
				 *
				 * \returns							The series of points.
				 */
				std::vector<carve::geom::vector<3>> convertIfcPolyline(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPolyline>& ifcpolyline
				) const throw(...)
				{
					// **************************************************************************************************************************
					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcpolyline.htm
					// **************************************************************************************************************************
					if (ifcpolyline.expired())
						throw oip::ReferenceExpiredException(ifcpolyline);

					return convertIfcCartesianPointVector(ifcpolyline->Points);
				}

				// (6/6) IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates trimming points of the curve. 
				* \param[in] polycurve				A pointer to data from c\ IfcTrimmedCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcTrimmedCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcTrimmedCurve>& trimmed_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints) const throw(...)
				{
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
					// end
					return;
				}

				// (2/6) IfcConic SUPTYPE of IfcCurve
				void convertIfcConic(
					const EXPRESSReference<typename IfcEntityTypesT::IfcConic>& conic,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// ABSTRACT SUPERTYPE of IfcCircle, IfcEllipse

					// (1/2) IfcCircle SUBTYPE OF IfcConic
					if (conic.isOfType<typename IfcEntityTypesT::IfcCircle>()) 
					{
						return convertIfcCircle( conic.as<typename IfcEntityTypesT::IfcCircle>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcCircle

					// (2/2) IfcEllipse SUBTYPE OF IfcConic
					else if (conic.isOfType<typename IfcEntityTypesT::IfcEllipse>())
					{
						return convertIfcEllipse(conic.as<typename IfcEntityTypesT::IfcEllipse>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					} // end if ellipse

					// the rest we do not support
					throw oip::UnhandledException(conic);
				}

				// (1/2) IfcCircle SUBTYPE OF IfcConic
				/**********************************************************************************************/
				/*! \brief Calculates ponts of the circle curve.
				* \param[in] polycurve				A pointer to data from c\ IfcCircle.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*/
				void convertIfcCircle(
					const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// determine position
					carve::math::Matrix conic_position_matrix = placementConverter->convertIfcAxis2Placement(circle->Position);

					// Get radius
					double circle_radius = 0.0;
					if (circle->Radius) {
						circle_radius = circle->Radius * UnitConvert()->getLengthInMeterFactor();
					}
					else {
						throw oip::InconsistentGeometryException(circle, "No radius!");
					}

					carve::geom::vector<3> circle_center =
						conic_position_matrix * carve::geom::VECTOR(0, 0, 0);

					//Calculate an angle on the circle for trimming begin.
					double start_angle = calculateTrimmingPointOnCircle(circle, trim1Vec, circle_center, circle_radius);
					//Calculate an angle on the circle for trimming end.
					double trim_angle2 = calculateTrimmingPointOnCircle(circle, trim2Vec, circle_center, circle_radius);

					double opening_angle = 0.0;

					if (senseAgreement) {
						if (start_angle < trim_angle2) {
							opening_angle = trim_angle2 - start_angle;
						}
						else {
							// circle passes 0 angle
							opening_angle = trim_angle2 - start_angle + 2.0*M_PI;
						}
					}
					else {
						if (start_angle > trim_angle2) {
							opening_angle = trim_angle2 - start_angle;
						}
						else {
							// circle passes 0 angle
							opening_angle = trim_angle2 - start_angle - 2.0*M_PI;
						}
					}

					// correct for -2*PI <= angle <= 2*PI
					if (opening_angle > 0) {
						GeomSettings()->normalizeAngle(opening_angle, 0., M_TWOPI);
					}
					else {
						GeomSettings()->normalizeAngle(opening_angle, -M_TWOPI, 0.);
					}

					int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(circle_radius, abs(opening_angle));

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
				}

				/**********************************************************************************************/
				/*! \brief Calculates the angle on the circle of the trimming point.
				* \param[in] circle				A pointer to data from c\ IfcCircle.
				* \param[in] trimmingVector		The trimming of the curve as saved in IFC model
				* \param[in] circle_center		Coordinates of the center of the circle.
				* \param[in] circle_radius		Radius of the circle.
				* \return						Angle on the circle of the trimming point.
				*/
				double  calculateTrimmingPointOnCircle(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trimmingVector,
					const carve::geom::vector<3> circle_center,
					const double circle_radius) const throw(...)
				{

					// Check for trimming point
					if (trimmingVector.size() > 0) {
						//BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Check for trimming point.";
						auto first = std::find_if(trimmingVector.begin(), trimmingVector.end(), [](auto select) { return select->which() == 1; });
						if (first != trimmingVector.end() && *first) {
							//BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming pomt as IfcParameterValue.";
							typename IfcEntityTypesT::IfcParameterValue trim_par1 = (*first)->get<1>();
							return trim_par1 * UnitConvert()->getAngleInRadianFactor();
						}
						else {
							first = std::find_if(trimmingVector.begin(), trimmingVector.end(), [](auto select) { return select->which() == 0; });
							if (first != trimmingVector.end() && (*first) != nullptr) {
								//BLUE_LOG(trace) << "Processing " << circle->getErrorLog() << ": Found trimming point as IfcCartesianPoint.";
								try {
									carve::geom::vector<3> trim_point = placementConverter->convertIfcCartesianPoint((*first)->get<0>());

									return getAngleOnCircle(circle_center, circle_radius, trim_point);
								}
								catch (const oip::InconsistentModellingException& ex) {
									throw oip::InconsistentModellingException(circle, ex.what());
								}
							}
							else {
								throw oip::InconsistentGeometryException(circle, "No trimming point found.");
							}
						}
					}
					else {
						throw oip::InconsistentGeometryException(circle, "Trimming vector is empty!");
					}
				}

				// (2/2) IfcEllipse SUBTYPE OF IfcConic
				void convertIfcEllipse(
					const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// determine position
					carve::math::Matrix conic_position_matrix = placementConverter->convertIfcAxis2Placement(ellipse->Position);

					if (ellipse->SemiAxis1) {
						if (ellipse->SemiAxis2) {

							double xRadius = ellipse->SemiAxis1 * UnitConvert()->getLengthInMeterFactor();
							double yRadius = ellipse->SemiAxis2 * UnitConvert()->getLengthInMeterFactor();

							double radiusMax = std::max(xRadius, yRadius);
							double radiusMin = std::min(xRadius, yRadius);
							int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(radiusMin);
							double deltaAngle = GeomSettings()->getAngleLength(radiusMin);

							// todo: implement clipping
							if (!trim1Vec.empty() || !trim2Vec.empty())
								throw oip::InconsistentModellingException(ellipse, "Trimming not supported");

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
				}

				// (3/6) IfcLine SUPTYPE of IfcCurve
				void convertIfcLine(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLine>& line,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// Part 1: Get information from IfcLine. 

					// Get IfcLine attributes: line point and line direction. 
					carve::geom::vector<3> line_origin = placementConverter->convertIfcCartesianPoint(line->Pnt);

					EXPRESSReference<typename IfcEntityTypesT::IfcVector> line_vec = line->Dir;
					if (!line_vec) {
						throw oip::InconsistentGeometryException(line, " No direction specified");
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
								direction_ratios[1], 0.0);
						}
					}
					line_direction.normalize();

					// Magnitude type IfcLengthMeasure
					double line_magnitude = line_vec->Magnitude * UnitConvert()->getLengthInMeterFactor();

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
						auto first_point = std::find_if(trim1Vec.begin(), trim1Vec.end(), [](auto select_ptr) { return select_ptr->which() == 0; });

						if (first_point != trim1Vec.end() && *first_point) {
							carve::geom::vector<3> trim_point = placementConverter->convertIfcCartesianPoint((*first_point)->get<0>());

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
						line_magnitude = trim_par2 * UnitConvert()->getLengthInMeterFactor();
						line_end = line_origin + line_direction * line_magnitude;
					}
					else {
						auto first_point = std::find_if(trim2Vec.begin(), trim2Vec.end(), [](auto select_ptr) { return select_ptr->which() == 0; });

						if (first_point != trim2Vec.end() && *first_point) {
							carve::geom::vector<3> trim_point = placementConverter->convertIfcCartesianPoint((*first_point)->get<0>());

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
				}

				// (4/6) IfcOffsetCurve SUPTYPE of IfcCurve
				void convertIfcOffsetCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurve>& offset_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					//	ABSTRACT SUPERTYPE OF IfcOffsetCurve2D, IfcOffsetCurve3D, IfcOffsetCurveByDistances										//

					throw oip::UnhandledException(offset_curve);
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
				}

				// (5/6) IfcPcurve SUPTYPE of IfcCurve
				void convertIfcPcurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPcurve>& pcurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(pcurve);
				}

				// (6/6) IfcSurfaceCurve SUPTYPE of IfcCurve
				void convertIfcSurfaceCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceCurve>& surface_curve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					//	ABSTRACT SUPERTYPE OF IfcIntersectionCurve, IfcSeamCurve																//

					throw oip::UnhandledException(surface_curve);

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
				void convertIfcLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcLoop>& ifcloop,
					std::vector<carve::geom::vector<3>>& loop
				) const throw(...)
				{
					if (ifcloop.isOfType<typename IfcEntityTypesT::IfcPolyLoop>()) 
					{	
						convertIfcCartesianPointVectorSkipDuplicates(ifcloop.as<typename IfcEntityTypesT::IfcPolyLoop>()->Polygon, loop);
						convertIfcPolyLoop(loop);
						return;
					} // end if polyloop

					if (ifcloop.isOfType<typename IfcEntityTypesT::IfcEdgeLoop>())
					{

						convertIfcEdgeLoop(ifcloop.as<typename IfcEntityTypesT::IfcEdgeLoop>(), loop);
						return;
					} // end if edge loop

					throw oip::UnhandledException(ifcloop);
				} // end convertIfcLoop

				/*! \brief Converts \c IfcPolyLoop to a series of points.
				* \param[out] loop					The series of points.
				*/
				void convertIfcPolyLoop(std::vector<carve::geom::vector<3>>& loop) const throw(...)
				{
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
				}

				/*! \brief Converts \c IfcEdgeLoop to a series of points.
				* \param[in] edgeLoop				The \c IfcEdgeLoop to be converted.
				* \param[out] loop					The series of points.
				*/
				void convertIfcEdgeLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcEdgeLoop>& edgeLoop,
					std::vector<carve::geom::vector<3>>& loop) const throw(...)
				{
					/*
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge>> edgeList;
					edgeList.resize(edgeLoop->EdgeList.size());*/
					

					for (auto &orientedEdge : edgeLoop->EdgeList) {
						// which are described by the type of its edge element object
						EXPRESSReference<typename IfcEntityTypesT::IfcEdge> edgeElement = orientedEdge->EdgeElement;

						if (edgeElement.isOfType<typename IfcEntityTypesT::IfcEdgeCurve>()) {
							auto edgeCurve = edgeElement.as<typename IfcEntityTypesT::IfcEdgeCurve>();
							EXPRESSReference<typename IfcEntityTypesT::IfcCurve> curveGeom = edgeCurve->EdgeGeometry;
							std::vector<carve::geom::vector<3>> segmentStartPoints;

							convertIfcCurve(curveGeom, loop, segmentStartPoints);
							continue;
						}

						if (edgeElement.isOfType<typename IfcEntityTypesT::IfcSubedge>()) {
							auto subEdge = edgeElement.as<typename IfcEntityTypesT::IfcSubedge>();
							// Not yet implemented!
							throw oip::UnhandledException(edgeLoop);
						}
						/*
						std::cout << "ERROR\t| Entity " << orientedEdge->classname() << " not handled" << std::endl;
						BLUE_LOG(warning) << "Developer Warning: Entity " << orientedEdge->classname() << " not handled.";*/

						// every edge consists of one start and end vertex
						EXPRESSReference<typename IfcEntityTypesT::IfcVertex> edgeStartVertex = edgeElement->EdgeStart;

						if (edgeStartVertex.isOfType<typename IfcEntityTypesT::IfcVertexPoint>())
						{
							auto edgeStartVertexPoint = edgeStartVertex.as<typename IfcEntityTypesT::IfcVertexPoint>();

							if (edgeStartVertexPoint->VertexGeometry)
							{
								EXPRESSReference<typename IfcEntityTypesT::IfcPoint> startPoint = edgeStartVertexPoint->VertexGeometry;

								if (!startPoint.isOfType<typename IfcEntityTypesT::IfcCartesianPoint>())
								{
									auto ifcPoint = startPoint.as<typename IfcEntityTypesT::IfcCartesianPoint>();
									// TODO: could be also  IfcPointOnCurve, IfcPointOnSurface
									// Not yet implemented!
									throw oip::UnhandledException(edgeLoop);
									continue;
								}
								// TODO: implement
							}
						}
					}
				}



				/*! \internal TODO refactor*/
				void convertIfcEdge(
					const EXPRESSReference<typename IfcEntityTypesT::IfcEdge>& ifcEdge,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<carve::input::PolylineSetData> polyline_data
				) const throw(...)
				{
					polyline_data->beginPolyline();

					auto& vertex_start = ifcEdge->EdgeStart;
					std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_start_point =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_start.lock());
					if (vertex_start_point) {
						carve::geom::vector<3> point = placementConverter->convertIfcPoint(vertex_start_point->VertexGeometry);

						polyline_data->addVertex(objectPlacement * point);
						polyline_data->addPolylineIndex(0);
					}

					auto& vertex_end = ifcEdge->EdgeEnd;
					std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_end_point =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_end.lock());
					if (vertex_end_point) {
						carve::geom::vector<3> point = placementConverter->convertIfcPoint(vertex_end_point->VertexGeometry);

						polyline_data->addVertex(objectPlacement * point);
						polyline_data->addPolylineIndex(1);
					}
				}


				/*! \brief Converts an array of \c IfcCartesianPoint-s to a series of \c carve points.
				*
				* \param[in] points				The array of \c IfcCartesianPoint-s to be converted.
				* \returns						The series of \c carve points.
				*/
				std::vector<carve::geom::vector<3>> convertIfcCartesianPointVector(
					const std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>>& points
				) const throw(...)
				{
					// initialize the return value with enough space
					std::vector<carve::geom::vector<3>> loop;
					loop.reserve(points.size());
					// convert each point individually and add to the return vector
					for ( auto& it : points )
						loop.push_back(placementConverter->convertIfcCartesianPoint(it));
					// return the loop
					return loop;
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
					const std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints,
					std::vector<carve::geom::vector<3> >& loop
				) const throw(...)
				{
					carve::geom::vector<3>  vertex_previous;
					bool first = true;

					for ( auto& it_cp : ifcPoints) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = it_cp.lock();

						carve::geom::vector<3>  vertex = placementConverter->convertIfcCartesianPoint( it_cp );

						// skip duplicate vertices
						if (!first) {
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
						else
							first = false;

						loop.push_back(vertex);
						vertex_previous = vertex;
					}
				}

				std::vector<carve::geom::vector<3> > convertIfcCartesianPointList(
					const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPointList>& pointlist
				) const throw(...)
				{
					// **************************************************************************************************************************
					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4/ADD1/HTML/link/ifccartesianpointlist.htm
					// ENTITY IfcCartesianPointList
					// ABSTRACT SUPERTYPE OF(ONEOF(IfcCartesianPointList2D, IfcCartesianPointList3D))

					// ENTITY IfcCartesianPointList2D
					//	SUBTYPE OF(IfcCartesianPointList);
					//	CoordList: LIST[1:? ] OF LIST[2:2] OF IfcLengthMeasure;
					// END_ENTITY;

					// https://standards.buildingsmart.org/IFC/RELEASE/IFC4/ADD1/HTML/link/ifccartesianpointlist3d.htm
					// ENTITY IfcCartesianPointList3D
					//	SUBTYPE OF(IfcCartesianPointList);
					//	CoordList: LIST[1:? ] OF LIST[3:3] OF IfcLengthMeasure;
					// END_ENTITY;
					// **************************************************************************************************************************

					// check input
					if (pointlist.expired())
						throw oip::ReferenceExpiredException(pointlist);
					
					std::vector<carve::geom::vector<3> > loop;
					// interpret the points
					if (pointlist.isOfType<typename IfcEntityTypesT::IfcCartesianPointList2D>())
					{
						const auto& pointlist2d = pointlist.as<typename IfcEntityTypesT::IfcCartesianPointList2D>();
						loop.reserve(pointlist2d->CoordList.size());
						for (const auto& point : pointlist2d->CoordList)
							loop.push_back(carve::geom::VECTOR(point[0], point[1], 0.) * UnitConvert()->getLengthInMeterFactor());
					}
					else if (pointlist.isOfType<typename IfcEntityTypesT::IfcCartesianPointList3D>())
					{
						const auto& pointlist3d = pointlist.as<typename IfcEntityTypesT::IfcCartesianPointList3D>();
						loop.reserve(pointlist3d->CoordList.size());
						for (const auto& point : pointlist3d->CoordList)
							loop.push_back(carve::geom::VECTOR(point[0], point[1], point[2]) * UnitConvert()->getLengthInMeterFactor());
					}
					else
						throw oip::UnhandledException(pointlist);

					return loop;
				}


				// \internal Doxycomment missing
				std::vector<double> getStationsForTessellationOfIfcAlignmentCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignment_curve
				) const throw(...)
				{
					// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve
					// the stations at which a point of the tesselation has to be calcuated
					std::vector<double> stations;

					// **************************************************************************************************************************** //
					// Step 1: Get segment information from horizontal and vertical alignments.
					std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignment_curve->Horizontal.lock();

					if (!horizontal)
						throw oip::InconsistentModellingException(alignment_curve, "No IfcAlignment2DHorizontal");

					// StartDistAlong type IfcLengthMeasure [0:1]
					double horStartDistAlong = horizontal->StartDistAlong.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();

					// Segments type IfcAlignment2DHorizontalSegment L[1:?]
					if (horizontal->Segments.empty())
						throw oip::InconsistentModellingException(horizontal, "No segments");

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
							BLUE_LOG(warning) << "No segments in " << vertical->getErrorLog();
							bOnlyHorizontal = true;
						}
					}

					// start at the beginning of the alignment
					double dCurrentDistAlong = 0.;

					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment>>::iterator itHorizontalSegment = horizontal->Segments.begin();
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment>>::iterator   itVerticalSegment;
					if (!bOnlyHorizontal)
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
						if (!horCurveGeometry) 
							throw oip::InconsistentModellingException(*itHorizontalSegment, "No curve geometry");

						// SegmentLength type IfcPositiveLengthMeasure [1:1]
						if (horCurveGeometry->SegmentLength <= 0.) 
							throw oip::InconsistentGeometryException(horCurveGeometry, "Curve segment length is " + std::to_string(horCurveGeometry->SegmentLength));
						
						double dHorizontalSegLength = horCurveGeometry->SegmentLength * UnitConvert()->getLengthInMeterFactor();
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
							throw oip::InconsistentModellingException(*itHorizontalSegment, "Could not determine tesselation values.");
						}

						dHorizontalRadius *= UnitConvert()->getLengthInMeterFactor();
						nFragments = GeomSettings()->getNumberOfSegmentsForTessellation(dHorizontalRadius);
						dFragmentLength = dHorizontalSegLength / (double)(nFragments);
						// Step 2 finished: We have the necessary information from the horizontal element

						// Step 3: Get vertical segment type and store number and length of fragments.
						double dOverlapStart = dHorizontalSegStart, dOverlapEnd = dHorizontalSegEnd; // where does the overlap happen?
						if (!bOnlyHorizontal // if there is a vertical alignment
							&& itVerticalSegment != vertical->Segments.end()) // the vertical alignment may be shorter than horizontal
						{
							// check, if the current vertical segment overlaps the horizontal
							bool bLoop = true;
							double dVerticalSegLength = 0.;
							double dVerticalSegEnd = 0.;

							while (bLoop)
							{
								// StartDistAlong type IfcLengthMeasure [1:1]
								dVerticalSegStart = (*itVerticalSegment)->StartDistAlong * UnitConvert()->getLengthInMeterFactor();

								// HorizontalLength type IfcPositiveLengthMeasure [1:1]
								if ((*itVerticalSegment)->HorizontalLength <= 0.0) 
									throw oip::InconsistentGeometryException(*itVerticalSegment, "Invalid horizontal length.");
								
								dVerticalSegLength = (*itVerticalSegment)->HorizontalLength * UnitConvert()->getLengthInMeterFactor();
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
									throw oip::InconsistentModellingException(*itVerticalSegment, "Invalid sequence of vertical elements.");

								// take the next element
								if (bLoop)
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
								throw oip::InconsistentModellingException(*itVerticalSegment, "Could not determine tesselation values.");
							}

							dVerticalRadius *= UnitConvert()->getLengthInMeterFactor();

							// determine tesselation density
							int nVerFragments = GeomSettings()->getNumberOfSegmentsForTessellation(dVerticalRadius);
							double dVerFragmentsLength = dVerticalSegLength / (double)(nVerFragments);

							// Select greater accuracy / more fragments / smaller fragments.
							nFragments = std::max(nFragments, nVerFragments);
							dFragmentLength = std::min(dFragmentLength, dVerFragmentsLength);

							// determine the overlap area
							dOverlapStart = std::max(dOverlapStart, dVerticalSegStart);
							dOverlapEnd = std::min(dOverlapEnd, dVerticalSegEnd);
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
						if (dOverlapEnd >= dHorizontalSegEnd)
						{
							itHorizontalSegment++;
							dHorizontalSegStart = dHorizontalSegEnd; // save the end station of itHorizontalSegment for the next iteration
						}
						// vice versa
						else
						{
							if (itVerticalSegment != vertical->Segments.end())
								itVerticalSegment++;
						}

					} // end of horizontal / vertical segments while iteration
					// add the last station
					stations.push_back(dHorizontalSegStart);

					return stations;
				}

				// Function 3: Get angle on circle (returns angle if the given point lies on the circle; if not, -1 is returned). 
				double getAngleOnCircle(const carve::geom::vector<3>& circleCenter,
					double circleRadius,
					const carve::geom::vector<3>& trimPoint
				) const throw(...)
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
