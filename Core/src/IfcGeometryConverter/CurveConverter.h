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
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifccurve.htm
					//	ENTITY IfcCurve
					//		ABSTRACT SUPERTYPE OF(ONEOF
					//			(IfcBlossCurve,
					//			IfcBoundedCurve,
					//			IfcConic,
					//			IfcLine,
					//			IfcOffsetCurve,
					//			IfcPcurve,
					//			IfcSeriesParameterCurve,
					//			IfcSurfaceCurve))
					//		SUBTYPE OF(IfcGeometricRepresentationItem);
					//		DERIVE
					//		Dim : IfcDimensionCount: = IfcCurveDim(SELF);
					//	END_ENTITY;
					// **************************************************************************************************************************
					// IfcBlossCurve SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
					if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcBlossCurve>())
					{
						return convertIfcBlossCurve(ifcCurve.as<typename IfcEntityTypesT::IfcBlossCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
#endif

					// IfcBoundedCurve SUBTYPE of IfcCurve
					if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcBoundedCurve>())
					{
						return convertIfcBoundedCurve(ifcCurve.as<typename IfcEntityTypesT::IfcBoundedCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// IfcClothoid SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcClothoid>())
					{
						return convertIfcClothoid(ifcCurve.as<typename IfcEntityTypesT::IfcClothoid>(), 
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
#endif
					
					// IfcConic SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcConic>())
					{
						return convertIfcConic(ifcCurve.as<typename IfcEntityTypesT::IfcConic>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// IfcLine SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcLine>())
					{
						return convertIfcLine(ifcCurve.as<typename IfcEntityTypesT::IfcLine>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// IfcOffsetCurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcOffsetCurve>())
					{
						return convertIfcOffsetCurve(ifcCurve.as<typename IfcEntityTypesT::IfcOffsetCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// IfcPcurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcPcurve>())
					{
						return convertIfcPcurve(ifcCurve.as<typename IfcEntityTypesT::IfcPcurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}

					// IfcSeriesParameterCurve SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcSeriesParameterCurve>())
					{
						return convertIfcSeriesParameterCurve(ifcCurve.as<typename IfcEntityTypesT::IfcSeriesParameterCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
#endif

					// IfcSurfaceCurve SUPTYPE of IfcCurve
					else if (ifcCurve.isOfType<typename IfcEntityTypesT::IfcSurfaceCurve>())
					{
						return convertIfcSurfaceCurve(ifcCurve.as<typename IfcEntityTypesT::IfcSurfaceCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					}
					else 
					{
						// the rest we do not support
						throw oip::UnhandledException(ifcCurve);
					}
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

				// IfcBlossCurve SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcBlossCurve to a tesselated curve.
				* \param[in] blossCurve				A pointer to data from \c IfcBlossCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcBlossCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcBlossCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcBlossCurve>& blossCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(blossCurve);
				}
#endif

				/**********************************************************************************************/
				/*! \brief Converts an \c IfcBoundedCurve to a tesselated curve.
				* \param[in] boundedCurve			A pointer to data from \c IfcBoundedCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcBoundedCurve.
				*/
				// IfcBoundedCurve SUBTYPE of IfcCurve
				void convertIfcBoundedCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve>& boundedCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcboundedcurve.htm
					//	ENTITY IfcBoundedCurve
					//		ABSTRACT SUPERTYPE OF(ONEOF
					//			(IfcAlignmentCurve,
					//			IfcBSplineCurve,
					//			IfcCompositeCurve,
					//			IfcCurveSegment2D,
					//			IfcIndexedPolyCurve,
					//			IfcPolyline,
					//			IfcTrimmedCurve))
					//		SUBTYPE OF(IfcCurve);
					//	END_ENTITY;
					// **************************************************************************************************************************
					// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve (Deprecated starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined( OIP_MODULE_EARLYBINDING_IFC4X2) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
					if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcAlignmentCurve>())
					{
						return convertIfcAlignmentCurve(boundedCurve.as<typename IfcEntityTypesT::IfcAlignmentCurve>(),
							targetVec, segmentStartPoints,
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcAlignmentCurve
#endif

					// IfcBSplineCurve SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcBSplineCurve>()) 
					{
						EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve> bsplineCurve = boundedCurve.as<typename IfcEntityTypesT::IfcBSplineCurve>();
						
						SplineConverterT<IfcEntityTypesT> splineConverter(GeomSettings(), UnitConvert(), placementConverter);
						// splineConverter.convertIfcBSplineCurve can handle IfcBSplineCurveWithKnots and IfcRationalBsplineWithKnots, 
						// both are subtypes of IfcBSplineCurve
						splineConverter.convertIfcBSplineCurve(bsplineCurve, targetVec);
						return;
					} // end if IfcBSplineCurve

					// IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcCompositeCurve>())
					{
						return convertIfcCompositeCurve(boundedCurve.as<typename IfcEntityTypesT::IfcCompositeCurve>(),
							targetVec, segmentStartPoints, 
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcCompositeCurve

					// IfcGradientCurve SUBTYPE of IfcBoundedCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcGradientCurve>())
					{
						return convertIfcGradientCurve(boundedCurve.as<typename IfcEntityTypesT::IfcGradientCurve>(),
							targetVec, segmentStartPoints, 
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcGradientCurve
#endif 

					// IfcIndexedPolyCurve SUBTYPE OF IfcBoundedCurve
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcIndexedPolyCurve>())
					{
						return convertIfcIndexedPolyCurve(
							boundedCurve.as<typename IfcEntityTypesT::IfcIndexedPolyCurve>(),
							targetVec, segmentStartPoints,
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcIndexedPolyCurve

					// IfcPolyline SUBTYPE OF IfcBoundedCurve
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcPolyline>()) 
					{
						if (boundedCurve.as<typename IfcEntityTypesT::IfcPolyline>()->Points.empty()) {
							throw oip::InconsistentModellingException(boundedCurve, "Points are empty!");
						}
						else {
							return convertIfcPolyline(boundedCurve.as<typename IfcEntityTypesT::IfcPolyline>(),
								targetVec, segmentStartPoints,
								trim1Vec, trim2Vec, senseAgreement);
						}
					} // end if IfcPolyline

					// IfcSegmentedReferenceCurve SUBTYPE OF IfcBoundedCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>())
					{
						return convertIfcGradientCurve(boundedCurve.as<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>(),
							targetVec, segmentStartPoints,
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcSegmentedReferenceCurve
#endif 

					// IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
					else if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcTrimmedCurve>()) 
					{
						return convertIfcTrimmedCurve(boundedCurve.as<typename IfcEntityTypesT::IfcTrimmedCurve>(), 
							targetVec, segmentStartPoints,
							trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcTrimmedCurve
					
					else 
					{
						// the rest we do not support
						throw oip::UnhandledException( boundedCurve );
					}
				}

				// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve (Deprecated starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined( OIP_MODULE_EARLYBINDING_IFC4X2) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
				/**********************************************************************************************/
				/*! \brief Calculates the 3D point along a curve.
				* \param[in] alignmentCurve			A pointer to data from c\ IfcAlignmentCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcAlignmentCurve.
				*/
				void convertIfcAlignmentCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignmentCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcalignmentcurve.htm
					//	ENTITY IfcAlignmentCurve
					//		SUBTYPE OF(IfcBoundedCurve);
					//		Horizontal: IfcAlignment2DHorizontal;
					//		Vertical: OPTIONAL IfcAlignment2DVertical;
					//		Tag: OPTIONAL IfcLabel;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// the stations at which a point of the tesselation has to be calcuated - to be converted and fill the targetVec
					std::vector<double> stations = getStationsForTessellationOfIfcAlignmentCurve(alignmentCurve);

					carve::geom::vector<3> targetPoint3D;
					carve::geom::vector<3> targetDirection3D;
					std::vector<carve::geom::vector<3>> curve_points;

					// Internal TODO: Implement function GetPointOnCurve, which will be able calculate trimming for each curve
					if (!trim1Vec.empty() || !trim2Vec.empty())
						throw oip::InconsistentModellingException(alignmentCurve, "Trimming not supported");

					// attach the curve points
					for (auto& it_station : stations)
					{
						// call the placement converter that handles the geometry and calculates the 3D point along a curve
						placementConverter->convertBoundedCurveDistAlongToPoint3D(alignmentCurve, it_station, true, targetPoint3D, targetDirection3D);
						curve_points.push_back(targetPoint3D);
					}
					GeomUtils::appendPointsToCurve(curve_points, targetVec);

					// add the first point to segments
					placementConverter->convertBoundedCurveDistAlongToPoint3D(alignmentCurve, stations.at(0), true, targetPoint3D, targetDirection3D);
					segmentStartPoints.push_back(targetPoint3D);
				}
#endif

				// IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates curve segments and appends them to the curve.
				* \param[in] compositeCurve			A pointer to data from \c IfcCompositeCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCompositeCurve.
				*/
				void convertIfcCompositeCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCompositeCurve>& compositeCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifccompositecurve.htm
					//	ENTITY IfcCompositeCurve
					//		SUPERTYPE OF(ONEOF
					//		(IfcCompositeCurveOnSurface))
					//	SUBTYPE OF(IfcBoundedCurve);
					//		Segments: LIST[1:? ] OF IfcCompositeCurveSegment;
					//		SelfIntersect: IfcLogical;
					//	DERIVE
					//		NSegments : IfcInteger: = SIZEOF(Segments);
					//		ClosedCurve: IfcLogical: = Segments[NSegments].Transition <> Discontinuous;
					//	WHERE
					//		CurveContinuous : ((NOT ClosedCurve) AND(SIZEOF(QUERY(Temp < *Segments | Temp.Transition = Discontinuous)) = 1)) OR((ClosedCurve)AND(SIZEOF(QUERY(Temp < *Segments | Temp.Transition = Discontinuous)) = 0));
					//		SameDim: SIZEOF(QUERY(Temp < *Segments | Temp.Dim <> Segments[1].Dim)) = 0;
					//	END_ENTITY;
					// **************************************************************************************************************************

					// Internal TODO: Implement function GetPointOnCurve, which will be able calculate trimming for each curve
					if (!trim1Vec.empty() || !trim2Vec.empty())
						throw oip::InconsistentModellingException(compositeCurve, "Trimming not supported");

					for (auto &segment: compositeCurve->Segments) {
						std::vector<carve::geom::vector<3>> segment_vec;

						convertIfcCurve(segment->ParentCurve, segment_vec, segmentStartPoints);
						if (!segment_vec.empty()) {
							GeomUtils::appendPointsToCurve(segment_vec, targetVec);
						}
					}
				}

				// IfcGradientCurve SUBTYPE of IfcBoundedCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/**********************************************************************************************/
				/*! \brief Converts base curve (inherited from IfcBoundedCurve) to 3D curve representation using gradient segments
				* \param[in] gradientCurve			A pointer to data from \c IfcGradientCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcGradientCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcGradientCurve(EXPRESSReference<typename IfcEntityTypesT::IfcGradientCurve>& gradientCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(gradientCurve);
				}
#endif 

				// IfcIndexedPolyCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] polycurve				A pointer to data from \c IfcIndexedPolyCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcIndexedPolyCurve.
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
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcindexedpolycurve.htm
					//	ENTITY IfcIndexedPolyCurve
					//		SUBTYPE OF(IfcBoundedCurve);
					//		Points: IfcCartesianPointList;
					//		Segments: OPTIONAL LIST[1:? ] OF IfcSegmentIndexSelect;
					//		SelfIntersect: OPTIONAL IfcBoolean;
					//	WHERE
					//		Consecutive : (SIZEOF(Segments) = 0) OR IfcConsecutiveSegments(Segments);
					//	END_ENTITY;
					// **************************************************************************************************************************
					// check input
					if (polycurve.expired())
						throw oip::ReferenceExpiredException(polycurve);

					// get the points
					std::vector<carve::geom::vector<3>> points = convertIfcCartesianPointList(polycurve->Points);

					// Internal TODO: Implement function GetPointOnCurve, which will be able calculate trimming for each curve
					if (!trim1Vec.empty() || !trim2Vec.empty())
						throw oip::InconsistentModellingException(polycurve, "Trimming not supported");

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

				// TYPE IfcArcIndex = LIST [3:3] OF IfcPositiveInteger;
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
				// TYPE IfcLineIndex = LIST [2:?] OF IfcPositiveInteger;
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

						double openingAngle = (theta2 - theta1);

						// correct for -2*PI <= angle <= 2*PI
						if (openingAngle > 0) {
							GeomSettings()->normalizeAngle(openingAngle, 0., M_TWOPI);
						}
						else {
							GeomSettings()->normalizeAngle(openingAngle, -M_TWOPI, 0.);
						}

						int numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(radius, abs(openingAngle));

						std::vector<carve::geom::vector<2> > circle_points;
						ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
							circle_points, radius,
							theta1, openingAngle,
							centerOfCircleX, centerOfCircleY,
							numSegments);

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

				// IfcPolyline SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Converts \c IfcPolyline to a series of points.
				* \param[in] polyline				A pointer to data from c\ IfcPolyline.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcPolyline.
				*/
				void convertIfcPolyline(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPolyline>& polyline, 
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcpolyline.htm
					//	ENTITY IfcPolyline
					//		SUBTYPE OF(IfcBoundedCurve);
					//		Points: LIST[2:? ] OF IfcCartesianPoint;
					//	WHERE
					//		SameDim : SIZEOF(QUERY(Temp < *Points | Temp.Dim <> Points[1].Dim)) = 0;
					//	END_ENTITY;
					// **************************************************************************************************************************
					if (polyline.expired())
						throw oip::ReferenceExpiredException(polyline);

					std::vector<carve::geom::vector<3>> loop = convertIfcCartesianPointVector(polyline->Points);

					// Internal TODO: Implement function GetPointOnCurve, which will be able calculate trimming for each curve
					if (!trim1Vec.empty() || !trim2Vec.empty())
						throw oip::InconsistentModellingException(polyline, "Trimming not supported");

					segmentStartPoints.push_back(loop.at(0));
					targetVec.insert(targetVec.end(), loop.begin(), loop.end());
				}

				// IfcSegmentedReferenceCurve SUBTYPE of IfcBoundedCurve(exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/**********************************************************************************************/
				/*! \brief Converts c\ IfcSegmentedReferenceCurveCalculates to curve segments and appends them to the curve. 
				* \param[in] segmentedReferenceCurve		A pointer to data from c\ IfcSegmentedReferenceCurve.
				* \param[out] targetVec						The tessellated line.
				* \param[out] segmentStartPoints			The starting points of separate segments.
				* \param[in] trim1Vec						The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec						The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement					Does the resulting geometry have the same sense agreement as the \c IfcSegmentedReferenceCurve.
				*/
				void convertIfcSegmentedReferenceCurve(EXPRESSReference<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>& segmentedReferenceCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(segmentedReferenceCurve);
				}
#endif 

				// IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates trimming points of the curve.
				* \param[in] trimmedCurve				A pointer to data from c\ IfcTrimmedCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcTrimmedCurve.
				*/
				void convertIfcTrimmedCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcTrimmedCurve>& trimmedCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifctrimmedcurve.htm
					//	ENTITY IfcTrimmedCurve
					//		SUBTYPE OF(IfcBoundedCurve);
					//			BasisCurve: IfcCurve;
					//			Trim1: SET[1:2] OF IfcTrimmingSelect;
					//			Trim2: SET[1:2] OF IfcTrimmingSelect;
					//			SenseAgreement: IfcBoolean;
					//			MasterRepresentation: IfcTrimmingPreference;
					//		WHERE
					//			Trim1ValuesConsistent : (HIINDEX(Trim1) = 1) OR(TYPEOF(Trim1[1]) < > TYPEOF(Trim1[2]));
					//			Trim2ValuesConsistent: (HIINDEX(Trim2) = 1) OR(TYPEOF(Trim2[1]) < > TYPEOF(Trim2[2]));
					//			NoTrimOfBoundedCurves: NOT('IFC4X1.IFCBOUNDEDCURVE' IN TYPEOF(BasisCurve));
					//	END_ENTITY;
					// **************************************************************************************************************************
					if (!trim1Vec.empty() || !trim2Vec.empty())
						throw oip::InconsistentModellingException(trimmedCurve, "Trimming not supported");

					std::shared_ptr<typename IfcEntityTypesT::IfcCurve> basisCurve = trimmedCurve->BasisCurve.lock();
					std::vector<carve::geom::vector<3> > basisCurvePoints;

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> curveTrim1Vec;
					curveTrim1Vec.resize(trimmedCurve->Trim1.size());
					std::transform(trimmedCurve->Trim1.begin(),
						trimmedCurve->Trim1.end(),
						curveTrim1Vec.begin(), [](auto it) { return std::make_shared<decltype(it)>(it); });

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> curveTrim2Vec;
					curveTrim2Vec.resize(trimmedCurve->Trim2.size());
					std::transform(trimmedCurve->Trim2.begin(),
						trimmedCurve->Trim2.end(),
						curveTrim2Vec.begin(), [](auto it) { return std::make_shared<decltype(it)>(it); });

					bool trimmedSenseAgreement = trimmedCurve->SenseAgreement;

					// call recursively with trimmings
					convertIfcCurve(basisCurve, basisCurvePoints, segmentStartPoints,
						curveTrim1Vec, curveTrim2Vec, trimmedSenseAgreement);
					GeomUtils::appendPointsToCurve(basisCurvePoints, targetVec);
					// end
					return;
				}

				// IfcClothoid SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcClothoid to a tesselated curve.
				* \param[in] clothoid				A pointer to data from \c IfcClothoid.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcClothoid(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(clothoid);
				}
#endif

				// IfcConic SUPTYPE of IfcCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcConic to a tesselated curve.
				* \param[in] conic					A pointer to data from \c IfcConic.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcConic.
				*/
				void convertIfcConic(
					const EXPRESSReference<typename IfcEntityTypesT::IfcConic>& conic,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcconic.htm
					//	ENTITY IfcConic
					//		ABSTRACT SUPERTYPE OF(ONEOF
					//			(IfcCircle,
					//			IfcEllipse))
					//		SUBTYPE OF(IfcCurve);
					//		Position: IfcAxis2Placement;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// IfcCircle SUBTYPE OF IfcConic
					if (conic.isOfType<typename IfcEntityTypesT::IfcCircle>()) 
					{
						return convertIfcCircle( conic.as<typename IfcEntityTypesT::IfcCircle>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					} // end if IfcCircle

					// IfcEllipse SUBTYPE OF IfcConic
					else if (conic.isOfType<typename IfcEntityTypesT::IfcEllipse>())
					{
						return convertIfcEllipse(conic.as<typename IfcEntityTypesT::IfcEllipse>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement);
					} // end if ellipse

					// the rest we do not support
					throw oip::UnhandledException(conic);
				}

				// IfcCircle SUBTYPE OF IfcConic
				/**********************************************************************************************/
				/*! \brief Calculates points of the circle curve.
				* \param[in] circle					A pointer to data from c\ IfcCircle.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCircle.
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
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifccircle.htm
					//	ENTITY IfcCircle
					//		SUBTYPE OF(IfcConic);
					//		Radius: IfcPositiveLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// determine position
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(circle->Position);

					// Get radius
					double circleRadius = circle->Radius * UnitConvert()->getLengthInMeterFactor();
					// Get center of the circle
					carve::geom::vector<3> circleCenter = conicPositionMatrix * carve::geom::VECTOR(0., 0., 0.);

					//Calculate an angle on the circle for trimming begin.
					double startAngle = 0.; 
					for (const auto& element : trim1Vec)
					{
						carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcCircle>(circle, *element);
						startAngle = getAngleOnCircle(circleCenter, circleRadius, point);
					}
					//Calculate an angle on the circle for trimming end.
					double endAngle = 0.;
					for (const auto& element : trim2Vec)
					{
						carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcCircle>(circle, *element);
						endAngle = getAngleOnCircle(circleCenter, circleRadius, point);
					}
					
					double openingAngle = calculateOpeningAngle(senseAgreement, openingAngle, endAngle);

					int numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(circleRadius, abs(openingAngle));

					const double circleCenter_x = 0.0;
					const double circleCenter_y = 0.0;
					std::vector<carve::geom::vector<2> > circle_points;
					ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
						circle_points, circleRadius,
						startAngle, openingAngle,
						circleCenter_x, circleCenter_y,
						numSegments);

					if (circle_points.size() > 0) {
						// apply position
						for (unsigned int i = 0; i < circle_points.size(); ++i) {
							carve::geom::vector<2>&  point = circle_points.at(i);
							carve::geom::vector<3> point3d(carve::geom::VECTOR(point.x, point.y, 0));
							point3d = conicPositionMatrix * point3d;
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

				// IfcEllipse SUBTYPE OF IfcConic
				/**********************************************************************************************/
				/*! \brief Calculates points of the ellipse curve.
				* \param[in] ellipse				A pointer to data from c\ IfcEllipse.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcEllipse.
				*/
				void convertIfcEllipse(
					const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcellipse.htm
					//	ENTITY IfcEllipse
					//		SUBTYPE OF(IfcConic);
					//			SemiAxis1: IfcPositiveLengthMeasure;
					//			SemiAxis2: IfcPositiveLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// determine position
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(ellipse->Position);

					if (ellipse->SemiAxis1) {
						if (ellipse->SemiAxis2) {

							double xRadius = ellipse->SemiAxis1 * UnitConvert()->getLengthInMeterFactor();
							double yRadius = ellipse->SemiAxis2 * UnitConvert()->getLengthInMeterFactor();

							double radiusMax = std::max(xRadius, yRadius);
							double radiusMin = std::min(xRadius, yRadius);
							int numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(radiusMin);
							double deltaAngle = GeomSettings()->getAngleLength(radiusMin);

							carve::geom::vector<3> ellipse_center =
								conicPositionMatrix * carve::geom::VECTOR(0, 0, 0);

							// todo: implement clipping
							if (!trim1Vec.empty() || !trim2Vec.empty()) {
								//Calculate an angle on the ellipse for trimming begin.
								double startAngle = 0.;
								for (const auto& element : trim1Vec)
								{
									carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcEllipse>(ellipse, *element);
									startAngle = getAngleOnEllipse(ellipse_center, xRadius, yRadius, point);
								}
								//Calculate an angle on the ellipse for trimming end.
								double endAngle = 0.;
								for (const auto& element : trim2Vec)
								{
									carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcEllipse>(ellipse, *element);
									endAngle = getAngleOnEllipse(ellipse_center, xRadius, yRadius, point);
								}
								// Calculate an opening angle
								double openingAngle = calculateOpeningAngle(senseAgreement, startAngle, endAngle);
								
								numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(radiusMin, abs(openingAngle));
								deltaAngle = GeomSettings()->getAngleLength(radiusMin, abs(openingAngle));
							}

							std::vector<carve::geom::vector<3> > ellipsePoints;
							double angle = 0.0;
							for (int i = 0; i < numSegments; ++i) {
								ellipsePoints.push_back(carve::geom::vector<3>(
									carve::geom::VECTOR(
										xRadius * cos(angle),
										yRadius * sin(angle),
										0)));
								angle += deltaAngle;
							}

							// apply position
							for (unsigned int i = 0; i < ellipsePoints.size(); ++i) {
								carve::geom::vector<3>& point = ellipsePoints.at(i);
								point = conicPositionMatrix * point;
							}
							GeomUtils::appendPointsToCurve(ellipsePoints, targetVec);
							segmentStartPoints.push_back(ellipsePoints.at(0));
						}
					}
				}

				// IfcLine SUPTYPE of IfcCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcLine to a tesselated curve.
				* \param[in] line					A pointer to data from \c IfcLine.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcLine.
				*/
				void convertIfcLine(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLine>& line,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcline.htm
					//	ENTITY IfcLine
					//		SUBTYPE OF(IfcCurve);
					//			Pnt: IfcCartesianPoint;
					//			Dir: IfcVector;
					//		WHERE
					//			SameDim : Dir.Dim = Pnt.Dim;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// Part 1: Get information from IfcLine. 
					// Get IfcLine attributes: line point and line direction. 
					carve::geom::vector<3> line_origin = placementConverter->convertIfcCartesianPoint(line->Pnt);

					EXPRESSReference<typename IfcEntityTypesT::IfcVector> line_vec = line->Dir;
					// Get IfcVector attributes: line orientation and magnitude. 
					// Orientation type IfcDirection
					carve::geom::vector<3> line_direction = placementConverter->convertIfcDirection(line_vec->Orientation);

					// Magnitude type IfcLengthMeasure
					double line_magnitude = line_vec->Magnitude * UnitConvert()->getLengthInMeterFactor();

					// Part 2: Trimming
					// Internal TODO: Implement function GetPointOnCurve, which will be able calculate trimming for each curve
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

				// IfcOffsetCurve SUPTYPE of IfcCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcOffsetCurve to a tesselated curve.
				* \param[in] offsetCurve			A pointer to data from \c IfcOffsetCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcOffsetCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcOffsetCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurve>& offsetCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcoffsetcurve.htm
					//	ENTITY IfcOffsetCurve
					//		ABSTRACT SUPERTYPE OF(ONEOF
					//			(IfcOffsetCurve2D,
					//			IfcOffsetCurve3D,
					//			IfcOffsetCurveByDistances))
					//		SUBTYPE OF(IfcCurve);
					//			BasisCurve: IfcCurve;
					//	END_ENTITY;
					// **************************************************************************************************************************
					throw oip::UnhandledException(offsetCurve);
					/*
					// IfcOffsetCurve2D SUBTYPE OF IfcOffsetCurve
					std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve2D> offsetCurve2D =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve2D>(offsetCurve);
					if (offsetCurve2D) {
#ifdef _DEBUG
						std::cout << "Warning\t| IfcOffsetCurve2D not implemented" << std::endl;
#endif
						return;
					}

					// IfcOffsetCurve3D SUBTYPE OF IfcOffsetCurve
					std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve3D> offsetCurve3D =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve3D>(offsetCurve);
					if (offsetCurve3D) {
#ifdef _DEBUG
						std::cout << "Warning\t| IfcOffsetCurve3D not implemented" << std::endl;
#endif
						return;
					}

					// IfcOffsetCurveByDistances SUBTYPE OF IfcOffsetCurve
					std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurveByDistances> offsetCurveDist =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurveByDistances>(offsetCurve);
					if (offsetCurveDist) {
#ifdef _DEBUG
						std::cout << "Warning\t| IfcOffsetCurveByDistances not implemented" << std::endl;
#endif
						return;
					}
					*/
				}

				// IfcPcurve SUPTYPE of IfcCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcPcurve to a tesselated curve.
				* \param[in] pCurve					A pointer to data from \c IfcPcurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcPcurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcPcurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPcurve>& pCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(pCurve);
				}

				// IfcSeriesParameterCurve SUBTYPE of IfcCurve (exists starting IFC4x3_RC2)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcSeriesParameterCurve to a tesselated curve.
				* \param[in] boundedCurve			A pointer to data from \c IfcSeriesParameterCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcSeriesParameterCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcSeriesParameterCurve>& seriesParameterCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					throw oip::UnhandledException(pcurve);
				}
				
#endif

				// IfcSurfaceCurve SUPTYPE of IfcCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcSurfaceCurve to a tesselated curve.
				* \param[in] surfaceCurve			A pointer to data from \c IfcSurfaceCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcSurfaceCurve.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcSurfaceCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcSurfaceCurve>& surfaceCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement
				) const throw(...)
				{
					//	ABSTRACT SUPERTYPE OF IfcIntersectionCurve, IfcSeamCurve																//

					throw oip::UnhandledException(surfaceCurve);

					/*
					// IfcIntersectionCurve SUBTYPE OF IfcSurfaceCurve
					std::shared_ptr<typename IfcEntityTypesT::IfcIntersectionCurve> intersectionCurve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcIntersectionCurve>(ifcCurve);
					if (intersectionCurve)
					{
						// TO DO: implement
					}

					// IfcSeamCurve SUBTYPE OF IfcSurfaceCurve
					std::shared_ptr<typename IfcEntityTypesT::IfcSeamCurve> seamCurve =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSeamCurve>(ifcCurve);
					if (seamCurve)
					{
						// TO DO: implement
					}
					*/
				}

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/*! \brief Converts \c IfcSegment and its subtypes to a series of points.
				* \param[in] segment				The \c IfcSegment to be converted.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcSegment(const EXPRESSReference<typename IfcEntityTypesT::IfcSegment>& segment,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const throw(...)
				{
					throw oip::UnhandledException(segment);
					/*
					if (segment.isOfType<typename IfcEntityTypesT::IfcCurveSegment>())
					{
						return convertIfcCurveSegment(segment.as<typename IfcEntityTypesT::IfcCurveSegment>(), targetVec, segmentStartPoints);
					}
					if  (segment.isOfType<typename IfcEntityTypesT::IfcCompositeCurveSegment>())
					{
						return IfcCompositeCurveSegment(segment.as<typename IfcEntityTypesT::IfcCompositeCurveSegment>(), targetVec, segmentStartPoints);
					}
					*/
				}
#endif

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC2)
				/*! \brief Converts \c IfcCurveSegment to a series of points and appends them to the curve.
				* \param[in] curveSegment			The \c IfcCurveSegment to be converted.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcCurveSegment(const EXPRESSReference<typename IfcEntityTypesT::IfcCurveSegment>& curveSegment,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const throw(...)
				{
					throw oip::UnhandledException(curveSegment);
				}
#endif

				/*! \brief Converts \c IfcLoop and its subtypes to a series of points.
				* \param[in] ifcloop				The \c IfcLoop to be converted.
				* \param[out] loop					The series of points.
				*/
				void convertIfcLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcLoop>& ifcloop,
					std::vector<carve::geom::vector<3>>& loop
				) const throw(...)
				{
					if (ifcloop.isOfType<typename IfcEntityTypesT::IfcPolyLoop>()) 
					{	
						return convertIfcPolyLoop(ifcloop.as<typename IfcEntityTypesT::IfcPolyLoop>(), loop);
					} // end if polyloop

					else if (ifcloop.isOfType<typename IfcEntityTypesT::IfcEdgeLoop>())
					{
						return convertIfcEdgeLoop(ifcloop.as<typename IfcEntityTypesT::IfcEdgeLoop>(), loop);
					} // end if edge loop

					else {
						throw oip::UnhandledException(ifcloop);
					}
					
				} // end convertIfcLoop

				/*! \brief Converts \c IfcPolyLoop to a series of points.
				* \param[in] polyLoop				The \c IfcPolyLoop to be converted.
				* \param[out] loop					The series of points.
				*/
				void convertIfcPolyLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcPolyLoop>& polyLoop,
					std::vector<carve::geom::vector<3>>& loop) const throw(...)
				{
					convertIfcCartesianPointVectorSkipDuplicates(polyLoop->Polygon, loop);
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
				*
				* \note The function disregards topological relationships.
				* \note The function is not fully implemented.
				*
				* \internal TODO.
				*/
				void convertIfcEdgeLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcEdgeLoop>& edgeLoop,
					std::vector<carve::geom::vector<3>>& loop) const throw(...)
				{
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

				/*! \brief Converts \c IfcEdge and adds it to the plolyline. 
				* \param[in] ifcEdge				The \c IfcEdge to be converted.
				* \param[in] objectPlacement		Coordinates of the object.
				* \param[out] polyline_data			Infromation of the polyline. 
				*/
				void convertIfcEdge(
					const EXPRESSReference<typename IfcEntityTypesT::IfcEdge>& ifcEdge,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<carve::input::PolylineSetData> polyline_data
				) const throw(...)
				{
					polyline_data->beginPolyline();

					auto& vertex_start = ifcEdge->EdgeStart;
					if (vertex_start.isOfType<typename IfcEntityTypesT::IfcVertexPoint>()) {
						auto vertex_start_point = vertex_start.as<typename IfcEntityTypesT::IfcVertexPoint>();
						carve::geom::vector<3> point = placementConverter->convertIfcPoint(vertex_start_point->VertexGeometry);

						polyline_data->addVertex(objectPlacement * point);
						polyline_data->addPolylineIndex(0);
					}

					auto& vertex_end = ifcEdge->EdgeEnd;
					if (vertex_end.isOfType<typename IfcEntityTypesT::IfcVertexPoint>()) {
						auto vertex_end_point = vertex_end.as<typename IfcEntityTypesT::IfcVertexPoint>();
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

				/*! \brief Converts \c IfcCartesianPointList to a series of points.
				* \param[in] pointlist			The \c IfcCartesianPointList to be converted.
				* \return						The series of points.
				*/
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

				/*! \brief Gets stations for \c IfcAlignmentCurve at which a point of the tesselation has to be calcuated. 
				* \param[in] alignmentCurve			The \c IfcAlignmentCurve to be converted.
				* \retrun							The series of stations at which a point of the tesselation has to be calcuated.
				*/
				std::vector<double> getStationsForTessellationOfIfcAlignmentCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignmentCurve
				) const throw(...)
				{
					// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve
					// Stations at which a point of the tesselation has to be calcuated
					std::vector<double> stations;

					// **************************************************************************************************************************** //
					// Step 1: Get segment information from horizontal and vertical alignments.
					std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignmentCurve->Horizontal.lock();

					if (!horizontal)
						throw oip::InconsistentModellingException(alignmentCurve, "No IfcAlignment2DHorizontal");

					// StartDistAlong type IfcLengthMeasure [0:1]
					double horStartDistAlong = horizontal->StartDistAlong.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();

					// Segments type IfcAlignment2DHorizontalSegment L[1:?]
					if (horizontal->Segments.empty())
						throw oip::InconsistentModellingException(horizontal, "No segments");

					// is it going to be only a horizontal alignment?
					bool bOnlyHorizontal = false;
					//std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVertical>
					auto vertical = alignmentCurve->Vertical;
					if (!vertical) {
						// there is no vertical alignment
						BLUE_LOG(info) << "No IfcAlignment2DVertical in " << alignmentCurve->getErrorLog();
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
				/**********************************************************************************************/
				/*! \brief Calculates an angle of the point on the circle.
				* \param[in] circleCenter				Location of the center of the circle.
				* \param[in] circleRadius				Radius of the circle.
				* \param[in] trimPoint					Location of the point on the circle.
				* \return								An angle of the point on the circle.
				*/
				double getAngleOnCircle(const carve::geom::vector<3>& circleCenter,
					double circleRadius,
					const carve::geom::vector<3>& trimPoint
				) const throw(...)
				{
					carve::geom::vector<3> centerToTrimPoint = trimPoint - circleCenter;
					if (abs(centerToTrimPoint.length() - circleRadius) < 0.0001) {
						centerToTrimPoint.normalize();
						double cosAngle = carve::geom::dot(centerToTrimPoint, carve::geom::vector<3>(carve::geom::VECTOR(1., 0., 0.)));

						if (abs(cosAngle) < 0.0001) {
							if (centerToTrimPoint.y > 0.) {
								return M_PI_2;
							}
							else if (centerToTrimPoint.y < 0.) {
								return M_PI * 1.5;
							}
						}
						else {
							if (centerToTrimPoint.y > 0.) {
								return acos(cosAngle);
							}
							else if (centerToTrimPoint.y < 0.) {
								return 2.0*M_PI - acos(cosAngle);
							}
							else {
								if (centerToTrimPoint.x > 0.) {
									return 0.;
								}
								else {
									return M_PI;
								}
							}
						}
					}
					else {
						throw oip::InconsistentModellingException("The point is not located on the circle");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates an angle of the point on the ellipse.
				* \param[in] ellipseCenter				Location of the center of the ellipse.
				* \param[in] ellipseRadiusX				Radius of the ellipse in the X-axis direction.
				* \param[in] ellipseRadiusY				Radius of the ellipse in the Y-axis direction.
				* \param[in] trimPoint					Location of the point on the ellipse.
				* \return								An angle of the point on the ellipse.
				*/
				double getAngleOnEllipse(const carve::geom::vector<3>& ellipseCenter,
					double ellipseRadiusX,
					double ellipseRadiusY,
					const carve::geom::vector<3>& trimPoint
				) const throw(...)
				{
					carve::geom::vector<3> centerToTrimPoint = trimPoint - ellipseCenter;
					
					if ((centerToTrimPoint.x / ellipseRadiusX) <= 1. && (centerToTrimPoint.y / ellipseRadiusY) <= 1.) {
						double cosAngle = centerToTrimPoint.x / ellipseRadiusX;

						if (abs(cosAngle) < 0.0001) {
							if (centerToTrimPoint.y > 0.) {
								return M_PI_2;
							}
							else if (centerToTrimPoint.y < 0.) {
								return 3 * M_PI_2;
							}
						}
						else {
							if (centerToTrimPoint.y > 0.) {
								return acos(cosAngle);
							}
							else if (centerToTrimPoint.y < 0.) {
								return 2.0 * M_PI - acos(cosAngle);
							}
							else {
								if (centerToTrimPoint.x > 0.) {
									return 0.;
								}
								else {
									return M_PI;
								}
							}
						}
					}
					else {
						throw oip::InconsistentModellingException("The point is located outside the ellipse");
					}
				}

				double calculateOpeningAngle(const  bool senseAgreement, const double startAngle, const double endAngle)const throw(...)
				{
					double openingAngle = 0.;
					if (senseAgreement) {
						if (startAngle < endAngle) {
							openingAngle = endAngle - startAngle;
						}
						else {
							// circle passes 0 angle
							openingAngle = endAngle - startAngle + 2.0*M_PI;
						}
					}
					else {
						if (startAngle > endAngle) {
							openingAngle = endAngle - startAngle;
						}
						else {
							// circle passes 0 angle
							openingAngle = endAngle - startAngle - 2.0*M_PI;
						}
					}

					// correct for -2*PI <= angle <= 2*PI
					if (openingAngle > 0) {
						GeomSettings()->normalizeAngle(openingAngle, 0., M_TWOPI);
					}
					else {
						GeomSettings()->normalizeAngle(openingAngle, -M_TWOPI, 0.);
					}
					return openingAngle;
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve.
				* \param[in] curve					A pointer to data from a curve.
				* \param[in] trimming				A pointer to data form \c IfcTrimmingSelect.
				* \return							The location of the trimming point.
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcTrimmingSelect & trimming) const throw(...)
				{
					switch (trimming.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcCartesianPoint. 
						return getPointOnCurve<typename TCurve>(curve, trimming.get<0>());
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getPointOnCurve(curve, trimming.get<1>());
					}
					default:
						throw oip::InconsistentGeometryException(curve, "TrimmingSelect is wrong!");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcCartesianPoint. .
				* \param[in] curve					A pointer to data from a curve.
				* \param[in] cartesianPoint			A pointer to data form \c IfcCartesianPoint.
				* \return							The location of the trimming point.
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve>& curve,
					const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>& cartesianPoint) const throw(...)
				{
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(curve->Position);
					carve::geom::vector<3> conicCenter = conicPositionMatrix * carve::geom::VECTOR(0., 0., 0.);

					return conicCenter + placementConverter->convertIfcCartesianPoint(cartesianPoint);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \param[in] circle					A pointer to data from \c IfcCircle.
				* \param[in] parameter				A pointer to data form \c IfcParameterValue.
				* \return							The location of the trimming point.
				*/
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const throw(...)
				{
					double angle = parameter * UnitConvert()->getAngleInRadianFactor();
					// determine position
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(circle->Position);

					// Get radius
					double circleRadius = circle->Radius * UnitConvert()->getLengthInMeterFactor();

					carve::geom::vector<3> circleCenter =
						conicPositionMatrix * carve::geom::VECTOR(0., 0., 0.);
					return circleCenter + carve::geom::VECTOR(circleRadius * cos(angle), circleRadius * sin(angle), 0.);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \param[in] ellipse				A pointer to data from \c IfcEllipse.
				* \param[in] parameter				A pointer to data form \c IfcParameterValue.
				* \return							The location of the trimming point.
				*/
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const throw(...)
				{
					double angle = parameter * UnitConvert()->getAngleInRadianFactor();
					// determine position
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(ellipse->Position);

					// Get radius
					double xRadius = ellipse->SemiAxis1 * UnitConvert()->getLengthInMeterFactor();
					double yRadius = ellipse->SemiAxis2 * UnitConvert()->getLengthInMeterFactor();

					carve::geom::vector<3> ellipse_center =
						conicPositionMatrix * carve::geom::VECTOR(0., 0., 0.);

					return ellipse_center + carve::geom::VECTOR(xRadius * cos(angle), yRadius * sin(angle), 0.);
				}

			protected:

				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;

			}; // end class
		}; // end namespace IfcGeometryConverter
	}; // end namespace Core
}; // end namespace OIP


#endif
