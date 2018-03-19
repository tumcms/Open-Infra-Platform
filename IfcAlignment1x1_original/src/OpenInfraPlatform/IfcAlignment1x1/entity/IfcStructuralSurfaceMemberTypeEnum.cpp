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

#include "IfcStructuralSurfaceMemberTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnum() {}
		IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnum(IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum value) { m_enum = value; }
		IfcStructuralSurfaceMemberTypeEnum::~IfcStructuralSurfaceMemberTypeEnum() {}
		void IfcStructuralSurfaceMemberTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_BENDING_ELEMENT)
				{
					stream << ".BENDING_ELEMENT.";
				}
				else if ( m_enum == IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_MEMBRANE_ELEMENT)
				{
					stream << ".MEMBRANE_ELEMENT.";
				}
				else if ( m_enum == IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_SHELL)
				{
					stream << ".SHELL.";
				}
				else if ( m_enum == IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcStructuralSurfaceMemberTypeEnum> IfcStructuralSurfaceMemberTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcStructuralSurfaceMemberTypeEnum>(); }
				std::shared_ptr<IfcStructuralSurfaceMemberTypeEnum> type_object(new IfcStructuralSurfaceMemberTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BENDING_ELEMENT.") == 0)
				{
					type_object->m_enum = IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_BENDING_ELEMENT;
				}
				else if ( _stricmp( arg.c_str(), ".MEMBRANE_ELEMENT.") == 0)
				{
					type_object->m_enum = IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_MEMBRANE_ELEMENT;
				}
				else if ( _stricmp( arg.c_str(), ".SHELL.") == 0)
				{
					type_object->m_enum = IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_SHELL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcStructuralSurfaceMemberTypeEnum::IfcStructuralSurfaceMemberTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
