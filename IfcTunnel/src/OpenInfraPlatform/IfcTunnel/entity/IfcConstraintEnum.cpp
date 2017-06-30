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
#include "include/IfcConstraintEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcConstraintEnum 
		IfcConstraintEnum::IfcConstraintEnum() {}
		IfcConstraintEnum::~IfcConstraintEnum() {}
		void IfcConstraintEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCONSTRAINTENUM("; }
			if( m_enum == ENUM_HARD )
			{
				stream << ".HARD.";
			}
			else if( m_enum == ENUM_SOFT )
			{
				stream << ".SOFT.";
			}
			else if( m_enum == ENUM_ADVISORY )
			{
				stream << ".ADVISORY.";
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
		shared_ptr<IfcConstraintEnum> IfcConstraintEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcConstraintEnum>(); }
			shared_ptr<IfcConstraintEnum> type_object( new IfcConstraintEnum() );
			if( _stricmp( arg.c_str(), ".HARD." ) == 0 )
			{
				type_object->m_enum = IfcConstraintEnum::ENUM_HARD;
			}
			else if( _stricmp( arg.c_str(), ".SOFT." ) == 0 )
			{
				type_object->m_enum = IfcConstraintEnum::ENUM_SOFT;
			}
			else if( _stricmp( arg.c_str(), ".ADVISORY." ) == 0 )
			{
				type_object->m_enum = IfcConstraintEnum::ENUM_ADVISORY;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcConstraintEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcConstraintEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
