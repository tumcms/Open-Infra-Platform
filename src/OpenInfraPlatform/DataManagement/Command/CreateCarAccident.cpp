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

#include "CreateCarAccident.h"
#include "../Data.h"

OpenInfraPlatform::DataManagement::Command::CreateCarAccident::CreateCarAccident(const int selectedIndex, const double station)
{
	selectedIndex_ = selectedIndex;
	station_ = station;
	ca_.position = buw::Vector3d(10, 10, 10);
}

OpenInfraPlatform::DataManagement::Command::CreateCarAccident::~CreateCarAccident()
{

}

void OpenInfraPlatform::DataManagement::Command::CreateCarAccident::execute()
{	
	CarAccidentReportIndex_ = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().createCarAccidentReport(ca_);
}

void OpenInfraPlatform::DataManagement::Command::CreateCarAccident::unexecute()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().removeCarAccidentReport(CarAccidentReportIndex_);
}
