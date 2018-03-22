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

#include "IfcProcedureTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcProcedureTypeEnum::IfcProcedureTypeEnum() {}
		IfcProcedureTypeEnum::IfcProcedureTypeEnum(IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum value) { m_enum = value; }
		IfcProcedureTypeEnum::~IfcProcedureTypeEnum() {}
		void IfcProcedureTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_ADVICE_CAUTION)
				{
					stream << ".ADVICE_CAUTION.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_ADVICE_NOTE)
				{
					stream << ".ADVICE_NOTE.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_ADVICE_WARNING)
				{
					stream << ".ADVICE_WARNING.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_CALIBRATION)
				{
					stream << ".CALIBRATION.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_DIAGNOSTIC)
				{
					stream << ".DIAGNOSTIC.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_SHUTDOWN)
				{
					stream << ".SHUTDOWN.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_STARTUP)
				{
					stream << ".STARTUP.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcProcedureTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcProcedureTypeEnum> IfcProcedureTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcProcedureTypeEnum>(); }
				std::shared_ptr<IfcProcedureTypeEnum> type_object(new IfcProcedureTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ADVICE_CAUTION.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_ADVICE_CAUTION;
				}
				else if ( _stricmp( arg.c_str(), ".ADVICE_NOTE.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_ADVICE_NOTE;
				}
				else if ( _stricmp( arg.c_str(), ".ADVICE_WARNING.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_ADVICE_WARNING;
				}
				else if ( _stricmp( arg.c_str(), ".CALIBRATION.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_CALIBRATION;
				}
				else if ( _stricmp( arg.c_str(), ".DIAGNOSTIC.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_DIAGNOSTIC;
				}
				else if ( _stricmp( arg.c_str(), ".SHUTDOWN.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_SHUTDOWN;
				}
				else if ( _stricmp( arg.c_str(), ".STARTUP.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_STARTUP;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcProcedureTypeEnum::IfcProcedureTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
