/*
    Copyright (c) 2018 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// visual studio
#pragma once
// unix
#ifndef PLACEMENTCONVERTER_H
#define PLACEMENTCONVERTER_H

#include <math.h>
#include <set>
#include <memory>
#include "CarveHeaders.h"


/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {
			template <
				class IfcEntityTypesT
			>
				class PlacementConverterT {
				public:

					// **************************************************************************************************************************//
					//	IfcPlacement (http://www.buildingsmart-tech.org/ifc/IFC4x1/RC3/html/schema/ifcgeometryresource/lexical/ifcplacement.htm) //
					//	ABSTRACT SUPERTYPE OF IfcAxis1Placement, IfcAxis2Placement2D, IfcAxis2Placement3D										 //
					// **************************************************************************************************************************//

					static void convertIfcPlacement(
						const std::shared_ptr<typename IfcEntityTypesT::IfcPlacement> placement,
						carve::math::Matrix& matrix,
						double length_factor)
					{
						// (1/3) IfcAxis1Placement SUBTYPE OF IfcPlacement
						if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis1Placement>(placement)) {
							std::stringstream ss;
#ifdef _DEBUG
							ss << "Warning\t| IfcAxis1Placement not implemented ";
#endif
							throw std::runtime_error(ss.str().c_str());
						}

						// (2/3) IfcAxis2Placement2D SUBTYPE OF IfcPlacement 
						else if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement);
							convertIfcAxis2Placement2D(axis2placement2d, matrix, length_factor);
						}

						// (3/3) IfcAxis2Placement3D SUBTYPE OF IfcPlacement
						else if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement);
							convertIfcAxis2Placement3D(axis2placement3d, matrix, length_factor);
						}
						else {
							std::stringstream ss;
							ss << "Error\t| IfcPlacement is not IfcAxis2Placement2D or IfcAxis2Placement3D ";
							throw std::runtime_error(ss.str().c_str());
						}
					};

					// ********************************************************************************************************************************************************	//
					//	Functions																																				//
					//	convertIfcAxis2Placement2D, convertIfcAxis2Placement3D, convertIfcObjectPlacement, getWorldCoordinateSystem, convertTransformationOperator, getPlane.	//
					// ********************************************************************************************************************************************************	//

					// Function 1: Convert IfcAxis2Placement2D.
					static void convertIfcAxis2Placement2D(
						const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d,
						carve::math::Matrix& matrix,
						double length_factor)
					{

						carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
						carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

						// Location type IfcCartesianPoint 
						if(axis2placement2d->Location) {
							if(axis2placement2d->Location->Coordinates.size() > 1) {
								translate = carve::geom::VECTOR(axis2placement2d->Location->Coordinates[0] * length_factor, axis2placement2d->Location->Coordinates[1] * length_factor, 0.0);
							}
						}

						// Reference Direction type IfcDirection [OPTIONAL]
						if(axis2placement2d->RefDirection) {
							if(axis2placement2d->RefDirection->DirectionRatios.size() > 1) {
								ref_direction.x = axis2placement2d->RefDirection->DirectionRatios[0];
								ref_direction.y = axis2placement2d->RefDirection->DirectionRatios[1];
								ref_direction.z = 0;

								local_x = ref_direction;	//carve::geom::VECTOR(direction_ratios[0], direction_ratios[1], 0 );
								carve::geom::vector<3>  z_axis(carve::geom::VECTOR(0.0, 0.0, 1.0));
								local_y = carve::geom::cross(z_axis, local_x);	// ref_direction can be just in the x-z-plane, not perpendicular to y and z. so re-compute local x					
								local_x = carve::geom::cross(local_y, local_z);
							}
						}

						local_x.normalize();
						local_y.normalize();
						local_z.normalize();

						matrix = carve::math::Matrix(
							local_x.x, local_y.x, local_z.x, translate.x,
							local_x.y, local_y.y, local_z.y, translate.y,
							local_x.z, local_y.z, local_z.z, translate.z,
							0, 0, 0, 1);
					}

					// Function 2: Convert IfcAxis2Placement3D.
					static void convertIfcAxis2Placement3D(
						const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d,
						carve::math::Matrix& matrix,
						double length_factor)
					{
						carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
						carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

						// Location type IfcCartesianPoint
						if(axis2placement3d->Location) {
							//std::vector<carve::geom::vector<3>>
							/*Syntax?*/			auto& coords = axis2placement3d->Location->Coordinates; //Richtig

							if(coords.size() > 2) {
								translate = carve::geom::VECTOR(coords[0] * length_factor, coords[1] * length_factor, coords[2] * length_factor);
							}
							else if(coords.size() > 1) {
								translate = carve::geom::VECTOR(coords[0] * length_factor, coords[1] * length_factor, 0.0);
							}
						}

						// Axis type IfcDirection [OPTIONAL]
						if(axis2placement3d->Axis) {

							auto& axis = axis2placement3d->Axis->DirectionRatios; //Richtig


							if(axis.size() > 2) {
								local_z = carve::geom::VECTOR(axis[0], axis[1], axis[2]);
							}
						}

						// Reference Direction type IfcDirection [OPTIONAL]
						if(axis2placement3d->RefDirection) {
							if(axis2placement3d->RefDirection->DirectionRatios.size() > 2) {
								ref_direction.x = axis2placement3d->RefDirection->DirectionRatios[0];
								ref_direction.y = axis2placement3d->RefDirection->DirectionRatios[1];
								ref_direction.z = axis2placement3d->RefDirection->DirectionRatios[2];
							}
						}

						local_x = ref_direction;
						local_y = carve::geom::cross(local_z, local_x);	// ref_direction can be just in the x-z-plane, not perpendicular to y and z. so re-compute local x
						local_x = carve::geom::cross(local_y, local_z);

						local_x.normalize();
						local_y.normalize();
						local_z.normalize();

						matrix = carve::math::Matrix(
							local_x.x, local_y.x, local_z.x, translate.x,
							local_x.y, local_y.y, local_z.y, translate.y,
							local_x.z, local_y.z, local_z.z, translate.z,
							0, 0, 0, 1);
					}

					// Function 3: Convert IfcObjectPlacement. 
					static void convertIfcObjectPlacement(
						const std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> object_placement,
						carve::math::Matrix& matrix,
						double length_factor,
						std::set<int>& already_applied)
					{
						// Prevent cyclic relative placement
						const int placement_id = object_placement->getId();
						if(placement_id > 0) {
							if(already_applied.find(placement_id) != already_applied.end()) {
								return;
								//throw IfcPPException( "PlacementConverter::convertIfcObjectPlacement: detected placement cycle", __func__ );
							}
							already_applied.insert(placement_id);
						}
						carve::math::Matrix object_placement_matrix(carve::math::Matrix::IDENT());

						// (1/2) IfcLocalPLacement SUBTYPE OF IfcObjectPlacement
						std::shared_ptr<typename IfcEntityTypesT::IfcLocalPlacement> local_placement =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLocalPlacement>(object_placement);
						if(local_placement) {
							// Relative Placement type IfcAxis2Placement [1:1]					
							decltype(local_placement->RelativePlacement)& axis2placement = local_placement->RelativePlacement;
							carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());

							switch(axis2placement.which()) {
							case 0:
								convertIfcAxis2Placement2D(axis2placement.get<0>().lock(), relative_placement, length_factor);
								break;
							case 1:
								convertIfcAxis2Placement3D(axis2placement.get<1>().lock(), relative_placement, length_factor);
								break;
							default:
								break;
							}

							//convertIfcPlacement(placement, relative_placement, length_factor);
							object_placement_matrix = relative_placement;



							// PlacementRelTo type IfcObjectPlacement [0:1]
							if(local_placement->PlacementRelTo) {
								// Reference to Object that provides the relative placement by its local coordinate system. 
								decltype(local_placement->PlacementRelTo)::type& local_object_placement = local_placement->PlacementRelTo;
								carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
								convertIfcObjectPlacement(local_object_placement.lock(), relative_placement, length_factor, already_applied);
								object_placement_matrix = relative_placement*object_placement_matrix;
							}
							else {
								// If reference to Object is omitted, then the local placement is given to the WCS, established by the geometric representation context.
									//carve::math::Matrix context_matrix( carve::math::Matrix::IDENT() );
									//applyContext( context, context_matrix, length_factor, placement_already_applied );
									//object_placement_matrix = context_matrix*object_placement_matrix;
							}
						}

						// (2/2) IfcGridPlacement SUBTYPE OF IfcObjectPlacement
						else if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcGridPlacement> grid_placement =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement);

							// PlacementLocation type IfcVirtualGridIntersection
							auto grid_intersection = grid_placement->PlacementLocation;

							if(grid_intersection) {
								// IntersectingAxes type IfcGridAxis L[2:2]
								/*Syntax?*/
								//std::vector<carve::geom::vector<2>>& vec_grid_axis = grid_intersection->IntersectingAxes;

								// OffsetDistances type IfcLengthMeasure L[2:3]
								//std::vector<double>& vec_offsets = grid_intersection->OffsetDistances;
								// TODO: implement

								// IfcPlacementRefDirection [OPTIONAL]
								//IfcGridPlacementDirectionSelect* ref_direction = grid_placement->PlacementRefDirection.get()
							}

						}
						matrix = object_placement_matrix;
					}

					// Function 4: Get World Coordinate System. 
					static void getWorldCoordinateSystem(
						const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationContext>& context,
						carve::math::Matrix& matrix, double length_factor,
						std::set<int>& already_applied)
					{
						if(!context) {
							return;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext> geom_context =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationContext>(context);
						if(!geom_context) {
							return;
						}

						// Prevent cyclic relative placement
						const int placement_id = context->getId();
						if(placement_id > 0) {
							if(already_applied.find(placement_id) != already_applied.end()) {
								return;
							}
							already_applied.insert(placement_id);
						}

						// Get attributes. 
						// CoordinateSpaceDimension type IfcDimensionCount, Precision type IfcReal [OPTIONAL], World Coordinate System type IfcAxis2Placement, TrueNorth type IfcDirection [OPTIONAL].
						int dim_count = geom_context->CoordinateSpaceDimension;
						double	precision = geom_context->Precision;
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement>& world_coords = geom_context->WorldCoordinateSystem;
						double true_north = geom_context->TrueNorth;

						// Inverse attributes: std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >	HasSubContexts_inverse;

						carve::math::Matrix world_coords_matrix(carve::math::Matrix::IDENT());
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> world_coords_3d = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(world_coords);
						if(world_coords_3d) {
							PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(world_coords_3d, world_coords_matrix, length_factor);
						}

						matrix = matrix*world_coords_matrix;

						// Get inverse attribute.
						std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext> geom_sub_context =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>(geom_context);
						if(geom_sub_context) {
							// Get attributes.
							// ParentContext type IfcGeometricRepresentationContext, TargetScale type IfcPositiveRatioMeasure [OPTIONAL], TargetView type IfcGeometricProjectionEnum, UserDefinedTargetView type IfcLabel [OPTIONAL]
							std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& parent_context = geom_sub_context->ParentContext;
							double target_scale = geom_sub_context->TargetScale;
							std::shared_ptr<typename IfcEntityTypesT::IfcGeometricProjectionEnum>& target_view = geom_sub_context->TargetView;
							std::shared_ptr<typename IfcEntityTypesT::IfcLabel>& user_target_view = geom_sub_context->UserDefinedTargetView;

							if(parent_context) {
								getWorldCoordinateSystem(parent_context, matrix, length_factor, already_applied);
							}
						}
					}

					// Function 5: Convert Transformation Operator. 
					static void convertTransformationOperator(
						const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator> transform_operator,
						carve::math::Matrix& matrix,
						double length_factor)
					{
						// IfcCartesianTransformationOperator ABSTRACT SUPERTYPE OF IfcCartesianTransformationOperator2D, IfcCartesianTransformationOperator3D
						carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));

						double scale = 1.0;
						double scale_y = 1.0;
						double scale_z = 1.0;

						// (1/2) IfcCartesianTransformationOperator2D SUBTYPE OF IfcCartesianTranformationOperator
						if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D> trans_operator_2d =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator);

							if(!trans_operator_2d->LocalOrigin) {
								std::stringstream ss;
								ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
								throw std::runtime_error(ss.str().c_str());
							}

							if(trans_operator_2d->LocalOrigin->Coordinates.size() < 2) {
								std::stringstream ss;
								ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
								throw std::runtime_error(ss.str().c_str());
							}
							double x = trans_operator_2d->LocalOrigin->Coordinates[0] * length_factor;
							double y = trans_operator_2d->LocalOrigin->Coordinates[1] * length_factor;
							translate = carve::geom::VECTOR(x, y, 0.0);

							if(trans_operator_2d->Scale == trans_operator_2d->Scale) {
								// transOperator2D->Scale is not NAN
								// Magic: Markic & Hecht 19.06.18
								if(std::is_same<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D, OpenInfraPlatform::IFC4X1::IfcCartesianTransformationOperator2D>::value)
									scale = std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcCartesianTransformationOperator2D>(trans_operator_2d)->Scale;
								else
									scale = *(double*)(&(trans_operator_2d->Scale));
								// end magic
							}

							scale_y = scale;
							scale_z = scale;

							if(trans_operator_2d->Axis1 && trans_operator_2d->Axis2) {
								if(trans_operator_2d->Axis1->DirectionRatios.size() < 2) {
									std::stringstream ss;
									ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
									throw std::runtime_error(ss.str().c_str());
								}
								if(trans_operator_2d->Axis2->DirectionRatios.size() < 2) {
									std::stringstream ss;
									ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
									throw std::runtime_error(ss.str().c_str());
								}

								local_x.x = trans_operator_2d->Axis1->DirectionRatios[0];
								local_x.y = trans_operator_2d->Axis1->DirectionRatios[1];

								local_y.x = trans_operator_2d->Axis2->DirectionRatios[0];
								local_y.y = trans_operator_2d->Axis2->DirectionRatios[1];
							}

							// IfcCartesianTransformationOperator2DnonUniform SUBTYPE OF IfcCartesianTransformationOperator2D
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform> non_uniform = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform>(transform_operator);
							if(non_uniform) {
								if(non_uniform->Scale2 == non_uniform->Scale2) {
									// Scale2 is not NAN
									scale_y = non_uniform->Scale2;
								}
							}
						}

						// (2/2) IfcCartesianTransformationOperator3D SUBTYPE OF IfcCartesianTranformationOperator
						else {
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D> trans_operator_3d =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D>(transform_operator);

							if(!trans_operator_3d) {
								std::stringstream ss;
								ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
								throw std::runtime_error(ss.str().c_str());
							}
							if(!trans_operator_3d->LocalOrigin) {
								std::stringstream ss;
								ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
								throw std::runtime_error(ss.str().c_str());
							}
							if(trans_operator_3d->LocalOrigin->Coordinates.size() < 3) {
								std::stringstream ss;
								ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
								throw std::runtime_error(ss.str().c_str());
							}
							translate.x = trans_operator_3d->LocalOrigin->Coordinates[0] * length_factor;
							translate.y = trans_operator_3d->LocalOrigin->Coordinates[1] * length_factor;
							translate.z = trans_operator_3d->LocalOrigin->Coordinates[2] * length_factor;

							if(trans_operator_3d->Scale == trans_operator_3d->Scale) {
								// Scale is not NAN
								scale = trans_operator_3d->Scale;
							}
							scale_y = scale;
							scale_z = scale;

							if(trans_operator_3d->Axis1 && trans_operator_3d->Axis2 && trans_operator_3d->Axis3) {
								// Axis1, Axis2, Axis3 type IfcDirection
								auto axis1 = trans_operator_3d->Axis1;
								auto axis2 = trans_operator_3d->Axis2;
								auto axis3 = trans_operator_3d->Axis3;

								if(axis1->DirectionRatios.size() < 2) {
									std::stringstream ss;
									ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
									throw std::runtime_error(ss.str().c_str());
								}
								if(axis2->DirectionRatios.size() < 2) {
									std::stringstream ss;
									ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
									throw std::runtime_error(ss.str().c_str());
								}
								if(axis3->DirectionRatios.size() < 2) {
									std::stringstream ss;
									ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
									throw std::runtime_error(ss.str().c_str());
								}

								local_x.x = axis1->DirectionRatios[0];
								local_x.y = axis1->DirectionRatios[1];
								local_x.z = axis1->DirectionRatios[2];

								local_y.x = axis2->DirectionRatios[0];
								local_y.y = axis2->DirectionRatios[1];
								local_y.z = axis2->DirectionRatios[2];

								local_z.x = axis3->DirectionRatios[0];
								local_z.y = axis3->DirectionRatios[1];
								local_z.z = axis3->DirectionRatios[2];
							}

							// IfcCartesianTransformationOperator3DnonUniform SUBTYPE OF IfcCartesianTransformationOperator3D
							std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform> non_uniform =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform>(transform_operator);

							if(non_uniform) {
								if(non_uniform->Scale2 == non_uniform->Scale2) {
									scale_y = non_uniform->Scale2;
								}
								if(non_uniform->Scale3 == non_uniform->Scale3) {
									scale_z = non_uniform->Scale3;
								}
							}
						}

						local_x.normalize();
						local_y.normalize();
						local_z.normalize();

						carve::math::Matrix rotate_translate(
							local_x.x, local_y.x, local_z.x, translate.x,
							local_x.y, local_y.y, local_z.y, translate.y,
							local_x.z, local_y.z, local_z.z, translate.z,
							0, 0, 0, 1);
						matrix = rotate_translate*carve::math::Matrix::SCALE(scale, scale_y, scale_z);
					}

					// Function 6: Get Plane. 
					static void getPlane(const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d,
						carve::geom::plane<3>& plane,
						carve::geom::vector<3>& translate,
						double length_factor)
					{
						carve::geom::vector<3>  location(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
						carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

						// Location type IfcCartesianPoint 
						if(axis2placement3d->Location) {
							auto coords = axis2placement3d->Location->Coordinates;
							//coords.reserve(axis2placement3d->Location->Coordinates.size());
							//std::transform(
							//	axis2placement3d->Location->Coordinates.begin(),
							//	axis2placement3d->Location->Coordinates.end(),
							//	coords.begin(),
							//	[](auto &point) {
							//	carve::geom::vector<3> carve_point;
							//	carve_point.x = point[0];
							//	carve_point.y = point[1];
							//	carve_point.z = point[2];
							//	return carve_point;
							//	}
							//);

							if(coords.size() > 2) {
								location = carve::geom::VECTOR(coords[0] * length_factor, coords[1] * length_factor, coords[2] * length_factor);
							}
							else if(coords.size() > 1) {
								location = carve::geom::VECTOR(coords[0] * length_factor, coords[1] * length_factor, 0.0);
							}
						}

						// Axis type IfcDirection
						if(axis2placement3d->Axis) {
							auto axis = axis2placement3d->Axis->DirectionRatios;	// local z-axis

							if(axis.size() > 2) {
								local_z = carve::geom::VECTOR(axis[0], axis[1], axis[2]);
							}
						}

						local_z.normalize();

						carve::geom::plane<3> p(local_z, location);
						plane.d = p.d;
						plane.N = local_z;
						translate = location;
					}

					// Function 7: Convert distance along an alignment curve to 3D coordinates.
					static void convertAlignmentCurveDistAlongToPoint3D(std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> ifcAlignmentCurve,
						std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> pointDistAlong,
						carve::geom::vector<3>& targetPoint3D,
						carve::geom::vector<3>& targetDirection3D)
					
					{	
						// Function allows IfcBoundedCurve as input because of template issues. TODO: change to IfcAlignmentCurve
						std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignmentCurve> alignment_curve =
							std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignmentCurve>(ifcAlignmentCurve);
						if (alignment_curve)
						{
							double length_factor = unitConverter->getLengthInMeterFactor();
							double plane_angle_factor = unitConverter->getAngleInRadianFactor();

							// Get information from horizontal alignment.
							std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DHorizontal> horizontal = alignment_curve->Horizontal.lock();

							if (!horizontal)
							{
								BLUE_LOG(error) << "No IfcAlignment2DHorizontal in IfcAlignmentCurve.";
								return;
							}

							// Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if (horizontal->Segments.empty()) {
								BLUE_LOG(error) << "Not enough segments in IfcAlignment2DHorizontal. (Segment ID: " << horizontal->getId() << ").";
								return;
							}

							std::vector<std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DHorizontalSegment> > horSegments;
							horSegments.resize(horizontal->Segments.size());
							std::transform(horizontal->Segments.begin(), horizontal->Segments.end(), horSegments.begin(), [](auto &it) {return it.lock(); });

							std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DHorizontalSegment> horizontalSegmentRelevantToPoint;
							std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcCurveSegment2D> horCurveGeometry;
							double horizSegStartDistAlong = 0.;
							double horizSegStartPointX = 0.;
							double horizSegStartPointY = 0.;
							double horizSegStartDirection = 0.;
							double horizSegLength = 0.;

							// Iterate over horizontal segments
							for (auto it_segment : horSegments) {
								//IfcAlignment2DHorizontalSegment (TangentialContinuity type IfcBoolean [0:1], StartTag type IfcLabel [0:1], EndTag type IfcLabel [0:1], CurveGeometry type IfcCurveSegment2D [1:1])
								horCurveGeometry = it_segment->CurveGeometry.lock();

								// Get and interpret information from IfcCurveSegment2D.
								if (!horCurveGeometry) {
									BLUE_LOG(error) << "No curve geometry in IfcAlignment2DHorizontalSegment (Segment ID: " << it_segment->getId() << ").";
									return;
								}

								// SegmentLength type IfcPositiveLengthMeasure [1:1]
								if (horCurveGeometry->SegmentLength < 0) {
									BLUE_LOG(error) << "No curve segment length in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									return;
								}
								horizSegLength = horCurveGeometry->SegmentLength * length_factor;


								// If the end of this segment is further along than the point, the point is within this segment.
								if (horizSegStartDistAlong + horizSegLength > pointDistAlong)
								{
									horizontalSegmentRelevantToPoint = it_segment;

									// StartPoint type IfcCartesianPoint [1:1]
									auto curveSegStartPoint = horCurveGeometry->StartPoint.lock();
									if (curveSegStartPoint.empty()) {
										BLUE_LOG(error) << "No curve segment start point in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									horizSegStartPointX = curveSegStartPoint->Coordinates[0] * length_factor;
									horizSegStartPointY = curveSegStartPoint->Coordinates[1] * length_factor;

									// StartDirection type IfcPlaneAngleMeasure [1:1]
									// cannot check because StartDirection is IfcPlaneAngleMeasure
									/*if (!horCurveGeometry->StartDirection) {
										BLUE_LOG(error) << "No curve segment start direction in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
										return;
									}*/
									horizSegStartDirection = horCurveGeometry->StartDirection * plane_angle_factor;

									break;
								} // end if

								// If the start of the segment along the alignment equals the point's distance along the alignment, save the segment start point coordinates.
								// horizSegStartDistAlong is the sum of the previous segments (starting with 0 at first segment)
								// todo in different commit change links
								else if (horizSegStartDistAlong == pointDistAlong)
								{
									// StartPoint type IfcCartesianPoint [1:1]
									auto curveSegStartPoint = horCurveGeometry->StartPoint.lock();
									if (curveSegStartPoint.empty()) {
										BLUE_LOG(error) << "No curve segment start point in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
										return;
									}

									targetPoint3D->Coordinates[0] = curveSegStartPoint->Coordinates[0] * length_factor;
									targetPoint3D->Coordinates[1] = curveSegStartPoint->Coordinates[1] * length_factor;

									break;
								} // end if

								horizSegStartDistAlong = horizSegStartDistAlong + horizSegLength;
							} // end segments iteration


							// Get information on vertical alignment.
							auto vertical = alignment_curve->Vertical;
							if (!vertical) {
								BLUE_LOG(warning) << "No IfcAlignment2DVertical in IfcAlignmentCurve (Segment ID: " << vertical->getId() << ").";
								// TO DO: Handle as horizontal alignment only.
							}
							else
							{
								if (vertical->Segments.empty()) {
									BLUE_LOG(error) << "No segments in IfcAlignment2DVertical. (Segment ID: " << vertical->getId() << ").";
								}
								std::vector<std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerticalSegment> > verSegments;
								verSegments.resize(vertical->Segments.size());

								std::transform(vertical->Segments.begin(), vertical->Segments.end(), verSegments.begin(), [](auto &it) {return it.lock(); });


								std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerticalSegment >> verticalSegmentRelevantToPoint;
								double verSegStartHeight = 0.;
								double verSegStartGradient = 0.;
								double verSegLength = 0.;
								double verSegDistAlong = 0.;

								// Iterate over horizontal segments
								for (auto it_segment : verSegments) {

									// StartDistAlong type IfcLengthMeasure [1:1]
									if (it_segment->StartDistAlong < 0) {
										BLUE_LOG(error) << "No start distance along in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									verSegDistAlong = it_segment->StartDistAlong * length_factor;

									// HorizontalLength type IfcPositiveLengthMeasure [1:1]
									if (it_segment->HorizontalLength <= 0) {
										BLUE_LOG(error) << "No horizontal length in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
										return;
									}
									double VerSegLength = it_segment->HorizontalLength * length_factor;

									// If the end of this segment is further along than the point, the point is within this segment.
									if (verSegDistAlong + VerSegLength > pointDistAlong)
									{
										verticalSegmentRelevantToPoint = it_segment;

										// StartHeight type IfcLengthMeasure [1:1]
										// cannot check since StartHeight is IfcLengthMeasure, not IfcPositiveLengthMeasure
										/*if (!it_segment->StartHeight) {
											BLUE_LOG(error) << "No start height in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
											return;
										}*/
										double verSegStartHeight = it_segment->StartHeight * length_factor;

										// StartGradient type IfcRatioMeasure [1:1]
										// cannot check since StartGradient is IfcRatioMeasure
										/*if (!it_segment->StartGradient) {
											BLUE_LOG(error) << "No start gradient in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
											return;
										}*/
										double verSegStartGradient = it_segment->StartGradient;

										break;
									} // end if

								}// end vertical stations iteration

								// Calculate x and y coordinates from horizontal curve, if not already there.
								if (targetPoint3D->Coordinates.empty())
								{
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcLineSegment2D> line_segment_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcLineSegment2D>(horCurveGeometry);
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcCircularArcSegment2D> circular_arc_segment_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcCircularArcSegment2D>(horCurveGeometry);
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcTransitionCurveSegment2D>(horCurveGeometry);

									if (line_segment_2D) {
										double distanceToStart = pointDistAlong - horizSegStartDistAlong;
										targetPoint3D->Coordinates[0] = horizSegStartPointX + distanceToStart * cos(horizSegStartDirection);
										targetPoint3D->Coordinates[1] = horizSegStartPointY + distanceToStart * sin(horizSegStartDirection);
									}
									if (circular_arc_segment_2D) {
										// Radius type IfcPositiveLengthMeasure [1:1]
										if (circular_arc_segment_2D->Radius <= 0) {
											BLUE_LOG(error) << "No radius in IfcCircularArcSegment2D (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
											return;
										}
										double radius = circular_arc_segment_2D->Radius * length_factor;

										// IsCCW type IfcBoolean [1:1]
										// TODO: can check boolean this way?
										/*if (!circular_arc_segment_2D->IsCCW) {
											BLUE_LOG(error) << "No direction information for IfcCircularArcSegment2D (counterclockwise/clockwise) (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
											return;
										}*/
										bool is_CCW = circular_arc_segment_2D->IsCCW;

										// Calculate circle center, given start point and direction (angle between tangent and x-axis).
										double radiusDirection = 0.;
										is_CCW ? radiusDirection = horizSegStartDirection + 3 * M_PI / 2 : radiusDirection = horizSegStartDirection + M_PI / 2;
										double centerX = horizSegStartPointX + cos(radiusDirection) * radius;
										double centerY = horizSegStartPointY + sin(radiusDirection) * radius;
										double angleAlpha = atan2(horizSegStartPointY - centerY, horizSegStartPointX - centerX); // Angle between x-axis and vector(start, center).

										// Calculate x and y
										double distanceStartToStation = pointDistAlong - horizSegStartDistAlong; // Distance from start of segment to point along alignment.
										double angleBeta = 0;
										if (is_CCW)
										{
											angleBeta = angleAlpha - distanceStartToStation / radius; // Angle between x-axis and point according to circle direction.
										}
										else
										{
											angleBeta = angleAlpha + distanceStartToStation / radius; // Angle between x-axis and point according to circle direction.
										}

										targetPoint3D->Coordinates[0] = centerX + radius * cos(angleBeta);
										targetPoint3D->Coordinates[1] = centerY + radius * sin(angleBeta);
									}
									if (trans_curve_segment_2D) {
										// StartRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
										double startRadius = 0.0;
										if (trans_curve_segment_2D->StartRadius <= 0) {
											BLUE_LOG(warning) << "IfcTransitionCurve: Start radius NIL, interpreted as infinite. (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
										}
										else {
											startRadius = trans_curve_segment_2D->StartRadius * length_factor;
										}
										// EndRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
										double endRadius = 0.0;
										if (trans_curve_segment_2D->EndRadius <= 0) {
											BLUE_LOG(warning) << "IfcTransitionCurve: End radius NIL, interpreted as infinite. (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
										}
										else {
											endRadius = trans_curve_segment_2D->EndRadius * length_factor;
										}
										// IsStartRadiusCCW type IfcBoolean
										// TODO: can check boolean this way?
										/*if (!trans_curve_segment_2D->IsStartRadiusCCW) {
											BLUE_LOG(error) << "No direction information for start of IfcTransitionCurveSegment2D (counterclockwise/clockwise). (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
											return;
										}*/
										bool is_start_ccw = trans_curve_segment_2D->IsStartRadiusCCW;
										// IsEndRadiusCCW type IfcBoolean
										// TODO: can check boolean this way?
										/*if (!trans_curve_segment_2D->IsEndRadiusCCW) {
											BLUE_LOG(error) << "No direction information for end of IfcTransitionCurveSegment2D (counterclockwise/clockwise). (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
											return;
										}*/
										bool is_end_ccw = trans_curve_segment_2D->IsEndRadiusCCW;

										auto trans_type = trans_curve_segment_2D->TransitionCurveType;

										switch (trans_type) {

										case(eTransitionCurveType::ENUM_BIQUADRATICPARABOLA):
										{
											double x = pointDistAlong;		// x coordinate
											double y = 0.0;
											if (x <= horizSegLength / 2)	// y coordinate
											{
												y = pow(x, 4) / (6 * endRadius * horizSegLength * horizSegLength);
											}
											else if (horizSegLength / 2 < x && x <= horizSegLength)
											{
												y = -(pow(x, 4) / (6 * endRadius * pow(horizSegLength, 2)) + (2 * pow(x, 3)) / (3 * endRadius * horizSegLength)
													- pow(x, 2) / (2 * endRadius) + (horizSegLength * x) / (6 * endRadius) - pow(horizSegLength, 2) / (48 * endRadius));
											} // end elseif
											else
											{
												BLUE_LOG(error) << "Y coordinate not defined for biquadratic parabola (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
												break;
											}
											targetPoint3D->Coordinates[0] = x;
											targetPoint3D->Coordinates[1] = y;
										} // end case BIQUADRATICPARABOLA
										break;

										case(eTransitionCurveType::ENUM_BLOSSCURVE):
										{
											// Integration durch Substitution(s.Formel: http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifctransitioncurvetype.htm).
											double teta_up = pow(pointDistAlong + horizSegLength, 3) / (endRadius * pow(horizSegLength, 2))
												- pow(pointDistAlong + horizSegLength, 4) / (2 * endRadius * pow(horizSegLength, 3)); //values for upper boundary of integral
											double teta_low = pow(pointDistAlong, 3) / (endRadius * pow(horizSegLength, 2))
												- pow(pointDistAlong, 4) / (2 * endRadius * pow(horizSegLength, 3)); //values for lower boundary of integral
											double teta_deriv_up = 2 * pow(pointDistAlong + horizSegLength, 2) / endRadius * pow(horizSegLength, 2)
												- 4 * pow(pointDistAlong + horizSegLength, 3) / 2 * endRadius*pow(horizSegLength, 3);
											double teta_deriv_low = 2 * pow(pointDistAlong, 2) / endRadius * pow(horizSegLength, 2)
												- 4 * pow(pointDistAlong, 3) / 2 * endRadius*pow(horizSegLength, 3);
											double x = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;
											double y = -cos(teta_up) / teta_deriv_up + cos(teta_low) / teta_deriv_low;

											targetPoint3D->Coordinates[0] = x;
											targetPoint3D->Coordinates[1] = y;

										} // end case BLOSSCURVE
										break;

										case(eTransitionCurveType::ENUM_CLOTHOIDCURVE):
										{
											targetPoint3D->Coordinates[0] = pointDistAlong * (1 - pow(pointDistAlong, 4) / 40 * pow(endRadius, 2) * pow(horizSegLength, 2) + pow(pointDistAlong, 8) / 3456 * pow(endRadius, 4) * pow(horizSegLength, 4));
											targetPoint3D->Coordinates[1] = (pow(pointDistAlong, 3) / 6 * endRadius*horizSegLength) * (1 - pow(pointDistAlong, 4) / 56 * pow(endRadius, 2) * pow(horizSegLength, 2) + pow(pointDistAlong, 8) / 7040 * pow(endRadius, 4) * pow(horizSegLength, 4));
										} // end case CLOTHOIDCURVE
										break;

										case(eTransitionCurveType::ENUM_COSINECURVE):
										{
											double psi = M_PI * pointDistAlong / horizSegLength;
											double x = pointDistAlong - (pow(horizSegLength, 2) / (8 * pow(M_PI, 2) * pow(endRadius, 2))) * horizSegLength / M_PI
												* ((pow(psi, 3) / 3) + (psi / 2 - sin(psi) * cos(psi) / 2) - 2 * (sin(psi) - psi * cos(psi)));
											double y = horizSegLength * (horizSegLength / (2 * pow(M_PI, 2) * endRadius) * (pow(psi, 2) / 2 + cos(psi) - 1)
												- (pow(horizSegLength, 3) / (48 * pow(M_PI, 4) * pow(endRadius, 3)))
												* (pow(psi, 4) / 4 + pow(sin(psi), 2) * cos(psi) / 3 - 16 * cos(psi) / 3 + 3 * pow(psi, 2) * cos(psi)
													- 6 * psi * sin(psi) + 3 * pow(psi, 2) / 4 - 3 * psi * sin(2 * psi) / 4 - 3 * cos(2 * psi) / 8 + 137 / 24));
											targetPoint3D->Coordinates[0] = x;
											targetPoint3D->Coordinates[1] = y;
										} // end case COSINECURVE
										break;

										case (eTransitionCurveType::ENUM_CUBICPARABOLA):
										{
											double x = pointDistAlong;
											double y = pow(x, 3) / (6 * endRadius * horizSegLength);
											targetPoint3D->Coordinates[0] = x;
											targetPoint3D->Coordinates[1] = y;
										} // end case CUBICPARABOLA
										break;

										case (eTransitionCurveType::ENUM_SINECURVE):
										{
											double psi = (2 * M_PI * pointDistAlong) / horizSegLength;
											double x = pointDistAlong * (1 - pow(horizSegLength, 2) / (32 * pow(M_PI, 4)*pow(endRadius, 2) - (pow(horizSegLength, 3) / 3840 * pow(M_PI, 5)*pow(endRadius, 2)))
												* (3 * pow(psi, 5) - 20 * pow(psi, 3) + 30 * psi - (240 - 60 * pow(psi, 2)*sin(psi) + 30 * cos(psi)*sin(psi) + 120 * psi*cos(psi))));
											// Integration durch Substitution (s. Formel: http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifctransitioncurvetype.htm).
											double teta_up = pow((pointDistAlong + horizSegLength), 2) / (2 * endRadius*horizSegLength) + (horizSegLength / (4 * pow(M_PI, 2)*endRadius)) * (cos(2 * M_PI*(pointDistAlong + horizSegLength) / horizSegLength) - 1);
											double teta_low = pow((pointDistAlong + horizSegLength), 2) / (2 * endRadius*horizSegLength) + (horizSegLength / (4 * pow(M_PI, 2)*endRadius)) * (cos(2 * M_PI*(pointDistAlong) / horizSegLength) - 1);
											double teta_deriv_up = 2 * (pointDistAlong + horizSegLength) / 2 * endRadius*horizSegLength;
											double teta_deriv_low = 2 * pointDistAlong / 2 * endRadius*horizSegLength;
											double y = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;
											targetPoint3D->Coordinates[0] = x;
											targetPoint3D->Coordinates[1] = y;
										} // end case SINECURVE
										break;
										} // end switch (trans_type)
									} // end if trans curve
								} // end x, y coordinate calculation


								// Calculate z coordinate from vertical alignment, if not already there.
								if (targetPoint3D->Coordinates.empty())
								{
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegLine> v_seg_line_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcLineSegment2D>(verticalSegmentRelevantToPoint);
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegCircularArc>(verticalSegmentRelevantToPoint);
									std::shared_ptr<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
										std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcAlignment2DVerSegParabolicArc>(verticalSegmentRelevantToPoint);

									if (v_seg_line_2D)
									{
										double distanceToStart = pointDistAlong - verSegDistAlong;
										targetPoint3D->Coordinates[2] = verSegStartHeight + verSegStartGradient * distanceToStart;
									}
									if (v_seg_circ_arc_2D)
									{
										// Radius type IfcPositiveLengthMeasure [1:1] 
										if (v_seg_circ_arc_2D->Radius <= 0) {
											BLUE_LOG(error) << "No radius in IfcAlignment2DVerSegCircularArc\" (Segment ID : " << verticalSegmentRelevantToPoint->getId() << ").";
											return;
										}
										double radius = v_seg_circ_arc_2D->Radius * length_factor;

										// IsConvex type IfcBoolean [1:1]
										// TODO: can check boolean this way?
										/*if (!v_seg_circ_arc_2D->IsConvex) {
											BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegCircularArc (convex/concave)\" (Segment ID : " << verticalSegmentRelevantToPoint->getId() << ").";
											return;
										}*/
										bool is_convex = v_seg_circ_arc_2D->IsConvex;

										// pointDistAlong and verSegDistAlong are along horizontal alignment, which corresponds to the horizontal axis in the vertical alignment
										double distanceToStart = pointDistAlong - verSegDistAlong;
										double z = 0.;

										if (is_convex == true) {
											z = -sqrt(pow(radius, 2) - pow(distanceToStart + (verSegStartGradient * radius) / sqrt(1 + pow(verSegStartGradient, 2)), 2))
												+ radius / sqrt(1 + pow(verSegStartGradient, 2)); // Crest (decreasing gradient)
										}
										else {
											z = sqrt(pow(radius, 2) - pow(distanceToStart - (verSegStartGradient * radius) / sqrt(1 + pow(verSegStartGradient, 2)), 2))
												- radius / sqrt(1 + pow(verSegStartGradient, 2)); // Sag (increasing gradient)
										}

										targetPoint3D->Coordinates[2] = z + verSegStartHeight;
									}
									if (v_seg_par_arc_2D)
									{
										// ParabolaConstant type IfcPositiveLengthMeasure [1:1]
										if (v_seg_par_arc_2D->ParabolaConstant <= 0) {
											BLUE_LOG(error) << "No parabola constant in IfcAlignment2DVerSegParabolicArc (Segment ID : " << verticalSegmentRelevantToPoint->getId() << ").";
											return;
										}
										double arc_const = v_seg_par_arc_2D->ParabolaConstant * length_factor;

										// IsConvex type IfcBoolean [1:1]
										// TODO: can check boolean this way?
										/*if (!v_seg_par_arc_2D->IsConvex) {
											BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegParabolicArc (convex/concave) (Segment ID : " << verticalSegmentRelevantToPoint->getId() << ").";
											return;
										}*/
										bool is_convex = v_seg_par_arc_2D->IsConvex;

										double parabola_radius = is_convex ? -arc_const : arc_const;
										double parabola_gradient = (pointDistAlong - startDistAlong) / parabola_radius + startGradient;
										targetPoint3D->Coordinates[2] = (pointDistAlong - startDistAlong) * (parabola_gradient + startGradient) / 2 + startHeight;
									}
								}// end z coordinate calculation

							}//end if vertical
						}//end if alignment curve
						else 
						{
							BLUE_LOG(error) << "Function convertAlignmentCurveDistAlongToPoint3D exclusively handles alignment curves.";
						}
					}//end convertAlignmentCurveDistAlongToPoint3D



					//static void PlacementConverter::convertMatrix( const carve::math::Matrix& matrix, 
					//									   std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>& axis2placement3d, 
					//									   double length_factor, int& entity_id, 
					//										std::vector<std::shared_ptr<IfcEntityT> >& vec_entities )
					//{
					//	throw std::exception();
					//
					//
					//	if( !axis2placement3d )
					//	{
					//		axis2placement3d = std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>(new typename IfcEntityTypesT::IfcAxis2Placement3D(entity_id++));
					//		vec_entities.push_back( axis2placement3d );
					//	}
					//
					//	carve::geom::vector<3>  local_x( carve::geom::VECTOR( 1.0, 0.0, 0.0 ) );
					//	carve::geom::vector<3>  local_y( carve::geom::VECTOR( 0.0, 1.0, 0.0 ) );
					//	carve::geom::vector<3>  local_z( carve::geom::VECTOR( 0.0, 0.0, 1.0 ) );
					//	carve::geom::vector<3>  translate( carve::geom::VECTOR( 0.0, 0.0, 0.0 ) );
					//
					//	local_x.x = matrix._11;//(0,0);
					//	local_x.y = matrix._12;//(0,1);
					//	local_x.z = matrix._13;//(0,2);
					//
					//	local_y.x = matrix._21;//(1,0);
					//	local_y.y = matrix._22;//(1,1);
					//	local_y.z = matrix._23;//(1,2);
					//
					//	local_z.x = matrix._31;//(2,0);
					//	local_z.y = matrix._32;//(2,1);
					//	local_z.z = matrix._33;//(2,2);
					//
					//	translate.x = matrix._41;//(3,0);
					//	translate.y = matrix._42;//(3,1);
					//	translate.z = matrix._43;//(3,2);
					//
					//	local_x.normalize();
					//	local_y.normalize();
					//	local_z.normalize();
					//
					//	axis2placement3d->Location = std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>( new typename IfcEntityTypesT::IfcCartesianPoint( entity_id++ ) );
					//	vec_entities.push_back( axis2placement3d->Location );
					//	axis2placement3d->Location->Coordinates.push_back( std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.x/length_factor ) ) );
					//	axis2placement3d->Location->Coordinates.push_back( std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.y/length_factor ) ) );
					//	axis2placement3d->Location->Coordinates.push_back( std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.z/length_factor ) ) );
					//
					//	axis2placement3d->Axis = std::shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
					//	vec_entities.push_back( axis2placement3d->Axis );
					//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.x );
					//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.y );
					//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.z );
					//
					//	axis2placement3d->RefDirection = std::shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
					//	vec_entities.push_back( axis2placement3d->RefDirection );
					//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.x );
					//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.y );
					//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.z );
					//}
			};
		}
	}
}

#endif
