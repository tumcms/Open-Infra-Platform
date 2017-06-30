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
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <utility>
#include <sstream>

#include "CarveHeaders.h"

#include "GeometrySettings.h"
#include "ProfileConverter.h"

#include "GeomUtils.h"

using namespace OpenInfraPlatform::IfcGeometryConverter;


/**********************************************************************************************/

carve::geom::vector<3> GeomUtils::computePolygonCentroid( 
										const std::vector<carve::geom::vector<3> >& polygon )
{
	carve::geom::vector<3> polygon_centroid( carve::geom::VECTOR(0, 0, 0) );
	for( std::vector<carve::geom::vector<3> >::const_iterator it = polygon.begin(); 
		 it != polygon.end(); ++it )
	{
		const carve::geom::vector<3>& vertex_current = (*it);
		polygon_centroid += vertex_current;
	}
	polygon_centroid /= double(polygon.size());
	return polygon_centroid;
}


/**********************************************************************************************/

carve::geom::vector<3> GeomUtils::computePolygonNormal( 
										const std::vector<carve::geom::vector<3> >& polygon )
{
	carve::geom::vector<3> polygon_normal( carve::geom::VECTOR(0, 0, 0) );
	bool last_loop = false;

	for( std::vector<carve::geom::vector<3> >::const_iterator it = polygon.begin(); ;  )
	{
		const carve::geom::vector<3>& vertex_current = (*it);
		++it;
		if( it == polygon.end() )
		{
			it = polygon.begin();
			last_loop = true;
		}
		const carve::geom::vector<3>& vertex_next = (*it);

		// Newell's method http://www.opengl.org/wiki/Calculating_a_Surface_Normal
		polygon_normal[0] += 
					(vertex_current.y - vertex_next.y) * (vertex_current.z + vertex_next.z);
		polygon_normal[1] += 
					(vertex_current.z - vertex_next.z) * (vertex_current.x + vertex_next.x);
		polygon_normal[2] += 
					(vertex_current.x - vertex_next.x) * (vertex_current.y + vertex_next.y);
		
		if( last_loop ) {
			break;
		}
	}
	polygon_normal.normalize();
	return polygon_normal;
}

/**********************************************************************************************/

carve::geom::vector<3> GeomUtils::computePolygon2DNormal( 
										const std::vector<carve::geom::vector<2> >& polygon )
{
	const int num_points = polygon.size();
	carve::geom::vector<3> polygon_normal( carve::geom::VECTOR(0, 0, 0) );

	for( int k=0; k<num_points; ++k )
	{
		const carve::geom::vector<2>& vertex_current = polygon.at(k);
		const carve::geom::vector<2>& vertex_next = polygon.at((k+1)%num_points);
		
		polygon_normal[2] += 
			(vertex_current.x - vertex_next.x) * (vertex_current.y + vertex_next.y );
	}

	polygon_normal.normalize();
	return polygon_normal;
}

/**********************************************************************************************/

