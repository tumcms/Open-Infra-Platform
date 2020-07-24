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

#pragma once
#ifndef PROFILECONVERTER_H
#define PROFILECONVERTER_H

#include <memory>

#include "CarveHeaders.h"

#include "ConverterBase.h"

#include "CurveConverter.h"
#include "GeomUtils.h"
#include "GeometryInputData.h"
#include "PlacementConverter.h"

#include "BlueFramework/Core/Diagnostics/log.h"


/**********************************************************************************************/

namespace OpenInfraPlatform {
	namespace Core{
	namespace IfcGeometryConverter {
		template <
			class IfcEntityTypesT
		>
			class ProfileConverterT : public ConverterBaseT<IfcEntityTypesT>
		{
		public:
			ProfileConverterT(
				std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter,
				std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> pc
			)
				:
				ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter),
				placementConverter(pc)
			{
				// std::cout << "Usage of ProfileConverterT" << std::endl;
			}

			~ProfileConverterT()
			{
			}

			// *************************************************************************************************************************************************************//
			//	IfcProfileDef		(http://www.buildingsmart-tech.org/ifc/IFC4x1/final/html/schema/ifcprofileresource/lexical/ifcprofiledef.htm)							//
			//	ABSTRACT SUPERTYPE OF IfcArbitraryClosedProfileDef, IfcArbitraryOpenProfileDef, IfcCompositeProfileDef, IfcDerivedProfileDef, IfcOpenCrossProfileDef, IfcParameterizedProfileDef	//
			// *************************************************************************************************************************************************************//
			void computeProfile(EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef> profileDef)
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcProfileDef #" << profileDef->getId();
#endif
				// (1/5) IfcArbitraryClosedProfileDef SUBTYPE OF IfcProfileDef
				//std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> arbitrary_closed =
				//std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(profileDef);
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> arbitrary_closed = profileDef.as<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>();
					convertIfcArbitraryClosedProfileDef(arbitrary_closed, paths);
					removeDuplicates(paths);
					return;
				}

				// (2/5) IfcArbitraryOpenProfileDef SUBTYPE OF IfcProfileDef
				//std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef> arbitrary_open =
				//	std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>(profileDef);
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef> arbitrary_open = profileDef.as<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>();
					convertIfcArbitraryOpenProfileDef(arbitrary_open, paths);
					removeDuplicates(paths);
					return;
				}

				// (3/5) IfcCompositeProfileDef SUBTYPE OF IfcProfileDef
				//std::shared_ptr<typename IfcEntityTypesT::IfcCompositeProfileDef> composite = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeProfileDef>(profileDef);
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcCompositeProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcCompositeProfileDef> composite = profileDef.as<typename IfcEntityTypesT::IfcCompositeProfileDef>();
					convertIfcCompositeProfileDef(composite, paths);
					removeDuplicates(paths);
					return;
				}

				// (4/5) IfcDerivedProfileDef SUBTYPE OF IfcProfileDef
				//std::shared_ptr<typename IfcEntityTypesT::IfcDerivedProfileDef> derived = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcDerivedProfileDef>(profileDef);
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcDerivedProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcDerivedProfileDef> derived = profileDef.as<typename IfcEntityTypesT::IfcDerivedProfileDef>();
					convertIfcDerivedProfileDef(derived, paths);
					removeDuplicates(paths);
					return;
				}

				// (5/5) IfcParameterizedProfileDef SUBTYPE OF IfcProfileDef
				//std::shared_ptr<typename IfcEntityTypesT::IfcParameterizedProfileDef> parameterized =
				//	std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcParameterizedProfileDef>(profileDef);
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcParameterizedProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcParameterizedProfileDef> parameterized = profileDef.as<typename IfcEntityTypesT::IfcParameterizedProfileDef>();
					convertIfcParameterizedProfileDefWithPosition(parameterized, paths);
					removeDuplicates(paths);
					return;
				}

				// std::shared_ptr<typename IfcEntityTypesT::IfcNurbsProfile> nurbs =
				// std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcNurbsProfile>(profileDef);
				// if( nurbs )
				//{
				//	convertIfcNurbsProfile( nurbs, paths );
				//	return;
				//}
				throw oip::UnhandledException(profileDef);
			}

			// ****************************************************************************************************************************************	//
			//	Profile Functions																														//
			//	convertIfcArbitraryClosedProfileDef, convertIfcArbitraryOpenProfileDef, convertIfcCompositeProfileDef, convertIfcDerivedProfileDef		//
			//	convertIfcArbitraryProfileWithVoids, convertIfcParameterizedProfileDefWithPosition														//
			// ****************************************************************************************************************************************	//

			// Function 1: Convert IfcArbitraryClosedProfileDef
			void convertIfcArbitraryClosedProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcArbitraryClosedProfileDef #" << profileDef->getId();
#endif
				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> outer_curve = profileDef->OuterCurve.lock();
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcArbitraryClosedProfileDef.OuterCurve IfcCurve #" << outer_curve->getId();
#endif
				std::vector<carve::geom::vector<2>> curve_polygon;
				std::vector<carve::geom::vector<2>> segment_start_points;

				CurveConverterT<IfcEntityTypesT> c_conv(GeomSettings(), UnitConvert(), placementConverter);
				c_conv.convertIfcCurve2D(outer_curve, curve_polygon, segment_start_points);
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcArbitraryClosedProfileDef.OuterCurve IfcCurve #" << outer_curve->getId();
#endif
				deleteLastPointIfEqualToFirst(curve_polygon);
				addAvoidingDuplicates(curve_polygon, paths);

				// IfcArbitraryProfileDefWithVoids
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids> profile_with_voids = profileDef.as<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>();
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processing IfcArbitraryProfileDefWithVoids #" << profile_with_voids->getId();
#endif
					for (auto it : profile_with_voids->InnerCurves) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> inner_ifc_curve = it.lock();
						std::vector<carve::geom::vector<2>> inner_curve_polygon;
						std::vector<carve::geom::vector<2>> segment_start_points;

						c_conv.convertIfcCurve2D(inner_ifc_curve, inner_curve_polygon, segment_start_points);
						deleteLastPointIfEqualToFirst(inner_curve_polygon);
						addAvoidingDuplicates(inner_curve_polygon, paths);
					}
#ifdef _DEBUG
					BLUE_LOG(trace) << "Processed IfcArbitraryProfileDefWithVoids #" << profile_with_voids->getId();
#endif
				}
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcArbitraryClosedProfileDef #" << profileDef->getId();
#endif
			}

			void convertIfcArbitraryClosedProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& profile,
				const EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& next_profile,
				const carve::math::Matrix& placement,
				std::shared_ptr<ItemData> itemData,
				const carve::geom::vector<3>& abscissa,
				const carve::geom::vector<3>& next_abscissa) const
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcArbitraryClosedProfileDef #" << profile->getId();
#endif
				const double lengthFactor = UnitConvert()->getLengthInMeterFactor();

				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> outer_curve = profile->OuterCurve;
				std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> polyline = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(outer_curve);

				if (polyline) {
					std::shared_ptr<typename IfcEntityTypesT::IfcCurve> next_outer_curve = next_profile->OuterCurve;
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> next_polyline = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(next_outer_curve);

					// describe 2D-polyline geometry
					std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());

					// describe 3D face geometry (gather vertex indices to avoid duplicates)
					std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
					std::map<std::string, uint32_t> polygonIndices;

					for (int i = 0; i < polyline->Points.size(); ++i) {
						int j = (i + 1) % polyline->Points.size();

						carve::geom::vector<3> position =
							carve::geom::VECTOR(polyline->Points[i]->Coordinates[0], polyline->Points[i]->Coordinates[1], polyline->Points[i]->Coordinates[2]);

						position += abscissa;
						position = placement * position;

						carve::geom::vector<3> nextPosition =
							carve::geom::VECTOR(polyline->Points[j]->Coordinates[0], polyline->Points[j]->Coordinates[1], polyline->Points[j]->Coordinates[2]);

						nextPosition += abscissa;
						nextPosition = placement * nextPosition;

						polylineData->beginPolyline();

						size_t i1 = polylineData->addVertex(position);
						polylineData->addPolylineIndex(i1);
						size_t i2 = polylineData->addVertex(nextPosition);
						polylineData->addPolylineIndex(i2);

						if (next_polyline) {
							if (polyline->Points.size() != next_polyline->Points.size()) {
								return;
							}

							carve::geom::vector<3> position2 =
								carve::geom::VECTOR(next_polyline->Points[i]->Coordinates[0], next_polyline->Points[i]->Coordinates[1], next_polyline->Points[i]->Coordinates[2]);

							position2 += next_abscissa;
							position2 = placement * position2;

							carve::geom::vector<3> nextPosition2 =
								carve::geom::VECTOR(next_polyline->Points[j]->Coordinates[0], next_polyline->Points[j]->Coordinates[1], next_polyline->Points[j]->Coordinates[2]);

							nextPosition2 += next_abscissa;
							nextPosition2 = placement * nextPosition2;

							// set string id and search for existing vertex in polygon
							std::stringstream vID, vID2, vID3, vID4;
							vID << position.x << " " << position.y << " " << position.z;
							vID2 << position2.x << " " << position2.y << " " << position2.z;
							vID3 << nextPosition.x << " " << nextPosition.y << " " << nextPosition.z;
							vID4 << nextPosition2.x << " " << nextPosition2.y << " " << nextPosition2.z;

							uint32_t index1, index2, index3, index4;

							SearchExistingVertex(vID.str(), index1, position, polygonIndices, polygon);
							SearchExistingVertex(vID2.str(), index2, position2, polygonIndices, polygon);
							SearchExistingVertex(vID3.str(), index3, nextPosition, polygonIndices, polygon);
							SearchExistingVertex(vID4.str(), index4, nextPosition2, polygonIndices, polygon);

							polygon->addFace(index1, index3, index4);
							polygon->addFace(index4, index2, index1);
						}
					}

					itemData->polylines.push_back(polylineData);
					itemData->open_or_closed_polyhedrons.push_back(polygon);
				}
				else {
					BLUE_LOG(warning) << "No polyline found in IfcArbitraryClosedProfileDef #" << profile->getId();
				}

