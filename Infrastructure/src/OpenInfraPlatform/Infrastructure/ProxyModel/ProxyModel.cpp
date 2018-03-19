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

const OpenInfraPlatform::Infrastructure::accidentReportDescription& OpenInfraPlatform::Infrastructure::ProxyModel::getAccidentReportByIndex(const int index) const
{
	return accidentReports_[index];
}

void OpenInfraPlatform::Infrastructure::ProxyModel::removeAccidentReportAt(const int index)
{
	accidentReports_.erase(accidentReports_.begin() + index);
}

int OpenInfraPlatform::Infrastructure::ProxyModel::getAccidentReportCount()
{
	return static_cast<int>(accidentReports_.size());
}

int OpenInfraPlatform::Infrastructure::ProxyModel::addAccidentReport(const accidentReportDescription& c)
{
	accidentReports_.push_back(c);
	return static_cast<int>(accidentReports_.size()) - 1;
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
	accidentReportDescription a;
	a.position = buw::Vector3d(0, 0, 0);
	
	addAccidentReport(a);
	a.position = buw::Vector3d(100, 0, 0);
	addAccidentReport(a);
	*/
}
