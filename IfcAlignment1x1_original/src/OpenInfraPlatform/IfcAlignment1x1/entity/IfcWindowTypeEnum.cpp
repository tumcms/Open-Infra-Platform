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

#include "IfcWindowTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcWindowTypeEnum::IfcWindowTypeEnum() {}
		IfcWindowTypeEnum::IfcWindowTypeEnum(IfcWindowTypeEnum::IfcWindowTypeEnumEnum value) { m_enum = value; }
		IfcWindowTypeEnum::~IfcWindowTypeEnum() {}
		void IfcWindowTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcWindowTypeEnumEnum::ENUM_WINDOW)
				{
					stream << ".WINDOW.";
				}
				else if ( m_enum == IfcWindowTypeEnumEnum::ENUM_SKYLIGHT)
				{
					stream << ".SKYLIGHT.";
				}
				else if ( m_enum == IfcWindowTypeEnumEnum::ENUM_LIGHTDOME)
				{
					stream << ".LIGHTDOME.";
				}
				else if ( m_enum == IfcWindowTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcWindowTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcWindowTypeEnum> IfcWindowTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcWindowTypeEnum>(); }
				std::shared_ptr<IfcWindowTypeEnum> type_object(new IfcWindowTypeEnum() );
				if ( _stricmp( arg.c_str(), ".WINDOW.") == 0)
				{
					type_object->m_enum = IfcWindowTypeEnum::IfcWindowTypeEnumEnum::ENUM_WINDOW;
				}
				else if ( _stricmp( arg.c_str(), ".SKYLIGHT.") == 0)
				{
					type_object->m_enum = IfcWindowTypeEnum::IfcWindowTypeEnumEnum::ENUM_SKYLIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".LIGHTDOME.") == 0)
				{
					type_object->m_enum = IfcWindowTypeEnum::IfcWindowTypeEnumEnum::ENUM_LIGHTDOME;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcWindowTypeEnum::IfcWindowTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcWindowTypeEnum::IfcWindowTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
