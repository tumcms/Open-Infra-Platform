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
#include <BlueFramework/Core/Math/vector.h>

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		class GeometrySettings;

		enum ProjectionPlane
		{
			UNDEFINED,
			XY_PLANE,
			YZ_PLANE,
			XZ_PLANE
		};

		struct GeomException : public std::exception
		{
		   std::string s;
		   GeomException(std::string ss) : s(ss) {}
		   ~GeomException() throw () {} // Updated
		   const char* what() const throw() { return s.c_str(); }
		};

		class GeomUtils
		{
		public:

			static carve::geom::vector<3> computePolygonCentroid( 
										const std::vector<carve::geom::vector<3> >& polygon );
			static carve::geom::vector<3> computePolygonNormal( 
										const std::vector<carve::geom::vector<3> >& polygon );
			static carve::geom::vector<3> computePolygon2DNormal( 
										const std::vector<carve::geom::vector<2> >& polygon );

			static bool LineSegmentToLineIntersection(carve::geom::vector<2>& v1, 
														carve::geom::vector<2>& v2, 
														carve::geom::vector<2>& v3, 
														carve::geom::vector<2>& v4, 
												std::vector<carve::geom::vector<2> >& result );

			static bool LineSegmentToLineSegmentIntersection(carve::geom::vector<2>& v1, 
															carve::geom::vector<2>& v2, 
															carve::geom::vector<2>& v3, 
															carve::geom::vector<2>& v4, 
												std::vector<carve::geom::vector<2> >& result );

			static void appendPointsToCurve(
										const std::vector<carve::geom::vector<3> >& points_vec, 
										std::vector<carve::geom::vector<3> >& target_vec );
			static void appendPointsToCurve(
										const std::vector<carve::geom::vector<2> >& points_vec, 
											std::vector<carve::geom::vector<3> >& target_vec );

			static void computeInverse(	const carve::math::Matrix& matrix_a, 
										carve::math::Matrix& inv );

			static void closestPointOnLine( const carve::geom::vector<3>& point, 
											const carve::geom::vector<3>& line_origin, 
											const carve::geom::vector<3>& line_direction, 
											carve::geom::vector<3>& closest );


			static void closestPointOnLine( const buw::Vector3f& point, 
											const buw::Vector3f& line_origin, 
											const buw::Vector3f& line_direction, 
											buw::Vector3f& closest );

			static bool isPointOnLineSegment( double& lambda, 
											const buw::Vector3f& point, 
											const buw::Vector3f& line_origin, 
											const buw::Vector3f& line_direction );
	
			static void extrude(const std::vector<std::vector<carve::geom::vector<2> > >& paths, 
								const carve::geom::vector<3> dir, 
								std::shared_ptr<carve::input::PolyhedronData>& poly_data, 
								std::stringstream& err );

			static void makeLookAt(	const carve::geom::vector<3>& eye,
									const carve::geom::vector<3>& center,
									const carve::geom::vector<3>& up, 
									carve::math::Matrix& m );

			static bool bisectingPlane( const carve::geom::vector<3>& v1, 
										const carve::geom::vector<3>& v2, 
										const carve::geom::vector<3>& v3, 
										carve::geom::vector<3>& normal );

			static void convertPlane2Matrix(	const carve::geom::vector<3>& plane_normal, 
												const carve::geom::vector<3>& plane_position, 
												const carve::geom::vector<3>& local_z, 
												carve::math::Matrix& resulting_matrix );

			static bool checkMeshSet( const carve::mesh::MeshSet<3>* mesh_set, 
										std::stringstream& err_poly, int entity_id );
	
		};
	}
}

#endif
