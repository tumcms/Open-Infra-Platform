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

#include "Octree.h"
#include <ccPointCloud.h>

OpenInfraPlatform::Infrastructure::Octree::Octree(CCLib::GenericIndexedCloudPersist * cloud) : CCLib::DgmOctree(cloud)
{
}

CCLib::DgmOctree::CellCode OpenInfraPlatform::Infrastructure::Octree::getTruncatedCellCode(const Tuple3i & cellPos, const unsigned char level)
{	
	return GenerateTruncatedCellCode(cellPos, level);
}

std::vector<Tuple3i> OpenInfraPlatform::Infrastructure::Octree::getNeighborCellPositionsAround(const Tuple3i & cellPos, int neighbourhoodLength, unsigned char level) const
{
	auto positions = std::vector<Tuple3i>();
	CCLib::DgmOctree::cellIndexesContainer indices = CCLib::DgmOctree::cellIndexesContainer();
	getNeighborCellsAround(cellPos, indices, neighbourhoodLength, level);
	

	for(auto idx : indices) {
		Tuple3i pos = Tuple3i();
		getCellPos(getCellCode(idx), level, pos, false);
		positions.push_back(pos);
	}

	return positions;
}



