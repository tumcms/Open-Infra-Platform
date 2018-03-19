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

#include "IfcPipeFittingTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnum() {}
		IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnum(IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum value) { m_enum = value; }
		IfcPipeFittingTypeEnum::~IfcPipeFittingTypeEnum() {}
		void IfcPipeFittingTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_BEND)
				{
					stream << ".BEND.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_CONNECTOR)
				{
					stream << ".CONNECTOR.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_ENTRY)
				{
					stream << ".ENTRY.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_EXIT)
				{
					stream << ".EXIT.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_JUNCTION)
				{
					stream << ".JUNCTION.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_OBSTRUCTION)
				{
					stream << ".OBSTRUCTION.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_TRANSITION)
				{
					stream << ".TRANSITION.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcPipeFittingTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcPipeFittingTypeEnum> IfcPipeFittingTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPipeFittingTypeEnum>(); }
				std::shared_ptr<IfcPipeFittingTypeEnum> type_object(new IfcPipeFittingTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BEND.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_BEND;
				}
				else if ( _stricmp( arg.c_str(), ".CONNECTOR.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_CONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".ENTRY.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_ENTRY;
				}
				else if ( _stricmp( arg.c_str(), ".EXIT.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_EXIT;
				}
				else if ( _stricmp( arg.c_str(), ".JUNCTION.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_JUNCTION;
				}
				else if ( _stricmp( arg.c_str(), ".OBSTRUCTION.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_OBSTRUCTION;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSITION.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_TRANSITION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcPipeFittingTypeEnum::IfcPipeFittingTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
