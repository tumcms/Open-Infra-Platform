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

#pragma once
#ifndef GEOMETRYINPUTDATA_H
#define GEOMETRYINPUTDATA_H

#include <vector>
#include <array>
#include <memory>

#include "CarveHeaders.h"

/**********************************************************************************************/

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{

		//\brief Class to hold input data of one IFC geometric representation item.
		class ItemData
		{
		public:
			std::vector<std::shared_ptr<carve::input::PolyhedronData>>	closed_polyhedrons;
			std::vector<std::shared_ptr<carve::input::PolyhedronData>>	open_polyhedrons;
			std::vector<std::shared_ptr<carve::input::PolyhedronData>>	open_or_closed_polyhedrons;
			std::vector<std::shared_ptr<carve::input::PolylineSetData>> polylines;
			std::vector<std::shared_ptr<carve::mesh::MeshSet<3>>>		meshsets;
			void createMeshSetsFromClosedPolyhedrons();
		};

		/**************************************************************************************/

		struct PlacementData
		{
			std::set<int> placement_already_applied;
			carve::math::Matrix pos;
		};

		/**************************************************************************************/

		template<
			class IfcEntityTypesT
		>
		class ShapeInputDataT
		{
		public:
			ShapeInputDataT()
				: added_to_storey(false)
			{ }

			~ShapeInputDataT()
			{ }

			// compute AABB from meshsets
			void computeAABB()
			{
				bool firstIteration = true;

				for (const auto& itemData : vec_item_data)
				{
					for (const auto& meshset : itemData->meshsets)
					{
						if (meshset->meshes.empty()) {
							continue;
						}

						const carve::mesh::MeshSet<3>::aabb_t& aabb = meshset->getAABB();

						if (firstIteration) {
							m_aabb = aabb;
							firstIteration = false;
						}
						else {
							m_aabb.unionAABB(aabb);
						}
					}
				}
			}

			std::shared_ptr<typename IfcEntityTypesT::IfcProduct>				ifc_product;
			std::shared_ptr<typename IfcEntityTypesT::IfcRepresentation>		representation;
			std::shared_ptr<typename IfcEntityTypesT::IfcObjectPlacement>		object_placement;
			std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProduct>>	vec_openings;

			std::vector<std::shared_ptr<ItemData>>	vec_item_data;
			bool									added_to_storey;

			carve::mesh::MeshSet<3>::aabb_t			m_aabb;
		};
	}
}

#endif
