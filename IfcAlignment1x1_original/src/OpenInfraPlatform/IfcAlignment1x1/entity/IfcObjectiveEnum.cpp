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

#include "IfcObjectiveEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcObjectiveEnum::IfcObjectiveEnum() {}
		IfcObjectiveEnum::IfcObjectiveEnum(IfcObjectiveEnum::IfcObjectiveEnumEnum value) { m_enum = value; }
		IfcObjectiveEnum::~IfcObjectiveEnum() {}
		void IfcObjectiveEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcObjectiveEnumEnum::ENUM_CODECOMPLIANCE)
				{
					stream << ".CODECOMPLIANCE.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_CODEWAIVER)
				{
					stream << ".CODEWAIVER.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_DESIGNINTENT)
				{
					stream << ".DESIGNINTENT.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_EXTERNAL)
				{
					stream << ".EXTERNAL.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_HEALTHANDSAFETY)
				{
					stream << ".HEALTHANDSAFETY.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_MERGECONFLICT)
				{
					stream << ".MERGECONFLICT.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_MODELVIEW)
				{
					stream << ".MODELVIEW.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_PARAMETER)
				{
					stream << ".PARAMETER.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_REQUIREMENT)
				{
					stream << ".REQUIREMENT.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_SPECIFICATION)
				{
					stream << ".SPECIFICATION.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_TRIGGERCONDITION)
				{
					stream << ".TRIGGERCONDITION.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcObjectiveEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcObjectiveEnum> IfcObjectiveEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcObjectiveEnum>(); }
				std::shared_ptr<IfcObjectiveEnum> type_object(new IfcObjectiveEnum() );
				if ( _stricmp( arg.c_str(), ".CODECOMPLIANCE.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_CODECOMPLIANCE;
				}
				else if ( _stricmp( arg.c_str(), ".CODEWAIVER.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_CODEWAIVER;
				}
				else if ( _stricmp( arg.c_str(), ".DESIGNINTENT.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_DESIGNINTENT;
				}
				else if ( _stricmp( arg.c_str(), ".EXTERNAL.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_EXTERNAL;
				}
				else if ( _stricmp( arg.c_str(), ".HEALTHANDSAFETY.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_HEALTHANDSAFETY;
				}
				else if ( _stricmp( arg.c_str(), ".MERGECONFLICT.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_MERGECONFLICT;
				}
				else if ( _stricmp( arg.c_str(), ".MODELVIEW.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_MODELVIEW;
				}
				else if ( _stricmp( arg.c_str(), ".PARAMETER.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_PARAMETER;
				}
				else if ( _stricmp( arg.c_str(), ".REQUIREMENT.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_REQUIREMENT;
				}
				else if ( _stricmp( arg.c_str(), ".SPECIFICATION.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_SPECIFICATION;
				}
				else if ( _stricmp( arg.c_str(), ".TRIGGERCONDITION.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_TRIGGERCONDITION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcObjectiveEnum::IfcObjectiveEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
