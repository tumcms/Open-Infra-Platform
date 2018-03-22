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

#include "IfcLampTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcLampTypeEnum::IfcLampTypeEnum() {}
		IfcLampTypeEnum::IfcLampTypeEnum(IfcLampTypeEnum::IfcLampTypeEnumEnum value) { m_enum = value; }
		IfcLampTypeEnum::~IfcLampTypeEnum() {}
		void IfcLampTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcLampTypeEnumEnum::ENUM_COMPACTFLUORESCENT)
				{
					stream << ".COMPACTFLUORESCENT.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_FLUORESCENT)
				{
					stream << ".FLUORESCENT.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_HALOGEN)
				{
					stream << ".HALOGEN.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_HIGHPRESSUREMERCURY)
				{
					stream << ".HIGHPRESSUREMERCURY.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_HIGHPRESSURESODIUM)
				{
					stream << ".HIGHPRESSURESODIUM.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_LED)
				{
					stream << ".LED.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_METALHALIDE)
				{
					stream << ".METALHALIDE.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_OLED)
				{
					stream << ".OLED.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_TUNGSTENFILAMENT)
				{
					stream << ".TUNGSTENFILAMENT.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcLampTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcLampTypeEnum> IfcLampTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcLampTypeEnum>(); }
				std::shared_ptr<IfcLampTypeEnum> type_object(new IfcLampTypeEnum() );
				if ( _stricmp( arg.c_str(), ".COMPACTFLUORESCENT.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_COMPACTFLUORESCENT;
				}
				else if ( _stricmp( arg.c_str(), ".FLUORESCENT.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_FLUORESCENT;
				}
				else if ( _stricmp( arg.c_str(), ".HALOGEN.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_HALOGEN;
				}
				else if ( _stricmp( arg.c_str(), ".HIGHPRESSUREMERCURY.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_HIGHPRESSUREMERCURY;
				}
				else if ( _stricmp( arg.c_str(), ".HIGHPRESSURESODIUM.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_HIGHPRESSURESODIUM;
				}
				else if ( _stricmp( arg.c_str(), ".LED.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_LED;
				}
				else if ( _stricmp( arg.c_str(), ".METALHALIDE.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_METALHALIDE;
				}
				else if ( _stricmp( arg.c_str(), ".OLED.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_OLED;
				}
				else if ( _stricmp( arg.c_str(), ".TUNGSTENFILAMENT.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_TUNGSTENFILAMENT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcLampTypeEnum::IfcLampTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
