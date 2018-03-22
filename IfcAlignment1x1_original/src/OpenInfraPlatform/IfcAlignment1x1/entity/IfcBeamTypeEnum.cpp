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

#include "IfcBeamTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcBeamTypeEnum::IfcBeamTypeEnum() {}
		IfcBeamTypeEnum::IfcBeamTypeEnum(IfcBeamTypeEnum::IfcBeamTypeEnumEnum value) { m_enum = value; }
		IfcBeamTypeEnum::~IfcBeamTypeEnum() {}
		void IfcBeamTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcBeamTypeEnumEnum::ENUM_BEAM)
				{
					stream << ".BEAM.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_JOIST)
				{
					stream << ".JOIST.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_HOLLOWCORE)
				{
					stream << ".HOLLOWCORE.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_LINTEL)
				{
					stream << ".LINTEL.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_SPANDREL)
				{
					stream << ".SPANDREL.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_T_BEAM)
				{
					stream << ".T_BEAM.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcBeamTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcBeamTypeEnum> IfcBeamTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcBeamTypeEnum>(); }
				std::shared_ptr<IfcBeamTypeEnum> type_object(new IfcBeamTypeEnum() );
				if ( _stricmp( arg.c_str(), ".BEAM.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_BEAM;
				}
				else if ( _stricmp( arg.c_str(), ".JOIST.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_JOIST;
				}
				else if ( _stricmp( arg.c_str(), ".HOLLOWCORE.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_HOLLOWCORE;
				}
				else if ( _stricmp( arg.c_str(), ".LINTEL.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_LINTEL;
				}
				else if ( _stricmp( arg.c_str(), ".SPANDREL.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_SPANDREL;
				}
				else if ( _stricmp( arg.c_str(), ".T_BEAM.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_T_BEAM;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcBeamTypeEnum::IfcBeamTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
