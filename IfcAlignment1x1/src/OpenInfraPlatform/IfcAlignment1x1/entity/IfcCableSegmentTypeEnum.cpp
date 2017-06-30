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

#include "IfcCableSegmentTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnum() {}
		IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnum(IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum value) { m_enum = value; }
		IfcCableSegmentTypeEnum::~IfcCableSegmentTypeEnum() {}
		void IfcCableSegmentTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_BUSBARSEGMENT)
				{
					stream << ".BUSBARSEGMENT.";
				}
				else if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_CABLESEGMENT)
				{
					stream << ".CABLESEGMENT.";
				}
				else if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_CONDUCTORSEGMENT)
				{
					stream << ".CONDUCTORSEGMENT.";
				}
				else if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_CORESEGMENT)
				{
					stream << ".CORESEGMENT.";
				}
				else if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcCableSegmentTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcCableSegmentTypeEnum> IfcCableSegmentTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcCableSegmentTypeEnum>(); }
				std::shared_ptr<IfcCableSegmentTypeEnum> type_object(new IfcCableSegmentTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BUSBARSEGMENT.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_BUSBARSEGMENT;
				}
				else if ( _stricmp( arg.c_str(), ".CABLESEGMENT.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_CABLESEGMENT;
				}
				else if ( _stricmp( arg.c_str(), ".CONDUCTORSEGMENT.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_CONDUCTORSEGMENT;
				}
				else if ( _stricmp( arg.c_str(), ".CORESEGMENT.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_CORESEGMENT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcCableSegmentTypeEnum::IfcCableSegmentTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
