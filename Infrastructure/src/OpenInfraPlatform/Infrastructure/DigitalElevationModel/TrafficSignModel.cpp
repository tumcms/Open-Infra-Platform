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

#include "TrafficSignModel.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

TrafficSignModel::TrafficSignModel() {

}

TrafficSignModel::~TrafficSignModel() {

}

buw::ReferenceCounted<TrafficSign> OpenInfraPlatform::Infrastructure::TrafficSignModel::getTrafficSignByIndex(const int index) {
	return trafficSigns_[index];
}

int TrafficSignModel::getTrafficSignCount() const {
	return trafficSigns_.size();
}

void TrafficSignModel::addTrafficSign(buw::ReferenceCounted<TrafficSign> ts) {
	trafficSigns_.push_back(ts);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
