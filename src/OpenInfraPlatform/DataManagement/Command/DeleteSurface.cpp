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

#include "DeleteSurface.h"
#include "OpenInfraPlatform/DataManagement/Data.h"

OpenInfraPlatform::DataManagement::Command::DeleteSurface::DeleteSurface(buw::ReferenceCounted<buw::Surface> surface) :
surface_(surface)
{

}

OpenInfraPlatform::DataManagement::Command::DeleteSurface::~DeleteSurface()
{

}

void OpenInfraPlatform::DataManagement::Command::DeleteSurface::execute()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().deleteSurface(surface_);
}

void OpenInfraPlatform::DataManagement::Command::DeleteSurface::unexecute()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addSurface(surface_);
}
