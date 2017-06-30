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

#include "IfcSwitchingDeviceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnum() {}
		IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnum(IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum value) { m_enum = value; }
		IfcSwitchingDeviceTypeEnum::~IfcSwitchingDeviceTypeEnum() {}
		void IfcSwitchingDeviceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_CONTACTOR)
				{
					stream << ".CONTACTOR.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_DIMMERSWITCH)
				{
					stream << ".DIMMERSWITCH.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_EMERGENCYSTOP)
				{
					stream << ".EMERGENCYSTOP.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_KEYPAD)
				{
					stream << ".KEYPAD.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_MOMENTARYSWITCH)
				{
					stream << ".MOMENTARYSWITCH.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_SELECTORSWITCH)
				{
					stream << ".SELECTORSWITCH.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_STARTER)
				{
					stream << ".STARTER.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_SWITCHDISCONNECTOR)
				{
					stream << ".SWITCHDISCONNECTOR.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_TOGGLESWITCH)
				{
					stream << ".TOGGLESWITCH.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcSwitchingDeviceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSwitchingDeviceTypeEnum> IfcSwitchingDeviceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSwitchingDeviceTypeEnum>(); }
				std::shared_ptr<IfcSwitchingDeviceTypeEnum> type_object(new IfcSwitchingDeviceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONTACTOR.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_CONTACTOR;
				}
				else if ( _stricmp( arg.c_str(), ".DIMMERSWITCH.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_DIMMERSWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".EMERGENCYSTOP.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_EMERGENCYSTOP;
				}
				else if ( _stricmp( arg.c_str(), ".KEYPAD.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_KEYPAD;
				}
				else if ( _stricmp( arg.c_str(), ".MOMENTARYSWITCH.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_MOMENTARYSWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".SELECTORSWITCH.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_SELECTORSWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".STARTER.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_STARTER;
				}
				else if ( _stricmp( arg.c_str(), ".SWITCHDISCONNECTOR.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_SWITCHDISCONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".TOGGLESWITCH.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_TOGGLESWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcSwitchingDeviceTypeEnum::IfcSwitchingDeviceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
