/*
    Copyright (c) 2017 Technical University of Munich
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
			static void convertIfcPlacement(
				const std::shared_ptr<typename IfcEntityTypesT::IfcPlacement> placement,
				carve::math::Matrix& matrix,
				double length_factor)
			{
				//std::cout << "Called PlacementConverterT::convertIfcPlacement" << std::endl;
				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis1Placement>(placement))
				{
					std::stringstream ss;
#ifdef _DEBUG
					ss << "Warning\t| IfcAxis1Placement not implemented "; //<< __func__;
#endif
					throw std::runtime_error(ss.str().c_str());
				}
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(placement);
					convertIfcAxis2Placement2D(axis2placement2d, matrix, length_factor);
				}
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement);
					convertIfcAxis2Placement3D(axis2placement3d, matrix, length_factor);
				}
				else
				{
					std::stringstream ss;
					ss << "Error\t| IfcPlacement is not IfcAxis2Placement2D or IfcAxis2Placement3D "; ///<< __func__;
					throw std::runtime_error(ss.str().c_str());
				}
			}

			static void convertIfcAxis2Placement2D(
				const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d,
				carve::math::Matrix& matrix,
				double length_factor)
			{
				//std::cout << "Called PlacementConverterT::convertIfcAxis2Placement2D" << std::endl;

				carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
				carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
				carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
				carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
				carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

				if (axis2placement2d->m_Location)
				{
					std::vector<shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords = axis2placement2d->m_Location->m_Coordinates;
					if (coords.size() > 1)
					{
						translate = carve::geom::VECTOR(coords[0]->m_value*length_factor, coords[1]->m_value*length_factor, 0.0);
					}
				}

				if (axis2placement2d->m_RefDirection)
				{
					if (axis2placement2d->m_RefDirection->m_DirectionRatios.size() > 1)
					{
						ref_direction.x = axis2placement2d->m_RefDirection->m_DirectionRatios[0];
						ref_direction.y = axis2placement2d->m_RefDirection->m_DirectionRatios[1];
						ref_direction.z = 0;
					}
				}

				//if( axis2placement2d->m_RefDirection )
				{
					//shared_ptr<IfcDirection>& ifc_placement_direction = axis2placement2d->m_RefDirection;
					//std::vector<double>& direction_ratios = ifc_placement_direction->m_DirectionRatios;

					//if( direction_ratios.size() > 1 )
					{
						local_x = ref_direction;//carve::geom::VECTOR(direction_ratios[0], direction_ratios[1], 0 );
						carve::geom::vector<3>  z_axis(carve::geom::VECTOR(0.0, 0.0, 1.0));
						local_y = carve::geom::cross(z_axis, local_x);
						// ref_direction can be just in the x-z-plane, not perpendicular to y and z. so re-compute local x
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

			static void convertIfcAxis2Placement3D(
				const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d,
				carve::math::Matrix& matrix,
				double length_factor)
			{
				//std::cout << "Called PlacementConverterT::convertIfcAxis2Placement3D" << std::endl;

				carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
				carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
				carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
				carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
				carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

				if (axis2placement3d->m_Location)
				{
					std::vector<shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords = axis2placement3d->m_Location->m_Coordinates;
					if (coords.size() > 2)
					{
						translate = carve::geom::VECTOR(coords[0]->m_value*length_factor, coords[1]->m_value*length_factor, coords[2]->m_value*length_factor);
					}
					else if (coords.size() > 1)
					{
						translate = carve::geom::VECTOR(coords[0]->m_value*length_factor, coords[1]->m_value*length_factor, 0.0);
					}
				}

				if (axis2placement3d->m_Axis)
				{
					// local z-axis
					std::vector<double>& axis = axis2placement3d->m_Axis->m_DirectionRatios;

					if (axis.size() > 2)
					{
						local_z = carve::geom::VECTOR(axis[0], axis[1], axis[2]);
					}
				}

				if (axis2placement3d->m_RefDirection)
				{
					if (axis2placement3d->m_RefDirection->m_DirectionRatios.size() > 2)
					{
						ref_direction.x = axis2placement3d->m_RefDirection->m_DirectionRatios[0];
						ref_direction.y = axis2placement3d->m_RefDirection->m_DirectionRatios[1];
						ref_direction.z = axis2placement3d->m_RefDirection->m_DirectionRatios[2];
					}
				}

				local_x = ref_direction;
				local_y = carve::geom::cross(local_z, local_x);
				// ref_direction can be just in the x-z-plane, not perpendicular to y and z. so re-compute local x
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

			static void convertIfcObjectPlacement(
				const std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> object_placement,
				carve::math::Matrix& matrix,
				double length_factor,
				std::set<int>& already_applied)
			{
				// prevent cyclic relative placement
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
				shared_ptr<typename IfcEntityTypesT::IfcLocalPlacement> local_placement = dynamic_pointer_cast<typename IfcEntityTypesT::IfcLocalPlacement>(object_placement);
				if (local_placement)
				{
					if (local_placement->m_RelativePlacement)
					{
						shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement> axis2placement = local_placement->m_RelativePlacement;
						// IfcAxis2Placement = SELECT(IfcAxis2Placement2D,IfcAxis2Placement3D)
						if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(axis2placement))
						{
							shared_ptr<typename IfcEntityTypesT::IfcPlacement> placement = dynamic_pointer_cast<typename IfcEntityTypesT::IfcPlacement>(axis2placement);
							carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
							convertIfcPlacement(placement, relative_placement, length_factor);
							object_placement_matrix = relative_placement;
						}
					}

					if (local_placement->m_PlacementRelTo)
					{
						shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> local_object_placement = local_placement->m_PlacementRelTo;
						// placement is relative to other placement
						carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
						convertIfcObjectPlacement(local_object_placement, relative_placement, length_factor, already_applied);
						object_placement_matrix = relative_placement*object_placement_matrix;
					}
					else
					{
						// If the PlacementRelTo is not given, then the IfcProduct is placed absolutely within the world coordinate system
						//carve::math::Matrix context_matrix( carve::math::Matrix::IDENT() );
						//applyContext( context, context_matrix, length_factor, placement_already_applied );
						//object_placement_matrix = context_matrix*object_placement_matrix;
					}
				}
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement))
				{
					shared_ptr<typename IfcEntityTypesT::IfcGridPlacement> grid_placement = dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement);

					shared_ptr<typename IfcEntityTypesT::IfcVirtualGridIntersection> grid_intersection = grid_placement->m_PlacementLocation;
					if (grid_intersection)
					{
						std::vector<shared_ptr<typename IfcEntityTypesT::IfcGridAxis> >& vec_grid_axis = grid_intersection->m_IntersectingAxes;
						std::vector<shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& vec_offsets = grid_intersection->m_OffsetDistances;
						// todo: implement
					}
					//IfcGridPlacementDirectionSelect* ref_direction = grid_placement->m_PlacementRefDirection.get();	//optional
				}

				matrix = object_placement_matrix;
			}

			static void getWorldCoordinateSystem(
				const std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationContext>& context,
				carve::math::Matrix& matrix, double length_factor,
				std::set<int>& already_applied)
			{
				if (!context)
				{
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext> geom_context = dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationContext>(context);
				if (!geom_context)
				{
					return;
				}

				// prevent cyclic relative placement
				const int placement_id = context->getId();
				if (placement_id > 0)
				{
					if (already_applied.find(placement_id) != already_applied.end())
					{
						return;
					}
					already_applied.insert(placement_id);
				}

				shared_ptr<typename IfcEntityTypesT::IfcDimensionCount>& dim_count = geom_context->m_CoordinateSpaceDimension;
				double							precision = geom_context->m_Precision;				//optional
				shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement>& world_coords = geom_context->m_WorldCoordinateSystem;
				shared_ptr<typename IfcEntityTypesT::IfcDirection>& true_north = geom_context->m_TrueNorth;				//optional
				// inverse attributes: std::vector<weak_ptr<IfcGeometricRepresentationSubContext> >	m_HasSubContexts_inverse;

				carve::math::Matrix world_coords_matrix(carve::math::Matrix::IDENT());
				shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> world_coords_3d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(world_coords);
				if (world_coords_3d)
				{
					PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(world_coords_3d, world_coords_matrix, length_factor);
				}

				matrix = matrix*world_coords_matrix;

				shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext> geom_sub_context = dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>(geom_context);
				if (geom_sub_context)
				{
					shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& parent_context = geom_sub_context->m_ParentContext;
					shared_ptr<typename IfcEntityTypesT::IfcPositiveRatioMeasure>& target_scale = geom_sub_context->m_TargetScale;				//optional
					shared_ptr<typename IfcEntityTypesT::IfcGeometricProjectionEnum>& target_view = geom_sub_context->m_TargetView;
					shared_ptr<typename IfcEntityTypesT::IfcLabel>& user_target_view = geom_sub_context->m_UserDefinedTargetView;	//optional

					if (parent_context)
					{
						getWorldCoordinateSystem(parent_context, matrix, length_factor, already_applied);
					}
				}
			}

			static void convertTransformationOperator(
				const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator> transform_operator,
				carve::math::Matrix& matrix,
				double length_factor)
			{
				// ENTITY IfcCartesianTransformationOperator  ABSTRACT SUPERTYPE OF(ONEOF(IfcCartesianTransformationOperator2D, IfcCartesianTransformationOperator3D))
				carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
				carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
				carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
				carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));

				double scale = 1.0;
				double scale_y = 1.0;
				double scale_z = 1.0;

				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator))
				{
					// ENTITY IfcCartesianTransformationOperator2D SUPERTYPE OF(IfcCartesianTransformationOperator2DnonUniform)
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D> trans_operator_2d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D>(transform_operator);
					if (!trans_operator_2d->m_LocalOrigin)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());

					}
					if (trans_operator_2d->m_LocalOrigin->m_Coordinates.size() < 2)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					double x = trans_operator_2d->m_LocalOrigin->m_Coordinates[0]->m_value*length_factor;
					double y = trans_operator_2d->m_LocalOrigin->m_Coordinates[1]->m_value*length_factor;
					translate = carve::geom::VECTOR(x, y, 0.0);

					if (trans_operator_2d->m_Scale == trans_operator_2d->m_Scale)
					{
						// transOperator2D->m_Scale is not NAN
						scale = trans_operator_2d->m_Scale;
					}
					scale_y = scale;
					scale_z = scale;
					if (trans_operator_2d->m_Axis1 && trans_operator_2d->m_Axis2)
					{
						if (trans_operator_2d->m_Axis1->m_DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (trans_operator_2d->m_Axis2->m_DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}

						local_x.x = trans_operator_2d->m_Axis1->m_DirectionRatios[0];
						local_x.y = trans_operator_2d->m_Axis1->m_DirectionRatios[1];

						local_y.x = trans_operator_2d->m_Axis2->m_DirectionRatios[0];
						local_y.y = trans_operator_2d->m_Axis2->m_DirectionRatios[1];
					}

					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform> non_uniform = dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator2DnonUniform>(transform_operator);
					if (non_uniform)
					{
						if (non_uniform->m_Scale2 == non_uniform->m_Scale2)
						{
							// m_Scale2 is not NAN
							scale_y = non_uniform->m_Scale2;
						}
					}
				}
				else
				{
					// ENTITY IfcCartesianTransformationOperator3D SUPERTYPE OF(IfcCartesianTransformationOperator3DnonUniform)
					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D> trans_operator_3d = dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3D>(transform_operator);
					if (!trans_operator_3d)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					if (!trans_operator_3d->m_LocalOrigin)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					if (trans_operator_3d->m_LocalOrigin->m_Coordinates.size() < 3)
					{
						std::stringstream ss;
						ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
						throw std::runtime_error(ss.str().c_str());
					}
					translate.x = trans_operator_3d->m_LocalOrigin->m_Coordinates[0]->m_value*length_factor;
					translate.y = trans_operator_3d->m_LocalOrigin->m_Coordinates[1]->m_value*length_factor;
					translate.z = trans_operator_3d->m_LocalOrigin->m_Coordinates[2]->m_value*length_factor;
					if (trans_operator_3d->m_Scale == trans_operator_3d->m_Scale)
					{
						// m_Scale is not NAN
						scale = trans_operator_3d->m_Scale;
					}
					scale_y = scale;
					scale_z = scale;
					if (trans_operator_3d->m_Axis1 && trans_operator_3d->m_Axis2 && trans_operator_3d->m_Axis3)
					{
						shared_ptr<typename IfcEntityTypesT::IfcDirection> axis1 = trans_operator_3d->m_Axis1;
						shared_ptr<typename IfcEntityTypesT::IfcDirection> axis2 = trans_operator_3d->m_Axis2;
						shared_ptr<typename IfcEntityTypesT::IfcDirection> axis3 = trans_operator_3d->m_Axis3;
						if (axis1->m_DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (axis2->m_DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						if (axis3->m_DirectionRatios.size() < 2)
						{
							std::stringstream ss;
							ss << "IfcCartesianTransformationOperator is not valid ";// << __func__;
							throw std::runtime_error(ss.str().c_str());
						}
						local_x.x = axis1->m_DirectionRatios[0];
						local_x.y = axis1->m_DirectionRatios[1];
						local_x.z = axis1->m_DirectionRatios[2];

						local_y.x = axis2->m_DirectionRatios[0];
						local_y.y = axis2->m_DirectionRatios[1];
						local_y.z = axis2->m_DirectionRatios[2];

						local_z.x = axis3->m_DirectionRatios[0];
						local_z.y = axis3->m_DirectionRatios[1];
						local_z.z = axis3->m_DirectionRatios[2];
					}

					shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform> non_uniform = dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianTransformationOperator3DnonUniform>(transform_operator);
					if (non_uniform)
					{
						if (non_uniform->m_Scale2 == non_uniform->m_Scale2)
						{
							scale_y = non_uniform->m_Scale2;
						}
						if (non_uniform->m_Scale3 == non_uniform->m_Scale3)
						{
							scale_z = non_uniform->m_Scale3;
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

				if (axis2placement3d->m_Location)
				{
					std::vector<shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords = axis2placement3d->m_Location->m_Coordinates;
					if (coords.size() > 2)
					{
						location = carve::geom::VECTOR(coords[0]->m_value*length_factor, coords[1]->m_value*length_factor, coords[2]->m_value*length_factor);
					}
					else if (coords.size() > 1)
					{
						location = carve::geom::VECTOR(coords[0]->m_value*length_factor, coords[1]->m_value*length_factor, 0.0);
					}
				}

				if (axis2placement3d->m_Axis)
				{
					// local z-axis
					std::vector<double>& axis = axis2placement3d->m_Axis->m_DirectionRatios;

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
			//	axis2placement3d->m_Location = shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>( new typename IfcEntityTypesT::IfcCartesianPoint( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->m_Location );
			//	axis2placement3d->m_Location->m_Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.x/length_factor ) ) );
			//	axis2placement3d->m_Location->m_Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.y/length_factor ) ) );
			//	axis2placement3d->m_Location->m_Coordinates.push_back( shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>( new typename IfcEntityTypesT::IfcLengthMeasure( translate.z/length_factor ) ) );
			//
			//	axis2placement3d->m_Axis = shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->m_Axis );
			//	axis2placement3d->m_Axis->m_DirectionRatios.push_back( local_z.x );
			//	axis2placement3d->m_Axis->m_DirectionRatios.push_back( local_z.y );
			//	axis2placement3d->m_Axis->m_DirectionRatios.push_back( local_z.z );
			//
			//	axis2placement3d->m_RefDirection = shared_ptr<typename IfcEntityTypesT::IfcDirection>( new typename IfcEntityTypesT::IfcDirection( entity_id++ ) );
			//	vec_entities.push_back( axis2placement3d->m_RefDirection );
			//	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back( local_x.x );
			//	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back( local_x.y );
			//	axis2placement3d->m_RefDirection->m_DirectionRatios.push_back( local_x.z );
			//}
		};
	}
}

#endif
