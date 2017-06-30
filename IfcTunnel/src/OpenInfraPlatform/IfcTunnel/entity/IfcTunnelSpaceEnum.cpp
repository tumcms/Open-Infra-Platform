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
#include "include/IfcTunnelSpaceEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcTunnelSpaceEnum 
		IfcTunnelSpaceEnum::IfcTunnelSpaceEnum() {}
		IfcTunnelSpaceEnum::~IfcTunnelSpaceEnum() {}
		void IfcTunnelSpaceEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCTUNNELSPACEENUM("; }
			if( m_enum == ENUM_FULLTUNNELSPACE )
			{
				stream << ".FULLTUNNELSPACE.";
			}
			else if( m_enum == ENUM_INTERIORSPACE )
			{
				stream << ".INTERIORSPACE.";
			}
			else if( m_enum == ENUM_ANNULARGAPSPACE )
			{
				stream << ".ANNULARGAPSPACE.";
			}
			else if( m_enum == ENUM_LININGSPACE )
			{
				stream << ".LININGSPACE.";
			}
			else if( m_enum == ENUM_CLEARANCESPACE )
			{
				stream << ".CLEARANCESPACE.";
			}
			else if( m_enum == ENUM_SERVICESPACE )
			{
				stream << ".SERVICESPACE.";
			}
			else if( m_enum == ENUM_TRACKSPACE )
			{
				stream << ".TRACKSPACE.";
			}
			else if( m_enum == ENUM_FLOORSPACE )
			{
				stream << ".FLOORSPACE.";
			}
			else if( m_enum == ENUM_RING )
			{
				stream << ".RING.";
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
		shared_ptr<IfcTunnelSpaceEnum> IfcTunnelSpaceEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcTunnelSpaceEnum>(); }
			shared_ptr<IfcTunnelSpaceEnum> type_object( new IfcTunnelSpaceEnum() );
			if( _stricmp( arg.c_str(), ".FULLTUNNELSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_FULLTUNNELSPACE;
			}
			else if( _stricmp( arg.c_str(), ".INTERIORSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_INTERIORSPACE;
			}
			else if( _stricmp( arg.c_str(), ".ANNULARGAPSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_ANNULARGAPSPACE;
			}
			else if( _stricmp( arg.c_str(), ".LININGSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_LININGSPACE;
			}
			else if( _stricmp( arg.c_str(), ".CLEARANCESPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_CLEARANCESPACE;
			}
			else if( _stricmp( arg.c_str(), ".SERVICESPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_SERVICESPACE;
			}
			else if( _stricmp( arg.c_str(), ".TRACKSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_TRACKSPACE;
			}
			else if( _stricmp( arg.c_str(), ".FLOORSPACE." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_FLOORSPACE;
			}
			else if( _stricmp( arg.c_str(), ".RING." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_RING;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcTunnelSpaceEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
