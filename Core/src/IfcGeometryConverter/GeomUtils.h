/*
    Copyright (c) 2021 Technical University of Munich
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
 *
 * - modified by Michael Kern, September 2014
*/
// visual studio
#pragma once
// unix
#ifndef GEOMUTILS_H
#define GEOMUTILS_H

#include <vector>

#include "CarveHeaders.h"

//#include <buw.BlueEngine.h>
#include <BlueFramework/Core/Math/Vector.h>

namespace OpenInfraPlatform
{
	namespace Core {
		namespace IfcGeometryConverter {
			class GeometrySettings;

			enum ProjectionPlane {
				UNDEFINED,
				XY_PLANE,
				YZ_PLANE,
				XZ_PLANE
			};

			struct GeomException : public std::exception {
				std::string s;
				GeomException(std::string ss) : s(ss) {}
				~GeomException() throw () {} // Updated
				const char* what() const throw() { return s.c_str(); }
			};

			/*!	\brief Helper functions for calculations of geometries

			*/
			class GeomUtils {
			public:

				/**********************************************************************************************/
				/*! \brief Compare two doubles for equality to the custom precision
				*
				* \param[in] first					The first value
				* \param[in] second					The second value
				* \param[in] precision				Precision of model
				*
				* \return							True, if the absolute difference is smaller than the precision. False otherwise
				*/
				static bool GeomUtils::areEqual(const double first, 
					const double second, const double precision);

				/**********************************************************************************************/
				/*! \brief Calculates a geometric center of the plane figure. 
				*
				* \param[in] polygon				Polygon, which contains points of a plane figure. 
				*
				* \return							Geometric center of the plane figure. 
				*/
				static carve::geom::vector<3> computePolygonCentroid(
					const std::vector<carve::geom::vector<3>>& polygon);

				/**********************************************************************************************/
				/*! \brief Calculates a normal of the plane using points of the polygon on this plane.
				*
				* \param[in] polygon				Polygon with points (in 3D) on the plane. 
				*
				* \return							Normal vector of the plane. 
				*/
				static carve::geom::vector<3> computePolygonNormal(
					const std::vector<carve::geom::vector<3>>& polygon);

				/**********************************************************************************************/
				/*! \brief Calculates a normal of the plane using points of the polygon on this plane.
				*
				* \param[in] polygon				Polygon with points (in 2D) on the plane.
				*
				* \return							Normal vector of the plane.
				*/
				static carve::geom::vector<3> computePolygon2DNormal(
					const std::vector<carve::geom::vector<2>>& polygon);

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				*
				* \param[in] initialPointSeg1		1st line segment, 1st point.
				* \param[in] terminalPointSeg1		1st line segment, 2nd point.
				* \param[in] initialPointSeg2		2nd line segment, 1st point.
				* \param[in] terminalPointSeg2		2nd line segment, 2nd point.
				* \param[out] intersectionPoint		Coordinates of the intersection point between first line segment and second line.
				*
				* \return							Returns true, if lines are intersecting with each other. False otherwise.
				*/
				static bool LineSegmentToLineIntersection(const carve::geom::vector<2>& initialPointSeg1,
					const carve::geom::vector<2>& terminalPointSeg1,
					const carve::geom::vector<2>& initialPointSeg2,
					const carve::geom::vector<2>& terminalPointSeg2,
					carve::geom::vector<2> & intersectionPoint);

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				*
				* \param[in] initialPointSeg1		1st line segment, 1st point.
				* \param[in] terminalPointSeg1		1st line segment, 2nd point.
				* \param[in] initialPointSeg2		2nd line segment, 1st point.
				* \param[in] terminalPointSeg2		2nd line segment, 2nd point.
				* \param[out] intersectionPoint		Coordinates of the intersection point between first line and second line.
				*
				* \return							Returns true, if lines are intersecting with each other. False otherwise.
				*/
				static bool LineSegmentToLineSegmentIntersection(const carve::geom::vector<2>& initialPointSeg1,
					const carve::geom::vector<2>& terminalPointSeg1,
					const carve::geom::vector<2>& initialPointSeg2,
					const carve::geom::vector<2>& terminalPointSeg2,
					carve::geom::vector<2> & intersectionPoint);

