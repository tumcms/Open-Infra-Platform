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

#include "IfcConstructionEquipmentResourceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnum() {}
		IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnum(IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum value) { m_enum = value; }
		IfcConstructionEquipmentResourceTypeEnum::~IfcConstructionEquipmentResourceTypeEnum() {}
		void IfcConstructionEquipmentResourceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_DEMOLISHING)
				{
					stream << ".DEMOLISHING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_EARTHMOVING)
				{
					stream << ".EARTHMOVING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_ERECTING)
				{
					stream << ".ERECTING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_HEATING)
				{
					stream << ".HEATING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_LIGHTING)
				{
					stream << ".LIGHTING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_PAVING)
				{
					stream << ".PAVING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_PUMPING)
				{
					stream << ".PUMPING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_TRANSPORTING)
				{
					stream << ".TRANSPORTING.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcConstructionEquipmentResourceTypeEnum> IfcConstructionEquipmentResourceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcConstructionEquipmentResourceTypeEnum>(); }
				std::shared_ptr<IfcConstructionEquipmentResourceTypeEnum> type_object(new IfcConstructionEquipmentResourceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DEMOLISHING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_DEMOLISHING;
				}
				else if ( _stricmp( arg.c_str(), ".EARTHMOVING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_EARTHMOVING;
				}
				else if ( _stricmp( arg.c_str(), ".ERECTING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_ERECTING;
				}
				else if ( _stricmp( arg.c_str(), ".HEATING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_HEATING;
				}
				else if ( _stricmp( arg.c_str(), ".LIGHTING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_LIGHTING;
				}
				else if ( _stricmp( arg.c_str(), ".PAVING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_PAVING;
				}
				else if ( _stricmp( arg.c_str(), ".PUMPING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_PUMPING;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSPORTING.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_TRANSPORTING;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
