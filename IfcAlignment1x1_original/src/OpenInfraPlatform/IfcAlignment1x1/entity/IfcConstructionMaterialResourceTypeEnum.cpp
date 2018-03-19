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

#include "IfcConstructionMaterialResourceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnum() {}
		IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnum(IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum value) { m_enum = value; }
		IfcConstructionMaterialResourceTypeEnum::~IfcConstructionMaterialResourceTypeEnum() {}
		void IfcConstructionMaterialResourceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_AGGREGATES)
				{
					stream << ".AGGREGATES.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_CONCRETE)
				{
					stream << ".CONCRETE.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_DRYWALL)
				{
					stream << ".DRYWALL.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_FUEL)
				{
					stream << ".FUEL.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_GYPSUM)
				{
					stream << ".GYPSUM.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_MASONRY)
				{
					stream << ".MASONRY.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_METAL)
				{
					stream << ".METAL.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_PLASTIC)
				{
					stream << ".PLASTIC.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_WOOD)
				{
					stream << ".WOOD.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				else if ( m_enum == IfcConstructionMaterialResourceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcConstructionMaterialResourceTypeEnum> IfcConstructionMaterialResourceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcConstructionMaterialResourceTypeEnum>(); }
				std::shared_ptr<IfcConstructionMaterialResourceTypeEnum> type_object(new IfcConstructionMaterialResourceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".AGGREGATES.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_AGGREGATES;
				}
				else if ( _stricmp( arg.c_str(), ".CONCRETE.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_CONCRETE;
				}
				else if ( _stricmp( arg.c_str(), ".DRYWALL.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_DRYWALL;
				}
				else if ( _stricmp( arg.c_str(), ".FUEL.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_FUEL;
				}
				else if ( _stricmp( arg.c_str(), ".GYPSUM.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_GYPSUM;
				}
				else if ( _stricmp( arg.c_str(), ".MASONRY.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_MASONRY;
				}
				else if ( _stricmp( arg.c_str(), ".METAL.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_METAL;
				}
				else if ( _stricmp( arg.c_str(), ".PLASTIC.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_PLASTIC;
				}
				else if ( _stricmp( arg.c_str(), ".WOOD.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_WOOD;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcConstructionMaterialResourceTypeEnum::IfcConstructionMaterialResourceTypeEnumEnum::ENUM_USERDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
