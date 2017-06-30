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

#include <set>
#include <sstream>
#include <memory>

#include "CarveHeaders.h"
//#include "ReaderSettings.h"

#include "EMTIfc4EntityTypes.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Model.h"

#include "ProfileCache.h"
#include "ProfileConverter.h"
#include "FaceConverter.h"
#include "CurveConverter.h"
#include "SolidModelConverter.h"
#include "PlacementConverter.h"
#include "GeometrySettings.h"
#include "GeomUtils.h"

/**********************************************************************************************/

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT,
			class IfcUnitConverterT,
			class IfcEntityT
		>
		class RepresentationConverterT
		{
		public:
			RepresentationConverterT(std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<IfcUnitConverterT> unitConverter)
				: 
			m_geomSettings(geomSettings), 
			m_unitConverter(unitConverter)
			{
				m_handle_styled_items = true;
				m_handle_layer_assignments = true;

				//m_styles_converter = shared_ptr<StylesConverter>( new StylesConverter() );
				m_profileCache = std::make_shared<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>>(m_geomSettings, m_unitConverter);
				
				m_curveConverter = std::make_shared<CurveConverterT<IfcEntityTypesT, IfcUnitConverterT>>(m_geomSettings, m_unitConverter);
				
				m_faceConverter = std::make_shared<FaceConverterT<IfcEntityTypesT, IfcUnitConverterT>>(m_geomSettings, m_unitConverter,
				                                                                                       m_curveConverter);

				m_solidConverter = std::make_shared<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>>(m_geomSettings, m_unitConverter,
				                                                                                                          m_curveConverter, m_faceConverter, m_profileCache);
			}

			~RepresentationConverterT()
			{

			}

			void convertIfcRepresentation(
				const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>& representation,
				const carve::math::Matrix& objectPlacement,
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& inputData,
				std::stringstream& err)
			{
				double length_factor = m_unitConverter->getLengthInMeterFactor();

				/*std::set<int> context_applied;
				carve::math::Matrix world_coord_system( carve::math::Matrix::IDENT() );
				shared_ptr<typename IfcEntityTypesT::IfcRepresentationContext>& context = representation->m_ContextOfItems;
				PlacementConverterT<IfcEntityTypesT>::getWorldCoordinateSystem( context, world_coord_system, length_factor, context_applied );
				carve::math::Matrix world_placement = objectPlacement*world_coord_system;*/

				typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem>>::iterator it_representation_items;

				for (it_representation_items = representation->m_Items.begin();
					it_representation_items != representation->m_Items.end(); ++it_representation_items)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem>& representation_item = (*it_representation_items);
					std::shared_ptr<ItemData> itemData(new ItemData());
					inputData->vec_item_data.push_back(itemData);

					/*if (m_handle_styled_items)
					{
						convertStyledItem(representation_item, itemData);
					}*/

					//ENTITY IfcRepresentationItem  ABSTRACT SUPERTYPE OF(ONEOF(IfcGeometricRepresentationItem, IfcMappedItem, IfcStyledItem, IfcTopologicalRepresentationItem));
					std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem> geom_item =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(representation_item);

					if (geom_item)
					{
						convertIfcGeometricRepresentationItem(geom_item, objectPlacement, itemData, err);
						continue;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcMappedItem> mapped_item =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcMappedItem>(representation_item);
					if (mapped_item)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationMap> map_source = mapped_item->m_MappingSource;

						if (!map_source)
						{
							err << "unhandled representation: #" << representation_item->getId()
								<< " = " << representation_item->classname() << std::endl;
							continue;
						}
						std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation> mapped_representation =
							map_source->m_MappedRepresentation;
						if (!mapped_representation)
						{
							err << "unhandled representation: #" << representation_item->getId()
								<< " = " << representation_item->classname() << std::endl;
							continue;
						}

						carve::math::Matrix map_matrix_target(carve::math::Matrix::IDENT());
						if (mapped_item->m_MappingTarget)
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator> transform_operator =
								mapped_item->m_MappingTarget;

							PlacementConverterT<IfcEntityTypesT>::convertTransformationOperator(transform_operator,
								map_matrix_target,
								length_factor);
						}

						carve::math::Matrix map_matrix_origin(carve::math::Matrix::IDENT());
						if (map_source->m_MappingOrigin)
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement> mapping_origin = map_source->m_MappingOrigin;
							std::shared_ptr<typename IfcEntityTypesT::IfcPlacement> mapping_origin_placement =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(mapping_origin);

							if (mapping_origin_placement)
							{
								PlacementConverterT<IfcEntityTypesT>::convertIfcPlacement(mapping_origin_placement,
									map_matrix_origin,
									length_factor);
							}
							else
							{
								err << "#" << mapping_origin_placement->getId()
									<< " = IfcPlacement: !dynamic_pointer_cast<IfcPlacement>( mapping_origin ) )";
								continue;
							}
						}

						carve::math::Matrix mapped_pos(
							(map_matrix_origin * objectPlacement) * map_matrix_target);

						convertIfcRepresentation(mapped_representation, mapped_pos, inputData, err);
						continue;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcStyledItem>(representation_item);
					if (styled_item)
					{
						continue;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcTopologicalRepresentationItem> topo_item =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcTopologicalRepresentationItem>(representation_item);
					if (topo_item)
					{
						//IfcTopologicalRepresentationItem 		ABSTRACT SUPERTYPE OF(ONEOF(IfcConnectedFaceSet, IfcEdge, IfcFace, IfcFaceBound, IfcLoop, IfcPath, IfcVertex))
						std::shared_ptr<typename IfcEntityTypesT::IfcConnectedFaceSet> topo_connected_face_set =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcConnectedFaceSet>(topo_item);
						if (topo_connected_face_set)
						{
							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcEdge> topo_edge =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdge>(topo_item);
						if (topo_edge)
						{
							std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());
							polyline_data->beginPolyline();
							std::shared_ptr<typename IfcEntityTypesT::IfcVertex>& vertex_start = topo_edge->m_EdgeStart;

							std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_start_point =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_start);

							if (vertex_start_point)
							{
								if (vertex_start_point->m_VertexGeometry)
								{
									std::shared_ptr<typename IfcEntityTypesT::IfcPoint> edge_start_point_geometry =
										vertex_start_point->m_VertexGeometry;

									std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_point =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(edge_start_point_geometry);
									if (ifc_point)
									{
										if (ifc_point->m_Coordinates.size() > 2)
										{
											carve::geom::vector<3> point =
												carve::geom::VECTOR(ifc_point->m_Coordinates[0]->m_value*length_factor,
												ifc_point->m_Coordinates[1]->m_value*length_factor,
												ifc_point->m_Coordinates[2]->m_value*length_factor);

											polyline_data->addVertex(objectPlacement * point);
											polyline_data->addPolylineIndex(0);
										}
									}
								}
							}

							std::shared_ptr<typename IfcEntityTypesT::IfcVertex>& vertex_end = topo_edge->m_EdgeEnd;

							std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> vertex_end_point =
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(vertex_end);
							if (vertex_end_point)
							{
								if (vertex_end_point->m_VertexGeometry)
								{
									std::shared_ptr<typename IfcEntityTypesT::IfcPoint> edge_point_geometry =
										vertex_end_point->m_VertexGeometry;
									std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_point =
										dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(edge_point_geometry);
									if (ifc_point)
									{
										if (ifc_point->m_Coordinates.size() > 2)
										{
											carve::geom::vector<3> point =
												carve::geom::VECTOR(ifc_point->m_Coordinates[0]->m_value*length_factor,
												ifc_point->m_Coordinates[1]->m_value*length_factor,
												ifc_point->m_Coordinates[2]->m_value*length_factor);

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

					err << "unhandled representation: #" << representation_item->getId()
						<< " = " << representation_item->classname() << std::endl;
				}

				if (m_handle_layer_assignments)
				{
					std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment>>& LayerAssignments_inverse =
						representation->m_LayerAssignments_inverse;

					typename std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment>>::iterator it_LayerAssignments_inverse;
					for (it_LayerAssignments_inverse = LayerAssignments_inverse.begin();
						it_LayerAssignments_inverse != LayerAssignments_inverse.end();
						++it_LayerAssignments_inverse)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcPresentationLayerAssignment> layer_assignment((*it_LayerAssignments_inverse));

						std::shared_ptr<typename IfcEntityTypesT::IfcPresentationLayerWithStyle> layer_assignment_with_style =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcPresentationLayerWithStyle>(layer_assignment);
						if (layer_assignment_with_style)
						{
							// deactivated by now due to compability issues
							/*std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcPresentationStyleSelect> >& vec_presentation_styles = layer_assignment_with_style->m_LayerStyles;
							for (int i = 0; i<vec_presentation_styles.size(); ++i)
							{
								std::shared_ptr<typename IfcEntityTypesT::IfcPresentationStyleSelect>&  presentation_style = vec_presentation_styles[i];
							}*/
						}
					}
				}
			}

			void convertIfcGeometricRepresentationItem(
				const std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem>& geomItem,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				std::stringstream& err)
			{
				//ENTITY IfcGeometricRepresentationItem
				//ABSTRACT SUPERTYPE OF(ONEOF(
				//	IfcAnnotationFillArea, IfcBooleanResult, IfcBoundingBox, IfcCartesianTransformationOperator, IfcCompositeCurveSegment, IfcCsgPrimitive3D,
				//	IfcCurve, IfcDefinedSymbol, IfcDirection, IfcFaceBasedSurfaceModel, IfcFillAreaStyleHatching, IfcFillAreaStyleTiles, IfcFillAreaStyleTileSymbolWithStyle,
				//	IfcGeometricSet, IfcHalfSpaceSolid, IfcLightSource, IfcOneDirectionRepeatFactor, IfcPlacement, IfcPlanarExtent, IfcPoint, IfcSectionedSpine,
				//	IfcShellBasedSurfaceModel, IfcSolidModel, IfcSurface, IfcTextLiteral, IfcTextureCoordinate, IfcTextureVertex, IfcVector))

				std::shared_ptr<typename IfcEntityTypesT::IfcBoundingBox> bbox =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundingBox>(geomItem);
				if (bbox)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> corner = bbox->m_Corner;
					std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> x_dim = bbox->m_XDim;
					std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> y_dim = bbox->m_YDim;
					std::shared_ptr<typename IfcEntityTypesT::IfcPositiveLengthMeasure> z_dim = bbox->m_ZDim;
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel> surface_model =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcFaceBasedSurfaceModel>(geomItem);
				if (surface_model)
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcConnectedFaceSet> >& vec_face_sets = surface_model->m_FbsmFaces;
					typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcConnectedFaceSet> >::iterator it_face_sets;

					for (it_face_sets = vec_face_sets.begin(); it_face_sets != vec_face_sets.end(); ++it_face_sets)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcConnectedFaceSet> face_set = (*it_face_sets);
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>>& vec_ifc_faces = face_set->m_CfsFaces;

						std::shared_ptr<ItemData> input_data_face_set(new ItemData);
						try {
							m_faceConverter->convertIfcFaceList(vec_ifc_faces, pos,
								input_data_face_set, err);
						}
						catch (...)
						{
							//return;
						}
						std::copy(input_data_face_set->open_or_closed_polyhedrons.begin(),
							input_data_face_set->open_or_closed_polyhedrons.end(),
							std::back_inserter(itemData->open_polyhedrons));
					}

					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcBooleanResult> boolean_result = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcBooleanResult>(geomItem);
				if (boolean_result)
				{
					try {
						m_solidConverter->convertIfcBooleanResult(boolean_result, pos, itemData, err);
					}
					catch (...)
					{
						std::cout << "Warning:\t| Boolean operand could not be used correctly!\n";
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcSolidModel> solid_model = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcSolidModel>(geomItem);
				if (solid_model)
				{
					m_solidConverter->convertIfcSolidModel(solid_model, pos, itemData, err);
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> curve = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurve>(geomItem);
				if (curve)
				{
					std::vector<carve::geom::vector<3>> loops;
					std::vector<carve::geom::vector<3>> segment_start_points;
					m_curveConverter->convertIfcCurve(curve, loops, segment_start_points);

					std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());
					polylineData->beginPolyline();
					for (int i = 0; i < loops.size(); ++i)
					{
						carve::geom::vector<3> point = loops.at(i);
						polylineData->addVertex(pos * point);
						polylineData->addPolylineIndex(i);
					}
					itemData->polylines.push_back(polylineData);

					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcShellBasedSurfaceModel> shell_based_surface_model = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcShellBasedSurfaceModel>(geomItem);
				if (shell_based_surface_model)
				{
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcShell> >& vec_shells = shell_based_surface_model->m_SbsmBoundary;
					for (typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcShell> >::iterator it_shells = vec_shells.begin(); it_shells != vec_shells.end(); ++it_shells)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcShell> shell_select = (*it_shells);
						if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcClosedShell>(shell_select))
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcClosedShell> closed_shell = 
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcClosedShell>(shell_select);
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace>>& vec_ifc_faces = closed_shell->m_CfsFaces;

							std::shared_ptr<ItemData> input_data(new ItemData());

							try
							{
								m_faceConverter->convertIfcFaceList(vec_ifc_faces, pos, input_data, err);
							}
							catch (...)
							{
								std::cout << "TEST ERROR" << std::endl << std::flush;
								//return;
							}
							std::copy(input_data->open_or_closed_polyhedrons.begin(), input_data->open_or_closed_polyhedrons.end(), std::back_inserter(itemData->closed_polyhedrons));
						}
						else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcOpenShell>(shell_select))
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcOpenShell> open_shell = 
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcOpenShell>(shell_select);
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcFace> >& vec_ifc_faces = open_shell->m_CfsFaces;

							std::shared_ptr<ItemData> input_data(new ItemData());


							try
							{
								//m_faceConverter->convertIfcFaceList(vec_ifc_faces, pos, input_data, err);
							}
							catch (...)
							{
								std::cout << "TEST ERROR" << std::endl << std::flush;
								//return;
							}


							std::copy(input_data->open_or_closed_polyhedrons.begin(), input_data->open_or_closed_polyhedrons.end(), std::back_inserter(itemData->open_polyhedrons));

						}
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcSurface> surface = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurface>(geomItem);
				if (surface)
				{
					std::shared_ptr<carve::input::PolylineSetData> polyline(new carve::input::PolylineSetData());
					m_faceConverter->convertIfcSurface(surface, pos, polyline);
					if (polyline->getVertexCount() > 1)
					{
						itemData->polylines.push_back(polyline);
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> poly_line = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(geomItem);
				if (poly_line)
				{
					std::vector<carve::geom::vector<3>> poly_vertices;
					m_curveConverter->convertIfcPolyline(poly_line, poly_vertices);

					const unsigned int num_points = poly_vertices.size();
					std::shared_ptr<carve::input::PolylineSetData> polyline_data(new carve::input::PolylineSetData());

					polyline_data->beginPolyline();

					// apply position
					for (unsigned int i = 0; i<num_points; ++i)
					{
						carve::geom::vector<3>& vertex = poly_vertices.at(i);
						vertex = pos*vertex;

						polyline_data->addVertex(vertex);
						polyline_data->addPolylineIndex(i);
					}
					itemData->polylines.push_back(polyline_data);

					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcGeometricSet> geometric_set = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricSet>(geomItem);
				if (geometric_set)
				{
					// ENTITY IfcGeometricSet SUPERTYPE OF(IfcGeometricCurveSet)
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcGeometricSetSelect> >& geom_set_elements =
						geometric_set->m_Elements;
					typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcGeometricSetSelect> >::iterator it_set_elements;
					for (it_set_elements = geom_set_elements.begin();
						it_set_elements != geom_set_elements.end();
						++it_set_elements)
					{
						// TYPE IfcGeometricSetSelect = SELECT (IfcPoint, IfcCurve, IfcSurface);
						std::shared_ptr<typename IfcEntityTypesT::IfcGeometricSetSelect>& geom_select = (*it_set_elements);

						std::shared_ptr<typename IfcEntityTypesT::IfcPoint> select_point = 
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcPoint>(geom_select);
						if (select_point)
						{
#ifdef _DEBUG
							std::cout << "Warning\t| IfcPoint not implemented" << std::endl;
#endif
							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> select_curve =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcCurve>(geom_select);
						if (select_curve)
						{
#ifdef _DEBUG
							std::cout << "Warning\t| IfcCurve not implemented" << std::endl;
#endif
							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcSurface> select_surface =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcSurface>(geom_select);
						if (select_surface)
						{
							std::shared_ptr<carve::input::PolylineSetData> polyline(new carve::input::PolylineSetData());
							m_faceConverter->convertIfcSurface(select_surface, pos, polyline);
							if (polyline->getVertexCount() > 1)
							{
								itemData->polylines.push_back(polyline);
							}

							continue;
						}
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcGeometricCurveSet> geometric_curve_set =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricCurveSet>(geometric_set);
					if (geometric_curve_set)
					{
#ifdef _DEBUG
						std::cout << "Warning\t| IfcGeometricCurveSet not implemented" << std::endl;
#endif
						return;
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcSectionedSpine> sectioned_spine =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcSectionedSpine>(geomItem);
				if (sectioned_spine)
				{
					convertIfcSectionedSpine(sectioned_spine, pos, itemData, err);
					return;
				}

				if (convertVersionSpecificIfcGeometricRepresentationItem(geomItem, pos, itemData, err))
				{
					return;
				}

				err << "Unhandled IFC Representation: #" << geomItem->getId()
					<< "=" << geomItem->classname() << std::endl;
			}

			bool convertVersionSpecificIfcGeometricRepresentationItem(
				const std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem>& geomItem,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				std::stringstream& err)
			{
#ifdef _DEBUG
				std::cout << "Warning\t| Could not find other version specific geometric representations" << std::endl;
#endif
				return false;
			}

			void convertIfcSectionedSpine(const std::shared_ptr<typename IfcEntityTypesT::IfcSectionedSpine>& spine,
				const carve::math::Matrix& pos,
				std::shared_ptr<ItemData> itemData,
				std::stringstream& err)
			{
				const std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurve> spine_curve = spine->m_SpineCurve;
				if (!spine_curve)
				{
					return;
				}
				const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> >& vec_cross_sections = spine->m_CrossSections;
				const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> >& vec_cross_section_positions = spine->m_CrossSectionPositions;

				typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> >::iterator it_cross_sections;

				unsigned int num_cross_sections = vec_cross_sections.size();
				if (vec_cross_section_positions.size() < num_cross_sections)
				{
					num_cross_sections = vec_cross_section_positions.size();
				}

				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> > segements = spine_curve->m_Segments;
				int num_segments = segements.size();
				if (vec_cross_section_positions.size() < num_segments + 1)
				{
					num_segments = vec_cross_section_positions.size() - 1;
				}

				std::vector<carve::geom::vector<3>> curve_polygon;
				std::vector<carve::geom::vector<3>> segment_start_points;

				m_curveConverter->convertIfcCurve(spine_curve, curve_polygon, segment_start_points);
#ifdef _DEBUG
				std::cout << "Warning\t| IfcSectionedSpine not implemented." << std::endl;
#endif
			}

			//void convertIfcPropertySet(	const std::shared_ptr<IfcPropertySet>& property_set,	osg::Group* group );
			
			void convertStyledItem(const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem>& representation_item,
				std::shared_ptr<ItemData>& itemData)
			{
				std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem>>&	StyledByItem_inverse_vec = 
					representation_item->m_StyledByItem_inverse;
				for (unsigned int i = 0; i<StyledByItem_inverse_vec.size(); ++i)
				{
					std::weak_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item_weak = StyledByItem_inverse_vec[i];
					std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem> styled_item = 
						std::shared_ptr<typename IfcEntityTypesT::IfcStyledItem>(styled_item_weak);
				}
			}

			void convertOpenings(const std::shared_ptr<typename IfcEntityTypesT::IfcElement>& ifcElement,
				std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> >& vecOpeningData,
				std::stringstream& err)
			{
				std::vector<std::weak_ptr<typename IfcEntityTypesT::IfcRelVoidsElement>> vec_rel_voids(
					ifcElement->m_HasOpenings_inverse);
				if (vec_rel_voids.size() == 0)
				{
					return;
				}
				const int product_id = ifcElement->getId();
				const double length_factor = m_unitConverter->getLengthInMeterFactor();

				// convert opening representation
				for (int i_void = 0; i_void<vec_rel_voids.size(); ++i_void)
				{
					std::weak_ptr<typename IfcEntityTypesT::IfcRelVoidsElement>& rel_voids_weak = vec_rel_voids[i_void];
					if (rel_voids_weak.expired())
					{
						continue;
					}
					std::shared_ptr<typename IfcEntityTypesT::IfcRelVoidsElement> rel_voids(rel_voids_weak);
					std::shared_ptr<typename IfcEntityTypesT::IfcFeatureElementSubtraction> opening = rel_voids->m_RelatedOpeningElement;
					if (!opening)
					{
						continue;
					}
					if (!opening->m_Representation)
					{
						continue;
					}

					const int opening_id = opening->getId();

					// opening can have its own relative placement
					std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> opening_placement = opening->m_ObjectPlacement;			//optional
					carve::math::Matrix opening_placement_matrix(carve::math::Matrix::IDENT());
					if (opening_placement)
					{
						std::set<int> opening_placements_applied;
						PlacementConverterT<IfcEntityTypesT>::convertIfcObjectPlacement(opening_placement,
							opening_placement_matrix, length_factor, opening_placements_applied);
					}

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>>& vec_opening_representations =
						opening->m_Representation->m_Representations;

					for (typename std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>>::iterator
						it_representations = vec_opening_representations.begin();
						it_representations != vec_opening_representations.end(); ++it_representations)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation> ifc_opening_representation = (*it_representations);
						std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> opening_representation_data(new ShapeInputDataT<IfcEntityTypesT>());

						opening_representation_data->representation = ifc_opening_representation;

						// TODO: Representation caching, one element could be used for several openings
						convertIfcRepresentation(ifc_opening_representation, opening_placement_matrix,
							opening_representation_data, err);


						vecOpeningData.push_back(opening_representation_data);
					}
				}
			}

			void subtractOpenings(const std::shared_ptr<typename IfcEntityTypesT::IfcElement>& ifcElement,
				std::shared_ptr<ItemData>& itemData,
				std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& vecOpeningData,
				std::stringstream& err)
			{
				const int product_id = ifcElement->getId();

				// now go through all meshsets of the item
				for (int i_product_meshset = 0;
					i_product_meshset < itemData->meshsets.size();
					++i_product_meshset)
				{
					std::shared_ptr<carve::mesh::MeshSet<3> >& product_meshset =
						itemData->meshsets[i_product_meshset];
					std::stringstream strs_meshset_err;


					bool product_meshset_valid_for_csg = GeomUtils::checkMeshSet(product_meshset.get(),
						strs_meshset_err,
						product_id);
					if (!product_meshset_valid_for_csg)
					{
						continue;
					}

					for (int i_opening = 0; i_opening < vecOpeningData.size(); ++i_opening)
					{
						std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>& opening_representation_data = vecOpeningData[i_opening];
						int representation_id = -1;
						if (opening_representation_data->representation)
						{
							representation_id = opening_representation_data->representation->getId();
						}

						std::vector<std::shared_ptr<ItemData> >& vec_opening_items =
							opening_representation_data->vec_item_data;

						for (int i_item = 0; i_item<vec_opening_items.size(); ++i_item)
						{
							std::shared_ptr<ItemData>& opening_item_data = vec_opening_items[i_item];
							opening_item_data->createMeshSetsFromClosedPolyhedrons();

							std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>::iterator it_opening_meshsets =
								opening_item_data->meshsets.begin();

							for (; it_opening_meshsets != opening_item_data->meshsets.end();
								++it_opening_meshsets)
							{
								std::shared_ptr<carve::mesh::MeshSet<3>> opening_meshset =
									(*it_opening_meshsets);

								// try to cut out the opening elements
								// due to rounding errors carve is not always capable of finding a solution
								// for the CSG subtraction
								// so enlarge the opening element 


								// to do so, first compute center of object
								carve::geom::vector<3> center;
								center.setZero();

								const uint16_t numVertices = opening_meshset->vertex_storage.size();

								for (size_t i = 0; i < numVertices; ++i)
								{
									center += opening_meshset->vertex_storage[i].v;
								}

								center /= numVertices;

								double volume = 0.0;

								for (const auto& mesh : opening_meshset->meshes)
								{
									volume += mesh->volume();
								}

								//std::cout << "volume = " << volume << std::endl;

								const double enlargeFactor = volume / 3000.0f;

								for (size_t i = 0; i < numVertices; ++i)
								{
									carve::geom::vector<3>& v = opening_meshset->vertex_storage[i].v;

									carve::geom::vector<3> dir = v - center;
									dir.normalize();
									v += enlargeFactor * dir;
								}

								for (size_t i = 0; i < opening_meshset->meshes.size(); ++i)
								{
									opening_meshset->meshes[i]->recalc();
								}

								// do the subtraction
								std::shared_ptr<carve::mesh::MeshSet<3>> result;
								bool csg_op_ok = m_solidConverter->computeCSG(product_meshset.get(),
									opening_meshset.get(),
									carve::csg::CSG::A_MINUS_B,
									product_id,
									representation_id, err,
									result);

								if (!result || !csg_op_ok)
								{
									err << "Error: Subtraction of opening elements #"
										<< ifcElement->getId() << " failed" << std::endl;
									continue;
								}

								if (csg_op_ok)
								{
									product_meshset = result;
								}
							}
						}
					}
				}
			}

			std::shared_ptr<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>>& getSolidConverter()
			{
				return m_solidConverter;
			}

			std::shared_ptr<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>>& getProfileCache() 
			{ 
				return m_profileCache; 
			}

			bool handleLayerAssignments() { return m_handle_layer_assignments; }

			void setHandleLayerAssignments(bool handle)
			{
				m_handle_layer_assignments = handle;
			}

			bool handleStyledItems() { return m_handle_styled_items; }
			void setHandleStyledItems(bool handle) { m_handle_styled_items = handle; }

		protected:
			std::shared_ptr<GeometrySettings> m_geomSettings;
			std::shared_ptr<IfcUnitConverterT> m_unitConverter;
			//std::shared_ptr<StylesConverter>	m_stylesConverter;
			std::shared_ptr<CurveConverterT<IfcEntityTypesT, IfcUnitConverterT>> m_curveConverter;
			std::shared_ptr<SolidModelConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>> m_solidConverter;
			std::shared_ptr<FaceConverterT<IfcEntityTypesT, IfcUnitConverterT>> m_faceConverter;
			std::shared_ptr<ProfileCacheT<IfcEntityTypesT, IfcUnitConverterT>> m_profileCache;

			bool m_handle_styled_items;
			bool m_handle_layer_assignments;

		};

		template <>
		inline bool RepresentationConverterT<emt::Ifc4EntityTypes, OpenInfraPlatform::Ifc4::UnitConverter,
		OpenInfraPlatform::Ifc4::Ifc4Entity>::convertVersionSpecificIfcGeometricRepresentationItem(
			const std::shared_ptr<emt::Ifc4EntityTypes::IfcGeometricRepresentationItem>& geomItem,
			const carve::math::Matrix& pos,
			std::shared_ptr<ItemData> itemData,
			std::stringstream& err)
		{
			const double lengthFactor = m_unitConverter->getLengthInMeterFactor();

			std::shared_ptr<emt::Ifc4EntityTypes::IfcTessellatedItem>  tessellatedItem =
				std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcTessellatedItem>(geomItem);

			if (tessellatedItem)
			{
				std::shared_ptr<emt::Ifc4EntityTypes::IfcTriangulatedFaceSet> faceSet =
					std::dynamic_pointer_cast<emt::Ifc4EntityTypes::IfcTriangulatedFaceSet>(tessellatedItem);

				if (faceSet)
				{
					std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());

					std::vector<std::vector<int>>& coordinatesIndices = faceSet->m_CoordIndex;
					std::vector<std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcLengthMeasure>>>& pointList = faceSet->m_Coordinates->m_CoordList;

					// obtain vertices from coordination list and add them to the new polygon
					for (const auto& point : pointList)
					{
						carve::geom::vector<3> vertex = 
							carve::geom::VECTOR(point[0]->m_value * lengthFactor, 
							point[1]->m_value * lengthFactor,
							point[2]->m_value * lengthFactor);

						// apply transformation
						vertex = pos * vertex;

						polygon->addVertex(vertex);
					}

					// read coordinates index list and create faces
					for (const std::vector<int>& indices : coordinatesIndices)
					{
						if (indices.size() < 3)
						{
							throw std::exception("invalid size of coordIndex of tessellated item.");
						}

						polygon->addFace(indices[0] - 1, indices[1] - 1, indices[2] - 1);
					}

					itemData->open_or_closed_polyhedrons.push_back(polygon);

					return true;
				}
			}

			return false;
		}
	}
}

#endif
