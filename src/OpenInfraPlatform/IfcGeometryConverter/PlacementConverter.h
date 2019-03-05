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

#include <set>
#include <memory>
#include "CarveHeaders.h"


/**********************************************************************************************/

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT
		>
		class PlacementConverterT
		{
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
				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis1Placement>(placement))
				{
					std::stringstream ss;
					#ifdef _DEBUG
					ss << "Warning\t| IfcAxis1Placement not implemented "; 
					#endif
					throw std::runtime_error(ss.str().c_str());
				}

				// (2/3) IfcAxis2Placement2D SUBTYPE OF IfcPlacement 
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement);
					convertIfcAxis2Placement2D(axis2placement2d, matrix, length_factor);
				}

				// (3/3) IfcAxis2Placement3D SUBTYPE OF IfcPlacement
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement);
					convertIfcAxis2Placement3D(axis2placement3d, matrix, length_factor);
				}
				else
				{
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
				if(axis2placement2d->Location)
				{
					if (axis2placement2d->Location->Coordinates.size() > 1)
					{					
						translate = carve::geom::VECTOR(axis2placement2d->Location->Coordinates[0]*length_factor, axis2placement2d->Location->Coordinates[1]*length_factor, 0.0);
					}
				}

				// Reference Direction type IfcDirection [OPTIONAL]
				if (axis2placement2d->RefDirection)
				{
					if (axis2placement2d->RefDirection->DirectionRatios.size() > 1)
					{
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
				if (axis2placement3d->Location)
				{
/*Syntax?*/			std::vector<carve::geom::vector<3>>& coords = axis2placement3d->Location->Coordinates;

					if (coords.size() > 2)
					{
						translate = carve::geom::VECTOR(coords[0]*length_factor, coords[1]*length_factor, coords[2]*length_factor);
					}
					else if (coords.size() > 1)
					{
						translate = carve::geom::VECTOR(coords[0]*length_factor, coords[1]*length_factor, 0.0);
					}
				}

				// Axis type IfcDirection [OPTIONAL]
				if (axis2placement3d->Axis)
				{
					std::vector<double>& axis = axis2placement3d->Axis->DirectionRatios;

					if (axis.size() > 2)
					{
						local_z = carve::geom::VECTOR(axis[0], axis[1], axis[2]);
					}
				}

				// Reference Direction type IfcDirection [OPTIONAL]
				if (axis2placement3d->RefDirection)
				{
					if (axis2placement3d->RefDirection->DirectionRatios.size() > 2)
					{
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
				if (placement_id > 0)
				{
					if (already_applied.find(placement_id) != already_applied.end())
					{
						return;
						//throw IfcPPException( "PlacementConverter::convertIfcObjectPlacement: detected placement cycle", __func__ );
					}
					already_applied.insert(placement_id);
				}
				carve::math::Matrix object_placement_matrix(carve::math::Matrix::IDENT());

				// (1/2) IfcLocalPLacement SUBTYPE OF IfcObjectPlacement
				shared_ptr<typename IfcEntityTypesT::IfcLocalPlacement> local_placement = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcLocalPlacement>(object_placement);			
				if(local_placement)
				{
					// Relative Placement type IfcAxis2Placement [1:1]
					if(local_placement->RelativePlacement)
					{
						shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement> axis2placement = local_placement->RelativePlacement;
						
						// IfcAxis2Placement = SELECT(IfcAxis2Placement2D,IfcAxis2Placement3D)
						if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(axis2placement))
						{
							shared_ptr<typename IfcEntityTypesT::IfcPlacement> placement = 
								dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(axis2placement);
							carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
							convertIfcPlacement(placement, relative_placement, length_factor);
							object_placement_matrix = relative_placement;
						}
					}

					// PlacementRelTo type IfcObjectPlacement [0:1]
					if (local_placement->PlacementRelTo)
					{
						// Reference to Object that provides the relative placement by its local coordinate system. 
						shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> local_object_placement = local_placement->PlacementRelTo;
						carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
						convertIfcObjectPlacement(local_object_placement, relative_placement, length_factor, already_applied);
						object_placement_matrix = relative_placement*object_placement_matrix;
					}
					else
					{
						// If reference to Object is omitted, then the local placement is given to the WCS, established by the geometric representation context.
							//carve::math::Matrix context_matrix( carve::math::Matrix::IDENT() );
							//applyContext( context, context_matrix, length_factor, placement_already_applied );
							//object_placement_matrix = context_matrix*object_placement_matrix;
					}
				}

				// (2/2) IfcGridPlacement SUBTYPE OF IfcObjectPlacement
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcGridPlacement> grid_placement = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement);

					// PlacementLocation type IfcVirtualGridIntersection
					shared_ptr<typename IfcEntityTypesT::IfcVirtualGridIntersection> grid_intersection = 
						grid_placement->PlacementLocation;

					if (grid_intersection)
					{
						// IntersectingAxes type IfcGridAxis L[2:2]
	/*Syntax?*/			std::vector<carve::geom::vector<2>>& vec_grid_axis = grid_intersection->IntersectingAxes;

						// OffsetDistances type IfcLengthMeasure L[2:3]
						std::vector<double>>& vec_offsets = grid_intersection->OffsetDistances;
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
				if (!context)
				{
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext> geom_context = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationContext>(context);
				if (!geom_context)
				{
					return;
				}

				// Prevent cyclic relative placement
				const int placement_id = context->getId();
				if (placement_id > 0)
				{
					if (already_applied.find(placement_id) != already_applied.end())
					{
						return;
					}
					already_applied.insert(placement_id);
				}

				// Get attributes. 
				// CoordinateSpaceDimension type IfcDimensionCount, Precision type IfcReal [OPTIONAL], World Coordinate System type IfcAxis2Placement, TrueNorth type IfcDirection [OPTIONAL].
				int dim_count = geom_context->CoordinateSpaceDimension;
				double	precision = geom_context->Precision;				
				shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement>& world_coords = geom_context->WorldCoordinateSystem;
				double true_north = geom_context->TrueNorth;	

				// Inverse attributes: std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >	HasSubContexts_inverse;

				carve::math::Matrix world_coords_matrix(carve::math::Matrix::IDENT());
				shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> world_coords_3d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(world_coords);
				if (world_coords_3d)
				{
					PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(world_coords_3d, world_coords_matrix, length_factor);
				}

				matrix = matrix*world_coords_matrix;

				// Get inverse attribute.
				shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext> geom_sub_context = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>(geom_context);
				if (geom_sub_context)
				{
					// Get attributes.
					// ParentContext type IfcGeometricRepresentationContext, TargetScale type IfcPositiveRatioMeasure [OPTIONAL], TargetView type IfcGeometricProjectionEnum, UserDefinedTargetView type IfcLabel [OPTIONAL]
					shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& parent_context = geom_sub_context->ParentContext;
					double target_scale = geom_sub_context->TargetScale;				
					shared_ptr<typename IfcEntityTypesT::IfcGeometricProjectionEnum>& target_view = geom_sub_context->TargetView;
					shared_ptr<typename IfcEntityTypesT::IfcLabel>& user_target_view = geom_sub_context->UserDefinedTargetView;	
					
					if (parent_context)
					{
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
				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator))
				{
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D> trans_operator_2d = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator);

					if (!trans_operator_2d->LocalOrigin)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}

					if (trans_operator_2d->LocalOrigin->Coordinates.size() < 2)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					double x = trans_operator_2d->LocalOrigin->Coordinates[0]*length_factor;
					double y = trans_operator_2d->LocalOrigin->Coordinates[1]*length_factor;
					translate = carve::geom::VECTOR(x, y, 0.0);

					if (trans_operator_2d->Scale == trans_operator_2d->Scale)
					{
						// transOperator2D->Scale is not NAN
						// Magic: Markic & Hecht 19.06.18
						if(std::is_same<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D, OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2D>::value)
							scale = dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2D>(trans_operator_2d)->Scale;
						else 
							scale = *(double*)(&(trans_operator_2d->Scale));
						// end magic
					}

					scale_y = scale;
					scale_z = scale;

					if (trans_operator_2d->Axis1 && trans_operator_2d-Axis2)
					{
						if (trans_operator_2d->Axis1->DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (trans_operator_2d->Axis2->DirectionRatios.size() < 2)
						{
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
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform> non_uniform = dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform>(transform_operator);
					if (non_uniform)
					{
						if (non_uniform->Scale2 == non_uniform->Scale2)
						{
							// Scale2 is not NAN
							scale_y = non_uniform->Scale2;
						}
					}
				}

				// (2/2) IfcCartesianTransformationOperator3D SUBTYPE OF IfcCartesianTranformationOperator
				else
				{
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D> trans_operator_3d =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D>(transform_operator);
					
					if (!trans_operator_3d)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					if (!trans_operator_3d->LocalOrigin)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					if (trans_operator_3d->LocalOrigin->Coordinates.size() < 3)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					translate.x = trans_operator_3d->LocalOrigin->Coordinates[0]*length_factor;
					translate.y = trans_operator_3d->LocalOrigin->Coordinates[1]*length_factor;
					translate.z = trans_operator_3d->LocalOrigin->Coordinates[2]*length_factor;

					if (trans_operator_3d->Scale == trans_operator_3d->Scale)
					{
						// Scale is not NAN
						scale = trans_operator_3d->Scale;
					}
					scale_y = scale;
					scale_z = scale;

					if (trans_operator_3d->Axis1 && trans_operator_3d->Axis2 && trans_operator_3d->Axis3)
					{
						// Axis1, Axis2, Axis3 type IfcDirection
						double axis1 = trans_operator_3d->Axis1;
						double axis2 = trans_operator_3d->Axis2;
						double axis3 = trans_operator_3d->Axis3;

						if (axis1->DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (axis2->DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (axis3->DirectionRatios.size() < 2)
						{
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
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform> non_uniform = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform>(transform_operator);
					
					if (non_uniform)
					{
						if (non_uniform->Scale2 == non_uniform->Scale2)
						{
							scale_y = non_uniform->Scale2;
						}
						if (non_uniform->Scale3 == non_uniform->Scale3)
						{
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
				if (axis2placement3d->Location)
				{
/*Syntax?*/			std::vector<carve::geom::vector<3>> >& coords = axis2placement3d->Location->Coordinates;

					if (coords.size() > 2)
					{
						location = carve::geom::VECTOR(coords[0]*length_factor, coords[1]*length_factor, coords[2]*length_factor);
					}
					else if (coords.size() > 1)
					{
						location = carve::geom::VECTOR(coords[0]*length_factor, coords[1]*length_factor, 0.0);
					}
				}

				// Axis type IfcDirection
				if (axis2placement3d->Axis)
				{
					std::vector<double>& axis = axis2placement3d->Axis->DirectionRatios;	// local z-axis

					if (axis.size() > 2)
					{
						local_z = carve::geom::VECTOR(axis[0], axis[1], axis[2]);
					}
				}

				local_z.normalize();

				carve::geom::plane<3> p(local_z, location);
				plane.d = p.d;
				plane.N = local_z;
				translate = location;
			}

			//static void PlacementConverter::convertMatrix( const carve::math::Matrix& matrix, 
			//									   shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>& axis2placement3d, 
			//									   double length_factor, int& entity_id, 
			//										std::vector<shared_ptr<IfcEntityT> >& vec_entities )
			//{
			//	throw std::exception();
			//
			//
			//	if( !axis2placement3d )
			//	{
			//		axis2placement3d = shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D>(new typename IfcEntityTypesT::IfcAxis2Placement3D(entity_id++));
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
			//	axis2placement3d->Location = shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>( new typename IfcEntityTypesT::IfcCartesianPoint( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->Location );
			//	axis2placement3d->Location->Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.x/length_factor ) ) );
			//	axis2placement3d->Location->Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.y/length_factor ) ) );
			//	axis2placement3d->Location->Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.z/length_factor ) ) );
			//
			//	axis2placement3d->Axis = shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->Axis );
			//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.x );
			//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.y );
			//	axis2placement3d->Axis->DirectionRatios.push_back( local_z.z );
			//
			//	axis2placement3d->RefDirection = shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->RefDirection );
			//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.x );
			//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.y );
			//	axis2placement3d->RefDirection->DirectionRatios.push_back( local_x.z );
			//}
		};
	}
}

#endif
