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
#include "include/IfcBridgeSegmentType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeSegmentType 
		IfcBridgeSegmentType::IfcBridgeSegmentType() {}
		IfcBridgeSegmentType::~IfcBridgeSegmentType() {}
		void IfcBridgeSegmentType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGESEGMENTTYPE("; }
			if( m_enum == ENUM_TYPICAL_SEGMENT )
			{
				stream << ".TYPICAL_SEGMENT.";
			}
			else if( m_enum == ENUM_PIER_SEGMENT )
			{
				stream << ".PIER_SEGMENT.";
			}
			else if( m_enum == ENUM_PIECE )
			{
				stream << ".PIECE.";
			}
			else if( m_enum == ENUM_LIFT )
			{
				stream << ".LIFT.";
			}
			else if( m_enum == ENUM_ELEMENT )
			{
				stream << ".ELEMENT.";
			}
			else if( m_enum == ENUM_JAMB )
			{
				stream << ".JAMB.";
			}
			else if( m_enum == ENUM_PYLON_HEAD )
			{
				stream << ".PYLON_HEAD.";
			}
			else if( m_enum == ENUM_SPAN )
			{
				stream << ".SPAN.";
			}
			else if( m_enum == ENUM_CANTILEVER )
			{
				stream << ".CANTILEVER.";
			}
			else if( m_enum == ENUM_FINITE_ELEMENT_REFERENCE )
			{
				stream << ".FINITE_ELEMENT_REFERENCE.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeSegmentType> IfcBridgeSegmentType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeSegmentType>(); }
			shared_ptr<IfcBridgeSegmentType> type_object( new IfcBridgeSegmentType() );
			if( _stricmp( arg.c_str(), ".TYPICAL_SEGMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_TYPICAL_SEGMENT;
			}
			else if( _stricmp( arg.c_str(), ".PIER_SEGMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_PIER_SEGMENT;
			}
			else if( _stricmp( arg.c_str(), ".PIECE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_PIECE;
			}
			else if( _stricmp( arg.c_str(), ".LIFT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_LIFT;
			}
			else if( _stricmp( arg.c_str(), ".ELEMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_ELEMENT;
			}
			else if( _stricmp( arg.c_str(), ".JAMB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_JAMB;
			}
			else if( _stricmp( arg.c_str(), ".PYLON_HEAD." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_PYLON_HEAD;
			}
			else if( _stricmp( arg.c_str(), ".SPAN." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_SPAN;
			}
			else if( _stricmp( arg.c_str(), ".CANTILEVER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_CANTILEVER;
			}
			else if( _stricmp( arg.c_str(), ".FINITE_ELEMENT_REFERENCE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSegmentType::ENUM_FINITE_ELEMENT_REFERENCE;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
