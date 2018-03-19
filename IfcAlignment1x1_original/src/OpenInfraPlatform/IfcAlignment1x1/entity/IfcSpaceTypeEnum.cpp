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

#include "IfcSpaceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSpaceTypeEnum::IfcSpaceTypeEnum() {}
		IfcSpaceTypeEnum::IfcSpaceTypeEnum(IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum value) { m_enum = value; }
		IfcSpaceTypeEnum::~IfcSpaceTypeEnum() {}
		void IfcSpaceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_SPACE)
				{
					stream << ".SPACE.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_PARKING)
				{
					stream << ".PARKING.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_GFA)
				{
					stream << ".GFA.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_INTERNAL)
				{
					stream << ".INTERNAL.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_EXTERNAL)
				{
					stream << ".EXTERNAL.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcSpaceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSpaceTypeEnum> IfcSpaceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSpaceTypeEnum>(); }
				std::shared_ptr<IfcSpaceTypeEnum> type_object(new IfcSpaceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".SPACE.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_SPACE;
				}
				else if ( _stricmp( arg.c_str(), ".PARKING.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_PARKING;
				}
				else if ( _stricmp( arg.c_str(), ".GFA.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_GFA;
				}
				else if ( _stricmp( arg.c_str(), ".INTERNAL.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_INTERNAL;
				}
				else if ( _stricmp( arg.c_str(), ".EXTERNAL.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_EXTERNAL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcSpaceTypeEnum::IfcSpaceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
