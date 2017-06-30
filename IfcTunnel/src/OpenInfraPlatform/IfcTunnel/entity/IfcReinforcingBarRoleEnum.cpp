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
#include "include/IfcReinforcingBarRoleEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcReinforcingBarRoleEnum 
		IfcReinforcingBarRoleEnum::IfcReinforcingBarRoleEnum() {}
		IfcReinforcingBarRoleEnum::~IfcReinforcingBarRoleEnum() {}
		void IfcReinforcingBarRoleEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCREINFORCINGBARROLEENUM("; }
			if( m_enum == ENUM_MAIN )
			{
				stream << ".MAIN.";
			}
			else if( m_enum == ENUM_SHEAR )
			{
				stream << ".SHEAR.";
			}
			else if( m_enum == ENUM_LIGATURE )
			{
				stream << ".LIGATURE.";
			}
			else if( m_enum == ENUM_STUD )
			{
				stream << ".STUD.";
			}
			else if( m_enum == ENUM_PUNCHING )
			{
				stream << ".PUNCHING.";
			}
			else if( m_enum == ENUM_EDGE )
			{
				stream << ".EDGE.";
			}
			else if( m_enum == ENUM_RING )
			{
				stream << ".RING.";
			}
			else if( m_enum == ENUM_ANCHORING )
			{
				stream << ".ANCHORING.";
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
		shared_ptr<IfcReinforcingBarRoleEnum> IfcReinforcingBarRoleEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcReinforcingBarRoleEnum>(); }
			shared_ptr<IfcReinforcingBarRoleEnum> type_object( new IfcReinforcingBarRoleEnum() );
			if( _stricmp( arg.c_str(), ".MAIN." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_MAIN;
			}
			else if( _stricmp( arg.c_str(), ".SHEAR." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_SHEAR;
			}
			else if( _stricmp( arg.c_str(), ".LIGATURE." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_LIGATURE;
			}
			else if( _stricmp( arg.c_str(), ".STUD." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_STUD;
			}
			else if( _stricmp( arg.c_str(), ".PUNCHING." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_PUNCHING;
			}
			else if( _stricmp( arg.c_str(), ".EDGE." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_EDGE;
			}
			else if( _stricmp( arg.c_str(), ".RING." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_RING;
			}
			else if( _stricmp( arg.c_str(), ".ANCHORING." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_ANCHORING;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcReinforcingBarRoleEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