#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcArbitraryClosedProfileDef #" << profile->getId();
#endif
			}

			// Function 2: Convert IfcArbitraryOpenProfileDef
			void convertIfcArbitraryOpenProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				// ENTITY IfcArbitraryOpenProfileDef
				//	SUPERTYPE OF(IfcCenterLineProfileDef)
				//	SUBTYPE OF IfcProfileDef;
				//	Curve	 :	IfcBoundedCurve;
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcArbitraryOpenProfileDef #" << profileDef->getId();
#endif
				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> ifc_curve = profileDef->Curve.lock();
				CurveConverterT<IfcEntityTypesT> c_converter(GeomSettings(), UnitConvert(), placementConverter);

				if (profileDef.isOfType<typename IfcEntityTypesT::IfcCenterLineProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcCenterLineProfileDef> center_line_profile_def = profileDef.as<typename IfcEntityTypesT::IfcCenterLineProfileDef>();
					if (center_line_profile_def->Thickness) {
						const double thickness = center_line_profile_def->Thickness * UnitConvert()->getLengthInMeterFactor();
						std::vector<carve::geom::vector<3>> segment_start_points;
						std::vector<carve::geom::vector<3>> basis_curve_points;
						c_converter.convertIfcCurve(ifc_curve, basis_curve_points, segment_start_points);

						int num_base_points = basis_curve_points.size();
						if (num_base_points < 2) {
							std::cout << "IfcCenterLineProfileDef: num curve points < 2";
							return;
						}

						carve::math::Matrix matrix_sweep;
						carve::geom::vector<3> local_z(carve::geom::VECTOR(0, 0, 1));
						std::vector<carve::geom::vector<3>> left_points;
						std::vector<carve::geom::vector<3>> right_points;
						carve::geom::vector<3> point_left(carve::geom::VECTOR(0.0, -thickness * 0.5, 0.0));
						carve::geom::vector<3> point_right(carve::geom::VECTOR(0.0, thickness * 0.5, 0.0));

						for (int ii = 0; ii < num_base_points; ++ii) {
							carve::geom::vector<3> vertex_current = basis_curve_points.at(ii);
							carve::geom::vector<3> vertex_next;
							carve::geom::vector<3> vertex_before;
							if (ii == 0) {
								// first point
								vertex_next = basis_curve_points.at(ii + 1);
								carve::geom::vector<3> delta_element = vertex_next - vertex_current;
								vertex_before = vertex_current - (delta_element);
							}
							else if (ii == num_base_points - 1) {
								// last point
								vertex_before = basis_curve_points.at(ii - 1);
								carve::geom::vector<3> delta_element = vertex_current - vertex_before;
								vertex_next = vertex_before + (delta_element);
							}
							else {
								// inner point
								vertex_next = basis_curve_points.at(ii + 1);
								vertex_before = basis_curve_points.at(ii - 1);
							}

							carve::geom::vector<3> bisecting_normal;
							GeomUtils::bisectingPlane(vertex_before, vertex_current, vertex_next, bisecting_normal);

							if (ii == num_base_points - 1) {
								bisecting_normal *= -1.0;
							}

							local_z.x = 0;
							local_z.y = 0;
							local_z.z = -1;
							GeomUtils::convertPlane2Matrix(bisecting_normal, vertex_current, local_z, matrix_sweep);

							left_points.push_back(matrix_sweep * point_left);
							right_points.push_back(matrix_sweep * point_right);
						}

						std::reverse(right_points.begin(), right_points.end());
						std::vector<carve::geom::vector<2>> polygon;
						for (int i2 = 0; i2 < left_points.size(); ++i2) {
							carve::geom::vector<3>& point3d = left_points[i2];
							polygon.push_back(carve::geom::VECTOR(point3d.x, point3d.y));
						}
						for (int i2 = 0; i2 < right_points.size(); ++i2) {
							carve::geom::vector<3>& point3d = right_points[i2];
							polygon.push_back(carve::geom::VECTOR(point3d.x, point3d.y));
						}
						addAvoidingDuplicates(polygon, paths);
					}
				}
				else {
					std::vector<carve::geom::vector<2>> polygon;
					std::vector<carve::geom::vector<2>> segment_start_points;
					c_converter.convertIfcCurve2D(ifc_curve, polygon, segment_start_points);
					addAvoidingDuplicates(polygon, paths);
				}
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcArbitraryOpenProfileDef #" << profileDef->getId();
#endif
			}

			// Function 3: Convert IfcCompositeProfileDef
			void convertIfcCompositeProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcCompositeProfileDef>& compositeProfileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcCompositeProfileDef #" << compositeProfileDef->getId();
#endif
				std::vector<int> temploop_counts;
				std::vector<int> tempcontour_counts;

				std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcProfileDef>> profiles;
				profiles.reserve(compositeProfileDef->Profiles.size());
				std::transform(
					compositeProfileDef->Profiles.begin(),
					compositeProfileDef->Profiles.end(),
					profiles.begin(),
					[](auto& it) {return it.lock(); });

				for (auto profileDef : profiles) {
					//std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> profileDef = it;

					if (profileDef.isOfType<typename IfcEntityTypesT::IfcParameterizedProfileDef>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcParameterizedProfileDef> parameterized = profileDef.as<typename IfcEntityTypesT::IfcParameterizedProfileDef>();
						convertIfcParameterizedProfileDefWithPosition(parameterized, paths);
						continue;
					}

					if (profileDef.isOfType<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef> open = profileDef.as<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>();
						convertIfcArbitraryOpenProfileDef(open, paths);
						continue;
					}

					if (profileDef.isOfType<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> closed = profileDef.as<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>();
						convertIfcArbitraryClosedProfileDef(closed, paths);
						continue;
					}

					if (profileDef.isOfType<typename IfcEntityTypesT::IfcCompositeProfileDef>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcCompositeProfileDef> composite = profileDef.as<typename IfcEntityTypesT::IfcCompositeProfileDef>();
						convertIfcCompositeProfileDef(composite, paths);
						continue;
					}

					if (profileDef.isOfType<typename IfcEntityTypesT::IfcDerivedProfileDef>()) {
						EXPRESSReference<typename IfcEntityTypesT::IfcDerivedProfileDef> derived = profileDef.as<typename IfcEntityTypesT::IfcDerivedProfileDef>();
						convertIfcDerivedProfileDef(derived, paths);
						continue;
					}
					throw oip::UnhandledException(profileDef);
				}
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcCompositeProfileDef #" << compositeProfileDef->getId();
#endif
			}

			// Function 4: Convert IfcDerivedProfileDef
			void convertIfcDerivedProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcDerivedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcDerivedProfileDef #" << profileDef->getId();
#endif
				ProfileConverterT<IfcEntityTypesT> temp_profiler(GeomSettings(), UnitConvert(), placementConverter);
				temp_profiler.computeProfile(profileDef->ParentProfile.lock());
				const std::vector<std::vector<carve::geom::vector<2>>>& parent_paths = temp_profiler.getCoordinates();

				std::shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D> transf_op_2D = profileDef->Operator.lock();

				carve::math::Matrix transform(carve::math::Matrix::IDENT());
				placementConverter->convertTransformationOperator(transf_op_2D, transform, UnitConvert()->getLengthInMeterFactor());
				for (int i = 0; i < parent_paths.size(); ++i) {
					const std::vector<carve::geom::vector<2>>& loop_parent = parent_paths[i];
					std::vector<carve::geom::vector<2>> loop;

					for (int j = 0; j < loop_parent.size(); ++j) {
						const carve::geom::vector<2>& pt = loop_parent.at(j);
						carve::geom::vector<3> pt3d(carve::geom::VECTOR(pt.x, pt.y, 0));
						pt3d = transform * pt3d;
						loop.push_back(carve::geom::VECTOR(pt3d.x, pt3d.y));
					}
					paths.push_back(loop);
				}

