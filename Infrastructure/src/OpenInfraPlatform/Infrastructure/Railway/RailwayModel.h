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
#ifndef OpenInfraPlatform_Infrastructure_RailwayModel_d64e83bc_9dcb_408b_bba4_09e856a9a68a_h
#define OpenInfraPlatform_Infrastructure_RailwayModel_d64e83bc_9dcb_408b_bba4_09e856a9a68a_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"

#include <BlueFramework/Core/memory.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

// Forward declarations for pointer to PointCloud and pointer to AlignmentModel.
class RailwayPointCloud;
class AlignmentModel;

class BLUEINFRASTRUCTURE_API RailwayModel {
public:
	RailwayModel() = default;

	virtual ~RailwayModel();

private:
	buw::ReferenceCounted<RailwayPointCloud> pointCloud_ = nullptr;

	buw::ReferenceCounted<AlignmentModel> alignmentModel_ = nullptr;

};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::RailwayModel;
}


#endif // end define OpenInfraPlatform_Infrastructure_RailwayModel_d64e83bc_9dcb_408b_bba4_09e856a9a68a_h
