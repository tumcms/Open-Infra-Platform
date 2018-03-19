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

#include "IfcAlarmTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAlarmTypeEnum::IfcAlarmTypeEnum() {}
		IfcAlarmTypeEnum::IfcAlarmTypeEnum(IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum value) { m_enum = value; }
		IfcAlarmTypeEnum::~IfcAlarmTypeEnum() {}
		void IfcAlarmTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_BELL)
				{
					stream << ".BELL.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_BREAKGLASSBUTTON)
				{
					stream << ".BREAKGLASSBUTTON.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_LIGHT)
				{
					stream << ".LIGHT.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_MANUALPULLBOX)
				{
					stream << ".MANUALPULLBOX.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_SIREN)
				{
					stream << ".SIREN.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_WHISTLE)
				{
					stream << ".WHISTLE.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcAlarmTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAlarmTypeEnum> IfcAlarmTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAlarmTypeEnum>(); }
				std::shared_ptr<IfcAlarmTypeEnum> type_object(new IfcAlarmTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BELL.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_BELL;
				}
				else if ( _stricmp( arg.c_str(), ".BREAKGLASSBUTTON.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_BREAKGLASSBUTTON;
				}
				else if ( _stricmp( arg.c_str(), ".LIGHT.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_LIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".MANUALPULLBOX.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_MANUALPULLBOX;
				}
				else if ( _stricmp( arg.c_str(), ".SIREN.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_SIREN;
				}
				else if ( _stricmp( arg.c_str(), ".WHISTLE.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_WHISTLE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAlarmTypeEnum::IfcAlarmTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
