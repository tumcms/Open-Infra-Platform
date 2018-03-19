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

#include "IfcElectricApplianceTypeEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnum() {}
		IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnum(IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum value) { m_enum = value; }
		IfcElectricApplianceTypeEnum::~IfcElectricApplianceTypeEnum() {}
		void IfcElectricApplianceTypeEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_DISHWASHER)
				{
					stream << ".DISHWASHER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_ELECTRICCOOKER)
				{
					stream << ".ELECTRICCOOKER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGELECTRICHEATER)
				{
					stream << ".FREESTANDINGELECTRICHEATER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGFAN)
				{
					stream << ".FREESTANDINGFAN.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGWATERHEATER)
				{
					stream << ".FREESTANDINGWATERHEATER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGWATERCOOLER)
				{
					stream << ".FREESTANDINGWATERCOOLER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FREEZER)
				{
					stream << ".FREEZER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_FRIDGE_FREEZER)
				{
					stream << ".FRIDGE_FREEZER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_HANDDRYER)
				{
					stream << ".HANDDRYER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_KITCHENMACHINE)
				{
					stream << ".KITCHENMACHINE.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_MICROWAVE)
				{
					stream << ".MICROWAVE.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_PHOTOCOPIER)
				{
					stream << ".PHOTOCOPIER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_REFRIGERATOR)
				{
					stream << ".REFRIGERATOR.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_TUMBLEDRYER)
				{
					stream << ".TUMBLEDRYER.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_VENDINGMACHINE)
				{
					stream << ".VENDINGMACHINE.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_WASHINGMACHINE)
				{
					stream << ".WASHINGMACHINE.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				else if ( m_enum == IfcElectricApplianceTypeEnumEnum::ENUM_NOTDEFINED)
				{
					stream << ".NOTDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcElectricApplianceTypeEnum> IfcElectricApplianceTypeEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcElectricApplianceTypeEnum>(); }
				std::shared_ptr<IfcElectricApplianceTypeEnum> type_object(new IfcElectricApplianceTypeEnum() );
				if ( _stricmp( arg.c_str(), ".DISHWASHER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_DISHWASHER;
				}
				else if ( _stricmp( arg.c_str(), ".ELECTRICCOOKER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_ELECTRICCOOKER;
				}
				else if ( _stricmp( arg.c_str(), ".FREESTANDINGELECTRICHEATER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGELECTRICHEATER;
				}
				else if ( _stricmp( arg.c_str(), ".FREESTANDINGFAN.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGFAN;
				}
				else if ( _stricmp( arg.c_str(), ".FREESTANDINGWATERHEATER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGWATERHEATER;
				}
				else if ( _stricmp( arg.c_str(), ".FREESTANDINGWATERCOOLER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FREESTANDINGWATERCOOLER;
				}
				else if ( _stricmp( arg.c_str(), ".FREEZER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FREEZER;
				}
				else if ( _stricmp( arg.c_str(), ".FRIDGE_FREEZER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_FRIDGE_FREEZER;
				}
				else if ( _stricmp( arg.c_str(), ".HANDDRYER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_HANDDRYER;
				}
				else if ( _stricmp( arg.c_str(), ".KITCHENMACHINE.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_KITCHENMACHINE;
				}
				else if ( _stricmp( arg.c_str(), ".MICROWAVE.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_MICROWAVE;
				}
				else if ( _stricmp( arg.c_str(), ".PHOTOCOPIER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_PHOTOCOPIER;
				}
				else if ( _stricmp( arg.c_str(), ".REFRIGERATOR.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_REFRIGERATOR;
				}
				else if ( _stricmp( arg.c_str(), ".TUMBLEDRYER.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_TUMBLEDRYER;
				}
				else if ( _stricmp( arg.c_str(), ".VENDINGMACHINE.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_VENDINGMACHINE;
				}
				else if ( _stricmp( arg.c_str(), ".WASHINGMACHINE.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_WASHINGMACHINE;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_USERDEFINED;
				}
				else if ( _stricmp( arg.c_str(), ".NOTDEFINED.") == 0)
				{
					type_object->m_enum = IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnumEnum::ENUM_NOTDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
