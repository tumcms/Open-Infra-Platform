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

#include "IfcGridTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcGridTypeEnum::IfcGridTypeEnum() {}
		IfcGridTypeEnum::IfcGridTypeEnum(IfcGridTypeEnum::IfcGridTypeEnumEnum value) { m_enum = value; }
		IfcGridTypeEnum::~IfcGridTypeEnum() {}
		void IfcGridTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcGridTypeEnumEnum::ENUM_RECTANGULAR)
				{
					stream << ".RECTANGULAR.";
				}
				else if ( m_enum == IfcGridTypeEnumEnum::ENUM_RADIAL)
				{
					stream << ".RADIAL.";
				}
				else if ( m_enum == IfcGridTypeEnumEnum::ENUM_TRIANGULAR)
				{
					stream << ".TRIANGULAR.";
				}
				else if ( m_enum == IfcGridTypeEnumEnum::ENUM_IRREGULAR)
				{
					stream << ".IRREGULAR.";
				}
				else if ( m_enum == IfcGridTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcGridTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcGridTypeEnum> IfcGridTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcGridTypeEnum>(); }
				std::shared_ptr<IfcGridTypeEnum> type_object(new IfcGridTypeEnum() );
				if ( _stricmp( arg.c_str(), ".RECTANGULAR.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_RECTANGULAR;
				}
				else if ( _stricmp( arg.c_str(), ".RADIAL.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_RADIAL;
				}
				else if ( _stricmp( arg.c_str(), ".TRIANGULAR.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_TRIANGULAR;
				}
				else if ( _stricmp( arg.c_str(), ".IRREGULAR.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_IRREGULAR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcGridTypeEnum::IfcGridTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
