/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
 *
 * - modfied by Michael Kern (September 2014)
*/

// visual studio
#pragma once
// unix
#ifndef CURVECONVERTER_H
#define CURVECONVERTER_H

#define _USE_MATH_DEFINES 
#include <math.h>

#include "CarveHeaders.h"

#include "GeomUtils.h"
#include "UnhandledRepresentationException.h"
#include "PlacementConverter.h"
#include "ProfileConverter.h"
#include "GeometrySettings.h"
#include "SplineConverter.h"


#include "OpenInfraPlatform/ExpressBinding/vectorUtilites.h"

/**********************************************************************************************/

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template<
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>
		class CurveConverterT
		{
		public:
			CurveConverterT(std::shared_ptr<GeometrySettings> geomSettings,
				std::shared_ptr<IfcUnitConverterT> unitConverter)
				: 
			m_geomSettings(geomSettings), 
			m_unitConverter(unitConverter)
			{
			}

			virtual ~CurveConverterT()
			{

			}

			void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
				std::vector<carve::geom::vector<3>>& loops,
				std::vector<carve::geom::vector<3>>& segmentStartPoints) const
			{
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim1Vec;
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > trim2Vec;
				convertIfcCurve(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
			}

			void convertIfcCurve(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
				std::vector<carve::geom::vector<3>>& targetVec,
				std::vector<carve::geom::vector<3>>& segmentStartPoints,
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim1Vec,
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> >& trim2Vec,
				bool senseAgreement) const
			{
				double length_factor = m_unitConverter->getLengthInMeterFactor();
				double plane_angle_factor = m_unitConverter->getAngleInRadianFactor();

				//	ENTITY IfcCurve ABSTRACT SUPERTYPE OF	(ONEOF(IfcBoundedCurve, IfcConic, IfcLine, IfcOffsetCurve2D, IfcOffsetCurve3D, IfcPCurve))
				std::shared_ptr<typename IfcEntityTypesT::IfcBoundedCurve> bounded_curve =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcBoundedCurve>(ifcCurve);
				if (bounded_curve)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurve> composite_curve =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCompositeCurve>(bounded_curve);
					if (composite_curve)
					{
						// ENTITY IfcBoundedCurve ABSTRACT SUPERTYPE OF	(ONEOF(IfcCompositeCurve, IfcPolyline, IfcTrimmedCurve, IfcBSplineCurve))
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> > segements =
							composite_curve->m_Segments;
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> >::iterator it_segments =
							segements.begin();
						for (; it_segments != segements.end(); ++it_segments)
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcCompositeCurveSegment> segement = (*it_segments);
							std::shared_ptr<typename IfcEntityTypesT::IfcCurve> segement_curve = segement->m_ParentCurve;

							std::vector<carve::geom::vector<3>> segment_vec;
							convertIfcCurve(segement_curve, segment_vec, segmentStartPoints);
							if (segment_vec.size() > 0)
							{
								GeomUtils::appendPointsToCurve(segment_vec, targetVec);
							}
						}
						return;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcPolyline> poly_line = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyline>(ifcCurve);
					if (poly_line)
					{
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& points = poly_line->m_Points;
						if (points.size() > 0)
						{
							convertIfcCartesianPointVector(points, targetVec);
							segmentStartPoints.push_back(carve::geom::VECTOR(
								points[0]->m_Coordinates[0]->m_value*length_factor,
								points[0]->m_Coordinates[1]->m_value*length_factor,
								0));
						}
						return;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcTrimmedCurve> trimmed_curve =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcTrimmedCurve>(bounded_curve);
					if (trimmed_curve)
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcCurve> basis_curve = trimmed_curve->m_BasisCurve;
						std::vector<carve::geom::vector<3> > basis_curve_points;

						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > curve_trim1_vec =
							trimmed_curve->m_Trim1;
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect> > curve_trim2_vec =
							trimmed_curve->m_Trim2;
						bool trimmed_sense_agreement = trimmed_curve->m_SenseAgreement;

						convertIfcCurve(basis_curve, basis_curve_points, segmentStartPoints,
							curve_trim1_vec, curve_trim2_vec, trimmed_sense_agreement);
						GeomUtils::appendPointsToCurve(basis_curve_points, targetVec);
						return;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcBSplineCurve> bspline_curve =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcBSplineCurve>(bounded_curve);
					if (bspline_curve)
					{
						std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points = 
							bspline_curve->m_ControlPointsList;

						std::vector<carve::geom::vector<3>> splinePoints;
						splinePoints.reserve(points.size());
						convertIfcCartesianPointVector(points, splinePoints);

						SplineConverterT<typename IfcEntityTypesT, IfcUnitConverterT>::convertIfcBSplineCurve(bspline_curve, splinePoints, targetVec);
						return;
					}
					throw UnhandledRepresentationException<IfcEntityTypesT>(bounded_curve);
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcConic> conic = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcConic>(ifcCurve);
				if (conic)
				{
					// ENTITY IfcConic ABSTRACT SUPERTYPE OF(ONEOF(IfcCircle, IfcEllipse))
					std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement> conic_placement = conic->m_Position;
					carve::math::Matrix conic_position_matrix(carve::math::Matrix::IDENT());

					std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement2D> axis2placement2d =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement2D>(conic_placement);

					if (axis2placement2d)
					{
						PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement2D(axis2placement2d,
							conic_position_matrix, length_factor);
					}
					else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(conic_placement))
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcAxis2Placement3D> axis2placement3d =
							dynamic_pointer_cast<typename IfcEntityTypesT::IfcAxis2Placement3D>(conic_placement);

						PlacementConverterT<IfcEntityTypesT>::convertIfcAxis2Placement3D(axis2placement3d,
							conic_position_matrix, length_factor);
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcCircle> circle = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcCircle>(conic);
					if (circle)
					{
						double circle_radius = 0.0;
						if (circle->m_Radius)
						{
							circle_radius = dynamic_pointer_cast<typename IfcEntityTypesT::IfcLengthMeasure>(circle->m_Radius)->m_value*length_factor;
						}

						carve::geom::vector<3> circle_center =
							conic_position_matrix*carve::geom::VECTOR(0, 0, 0);

						double trim_angle1 = 0.0;
						double trim_angle2 = M_PI*2.0;

						// check for trimming begin
						std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par1;
						if (trim1Vec.size() > 0)
						{
							if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_par1))
							{
								trim_angle1 = trim_par1->m_value * plane_angle_factor;
							}
							else
							{
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> trim_point1;
								if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_point1))
								{
									carve::geom::vector<3> trim_point;
									convertIfcCartesianPoint(trim_point1, trim_point);

									trim_angle1 = getAngleOnCircle(circle_center,
										circle_radius,
										trim_point);
								}
							}
						}

						if (trim2Vec.size() > 0)
						{
							// check for trimming end
							std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par2;
							if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, trim_par2))
							{
								trim_angle2 = trim_par2->m_value * plane_angle_factor;
							}
							else
							{
								std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
								if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, ifc_trim_point))
								{
									carve::geom::vector<3> trim_point;
									convertIfcCartesianPoint(ifc_trim_point, trim_point);
									trim_angle2 = getAngleOnCircle(circle_center,
										circle_radius,
										trim_point);
								}
							}
						}

						double start_angle = trim_angle1;
						double opening_angle = 0;

						if (senseAgreement)
						{
							if (trim_angle1 < trim_angle2)
							{
								opening_angle = trim_angle2 - trim_angle1;
							}
							else
							{
								// circle passes 0 angle
								opening_angle = trim_angle2 - trim_angle1 + 2.0*M_PI;
							}
						}
						else
						{
							if (trim_angle1 > trim_angle2)
							{
								opening_angle = trim_angle2 - trim_angle1;
							}
							else
							{
								// circle passes 0 angle
								opening_angle = trim_angle2 - trim_angle1 - 2.0*M_PI;
							}
						}

						if (opening_angle > 0)
						{
							while (opening_angle > 2.0*M_PI)
							{
								opening_angle -= 2.0*M_PI;
							}
						}
						else
						{
							while (opening_angle < -2.0*M_PI)
							{
								opening_angle += 2.0*M_PI;
							}
						}

						int num_segments = m_geomSettings->m_num_vertices_per_circle
							* (abs(opening_angle) / (2.0*M_PI));

						if (num_segments < m_geomSettings->m_min_num_vertices_per_arc)
						{
							num_segments = m_geomSettings->m_min_num_vertices_per_arc;
						}

						const double circle_center_x = 0.0;
						const double circle_center_y = 0.0;
						std::vector<carve::geom::vector<2> > circle_points;
						ProfileConverterT<IfcEntityTypesT, IfcUnitConverterT>::addArcWithEndPoint(circle_points, circle_radius, start_angle,
							opening_angle, circle_center_x,
							circle_center_y, num_segments);

						if (circle_points.size() > 0)
						{
							// apply position
							for (unsigned int i = 0; i<circle_points.size(); ++i)
							{
								carve::geom::vector<2>&  point = circle_points.at(i);
								carve::geom::vector<3> point3d(carve::geom::VECTOR(point.x, point.y, 0));
								point3d = conic_position_matrix * point3d;
								point.x = point3d.x;
								point.y = point3d.y;
							}

							GeomUtils::appendPointsToCurve(circle_points, targetVec);
							segmentStartPoints.push_back(carve::geom::VECTOR(circle_points.at(0).x,
								circle_points.at(0).y,
								0));
						}

						return;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcEllipse> ellipse = 
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcEllipse>(conic);
					if (ellipse)
					{
						if (ellipse->m_SemiAxis1)
						{
							if (ellipse->m_SemiAxis2)
							{
								double xRadius = ellipse->m_SemiAxis1->m_value*length_factor;
								double yRadius = ellipse->m_SemiAxis2->m_value*length_factor;

								double radiusMax = std::max(xRadius, yRadius);
								int num_segments = m_geomSettings->m_num_vertices_per_circle;
								// TODO: adapt to model size and complexity

								// todo: implement clipping

								std::vector<carve::geom::vector<3> > circle_points;
								double angle = 0;
								for (int i = 0; i < num_segments; ++i)
								{
									circle_points.push_back(carve::geom::vector<3>(
										carve::geom::VECTOR(xRadius * cos(angle),
										yRadius * sin(angle),
										0)));
									angle += 2.0*M_PI / double(num_segments);
								}

								// apply position
								for (unsigned int i = 0; i<circle_points.size(); ++i)
								{
									carve::geom::vector<3>& point = circle_points.at(i);
									point = conic_position_matrix * point;
								}
								GeomUtils::appendPointsToCurve(circle_points, targetVec);

								//if( segmentStartPoints != NULL )
								{
									carve::geom::vector<3> pt0 = circle_points.at(0);
									segmentStartPoints.push_back(pt0);
								}
							}
						}
						return;
					}
					throw UnhandledRepresentationException<IfcEntityTypesT>(conic);
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcLine> line = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcLine>(ifcCurve);
				if (line)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_line_point = line->m_Pnt;
					carve::geom::vector<3> line_origin;
					convertIfcCartesianPoint(ifc_line_point, line_origin);

					// line: lambda(u) = line_point + u*line_direction
					std::shared_ptr<typename IfcEntityTypesT::IfcVector> line_vec = line->m_Dir;
					if (!line_vec)
					{
						return;
					}
					std::shared_ptr<typename IfcEntityTypesT::IfcDirection> ifc_line_direction = line_vec->m_Orientation;

					std::vector<double> direction_ratios(ifc_line_direction->m_DirectionRatios.size());
					for (int i = 0; i < direction_ratios.size(); ++i) {
						direction_ratios[i] = ifc_line_direction->m_DirectionRatios[i];
					}

					carve::geom::vector<3> line_direction;
					if (direction_ratios.size() > 1)
					{
						if (direction_ratios.size() > 2)
						{
							line_direction = carve::geom::VECTOR(direction_ratios[0],
								direction_ratios[1],
								direction_ratios[2]);
						}
						else
						{
							line_direction = carve::geom::VECTOR(direction_ratios[0],
								direction_ratios[1], 0);
						}
					}
					line_direction.normalize();

					std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> line_magnitude = line_vec->m_Magnitude;
					double line_magnitude_value = line_magnitude->m_value*length_factor;

					// check for trimming at beginning of line
					double start_parameter = 0.0;
					std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par1;
					if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, trim_par1))
					{
						start_parameter = trim_par1->m_value;
						line_origin = line_origin + line_direction * start_parameter;
					}
					else
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
						if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim1Vec, ifc_trim_point))
						{
							carve::geom::vector<3> trim_point;
							convertIfcCartesianPoint(ifc_trim_point, trim_point);

							carve::geom::vector<3> closest_point_on_line;
							GeomUtils::closestPointOnLine(trim_point, line_origin,
								line_direction, closest_point_on_line);

							if ((closest_point_on_line - trim_point).length() < 0.0001)
							{
								// trimming point is on the line
								line_origin = trim_point;
							}
						}
					}
					// check for trimming at end of line
					carve::geom::vector<3> line_end;
					std::shared_ptr<typename IfcEntityTypesT::IfcParameterValue> trim_par2;
					if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcParameterValue, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, trim_par2))
					{
						line_magnitude_value = trim_par2->m_value * length_factor;
						line_end = line_origin + line_direction * line_magnitude_value;
					}
					else
					{
						std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifc_trim_point;
						if (OpenInfraPlatform::ExpressBinding::findFirstInVector<typename IfcEntityTypesT::IfcCartesianPoint, typename IfcEntityTypesT::IfcTrimmingSelect>(trim2Vec, ifc_trim_point))
						{
							carve::geom::vector<3> trim_point;
							convertIfcCartesianPoint(ifc_trim_point, trim_point);

							carve::geom::vector<3> closest_point_on_line;
							GeomUtils::closestPointOnLine(trim_point, line_origin,
								line_direction, closest_point_on_line);

							if ((closest_point_on_line - trim_point).length() < 0.0001)
							{
								// trimming point is on the line
								line_end = trim_point;
							}
						}
					}

					std::vector<carve::geom::vector<3> > points_vec;
					points_vec.push_back(line_origin);
					points_vec.push_back(line_end);

					GeomUtils::appendPointsToCurve(points_vec, targetVec);

					//if( segment_start_points != NULL )
					{
						segmentStartPoints.push_back(line_origin);
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve2D> offset_curve_2d =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve2D>(ifcCurve);
				if (offset_curve_2d)
				{
#ifdef _DEBUG
					std::cout << "Warning\t| IfcOffsetCurve2D not implemented" << std::endl;
#endif
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcOffsetCurve3D> offset_curve_3d =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcOffsetCurve3D>(ifcCurve);
				if (offset_curve_3d)
				{
#ifdef _DEBUG
					std::cout << "Warning\t| IfcOffsetCurve3D not implemented" << std::endl;
#endif
					return;
				}

				/*std::shared_ptr<IfcPcurve> pcurve = dynamic_pointer_cast<IfcPcurve>(ifcCurve);
				if( pcurve )
				{
				// TODO: implement
				return;
				}*/

				throw UnhandledRepresentationException<IfcEntityTypesT>(ifcCurve);
			}

			void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
				std::vector<carve::geom::vector<2>>& loops,
				std::vector<carve::geom::vector<2>>& segmentStartPoints) const
			{
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim1Vec;
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>> trim2Vec;
				convertIfcCurve2D(ifcCurve, loops, segmentStartPoints, trim1Vec, trim2Vec, true);
			}

			void convertIfcCurve2D(const std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& ifcCurve,
				std::vector<carve::geom::vector<2>>& targetVec,
				std::vector<carve::geom::vector<2>>& segmentStartPoints,
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim1Vec,
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcTrimmingSelect>>& trim2Vec,
				bool senseAgreement) const
			{
				std::vector<carve::geom::vector<3>> target_vec_3d;
				std::vector<carve::geom::vector<3>> segment_start_points_3d;

				convertIfcCurve(ifcCurve, target_vec_3d, segment_start_points_3d,
					trim1Vec, trim2Vec, senseAgreement);

				for (int i = 0; i<target_vec_3d.size(); ++i)
				{
					carve::geom::vector<3>& point_3d = target_vec_3d[i];
					targetVec.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
				}
				for (int i = 0; i<segment_start_points_3d.size(); ++i)
				{
					carve::geom::vector<3>& point_3d = segment_start_points_3d[i];
					segmentStartPoints.push_back(carve::geom::VECTOR(point_3d.x, point_3d.y));
				}
			}

			void convertIfcPolyline(const std::shared_ptr<typename IfcEntityTypesT::IfcPolyline>& polyLine,
				std::vector<carve::geom::vector<3>>& loop) const
			{
				convertIfcCartesianPointVector(polyLine->m_Points, loop);
			}

			void convertIfcLoop(const std::shared_ptr<typename IfcEntityTypesT::IfcLoop>& loop,
				std::vector<carve::geom::vector<3>>& loopPoints) const
			{
				const std::shared_ptr<typename IfcEntityTypesT::IfcPolyLoop> polyLoop = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcPolyLoop>(loop);
				if (polyLoop)
				{
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& ifcPoints = polyLoop->m_Polygon;
					convertIfcCartesianPointVectorSkipDuplicates(ifcPoints, loopPoints);

					// if first and last point have same coordinates, remove last point
					while (loopPoints.size() > 2)
					{
						carve::geom3d::Vector& first = loopPoints.front();
						carve::geom3d::Vector& last = loopPoints.back();

						if (abs(first.x - last.x) < 0.00000001)
						{
							if (abs(first.y - last.y) < 0.00000001)
							{
								if (abs(first.z - last.z) < 0.00000001)
								{
									loopPoints.pop_back();
									continue;
								}
							}
						}
						break;
					}
					return;
				}

				std::shared_ptr<typename IfcEntityTypesT::IfcEdgeLoop> edgeLoop = 
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeLoop>(loop);
				if (edgeLoop)
				{
					//std::vector<carve::geom::vector<3>> edgePoints;

					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge>>& edgeList = edgeLoop->m_EdgeList;
					// go through every edge in the edge list
					for (auto it_edge = edgeList.begin(); it_edge != edgeList.end(); ++it_edge)
					{
						// edge loop consists of many oriented edges
						std::shared_ptr<typename IfcEntityTypesT::IfcOrientedEdge> orientedEdge = (*it_edge);
						// which are described by the type of its edge element object
						std::shared_ptr<typename IfcEntityTypesT::IfcEdge>& edgeElement = orientedEdge->m_EdgeElement;

						std::shared_ptr<typename IfcEntityTypesT::IfcEdgeCurve> edgeCurve =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcEdgeCurve>(edgeElement);

						if (edgeCurve)
						{
							std::shared_ptr<typename IfcEntityTypesT::IfcCurve>& curveGeom = edgeCurve->m_EdgeGeometry;
							std::vector<carve::geom::vector<3>> segmentStartPoints;

							convertIfcCurve(curveGeom, loopPoints, segmentStartPoints);

							continue;
						}

						std::shared_ptr<typename IfcEntityTypesT::IfcSubedge> subEdge =
							std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSubedge>(edgeElement);

						if (subEdge)
						{
							std::cout << "ERROR\t| IfcSubedge not implemented" << std::endl;
							continue;
						}

						std::cout << "ERROR\t| Entity " << orientedEdge->classname() << " not handled" << std::endl;

						// every edge consists of one start and end vertex
						//std::shared_ptr<typename IfcEntityTypesT::IfcVertex>& edgeStartVertex = edgeElement->m_EdgeStart;
						//std::shared_ptr<typename IfcEntityTypesT::IfcVertexPoint> edgeStartVertexPoint =
						//	dynamic_pointer_cast<typename IfcEntityTypesT::IfcVertexPoint>(edgeStartVertex);
						//
						//if (edgeStartVertexPoint)
						//{
						//	if (edgeStartVertexPoint->m_VertexGeometry)
						//	{
						//		std::shared_ptr<typename IfcEntityTypesT::IfcPoint>& startPoint =
						//			edgeStartVertexPoint->m_VertexGeometry;
						//		std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> ifcPoint =
						//			dynamic_pointer_cast<typename IfcEntityTypesT::IfcCartesianPoint>(startPoint);
						//		if (!ifc_point)
						//		{
						//			// TODO: could be also  IfcPointOnCurve, IfcPointOnSurface
						//			continue;
						//		}
						//		// TODO: implement
						//	}
						//}
						
					}
				}
			}

			void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
				carve::geom::vector<3> & point) const
			{
				double length_factor = m_unitConverter->getLengthInMeterFactor();
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords1 = ifcPoint->m_Coordinates;
				if (coords1.size() > 2)
				{
					double x = coords1[0]->m_value * length_factor;
					double y = coords1[1]->m_value * length_factor;
					double z = coords1[2]->m_value * length_factor;

					point = carve::geom::VECTOR(x, y, z);
				}
				else if (coords1.size() > 1)
				{
					// round to 0.1 mm
					double x = coords1[0]->m_value * length_factor;
					double y = coords1[1]->m_value * length_factor;

					point = carve::geom::VECTOR(x, y, 0.0);
				}
			}

			void convertIfcCartesianPointVector(
				const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>>& points,
				std::vector<carve::geom::vector<3>>& loop) const
			{
				const double length_factor = m_unitConverter->getLengthInMeterFactor();
				const unsigned int num_points = points.size();
				for (unsigned int i_point = 0; i_point < num_points; ++i_point)
				{
					const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords =
						points[i_point]->m_Coordinates;

					if (coords.size() > 2)
					{
						double x = coords[0]->m_value * length_factor;
						double y = coords[1]->m_value * length_factor;
						double z = coords[2]->m_value * length_factor;

						loop.push_back(carve::geom::VECTOR(x, y, z));
					}
					else if (coords.size() > 1)
					{

						double x = coords[0]->m_value * length_factor;
						double y = coords[1]->m_value * length_factor;

						loop.push_back(carve::geom::VECTOR(x, y, 0.0));
					}
					else
					{
						std::cout << "convertIfcCartesianPointVector: ifc_pt->m_Coordinates.size() != 2"
							<< std::endl;
					}
				}
			}

			// @brief: returns the corresponding angle (radian, 0 is to the right) if the given point lies on the circle. If the point does not lie on the circle, -1 is returned.
			static double getAngleOnCircle(const carve::geom::vector<3>& circleCenter,
				double circleRadius,
				const carve::geom::vector<3>& trimPoint)
			{
				double result_angle = -1.0;
				carve::geom::vector<3> center_trim_point = trimPoint - circleCenter;
				if (abs(center_trim_point.length() - circleRadius) < 0.0001)
				{
					carve::geom::vector<3> center_trim_point_direction = center_trim_point;
					center_trim_point_direction.normalize();
					double cos_angle = carve::geom::dot(center_trim_point_direction, carve::geom::vector<3>(carve::geom::VECTOR(1.0, 0, 0)));

					if (abs(cos_angle) < 0.0001)
					{
						if (center_trim_point.y > 0)
						{
							result_angle = M_PI_2;
						}
						else if (center_trim_point.y < 0)
						{
							result_angle = M_PI*1.5;
						}
					}
					else
					{
						if (center_trim_point.y > 0)
						{
							result_angle = acos(cos_angle);
						}
						else if (center_trim_point.y < 0)
						{
							result_angle = 2.0*M_PI - acos(cos_angle);
						}
					}
				}
				return result_angle;
			}

			void convertIfcCartesianPointVectorSkipDuplicates(
				const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >& ifcPoints,
				std::vector<carve::geom::vector<3> >& loop) const
			{
				const double length_factor = m_unitConverter->getLengthInMeterFactor();
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> >::const_iterator it_cp;
				int i = 0;
				carve::geom::vector<3>  vertex_previous;
				for (it_cp = ifcPoints.begin(); it_cp != ifcPoints.end(); ++it_cp, ++i)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint> cp = (*it_cp);
					const int cp_id = cp->getId();
					double x = 0.0, y = 0.0, z = 0.0;
					std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure> >& coords = cp->m_Coordinates;

					if (coords.size() > 2)
					{
						x = coords[0]->m_value * length_factor;
						y = coords[1]->m_value * length_factor;
						z = coords[2]->m_value * length_factor;
					}
					else if (coords.size() > 1)
					{

						x = coords[0]->m_value * length_factor;
						y = coords[1]->m_value * length_factor;
					}

					carve::geom::vector<3>  vertex(carve::geom::VECTOR(x, y, z));

					// skip duplicate vertices
					if (it_cp != ifcPoints.begin())
					{
						if (abs(vertex.x - vertex_previous.x) < 0.00000001)
						{
							if (abs(vertex.y - vertex_previous.y) < 0.00000001)
							{
								if (abs(vertex.z - vertex_previous.z) < 0.00000001)
								{
									// TODO: is it better to report degenerated loops, or to just omit them?
									continue;
								}
							}
						}
					}
					loop.push_back(vertex);
					vertex_previous = vertex;
				}
			}

			static void convertIfcCartesianPoint(const std::shared_ptr<typename IfcEntityTypesT::IfcCartesianPoint>& ifcPoint,
				carve::geom::vector<3> & point,
				double lengthFactor)
			{
				std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcLengthMeasure>>& coords1 = ifcPoint->m_Coordinates;
				if (coords1.size() > 2)
				{
					double x = coords1[0]->m_value * lengthFactor;
					double y = coords1[1]->m_value * lengthFactor;
					double z = coords1[2]->m_value * lengthFactor;

					point = carve::geom::VECTOR(x, y, z);
				}
				else if (coords1.size() > 1)
				{
					// round to 0.1 mm
					double x = coords1[0]->m_value * lengthFactor;
					double y = coords1[1]->m_value * lengthFactor;

					point = carve::geom::VECTOR(x, y, 0.0);
				}
			}

		protected:
			std::shared_ptr<GeometrySettings>	m_geomSettings;
			std::shared_ptr<IfcUnitConverterT>	m_unitConverter;
		};
	}
}


#endif
