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

#include "IfcTransportElementTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcTransportElementTypeEnum::IfcTransportElementTypeEnum() {}
		IfcTransportElementTypeEnum::IfcTransportElementTypeEnum(IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum value) { m_enum = value; }
		IfcTransportElementTypeEnum::~IfcTransportElementTypeEnum() {}
		void IfcTransportElementTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_ELEVATOR)
				{
					stream << ".ELEVATOR.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_ESCALATOR)
				{
					stream << ".ESCALATOR.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_MOVINGWALKWAY)
				{
					stream << ".MOVINGWALKWAY.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_CRANEWAY)
				{
					stream << ".CRANEWAY.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_LIFTINGGEAR)
				{
					stream << ".LIFTINGGEAR.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcTransportElementTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcTransportElementTypeEnum> IfcTransportElementTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcTransportElementTypeEnum>(); }
				std::shared_ptr<IfcTransportElementTypeEnum> type_object(new IfcTransportElementTypeEnum() );
				if ( _stricmp( arg.c_str(), ".ELEVATOR.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_ELEVATOR;
				}
				else if ( _stricmp( arg.c_str(), ".ESCALATOR.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_ESCALATOR;
				}
				else if ( _stricmp( arg.c_str(), ".MOVINGWALKWAY.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_MOVINGWALKWAY;
				}
				else if ( _stricmp( arg.c_str(), ".CRANEWAY.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_CRANEWAY;
				}
				else if ( _stricmp( arg.c_str(), ".LIFTINGGEAR.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_LIFTINGGEAR;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcTransportElementTypeEnum::IfcTransportElementTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
