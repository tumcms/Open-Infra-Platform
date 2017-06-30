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
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "include/IfcConstructionEquipmentResourceTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcConstructionEquipmentResourceTypeEnum 
		IfcConstructionEquipmentResourceTypeEnum::IfcConstructionEquipmentResourceTypeEnum() {}
		IfcConstructionEquipmentResourceTypeEnum::~IfcConstructionEquipmentResourceTypeEnum() {}
		void IfcConstructionEquipmentResourceTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCONSTRUCTIONEQUIPMENTRESOURCETYPEENUM("; }
			if( m_enum == ENUM_DEMOLISHING )
			{
				stream << ".DEMOLISHING.";
			}
			else if( m_enum == ENUM_EARTHMOVING )
			{
				stream << ".EARTHMOVING.";
			}
			else if( m_enum == ENUM_ERECTING )
			{
				stream << ".ERECTING.";
			}
			else if( m_enum == ENUM_HEATING )
			{
				stream << ".HEATING.";
			}
			else if( m_enum == ENUM_LIGHTING )
			{
				stream << ".LIGHTING.";
			}
			else if( m_enum == ENUM_PAVING )
			{
				stream << ".PAVING.";
			}
			else if( m_enum == ENUM_PUMPING )
			{
				stream << ".PUMPING.";
			}
			else if( m_enum == ENUM_TRANSPORTING )
			{
				stream << ".TRANSPORTING.";
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
		shared_ptr<IfcConstructionEquipmentResourceTypeEnum> IfcConstructionEquipmentResourceTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcConstructionEquipmentResourceTypeEnum>(); }
			shared_ptr<IfcConstructionEquipmentResourceTypeEnum> type_object( new IfcConstructionEquipmentResourceTypeEnum() );
			if( _stricmp( arg.c_str(), ".DEMOLISHING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_DEMOLISHING;
			}
			else if( _stricmp( arg.c_str(), ".EARTHMOVING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_EARTHMOVING;
			}
			else if( _stricmp( arg.c_str(), ".ERECTING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_ERECTING;
			}
			else if( _stricmp( arg.c_str(), ".HEATING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_HEATING;
			}
			else if( _stricmp( arg.c_str(), ".LIGHTING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_LIGHTING;
			}
			else if( _stricmp( arg.c_str(), ".PAVING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_PAVING;
			}
			else if( _stricmp( arg.c_str(), ".PUMPING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_PUMPING;
			}
			else if( _stricmp( arg.c_str(), ".TRANSPORTING." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_TRANSPORTING;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcConstructionEquipmentResourceTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
