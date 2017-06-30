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

#include "IfcPileTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPileTypeEnum::IfcPileTypeEnum() {}
		IfcPileTypeEnum::IfcPileTypeEnum(IfcPileTypeEnum::IfcPileTypeEnumEnum value) { m_enum = value; }
		IfcPileTypeEnum::~IfcPileTypeEnum() {}
		void IfcPileTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcPileTypeEnumEnum::ENUM_BORED)
				{
					stream << ".BORED.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_DRIVEN)
				{
					stream << ".DRIVEN.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_JETGROUTING)
				{
					stream << ".JETGROUTING.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_COHESION)
				{
					stream << ".COHESION.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_FRICTION)
				{
					stream << ".FRICTION.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_SUPPORT)
				{
					stream << ".SUPPORT.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcPileTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcPileTypeEnum> IfcPileTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPileTypeEnum>(); }
				std::shared_ptr<IfcPileTypeEnum> type_object(new IfcPileTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BORED.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_BORED;
				}
				else if ( _stricmp( arg.c_str(), ".DRIVEN.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_DRIVEN;
				}
				else if ( _stricmp( arg.c_str(), ".JETGROUTING.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_JETGROUTING;
				}
				else if ( _stricmp( arg.c_str(), ".COHESION.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_COHESION;
				}
				else if ( _stricmp( arg.c_str(), ".FRICTION.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_FRICTION;
				}
				else if ( _stricmp( arg.c_str(), ".SUPPORT.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_SUPPORT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcPileTypeEnum::IfcPileTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
