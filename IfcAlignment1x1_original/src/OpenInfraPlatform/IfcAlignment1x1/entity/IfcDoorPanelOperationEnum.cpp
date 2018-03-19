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

#include "IfcDoorPanelOperationEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnum() {}
		IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnum(IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum value) { m_enum = value; }
		IfcDoorPanelOperationEnum::~IfcDoorPanelOperationEnum() {}
		void IfcDoorPanelOperationEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_SWINGING)
				{
					stream << ".SWINGING.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_DOUBLE_ACTING)
				{
					stream << ".DOUBLE_ACTING.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_SLIDING)
				{
					stream << ".SLIDING.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_FOLDING)
				{
					stream << ".FOLDING.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_REVOLVING)
				{
					stream << ".REVOLVING.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_ROLLINGUP)
				{
					stream << ".ROLLINGUP.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_FIXEDPANEL)
				{
					stream << ".FIXEDPANEL.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDoorPanelOperationEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDoorPanelOperationEnum> IfcDoorPanelOperationEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDoorPanelOperationEnum>(); }
				std::shared_ptr<IfcDoorPanelOperationEnum> type_object(new IfcDoorPanelOperationEnum() );
				if ( _stricmp( arg.c_str(), ".SWINGING.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_SWINGING;
				}
				else if ( _stricmp( arg.c_str(), ".DOUBLE_ACTING.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_DOUBLE_ACTING;
				}
				else if ( _stricmp( arg.c_str(), ".SLIDING.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_SLIDING;
				}
				else if ( _stricmp( arg.c_str(), ".FOLDING.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_FOLDING;
				}
				else if ( _stricmp( arg.c_str(), ".REVOLVING.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_REVOLVING;
				}
				else if ( _stricmp( arg.c_str(), ".ROLLINGUP.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_ROLLINGUP;
				}
				else if ( _stricmp( arg.c_str(), ".FIXEDPANEL.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_FIXEDPANEL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorPanelOperationEnum::IfcDoorPanelOperationEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
