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
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "CarveHeaders.h"

#include "ConverterBase.h"

#include "GeomUtils.h"
#include "SpiralUtils.h"
#include "PlacementConverter.h"
#include "ProfileConverter.h"
#include "SplineConverter.h"

#include "BlueFramework/Core/Diagnostics/log.h"


namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{

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
					placementConverter.reset();
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
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> loops;
					std::vector<carve::geom::vector<3>> segment_start_points;
					convertIfcCurve(ifcCurve, loops, segment_start_points);

					std::shared_ptr<carve::input::PolylineSetData> polylineData = std::make_shared<
						carve::input::PolylineSetData>();
					polylineData->beginPolyline();
					for (int i = 0; i < loops.size(); ++i) 
					{
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
				) const noexcept(false)
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim2Vec;
					typename IfcEntityTypesT::IfcTrimmingPreference trimmingPreference;
					convertIfcCurve(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true, trimmingPreference);
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
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
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
					// IfcBlossCurve SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
//#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
//					if (ifcCurve.template as<typename IfcEntityTypesT::IfcBlossCurve>())
//					{
//						return convertIfcBlossCurve(ifcCurve.as<typename IfcEntityTypesT::IfcBlossCurve>(),
//							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
//					}
//#endif

					// IfcBoundedCurve SUBTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcBoundedCurve>())
					{
						return convertIfcBoundedCurve(ifcCurve.template as<typename IfcEntityTypesT::IfcBoundedCurve>(),
							targetVec, segmentStartPoints);
					}

					// IfcClothoid SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcClothoid>())
					{
						return convertIfcClothoid(ifcCurve.template as<typename IfcEntityTypesT::IfcClothoid>(), 
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					}
#endif
					
					// IfcConic SUPTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcConic>())
					{
						return convertIfcConic(ifcCurve.template as<typename IfcEntityTypesT::IfcConic>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					}

					// IfcLine SUPTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcLine>())
					{
						return convertIfcLine(ifcCurve.template as<typename IfcEntityTypesT::IfcLine>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					}

					// IfcOffsetCurve SUPTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcOffsetCurve>())
					{
						return convertIfcOffsetCurve(ifcCurve.template as<typename IfcEntityTypesT::IfcOffsetCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					}

					// IfcPcurve SUPTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcPcurve>())
					{
						return convertIfcPcurve(ifcCurve.template as<typename IfcEntityTypesT::IfcPcurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					}

//					// IfcSeriesParameterCurve SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
//#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
//					else if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcSeriesParameterCurve>())
//					{
//						return convertIfcSeriesParameterCurve(ifcCurve.template as<typename IfcEntityTypesT::IfcSeriesParameterCurve>(),
//							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
//					}
//#endif

					// IfcSurfaceCurve SUPTYPE of IfcCurve
					if (ifcCurve.template isOfType<typename IfcEntityTypesT::IfcSurfaceCurve>())
					{
						return convertIfcSurfaceCurve(ifcCurve.template as<typename IfcEntityTypesT::IfcSurfaceCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
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
				) const noexcept(false)
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim1Vec;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim2Vec;
					typename IfcEntityTypesT::IfcTrimmingPreference trimmingPreference;
					convertIfcCurve2D(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true, trimmingPreference);
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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> target_vec_3d;
					std::vector<carve::geom::vector<3>> segment_start_points_3d;

					convertIfcCurve(ifcCurve, target_vec_3d, segment_start_points_3d,
						trim1Vec, trim2Vec, senseAgreement, trimmingPreference);

					for (int i = 0; i < target_vec_3d.size(); ++i) 
					{
						carve::geom::vector<3>& point_3d = target_vec_3d[i];
						targetVec.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
					for (int i = 0; i < segment_start_points_3d.size(); ++i) 
					{
						carve::geom::vector<3>& point_3d = segment_start_points_3d[i];
						segmentStartPoints.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
					}
				} //end convertIfcCurve2D

				// IfcBlossCurve SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
//#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
//				/**********************************************************************************************/
//				/*! \brief Converts an \c IfcBlossCurve to a tesselated curve.
//				* \param[in] blossCurve				A pointer to data from \c IfcBlossCurve.
//				* \param[out] targetVec				The tessellated line.
//				* \param[out] segmentStartPoints	The starting points of separate segments.
//				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
//				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
//				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcBlossCurve.
//				*
//				* \note The function is not implemented.
//				* \internal TODO.
//				*/
//				void convertIfcBlossCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcBlossCurve>& blossCurve,
//					std::vector<carve::geom::vector<3>>& targetVec,
//					std::vector<carve::geom::vector<3>>& segmentStartPoints,
//					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
//					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
//					const bool senseAgreement,
//					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
//				) const noexcept(false)
//				{
//					throw oip::UnhandledException(blossCurve);
//				}
//#endif

				/**********************************************************************************************/
				/*! \brief Converts an \c IfcBoundedCurve to a tesselated curve.
				* \param[in] boundedCurve			A pointer to data from \c IfcBoundedCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				// IfcBoundedCurve SUBTYPE of IfcCurve
				void convertIfcBoundedCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve>& boundedCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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
					// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve (Deprecated starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined( OIP_MODULE_EARLYBINDING_IFC4X2) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
					if (boundedCurve.isOfType<typename IfcEntityTypesT::IfcAlignmentCurve>())
					{
						return convertIfcAlignmentCurve(boundedCurve.as<typename IfcEntityTypesT::IfcAlignmentCurve>(),
							targetVec, segmentStartPoints);
					} // end if IfcAlignmentCurve
#endif

					// IfcBSplineCurve SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcBSplineCurve>()) 
					{
						EXPRESSReference<typename IfcEntityTypesT::IfcBSplineCurve> bsplineCurve = boundedCurve.template
							as<typename IfcEntityTypesT::IfcBSplineCurve>();
						
						SplineConverterT<IfcEntityTypesT> splineConverter(
							this->GeomSettings(), this->UnitConvert(), placementConverter);
						// splineConverter.convertIfcBSplineCurve can handle IfcBSplineCurveWithKnots and IfcRationalBsplineWithKnots, 
						// both are subtypes of IfcBSplineCurve
						splineConverter.convertIfcBSplineCurve(bsplineCurve, targetVec);
						return;
					} // end if IfcBSplineCurve

					// IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcCompositeCurve>())
					{
						return convertIfcCompositeCurve(boundedCurve.template as<typename IfcEntityTypesT::IfcCompositeCurve>(),
							targetVec, segmentStartPoints);
					} // end if IfcCompositeCurve

					// IfcGradientCurve SUBTYPE of IfcBoundedCurve (exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcGradientCurve>())
					{
						return convertIfcGradientCurve(boundedCurve.template as<typename IfcEntityTypesT::IfcGradientCurve>(),
							targetVec, segmentStartPoints);
					} // end if IfcGradientCurve
#endif 

					// IfcIndexedPolyCurve SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcIndexedPolyCurve>())
					{
						return convertIfcIndexedPolyCurve(
							boundedCurve.template as<typename IfcEntityTypesT::IfcIndexedPolyCurve>(),
							targetVec, segmentStartPoints);
					} // end if IfcIndexedPolyCurve

					// IfcPolyline SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcPolyline>()) 
					{
						if (boundedCurve.template as<typename IfcEntityTypesT::IfcPolyline>()->Points.empty()) 
							throw oip::InconsistentModellingException(boundedCurve, "Points are empty!");

						return convertIfcPolyline(boundedCurve.template as<typename IfcEntityTypesT::IfcPolyline>(),
							targetVec, segmentStartPoints);
					} // end if IfcPolyline

					// IfcSegmentedReferenceCurve SUBTYPE OF IfcBoundedCurve (exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
					else if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>())
					{
						return convertIfcSegmentedReferenceCurve(
							boundedCurve.template as<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>(),
							targetVec, segmentStartPoints);
					} // end if IfcSegmentedReferenceCurve
#endif 

					// IfcTrimmedCurve SUBTYPE OF IfcBoundedCurve
					if (boundedCurve.template isOfType<typename IfcEntityTypesT::IfcTrimmedCurve>()) 
					{
						return convertIfcTrimmedCurve(boundedCurve.template as<typename IfcEntityTypesT::IfcTrimmedCurve>(), 
							targetVec, segmentStartPoints);
					} // end if IfcTrimmedCurve
					
					// the rest we do not support
					throw oip::UnhandledException( boundedCurve );
				}

				// IfcAlignmentCurve SUBTYPE OF IfcBoundedCurve (Deprecated starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined( OIP_MODULE_EARLYBINDING_IFC4X2) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
				/**********************************************************************************************/
				/*! \brief Calculates the 3D point along a curve.
				* \param[in] alignmentCurve			A pointer to data from c\ IfcAlignmentCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcAlignmentCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignmentCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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

					// attach the curve points
					for (auto& it_station : stations)
					{
						// call the placement converter that handles the geometry and calculates the 3D point along a curve
						if( placementConverter->convertBoundedCurveDistAlongToPoint3D(
							alignmentCurve.template as<typename IfcEntityTypesT::IfcBoundedCurve>(), 
							it_station, true, targetPoint3D, targetDirection3D)	)
							curve_points.push_back(targetPoint3D);
					}
					GeomUtils::appendPointsToCurve(curve_points, targetVec);

					// add the first point to segments
					if(	placementConverter->convertBoundedCurveDistAlongToPoint3D(
						alignmentCurve.template as<typename IfcEntityTypesT::IfcBoundedCurve>(),
						stations.at(0), true, targetPoint3D, targetDirection3D)	)
						segmentStartPoints.push_back(targetPoint3D);
				}
#endif

				// IfcCompositeCurve SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Calculates curve segments and appends them to the curve.
				* \param[in] compositeCurve			A pointer to data from \c IfcCompositeCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcCompositeCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcCompositeCurve>& compositeCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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
					for (auto &segment : compositeCurve->Segments) 
					{
						std::vector<carve::geom::vector<3>> segment_vec;

#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
						convertIfcCurve(segment->ParentCurve, segment_vec, segmentStartPoints);
#else
						convertIfcSegment(segment, segment_vec, segmentStartPoints);
#endif
						if (!segment_vec.empty()) {
							GeomUtils::appendPointsToCurve(segment_vec, targetVec);
						}
					}
				}

				// IfcGradientCurve SUBTYPE of IfcBoundedCurve (exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/**********************************************************************************************/
				/*! \brief Converts base curve (inherited from IfcBoundedCurve) to 3D curve representation using gradient segments
				* \param[in] gradientCurve			A pointer to data from \c IfcGradientCurve.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcGradientCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcGradientCurve>& gradientCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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
				*/
				void convertIfcIndexedPolyCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcIndexedPolyCurve>& polycurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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

					// are segments there?
					if (polycurve->Segments)
					{
						try
						{
							std::vector<carve::geom::vector<3>> loop;
							for (const auto& seg : polycurve->Segments.get())
							{
								std::vector<carve::geom::vector<3>> loop_intern = convertIfcSegmentIndexSelect(
									seg, points);
								// skips same points
								GeomUtils::appendPointsToCurve(loop_intern, loop);
							}

							// add the calculated points to the return values
							GeomUtils::appendPointsToCurve(loop, targetVec);
							segmentStartPoints.push_back(loop[0]);
						}
						catch (const oip::InconsistentModellingException& ex) 
						{
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
				* \return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcSegmentIndexSelect(
					const typename IfcEntityTypesT::IfcSegmentIndexSelect & segmentIndexSelect,
					const std::vector<carve::geom::vector<3>>& points
				)const noexcept(false)
				{
					switch (segmentIndexSelect.which())
					{
					case 0:
						{
							// TYPE IfcArcIndex = LIST [3:3] OF IfcPositiveInteger;
							return convertIfcArcIndex(segmentIndexSelect.template get<0>(), points);
						}
					case 1:
						{
							// TYPE IfcLineIndex = LIST [2:?] OF IfcPositiveInteger;
							return convertIfcLineIndex(segmentIndexSelect.template get<1>(), points);
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
				* \return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcLineIndex(
					const typename IfcEntityTypesT::IfcLineIndex &lineSegment,
					const std::vector<carve::geom::vector<3>>& points
				) const noexcept(false)
				{
					if (lineSegment.size() < 2)
						throw oip::InconsistentModellingException(
							"The number of indices for one of IfcLineIndex is less than 2!");

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
				* \return							The series of points of the curve.
				*/
				std::vector<carve::geom::vector<3>> convertIfcArcIndex(
					const typename IfcEntityTypesT::IfcArcIndex &arcSegment,
					const std::vector<carve::geom::vector<3>>& points
				) const noexcept(false)
				{
					if (arcSegment.size() != 3)
						throw oip::InconsistentModellingException(
							"The number of indices for one of IfcArcIndex is not 3!");

					carve::geom::vector<3> arcStart = points[arcSegment[0] - 1];
					carve::geom::vector<3> arcMid = points[arcSegment[1] - 1];
					carve::geom::vector<3> arcEnd = points[arcSegment[2] - 1];

					//Converting a 3D to a 2D problem to then find the circle from three points on the plane.
					// see https://math.stackexchange.com/questions/1379217/3-points-in-3d-space-to-find-the-center-of-an-arc-or-circle

					//Start by finding the normal vector to the plane defined by the three points
					//n=unitvector(A×B+B×C+C×A)
					carve::geom::vector<3> normalVector = cross(arcStart, arcMid) + cross(arcMid, arcEnd) + cross(arcEnd, arcStart);
					normalVector.normalize();
					//u=(C−A)×n
					carve::geom::vector<3> firstOrthogonalDirection = cross(arcEnd - arcStart, normalVector);
					firstOrthogonalDirection.normalize();
					//v=n×u
					carve::geom::vector<3> secondOrthogonalDirection = cross(normalVector, firstOrthogonalDirection);
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

					if (xDeltaA != 0. && xDeltaB != 0.) 
					{
						double aSlope = yDeltaA / xDeltaA;
						double bSlope = yDeltaB / xDeltaB;

						double centerOfCircleX = (aSlope * bSlope * (arcStart2D.y - arcEnd2D.y) + bSlope * (arcStart2D.x + arcMid2D.x)
							- aSlope * (arcMid2D.x + arcEnd2D.x)) / (2. * (bSlope - aSlope));

						double centerOfCircleY = -(centerOfCircleX - (arcStart2D.x + arcMid2D.x) * 0.5) / aSlope + (
							arcStart2D.y + arcMid2D.y) * 0.5;

						carve::geom::vector<2> radiusVector = carve::geom::VECTOR(
							arcStart2D.x - centerOfCircleX, arcStart2D.y - centerOfCircleY);
						double radius = radiusVector.length();

						double theta1 = std::atan2(arcStart2D.y - centerOfCircleY, arcStart2D.x - centerOfCircleX);
						double theta2 = std::atan2(arcEnd2D.y - centerOfCircleY, arcEnd2D.x - centerOfCircleX);

						double openingAngle = (theta2 - theta1);

						// correct for -2*PI <= angle <= 2*PI
						if (openingAngle > 0) {
							this->GeomSettings()->normalizeAngle(openingAngle, 0., M_TWOPI);
						}
						else {
							this->GeomSettings()->normalizeAngle(openingAngle, -M_TWOPI, 0.);
						}

						int numSegments = this->GeomSettings()->getNumberOfSegmentsForTessellation(radius, abs(openingAngle));

						std::vector<carve::geom::vector<2>> circle_points;
						ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
							circle_points, radius,
							theta1, openingAngle,
							centerOfCircleX, centerOfCircleY,
							numSegments);

						//std::vector<carve::geom::vector<3>> arcPoints;
						std::vector<carve::geom::vector<3>> loop_intern;
						loop_intern.push_back(arcStart);
						for (int i = 1; i < circle_points.size(); i++) 
						{

							loop_intern.push_back(carve::geom::VECTOR(
								normalVector.x * distance + firstOrthogonalDirection.x * circle_points[i].x + secondOrthogonalDirection.x * circle_points[i].y,
								normalVector.y * distance + firstOrthogonalDirection.y * circle_points[i].x + secondOrthogonalDirection.y * circle_points[i].y,
								normalVector.z * distance + firstOrthogonalDirection.z * circle_points[i].x + secondOrthogonalDirection.z * circle_points[i].y));
						}
						return loop_intern;
					}
					else 
					{
						throw oip::InconsistentGeometryException("The distance between points cannot be 0.");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				* \param[in] conversionMatrix		A pointer to data from IfcIndexedPolyCurve.
				* \param[in] vector3D				Vector in 3D
				* return							Converted vector in 2D.
				*/
				carve::geom::vector<2> convert3Dto2D(const carve::math::Matrix&  conversionMatrix,
					const carve::geom::vector<3>& vector3D
				) const noexcept(false)
				{
					return carve::geom::VECTOR((conversionMatrix._11 * vector3D.x + conversionMatrix._12 * vector3D.y + conversionMatrix._13 * vector3D.z),
						(conversionMatrix._21 * vector3D.x + conversionMatrix._22 * vector3D.y + conversionMatrix._23 * vector3D.z));
				}

				// IfcPolyline SUBTYPE OF IfcBoundedCurve
				/**********************************************************************************************/
				/*! \brief Converts \c IfcPolyline to a series of points.
				* \param[in] polyline				A pointer to data from c\ IfcPolyline.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcPolyline(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPolyline>& polyline,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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

					segmentStartPoints.push_back(loop.at(0));
					GeomUtils::appendPointsToCurve(loop, targetVec);
				}

				// IfcSegmentedReferenceCurve SUBTYPE of IfcBoundedCurve(exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/**********************************************************************************************/
				/*! \brief Converts c\ IfcSegmentedReferenceCurveCalculates to curve segments and appends them to the curve. 
				* \param[in] segmentedReferenceCurve		A pointer to data from c\ IfcSegmentedReferenceCurve.
				* \param[out] targetVec						The tessellated line.
				* \param[out] segmentStartPoints			The starting points of separate segments.
				*/
				void convertIfcSegmentedReferenceCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcSegmentedReferenceCurve>& segmentedReferenceCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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
				*/
				void convertIfcTrimmedCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcTrimmedCurve>& trimmedCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
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
					EXPRESSReference<typename IfcEntityTypesT::IfcCurve> basisCurve = trimmedCurve->BasisCurve;

					if (basisCurve.template isOfType<typename IfcEntityTypesT::IfcBoundedCurve>())
						throw oip::InconsistentModellingException(trimmedCurve, "Trimmed curve can not have bouded curve as basis curve");
					
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
					typename IfcEntityTypesT::IfcTrimmingPreference trimmingPreference = trimmedCurve->MasterRepresentation;

					// call recursively with trimmings
					convertIfcCurve(basisCurve, basisCurvePoints, segmentStartPoints,
						curveTrim1Vec, curveTrim2Vec, trimmedSenseAgreement, trimmingPreference); 
					GeomUtils::appendPointsToCurve(basisCurvePoints, targetVec);
				}

				// IfcSpiral SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcSpiral to a tesselated curve.
				* \param[in] spiral					A pointer to data from \c Spiral.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcSpiral.
				*/
				void convertIfcSpiral(
					const EXPRESSReference<typename IfcEntityTypesT::IfcSpiral>& spiral,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	 https://
					//	ENTITY IfcSpiral
					//		ABSTRACT SUPERTYPE OF(ONEOF
					//			(IfcBlossCurve,
					//          IfcClothoid
					//          IfcCosine
					//          IfcHelmertCurve
					//			IfcSine))
					//		SUBTYPE OF(IfcCurve);
					//		Position: OPTIONAL IfcAxis2Placement;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// IfcBlossCurve SUBTYPE OF IfcSpiral
					if (spiral.template isOfType<typename IfcEntityTypesT::IfcBlossCurve>())
					{
						return convertIfcBlossCurve(spiral.template as<typename IfcEntityTypesT::IfcBlossCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcBlossCurve

					// IfcClothoid SUBTYPE OF IfcSpiral
					if (spiral.template isOfType<typename IfcEntityTypesT::IfcClothoid>())
					{
						return convertIfcClothoid(spiral.template as<typename IfcEntityTypesT::IfcClothoid>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcClothoid

					// IfcCosine SUBTYPE OF IfcSpiral
					if (spiral.template isOfType<typename IfcEntityTypesT::IfcCosine>())
					{
						return convertIfcCosine(spiral.template as<typename IfcEntityTypesT::IfcCosine>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcCosine

					// IfcHelmertCurve SUBTYPE OF IfcSpiral
					if (spiral.template isOfType<typename IfcEntityTypesT::IfcHelmertCurve>())
					{
						return convertIfcHelmertCurve(spiral.template as<typename IfcEntityTypesT::IfcHelmertCurve>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcHelmertCurve

					// IfcSine SUBTYPE OF IfcSpiral
					if (spiral.template isOfType<typename IfcEntityTypesT::IfcSine>())
					{
						return convertIfcSine(spiral.template as<typename IfcEntityTypesT::IfcSine>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcSine

					// the rest we do not support
					throw oip::UnhandledException(spiral);
				}

				// IfcClothoid SUBTYPE of IfcSpiral (exists starting IFC4X3_RC3)
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcClothoid to a tesselated curve.
				* \param[in] clothoid				A pointer to data from \c IfcClothoid.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcClothoid.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcClothoid(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					//throw oip::UnhandledException(clothoid);
					//check input 
					if (clothoid.expired())
						throw oip::ReferenceExpiredException(clothoid);
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC3/HTML/schema/ifcgeometryresource/lexical/ifcclothoid.htm
					//	ENTITY IfcClothoid
					//		SUBTYPE OF(IfcSpiral);
					//			Position: IfcAxis2Placement;
					//			ClothoidConstant: IfcLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					
					// Part 1: Get information from IfcClothoid.
					//1.1 Clothoid position
					carve::math::Matrix clothoidPositionMatrix = carve::math::Matrix::IDENT();
					if (clothoid->Position)
					{
						clothoidPositionMatrix = this->placementConverter->convertIfcAxis2Placement(clothoid->Position.get());
					}

					carve::math::Matrix inverseClothoidPositionMatrix = GeomUtils::computeInverse(clothoidPositionMatrix);

					// Get parameter of the clothoid for trimming begin.
					carve::geom::vector<3> firstPoint = getPointOnCurve<typename IfcEntityTypesT::IfcClothoid>(clothoid, trim1Vec, trimmingPreference);

					// Get parameter of the clothoid for trimming end.
					carve::geom::vector<3> endPoint = getPointOnCurve<typename IfcEntityTypesT::IfcClothoid>(clothoid, trim2Vec, trimmingPreference);

					// get L, A
					// A - Clothoid constant.
					double A = clothoid->ClothoidConstant * this->UnitConvert()->getLengthInMeterFactor();

					// Calculate the length "L" between two ponts.
					//double L = sqrt(pow(endPoint.x- firstPoint.x)+pow(endPoint.y - firstPoint.y)+ pow(endPoint.z - firstPoint.z));
					double L = carve::geom::distance(firstPoint, endPoint);

					// Calculate the length of clothoid curve from (0,0,0,) to x(l),y(l)
					double length = L / A * sqrt(M_PI);
		
					// Get number of tesselated segments
					//int numSegments = this->GeomSettings()->getNumberOfTessellationSegmentsByLength(length);
					//Calculate segment length
					int numSegments = 100;
					double segmentLength = length / numSegments;
					double lengthNew = segmentLength;

					std::vector<carve::geom::vector<3>> clothoidPoints;
					clothoidPoints[0] = carve::geom::VECTOR(0., 0., 0.);
			
					for (int i = 0; i < numSegments; ++i) 
					{
						const IfcEntityTypesT::IfcParameterValue val = lengthNew;

						clothoidPoints.push_back(getPointOnCurve(clothoid, val));
						//val += segmentLength;
					
					}
					
					// Apply position
					if (!clothoidPoints.empty())
					{
						std::vector<carve::geom::vector<3>> newClothoidPoints;
						for (unsigned int i = 0; i < clothoidPoints.size(); ++i)
						{
							carve::geom::vector<3> point3d = clothoidPoints.at(i);
							point3d = clothoidPositionMatrix * point3d;
							newClothoidPoints.push_back(point3d);
						}

						GeomUtils::appendPointsToCurve(newClothoidPoints, targetVec);
						segmentStartPoints.push_back(carve::geom::VECTOR(
							newClothoidPoints.at(0).x,
							newClothoidPoints.at(0).y,
							newClothoidPoints.at(0).z));
					}

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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
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
					if (conic.template isOfType<typename IfcEntityTypesT::IfcCircle>()) 
					{
						return convertIfcCircle(conic.template as<typename IfcEntityTypesT::IfcCircle>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcCircle

					// IfcEllipse SUBTYPE OF IfcConic
					if (conic.template isOfType<typename IfcEntityTypesT::IfcEllipse>())
					{
						return convertIfcEllipse(conic. template as<typename IfcEntityTypesT::IfcEllipse>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifccircle.htm
					//	ENTITY IfcCircle
					//		SUBTYPE OF(IfcConic);
					//		Radius: IfcPositiveLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// Determine position
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(circle->Position);
					carve::math::Matrix inverseConicPositionMatrix = GeomUtils::computeInverse(conicPositionMatrix);

					// Get radius
					double circleRadius = circle->Radius * this->UnitConvert()->getLengthInMeterFactor();
					
					// Calculate an angle on the circle (with circle center in (0., 0., 0.)) for trimming begin.
					carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcCircle>(circle, trim1Vec, trimmingPreference);
					double startAngle = getAngleOnCircle(carve::geom::VECTOR(0., 0., 0.), circleRadius, inverseConicPositionMatrix * point);
					
					// Calculate an angle on the circle (with circle center in (0., 0., 0.)) for trimming end.
					point = getPointOnCurve<typename IfcEntityTypesT::IfcCircle>(circle, trim2Vec, trimmingPreference);
					double endAngle = getAngleOnCircle(carve::geom::VECTOR(0., 0., 0.), circleRadius, inverseConicPositionMatrix * point);

					// Calculate an opening angle.
					double openingAngle = calculateOpeningAngle(senseAgreement, startAngle, endAngle);

					int numSegments = this->GeomSettings()->getNumberOfSegmentsForTessellation(circleRadius, abs(openingAngle));

					const double circleCenter_x = 0.0;
					const double circleCenter_y = 0.0;
					std::vector<carve::geom::vector<2>> circle_points;
					ProfileConverterT<IfcEntityTypesT>::addArcWithEndPoint(
						circle_points, circleRadius,
						startAngle, openingAngle,
						circleCenter_x, circleCenter_y,
						numSegments);

					if (circle_points.size() > 0) 
					{
						// apply position
						std::vector<carve::geom::vector<3>> newCirclePoints;
						for (unsigned int i = 0; i < circle_points.size(); ++i) 
						{
							carve::geom::vector<2>&  point = circle_points.at(i);
							carve::geom::vector<3> point3d(carve::geom::VECTOR(point.x, point.y, 0));
							point3d = conicPositionMatrix * point3d;
							newCirclePoints.push_back(point3d);
						}

						GeomUtils::appendPointsToCurve(newCirclePoints, targetVec);
						segmentStartPoints.push_back(carve::geom::VECTOR(
							newCirclePoints.at(0).x,
							newCirclePoints.at(0).y,
							newCirclePoints.at(0).z));
					}
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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC2/HTML/schema/ifcgeometryresource/lexical/ifcellipse.htm
					//	ENTITY IfcEllipse
					//		SUBTYPE OF(IfcConic);
					//			SemiAxis1: IfcPositiveLengthMeasure;
					//			SemiAxis2: IfcPositiveLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// Determine position.
					carve::math::Matrix conicPositionMatrix = placementConverter->convertIfcAxis2Placement(ellipse->Position);

					// Get both radiuses.
					double xRadius = ellipse->SemiAxis1 * this->UnitConvert()->getLengthInMeterFactor();
					double yRadius = ellipse->SemiAxis2 * this->UnitConvert()->getLengthInMeterFactor();

					double radiusMax = std::max(xRadius, yRadius);
					double radiusMin = std::min(xRadius, yRadius);

					// Calculate a number of segments.
					int numSegments = this->GeomSettings()->getNumberOfSegmentsForTessellation(radiusMax);
					double deltaAngle = 2.0 * M_PI / numSegments;

					double startAngle = 0.;
					if (!trim1Vec.empty() || !trim2Vec.empty()) {
						//Calculate an angle on the ellipse (with ellipse center in (0., 0., 0.)) for trimming begin.
						carve::geom::vector<3> point = getPointOnCurve<typename IfcEntityTypesT::IfcEllipse>(ellipse, trim1Vec, trimmingPreference);
						startAngle = getAngleOnEllipse(carve::geom::VECTOR(0., 0., 0.), xRadius, yRadius, point);

						//Calculate an angle on the ellipse (with ellipse center in (0., 0., 0.)) for trimming end.
						point = getPointOnCurve<typename IfcEntityTypesT::IfcEllipse>(ellipse, trim2Vec, trimmingPreference);
						double endAngle = getAngleOnEllipse(carve::geom::VECTOR(0., 0., 0.), xRadius, yRadius, point);

						// Calculate an opening angle.
						double openingAngle = calculateOpeningAngle(senseAgreement, startAngle, endAngle);

						// Calculate a number of segments.
						numSegments = this->GeomSettings()->getNumberOfSegmentsForTessellation(radiusMax, abs(openingAngle));
						deltaAngle = openingAngle/ numSegments;
					}

					std::vector<carve::geom::vector<3> > ellipsePoints;
					double angle = startAngle;
					for (int i = 0; i < numSegments; ++i) {
						ellipsePoints.push_back(carve::geom::vector<3>(
							carve::geom::VECTOR(
								xRadius * cos(angle),
								yRadius * sin(angle),
								0.)));
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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
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
					carve::geom::vector<3> lineOrigin = placementConverter->convertIfcCartesianPoint(line->Pnt);
					EXPRESSReference<typename IfcEntityTypesT::IfcVector> lineVector = line->Dir;

					carve::geom::vector<3> lineEnd = lineOrigin + 
						placementConverter->convertIfcDirection(lineVector->Orientation) * 
						lineVector->Magnitude * this->UnitConvert()->getLengthInMeterFactor();

					// Part 2: Trimming
					// Calculate trimming at beginning of line.
					if (!trim1Vec.empty()) 
						lineOrigin = getPointOnCurve<typename IfcEntityTypesT::IfcLine>(line, trim1Vec, trimmingPreference);
					// Calculate trimming at end of line.
					if (!trim2Vec.empty())
						lineEnd = getPointOnCurve<typename IfcEntityTypesT::IfcLine>(line, trim2Vec, trimmingPreference);
					
					// Part 3: Add line points
					std::vector<carve::geom::vector<3>> pointVector;
					pointVector.push_back(lineOrigin);
					pointVector.push_back(lineEnd);

					GeomUtils::appendPointsToCurve(pointVector, targetVec);
					segmentStartPoints.push_back(lineOrigin);
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
				*/
				void convertIfcOffsetCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurve>& offsetCurve,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
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
					
					// IfcOffsetCurve2D SUBTYPE OF IfcOffsetCurve
					if (offsetCurve.template isOfType<typename IfcEntityTypesT::IfcOffsetCurve2D>())
					{
						return convertIfcOffsetCurve2D(offsetCurve.template as<typename IfcEntityTypesT::IfcOffsetCurve2D>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcOffsetCurve2D

					// IfcOffsetCurve3D SUBTYPE OF IfcOffsetCurve
					if (offsetCurve.template isOfType<typename IfcEntityTypesT::IfcOffsetCurve3D>())
					{
						return convertIfcOffsetCurve3D(offsetCurve.template as<typename IfcEntityTypesT::IfcOffsetCurve3D>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcOffsetCurve3D

					// IfcOffsetCurveByDistances SUBTYPE OF IfcOffsetCurve
					if (offsetCurve.template isOfType<typename IfcEntityTypesT::IfcOffsetCurveByDistances>())
					{
						return convertIfcOffsetCurveByDistances(offsetCurve.template as<typename IfcEntityTypesT::IfcOffsetCurveByDistances>(),
							targetVec, segmentStartPoints, trim1Vec, trim2Vec, senseAgreement, trimmingPreference);
					} // end if IfcOffsetCurveByDistances

					// the rest we do not support
					throw oip::UnhandledException(offsetCurve);
				}

				// IfcOffsetCurve2D SUBTYPE OF IfcOffsetCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcOffsetCurve2D to a tesselated curve.
				* \param[in] offsetCurve2D			A pointer to data from \c IfcOffsetCurve2D.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcOffsetCurve2D.
				*
				* \note The function is not implemented.
				*/
				void convertIfcOffsetCurve2D(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurve2D>& offsetCurve2D,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference& trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/RELEASE/IFC4_3/lexical/IfcOffsetCurve2D.htm
					//	ENTITY IfcOffsetCurve2D
					//		SUBTYPE OF(IfcOffsetCurve);
					//			Distance: IfcLengthMeasure;
					//			SelfIntersect: IfcLogical;
					//		WHERE
					//			DimIs2D : BasisCurve.Dim = 2;
					//	END_ENTITY;
					// **************************************************************************************************************************
					EXPRESSReference<typename IfcEntityTypesT::IfcCurve> basisCurve = offsetCurve2D->BasisCurve;
					std::vector<carve::geom::vector<3>> basisCurvePoints;
					double distance = offsetCurve2D->Distance * this->UnitConvert()->getLengthInMeterFactor();

					convertIfcCurve(basisCurve, basisCurvePoints, segmentStartPoints,
						trim1Vec, trim2Vec, senseAgreement, trimmingPreference);

					std::vector<carve::geom::vector<3>> offsetCurve2DPoints;

					for (int i; i < basisCurvePoints.size() - 1; i++) {
						carve::geom::vector<3> startPoint = basisCurvePoints[i];
						carve::geom::vector<3> endPoint = basisCurvePoints[i + 1];

						carve::geom::vector<2> startPoint2D = carve::geom::VECTOR(startPoint.x, startPoint.y);
						carve::geom::vector<2> endPoint2D = carve::geom::VECTOR(endPoint.x, endPoint.y);

						carve::geom::vector<2> tangent = endPoint2D - startPoint2D;
						carve::geom::vector<2> orthogonal = carve::geom::VECTOR(-tangent.y, tangent.x);

						carve::geom::vector<3> offsetPoint = carve::geom::VECTOR(startPoint.x + distance * orthogonal.x, 
																				startPoint.y + distance * orthogonal.y, 
																				startPoint.z);
						offsetCurve2DPoints.push_back(offsetPoint);
					}

					//Last Point (I have decided to calculate it in opposite direction, since I have no clue, how to calculate offset of the last point otherwise)
					carve::geom::vector<3> lastStartPoint = basisCurvePoints[basisCurvePoints.size()-1];
					carve::geom::vector<3> lastEndPoint = basisCurvePoints[basisCurvePoints.size() - 2];
					carve::geom::vector<2> lastStartPoint2D = carve::geom::VECTOR(lastStartPoint.x, lastStartPoint.y);
					carve::geom::vector<2> lastEndPoint2D = carve::geom::VECTOR(lastEndPoint.x, lastEndPoint.y);
					carve::geom::vector<2> lastTangent = lastEndPoint2D - lastStartPoint2D;
					carve::geom::vector<2> lastOrthogonal = carve::geom::VECTOR(-lastTangent.y, lastTangent.x);

					carve::geom::vector<3> lastOffsetPoint = carve::geom::VECTOR(lastStartPoint.x - distance * lastOrthogonal.x,
						lastStartPoint.y - distance * lastOrthogonal.y,
						lastStartPoint.z);

					offsetCurve2DPoints.push_back(lastOffsetPoint);
					GeomUtils::appendPointsToCurve(offsetCurve2DPoints, targetVec);
					segmentStartPoints.push_back(offsetCurve2DPoints[0]);
				}

				// IfcOffsetCurve3D SUBTYPE OF IfcOffsetCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcOffsetCurve3D to a tesselated curve.
				* \param[in] offsetCurve3D			A pointer to data from \c IfcOffsetCurve3D.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcOffsetCurve3D.
				*
				* \note The function is not implemented.
				*/
				void convertIfcOffsetCurve3D(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurve3D>& offsetCurve3D,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference& trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/RELEASE/IFC4_3/lexical/IfcOffsetCurve3D.htm
					//	ENTITY IfcOffsetCurve3D
					//		SUBTYPE OF(IfcOffsetCurve);
					//			Distance: IfcLengthMeasure;
					//			SelfIntersect: IfcLogical;
					//			RefDirection: IfcDirection;
					//		WHERE
					//			DimIs2D : BasisCurve.Dim = 3;
					//	END_ENTITY;
					// **************************************************************************************************************************
					EXPRESSReference<typename IfcEntityTypesT::IfcCurve> basisCurve = offsetCurve3D->BasisCurve;
					std::vector<carve::geom::vector<3>> basisCurvePoints;
					double distance = offsetCurve3D->Distance * this->UnitConvert()->getLengthInMeterFactor();
					
					EXPRESSReference<typename IfcEntityTypesT::IfcDirection> offsetDirectionVector = offsetCurve3D->RefDirection;
					carve::geom::vector<3> direction = placementConverter->convertIfcDirection(offsetDirectionVector->Orientation);


					convertIfcCurve(basisCurve, basisCurvePoints, segmentStartPoints,
						trim1Vec, trim2Vec, senseAgreement, trimmingPreference);

					std::vector<carve::geom::vector<3>> offsetCurve3DPoints;

					for (int i; i < basisCurvePoints.size() - 1; i++) {
						carve::geom::vector<3> startPoint = basisCurvePoints[i];
						carve::geom::vector<3> endPoint = basisCurvePoints[i + 1];

						carve::geom::vector<3> tangent = endPoint - startPoint;

						carve::geom::vector<3> offset = carve::geom::cross(direction, tangent);
						carve::geom::vector<3> offsetPoint = startPoint + offset;
						offsetCurve3DPoints.push_back(offsetPoint);
					}

					//Last Point (I have decided to calculate it in opposite direction, since I have no clue, how to calculate offset of the last point otherwise)
					carve::geom::vector<3> lastStartPoint = basisCurvePoints[basisCurvePoints.size() - 1];
					carve::geom::vector<3> lastEndPoint = basisCurvePoints[basisCurvePoints.size() - 2];
					carve::geom::vector<3> lastTangent = lastEndPoint - lastStartPoint;

					carve::geom::vector<3> lastOffset = carve::geom::cross(direction, lastTangent);
					carve::geom::vector<3> lastOffsetPoint = lastStartPoint - lastOffset;

					offsetCurve3DPoints.push_back(lastOffsetPoint);
					GeomUtils::appendPointsToCurve(offsetCurve3DPoints, targetVec);
					segmentStartPoints.push_back(offsetCurve3DPoints[0]);
				}

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				// IfcOffsetCurveByDistances SUBTYPE OF IfcOffsetCurve
				/**********************************************************************************************/
				/*! \brief Converts an \c IfcOffsetCurveByDistances to a tesselated curve.
				* \param[in] offsetCurveByDistances	A pointer to data from \c IfcOffsetCurveByDistances.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcOffsetCurveByDistances.
				*
				* \note The function is not implemented.
				* \internal TODO.
				*/
				void convertIfcOffsetCurveByDistances(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOffsetCurveByDistances>& offsetCurveByDistances,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference& trimmingPreference
				) const noexcept(false)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/RELEASE/IFC4_3/lexical/IfcOffsetCurveByDistances.htm
					//	ENTITY IfcOffsetCurveByDistances
					//		SUBTYPE OF(IfcOffsetCurve);
					//			OffsetValues: LIST[1:? ] OF IfcPointByDistanceExpression;
					//			Tag: OPTIONAL IfcLabel;
					//	END_ENTITY;
					// **************************************************************************************************************************

					EXPRESSReference<typename IfcEntityTypesT::IfcCurve> basisCurve = offsetCurveByDistances->BasisCurve;
					std::vector<std::vector<carve::geom::vector<3>>> basisCurves;

					EXPRESSReference<typename IfcEntityTypesT::IfcDirection> offsetDirectionVector = offsetCurveByDistances->RefDirection;
					carve::geom::vector<3> direction = placementConverter->convertIfcDirection(offsetDirectionVector->Orientation);

					convertIfcCurve(basisCurve, basisCurvePoints, segmentStartPoints,
						trim1Vec, trim2Vec, senseAgreement, trimmingPreference);

					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcDistanceExpression>> OffsetValues = offsetCurveByDistances->OffsetValues;
					std::vector < std::vector<carve::geom::vector<3>>> offsetCurves;

					for (auto distanceExpressionOffset : OffsetValues) {
						carve::geom::vector<3> distanceExpression = convertIfcDistanceExpressionOffsets(distanceExpressionOffset);
					}
				}
#endif

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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					throw oip::UnhandledException(pCurve);
				}

//				// IfcSeriesParameterCurve SUBTYPE of IfcCurve (exists starting IFC4X3_RC4)
//#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
//				/**********************************************************************************************/
//				/*! \brief Converts an \c IfcSeriesParameterCurve to a tesselated curve.
//				* \param[in] boundedCurve			A pointer to data from \c IfcSeriesParameterCurve.
//				* \param[out] targetVec				The tessellated line.
//				* \param[out] segmentStartPoints	The starting points of separate segments.
//				* \param[in] trim1Vec				The trimming of the curve as saved in IFC model - trim at start of curve.
//				* \param[in] trim2Vec				The trimming of the curve as saved in IFC model - trim at end of curve.
//				* \param[in] senseAgreement			Does the resulting geometry have the same sense agreement as the \c IfcCurve.
//				*
//				* \note The function is not implemented.
//				* \internal TODO.
//				*/
//				void convertIfcSeriesParameterCurve(
//					const EXPRESSReference<typename IfcEntityTypesT::IfcSeriesParameterCurve>& seriesParameterCurve,
//					std::vector<carve::geom::vector<3>>& targetVec,
//					std::vector<carve::geom::vector<3>>& segmentStartPoints,
//					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
//					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
//					const bool senseAgreement,
//					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
//				) const noexcept(false)
//				{
//					throw oip::UnhandledException(seriesParameterCurve);
//				}
//				
//#endif

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
					const bool senseAgreement,
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
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

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/*! \brief Converts \c IfcSegment and its subtypes to a series of points.
				* \param[in] segment				The \c IfcSegment to be converted.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcSegment(const EXPRESSReference<typename IfcEntityTypesT::IfcSegment>& segment,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
				{
					//throw oip::UnhandledException(segment);
					
					// IfcCurveSegment SUPTYPE of IfcSegment
					if (segment.isOfType<typename IfcEntityTypesT::IfcCurveSegment>())
					{
						return convertIfcCurveSegment(segment.as<typename IfcEntityTypesT::IfcCurveSegment>(), targetVec, segmentStartPoints);
					}
					// IfcCompositeCurveSegment SUPTYPE of IfcSegment
					else if  (segment.isOfType<typename IfcEntityTypesT::IfcCompositeCurveSegment>())
					{
						return convertIfcCurve(segment.as<typename IfcEntityTypesT::IfcCompositeCurveSegment>()->ParentCurve, targetVec, segmentStartPoints);
					}
					else {
						throw oip::UnhandledException(segment);
					}
					
				}
#endif

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/*! \brief Converts \c IfcCurveSegment to a series of points and appends them to the curve.
				* https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC4-voting/HTML/link/ifccurvesegment.htm
				* \param[in] curveSegment			The \c IfcCurveSegment to be converted.
				* \param[out] targetVec				The tessellated line.
				* \param[out] segmentStartPoints	The starting points of separate segments.
				*/
				void convertIfcCurveSegment(const EXPRESSReference<typename IfcEntityTypesT::IfcCurveSegment>& curveSegment,
					std::vector<carve::geom::vector<3>>& targetVec,
					std::vector<carve::geom::vector<3>>& segmentStartPoints
				) const noexcept(false)
				{
					//	ENTITY IfcCurveSegment
					//	  SUBTYPE OF(IfcSegment);
					//       Placement: IfcPlacement;
					//       SegmentStart: IfcCurveMeasureSelect;
					//       SegmentLength: IfcCurveMeasureSelect;
					//       ParentCurve: IfcCurve;
					//	  DERIVE
					//		Dim : IfcDimensionCount: = ParentCurve.Dim;
					//	END_ENTITY;

					// Get length of the segment curve
					double length = 0.;
					switch (curveSegment->SegmentLength.which())
					{
					case 0:
					{
						// Calculate the length using \c IfcNonNegativeLengthMeasure. 
						length = curveSegment->SegmentLength.get<0>();// *this->UnitConvert()->getLengthInMeterFactor();
						break;
					}
					case 1:
					{
						// Calculate the length using \c IfcParameterValue.
						length = curveSegment->SegmentLength.get<1>();
						break;
					}
					default:
						throw oip::InconsistentGeometryException(curveSegment, "Could not determine SegmentLength!");
					}

					// Determine segments
					double numSegments = 100;
					double deltaLength = length / numSegments;

					std::vector<carve::geom::vector<3>> segmentPoints, segmentDirections;
					double lengthAlong = 0.;
					switch (curveSegment->SegmentStart.which())
					{
					case 0:
					{
						// Calculate the length using \c IfcNonNegativeLengthMeasure. 
						lengthAlong = curveSegment->SegmentStart.get<0>();// *this->UnitConvert()->getLengthInMeterFactor();
						break;
					}
					case 1:
					{
						// Calculate the length using \c IfcParameterValue.
						lengthAlong = curveSegment->SegmentStart.get<1>();
						break;
					}
					default:
						throw oip::InconsistentGeometryException(curveSegment, "Could not determine SegmentStart!");
					}

				    auto runningLength = curveSegment->SegmentStart;
					for( int i = 0; i < numSegments; ++i )
					{ 
						// determine point
						carve::geom::vector<3> point, direction;
						if (curveSegment->ParentCurve.isOfType<typename IfcEntityTypesT::IfcClothoid>())
						{
							point = getPointOnCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcClothoid>(), runningLength);
							direction = getDirectionOfCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcClothoid>(), runningLength);
						}
						else if (curveSegment->ParentCurve.isOfType<typename IfcEntityTypesT::IfcLine>())
						{
							point = getPointOnCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcLine>(), runningLength);
							direction = getDirectionOfCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcLine>(), runningLength);
						}
						else if (curveSegment->ParentCurve.isOfType<typename IfcEntityTypesT::IfcCircle>())
						{
							point = getPointOnCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcCircle>(), runningLength);
							direction = getDirectionOfCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcCircle>(), runningLength);
						}
						else if (curveSegment->ParentCurve.isOfType<typename IfcEntityTypesT::IfcSine>())
						{
							point = getPointOnCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcSine>(), runningLength, length);
							direction = getDirectionOfCurve(curveSegment->ParentCurve.as<typename IfcEntityTypesT::IfcSine>(), runningLength, length);
						}
						segmentPoints.push_back(point);
						segmentDirections.push_back(direction);
						// determine next length
						lengthAlong += deltaLength;
						switch (runningLength.which())
						{
						case 0:
						{
							// Calculate the length using \c IfcNonNegativeLengthMeasure. 
							runningLength = typename IfcEntityTypesT::IfcNonNegativeLengthMeasure(lengthAlong);// *this->UnitConvert()->getLengthInMeterFactor();
							break;
						}
						case 1:
						{
							// Calculate the length using \c IfcParameterValue.
							runningLength = typename IfcEntityTypesT::IfcParameterValue(lengthAlong);
							break;
						}
						default:
							throw oip::InconsistentGeometryException(curveSegment, "Could not determine SegmentStart!");
						}
					}

					if (!segmentPoints.empty())
					{
						//get the local coordinate system
						carve::geom::vector<3> tangent = segmentDirections[0].normalize();
						tangent.y = -tangent.y;
						carve::geom::vector<3> localZ = carve::geom::VECTOR(0., 0., 1.),
							orthogonal = carve::geom::cross(localZ, tangent).normalize(),
							translate = -segmentPoints[0];
						//calculate rotation
						carve::math::Matrix rotationMatrix = carve::math::Matrix(
							tangent.x, orthogonal.x, localZ.x, 0.,
							tangent.y, orthogonal.y, localZ.y, 0.,
							tangent.z, orthogonal.z, localZ.z, 0.,
							0., 0., 0., 1.);
						// apply placement
						const carve::math::Matrix placement =
							placementConverter->convertIfcPlacement(curveSegment->Placement)
							* rotationMatrix;

						std::vector<carve::geom::vector<3>> newPoints;
						for (const auto& point : segmentPoints)
						{
							newPoints.push_back(placement * (point + translate));
						}

						GeomUtils::appendPointsToCurve(newPoints, targetVec);
						segmentStartPoints.push_back(newPoints[0]);
					}
				}
#endif

				/*! \brief Converts \c IfcLoop and its subtypes to a series of points.
				* \param[in] ifcLoop				The \c IfcLoop to be converted.
				* \return							The series of points.
				*/
				std::vector<carve::geom::vector<3>> convertIfcLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcLoop>& ifcLoop
				) const noexcept(false)
				{
					if (ifcLoop.expired()) {
						throw oip::ReferenceExpiredException(ifcLoop);
					}

					if (ifcLoop.template isOfType<typename IfcEntityTypesT::IfcPolyLoop>()) 
					{	
						return convertIfcPolyLoop(ifcLoop.template as<typename IfcEntityTypesT::IfcPolyLoop>());
					} // end if polyloop

					else if (ifcLoop.template isOfType<typename IfcEntityTypesT::IfcEdgeLoop>())
					{
						return convertIfcEdgeLoop(ifcLoop.template as<typename IfcEntityTypesT::IfcEdgeLoop>());
					} // end if edge loop

					throw oip::UnhandledException(ifcLoop);
					
				} // end convertIfcLoop

				/*! \brief Converts \c IfcPolyLoop to a series of points.
				* \param[in] polyLoop				The \c IfcPolyLoop to be converted.
				* \return							The series of points.
				*/
				std::vector<carve::geom::vector<3>> convertIfcPolyLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcPolyLoop>& polyLoop
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> loop = convertIfcCartesianPointVectorSkipDuplicates(polyLoop->Polygon);

					// If first and last point have same coordinates, remove last point
					while (loop.size() > 2) {
						
						if (this->GeomSettings()->areEqual(loop.front(), loop.back()))
						{
							loop.pop_back();
							continue;
						}
						
						return loop;
					}
				}

				/*! \brief Converts \c IfcEdgeLoop to a series of points.
				* \param[in] edgeLoop				The \c IfcEdgeLoop to be converted.
				* \return							The series of points.
				*
				* \note The function disregards topological relationships.
				* \note The function is not fully implemented.
				*
				* \internal TODO.
				*/
				std::vector<carve::geom::vector<3>> convertIfcEdgeLoop(const EXPRESSReference<typename IfcEntityTypesT::IfcEdgeLoop>& edgeLoop
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> loop;

					for (auto &orientedEdge : edgeLoop->EdgeList) {
						// which are described by the type of its edge element object
						EXPRESSReference<typename IfcEntityTypesT::IfcEdge> edgeElement = orientedEdge->EdgeElement;

						if (edgeElement.template isOfType<typename IfcEntityTypesT::IfcEdgeCurve>()) {
							auto edgeCurve = edgeElement.template as<typename IfcEntityTypesT::IfcEdgeCurve>();
							EXPRESSReference<typename IfcEntityTypesT::IfcCurve> curveGeom = edgeCurve->EdgeGeometry;
							std::vector<carve::geom::vector<3>> segmentStartPoints;

							convertIfcCurve(curveGeom, loop, segmentStartPoints);
							continue;
						}

						if (edgeElement.template isOfType<typename IfcEntityTypesT::IfcSubedge>()) 
						{
							auto subEdge = edgeElement.template as<typename IfcEntityTypesT::IfcSubedge>();
							// Not yet implemented!
							throw oip::UnhandledException(edgeLoop);
						}
						/*
						std::cout << "ERROR\t| Entity " << orientedEdge->classname() << " not handled" << std::endl;
						BLUE_LOG(warning) << "Developer Warning: Entity " << orientedEdge->classname() << " not handled.";*/

						// every edge consists of one start and end vertex
						EXPRESSReference<typename IfcEntityTypesT::IfcVertex> edgeStartVertex = edgeElement->EdgeStart;

						if (edgeStartVertex.template isOfType<typename IfcEntityTypesT::IfcVertexPoint>())
						{
							auto edgeStartVertexPoint = edgeStartVertex.template as<typename IfcEntityTypesT::IfcVertexPoint>();

							if (edgeStartVertexPoint->VertexGeometry)
							{
								EXPRESSReference<typename IfcEntityTypesT::IfcPoint> startPoint = edgeStartVertexPoint->VertexGeometry;

								if (!startPoint.template isOfType<typename IfcEntityTypesT::IfcCartesianPoint>())
								{
									auto ifcPoint = startPoint.template as<typename IfcEntityTypesT::IfcCartesianPoint>();
									// TODO: could be also  IfcPointOnCurve, IfcPointOnSurface
									// Not yet implemented!
									throw oip::UnhandledException(edgeLoop);
									continue;
								}
								// TODO: implement
							}
						}
					}

					return loop;
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
				) const noexcept(false)
				{
					polyline_data->beginPolyline();

					auto& vertex_start = ifcEdge->EdgeStart;
					if (vertex_start.template isOfType<typename IfcEntityTypesT::IfcVertexPoint>()) 
					{
						auto vertex_start_point = vertex_start.template as<typename IfcEntityTypesT::IfcVertexPoint>();
						carve::geom::vector<3> point = placementConverter->convertIfcPoint(vertex_start_point->VertexGeometry);

						polyline_data->addVertex(objectPlacement * point);
						polyline_data->addPolylineIndex(0);
					}

					auto& vertex_end = ifcEdge->EdgeEnd;
					if (vertex_end.template isOfType<typename IfcEntityTypesT::IfcVertexPoint>()) 
					{
						auto vertex_end_point = vertex_end.template as<typename IfcEntityTypesT::IfcVertexPoint>();
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
				) const noexcept(false)
				{
					// initialize the return value with enough space
					std::vector<carve::geom::vector<3>> loop;
					loop.reserve(points.size());
					// convert each point individually and add to the return vector
					for (auto& it : points)
						loop.push_back(placementConverter->convertIfcCartesianPoint(it));
						
					// return the loop
					return loop;
				} // end convertIfcCartesianPointVector

				/*! \brief Converts an array of \c IfcCartesianPoint-s to a series of points.
				*
				* \param[in] points				The array of \c IfcCartesianPoint-s to be converted.
				* \return				The series of points.
				*
				* \note The function is not fully implemented.
				*
				* \internal TODO.
				*/
				std::vector<carve::geom::vector<3>> convertIfcCartesianPointVectorSkipDuplicates(
					const std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> loop;

					carve::geom::vector<3>  vertex_previous;
					bool first = true;

					for ( auto& it_cp : ifcPoints) 
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = it_cp.lock();

						carve::geom::vector<3> vertex = placementConverter->convertIfcCartesianPoint( it_cp );

						// skip duplicate vertices
						if (!first) 
						{

							if (this->GeomSettings()->areEqual(vertex, vertex_previous))
							{
								// TODO: is it better to report degenerated loops, or to just omit them?
								BLUE_LOG(warning) << "Duplicate point in polyloop. IfcPoint #" << cp->getId();
								//continue;
							}

						}
						else
							first = false;

						loop.push_back(vertex);
						vertex_previous = vertex;
					}

					return loop;
				}

				/*! \brief Converts \c IfcCartesianPointList to a series of points.
				* \param[in] pointlist			The \c IfcCartesianPointList to be converted.
				* \return						The series of points.
				*/
				std::vector<carve::geom::vector<3> > convertIfcCartesianPointList(
					const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPointList>& pointlist
				) const noexcept(false)
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
					
					std::vector<carve::geom::vector<3>> loop;
					// interpret the points
					if (pointlist.template isOfType<typename IfcEntityTypesT::IfcCartesianPointList2D>())
					{
						const auto& pointlist2d = pointlist.template as<typename IfcEntityTypesT::IfcCartesianPointList2D>();
						loop.reserve(pointlist2d->CoordList.size());
						for (const auto& point : pointlist2d->CoordList)
							loop.push_back(carve::geom::VECTOR(point[0], point[1], 0.) * this->UnitConvert()->getLengthInMeterFactor());
					}
					else if (pointlist.template isOfType<typename IfcEntityTypesT::IfcCartesianPointList3D>())
					{
						const auto& pointlist3d = pointlist.template as<typename IfcEntityTypesT::IfcCartesianPointList3D>();
						loop.reserve(pointlist3d->CoordList.size());
						for (const auto& point : pointlist3d->CoordList)
							loop.push_back(carve::geom::VECTOR(point[0], point[1], point[2]) * this->UnitConvert()->getLengthInMeterFactor());
					}
					else
						throw oip::UnhandledException(pointlist);

					return loop;
				}

#if defined(OIP_MODULE_EARLYBINDING_IFC4X1) || defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
				/*! \brief Gets stations for \c IfcAlignmentCurve at which a point of the tesselation has to be calcuated. 
				* \param[in] alignmentCurve			The \c IfcAlignmentCurve to be converted.
				* \retrun							The series of stations at which a point of the tesselation has to be calcuated.
				*/
				std::vector<double> getStationsForTessellationOfIfcAlignmentCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAlignmentCurve>& alignmentCurve
				) const noexcept(false)
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
					double horStartDistAlong = horizontal->StartDistAlong.value_or(0.0) * this->UnitConvert()->getLengthInMeterFactor();

					// Segments type IfcAlignment2DHorizontalSegment L[1:?]
					if (horizontal->Segments.empty())
						throw oip::InconsistentModellingException(horizontal, "No segments");

					// is it going to be only a horizontal alignment?
					bool bOnlyHorizontal = false;
					//std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVertical>
					auto vertical = alignmentCurve->Vertical;
					if (!vertical) 
					{
						// there is no vertical alignment
						BLUE_LOG(info) << "No IfcAlignment2DVertical in " << alignmentCurve->getErrorLog();
						bOnlyHorizontal = true;
					}
					else
					{
						// vertical alignment is there
						if (vertical->Segments.empty()) 
						{
							BLUE_LOG(warning) << "No segments in " << vertical->getErrorLog();
							bOnlyHorizontal = true;
						}
					}

					// start at the beginning of the alignment
					double dCurrentDistAlong = 0.;

					typename std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment>>::iterator itHorizontalSegment = horizontal->Segments.begin();
					typename std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment>>::iterator   itVerticalSegment;
					if (!bOnlyHorizontal)
						itVerticalSegment = vertical->Segments.begin();

					double dHorizontalSegStart = 0.; 
					// the end station of the last element in the horizontal ( i.e. the start station of current itHorizotnalSegment )
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
							throw oip::InconsistentGeometryException(horCurveGeometry,
							 "Curve segment length is " + std::to_string(horCurveGeometry->SegmentLength));
						
						double dHorizontalSegLength = horCurveGeometry->SegmentLength * this->UnitConvert()->getLengthInMeterFactor();
						double dHorizontalSegEnd = dHorizontalSegStart + dHorizontalSegLength;

						// Step 2: Get horizontal segment type and store the number and length of fragments.
						// the values are needed for calculation of points
						double dFragmentLength = 0.;
						int nFragments = 0;

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
						if (line_segment_2D) 
						{
							dHorizontalRadius = 0.;
						}
						else if (circular_arc_segment_2D) 
						{
							dHorizontalRadius = circular_arc_segment_2D->Radius;
						}
						else if (trans_curve_segment_2D) 
						{
							double dStartRadius = INFINITY, dEndRadius = INFINITY;
							if (trans_curve_segment_2D->StartRadius)
								dStartRadius = trans_curve_segment_2D->StartRadius;
							if (trans_curve_segment_2D->EndRadius)
								dEndRadius = trans_curve_segment_2D->EndRadius;
							dHorizontalRadius = std::min(dStartRadius, dEndRadius);
							if (dHorizontalRadius == INFINITY)
							{
								BLUE_LOG(warning) << trans_curve_segment_2D->getErrorLog() << 
									": A straight disgusised as a transition curve.";
								dHorizontalRadius = 0.;
							}
						}
						else
						{
							throw oip::InconsistentModellingException(*itHorizontalSegment, 
									"Could not determine tesselation values.");
						}

						dHorizontalRadius *= this->UnitConvert()->getLengthInMeterFactor();
						nFragments = this->GeomSettings()->getNumberOfSegmentsForTessellation(dHorizontalRadius);
						dFragmentLength = dHorizontalSegLength / static_cast<double>(nFragments);
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
								dVerticalSegStart = (*itVerticalSegment)->StartDistAlong * this->UnitConvert()->getLengthInMeterFactor();

								// HorizontalLength type IfcPositiveLengthMeasure [1:1]
								if ((*itVerticalSegment)->HorizontalLength <= 0.0) 
									throw oip::InconsistentGeometryException(
										*itVerticalSegment, "Invalid horizontal length.");
								
								dVerticalSegLength = (*itVerticalSegment)->HorizontalLength * this->UnitConvert()->getLengthInMeterFactor();
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
								//      8:                               +---------+    <------- should never ever happen (except if we're considering the first vertical element that strats way beyond the end of the first horizontal segment)

								// option 1 & 2 - bLoop stays on true
								// - these elements should have been considered with previous horizontal element

								// options 3 through 7
								if (dVerticalSegEnd > dHorizontalSegStart)
									bLoop = false;

								// option 8
								if (dVerticalSegStart > dHorizontalSegEnd)
								{
									if (itVerticalSegment == vertical->Segments.begin())
									{
										goto vertical_starts_late; // skip height calculations for this horizontal segment
									}
									else
									{
										throw oip::InconsistentModellingException(
											*itVerticalSegment, "Invalid sequence of vertical elements.");
									}
								}

								// take the next element
								if (bLoop)
									++itVerticalSegment;
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
							if (v_seg_line_2D) 
							{
								dVerticalRadius = 0.;
							}
							else if (v_seg_circ_arc_2D) 
							{
								dVerticalRadius = v_seg_circ_arc_2D->Radius;
							}
							else if (v_seg_par_arc_2D) 
							{
								dVerticalRadius = v_seg_par_arc_2D->ParabolaConstant;
							}
							else
							{
								throw oip::InconsistentModellingException(
									*itVerticalSegment, "Could not determine tesselation values.");
							}

							dVerticalRadius *= this->UnitConvert()->getLengthInMeterFactor();

							// determine tesselation density
							int nVerFragments = this->GeomSettings()->getNumberOfSegmentsForTessellation(dVerticalRadius);
							double dVerFragmentsLength = dVerticalSegLength / (double)(nVerFragments);

							// Select greater accuracy / more fragments / smaller fragments.
							nFragments = std::max(nFragments, nVerFragments);
							dFragmentLength = std::min(dFragmentLength, dVerFragmentsLength);

							// determine the overlap area
							dOverlapStart = std::max(dOverlapStart, dVerticalSegStart);
							dOverlapEnd = std::min(dOverlapEnd, dVerticalSegEnd);
						}

						vertical_starts_late:
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
							++itHorizontalSegment;
							dHorizontalSegStart = dHorizontalSegEnd; // save the end station of itHorizontalSegment for the next iteration
						}
						// vice versa
						else
						{
							if (itVerticalSegment != vertical->Segments.end())
								++itVerticalSegment;
						}

					} // end of horizontal / vertical segments while iteration
					// add the last station
					stations.push_back(dHorizontalSegStart);

					return stations;
				}
#endif

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
				) const noexcept(false)
				{
					carve::geom::vector<3> centerToTrimPoint = trimPoint - circleCenter;
					
					if (this->GeomSettings()->areEqual(centerToTrimPoint.length(), circleRadius)) {
						centerToTrimPoint.normalize();

						double cosAngle = carve::geom::dot(centerToTrimPoint, carve::geom::vector<3>(carve::geom::VECTOR(1., 0., 0.)));

						if (this->GeomSettings()->areEqual(abs(cosAngle), 0.)) 
						{
							if (centerToTrimPoint.y > 0.) 
							{
								return M_PI_2;
							}
							else if (centerToTrimPoint.y < 0.) 
							{
								return M_PI * 1.5;
							}
							else 
							{
								throw oip::InconsistentGeometryException("Cosine and sine cannot be 0 simultaneously!");
							}
						}
						else {
							if (centerToTrimPoint.y > 0.) 
							{
								return acos(cosAngle);
							}
							else if (centerToTrimPoint.y < 0.) 
							{
								return 2.0*M_PI - acos(cosAngle);
							}
							else 
							{
								if (centerToTrimPoint.x > 0.) 
								{
									return 0.;
								}
								else 
								{
									return M_PI;
								}
							}
						}
					}
					else 
					{
						throw oip::InconsistentGeometryException("The point is not located on the circle");
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
				) const noexcept(false)
				{
					carve::geom::vector<3> centerToTrimPoint = trimPoint - ellipseCenter;
					
					if ((centerToTrimPoint.x / ellipseRadiusX) <= 1. && (centerToTrimPoint.y / ellipseRadiusY) <= 1.) {
						double cosAngle = centerToTrimPoint.x / ellipseRadiusX;

						if (this->GeomSettings()->areEqual(abs(cosAngle), 0.)) 
						{
							if (centerToTrimPoint.y > 0.) 
							{
								return M_PI_2;
							}
							else if (centerToTrimPoint.y < 0.) 
							{
								return M_PI * 1.5;
							}
							else 
							{
								throw oip::InconsistentGeometryException("Cosine and sine cannot be 0 simultaneously!");
							}
						}
						else {
							if (centerToTrimPoint.y > 0.) 
							{
								return acos(cosAngle);
							}
							else if (centerToTrimPoint.y < 0.) 
							{
								return 2.0 * M_PI - acos(cosAngle);
							}
							else 
							{
								if (centerToTrimPoint.x > 0.) 
								{
									return 0.;
								}
								else 
								{
									return M_PI;
								}
							}
						}
					}
					else {
						throw oip::InconsistentGeometryException("The point is located outside the ellipse");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates an opening angle based on senseAgreement.
				* \param[in] senseAgreement				True, if direction of the trimmed curve agrees with basis curve. False otherwise.
				* \param[in] startAngle					Start angle of the curve.
				* \param[in] endAngle					End angle of the curve. 
				* \return								Returns an angle between start and end angles.
				*/
				double calculateOpeningAngle(const  bool senseAgreement, 
					const double startAngle, 
					const double endAngle
				)const noexcept(false)
				{
					double openingAngle = 0.;
					if (senseAgreement) 
					{
						if (startAngle < endAngle) 
						{
							openingAngle = endAngle - startAngle;
						}
						else 
						{
							// circle passes 0 angle
							openingAngle = endAngle - startAngle + 2.0*M_PI;
						}
					}
					else {
						if (startAngle > endAngle) 
						{
							openingAngle = endAngle - startAngle;
						}
						else 
						{
							// circle passes 0 angle
							openingAngle = endAngle - startAngle - 2.0*M_PI;
						}
					}

					// correct for -2*PI <= angle <= 2*PI
					if (openingAngle > 0) 
					{
						this->GeomSettings()->normalizeAngle(openingAngle, 0., M_TWOPI);
					}
					else 
					{
						this->GeomSettings()->normalizeAngle(openingAngle, -M_TWOPI, 0.);
					}
					return openingAngle;
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve.
				* \tparam TCurve					A type of the curve. 
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] trimmingVec			A vector of pointers to data form \c IfcTrimmingSelect.
				* \param[in] trimmingPreference		Specifies the preferred way of trimming.
				* \return							The location of the trimming point.
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(
					const EXPRESSReference<TCurve>& curve, 
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trimmingVec, 
					const typename IfcEntityTypesT::IfcTrimmingPreference & trimmingPreference
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> points;

					for (int i = 0; i < trimmingVec.size(); i++) {
						carve::geom::vector<3> point = getPointOnCurve<TCurve>(curve, *trimmingVec[i]);
						points.push_back(point);
					}
					if (trimmingVec.size() == 1) {
						return points[0];
					}
					else if (trimmingVec.size() == 2)
					{
						if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_PARAMETER) == typeid(trimmingPreference))
							return points[0];
						else if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_CARTESIAN) == typeid(trimmingPreference))
							return points[1];
						else if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_UNSPECIFIED) == typeid(trimmingPreference))
							return points[0];
						else
						{
							throw oip::InconsistentModellingException("There is no more Enumeration for IfcTrimmingPreference");
						}
					}
					else 
					{
						throw oip::InconsistentModellingException("Trimming point can be specified only with one or two parameters");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve.
				* \tparam TCurve					A type of the curve. 
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] trimming				A pointer to data from \c IfcTrimmingSelect.
				* \return							The location of the trimming point.
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcTrimmingSelect & trimming) const noexcept(false)
				{
					switch (trimming.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcCartesianPoint. 
						return getPointOnCurve<TCurve>(curve, trimming.get<0>());
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getPointOnCurve<TCurve>(curve, trimming.get<1>());
					}
					default:
						throw oip::InconsistentGeometryException(curve, "TrimmingSelect is wrong!");
					}
				}

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcCurveMeasureSelect & trimming) const noexcept(false)
				{
					switch (trimming.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcNonNegativeLengthMeasure. 
						return getPointOnCurve<TCurve>(curve, trimming.get<0>());
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getPointOnCurve<TCurve>(curve, trimming.get<1>());
					}
					default:
						throw oip::InconsistentGeometryException(curve, "TrimmingSelect is wrong!");
					}
				}
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcCurveMeasureSelect& trimming,
				    const double& length) const noexcept(false)
				{
					switch (trimming.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcNonNegativeLengthMeasure. 
						return getPointOnCurve<TCurve>(curve, trimming.get<0>(), length);
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getPointOnCurve<TCurve>(curve, trimming.get<1>(), length);
					}
					default:
						throw oip::InconsistentGeometryException(curve, "TrimmingSelect is wrong!");
					}
				}
#endif

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcCartesianPoint.
				* \tparam TCurve					A type of the curve. 
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] cartesianPoint			A pointer to data from \c IfcCartesianPoint.
				* \return							The location of the trimming point.
				* \note								The position is not applied.All calculations are made based on center in(0., 0., 0.).
				*/ 
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve> & curve,
					const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>& cartesianPoint) const noexcept(false)
				{
					return placementConverter->convertIfcCartesianPoint(cartesianPoint);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the line using \c IfcCartesianPoint.
				* \param[in] line					A pointer to data from a c\ IfcLine.
				* \param[in] cartesianPoint			A pointer to data from \c IfcCartesianPoint.
				* \return							The location of the trimming point.
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcLine>& line,
					const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>& cartesianPoint)const noexcept(false)
				{
					carve::geom::vector<3> trimmingPoint = placementConverter->convertIfcCartesianPoint(cartesianPoint);
					EXPRESSReference<typename IfcEntityTypesT::IfcVector> lineVector = line->Dir;
					carve::geom::vector<3> closestPointOnLine;

					GeomUtils::closestPointOnLine(trimmingPoint, placementConverter->convertIfcCartesianPoint(line->Pnt),
						placementConverter->convertIfcDirection(lineVector->Orientation), closestPointOnLine);

					if ((closestPointOnLine - trimmingPoint).length() < 0.0001) {
						// trimming point is on the line
						return trimmingPoint;
					}
					else
					{
						throw oip::InconsistentGeometryException(line, "Point is not on the line");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				* \note								The position is not applied.All calculations are made based on center in(0., 0., 0.).
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve> & curve,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve> & curve,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure & parameter) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}
				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \param[in] length  				The Lenght of the curve from \c IfcCurveMeasureSelect.
				* \return							The location of the trimming point.
				* \note								The position is not applied.All calculations are made based on center in(0., 0., 0.).
				*/
				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcParameterValue& parameter, const double& length) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				template <typename TCurve>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure& parameter, const double& length) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the circle using \c IfcParameterValue.
				* \param[in] circle					A pointer to data from \c IfcCircle.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				* \note								The position is not applied. All calculations are made based on center in ( 0., 0., 0.).
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					// Interpret parameter
					double angle = parameter * this->UnitConvert()->getAngleInRadianFactor();

					// Get radius
					double circleRadius = circle->Radius * this->UnitConvert()->getLengthInMeterFactor();
					// Get conic's position
					carve::math::Matrix placement = placementConverter->convertIfcAxis2Placement(circle->Position);
					// Calculate point + apply position
					return placement * carve::geom::VECTOR(circleRadius * cos(angle), circleRadius * sin(angle), 0.);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the ellipse using \c IfcParameterValue.
				* \param[in] ellipse				A pointer to data from \c IfcEllipse.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					// Interpret parameter
					double angle = parameter * this->UnitConvert()->getAngleInRadianFactor();

					// Get radius
					double xRadius = ellipse->SemiAxis1 * this->UnitConvert()->getLengthInMeterFactor();
					double yRadius = ellipse->SemiAxis2 * this->UnitConvert()->getLengthInMeterFactor();
					// Get conic's position
					carve::math::Matrix placement = placementConverter->convertIfcAxis2Placement(ellipse->Position);
					// Calculate point + apply position
					return placement * carve::geom::VECTOR(xRadius * cos(angle), yRadius * sin(angle), 0.);
				}

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the line using \c IfcParameterValue.
				* \param[in] line					A pointer to data from \c IfcLine.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcLine>& line,
					const typename IfcEntityTypesT::IfcParameterValue & parameter)const noexcept(false)
				{
					return placementConverter->convertIfcCartesianPoint(line->Pnt) +
						placementConverter->convertIfcVector(line->Dir) * parameter;
				}


