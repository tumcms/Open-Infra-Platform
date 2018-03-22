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

#include "IfcCondenserTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCondenserTypeEnum::IfcCondenserTypeEnum() {}
		IfcCondenserTypeEnum::IfcCondenserTypeEnum(IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum value) { m_enum = value; }
		IfcCondenserTypeEnum::~IfcCondenserTypeEnum() {}
		void IfcCondenserTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_AIRCOOLED)
				{
					stream << ".AIRCOOLED.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_EVAPORATIVECOOLED)
				{
					stream << ".EVAPORATIVECOOLED.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_WATERCOOLED)
				{
					stream << ".WATERCOOLED.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDBRAZEDPLATE)
				{
					stream << ".WATERCOOLEDBRAZEDPLATE.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDSHELLCOIL)
				{
					stream << ".WATERCOOLEDSHELLCOIL.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDSHELLTUBE)
				{
					stream << ".WATERCOOLEDSHELLTUBE.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDTUBEINTUBE)
				{
					stream << ".WATERCOOLEDTUBEINTUBE.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCondenserTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCondenserTypeEnum> IfcCondenserTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCondenserTypeEnum>(); }
				std::shared_ptr<IfcCondenserTypeEnum> type_object(new IfcCondenserTypeEnum() );
				if ( _stricmp( arg.c_str(), ".AIRCOOLED.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_AIRCOOLED;
				}
				else if ( _stricmp( arg.c_str(), ".EVAPORATIVECOOLED.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_EVAPORATIVECOOLED;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLED.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_WATERCOOLED;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLEDBRAZEDPLATE.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDBRAZEDPLATE;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLEDSHELLCOIL.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDSHELLCOIL;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLEDSHELLTUBE.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDSHELLTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".WATERCOOLEDTUBEINTUBE.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_WATERCOOLEDTUBEINTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCondenserTypeEnum::IfcCondenserTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
