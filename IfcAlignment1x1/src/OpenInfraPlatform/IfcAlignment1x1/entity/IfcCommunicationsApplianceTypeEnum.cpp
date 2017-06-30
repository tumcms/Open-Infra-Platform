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

#include "IfcCommunicationsApplianceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnum() {}
		IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnum(IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum value) { m_enum = value; }
		IfcCommunicationsApplianceTypeEnum::~IfcCommunicationsApplianceTypeEnum() {}
		void IfcCommunicationsApplianceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_ANTENNA)
				{
					stream << ".ANTENNA.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_COMPUTER)
				{
					stream << ".COMPUTER.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_FAX)
				{
					stream << ".FAX.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_GATEWAY)
				{
					stream << ".GATEWAY.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_MODEM)
				{
					stream << ".MODEM.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKAPPLIANCE)
				{
					stream << ".NETWORKAPPLIANCE.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKBRIDGE)
				{
					stream << ".NETWORKBRIDGE.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKHUB)
				{
					stream << ".NETWORKHUB.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_PRINTER)
				{
					stream << ".PRINTER.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_REPEATER)
				{
					stream << ".REPEATER.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_ROUTER)
				{
					stream << ".ROUTER.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_SCANNER)
				{
					stream << ".SCANNER.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCommunicationsApplianceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCommunicationsApplianceTypeEnum> IfcCommunicationsApplianceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCommunicationsApplianceTypeEnum>(); }
				std::shared_ptr<IfcCommunicationsApplianceTypeEnum> type_object(new IfcCommunicationsApplianceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ANTENNA.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_ANTENNA;
				}
				else if ( _stricmp( arg.c_str(), ".COMPUTER.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_COMPUTER;
				}
				else if ( _stricmp( arg.c_str(), ".FAX.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_FAX;
				}
				else if ( _stricmp( arg.c_str(), ".GATEWAY.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_GATEWAY;
				}
				else if ( _stricmp( arg.c_str(), ".MODEM.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_MODEM;
				}
				else if ( _stricmp( arg.c_str(), ".NETWORKAPPLIANCE.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKAPPLIANCE;
				}
				else if ( _stricmp( arg.c_str(), ".NETWORKBRIDGE.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKBRIDGE;
				}
				else if ( _stricmp( arg.c_str(), ".NETWORKHUB.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_NETWORKHUB;
				}
				else if ( _stricmp( arg.c_str(), ".PRINTER.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_PRINTER;
				}
				else if ( _stricmp( arg.c_str(), ".REPEATER.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_REPEATER;
				}
				else if ( _stricmp( arg.c_str(), ".ROUTER.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_ROUTER;
				}
				else if ( _stricmp( arg.c_str(), ".SCANNER.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_SCANNER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCommunicationsApplianceTypeEnum::IfcCommunicationsApplianceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
