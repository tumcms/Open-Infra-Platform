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

#include "IfcLogicalOperatorEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcLogicalOperatorEnum::IfcLogicalOperatorEnum() {}
		IfcLogicalOperatorEnum::IfcLogicalOperatorEnum(IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum value) { m_enum = value; }
		IfcLogicalOperatorEnum::~IfcLogicalOperatorEnum() {}
		void IfcLogicalOperatorEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcLogicalOperatorEnumEnum::ENUM_LOGICALAND)
				{
					stream << ".LOGICALAND.";
				}
				else if ( m_enum == IfcLogicalOperatorEnumEnum::ENUM_LOGICALOR)
				{
					stream << ".LOGICALOR.";
				}
				else if ( m_enum == IfcLogicalOperatorEnumEnum::ENUM_LOGICALXOR)
				{
					stream << ".LOGICALXOR.";
				}
				else if ( m_enum == IfcLogicalOperatorEnumEnum::ENUM_LOGICALNOTAND)
				{
					stream << ".LOGICALNOTAND.";
				}
				else if ( m_enum == IfcLogicalOperatorEnumEnum::ENUM_LOGICALNOTOR)
				{
					stream << ".LOGICALNOTOR.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcLogicalOperatorEnum> IfcLogicalOperatorEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcLogicalOperatorEnum>(); }
				std::shared_ptr<IfcLogicalOperatorEnum> type_object(new IfcLogicalOperatorEnum() );
				if ( _stricmp( arg.c_str(), ".LOGICALAND.") == 0)
				{
					type_object->m_enum = IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum::ENUM_LOGICALAND;
				}
				else if ( _stricmp( arg.c_str(), ".LOGICALOR.") == 0)
				{
					type_object->m_enum = IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum::ENUM_LOGICALOR;
				}
				else if ( _stricmp( arg.c_str(), ".LOGICALXOR.") == 0)
				{
					type_object->m_enum = IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum::ENUM_LOGICALXOR;
				}
				else if ( _stricmp( arg.c_str(), ".LOGICALNOTAND.") == 0)
				{
					type_object->m_enum = IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum::ENUM_LOGICALNOTAND;
				}
				else if ( _stricmp( arg.c_str(), ".LOGICALNOTOR.") == 0)
				{
					type_object->m_enum = IfcLogicalOperatorEnum::IfcLogicalOperatorEnumEnum::ENUM_LOGICALNOTOR;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
