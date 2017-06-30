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

#include "Girder.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

Girder::Girder(int const id, std::wstring const& name)
	: id(id)
	, name(name)
	, horizontalAlignment()
	, verticalAlignment()
{
}

Girder::~Girder()
{
}

buw::String Girder::getName() const
{
	return name;
}

void Girder::setName(std::wstring const& name)
{
	this->name = name;
}

void Girder::setHorizontalAlignment(std::shared_ptr<HorizontalAlignment2D> horiz)
{
	horizontalAlignment = horiz;
}

void Girder::setVerticalAlignment(std::shared_ptr<VerticalAlignment2D> vert)
{
	verticalAlignment = vert;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
