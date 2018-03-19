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

#include "IfcMemberTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcMemberTypeEnum::IfcMemberTypeEnum() {}
		IfcMemberTypeEnum::IfcMemberTypeEnum(IfcMemberTypeEnum::IfcMemberTypeEnumEnum value) { m_enum = value; }
		IfcMemberTypeEnum::~IfcMemberTypeEnum() {}
		void IfcMemberTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcMemberTypeEnumEnum::ENUM_BRACE)
				{
					stream << ".BRACE.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_CHORD)
				{
					stream << ".CHORD.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_COLLAR)
				{
					stream << ".COLLAR.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_MEMBER)
				{
					stream << ".MEMBER.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_MULLION)
				{
					stream << ".MULLION.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_PLATE)
				{
					stream << ".PLATE.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_POST)
				{
					stream << ".POST.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_PURLIN)
				{
					stream << ".PURLIN.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_RAFTER)
				{
					stream << ".RAFTER.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_STRINGER)
				{
					stream << ".STRINGER.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_STRUT)
				{
					stream << ".STRUT.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_STUD)
				{
					stream << ".STUD.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcMemberTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcMemberTypeEnum> IfcMemberTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcMemberTypeEnum>(); }
				std::shared_ptr<IfcMemberTypeEnum> type_object(new IfcMemberTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BRACE.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_BRACE;
				}
				else if ( _stricmp( arg.c_str(), ".CHORD.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_CHORD;
				}
				else if ( _stricmp( arg.c_str(), ".COLLAR.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_COLLAR;
				}
				else if ( _stricmp( arg.c_str(), ".MEMBER.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_MEMBER;
				}
				else if ( _stricmp( arg.c_str(), ".MULLION.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_MULLION;
				}
				else if ( _stricmp( arg.c_str(), ".PLATE.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_PLATE;
				}
				else if ( _stricmp( arg.c_str(), ".POST.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_POST;
				}
				else if ( _stricmp( arg.c_str(), ".PURLIN.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_PURLIN;
				}
				else if ( _stricmp( arg.c_str(), ".RAFTER.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_RAFTER;
				}
				else if ( _stricmp( arg.c_str(), ".STRINGER.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_STRINGER;
				}
				else if ( _stricmp( arg.c_str(), ".STRUT.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_STRUT;
				}
				else if ( _stricmp( arg.c_str(), ".STUD.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_STUD;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcMemberTypeEnum::IfcMemberTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