#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)

				/*! \brief Calculates a trimming point on the clothoid.
				* \param[in] clothoid			    A pointer to data from \c IfcClothoid.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				* \note															
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					return getPointOnCurve(clothoid, parameter * this->UnitConvert()->getLengthInMeterFactor());
				}
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure & parameter) const noexcept(false)
				{
					return getPointOnCurve(clothoid, parameter * this->UnitConvert()->getLengthInMeterFactor());
				}
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					// Interpret parameter
					// Get Clothoid Constant
					double A = clothoid->ClothoidConstant * this->UnitConvert()->getLengthInMeterFactor();
					// Interpret polinomial constant for the following integral computations
					//std::vector<double> polynomialConstants = { 0., 0., A, 0. };
					//std::vector<double> polynomialConstants = { 0., 0., A / std::fabs(A), 0. };

					// Implement Taylor series for x coordinate
					double x = SpiralUtils::XbyAngleDeviationPolynomialByTerms(0., 0., 0., 0., 0., 0., A, 0., parameter);

					// Implement Taylor series for y coordinate
					double y = SpiralUtils::YbyAngleDeviationPolynomialByTerms(0., 0., 0., 0., 0., 0., A, 0., parameter);

					return carve::geom::VECTOR(x, y, 0.);
				}
#endif

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)

				/*! \brief Calculates a trimming point on the sine curve.
				* \param[in] sine			        A pointer to data from \c IfcSine.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \param[in] length 				The Lenght of the curve from \c IfcCurveMeasureSelect.
				* \return							The location of the trimming point.
				* \note
				*/
				template <>
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcSine>& sine,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure& parameter, const double& length) const noexcept(false)
				{
					return getPointOnCurve(sine, parameter * this->UnitConvert()->getLengthInMeterFactor(), length * this->UnitConvert()->getLengthInMeterFactor());
				}
				carve::geom::vector<3> getPointOnCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcSine>& sine,
					const typename IfcEntityTypesT::IfcParameterValue& parameter, const double& length) const noexcept(false)
				{
					// Interpret parameter
					double sineTerm = sine->SineTerm * this->UnitConvert()->getLengthInMeterFactor();
					//if length of the curve is less than 1, factor is equal to 1, otherways factor is equal to lenght 
					double factor = std::max(length, 1.0);
					sineTerm /= factor;
					// LinearTerm, ConstantTerm are optional parameters
					EXPRESSOptional<typename IfcEntityTypesT::IfcLengthMeasure> lt = sine->LinearTerm;
					EXPRESSOptional<typename IfcEntityTypesT::IfcLengthMeasure> ct = sine->ConstantTerm;

					double linearTerm, constantTerm;
					if (lt) linearTerm = lt/factor;
					else linearTerm = 0.;
					if (ct) constantTerm = ct/factor;
					else constantTerm = 0.;
	
					std::vector<double> polynomial(26);
					SpiralUtils::PopulateTaylorSeriesSine(polynomial, polynomial.size(), 2. * M_PI);
					if (sineTerm) {
						for (int i = 0; i < polynomial.size(); i++) {
							polynomial[i] /= sineTerm;
						}
					}

					if (constantTerm) { polynomial[0] += 1. / constantTerm; }
					if (linearTerm) { polynomial[1] += linearTerm / std::fabs(linearTerm * linearTerm * linearTerm); }
					if (std::fabs(polynomial[1]) < 0.00000000001) { polynomial[1] = 0.; }

					double x = factor * SpiralUtils::XbyAngleDeviationPolynomial(polynomial, polynomial.size(), parameter/ factor);
					double y = factor * SpiralUtils::YbyAngleDeviationPolynomial(polynomial, polynomial.size(), parameter/ factor);
					
					return carve::geom::VECTOR(x, y, 0.);
				}
