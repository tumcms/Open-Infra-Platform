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

#include "IfcElectricFlowStorageDeviceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnum() {}
		IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnum(IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum value) { m_enum = value; }
		IfcElectricFlowStorageDeviceTypeEnum::~IfcElectricFlowStorageDeviceTypeEnum() {}
		void IfcElectricFlowStorageDeviceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_BATTERY)
				{
					stream << ".BATTERY.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_CAPACITORBANK)
				{
					stream << ".CAPACITORBANK.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_HARMONICFILTER)
				{
					stream << ".HARMONICFILTER.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_INDUCTORBANK)
				{
					stream << ".INDUCTORBANK.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_UPS)
				{
					stream << ".UPS.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElectricFlowStorageDeviceTypeEnum> IfcElectricFlowStorageDeviceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElectricFlowStorageDeviceTypeEnum>(); }
				std::shared_ptr<IfcElectricFlowStorageDeviceTypeEnum> type_object(new IfcElectricFlowStorageDeviceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BATTERY.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_BATTERY;
				}
				else if ( _stricmp( arg.c_str(), ".CAPACITORBANK.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_CAPACITORBANK;
				}
				else if ( _stricmp( arg.c_str(), ".HARMONICFILTER.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_HARMONICFILTER;
				}
				else if ( _stricmp( arg.c_str(), ".INDUCTORBANK.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_INDUCTORBANK;
				}
				else if ( _stricmp( arg.c_str(), ".UPS.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_UPS;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricFlowStorageDeviceTypeEnum::IfcElectricFlowStorageDeviceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
