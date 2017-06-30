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
#include "include/IfcBridgeMechanicalRoleType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeMechanicalRoleType 
		IfcBridgeMechanicalRoleType::IfcBridgeMechanicalRoleType() {}
		IfcBridgeMechanicalRoleType::~IfcBridgeMechanicalRoleType() {}
		void IfcBridgeMechanicalRoleType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGEMECHANICALROLETYPE("; }
			if( m_enum == ENUM_LONGITUDINAL )
			{
				stream << ".LONGITUDINAL.";
			}
			else if( m_enum == ENUM_TRANSVERSAL )
			{
				stream << ".TRANSVERSAL.";
			}
			else if( m_enum == ENUM_COMPLETE )
			{
				stream << ".COMPLETE.";
			}
			else if( m_enum == ENUM_NONE )
			{
				stream << ".NONE.";
			}
			else if( m_enum == ENUM_UNDEFINED )
			{
				stream << ".UNDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeMechanicalRoleType> IfcBridgeMechanicalRoleType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeMechanicalRoleType>(); }
			shared_ptr<IfcBridgeMechanicalRoleType> type_object( new IfcBridgeMechanicalRoleType() );
			if( _stricmp( arg.c_str(), ".LONGITUDINAL." ) == 0 )
			{
				type_object->m_enum = IfcBridgeMechanicalRoleType::ENUM_LONGITUDINAL;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSAL." ) == 0 )
			{
				type_object->m_enum = IfcBridgeMechanicalRoleType::ENUM_TRANSVERSAL;
			}
			else if( _stricmp( arg.c_str(), ".COMPLETE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeMechanicalRoleType::ENUM_COMPLETE;
			}
			else if( _stricmp( arg.c_str(), ".NONE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeMechanicalRoleType::ENUM_NONE;
			}
			else if( _stricmp( arg.c_str(), ".UNDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcBridgeMechanicalRoleType::ENUM_UNDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
