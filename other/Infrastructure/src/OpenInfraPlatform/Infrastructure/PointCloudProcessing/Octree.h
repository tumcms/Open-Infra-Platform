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
#ifndef OpenInfraPlatform_Infrastructure_PointCloudProcessing_Octree_A4497380_8447_40E1_9366_D2DDE1F2D7FE_h
#define OpenInfraPlatform_Infrastructure_PointCloudProcessing_Octree_A4497380_8447_40E1_9366_D2DDE1F2D7FE_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"

#include <DgmOctree.h>

namespace OpenInfraPlatform {
	namespace Infrastructure {
		class BLUEINFRASTRUCTURE_API Octree : public CCLib::DgmOctree {
		public:
			Octree() = default;

			Octree(CCLib::GenericIndexedCloudPersist* cloud);

			~Octree() {}

			CCLib::DgmOctree::CellCode getTruncatedCellCode(const Tuple3i &cellPos, const unsigned char level);

			std::vector<Tuple3i> getNeighborCellPositionsAround(const Tuple3i& cellPos, int neighbourhoodLength, unsigned char level) const;
		};
	}
}

namespace buw {
	using OpenInfraPlatform::Infrastructure::Octree;
}

#endif