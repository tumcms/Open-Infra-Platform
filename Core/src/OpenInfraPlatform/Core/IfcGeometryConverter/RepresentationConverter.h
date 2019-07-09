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

#include "CurveConverter.h"
#include "FaceConverter.h"
#include "GeomUtils.h"
#include "GeometrySettings.h"
#include "PlacementConverter.h"
#include "ProfileCache.h"
#include "ProfileConverter.h"
#include "SolidModelConverter.h"

/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace IfcGeometryConverter {
		template <class IfcEntityTypesT, class IfcUnitConverterT>
		class RepresentationConverterT {
		public:
			RepresentationConverterT(std::shared_ptr<GeometrySettings> geomSettings, std::shared_ptr<IfcUnitConverterT> unitConverter)
			    : geomSettings(geomSettings), unitConverter(unitConverter) {
				handle_styled_items = true;
				handle_layer_assignments = true;

				// styles_converter = shared_ptr<StylesConverter>( new StylesConverter() );
				profileCache = std::make_shared<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>>(geomSettings, unitConverter);

				curveConverter = std::make_shared<CurveConverterT<IfcEntityTypesT, IfcUnitConverterT>>(geomSettings, unitConverter);

				faceConverter = std::make_shared<FaceConverterT<IfcEntityTypesT, IfcUnitConverterT>>(geomSettings, unitConverter, curveConverter);

				solidConverter =
				  std::make_shared<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT>>(geomSettings, unitConverter, curveConverter, faceConverter, profileCache);
			}

			~RepresentationConverterT() {
			}

			// *************************************************************************************************************************************************************//
			//	IfcRepresentationItem	(http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifcgeometricrepresentationitem.htm)		//
			//	ABSTRACT SUPERTYPE OF IfcGeometricRepresentationItem, IfcMappedItem, IfcStyledItem, IfcTopologicalRepresentationItem										//
			// *************************************************************************************************************************************************************//

			void convertIfcRepresentation(const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>& representation,
			                              const carve::math::Matrix& objectPlacement,
			                              std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& inputData,
			                              std::stringstream& err) {
				double length_factor = unitConverter->getLengthInMeterFactor();

				for (auto it_representation_items : representation->Items) {
					std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem>& representation_item = it_representation_items.lock();
					std::shared_ptr<ItemData> itemData(new ItemData());
					inputData->vec_item_data.push_back(itemData);

					// (1/4) IfcGeometricRepresenationItem SUBTYPE OF IfcRepresentationItem
					std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem> geom_item =
					  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(representation_item);
					if (geom_item) {
						convertIfcGeometricRepresentationItem(geom_item, objectPlacement, itemData, err);
						continue;
					}

					// (2/4) IfcMappedItem SUBTYPE OF IfcRepresentationItem
					std::shared_ptr<typename IfcEntityTypesT::IfcMappedItem> mapped_item = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcMappedItem>(representation_item);
					if (mapped_item) {
						// decltype(mapped_item->MappingSource)::type &map_source = mapped_item->MappingSource;
						auto& map_source = mapped_item->MappingSource;

						if (!map_source.lock()) {
							err << "unhandled representation: #" << representation_item->getId() << " = " << representation_item->classname() << std::endl;
							continue;
						}

						// decltype(map_source->Mapped_Representation)::type &mapped_representation = map_source->MappedRepresentation;
						auto& mapped_representation = map_source->MappedRepresentation;
						if (!mapped_representation.lock()) {
							err << "unhandled representation: #" << representation_item->getId() << " = " << representation_item->classname() << std::endl;
							continue;
						}

						carve::math::Matrix map_matrix_target(carve::math::Matrix::IDENT());
						if (mapped_item->MappingTarget) {
							auto& transform_operator = mapped_item->MappingTarget;

							PlacementConverterT<IfcEntityTypesT>::convertTransformationOperator(transform_operator.lock(), map_matrix_target, length_factor);
						}

						carve::math::Matrix map_matrix_origin(carve::math::Matrix::IDENT());
						typename IfcEntityTypesT::IfcAxis2Placement mapping_origin_select = map_source->MappingOrigin;

						std::shared_ptr<typename IfcEntityTypesT::IfcPlacement> mapping_origin_placement = nullptr;

						switch (mapping_origin_select.which()) {
						case 0: mapping_origin_placement = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(mapping_origin_select.get<0>().lock()); break;
						case 1: mapping_origin_placement = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(mapping_origin_select.get<1>().lock()); break;
						default: break;
						}

						if (mapping_origin_placement) {
							PlacementConverterT<IfcEntityTypesT>::convertIfcPlacement(mapping_origin_placement, map_matrix_origin, length_factor);
						} else {
							err << "#" << mapping_origin_placement->getId() << " = IfcPlacement: !std::dynamic_pointer_cast<IfcPlacement>( mapping_origin ) )";
							continue;
						}
						

						carve::math::Matrix mapped_pos((map_matrix_origin * objectPlacement) * map_matrix_target);

						convertIfcRepresentation(mapped_representation.lock(), mapped_pos, inputData, err);
						continue;
					}

					// (3/4) IfcStyledItem SUBTYPE OF IfcRepresentationItem
					std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcStyledItem>(representation_item);
					if (styled_item) {
						continue;
					}

					// (4/4) IfcTopologicalRepresentationItem SUBTYPE OF IfcRepresentationItem
					std::shared_ptr<typename IfcEntityTypesT::IfcTopologicalRepresentationItem> topo_item =
					  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcTopologicalRepresentationItem>(representation_item);
					if (topo_item) {
						// IfcTopologicalRepresentationItem ABSTRACT SUPERTYPE OF IfcConnectedFaceSet, IfcEdge, IfcFace*, IfcFaceBound*, IfcLoop*, IfcPath*, IfcVertex*.

						// IfcConnectedFaceSet SUBTYPE OF IfcTopologicalRepresentationItem
						std::shared_ptr<typename IfcEntityTypesT::IfcConnectedFaceSet> topo_connected_face_set =
						  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcConnectedFaceSet>(topo_item);
						if (topo_connected_face_set) {
							continue;
						}

						// IfcEdge SUBTYPE OF IfcTopologicalRepresentationItem
						std::shared_ptr<typename IfcEntityTypesT::IfcEdge> topo_edge = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdge>(topo_item);
						if (topo_edge) {
							std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());
							polyline_data->beginPolyline();

							// decltype(vertex_start = topo_edge->EdgeStart)::type& vertex_start = topo_edge->EdgeStart;
							auto& vertex_start = topo_edge->EdgeStart;

							std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_start_point =
							  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_start.lock());

							if (vertex_start_point) {
								if (vertex_start_point->VertexGeometry) {
									auto& edge_start_point_geometry = vertex_start_point->VertexGeometry;

									std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_point =
									  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(edge_start_point_geometry.lock());
									if (ifc_point) {
										if (ifc_point->Coordinates.size() > 2) {
											carve::geom::vector<3> point = carve::geom::VECTOR(ifc_point->Coordinates[0] * length_factor, ifc_point->Coordinates[1] * length_factor,
											                                                   ifc_point->Coordinates[2] * length_factor);

											polyline_data->addVertex(objectPlacement * point);
											polyline_data->addPolylineIndex(0);
										}
									}
								}
							}

							// decltype(topo_edge->EdgeEnd)::type& vertex_end = topo_edge->EdgeEnd;
							auto& vertex_end = topo_edge->EdgeEnd;
							std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_end_point =
							  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_end.lock());
							if (vertex_end_point) {
								if (vertex_end_point->VertexGeometry) {
									auto& edge_point_geometry = vertex_end_point->VertexGeometry;

									std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_point =
									  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(edge_point_geometry.lock());
									if (ifc_point) {
										if (ifc_point->Coordinates.size() > 2) {
											carve::geom::vector<3> point = carve::geom::VECTOR(ifc_point->Coordinates[0] * length_factor, ifc_point->Coordinates[1] * length_factor,
											                                                   ifc_point->Coordinates[2] * length_factor);

											polyline_data->addVertex(objectPlacement * point);
											polyline_data->addPolylineIndex(1);
										}
									}
								}
							}
							itemData->polylines.push_back(polyline_data);
							continue;
						}
					}
					err << "unhandled representation: #" << representation_item->getId() << " = " << representation_item->classname() << std::endl;
				}

				if (handle_layer_assignments) {
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

			// *********************************************************************************************************************************************************************//
			//	IfcGeometricRepresentationItem	 (http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifcgeometricrepresentationitem.htm)
			//// 	ABSTRACT SUPERTYPE OF IfcAnnotationFillArea, IfcBooleanResult, IfcBoundingBox, IfcCartesianTransformationOperator, IfcCompositeCurveSegment, IfcCsgPrimitive3D,
			//// 	IfcCurve, IfcDefinedSymbol, IfcDirection, IfcFaceBasedSurfaceModel, IfcFillAreaStyleHatching, IfcFillAreaStyleTiles, IfcFillAreaStyleTileSymbolWithStyle, //
			//	IfcGeometricSet, IfcHalfSpaceSolid, IfcLightSource, IfcOneDirectionRepeatFactor, IfcPlacement, IfcPlanarExtent, IfcPoint, IfcSectionedSpine, //
			//	IfcShellBasedSurfaceModel, IfcSolidModel, IfcSurface, IfcTextLiteral, IfcTextureCoordinate, IfcTextureVertex, IfcVector. //
			// *********************************************************************************************************************************************************************//

			void convertIfcGeometricRepresentationItem(const std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem>& geomItem,
			                                           const carve::math::Matrix& pos,
			                                           std::shared_ptr<ItemData> itemData,
			                                           std::stringstream& err) {
				// (1/9) IfcFaceBasedSurfaceModel SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel> surface_model =
				  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel>(geomItem);
				if (surface_model) {
					auto vec_face_sets = surface_model->FbsmFaces;

					for (auto& it_face_sets : vec_face_sets) {
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>> vec_ifc_faces;
						vec_ifc_faces.reserve(it_face_sets->CfsFaces.size());
						std::transform(it_face_sets->CfsFaces.begin(), it_face_sets->CfsFaces.end(), vec_ifc_faces.begin(), [](auto& it) { return it.lock(); });

						std::shared_ptr<ItemData> input_data_face_set(new ItemData);
						try {
							faceConverter->convertIfcFaceList(vec_ifc_faces, pos, input_data_face_set, err);
						} catch (...) {
							// return;
						}
						std::copy(input_data_face_set->open_or_closed_polyhedrons.begin(),
						          input_data_face_set->open_or_closed_polyhedrons.end(),
						          std::back_inserter(itemData->open_polyhedrons));
					}

					return;
				}

				// (2/9) IfcBooleanResult SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcBooleanResult> boolean_result = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBooleanResult>(geomItem);
				if (boolean_result) {
					try {
						solidConverter->convertIfcBooleanResult(boolean_result, pos, itemData, err);
					} catch (...) {
						std::cout << "Warning:\t| Boolean operand could not be used correctly!\n";
					}
					return;
				}

				// (3/9) IfcSolidModel SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcSolidModel> solid_model = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSolidModel>(geomItem);
				if (solid_model) {
					solidConverter->convertIfcSolidModel(solid_model, pos, itemData, err);
					return;
				}

				// (4/9) IfcCurve SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> curve = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurve>(geomItem);
				if (curve) {
					std::vector<carve::geom::vector<3>> loops;
					std::vector<carve::geom::vector<3>> segment_start_points;
					curveConverter->convertIfcCurve(curve, loops, segment_start_points);

					std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());
					polylineData->beginPolyline();
					for (int i = 0; i < loops.size(); ++i) {
						carve::geom::vector<3> point = loops.at(i);
						polylineData->addVertex(pos * point);
						polylineData->addPolylineIndex(i);
					}
					itemData->polylines.push_back(polylineData);

					return;
				}

				// (5/9) IfcShellBasedSurfaceModel SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcShellBasedSurfaceModel> shell_based_surface_model =
				  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcShellBasedSurfaceModel>(geomItem);
				if (shell_based_surface_model) {
					
					auto vec_shells = shell_based_surface_model->SbsmBoundary; 
					for (auto& it_shells : vec_shells) {
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>> vec_shells;
							std::shared_ptr<ItemData> input_data_shells_set(new ItemData);

							switch (it_shells.which()) {
							case 0:
								vec_shells.reserve(it_shells.get<0>()->CfsFaces.size());
								std::transform(it_shells.get<0>()->CfsFaces.begin(), it_shells.get<0>()->CfsFaces.end(), vec_shells.begin(), [](auto& it) {return it.lock(); });
								break;
							case 1:
								vec_shells.reserve(it_shells.get<1>()->CfsFaces.size());
								std::transform(it_shells.get<1>()->CfsFaces.begin(), it_shells.get<1>()->CfsFaces.end(), vec_shells.begin(), [](auto& it) {return it.lock(); });
								break;
							}

							try {
								faceConverter->convertIfcFaceList(vec_shells, pos, input_data_shells_set, err);
							}
							catch (...) {
								std::cout << "TEST ERROR" << std::endl << std::flush;
								// return;
							}
							std::copy(input_data_shells_set->open_or_closed_polyhedrons.begin(),
								input_data_shells_set->open_or_closed_polyhedrons.end(),
								std::back_inserter(itemData->closed_polyhedrons));
							
					}
					return;
				}

				// (6/9) IfcSurface SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcSurface> surface = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurface>(geomItem);
				if (surface) {
					std::shared_ptr<carve::input::PolylineSetData> polyline(new carve::input::PolylineSetData());
					faceConverter->convertIfcSurface(surface, pos, polyline);
					if (polyline->getVertexCount() > 1) {
						itemData->polylines.push_back(polyline);
					}
					return;
				}

				// (7/9) IfcPolyline SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> poly_line = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(geomItem);
				if (poly_line) {
					std::vector<carve::geom::vector<3>> poly_vertices;
					curveConverter->convertIfcPolyline(poly_line, poly_vertices);

					const unsigned int num_points = poly_vertices.size();
					std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());

					polyline_data->beginPolyline();

					// apply position
					for (unsigned int i = 0; i < num_points; ++i) {
						carve::geom::vector<3>& vertex = poly_vertices.at(i);
						vertex = pos * vertex;

						polyline_data->addVertex(vertex);
						polyline_data->addPolylineIndex(i);
					}
					itemData->polylines.push_back(polyline_data);

					return;
				}

				// (8/9) IfcGeometricSet SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcGeometricSet> geometric_set = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricSet>(geomItem);
				if (geometric_set) {
					// ENTITY IfcGeometricSet SUPERTYPE OF(IfcGeometricCurveSet)

					for (auto& it_set_elements : geometric_set->Elements) {
						// TYPE IfcGeometricSetSelect = SELECT (IfcPoint, IfcCurve, IfcSurface);
						std::shared_ptr<carve::input::PolylineSetData> polyline = nullptr;
						switch (it_set_elements.which()) {
						case 0: std::cout << "Warning\t| IfcCurve not implemented" << std::endl; break;
						case 1: std::cout << "Warning\t| IfcPoint not implemented" << std::endl; break;
						case 2:
							polyline = std::make_shared<carve::input::PolylineSetData>();
							faceConverter->convertIfcSurface(it_set_elements.get<2>().lock(), pos, polyline);
							if (polyline->getVertexCount() > 1) {
								itemData->polylines.push_back(polyline);
							}
							break;
						default: break;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcPoint> select_point =
						  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPoint>(it_set_elements.get<1>().lock());
						if (select_point) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcPoint not implemented" << std::endl;
#endif
							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> select_curve =
						  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurve>(it_set_elements.get<0>().lock());
						if (select_curve) {
#ifdef _DEBUG
							std::cout << "Warning\t| IfcCurve not implemented" << std::endl;
#endif
							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcSurface> select_surface =
						  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurface>(it_set_elements.get<2>().lock());
						if (select_surface) {
							std::shared_ptr<carve::input::PolylineSetData> polyline(new carve::input::PolylineSetData());
							faceConverter->convertIfcSurface(select_surface, pos, polyline);
							if (polyline->getVertexCount() > 1) {
								itemData->polylines.push_back(polyline);
							}

							continue;
						}
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcGeometricCurveSet> geometric_curve_set =
					  std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricCurveSet>(geometric_set);
					if (geometric_curve_set) {
#ifdef _DEBUG
						std::cout << "Warning\t| IfcGeometricCurveSet not implemented" << std::endl;
#endif
						return;
					}
					return;
				}

				// (9/9) IfcSectionedSpine SUBTYPE OF IfcGeometricRepresentationItem
				std::shared_ptr<typename IfcEntityTypesT::IfcSectionedSpine> sectioned_spine = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSectionedSpine>(geomItem);
				if (sectioned_spine) {
					convertIfcSectionedSpine(sectioned_spine, pos, itemData, err);
					return;
				}

				if (convertVersionSpecificIfcGeometricRepresentationItem(geomItem, pos, itemData, err)) {
					return;
				}
				err << "Unhandled IFC Representation: #" << geomItem->getId() << "=" << geomItem->classname() << std::endl;
			}

			// ****************************************************************************************************************************************	//
			//	Functions																																//
			//	convertVersionSpecificIfcGeometricRepresentationItem, convertIfcSectionedSpine, convertStyledItem, convertOpenings, subtractOpenings	//
			// ****************************************************************************************************************************************	//

			// Function 1:  Convert version specific IfcGeometricRepresentationItem,
			bool convertVersionSpecificIfcGeometricRepresentationItem(const std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem>& geomItem,
			                                                          const carve::math::Matrix& pos,
			                                                          std::shared_ptr<ItemData> itemData,
			                                                          std::stringstream& err) {
#ifdef _DEBUG
				std::cout << "Warning\t| Could not find other version specific geometric representations" << std::endl;
#endif
				return false;
			}

			// Function 2:  Convert IfcSectionedSpine,
			void convertIfcSectionedSpine(const std::shared_ptr<typename IfcEntityTypesT::IfcSectionedSpine>& spine,
			                              const carve::math::Matrix& pos,
			                              std::shared_ptr<ItemData> itemData,
			                              std::stringstream& err)
			{
				const std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurve> spine_curve = spine->SpineCurve.lock();
				if (!spine_curve) {
					return;
				}
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>> vec_cross_sections;
				vec_cross_sections.reserve(spine->CrossSections.size());
				std::transform(spine->CrossSections.begin(), spine->CrossSections.end(), vec_cross_sections.begin(), [](auto &it) { return it.lock(); });

				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>> vec_cross_section_positions;
				vec_cross_section_positions.reserve(spine->CrossSectionPositions.size());
				std::transform(spine->CrossSectionPositions.begin(), spine->CrossSectionPositions.end(), vec_cross_section_positions.begin(), [](auto &it) { return it.lock(); });

				typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef>>::iterator it_cross_sections;

				unsigned int num_cross_sections = vec_cross_sections.size();
				if (vec_cross_section_positions.size() < num_cross_sections) {
					num_cross_sections = vec_cross_section_positions.size();
				}

				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment>> segments;
				segments.reserve(spine_curve->Segments.size());
				std::transform(spine_curve->Segments.begin(), spine_curve->Segments.end(), segments.begin(), [](auto &it) { return it.lock(); });
				int num_segments = segments.size();
				if (vec_cross_section_positions.size() < num_segments + 1) {
					num_segments = vec_cross_section_positions.size() - 1;
				}

				std::vector<carve::geom::vector<3>> curve_polygon;
				std::vector<carve::geom::vector<3>> segment_start_points;

				curveConverter->convertIfcCurve(spine_curve, curve_polygon, segment_start_points);
#ifdef _DEBUG
				std::cout << "Warning\t| IfcSectionedSpine not implemented." << std::endl;
#endif
			}

			// Function 3: Convert IfcStyledItem.
			void convertStyledItem(const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem>& representation_item, std::shared_ptr<ItemData>& itemData) {
				std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem>>& StyledByItem_inverse_vec = representation_item->StyledByItem_inverse;
				for (unsigned int i = 0; i < StyledByItem_inverse_vec.size(); ++i) {
					std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item_weak = StyledByItem_inverse_vec[i];
					std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item = std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem>(styled_item_weak);
				}
			}

			// Function 4: Convert openings.
			void convertOpenings(const std::shared_ptr<typename IfcEntityTypesT::IfcElement>& ifcElement,
			                     std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& vecOpeningData,
			                     std::stringstream& err) {
				//	std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcRelVoidsElement>> vec_rel_voids(
				//		ifcElement->HasOpenings_inverse);
				//	if (vec_rel_voids.size() == 0)
				//	{
				//		return;
				//	}
				//	const int product_id = ifcElement->getId();
				//	const double length_factor = unitConverter->getLengthInMeterFactor();
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

			// Function 5: Subtract openings.
			void subtractOpenings(const std::shared_ptr<typename IfcEntityTypesT::IfcElement>& ifcElement,
			                      std::shared_ptr<ItemData>& itemData,
			                      std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& vecOpeningData,
			                      std::stringstream& err) {
				const int product_id = ifcElement->getId();

				// now go through all meshsets of the item
				for (int i_product_meshset = 0; i_product_meshset < itemData->meshsets.size(); ++i_product_meshset) {
					std::shared_ptr<carve::mesh::MeshSet<3>>& product_meshset = itemData->meshsets[i_product_meshset];
					std::stringstream strs_meshset_err;

					bool product_meshset_valid_for_csg = GeomUtils::checkMeshSet(product_meshset.get(), strs_meshset_err, product_id);
					if (!product_meshset_valid_for_csg) {
						continue;
					}

					for (int i_opening = 0; i_opening < vecOpeningData.size(); ++i_opening) {
						std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& opening_representation_data = vecOpeningData[i_opening];
						int representation_id = -1;
						if (opening_representation_data->representation) {
							representation_id = opening_representation_data->representation->getId();
						}

						std::vector<std::shared_ptr<ItemData>>& vec_opening_items = opening_representation_data->vec_item_data;

						for (int i_item = 0; i_item < vec_opening_items.size(); ++i_item) {
							std::shared_ptr<ItemData>& opening_item_data = vec_opening_items[i_item];
							opening_item_data->createMeshSetsFromClosedPolyhedrons();

							std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>::iterator it_opening_meshsets = opening_item_data->meshsets.begin();

							for (; it_opening_meshsets != opening_item_data->meshsets.end(); ++it_opening_meshsets) {
								std::shared_ptr<carve::mesh::MeshSet<3>> opening_meshset = (*it_opening_meshsets);

								// try to cut out the opening elements
								// due to rounding errors carve is not always capable of finding a solution
								// for the CSG subtraction
								// so enlarge the opening element

								// to do so, first compute center of object
								carve::geom::vector<3> center;
								center.setZero();

								const uint16_t numVertices = opening_meshset->vertex_storage.size();

								for (size_t i = 0; i < numVertices; ++i) {
									center += opening_meshset->vertex_storage[i].v;
								}

								center /= numVertices;

								double volume = 0.0;

								for (const auto& mesh : opening_meshset->meshes) {
									volume += mesh->volume();
								}

								// std::cout << "volume = " << volume << std::endl;

								const double enlargeFactor = volume / 3000.0f;

								for (size_t i = 0; i < numVertices; ++i) {
									carve::geom::vector<3>& v = opening_meshset->vertex_storage[i].v;

									carve::geom::vector<3> dir = v - center;
									dir.normalize();
									v += enlargeFactor * dir;
								}

								for (size_t i = 0; i < opening_meshset->meshes.size(); ++i) {
									opening_meshset->meshes[i]->recalc();
								}

								// do the subtraction
								std::shared_ptr<carve::mesh::MeshSet<3>> result;
								bool csg_op_ok =
								  solidConverter->computeCSG(product_meshset.get(), opening_meshset.get(), carve::csg::CSG::A_MINUS_B, product_id, representation_id, err, result);

								if (!result || !csg_op_ok) {
									err << "Error: Subtraction of opening elements #" << ifcElement->getId() << " failed" << std::endl;
									continue;
								}

								if (csg_op_ok) {
									product_meshset = result;
								}
							}
						}
					}
				}
			}

			std::shared_ptr<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT>>& getSolidConverter() {
				return solidConverter;
			}
			std::shared_ptr<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>>& getProfileCache() {
				return profileCache;
			}
			bool handleLayerAssignments() {
				return handle_layer_assignments;
			}
			void setHandleLayerAssignments(bool handle) {
				handle_layer_assignments = handle;
			}
			bool handleStyledItems() {
				return handle_styled_items;
			}
			void setHandleStyledItems(bool handle) {
				handle_styled_items = handle;
			}

		protected:
			std::shared_ptr<GeometrySettings> geomSettings;
			std::shared_ptr<IfcUnitConverterT> unitConverter;
			// std::shared_ptr<StylesConverter>	stylesConverter;
			std::shared_ptr<CurveConverterT<IfcEntityTypesT, IfcUnitConverterT>> curveConverter;
			std::shared_ptr<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT>> solidConverter;
			std::shared_ptr<FaceConverterT<IfcEntityTypesT, IfcUnitConverterT>> faceConverter;
			std::shared_ptr<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>> profileCache;

			bool handle_styled_items;
			bool handle_layer_assignments;

		}; // namespace IfcGeometryConverter
		   // template <>
		// inline bool RepresentationConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter,
		// OpenInfraPlatform::Ifc4::Ifc4Entity>::convertVersionSpecificIfcGeometricRepresentationItem(
		//	const std::shared_ptr<emt::Ifc4EntityTypes::IfcGeometricRepresentationItem>& geomItem,
		//	const carve::math::Matrix& pos,
		//	std::shared_ptr<ItemData> itemData,
		//	std::stringstream& err)
		//{
		//	const double lengthFactor = unitConverter->getLengthInMeterFactor();
		//
		//	std::shared_ptr<emt::Ifc4EntityTypes::IfcTessellatedItem>  tessellatedItem =
		//		std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcTessellatedItem>(geomItem);
		//
		//	if (tessellatedItem)
		//	{
		//		std::shared_ptr<emt::Ifc4EntityTypes::IfcTriangulatedFaceSet> faceSet =
		//			std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcTriangulatedFaceSet>(tessellatedItem);
		//
		//		if (faceSet)
		//		{
		//			std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
		//
		//			std::vector<std::vector<int>>& coordinatesIndices = faceSet->CoordIndex;
		//			std::vector<std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcLengthMeasure>>>& pointList = faceSet->Coordinates->CoordList;
		//
		//			// obtain vertices from coordination list and add them to the new polygon
		//			for (const auto& point : pointList)
		//			{
		//				carve::geom::vector<3> vertex =
		//					carve::geom::VECTOR(point[0] * lengthFactor,
		//					point[1] * lengthFactor,
		//					point[2] * lengthFactor);
		//
		//				// apply transformation
		//				vertex = pos * vertex;
		//
		//				polygon->addVertex(vertex);
		//			}
		//
		//			// read coordinates index list and create faces
		//			for (const std::vector<int>& indices : coordinatesIndices)
		//			{
		//				if (indices.size() < 3)
		//				{
		//					throw std::exception("invalid size of coordIndex of tessellated item.");
		//				}
		//
		//				polygon->addFace(indices[0] - 1, indices[1] - 1, indices[2] - 1);
		//			}
		//
		//			itemData->open_or_closed_polyhedrons.push_back(polygon);
		//
		//			return true;
		//		}
		//	}
		//
		//	return false;
		//}
	} // namespace IfcGeometryConverter
} // namespace OpenInfraPlatform

#endif