#endif

				/**********************************************************************************************/
				/*! \brief Calculates a direction of the curve.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] trimmingVec			A vector of pointers to data form \c IfcTrimmingSelect.
				* \param[in] trimmingPreference		Specifies the preferred way of trimming.
				* \return							The direction of the curve. 
				*/
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(
					const EXPRESSReference<TCurve>& curve,
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trimmingVec,
					const typename IfcEntityTypesT::IfcTrimmingPreference& trimmingPreference
				) const noexcept(false)
				{
					std::vector<carve::geom::vector<3>> directions;

					for (int i = 0; i < trimmingVec.size(); i++) {
						carve::geom::vector<3> direction = getDirectionOfCurve<TCurve>(curve, *trimmingVec[i]);
						directions.push_back(direction);
					}
					if (trimmingVec.size() == 1) {
						return directions[0];
					}
					else if (trimmingVec.size() == 2)
					{
						if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_PARAMETER) == typeid(trimmingPreference))
							return directions[0];
						else if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_CARTESIAN) == typeid(trimmingPreference))
							return directions[1];
						else if (typeid(IfcEntityTypesT::IfcTrimmingPreference::ENUM::ENUM_UNSPECIFIED) == typeid(trimmingPreference))
							return directions[0];
						else
						{
							throw oip::InconsistentModellingException("There is no more Enumeration for IfcTrimmingPreference");
						}
					}
					else
					{
						throw oip::InconsistentModellingException("Trimming point can be specified only with one or two parameters");
					}
				}


				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] trimming				A pointer to data from \c IfcTrimmingSelect.
				* \return							The location of the trimming point.
				*/
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcTrimmingSelect & trimming) const noexcept(false)
				{
					switch (trimming.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcCartesianPoint. 
						return getDirectionOfCurve<TCurve>(curve, trimming.get<0>());
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getDirectionOfCurve<TCurve>(curve, trimming.get<1>());
					}
					default:
						throw oip::InconsistentGeometryException(curve, "IfcTrimmingSelect is wrong!");
					}
				}

