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
#include "include/IfcBridgeStructureElementType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeStructureElementType 
		IfcBridgeStructureElementType::IfcBridgeStructureElementType() {}
		IfcBridgeStructureElementType::~IfcBridgeStructureElementType() {}
		void IfcBridgeStructureElementType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGESTRUCTUREELEMENTTYPE("; }
			if( m_enum == ENUM_DECK )
			{
				stream << ".DECK.";
			}
			else if( m_enum == ENUM_PIER )
			{
				stream << ".PIER.";
			}
			else if( m_enum == ENUM_SMALL_PIER )
			{
				stream << ".SMALL_PIER.";
			}
			else if( m_enum == ENUM_PYLON )
			{
				stream << ".PYLON.";
			}
			else if( m_enum == ENUM_ARCH )
			{
				stream << ".ARCH.";
			}
			else if( m_enum == ENUM_LAUNCHING_NOSE )
			{
				stream << ".LAUNCHING_NOSE.";
			}
			else if( m_enum == ENUM_TEMPORARY_BENT )
			{
				stream << ".TEMPORARY_BENT.";
			}
			else if( m_enum == ENUM_TRANSVERSE_GIRDER )
			{
				stream << ".TRANSVERSE_GIRDER.";
			}
			else if( m_enum == ENUM_STRUT )
			{
				stream << ".STRUT.";
			}
			else if( m_enum == ENUM_COUNTER_STRUT )
			{
				stream << ".COUNTER_STRUT.";
			}
			else if( m_enum == ENUM_CABLE )
			{
				stream << ".CABLE.";
			}
			else if( m_enum == ENUM_SUSPENDED_TENDON )
			{
				stream << ".SUSPENDED_TENDON.";
			}
			else if( m_enum == ENUM_SUSPENDER )
			{
				stream << ".SUSPENDER.";
			}
			else if( m_enum == ENUM_MOBILE_FALSEWORK )
			{
				stream << ".MOBILE_FALSEWORK.";
			}
			else if( m_enum == ENUM_STAYING_MAST )
			{
				stream << ".STAYING_MAST.";
			}
			else if( m_enum == ENUM_LAUNCHING_BEAM )
			{
				stream << ".LAUNCHING_BEAM.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeStructureElementType> IfcBridgeStructureElementType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeStructureElementType>(); }
			shared_ptr<IfcBridgeStructureElementType> type_object( new IfcBridgeStructureElementType() );
			if( _stricmp( arg.c_str(), ".DECK." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_DECK;
			}
			else if( _stricmp( arg.c_str(), ".PIER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_PIER;
			}
			else if( _stricmp( arg.c_str(), ".SMALL_PIER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_SMALL_PIER;
			}
			else if( _stricmp( arg.c_str(), ".PYLON." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_PYLON;
			}
			else if( _stricmp( arg.c_str(), ".ARCH." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_ARCH;
			}
			else if( _stricmp( arg.c_str(), ".LAUNCHING_NOSE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_LAUNCHING_NOSE;
			}
			else if( _stricmp( arg.c_str(), ".TEMPORARY_BENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_TEMPORARY_BENT;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSE_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_TRANSVERSE_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".STRUT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_STRUT;
			}
			else if( _stricmp( arg.c_str(), ".COUNTER_STRUT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_COUNTER_STRUT;
			}
			else if( _stricmp( arg.c_str(), ".CABLE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_CABLE;
			}
			else if( _stricmp( arg.c_str(), ".SUSPENDED_TENDON." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_SUSPENDED_TENDON;
			}
			else if( _stricmp( arg.c_str(), ".SUSPENDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_SUSPENDER;
			}
			else if( _stricmp( arg.c_str(), ".MOBILE_FALSEWORK." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_MOBILE_FALSEWORK;
			}
			else if( _stricmp( arg.c_str(), ".STAYING_MAST." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_STAYING_MAST;
			}
			else if( _stricmp( arg.c_str(), ".LAUNCHING_BEAM." ) == 0 )
			{
				type_object->m_enum = IfcBridgeStructureElementType::ENUM_LAUNCHING_BEAM;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
