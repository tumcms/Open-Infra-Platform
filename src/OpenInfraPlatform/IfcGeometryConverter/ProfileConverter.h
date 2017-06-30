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

#pragma once
#ifndef PROFILECONVERTER_H
#define PROFILECONVERTER_H

#include <memory>

#include "CarveHeaders.h"

#include "PlacementConverter.h"
#include "CurveConverter.h"
#include "GeometrySettings.h"
#include "GeomUtils.h"
#include "GeometryInputData.h"


/**********************************************************************************************/

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>
		class ProfileConverterT
		{

		public:
			ProfileConverterT(std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<IfcUnitConverterT> unitConverter) 
				: 
			m_geomSettings(geomSettings),
			m_unitConverter(unitConverter)
			{
				//std::cout << "Usage of ProfileConverterT" << std::endl;
			}

			~ProfileConverterT()
			{
			}

			void computeProfile(std::shared_ptr<typename IfcEntityTypesT::IfcProfileDef> profileDef)
			{
				// ENTITY IfcProfileDef SUPERTYPE OF(ONEOF(IfcArbitraryClosedProfileDef, IfcArbitraryOpenProfileDef, IfcCompositeProfileDef,
				//IfcDerivedProfileDef, IfcParameterizedProfileDef));
				shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> arbitrary_closed =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(profileDef);
				if (arbitrary_closed)
				{
					convertIfcArbitraryClosedProfileDef(arbitrary_closed, m_paths);
					removeDuplicates(m_paths);
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef> arbitrary_open =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>(profileDef);
				if (arbitrary_open)
				{
					convertIfcArbitraryOpenProfileDef(arbitrary_open, m_paths);
					removeDuplicates(m_paths);
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcCompositeProfileDef> composite = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeProfileDef>(profileDef);
				if (composite)
				{
					convertIfcCompositeProfileDef(composite, m_paths);
					removeDuplicates(m_paths);
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcDerivedProfileDef> derived = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcDerivedProfileDef>(profileDef);
				if (derived)
				{
					convertIfcDerivedProfileDef(derived, m_paths);
					removeDuplicates(m_paths);
					return;
				}

				shared_ptr<typename IfcEntityTypesT::IfcParameterizedProfileDef> parameterized =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcParameterizedProfileDef>(profileDef);
				if (parameterized)
				{
					convertIfcParameterizedProfileDefWithPosition(parameterized, m_paths);
					removeDuplicates(m_paths);
					return;
				}

				//shared_ptr<typename IfcEntityTypesT::IfcNurbsProfile> nurbs = 
					//dynamic_pointer_cast<typename IfcEntityTypesT::IfcNurbsProfile>(profileDef);
				//if( nurbs )
				//{
				//	convertIfcNurbsProfile( nurbs, m_paths );
				//	return;
				//}

				std::stringstream sstr;
				sstr << "ProfileDef not supported: " << profileDef->classname() << " ";
				throw std::runtime_error(sstr.str().c_str());
			}

			void convertIfcArbitraryClosedProfileDef(
				const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				shared_ptr<typename IfcEntityTypesT::IfcCurve> outer_curve = profileDef->m_OuterCurve;
				std::vector<carve::geom::vector<2>> curve_polygon;
				std::vector<carve::geom::vector<2>> segment_start_points;

				CurveConverterT<IfcEntityTypesT, IfcUnitConverterT> c_conv(m_geomSettings, m_unitConverter);
				c_conv.convertIfcCurve2D(outer_curve, curve_polygon, segment_start_points);

				deleteLastPointIfEqualToFirst(curve_polygon);
				addAvoidingDuplicates(curve_polygon, paths);

				// IfcArbitraryProfileDefWithVoids
				shared_ptr<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids> profile_with_voids =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>(profileDef);
				if (profile_with_voids)
				{
					std::vector<shared_ptr<typename IfcEntityTypesT::IfcCurve> > inner_curves = 
						profile_with_voids->m_InnerCurves;
					for (int i = 0; i < inner_curves.size(); ++i)
					{
						shared_ptr<typename IfcEntityTypesT::IfcCurve> inner_ifc_curve = inner_curves[i];
						std::vector<carve::geom::vector<2>> inner_curve_polygon;
						std::vector<carve::geom::vector<2>> segment_start_points;

						c_conv.convertIfcCurve2D(inner_ifc_curve, inner_curve_polygon, segment_start_points);
						deleteLastPointIfEqualToFirst(inner_curve_polygon);
						addAvoidingDuplicates(inner_curve_polygon, paths);
					}
				}
			}

			void convertIfcArbitraryOpenProfileDef(
				const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2> > >& paths) const
			{
				// ENTITY IfcArbitraryOpenProfileDef
				//	SUPERTYPE OF(IfcCenterLineProfileDef)
				//	SUBTYPE OF IfcProfileDef;
				//	Curve	 :	IfcBoundedCurve;

				shared_ptr<typename IfcEntityTypesT::IfcCurve> ifc_curve = profileDef->m_Curve;
				CurveConverterT<IfcEntityTypesT, IfcUnitConverterT> c_converter(m_geomSettings, m_unitConverter);

				//TODO IfcCenterLineProfileDef
				shared_ptr<typename IfcEntityTypesT::IfcCenterLineProfileDef> center_line_profile_def =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcCenterLineProfileDef>(profileDef);
				if (center_line_profile_def)
				{
					if (center_line_profile_def->m_Thickness)
					{
						const double thickness = center_line_profile_def->m_Thickness->m_value * m_unitConverter->getLengthInMeterFactor();
						std::vector<carve::geom::vector<3> > segment_start_points;
						std::vector<carve::geom::vector<3> > basis_curve_points;
						c_converter.convertIfcCurve(ifc_curve, basis_curve_points, segment_start_points);

						int num_base_points = basis_curve_points.size();
						if (num_base_points < 2)
						{
							std::cout << "IfcCenterLineProfileDef: num curve points < 2";
							return;
						}

						carve::math::Matrix matrix_sweep;
						carve::geom::vector<3> local_z(carve::geom::VECTOR(0, 0, 1));
						std::vector<carve::geom::vector<3> > left_points;
						std::vector<carve::geom::vector<3> > right_points;
						carve::geom::vector<3> point_left(carve::geom::VECTOR(0.0, -thickness*0.5, 0.0));
						carve::geom::vector<3> point_right(carve::geom::VECTOR(0.0, thickness*0.5, 0.0));

						for (int ii = 0; ii<num_base_points; ++ii)
						{
							carve::geom::vector<3> vertex_current = basis_curve_points.at(ii);
							carve::geom::vector<3> vertex_next;
							carve::geom::vector<3> vertex_before;
							if (ii == 0)
							{
								// first point
								vertex_next = basis_curve_points.at(ii + 1);
								carve::geom::vector<3> delta_element = vertex_next - vertex_current;
								vertex_before = vertex_current - (delta_element);
							}
							else if (ii == num_base_points - 1)
							{
								// last point
								vertex_before = basis_curve_points.at(ii - 1);
								carve::geom::vector<3> delta_element = vertex_current - vertex_before;
								vertex_next = vertex_before + (delta_element);
							}
							else
							{
								// inner point
								vertex_next = basis_curve_points.at(ii + 1);
								vertex_before = basis_curve_points.at(ii - 1);
							}

							carve::geom::vector<3> bisecting_normal;
							GeomUtils::bisectingPlane(vertex_before, vertex_current, vertex_next, bisecting_normal);

							if (ii == num_base_points - 1)
							{
								bisecting_normal *= -1.0;
							}

							local_z.x = 0;
							local_z.y = 0;
							local_z.z = -1;
							GeomUtils::convertPlane2Matrix(bisecting_normal, vertex_current, local_z, matrix_sweep);

							left_points.push_back(matrix_sweep*point_left);
							right_points.push_back(matrix_sweep*point_right);
						}

						std::reverse(right_points.begin(), right_points.end());
						std::vector<carve::geom::vector<2> > polygon;
						for (int i2 = 0; i2<left_points.size(); ++i2)
						{
							carve::geom::vector<3>& point3d = left_points[i2];
							polygon.push_back(carve::geom::VECTOR(point3d.x, point3d.y));
						}
						for (int i2 = 0; i2<right_points.size(); ++i2)
						{
							carve::geom::vector<3>& point3d = right_points[i2];
							polygon.push_back(carve::geom::VECTOR(point3d.x, point3d.y));
						}
						addAvoidingDuplicates(polygon, paths);
					}
				}
				else
				{
					std::vector<carve::geom::vector<2> > polygon;
					std::vector<carve::geom::vector<2> > segment_start_points;
					c_converter.convertIfcCurve2D(ifc_curve, polygon, segment_start_points);
					addAvoidingDuplicates(polygon, paths);
				}
			}


			void convertIfcCompositeProfileDef(
				const std::shared_ptr<typename IfcEntityTypesT::IfcCompositeProfileDef>& compositeProfileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				std::vector<int> temploop_counts;
				std::vector<int> tempcontour_counts;

				std::vector<shared_ptr<typename IfcEntityTypesT::IfcProfileDef> >& profiles = compositeProfileDef->m_Profiles;
				std::vector<shared_ptr<typename IfcEntityTypesT::IfcProfileDef> >::iterator it;

				for (it = profiles.begin(); it != profiles.end(); ++it)
				{
					shared_ptr<typename IfcEntityTypesT::IfcProfileDef> profileDef = (*it);

					shared_ptr<typename IfcEntityTypesT::IfcParameterizedProfileDef> parameterized =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcParameterizedProfileDef>(profileDef);
					if (parameterized)
					{
						convertIfcParameterizedProfileDefWithPosition(parameterized, paths);
						continue;
					}

					shared_ptr<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef> open =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryOpenProfileDef>(profileDef);
					if (open)
					{
						convertIfcArbitraryOpenProfileDef(open, paths);
						continue;
					}

					shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> closed =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(profileDef);
					if (closed)
					{
						convertIfcArbitraryClosedProfileDef(closed, paths);
						continue;
					}

					shared_ptr<typename IfcEntityTypesT::IfcCompositeProfileDef> composite =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeProfileDef>(profileDef);
					if (composite)
					{
						convertIfcCompositeProfileDef(composite, paths);
						continue;
					}

					shared_ptr<typename IfcEntityTypesT::IfcDerivedProfileDef> derived =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcDerivedProfileDef>(profileDef);
					if (derived)
					{
						convertIfcDerivedProfileDef(derived, paths);
						continue;
					}

					std::stringstream sstr;
					sstr << "ProfileDef not supported: " << compositeProfileDef->classname() << " "; //<< __func__;
					throw std::runtime_error(sstr.str().c_str());
				}
			}

			void convertIfcDerivedProfileDef(
				const std::shared_ptr<typename IfcEntityTypesT::IfcDerivedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT> temp_profiler(m_geomSettings, m_unitConverter);
				temp_profiler.computeProfile(profileDef->m_ParentProfile);
				const std::vector<std::vector<carve::geom::vector<2>>>& parent_paths = temp_profiler.getCoordinates();

				shared_ptr<typename IfcEntityTypesT::IfcCartesianTransformationOperator2D> transf_op_2D = 
					profileDef->m_Operator;

				double length_factor = m_unitConverter->getLengthInMeterFactor();
				carve::math::Matrix transform(carve::math::Matrix::IDENT());
				PlacementConverterT<IfcEntityTypesT>::convertTransformationOperator(transf_op_2D, transform, length_factor);
				for (int i = 0; i<parent_paths.size(); ++i)
				{
					const std::vector<carve::geom::vector<2> >& loop_parent = parent_paths[i];
					std::vector<carve::geom::vector<2> > loop;

					for (int j = 0; j<loop_parent.size(); ++j)
					{
						const carve::geom::vector<2>& pt = loop_parent.at(j);
						carve::geom::vector<3> pt3d(carve::geom::VECTOR(pt.x, pt.y, 0));
						pt3d = transform*pt3d;
						loop.push_back(carve::geom::VECTOR(pt3d.x, pt3d.y));
					}
					paths.push_back(loop);
				}
			}

			void convertIfcParameterizedProfileDef(
				const std::shared_ptr<typename IfcEntityTypesT::IfcParameterizedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				//IfcParameterizedProfileDef ABSTRACT SUPERTYPE OF (ONEOF
				//	(IfcCShapeProfileDef, IfcCircleProfileDef, IfcEllipseProfileDef, IfcIShapeProfileDef, IfcLShapeProfileDef,
				//	IfcRectangleProfileDef, IfcTShapeProfileDef, IfcTrapeziumProfileDef, IfcUShapeProfileDef, IfcZShapeProfileDef))

				double length_factor = m_unitConverter->getLengthInMeterFactor();
				double angle_factor = m_unitConverter->getAngleInRadianFactor();
				std::vector<carve::geom::vector<2> > outer_loop;

				shared_ptr<typename IfcEntityTypesT::IfcRectangleProfileDef> rectangle_profile =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcRectangleProfileDef>(profileDef);
				if (rectangle_profile)
				{
					if (rectangle_profile->m_XDim && rectangle_profile->m_YDim)
					{
						double x = rectangle_profile->m_XDim->m_value*length_factor;
						double y = rectangle_profile->m_YDim->m_value*length_factor;

						shared_ptr<typename IfcEntityTypesT::IfcRectangleHollowProfileDef> hollow =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcRectangleHollowProfileDef>(rectangle_profile);
						if (hollow)
						{
							if (hollow->m_WallThickness)
							{
								double t = hollow->m_WallThickness->m_value*length_factor;
								double r1 = 0;
								if (hollow->m_OuterFilletRadius)
								{
									r1 = hollow->m_InnerFilletRadius->m_value*length_factor;
								}

								double r2 = 0;
								if (hollow->m_InnerFilletRadius)
								{
									r2 = hollow->m_InnerFilletRadius->m_value*length_factor;
								}

								// Outer
								if (r1 != 0)
								{
									addArc(outer_loop, r1, 0, M_PI_2, x*0.5 - r1, y*0.5 - r1);
									addArc(outer_loop, r1, M_PI_2, M_PI_2, -x*0.5 + r1, y*0.5 - r1);
									addArc(outer_loop, r1, M_PI, M_PI_2, -x*0.5 + r1, -y*0.5 + r1);
									addArc(outer_loop, r1, 3 * M_PI_2, M_PI_2, x*0.5 - r1, -y*0.5 + r1);
								}
								else
								{
									outer_loop.push_back(carve::geom::VECTOR(-x*0.5, -y*0.5));
									outer_loop.push_back(carve::geom::VECTOR(x*0.5, -y*0.5));
									outer_loop.push_back(carve::geom::VECTOR(x*0.5, y*0.5));
									outer_loop.push_back(carve::geom::VECTOR(-x*0.5, y*0.5));
								}

								// Inner
								std::vector<carve::geom::vector<2> > inner_loop;
								x -= 2 * t;
								y -= 2 * t;
								if (r2 != 0)
								{
									addArc(inner_loop, r2, 0, M_PI_2, x*0.5 - r2, y*0.5 - r2);
									addArc(inner_loop, r2, M_PI_2, M_PI_2, -x*0.5 + r2, y*0.5 - r2);
									addArc(inner_loop, r2, M_PI, M_PI_2, -x*0.5 + r2, -y*0.5 + r2);
									addArc(inner_loop, r2, 3 * M_PI_2, M_PI_2, x*0.5 - r2, -y*0.5 + r2);
								}
								else
								{
									inner_loop.push_back(carve::geom::VECTOR(-x*0.5, -y*0.5));
									inner_loop.push_back(carve::geom::VECTOR(x*0.5, -y*0.5));
									inner_loop.push_back(carve::geom::VECTOR(x*0.5, y*0.5));
									inner_loop.push_back(carve::geom::VECTOR(-x*0.5, y*0.5));
								}
								paths.push_back(outer_loop);
								paths.push_back(inner_loop);
							}
							return;
						}

						// RoundedRectangle
						shared_ptr<typename IfcEntityTypesT::IfcRoundedRectangleProfileDef> rounded_rectangle =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcRoundedRectangleProfileDef>(rectangle_profile);
						if (rounded_rectangle)
						{

							if (rounded_rectangle->m_RoundingRadius)
							{
								double rr = rounded_rectangle->m_RoundingRadius->m_value*length_factor;
								addArc(outer_loop, rr, 0, M_PI_2, x*0.5 - rr, y*0.5 - rr);
								addArc(outer_loop, rr, M_PI_2, M_PI_2, -x*0.5 + rr, y*0.5 - rr);
								addArc(outer_loop, rr, M_PI, M_PI_2, -x*0.5 + rr, -y*0.5 + rr);
								addArc(outer_loop, rr, 3 * M_PI_2, M_PI_2, x*0.5 - rr, -y*0.5 + rr);
								paths.push_back(outer_loop);
							}
							return;
						}


						// else it's a standard rectangle
						outer_loop.push_back(carve::geom::VECTOR(-x*0.5, -y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(x*0.5, -y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(x*0.5, y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(-x*0.5, y*0.5));
						paths.push_back(outer_loop);
						return;
					}
				}

				// Trapezium
				shared_ptr<typename IfcEntityTypesT::IfcTrapeziumProfileDef> trapezium =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcTrapeziumProfileDef>(profileDef);
				if (trapezium)
				{
					if (trapezium->m_BottomXDim && trapezium->m_TopXDim && trapezium->m_TopXOffset && trapezium->m_YDim)
					{
						double xBottom = trapezium->m_BottomXDim->m_value*length_factor;
						double xTop = trapezium->m_TopXDim->m_value*length_factor;
						double xOffset = trapezium->m_TopXOffset->m_value*length_factor;
						double y = trapezium->m_YDim->m_value*length_factor;
						outer_loop.push_back(carve::geom::VECTOR(-xBottom*0.5, -y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(xBottom*0.5, -y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(-xBottom*0.5 + xOffset + xTop, y*0.5));
						outer_loop.push_back(carve::geom::VECTOR(-xBottom*0.5 + xOffset, y*0.5));
						paths.push_back(outer_loop);
					}
					return;
				}

				// Circle
				shared_ptr<typename IfcEntityTypesT::IfcCircleProfileDef> circle_profile_def =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircleProfileDef>(profileDef);
				if (circle_profile_def)
				{
					double radius = circle_profile_def->m_Radius->m_value*length_factor;
					if (radius < 0.000001)
					{
						return;
					}
					int num_segments = m_geomSettings->m_num_vertices_per_circle; // TODO: adapt to model size and complexity
					double angle = 0;
					for (int i = 0; i<num_segments; ++i)
					{
						outer_loop.push_back(carve::geom::VECTOR((radius * cos(angle)), (radius * sin(angle))));
						angle += 2.0*M_PI / double(num_segments);
					}
					paths.push_back(outer_loop);

					// CircleHollow
					std::vector<carve::geom::vector<2> > inner_loop;
					shared_ptr<typename IfcEntityTypesT::IfcCircleHollowProfileDef> hollow =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircleHollowProfileDef>(profileDef);
					if (hollow)
					{
						angle = 0;
						radius -= hollow->m_WallThickness->m_value*length_factor;

						int num_segments2 = m_geomSettings->m_num_vertices_per_circle; // TODO: adapt to model size and complexity
						for (int i = 0; i<num_segments2; ++i)
						{
							inner_loop.push_back(carve::geom::VECTOR((radius * cos(angle)), (radius * sin(angle))));
							angle += 2.0*M_PI / double(num_segments2);
						}
						paths.push_back(inner_loop);
					}
					return;
				}

				// Ellipse
				shared_ptr<typename IfcEntityTypesT::IfcEllipseProfileDef> ellipse_profile_def =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcEllipseProfileDef>(profileDef);
				if (ellipse_profile_def)
				{
					if (ellipse_profile_def->m_SemiAxis1)
					{
						if (ellipse_profile_def->m_SemiAxis2)
						{
							double xRadius = ellipse_profile_def->m_SemiAxis1->m_value*length_factor;
							double yRadius = ellipse_profile_def->m_SemiAxis2->m_value*length_factor;
							double radiusMax = std::max(xRadius, yRadius);
							int num_segments = m_geomSettings->m_num_vertices_per_circle; // TODO: adapt to model size and complexity
							double angle = 0;
							for (int i = 0; i < num_segments; ++i)
							{
								outer_loop.push_back(carve::geom::VECTOR((xRadius * cos(angle)), (yRadius * sin(angle))));
								angle += 2.0*M_PI / double(num_segments);
							}
							paths.push_back(outer_loop);
						}
					}
					return;
				}

				// I
				shared_ptr<typename IfcEntityTypesT::IfcIShapeProfileDef> i_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcIShapeProfileDef>(profileDef);
				if (i_shape)
				{
					if (i_shape->m_OverallDepth && i_shape->m_OverallWidth && i_shape->m_WebThickness && i_shape->m_FlangeThickness)
					{
						double h = i_shape->m_OverallDepth->m_value*length_factor;
						double b = i_shape->m_OverallWidth->m_value*length_factor;
						double tw = i_shape->m_WebThickness->m_value*length_factor;
						double tf = i_shape->m_FlangeThickness->m_value*length_factor;
						double r = 0;
						if (i_shape->m_FilletRadius)
						{
							r = i_shape->m_FilletRadius->m_value*length_factor;
						}

						outer_loop.push_back(carve::geom::VECTOR(b*0.5, -h*0.5));
						outer_loop.push_back(carve::geom::VECTOR(b*0.5, (-h*0.5 + tf)));

						if (r != 0)
						{
							addArc(outer_loop, r, 3 * M_PI_2, -M_PI_2, tw*0.5 + r, -h*0.5 + tf + r);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR(tw*0.5, (-h*0.5 + tf)));
						}

						shared_ptr<typename IfcEntityTypesT::IfcAsymmetricIShapeProfileDef> asym_I_profile =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcAsymmetricIShapeProfileDef>(i_shape);
						if (asym_I_profile)
						{
							if (asym_I_profile->m_TopFlangeWidth)
							{
								double bTop = asym_I_profile->m_TopFlangeWidth->m_value*length_factor;
								double tfTop = tf;

								if (asym_I_profile->m_TopFlangeThickness)
								{
									tfTop = asym_I_profile->m_TopFlangeThickness->m_value*length_factor;
								}
								double rTop = r;
								if (asym_I_profile->m_TopFlangeFilletRadius)
								{
									rTop = asym_I_profile->m_TopFlangeFilletRadius->m_value*length_factor;
								}

								if (rTop != 0)
								{
									addArc(outer_loop, rTop, M_PI, -M_PI_2, tw*0.5 + rTop, h*0.5 - tfTop - rTop);
								}
								else
								{
									outer_loop.push_back(carve::geom::VECTOR(tw*0.5, (h*0.5 - tfTop)));
								}
								outer_loop.push_back(carve::geom::VECTOR(bTop*0.5, (h*0.5 - tfTop)));
								outer_loop.push_back(carve::geom::VECTOR(bTop*0.5, h*0.5));
							}
						}
						else
						{
							// symmetric: mirror horizontally along x-Axis
							mirrorCopyPathReverse(outer_loop, false, true);
						}

						// mirror vertically along y-axis
						mirrorCopyPathReverse(outer_loop, true, false);
						paths.push_back(outer_loop);
					}
					return;
				}

				// L
				shared_ptr<typename IfcEntityTypesT::IfcLShapeProfileDef> l_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcLShapeProfileDef>(profileDef);
				if (l_shape)
				{
					if (l_shape->m_Depth && l_shape->m_Thickness)
					{
						double h = l_shape->m_Depth->m_value*length_factor;
						double b = h;

						if (l_shape->m_Width)
						{
							b = l_shape->m_Width->m_value*length_factor;
						}

						double t = l_shape->m_Thickness->m_value*length_factor;

						double r1 = 0;
						if (l_shape->m_FilletRadius)
						{
							r1 = l_shape->m_FilletRadius->m_value*length_factor;
						}

						double r2 = 0;
						if (l_shape->m_EdgeRadius)
						{
							r2 = l_shape->m_EdgeRadius->m_value*length_factor;
						}

						double ls = 0;
						if (l_shape->m_LegSlope)
						{
							ls = l_shape->m_LegSlope->m_value*angle_factor;
						}

						outer_loop.push_back(carve::geom::VECTOR(-b*0.5, -h*0.5));
						outer_loop.push_back(carve::geom::VECTOR(b*0.5, -h*0.5));

						if (r2 != 0)
						{
							addArc(outer_loop, r2, 0, M_PI_2 - ls, b*0.5 - r2, -h*0.5 + t - r2);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR(b*0.5, (-h*0.5 + t)));
						}

						double s = sin(ls);
						double c = cos(ls);
						double z1 = (-s*((c - s)*(r1 + r2 + t) - c*b + s*h)) / (2 * c*c - 1);
						double z2 = (-s*((c - s)*(r1 + r2 + t) - c*h + s*b)) / (2 * c*c - 1);
						if (r1 != 0)
						{
							addArc(outer_loop, r1, 3 * M_PI_2 - ls, -M_PI_2 + 2 * ls, -b*0.5 + t + z2 + r1, -h*0.5 + t + z1 + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((-b*0.5 + t + z2), (-h*0.5 + t + z1)));
						}

						if (r2 != 0)
						{
							addArc(outer_loop, r2, ls, M_PI_2 - ls, -b*0.5 + t - r2, h*0.5 - r2);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((-b*0.5 + t), h*0.5));
						}

						outer_loop.push_back(carve::geom::VECTOR(-b*0.5, h*0.5));
						paths.push_back(outer_loop);
					}
					return;
				}

				// U
				shared_ptr<typename IfcEntityTypesT::IfcUShapeProfileDef> u_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcUShapeProfileDef>(profileDef);
				if (u_shape)
				{
					if (u_shape->m_Depth && u_shape->m_FlangeWidth && u_shape->m_WebThickness && u_shape->m_FlangeThickness)
					{
						double h = u_shape->m_Depth->m_value*length_factor;
						double b = u_shape->m_FlangeWidth->m_value*length_factor;
						double tw = u_shape->m_WebThickness->m_value*length_factor;
						double tf = u_shape->m_FlangeThickness->m_value*length_factor;
						double r1 = 0;
						if (u_shape->m_FilletRadius)
						{
							r1 = u_shape->m_FilletRadius->m_value*length_factor;
						}
						double r2 = 0;
						if (u_shape->m_EdgeRadius)
						{
							r2 = u_shape->m_EdgeRadius->m_value*length_factor;
						}
						double fs = 0;
						if (u_shape->m_FlangeSlope)
						{
							fs = u_shape->m_FlangeSlope->m_value*angle_factor;
						}

						outer_loop.push_back(carve::geom::VECTOR(-b*0.5, -h*0.5));
						outer_loop.push_back(carve::geom::VECTOR(b*0.5, -h*0.5));

						double z = tan(fs)*(b*0.5 - r2);
						if (r2 != 0)
						{
							addArc(outer_loop, r2, 0, M_PI_2 - fs, b*0.5 - r2, -h*0.5 + tf - z - r2);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR(b*0.5, (-h*0.5 + tf - z)));
						}

						z = tan(fs)*(b*0.5 - tw - r1);
						if (r1 != 0)
						{
							addArc(outer_loop, r1, 3 * M_PI_2 - fs, -M_PI_2 + fs, -b*0.5 + tw + r1, -h*0.5 + tf + z + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((-b*0.5 + tw), (-h*0.5 + tf + z)));
						}

						// mirror horizontally along x-Axis
						mirrorCopyPathReverse(outer_loop, false, true);
						paths.push_back(outer_loop);
					}
					return;
				}

				// C
				shared_ptr<typename IfcEntityTypesT::IfcCShapeProfileDef> c_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcCShapeProfileDef>(profileDef);
				if (c_shape)
				{
					if (c_shape->m_Depth && c_shape->m_Width && c_shape->m_Girth && c_shape->m_WallThickness)
					{
						double h = c_shape->m_Depth->m_value*length_factor;
						double b = c_shape->m_Width->m_value*length_factor;
						double g = c_shape->m_Girth->m_value*length_factor;
						double t = c_shape->m_WallThickness->m_value*length_factor;
						double r1 = 0;
						if (c_shape->m_InternalFilletRadius)
						{
							r1 = c_shape->m_InternalFilletRadius->m_value*length_factor;
						}

						if (r1 != 0)
						{
							addArc(outer_loop, r1 + t, M_PI, M_PI_2, -b*0.5 + t + r1, -h*0.5 + t + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR(-b*0.5, -h*0.5));
						}

						if (r1 != 0)
						{
							addArc(outer_loop, r1 + t, 3 * M_PI_2, M_PI_2, b*0.5 - t - r1, -h*0.5 + t + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR(b*0.5, -h*0.5));
						}

						outer_loop.push_back(carve::geom::VECTOR(b*0.5, (-h*0.5 + g)));
						outer_loop.push_back(carve::geom::VECTOR((b*0.5 - t), (-h*0.5 + g)));

						if (r1 != 0)
						{
							addArc(outer_loop, r1, 0, -M_PI_2, b*0.5 - t - r1, -h*0.5 + t + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((b*0.5 - t), (-h*0.5 + t)));
						}

						if (r1 != 0)
						{
							addArc(outer_loop, r1, 3 * M_PI_2, -M_PI_2, -b*0.5 + t + r1, -h*0.5 + t + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((-b*0.5 + t), (-h*0.5 + t)));
						}
						// mirror horizontally along x-Axis
						mirrorCopyPathReverse(outer_loop, false, true);
						paths.push_back(outer_loop);
					}
					return;
				}


				//Z-Shape-Profile
				shared_ptr<typename IfcEntityTypesT::IfcZShapeProfileDef> z_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcZShapeProfileDef>(profileDef);
				if (z_shape)
				{
					if (z_shape->m_Depth && z_shape->m_FlangeWidth && z_shape->m_WebThickness && z_shape->m_FlangeThickness)
					{
						double h = z_shape->m_Depth->m_value*length_factor;
						double b = z_shape->m_FlangeWidth->m_value*length_factor;
						double tw = z_shape->m_WebThickness->m_value*length_factor;
						double tf = z_shape->m_FlangeThickness->m_value*length_factor;
						double r1 = 0;
						if (z_shape->m_FilletRadius)
						{
							r1 = z_shape->m_FilletRadius->m_value*length_factor;
						}

						double r2 = 0;
						if (z_shape->m_EdgeRadius)
						{
							r2 = z_shape->m_EdgeRadius->m_value*length_factor;
						}

						outer_loop.push_back(carve::geom::VECTOR((-tw*0.5), -h*0.5));
						outer_loop.push_back(carve::geom::VECTOR((b - tw*0.5), -h*0.5));

						if (r2 != 0)
						{
							addArc(outer_loop, r2, 0, M_PI_2, b - tw*0.5 - r2, -h*0.5 + tf - r2);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((b - tw*0.5), (-h*0.5 + tf)));
						}

						if (r1 != 0)
						{
							addArc(outer_loop, r1, 3 * M_PI_2, -M_PI_2, tw*0.5 + r1, -h*0.5 + tf + r1);
						}
						else
						{
							outer_loop.push_back(carve::geom::VECTOR((tw*0.5), (-h*0.5 + tf)));
						}

						// mirror horizontally and vertically
						mirrorCopyPath(outer_loop, true, true);
						paths.push_back(outer_loop);
					}
					return;
				}

				//T-Shape-Profile
				shared_ptr<typename IfcEntityTypesT::IfcTShapeProfileDef> t_shape =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcTShapeProfileDef>(profileDef);
				if (t_shape)
				{
					const double h = t_shape->m_Depth->m_value*length_factor;
					const double b = t_shape->m_FlangeWidth->m_value*length_factor;
					const double tw = t_shape->m_WebThickness->m_value*length_factor*0.5;
					const double tf = t_shape->m_FlangeThickness->m_value*length_factor;

					double r1 = 0;
					if (t_shape->m_FilletRadius)
					{
						r1 = t_shape->m_FilletRadius->m_value*length_factor;
					}

					double r2 = 0;
					if (t_shape->m_FlangeEdgeRadius)
					{
						r2 = t_shape->m_FlangeEdgeRadius->m_value*length_factor;
					}

					double r3 = 0;
					if (t_shape->m_WebEdgeRadius)
					{
						r3 = t_shape->m_WebEdgeRadius->m_value*length_factor;
					}
					double fs = 0;

					if (t_shape->m_FlangeSlope)
					{
						fs = t_shape->m_FlangeSlope->m_value*angle_factor;
					}

					double ws = 0;
					if (t_shape->m_WebSlope)
					{
						ws = t_shape->m_WebSlope->m_value*angle_factor;
					}

					outer_loop.push_back(carve::geom::VECTOR(-b*0.5, h*0.5));

					double zf = tan(fs)*(b*0.25 - r2);
					double zw = tan(ws)*(h*0.5 - r3);
					if (r2 != 0)
					{
						addArc(outer_loop, r2, M_PI, M_PI_2 - fs, -b*0.5 + r2, h*0.5 - tf + zf + r2);
					}
					else
					{
						outer_loop.push_back(carve::geom::VECTOR(-b*0.5, (h*0.5 - tf + zf)));
					}

					double cf = cos(fs);
					double sf = sin(fs);
					double cw = cos(ws);
					double sw = sin(ws);
					double z1 = (sf*((b - 2 * (r1 + r2 + tw - zw))*cw - 2 * (h - r3 - r1 - tf + zf)*sw)) / (2 * (cf*cw - sf*sw));
					double z2 = tan(ws)*(h - r3 - r1 - z1 - tf + zf);
					if (r1 != 0)
					{
						addArc(outer_loop, r1, M_PI_2 - fs, -M_PI_2 + fs + ws, -tw + zw - z2 - r1, h*0.5 - tf + zf - z1 - r1);
					}
					else
					{
						outer_loop.push_back(carve::geom::VECTOR((-tw + zw - z2), (h*0.5 - tf + zf - z1)));
					}

					if (r3 != 0)
					{
						addArc(outer_loop, r3, M_PI + ws, M_PI_2 - ws, -tw + zw + r3, -h*0.5 + r3);
					}
					else
					{
						outer_loop.push_back(carve::geom::VECTOR((-tw + zw), -h*0.5));
					}

					// mirror vertically along y-Axis
					mirrorCopyPathReverse(outer_loop, true, false);
					paths.push_back(outer_loop);
					return;
				}

				//not supported ProfileDef
				std::stringstream sstr;
				sstr << "IfcProfileDef not supported: " << profileDef->classname() << " #" << profileDef->getId();// << __func__;
				throw std::runtime_error(sstr.str().c_str());
			}

			/*
			void ProfileConverter::convertIfcNurbsProfile(const shared_ptr<IfcNurbsProfile>& nurbs_profile, 
			std::vector<std::vector<carve::geom::vector<3>>>& paths )
			{
				std::stringstream err;
				shared_ptr<IfcRationalBSplineSurfaceWithKnots> surface = dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(nurbs_profile->m_Surface);
				if( !surface )
				{
				return;
				}
				std::vector<carve::geom::vector<3> > loop;
				double length_factor = polygon->getLengthInMeterFactor();
				std::vector<std::vector<shared_ptr<IfcCartesianPoint> > >& vec_control_points = surface->m_ControlPointsList;
				std::vector<std::vector<double> >& vec_weights = surface->m_WeightsData;

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
				std::vector<shared_ptr<IfcCartesianPoint> >& vec_control_points_eta0 = vec_control_points[0];
				std::vector<shared_ptr<IfcCartesianPoint> >::iterator it_xi0 = vec_control_points_eta0.begin();
				for( ; it_xi0 != vec_control_points_eta0.end(); ++it_xi0 )
				{
				shared_ptr<IfcCartesianPoint>& ifc_point = (*it_xi0);
				carve::geom::vector<3>  point;
				converter.convertIfcCartesianPoint( ifc_point, point );
				loop.push_back(point);
				}

				// eta = 1
				std::vector<std::vector<shared_ptr<IfcCartesianPoint> > >::iterator it_eta1 = vec_control_points.begin();
				std::vector<std::vector<shared_ptr<IfcCartesianPoint> > >::iterator it_eta1_last = vec_control_points.end();
				++it_eta1;
				--it_eta1_last;
				for( ; it_eta1 != it_eta1_last; ++it_eta1 )
				{
				std::vector<shared_ptr<IfcCartesianPoint> >& vec_eta = *it_eta1;
				shared_ptr<IfcCartesianPoint>& ifc_point = vec_eta.back();
				carve::geom::vector<3>  point;
				converter.convertIfcCartesianPoint( ifc_point, point );
				loop.push_back(point);
				}

				// xi = 1
				std::vector<shared_ptr<IfcCartesianPoint> >& vec_control_points_eta1 = vec_control_points[vec_control_points.size()-1];
				std::vector<shared_ptr<IfcCartesianPoint> >::reverse_iterator it_control_points_reverse = vec_control_points_eta1.rbegin();
				for( ; it_control_points_reverse != vec_control_points_eta1.rend(); ++it_control_points_reverse )
				{
				shared_ptr<IfcCartesianPoint>& ifc_point = (*it_control_points_reverse);
				carve::geom::vector<3>  point;
				converter.convertIfcCartesianPoint( ifc_point, point );
				loop.push_back(point);
				}

				// eta = 0
				std::vector<std::vector<shared_ptr<IfcCartesianPoint> > >::reverse_iterator it_eta0 = vec_control_points.rbegin();
				std::vector<std::vector<shared_ptr<IfcCartesianPoint> > >::reverse_iterator it_eta0_last = vec_control_points.rend();
				++it_eta0;
				--it_eta0_last;
				for( ; it_eta0 != it_eta0_last; ++it_eta0 )
				{
				std::vector<shared_ptr<IfcCartesianPoint> >& vec_eta = *it_eta1;
				shared_ptr<IfcCartesianPoint>& ifc_point = vec_eta.back();
				carve::geom::vector<3>  point;
				converter.convertIfcCartesianPoint( ifc_point, point );
				loop.push_back(point);
				}
				paths.push_back(loop);
			}
			*/

			void convertIfcArbitraryProfileWithVoids(const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>& profile_with_voids,
				const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryProfileDefWithVoids>& next_profile_with_voids,
				const carve::math::Matrix& placement,
				std::shared_ptr<ItemData> itemData,
				const carve::geom::vector<3>& abscissa, const carve::geom::vector<3>& next_abscissa)
			{
				const double lengthFactor = m_unitConverter->getLengthInMeterFactor();

				std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> outer_curve = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(profile_with_voids);
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCurve> > inner_curves = profile_with_voids->m_InnerCurves;

				std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef> next_outer_curve = dynamic_pointer_cast<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>(next_profile_with_voids);
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCurve> > next_inner_curves = next_profile_with_voids->m_InnerCurves;

				// if there is any outer curve (as closed profile) convert it to geometry first
				if (outer_curve) 
				{
					convertIfcArbitraryClosedProfileDef(outer_curve, next_outer_curve, placement, itemData, abscissa, next_abscissa);
				}

				// then convert all inner curve profiles
				for (int i = 0; i < inner_curves.size(); ++i)
				{
					//this inner curve
					std::shared_ptr<typename IfcEntityTypesT::IfcCurve> inner_curve = inner_curves[i];
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> polyline = 
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(inner_curve);

					//next inner curve
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> next_polyline;
					if (next_inner_curves.size() == inner_curves.size())
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> next_inner_curve = next_inner_curves[i];
						next_polyline = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(next_inner_curve);
					}

					if (polyline)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> bounded_curve = 
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(polyline);

						// describe 2D-polyline geometry
						std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());

						// describe 3D face geometry (gather vertex indices to avoid duplicates)
						std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
						std::map<std::string, uint32_t> polygonIndices;

						for (int j = 0; j < polyline->m_Points.size(); ++j)
						{
							int h = (j + 1) % polyline->m_Points.size();

							carve::geom::vector<3> position =
								carve::geom::VECTOR(polyline->m_Points[j]->m_Coordinates[0]->m_value * lengthFactor,
								polyline->m_Points[j]->m_Coordinates[1]->m_value * lengthFactor,
								polyline->m_Points[j]->m_Coordinates[2]->m_value * lengthFactor);

							position += abscissa;
							position = placement * position;

							carve::geom::vector<3> nextPosition =
								carve::geom::VECTOR(polyline->m_Points[h]->m_Coordinates[0]->m_value * lengthFactor,
								polyline->m_Points[h]->m_Coordinates[1]->m_value * lengthFactor,
								polyline->m_Points[h]->m_Coordinates[2]->m_value * lengthFactor);

							nextPosition += abscissa;
							nextPosition = placement * nextPosition;

							polylineData->beginPolyline();

							size_t i1 = polylineData->addVertex(position);
							polylineData->addPolylineIndex(i1);
							size_t i2 = polylineData->addVertex(nextPosition);
							polylineData->addPolylineIndex(i2);

							if (next_polyline)
							{
								if (polyline->m_Points.size() != next_polyline->m_Points.size()) { return; }

								carve::geom::vector<3> position2 =
									carve::geom::VECTOR(next_polyline->m_Points[j]->m_Coordinates[0]->m_value * lengthFactor,
									next_polyline->m_Points[j]->m_Coordinates[1]->m_value * lengthFactor,
									next_polyline->m_Points[j]->m_Coordinates[2]->m_value * lengthFactor);

								position2 += next_abscissa;
								position2 = placement * position2;

								carve::geom::vector<3> nextPosition2 =
									carve::geom::VECTOR(next_polyline->m_Points[h]->m_Coordinates[0]->m_value * lengthFactor,
									next_polyline->m_Points[h]->m_Coordinates[1]->m_value * lengthFactor,
									next_polyline->m_Points[h]->m_Coordinates[2]->m_value * lengthFactor);

								nextPosition2 += next_abscissa;
								nextPosition2 = placement * nextPosition2;

								// set string id and search for existing vertex in polygon
								std::stringstream vID, vID2, vID3, vID4;
								vID << position.x << " " << position.y << " " << position.z;
								vID2 << position2.x << " " << position2.y << " " << position2.z;
								vID3 << nextPosition.x << " " << nextPosition.y << " " << nextPosition.z;
								vID4 << nextPosition2.x << " " << nextPosition2.y << " " << nextPosition2.z;

								uint32_t index1, index2, index3, index4;

								auto itFound = polygonIndices.find(vID.str());
								if (itFound != polygonIndices.end()) { index1 = itFound->second; }
								else { index1 = polygon->addVertex(position); polygonIndices[vID.str()] = index1; }

								itFound = polygonIndices.find(vID2.str());
								if (itFound != polygonIndices.end()) { index2 = itFound->second; }
								else { index2 = polygon->addVertex(position2); polygonIndices[vID2.str()] = index2; }

								itFound = polygonIndices.find(vID3.str());
								if (itFound != polygonIndices.end()) { index3 = itFound->second; }
								else { index3 = polygon->addVertex(nextPosition); polygonIndices[vID3.str()] = index3; }

								itFound = polygonIndices.find(vID4.str());
								if (itFound != polygonIndices.end()) { index4 = itFound->second; }
								else { index4 = polygon->addVertex(nextPosition2); polygonIndices[vID4.str()] = index4; }

								polygon->addFace(index1, index3, index4);
								polygon->addFace(index4, index2, index1);
							}
						}

						itemData->polylines.push_back(polylineData);
						itemData->open_or_closed_polyhedrons.push_back(polygon);
					}

				}
			}

			void convertIfcArbitraryClosedProfileDef(const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& profile,
				const std::shared_ptr<typename IfcEntityTypesT::IfcArbitraryClosedProfileDef>& next_profile,
				const carve::math::Matrix& placement,
				std::shared_ptr<ItemData> itemData,
				const carve::geom::vector<3>& abscissa, const carve::geom::vector<3>& next_abscissa) const
			{
				const double lengthFactor = m_unitConverter->getLengthInMeterFactor();

				std::shared_ptr<typename IfcEntityTypesT::IfcCurve> outer_curve = profile->m_OuterCurve;
				std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> polyline = 
					std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(outer_curve);

				if (polyline)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcCurve> next_outer_curve = next_profile->m_OuterCurve;
					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> next_polyline =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(next_outer_curve);

					// describe 2D-polyline geometry
					std::shared_ptr<carve::input::PolylineSetData> polylineData(new carve::input::PolylineSetData());

					// describe 3D face geometry (gather vertex indices to avoid duplicates)
					std::shared_ptr<carve::input::PolyhedronData> polygon(new carve::input::PolyhedronData());
					std::map<std::string, uint32_t> polygonIndices;

					for (int i = 0; i < polyline->m_Points.size(); ++i)
					{
						int j = (i + 1) % polyline->m_Points.size();

						carve::geom::vector<3> position =
							carve::geom::VECTOR(polyline->m_Points[i]->m_Coordinates[0]->m_value * lengthFactor,
							polyline->m_Points[i]->m_Coordinates[1]->m_value * lengthFactor,
							polyline->m_Points[i]->m_Coordinates[2]->m_value * lengthFactor);

						position += abscissa;
						position = placement * position;

						carve::geom::vector<3> nextPosition =
							carve::geom::VECTOR(polyline->m_Points[j]->m_Coordinates[0]->m_value * lengthFactor,
							polyline->m_Points[j]->m_Coordinates[1]->m_value * lengthFactor,
							polyline->m_Points[j]->m_Coordinates[2]->m_value * lengthFactor);

						nextPosition += abscissa;
						nextPosition = placement * nextPosition;

						polylineData->beginPolyline();

						size_t i1 = polylineData->addVertex(position);
						polylineData->addPolylineIndex(i1);
						size_t i2 = polylineData->addVertex(nextPosition);
						polylineData->addPolylineIndex(i2);

						if (next_polyline)
						{
							if (polyline->m_Points.size() != next_polyline->m_Points.size()) { return; }

							carve::geom::vector<3> position2 =
								carve::geom::VECTOR(next_polyline->m_Points[i]->m_Coordinates[0]->m_value * lengthFactor,
								next_polyline->m_Points[i]->m_Coordinates[1]->m_value * lengthFactor,
								next_polyline->m_Points[i]->m_Coordinates[2]->m_value * lengthFactor);

							position2 += next_abscissa;
							position2 = placement * position2;

							carve::geom::vector<3> nextPosition2 =
								carve::geom::VECTOR(next_polyline->m_Points[j]->m_Coordinates[0]->m_value * lengthFactor,
								next_polyline->m_Points[j]->m_Coordinates[1]->m_value * lengthFactor,
								next_polyline->m_Points[j]->m_Coordinates[2]->m_value * lengthFactor);

							nextPosition2 += next_abscissa;
							nextPosition2 = placement * nextPosition2;

							// set string id and search for existing vertex in polygon
							std::stringstream vID, vID2, vID3, vID4;
							vID << position.x << " " << position.y << " " << position.z;
							vID2 << position2.x << " " << position2.y << " " << position2.z;
							vID3 << nextPosition.x << " " << nextPosition.y << " " << nextPosition.z;
							vID4 << nextPosition2.x << " " << nextPosition2.y << " " << nextPosition2.z;

							uint32_t index1, index2, index3, index4;

							auto itFound = polygonIndices.find(vID.str());
							if (itFound != polygonIndices.end()) { index1 = itFound->second; }
							else { index1 = polygon->addVertex(position); polygonIndices[vID.str()] = index1; }

							itFound = polygonIndices.find(vID2.str());
							if (itFound != polygonIndices.end()) { index2 = itFound->second; }
							else { index2 = polygon->addVertex(position2); polygonIndices[vID2.str()] = index2; }

							itFound = polygonIndices.find(vID3.str());
							if (itFound != polygonIndices.end()) { index3 = itFound->second; }
							else { index3 = polygon->addVertex(nextPosition); polygonIndices[vID3.str()] = index3; }

							itFound = polygonIndices.find(vID4.str());
							if (itFound != polygonIndices.end()) { index4 = itFound->second; }
							else { index4 = polygon->addVertex(nextPosition2); polygonIndices[vID4.str()] = index4; }

							polygon->addFace(index1, index3, index4);
							polygon->addFace(index4, index2, index1);

						}
					}

					itemData->polylines.push_back(polylineData);
					itemData->open_or_closed_polyhedrons.push_back(polygon);

				}
			}

			void convertIfcParameterizedProfileDefWithPosition(
				const std::shared_ptr<typename IfcEntityTypesT::IfcParameterizedProfileDef>& profileDef,
				std::vector<std::vector<carve::geom::vector<2>>>& paths) const
			{
				std::vector<std::vector<carve::geom::vector<2>>> temp_paths;
				convertIfcParameterizedProfileDef(profileDef, temp_paths);

				// local coordinate system
				if (profileDef->m_Position)
				{
					shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2Placement2D = profileDef->m_Position;
					double length_factor = m_unitConverter->getLengthInMeterFactor();
					carve::math::Matrix transform(carve::math::Matrix::IDENT());
					PlacementConverterT<IfcEntityTypesT>::convertIfcPlacement(axis2Placement2D, transform, length_factor);

					for (int i = 0; i < temp_paths.size(); ++i)
					{
						std::vector<carve::geom::vector<2> >& path_loop = temp_paths[i];
						for (int j = 0; j < path_loop.size(); ++j)
						{
							carve::geom::vector<2>& pt = path_loop.at(j);
							carve::geom::vector<3> pt_3d(carve::geom::VECTOR(pt.x, pt.y, 0));
							pt_3d = transform*pt_3d;
							pt.x = pt_3d.x;
							pt.y = pt_3d.y;
						}
						paths.push_back(path_loop);
					}
				}
				else
				{
					for (int i = 0; i < temp_paths.size(); ++i)
					{
						std::vector<carve::geom::vector<2> >& path_loop = temp_paths[i];
						paths.push_back(path_loop);
					}
				}
			}

			void addArc(std::vector<carve::geom::vector<2>>& coords,
				double radius, double startAngle,
				double openingAngle,
				double xM, double yM, int numSegments = -1) const
			{
				if (numSegments < 0)
				{
					numSegments = (int)(abs(openingAngle) / (2.0*M_PI)*m_geomSettings->m_num_vertices_per_circle); // TODO: adapt to model size and complexity
				}

				if (numSegments < m_geomSettings->m_min_num_vertices_per_arc)
				{
					numSegments = m_geomSettings->m_min_num_vertices_per_arc;
				}

				if (numSegments > 100)
				{
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)numSegments;
				for (int i = 0; i < numSegments; ++i)
				{
					coords.push_back(carve::geom::VECTOR((radius*cos(angle) + xM), (radius*sin(angle) + yM)));
					angle += angle_delta;
				}
			}

			void addArcWithEndPoint(std::vector<carve::geom::vector<2>>& coords,
				double radius, double startAngle,
				double openingAngle,
				double xM, double yM) const
			{
				int numSegments = (int)(abs(openingAngle) / (2.0*M_PI) * m_geomSettings->m_num_vertices_per_circle); // TODO: adapt to model size and complexity

				if (numSegments < m_geomSettings->m_min_num_vertices_per_arc)
				{
					numSegments = m_geomSettings->m_min_num_vertices_per_arc;
				}

				if (numSegments > 100)
				{
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)(numSegments - 1);
				for (int i = 0; i<numSegments; ++i)
				{
					coords.push_back(carve::geom::VECTOR(radius*cos(angle) + xM, radius*sin(angle) + yM));
					angle += angle_delta;
				}
			}

			void simplifyPaths()
			{
				simplifyPaths(m_paths);
			}

			static void removeDuplicates( std::vector<std::vector<carve::geom::vector<2>>>&	paths )
			{
				for( std::vector<std::vector<carve::geom::vector<2> > >::iterator it = paths.begin(); 
					it != paths.end(); ++it )
				{
					std::vector<carve::geom::vector<2> >& loop = (*it);
					if( loop.size() > 1 )
					{
						std::vector<carve::geom::vector<2> >::iterator it_loop = loop.begin();
						carve::geom::vector<2> previous_point = (*it_loop);
						++it_loop;
						for( ; it_loop != loop.end(); ++it_loop )
						{
							carve::geom::vector<2>& current_point = (*it_loop);
							if( abs(current_point.x - previous_point.x ) < 0.00001 )
							{
								if( abs(current_point.y - previous_point.y ) < 0.00001 )
								{
									it_loop = loop.erase( it_loop );
									previous_point = (*it_loop);
									continue;
								}
							}
							previous_point = current_point;
						}
					}
				}
			}

			static void addArcWithEndPoint(std::vector<carve::geom::vector<2>>& coords,
				double radius, double startAngle, double openingAngle, 
				double xM, double yM, int numSegments)
			{
				if (numSegments < 3)
				{
					numSegments = 3;
				}

				if (numSegments > 100)
				{
					numSegments = 100;
				}

				double angle = startAngle;
				double angle_delta = openingAngle / (double)(numSegments - 1);
				for (int i = 0; i < numSegments; ++i)
				{
					coords.push_back(carve::geom::VECTOR(radius*cos(angle) + xM, radius*sin(angle) + yM));
					angle += angle_delta;
				}
			}

			static void mirrorCopyPath(std::vector<carve::geom::vector<2>>& coords,
				bool mirrorOnYAxis, bool mirrorOnXAxis)
			{
				int points_count = coords.size();
				double x, y;
				for (int i = 0; i < points_count; ++i)
				{
					carve::geom::vector<2> & p = coords.at(i);
					if (mirrorOnYAxis)
					{
						x = -p.x;
					}
					else
					{
						x = p.x;
					}
					if (mirrorOnXAxis)
					{
						y = -p.y;
					}
					else
					{
						y = p.y;
					}
					coords.push_back(carve::geom::VECTOR(x, y));
				}
			}

			static void mirrorCopyPathReverse(std::vector<carve::geom::vector<2>>& coords,
				bool mirrorOnYAxis, bool mirrorOnXAxis)
			{
				int points_count = coords.size();
				double x, y;
				for (int i = points_count - 1; i >= 0; --i)
				{
					carve::geom::vector<2> & p = coords.at(i);
					if (mirrorOnYAxis)
					{
						x = -p.x;
					}
					else
					{
						x = p.x;
					}
					if (mirrorOnXAxis)
					{
						y = -p.y;
					}
					else
					{
						y = p.y;
					}

					coords.push_back(carve::geom::VECTOR(x, y));
				}
			}

			static void addAvoidingDuplicates(const std::vector<carve::geom::vector<2>>& polygon,
				std::vector<std::vector<carve::geom::vector<2>>>& paths)
			{
				if (polygon.size() < 1)
				{
					return;
				}

				std::vector<carve::geom::vector<2> > polygon_add;
				polygon_add.push_back(polygon.at(0));
				for (int i = 1; i<polygon.size(); ++i)
				{
					const carve::geom::vector<2> & point = polygon.at(i);
					const carve::geom::vector<2> & point_previous = polygon.at(i - 1);

					// omit duplicate points
					if (abs(point.x - point_previous.x) > 0.00001)
					{
						polygon_add.push_back(point);
						continue;
					}

					if (abs(point.y - point_previous.y) > 0.00001)
					{
						polygon_add.push_back(point);
						continue;
					}

					//if( abs(point.z - point_previous.z) > 0.00001 )
					//{
					//	polygon_add.push_back( point );
					//	continue;
					//}
				}
				paths.push_back(polygon_add);
			}

			static void deleteLastPointIfEqualToFirst(
				std::vector<carve::geom::vector<2>>& coords)
			{
				while (coords.size() > 2)
				{
					carve::geom::vector<2> & first = coords.front();
					carve::geom::vector<2> & last = coords.back();

					if (abs(first.x - last.x) < 0.00000001)
					{
						if (abs(first.y - last.y) < 0.00000001)
						{
							//if( abs(first.z-last.z) < 0.00000001 )
							{
								coords.pop_back();
								continue;
							}
						}
					}
					break;
				}
			}

			static void simplifyPaths(std::vector<std::vector<carve::geom::vector<2>>>& paths)
			{
				for (std::vector<std::vector<carve::geom::vector<2> > >::iterator it_paths = 
					paths.begin(); it_paths != paths.end(); ++it_paths)
				{
					std::vector<carve::geom::vector<2>>& path = (*it_paths);
					if (path.size() < 3)
					{
						continue;
					}
					simplifyPath(path);
				}
			}

			static void simplifyPath(std::vector<carve::geom::vector<2>>& path)
			{
				if (path.size() < 3)
				{
					return;
				}

				for (int i = 1; i<path.size() - 1;)
				{
					carve::geom::vector<2>& previous = path[i - 1];
					carve::geom::vector<2>& current = path[i];
					carve::geom::vector<2>& next = path[i + 1];

					carve::geom::vector<2> segment1 = current - previous;
					segment1.normalize();
					carve::geom::vector<2> segment2 = next - current;
					segment2.normalize();
					double angle = abs(segment1.x*segment2.x + segment1.y*segment2.y);
					if (abs(angle - 1) < 0.00001)
					{
						// points are colinear, current point can be removed
						path.erase(path.begin() + i);
						continue;
					}
					++i;
				}

				// 1-----0 5-----4      0-----------3         1---0 4---3      0-----------2
				// |             |  ->  |           |         |   _ ---    ->  |   _ ---
				// 2-------------3      1-----------2         2--              1---

				if (path.size() > 4)
				{
					carve::geom::vector<2>& first = path.front();
					carve::geom::vector<2>& last = path.back();

					if ((last - first).length2() < 0.000001)
					{
						carve::geom::vector<2> first_segment = path[1] - first;
						first_segment.normalize();
						carve::geom::vector<2> last_segment = last - path[path.size() - 2];
						last_segment.normalize();
						double angle = abs(first_segment.x*last_segment.x + first_segment.y*last_segment.y);
						if (abs(angle - 1) < 0.00001)
						{
							// remove first and last point
							path.erase(path.begin());
							path.pop_back();
						}
					}
				}
			}

			const std::vector<std::vector<carve::geom::vector<2>>>& getCoordinates()
			{
				return m_paths;
			}

		protected:
			std::shared_ptr<GeometrySettings>	m_geomSettings;
			std::shared_ptr<IfcUnitConverterT>	m_unitConverter;
			std::vector<std::vector<carve::geom::vector<2>>>	m_paths;
		};
	}
}

#endif
