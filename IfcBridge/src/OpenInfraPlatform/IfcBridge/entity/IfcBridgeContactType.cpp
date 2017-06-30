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
#include "include/IfcBridgeContactType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeContactType 
		IfcBridgeContactType::IfcBridgeContactType() {}
		IfcBridgeContactType::~IfcBridgeContactType() {}
		void IfcBridgeContactType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGECONTACTTYPE("; }
			if( m_enum == ENUM_GLUE )
			{
				stream << ".GLUE.";
			}
			else if( m_enum == ENUM_RIVET )
			{
				stream << ".RIVET.";
			}
			else if( m_enum == ENUM_CONNECTOR )
			{
				stream << ".CONNECTOR.";
			}
			else if( m_enum == ENUM_WELD )
			{
				stream << ".WELD.";
			}
			else if( m_enum == ENUM_RESUMPTION_OF_CONCRETE )
			{
				stream << ".RESUMPTION_OF_CONCRETE.";
			}
			else if( m_enum == ENUM_SLIDING )
			{
				stream << ".SLIDING.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeContactType> IfcBridgeContactType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeContactType>(); }
			shared_ptr<IfcBridgeContactType> type_object( new IfcBridgeContactType() );
			if( _stricmp( arg.c_str(), ".GLUE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_GLUE;
			}
			else if( _stricmp( arg.c_str(), ".RIVET." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_RIVET;
			}
			else if( _stricmp( arg.c_str(), ".CONNECTOR." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_CONNECTOR;
			}
			else if( _stricmp( arg.c_str(), ".WELD." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_WELD;
			}
			else if( _stricmp( arg.c_str(), ".RESUMPTION_OF_CONCRETE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_RESUMPTION_OF_CONCRETE;
			}
			else if( _stricmp( arg.c_str(), ".SLIDING." ) == 0 )
			{
				type_object->m_enum = IfcBridgeContactType::ENUM_SLIDING;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
