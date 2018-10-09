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
#ifndef OpenInfraPlatform_Infrastructure_RailwayPointCloud_676ff3cf_36f7_4466_a21a_47608e9b561e_h
#define OpenInfraPlatform_Infrastructure_RailwayPointCloud_676ff3cf_36f7_4466_a21a_47608e9b561e_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"

#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloud.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API RailwayPointCloud : public PointCloud {
public:

	// Constructors.
	RailwayPointCloud() : PointCloud() {}
	RailwayPointCloud(QString name) : PointCloud(name) {}
	RailwayPointCloud(PointCloud && other) : PointCloud(std::move(other)) {}

	virtual ~RailwayPointCloud();	

private:
	buw::CenterlineComputationDescription centerlineDescription_;
	bool bHasPairs_ = false, bHasCenterline_ = false;
	std::vector<buw::ReferenceCounted<PointCloudSection>> sections_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::RailwayPointCloud;
}


#endif // end define OpenInfraPlatform_Infrastructure_RailwayPointCloud_676ff3cf_36f7_4466_a21a_47608e9b561e_h
