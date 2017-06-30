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

#include "IfcCrewResourceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnum() {}
		IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnum(IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnumEnum value) { m_enum = value; }
		IfcCrewResourceTypeEnum::~IfcCrewResourceTypeEnum() {}
		void IfcCrewResourceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCrewResourceTypeEnumEnum::ENUM_OFFICE)
				{
					stream << ".OFFICE.";
				}
				else if ( m_enum == IfcCrewResourceTypeEnumEnum::ENUM_SITE)
				{
					stream << ".SITE.";
				}
				else if ( m_enum == IfcCrewResourceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCrewResourceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCrewResourceTypeEnum> IfcCrewResourceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCrewResourceTypeEnum>(); }
				std::shared_ptr<IfcCrewResourceTypeEnum> type_object(new IfcCrewResourceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".OFFICE.") == 0)
				{
					type_object->m_enum = IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnumEnum::ENUM_OFFICE;
				}
				else if ( _stricmp( arg.c_str(), ".SITE.") == 0)
				{
					type_object->m_enum = IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnumEnum::ENUM_SITE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCrewResourceTypeEnum::IfcCrewResourceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