void GeomUtils::extrude( 
					const std::vector<std::vector<carve::geom::vector<2> > >& face_loops_input, 
					const carve::geom::vector<3> extrusion_vector, 
					std::shared_ptr<carve::input::PolyhedronData>& poly_data, 
					std::stringstream& err )
{
	if( face_loops_input.size() == 0 )
	{
		std::cout << "extrude: face_loops_input.size() == 0" << std::endl;
		return;
	}
	if( poly_data->points.size() > 0 )
	{
		std::cout << "extrude: points vec should be empty" << std::endl;
		return;
	}
	if( poly_data->getFaceCount() > 0 )
	{
		std::cout << "extrude: PolyhedronData::faceCount should be 0" << std::endl;
		return;
	}

	// figure 1: loops and indexes
	//  3----------------------------2
	//  |                            |
	//  |   1-------------------2    |3---------2
	//  |   |                   |    |          |
	//  |   |                   |    |          |face_loops[2]   // TODO: handle combined profiles
	//  |   0---face_loops[1]---3    |0---------1
	//  |                            |
	//  0-------face_loops[0]--------1

	carve::geom::vector<3> normal_first_loop;
	std::vector<std::vector<carve::geom2d::P2> >	face_loops;
	for( std::vector<std::vector<carve::geom::vector<2> > >::const_iterator it_face_loops = face_loops_input.begin(); it_face_loops != face_loops_input.end(); ++it_face_loops )
	{
		const std::vector<carve::geom::vector<2> >& loop = (*it_face_loops);

		if( loop.size() < 3 )
		{
			err << "loop.size() < 3" << std::endl;
			if( it_face_loops == face_loops_input.begin() )
			{
				break;
			}
			else
			{
				continue;
			}
		}

		// check winding order
		bool reverse_loop = false;
		std::vector<carve::geom2d::P2> loop_2d( loop );
		carve::geom::vector<3>  normal_2d = computePolygon2DNormal( loop_2d );
		if( it_face_loops == face_loops_input.begin() )
		{
			normal_first_loop = normal_2d;
			if( normal_2d.z < 0 )
			{
				reverse_loop = true;
				normal_first_loop = -normal_first_loop;
			}
		}
		else
		{
			if( normal_2d.z > 0 )
			{
				reverse_loop = true;
			}
		}
		if( reverse_loop )
		{
			std::reverse( loop_2d.begin(), loop_2d.end() );
		}
				
		if( loop_2d.size() < 3 )
		{
			err << "extrude: loop_2d.size() < 3" << std::endl;
		}
		
		// close loop, insert first point at end if not already there
//		while( loop_2d.size() > 2 )
		{
			carve::geom::vector<2> first = loop_2d.front();
			carve::geom::vector<2>& last = loop_2d.back();

			if( abs(first.x-last.x) > 0.00001 || abs(first.y-last.y) > 0.00001 )
			{
				loop_2d.push_back( first );
			}
		}

		face_loops.push_back(loop_2d);
	}

	bool flip_faces = false;
	double extrusion_dot_normal = dot( extrusion_vector, normal_first_loop );
	if( extrusion_dot_normal > 0 )
	{
		flip_faces = true;
	}

	// triangulate
	std::vector<carve::geom2d::P2> merged_path;
	std::vector<carve::triangulate::tri_idx> triangulated;
	std::vector<std::pair<size_t, size_t> > path_all_loops;
	try
	{
		path_all_loops = carve::triangulate::incorporateHolesIntoPolygon(face_loops);
		// figure 2: path wich incorporates holes, described by path_all_loops
		// (0/0) -> (1/3) -> (1/0) -> (1/1) -> (1/2) -> (1/3) -> (0/0) -> (0/1) -> (0/2) -> (0/3)
		//  0/3<-----------------------0/2
		//  |                            ^
		//  |   1/0-------------->1/1    |
		//  |   ^                   |    |
		//  |   |                   v    |
		//  |   1/3<--------------1/2    |
		//  v                            |
		//  0/0------------------------>0/1

		merged_path.reserve(path_all_loops.size());
		for( size_t i = 0; i < path_all_loops.size(); ++i )
		{
			int loop_number = path_all_loops[i].first;
			int index_in_loop = path_all_loops[i].second;
			
			if( loop_number >= face_loops.size() )
			{
				err << "extrude: loop_number >= face_loops_projected.size()" << std::endl;
				continue;
			}
			std::vector<carve::geom2d::P2>& loop = face_loops[loop_number];
			carve::geom2d::P2& point_projected = loop[index_in_loop];
			merged_path.push_back( point_projected );

		}
		// figure 3: merged path for triangulation
		//  9<---------------------------8
		//  |                            ^
		//  |   2------------------>3    |
		//  |   ^                   |    |
		//  |   |                   v    |
		//  |   1, 5<---------------4    |
		//  | /                          |
		//  0,6------------------------->7
		carve::triangulate::triangulate(merged_path, triangulated);
		carve::triangulate::improve(merged_path, triangulated);
		// triangles: (9,0,1)  (5,6,7)  (4,5,7)  (4,7,8)  (9,1,2)  (8,9,2)  (3,4,8)  (2,3,8)
	}
	catch(...)
	{
		err << "carve::triangulate::incorporateHolesIntoPolygon failed " << std::endl;
		return;
	}

	// now insert points to polygon, avoiding points with same coordinates
	std::map<double, std::map<double, int> > existing_vertices_coords;
	std::map<double, std::map<double, int> >::iterator vert_it;
	std::map<double, int>::iterator it_find_y;

	std::map<int,int> map_merged_idx;
	for( size_t i = 0; i != merged_path.size(); ++i )
	{
		const carve::geom::vector<2>&  v = merged_path[i];
		
#ifdef ROUND_IFC_COORDINATES
		const double vertex_x = round(v.x*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
		const double vertex_y = round(v.y*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
#else
		const double vertex_x = v.x;
		const double vertex_y = v.y;
#endif

		//  return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
		vert_it = existing_vertices_coords.insert( std::make_pair(vertex_x, std::map<double,int>() ) ).first;
		std::map<double, int>& map_y_index = vert_it->second;

		it_find_y = map_y_index.find( vertex_y );
		if( it_find_y != map_y_index.end() )
		{
			// vertex already exists in polygon. remember its index for triangles
			map_merged_idx[i] = it_find_y->second;
			continue;
		}

		carve::geom::vector<3>  vertex3D( carve::geom::VECTOR( v.x, v.y, 0 ) );
		int vertex_id = poly_data->addVertex(vertex3D);
		map_y_index[vertex_y] = vertex_id;  // TODO: it works for now, but check if we have to round here. maybe use checksum of rounded x and y as a single map key
		map_merged_idx[i] = vertex_id;
	}

	// figure 4: points in poly_data (merged path without duplicate vertices):
	//  7<---------------------------6
	//  |                            ^
	//  |   2------------------>3    |
	//  |   ^                   |    |     map_merged_idx: figure 3 -> figure 4
	//  |   |                   v    |
	//  |   1<------------------4    |
	//  | /                          |
	//  0--------------------------->5

	// copy points from base to top
	std::vector<carve::geom::vector<3> >& points = poly_data->points;
	const int num_points_base = points.size();
	for( int i=0; i<num_points_base; ++i )
	{
		carve::geom::vector<3>& pt = points[i];
		poly_data->addVertex( pt + extrusion_vector );
	}

	// collect vertex indexes of loops
	std::map<int, std::vector<int> > loop_vert_idx;
	for( size_t merged_idx = 0; merged_idx < path_all_loops.size(); ++merged_idx )
	{
		int loop_number = path_all_loops[merged_idx].first;
		int point_idx_merged = map_merged_idx[merged_idx];
	
		std::map<int, std::vector<int> >::iterator it_result_loops = loop_vert_idx.insert( std::make_pair( loop_number, std::vector<int>() ) ).first;
		std::vector<int>& result_loop_vec = it_result_loops->second;
		
		// check if point index is already in loop
		bool already_in_loop = false;
		for( int i2 = 0; i2 < result_loop_vec.size(); ++i2 )
		{
			if( point_idx_merged == result_loop_vec[i2] )
			{
				already_in_loop = true;
				break;
			}
		}
		if( !already_in_loop )
		{
			result_loop_vec.push_back( point_idx_merged );
		}
	}

	// add faces along outer and inner loops
	for( std::map<int, std::vector<int> >::iterator it_result_loop = loop_vert_idx.begin(); it_result_loop != loop_vert_idx.end(); ++it_result_loop )
	{
		const std::vector<int>& loop_idx = it_result_loop->second;
		const int num_points_in_loop = loop_idx.size();
		
		for( int i=0; i<num_points_in_loop; ++i )
		{
			int point_idx		= loop_idx[i];
			int point_idx_next	= loop_idx[(i+1)%num_points_in_loop];
			int point_idx_up = point_idx + num_points_base;
			int point_idx_next_up = point_idx_next + num_points_base;

			if( point_idx_next_up >= 2*num_points_base )
			{
				std::cout << "point_idx_next_up >= 2*num_points_base" << std::endl;
				continue;
			}
			if( flip_faces )
			{
				poly_data->addFace( point_idx, point_idx_next, point_idx_next_up );
				poly_data->addFace( point_idx_next_up, point_idx_up, point_idx );
			}
			else
			{
				poly_data->addFace( point_idx, point_idx_up, point_idx_next_up );
				poly_data->addFace( point_idx_next_up, point_idx_next, point_idx );
			}
		}
	}

	// now the triangulated bottom and top cap
	for( size_t i = 0; i != triangulated.size(); ++i )
	{
		carve::triangulate::tri_idx triangle = triangulated[i];
		int a = triangle.a;
		int b = triangle.b;
		int c = triangle.c;

		int vertex_id_a = map_merged_idx[a];
		int vertex_id_b = map_merged_idx[b];
		int vertex_id_c = map_merged_idx[c];

		if( vertex_id_a == vertex_id_b || vertex_id_a == vertex_id_c || vertex_id_b == vertex_id_c )
		{
			continue;
		}

		int vertex_id_a_top = vertex_id_a + num_points_base;
		int vertex_id_b_top = vertex_id_b + num_points_base;
		int vertex_id_c_top = vertex_id_c + num_points_base;

#ifdef _DEBUG
		const carve::poly::Vertex<3>& v_a = poly_data->getVertex(vertex_id_a);
		const carve::poly::Vertex<3>& v_b = poly_data->getVertex(vertex_id_b);
		const carve::poly::Vertex<3>& v_c = poly_data->getVertex(vertex_id_c);

		carve::geom::vector<3> pa( carve::geom::VECTOR( v_a.v[0],	v_a.v[1],	v_a.v[2] ) );
		carve::geom::vector<3> pb( carve::geom::VECTOR( v_b.v[0],	v_b.v[1],	v_b.v[2] ) );
		carve::geom::vector<3> pc( carve::geom::VECTOR( v_c.v[0],	v_c.v[1],	v_c.v[2] ) );

		double A = 0.5*(cross( pa-pb, pa-pc ).length());
		if( abs(A) < 0.000000001 )
		{
			std::cout << "area < 0.000000001\n" << std::endl;
		}
#endif

		if( flip_faces )
		{
			// bottom cap
			poly_data->addFace( vertex_id_a,		vertex_id_c,		vertex_id_b );		
			// top cap, flipped outward
			poly_data->addFace( vertex_id_a_top,	vertex_id_b_top,	vertex_id_c_top );	
		}
		else
		{
			// bottom cap
			poly_data->addFace( vertex_id_a,		vertex_id_b,		vertex_id_c );	
			// top cap, flipped outward
			poly_data->addFace( vertex_id_a_top,	vertex_id_c_top,	vertex_id_b_top );	
		}
	}
}

/**********************************************************************************************/

void GeomUtils::computeInverse( const carve::math::Matrix& matrix_a, carve::math::Matrix& inv ) 
{
	int i, j;	// col, row
	int s;		// step
	int prow;	// pivot
	int err_flag = 0;
	double factor;
	const double eps = 0.01;
	double max;
	int pivot = 1;
	double a[4][8];

	a[0][0] = matrix_a._11;
	a[0][1] = matrix_a._12;
	a[0][2] = matrix_a._13;
	a[0][3] = matrix_a._14;

	a[1][0] = matrix_a._21;
	a[1][1] = matrix_a._22;
	a[1][2] = matrix_a._23;
	a[1][3] = matrix_a._24;

	a[2][0] = matrix_a._31;
	a[2][1] = matrix_a._32;
	a[2][2] = matrix_a._33;
	a[2][3] = matrix_a._34;

	a[3][0] = matrix_a._41;
	a[3][1] = matrix_a._42;
	a[3][2] = matrix_a._43;
	a[3][3] = matrix_a._44;

	// append identity at the right
	for( i = 0; i < 4; ++i )
	{
		for( j = 0; j < 4; ++j )
		{
			a[i][4+j] = 0.0;
			if( i == j )
			{
				a[i][4+j] = 1.0;
			}
		}
	}

	s = 0;
	do
	{
		max = fabs(a[s][s]);
		if( pivot )
		{
			prow = s;
			for( i = s+1; i < 4; ++i )
			{
				if( fabs(a[i][s]) > max)
				{
					max = fabs(a[i][s]);
					prow = i;
				}
			}
		}
		err_flag = max < eps;

		if( err_flag ) break;

		if( pivot )
		{
			if( prow != s )
			{
				// change rows
				double temp;
				for( j = s ; j < 2*4; ++j )
				{
					temp = a[s][j];
					a[s][j] = a[prow][j];
					a[prow][j]= temp;
				}
			}
		}

		// elimination: divide by pivot coefficient f = a[s][s]
		factor = a[s][s];
		for( j = s; j < 2*4; ++j )
		{
			a[s][j] = a[s][j] / factor;
		}

		for( i = 0; i < 4; ++i )
		{
			if( i != s )
			{
				factor = -a[i][s];
				for( j = s; j < 2*4 ; ++j )
				{
					a[i][j] += factor*a[s][j];
				}
			}
		}
		++s;
	}
	while( s < 4 ) ;

	if( err_flag )
	{
		std::stringstream ss;
		ss << "cannot compute inverse of matrix " << __FUNCTION__;
		throw GeomException(ss.str());
	}
	
	inv._11 = a[0][4];
	inv._12 = a[0][5];
	inv._13 = a[0][6];
	inv._14 = a[0][7];
	
	inv._21 = a[1][4];
	inv._22 = a[1][5];
	inv._23 = a[1][6];
	inv._24 = a[1][7];

	inv._31 = a[2][4];
	inv._32 = a[2][5];
	inv._33 = a[2][6];
	inv._34 = a[2][7];

	inv._41 = a[3][4];
	inv._42 = a[3][5];
	inv._43 = a[3][6];
	inv._44 = a[3][7];
}

/**********************************************************************************************/

void GeomUtils::closestPointOnLine( const carve::geom::vector<3>& point, const 
								   carve::geom::vector<3>& line_origin, const 
								   carve::geom::vector<3>& line_direction, 
								   carve::geom::vector<3>& closest )
{
	double denom = point.x*line_direction.x + point.y*line_direction.y + point.z*line_direction.z - line_direction.x*line_origin.x - line_direction.y*line_origin.y - line_direction.z*line_origin.z;
	double numer = line_direction.x*line_direction.x + line_direction.y*line_direction.y + line_direction.z*line_direction.z;
	if(numer == 0)
	{
		std::stringstream ss;
		ss << "Line is degenerated: the line's direction vector is a null vector! " 
			<< __FUNCTION__;
		throw GeomException(ss.str());
	}
	double lambda = denom/numer;
	closest = carve::geom::VECTOR(line_origin.x+lambda*line_direction.x, line_origin.y+lambda*line_direction.y, line_origin.z+lambda*line_direction.z);
}

/**********************************************************************************************/


void GeomUtils::closestPointOnLine( const buw::Vector3f& point, 
								   const buw::Vector3f& line_origin, 
								   const buw::Vector3f& line_direction, 
								   buw::Vector3f& closest )
{
	double denom = point.x()*line_direction.x() + point.y()*line_direction.y() + point.z()*line_direction.z() - line_direction.x()*line_origin.x() - line_direction.y()*line_origin.y() - line_direction.z()*line_origin.z();
	double numer = line_direction.x()*line_direction.x() + line_direction.y()*line_direction.y() + line_direction.z()*line_direction.z();
	if(numer == 0)
	{
		std::stringstream ss;
		ss << "Line is degenerated: the line's direction vector is a null vector! " 
			<< __FUNCTION__;
		throw GeomException(ss.str());
	}
	double lambda = denom/numer;
	closest = buw::Vector3f(line_origin.x()+lambda*line_direction.x(), line_origin.y()+lambda*line_direction.y(), line_origin.z()+lambda*line_direction.z());
}

/**********************************************************************************************/

//void closestPointOnLineSegment( osg::Vec3d& closest, osg::Vec3d& point, osg::Vec3d& line_origin, osg::Vec3d& line_end )

bool GeomUtils::isPointOnLineSegment( double& target_lambda, 
									 const buw::Vector3f& point, 
									 const buw::Vector3f& line_origin, 
									 const buw::Vector3f& line_end )
{
	const buw::Vector3f line_direction = line_end - line_origin;
	const double denom = point.x()*line_direction.x() + point.y()*line_direction.y() + point.z()*line_direction.z() - line_direction.x()*line_origin.x() - line_direction.y()*line_origin.y() - line_direction.z()*line_origin.z();
	const double numer = line_direction.x()*line_direction.x() + line_direction.y()*line_direction.y() + line_direction.z()*line_direction.z();
	if(numer == 0)
	{
		std::stringstream ss;
		ss << "Line is degenerated: the line's direction vector is a null vector! " 
			<< __FUNCTION__;
		throw GeomException(ss.str());
	}
	const double lambda = denom/numer;
	buw::Vector3f closest( line_origin.x()+lambda*line_direction.x(), line_origin.y()+lambda*line_direction.y(), line_origin.z()+lambda*line_direction.z() );
	const double length2 = (closest-point).norm() * (closest-point).norm();
	if(  length2 > 0.0001 )
	{
		// point is not on line
		return false;
	}
	if( lambda < -0.0001 )
	{
		// point is not on line
		return false;
	}
	if( lambda > 1.0001 )
	{
		// point is not on line
		return false;
	}
	target_lambda = lambda;
	return true;
}

/**********************************************************************************************/

bool LineToLineIntersectionHelper(carve::geom::vector<2>& v1, 
								  carve::geom::vector<2>& v2, 
								  carve::geom::vector<2>& v3, 
								  carve::geom::vector<2>& v4, double & r, double & s)
{
	// check if lines are parallel
	const carve::geom::vector<2> vertex1to2 = v2 - v1;
	const carve::geom::vector<2> vertex3to4 = v4 - v3;
	if( vertex1to2.y / vertex1to2.x != vertex3to4.y / vertex3to4.x )
	{
		const double d = vertex1to2.x*vertex3to4.y - vertex1to2.y*vertex3to4.x;
		if( d != 0 )
		{
			const carve::geom::vector<2> vertex3to1 = v1 - v3;
			r = (vertex3to1.y*vertex3to4.x - vertex3to1.x*vertex3to4.y) / d;
			s = (vertex3to1.y*vertex1to2.x - vertex3to1.x*vertex1to2.y) / d;
			return true;
		}
	}
	return false;

}

/**********************************************************************************************/

bool GeomUtils::LineSegmentToLineIntersection(carve::geom::vector<2>& v1,
											  carve::geom::vector<2>& v2, 
											  carve::geom::vector<2>& v3,
											  carve::geom::vector<2>& v4,
										std::vector<carve::geom::vector<2> >& result )
{
	double r, s;
	if( LineToLineIntersectionHelper(v1, v2, v3, v4, r, s) )
	{
		if (r >= 0 && r <= 1)
		{
			result.push_back(v1 + (v2 - v1) * r);
			return true;
		}
	}
	return false;
}

/**********************************************************************************************/

bool GeomUtils::LineSegmentToLineSegmentIntersection(carve::geom::vector<2>& v1,
													 carve::geom::vector<2>& v2,
													 carve::geom::vector<2>& v3, 
													 carve::geom::vector<2>& v4, 
										std::vector<carve::geom::vector<2> >& result )
{
	double r, s;
	if( LineToLineIntersectionHelper(v1, v2, v3, v4, r, s) )
	{
		if (r >= 0 && r <= 1)
		{
			if (s >= 0 && s <= 1)
			{
				result.push_back(v1 + (v2 - v1) * r);
				return true;
			}
		}
	}
	return false;
}

/**********************************************************************************************/

void GeomUtils::appendPointsToCurve( const std::vector<carve::geom::vector<2> >& points_vec, 
									std::vector<carve::geom::vector<3> >& target_vec )
{
	// sometimes, sense agreement is not given correctly. try to correct sense of segment if necessary
	//if( target_vec.size() > 0 && points_vec.size() > 1 )
	//{
	//	carve::geom::vector<3> first_target_point = target_vec.front();
	//	carve::geom::vector<3> last_target_point = target_vec.back();

	//	carve::geom::vector<2> first_segment_point = points_vec.front();
	//	carve::geom::vector<2> last_segment_point = points_vec.back();

	//	if( (last_target_point.x - first_segment_point).length2() < 0.000001 )
	//	{
	//		// segment order is as expected, nothing to do
	//	}
	//	else
	//	{
	//		if( (last_target_point-last_segment_point).length() < 0.000001 )
	//		{
	//			// current segment seems to be in wrong order
	//			std::reverse( points_vec.begin(), points_vec.end() );
	//		}
	//		else
	//		{
	//			// maybe the current segment fits to the beginning of the target vector
	//			if( (first_target_point-first_segment_point).length() < 0.000001 )
	//			{
	//				std::reverse( target_vec.begin(), target_vec.end() );
	//			}
	//			else
	//			{
	//				if( (first_target_point-last_segment_point).length() < 0.000001 )
	//				{
	//					std::reverse( target_vec.begin(), target_vec.end() );
	//					std::reverse( points_vec.begin(), points_vec.end() );
	//				}
	//			}
	//		}
	//	}
	//}

	bool omit_first = false;
	if( target_vec.size() > 0 )
	{
		const carve::geom::vector<3>& last_point = target_vec.back();
		const carve::geom::vector<2>& first_point_current_segment = points_vec.front();
		if( abs(last_point.x - first_point_current_segment.x) < 0.000001 )
		{
			if( abs(last_point.y - first_point_current_segment.y) < 0.000001 )
			{
				omit_first = true;
			}
		}
	}

	if( omit_first )
	{
		//target_vec.insert( target_vec.end(), points_vec.begin()+1, points_vec.end() );
		for( int i=1; i<points_vec.size(); ++i )
		{
			const carve::geom::vector<2>& pt = points_vec[i];
			target_vec.push_back( carve::geom::VECTOR( pt.x, pt.y, 0 ) );
		}
	}
	else
	{
		//target_vec.insert( target_vec.end(), points_vec.begin(), points_vec.end() );
		for( int i=0; i<points_vec.size(); ++i )
		{
			const carve::geom::vector<2>& pt = points_vec[i];
			target_vec.push_back( carve::geom::VECTOR( pt.x, pt.y, 0 ) );
		}
	}
	// TODO: handle all segments separately: std::vector<std::vector<carve::geom::vector<3> > >& target_vec
}

/**********************************************************************************************/

void GeomUtils::appendPointsToCurve( const std::vector<carve::geom::vector<3> >& points_vec_src,
									std::vector<carve::geom::vector<3> >& target_vec )
{
	// sometimes, sense agreement is not given correctly. try to correct sense of segment if necessary
	std::vector<carve::geom::vector<3> > points_vec( points_vec_src );
	if( target_vec.size() > 0 && points_vec.size() > 1 )
	{
		carve::geom::vector<3> first_target_point = target_vec.front();
		carve::geom::vector<3> last_target_point = target_vec.back();

		carve::geom::vector<3> first_segment_point = points_vec.front();
		carve::geom::vector<3> last_segment_point = points_vec.back();

		if( (last_target_point-first_segment_point).length2() < 0.000001 )
		{
			// segment order is as expected, nothing to do
		}
		else
		{
			if( (last_target_point-last_segment_point).length2() < 0.000001 )
			{
				// current segment seems to be in wrong order
				std::reverse( points_vec.begin(), points_vec.end() );
			}
			else
			{
				// maybe the current segment fits to the beginning of the target vector
				if( (first_target_point-first_segment_point).length2() < 0.000001 )
				{
					std::reverse( target_vec.begin(), target_vec.end() );
				}
				else
				{
					if( (first_target_point-last_segment_point).length2() < 0.000001 )
					{
						std::reverse( target_vec.begin(), target_vec.end() );
						std::reverse( points_vec.begin(), points_vec.end() );
					}
				}
			}
		}
	}

	bool omit_first = false;
	if( target_vec.size() > 0 )
	{
		carve::geom::vector<3> last_point = target_vec.back();
		carve::geom::vector<3> first_point_current_segment = points_vec.front();
		if( (last_point-first_point_current_segment).length() < 0.000001 )
		{
			omit_first = true;
		}
	}

	if( omit_first )
	{
		target_vec.insert( target_vec.end(), points_vec.begin()+1, points_vec.end() );
	}
	else
	{
		target_vec.insert( target_vec.end(), points_vec.begin(), points_vec.end() );
	}
	// TODO: handle all segments separately: std::vector<std::vector<carve::geom::vector<3> > >& target_vec
}

/**********************************************************************************************/


void GeomUtils::makeLookAt(const carve::geom::vector<3>& eye,
						   const carve::geom::vector<3>& center,
						   const carve::geom::vector<3>& up, carve::math::Matrix& m )
{
	carve::geom::vector<3> f(center-eye);
    f.normalize();
    carve::geom::vector<3> s = cross(f,up);
    s.normalize();
    carve::geom::vector<3> u = cross(s, f);
    u.normalize();

	m._11 = s[0];
	m._12 = u[0];
	m._13 = -f[0];
	m._14 = 0.0;
	m._21 = s[1];
	m._22 = u[1];
	m._23 = -f[1];
	m._24 = 0.0;
	m._31 = s[2];
	m._32 = u[2];
	m._33 = -f[2];
	m._34 = 0.0;
	m._41 = 0.0;
	m._42 = 0.0;
	m._43 = 0.0;
	m._44 = 1.0;

	for (unsigned i = 0; i < 3; ++i)
    {
        double tmp = -eye[i];
        if (tmp == 0)
            continue;
        m.m[3][0] += tmp*m.m[i][0];
        m.m[3][1] += tmp*m.m[i][1];
        m.m[3][2] += tmp*m.m[i][2];
        m.m[3][3] += tmp*m.m[i][3];
    }
}

/**********************************************************************************************/

bool GeomUtils::bisectingPlane(const carve::geom::vector<3>& v1, 
							   const carve::geom::vector<3>& v2, 
					const carve::geom::vector<3>& v3, carve::geom::vector<3>& normal )
{
	bool valid = false;
	carve::geom::vector<3> v21 = v2 - v1;
	carve::geom::vector<3> v32 = v3 - v2;
	double len21 = v21.length();
	double len32 = v32.length();

	if( len21 <= GEOM_TOLERANCE * len32)
	{
		if( len32 == 0.0)
		{
			// all three points lie ontop of one-another
			normal = carve::geom::VECTOR( 0.0, 0.0, 0.0 );
			valid = false;
		}
		else
		{
			// return a normalized copy of v32 as bisector
			len32 = 1.0 / len32;
			normal = v32*len32;
			normal.normalize();
			valid = true;
		}

	}
	else
	{
		valid = true;
		if( len32 <= GEOM_TOLERANCE * len21)
		{
			// return v21 as bisector
			v21.normalize();
			normal = v21;
		}
		else
		{
			v21.normalize();
			v32.normalize();

			double dot_product = dot( v32, v21 );
			double dot_product_abs = abs( dot_product );

			if( dot_product_abs > (1.0+GEOM_TOLERANCE) || dot_product_abs < (1.0-GEOM_TOLERANCE) )
			{
				normal = (v32 + v21)*dot_product - v32 - v21;
				normal.normalize();
			}
			else
			{
				// dot == 1 or -1, points are colinear
				normal = -v21;
			}
		}
	}
	return valid;
}

/**********************************************************************************************/

void GeomUtils::convertPlane2Matrix( const carve::geom::vector<3>& plane_normal, 
									const carve::geom::vector<3>& plane_position, 
		const carve::geom::vector<3>& local_z, carve::math::Matrix& resulting_matrix )
{
	carve::geom::vector<3> local_x( plane_normal );
	local_x.normalize();
	carve::geom::vector<3> local_z_new( local_z );

	carve::geom::vector<3> local_y = cross( local_x, local_z_new );
	local_z_new = cross( local_y, local_x );
	local_z_new.normalize();
	local_y.normalize();

	resulting_matrix._11 = local_x.x;
	resulting_matrix._12 = local_x.y;
	resulting_matrix._13 = local_x.z,
	resulting_matrix._14 = 0;
	resulting_matrix._21 = local_y.x;
	resulting_matrix._22 = local_y.y;
	resulting_matrix._23 =	local_y.z;
	resulting_matrix._24 =	0;
	resulting_matrix._31 = local_z_new.x;
	resulting_matrix._32 = local_z_new.y;
	resulting_matrix._33 = local_z_new.z;
	resulting_matrix._34 = 0;
	resulting_matrix._41 = plane_position.x;
	resulting_matrix._42 = plane_position.y;
	resulting_matrix._43 = plane_position.z;
	resulting_matrix._44 = 1;
}

/**********************************************************************************************/


bool GeomUtils::checkMeshSet( const carve::mesh::MeshSet<3>* mesh_set, 
							 std::stringstream& err_poly, int entity_id )
{
	// check opening polyhedron
	if( !mesh_set )
	{
#ifdef _DEBUG
		if (entity_id == -1) 
			err_poly << "MeshSet of resulting mesh not valid" << std::endl;
		else 
			err_poly << "MeshSet of entity #" << entity_id << " not valid" << std::endl;
#endif
		return false;
	}
	if( mesh_set->meshes.size() == 0 )
	{
#ifdef _DEBUG
		if (entity_id == -1) 
			err_poly << "MeshSet of resulting mesh is empty" << std::endl;
		else
			err_poly << "MeshSet of entity #" << entity_id << " has no meshes" << std::endl;
#endif
		return false;
	}

	std::stringstream err;
	bool meshes_closed = true;
	for (size_t i = 0; i < mesh_set->meshes.size(); ++i)
	{
		carve::mesh::Mesh<3>* mesh_i = mesh_set->meshes[i];

		if( mesh_i->isNegative() )
		{
			mesh_i->invert();
			if( mesh_i->isNegative() )
			{
				mesh_i->recalc();
				mesh_i->calcOrientation();
				if( mesh_i->isNegative() )
				{
					err << "mesh_set->meshes[" << i << "]->isNegative() " << std::endl;
				}
			}
		}

		if( !mesh_i->isClosed() && entity_id != -1)
		{
			meshes_closed = false;
		}



		
		//for( int j=0; j<vec_faces.size(); ++j )
		//{
		//	carve::mesh::Face<3>* face = vec_faces[j];

		//	carve::mesh::Edge<3>* edge = face->edge;
		//	do
		//	{
		//		double length2 = (edge->v2()->v - edge->v1()->v).length2();
		//		if( length2 < 0.0000001 )
		//		{
		//			//carve::mesh::Edge<3>* edge_back = edge->prev;
		//			edge = edge->removeEdge();
		//			continue;
		//			// start over
		//			//edge = face->edge;
		//			//
		//		}
		//		edge = edge->next;
		//	} while (edge != face->edge);
		//}

		//mesh_i->cacheEdges();


#ifdef THOROUGH_MESHSET_CHECK

		std::vector<carve::mesh::Face<3>* >& vec_faces = mesh_i->faces;
		for( int j=0; j<vec_faces.size(); ++j )
		{
			carve::mesh::Face<3>* face = vec_faces[j];

			// TODO: if quad, check if it is flat

			carve::geom::vector<3>& face_normal = face->plane.N;
			//carve::geom::vector<3>& face_centroid = face->centroid;
			carve::geom::vector<3>& point_on_face = face->edge->v1()->v;
			carve::geom::linesegment<3> face_linesegment( point_on_face, point_on_face + face_normal*10000 );
			int intersect_face_count = 0;
			int intersect_vertex_count = 0;
			int intersect_edge_count = 0;

			for( int j_other=0; j_other<vec_faces.size(); ++j_other )
			{
				if( j == j_other )
				{
					// don't intersect face with itself
					continue;
				}
				carve::mesh::Face<3>* other_face = vec_faces[j_other];

				carve::geom::vector<3> intersection_point;
				carve::IntersectionClass intersection_result = other_face->lineSegmentIntersection( face_linesegment, intersection_point );

				double intersection_distance = DBL_MAX;

				if( intersection_result > 0 )
				{
					if( intersection_result == carve::INTERSECT_FACE )
					{
						++intersect_face_count;
					}
					else if( intersection_result == carve::INTERSECT_VERTEX )
					{
						++intersect_vertex_count;
					}
					else if( intersection_result == carve::INTERSECT_EDGE )
					{
						++intersect_edge_count;
					}
				}
			}
			if( intersect_face_count > 0 )
			{
				if( intersect_face_count%2 == 1 )
				{
					if( intersect_vertex_count == 0 )
					{
						err_poly << "face normal pointing inside" << std::endl;
						return false;
					}
				}
			}
		}
#endif
	}

	if( !meshes_closed )
	{
		err << "mesh_set not closed" << std::endl;
	}

#ifdef _DEBUG
	if( meshes_closed )
	{
		// check volume
		double object_volume = 0;
		for( size_t kk = 0; kk < mesh_set->meshes.size(); ++kk )
		{
			carve::mesh::Mesh<3>* mesh = mesh_set->meshes[kk];
			double mesh_volume = mesh->volume();
			object_volume += mesh_volume;
		}
		if (object_volume <= 0 && entity_id != -1)
		{
			err << "object_volume <= 0" << std::endl;
		}
	}
#endif

	if( err.tellp() > 0 )
	{
#ifdef _DEBUG
		if (entity_id == -1) {
			err_poly << "MeshSet of resulting mesh has problems:" << std::endl;
			err_poly << err.str().c_str();
		} else  {
			err_poly << "MeshSet of entity #" << entity_id << " has problems:" << std::endl;
			err_poly << err.str().c_str();
		}
		
#endif
		return false;
	}
	return true;
}

/**********************************************************************************************/
