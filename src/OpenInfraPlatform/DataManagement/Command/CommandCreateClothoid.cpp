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

#include "CommandCreateClothoid.h"

#include "OpenInfraPlatform/DataManagement/Data.h"

OpenInfraPlatform::DataManagement::Command::CommandCreateClothoid::CommandCreateClothoid(
	const buw::clothoidDescription& cd) :
cd_(cd),
alignment_(nullptr)
{

}

OpenInfraPlatform::DataManagement::Command::CommandCreateClothoid::~CommandCreateClothoid()
{

}

void OpenInfraPlatform::DataManagement::Command::CommandCreateClothoid::execute()
{
	using namespace buw;
	auto clothoid = buw::makeReferenceCounted<HorizontalAlignmentElement2DClothoid>(cd_);
	
	auto ha = buw::makeReferenceCounted<HorizontalAlignment2D>();
	ha->addElement(clothoid);	
	
	alignment_ = buw::makeReferenceCounted<Alignment2DBased3D>();
	alignment_->setName("New Alignment");
	alignment_->setHorizontalAlignment(ha);

	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(alignment_);
}

void OpenInfraPlatform::DataManagement::Command::CommandCreateClothoid::unexecute()
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().deleteAlignment(alignment_);
}
