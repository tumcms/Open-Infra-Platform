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

#include "GeomUtils.h"
#include "ConverterBase.h"

#include <BlueFramework/Core/Diagnostics/log.h>

#include <EXPRESS/EXPRESSReference.h>
#include <EXPRESS/EXPRESSOptional.h>

/**********************************************************************************************/

namespace OpenInfraPlatform {
    namespace Core {
        namespace IfcGeometryConverter {

            /*! \brief Converter functionality for \c IfcPlacement's and \c IfcObjectPlacement's subtypes.
            *
            * This class includes converter functions for
            * \c IfcPlacement and its subtypes,
            * \c IfcObjectPlacement and its subtypes,
            * \c IfcCartesianPoint and
            * \c IfcDirection.
            *
            * \param IfcEntityTypesT The IFC version templates
            */
			template <
				class IfcEntityTypesT
			>
				class PlacementConverterT : public ConverterBaseT<IfcEntityTypesT>, public std::enable_shared_from_this<PlacementConverterT<IfcEntityTypesT>> {
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

				/*! \brief Converts \c IfcPoint to a vector.
				 * 
				 * \param[in]	point	\c IfcPoint entity to be interpreted.
				 * 
				 * \return		Calculated 2D or 3D vector.
				 * 
				 * \note The point's coordinates are scaled according to the unit conversion factor.
				 */
				carve::geom::vector<3> convertIfcPoint(
					const EXPRESSReference<typename IfcEntityTypesT::IfcPoint>& point
				) const throw(...)
				{
					// **************************************************************************************************************************
					// ENTITY IfcPoint
					//  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcpoint.htm
					// ABSTRACT SUPERTYPE OF(ONEOF(IfcCartesianPoint, IfcPointOnCurve, IfcPointOnSurface))
					//	SUBTYPE OF(IfcGeometricRepresentationItem);
					// END_ENTITY;
					// **************************************************************************************************************************
					// IfcCartesianPoint
					if (point.isOfType<typename IfcEntityTypesT::IfcCartesianPoint>())
						return convertIfcCartesianPoint(point.as<typename IfcEntityTypesT::IfcCartesianPoint>());

					// IfcPointOnCurve & IfcPointOnSurface are not supported
					throw oip::UnhandledException(point);
				}

                /*! \brief Converts \c IfcCartesianPoint to a 3D vector.
				 * 
                 * \param[in]	cartesianPoint	\c IfcCartesianPoint entity to be interpreted.
				 *
                 * \return		Calculated 2D or 3D vector.
				 *
                 * \note The point's coordinates are scaled according to the unit conversion factor.
                 */
				carve::geom::vector<3> convertIfcCartesianPoint(
                    const EXPRESSReference<typename IfcEntityTypesT::IfcCartesianPoint>& cartesianPoint
                ) const throw(...)
                {
                    // **************************************************************************************************************************
                    // IfcCartesianPoint
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifccartesianpoint.htm
                    // ENTITY IfcCartesianPoint
                    //	SUBTYPE OF(IfcPoint);
                    //		Coordinates: LIST[1:3] OF IfcLengthMeasure;
                    //	DERIVE
                    //		Dim : IfcDimensionCount: = HIINDEX(Coordinates);
                    //	WHERE
                    //		CP2Dor3D : HIINDEX(Coordinates) >= 2;
                    // END_ENTITY;
                    // **************************************************************************************************************************
					// check input
					if (cartesianPoint.expired())
						throw oip::ReferenceExpiredException(cartesianPoint);

                    // set to default
					carve::geom::vector<3> point = carve::geom::VECTOR(0.0, 0.0, 0.0);
                    // read the coordinates
					auto& coords = cartesianPoint->Coordinates;
					switch (coords.size())
					{
					case 3:
						point.z = coords[2];
					case 2:
						point.y = coords[1];
					case 1:
						point.x = coords[0];
						break;
					default:
						throw oip::InconsistentGeometryException( cartesianPoint, "Number of coordinates is inconsistent.");
					}

                    // scale the lengths according to the unit conversion & return
					return point * UnitConvert()->getLengthInMeterFactor();
                }

                /*! \brief Converts \c IfcDirection to a 3D vector.
				 *
                 * \param[in]	ifcDirection	IfcDirection entity to be interpreted.
                 * \returns    Calculated 2D or 3D vector.
				 * 
                 * \note The direction is normalized.
                 */
                carve::geom::vector<3> convertIfcDirection(
					const EXPRESSReference<typename IfcEntityTypesT::IfcDirection>& ifcDirection
				) const throw(...)
                {
                    // **************************************************************************************************************************
                    // IfcDirection
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcdirection.htm
                    // ENTITY IfcDirection
                    //	SUBTYPE OF(IfcGeometricRepresentationItem);
                    //		DirectionRatios: LIST[2:3] OF IfcReal;
                    //	DERIVE
                    //		Dim : IfcDimensionCount: = HIINDEX(DirectionRatios);
                    //	WHERE
                    //		MagnitudeGreaterZero : SIZEOF(QUERY(Tmp < *DirectionRatios | Tmp <> 0.0)) > 0;
                    // END_ENTITY;
                    // **************************************************************************************************************************
					// check input
					if (ifcDirection.expired()) 
						throw oip::ReferenceExpiredException(ifcDirection);

					// set to default
					carve::geom::vector<3> direction = carve::geom::VECTOR(1., 0., 0.);
					// read the coordinates
					auto& ratios = ifcDirection->DirectionRatios;
					switch (ratios.size())
					{
					case 3:
						direction.z = ratios[2];
					case 2:
						direction.y = ratios[1];
					case 1:
						direction.x = ratios[0];
						break;
					default:
						throw oip::InconsistentGeometryException(ifcDirection, "Number of coordinates is inconsistent.");
					}

					// check
					if( direction.isZero( GeomSettings()->getPrecision() ) )
						throw oip::InconsistentGeometryException(ifcDirection, "Magnitude is zero.");

                    // normalize the direction
                    direction.normalize();
					// returns
                    return direction;
                }

				/*! \brief Converts \c IfcVector to a 3D vector.
				 *
				 * \param[in]	ifcVector	IfcVector entity to be interpreted.
				 * \returns    Calculated 2D or 3D vector.
				 */
				carve::geom::vector<3> convertIfcVector(
					const EXPRESSReference<typename IfcEntityTypesT::IfcVector>& ifcVector
				) const throw(...)
				{
					// **************************************************************************************************************************
					// IfcVector
					//  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifcvector.htm
					//	ENTITY IfcVector
					//		SUBTYPE OF(IfcGeometricRepresentationItem);
					//		Orientation: IfcDirection;
					//		Magnitude: IfcLengthMeasure;
					//	DERIVE
					//		Dim : IfcDimensionCount: = Orientation.Dim;
					//	WHERE
					//		MagGreaterOrEqualZero : Magnitude >= 0.0;
					//	END_ENTITY;
					// **************************************************************************************************************************
					// check input
					if (ifcVector.expired())
						throw oip::ReferenceExpiredException(ifcVector);

					// read direction
					carve::geom::vector<3> direction = convertIfcDirection(ifcVector->Orientation);

					// ignore magnitude if == 0
					if (ifcVector->Magnitude != 0.)
						// scale the lengths according to the unit conversion & return
						return direction * ifcVector->Magnitude * UnitConvert()->getLengthInMeterFactor();
					else
						// otherwise return normalized direction
						return direction;
				}


                /*! \brief Converts \c IfcPlacement to a transformation matrix.
				 * 
                 * \param[in]	placement	\c IfcPlacement entity to be interpreted.
				 *
                 * \returns		Calculated transformation matrix.
                 */
				carve::math::Matrix convertIfcPlacement(
                    const EXPRESSReference<typename IfcEntityTypesT::IfcPlacement>& placement
                ) const throw(...)
                {
                    // **************************************************************************************************************************
                    // IfcPlacement 
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcplacement.htm
                    // ENTITY IfcPlacement
                    //	ABSTRACT SUPERTYPE OF(ONEOF(IfcAxis1Placement, IfcAxis2Placement2D, IfcAxis2Placement3D))
                    //	SUBTYPE OF(IfcGeometricRepresentationItem);
                    //		Location: IfcCartesianPoint;
                    //	DERIVE
                    //		Dim : IfcDimensionCount: = Location.Dim;
                    // END_ENTITY;									 
                    // **************************************************************************************************************************
					// check input
					if (placement.expired()) 
						throw oip::ReferenceExpiredException(placement);

                    // (1/3) IfcAxis1Placement SUBTYPE OF IfcPlacement
                    if(placement.isOfType<typename IfcEntityTypesT::IfcAxis1Placement>()) {
                        throw oip::UnhandledException(placement);
                    }
                    // (2/3) IfcAxis2Placement2D SUBTYPE OF IfcPlacement 
                    else if(placement.isOfType<typename IfcEntityTypesT::IfcAxis2Placement2D>()) {
                        return convertIfcAxis2Placement2D( placement.as<typename IfcEntityTypesT::IfcAxis2Placement2D>() );
                    }
                    // (3/3) IfcAxis2Placement3D SUBTYPE OF IfcPlacement
                    else if(placement.isOfType<typename IfcEntityTypesT::IfcAxis2Placement3D>()) {
                        return convertIfcAxis2Placement3D( placement.as<typename IfcEntityTypesT::IfcAxis2Placement3D>());
                    }
					// anything else is not supported
					throw oip::UnhandledException(placement);
                }


