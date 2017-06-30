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

#include "IfcExternalSpatialElementTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnum() {}
		IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnum(IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum value) { m_enum = value; }
		IfcExternalSpatialElementTypeEnum::~IfcExternalSpatialElementTypeEnum() {}
		void IfcExternalSpatialElementTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL)
				{
					stream << ".EXTERNAL.";
				}
				else if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_EARTH)
				{
					stream << ".EXTERNAL_EARTH.";
				}
				else if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_WATER)
				{
					stream << ".EXTERNAL_WATER.";
				}
				else if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_FIRE)
				{
					stream << ".EXTERNAL_FIRE.";
				}
				else if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcExternalSpatialElementTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcExternalSpatialElementTypeEnum> IfcExternalSpatialElementTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcExternalSpatialElementTypeEnum>(); }
				std::shared_ptr<IfcExternalSpatialElementTypeEnum> type_object(new IfcExternalSpatialElementTypeEnum() );
				if ( _stricmp( arg.c_str(), ".EXTERNAL.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL;
				}
				else if ( _stricmp( arg.c_str(), ".EXTERNAL_EARTH.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_EARTH;
				}
				else if ( _stricmp( arg.c_str(), ".EXTERNAL_WATER.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_WATER;
				}
				else if ( _stricmp( arg.c_str(), ".EXTERNAL_FIRE.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_EXTERNAL_FIRE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcExternalSpatialElementTypeEnum::IfcExternalSpatialElementTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