#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcCurveMeasureSelect & measureSelect) const noexcept(false)
				{
					switch (measureSelect.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcNonNegativeLengthMeasure. 
						return getDirectionOfCurve<TCurve>(curve, measureSelect.get<0>());
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getDirectionOfCurve<TCurve>(curve, measureSelect.get<1>());
					}
					default:
						throw oip::InconsistentGeometryException(curve, "IfcCurveMeasureSelect is wrong!");
					}
				}
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(
					const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcCurveMeasureSelect& measureSelect,
				    const double& length) const noexcept(false)
				{
					switch (measureSelect.which())
					{
					case 0:
					{
						// Calculate a trimming point using \c IfcNonNegativeLengthMeasure. 
						return getDirectionOfCurve<TCurve>(curve, measureSelect.get<0>(), length);
					}
					case 1:
					{
						// Calculate a trimming point using \c IfcParameterValue.
						return getDirectionOfCurve<TCurve>(curve, measureSelect.get<1>(),length);
					}
					default:
						throw oip::InconsistentGeometryException(curve, "IfcCurveMeasureSelect is wrong!");
					}
				}
#endif

				/**********************************************************************************************/
				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The location of the trimming point.
				* \note								The position is not applied.All calculations are made based on center in(0., 0., 0.).
				*/
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve> & curve,
					const typename IfcEntityTypesT::IfcCartesianPoint & point) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve> & curve,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve> & curve,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure & parameter) const noexcept(false)
				{
					throw oip::UnhandledException(curve);

				}

				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve>& curve,
					const double& parameter) const noexcept(false)
				{
					throw oip::UnhandledException(curve);

				}

				/*! \brief Calculates a trimming point on the curve using \c IfcParameterValue.
				* \tparam TCurve					A type of the curve.
				* \param[in] curve					A pointer to data from the curve.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue or \c IfcNonNegativeLengthMeasure.
				* \param[in] length 				The Lenght of the curve from \c IfcCurveMeasureSelect.
				* \return							The location of the trimming point.
				* \note								The position is not applied.All calculations are made based on center in(0., 0., 0.).
				*/
				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcParameterValue& parameter, const double& length) const noexcept(false)
				{
					throw oip::UnhandledException(curve);
				}

				template <typename TCurve>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<TCurve>& curve,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure& parameter, const double& length) const noexcept(false)
				{
					throw oip::UnhandledException(curve);

				}

				/**********************************************************************************************/
				/*! \brief Converts \c IfcCartesianPoint to a angle parameter and passes it to getDirectionOfCurve.
				* \param[in] circle					A pointer to data from \c IfcCircle.
				* \param[in] point					A pointer to data from \c IfcCartesianPoint.
				* \return							The direction of the tangent.
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const typename IfcEntityTypesT::IfcCartesianPoint& cartesianPoint) const noexcept(false)
				{
					carve::geom::vector<3> point = placementConverter->convertIfcCartesianPoint(cartesianPoint);
					carve::math::Matrix placement = placementConverter->convertIfcAxis2Placement(circle->Position);
					carve::math::Matrix inversePlacement = GeomUtils::computeInverse(placement);
					carve::geom::vector<3> directionFromCenterToPoint = inversePlacement * point; //-carve::geom::VECTOR(0., 0., 0.)
					// if the radial vector from Center to a point has coordinates (a,b), then the direction vector at that point is (−b,a)
					return carve::geom::VECTOR(-directionFromCenterToPoint.y, directionFromCenterToPoint.x, 0.);
				}

				/*! \brief Converts \c IfcParameterValue to a angle parameter and passes it to getDirectionOfCurve.
				* \param[in] circle					A pointer to data from \c IfcCircle.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The direction of the tangent.
				* \note
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const typename IfcEntityTypesT::IfcParameterValue& parameter) const noexcept(false)
				{
					return getDirectionOfCurve(circle, parameter * this->UnitConvert()->getAngleInRadianFactor());
				}

				/*! \brief Calculates a direciton of the tangent on the circle border.
				* \param[in] circle					A pointer to data from \c IfcCircle.
				* \param[in] angle					The angle.
				* \return							The direction of the tangent.
				* \note
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcCircle>& circle,
					const double& angle) const noexcept(false)
				{
					// https://math.stackexchange.com/questions/2680855/find-direction-of-tangent-vector-based-on-trajectory-along-circle
					// if the radial vector from Center to a point has coordinates (a,b), then the direction vector at that point is (−b,a) 
					return carve::geom::VECTOR(-sin(angle), cos(angle), 0.);
				}


				/**********************************************************************************************/
				/*! \brief Converts \c IfcCartesianPoint to a angle parameter and passes it to getDirectionOfCurve.
				* \param[in] ellipse				A pointer to data from \c IfcEllipse.
				* \param[in] point					A pointer to data from \c IfcCartesianPoint.
				* \return							The direction of the tangent.
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					const typename IfcEntityTypesT::IfcCartesianPoint& cartesianPoint) const noexcept(false)
				{
					carve::geom::vector<3> point = placementConverter->convertIfcCartesianPoint(cartesianPoint);

					double angle = std::atan2(point.y, point.x);

					return getDirectionOfCurve(ellipse, angle);
				}

				/*! \brief Converts \c IfcParameterValue to a angle parameter and passes it to getDirectionOfCurve.
				* \param[in] ellipse				A pointer to data from \c IfcEllipse.
				* \param[in] parameter				A pointer to data from \c IfcParameterValue.
				* \return							The direction of the tangent.
				* \note
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					const typename IfcEntityTypesT::IfcParameterValue& parameter) const noexcept(false)
				{
					return getDirectionOfCurve(ellipse, parameter * this->UnitConvert()->getAngleInRadianFactor());
				}

				/*! \brief Calculates a direciton of the tangent on the ellipse border.
				* \param[in] ellipse			    A pointer to data from \c IfcEllipse.
				* \param[in] angle					The angle.
				* \return							The direction of the tangent.
				* \note
				*/
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcEllipse>& ellipse,
					const double& angle) const noexcept(false)
				{
					carve::math::Matrix placement = placementConverter->convertIfcAxis2Placement(ellipse->Position);
					carve::math::Matrix inversePlacement = GeomUtils::computeInverse(placement);
					
					double xRadius = ellipse->SemiAxis1 * this->UnitConvert()->getLengthInMeterFactor();
					double yRadius = ellipse->SemiAxis2 * this->UnitConvert()->getLengthInMeterFactor();

					carve::geom::vector<3> point = carve::geom::VECTOR(xRadius * cos(angle), yRadius * sin(angle), 0.);
					carve::geom::vector<3> directionFromCenterToPoint = inversePlacement * point;
					//https://www.algebra.com/algebra/homework/Quadratic-relations-and-conic-sections/Tangent-lines-to-an-ellipse.lesson
					// if the radial vector from Center to a point has coordinates (a,b), then the direction vector at that point is (−b/yRadius^2 ,a/xRadius^2)					
					carve::geom::vector<3> direction = carve::geom::VECTOR(-point.y / (yRadius * yRadius),
																			point.x / (xRadius * xRadius),
																			0.);
					return direction.normalize();
				}


