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

#include "IfcEvaporatorTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnum() {}
		IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnum(IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum value) { m_enum = value; }
		IfcEvaporatorTypeEnum::~IfcEvaporatorTypeEnum() {}
		void IfcEvaporatorTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSION)
				{
					stream << ".DIRECTEXPANSION.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONSHELLANDTUBE)
				{
					stream << ".DIRECTEXPANSIONSHELLANDTUBE.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONTUBEINTUBE)
				{
					stream << ".DIRECTEXPANSIONTUBEINTUBE.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONBRAZEDPLATE)
				{
					stream << ".DIRECTEXPANSIONBRAZEDPLATE.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_FLOODEDSHELLANDTUBE)
				{
					stream << ".FLOODEDSHELLANDTUBE.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_SHELLANDCOIL)
				{
					stream << ".SHELLANDCOIL.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcEvaporatorTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcEvaporatorTypeEnum> IfcEvaporatorTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcEvaporatorTypeEnum>(); }
				std::shared_ptr<IfcEvaporatorTypeEnum> type_object(new IfcEvaporatorTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DIRECTEXPANSION.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSION;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEXPANSIONSHELLANDTUBE.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONSHELLANDTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEXPANSIONTUBEINTUBE.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONTUBEINTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".DIRECTEXPANSIONBRAZEDPLATE.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_DIRECTEXPANSIONBRAZEDPLATE;
				}
				else if ( _stricmp( arg.c_str(), ".FLOODEDSHELLANDTUBE.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_FLOODEDSHELLANDTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".SHELLANDCOIL.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_SHELLANDCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcEvaporatorTypeEnum::IfcEvaporatorTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
