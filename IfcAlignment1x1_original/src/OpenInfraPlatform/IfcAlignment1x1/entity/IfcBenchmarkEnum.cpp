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

#include "IfcBenchmarkEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcBenchmarkEnum::IfcBenchmarkEnum() {}
		IfcBenchmarkEnum::IfcBenchmarkEnum(IfcBenchmarkEnum::IfcBenchmarkEnumEnum value) { m_enum = value; }
		IfcBenchmarkEnum::~IfcBenchmarkEnum() {}
		void IfcBenchmarkEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcBenchmarkEnumEnum::ENUM_GREATERTHAN)
				{
					stream << ".GREATERTHAN.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_GREATERTHANOREQUALTO)
				{
					stream << ".GREATERTHANOREQUALTO.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_LESSTHAN)
				{
					stream << ".LESSTHAN.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_LESSTHANOREQUALTO)
				{
					stream << ".LESSTHANOREQUALTO.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_EQUALTO)
				{
					stream << ".EQUALTO.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_NOTEQUALTO)
				{
					stream << ".NOTEQUALTO.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_INCLUDES)
				{
					stream << ".INCLUDES.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_NOTINCLUDES)
				{
					stream << ".NOTINCLUDES.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_INCLUDEDIN)
				{
					stream << ".INCLUDEDIN.";
				}
				else if ( m_enum == IfcBenchmarkEnumEnum::ENUM_NOTINCLUDEDIN)
				{
					stream << ".NOTINCLUDEDIN.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcBenchmarkEnum> IfcBenchmarkEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcBenchmarkEnum>(); }
				std::shared_ptr<IfcBenchmarkEnum> type_object(new IfcBenchmarkEnum() );
				if ( _stricmp( arg.c_str(), ".GREATERTHAN.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_GREATERTHAN;
				}
				else if ( _stricmp( arg.c_str(), ".GREATERTHANOREQUALTO.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_GREATERTHANOREQUALTO;
				}
				else if ( _stricmp( arg.c_str(), ".LESSTHAN.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_LESSTHAN;
				}
				else if ( _stricmp( arg.c_str(), ".LESSTHANOREQUALTO.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_LESSTHANOREQUALTO;
				}
				else if ( _stricmp( arg.c_str(), ".EQUALTO.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_EQUALTO;
				}
				else if ( _stricmp( arg.c_str(), ".NOTEQUALTO.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_NOTEQUALTO;
				}
				else if ( _stricmp( arg.c_str(), ".INCLUDES.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_INCLUDES;
				}
				else if ( _stricmp( arg.c_str(), ".NOTINCLUDES.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_NOTINCLUDES;
				}
				else if ( _stricmp( arg.c_str(), ".INCLUDEDIN.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_INCLUDEDIN;
				}
				else if ( _stricmp( arg.c_str(), ".NOTINCLUDEDIN.") == 0)
				{
					type_object->m_enum = IfcBenchmarkEnum::IfcBenchmarkEnumEnum::ENUM_NOTINCLUDEDIN;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
