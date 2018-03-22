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

#include "IfcAirTerminalTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnum() {}
		IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnum(IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum value) { m_enum = value; }
		IfcAirTerminalTypeEnum::~IfcAirTerminalTypeEnum() {}
		void IfcAirTerminalTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_DIFFUSER)
				{
					stream << ".DIFFUSER.";
				}
				else if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_GRILLE)
				{
					stream << ".GRILLE.";
				}
				else if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_LOUVRE)
				{
					stream << ".LOUVRE.";
				}
				else if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_REGISTER)
				{
					stream << ".REGISTER.";
				}
				else if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcAirTerminalTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAirTerminalTypeEnum> IfcAirTerminalTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAirTerminalTypeEnum>(); }
				std::shared_ptr<IfcAirTerminalTypeEnum> type_object(new IfcAirTerminalTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DIFFUSER.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_DIFFUSER;
				}
				else if ( _stricmp( arg.c_str(), ".GRILLE.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_GRILLE;
				}
				else if ( _stricmp( arg.c_str(), ".LOUVRE.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_LOUVRE;
				}
				else if ( _stricmp( arg.c_str(), ".REGISTER.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_REGISTER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAirTerminalTypeEnum::IfcAirTerminalTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
