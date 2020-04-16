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

#include "ConverterBase.h"

#include "BlueFramework/Core/Diagnostics/log.h"



/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {
			template <
				class IfcEntityTypesT
			>
			class PlacementConverterT : public ConverterBaseT<IfcEntityTypesT>
			{
			public:
				//! Constructor
				PlacementConverterT(
					std::shared_ptr<GeometrySettings> geomSettings,
					std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter)
					:
					ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter)
				{
				}

				//! Virtual destructor
				virtual ~PlacementConverterT()
				{

				}

					// **************************************************************************************************************************//
					//	IfcPlacement (http://www.buildingsmart-tech.org/ifc/IFC4x1/RC3/html/schema/ifcgeometryresource/lexical/ifcplacement.htm) //
					//	ABSTRACT SUPERTYPE OF IfcAxis1Placement, IfcAxis2Placement2D, IfcAxis2Placement3D										 //
					// **************************************************************************************************************************//

					void convertIfcPlacement(
						const std::shared_ptr<typename IfcEntityTypesT::IfcPlacement> placement,
						carve::math::Matrix& matrix)
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
							convertIfcAxis2Placement2D(axis2placement2d, matrix);
						}

						// (3/3) IfcAxis2Placement3D SUBTYPE OF IfcPlacement
						else if(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement)) {
							std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(placement);
							convertIfcAxis2Placement3D(axis2placement3d, matrix);
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
					void convertIfcAxis2Placement2D(
						const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d,
						carve::math::Matrix& matrix)
					{

						carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
						carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

						double length_factor = UnitConvert()->getLengthInMeterFactor();

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

						// produce a quaternion
						matrix = carve::math::Matrix(
							local_x.x, local_y.x, local_z.x, translate.x,
							local_x.y, local_y.y, local_z.y, translate.y,
							local_x.z, local_y.z, local_z.z, translate.z,
							0, 0, 0, 1);
					}

					// Function 2: Convert IfcAxis2Placement3D.
					void convertIfcAxis2Placement3D(
						const std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d,
						carve::math::Matrix& matrix)
					{
						carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
						carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
						carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
						carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
						carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

						double length_factor = UnitConvert()->getLengthInMeterFactor();

						// Location type IfcCartesianPoint
						if(axis2placement3d->Location) {

							auto& coords = axis2placement3d->Location->Coordinates;

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

						// produce a quaternion
						matrix = carve::math::Matrix(
							local_x.x, local_y.x, local_z.x, translate.x,
							local_x.y, local_y.y, local_z.y, translate.y,
							local_x.z, local_y.z, local_z.z, translate.z,
							0, 0, 0, 1);
					}

					// Function 3: Convert IfcObjectPlacement
					void convertIfcObjectPlacement(
						const std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement> object_placement,
						carve::math::Matrix& matrix,
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

						// (1/3) IfcLocalPLacement SUBTYPE OF IfcObjectPlacement
						std::shared_ptr<typename IfcEntityTypesT::IfcLocalPlacement> local_placement =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLocalPlacement>(object_placement);
						if(local_placement) {
							// Relative Placement type IfcAxis2Placement [1:1]					
							decltype(local_placement->RelativePlacement)& axis2placement = local_placement->RelativePlacement;
							carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());

							switch(axis2placement.which()) {
							case 0:
								convertIfcAxis2Placement2D(axis2placement.get<0>().lock(), relative_placement);
								break;
							case 1:
								convertIfcAxis2Placement3D(axis2placement.get<1>().lock(), relative_placement);
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
								convertIfcObjectPlacement(local_object_placement.lock(), relative_placement, already_applied);
								object_placement_matrix = relative_placement*object_placement_matrix;
							}
							else {
								// If reference to Object is omitted, then the local placement is given to the WCS, established by the geometric representation context.
									//carve::math::Matrix context_matrix( carve::math::Matrix::IDENT() );
									//applyContext( context, context_matrix, length_factor, placement_already_applied );
									//object_placement_matrix = context_matrix*object_placement_matrix;
							}
						} // end if IfcLocalPlacement

						// (2/3) IfcGridPlacement SUBTYPE OF IfcObjectPlacement
						std::shared_ptr<typename IfcEntityTypesT::IfcGridPlacement> grid_placement =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGridPlacement>(object_placement);
						if( grid_placement ) {

							BLUE_LOG(warning) << grid_placement->getErrorLog() << ": Not implemented";

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

						} // end if IfcGridPlacement

						// (3/3) IfcLinearPlacement SUBTYPE OF IfcObjectPlacement
						std::shared_ptr<typename IfcEntityTypesT::IfcLinearPlacement > linear_placement =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLinearPlacement>(object_placement);
						if (linear_placement) {
							// TODO implement

							// ENTITY IfcLinearPlacement
							//  SUBTYPE OF(IfcObjectPlacement);
							//   PlacementRelTo : IfcCurve;			// IFC4x1
							//   PlacementMeasuredAlong: IfcCurve;  // from IFC4x2+
							//   Distance: IfcDistanceExpression;
							//   Orientation: OPTIONAL IfcOrientationExpression;
							//   CartesianPosition: OPTIONAL IfcAxis2Placement3D;
							// END_ENTITY;

							// IFC4x1
							std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve = linear_placement->PlacementRelTo.lock();
							std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> ifcBoundedCurve =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(ifcCurve);
							if (!ifcBoundedCurve)
							{
								BLUE_LOG(error) << linear_placement->getErrorLog() << ": Placement along a " << ifcCurve->classname() << " is not supported!";
								return;
							}
							// IFC4x2+
							//std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve = linear_placement->PlacementMeasuredAlong.lock();

							auto& distExpr = linear_placement->Distance;

							auto& orientExpr = linear_placement->Orientation;

							carve::math::Matrix absolute_placement(carve::math::Matrix::IDENT());
							if (linear_placement->CartesianPosition)
								convertIfcAxis2Placement3D(linear_placement->CartesianPosition.get().lock(), absolute_placement);

							double length_factor = UnitConvert()->getLengthInMeterFactor();

							// evaluate distance expression
							// ENTITY IfcDistanceExpression
							//  SUBTYPE OF (IfcGeometricRepresentationItem);
							//   DistanceAlong : IfcLengthMeasure;
							//   OffsetLateral : OPTIONAL IfcLengthMeasure;
							//   OffsetVertical : OPTIONAL IfcLengthMeasure;
							//   OffsetLongitudinal : OPTIONAL IfcLengthMeasure;
							//   AlongHorizontal : OPTIONAL IfcBoolean;
							// END_ENTITY;
							double distAlong = distExpr->DistanceAlong * length_factor;
							carve::geom::vector<3> offsetFromCurve(carve::geom::VECTOR(0.0, 0.0, 0.0));
							bool alongHorizontal = true;
							if (distExpr->OffsetLongitudinal)
								offsetFromCurve.x = distExpr->OffsetLongitudinal.get() * length_factor;
							if (distExpr->OffsetLateral)
								offsetFromCurve.y = distExpr->OffsetLateral.get() * length_factor;
							if (distExpr->OffsetVertical)
								offsetFromCurve.z = distExpr->OffsetVertical.get() * length_factor;
							alongHorizontal = distExpr->AlongHorizontal;

							// calculate the position on and the direction of the base curve
							carve::geom::vector<3>  pointOnCurve	 ( carve::geom::VECTOR(0.0, 0.0, 0.0) ),
													directionOfCurve ( carve::geom::VECTOR(1.0, 0.0, 0.0) );
							convertAlignmentCurveDistAlongToPoint3D( 
								ifcBoundedCurve, distAlong, alongHorizontal, 
								pointOnCurve, directionOfCurve);

							// calculate the position
							object_placement_matrix = absolute_placement; //TODO wrong

							// PlacementRelTo type IfcObjectPlacement [0:1] (introduced in IFC4x2)
							if (linear_placement->PlacementRelTo) {
								// Reference to Object that provides the relative placement by its local coordinate system. 
								decltype(local_placement->PlacementRelTo)::type& local_object_placement = local_placement->PlacementRelTo;
								carve::math::Matrix relative_placement(carve::math::Matrix::IDENT());
								convertIfcObjectPlacement(local_object_placement.lock(), relative_placement, already_applied);
								object_placement_matrix = relative_placement * object_placement_matrix;
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
								//if(std::is_same<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D, OpenInfraPlatform::IFC4X1::IfcCartesianTransformationOperator2D>::value)
								//	scale = std::dynamic_pointer_cast<OpenInfraPlatform::IFC4X1::IfcCartesianTransformationOperator2D>(trans_operator_2d)->Scale;
								//else
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
					// Function allows IfcBoundedCurve as input because of template issues. TODO: change to IfcAlignmentCurve
					void convertAlignmentCurveDistAlongToPoint3D(
						std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> ifcAlignmentCurve,
						double dDistAlongOfPoint,
						bool bDistMeasuredAlongHorizontal,
						carve::geom::vector<3>& vkt3DtargetPoint,
						carve::geom::vector<3>& vkt3DtargetDirection) 					
					{	
						// preset the return values
						vkt3DtargetPoint	 = carve::geom::VECTOR(0., 0., 0.);
						vkt3DtargetDirection = carve::geom::VECTOR(1., 0., 0.);

						// get the length & angle factors
						double length_factor = UnitConvert()->getLengthInMeterFactor();
						double plane_angle_factor = UnitConvert()->getAngleInRadianFactor();

						std::shared_ptr<typename IfcEntityTypesT::IfcAlignmentCurve> alignment_curve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignmentCurve>(ifcAlignmentCurve);
						if (alignment_curve)
						{
							// the vectors of horizontal and vertical segments - used in analysis
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment> > horSegments;
							std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment> > verSegments;

							// Get information from horizontal alignment.
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal> horizontal = alignment_curve->Horizontal.lock();

							if (!horizontal)
							{
								BLUE_LOG(error) << alignment_curve->getErrorLog() << ": No IfcAlignment2DHorizontal!";
								return;
							}

							// Segments type IfcAlignment2DHorizontalSegment L[1:?]
							if (horizontal->Segments.empty()) {
								BLUE_LOG(error) << horizontal->getErrorLog() << ": Segments are emtpy!";
								return;
							}
							horSegments.resize(horizontal->Segments.size());
							std::transform(horizontal->Segments.begin(), horizontal->Segments.end(), horSegments.begin(), [](auto &it) {return it.lock(); });

							// Get information from vertical alignment.
							bool bOnlyHorizontal = false;
							auto vertical = alignment_curve->Vertical; // .lock();

							if (!vertical)
							{
								BLUE_LOG(trace) << alignment_curve->getErrorLog() << ": No IfcAlignment2DVertical! Interpreting as 2D alignment curve.";
								bOnlyHorizontal = true;
							}
							else
							{
								// Segments type IfcAlignment2DHorizontalSegment L[1:?]
								if (vertical->Segments.empty()) {
									BLUE_LOG(error) << vertical->getErrorLog() << ": Segments are emtpy!";
									return;
								}
								verSegments.resize(vertical->Segments.size());
								std::transform(vertical->Segments.begin(), vertical->Segments.end(), verSegments.begin(), [](auto &it) {return it.lock(); });
							}
							
							// the entities relevant to the point trying to be calculated
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment> horizontalSegmentRelevantToPoint;
							std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment> verticalSegmentRelevantToPoint;
							std::shared_ptr<typename IfcEntityTypesT::IfcCurveSegment2D> horCurveGeometryRelevantToPoint;
							// some necessary temporary variables
							double horizSegStartDistAlong = 0.;

							// Iterate over horizontal segments -> find the necessary element
							for (auto it_segment : horSegments) 
							{
								//IfcAlignment2DHorizontalSegment (TangentialContinuity type IfcBoolean [0:1], StartTag type IfcLabel [0:1], EndTag type IfcLabel [0:1], CurveGeometry type IfcCurveSegment2D [1:1])
								horCurveGeometryRelevantToPoint = it_segment->CurveGeometry.lock();

								//********************************************************************
								// some checks
								// Get and interpret information from IfcCurveSegment2D.
								if (!horCurveGeometryRelevantToPoint) {
									BLUE_LOG(error) << it_segment->getErrorLog() << ": No curve geometry.";
									continue;
								}

								// SegmentLength type IfcPositiveLengthMeasure [1:1]
								if (horCurveGeometryRelevantToPoint->SegmentLength < 0) {
									BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog() << ": No curve segment length.";
									continue;
								}
								double horizSegLength = horCurveGeometryRelevantToPoint->SegmentLength * length_factor;
								if (horizSegLength == 0.)
								{
									BLUE_LOG(trace) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Segment length is ZERO?!";
									continue;
								}
								//*********************************************************************

								// if begin of this segment is after the station -> sth went wrong
								if (horizSegStartDistAlong > dDistAlongOfPoint)
								{
									BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Inconsistency! Segment begins after the station.";
									return;
								}

								//*********************************************************************
								// If the end of this segment is further along than the point searched for, 
								//    the point is within this segment -> remember that!
								if (horizSegStartDistAlong + horizSegLength > dDistAlongOfPoint)
								{
									horizontalSegmentRelevantToPoint = it_segment;

									// StartPoint type IfcCartesianPoint [1:1]
									//auto curveSegStartPoint = horizontalSegmentRelevantToPoint->StartPoint.lock();
									//if (!curveSegStartPoint) {
									//	BLUE_LOG(error) << horizontalSegmentRelevantToPoint->getErrorLog() 
									//					<< ": No curve segment start point.";
									//	return;
									//}

									//horizSegStartPointX = curveSegStartPoint->Coordinates[0] * length_factor;
									//horizSegStartPointY = curveSegStartPoint->Coordinates[1] * length_factor;

									//// StartDirection type IfcPlaneAngleMeasure [1:1]
									//// cannot check because StartDirection is IfcPlaneAngleMeasure
									///*if (!horCurveGeometry->StartDirection) {
									//	BLUE_LOG(error) << "No curve segment start direction in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
									//	return;
									//}*/
									//horizSegStartDirection = horCurveGeometry->StartDirection * plane_angle_factor;

									// break the for loop, since we have found the element!
									break;
								} // end if (horizSegStartDistAlong + horizSegLength > dDistAlongOfPoint)
								//********************************************************************

								// If the start of the segment along the alignment equals the point's distance along the alignment, save the segment start point coordinates.
								// horizSegStartDistAlong is the sum of the previous segments (starting with 0 at first segment)

								//else if (horizSegStartDistAlong == pointDistAlong)
								//{
								//	// StartPoint type IfcCartesianPoint [1:1]
								//	auto curveSegStartPoint = horCurveGeometry->StartPoint.lock();
								//	if (!curveSegStartPoint) {
								//		BLUE_LOG(error) << "No curve segment start point in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
								//		return;
								//	}

								//	targetPoint3D.x = curveSegStartPoint->Coordinates[0] * length_factor;
								//	targetPoint3D.y = curveSegStartPoint->Coordinates[1] * length_factor;

								//	break; // todo: Return?
								//} // end if

								horizSegStartDistAlong += horizSegLength;
							} // end horizontal segments iteration
							
							//********************************************************************
							// now check the vertical alignment
							if (!verSegments.empty())
							{
								double verSegStartHeight = 0.;
								double verSegStartGradient = 0.;

								double verSegLength = 0.;
								double verSegDistAlong = 0.;

								//********************************************************************
								// Iterate over vertical segments
								for (auto it_segment : verSegments) {

									// StartDistAlong type IfcLengthMeasure [1:1]
									if (it_segment->StartDistAlong < 0) {
										BLUE_LOG(error) << it_segment->getErrorLog() << ": No start distance along.";
										return;
									}
									verSegDistAlong = it_segment->StartDistAlong * length_factor;

									// HorizontalLength type IfcPositiveLengthMeasure [1:1]
									if (it_segment->HorizontalLength <= 0) {
										BLUE_LOG(error) << it_segment->getErrorLog() << ": No horizontal length.";
										continue;
									}
									verSegLength = it_segment->HorizontalLength * length_factor;

									// If the end of this segment is further along than the point, the point is within this segment.
									if (verSegDistAlong + verSegLength > dDistAlongOfPoint)
									{
										verticalSegmentRelevantToPoint = it_segment;

										// StartHeight type IfcLengthMeasure [1:1]
										// cannot check since StartHeight is IfcLengthMeasure, not IfcPositiveLengthMeasure
										/*if (!it_segment->StartHeight) {
											BLUE_LOG(error) << "No start height in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
											return;
										}*/
										//verSegStartHeight = it_segment->StartHeight * length_factor;

										// StartGradient type IfcRatioMeasure [1:1]
										// cannot check since StartGradient is IfcRatioMeasure
										/*if (!it_segment->StartGradient) {
											BLUE_LOG(error) << "No start gradient in IfcAlignment2DVerticalSegment (Segment ID: " << it_segment->getId() << ").";
											return;
										}*/
										//verSegStartGradient = it_segment->StartGradient;

										break;
									} // end if (verSegDistAlong + verSegLength > dDistAlongOfPoint)

								}// end vertical stations iteration
							} // end if (!verSegments.empty())

							//********************************************************************
							// Calculate x and y coordinates from horizontal segment
							std::shared_ptr<typename IfcEntityTypesT::IfcLineSegment2D> line_segment_2D =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLineSegment2D>(horCurveGeometryRelevantToPoint);
							std::shared_ptr<typename IfcEntityTypesT::IfcCircularArcSegment2D> circular_arc_segment_2D =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircularArcSegment2D>(horCurveGeometryRelevantToPoint);
							std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcTransitionCurveSegment2D>(horCurveGeometryRelevantToPoint);
							
							// some temporary variables
							auto curveSegStartPoint = horCurveGeometryRelevantToPoint->StartPoint.lock();
							if (!curveSegStartPoint) {
								BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog()
									<< ": No curve segment start point.";
								return;
							}
							// x, y
							double horizSegStartPointX = curveSegStartPoint->Coordinates[0] * length_factor;
							double horizSegStartPointY = curveSegStartPoint->Coordinates[1] * length_factor;
							// length
							double horizSegLength = horCurveGeometryRelevantToPoint->SegmentLength * length_factor;
							if( horizSegLength < 0. ) {
								BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog()
									<< ": No curve segment length specified.";
								return;
							}

							// direction
							// StartDirection type IfcPlaneAngleMeasure [1:1]
							// cannot check because StartDirection is IfcPlaneAngleMeasure
							/*if (!horCurveGeometry->StartDirection) {
								BLUE_LOG(error) << "No curve segment start direction in IfcCurveSegment2D (Segment ID: " << it_segment->getId() << ").";
								return;
							}*/
							double horizSegStartDirection = horCurveGeometryRelevantToPoint->StartDirection * plane_angle_factor; // get it in RADIAN

							// types have additional data
							//   -> calculate the exact position within the x,y
							double distanceToStart = dDistAlongOfPoint - horizSegStartDistAlong; // Distance from start of segment to point along alignment.

							// these values should be set after the following if - else if - ...
							double x, y; // the resulting point coordinate
							double dir; //TODO the resulting direction (in radian)

							if (line_segment_2D) 
							{
								// straight line
								// Calculate x and y
								x = horizSegStartPointX + distanceToStart * cos(horizSegStartDirection);
								y = horizSegStartPointY + distanceToStart * sin(horizSegStartDirection);

								// calculate direction
								dir = horizSegStartDirection;

							} // if (line_segment_2D) 
							else if (circular_arc_segment_2D) 
							{
								// Radius type IfcPositiveLengthMeasure [1:1]
								if (circular_arc_segment_2D->Radius <= 0) {
									BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog() << ": No radius.";
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
								double radiusDirection = horizSegStartDirection + M_PI / 2 * (is_CCW ? 3 : 1);
								double centerX = horizSegStartPointX + cos(radiusDirection) * radius;
								double centerY = horizSegStartPointY + sin(radiusDirection) * radius;

								// Angle between x-axis and vector(start, center).
								double angleAlpha = atan2(horizSegStartPointY - centerY, horizSegStartPointX - centerX); 

								// Angle between x-axis and point according to circle direction.
								double angleBeta = angleAlpha + distanceToStart / radius * ( is_CCW ? -1 : 1); 

								// Calculate x and y
								x = centerX + radius * cos(angleBeta);
								y = centerY + radius * sin(angleBeta);

								//TODO calculate direction
								//dir = ?

							} // if (circular_arc_segment_2D) 
							else if (trans_curve_segment_2D) 
							{
								// StartRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
								double startRadius = 0.0;
								if (trans_curve_segment_2D->StartRadius <= 0.) {
									BLUE_LOG(warning) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Start radius NIL, interpreted as infinite.";
								}
								else {
									startRadius = trans_curve_segment_2D->StartRadius * length_factor;
								}
								// EndRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
								double endRadius = 0.0;
								if (trans_curve_segment_2D->EndRadius <= 0.) {
									BLUE_LOG(warning) << horCurveGeometryRelevantToPoint->getErrorLog() << ": End radius NIL, interpreted as infinite.";
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
								// *DONE*: can check boolean this way? cppreference about "!": It has only one operand, to its right, and inverts it, producing false if its operand is true, and true if its operand is false. Basically, it returns the opposite Boolean value of evaluating its operand. 
								/*if (!trans_curve_segment_2D->IsEndRadiusCCW) {
									BLUE_LOG(error) << "No direction information for end of IfcTransitionCurveSegment2D (counterclockwise/clockwise). (Segment ID: " << dHorizontalSegmentRelevantToPoint->getId() << ").";
									return;
								}*/
								bool is_end_ccw = trans_curve_segment_2D->IsEndRadiusCCW;

								auto trans_type = trans_curve_segment_2D->TransitionCurveType;

								//TODO account for the start direction (horizSegStartDirection) -> put it in -dir-
								switch (trans_type) 
								{
								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_BIQUADRATICPARABOLA):
								{
									x = dDistAlongOfPoint;		// x coordinate
									y = 0.0;
									if (x <= horizSegLength / 2)	// y coordinate
									{
										y = pow(x, 4) / (6. * endRadius * horizSegLength * horizSegLength);
									}
									else if (horizSegLength / 2 < x && x <= horizSegLength)
									{
										y = -(pow(x, 4) / (6. * endRadius * pow(horizSegLength, 2)) + (2. * pow(x, 3)) / (3. * endRadius * horizSegLength)
											- pow(x, 2) / (2. * endRadius) + (horizSegLength * x) / (6. * endRadius) - pow(horizSegLength, 2) / (48. * endRadius));
									} // end elseif
									else
									{
										BLUE_LOG(error) << "Y coordinate not defined for biquadratic parabola (Segment ID: " << trans_curve_segment_2D->getErrorLog() << ").";
										break;
									}
								} // end case BIQUADRATICPARABOLA
								break;

								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_BLOSSCURVE):
								{
									// Integration durch Substitution(s.Formel: http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifctransitioncurvetype.htm).
									double teta_up = pow(dDistAlongOfPoint + horizSegLength, 3) / (endRadius * pow(horizSegLength, 2))
										- pow(dDistAlongOfPoint + horizSegLength, 4) / (2 * endRadius * pow(horizSegLength, 3)); //values for upper boundary of integral
									double teta_low = pow(dDistAlongOfPoint, 3) / (endRadius * pow(horizSegLength, 2))
										- pow(dDistAlongOfPoint, 4) / (2 * endRadius * pow(horizSegLength, 3)); //values for lower boundary of integral
									double teta_deriv_up = 2 * pow(dDistAlongOfPoint + horizSegLength, 2) / endRadius * pow(horizSegLength, 2)
										- 4 * pow(dDistAlongOfPoint + horizSegLength, 3) / 2 * endRadius*pow(horizSegLength, 3);
									double teta_deriv_low = 2 * pow(dDistAlongOfPoint, 2) / endRadius * pow(horizSegLength, 2)
										- 4 * pow(dDistAlongOfPoint, 3) / 2 * endRadius*pow(horizSegLength, 3);
									x = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;
									y = -cos(teta_up) / teta_deriv_up + cos(teta_low) / teta_deriv_low;
									
								} // end case BLOSSCURVE
								break;

								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_CLOTHOIDCURVE):
								{
									x = dDistAlongOfPoint * (1 - pow(dDistAlongOfPoint, 4) / 40 * pow(endRadius, 2) * pow(horizSegLength, 2) + pow(dDistAlongOfPoint, 8) / 3456 * pow(endRadius, 4) * pow(horizSegLength, 4));
									y = (pow(dDistAlongOfPoint, 3) / 6 * endRadius*horizSegLength) * (1 - pow(dDistAlongOfPoint, 4) / 56 * pow(endRadius, 2) * pow(horizSegLength, 2) + pow(dDistAlongOfPoint, 8) / 7040 * pow(endRadius, 4) * pow(horizSegLength, 4));
								} // end case CLOTHOIDCURVE
								break;

								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_COSINECURVE):
								{
									double psi = M_PI * dDistAlongOfPoint / horizSegLength;
									x = dDistAlongOfPoint - (pow(horizSegLength, 2) / (8 * pow(M_PI, 2) * pow(endRadius, 2))) * horizSegLength / M_PI
										* ((pow(psi, 3) / 3) + (psi / 2 - sin(psi) * cos(psi) / 2) - 2 * (sin(psi) - psi * cos(psi)));
									y = horizSegLength * (horizSegLength / (2 * pow(M_PI, 2) * endRadius) * (pow(psi, 2) / 2 + cos(psi) - 1)
										- (pow(horizSegLength, 3) / (48 * pow(M_PI, 4) * pow(endRadius, 3)))
										* (pow(psi, 4) / 4 + pow(sin(psi), 2) * cos(psi) / 3 - 16 * cos(psi) / 3 + 3 * pow(psi, 2) * cos(psi)
											- 6 * psi * sin(psi) + 3 * pow(psi, 2) / 4 - 3 * psi * sin(2 * psi) / 4 - 3 * cos(2 * psi) / 8 + 137 / 24));
								} // end case COSINECURVE
								break;

								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_CUBICPARABOLA):
								{
									x = dDistAlongOfPoint;
									y = pow(x, 3) / (6 * endRadius * horizSegLength);
								} // end case CUBICPARABOLA
								break;

								case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_SINECURVE):
								{
									double psi = (2 * M_PI * dDistAlongOfPoint) / horizSegLength;
									x = dDistAlongOfPoint * (1 - pow(horizSegLength, 2) / (32 * pow(M_PI, 4)*pow(endRadius, 2) - (pow(horizSegLength, 3) / 3840 * pow(M_PI, 5)*pow(endRadius, 2)))
										* (3 * pow(psi, 5) - 20 * pow(psi, 3) + 30 * psi - (240 - 60 * pow(psi, 2)*sin(psi) + 30 * cos(psi)*sin(psi) + 120 * psi*cos(psi))));
									// Integration durch Substitution (s. Formel: http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcgeometryresource/lexical/ifctransitioncurvetype.htm).
									double teta_up = pow((dDistAlongOfPoint + horizSegLength), 2) / (2 * endRadius*horizSegLength) + (horizSegLength / (4 * pow(M_PI, 2)*endRadius)) * (cos(2 * M_PI*(dDistAlongOfPoint + horizSegLength) / horizSegLength) - 1);
									double teta_low = pow((dDistAlongOfPoint + horizSegLength), 2) / (2 * endRadius*horizSegLength) + (horizSegLength / (4 * pow(M_PI, 2)*endRadius)) * (cos(2 * M_PI*(dDistAlongOfPoint) / horizSegLength) - 1);
									double teta_deriv_up = 2 * (dDistAlongOfPoint + horizSegLength) / 2 * endRadius*horizSegLength;
									double teta_deriv_low = 2 * dDistAlongOfPoint / 2 * endRadius*horizSegLength;
									y = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;

								} // end case SINECURVE
								break;
								} // end switch (trans_type)

							} // end if (trans_curve_segment_2D) 

							// set the x,y
							vkt3DtargetPoint.x = x;
							vkt3DtargetPoint.y = y;

							// set the direction
							dir = dir * 180 / M_PI; // convert "dir" from deg to rad (for use of sin and cos). TODO: if used more than once, write function.
							vkt3DtargetDirection.x = cos(dir);
							vkt3DtargetDirection.y = sin(dir);
								
							// normalize the direction
							vkt3DtargetDirection /= vkt3DtargetDirection.length();
							// end x, y coordinate calculation
							// end x, y direction  calculation
							//********************************************************************

							//********************************************************************
							// Calculate z coordinate from vertical alignment, if there.
							if ( verticalSegmentRelevantToPoint )
							{
								std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegLine> v_seg_line_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>(verticalSegmentRelevantToPoint);
								std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc> v_seg_circ_arc_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>(verticalSegmentRelevantToPoint);
								std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc> v_seg_par_arc_2D =
									std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc>(verticalSegmentRelevantToPoint);

								// common parameters
								// StartDistAlong type IfcLengthMeasure [1:1]
								double verSegDistAlong = verticalSegmentRelevantToPoint->StartDistAlong * length_factor;
								double distVerToStart = dDistAlongOfPoint - verSegDistAlong;

								// HorizontalLength type IfcPositiveLengthMeasure [1:1]
								double verSegLength = verticalSegmentRelevantToPoint->HorizontalLength * length_factor;

								// StartHeight type IfcLengthMeasure [1:1]
								double verSegStartHeight = verticalSegmentRelevantToPoint->StartHeight * length_factor;

								// StartGradient type IfcRatioMeasure [1:1]
								double verSegStartGradient = verticalSegmentRelevantToPoint->StartGradient;

								// the results
								double dz = 0.0; // the height above verSegStartHeight
								double gradient = 0.0; //TODO set the correct value for the gradient
								if (v_seg_line_2D)
								{
									dz = verSegStartGradient * distVerToStart;
									gradient = verSegStartGradient;
								}
								else if (v_seg_circ_arc_2D)
								{
									// Radius type IfcPositiveLengthMeasure [1:1] 
									if (v_seg_circ_arc_2D->Radius <= 0.) {
										BLUE_LOG(error) << verticalSegmentRelevantToPoint->getErrorLog() << ": No radius.";
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

									if (is_convex == true) {
										dz = -sqrt(pow(radius, 2) - pow(distVerToStart + (verSegStartGradient * radius) / sqrt(1 + pow(verSegStartGradient, 2)), 2))
											+ radius / sqrt(1 + pow(verSegStartGradient, 2)); // Crest (decreasing gradient)
									}
									else {
										dz = sqrt(pow(radius, 2) - pow(distVerToStart - (verSegStartGradient * radius) / sqrt(1 + pow(verSegStartGradient, 2)), 2))
											- radius / sqrt(1 + pow(verSegStartGradient, 2)); // Sag (increasing gradient)
									}
								}
								else if (v_seg_par_arc_2D)
								{
									// ParabolaConstant type IfcPositiveLengthMeasure [1:1]
									if (v_seg_par_arc_2D->ParabolaConstant <= 0.) {
										BLUE_LOG(error) << verticalSegmentRelevantToPoint->getErrorLog() << ": No parabola constant.";
										return;
									}
									double arc_const = v_seg_par_arc_2D->ParabolaConstant * length_factor; //TODO really needed?

									// IsConvex type IfcBoolean [1:1]
									// TODO: can check boolean this way?
									/*if (!v_seg_par_arc_2D->IsConvex) {
										BLUE_LOG(error) << "No curvature information in IfcAlignment2DVerSegParabolicArc (convex/concave) (Segment ID : " << verticalSegmentRelevantToPoint->getId() << ").";
										return;
									}*/
									bool is_convex = v_seg_par_arc_2D->IsConvex;

									double parabola_radius = is_convex ? -arc_const : arc_const;
									double parabola_gradient = distVerToStart / parabola_radius + verSegStartGradient;
									dz = distVerToStart * (parabola_gradient + verSegStartGradient) * 0.5; //TODO why + verSegStartGradient (see above line)
								}

								// set the coordinate
								vkt3DtargetPoint.z = verSegStartHeight + dz;

								// set the vertical direction
								vkt3DtargetDirection.z = gradient;
								// normalize the direction again
								vkt3DtargetDirection /= vkt3DtargetDirection.length();
							}// end if ( verticalSegmentRelevantToPoint ) --> z coordinate calculation
							//********************************************************************

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
