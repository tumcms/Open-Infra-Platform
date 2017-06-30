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

#include "IAlignment3D.h"
#include <BlueFramework/Core/string.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

void IAlignment3D::setName(const std::wstring& name)
{
	name_ = name;
}

void IAlignment3D::setName(const std::string& name)
{
	name_ = buw::String::toWStdString(name);
}

e3DAlignmentType OpenInfraPlatform::Infrastructure::IAlignment3D::getType() const
{
	return type_;
}

buw::String IAlignment3D::getName() const
{
	return name_;
}

IAlignment3D::~IAlignment3D()
{

}

IAlignment3D::IAlignment3D(const e3DAlignmentType type) :
type_(type)
{

}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END