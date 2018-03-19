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

#include "IfcPumpTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPumpTypeEnum::IfcPumpTypeEnum() {}
		IfcPumpTypeEnum::IfcPumpTypeEnum(IfcPumpTypeEnum::IfcPumpTypeEnumEnum value) { m_enum = value; }
		IfcPumpTypeEnum::~IfcPumpTypeEnum() {}
		void IfcPumpTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcPumpTypeEnumEnum::ENUM_CIRCULATOR)
				{
					stream << ".CIRCULATOR.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_ENDSUCTION)
				{
					stream << ".ENDSUCTION.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_SPLITCASE)
				{
					stream << ".SPLITCASE.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_SUBMERSIBLEPUMP)
				{
					stream << ".SUBMERSIBLEPUMP.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_SUMPPUMP)
				{
					stream << ".SUMPPUMP.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_VERTICALINLINE)
				{
					stream << ".VERTICALINLINE.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_VERTICALTURBINE)
				{
					stream << ".VERTICALTURBINE.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcPumpTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcPumpTypeEnum> IfcPumpTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPumpTypeEnum>(); }
				std::shared_ptr<IfcPumpTypeEnum> type_object(new IfcPumpTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CIRCULATOR.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_CIRCULATOR;
				}
				else if ( _stricmp( arg.c_str(), ".ENDSUCTION.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_ENDSUCTION;
				}
				else if ( _stricmp( arg.c_str(), ".SPLITCASE.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_SPLITCASE;
				}
				else if ( _stricmp( arg.c_str(), ".SUBMERSIBLEPUMP.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_SUBMERSIBLEPUMP;
				}
				else if ( _stricmp( arg.c_str(), ".SUMPPUMP.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_SUMPPUMP;
				}
				else if ( _stricmp( arg.c_str(), ".VERTICALINLINE.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_VERTICALINLINE;
				}
				else if ( _stricmp( arg.c_str(), ".VERTICALTURBINE.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_VERTICALTURBINE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcPumpTypeEnum::IfcPumpTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
