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
#include "../model/Ifc2x3Exception.h"
#include "include/IfcConnectionTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcConnectionTypeEnum 
		IfcConnectionTypeEnum::IfcConnectionTypeEnum() {}
		IfcConnectionTypeEnum::~IfcConnectionTypeEnum() {}
		void IfcConnectionTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCONNECTIONTYPEENUM("; }
			if( m_enum == ENUM_ATPATH )
			{
				stream << ".ATPATH.";
			}
			else if( m_enum == ENUM_ATSTART )
			{
				stream << ".ATSTART.";
			}
			else if( m_enum == ENUM_ATEND )
			{
				stream << ".ATEND.";
			}
			else if( m_enum == ENUM_NOTDEFINED )
			{
				stream << ".NOTDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcConnectionTypeEnum> IfcConnectionTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcConnectionTypeEnum>(); }
			shared_ptr<IfcConnectionTypeEnum> type_object( new IfcConnectionTypeEnum() );
			if( _stricmp( arg.c_str(), ".ATPATH." ) == 0 )
			{
				type_object->m_enum = IfcConnectionTypeEnum::ENUM_ATPATH;
			}
			else if( _stricmp( arg.c_str(), ".ATSTART." ) == 0 )
			{
				type_object->m_enum = IfcConnectionTypeEnum::ENUM_ATSTART;
			}
			else if( _stricmp( arg.c_str(), ".ATEND." ) == 0 )
			{
				type_object->m_enum = IfcConnectionTypeEnum::ENUM_ATEND;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcConnectionTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
