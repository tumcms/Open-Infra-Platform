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

#include "IfcPileConstructionEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcPileConstructionEnum::IfcPileConstructionEnum() {}
		IfcPileConstructionEnum::IfcPileConstructionEnum(IfcPileConstructionEnum::IfcPileConstructionEnumEnum value) { m_enum = value; }
		IfcPileConstructionEnum::~IfcPileConstructionEnum() {}
		void IfcPileConstructionEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcPileConstructionEnumEnum::ENUM_CAST_IN_PLACE)
				{
					stream << ".CAST_IN_PLACE.";
				}
				else if ( m_enum == IfcPileConstructionEnumEnum::ENUM_COMPOSITE)
				{
					stream << ".COMPOSITE.";
				}
				else if ( m_enum == IfcPileConstructionEnumEnum::ENUM_PRECAST_CONCRETE)
				{
					stream << ".PRECAST_CONCRETE.";
				}
				else if ( m_enum == IfcPileConstructionEnumEnum::ENUM_PREFAB_STEEL)
				{
					stream << ".PREFAB_STEEL.";
				}
				else if ( m_enum == IfcPileConstructionEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcPileConstructionEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcPileConstructionEnum> IfcPileConstructionEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcPileConstructionEnum>(); }
				std::shared_ptr<IfcPileConstructionEnum> type_object(new IfcPileConstructionEnum() );
				if ( _stricmp( arg.c_str(), ".CAST_IN_PLACE.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_CAST_IN_PLACE;
				}
				else if ( _stricmp( arg.c_str(), ".COMPOSITE.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_COMPOSITE;
				}
				else if ( _stricmp( arg.c_str(), ".PRECAST_CONCRETE.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_PRECAST_CONCRETE;
				}
				else if ( _stricmp( arg.c_str(), ".PREFAB_STEEL.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_PREFAB_STEEL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcPileConstructionEnum::IfcPileConstructionEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
