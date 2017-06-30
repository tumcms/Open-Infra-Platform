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
#include "../model/IfcTunnelException.h"
#include "include/IfcUnitaryEquipmentTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcUnitaryEquipmentTypeEnum 
		IfcUnitaryEquipmentTypeEnum::IfcUnitaryEquipmentTypeEnum() {}
		IfcUnitaryEquipmentTypeEnum::~IfcUnitaryEquipmentTypeEnum() {}
		void IfcUnitaryEquipmentTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCUNITARYEQUIPMENTTYPEENUM("; }
			if( m_enum == ENUM_AIRHANDLER )
			{
				stream << ".AIRHANDLER.";
			}
			else if( m_enum == ENUM_AIRCONDITIONINGUNIT )
			{
				stream << ".AIRCONDITIONINGUNIT.";
			}
			else if( m_enum == ENUM_DEHUMIDIFIER )
			{
				stream << ".DEHUMIDIFIER.";
			}
			else if( m_enum == ENUM_SPLITSYSTEM )
			{
				stream << ".SPLITSYSTEM.";
			}
			else if( m_enum == ENUM_ROOFTOPUNIT )
			{
				stream << ".ROOFTOPUNIT.";
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
		shared_ptr<IfcUnitaryEquipmentTypeEnum> IfcUnitaryEquipmentTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcUnitaryEquipmentTypeEnum>(); }
			shared_ptr<IfcUnitaryEquipmentTypeEnum> type_object( new IfcUnitaryEquipmentTypeEnum() );
			if( _stricmp( arg.c_str(), ".AIRHANDLER." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_AIRHANDLER;
			}
			else if( _stricmp( arg.c_str(), ".AIRCONDITIONINGUNIT." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_AIRCONDITIONINGUNIT;
			}
			else if( _stricmp( arg.c_str(), ".DEHUMIDIFIER." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_DEHUMIDIFIER;
			}
			else if( _stricmp( arg.c_str(), ".SPLITSYSTEM." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_SPLITSYSTEM;
			}
			else if( _stricmp( arg.c_str(), ".ROOFTOPUNIT." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_ROOFTOPUNIT;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcUnitaryEquipmentTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
