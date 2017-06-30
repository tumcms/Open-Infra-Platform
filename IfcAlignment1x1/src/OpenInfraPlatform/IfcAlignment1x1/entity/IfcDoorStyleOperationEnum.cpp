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

#include "IfcDoorStyleOperationEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnum() {}
		IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnum(IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum value) { m_enum = value; }
		IfcDoorStyleOperationEnum::~IfcDoorStyleOperationEnum() {}
		void IfcDoorStyleOperationEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_SINGLE_SWING_LEFT)
				{
					stream << ".SINGLE_SWING_LEFT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_SINGLE_SWING_RIGHT)
				{
					stream << ".SINGLE_SWING_RIGHT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING)
				{
					stream << ".DOUBLE_DOOR_SINGLE_SWING.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT)
				{
					stream << ".DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT)
				{
					stream << ".DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_SWING_LEFT)
				{
					stream << ".DOUBLE_SWING_LEFT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_SWING_RIGHT)
				{
					stream << ".DOUBLE_SWING_RIGHT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_DOUBLE_SWING)
				{
					stream << ".DOUBLE_DOOR_DOUBLE_SWING.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_SLIDING_TO_LEFT)
				{
					stream << ".SLIDING_TO_LEFT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_SLIDING_TO_RIGHT)
				{
					stream << ".SLIDING_TO_RIGHT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SLIDING)
				{
					stream << ".DOUBLE_DOOR_SLIDING.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_FOLDING_TO_LEFT)
				{
					stream << ".FOLDING_TO_LEFT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_FOLDING_TO_RIGHT)
				{
					stream << ".FOLDING_TO_RIGHT.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_FOLDING)
				{
					stream << ".DOUBLE_DOOR_FOLDING.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_REVOLVING)
				{
					stream << ".REVOLVING.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_ROLLINGUP)
				{
					stream << ".ROLLINGUP.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDoorStyleOperationEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDoorStyleOperationEnum> IfcDoorStyleOperationEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDoorStyleOperationEnum>(); }
				std::shared_ptr<IfcDoorStyleOperationEnum> type_object(new IfcDoorStyleOperationEnum() );
				if ( _stricmp( arg.c_str(), ".SINGLE_SWING_LEFT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_SINGLE_SWING_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".SINGLE_SWING_RIGHT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_SINGLE_SWING_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_SINGLE_SWING.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_SWING_LEFT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_SWING_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_SWING_RIGHT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_SWING_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_DOUBLE_SWING.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_DOUBLE_SWING;
				}
				else if ( _stricmp( arg.c_str(), ".SLIDING_TO_LEFT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_SLIDING_TO_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".SLIDING_TO_RIGHT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_SLIDING_TO_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_SLIDING.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_SLIDING;
				}
				else if ( _stricmp( arg.c_str(), ".FOLDING_TO_LEFT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_FOLDING_TO_LEFT;
				}
				else if ( _stricmp( arg.c_str(), ".FOLDING_TO_RIGHT.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_FOLDING_TO_RIGHT;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_DOOR_FOLDING.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_DOUBLE_DOOR_FOLDING;
				}
				else if ( _stricmp( arg.c_str(), ".REVOLVING.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_REVOLVING;
				}
				else if ( _stricmp( arg.c_str(), ".ROLLINGUP.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_ROLLINGUP;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorStyleOperationEnum::IfcDoorStyleOperationEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
