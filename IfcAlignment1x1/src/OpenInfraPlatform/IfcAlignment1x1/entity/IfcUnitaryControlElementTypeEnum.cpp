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

#include "IfcUnitaryControlElementTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnum() {}
		IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnum(IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum value) { m_enum = value; }
		IfcUnitaryControlElementTypeEnum::~IfcUnitaryControlElementTypeEnum() {}
		void IfcUnitaryControlElementTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_ALARMPANEL)
				{
					stream << ".ALARMPANEL.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_CONTROLPANEL)
				{
					stream << ".CONTROLPANEL.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_GASDETECTIONPANEL)
				{
					stream << ".GASDETECTIONPANEL.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_INDICATORPANEL)
				{
					stream << ".INDICATORPANEL.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_MIMICPANEL)
				{
					stream << ".MIMICPANEL.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_HUMIDISTAT)
				{
					stream << ".HUMIDISTAT.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_THERMOSTAT)
				{
					stream << ".THERMOSTAT.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_WEATHERSTATION)
				{
					stream << ".WEATHERSTATION.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcUnitaryControlElementTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcUnitaryControlElementTypeEnum> IfcUnitaryControlElementTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcUnitaryControlElementTypeEnum>(); }
				std::shared_ptr<IfcUnitaryControlElementTypeEnum> type_object(new IfcUnitaryControlElementTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ALARMPANEL.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_ALARMPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".CONTROLPANEL.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_CONTROLPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".GASDETECTIONPANEL.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_GASDETECTIONPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".INDICATORPANEL.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_INDICATORPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".MIMICPANEL.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_MIMICPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".HUMIDISTAT.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_HUMIDISTAT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMOSTAT.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_THERMOSTAT;
				}
				else if ( _stricmp( arg.c_str(), ".WEATHERSTATION.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_WEATHERSTATION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcUnitaryControlElementTypeEnum::IfcUnitaryControlElementTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