#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/*! \brief Calculates an angle of the clothoid.
				* \param[in] clothoid			    A pointer to data from \c IfcClothoid.
				* \param[in] parameter				The length.
				* \return							The Angle in radians.
				* \note
				*/
				template <>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const typename IfcEntityTypesT::IfcParameterValue & parameter) const noexcept(false)
				{
					return getDirectionOfCurve(clothoid, parameter * this->UnitConvert()->getLengthInMeterFactor());
				}
				template <>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure & parameter) const noexcept(false)
				{
					return getDirectionOfCurve(clothoid, parameter * this->UnitConvert()->getLengthInMeterFactor());
				}
				template<>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcClothoid>& clothoid,
					const double& parameter) const noexcept(false)
				{
					//get clothoid constant -> linear term
					double A = clothoid->ClothoidConstant * this->UnitConvert()->getLengthInMeterFactor();
					//get calculated linearterm

					double angle = SpiralUtils::AngleByAngleDeviationPolynomialByTerms(0., 0., 0., 0., 0., 0., A, 0., parameter);
				

					// double term = SpiralUtils::AngleByAngleDeviationPolynomialByTerms(0., 0., 0., 0., 0., 0., A, 0., parameter);

					//std::vector<double> polynomialConstants = { 0.,0.,term };

					//double angle = SpiralUtils::AngleByAngleDeviationPolynomial(polynomialConstants, polynomialConstants.size(), parameter);

					return carve::geom::VECTOR(std::cos(angle), std::sin(angle), 0.);
				}
