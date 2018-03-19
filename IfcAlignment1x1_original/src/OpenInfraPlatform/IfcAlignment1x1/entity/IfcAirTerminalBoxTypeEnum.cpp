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

#include "IfcAirTerminalBoxTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnum() {}
		IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnum(IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum value) { m_enum = value; }
		IfcAirTerminalBoxTypeEnum::~IfcAirTerminalBoxTypeEnum() {}
		void IfcAirTerminalBoxTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAirTerminalBoxTypeEnumEnum::ENUM_CONSTANTFLOW)
				{
					stream << ".CONSTANTFLOW.";
				}
				else if ( m_enum == IfcAirTerminalBoxTypeEnumEnum::ENUM_VARIABLEFLOWPRESSUREDEPENDANT)
				{
					stream << ".VARIABLEFLOWPRESSUREDEPENDANT.";
				}
				else if ( m_enum == IfcAirTerminalBoxTypeEnumEnum::ENUM_VARIABLEFLOWPRESSUREINDEPENDANT)
				{
					stream << ".VARIABLEFLOWPRESSUREINDEPENDANT.";
				}
				else if ( m_enum == IfcAirTerminalBoxTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcAirTerminalBoxTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAirTerminalBoxTypeEnum> IfcAirTerminalBoxTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAirTerminalBoxTypeEnum>(); }
				std::shared_ptr<IfcAirTerminalBoxTypeEnum> type_object(new IfcAirTerminalBoxTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONSTANTFLOW.") == 0)
				{
					type_object->m_enum = IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum::ENUM_CONSTANTFLOW;
				}
				else if ( _stricmp( arg.c_str(), ".VARIABLEFLOWPRESSUREDEPENDANT.") == 0)
				{
					type_object->m_enum = IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum::ENUM_VARIABLEFLOWPRESSUREDEPENDANT;
				}
				else if ( _stricmp( arg.c_str(), ".VARIABLEFLOWPRESSUREINDEPENDANT.") == 0)
				{
					type_object->m_enum = IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum::ENUM_VARIABLEFLOWPRESSUREINDEPENDANT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirTerminalBoxTypeEnum::IfcAirTerminalBoxTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
