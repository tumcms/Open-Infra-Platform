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

#include "IfcProtectiveDeviceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnum() {}
		IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnum(IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum value) { m_enum = value; }
		IfcProtectiveDeviceTypeEnum::~IfcProtectiveDeviceTypeEnum() {}
		void IfcProtectiveDeviceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_CIRCUITBREAKER)
				{
					stream << ".CIRCUITBREAKER.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_EARTHLEAKAGECIRCUITBREAKER)
				{
					stream << ".EARTHLEAKAGECIRCUITBREAKER.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_EARTHINGSWITCH)
				{
					stream << ".EARTHINGSWITCH.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_FUSEDISCONNECTOR)
				{
					stream << ".FUSEDISCONNECTOR.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_RESIDUALCURRENTCIRCUITBREAKER)
				{
					stream << ".RESIDUALCURRENTCIRCUITBREAKER.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_RESIDUALCURRENTSWITCH)
				{
					stream << ".RESIDUALCURRENTSWITCH.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_VARISTOR)
				{
					stream << ".VARISTOR.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcProtectiveDeviceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcProtectiveDeviceTypeEnum> IfcProtectiveDeviceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcProtectiveDeviceTypeEnum>(); }
				std::shared_ptr<IfcProtectiveDeviceTypeEnum> type_object(new IfcProtectiveDeviceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CIRCUITBREAKER.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_CIRCUITBREAKER;
				}
				else if ( _stricmp( arg.c_str(), ".EARTHLEAKAGECIRCUITBREAKER.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_EARTHLEAKAGECIRCUITBREAKER;
				}
				else if ( _stricmp( arg.c_str(), ".EARTHINGSWITCH.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_EARTHINGSWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".FUSEDISCONNECTOR.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_FUSEDISCONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".RESIDUALCURRENTCIRCUITBREAKER.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_RESIDUALCURRENTCIRCUITBREAKER;
				}
				else if ( _stricmp( arg.c_str(), ".RESIDUALCURRENTSWITCH.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_RESIDUALCURRENTSWITCH;
				}
				else if ( _stricmp( arg.c_str(), ".VARISTOR.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_VARISTOR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcProtectiveDeviceTypeEnum::IfcProtectiveDeviceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