#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcDerivedProfileDef #" << profileDef->getId();
#endif
			}

			/*! \internal TODO
			*
			*/
			// Function 5: Convert IfcOpenCrossProfileDef
			void convertIfcOpenCrossProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcOpenCrossProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				if (profileDef->expired())
					throw oip::ReferenceExpiredException(profileDef);

				std::vector<carve::geom::vector<2>> outer_loop;

				bool horizontal = profileDef->HorizontalWidths;
				vector<double> b = profileDef->Widths * UnitConvert()->getLengthInMeterFactor();
				vector<double> slope = profileDef->Slopes * UnitConvert()->getAngleInRadianFactor();

				if (sizeof(b) != sizeof(slope)) {
					throw oip::InconsistentModellingException(profileDef, "Number of Widths is not even to number of Slopes");
				}
				else {
					double TagX = 0.0;
					double TAgY = 0.0;

					for (int i = 0; i < sizeof(b) / 8; i++) {
						paths.push_back(carve::geom::VECTOR(TagX, TagY));
						double x, y = AddXYCoordinates(horizontal, b(i), slope(i));
						TagX = TagX + x;
						TagY = TagY + y;
					}

				paths.push_back(carve::geom::VECTOR(TagX, TagY));
				}
			}

			double AddXYCoordinates(bool horizontal, double b, double slope) const {
				if (horizontal) {
					if (slope == M_PI_2) {
						throw oip::InconsistentGeometryException(profileDef, "slope can not be 90 degree");
					}
					else
					{
						double x = b;
						double y = b / tan(slope);
					}
				}
				else {
					double x = b * cos(slope);
					double y = b * sin(slope);
				}
				return x, y;
			}

			/*! \brief  Defines a 2D position coordinate system to which the parameters of the different profiles relate to.
			*  \param[in] profileDef A pointer to data from IfcProfileDef.
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			// Function 6: Convert IfcParametrizedProfileDef
			void convertIfcParameterizedProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcParameterizedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{

				// *************************************************************************************************************************************************************
				//	ENTITY IfcParameterizedProfileDef	
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifcparameterizedprofiledef.htm		
				//	ABSTRACT SUPERTYPE OF(ONEOF
				//	(IfcAsymmetricIShapeProfileDef
				//		, IfcCShapeProfileDef
				//		, IfcCircleProfileDef
				//		, IfcEllipseProfileDef
				//		, IfcIShapeProfileDef
				//		, IfcLShapeProfileDef
				//		, IfcRectangleProfileDef
				//		, IfcTShapeProfileDef
				//		, IfcTrapeziumProfileDef
				//		, IfcUShapeProfileDef
				//		, IfcZShapeProfileDef))
				//	SUBTYPE OF(IfcProfileDef);
				//	Position: OPTIONAL IfcAxis2Placement2D;
				//	END_ENTITY;
				//
				// *************************************************************************************************************************************************************
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcParameterizedProfileDef #" << profileDef->getId();
#endif

				// (1/10) IfcRectangleProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcRectangleProfileDef>()) {
					return convertIfcRectangleProfileDef(profileDef.as<typename IfcEntityTypesT::IfcRectangleProfileDef>(), paths);
				}

				// (2/10) IfcTrapeziumProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcTrapeziumProfileDef>()) {
					return convertIfcTrapeziumProfileDef(profileDef.as<typename IfcEntityTypesT::IfcTrapeziumProfileDef>(), paths);
				}

				// (3/10) IfcCircleProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcCircleProfileDef>()) {
					return convertIfcCircleProfileDef(profileDef.as<typename IfcEntityTypesT::IfcCircleProfileDef>(), paths);
				}

				// (4/10) IfcEllipseProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcEllipseProfileDef>()) {
					return convertIfcEllipseProfileDef(profileDef.as<typename IfcEntityTypesT::IfcEllipseProfileDef>(), paths);
				}

				// (5/10) IfcIShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcIShapeProfileDef>()) {
					return convertIfcIShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcIShapeProfileDef>(), paths);
				}

				// (6/10) IfcLShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcLShapeProfileDef>()) {
					return convertIfcLShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcLShapeProfileDef>(), paths);
				}

				// (7/10) IfcUShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcUShapeProfileDef>()) {
					return convertIfcUShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcUShapeProfileDef>(), paths);
				}

				// (8/10) IfcCShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcCShapeProfileDef>()) {
					return convertIfcCShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcCShapeProfileDef>(), paths);
				}

				// (9/10) IfcZShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcZShapeProfileDef>()) {
					return convertIfcZShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcZShapeProfileDef>(), paths);
				}

				// (10/10) IfcTShapeProfileDef SUBTYPE OF IfcParametrizedProfileDef
				if (profileDef.isOfType<typename IfcEntityTypesT::IfcTShapeProfileDef>()) {
					return convertIfcTShapeProfileDef(profileDef.as<typename IfcEntityTypesT::IfcTShapeProfileDef>(), paths);
				}

				// Not supported ProfileDef
				throw oip::UnhandledException(profileDef);
			}
			

			/*! \brief defines a rectangle as the profile definition
			*  \param[in] rectangle_profile A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			void convertIfcRectangleProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcRectangleProfileDef>& rectangle_profile,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//	**************************************************************************************************************************
				//	ENTITY IfcRectangleProfileDef
				//	SUPERTYPE OF(ONEOF
				//		(IfcRectangleHollowProfileDef
				//		, IfcRoundedRectangleProfileDef))
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		XDim: IfcPositiveLengthMeasure;
				//		YDim: IfcPositiveLengthMeasure;
				//	END_ENTITY;
				//	**************************************************************************************************************************
				if (rectangle_profile->XDim && rectangle_profile->YDim) {
					// IfcRectangleHollowProfileDef SUBTYPE OF IfcRectangleProfile 
					if (rectangle_profile.isOfType<typename IfcEntityTypesT::IfcRectangleHollowProfileDef>()) {
						convertIfcRectangleHollowProfileDef(rectangle_profile.as<typename IfcEntityTypesT::IfcRectangleHollowProfileDef>(), paths);
					}
					// IfcRoundedRectangleProfileDef SUBTYPE OF IfcRectangleProfile 
					else if (rectangle_profile.isOfType<typename IfcEntityTypesT::IfcRoundedRectangleProfileDef>()) {
						convertIfcRoundedRectangleProfileDef(rectangle_profile.as<typename IfcEntityTypesT::IfcRoundedRectangleProfileDef>(), paths);
					}
					// Else it's a standard rectangle
					else {
						convertIfcStandardRectangleProfileDef(rectangle_profile, paths);
					}
				}
			}

			/*! \brief provides the defining parameters of a rectangular hollow section
			*  \param[in] hollow A pointer to data from \c IfcRectangleProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			void convertIfcRectangleHollowProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcRectangleHollowProfileDef>& hollow, 
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//	**************************************************************************************************************************
				//	ENTITY IfcRectangleHollowProfileDef
				//  SUBTYPE OF(IfcRectangleProfileDef);
				//		WallThickness: IfcPositiveLengthMeasure;
				//		InnerFilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		OuterFilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//  WHERE
				//		ValidWallThickness : (WallThickness < (SELF\IfcRectangleProfileDef.XDim / 2.)) AND
				//		(WallThickness < (SELF\IfcRectangleProfileDef.YDim / 2.));
				//		ValidInnerRadius: NOT(EXISTS(InnerFilletRadius)) OR
				//		((InnerFilletRadius <= (SELF\IfcRectangleProfileDef.XDim / 2. - WallThickness)) AND
				//		(InnerFilletRadius <= (SELF\IfcRectangleProfileDef.YDim / 2. - WallThickness)));
				//		ValidOuterRadius: NOT(EXISTS(OuterFilletRadius)) OR
				//		((OuterFilletRadius <= (SELF\IfcRectangleProfileDef.XDim / 2.)) AND
				//		(OuterFilletRadius <= (SELF\IfcRectangleProfileDef.YDim / 2.)));
				//	END_ENTITY;
				//	**************************************************************************************************************************
				double x = hollow->XDim * UnitConvert()->getLengthInMeterFactor();
				double y = hollow->YDim * UnitConvert()->getLengthInMeterFactor();
				std::vector<carve::geom::vector<2>> outer_loop;
				std::vector<carve::geom::vector<2>> inner_loop;
				if (hollow->WallThickness) {
					double t = hollow->WallThickness * UnitConvert()->getLengthInMeterFactor();
					double r1 = hollow->InnerFilletRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
					double r2 = hollow->InnerFilletRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
					// Outer
					AddRectangleCoordinates(outer_loop, r1, x, y);

					// Inner
					x -= 2.0 * t;
					y -= 2.0 * t;
					AddRectangleCoordinates(inner_loop, r2, x, y);

					paths.push_back(outer_loop);
					paths.push_back(inner_loop);
				}
				return;
			}

			/*! \brief defines a rectangle with equally rounded corners as the profile definition
			*  \param[in] rounded_rectangle A pointer to data from \c IfcRectangleProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			void convertIfcRoundedRectangleProfileDef(const EXPRESSReference <typename IfcEntityTypesT::IfcRoundedRectangleProfileDef>& rounded_rectangle,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//	**************************************************************************************************************************
				//	ENTITY IfcRoundedRectangleProfileDef
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifcroundedrectangleprofiledef.htm
				//	SUBTYPE OF(IfcRectangleProfileDef);
				//		RoundingRadius: IfcPositiveLengthMeasure;
				//	WHERE
				//		ValidRadius : ((RoundingRadius <= (SELF\IfcRectangleProfileDef.XDim / 2.)) AND
				//		(RoundingRadius <= (SELF\IfcRectangleProfileDef.YDim / 2.)));
				//	END_ENTITY;
				//	**************************************************************************************************************************
				double x = rounded_rectangle->XDim * UnitConvert()->getLengthInMeterFactor();
				double y = rounded_rectangle->YDim * UnitConvert()->getLengthInMeterFactor();
				std::vector<carve::geom::vector<2>> outer_loop;
				if (rounded_rectangle->RoundingRadius) {
					AddRectangleCoordinates(outer_loop, rounded_rectangle->RoundingRadius * UnitConvert()->getLengthInMeterFactor(), x, y);
					paths.push_back(outer_loop);
				}
				return;
			}
			/*! \brief defines a standard rectangle
			*  \param[in] rectangle_profile A pointer to data from \c IfcRectangleProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			void convertIfcStandardRectangleProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcRectangleProfileDef>& rectangle_profile, 
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				
				double x = rectangle_profile->XDim * UnitConvert()->getLengthInMeterFactor();
				double y = rectangle_profile->YDim * UnitConvert()->getLengthInMeterFactor();
				std::vector<carve::geom::vector<2>> outer_loop;
				AddRectangleCoordinates(outer_loop, 0.0, x, y);
				paths.push_back(outer_loop);
				return;
			}

			/*! \brief defines a trapezium as the profile definition
			*  \param[in] trapezium A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data
			*/
			void convertIfcTrapeziumProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcTrapeziumProfileDef>& trapezium,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				// **************************************************************************************************************************
				// ENTITY IfcTrapeziumProfileDef
				// https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifctrapeziumprofiledef.htm			
				// SUBTYPE OF(IfcParameterizedProfileDef);
				//		BottomXDim: IfcPositiveLengthMeasure;
				//		TopXDim: IfcPositiveLengthMeasure;
				//		YDim: IfcPositiveLengthMeasure;
				//		TopXOffset: IfcLengthMeasure;
				// END_ENTITY;
				// **************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (trapezium->BottomXDim && trapezium->TopXDim && trapezium->TopXOffset && trapezium->YDim) {
					double xBottom = trapezium->BottomXDim * UnitConvert()->getLengthInMeterFactor();
					double xTop = trapezium->TopXDim * UnitConvert()->getLengthInMeterFactor();
					double xOffset = trapezium->TopXOffset * UnitConvert()->getLengthInMeterFactor();
					double y = trapezium->YDim * UnitConvert()->getLengthInMeterFactor();

					AddTrapeziumCoordinates(outer_loop, xBottom, xOffset, xTop, y);
					paths.push_back(outer_loop);
				}
				return;
			}

			/*! \brief defines a circle as the profile definition
			*  \param[in] circle_profile_def A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcCircleProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcCircleProfileDef> & circle_profile_def,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				// **************************************************************************************************************************
				// ENTITY IfcCircleProfileDef
				//  https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifccircleprofiledef.htm
				// SUPERTYPE OF(ONEOF
				// (IfcCircleHollowProfileDef))
				// SUBTYPE OF(IfcParameterizedProfileDef);
				// Radius: IfcPositiveLengthMeasure;
				// END_ENTITY;
				// **************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				double radius = circle_profile_def->Radius * UnitConvert()->getLengthInMeterFactor();
				if (radius < GeomSettings()->getPrecision()) {
					return;
				}
				int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(radius);
				double d_angle = GeomSettings()->getAngleLength(radius);

				addArc(outer_loop, radius, 0.0, d_angle, 0.0, 0.0, num_segments);
				paths.push_back(outer_loop);

				// IfcCircleHollowProfileDef SUBTYPE OF IfcCircleProfileDef
				if (circle_profile_def.isOfType<typename IfcEntityTypesT::IfcCircleHollowProfileDef>()) {
					EXPRESSReference<typename IfcEntityTypesT::IfcCircleHollowProfileDef> hollow = circle_profile_def.as<typename IfcEntityTypesT::IfcCircleHollowProfileDef>();
					std::vector<carve::geom::vector<2>> inner_loop;
					double radius2 = radius - hollow->WallThickness * UnitConvert()->getLengthInMeterFactor();
					int num_segments2 = GeomSettings()->getNumberOfSegmentsForTessellation(radius2);
					double d_angle2 = GeomSettings()->getAngleLength(radius2);

					addArc(inner_loop, radius2, 0.0, d_angle2, 0.0, 0.0, num_segments2);
					paths.push_back(inner_loop);
				}
				return;
			}

			/*! \brief defines an ellipse as the profile definition
			*  \param[in] ellipse_profile_def A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcEllipseProfileDef(const EXPRESSReference <typename IfcEntityTypesT::IfcEllipseProfileDef> & ellipse_profile_def,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				// **************************************************************************************************************************
				// ENTITY IfcEllipseProfileDef
				// https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifcellipseprofiledef.htm
				// ENTITY IfcEllipseProfileDef
				// SUBTYPE OF(IfcParameterizedProfileDef);
				//		SemiAxis1: IfcPositiveLengthMeasure;
				//		SemiAxis2: IfcPositiveLengthMeasure;
				// END_ENTITY;
				// **************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (ellipse_profile_def->SemiAxis1) {
					if (ellipse_profile_def->SemiAxis2) {
						double xRadius = ellipse_profile_def->SemiAxis1 * UnitConvert()->getLengthInMeterFactor();
						double yRadius = ellipse_profile_def->SemiAxis2 * UnitConvert()->getLengthInMeterFactor();
						double radiusMax = std::max(xRadius, yRadius);
						int num_segments = GeomSettings()->getNumberOfSegmentsForTessellation(radiusMax);
						double d_angle = GeomSettings()->getAngleLength(radiusMax);
						double angle = 0.0;

						for (int i = 0; i < num_segments; ++i) {
							outer_loop.push_back(carve::geom::VECTOR((xRadius * cos(angle)), (yRadius * sin(angle))));
							angle += d_angle;
						}
						paths.push_back(outer_loop);
					}
				}
				return;
			}

			/*! \brief defines a section profile that provides the defining parameters of an 'I' or 'H' section
			*  \param[in] rectangle_profile A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcIShapeProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcIShapeProfileDef> i_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				// **************************************************************************************************************************
				// ENTITY IfcIShapeProfileDef
				//  https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifcishapeprofiledef.htm
				// SUBTYPE OF(IfcParameterizedProfileDef);
				//		OverallWidth: IfcPositiveLengthMeasure;
				//		OverallDepth: IfcPositiveLengthMeasure;
				//		WebThickness: IfcPositiveLengthMeasure;
				//		FlangeThickness: IfcPositiveLengthMeasure;
				//		FilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		FlangeEdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		FlangeSlope: OPTIONAL IfcPlaneAngleMeasure;
				// WHERE
				//		ValidFlangeThickness : (2. * FlangeThickness) < OverallDepth;
				//		ValidWebThickness: WebThickness < OverallWidth;
				//		ValidFilletRadius: NOT(EXISTS(FilletRadius)) OR
				//		((FilletRadius <= (OverallWidth - WebThickness) / 2.) AND
				//		(FilletRadius <= (OverallDepth - (2. * FlangeThickness)) / 2.));
				// END_ENTITY;
				// **************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (i_shape->OverallDepth && i_shape->OverallWidth && i_shape->WebThickness && i_shape->FlangeThickness) {
					double h = i_shape->OverallDepth * UnitConvert()->getLengthInMeterFactor();
					double b = i_shape->OverallWidth * UnitConvert()->getLengthInMeterFactor();
					double tw = i_shape->WebThickness * UnitConvert()->getLengthInMeterFactor();
					double tf = i_shape->FlangeThickness * UnitConvert()->getLengthInMeterFactor();
					double r = i_shape->FilletRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();

					outer_loop.push_back(carve::geom::VECTOR(b * 0.5, -h * 0.5));
					outer_loop.push_back(carve::geom::VECTOR(b * 0.5, (-h * 0.5 + tf)));

					addArc_or_push_back(outer_loop, r, 3 * M_PI_2, -M_PI_2, (tw * 0.5 + r), (-h * 0.5 + tf + r), (tw * 0.5), (-h * 0.5 + tf));

					// IfcAsymmetricIShapeProfileDef SUBTYPE OF IfcIShapeProfileDef
					if (i_shape.isOfType<typename IfcEntityTypesT::IfcAsymmetricIShapeProfileDef>()) {
						auto asym_I_profile = i_shape.as<typename IfcEntityTypesT::IfcAsymmetricIShapeProfileDef>();

						if (asym_I_profile->TopFlangeWidth) {
							double bTop = asym_I_profile->TopFlangeWidth * UnitConvert()->getLengthInMeterFactor();
							double tfTop = asym_I_profile->TopFlangeThickness.value_or(i_shape->FlangeThickness) * UnitConvert()->getLengthInMeterFactor();
							double rTop = asym_I_profile->TopFlangeFilletRadius.value_or(i_shape->FilletRadius.value_or(0.0)) * UnitConvert()->getLengthInMeterFactor();
							
							addArc_or_push_back(outer_loop, rTop, M_PI, -M_PI_2, (tw * 0.5 + rTop), (h * 0.5 - tfTop - rTop), (tw * 0.5), (h * 0.5 - tfTop));

							outer_loop.push_back(carve::geom::VECTOR(bTop * 0.5, (h * 0.5 - tfTop)));
							outer_loop.push_back(carve::geom::VECTOR(bTop * 0.5, h * 0.5));
						}
					}
					else {
						// symmetric: mirror horizontally along x-Axis
						mirrorCopyPathReverse(outer_loop, false, true);
					}

					// mirror vertically along y-axis
					mirrorCopyPathReverse(outer_loop, true, false);
					paths.push_back(outer_loop);
				}
				return;
			}


			/*! \brief defines a section profile that provides the defining parameters of an L-shaped section
			*  \param[in] l_shape A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcLShapeProfileDef(const EXPRESSReference <typename IfcEntityTypesT::IfcLShapeProfileDef >& l_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				std::vector<carve::geom::vector<2>> outer_loop;
				// **************************************************************************************************************************
				//  ENTITY IfcLShapeProfileDef
				//  https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifclshapeprofiledef.htm
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		Depth: IfcPositiveLengthMeasure;
				//		Width: OPTIONAL IfcPositiveLengthMeasure;
				//		Thickness: IfcPositiveLengthMeasure;
				//		FilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		EdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		LegSlope: OPTIONAL IfcPlaneAngleMeasure;
				//	WHERE
				//		ValidThickness : (Thickness < Depth) AND(NOT(EXISTS(Width)) OR(Thickness < Width));
				//	END_ENTITY;
				// **************************************************************************************************************************
				if (l_shape->Depth && l_shape->Thickness) {
					double h = l_shape->Depth * UnitConvert()->getLengthInMeterFactor();
					double b = l_shape->Width.value_or(l_shape->Depth) * UnitConvert()->getLengthInMeterFactor();
					double t = l_shape->Thickness;
					double r1 = l_shape->FilletRadius.value_or(0.) * UnitConvert()->getLengthInMeterFactor();
					double r2 = l_shape->EdgeRadius.value_or(0.) * UnitConvert()->getLengthInMeterFactor();
					double ls = l_shape->LegSlope.value_or(0.) * UnitConvert()->getLengthInMeterFactor();

					outer_loop.push_back(carve::geom::VECTOR(-b * 0.5, -h * 0.5));
					outer_loop.push_back(carve::geom::VECTOR(b * 0.5, -h * 0.5));

					addArc_or_push_back(outer_loop, r2, 0.0, M_PI_2 - ls, b * 0.5 - r2, -h * 0.5 + t - r2, b * 0.5, (-h * 0.5 + t));

					double s = sin(ls);
					double c = cos(ls);
					double z1 = (-s * ((c - s) * (r1 + r2 + t) - c * b + s * h)) / (2 * c * c - 1);
					double z2 = (-s * ((c - s) * (r1 + r2 + t) - c * h + s * b)) / (2 * c * c - 1);

					addArc_or_push_back(outer_loop, r1, (3 * M_PI_2 - ls), (-M_PI_2 + 2 * ls), (-b * 0.5 + t + z2 + r1), (-h * 0.5 + t + z1 + r1), (-b * 0.5 + t + z2), (-h * 0.5 + t + z1));
					addArc_or_push_back(outer_loop, r2, ls, (M_PI_2 - ls), (-b * 0.5 + t - r2), (h * 0.5 - r2), (-b * 0.5 + t), (h * 0.5));

					outer_loop.push_back(carve::geom::VECTOR(-b * 0.5, h * 0.5));
					paths.push_back(outer_loop);
				}
				return;
			}

			/*! \brief defines a section profile that provides the defining parameters of a U-shape (channel) section
			*  \param[in] u_shape A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcUShapeProfileDef(const EXPRESSReference <typename IfcEntityTypesT::IfcUShapeProfileDef>& u_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				// **************************************************************************************************************************
				//	ENTITY IfcUShapeProfileDef
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifcushapeprofiledef.htm
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		Depth: IfcPositiveLengthMeasure;
				//		FlangeWidth: IfcPositiveLengthMeasure;
				//		WebThickness: IfcPositiveLengthMeasure;
				//		FlangeThickness: IfcPositiveLengthMeasure;
				//		FilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		EdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		FlangeSlope: OPTIONAL IfcPlaneAngleMeasure;
				//	WHERE
				//		ValidFlangeThickness : FlangeThickness < (Depth / 2.);
				//		ValidWebThickness: WebThickness < FlangeWidth;
				//	END_ENTITY;
				// **************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (u_shape->Depth && u_shape->FlangeWidth && u_shape->WebThickness && u_shape->FlangeThickness) {
					double h = u_shape->Depth * UnitConvert()->getLengthInMeterFactor();
					double b = u_shape->FlangeWidth * UnitConvert()->getLengthInMeterFactor();
					double tw = u_shape->WebThickness * UnitConvert()->getLengthInMeterFactor();
					double tf = u_shape->FlangeThickness * UnitConvert()->getLengthInMeterFactor();
					double r1 = u_shape->FilletRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
					double r2 = u_shape->EdgeRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
					double fs = u_shape->FlangeSlope.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();

					outer_loop.push_back(carve::geom::VECTOR(-b * 0.5, -h * 0.5));
					outer_loop.push_back(carve::geom::VECTOR(b * 0.5, -h * 0.5));

					double z = tan(fs) * (b * 0.5 - r2);
					addArc_or_push_back(outer_loop, r2, 0, (M_PI_2 - fs), (b * 0.5 - r2), (-h * 0.5 + tf - z - r2), (b * 0.5), (-h * 0.5 + tf - z));

					z = tan(fs) * (b * 0.5 - tw - r1);
					addArc_or_push_back(outer_loop, r1, (3 * M_PI_2 - fs), (-M_PI_2 + fs), (-b * 0.5 + tw + r1), (-h * 0.5 + tf + z + r1), (-b * 0.5 + tw), (-h * 0.5 + tf + z));

					// mirror horizontally along x-Axis
					mirrorCopyPathReverse(outer_loop, false, true);
					paths.push_back(outer_loop);
				}
				return;
			}

			/*! \brief defines a section profile that provides the defining parameters of a C-shaped section
			*  \param[in] c_shape A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcCShapeProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcCShapeProfileDef>& c_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//  **************************************************************************************************************************
				//	ENTITY IfcCShapeProfileDef
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifccshapeprofiledef.htm
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		Depth: IfcPositiveLengthMeasure;
				//		Width: IfcPositiveLengthMeasure;
				//		WallThickness: IfcPositiveLengthMeasure;
				//		Girth: IfcPositiveLengthMeasure;
				//		InternalFilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//	WHERE
				//		ValidGirth : Girth < (Depth / 2.);
				//		ValidInternalFilletRadius: NOT(EXISTS(InternalFilletRadius)) OR
				//		((InternalFilletRadius <= Width / 2. - WallThickness) AND(InternalFilletRadius <= Depth / 2. - WallThickness));
				//		ValidWallThickness: (WallThickness < Width / 2.) AND(WallThickness < Depth / 2.);
				//	END_ENTITY;
				//	**************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (c_shape->Depth && c_shape->Width && c_shape->Girth && c_shape->WallThickness) {
					double h = c_shape->Depth * UnitConvert()->getLengthInMeterFactor();
					double b = c_shape->Width * UnitConvert()->getLengthInMeterFactor();
					double g = c_shape->Girth * UnitConvert()->getLengthInMeterFactor();
					double t = c_shape->WallThickness * UnitConvert()->getLengthInMeterFactor();
					double r1 = c_shape->InternalFilletRadius.value_or(0.) * UnitConvert()->getLengthInMeterFactor();

					addArc_or_push_back(outer_loop, (r1 + t), M_PI, M_PI_2, (-b * 0.5 + t + r1), (-h * 0.5 + t + r1), (-b * 0.5), (-h * 0.5));
					addArc_or_push_back(outer_loop, (r1 + t), 3 * M_PI_2, M_PI_2, (b * 0.5 - t - r1), (-h * 0.5 + t + r1), (b * 0.5), (-h * 0.5));

					outer_loop.push_back(carve::geom::VECTOR(b * 0.5, (-h * 0.5 + g)));
					outer_loop.push_back(carve::geom::VECTOR((b * 0.5 - t), (-h * 0.5 + g)));

					addArc_or_push_back(outer_loop, r1, 0, -M_PI_2, (b * 0.5 - t - r1), (-h * 0.5 + t + r1), (b * 0.5 - t), (-h * 0.5 + t));
					addArc_or_push_back(outer_loop, r1, 3 * M_PI_2, -M_PI_2, (-b * 0.5 + t + r1), (-h * 0.5 + t + r1), (-b * 0.5 + t), (-h * 0.5 + t));

					// mirror horizontally along x-Axis
					mirrorCopyPathReverse(outer_loop, false, true);
					paths.push_back(outer_loop);
				}
				return;
			}

			/*! \brief defines a section profile that provides the defining parameters of a Z-shape section
			*  \param[in] z_shape A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcZShapeProfileDef(const EXPRESSReference <typename IfcEntityTypesT::IfcZShapeProfileDef>& z_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//	**************************************************************************************************************************
				//	ENTITY IfcZShapeProfileDef
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifczshapeprofiledef.htm
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		Depth: IfcPositiveLengthMeasure;
				//		FlangeWidth: IfcPositiveLengthMeasure;
				//		WebThickness: IfcPositiveLengthMeasure;
				//		FlangeThickness: IfcPositiveLengthMeasure;
				//		FilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		EdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//	WHERE
				//		ValidFlangeThickness : FlangeThickness < (Depth / 2.);
				//	END_ENTITY;
				//	**************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				if (z_shape->Depth && z_shape->FlangeWidth && z_shape->WebThickness && z_shape->FlangeThickness) {
					double h = z_shape->Depth * UnitConvert()->getLengthInMeterFactor();
					double b = z_shape->FlangeWidth * UnitConvert()->getLengthInMeterFactor();
					double tw = z_shape->WebThickness * UnitConvert()->getLengthInMeterFactor();
					double tf = z_shape->FlangeThickness * UnitConvert()->getLengthInMeterFactor();
					double r1 = z_shape->FilletRadius.value_or(0.) * UnitConvert()->getLengthInMeterFactor();
					double r2 = z_shape->EdgeRadius.value_or(0.) * UnitConvert()->getLengthInMeterFactor();

					outer_loop.push_back(carve::geom::VECTOR((-tw * 0.5), -h * 0.5));
					outer_loop.push_back(carve::geom::VECTOR((b - tw * 0.5), -h * 0.5));

					addArc_or_push_back(outer_loop, r2, 0, M_PI_2, (b - tw * 0.5 - r2), (-h * 0.5 + tf - r2), (b - tw * 0.5), (-h * 0.5 + tf));
					addArc_or_push_back(outer_loop, r1, 3 * M_PI_2, -M_PI_2, (tw * 0.5 + r1), (-h * 0.5 + tf + r1), (tw * 0.5), (-h * 0.5 + tf));

					// mirror horizontally and vertically
					mirrorCopyPath(outer_loop, true, true);
					paths.push_back(outer_loop);
				}
				return;
			}

			/*! \brief defines a section profile that provides the defining parameters of a T-shaped section
			*  \param[in] t_shape A pointer to data from \c IfcParametrizedProfileDef
			*  \param[out] paths A pointer to be filled with the relevant data.
			*/
			void convertIfcTShapeProfileDef(const EXPRESSReference<typename IfcEntityTypesT::IfcTShapeProfileDef>& t_shape,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const {
				//	**************************************************************************************************************************
				//	ENTITY IfcTShapeProfileDef
				//	https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcprofileresource/lexical/ifctshapeprofiledef.htm
				//	SUBTYPE OF(IfcParameterizedProfileDef);
				//		Depth: IfcPositiveLengthMeasure;
				//		FlangeWidth: IfcPositiveLengthMeasure;
				//		WebThickness: IfcPositiveLengthMeasure;
				//		FlangeThickness: IfcPositiveLengthMeasure;
				//		FilletRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		FlangeEdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		WebEdgeRadius: OPTIONAL IfcNonNegativeLengthMeasure;
				//		WebSlope: OPTIONAL IfcPlaneAngleMeasure;
				//		FlangeSlope: OPTIONAL IfcPlaneAngleMeasure;
				//	WHERE
				//		ValidFlangeThickness : FlangeThickness < Depth;
				//		ValidWebThickness: WebThickness < FlangeWidth;
				//	END_ENTITY;
				//	**************************************************************************************************************************
				std::vector<carve::geom::vector<2>> outer_loop;
				const double h = t_shape->Depth * UnitConvert()->getLengthInMeterFactor();
				const double b = t_shape->FlangeWidth * UnitConvert()->getLengthInMeterFactor();
				const double tw = t_shape->WebThickness * UnitConvert()->getLengthInMeterFactor() * 0.5;
				const double tf = t_shape->FlangeThickness * UnitConvert()->getLengthInMeterFactor();
				double r1 = t_shape->FilletRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
				double r2 = r2 = t_shape->FlangeEdgeRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
				double r3 = t_shape->WebEdgeRadius.value_or(0.0) * UnitConvert()->getLengthInMeterFactor();
				double fs = t_shape->FlangeSlope.value_or(0.0) * UnitConvert()->getAngleInRadianFactor();
				double ws = t_shape->WebSlope.value_or(0.0) * UnitConvert()->getAngleInRadianFactor();

				outer_loop.push_back(carve::geom::VECTOR(-b * 0.5, h * 0.5));

				double zf = tan(fs) * (b * 0.25 - r2);
				double zw = tan(ws) * (h * 0.5 - r3);

				addArc_or_push_back(outer_loop, r2, M_PI, M_PI_2 - fs, (-b * 0.5 + r2), (h * 0.5 - tf + zf + r2), (-b * 0.5), (h * 0.5 - tf + zf));

				double cf = cos(fs);
				double sf = sin(fs);
				double cw = cos(ws);
				double sw = sin(ws);
				double z1 = (sf * ((b - 2 * (r1 + r2 + tw - zw)) * cw - 2 * (h - r3 - r1 - tf + zf) * sw)) / (2 * (cf * cw - sf * sw));
				double z2 = tan(ws) * (h - r3 - r1 - z1 - tf + zf);

				addArc_or_push_back(outer_loop, r1, (M_PI_2 - fs), (-M_PI_2 + fs + ws), (-tw + zw - z2 - r1), (h * 0.5 - tf + zf - z1 - r1), (-tw + zw - z2), (h * 0.5 - tf + zf - z1));
				addArc_or_push_back(outer_loop, r3, (M_PI + ws), (M_PI_2 - ws), (-tw + zw + r3), (-h * 0.5 + r3), (-tw + zw), (-h * 0.5));

				// mirror vertically along y-Axis
				mirrorCopyPathReverse(outer_loop, true, false);
				paths.push_back(outer_loop);
				return;
			}

			/*
			void ProfileConverter::convertIfcNurbsProfile(const std::shared_ptr<IfcNurbsProfile>& nurbs_profile,
			std::vector<std::vector<carve::geom::vector<3>>>& paths )
			{
			std::stringstream err;
			std::shared_ptr<IfcRationalBSplineSurfaceWithKnots> surface = std::dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(nurbs_profile->Surface);
			if( !surface )
			{
			return;
			}
			std::vector<carve::geom::vector<3> > loop;
			double length_factor = polygon->getLengthInMeterFactor();
			std::vector<std::vector<std::shared_ptr<IfcCartesianPoint> > >& vec_control_points = surface->ControlPointsList;
			std::vector<std::vector<double> >& vec_weights = surface->WeightsData;

			// o------------<------------o
			// |     --> xi              |
			// |    |                    |
			// v    v                    ^
			// |    eta                  |
			// |                         |
			// o------------>------------o
			// insert control points at xi=0/1 and eta=0/1

			RepresentationConverter converter( polygon );

			// xi = 0
			std::vector<std::shared_ptr<IfcCartesianPoint> >& vec_control_points_eta0 = vec_control_points[0];
			std::vector<std::shared_ptr<IfcCartesianPoint> >::iterator it_xi0 = vec_control_points_eta0.begin();
			for( ; it_xi0 != vec_control_points_eta0.end(); ++it_xi0 )
			{
			std::shared_ptr<IfcCartesianPoint>& ifc_point = (*it_xi0);
			carve::geom::vector<3>  point;
			converter.convertIfcCartesianPoint( ifc_point, point );
			loop.push_back(point);
			}

			// eta = 1
			std::vector<std::vector<std::shared_ptr<IfcCartesianPoint> > >::iterator it_eta1 = vec_control_points.begin();
			std::vector<std::vector<std::shared_ptr<IfcCartesianPoint> > >::iterator it_eta1_last = vec_control_points.end();
			++it_eta1;
			--it_eta1_last;
			for( ; it_eta1 != it_eta1_last; ++it_eta1 )
			{
			std::vector<std::shared_ptr<IfcCartesianPoint> >& vec_eta = *it_eta1;
			std::shared_ptr<IfcCartesianPoint>& ifc_point = vec_eta.back();
			carve::geom::vector<3>  point;
			converter.convertIfcCartesianPoint( ifc_point, point );
			loop.push_back(point);
			}

			// xi = 1
			std::vector<std::shared_ptr<IfcCartesianPoint> >& vec_control_points_eta1 = vec_control_points[vec_control_points.size()-1];
			std::vector<std::shared_ptr<IfcCartesianPoint> >::reverse_iterator it_control_points_reverse = vec_control_points_eta1.rbegin();
			for( ; it_control_points_reverse != vec_control_points_eta1.rend(); ++it_control_points_reverse )
			{
			std::shared_ptr<IfcCartesianPoint>& ifc_point = (*it_control_points_reverse);
			carve::geom::vector<3>  point;
			converter.convertIfcCartesianPoint( ifc_point, point );
			loop.push_back(point);
			}

			// eta = 0
			std::vector<std::vector<std::shared_ptr<IfcCartesianPoint> > >::reverse_iterator it_eta0 = vec_control_points.rbegin();
			std::vector<std::vector<std::shared_ptr<IfcCartesianPoint> > >::reverse_iterator it_eta0_last = vec_control_points.rend();
			++it_eta0;
			--it_eta0_last;
			for( ; it_eta0 != it_eta0_last; ++it_eta0 )
			{
			std::vector<std::shared_ptr<IfcCartesianPoint> >& vec_eta = *it_eta1;
			std::shared_ptr<IfcCartesianPoint>& ifc_point = vec_eta.back();
			carve::geom::vector<3>  point;
			converter.convertIfcCartesianPoint( ifc_point, point );
			loop.push_back(point);
			}
			paths.push_back(loop);
			}
			*/

			// Function 7: Convert IfcArbitraryProfileWithVoids
			void convertIfcArbitraryProfileWithVoids(const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>& profile_with_voids,
				const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>& next_profile_with_voids,
				const carve::math::Matrix& placement,
				std::shared_ptr<ItemData> itemData,
				const carve::geom::vector<3>& abscissa,
				const carve::geom::vector<3>& next_abscissa)
			{
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processing IfcArbitraryProfileDefWithVoids #" << profile_with_voids->getId();
#endif
				const double lengthFactor = UnitConvert()->getLengthInMeterFactor();

				std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> outer_curve =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(profile_with_voids);
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCurve>> inner_curves = profile_with_voids->InnerCurves;

				std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> next_outer_curve =
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(next_profile_with_voids);
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCurve>> next_inner_curves = next_profile_with_voids->InnerCurves;

				// if there is any outer curve (as closed profile) convert it to geometry first
				if(outer_curve) {
					convertIfcArbitraryClosedProfileDef(outer_curve, next_outer_curve, placement, itemData, abscissa, next_abscissa);
				}

				// then convert all inner curve profiles
				for(int i = 0; i < inner_curves.size(); ++i) {
					// this inner curve
					std::shared_ptr<typename IfcEntityTypesT::IfcCurve> inner_curve = inner_curves[i];
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> polyline = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(inner_curve);

					// next inner curve
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> next_polyline;
					if(next_inner_curves.size() == inner_curves.size()) {
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> next_inner_curve = next_inner_curves[i];
						next_polyline = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(next_inner_curve);
					}

					if(polyline) {
						std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> bounded_curve = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(polyline);

						// describe 2D-polyline geometry
						std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());

						// describe 3D face geometry (gather vertex indices to avoid duplicates)
						std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
						std::map<std::string, uint32_t> polygonIndices;

						for(int j = 0; j < polyline->Points.size(); ++j) {
							int h = (j + 1) % polyline->Points.size();

							carve::geom::vector<3> position =
								carve::geom::VECTOR(polyline->Points[j]->Coordinates[0], polyline->Points[j]->Coordinates[1], polyline->Points[j]->Coordinates[2]);

							position += abscissa;
							position = placement * position;

							carve::geom::vector<3> nextPosition =
								carve::geom::VECTOR(polyline->Points[h]->Coordinates[0], polyline->Points[h]->Coordinates[1], polyline->Points[h]->Coordinates[2]);

							nextPosition += abscissa;
							nextPosition = placement * nextPosition;

							polylineData->beginPolyline();

							size_t i1 = polylineData->addVertex(position);
							polylineData->addPolylineIndex(i1);
							size_t i2 = polylineData->addVertex(nextPosition);
							polylineData->addPolylineIndex(i2);

							if(next_polyline) {
								if(polyline->Points.size() != next_polyline->Points.size()) {
									return;
								}

								carve::geom::vector<3> position2 =
									carve::geom::VECTOR(next_polyline->Points[j]->Coordinates[0], next_polyline->Points[j]->Coordinates[1], next_polyline->Points[j]->Coordinates[2]);

								position2 += next_abscissa;
								position2 = placement * position2;

								carve::geom::vector<3> nextPosition2 =
									carve::geom::VECTOR(next_polyline->Points[h]->Coordinates[0], next_polyline->Points[h]->Coordinates[1], next_polyline->Points[h]->Coordinates[2]);

								nextPosition2 += next_abscissa;
								nextPosition2 = placement * nextPosition2;

								// set string id and search for existing vertex in polygon
								std::stringstream vID, vID2, vID3, vID4;
								vID << position.x << " " << position.y << " " << position.z;
								vID2 << position2.x << " " << position2.y << " " << position2.z;
								vID3 << nextPosition.x << " " << nextPosition.y << " " << nextPosition.z;
								vID4 << nextPosition2.x << " " << nextPosition2.y << " " << nextPosition2.z;

								uint32_t index1, index2, index3, index4;

								SearchExistingVertex(vID.str(), index1, position, polygonIndices, polygon);
								SearchExistingVertex(vID2.str(), index2, position2, polygonIndices, polygon);
								SearchExistingVertex(vID3.str(), index3, nextPosition, polygonIndices, polygon);
								SearchExistingVertex(vID4.str(), index4, nextPosition2, polygonIndices, polygon);
								

								polygon->addFace(index1, index3, index4);
								polygon->addFace(index4, index2, index1);
							}
						}

						itemData->polylines.push_back(polylineData);
						itemData->open_or_closed_polyhedrons.push_back(polygon);
					}
				}
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcArbitraryProfileDefWithVoids #" << profile_with_voids->getId();
#endif
			}

			// Function 8: Convert IfcParametrizedProfileDefWithPosition
			void convertIfcParameterizedProfileDefWithPosition(const EXPRESSReference<typename IfcEntityTypesT::IfcParameterizedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				std::vector<std::vector<carve::geom::vector<2>>> temp_paths;
				convertIfcParameterizedProfileDef(profileDef, temp_paths);

				// local coordinate system
				if(profileDef->Position) {
					carve::math::Matrix transform = placementConverter->convertIfcPlacement(profileDef->Position.get());

					for(int i = 0; i < temp_paths.size(); ++i) {
						std::vector<carve::geom::vector<2>>& path_loop = temp_paths[i];
						for(int j = 0; j < path_loop.size(); ++j) {
							carve::geom::vector<2>& pt = path_loop.at(j);
							carve::geom::vector<3> pt_3d(carve::geom::VECTOR(pt.x, pt.y, 0));
							pt_3d = transform * pt_3d;
							pt.x = pt_3d.x;
							pt.y = pt_3d.y;
						}
						paths.push_back(path_loop);
					}
				}
				else {
					for(int i = 0; i < temp_paths.size(); ++i) {
						std::vector<carve::geom::vector<2>>& path_loop = temp_paths[i];
						paths.push_back(path_loop);
					}
				}
			}

			// ****************************************************************************************************************************************	//
			//	General Functions																														//			
			//	addArc, addArcWithEndPoint, simplifyPaths, removeDuplicates, mirrorCopyPath, mirrorCopyPathReverse, addAvoidingDuplicates				//
			//	deleteLastPointIfEqualToFirst, getCoordinates																							//
			// ****************************************************************************************************************************************	//

			// Function 1: Add arc
			void addArc(std::vector<carve::geom::vector<2>>& coords, double radius, double startAngle, double openingAngle, double xM, double yM, int numSegments = -1) const
			{
				if(numSegments < 0) {
					numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(radius, abs(openingAngle));
				}

				if(numSegments > 100) {
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)numSegments;
				for(int i = 0; i < numSegments; ++i) {
					coords.push_back(carve::geom::VECTOR((radius * cos(angle) + xM), (radius * sin(angle) + yM)));
					angle += angle_delta;
				}
			}

			// Function 2: Add arc with end point 
			void addArcWithEndPoint(std::vector<carve::geom::vector<2>>& coords, double radius, double startAngle, double openingAngle, double xM, double yM) const
			{
				int numSegments = GeomSettings()->getNumberOfSegmentsForTessellation(radius, abs(openingAngle));

				if(numSegments > 100) {
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)(numSegments - 1);
				for(int i = 0; i < numSegments; ++i) {
					coords.push_back(carve::geom::VECTOR(radius * cos(angle) + xM, radius * sin(angle) + yM));
					angle += angle_delta;
				}
			}
			static void addArcWithEndPoint(std::vector<carve::geom::vector<2>>& coords, double radius, double startAngle, double openingAngle, double xM, double yM, int numSegments)
			{
				if(numSegments < 3) {
					numSegments = 3;
				}

				if(numSegments > 100) {
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)(numSegments - 1);
				for(int i = 0; i < numSegments; ++i) {
					coords.push_back(carve::geom::VECTOR(radius * cos(angle) + xM, radius * sin(angle) + yM));
					angle += angle_delta;
				}
			}
			static void simplifyPath(std::vector<carve::geom::vector<2>>& path)
			{
				if(path.size() < 3) {
					return;
				}

				for(int i = 1; i < path.size() - 1;) {
					carve::geom::vector<2>& previous = path[i - 1];
					carve::geom::vector<2>& current = path[i];
					carve::geom::vector<2>& next = path[i + 1];

					carve::geom::vector<2> segment1 = current - previous;
					segment1.normalize();
					carve::geom::vector<2> segment2 = next - current;
					segment2.normalize();
					double angle = abs(segment1.x * segment2.x + segment1.y * segment2.y);
					if(abs(angle - 1) < 0.00001) {
						// points are colinear, current point can be removed
						path.erase(path.begin() + i);
						continue;
					}
					++i;
				}

				// 1-----0 5-----4      0-----------3         1---0 4---3      0-----------2
				// |             |  ->  |           |         |   _ ---    ->  |   _ ---
				// 2-------------3      1-----------2         2--              1---

				if(path.size() > 4) {
					carve::geom::vector<2>& first = path.front();
					carve::geom::vector<2>& last = path.back();

					if((last - first).length2() < 0.000001) {
						carve::geom::vector<2> first_segment = path[1] - first;
						first_segment.normalize();
						carve::geom::vector<2> last_segment = last - path[path.size() - 2];
						last_segment.normalize();
						double angle = abs(first_segment.x * last_segment.x + first_segment.y * last_segment.y);
						if(abs(angle - 1) < 0.00001) {
							// remove first and last point
							path.erase(path.begin());
							path.pop_back();
						}
					}
				}
			}
			
			// Function 3: Simplify paths
			void simplifyPaths()
			{
				simplifyPaths(paths);
			}
			static void simplifyPaths(std::vector<std::vector<carve::geom::vector<2>>>& paths)
			{
				for(std::vector<std::vector<carve::geom::vector<2>>>::iterator it_paths = paths.begin(); it_paths != paths.end(); ++it_paths) {
					std::vector<carve::geom::vector<2>>& path = (*it_paths);
					if(path.size() < 3) {
						continue;
					}
					simplifyPath(path);
				}
			}

			// Function 4: Remove duplicates
			static void removeDuplicates(std::vector<std::vector<carve::geom::vector<2>>>& paths)
			{
				for(std::vector<std::vector<carve::geom::vector<2>>>::iterator it = paths.begin(); it != paths.end(); ++it) {
					std::vector<carve::geom::vector<2>>& loop = (*it);
					if(loop.size() > 1) {
						std::vector<carve::geom::vector<2>>::iterator it_loop = loop.begin();
						carve::geom::vector<2> previous_point = (*it_loop);
						++it_loop;
						for(; it_loop != loop.end(); ++it_loop) {
							carve::geom::vector<2>& current_point = (*it_loop);
							if(abs(current_point.x - previous_point.x) < 0.00001) {
								if(abs(current_point.y - previous_point.y) < 0.00001) {
									it_loop = loop.erase(it_loop);
									previous_point = (*it_loop);
									continue;
								}
							}
							previous_point = current_point;
						}
					}
				}
			}

			// Function 5: Mirror copy path
			static void mirrorCopyPath(std::vector<carve::geom::vector<2>>& coords, bool mirrorOnYAxis, bool mirrorOnXAxis)
			{
				int points_count = coords.size();
				double x, y;
				for(int i = 0; i < points_count; ++i) {
					carve::geom::vector<2>& p = coords.at(i);
					if(mirrorOnYAxis) {
						x = -p.x;
					}
					else {
						x = p.x;
					}
					if(mirrorOnXAxis) {
						y = -p.y;
					}
					else {
						y = p.y;
					}
					coords.push_back(carve::geom::VECTOR(x, y));
				}
			}

			// Function 6: Mirror copy path reverse
			static void mirrorCopyPathReverse(std::vector<carve::geom::vector<2>>& coords, bool mirrorOnYAxis, bool mirrorOnXAxis)
			{
				int points_count = coords.size();
				double x, y;
				for(int i = points_count - 1; i >= 0; --i) {
					carve::geom::vector<2>& p = coords.at(i);
					if(mirrorOnYAxis) {
						x = -p.x;
					}
					else {
						x = p.x;
					}
					if(mirrorOnXAxis) {
						y = -p.y;
					}
					else {
						y = p.y;
					}

					coords.push_back(carve::geom::VECTOR(x, y));
				}
			}

			// Function 7: Add avoiding duplicates
			static void addAvoidingDuplicates(const std::vector<carve::geom::vector<2>>& polygon, std::vector<std::vector<carve::geom::vector<2>>>& paths)
			{
				if(polygon.size() < 1) {
					return;
				}

				std::vector<carve::geom::vector<2>> polygon_add;
				polygon_add.push_back(polygon.at(0));
				for(int i = 1; i < polygon.size(); ++i) {
					const carve::geom::vector<2>& point = polygon.at(i);
					const carve::geom::vector<2>& point_previous = polygon.at(i - 1);

					// omit duplicate points
					if(abs(point.x - point_previous.x) > 0.00001) {
						polygon_add.push_back(point);
						continue;
					}

					if(abs(point.y - point_previous.y) > 0.00001) {
						polygon_add.push_back(point);
						continue;
					}

					// if( abs(point.z - point_previous.z) > 0.00001 )
					//{
					//	polygon_add.push_back( point );
					//	continue;
					//}
				}
				paths.push_back(polygon_add);
			}

			// Function 8: Delete last point if equal to first
			static void deleteLastPointIfEqualToFirst(std::vector<carve::geom::vector<2>>& coords)
			{
				while(coords.size() > 2) {
					carve::geom::vector<2>& first = coords.front();
					carve::geom::vector<2>& last = coords.back();

					if(abs(first.x - last.x) < 0.00000001) {
						if(abs(first.y - last.y) < 0.00000001) {
							// if( abs(first.z-last.z) < 0.00000001 )
							{
								coords.pop_back();
								continue;
							}
						}
					}
					break;
				}
			}

			// Function 9: Get coordinates
			const std::vector<std::vector<carve::geom::vector<2>>>& getCoordinates()
			{
				return paths;
			}

			/*! \brief adds Coordinates to \c IfcRectangleProfileDef.
			*
			* \param[in] radius The inner or outer corner radius
			* \param[in] x The extent of the rectangle in the direction of the x-axis.
			* \param[in] y The extent of the rectangle in the direction of the y-axis.
			* \param[out] coords A pointer to be filled with the relevant data.
			*/
			void AddRectangleCoordinates (std::vector<carve::geom::vector<2>>& coords,  const double radius, const double x, const double y) const
			{
				// Check radius 
				if (radius != 0) {
					addArc(coords, radius, 0, M_PI_2, x * 0.5 - radius, y * 0.5 - radius);
					addArc(coords, radius, M_PI_2, M_PI_2, -x * 0.5 + radius, y * 0.5 - radius);
					addArc(coords, radius, M_PI, M_PI_2, -x * 0.5 + radius, -y * 0.5 + radius);
					addArc(coords, radius, 3 * M_PI_2, M_PI_2, x * 0.5 - radius, -y * 0.5 + radius);
				}
				// Default
				else {
					coords.push_back(carve::geom::VECTOR(-x * 0.5, -y * 0.5));
					coords.push_back(carve::geom::VECTOR(x * 0.5, -y * 0.5));
					coords.push_back(carve::geom::VECTOR(x * 0.5, y * 0.5));
					coords.push_back(carve::geom::VECTOR(-x * 0.5, y * 0.5));
				}
			}

			/*! \brief adds Coordinates to \c IfcTrapeziumProfileDef.
			*
			* \param[in] xBottom The extent of the bottom line measured along the implicit x-axis.
			* \param[in] xOffset Offset from the beginning of the top line to the bottom line, measured along the implicit x-axis.
			* \param[in] xTop The extent of the top line measured along the implicit x-axis.
			* \param[in] y The extent of the distance between the parallel bottom and top lines measured along the implicit y-axis.
			* \param[out] coords A pointer to be filled with the relevant data.
			*/
			void AddTrapeziumCoordinates(std::vector<carve::geom::vector<2>>& coords, const double xBottom, const double xOffset, const double xTop, const double y)const
			{
				coords.push_back(carve::geom::VECTOR(-xBottom * 0.5, -y * 0.5));
				coords.push_back(carve::geom::VECTOR(xBottom * 0.5, -y * 0.5));
				coords.push_back(carve::geom::VECTOR(-xBottom * 0.5 + xOffset + xTop, y * 0.5));
				coords.push_back(carve::geom::VECTOR(-xBottom * 0.5 + xOffset, y * 0.5));
			}

			/*! \brief adds Coordinates to \c IfcParametrizedProfileDef.
			*
			* \param[in] radius The inner or outer corner radius.
			* \param[in] startAngle The Angle with which filling of the relevant data starts.
			* \param[in] openingAngle The Value how much the angle schould be increased every cycle.
			* \param[in] xM Coordinte of the figure's center of the mass in x-axis.
			* \param[in] yM Coordinte of the figure's center of the mass in y-axis.
			* \param[in] push_back_x Default value of the figure's center of the mass in x-axis.
			* \param[in] push_back_y Default value of the figure's center of the mass in y-axis.
			* \param[out] coords A pointer to be filled with the relevant data.
			*/
			void addArc_or_push_back(std::vector<carve::geom::vector<2>>& coords, double  radius, double startAngle, double openingAngle, double xM, double yM, double push_back_x, double push_back_y, int numSegments = -1) const
			{
				//Check radius
				if (radius != 0.0) {
					addArc(coords, radius, startAngle, openingAngle, xM, yM, numSegments);
				}
				//Default 
				else {
					coords.push_back(carve::geom::VECTOR(push_back_x, push_back_y));
				}
			}

			/*! \brief searhes Existing Vertex and adds to \c IfcArbitraryClosedProfileDef.
			* \param[in] ID id of the string to search for existing vertex. 
			* \param[in] position A position of the Vertex in polygon.
			* \param[in] polygonIndices Indices of the polygon.
			* \param[in] polygon A pointer to the polygon, where to search existing vertex.
			* \param[out] index value to fill in the faceIndices.
			*/
			void SearchExistingVertex(const std::string & ID, const uint32_t & index, carve::geom::vector<3> position, std::map<std::string, uint32_t> & polygonIndices, std::shared_ptr<carve::input::PolyhedronData> polygon) const
			{
				auto itFound = polygonIndices.find(ID);
				if (itFound != polygonIndices.end()) {
					index = itFound->second;
				}
				else {
					index = polygon->addVertex(position);
					polygonIndices[ID] = index;
				}
			}

		protected:

			std::shared_ptr<PlacementConverterT<IfcEntityTypesT>> placementConverter;

			std::vector<std::vector<carve::geom::vector<2>>> paths;
		};
	} // namespace IfcGeometryConverter
	} // namespace Core
} // namespace OpenInfraPlatform

#endif