#endif
#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC4)
				/*! \brief Calculates an angle of the sine.
				* \param[in] sine			        A pointer to data from \c IfcSine.
				* \param[in] parameter				The trimmed length.
				* \param[in] length 				The Lenght of the curve from \c IfcCurveMeasureSelect.
				* \return							The Angle in radians.
				* \note
				*/
			    
				template <>
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcSine>& sine,
					const typename IfcEntityTypesT::IfcNonNegativeLengthMeasure& parameter, const double& length) const noexcept(false)
				{
					return getDirectionOfCurve(sine, parameter * this->UnitConvert()->getLengthInMeterFactor(), length * this->UnitConvert()->getLengthInMeterFactor());
				}
				carve::geom::vector<3> getDirectionOfCurve(const EXPRESSReference<typename IfcEntityTypesT::IfcSine>& sine,
					const typename IfcEntityTypesT::IfcParameterValue& parameter, const double& length) const noexcept(false)
				{
					// Interpret parameter
					double sineTerm = sine->SineTerm * this->UnitConvert()->getLengthInMeterFactor();
					//if length of the curve is less than 1, factor is equal to 1, otherways factor is equal to lenght 
					double factor = std::max(length, 1.0);
					sineTerm /= factor;
					// LinearTerm, ConstantTerm are optional parameters
					EXPRESSOptional<typename IfcEntityTypesT::IfcLengthMeasure> lt = sine->LinearTerm;
					EXPRESSOptional<typename IfcEntityTypesT::IfcLengthMeasure> ct = sine->ConstantTerm;

					double linearTerm, constantTerm;
					if (lt) linearTerm = lt / factor;
					else linearTerm = 0.;
					if (ct) constantTerm = ct / factor;
					else constantTerm = 0.;

					std::vector<double> polynomial(26);
					SpiralUtils::PopulateTaylorSeriesSine(polynomial, polynomial.size(), 2. * M_PI);
					if (sineTerm) {
						for (int i = 0; i < polynomial.size(); i++) {
							polynomial[i] /= sineTerm;
						}
					}

					if (constantTerm) { polynomial[0] += 1. / constantTerm; }
					if (linearTerm) { polynomial[1] += linearTerm / std::fabs(linearTerm * linearTerm * linearTerm); }
					if (std::fabs(polynomial[1]) < 0.00000000001) { polynomial[1] = 0.; }

					double angle = SpiralUtils::AngleByAngleDeviationPolynomial(polynomial, polynomial.size(), parameter/factor);

					return carve::geom::VECTOR(std::cos(angle), std::sin(angle), 0.);
				}
#endif

			protected:

				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;
			}; // end class
		}; // end namespace IfcGeometryConverter
	}; // end namespace Core
}; // end namespace OIP


#endif
