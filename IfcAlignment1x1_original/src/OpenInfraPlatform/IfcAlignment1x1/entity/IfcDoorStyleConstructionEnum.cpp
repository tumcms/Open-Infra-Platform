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

#include "IfcDoorStyleConstructionEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnum() {}
		IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnum(IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum value) { m_enum = value; }
		IfcDoorStyleConstructionEnum::~IfcDoorStyleConstructionEnum() {}
		void IfcDoorStyleConstructionEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM)
				{
					stream << ".ALUMINIUM.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_HIGH_GRADE_STEEL)
				{
					stream << ".HIGH_GRADE_STEEL.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_STEEL)
				{
					stream << ".STEEL.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_WOOD)
				{
					stream << ".WOOD.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM_WOOD)
				{
					stream << ".ALUMINIUM_WOOD.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM_PLASTIC)
				{
					stream << ".ALUMINIUM_PLASTIC.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_PLASTIC)
				{
					stream << ".PLASTIC.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcDoorStyleConstructionEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDoorStyleConstructionEnum> IfcDoorStyleConstructionEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDoorStyleConstructionEnum>(); }
				std::shared_ptr<IfcDoorStyleConstructionEnum> type_object(new IfcDoorStyleConstructionEnum() );
				if ( _stricmp( arg.c_str(), ".ALUMINIUM.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM;
				}
				else if ( _stricmp( arg.c_str(), ".HIGH_GRADE_STEEL.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_HIGH_GRADE_STEEL;
				}
				else if ( _stricmp( arg.c_str(), ".STEEL.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_STEEL;
				}
				else if ( _stricmp( arg.c_str(), ".WOOD.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_WOOD;
				}
				else if ( _stricmp( arg.c_str(), ".ALUMINIUM_WOOD.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM_WOOD;
				}
				else if ( _stricmp( arg.c_str(), ".ALUMINIUM_PLASTIC.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_ALUMINIUM_PLASTIC;
				}
				else if ( _stricmp( arg.c_str(), ".PLASTIC.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_PLASTIC;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
