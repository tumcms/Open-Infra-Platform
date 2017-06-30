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
#include "include/IfcKnotType.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcKnotType 
		IfcKnotType::IfcKnotType() {}
		IfcKnotType::~IfcKnotType() {}
		void IfcKnotType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCKNOTTYPE("; }
			if( m_enum == ENUM_UNIFORM_KNOTS )
			{
				stream << ".UNIFORM_KNOTS.";
			}
			else if( m_enum == ENUM_QUASI_UNIFORM_KNOTS )
			{
				stream << ".QUASI_UNIFORM_KNOTS.";
			}
			else if( m_enum == ENUM_PIECEWISE_BEZIER_KNOTS )
			{
				stream << ".PIECEWISE_BEZIER_KNOTS.";
			}
			else if( m_enum == ENUM_UNSPECIFIED )
			{
				stream << ".UNSPECIFIED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcKnotType> IfcKnotType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcKnotType>(); }
			shared_ptr<IfcKnotType> type_object( new IfcKnotType() );
			if( _stricmp( arg.c_str(), ".UNIFORM_KNOTS." ) == 0 )
			{
				type_object->m_enum = IfcKnotType::ENUM_UNIFORM_KNOTS;
			}
			else if( _stricmp( arg.c_str(), ".QUASI_UNIFORM_KNOTS." ) == 0 )
			{
				type_object->m_enum = IfcKnotType::ENUM_QUASI_UNIFORM_KNOTS;
			}
			else if( _stricmp( arg.c_str(), ".PIECEWISE_BEZIER_KNOTS." ) == 0 )
			{
				type_object->m_enum = IfcKnotType::ENUM_PIECEWISE_BEZIER_KNOTS;
			}
			else if( _stricmp( arg.c_str(), ".UNSPECIFIED." ) == 0 )
			{
				type_object->m_enum = IfcKnotType::ENUM_UNSPECIFIED;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
