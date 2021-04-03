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

#pragma once
#ifndef GEOMETRYINPUTDATA_H
#define GEOMETRYINPUTDATA_H

#include <vector>
#include <array>
#include <memory>

#include "CarveHeaders.h"
#include "namespace.h"
#include "EXPRESS/EXPRESS.h"

/**********************************************************************************************/
OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN


//! \brief Class to hold input data of one IFC geometric representation item.
class ItemData {
public:
	std::vector<std::shared_ptr<carve::input::PolyhedronData>>	closed_polyhedrons;
	std::vector<std::shared_ptr<carve::input::PolyhedronData>>	open_polyhedrons;
	std::vector<std::shared_ptr<carve::input::PolyhedronData>>	open_or_closed_polyhedrons;
	std::vector<std::shared_ptr<carve::input::PolylineSetData>> polylines;
	std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>		meshsets;
	void createMeshSetsFromClosedPolyhedrons();
	
	void simplifyMeshes()
	{
		bool rebuild = true;
		for( auto& meshset : meshsets )
		{
			int num_vertices = meshset->vertex_storage.size();
			if (rebuild && num_vertices > 8)
			{
				retriangulateMeshSet(meshset);
			}
		}
	}

	void retriangulateMeshSet(std::shared_ptr<carve::mesh::MeshSet<3>>& meshset)
	{
		//carve::poly::Polyhedron* poly = carve::polyhedronFromMesh(meshset, -1);
		//carve::mesh::MeshSet<3>* meshset_new = carve::meshFromPolyhedron(poly, -1);

		int num_vertices1 = meshset->vertex_storage.size();
		std::shared_ptr<carve::input::PolyhedronData> poly_data(new carve::input::PolyhedronData());
		std::map<double, std::map<double, std::map<double, int> > > existing_vertices_coords;
		std::map<double, std::map<double, std::map<double, int> > >::iterator vert_it;
		std::map<double, std::map<double, int> >::iterator it_find_y;
		std::map<double, int>::iterator it_find_z;
		std::map<int, int> map_merged_idx;
		double volume_check = 0;

		for (size_t ii = 0; ii < meshset->meshes.size(); ++ii)
		{
			carve::mesh::Mesh<3>* mesh = meshset->meshes[ii];
			volume_check += mesh->volume();
			std::vector<carve::mesh::Face<3>* >& vec_faces = mesh->faces;

			for (size_t i2 = 0; i2 < vec_faces.size(); ++i2)
			{
				carve::mesh::Face<3>* face = vec_faces[i2];
				std::vector<int> face_idx;

				carve::geom3d::Vector normal = face->plane.N;

				std::vector<carve::geom::vector<2> > verts2d;
				face->getProjectedVertices(verts2d);

				// check winding order
				//carve::geom3d::Vector normal_2d = GeomUtils::computePolygon2DNormal( verts2d );
				//if( normal_2d.z < 0 )
				//{
				//	std::reverse( verts2d.begin(), verts2d.end() );
				//}

				std::vector<carve::triangulate::tri_idx> triangulated;
				if (verts2d.size() > 3)
				{
					try
					{
						carve::triangulate::triangulate(verts2d, triangulated);
						carve::triangulate::improve(verts2d, triangulated);
					}
					catch (...)
					{
						std::cout //<< __FUNC__
							<< " carve::triangulate::incorporateHolesIntoPolygon failed " << std::endl;
						continue;
					}
				}
				else
				{
					triangulated.push_back(carve::triangulate::tri_idx(0, 1, 2));
				}

				// now insert points to polygon, avoiding points with same coordinates
				int i_vert = 0;
				carve::mesh::Edge<3>* edge = face->edge;
				do
				{
					const carve::geom::vector<3>& v = edge->vert->v;//verts3d[i]->v;
					edge = edge->next;

					//#ifdef ROUND_IFC_COORDINATES
					//							const double vertex_x = round(v.x*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
					//							const double vertex_y = round(v.y*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
					//							const double vertex_z = round(v.z*ROUND_IFC_COORDINATES_UP)*ROUND_IFC_COORDINATES_DOWN;
					//#else
					const double vertex_x = v.x;
					const double vertex_y = v.y;
					const double vertex_z = v.z;
					//#endif

												//  return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map
					vert_it = existing_vertices_coords.insert(std::make_pair(vertex_x, std::map<double, std::map<double, int> >())).first;
					std::map<double, std::map<double, int> >& map_y_index = (*vert_it).second;

					it_find_y = map_y_index.insert(std::make_pair(vertex_y, std::map<double, int>())).first;
					std::map<double, int>& map_z_index = it_find_y->second;

					it_find_z = map_z_index.find(vertex_z);
					if (it_find_z != map_z_index.end())
					{
						// vertex already exists in polygon. remember its index for triangles
						int vertex_index = it_find_z->second;
						map_merged_idx[i_vert] = vertex_index;
					}
					else
					{
						int vertex_id = poly_data->addVertex(v);
						map_z_index[vertex_z] = vertex_id;
						map_merged_idx[i_vert] = vertex_id;
					}

					++i_vert;
				} while (edge != face->edge);

				for (size_t i = 0; i != triangulated.size(); ++i)
				{
					carve::triangulate::tri_idx triangle = triangulated[i];
					int a = triangle.a;
					int b = triangle.b;
					int c = triangle.c;

					int vertex_id_a = map_merged_idx[a];
					int vertex_id_b = map_merged_idx[b];
					int vertex_id_c = map_merged_idx[c];
					/*
					#ifdef _DEBUG
					const carve::poly::Vertex<3>& v_a = poly_data->getVertex(vertex_id_a);
					const carve::poly::Vertex<3>& v_b = poly_data->getVertex(vertex_id_b);

					double dx = v_a.v[0] - v_b.v[0];
					if( abs(dx) < 0.0000001 )
					{
					double dy = v_a.v[1] - v_b.v[1];
					if( abs(dy) < 0.0000001 )
					{
					double dz = v_a.v[2] - v_b.v[2];
					if( abs(dz) < 0.0000001 )
					{
					std::cerr << "abs(dx) < 0.00001 && abs(dy) < 0.00001 && abs(dz) < 0.00001\n";
					}
					}
					}
					#endif*/
					poly_data->addFace(vertex_id_a, vertex_id_b, vertex_id_c);
				}
			}
		}

		meshset = std::shared_ptr<carve::mesh::MeshSet<3> >(poly_data->createMesh(carve::input::opts()));

		double volume_check2 = 0;
		for (size_t i = 0; i < meshset->meshes.size(); ++i)
		{
			carve::mesh::Mesh<3>* mesh = meshset->meshes[i];
			volume_check2 += mesh->volume();
		}

		/*if( abs(volume_check - volume_check2) > 0.0001 )
		{
		std::cout << __FUNC__ << " volume check failed." << std::endl;
		}

		int num_vertices2 = meshset->vertex_storage.size();
		if( num_vertices1 != num_vertices2 )
		{
		std::cout << __FUNC__ << " num vertices check failed." << std::endl;
		}*/
	}

	void append(const std::shared_ptr<ItemData>& other)
	{
		std::copy(other->closed_polyhedrons.begin(),         other->closed_polyhedrons.end(),         std::back_inserter(this->closed_polyhedrons));
		std::copy(other->open_polyhedrons.begin(),           other->open_polyhedrons.end(),           std::back_inserter(this->open_polyhedrons));
		std::copy(other->open_or_closed_polyhedrons.begin(), other->open_or_closed_polyhedrons.end(), std::back_inserter(this->open_or_closed_polyhedrons));
		std::copy(other->polylines.begin(),                  other->polylines.end(),                  std::back_inserter(this->polylines));
		std::copy(other->meshsets.begin(),                   other->meshsets.end(),                   std::back_inserter(this->meshsets));
	}
};

template<
	class IfcEntityTypesT
>
class ShapeInputDataT {
public:
	ShapeInputDataT()
	{
	}

	~ShapeInputDataT()
	{
	}

	oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>			ifc_product;
	oip::EXPRESSReference<typename IfcEntityTypesT::IfcRepresentation>	representation;
	std::vector<std::shared_ptr<ItemData>>								vec_item_data;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END


#endif
