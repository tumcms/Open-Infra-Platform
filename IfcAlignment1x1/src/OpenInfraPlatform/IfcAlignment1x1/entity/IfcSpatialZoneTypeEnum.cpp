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

#include "IfcSpatialZoneTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnum() {}
		IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnum(IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum value) { m_enum = value; }
		IfcSpatialZoneTypeEnum::~IfcSpatialZoneTypeEnum() {}
		void IfcSpatialZoneTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_CONSTRUCTION)
				{
					stream << ".CONSTRUCTION.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_FIRESAFETY)
				{
					stream << ".FIRESAFETY.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_LIGHTING)
				{
					stream << ".LIGHTING.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_OCCUPANCY)
				{
					stream << ".OCCUPANCY.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_SECURITY)
				{
					stream << ".SECURITY.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_THERMAL)
				{
					stream << ".THERMAL.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_TRANSPORT)
				{
					stream << ".TRANSPORT.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_VENTILATION)
				{
					stream << ".VENTILATION.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcSpatialZoneTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSpatialZoneTypeEnum> IfcSpatialZoneTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSpatialZoneTypeEnum>(); }
				std::shared_ptr<IfcSpatialZoneTypeEnum> type_object(new IfcSpatialZoneTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONSTRUCTION.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_CONSTRUCTION;
				}
				else if ( _stricmp( arg.c_str(), ".FIRESAFETY.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_FIRESAFETY;
				}
				else if ( _stricmp( arg.c_str(), ".LIGHTING.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_LIGHTING;
				}
				else if ( _stricmp( arg.c_str(), ".OCCUPANCY.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_OCCUPANCY;
				}
				else if ( _stricmp( arg.c_str(), ".SECURITY.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_SECURITY;
				}
				else if ( _stricmp( arg.c_str(), ".THERMAL.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_THERMAL;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSPORT.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_TRANSPORT;
				}
				else if ( _stricmp( arg.c_str(), ".VENTILATION.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_VENTILATION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcSpatialZoneTypeEnum::IfcSpatialZoneTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
