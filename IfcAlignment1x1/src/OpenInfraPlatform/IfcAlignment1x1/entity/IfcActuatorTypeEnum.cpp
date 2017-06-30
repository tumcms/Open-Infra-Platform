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

#include "IfcActuatorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcActuatorTypeEnum::IfcActuatorTypeEnum() {}
		IfcActuatorTypeEnum::IfcActuatorTypeEnum(IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum value) { m_enum = value; }
		IfcActuatorTypeEnum::~IfcActuatorTypeEnum() {}
		void IfcActuatorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_ELECTRICACTUATOR)
				{
					stream << ".ELECTRICACTUATOR.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_HANDOPERATEDACTUATOR)
				{
					stream << ".HANDOPERATEDACTUATOR.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_HYDRAULICACTUATOR)
				{
					stream << ".HYDRAULICACTUATOR.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_PNEUMATICACTUATOR)
				{
					stream << ".PNEUMATICACTUATOR.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_THERMOSTATICACTUATOR)
				{
					stream << ".THERMOSTATICACTUATOR.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcActuatorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcActuatorTypeEnum> IfcActuatorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcActuatorTypeEnum>(); }
				std::shared_ptr<IfcActuatorTypeEnum> type_object(new IfcActuatorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ELECTRICACTUATOR.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_ELECTRICACTUATOR;
				}
				else if ( _stricmp( arg.c_str(), ".HANDOPERATEDACTUATOR.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_HANDOPERATEDACTUATOR;
				}
				else if ( _stricmp( arg.c_str(), ".HYDRAULICACTUATOR.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_HYDRAULICACTUATOR;
				}
				else if ( _stricmp( arg.c_str(), ".PNEUMATICACTUATOR.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_PNEUMATICACTUATOR;
				}
				else if ( _stricmp( arg.c_str(), ".THERMOSTATICACTUATOR.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_THERMOSTATICACTUATOR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcActuatorTypeEnum::IfcActuatorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
