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

#include "IfcBuildingSystemTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnum() {}
		IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnum(IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum value) { m_enum = value; }
		IfcBuildingSystemTypeEnum::~IfcBuildingSystemTypeEnum() {}
		void IfcBuildingSystemTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_FENESTRATION)
				{
					stream << ".FENESTRATION.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_FOUNDATION)
				{
					stream << ".FOUNDATION.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_LOADBEARING)
				{
					stream << ".LOADBEARING.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_OUTERSHELL)
				{
					stream << ".OUTERSHELL.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_SHADING)
				{
					stream << ".SHADING.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_TRANSPORT)
				{
					stream << ".TRANSPORT.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcBuildingSystemTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcBuildingSystemTypeEnum> IfcBuildingSystemTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcBuildingSystemTypeEnum>(); }
				std::shared_ptr<IfcBuildingSystemTypeEnum> type_object(new IfcBuildingSystemTypeEnum() );
				if ( _stricmp( arg.c_str(), ".FENESTRATION.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_FENESTRATION;
				}
				else if ( _stricmp( arg.c_str(), ".FOUNDATION.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_FOUNDATION;
				}
				else if ( _stricmp( arg.c_str(), ".LOADBEARING.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_LOADBEARING;
				}
				else if ( _stricmp( arg.c_str(), ".OUTERSHELL.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_OUTERSHELL;
				}
				else if ( _stricmp( arg.c_str(), ".SHADING.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_SHADING;
				}
				else if ( _stricmp( arg.c_str(), ".TRANSPORT.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_TRANSPORT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcBuildingSystemTypeEnum::IfcBuildingSystemTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