				/**********************************************************************************************/
				/*! \brief Calculates coordinates of the intersection point.
				*
				* \param[in] initialPointSeg1		1st line segment, 1st point.
				* \param[in] terminalPointSeg1		1st line segment, 2nd point.
				* \param[in] initialPointSeg2		2nd line segment, 1st point.
				* \param[in] terminalPointSeg2		2nd line segment, 2nd point.
				* \param[out] intersectionPoint		Coordinates of the intersection point between first line segment and second line segment.
				*
				* \return							Returns true, if lines are intersecting with each other. False otherwise.
				*/
				static bool GeomUtils::LineToLineIntersection(const carve::geom::vector<2>& initialPointSeg1,
					const carve::geom::vector<2>& terminalPointSeg1,
					const carve::geom::vector<2>& initialPointSeg2,
					const carve::geom::vector<2>& terminalPointSeg2,
					carve::geom::vector<2> & intersectionPoint);

				/**********************************************************************************************/
				/*! \brief Calculates distances between start points of the segment and their intersection.
				* \param[in] initialPointSeg1		1st line segment, 1st point.
				* \param[in] terminalPointSeg1		1st line segment, 2nd point.
				* \param[in] initialPointSeg2		2nd line segment, 1st point.
				* \param[in] terminalPointSeg2		2nd line segment, 2nd point.
				*
				* \param[out] distToIntesection1	Distance from initialPointSeg1 to the segment intresection, which is calculated as section of the first segment.
				* \param[out] distToIntesection2	Distance from initialPointSeg2 to the segment intresection, which is calculated as section of the second segment.
				*
				* \return							Returns true, if lines are intersecting with each other. False otherwise.
				*/
				static bool GeomUtils::LineToLineIntersectionHelper(const carve::geom::vector<2>& initialPointSeg1,
					const carve::geom::vector<2>& terminalPointSeg1,
					const carve::geom::vector<2>& initialPointSeg2,
					const carve::geom::vector<2>& terminalPointSeg2,
					double & distToIntesection1, double & distToIntesection2);

				/**********************************************************************************************/
				/*! \brief Appedns vector of points (in 3D) to the curve.
				*
				* \param[in] points_vec				A vector of points. 
				*
				* \param[out] target_vec			A curve. 
				* 
				* \note Dupliation of points is checked in the function. All duplicated points are skipped. 
				*/
				static void appendPointsToCurve(
					const std::vector<carve::geom::vector<3>>& points_vec,
					std::vector<carve::geom::vector<3>>& target_vec);

				/**********************************************************************************************/
				/*! \brief Appedns vector of points (in 2D) to the curve.
				*
				* \param[in] points_vec				A vector of points.
				*
				* \param[out] target_vec			A curve.
				*
				* \note Dupliation of points is checked in the function. All duplicated points are skipped.
				*/
				static void appendPointsToCurve(
					const std::vector<carve::geom::vector<2>>& points_vec,
					std::vector<carve::geom::vector<3>>& target_vec);

				/**********************************************************************************************/
				/*! \brief Computes an inverse of the matrix.
				*
				* \param[in] matrix_a				An initial invertible matrix.
				*
				* \return							Inverted matrix
				*/
				static carve::math::Matrix computeInverse(
					const carve::math::Matrix& matrix_a);

				/**********************************************************************************************/
				/*! \brief Calculates the closest point on the line given another point. 
				*
				* \param[in] point					Point outside the line. 
				* \param[in] line_origin			Line origin point. 
				* \param[in] line_direction			Direction of the line. 	
				*
				* \param[out] closest				Closest point on the (infinite) line to the point.
				*/
				static void closestPointOnLine(const carve::geom::vector<3>& point,
					const carve::geom::vector<3>& line_origin,
					const carve::geom::vector<3>& line_direction,
					carve::geom::vector<3>& closest);

				/**********************************************************************************************/
				/*! \brief Calculates the closest point on the line given another point.
				*
				* \param[in] point					Point outside the line.
				* \param[in] line_origin			Line origin point.
				* \param[in] line_direction			Direction of the line.
				*
				* \param[out] closest				Closest point on the (infinite) line to the point.
				*/
				static void closestPointOnLine(const buw::Vector3f& point,
					const buw::Vector3f& line_origin,
					const buw::Vector3f& line_direction,
					buw::Vector3f& closest);

				/**********************************************************************************************/
				/*! \brief Verify if point is on the segment of the line. 
				*
				* \param[in] point					Point which should be verified. 
				* \param[in] line_origin			Line origin point.
				* \param[in] line_direction			Direction of the line.
				*
				* \param[out] lambda				The ratio of where the point lies on the line. 
				*
				* \return 							Returns true, if point is on the line. False otherwise.
				*
				* \note EXAMPLE: If lambda = 0, point is equal to line_origin. If lambda = 1, point is equal line_origin + line_direction.
				*/
				static bool isPointOnLineSegment(double& lambda,
					const buw::Vector3f& point,
					const buw::Vector3f& line_origin,
					const buw::Vector3f& line_direction);
				
