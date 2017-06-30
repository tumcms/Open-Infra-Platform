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

#include "IfcSlabTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcSlabTypeEnum::IfcSlabTypeEnum() {}
		IfcSlabTypeEnum::IfcSlabTypeEnum(IfcSlabTypeEnum::IfcSlabTypeEnumEnum value) { m_enum = value; }
		IfcSlabTypeEnum::~IfcSlabTypeEnum() {}
		void IfcSlabTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcSlabTypeEnumEnum::ENUM_FLOOR)
				{
					stream << ".FLOOR.";
				}
				else if ( m_enum == IfcSlabTypeEnumEnum::ENUM_ROOF)
				{
					stream << ".ROOF.";
				}
				else if ( m_enum == IfcSlabTypeEnumEnum::ENUM_LANDING)
				{
					stream << ".LANDING.";
				}
				else if ( m_enum == IfcSlabTypeEnumEnum::ENUM_BASESLAB)
				{
					stream << ".BASESLAB.";
				}
				else if ( m_enum == IfcSlabTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcSlabTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcSlabTypeEnum> IfcSlabTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcSlabTypeEnum>(); }
				std::shared_ptr<IfcSlabTypeEnum> type_object(new IfcSlabTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FLOOR.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_FLOOR;
				}
				else if ( _stricmp( arg.c_str(), ".ROOF.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_ROOF;
				}
				else if ( _stricmp( arg.c_str(), ".LANDING.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_LANDING;
				}
				else if ( _stricmp( arg.c_str(), ".BASESLAB.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_BASESLAB;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcSlabTypeEnum::IfcSlabTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
