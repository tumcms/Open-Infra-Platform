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

#pragma once

#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/Surface.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <boost/noncopyable.hpp>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API TrafficSign {
public:
	int alignmentId = -1;
	double distanceAlong = 0.0;
	bool bAlongHorizontal = false;
	float rotation = 0.0f;

	double offsetLateral;

	std::vector<buw::VertexPosition3> vertices;
	std::vector<unsigned int> indices;
};

class BLUEINFRASTRUCTURE_API TrafficSignModel {
public:
	TrafficSignModel();

	virtual ~TrafficSignModel();

	void addTrafficSign(buw::ReferenceCounted<TrafficSign> ts);

	int getTrafficSignCount() const;

	buw::ReferenceCounted<TrafficSign> getTrafficSignByIndex(const int index);

private:
	std::vector<buw::ReferenceCounted<TrafficSign>> trafficSigns_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::TrafficSign;
	using OpenInfraPlatform::Infrastructure::TrafficSignModel;
}