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
#include "../model/IfcBridgeException.h"
#include "include/IfcBridgeStructureType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeStructureType 
		IfcBridgeStructureType::IfcBridgeStructureType() {}
		IfcBridgeStructureType::~IfcBridgeStructureType() {}
		void IfcBridgeStructureType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGESTRUCTURETYPE("; }
			if( m_enum == ENUM_BOX_GIRDER_BRIDGE )
			{
				stream << ".BOX_GIRDER_BRIDGE.";
			}
			else if( m_enum == ENUM_ARCHED_BRIDGE )
			{
				stream << ".ARCHED_BRIDGE.";
			}
			else if( m_enum == ENUM_SUSPENSION_BRIDGE )
			{
				stream << ".SUSPENSION_BRIDGE.";
			}
			else if( m_enum == ENUM_CABLE_STAYED_BRIDGE )
			{
				stream << ".CABLE_STAYED_BRIDGE.";
			}
			else if( m_enum == ENUM_GIRDER_BRIDGE )
			{
				stream << ".GIRDER_BRIDGE.";
			}
			else if( m_enum == ENUM_SLAB_BRIDGE )
			{
				stream << ".SLAB_BRIDGE.";
			}
			else if( m_enum == ENUM_SLAB_BRIDGE_WITH_BROAD_CANTILEVER )
			{
				stream << ".SLAB_BRIDGE_WITH_BROAD_CANTILEVER.";
			}
			else if( m_enum == ENUM_BOW_STRING_BRIDGE )
			{
				stream << ".BOW_STRING_BRIDGE.";
			}
			else if( m_enum == ENUM_LADDER_BRIDGE )
			{
				stream << ".LADDER_BRIDGE.";
			}
			else if( m_enum == ENUM_FRAMEWORK_BRIDGE )
			{
				stream << ".FRAMEWORK_BRIDGE.";
			}
			else if( m_enum == ENUM_GISCLARD_BRIDGE )
			{
				stream << ".GISCLARD_BRIDGE.";
			}
			else if( m_enum == ENUM_PORTAL_BRIDGE )
			{
				stream << ".PORTAL_BRIDGE.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeStructureType> IfcBridgeStructureType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeStructureType>(); }
			shared_ptr<IfcBridgeStructureType> type_object( new IfcBridgeStructureType() );
			if( _stricmp( arg.c_str(), ".BOX_GIRDER_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_BOX_GIRDER_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".ARCHED_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_ARCHED_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".SUSPENSION_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_SUSPENSION_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".CABLE_STAYED_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_CABLE_STAYED_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".GIRDER_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_GIRDER_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".SLAB_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_SLAB_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".SLAB_BRIDGE_WITH_BROAD_CANTILEVER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_SLAB_BRIDGE_WITH_BROAD_CANTILEVER;
			}
			else if( _stricmp( arg.c_str(), ".BOW_STRING_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_BOW_STRING_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".LADDER_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_LADDER_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".FRAMEWORK_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_FRAMEWORK_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".GISCLARD_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_GISCLARD_BRIDGE;
			}
			else if( _stricmp( arg.c_str(), ".PORTAL_BRIDGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureType::ENUM_PORTAL_BRIDGE;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
