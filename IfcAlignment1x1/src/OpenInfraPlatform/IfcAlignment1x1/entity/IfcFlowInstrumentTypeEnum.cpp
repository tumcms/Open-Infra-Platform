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

#include "IfcFlowInstrumentTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnum() {}
		IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnum(IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum value) { m_enum = value; }
		IfcFlowInstrumentTypeEnum::~IfcFlowInstrumentTypeEnum() {}
		void IfcFlowInstrumentTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_PRESSUREGAUGE)
				{
					stream << ".PRESSUREGAUGE.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_THERMOMETER)
				{
					stream << ".THERMOMETER.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_AMMETER)
				{
					stream << ".AMMETER.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_FREQUENCYMETER)
				{
					stream << ".FREQUENCYMETER.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_POWERFACTORMETER)
				{
					stream << ".POWERFACTORMETER.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_PHASEANGLEMETER)
				{
					stream << ".PHASEANGLEMETER.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_VOLTMETER_PEAK)
				{
					stream << ".VOLTMETER_PEAK.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_VOLTMETER_RMS)
				{
					stream << ".VOLTMETER_RMS.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcFlowInstrumentTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcFlowInstrumentTypeEnum> IfcFlowInstrumentTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcFlowInstrumentTypeEnum>(); }
				std::shared_ptr<IfcFlowInstrumentTypeEnum> type_object(new IfcFlowInstrumentTypeEnum() );
				if ( _stricmp( arg.c_str(), ".PRESSUREGAUGE.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_PRESSUREGAUGE;
				}
				else if ( _stricmp( arg.c_str(), ".THERMOMETER.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_THERMOMETER;
				}
				else if ( _stricmp( arg.c_str(), ".AMMETER.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_AMMETER;
				}
				else if ( _stricmp( arg.c_str(), ".FREQUENCYMETER.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_FREQUENCYMETER;
				}
				else if ( _stricmp( arg.c_str(), ".POWERFACTORMETER.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_POWERFACTORMETER;
				}
				else if ( _stricmp( arg.c_str(), ".PHASEANGLEMETER.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_PHASEANGLEMETER;
				}
				else if ( _stricmp( arg.c_str(), ".VOLTMETER_PEAK.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_VOLTMETER_PEAK;
				}
				else if ( _stricmp( arg.c_str(), ".VOLTMETER_RMS.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_VOLTMETER_RMS;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcFlowInstrumentTypeEnum::IfcFlowInstrumentTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
