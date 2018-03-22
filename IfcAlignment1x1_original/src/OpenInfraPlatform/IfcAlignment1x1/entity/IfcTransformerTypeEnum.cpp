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

#include "IfcTransformerTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTransformerTypeEnum::IfcTransformerTypeEnum() {}
		IfcTransformerTypeEnum::IfcTransformerTypeEnum(IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum value) { m_enum = value; }
		IfcTransformerTypeEnum::~IfcTransformerTypeEnum() {}
		void IfcTransformerTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_CURRENT)
				{
					stream << ".CURRENT.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_FREQUENCY)
				{
					stream << ".FREQUENCY.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_INVERTER)
				{
					stream << ".INVERTER.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_RECTIFIER)
				{
					stream << ".RECTIFIER.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_VOLTAGE)
				{
					stream << ".VOLTAGE.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcTransformerTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTransformerTypeEnum> IfcTransformerTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTransformerTypeEnum>(); }
				std::shared_ptr<IfcTransformerTypeEnum> type_object(new IfcTransformerTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CURRENT.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_CURRENT;
				}
				else if ( _stricmp( arg.c_str(), ".FREQUENCY.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_FREQUENCY;
				}
				else if ( _stricmp( arg.c_str(), ".INVERTER.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_INVERTER;
				}
				else if ( _stricmp( arg.c_str(), ".RECTIFIER.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_RECTIFIER;
				}
				else if ( _stricmp( arg.c_str(), ".VOLTAGE.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_VOLTAGE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcTransformerTypeEnum::IfcTransformerTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
