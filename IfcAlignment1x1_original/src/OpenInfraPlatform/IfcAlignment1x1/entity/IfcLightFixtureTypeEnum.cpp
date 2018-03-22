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

#include "IfcLightFixtureTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnum() {}
		IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnum(IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum value) { m_enum = value; }
		IfcLightFixtureTypeEnum::~IfcLightFixtureTypeEnum() {}
		void IfcLightFixtureTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcLightFixtureTypeEnumEnum::ENUM_POINTSOURCE)
				{
					stream << ".POINTSOURCE.";
				}
				else if ( m_enum == IfcLightFixtureTypeEnumEnum::ENUM_DIRECTIONSOURCE)
				{
					stream << ".DIRECTIONSOURCE.";
				}
				else if ( m_enum == IfcLightFixtureTypeEnumEnum::ENUM_SECURITYLIGHTING)
				{
					stream << ".SECURITYLIGHTING.";
				}
				else if ( m_enum == IfcLightFixtureTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcLightFixtureTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcLightFixtureTypeEnum> IfcLightFixtureTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcLightFixtureTypeEnum>(); }
				std::shared_ptr<IfcLightFixtureTypeEnum> type_object(new IfcLightFixtureTypeEnum() );
				if ( _stricmp( arg.c_str(), ".POINTSOURCE.") == 0)
				{
					type_object->m_enum = IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum::ENUM_POINTSOURCE;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTIONSOURCE.") == 0)
				{
					type_object->m_enum = IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum::ENUM_DIRECTIONSOURCE;
				}
				else if ( _stricmp( arg.c_str(), ".SECURITYLIGHTING.") == 0)
				{
					type_object->m_enum = IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum::ENUM_SECURITYLIGHTING;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcLightFixtureTypeEnum::IfcLightFixtureTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
