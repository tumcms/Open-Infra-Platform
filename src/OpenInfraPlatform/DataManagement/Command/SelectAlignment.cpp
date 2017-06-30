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

#include "SelectAlignment.h"
#include "../Data.h"

OpenInfraPlatform::DataManagement::Command::SelectAlignment::SelectAlignment(int selectedIndex)
{
	selectedIndex_ = selectedIndex;
}

OpenInfraPlatform::DataManagement::Command::SelectAlignment::~SelectAlignment()
{

}

void OpenInfraPlatform::DataManagement::Command::SelectAlignment::execute()
{
	prevSelectedIndex_ = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment();
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setSelectedAlignment(selectedIndex_);
}

void OpenInfraPlatform::DataManagement::Command::SelectAlignment::unexecute()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setSelectedAlignment(prevSelectedIndex_);
}
