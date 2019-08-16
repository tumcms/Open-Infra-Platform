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

#include "Import.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_BEGIN

DataManagement::Import(const std::string& filename) : filename_(filename) 
{
	ifcGeometryModel_ = buw::makeReferenceCounted::<buw::IfcGeometryModel>();
}


buw::ReferenceCounted<OpenInfraPlatform::Core::IfcGeometryConverter::IfcGeometryModel> OpenInfraPlatform::Core::DataManagement::Import::Import getIfcGeometryModel() 
{
	return ifcGeometryModel_;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_END