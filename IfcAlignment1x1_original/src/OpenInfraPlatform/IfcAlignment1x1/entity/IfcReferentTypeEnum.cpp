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

#include "IfcReferentTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcReferentTypeEnum::IfcReferentTypeEnum() {}
		IfcReferentTypeEnum::IfcReferentTypeEnum(IfcReferentTypeEnum::IfcReferentTypeEnumEnum value) { m_enum = value; }
		IfcReferentTypeEnum::~IfcReferentTypeEnum() {}
		void IfcReferentTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcReferentTypeEnumEnum::ENUM_KILOPOINT)
				{
					stream << ".KILOPOINT.";
				}
				else if ( m_enum == IfcReferentTypeEnumEnum::ENUM_MILEPOINT)
				{
					stream << ".MILEPOINT.";
				}
				else if ( m_enum == IfcReferentTypeEnumEnum::ENUM_STATION)
				{
					stream << ".STATION.";
				}
				else if ( m_enum == IfcReferentTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcReferentTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcReferentTypeEnum> IfcReferentTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcReferentTypeEnum>(); }
				std::shared_ptr<IfcReferentTypeEnum> type_object(new IfcReferentTypeEnum() );
				if ( _stricmp( arg.c_str(), ".KILOPOINT.") == 0)
				{
					type_object->m_enum = IfcReferentTypeEnum::IfcReferentTypeEnumEnum::ENUM_KILOPOINT;
				}
				else if ( _stricmp( arg.c_str(), ".MILEPOINT.") == 0)
				{
					type_object->m_enum = IfcReferentTypeEnum::IfcReferentTypeEnumEnum::ENUM_MILEPOINT;
				}
				else if ( _stricmp( arg.c_str(), ".STATION.") == 0)
				{
					type_object->m_enum = IfcReferentTypeEnum::IfcReferentTypeEnumEnum::ENUM_STATION;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcReferentTypeEnum::IfcReferentTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcReferentTypeEnum::IfcReferentTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
