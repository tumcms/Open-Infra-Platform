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

#include "IfcFurnitureTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcFurnitureTypeEnum::IfcFurnitureTypeEnum() {}
		IfcFurnitureTypeEnum::IfcFurnitureTypeEnum(IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum value) { m_enum = value; }
		IfcFurnitureTypeEnum::~IfcFurnitureTypeEnum() {}
		void IfcFurnitureTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_CHAIR)
				{
					stream << ".CHAIR.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_TABLE)
				{
					stream << ".TABLE.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_DESK)
				{
					stream << ".DESK.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_BED)
				{
					stream << ".BED.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_FILECABINET)
				{
					stream << ".FILECABINET.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_SHELF)
				{
					stream << ".SHELF.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_SOFA)
				{
					stream << ".SOFA.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcFurnitureTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcFurnitureTypeEnum> IfcFurnitureTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcFurnitureTypeEnum>(); }
				std::shared_ptr<IfcFurnitureTypeEnum> type_object(new IfcFurnitureTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CHAIR.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_CHAIR;
				}
				else if ( _stricmp( arg.c_str(), ".TABLE.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_TABLE;
				}
				else if ( _stricmp( arg.c_str(), ".DESK.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_DESK;
				}
				else if ( _stricmp( arg.c_str(), ".BED.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_BED;
				}
				else if ( _stricmp( arg.c_str(), ".FILECABINET.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_FILECABINET;
				}
				else if ( _stricmp( arg.c_str(), ".SHELF.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_SHELF;
				}
				else if ( _stricmp( arg.c_str(), ".SOFA.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_SOFA;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcFurnitureTypeEnum::IfcFurnitureTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
