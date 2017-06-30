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

#include "IfcAddressTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcAddressTypeEnum::IfcAddressTypeEnum() {}
		IfcAddressTypeEnum::IfcAddressTypeEnum(IfcAddressTypeEnum::IfcAddressTypeEnumEnum value) { m_enum = value; }
		IfcAddressTypeEnum::~IfcAddressTypeEnum() {}
		void IfcAddressTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcAddressTypeEnumEnum::ENUM_OFFICE)
				{
					stream << ".OFFICE.";
				}
				else if ( m_enum == IfcAddressTypeEnumEnum::ENUM_SITE)
				{
					stream << ".SITE.";
				}
				else if ( m_enum == IfcAddressTypeEnumEnum::ENUM_HOME)
				{
					stream << ".HOME.";
				}
				else if ( m_enum == IfcAddressTypeEnumEnum::ENUM_DISTRIBUTIONPOINT)
				{
					stream << ".DISTRIBUTIONPOINT.";
				}
				else if ( m_enum == IfcAddressTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcAddressTypeEnum> IfcAddressTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcAddressTypeEnum>(); }
				std::shared_ptr<IfcAddressTypeEnum> type_object(new IfcAddressTypeEnum() );
				if ( _stricmp( arg.c_str(), ".OFFICE.") == 0)
				{
					type_object->m_enum = IfcAddressTypeEnum::IfcAddressTypeEnumEnum::ENUM_OFFICE;
				}
				else if ( _stricmp( arg.c_str(), ".SITE.") == 0)
				{
					type_object->m_enum = IfcAddressTypeEnum::IfcAddressTypeEnumEnum::ENUM_SITE;
				}
				else if ( _stricmp( arg.c_str(), ".HOME.") == 0)
				{
					type_object->m_enum = IfcAddressTypeEnum::IfcAddressTypeEnumEnum::ENUM_HOME;
				}
				else if ( _stricmp( arg.c_str(), ".DISTRIBUTIONPOINT.") == 0)
				{
					type_object->m_enum = IfcAddressTypeEnum::IfcAddressTypeEnumEnum::ENUM_DISTRIBUTIONPOINT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcAddressTypeEnum::IfcAddressTypeEnumEnum::ENUM_USERDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
