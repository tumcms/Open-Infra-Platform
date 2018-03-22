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

#include "IfcStructuralCurveMemberTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnum() {}
		IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnum(IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum value) { m_enum = value; }
		IfcStructuralCurveMemberTypeEnum::~IfcStructuralCurveMemberTypeEnum() {}
		void IfcStructuralCurveMemberTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_RIGID_JOINED_MEMBER)
				{
					stream << ".RIGID_JOINED_MEMBER.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_PIN_JOINED_MEMBER)
				{
					stream << ".PIN_JOINED_MEMBER.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_CABLE)
				{
					stream << ".CABLE.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_TENSION_MEMBER)
				{
					stream << ".TENSION_MEMBER.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_COMPRESSION_MEMBER)
				{
					stream << ".COMPRESSION_MEMBER.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcStructuralCurveMemberTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcStructuralCurveMemberTypeEnum> IfcStructuralCurveMemberTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcStructuralCurveMemberTypeEnum>(); }
				std::shared_ptr<IfcStructuralCurveMemberTypeEnum> type_object(new IfcStructuralCurveMemberTypeEnum() );
				if ( _stricmp( arg.c_str(), ".RIGID_JOINED_MEMBER.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_RIGID_JOINED_MEMBER;
				}
				else if ( _stricmp( arg.c_str(), ".PIN_JOINED_MEMBER.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_PIN_JOINED_MEMBER;
				}
				else if ( _stricmp( arg.c_str(), ".CABLE.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_CABLE;
				}
				else if ( _stricmp( arg.c_str(), ".TENSION_MEMBER.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_TENSION_MEMBER;
				}
				else if ( _stricmp( arg.c_str(), ".COMPRESSION_MEMBER.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_COMPRESSION_MEMBER;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralCurveMemberTypeEnum::IfcStructuralCurveMemberTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
