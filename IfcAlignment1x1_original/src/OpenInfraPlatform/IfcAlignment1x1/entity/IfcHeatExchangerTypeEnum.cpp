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

#include "IfcHeatExchangerTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnum() {}
		IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnum(IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnumEnum value) { m_enum = value; }
		IfcHeatExchangerTypeEnum::~IfcHeatExchangerTypeEnum() {}
		void IfcHeatExchangerTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcHeatExchangerTypeEnumEnum::ENUM_PLATE)
				{
					stream << ".PLATE.";
				}
				else if ( m_enum == IfcHeatExchangerTypeEnumEnum::ENUM_SHELLANDTUBE)
				{
					stream << ".SHELLANDTUBE.";
				}
				else if ( m_enum == IfcHeatExchangerTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcHeatExchangerTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcHeatExchangerTypeEnum> IfcHeatExchangerTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcHeatExchangerTypeEnum>(); }
				std::shared_ptr<IfcHeatExchangerTypeEnum> type_object(new IfcHeatExchangerTypeEnum() );
				if ( _stricmp( arg.c_str(), ".PLATE.") == 0)
				{
					type_object->m_enum = IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnumEnum::ENUM_PLATE;
				}
				else if ( _stricmp( arg.c_str(), ".SHELLANDTUBE.") == 0)
				{
					type_object->m_enum = IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnumEnum::ENUM_SHELLANDTUBE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcHeatExchangerTypeEnum::IfcHeatExchangerTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
