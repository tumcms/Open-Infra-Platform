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

#include "ProxyModel.h"

const OpenInfraPlatform::Infrastructure::carAccidentDescription& OpenInfraPlatform::Infrastructure::ProxyModel::getCarAccidentByIndex(const int index) const
{
	return carAccidents_[index];
}

void OpenInfraPlatform::Infrastructure::ProxyModel::removeCarAccidentAt(const int index)
{
	carAccidents_.erase(carAccidents_.begin() + index);
}

int OpenInfraPlatform::Infrastructure::ProxyModel::getCarAccidentCount()
{
	return static_cast<int>(carAccidents_.size());
}

int OpenInfraPlatform::Infrastructure::ProxyModel::addCarAccident(const carAccidentDescription& c)
{
	carAccidents_.push_back(c);
	return static_cast<int>(carAccidents_.size()) - 1;
}

const std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> >& OpenInfraPlatform::Infrastructure::ProxyModel::getIfc4x1Data() const
{
	return Ifc4x1Entities_;
}

bool OpenInfraPlatform::Infrastructure::ProxyModel::hasIfc4x1Data()
{
	return Ifc4x1Entities_.size() > 0;
}

void OpenInfraPlatform::Infrastructure::ProxyModel::setIfc4x1Entities(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > entities)
{
	Ifc4x1Entities_ = entities;
}

OpenInfraPlatform::Infrastructure::ProxyModel::~ProxyModel()
{

}

OpenInfraPlatform::Infrastructure::ProxyModel::ProxyModel()
{
	/* // Add some stuff for test proposes
	carAccidentDescription a;
	a.position = buw::Vector3d(0, 0, 0);
	
	addCarAccident(a);
	a.position = buw::Vector3d(100, 0, 0);
	addCarAccident(a);
	*/
}