				/*! \brief Converts \c IfcAxis2Placement2D to a transformation matrix.
				 *
				 * \param[in]	axis2placement2d	\c IfcAxis2Placement2D entity to be interpreted.
				 * 
				 * \return				Calculated transformation matrix.
				 */
				carve::math::Matrix convertIfcAxis2Placement2D(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement2D>& axis2placement2d
				) const throw(...)
                {
                    // **************************************************************************************************************************
                    // IfcAxis2Placement2D 
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcaxis2placement2d.htm
                    // ENTITY IfcAxis2Placement2D
                    //	SUBTYPE OF(IfcPlacement);
                    //		RefDirection: OPTIONAL IfcDirection;
                    //	DERIVE
                    //		P : LIST[2:2] OF IfcDirection : = IfcBuild2Axes(RefDirection);
                    //	WHERE
                    //		RefDirIs2D : (NOT(EXISTS(RefDirection))) OR(RefDirection.Dim = 2);
                    //		LocationIs2D: SELF\IfcPlacement.Location.Dim = 2;
                    // END_ENTITY;
                    // **************************************************************************************************************************
					// check input
					if (axis2placement2d.expired())
						throw oip::ReferenceExpiredException(axis2placement2d);

					// defaults
                    carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
                    carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
                    carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
                    carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
                    carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0)); // defaults to (1.0,0.0) according to the specification

                    // interpret Location 
					translate = convertIfcCartesianPoint( axis2placement2d->Location );

                    // interpret RefDirection [OPTIONAL]
                    if(axis2placement2d->RefDirection) {
                        ref_direction = convertIfcDirection(axis2placement2d->RefDirection);
                    }

                    // calculate
                    local_x = ref_direction;
                    // ref_direction can be just in the x-z-plane, not perpendicular to y and z.
                    //  --> so re-compute local x					
                    local_y = carve::geom::cross(local_z, local_x);
                    local_x = carve::geom::cross(local_y, local_z);

                    // normalize the direction vectors
                    local_x.normalize();
                    local_y.normalize();
                    local_z.normalize();

                    return carve::math::Matrix(
                        local_x.x, local_y.x, local_z.x, translate.x,
                        local_x.y, local_y.y, local_z.y, translate.y,
                        local_x.z, local_y.z, local_z.z, translate.z,
                        0, 0, 0, 1);
                }


				/*! \brief Converts \c IfcAxis2Placement3D to a transformation matrix.
				 *
				 * \param[in]	axis2placement3d	\c IfcAxis2Placement3D entity to be interpreted.
				 *
				 * \return				Calculated transformation matrix.
				 */
				carve::math::Matrix convertIfcAxis2Placement3D(
					const EXPRESSReference<typename IfcEntityTypesT::IfcAxis2Placement3D>& axis2placement3d
				) const throw(...)
                {
                    // **************************************************************************************************************************
                    // IfcAxis2Placement2D 
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/schema/ifcgeometryresource/lexical/ifcaxis2placement3d.htm
                    // ENTITY IfcAxis2Placement3D
                    //	SUBTYPE OF(IfcPlacement);
                    //		Axis: OPTIONAL IfcDirection;
                    //		RefDirection: OPTIONAL IfcDirection;
                    //	DERIVE
                    //		P : LIST[3:3] OF IfcDirection : = IfcBuildAxes(Axis, RefDirection);
                    //	WHERE
                    //		LocationIs3D : SELF\IfcPlacement.Location.Dim = 3;
                    //		AxisIs3D: (NOT(EXISTS(Axis))) OR(Axis.Dim = 3);
                    //		RefDirIs3D: (NOT(EXISTS(RefDirection))) OR(RefDirection.Dim = 3);
                    //		AxisToRefDirPosition: (NOT(EXISTS(Axis))) OR(NOT(EXISTS(RefDirection))) OR(IfcCrossProduct(Axis, RefDirection).Magnitude > 0.0);
                    //		AxisAndRefDirProvision: NOT((EXISTS(Axis)) XOR(EXISTS(RefDirection)));
                    // END_ENTITY;
                    // **************************************************************************************************************************
                    // check input
					if(axis2placement3d.expired())
                        throw oip::ReferenceExpiredException(axis2placement3d);

					// defaults
                    carve::geom::vector<3>  translate(carve::geom::VECTOR(0.0, 0.0, 0.0));
                    carve::geom::vector<3>  local_x(carve::geom::VECTOR(1.0, 0.0, 0.0));
                    carve::geom::vector<3>  local_y(carve::geom::VECTOR(0.0, 1.0, 0.0));
                    carve::geom::vector<3>  local_z(carve::geom::VECTOR(0.0, 0.0, 1.0));
                    carve::geom::vector<3>  ref_direction(carve::geom::VECTOR(1.0, 0.0, 0.0));

                    // interpret Location
					translate = convertIfcCartesianPoint(axis2placement3d->Location);

                    // interpret RefDirection [OPTIONAL]
                    if(axis2placement3d->RefDirection) {
                        ref_direction = convertIfcDirection(axis2placement3d->RefDirection);
                    }

                    // interpret Axis [OPTIONAL]
                    if(axis2placement3d->Axis) {
                            local_z = convertIfcDirection(axis2placement3d->Axis);
                    }

                    // calculate
                    local_x = ref_direction;
                    // ref_direction can be just in the x-z-plane, not perpendicular to y and z.
                    //  --> so re-compute local x					
                    local_y = carve::geom::cross(local_z, local_x);
                    local_x = carve::geom::cross(local_y, local_z);

                    // normalize the direction vectors
                    local_x.normalize();
                    local_y.normalize();
                    local_z.normalize();

                    // produce a quaternion
                    return carve::math::Matrix(
                        local_x.x, local_y.x, local_z.x, translate.x,
                        local_x.y, local_y.y, local_z.y, translate.y,
                        local_x.z, local_y.z, local_z.z, translate.z,
                        0, 0, 0, 1);
                }
					

				/**
				 * @brief Converts \c IfcAxis2Placement select and returns transformation matrix.
				 * 
				 * @param axis_placement The \c IfcAxis2Placement to convert
				 * @return The converted position
				 *  
				 * @note The select type IfcAxis2Placement can either be a \c IfcAxis2Placement2D or an \c IfcAxis2Placement3D
				 * and the respective convert function for the actually held type is called.
				 */
				carve::math::Matrix convertIfcAxis2Placement(
					const typename IfcEntityTypesT::IfcAxis2Placement& axis_placement
				) const throw(...)
                {
					// **************************************************************************************************************************
					// RelativePlacement				
                    // TYPE IfcAxis2Placement = SELECT (
                    //	IfcAxis2Placement2D,
                    //	IfcAxis2Placement3D);
                    // END_TYPE;
					// **************************************************************************************************************************
                    switch(axis_placement.which()) {
                    case 0:
                        return convertIfcAxis2Placement2D(axis_placement.get<0>());
                    case 1:
                        return convertIfcAxis2Placement3D(axis_placement.get<1>());
                    default:
                        throw oip::InconsistentModellingException( axis_placement->getErrorLog() );
                    }
                }

                /**
                 * @brief Gets the relative placement in which the local placement is located.
                 * 
                 * @param[in]  alreadyApplied List of already applied transformations, in order to not repeat the same transformation.
                 * @param[in]  local_placement \c IfcLocalPlacement of which to retrieve the relative coordinate system.
                 * @return  The converted placement matrix.
                 * 
                 */
                carve::math::Matrix convertRelativePlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLocalPlacement>& local_placement,
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied
				) const throw(...)
                {
					// check input
					if (local_placement.expired())
						throw oip::ReferenceExpiredException(local_placement);

                    // PlacementRelTo
                    if(local_placement->PlacementRelTo) {
                        // Reference to ObjectPlacement that provides the relative placement by its local coordinate system. 
                        return convertIfcObjectPlacement(local_placement->PlacementRelTo.get(), alreadyApplied);
                    }
                    else {
                        BLUE_LOG(warning) << "Context based local placement computation not supported.";
                        //TODO Georeferencing
                        // If reference to Object is omitted, then the local placement is given to the WCS, established by the geometric representation context.
                        //carve::math::Matrix context_matrix( carve::math::Matrix::IDENT() );
                        //applyContext( context, context_matrix, length_factor, placement_already_applied );
                        //object_placement_matrix = context_matrix*object_placement_matrix;
                        return carve::math::Matrix::IDENT();
                    }
                }

