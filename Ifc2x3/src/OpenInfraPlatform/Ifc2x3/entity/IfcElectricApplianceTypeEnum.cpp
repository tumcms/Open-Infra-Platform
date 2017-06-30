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

#include <sstream>
#include <limits>
#include <map>
#include "reader/ReaderUtil.h"
#include "writer/WriterUtil.h"
#include "../model/shared_ptr.h"
#include "../model/Ifc2x3Exception.h"
#include "include/IfcElectricApplianceTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcElectricApplianceTypeEnum 
		IfcElectricApplianceTypeEnum::IfcElectricApplianceTypeEnum() {}
		IfcElectricApplianceTypeEnum::~IfcElectricApplianceTypeEnum() {}
		void IfcElectricApplianceTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCELECTRICAPPLIANCETYPEENUM("; }
			if( m_enum == ENUM_COMPUTER )
			{
				stream << ".COMPUTER.";
			}
			else if( m_enum == ENUM_DIRECTWATERHEATER )
			{
				stream << ".DIRECTWATERHEATER.";
			}
			else if( m_enum == ENUM_DISHWASHER )
			{
				stream << ".DISHWASHER.";
			}
			else if( m_enum == ENUM_ELECTRICCOOKER )
			{
				stream << ".ELECTRICCOOKER.";
			}
			else if( m_enum == ENUM_ELECTRICHEATER )
			{
				stream << ".ELECTRICHEATER.";
			}
			else if( m_enum == ENUM_FACSIMILE )
			{
				stream << ".FACSIMILE.";
			}
			else if( m_enum == ENUM_FREESTANDINGFAN )
			{
				stream << ".FREESTANDINGFAN.";
			}
			else if( m_enum == ENUM_FREEZER )
			{
				stream << ".FREEZER.";
			}
			else if( m_enum == ENUM_FRIDGE_FREEZER )
			{
				stream << ".FRIDGE_FREEZER.";
			}
			else if( m_enum == ENUM_HANDDRYER )
			{
				stream << ".HANDDRYER.";
			}
			else if( m_enum == ENUM_INDIRECTWATERHEATER )
			{
				stream << ".INDIRECTWATERHEATER.";
			}
			else if( m_enum == ENUM_MICROWAVE )
			{
				stream << ".MICROWAVE.";
			}
			else if( m_enum == ENUM_PHOTOCOPIER )
			{
				stream << ".PHOTOCOPIER.";
			}
			else if( m_enum == ENUM_PRINTER )
			{
				stream << ".PRINTER.";
			}
			else if( m_enum == ENUM_REFRIGERATOR )
			{
				stream << ".REFRIGERATOR.";
			}
			else if( m_enum == ENUM_RADIANTHEATER )
			{
				stream << ".RADIANTHEATER.";
			}
			else if( m_enum == ENUM_SCANNER )
			{
				stream << ".SCANNER.";
			}
			else if( m_enum == ENUM_TELEPHONE )
			{
				stream << ".TELEPHONE.";
			}
			else if( m_enum == ENUM_TUMBLEDRYER )
			{
				stream << ".TUMBLEDRYER.";
			}
			else if( m_enum == ENUM_TV )
			{
				stream << ".TV.";
			}
			else if( m_enum == ENUM_VENDINGMACHINE )
			{
				stream << ".VENDINGMACHINE.";
			}
			else if( m_enum == ENUM_WASHINGMACHINE )
			{
				stream << ".WASHINGMACHINE.";
			}
			else if( m_enum == ENUM_WATERHEATER )
			{
				stream << ".WATERHEATER.";
			}
			else if( m_enum == ENUM_WATERCOOLER )
			{
				stream << ".WATERCOOLER.";
			}
			else if( m_enum == ENUM_USERDEFINED )
			{
				stream << ".USERDEFINED.";
			}
			else if( m_enum == ENUM_NOTDEFINED )
			{
				stream << ".NOTDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcElectricApplianceTypeEnum> IfcElectricApplianceTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcElectricApplianceTypeEnum>(); }
			shared_ptr<IfcElectricApplianceTypeEnum> type_object( new IfcElectricApplianceTypeEnum() );
			if( _stricmp( arg.c_str(), ".COMPUTER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_COMPUTER;
			}
			else if( _stricmp( arg.c_str(), ".DIRECTWATERHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_DIRECTWATERHEATER;
			}
			else if( _stricmp( arg.c_str(), ".DISHWASHER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_DISHWASHER;
			}
			else if( _stricmp( arg.c_str(), ".ELECTRICCOOKER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_ELECTRICCOOKER;
			}
			else if( _stricmp( arg.c_str(), ".ELECTRICHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_ELECTRICHEATER;
			}
			else if( _stricmp( arg.c_str(), ".FACSIMILE." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_FACSIMILE;
			}
			else if( _stricmp( arg.c_str(), ".FREESTANDINGFAN." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_FREESTANDINGFAN;
			}
			else if( _stricmp( arg.c_str(), ".FREEZER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_FREEZER;
			}
			else if( _stricmp( arg.c_str(), ".FRIDGE_FREEZER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_FRIDGE_FREEZER;
			}
			else if( _stricmp( arg.c_str(), ".HANDDRYER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_HANDDRYER;
			}
			else if( _stricmp( arg.c_str(), ".INDIRECTWATERHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_INDIRECTWATERHEATER;
			}
			else if( _stricmp( arg.c_str(), ".MICROWAVE." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_MICROWAVE;
			}
			else if( _stricmp( arg.c_str(), ".PHOTOCOPIER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_PHOTOCOPIER;
			}
			else if( _stricmp( arg.c_str(), ".PRINTER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_PRINTER;
			}
			else if( _stricmp( arg.c_str(), ".REFRIGERATOR." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_REFRIGERATOR;
			}
			else if( _stricmp( arg.c_str(), ".RADIANTHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_RADIANTHEATER;
			}
			else if( _stricmp( arg.c_str(), ".SCANNER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_SCANNER;
			}
			else if( _stricmp( arg.c_str(), ".TELEPHONE." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_TELEPHONE;
			}
			else if( _stricmp( arg.c_str(), ".TUMBLEDRYER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_TUMBLEDRYER;
			}
			else if( _stricmp( arg.c_str(), ".TV." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_TV;
			}
			else if( _stricmp( arg.c_str(), ".VENDINGMACHINE." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_VENDINGMACHINE;
			}
			else if( _stricmp( arg.c_str(), ".WASHINGMACHINE." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_WASHINGMACHINE;
			}
			else if( _stricmp( arg.c_str(), ".WATERHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_WATERHEATER;
			}
			else if( _stricmp( arg.c_str(), ".WATERCOOLER." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_WATERCOOLER;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricApplianceTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
