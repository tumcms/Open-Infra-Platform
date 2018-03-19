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

#include "IfcFootingTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcFootingTypeEnum::IfcFootingTypeEnum() {}
		IfcFootingTypeEnum::IfcFootingTypeEnum(IfcFootingTypeEnum::IfcFootingTypeEnumEnum value) { m_enum = value; }
		IfcFootingTypeEnum::~IfcFootingTypeEnum() {}
		void IfcFootingTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcFootingTypeEnumEnum::ENUM_CAISSON_FOUNDATION)
				{
					stream << ".CAISSON_FOUNDATION.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_FOOTING_BEAM)
				{
					stream << ".FOOTING_BEAM.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_PAD_FOOTING)
				{
					stream << ".PAD_FOOTING.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_PILE_CAP)
				{
					stream << ".PILE_CAP.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_STRIP_FOOTING)
				{
					stream << ".STRIP_FOOTING.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcFootingTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcFootingTypeEnum> IfcFootingTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcFootingTypeEnum>(); }
				std::shared_ptr<IfcFootingTypeEnum> type_object(new IfcFootingTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CAISSON_FOUNDATION.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_CAISSON_FOUNDATION;
				}
				else if ( _stricmp( arg.c_str(), ".FOOTING_BEAM.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_FOOTING_BEAM;
				}
				else if ( _stricmp( arg.c_str(), ".PAD_FOOTING.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_PAD_FOOTING;
				}
				else if ( _stricmp( arg.c_str(), ".PILE_CAP.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_PILE_CAP;
				}
				else if ( _stricmp( arg.c_str(), ".STRIP_FOOTING.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_STRIP_FOOTING;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcFootingTypeEnum::IfcFootingTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