                /*! \brief Converts \c IfcLocalPlacement to a transformation matrix.
				 * 
                 * \param		alreadyApplied		An array of references to already applied \c IfcObjectPlacement-s.
                 * \param[in]	local_placement		\c IfcLocalPlacement entity to be interpreted.
                 * \returns		matrix				Calculated transformation matrix.

                 * Function computes the local placement and stores it in the matrix.
                 */
                carve::math::Matrix convertIfcLocalPlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLocalPlacement>& local_placement,
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied
				) const throw(...)
                {
                    // **************************************************************************************************************************
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifclocalplacement.htm
                    // ENTITY IfcLocalPlacement
                    //	SUBTYPE OF(IfcObjectPlacement);
                    //		PlacementRelTo: OPTIONAL IfcObjectPlacement; // was promoted to ObjectPlacement from IFC4x2+
                    //		RelativePlacement: IfcAxis2Placement;
                    //	WHERE
                    //		WR21 : IfcCorrectLocalPlacement(RelativePlacement, PlacementRelTo);
                    // END_ENTITY;
                    // **************************************************************************************************************************
                    // check input
					if (local_placement.expired())
						throw oip::ReferenceExpiredException(local_placement);

					return convertRelativePlacement(local_placement, alreadyApplied)
						 * convertIfcAxis2Placement(local_placement->RelativePlacement);
                }

                /**
                 * @brief Compare the provided absolute placement in \c IfcLinearPlacement->Position against the passed matrix for identity.
                 * 
                 * @param[in] matrix			Matrix to compare against absolute placement.
                 * @param[in] linear_placement	\c IfcLinearPlacement which holds absolute placement position to compare against computed matrix.
				 *
				 * @exception oip::InconsistentGeometryException the positions do not agree.
				 * @exception oip::ReferenceExpiredException linear_placement reference has expired.
				 * @returns \c true, if the basolute position is not provided or if both positions are the same, otherwise throws oip::InconsistentGeometryException.
                 */
                bool checkLinearPlacementAgainstAbsolutePlacement(
					carve::math::Matrix& matrix, 
					const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement>& linear_placement
				) const throw(...)
                {
					// check input
					if (linear_placement.expired())
						throw oip::ReferenceExpiredException(linear_placement);

                    // check with the provided CartesianPosition [OPTIONAL]
                    if(    linear_placement->CartesianPosition
                        && convertIfcAxis2Placement3D(linear_placement->CartesianPosition.get()) != matrix) 
                            throw oip::InconsistentGeometryException( linear_placement, "Absolute placement and the calculated linear placement do not agree");
					else
						return true; // if none provided or it fits
                }

                /**
                 * @brief Get the offset from \c IfcDistanceExpression object.
                 * 
                 * @param[in] distExpr The \c IfcDistanceExpression from which to compute the offset.
				 *
                 * @return The offsets as 3D vector.
                 */
                carve::geom::vector<3> convertIfcDistanceExpressionOffsets(
					const EXPRESSReference<typename IfcEntityTypesT::IfcDistanceExpression>& distExpr
				) const throw(...)
                {
                    // ***********************************************************
                    // ENTITY IfcDistanceExpression
                    //  SUBTYPE OF (IfcGeometricRepresentationItem);
                    //   DistanceAlong : IfcLengthMeasure;
                    //   OffsetLateral : OPTIONAL IfcLengthMeasure;
                    //   OffsetVertical : OPTIONAL IfcLengthMeasure;
                    //   OffsetLongitudinal : OPTIONAL IfcLengthMeasure;
                    //   AlongHorizontal : OPTIONAL IfcBoolean;
                    // END_ENTITY;
					// ***********************************************************
					// check input
					if (distExpr.expired())
						throw oip::ReferenceExpiredException(distExpr);

                    return carve::geom::VECTOR(
                        distExpr->OffsetLongitudinal.value_or(0.0),
                        distExpr->OffsetLateral.value_or(0.0),
                        distExpr->OffsetVertical.value_or(0.0)
                    ) * UnitConvert()->getLengthInMeterFactor();
                }

				// ************************************************************************************
				// VERSION SPECIFIC STUFF
				// The implementation is in file PlacementConverterImpl.h
				EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve> getCurveOfPlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement>& linearPlacement) const throw (...);
				// This one too
				double convertRelativePlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement>& linear_placement,
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied) const throw(...);
				// ************************************************************************************

                /**
                 * @brief Compute the position of a \c IfcLinearPlacement on it's described curve
				 *  and returns the respective point and the direction at that point
                 * 
                 * @param[in] linear_placement \c IfcLinearPlacement for which to compute the point and direction.
				 * @param[in] relativeDistAlong Account for a relative placement in linear placement.
                 * @return The first vector are the coordinates of the point, the second vector of the direction.
                 */
                std::tuple< carve::geom::vector<3>, carve::geom::vector<3>> calculatePositionOnAndDirectionOfBaseCurve(
					const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement>& linear_placement,
					const double relativeDistAlong = 0.
				) const throw(...)
                {
					// check input
					if (linear_placement.expired())
						throw oip::ReferenceExpiredException(linear_placement);

					// defaults
                    carve::geom::vector<3> pointOnCurve = carve::geom::VECTOR(0.0, 0.0, 0.0);
                    carve::geom::vector<3> directionOfCurve = carve::geom::VECTOR(1.0, 0.0, 0.0);
					
					// account for relative placement
					double dDistAlong = 
						linear_placement->Distance->DistanceAlong * UnitConvert()->getLengthInMeterFactor()
						+ relativeDistAlong;
					
					// convert the point
                    convertBoundedCurveDistAlongToPoint3D(
                        getCurveOfPlacement(linear_placement),
                        dDistAlong,
                        linear_placement->Distance->AlongHorizontal.value_or(true),
                        pointOnCurve,
                        directionOfCurve
                    );
                    return { pointOnCurve, directionOfCurve };
                }

                /**
                 * @brief Computes the rotation matrix from an \c IfcOrientationExpression.
                 * 
                 * @param[in] orientExpr the \c IfcOrientationExpression to convert.
                 * @param[in] translate Optional translation component of transformation.
                 * @returns transformation (rotation+placement) matrix.
                 */
                carve::math::Matrix convertIfcOrientationExpression(
					const EXPRESSReference<typename IfcEntityTypesT::IfcOrientationExpression>& orientExpr,
					const carve::geom::vector<3> translate = carve::geom::VECTOR(0.,0.,0.)
				) const throw(...)
                {
					//check input
					if (orientExpr.expired())
						throw oip::ReferenceExpiredException(orientExpr);

					// defaults
                    carve::geom::vector<3> local_x = carve::geom::VECTOR(1.0, 0.0, 0.0);
                    carve::geom::vector<3> local_y = carve::geom::VECTOR(0.0, 1.0, 0.0);
                    carve::geom::vector<3> local_z = carve::geom::VECTOR(0.0, 0.0, 1.0);

                    // Orientation OPTIONAL
                    // ENTITY IfcOrientationExpression
                    //	SUBTYPE OF(IfcGeometricRepresentationItem);
                    //	LateralAxisDirection: IfcDirection;
                    //	VerticalAxisDirection: IfcDirection;
                    // END_ENTITY;
                    if(orientExpr) {
                        // convert the attributes
                        local_y = convertIfcDirection(orientExpr->LateralAxisDirection);
                        local_z = convertIfcDirection(orientExpr->VerticalAxisDirection);
                        local_x = carve::geom::cross(local_y, local_z);
                    }

                    // produce a rotation matrix
                    return carve::math::Matrix(
                        local_x.x, local_y.x, local_z.x, translate.x,
                        local_x.y, local_y.y, local_z.y, translate.y,
                        local_x.z, local_y.z, local_z.z, translate.z,
                        0, 0, 0, 1);
                }


                /**
                 * @brief Computes the matrix which is multiplied with the offset from the curve to move it to the correct position
                 * 
				 * @param[in] directionOfCurve The tangential 3D direction of the curve at \c pointOnCurve
                 * @param[in] alongHorizontal Is the transformation matrix to be set only along horizontal or is the 3D tangent to remain as is?
                 * @return the transformation matrix
                 */
                carve::math::Matrix calculateCurveOrientationMatrix(
					const carve::geom::vector<3>& directionOfCurve, 
					const bool alongHorizontal
				) const throw(...)
				{
					// check
					if (   alongHorizontal
						&& directionOfCurve.x == 0.
						&& directionOfCurve.y == 0.)
						throw oip::InconsistentGeometryException("Cannot apply alongHorizontal = true, since the direction is strictly vertical!");

					// correct the x-direction
                    carve::geom::vector<3> curve_x(carve::geom::VECTOR(directionOfCurve.x, directionOfCurve.y, alongHorizontal ? 0.0 : directionOfCurve.z));

                    // get the perpendicular to the left of the curve in the x-y plane (curve's coordinate system)
                    carve::geom::vector<3> curve_y(carve::geom::VECTOR(-curve_x.y, curve_x.x, 0.0)); // always lies in the x-y plane

                    // get the vertical as cross product
                    carve::geom::vector<3> curve_z = carve::geom::cross(curve_x, curve_y);

                    // normalize the direction vectors
                    curve_x.normalize();
                    curve_y.normalize();
                    curve_z.normalize();

                    // produce the conversion matrix
                    return carve::math::Matrix(
                        curve_x.x, curve_y.x, curve_z.x, 0.0,
                        curve_x.y, curve_y.y, curve_z.y, 0.0,
                        curve_x.z, curve_y.z, curve_z.z, 0.0,
                        0.0, 0.0, 0.0, 1.0);
                }

                /**
                 * @brief Convert \c IfcLinearPlacement to a transformation matrix
                 * 
                 * @param[in] linear_placement The \c IfcLinearPlacement to be converted
				 * @param[in] alreadyApplied   An array of references to already applied \c IfcObjectPlacement-s.
				 * @return the transformation matrix
                 */
                carve::math::Matrix convertIfcLinearPlacement(
                    const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement> linear_placement,
                    std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied
				) const throw(...)
                {
                    // **************************************************************************************************************************
                    //  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifclinearplacement.htm
                    // ENTITY IfcLinearPlacement
                    //  SUBTYPE OF(IfcObjectPlacement);
                    //   PlacementRelTo : IfcCurve;			// IFC4x1: IfcCurve - IFC4x2+: IfcObjectPlacement
                    //   PlacementMeasuredAlong: IfcCurve;  // from IFC4x2+
                    //   Distance: IfcDistanceExpression;
                    //   Orientation: OPTIONAL IfcOrientationExpression;
                    //   CartesianPosition: OPTIONAL IfcAxis2Placement3D;
                    // END_ENTITY;
                    // **************************************************************************************************************************
					// check input
					if (linear_placement.expired())
						throw oip::ReferenceExpiredException(linear_placement);

                    // 1. get offset from curve
                    carve::geom::vector<3> offsetFromCurve = convertIfcDistanceExpressionOffsets(linear_placement->Distance);
                        
                    // 2. calculate the position on and the direction of the base curve
					// also applay the relative dist along
                    carve::geom::vector<3> pointOnCurve;
                    carve::geom::vector<3> directionOfCurve;
                    std::tie(pointOnCurve, directionOfCurve) = 
						calculatePositionOnAndDirectionOfBaseCurve(linear_placement, convertRelativePlacement(linear_placement, alreadyApplied) );

                    // 3. calculate the rotations
                    // the direction of the curve's tangent = directionOfCurve
					carve::math::Matrix localPlacementMatrix = calculateCurveOrientationMatrix(directionOfCurve, linear_placement->Distance->AlongHorizontal.value_or(true));

                    // 4. calculate the position
                    // the position on the curve = pointOnCurve
                    // the offsets = offsetFromCurve
                    carve::geom::vector<3> translate = pointOnCurve + localPlacementMatrix * offsetFromCurve;
                    carve::math::Matrix object_placement_matrix = convertIfcOrientationExpression(linear_placement->Orientation, translate);
                    
					// 5. check against the provided 3D coordinate
					try {
						checkLinearPlacementAgainstAbsolutePlacement(object_placement_matrix, linear_placement);
					}
					catch (const oip::InconsistentGeometryException& ex) {
						BLUE_LOG(warning) << ex.what();
					}
                    
					// return 
					return object_placement_matrix;
                }
				
				/**********************************************************************************************/
				/*! \brief Convert \c IfcGridAxis
				* \param[in] IfcGridAxis			The \c IfcGridAxis to be converted
				* \return							The tessellated axis' curve (an ordered array of points, i.e. a polyline)
				*/
				std::vector<carve::geom::vector<2>> convertIfcGridAxis(const EXPRESSReference<typename IfcEntityTypesT::IfcGridAxis>& gridAxis
				) const throw(...)
				{
					//	ENTITY IfcGridAxis;
					//		AxisTag: OPTIONAL IfcLabel;
					//			AxisCurve: IfcCurve;
					//			SameSense: IfcBoolean;
					//		INVERSE
					//			PartOfW : SET[0:1] OF IfcGrid FOR WAxes;
					//			PartOfV: SET[0:1] OF IfcGrid FOR VAxes;
					//			PartOfU: SET[0:1] OF IfcGrid FOR UAxes;
					//			HasIntersections: SET[0:? ] OF IfcVirtualGridIntersection FOR IntersectingAxes;
					//		WHERE
					//			WR1 : AxisCurve.Dim = 2;
					//			WR2: (SIZEOF(PartOfU) = 1) XOR(SIZEOF(PartOfV) = 1) XOR(SIZEOF(PartOfW) = 1);
					//	END_ENTITY;

					std::vector<carve::geom::vector<2>> axisVector;
					carve::math::Matrix gridPositionMatrix = carve::math::Matrix::IDENT();
					std::vector<carve::geom::vector<2>> segmentStartPoints;
					
					std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter = std::make_shared<PlacementConverterT<IfcEntityTypesT>>(GeomSettings(), UnitConvert());

					CurveConverterT<IfcEntityTypesT> gridConv(GeomSettings(), UnitConvert(), placementConverter);
					gridConv.convertIfcCurve2D(gridAxis->AxisCurve, axisVector, segmentStartPoints);

					if (!gridAxis->SameSense)
						// turn around the axis
						std::reverse(std::begin(axisVector), std::end(axisVector));

					if (!gridAxis->PartOfU.empty() && gridAxis->PartOfV.empty() && gridAxis->PartOfW.empty()) {
						gridPositionMatrix = getGridPosition(gridAxis->PartOfU[0]);
						return applyGridPositionToAxis(gridPositionMatrix, axisVector);
					}
					else if (gridAxis->PartOfU.empty() && !gridAxis->PartOfV.empty() && gridAxis->PartOfW.empty()) {
						gridPositionMatrix = getGridPosition(gridAxis->PartOfV[0]);
						return applyGridPositionToAxis(gridPositionMatrix, axisVector);
					}
					else if (gridAxis->PartOfU.empty() && gridAxis->PartOfV.empty() && !gridAxis->PartOfW.empty()) {
						gridPositionMatrix = getGridPosition(gridAxis->PartOfW[0]);
						return applyGridPositionToAxis(gridPositionMatrix, axisVector);
					}
					else  {
						throw oip::InconsistentModellingException(gridAxis, "IfcGridAxis can only refer to a single instance of IfcGrid.");
					}
				}

				/**********************************************************************************************/
				/*! \brief Calculates a position of the grid. 
				* \param[in] grid					A pointer to data from \c IfcGrid.
				* \return							A grid position matrix.
				*/
				carve::math::Matrix getGridPosition(const EXPRESSReference< typename IfcEntityTypesT::IfcGrid>& grid
				)const throw(...)
				{
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>> placementAlreadyApplied;
					if (grid->ObjectPlacement) {
						return convertIfcObjectPlacement(grid->ObjectPlacement, placementAlreadyApplied);
					}
					else {
						throw oip::InconsistentModellingException(grid, "An IfcPositioningElement must have a placement");
					}
				}
				
				/**********************************************************************************************/
				/*! \brief Applies position of the grid to the tessellated axis' curve.
				* \param[in] gridPositionMatrix			A grid position matrix.
				* \param[in] axisVector					The tessellated axis' curve without applied position of the grid.
				* \return								The tessellated axis' curve with applied position of the grid.
				*/
				std::vector<carve::geom::vector<2>> applyGridPositionToAxis(const carve::math::Matrix& gridPositionMatrix,
					const std::vector<carve::geom::vector<2>>& axisVector
				)const throw(...) 
				{
					std::vector<carve::geom::vector<2>> axisVectorOnGrid;
					
					for (int i = 0; i < axisVector.size(); i++) {
						carve::geom::vector<2> pnt = axisVector.at(i);
						carve::geom::vector<3> pnt3D = carve::geom::VECTOR(pnt.x, pnt.y, 0.);
						pnt3D = gridPositionMatrix * pnt3D;
						axisVectorOnGrid.push_back(carve::geom::VECTOR(pnt3D.x, pnt3D.y));
					}
						
					return axisVectorOnGrid;
				}

				/**********************************************************************************************/
				/*! \brief Convert \c IfcVirtualGridIntersection to a transformation matrix
				* \param[in] intersection			The \c IfcVirtualGridIntersection to be converted
				* \return 							A tuple: 1: Location of the grid, 2: tangent of the first intersecting axis	
				*/
				std::tuple<carve::geom::vector<3>, carve::geom::vector<3>> convertIfcVirtualGridIntersection(
					const EXPRESSReference<typename IfcEntityTypesT::IfcVirtualGridIntersection>& intersection
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricconstraintresource/lexical/ifcvirtualgridintersection.htm
					//	ENTITY IfcVirtualGridIntersection;
					//		IntersectingAxes: LIST[2:2] OF UNIQUE IfcGridAxis;
					//		OffsetDistances: LIST[2:3] OF IfcLengthMeasure;
					//	END_ENTITY;
					// **************************************************************************************************************************
					if (intersection.expired())
						throw oip::ReferenceExpiredException(intersection);

					std::vector<carve::geom::vector<2>> xAxis = convertIfcGridAxis(intersection->IntersectingAxes[0]);
					std::vector<carve::geom::vector<2>> yAxis = convertIfcGridAxis(intersection->IntersectingAxes[1]);

					carve::geom::vector<2> intersectionPoint;
					carve::geom::vector<2> xAxisPosition;
					carve::geom::vector<2> xAxisPosition2;
					carve::geom::vector<2> yAxisPosition;
					carve::geom::vector<2> yAxisPosition2;

					for (int i = 0; i < xAxis.size()-1; i++) {
						xAxisPosition = xAxis[i];
						xAxisPosition2 = xAxis[i+1];
						for (int j = 0; j < yAxis.size()-1; j++) {
							yAxisPosition = yAxis[i];
							yAxisPosition2 = yAxis[i+1];
							if (GeomUtils::LineSegmentToLineSegmentIntersection(xAxisPosition2, xAxisPosition, yAxisPosition2, yAxisPosition, intersectionPoint)) {
								i = xAxis.size();
								j = yAxis.size();
							}
						}
					}
					
					carve::geom::vector<3> intersectingAxes1 = carve::geom::VECTOR(xAxisPosition2[0] - xAxisPosition[0], xAxisPosition2[1] - xAxisPosition[1], 0.0);
					intersectingAxes1.normalize();
					carve::geom::vector<3> intersectingAxes2 = carve::geom::VECTOR(yAxisPosition2[0] - yAxisPosition[0], yAxisPosition2[1] - yAxisPosition[1], 0.0);
					intersectingAxes2.normalize();

					carve::geom::vector<3> location = carve::geom::VECTOR(intersectionPoint.x, intersectionPoint.y, 0.0);
					switch (intersection->OffsetDistances.size())
					{
					case 3: {

						carve::geom::vector<3> orthogonalComplement = carve::geom::VECTOR(-intersectingAxes1.y, intersectingAxes1.x, 0.0);

						//cross product of IntersectingAxes[1] and the orthogonal complement of the IntersectingAxes[1] 
						carve::geom::vector<3> crossProduct = carve::geom::cross(intersectingAxes1, orthogonalComplement);
						crossProduct.normalize();
						location = location + crossProduct * intersection->OffsetDistances[2];
					}
					case 2: {
						carve::geom::vector<3> orthogonalComplement1 = carve::geom::VECTOR(-intersectingAxes1.y, intersectingAxes1.x, 0.0);
						carve::geom::vector<3> orthogonalComplement2 = carve::geom::VECTOR(-intersectingAxes2.y, intersectingAxes2.x, 0.0);
	
						location = location + orthogonalComplement1 * intersection->OffsetDistances[0];
						location = location + orthogonalComplement2 * intersection->OffsetDistances[1];
						break;
					}
					default:
						throw oip::InconsistentGeometryException( "Number of coordinates is inconsistent.");
					}
					
					return { location, intersectingAxes1 };
				}

				/**********************************************************************************************/
				/*! \brief Calculates X-axis direction of the grid using \c IfcGridPlacementDirectionSelect 
				* \param[in] directionSelect			A pointer to data from \c IfcGridPlacementDirectionSelect.
				* \param[in] location					Location of the grid.
				* \param[in] intersectingAxes1			Tangent of the first intersecting axis	
				* \return								X-axis direction
				*/
				carve::geom::vector<3> convertIfcGridPlacementDirectionSelect(const EXPRESSOptional<typename IfcEntityTypesT::IfcGridPlacementDirectionSelect>& directionSelect,
					const carve::geom::vector<3>& location,
					const carve::geom::vector<3>& intersectingAxes1
				) const throw(...)
				{	
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricconstraintresource/lexical/ifcgridplacementdirectionselect.htm
					//	TYPE IfcGridPlacementDirectionSelect = SELECT
					//		(IfcDirection,
					//		IfcVirtualGridIntersection);
					//	END_TYPE;
					// **************************************************************************************************************************
					if (!directionSelect)
						return intersectingAxes1.normalized();

					switch (directionSelect.get().which()) {
					case 0:
						return convertIfcDirection(directionSelect.get().get<0>());
					case 1: {
						carve::geom::vector<3> location2;
						carve::geom::vector<3> intersectingAxes2;
						std::tie(location2, intersectingAxes2) = convertIfcVirtualGridIntersection(directionSelect.get().get<1>());
						return (location2 - location).normalized();
					}	
					default:
						throw  oip::UnhandledException("Unable to determine grid placement direction.");
					}
				}
				
				/**********************************************************************************************/
				/*! \brief Convert \c IfcGridPlacement to a transformation matrix
				* \param[in] gridPlacement			The \c IfcGridPlacement to be converted
				* \param[in] alreadyApplied			An array of references to already applied \c IfcObjectPlacement-s.
				* \return							The transformation matrix
				*/
				carve::math::Matrix convertIfcGridPlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcGridPlacement>& gridPlacement,
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied
				) const throw(...)
				{
					// **************************************************************************************************************************
					//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricconstraintresource/lexical/ifcgridplacement.htm
					//	ENTITY IfcGridPlacement
					//		SUBTYPE OF(IfcObjectPlacement);
					//			PlacementLocation: IfcVirtualGridIntersection;
					//			PlacementRefDirection: OPTIONAL IfcGridPlacementDirectionSelect;
					//	END_ENTITY;
					// **************************************************************************************************************************

					if (gridPlacement.expired())
						throw oip::ReferenceExpiredException(gridPlacement);

					carve::geom::vector<3> location;
					carve::geom::vector<3> intersectingAxes1;

					std::tie(location, intersectingAxes1) = convertIfcVirtualGridIntersection(gridPlacement->PlacementLocation);
					carve::geom::vector<3> xAxisDirection = convertIfcGridPlacementDirectionSelect(gridPlacement->PlacementRefDirection, location, intersectingAxes1);
					
					carve::geom::vector<3> yAxisDirection = carve::geom::VECTOR(-xAxisDirection.y, xAxisDirection.x, 0.0);
					// https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricconstraintresource/lexical/ifcgridplacement.htm :
					//  The plane defined by the x and y axis shall be co-planar to the xy plane of the local placement of the IfcGrid. ?

					 carve::geom::vector<3> zAxisDirection = carve::geom::cross(xAxisDirection, yAxisDirection);
					// https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcgeometricconstraintresource/lexical/ifcgridplacement.htm :
					// the z-axis of the IfcGridPlacement shall be co-linear to the z-axis of the local placement of the IfcGrid. ?

					carve::math::Matrix object_placement_matrix = carve::math::Matrix(
						xAxisDirection.x, yAxisDirection.x, zAxisDirection.x, location.x,
						xAxisDirection.y, yAxisDirection.y, zAxisDirection.y, location.y,
						xAxisDirection.z, yAxisDirection.z, zAxisDirection.z, location.z,
						 0.0, 0.0, 0.0, 1.0);

					return object_placement_matrix;
				}



                /*! \brief Converts \c IfcObjectPlacement to a transformation matrix.
				 * 
                 * \param[in]	objectPlacement		\c IfcObjectPlacement entity to be interpreted.
                 * \param		alreadyApplied		An array of references to already applied \c IfcObjectPlacement-s.
                 * 
				 * \return				Calculated transformation matrix.
				 *
                 * \note Function checks, if \c objectPlacement is contained within \c alreadyApplied.
                 * Throws, if contained. Otherwise, transforms the \c objectPlacement with recursive calls to self.
                 * It adds the \c objectPlacement to \c alreadyApplied.
                 * This prevents cyclic \c IfcObjectPlacement-s.
                 */
				carve::math::Matrix convertIfcObjectPlacement(
					const EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>& objectPlacement,
					std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>>& alreadyApplied
				) const throw(...)
				{
					// **************************************************************************************************************************
					// IfcObjectPlacement
					//  https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifcobjectplacement.htm
					// ENTITY IfcObjectPlacement
					//	ABSTRACT SUPERTYPE OF(ONEOF(IfcGridPlacement, IfcLinearPlacement, IfcLocalPlacement));
					//   PlacementRelTo : IfcObjectPlacement;			// from IFC4x2+
					//       ( PlacementRelTo is handled by each subtype individually )
					//	INVERSE
					//		PlacesObject : SET[0:?] OF IfcProduct FOR ObjectPlacement;
					//		ReferencedByPlacements: SET[0:?] OF IfcLocalPlacement FOR PlacementRelTo;
					// END_ENTITY;
					// **************************************************************************************************************************
					//check input
					if (objectPlacement.expired())
						throw oip::ReferenceExpiredException(objectPlacement);

					// Prevent cyclic relative placement
					// this doesn't work as long as there is no comparisson operator==
					//if(std::find(alreadyApplied.begin(), alreadyApplied.end(), objectPlacement) != alreadyApplied.end())
					for (const auto& el : alreadyApplied)
						if (el->getId() == objectPlacement->getId())
							throw oip::InconsistentModellingException(objectPlacement, "Cyclic application of IfcObjectPlacement!");

					// Add self to apllied
					alreadyApplied.push_back(objectPlacement);

					// The placement matrix - local variable that will get returned at the end
					carve::math::Matrix object_placement_matrix(carve::math::Matrix::IDENT());

					// (1/3) IfcLocalPLacement SUBTYPE OF IfcObjectPlacement
					if (objectPlacement.isOfType<typename IfcEntityTypesT::IfcLocalPlacement>())
						object_placement_matrix = convertIfcLocalPlacement(objectPlacement.as<typename IfcEntityTypesT::IfcLocalPlacement>(), alreadyApplied);

					// (2/3) IfcGridPlacement SUBTYPE OF IfcObjectPlacement
					else if (objectPlacement.isOfType<typename IfcEntityTypesT::IfcGridPlacement>()) {
						//TODO Not implemented
						//throw oip::UnhandledException(objectPlacement);
						object_placement_matrix = convertIfcGridPlacement(objectPlacement.as<typename IfcEntityTypesT::IfcGridPlacement>(), alreadyApplied);
					} // end if IfcGridPlacement

					// (3/3) IfcLinearPlacement SUBTYPE OF IfcObjectPlacement
					else if (objectPlacement.isOfType<typename IfcEntityTypesT::IfcLinearPlacement>())
						object_placement_matrix = convertIfcLinearPlacement(objectPlacement.as<typename IfcEntityTypesT::IfcLinearPlacement>(), alreadyApplied);

					// Remove self from applied
					alreadyApplied.pop_back();
					// return the calculated placement matrix
					return object_placement_matrix;
				}

                // Function 4: Get World Coordinate System. 
				// \internal TODO refactoring
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

                        matrix = matrix * world_coords_matrix;

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
				// \internal TODO refactoring
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
                        matrix = rotate_translate * carve::math::Matrix::SCALE(scale, scale_y, scale_z);
                }

                // Function 6: Get Plane. 
				// \internal TODO refactoring
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

                /*! \brief Calculates a point and the tangent at the point along a \c IfcCurve.
				 * 
                 * \param[in]	ifcCurve						\c IfcBoundedCurve entity representing the directrix.
                 * \param[in]	dDistAlongOfPoint				The distance along the curve at which the point and tangent should be calculated.
                 * \param[in]	bDistMeasuredAlongHorizontal	Is the distance measured only along the x-y projection of the curve?
                 * \param[out]	vkt3DtargetPoint				The calculated 3D point.
                 * \param[out]	vkt3DtargetDirection			The calculated 3D direction vector of the tangent to the curve at that point.

                 * \note \c dDistAlongOfPoint need to account for unit conversion outside of function.
                 * \note Function currently only supports \c IfcAlignmentCurve.
                 * \note Function presets the returns to (0.,0.,0.) and (1.,0.,0.).
                 */
                void convertBoundedCurveDistAlongToPoint3D(
                    const EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve>& ifcCurve,
                    const double dDistAlongOfPoint,
                    const bool bDistMeasuredAlongHorizontal,
                    carve::geom::vector<3>& vkt3DtargetPoint,
                    carve::geom::vector<3>& vkt3DtargetDirection
				) const throw(...)
                {
                    if(!bDistMeasuredAlongHorizontal)
						throw oip::UnhandledException("Function convertAlignmentCurveDistAlongToPoint3D: Distance along a 3D curve not supported.");

                    // preset the return values
                    vkt3DtargetPoint = carve::geom::VECTOR(0., 0., 0.);
                    vkt3DtargetDirection = carve::geom::VECTOR(1., 0., 0.);

                    // get the length & angle factors
                    double length_factor = UnitConvert()->getLengthInMeterFactor();
                    double plane_angle_factor = UnitConvert()->getAngleInRadianFactor();

					if (!ifcCurve.isOfType<typename IfcEntityTypesT::IfcAlignmentCurve>())
						throw oip::UnhandledException("Function convertAlignmentCurveDistAlongToPoint3D exclusively handles IfcAlignmentCurve.");
					else
					{
						auto alignment_curve = ifcCurve.as<typename IfcEntityTypesT::IfcAlignmentCurve>();

						// **************************************************************************************************************************
                        // 1. Get information.
                        // Info about the horizontal alignment.
                        std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontal>& horizontal = alignment_curve->Horizontal.lock();

                        if(!horizontal) {
                            BLUE_LOG(error) << alignment_curve->getErrorLog() << ": No IfcAlignment2DHorizontal!";
                            return;
                        }

                        // Segments type IfcAlignment2DHorizontalSegment L[1:?]
                        if(horizontal->Segments.empty()) {
                            BLUE_LOG(error) << horizontal->getErrorLog() << ": Segments are emtpy!";
                            return;
                        }
                        // the vector of horizontal segments - used in analysis
                        std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment>> horSegments;
                        horSegments.resize(horizontal->Segments.size());
                        std::transform(horizontal->Segments.begin(), horizontal->Segments.end(), horSegments.begin(), [](auto &it) {return it.lock(); });

                        // Get information from vertical alignment.
                        bool bOnlyHorizontal = false;
                        auto vertical = alignment_curve->Vertical;
                        // the vector of vertical segments - used in analysis
                        std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment>> verSegments;

                        if(!vertical) {
                            bOnlyHorizontal = true;
                            //BLUE_LOG(info) << alignment_curve->getErrorLog() << ": No IfcAlignment2DVertical.";
                            if(!bDistMeasuredAlongHorizontal)
                                BLUE_LOG(warning) << alignment_curve->getErrorLog() << ": Although 3D distance along is wanted, we can only deliver along a 2D alignment curve.";
                        }
                        else {
                            // Segments type IfcAlignment2DHorizontalSegment L[1:?]
                            if(vertical->Segments.empty()) {
                                BLUE_LOG(warning) << vertical->getErrorLog() << ": Segments are emtpy!";
								bOnlyHorizontal = true;
                            }
							else
							{
								verSegments.resize(vertical->Segments.size());
								std::transform(vertical->Segments.begin(), vertical->Segments.end(), verSegments.begin(), [](auto &it) {return it.lock(); });
							}
                        }

                        // **************************************************************************************************************************
                        // 2. Find the corresponding segment in horizontal alignment.
                        // The entities relevant to the point trying to be calculated
                        std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DHorizontalSegment> horizontalSegmentRelevantToPoint;
                        std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerticalSegment> verticalSegmentRelevantToPoint;
                        std::shared_ptr<typename IfcEntityTypesT::IfcCurveSegment2D> horCurveGeometryRelevantToPoint;
                        // some necessary temporary variables
                        double horizSegStartDistAlong = 0.;

                        // Iterate over horizontal segments -> find the necessary element
                        for(auto& it_segment : horSegments) {
                            // IfcAlignment2DHorizontalSegment (TangentialContinuity type IfcBoolean [0:1], StartTag type IfcLabel [0:1], EndTag type IfcLabel [0:1], CurveGeometry type IfcCurveSegment2D [1:1])
                            // ENTITY IfcAlignment2DHorizontalSegment
                            //	SUBTYPE OF(IfcAlignment2DSegment);
                            //		CurveGeometry: IfcCurveSegment2D;
                            //	INVERSE
                            //		ToHorizontal : SET[1:1] OF IfcAlignment2DHorizontal FOR Segments;
                            // END_ENTITY;
                            horCurveGeometryRelevantToPoint = it_segment->CurveGeometry.lock();

                            //*********************************************************************
                            // 2.a some checks
                            // Get and interpret information from IfcCurveSegment2D.
                            if(!horCurveGeometryRelevantToPoint) {
                                BLUE_LOG(error) << it_segment->getErrorLog() << ": No curve geometry.";
                                continue;
                            }

                            // IfcCurveSegment2D -> SegmentLength type IfcPositiveLengthMeasure [1:1]
                            // ENTITY IfcCurveSegment2D
                            //	ABSTRACT SUPERTYPE OF(ONEOF(IfcCircularArcSegment2D, IfcLineSegment2D, IfcTransitionCurveSegment2D))
                            //	SUBTYPE OF(IfcBoundedCurve);
                            //		StartPoint: IfcCartesianPoint;
                            //		StartDirection: IfcPlaneAngleMeasure;
                            //		SegmentLength: IfcPositiveLengthMeasure;
                            // END_ENTITY;

                            // Get the segment's length
                            double horizSegLength = horCurveGeometryRelevantToPoint->SegmentLength * length_factor;
                            if(horizSegLength <= 0.) {
                                BLUE_LOG(trace) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Segment length is negative/ZERO?!";
                                return;
                            }

                            // if begin of this segment is after the station -> sth went wrong
                            if(horizSegStartDistAlong > dDistAlongOfPoint) {
                                BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Inconsistency! Segment begins after the specified station.";
                                return;
                            }

                            //*********************************************************************
                            // 2.b If the end of this segment is further along than the point searched for, 
                            //      the point is within this segment -> remember that!
                            if(horizSegStartDistAlong + horizSegLength >= dDistAlongOfPoint) {
                                // Remember the element for later
                                horizontalSegmentRelevantToPoint = it_segment;

                                // break the for loop, since we have found the element!
                                break;
                            } // end if (horizSegStartDistAlong + horizSegLength > dDistAlongOfPoint)

                            // Add the length to the distance along
                            //TODO Correct for 3D length
                            horizSegStartDistAlong += horizSegLength;
                        } // end horizontal segments iteration

                        //********************************************************************
                        // 3. Find the corresponding segment in vertical alignment.
                        if(!verSegments.empty()) {
                            // some temporary variables
                            double verSegStartHeight = 0.;
                            double verSegStartGradient = 0.;

                            double verSegLength = 0.;
                            double verSegDistAlong = 0.;

                            // Iterate over vertical segments
                            for(auto& it_segment : verSegments) {

                                // ENTITY IfcAlignment2DVerticalSegment
                                //	ABSTRACT SUPERTYPE OF(ONEOF(IfcAlignment2DVerSegCircularArc, IfcAlignment2DVerSegLine, IfcAlignment2DVerSegParabolicArc))
                                //	SUBTYPE OF(IfcAlignment2DSegment);
                                //		StartDistAlong: IfcLengthMeasure;
                                //		HorizontalLength: IfcPositiveLengthMeasure;
                                //		StartHeight: IfcLengthMeasure;
                                //		StartGradient: IfcRatioMeasure;
                                //	INVERSE
                                //		ToVertical : SET[1:1] OF IfcAlignment2DVertical FOR Segments;
                                // END_ENTITY;

                                //*********************************************************************
                                // 3.a some checks
                                // Get the start distance along: StartDistAlong
                                verSegDistAlong = it_segment->StartDistAlong * length_factor;
                                if(verSegDistAlong < 0.) {
                                    BLUE_LOG(error) << it_segment->getErrorLog() << ": Start distance along is inconsistent.";
                                    //return;
                                }

                                // Get the segment's length
                                verSegLength = it_segment->HorizontalLength * length_factor;
                                if(verSegLength <= 0.) {
                                    BLUE_LOG(error) << it_segment->getErrorLog() << ": Segment length is negative/ZERO?!";
                                    continue;
                                }

                                // if begin of this segment is after the station -> sth went wrong
                                if(verSegDistAlong > dDistAlongOfPoint) {
                                    BLUE_LOG(error) << it_segment->getErrorLog() << ": Inconsistency! Segment begins after the specified station.";
                                    return;
                                }

                                //*********************************************************************
                                // 3.b If the end of this segment is further along than the point searched for, 
                                //      the point is within this segment -> remember that!
                                if(verSegDistAlong + verSegLength >= dDistAlongOfPoint) {
                                    // Remember the element for later
                                    verticalSegmentRelevantToPoint = it_segment;

                                    // break the for loop, since we have found the element!
                                    break;
                                } // end if (verSegDistAlong + verSegLength > dDistAlongOfPoint)
                            }// end vertical stations iteration
                        } // end if (!verSegments.empty())

                        //********************************************************************
                        // 4. Calculate x and y coordinates of point
                        //     as well as the horizontal direction from horizontal segment

                        // get the starting point of segment
                        const auto& curveSegStartPoint = horCurveGeometryRelevantToPoint->StartPoint;
                        if(!curveSegStartPoint) {
                            BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog()
                                << ": No curve segment start point.";
                            return;
                        }

                        // get the length of the segment
                        double horizSegLength = horCurveGeometryRelevantToPoint->SegmentLength * length_factor;
                        if(horizSegLength <= 0.) {
                            BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog()
                                << ": Curve segment length inconsistent.";
                            return;
                        }
                        // Distance from start of segment to point along alignment.
                        double distanceToStart = dDistAlongOfPoint - horizSegStartDistAlong;

                        // types have additional data -> calculate the exact position within the segment
                        std::shared_ptr<typename IfcEntityTypesT::IfcLineSegment2D> line_segment_2D =
                            std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLineSegment2D>(horCurveGeometryRelevantToPoint);
                        std::shared_ptr<typename IfcEntityTypesT::IfcCircularArcSegment2D> circular_arc_segment_2D =
                            std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircularArcSegment2D>(horCurveGeometryRelevantToPoint);
                        std::shared_ptr<typename IfcEntityTypesT::IfcTransitionCurveSegment2D> trans_curve_segment_2D =
                            std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcTransitionCurveSegment2D>(horCurveGeometryRelevantToPoint);

                        //********************************************************************
                        // 4.a determine the functions
                        // initialize the function that calculates x,y coordinate
                        // that is, the deviation of y from x-axis along the curve
                        // (segment's true starting point is included later)
                        std::function<void(const double, const double, const double, double&, double&)> fctPosition =
                            [](const double distAlong, const double horizSegLength, const double radius,
                                double &x, double &y) -> void { x = y = 1.; };
                        // initialize the function that calculates horizontal direction
                        // that is, the deviation from the x-axis 
                        // (segment's true direction is included later)
                        std::function<void(const double, const double, const double, double&)> fctDirection =
                            [](const double distAlong, const double horizSegLength, const double radius,
                                double &dir) -> void { dir = 1.; };
                        // initialize the function that provides radius attribute for start and end
                        std::function<void(double&, double&)> fctRadii =
                            [](double& bStartRadius, double& bEndRadius) -> void { bStartRadius = bEndRadius = 0.; };
                        // initialize the function that provides CCW attribute for start and end
                        std::function<void(bool&, bool&)> fctCCW =
                            [](bool& bStartCCW, bool& bEndCCW) -> void { bStartCCW = bEndCCW = true; };

                        if(line_segment_2D) {
                            // straight line
                            fctPosition =
                                [](const double distAlong, const double horizSegLength, const double radius,
                                    double &x, double &y) -> void
                            {
                                // x-coordinate
                                x = distAlong;

                                // y-coordinate
                                y = 0.;
                            };

                            // the direction is the same for the whole line
                            fctDirection =
                                [](const double distAlong, const double horizSegLength, const double radius,
                                    double &dir) -> void
                            {
                                dir = 0.;
                            };

                            // CCW attributes - it doesn't matter, but still
                            fctCCW = [](bool& bStartCCW, bool& bEndCCW) -> void
                            {
                                bStartCCW = bEndCCW = true;
                            };

                        } // if (line_segment_2D) 
                        else if(circular_arc_segment_2D) {
                            // Radius type IfcPositiveLengthMeasure [1:1]
                            if(circular_arc_segment_2D->Radius <= 0.) {
                                BLUE_LOG(error) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Radius inconsistent.";
                                return;
                            }
                            //double radius = circular_arc_segment_2D->Radius * length_factor;
                            fctRadii = [&](double& bStartRadius, double& bEndRadius) -> void
                            {
                                bStartRadius = bEndRadius = circular_arc_segment_2D->Radius * length_factor;
                            };

                            // IsCCW type IfcBoolean [1:1]
                            //bool is_CCW = circular_arc_segment_2D->IsCCW;
                            // CCW attributes
                            fctCCW = [&](bool& bStartCCW, bool& bEndCCW) -> void
                            {
                                bStartCCW = bEndCCW = circular_arc_segment_2D->IsCCW;
                            };

                            // Calculate circle's center, given start point and direction (angle between tangent and x-axis).
                            //double radiusDirection = horizSegStartDirection + 0.5 * M_PI * (is_CCW ? -1 : 1);
                            //double centerX = startPoint.x + cos(radiusDirection) * radius;
                            //double centerY = startPoint.y + sin(radiusDirection) * radius;

                            // Angle between x-axis and vector(start, center).
                            //double angleAlpha = atan2(startPoint.y - centerY, startPoint.x - centerX);

                            // Angle between x-axis and point according to circle direction.
                            //double angleBeta = angleAlpha + distanceToStart / radius * ( is_CCW ? -1 : 1); 
                            //x = centerX + radius * cos(angleBeta);
                            //y = centerY + radius * sin(angleBeta);

                            fctPosition =
                                [](const double distAlong, const double horizSegLength, const double radius,
                                    double &x, double &y) -> void
                            {
                                double opening_angle = distAlong / radius;

                                // x-coordinate
                                x = radius * sin(opening_angle);

                                // y-coordinate
                                y = radius * (1. - cos(opening_angle));
                            };

                            // Calculate direction
                            //dir = angleBeta + (is_CCW ? -1 : 1) * 0.5 * M_PI;
                            fctDirection =
                                [](const double distAlong, const double horizSegLength, const double radius,
                                    double &dir) -> void
                            {
                                //double opening_angle = distAlong / radius;
                                dir = distAlong / radius;
                            };

                        } // if (circular_arc_segment_2D) 
                        else if(trans_curve_segment_2D) {
                            // StartRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
                            double startRadius = 0.0;
                            if(!trans_curve_segment_2D->StartRadius
                                || trans_curve_segment_2D->StartRadius <= 0.) {
                                //BLUE_LOG(info) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Start radius NIL, interpreted as infinite.";
                            }
                            else {
                                startRadius = trans_curve_segment_2D->StartRadius * length_factor;
                            }
                            // EndRadius type IfcLengthMeasure: if NIL, interpret as infinite (= no curvature)
                            double endRadius = 0.0;
                            if(!trans_curve_segment_2D->EndRadius
                                || trans_curve_segment_2D->EndRadius <= 0.) {
                                //BLUE_LOG(info) << horCurveGeometryRelevantToPoint->getErrorLog() << ": End radius NIL, interpreted as infinite.";
                            }
                            else {
                                endRadius = trans_curve_segment_2D->EndRadius * length_factor;
                            }
                            fctRadii = [&](double& bStartRadius, double& bEndRadius) -> void
                            {
                                bStartRadius = std::max(startRadius, 0.);
                                bEndRadius = std::max(endRadius, 0.);
                            };

                            // IsStartRadiusCCW type IfcBoolean
                            //bool is_start_ccw = trans_curve_segment_2D->IsStartRadiusCCW;
                            // IsEndRadiusCCW type IfcBoolean
                            //bool is_end_ccw = trans_curve_segment_2D->IsEndRadiusCCW;
                            // CCW attributes
                            fctCCW = [&](bool& bStartCCW, bool& bEndCCW) -> void
                            {
                                bStartCCW = trans_curve_segment_2D->IsStartRadiusCCW;
                                bEndCCW = trans_curve_segment_2D->IsEndRadiusCCW;
                            };

                            // get the type of transition
                            const auto& trans_type = trans_curve_segment_2D->TransitionCurveType;
                            // https://www.researchgate.net/publication/273829731_Investigation_of_a_New_Transition_Curve/link/5a6a60ce458515b2d0532a79/download
                            switch(trans_type) {
                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_BIQUADRATICPARABOLA):
                            {
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    // x-coordinate
                                    x = distAlong;

                                    // y-coordinate
                                    y = 0.;
                                    if(x <= horizSegLength * 0.5) {
                                        y = pow(x, 4) / (6. * radius * horizSegLength * horizSegLength);
                                    }
                                    else if(horizSegLength * 0.5 < x && x <= horizSegLength) {
                                        y = -(pow(x, 4) / (6. * radius * pow(horizSegLength, 2)) + (2. * pow(x, 3)) / (3. * radius * horizSegLength)
                                            - pow(x, 2) / (2. * radius) + (horizSegLength * x) / (6. * radius) - pow(horizSegLength, 2) / (48. * radius));
                                    } // end elseif
                                    else {
                                        y = INFINITY;
                                    }
                                };
                            } // end case BIQUADRATICPARABOLA
                            break;

                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_BLOSSCURVE):
                            {
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    // Integration with Substitution
                                    double teta_up = pow(distAlong + horizSegLength, 3) / (radius * pow(horizSegLength, 2))
                                        - pow(distAlong + horizSegLength, 4) / (2. * radius * pow(horizSegLength, 3)); //values for upper boundary of integral
                                    double teta_low = pow(distAlong, 3) / (radius * pow(horizSegLength, 2))
                                        - pow(distAlong, 4) / (2. * radius * pow(horizSegLength, 3)); //values for lower boundary of integral
                                    double teta_deriv_up = 2. * pow(distAlong + horizSegLength, 2) / (radius * pow(horizSegLength, 2))
                                        - 4. * pow(distAlong + horizSegLength, 3) / (2. * radius * pow(horizSegLength, 3));
                                    double teta_deriv_low = 2. * pow(distAlong, 2) / (radius * pow(horizSegLength, 2))
                                        - 4. * pow(distAlong, 3) / (2. * radius * pow(horizSegLength, 3));

                                    // x-coordinate
                                    x = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;
                                    // y-coordinate
                                    y = -cos(teta_up) / teta_deriv_up + cos(teta_low) / teta_deriv_low;
                                };
                            } // end case BLOSSCURVE
                            break;

                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_CLOTHOIDCURVE):
                            {
                                // https://www.springerprofessional.de/transition-curves-for-highway-geometric-design/12088070
                                // page 26, Eqs. (4.3) and (4.4)
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    double a2 = radius * horizSegLength;
                                    // x-coordinate
                                    x = distAlong
                                        - pow(distAlong, 5) / (40. * pow(a2, 2))
                                        + pow(distAlong, 9) / (3456. * pow(a2, 4));
                                    // y-coordinate
                                    y = pow(distAlong, 3) / (6. * a2)
                                        - pow(distAlong, 7) / (336. * pow(a2, 3))
                                        + pow(distAlong, 11) / (42240. * pow(a2, 5));
                                };
                            } // end case CLOTHOIDCURVE
                            break;

                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_COSINECURVE):
                            {
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    double psi = M_PI * distAlong / horizSegLength;

                                    // x-coordinate
                                    x = distAlong - (pow(horizSegLength, 2) / (8. * pow(M_PI, 2) * pow(radius, 2))) * horizSegLength / M_PI
                                        * ((pow(psi, 3) / 3.) + (psi / 2. - sin(psi) * cos(psi) / 2.) - 2. * (sin(psi) - psi * cos(psi)));
                                    // y-coordinate
                                    y = horizSegLength * (horizSegLength / (2. * pow(M_PI, 2) * radius) * (pow(psi, 2) / 2. + cos(psi) - 1.)
                                        - (pow(horizSegLength, 3) / (48. * pow(M_PI, 4) * pow(radius, 3)))
                                        * (pow(psi, 4) / 4. + pow(sin(psi), 2) * cos(psi) / 3. - 16. * cos(psi) / 3.
                                            + 3. * pow(psi, 2) * cos(psi)
                                            - 6. * psi * sin(psi) + 3. * pow(psi, 2) / 4. - 3. * psi * sin(2. * psi) / 4. - 3. * cos(2. * psi) / 8. + 137. / 24.));
                                };
                            } // end case COSINECURVE
                            break;

                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_CUBICPARABOLA):
                            {
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    // x-coordinate
                                    x = distAlong;
                                    // y-coordinate
                                    y = pow(x, 3) / (6. * radius * horizSegLength);
                                };
                            } // end case CUBICPARABOLA
                            break;

                            case(typename IfcEntityTypesT::IfcTransitionCurveType::ENUM::ENUM_SINECURVE):
                            {
                                fctPosition =
                                    [](const double distAlong, const double horizSegLength, const double radius,
                                        double &x, double &y) -> void
                                {
                                    double psi = (2. * M_PI * distAlong) / horizSegLength;
                                    // x-coordinate
                                    x = distAlong * (1. - pow(horizSegLength, 2) / (32. * pow(M_PI, 4)*pow(radius, 2)
                                        - (pow(horizSegLength, 3) / (3840. * pow(M_PI, 5)*pow(radius, 2))))
                                        * (3. * pow(psi, 5) - 20. * pow(psi, 3) + 30. * psi - (240. - 60. * pow(psi, 2)*sin(psi)
                                            + 30. * cos(psi)*sin(psi) + 120. * psi*cos(psi))));

                                    // Integration with Substitution
                                    double teta_up = pow((distAlong + horizSegLength), 2) / (2. * radius * horizSegLength) + (horizSegLength / (4. * pow(M_PI, 2)*radius)) * (cos(2. * M_PI*(distAlong + horizSegLength) / horizSegLength) - 1.);
                                    double teta_low = pow((distAlong + horizSegLength), 2) / (2. * radius * horizSegLength) + (horizSegLength / (4. * pow(M_PI, 2)*radius)) * (cos(2. * M_PI*(distAlong) / horizSegLength) - 1.);
                                    double teta_deriv_up = 2. * (distAlong + horizSegLength) / (2. * radius * horizSegLength);
                                    double teta_deriv_low = 2. * distAlong / (2. * radius * horizSegLength);
                                    // y-coordinate
                                    y = sin(teta_up) / teta_deriv_up - sin(teta_low) / teta_deriv_low;
                                };

                            } // end case SINECURVE
                            break;
                            } // end switch (trans_type)


                            // Calculate direction
                            fctDirection =
                                [this, &fctPosition](const double distAlong, const double horizSegLength, const double radius,
                                    double &dir) -> void
                            {
                                // for direction
                                // - step a bit backwards & forwards
                                // - calculate the coordinates
                                // - get the tangent from these points
                                double delta = GeomSettings()->getPrecision();
                                double xMinus, xPlus, yMinus, yPlus;

                                fctPosition(distAlong - delta, horizSegLength, radius, xMinus, yMinus);
                                fctPosition(distAlong + delta, horizSegLength, radius, xPlus, yPlus);

                                dir = atan2(yPlus - yMinus, xPlus - xMinus);
                            };

                        } // end if (trans_curve_segment_2D) 

                        //********************************************************************
                        // 4.b Determine the point
                        //  The radii
                        double dRadStart, dRadEnd;
                        fctRadii(dRadStart, dRadEnd);
                        if(dRadStart != 0. && dRadEnd != 0. && dRadStart != dRadEnd) {
                            BLUE_LOG(warning) << horCurveGeometryRelevantToPoint->getErrorLog() << ": Different radii with != 0. not supported.";
                            return;
                        }
                        // is it a curve with decreasing curvature? (doesn't matter with straights and circular arcs)
                        bool curveOut = (dRadStart != 0. && dRadStart != dRadEnd);
                        double radius = (curveOut ? dRadStart : dRadEnd);

                        // (counter-)clock-wise?
                        bool bCCWStart, bCCWEnd;
                        fctCCW(bCCWStart, bCCWEnd);
                        bool bCCW = (curveOut ? bCCWStart : bCCWEnd);

                        //  Starting point of the segment
                        carve::geom::vector<3> startPoint = convertIfcCartesianPoint(curveSegStartPoint);

                        // the transformation matrix
                        carve::math::Matrix matrix(carve::math::Matrix::IDENT());

                        // if curveOut -> handle the curve mirrored
                        if(curveOut) {
                            // mirror the distance to start of element
                            distanceToStart = horizSegLength - distanceToStart;

                            // calculate the end point
                            carve::geom::vector<3> vctEnd = carve::geom::VECTOR(0.0, 0.0, 0.0);
                            fctPosition(horizSegLength, horizSegLength, radius, vctEnd.x, vctEnd.y);

                            // Ending direction of the segment
                            double horizSegEndDirection;
                            fctDirection(horizSegLength, horizSegLength, radius, horizSegEndDirection);
                            // move to the end and draw from back
                            // account for CCW
                            if(!bCCW)
                                horizSegEndDirection = M_PI - horizSegEndDirection;
                            else
                                horizSegEndDirection = M_PI + horizSegEndDirection;

                            //GeomSettings()->normalizeAngle(horizSegEndDirection, 0., M_TWOPI);
                            // add an additional step in transformation (go from the end)
                            // see https://www.lantmateriet.se/contentassets/4a728c7e9f0145569edd5eb81fececa7/rapport_reit_eng.pdf
                            //  section 6.2
                            matrix =
                                carve::math::Matrix(
                                    cos(horizSegEndDirection), -sin(horizSegEndDirection), 0., 0.,
                                    sin(horizSegEndDirection), cos(horizSegEndDirection), 0., 0.,
                                    0., 0., 1., 0.,
                                    0., 0., 0., 1.) *
                                carve::math::Matrix(
                                    1., 0., 0., -vctEnd.x,
                                    0., 1., 0., -vctEnd.y,
                                    0., 0., 1., 0.,
                                    0., 0., 0., 1.) *
                                matrix;
                        }
                        else // not curveOut
                        {
                            // account for CCW
                            if(!bCCW)
                                matrix =
                                carve::math::Matrix(
                                    1., 0., 0., 0.,
                                    0., -1., 0., 0.,
                                    0., 0., 1., 0.,
                                    0., 0., 0., 1.) *
                                matrix;
                        }

                        //  Calculate the deltas for coordinates in the local system of the segment
                        carve::geom::vector<3> vctLocal = carve::geom::VECTOR(0.0, 0.0, 0.0);
                        fctPosition(distanceToStart, horizSegLength, radius, vctLocal.x, vctLocal.y);

                        //  Starting direction of the segment
                        double horizSegStartDirection = horCurveGeometryRelevantToPoint->StartDirection * plane_angle_factor; // get it in RADIAN
                        //GeomSettings()->normalizeAngle(horizSegStartDirection, 0., M_TWOPI);

                        // multiply
                        matrix = carve::math::Matrix(
                            cos(horizSegStartDirection), -sin(horizSegStartDirection), 0., startPoint.x,
                            sin(horizSegStartDirection), cos(horizSegStartDirection), 0., startPoint.y,
                            0., 0., 1., 0.,
                            0., 0., 0., 1.) * matrix;

                        // calculate the global x,y
                        vkt3DtargetPoint = matrix * vctLocal;
                        // end x, y coordinate calculation

                        //********************************************************************
                        // 4.c Determine the direction of the segment at point
                        double dir;
                        fctDirection(distanceToStart, horizSegLength, radius, dir);
                        // add the segment's direction
                        dir += horizSegStartDirection;
                        // mirror if needed
                        if(curveOut) {
                            //  Ending direction of the segment
                            double horizSegEndDirection;
                            fctDirection(horizSegLength, horizSegLength, radius, horizSegEndDirection);
                            dir += horizSegEndDirection + M_PI;
                            if(!bCCW)
                                dir = M_TWOPI - dir;
                        }

                        // set the direction
                        vkt3DtargetDirection.x = cos(dir);
                        vkt3DtargetDirection.y = sin(dir);
                        // end x, y direction  calculation

                        //********************************************************************
                        // 5. Calculate z coordinate from vertical alignment, if there.
                        if(verticalSegmentRelevantToPoint) {
                            const std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>& v_seg_line_2D =
                                std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegLine>(verticalSegmentRelevantToPoint);
                            const std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>& v_seg_circ_arc_2D =
                                std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment2DVerSegCircularArc>(verticalSegmentRelevantToPoint);
                            const std::shared_ptr<typename IfcEntityTypesT::IfcAlignment2DVerSegParabolicArc>& v_seg_par_arc_2D =
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
                            double gradient = 0.0; // the value for the gradient
                            if(v_seg_line_2D) {
                                dz = verSegStartGradient * distVerToStart;
                                gradient = verSegStartGradient;
                            }
                            else if(v_seg_circ_arc_2D) {
                                // https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifcalignment2dversegcirculararc.htm
                                // Radius type IfcPositiveLengthMeasure [1:1] 
                                if(v_seg_circ_arc_2D->Radius <= 0.) {
                                    BLUE_LOG(error) << verticalSegmentRelevantToPoint->getErrorLog() << ": No radius.";
                                    return;
                                }
                                double radius = v_seg_circ_arc_2D->Radius * length_factor;

                                // IsConvex type IfcBoolean [1:1]
                                bool is_convex = v_seg_circ_arc_2D->IsConvex;

                                // pointDistAlong and verSegDistAlong are along horizontal alignment, which corresponds to the horizontal axis in the vertical alignment

                                double tmp = radius / sqrt(1. + pow(verSegStartGradient, 2));
                                if(is_convex) {
                                    // Crest (decreasing gradient)
                                    dz = -sqrt(pow(radius, 2) - pow(distVerToStart + verSegStartGradient * tmp, 2)) + tmp;
                                }
                                else {
                                    // Sag (increasing gradient)
                                    dz = sqrt(pow(radius, 2) - pow(distVerToStart - verSegStartGradient * tmp, 2)) - tmp;
                                }
                            }
                            else if(v_seg_par_arc_2D) {
                                // https://standards.buildingsmart.org/IFC/RELEASE/IFC4_1/FINAL/HTML/link/ifcalignment2dversegparabolicarc.htm
                                // ParabolaConstant type IfcPositiveLengthMeasure [1:1]
                                if(v_seg_par_arc_2D->ParabolaConstant <= 0.) {
                                    BLUE_LOG(error) << verticalSegmentRelevantToPoint->getErrorLog() << ": No parabola constant.";
                                    return;
                                }
                                double arc_const = v_seg_par_arc_2D->ParabolaConstant * length_factor;

                                // IsConvex type IfcBoolean [1:1]
                                bool is_convex = v_seg_par_arc_2D->IsConvex;

                                double parabola_radius = is_convex ? -arc_const : arc_const;
                                double parabola_gradient = distVerToStart / parabola_radius + verSegStartGradient;
                                dz = distVerToStart * (parabola_gradient + verSegStartGradient) * 0.5;
                            }

                            // set the coordinate
                            vkt3DtargetPoint.z = verSegStartHeight + dz;

                            // normalize the direction
                            vkt3DtargetDirection.normalize();
                            // set the vertical direction
                            vkt3DtargetDirection.z = gradient;
                        }// end if ( verticalSegmentRelevantToPoint ) --> z coordinate calculation
                        //********************************************************************

                        // normalize the direction
                        vkt3DtargetDirection.normalize();

                    }//end if alignment curve
                }//end convertAlignmentCurveDistAlongToPoint3D

            };
        }
    }
}

#endif
