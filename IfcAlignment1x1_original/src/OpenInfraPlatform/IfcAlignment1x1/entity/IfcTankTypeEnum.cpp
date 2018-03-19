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

#include "IfcTankTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTankTypeEnum::IfcTankTypeEnum() {}
		IfcTankTypeEnum::IfcTankTypeEnum(IfcTankTypeEnum::IfcTankTypeEnumEnum value) { m_enum = value; }
		IfcTankTypeEnum::~IfcTankTypeEnum() {}
		void IfcTankTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTankTypeEnumEnum::ENUM_BASIN)
				{
					stream << ".BASIN.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_BREAKPRESSURE)
				{
					stream << ".BREAKPRESSURE.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_EXPANSION)
				{
					stream << ".EXPANSION.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_FEEDANDEXPANSION)
				{
					stream << ".FEEDANDEXPANSION.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_PRESSUREVESSEL)
				{
					stream << ".PRESSUREVESSEL.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_STORAGE)
				{
					stream << ".STORAGE.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_VESSEL)
				{
					stream << ".VESSEL.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcTankTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTankTypeEnum> IfcTankTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTankTypeEnum>(); }
				std::shared_ptr<IfcTankTypeEnum> type_object(new IfcTankTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BASIN.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_BASIN;
				}
				else if ( _stricmp( arg.c_str(), ".BREAKPRESSURE.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_BREAKPRESSURE;
				}
				else if ( _stricmp( arg.c_str(), ".EXPANSION.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_EXPANSION;
				}
				else if ( _stricmp( arg.c_str(), ".FEEDANDEXPANSION.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_FEEDANDEXPANSION;
				}
				else if ( _stricmp( arg.c_str(), ".PRESSUREVESSEL.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_PRESSUREVESSEL;
				}
				else if ( _stricmp( arg.c_str(), ".STORAGE.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_STORAGE;
				}
				else if ( _stricmp( arg.c_str(), ".VESSEL.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_VESSEL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcTankTypeEnum::IfcTankTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
