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

#include "IfcWorkCalendarTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnum() {}
		IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnum(IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum value) { m_enum = value; }
		IfcWorkCalendarTypeEnum::~IfcWorkCalendarTypeEnum() {}
		void IfcWorkCalendarTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcWorkCalendarTypeEnumEnum::ENUM_FIRSTSHIFT)
				{
					stream << ".FIRSTSHIFT.";
				}
				else if ( m_enum == IfcWorkCalendarTypeEnumEnum::ENUM_SECONDSHIFT)
				{
					stream << ".SECONDSHIFT.";
				}
				else if ( m_enum == IfcWorkCalendarTypeEnumEnum::ENUM_THIRDSHIFT)
				{
					stream << ".THIRDSHIFT.";
				}
				else if ( m_enum == IfcWorkCalendarTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcWorkCalendarTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcWorkCalendarTypeEnum> IfcWorkCalendarTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcWorkCalendarTypeEnum>(); }
				std::shared_ptr<IfcWorkCalendarTypeEnum> type_object(new IfcWorkCalendarTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FIRSTSHIFT.") == 0)
				{
					type_object->m_enum = IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum::ENUM_FIRSTSHIFT;
				}
				else if ( _stricmp( arg.c_str(), ".SECONDSHIFT.") == 0)
				{
					type_object->m_enum = IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum::ENUM_SECONDSHIFT;
				}
				else if ( _stricmp( arg.c_str(), ".THIRDSHIFT.") == 0)
				{
					type_object->m_enum = IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum::ENUM_THIRDSHIFT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
