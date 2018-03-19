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

#include "IfcWallTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcWallTypeEnum::IfcWallTypeEnum() {}
		IfcWallTypeEnum::IfcWallTypeEnum(IfcWallTypeEnum::IfcWallTypeEnumEnum value) { m_enum = value; }
		IfcWallTypeEnum::~IfcWallTypeEnum() {}
		void IfcWallTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcWallTypeEnumEnum::ENUM_MOVABLE)
				{
					stream << ".MOVABLE.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_PARAPET)
				{
					stream << ".PARAPET.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_PARTITIONING)
				{
					stream << ".PARTITIONING.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_PLUMBINGWALL)
				{
					stream << ".PLUMBINGWALL.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_SHEAR)
				{
					stream << ".SHEAR.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_SOLIDWALL)
				{
					stream << ".SOLIDWALL.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_STANDARD)
				{
					stream << ".STANDARD.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_POLYGONAL)
				{
					stream << ".POLYGONAL.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_ELEMENTEDWALL)
				{
					stream << ".ELEMENTEDWALL.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcWallTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcWallTypeEnum> IfcWallTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcWallTypeEnum>(); }
				std::shared_ptr<IfcWallTypeEnum> type_object(new IfcWallTypeEnum() );
				if ( _stricmp( arg.c_str(), ".MOVABLE.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_MOVABLE;
				}
				else if ( _stricmp( arg.c_str(), ".PARAPET.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_PARAPET;
				}
				else if ( _stricmp( arg.c_str(), ".PARTITIONING.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_PARTITIONING;
				}
				else if ( _stricmp( arg.c_str(), ".PLUMBINGWALL.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_PLUMBINGWALL;
				}
				else if ( _stricmp( arg.c_str(), ".SHEAR.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_SHEAR;
				}
				else if ( _stricmp( arg.c_str(), ".SOLIDWALL.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_SOLIDWALL;
				}
				else if ( _stricmp( arg.c_str(), ".STANDARD.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_STANDARD;
				}
				else if ( _stricmp( arg.c_str(), ".POLYGONAL.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_POLYGONAL;
				}
				else if ( _stricmp( arg.c_str(), ".ELEMENTEDWALL.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_ELEMENTEDWALL;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcWallTypeEnum::IfcWallTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
