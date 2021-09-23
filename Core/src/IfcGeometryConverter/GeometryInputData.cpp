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

#include "GeometryInputData.h"

#include <limits>

using namespace OpenInfraPlatform::Core::IfcGeometryConverter;

/**********************************************************************************************/

void ItemData::createMeshSetsFrom(std::vector<std::shared_ptr<carve::input::PolyhedronData>>& polyhedrons)
{
	for( auto& poly_data : polyhedrons )
	{
		if( poly_data->getVertexCount() < 3 )
		{
			continue;
		}

		std::shared_ptr<carve::mesh::MeshSet<3>> meshset(
												poly_data->createMesh(carve::input::opts()) );
		
		meshsets.push_back( meshset );

	}

	polyhedrons.clear();
}
