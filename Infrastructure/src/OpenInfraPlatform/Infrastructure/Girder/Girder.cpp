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
	, sectionedSolids()
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

Girder::SectionedSolidVector const& Girder::getSectionedSolids() const
{
	return sectionedSolids;
}

void Girder::addSectionedSolid(SectionedSolidHorizontal const& ssh)
{
	sectionedSolids.push_back(ssh);
}

void Girder::addSectionedSolid(SectionedSolidVector const& sshs)
{
	sectionedSolids.insert(sectionedSolids.end(), sshs.begin(), sshs.end());
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
