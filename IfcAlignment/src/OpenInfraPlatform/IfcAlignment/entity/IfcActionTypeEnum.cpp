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
#include "OpenInfraPlatform/IfcAlignment/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcAlignment/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcAlignment/model/IfcAlignmentP6Exception.h"
#include "include/IfcActionTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// TYPE IfcActionTypeEnum 
		IfcActionTypeEnum::IfcActionTypeEnum() {}
		IfcActionTypeEnum::~IfcActionTypeEnum() {}
		void IfcActionTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCACTIONTYPEENUM("; }
			if( m_enum == ENUM_PERMANENT_G )
			{
				stream << ".PERMANENT_G.";
			}
			else if( m_enum == ENUM_VARIABLE_Q )
			{
				stream << ".VARIABLE_Q.";
			}
			else if( m_enum == ENUM_EXTRAORDINARY_A )
			{
				stream << ".EXTRAORDINARY_A.";
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
		shared_ptr<IfcActionTypeEnum> IfcActionTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcActionTypeEnum>(); }
			shared_ptr<IfcActionTypeEnum> type_object( new IfcActionTypeEnum() );
			if( _stricmp( arg.c_str(), ".PERMANENT_G." ) == 0 )
			{
				type_object->m_enum = IfcActionTypeEnum::ENUM_PERMANENT_G;
			}
			else if( _stricmp( arg.c_str(), ".VARIABLE_Q." ) == 0 )
			{
				type_object->m_enum = IfcActionTypeEnum::ENUM_VARIABLE_Q;
			}
			else if( _stricmp( arg.c_str(), ".EXTRAORDINARY_A." ) == 0 )
			{
				type_object->m_enum = IfcActionTypeEnum::ENUM_EXTRAORDINARY_A;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcActionTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcActionTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
