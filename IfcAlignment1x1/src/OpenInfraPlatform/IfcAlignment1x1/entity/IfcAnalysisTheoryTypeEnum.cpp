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

#include "IfcAnalysisTheoryTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnum() {}
		IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnum(IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum value) { m_enum = value; }
		IfcAnalysisTheoryTypeEnum::~IfcAnalysisTheoryTypeEnum() {}
		void IfcAnalysisTheoryTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_FIRST_ORDER_THEORY)
				{
					stream << ".FIRST_ORDER_THEORY.";
				}
				else if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_SECOND_ORDER_THEORY)
				{
					stream << ".SECOND_ORDER_THEORY.";
				}
				else if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_THIRD_ORDER_THEORY)
				{
					stream << ".THIRD_ORDER_THEORY.";
				}
				else if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_FULL_NONLINEAR_THEORY)
				{
					stream << ".FULL_NONLINEAR_THEORY.";
				}
				else if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcAnalysisTheoryTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAnalysisTheoryTypeEnum> IfcAnalysisTheoryTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAnalysisTheoryTypeEnum>(); }
				std::shared_ptr<IfcAnalysisTheoryTypeEnum> type_object(new IfcAnalysisTheoryTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FIRST_ORDER_THEORY.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_FIRST_ORDER_THEORY;
				}
				else if ( _stricmp( arg.c_str(), ".SECOND_ORDER_THEORY.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_SECOND_ORDER_THEORY;
				}
				else if ( _stricmp( arg.c_str(), ".THIRD_ORDER_THEORY.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_THIRD_ORDER_THEORY;
				}
				else if ( _stricmp( arg.c_str(), ".FULL_NONLINEAR_THEORY.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_FULL_NONLINEAR_THEORY;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcAnalysisTheoryTypeEnum::IfcAnalysisTheoryTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
