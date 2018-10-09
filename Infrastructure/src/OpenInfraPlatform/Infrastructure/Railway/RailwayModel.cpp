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

#include "RailwayModel.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/Infrastructure/Railway/RailwayPointCloud.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

RailwayModel::~RailwayModel()
{
	// Safe delete point cloud and set to nullptr.
	buw::safeDelete(pointCloud_.get());
	pointCloud_ = nullptr;

	// Safe delete alignment model and set to nullptr.
	buw::safeDelete(alignmentModel_.get());
	alignmentModel_ = nullptr;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END