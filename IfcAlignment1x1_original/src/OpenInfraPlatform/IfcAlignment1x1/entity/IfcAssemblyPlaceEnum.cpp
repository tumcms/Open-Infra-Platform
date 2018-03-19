// Copied and modified code from "IfcPlusPlus" library.
// This library is available under the OpenSceneGraph Public License. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and / or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* OpenSceneGraph Public License for more details.
*/

/* This file has been automatically generated using the TUM Open Infra Platform
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */

#include "IfcAssemblyPlaceEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnum() {}
		IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnum(IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnumEnum value) { m_enum = value; }
		IfcAssemblyPlaceEnum::~IfcAssemblyPlaceEnum() {}
		void IfcAssemblyPlaceEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAssemblyPlaceEnumEnum::ENUM_SITE)
				{
					stream << ".SITE.";
				}
				else if ( m_enum == IfcAssemblyPlaceEnumEnum::ENUM_FACTORY)
				{
					stream << ".FACTORY.";
				}
				else if ( m_enum == IfcAssemblyPlaceEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAssemblyPlaceEnum> IfcAssemblyPlaceEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAssemblyPlaceEnum>(); }
				std::shared_ptr<IfcAssemblyPlaceEnum> type_object(new IfcAssemblyPlaceEnum() );
				if ( _stricmp( arg.c_str(), ".SITE.") == 0)
				{
					type_object->m_enum = IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnumEnum::ENUM_SITE;
				}
				else if ( _stricmp( arg.c_str(), ".FACTORY.") == 0)
				{
					type_object->m_enum = IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnumEnum::ENUM_FACTORY;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAssemblyPlaceEnum::IfcAssemblyPlaceEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
