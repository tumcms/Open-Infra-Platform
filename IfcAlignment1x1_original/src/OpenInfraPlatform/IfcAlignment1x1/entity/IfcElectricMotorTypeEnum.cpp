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

#include "IfcElectricMotorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnum() {}
		IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnum(IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum value) { m_enum = value; }
		IfcElectricMotorTypeEnum::~IfcElectricMotorTypeEnum() {}
		void IfcElectricMotorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_DC)
				{
					stream << ".DC.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_INDUCTION)
				{
					stream << ".INDUCTION.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_POLYPHASE)
				{
					stream << ".POLYPHASE.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_RELUCTANCESYNCHRONOUS)
				{
					stream << ".RELUCTANCESYNCHRONOUS.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_SYNCHRONOUS)
				{
					stream << ".SYNCHRONOUS.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcElectricMotorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElectricMotorTypeEnum> IfcElectricMotorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElectricMotorTypeEnum>(); }
				std::shared_ptr<IfcElectricMotorTypeEnum> type_object(new IfcElectricMotorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DC.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_DC;
				}
				else if ( _stricmp( arg.c_str(), ".INDUCTION.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_INDUCTION;
				}
				else if ( _stricmp( arg.c_str(), ".POLYPHASE.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_POLYPHASE;
				}
				else if ( _stricmp( arg.c_str(), ".RELUCTANCESYNCHRONOUS.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_RELUCTANCESYNCHRONOUS;
				}
				else if ( _stricmp( arg.c_str(), ".SYNCHRONOUS.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_SYNCHRONOUS;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricMotorTypeEnum::IfcElectricMotorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
