// Copied and modified code from "IfcPlusPlus".
// This code is available under the OSGPL license. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 */

// More details can be found in README.md file in the root directory.

// visual studio
#pragma once
// unix
#ifndef REPRESENTATIONCONVERTER_H
#define REPRESENTATIONCONVERTER_H

#include <algorithm>
#include <memory>
#include <set>
#include <sstream>

#include "CarveHeaders.h"
//#include "ReaderSettings.h"

#include "ConverterBase.h"

#include "GeorefConverter.h"
#include "CurveConverter.h"
#include "FaceConverter.h"
#include "GeomUtils.h"
#include "PlacementConverter.h"
#include "ProfileCache.h"
#include "ProfileConverter.h"
#include "SolidModelConverter.h"

#include "BlueFramework/Core/Diagnostics/log.h"


/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {

			/*! \brief The top converter class.
			 *
			 * This class includes top-level converter functions and calls other converters correspondingly.
			 * This should be used as an entry point to the geometry converter functionalities.
			 *
			 * \param IfcEntityTypesT The IFC version templates
			 */
			template <
				class IfcEntityTypesT
			>
			class RepresentationConverterT : public ConverterBaseT<IfcEntityTypesT>
			{
			public:
				//! Constructor
				RepresentationConverterT(
					std::shared_ptr<GeometrySettings> geomSettings, 
					std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
					std::shared_ptr<GeoreferencingConverterT<IfcEntityTypesT>> georefConv
				)
					: 
					ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
					georeferencingConverter_(georefConv)
				{
					handle_styled_items = true;
					handle_layer_assignments = true;

					placementConverter = std::make_shared<PlacementConverterT<IfcEntityTypesT>>(geomSettings, unitConverter);

					// styles_converter = shared_ptr<StylesConverter>( new StylesConverter() );

					curveConverter = std::make_shared<CurveConverterT<IfcEntityTypesT>>(geomSettings, unitConverter, placementConverter);

					faceConverter = std::make_shared<FaceConverterT<IfcEntityTypesT>>(geomSettings, unitConverter, placementConverter, curveConverter);

					profileCache = std::make_shared<ProfileCacheT<IfcEntityTypesT>>(geomSettings, unitConverter, placementConverter);
					solidConverter =
						std::make_shared<SolidModelConverterT<IfcEntityTypesT>>(geomSettings, unitConverter, placementConverter, curveConverter, faceConverter, profileCache);
				}

				//! Destructor
				~RepresentationConverterT()
				{
				}

				/*! \brief Converts \c IfcRepresentation to meshes and polylines.
				*
				* \param[in] representation The \c IfcRepresentation to be converted.
				* \param[in] objectPlacement The relative location of the origin of the representation's coordinate system within the geometric context.
				* \param[out] inputData A pointer to be filled with the relevant data.
				*/
				void convertIfcRepresentation(
					const EXPRESSReference<typename IfcEntityTypesT::IfcRepresentation>& representation,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& inputData
				) const throw(...)
				{
					// **************************************************************************************************************************
					// IfcRepresentation
					//  https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcrepresentationresource/lexical/ifcrepresentation.htm
					// ENTITY IfcRepresentation
					//	ABSTRACT SUPERTYPE OF(ONEOF(IfcShapeModel, IfcStyleModel));
					//		ContextOfItems: IfcRepresentationContext;
					//		RepresentationIdentifier: OPTIONAL IfcLabel;
					//		RepresentationType: OPTIONAL IfcLabel;
					//		Items: SET[1:?] OF IfcRepresentationItem;
					//	INVERSE
					//		RepresentationMap : SET[0:1] OF IfcRepresentationMap FOR MappedRepresentation;
					//		LayerAssignments: SET[0:? ] OF IfcPresentationLayerAssignment FOR AssignedItems;
					//		OfProductRepresentation: SET[0:? ] OF IfcProductRepresentation FOR Representations;
					// END_ENTITY;
					// **************************************************************************************************************************

					// loop over all RepresentationItems
					for (auto& it_representation_item : representation->Items)
					{
						// catch UnhandledException
						try
						{
							// the data of the item
							std::shared_ptr<ItemData> itemData(new ItemData());

							// call the converter
							convertIfcRepresentationItem(it_representation_item, objectPlacement, itemData);

							// only add if no exception was thrown
							inputData->vec_item_data.push_back(itemData);
						}
						catch (const oip::UnhandledException& ex)
						{
							// write the error to the console
							BLUE_LOG(warning) << representation->getErrorLog() + ": We don't support this (yet). Care to contribute?";
							BLUE_LOG(warning) << std::string(ex.what());
							continue;
						}
						catch (const oip::InconsistentGeometryException& ex)
						{
							// write the error to the console
							BLUE_LOG(warning) << representation->getErrorLog() + ": Nothing is shown - sth wrong with geometry.";
							BLUE_LOG(warning) << std::string(ex.what());
							continue;
						}
						catch (const oip::InconsistentModellingException& ex)
						{
							// write the error to the console
							BLUE_LOG(warning) << representation->getErrorLog() + ": Nothing is shown - sth wrong with IFC model.";
							BLUE_LOG(warning) << std::string(ex.what());
							continue;
						}
						catch (const std::exception& ex)
						{
							// write the error to the console
							BLUE_LOG(warning) << representation->getErrorLog() + ": Nothing is shown - std::exception.";
							BLUE_LOG(warning) << std::string(ex.what());
							continue;
						}
						catch (...)
						{
							// write the error to the console
							BLUE_LOG(warning) << representation->getErrorLog() + ": Nothing is shown - unknown error.";
							continue;
							throw; // throw onwards
						}

					} // end for each representation item

					//TODO remaining handle layer assignments (requires INVERSE)
					if(handle_layer_assignments) {
						// std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment>>& LayerAssignments_inverse =
						//	representation->LayerAssignments_inverse;
						//
						// typename std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment>>::iterator it_LayerAssignments_inverse;
						// for (it_LayerAssignments_inverse = LayerAssignments_inverse.begin();
						//	it_LayerAssignments_inverse != LayerAssignments_inverse.end();
						//	++it_LayerAssignments_inverse)
						//{
						//	std::shared_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment> layer_assignment((*it_LayerAssignments_inverse));
						//
						//	std::shared_ptr<typename IfcEntityTypesT::IfcPresentationLayerWithStyle> layer_assignment_with_style =
						//		std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPresentationLayerWithStyle>(layer_assignment);
						//	if (layer_assignment_with_style)
						//	{
						//		// deactivated by now due to compability issues
						//		/*std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPresentationStyleSelect> >& vec_presentation_styles =
						// layer_assignment_with_style->LayerStyles; 		for (int i = 0; i<vec_presentation_styles.size(); ++i)
						//		{
						//			std::shared_ptr<typename IfcEntityTypesT::IfcPresentationStyleSelect>&  presentation_style = vec_presentation_styles[i];
						//		}*/
						//	}
						//}
					}
				}

				/*! \brief Converts \c IfcRepresentationItem to meshes and polylines.
				 *
				 * \param[in] reprItem The \c IfcRepresentationItem to be converted.
				 * \param[in] objectPlacement The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData A pointer to be filled with the relevant data.
				 */
				void convertIfcRepresentationItem(
					const EXPRESSReference<typename IfcEntityTypesT::IfcRepresentationItem>& reprItem,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					// *************************************************************************************************************************************************************//
					//	IfcRepresentationItem	
					//   https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcrepresentationitem.htm
					//	ABSTRACT SUPERTYPE OF IfcGeometricRepresentationItem, IfcMappedItem, IfcStyledItem, IfcTopologicalRepresentationItem										//
					// *************************************************************************************************************************************************************//

					// (1/4) IfcGeometricRepresenationItem SUBTYPE OF IfcRepresentationItem
					if (reprItem.isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationItem>())
					{
						// convert as IfcGeometricRepresentationItem
						convertIfcGeometricRepresentationItem(
							reprItem.as<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(),
							objectPlacement, itemData);
						return;
					}

					// (2/4) IfcMappedItem SUBTYPE OF IfcRepresentationItem
					if (reprItem.isOfType<typename IfcEntityTypesT::IfcMappedItem>())
					{
						// convert as IfcMappedItem
						convertIfcMappedItem(
							reprItem.as<typename IfcEntityTypesT::IfcMappedItem>(),
							objectPlacement, itemData);
						return;
					}

					// (3/4) IfcStyledItem SUBTYPE OF IfcRepresentationItem
					if (reprItem.isOfType<typename IfcEntityTypesT::IfcStyledItem>())
					{
						// convert as IfcStyledItem
						convertIfcStyledItem(reprItem.as<typename IfcEntityTypesT::IfcStyledItem>(), itemData);
						return;
					}

					// (4/4) IfcTopologicalRepresentationItem SUBTYPE OF IfcRepresentationItem
					if (reprItem.isOfType<typename IfcEntityTypesT::IfcTopologicalRepresentationItem>()) 
					{
						// convert as IfcTopologicalRepresentationItem
						convertIfcTopologicalRepresentationItem(
							reprItem.as<typename IfcEntityTypesT::IfcTopologicalRepresentationItem>(),
							objectPlacement, itemData);
						return;
					}

					// should sth be added to the inheritance structure, we don't support it
					throw oip::UnhandledException(reprItem);
				}

				/*! \brief Converts \c IfcGeometricRepresentationItem to meshes and polylines.
				 *
				 * There are still some representations that are not covered.
				 *
				 * \param[in] geomItem The \c IfcGeometricRepresentationItem to be converted.
				 * \param[in] pos The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData A pointer to be filled with the relevant data.
				*/
				void convertIfcGeometricRepresentationItem(
					const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationItem>& geomItem,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					// *********************************************************************************************************************************************************************//
					//	IfcGeometricRepresentationItem	 
					//   https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC1/HTML/link/ifcgeometricrepresentationitem.htm
					// TODO Not all subtypes are covered (not all make sense either)
					//  *...* -> covered (at least by this function)
					//  -...- -> doesn't make sense
					//   ...  -> TODO (implement / decide)
					// 	ABSTRACT SUPERTYPE OF(ONEOF(-IfcAlignment2DHorizontal-, -IfcAlignment2DSegment-, -IfcAlignment2DVertical-, IfcAnnotationFillArea, 
					//   -IfcAxisLateralInclination-, *IfcBooleanResult*, IfcBoundingBox, IfcCartesianPointList, IfcCartesianTransformationOperator, 
					//   IfcCompositeCurveSegment, *IfcCsgPrimitive3D*, *IfcCurve*, IfcDirection, IfcDistanceExpression, *IfcFaceBasedSurfaceModel*, 
					//   IfcFillAreaStyleHatching, IfcFillAreaStyleTiles, *IfcGeometricSet*, IfcHalfSpaceSolid, IfcLightSource, IfcLinearAxisWithInclination, 
					//   IfcOrientationExpression, IfcPlacement, IfcPlanarExtent, *IfcPoint*, IfcSectionedSpine, *IfcShellBasedSurfaceModel*, *IfcSolidModel*, 
					//   *IfcSurface*, *IfcTessellatedItem*, IfcTextLiteral, *IfcVector*))
					// *********************************************************************************************************************************************************************//

					// (1/*) IfcFaceBasedSurfaceModel SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel>()) {
						faceConverter->convertIfcFaceBasedSurfaceModel(
							geomItem.as<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel>(), 
							pos, itemData);
						return;
					}

					// (2/*) IfcBooleanResult SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcBooleanResult>()) {
						solidConverter->convertIfcBooleanResult(
							geomItem.as<typename IfcEntityTypesT::IfcBooleanResult>().lock(), 
							pos, itemData);
						return;
					}

					// (3/*) IfcSolidModel SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcSolidModel>()) {
						solidConverter->convertIfcSolidModel(
							geomItem.as<typename IfcEntityTypesT::IfcSolidModel>(), 
							pos, itemData);
						return;
					}

					// (4/*) IfcCurve SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcCurve>()) {
						curveConverter->convertIfcCurve(
							geomItem.as<typename IfcEntityTypesT::IfcCurve>(), 
							pos, itemData);
						return;
					}

					// (5/*) IfcShellBasedSurfaceModel SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcShellBasedSurfaceModel>()) {
						faceConverter->convertIfcShellBasedSurfaceModel(
							geomItem.as<typename IfcEntityTypesT::IfcShellBasedSurfaceModel>(),
							pos, itemData);
						return;
					}

					// (6/*) IfcSurface SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcSurface>()) {
						faceConverter->convertIfcSurface(
							geomItem.as<typename IfcEntityTypesT::IfcSurface>(), 
							pos, itemData);
						return;
					}

					// (7/*) IfcGeometricSet SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcGeometricSet>()) {
						convertIfcGeometricSet(
							geomItem.as<typename IfcEntityTypesT::IfcGeometricSet>(),
							pos, itemData);
						return;
					}

					// (8/*) IfcSectionedSpine SUBTYPE OF IfcGeometricRepresentationItem
					if(geomItem.isOfType<typename IfcEntityTypesT::IfcSectionedSpine>()) {
						convertIfcSectionedSpine(
							geomItem.as<typename IfcEntityTypesT::IfcSectionedSpine>(), 
							pos, itemData);
						return;
					}

					// (9/*) IfcTessellatedItem SUBTYPE OF IfcGeometricRepresentationItem
					if (geomItem.isOfType<typename IfcEntityTypesT::IfcTessellatedItem>()) {
						faceConverter->convertIfcTessellatedItem(
							geomItem.as<typename IfcEntityTypesT::IfcTessellatedItem>(),
							pos, itemData);
						return;
					}

					// (10/*) IfcVector SUBTYPE OF IfcGeometricRepresentationItem
					if (geomItem.isOfType<typename IfcEntityTypesT::IfcVector>()) {
						carve::geom::vector<3> vct = placementConverter->convertIfcVector(
							geomItem.as<typename IfcEntityTypesT::IfcVector>());

						std::shared_ptr<carve::input::PolylineSetData> polylineData = std::make_shared<carve::input::PolylineSetData>();
						polylineData->beginPolyline();

						polylineData->addVertex(pos * carve::geom::VECTOR(0.,0.,0.));
						polylineData->addPolylineIndex(0);
						polylineData->addVertex(pos * vct);
						polylineData->addPolylineIndex(1);

						itemData->polylines.push_back(polylineData);
						return;
					}

					// (11/*) IfcPoint SUBTYPE OF IfcGeometricRepresentationItem
					if (geomItem.isOfType<typename IfcEntityTypesT::IfcPoint>())
					{
						addPointCross(geomItem.as<typename IfcEntityTypesT::IfcPoint>(), pos, itemData);
						return;
					}

					throw oip::UnhandledException(geomItem);
				}


				/*! \brief Converts \c IfcMappedItem to meshes and polylines.
				 *
				 * \param[in] mapped_item The \c IfcMappedItem to be converted.
				 * \param[in] pos The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData A pointer to be filled with the relevant data.
				 */
				void convertIfcMappedItem(
					const EXPRESSReference<typename IfcEntityTypesT::IfcMappedItem>& mapped_item,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					// *********************************************************************************************************************************************************************//
					//  https://standards.buildingsmart.org/IFC/DEV/IFC4_3/RC1/HTML/link/ifcmappeditem.htm
					// ENTITY IfcMappedItem
					//	SUBTYPE OF(IfcRepresentationItem);
					//	 MappingSource: IfcRepresentationMap;
					//	 MappingTarget: IfcCartesianTransformationOperator;
					// END_ENTITY;
					// *********************************************************************************************************************************************************************//
					auto& map_source = mapped_item->MappingSource;
					
					// *********************************************************************************************************************************************************************//
					// ENTITY IfcRepresentationMap;
					//  MappingOrigin: IfcAxis2Placement;
					//  MappedRepresentation: IfcRepresentation;
					// INVERSE
					//	HasShapeAspects : SET[0:?] OF IfcShapeAspect FOR PartOfProductDefinitionShape;
					//  MapUsage: SET[0:?] OF IfcMappedItem FOR MappingSource;
					// WHERE
					//	ApplicableMappedRepr : 'IFCREPRESENTATIONRESOURCE.IfcShapeModel' IN TYPEOF(MappedRepresentation);
					// END_ENTITY;
					// *********************************************************************************************************************************************************************//
					auto& mapped_representation = map_source->MappedRepresentation;
					
					// get the position
					carve::math::Matrix map_matrix_target(carve::math::Matrix::IDENT());
					PlacementConverterT<IfcEntityTypesT>::convertTransformationOperator(mapped_item->MappingTarget.lock(), map_matrix_target, UnitConvert()->getLengthInMeterFactor());
					carve::math::Matrix map_matrix_origin = placementConverter->convertIfcAxis2Placement(map_source->MappingOrigin);
					carve::math::Matrix mapped_pos((map_matrix_origin * objectPlacement) * map_matrix_target);

					// convert the mapped representation
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& inputData
						= std::make_shared<ShapeInputDataT<IfcEntityTypesT>>();
					convertIfcRepresentation(mapped_representation, mapped_pos, inputData);

					// add to the return data
					std::for_each(inputData->vec_item_data.begin(),
						inputData->vec_item_data.end(),
						[&](const std::shared_ptr<ItemData>& data) { itemData->append(data); });
				}


				/*! \brief Converts \c IfcTopologicalRepresentationItem to meshes and polylines.
				 *
				 * \param[in] mapped_item The \c IfcTopologicalRepresentationItem to be converted.
				 * \param[in] pos The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData A pointer to be filled with the relevant data.
				 */
				void convertIfcTopologicalRepresentationItem(
					const EXPRESSReference<typename IfcEntityTypesT::IfcTopologicalRepresentationItem>& topo_item,
					const carve::math::Matrix& objectPlacement,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					// IfcTopologicalRepresentationItem 
					//  ABSTRACT SUPERTYPE OF IfcConnectedFaceSet*, IfcEdge, IfcFace*, IfcFaceBound*, IfcLoop*, IfcPath*, IfcVertex*.

					// (1/*) IfcConnectedFaceSet SUBTYPE OF IfcTopologicalRepresentationItem
					if (topo_item.isOfType<typename IfcEntityTypesT::IfcConnectedFaceSet>()) {
						throw oip::UnhandledException(topo_item);
					}

					// (2/*) IfcEdge SUBTYPE OF IfcTopologicalRepresentationItem
					std::shared_ptr<typename IfcEntityTypesT::IfcEdge> topo_edge = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdge>(topo_item.lock());
					if (topo_item.isOfType<typename IfcEntityTypesT::IfcEdge>() ) {
						std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());
						curveConverter->convertIfcEdge(topo_item.as<typename IfcEntityTypesT::IfcEdge>(), objectPlacement, polyline_data);
						itemData->polylines.push_back(polyline_data);
						return;
					}

					// the rest is not supported
					throw oip::UnhandledException(topo_item);
				}

				/*! \brief Converts \c IfcGeometricSet to meshes and polylines.
				 *
				 * \param[in] geomSet The \c IfcGeometricSet to be converted.
				 * \param[in] pos The relative location of the origin of the representation's coordinate system within the geometric context.
				 * \param[out] itemData A pointer to be filled with the relevant data.
				 */
				void convertIfcGeometricSet(
					const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricSet>& geomSet,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					// loop over the elements
					for (auto& it_set_elements : geomSet->Elements) {
						// TYPE IfcGeometricSetSelect = SELECT (IfcCurve, IfcPoint, IfcSurface);
						switch (it_set_elements.which()) {
						case 0: 
						{
							curveConverter->convertIfcCurve(it_set_elements.template get<0>(), pos, itemData);
						}
							break;
						case 1:
						{
							addPointCross(it_set_elements.template get<1>(), pos, itemData);
						}
							break;
						case 2:
						{
							faceConverter->convertIfcSurface(it_set_elements.template get<2>(), pos, itemData);
						}
							break;
						default: 
							// what else?
							break;
						}
					}

					if (geomSet.isOfType<typename IfcEntityTypesT::IfcGeometricCurveSet>()) {
						// ENTITY IfcGeometricCurveSet
						//  SUBTYPE OF(IfcGeometricSet);
						//  WHERE
						//	 NoSurfaces : SIZEOF(QUERY(Temp < *SELF\IfcGeometricSet.Elements |
						//		'IFCGEOMETRYRESOURCE.IfcSurface' IN TYPEOF(Temp))) = 0;
						//  END_ENTITY;

						// we're done - it's just a Where, which we don't care about yet
					}
					
					return;
				}


				void addPointCross(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPoint>& ifcpoint,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					carve::geom::vector<3> point = placementConverter->convertIfcPoint(ifcpoint);
					// draw a 3D cross at the point
					std::vector<std::pair<int, int>> pairs({ { 1,1 },{ 1,-1 },{ -1,-1 },{ -1,1 } });
					for (auto el : pairs)
					{
						std::shared_ptr<carve::input::PolylineSetData> polyline =
							std::make_shared<carve::input::PolylineSetData>();
						polyline->beginPolyline();
						polyline->addVertex(pos * (point + carve::geom::VECTOR(0.1*el.first, 0.1*el.second, 0.1)));
						polyline->addPolylineIndex(0);
						polyline->addVertex(pos * (point + carve::geom::VECTOR(-0.1*el.first, -0.1*el.second, -0.1)));
						polyline->addPolylineIndex(1);
						itemData->polylines.push_back(polyline);
					}
				}

				// ****************************************************************************************************************************************	//
				//	Functions																																//
				//	convertVersionSpecificIfcGeometricRepresentationItem, convertIfcSectionedSpine, convertStyledItem, convertOpenings, subtractOpenings	//
				// ****************************************************************************************************************************************	//

				/*!
				 * \internal TODO
				 *
				 * The function is not refactored.
				 */
				// Function 2:  Convert IfcSectionedSpine,
				void convertIfcSectionedSpine(
					const EXPRESSReference<typename IfcEntityTypesT::IfcSectionedSpine>& spine,
					const carve::math::Matrix& pos,
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					/*
					const EXPRESSReference<typename IfcEntityTypesT::IfcCompositeCurve> spine_curve = spine->SpineCurve;
					if(!spine_curve) {
						return;
					}
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>> vec_cross_sections;
					vec_cross_sections.resize(spine->CrossSections.size());
					std::transform(spine->CrossSections.begin(), spine->CrossSections.end(), vec_cross_sections.begin(), [](auto &it) { return it.lock(); });

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>> vec_cross_section_positions;
					vec_cross_section_positions.resize(spine->CrossSectionPositions.size());
					std::transform(spine->CrossSectionPositions.begin(), spine->CrossSectionPositions.end(), vec_cross_section_positions.begin(), [](auto &it) { return it.lock(); });

					typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>>::iterator it_cross_sections;

					unsigned int num_cross_sections = vec_cross_sections.size();
					if(vec_cross_section_positions.size() < num_cross_sections) {
						num_cross_sections = vec_cross_section_positions.size();
					}

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment>> segments;
					segments.resize(spine_curve->Segments.size());
					std::transform(spine_curve->Segments.begin(), spine_curve->Segments.end(), segments.begin(), [](auto &it) { return it.lock(); });
					int num_segments = segments.size();
					if(vec_cross_section_positions.size() < num_segments + 1) {
						num_segments = vec_cross_section_positions.size() - 1;
					}

					std::vector<carve::geom::vector<3>> curve_polygon;
					std::vector<carve::geom::vector<3>> segment_start_points;

					curveConverter->convertIfcCurve(spine_curve, curve_polygon, segment_start_points);
					*/
#ifdef _DEBUG
					std::cout << "Warning\t| IfcSectionedSpine not implemented." << std::endl;
#endif
				}

				/*!
				 * \internal TODO
				 *
				 * The function is not implemented.
				 */
				void convertIfcStyledItem(
					const EXPRESSReference<typename IfcEntityTypesT::IfcStyledItem>& styledItem, 
					std::shared_ptr<ItemData>& itemData
				) const throw(...)
				{
					throw oip::UnhandledException( styledItem );

					// code left here for reference, for the future poor soul taking care of styled items
					//std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem>>& StyledByItem_inverse_vec = representation_item->StyledByItem_inverse;
					//for(unsigned int i = 0; i < StyledByItem_inverse_vec.size(); ++i) {
					//	std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item_weak = StyledByItem_inverse_vec[i];
					//	std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item = std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem>(styled_item_weak);
					//}
				}

				/*!
				 * \internal TODO
				 *
				 * The function is not refactored.
				 */
				// Function 4: Convert openings.
				void convertOpenings(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcElement>& ifcElement,
					std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& vecOpeningData)
				{
					//	std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcRelVoidsElement>> vec_rel_voids(
					//		ifcElement->HasOpenings_inverse);
					//	if (vec_rel_voids.size() == 0)
					//	{
					//		return;
					//	}
					//	const int product_id = ifcElement->getId();
					//	const double length_factor = UnitConvert()->getLengthInMeterFactor();
					//
					//	// convert opening representation
					//	for (int i_void = 0; i_void<vec_rel_voids.size(); ++i_void)
					//	{
					//		std::weak_ptr<typename IfcEntityTypesT::IfcRelVoidsElement>& rel_voids_weak = vec_rel_voids[i_void];
					//		if (rel_voids_weak.expired())
					//		{
					//			continue;
					//		}
					//		std::shared_ptr<typename IfcEntityTypesT::IfcRelVoidsElement> rel_voids(rel_voids_weak);
					//		std::shared_ptr<typename IfcEntityTypesT::IfcFeatureElementSubtraction> opening = rel_voids->RelatedOpeningElement;
					//		if (!opening)
					//		{
					//			continue;
					//		}
					//		if (!opening->Representation)
					//		{
					//			continue;
					//		}
					//
					//		const int opening_id = opening->getId();
					//
					//		// opening can have its own relative placement
					//		std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> opening_placement = opening->ObjectPlacement;			//optional
					//		carve::math::Matrix opening_placement_matrix(carve::math::Matrix::IDENT());
					//		if (opening_placement)
					//		{
					//			std::set<int> opening_placements_applied;
					//			PlacementConverterT<IfcEntityTypesT>::convertIfcObjectPlacement(opening_placement,
					//				opening_placement_matrix, length_factor, opening_placements_applied);
					//		}
					//
					//		std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>>& vec_opening_representations =
					//			opening->Representation->Representations;
					//
					//		for (typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>>::iterator
					//			it_representations = vec_opening_representations.begin();
					//			it_representations != vec_opening_representations.end(); ++it_representations)
					//		{
					//			std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation> ifc_opening_representation = (*it_representations);
					//			std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> opening_representation_data(new ShapeInputDataT<IfcEntityTypesT>());
					//
					//			opening_representation_data->representation = ifc_opening_representation;
					//
					//			// TODO: Representation caching, one element could be used for several openings
					//			convertIfcRepresentation(ifc_opening_representation, opening_placement_matrix,
					//				opening_representation_data, err);
					//
					//
					//			vecOpeningData.push_back(opening_representation_data);
					//		}
					//	}
				}

				/*!
				 * \internal TODO
				 *
				 * The function is not refactored.
				 */
				// Function 5: Subtract openings.
				void subtractOpenings(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcElement>& ifcElement,
					std::shared_ptr<ItemData>& itemData,
					std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& vecOpeningData)
				{
					const int product_id = ifcElement->getId();

					// now go through all meshsets of the item
					for(int i_product_meshset = 0; i_product_meshset < itemData->meshsets.size(); ++i_product_meshset) {
						std::shared_ptr<carve::mesh::MeshSet<3>>& product_meshset = itemData->meshsets[i_product_meshset];
						std::stringstream strs_meshset_err;

						bool product_meshset_valid_for_csg = GeomUtils::checkMeshSet(product_meshset.get(), strs_meshset_err, product_id);
						if(!product_meshset_valid_for_csg) {
							continue;
						}

						for(int i_opening = 0; i_opening < vecOpeningData.size(); ++i_opening) {
							std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& opening_representation_data = vecOpeningData[i_opening];
							int representation_id = -1;
							if(opening_representation_data->representation) {
								representation_id = opening_representation_data->representation->getId();
							}

							std::vector<std::shared_ptr<ItemData>>& vec_opening_items = opening_representation_data->vec_item_data;

							for(int i_item = 0; i_item < vec_opening_items.size(); ++i_item) {
								std::shared_ptr<ItemData>& opening_item_data = vec_opening_items[i_item];
								opening_item_data->createMeshSetsFromClosedPolyhedrons();

								std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>::iterator it_opening_meshsets = opening_item_data->meshsets.begin();

								for(; it_opening_meshsets != opening_item_data->meshsets.end(); ++it_opening_meshsets) {
									std::shared_ptr<carve::mesh::MeshSet<3>> opening_meshset = (*it_opening_meshsets);

									// try to cut out the opening elements
									// due to rounding errors carve is not always capable of finding a solution
									// for the CSG subtraction
									// so enlarge the opening element

									// to do so, first compute center of object
									carve::geom::vector<3> center;
									center.setZero();

									const uint16_t numVertices = opening_meshset->vertex_storage.size();

									for(size_t i = 0; i < numVertices; ++i) {
										center += opening_meshset->vertex_storage[i].v;
									}

									center /= numVertices;

									double volume = 0.0;

									for(const auto& mesh : opening_meshset->meshes) {
										volume += mesh->volume();
									}

									// std::cout << "volume = " << volume << std::endl;

									const double enlargeFactor = volume / 3000.0f;

									for(size_t i = 0; i < numVertices; ++i) {
										carve::geom::vector<3>& v = opening_meshset->vertex_storage[i].v;

										carve::geom::vector<3> dir = v - center;
										dir.normalize();
										v += enlargeFactor * dir;
									}

									for(size_t i = 0; i < opening_meshset->meshes.size(); ++i) {
										opening_meshset->meshes[i]->recalc();
									}

									// do the subtraction
									std::shared_ptr<carve::mesh::MeshSet<3>> result;
									bool csg_op_ok =
										solidConverter->computeCSG(product_meshset.get(), opening_meshset.get(), carve::csg::CSG::A_MINUS_B, product_id, representation_id, result);

									if(!result || !csg_op_ok) {
										BLUE_LOG(error) << "Error: Subtraction of opening elements #" << ifcElement->getId() << " failed";
										continue;
									}

									if(csg_op_ok) {
										product_meshset = result;
									}
								}
							}
						}
					}
				}

				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>>& getPlacementConverter()
				{
					return placementConverter;
				}
				std::shared_ptr<SolidModelConverterT<IfcEntityTypesT>>& getSolidConverter()
				{
					return solidConverter;
				}
				std::shared_ptr<ProfileCacheT<IfcEntityTypesT>>& getProfileCache()
				{
					return profileCache;
				}
				bool handleLayerAssignments()
				{
					return handle_layer_assignments;
				}
				void setHandleLayerAssignments(bool handle)
				{
					handle_layer_assignments = handle;
				}
				bool handleStyledItems()
				{
					return handle_styled_items;
				}
				void setHandleStyledItems(bool handle)
				{
					handle_styled_items = handle;
				}

			protected:

				std::shared_ptr<GeoreferencingConverterT<IfcEntityTypesT>> georeferencingConverter_;

				// std::shared_ptr<StylesConverter>	stylesConverter;
				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;
				std::shared_ptr<CurveConverterT<IfcEntityTypesT>> curveConverter;
				std::shared_ptr<SolidModelConverterT<IfcEntityTypesT>> solidConverter;
				std::shared_ptr<FaceConverterT<IfcEntityTypesT>> faceConverter;
				std::shared_ptr<ProfileCacheT<IfcEntityTypesT>> profileCache;

				bool handle_styled_items;
				bool handle_layer_assignments;

			}; // end class RepresentationConverterT

		} // namespace IfcGeometryConverter
	} // namespace Core
} // namespace OpenInfraPlatform

#endif
