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

#include "IfcWasteTerminalTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnum() {}
		IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnum(IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum value) { m_enum = value; }
		IfcWasteTerminalTypeEnum::~IfcWasteTerminalTypeEnum() {}
		void IfcWasteTerminalTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_FLOORTRAP)
				{
					stream << ".FLOORTRAP.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_FLOORWASTE)
				{
					stream << ".FLOORWASTE.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_GULLYSUMP)
				{
					stream << ".GULLYSUMP.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_GULLYTRAP)
				{
					stream << ".GULLYTRAP.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_ROOFDRAIN)
				{
					stream << ".ROOFDRAIN.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_WASTEDISPOSALUNIT)
				{
					stream << ".WASTEDISPOSALUNIT.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_WASTETRAP)
				{
					stream << ".WASTETRAP.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcWasteTerminalTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcWasteTerminalTypeEnum> IfcWasteTerminalTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcWasteTerminalTypeEnum>(); }
				std::shared_ptr<IfcWasteTerminalTypeEnum> type_object(new IfcWasteTerminalTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FLOORTRAP.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_FLOORTRAP;
				}
				else if ( _stricmp( arg.c_str(), ".FLOORWASTE.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_FLOORWASTE;
				}
				else if ( _stricmp( arg.c_str(), ".GULLYSUMP.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_GULLYSUMP;
				}
				else if ( _stricmp( arg.c_str(), ".GULLYTRAP.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_GULLYTRAP;
				}
				else if ( _stricmp( arg.c_str(), ".ROOFDRAIN.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_ROOFDRAIN;
				}
				else if ( _stricmp( arg.c_str(), ".WASTEDISPOSALUNIT.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_WASTEDISPOSALUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".WASTETRAP.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_WASTETRAP;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcWasteTerminalTypeEnum::IfcWasteTerminalTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
