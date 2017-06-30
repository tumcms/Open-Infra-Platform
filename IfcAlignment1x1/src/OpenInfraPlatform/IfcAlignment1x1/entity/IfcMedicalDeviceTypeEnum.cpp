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

#include "IfcMedicalDeviceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnum() {}
		IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnum(IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum value) { m_enum = value; }
		IfcMedicalDeviceTypeEnum::~IfcMedicalDeviceTypeEnum() {}
		void IfcMedicalDeviceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_AIRSTATION)
				{
					stream << ".AIRSTATION.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_FEEDAIRUNIT)
				{
					stream << ".FEEDAIRUNIT.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_OXYGENGENERATOR)
				{
					stream << ".OXYGENGENERATOR.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_OXYGENPLANT)
				{
					stream << ".OXYGENPLANT.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_VACUUMSTATION)
				{
					stream << ".VACUUMSTATION.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcMedicalDeviceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcMedicalDeviceTypeEnum> IfcMedicalDeviceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcMedicalDeviceTypeEnum>(); }
				std::shared_ptr<IfcMedicalDeviceTypeEnum> type_object(new IfcMedicalDeviceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".AIRSTATION.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_AIRSTATION;
				}
				else if ( _stricmp( arg.c_str(), ".FEEDAIRUNIT.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_FEEDAIRUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".OXYGENGENERATOR.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_OXYGENGENERATOR;
				}
				else if ( _stricmp( arg.c_str(), ".OXYGENPLANT.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_OXYGENPLANT;
				}
				else if ( _stricmp( arg.c_str(), ".VACUUMSTATION.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_VACUUMSTATION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcMedicalDeviceTypeEnum::IfcMedicalDeviceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
