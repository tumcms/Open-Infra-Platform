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

#include "IfcFlowMeterTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnum() {}
		IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnum(IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum value) { m_enum = value; }
		IfcFlowMeterTypeEnum::~IfcFlowMeterTypeEnum() {}
		void IfcFlowMeterTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_ENERGYMETER)
				{
					stream << ".ENERGYMETER.";
				}
				else if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_GASMETER)
				{
					stream << ".GASMETER.";
				}
				else if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_OILMETER)
				{
					stream << ".OILMETER.";
				}
				else if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_WATERMETER)
				{
					stream << ".WATERMETER.";
				}
				else if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcFlowMeterTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcFlowMeterTypeEnum> IfcFlowMeterTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcFlowMeterTypeEnum>(); }
				std::shared_ptr<IfcFlowMeterTypeEnum> type_object(new IfcFlowMeterTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ENERGYMETER.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_ENERGYMETER;
				}
				else if ( _stricmp( arg.c_str(), ".GASMETER.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_GASMETER;
				}
				else if ( _stricmp( arg.c_str(), ".OILMETER.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_OILMETER;
				}
				else if ( _stricmp( arg.c_str(), ".WATERMETER.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_WATERMETER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
