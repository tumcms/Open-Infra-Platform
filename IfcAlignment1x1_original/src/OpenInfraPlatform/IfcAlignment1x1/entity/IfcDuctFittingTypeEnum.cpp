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

#include "IfcDuctFittingTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnum() {}
		IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnum(IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum value) { m_enum = value; }
		IfcDuctFittingTypeEnum::~IfcDuctFittingTypeEnum() {}
		void IfcDuctFittingTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_BEND)
				{
					stream << ".BEND.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_CONNECTOR)
				{
					stream << ".CONNECTOR.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_ENTRY)
				{
					stream << ".ENTRY.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_EXIT)
				{
					stream << ".EXIT.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_JUNCTION)
				{
					stream << ".JUNCTION.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_OBSTRUCTION)
				{
					stream << ".OBSTRUCTION.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_TRANSITION)
				{
					stream << ".TRANSITION.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDuctFittingTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDuctFittingTypeEnum> IfcDuctFittingTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDuctFittingTypeEnum>(); }
				std::shared_ptr<IfcDuctFittingTypeEnum> type_object(new IfcDuctFittingTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BEND.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_BEND;
				}
				else if ( _stricmp( arg.c_str(), ".CONNECTOR.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_CONNECTOR;
				}
				else if ( _stricmp( arg.c_str(), ".ENTRY.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_ENTRY;
				}
				else if ( _stricmp( arg.c_str(), ".EXIT.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_EXIT;
				}
				else if ( _stricmp( arg.c_str(), ".JUNCTION.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_JUNCTION;
				}
				else if ( _stricmp( arg.c_str(), ".OBSTRUCTION.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_OBSTRUCTION;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSITION.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_TRANSITION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDuctFittingTypeEnum::IfcDuctFittingTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
