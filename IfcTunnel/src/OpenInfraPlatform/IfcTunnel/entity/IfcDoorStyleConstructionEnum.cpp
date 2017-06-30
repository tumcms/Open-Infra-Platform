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
#include "include/IfcDoorStyleConstructionEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcDoorStyleConstructionEnum 
		IfcDoorStyleConstructionEnum::IfcDoorStyleConstructionEnum() {}
		IfcDoorStyleConstructionEnum::~IfcDoorStyleConstructionEnum() {}
		void IfcDoorStyleConstructionEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCDOORSTYLECONSTRUCTIONENUM("; }
			if( m_enum == ENUM_ALUMINIUM )
			{
				stream << ".ALUMINIUM.";
			}
			else if( m_enum == ENUM_HIGH_GRADE_STEEL )
			{
				stream << ".HIGH_GRADE_STEEL.";
			}
			else if( m_enum == ENUM_STEEL )
			{
				stream << ".STEEL.";
			}
			else if( m_enum == ENUM_WOOD )
			{
				stream << ".WOOD.";
			}
			else if( m_enum == ENUM_ALUMINIUM_WOOD )
			{
				stream << ".ALUMINIUM_WOOD.";
			}
			else if( m_enum == ENUM_ALUMINIUM_PLASTIC )
			{
				stream << ".ALUMINIUM_PLASTIC.";
			}
			else if( m_enum == ENUM_PLASTIC )
			{
				stream << ".PLASTIC.";
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
		shared_ptr<IfcDoorStyleConstructionEnum> IfcDoorStyleConstructionEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcDoorStyleConstructionEnum>(); }
			shared_ptr<IfcDoorStyleConstructionEnum> type_object( new IfcDoorStyleConstructionEnum() );
			if( _stricmp( arg.c_str(), ".ALUMINIUM." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_ALUMINIUM;
			}
			else if( _stricmp( arg.c_str(), ".HIGH_GRADE_STEEL." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_HIGH_GRADE_STEEL;
			}
			else if( _stricmp( arg.c_str(), ".STEEL." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_STEEL;
			}
			else if( _stricmp( arg.c_str(), ".WOOD." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_WOOD;
			}
			else if( _stricmp( arg.c_str(), ".ALUMINIUM_WOOD." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_ALUMINIUM_WOOD;
			}
			else if( _stricmp( arg.c_str(), ".ALUMINIUM_PLASTIC." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_ALUMINIUM_PLASTIC;
			}
			else if( _stricmp( arg.c_str(), ".PLASTIC." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_PLASTIC;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcDoorStyleConstructionEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
