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

#include "IfcTendonAnchorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnum() {}
		IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnum(IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum value) { m_enum = value; }
		IfcTendonAnchorTypeEnum::~IfcTendonAnchorTypeEnum() {}
		void IfcTendonAnchorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTendonAnchorTypeEnumEnum::ENUM_COUPLER)
				{
					stream << ".COUPLER.";
				}
				else if ( m_enum == IfcTendonAnchorTypeEnumEnum::ENUM_FIXED_END)
				{
					stream << ".FIXED_END.";
				}
				else if ( m_enum == IfcTendonAnchorTypeEnumEnum::ENUM_TENSIONING_END)
				{
					stream << ".TENSIONING_END.";
				}
				else if ( m_enum == IfcTendonAnchorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcTendonAnchorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTendonAnchorTypeEnum> IfcTendonAnchorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTendonAnchorTypeEnum>(); }
				std::shared_ptr<IfcTendonAnchorTypeEnum> type_object(new IfcTendonAnchorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".COUPLER.") == 0)
				{
					type_object->m_enum = IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum::ENUM_COUPLER;
				}
				else if ( _stricmp( arg.c_str(), ".FIXED_END.") == 0)
				{
					type_object->m_enum = IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum::ENUM_FIXED_END;
				}
				else if ( _stricmp( arg.c_str(), ".TENSIONING_END.") == 0)
				{
					type_object->m_enum = IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum::ENUM_TENSIONING_END;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcTendonAnchorTypeEnum::IfcTendonAnchorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
