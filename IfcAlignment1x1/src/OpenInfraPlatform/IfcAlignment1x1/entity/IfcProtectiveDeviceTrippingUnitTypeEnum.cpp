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

#include "IfcProtectiveDeviceTrippingUnitTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnum() {}
		IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnum(IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum value) { m_enum = value; }
		IfcProtectiveDeviceTrippingUnitTypeEnum::~IfcProtectiveDeviceTrippingUnitTypeEnum() {}
		void IfcProtectiveDeviceTrippingUnitTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_ELECTRONIC)
				{
					stream << ".ELECTRONIC.";
				}
				else if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_ELECTROMAGNETIC)
				{
					stream << ".ELECTROMAGNETIC.";
				}
				else if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_RESIDUALCURRENT)
				{
					stream << ".RESIDUALCURRENT.";
				}
				else if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_THERMAL)
				{
					stream << ".THERMAL.";
				}
				else if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcProtectiveDeviceTrippingUnitTypeEnum> IfcProtectiveDeviceTrippingUnitTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcProtectiveDeviceTrippingUnitTypeEnum>(); }
				std::shared_ptr<IfcProtectiveDeviceTrippingUnitTypeEnum> type_object(new IfcProtectiveDeviceTrippingUnitTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ELECTRONIC.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_ELECTRONIC;
				}
				else if ( _stricmp( arg.c_str(), ".ELECTROMAGNETIC.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_ELECTROMAGNETIC;
				}
				else if ( _stricmp( arg.c_str(), ".RESIDUALCURRENT.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_RESIDUALCURRENT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMAL.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_THERMAL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTrippingUnitTypeEnum::IfcProtectiveDeviceTrippingUnitTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
