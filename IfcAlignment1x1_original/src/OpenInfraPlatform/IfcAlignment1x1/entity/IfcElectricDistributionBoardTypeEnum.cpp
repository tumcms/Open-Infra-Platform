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

#include "IfcElectricDistributionBoardTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnum() {}
		IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnum(IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum value) { m_enum = value; }
		IfcElectricDistributionBoardTypeEnum::~IfcElectricDistributionBoardTypeEnum() {}
		void IfcElectricDistributionBoardTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_CONSUMERUNIT)
				{
					stream << ".CONSUMERUNIT.";
				}
				else if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_DISTRIBUTIONBOARD)
				{
					stream << ".DISTRIBUTIONBOARD.";
				}
				else if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_MOTORCONTROLCENTRE)
				{
					stream << ".MOTORCONTROLCENTRE.";
				}
				else if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_SWITCHBOARD)
				{
					stream << ".SWITCHBOARD.";
				}
				else if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcElectricDistributionBoardTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElectricDistributionBoardTypeEnum> IfcElectricDistributionBoardTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElectricDistributionBoardTypeEnum>(); }
				std::shared_ptr<IfcElectricDistributionBoardTypeEnum> type_object(new IfcElectricDistributionBoardTypeEnum() );
				if ( _stricmp( arg.c_str(), ".CONSUMERUNIT.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_CONSUMERUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".DISTRIBUTIONBOARD.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_DISTRIBUTIONBOARD;
				}
				else if ( _stricmp( arg.c_str(), ".MOTORCONTROLCENTRE.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_MOTORCONTROLCENTRE;
				}
				else if ( _stricmp( arg.c_str(), ".SWITCHBOARD.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_SWITCHBOARD;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricDistributionBoardTypeEnum::IfcElectricDistributionBoardTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
