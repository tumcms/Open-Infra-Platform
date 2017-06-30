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

#include "IfcStairTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcStairTypeEnum::IfcStairTypeEnum() {}
		IfcStairTypeEnum::IfcStairTypeEnum(IfcStairTypeEnum::IfcStairTypeEnumEnum value) { m_enum = value; }
		IfcStairTypeEnum::~IfcStairTypeEnum() {}
		void IfcStairTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcStairTypeEnumEnum::ENUM_STRAIGHT_RUN_STAIR)
				{
					stream << ".STRAIGHT_RUN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_TWO_STRAIGHT_RUN_STAIR)
				{
					stream << ".TWO_STRAIGHT_RUN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_QUARTER_WINDING_STAIR)
				{
					stream << ".QUARTER_WINDING_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_QUARTER_TURN_STAIR)
				{
					stream << ".QUARTER_TURN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_HALF_WINDING_STAIR)
				{
					stream << ".HALF_WINDING_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_HALF_TURN_STAIR)
				{
					stream << ".HALF_TURN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_TWO_QUARTER_WINDING_STAIR)
				{
					stream << ".TWO_QUARTER_WINDING_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_TWO_QUARTER_TURN_STAIR)
				{
					stream << ".TWO_QUARTER_TURN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_THREE_QUARTER_WINDING_STAIR)
				{
					stream << ".THREE_QUARTER_WINDING_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_THREE_QUARTER_TURN_STAIR)
				{
					stream << ".THREE_QUARTER_TURN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_SPIRAL_STAIR)
				{
					stream << ".SPIRAL_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_DOUBLE_RETURN_STAIR)
				{
					stream << ".DOUBLE_RETURN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_CURVED_RUN_STAIR)
				{
					stream << ".CURVED_RUN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_TWO_CURVED_RUN_STAIR)
				{
					stream << ".TWO_CURVED_RUN_STAIR.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcStairTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcStairTypeEnum> IfcStairTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcStairTypeEnum>(); }
				std::shared_ptr<IfcStairTypeEnum> type_object(new IfcStairTypeEnum() );
				if ( _stricmp( arg.c_str(), ".STRAIGHT_RUN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_STRAIGHT_RUN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".TWO_STRAIGHT_RUN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_TWO_STRAIGHT_RUN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".QUARTER_WINDING_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_QUARTER_WINDING_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".QUARTER_TURN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_QUARTER_TURN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".HALF_WINDING_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_HALF_WINDING_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".HALF_TURN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_HALF_TURN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".TWO_QUARTER_WINDING_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_TWO_QUARTER_WINDING_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".TWO_QUARTER_TURN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_TWO_QUARTER_TURN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".THREE_QUARTER_WINDING_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_THREE_QUARTER_WINDING_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".THREE_QUARTER_TURN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_THREE_QUARTER_TURN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".SPIRAL_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_SPIRAL_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_RETURN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_DOUBLE_RETURN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".CURVED_RUN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_CURVED_RUN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".TWO_CURVED_RUN_STAIR.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_TWO_CURVED_RUN_STAIR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcStairTypeEnum::IfcStairTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
