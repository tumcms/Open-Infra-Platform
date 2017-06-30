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

#include "IfcSensorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSensorTypeEnum::IfcSensorTypeEnum() {}
		IfcSensorTypeEnum::IfcSensorTypeEnum(IfcSensorTypeEnum::IfcSensorTypeEnumEnum value) { m_enum = value; }
		IfcSensorTypeEnum::~IfcSensorTypeEnum() {}
		void IfcSensorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSensorTypeEnumEnum::ENUM_COSENSOR)
				{
					stream << ".COSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_CO2SENSOR)
				{
					stream << ".CO2SENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_CONDUCTANCESENSOR)
				{
					stream << ".CONDUCTANCESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_CONTACTSENSOR)
				{
					stream << ".CONTACTSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_FIRESENSOR)
				{
					stream << ".FIRESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_FLOWSENSOR)
				{
					stream << ".FLOWSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_FROSTSENSOR)
				{
					stream << ".FROSTSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_GASSENSOR)
				{
					stream << ".GASSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_HEATSENSOR)
				{
					stream << ".HEATSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_HUMIDITYSENSOR)
				{
					stream << ".HUMIDITYSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_IDENTIFIERSENSOR)
				{
					stream << ".IDENTIFIERSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_IONCONCENTRATIONSENSOR)
				{
					stream << ".IONCONCENTRATIONSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_LEVELSENSOR)
				{
					stream << ".LEVELSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_LIGHTSENSOR)
				{
					stream << ".LIGHTSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_MOISTURESENSOR)
				{
					stream << ".MOISTURESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_MOVEMENTSENSOR)
				{
					stream << ".MOVEMENTSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_PHSENSOR)
				{
					stream << ".PHSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_PRESSURESENSOR)
				{
					stream << ".PRESSURESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_RADIATIONSENSOR)
				{
					stream << ".RADIATIONSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_RADIOACTIVITYSENSOR)
				{
					stream << ".RADIOACTIVITYSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_SMOKESENSOR)
				{
					stream << ".SMOKESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_SOUNDSENSOR)
				{
					stream << ".SOUNDSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_TEMPERATURESENSOR)
				{
					stream << ".TEMPERATURESENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_WINDSENSOR)
				{
					stream << ".WINDSENSOR.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcSensorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSensorTypeEnum> IfcSensorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSensorTypeEnum>(); }
				std::shared_ptr<IfcSensorTypeEnum> type_object(new IfcSensorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".COSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_COSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".CO2SENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_CO2SENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".CONDUCTANCESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_CONDUCTANCESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".CONTACTSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_CONTACTSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".FIRESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_FIRESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".FLOWSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_FLOWSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".FROSTSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_FROSTSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".GASSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_GASSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".HEATSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_HEATSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".HUMIDITYSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_HUMIDITYSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".IDENTIFIERSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_IDENTIFIERSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".IONCONCENTRATIONSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_IONCONCENTRATIONSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".LEVELSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_LEVELSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".LIGHTSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_LIGHTSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".MOISTURESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_MOISTURESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".MOVEMENTSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_MOVEMENTSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".PHSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_PHSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".PRESSURESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_PRESSURESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".RADIATIONSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_RADIATIONSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".RADIOACTIVITYSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_RADIOACTIVITYSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".SMOKESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_SMOKESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".SOUNDSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_SOUNDSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".TEMPERATURESENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_TEMPERATURESENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".WINDSENSOR.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_WINDSENSOR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcSensorTypeEnum::IfcSensorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