				/**********************************************************************************************/
				/*! \brief Extrude geometry. 
				*
				* \param[in] paths					List of several sets of points of the geometry (profiles to be extruded).
				* \param[in] dir					The direction + length, where geometry should be extruded.
				* \param[in] closed					Should the geometry be closed, i.e. include a face at the bottom and top as well or is only the mantel of interest?
				*
				* \param[out] poly_data				List of faces of the geometry.
				*/
				static void extrude(const std::vector<std::vector<carve::geom::vector<2>>>& paths,
					const carve::geom::vector<3> dir,
					const bool closed,
					std::shared_ptr<carve::input::PolyhedronData>& poly_data);

				/**********************************************************************************************/
				/*! \brief Incorporates voids to the geometry. 
				*
				* \param[in] paths					List of several sets of points. 
				*
				* \param[out] merged_path			Arranged list of points.
				* \param[out] triangulated			List of triangles to visualize geometry.
				* \param[out] path_all_loops		List of several sets of indices. 
				*/
				static void incorporateVoids(const std::vector<std::vector<carve::geom2d::P2>>& paths,
					std::vector<carve::geom2d::P2>& merged_path,
					std::vector<carve::triangulate::tri_idx>& triangulated, 
					std::vector<std::pair<size_t, size_t>>& path_all_loops);

				/**********************************************************************************************/
				/*! \brief Corrects a winding of the points in curves.
				*
				* \param[in] face_loops_input		List of several sets of points.
				*
				* \param[out] normal_first_loop		Normalised first loop. 
				*
				* return							List of several sets of points with correct winding. 			
				*/
				static std::vector<std::vector<carve::geom2d::P2>> GeomUtils::correctWinding(
					const std::vector<std::vector<carve::geom::vector<2>>> & face_loops_input, 
					carve::geom::vector<3>& normal_first_loop);

				/**********************************************************************************************/
				/*! \brief ???
				*
				* \param[in] eye					???
				* \param[in] center					???
				* \param[in] up						??? 
				*
				* \param[out] m						???
				*/
				static void makeLookAt(const carve::geom::vector<3>& eye,
					const carve::geom::vector<3>& center,
					const carve::geom::vector<3>& up,
					carve::math::Matrix& m);

				/**********************************************************************************************/
				/*! \brief Calculates a normal of the bisecting plane.
				*
				* \param[in] v1						Coordinates of the first point.
				* \param[in] v2						Coordinates of the second point.
				* \param[in] v3						Coordinates of the third point.
				* \param[out] normal				A normal vector of the bisecting plane.
				*
				* \return							Returns true, if normal vector can be calculated. False otherwise.
				*/
				static bool bisectingPlane(const carve::geom::vector<3>& v1,
					const carve::geom::vector<3>& v2,
					const carve::geom::vector<3>& v3,
					carve::geom::vector<3>& normal);

				/**********************************************************************************************/
				/*! \brief Calculates a matrix of the plane.
				*
				* \param[in] planeNormal			A normal vector of the plane.
				* \param[in] planePosition			Global coordinates of the point positioned on the plane.
				* \param[in] localZ					A direction vector on the plane.
				*
				* \return							Returns calculated matrix of the plane.
				*/
				static carve::math::Matrix convertPlane2Matrix(const carve::geom::vector<3>& planeNormal,
					const carve::geom::vector<3>& planePosition,
					const carve::geom::vector<3>& localZ);

				/**********************************************************************************************/
				/*! \brief Applies a position to the point.
				*
				* \param[in] listOfPoint				A list of points to be converted.
				* \param[in] positionMatrix				A position matrix, which should be applied to the points.
				* \param[in] ammountOfPoints			Number of points.
				*
				* \return[out]							List of points with applied position.
				*/
				static void applyPositionToVertex(const std::vector<carve::geom::vector<3>>& listOfPoints,
					const carve::math::Matrix & positionMatrix,
					const int ammountOfPoints,
					std::vector<carve::geom::vector<3>>& newListOfPoints);

				/**********************************************************************************************/
				/*! \brief Applies a position to the point.
				*
				* \param[in] listOfPoint				A list of points to be converted.
				* \param[in] positionMatrix			A position matrix, which should be applied to the points.
				* \param[in] ammountOfPoints			Number of points.
				*
				* \return[out]							List of points with applied position.
				*/
				static std::vector<carve::geom::vector<2>> removeEmptyCoordinate
				(const std::vector<carve::geom::vector<3>>& listOfVectors3D);

				static bool checkMeshSet(const carve::mesh::MeshSet<3>* mesh_set,
					std::stringstream& err_poly, int entity_id);

			};
		}
	}
}

#endif
