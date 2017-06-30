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
#include "OpenInfraPlatform/Ifc4/reader/ReaderUtil.h"
#include "OpenInfraPlatform/Ifc4/writer/WriterUtil.h"
#include "OpenInfraPlatform/Ifc4/model/shared_ptr.h"
#include "OpenInfraPlatform/Ifc4/model/Ifc4Exception.h"
#include "include/IfcWorkCalendarTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcWorkCalendarTypeEnum 
		IfcWorkCalendarTypeEnum::IfcWorkCalendarTypeEnum() {}
		IfcWorkCalendarTypeEnum::~IfcWorkCalendarTypeEnum() {}
		void IfcWorkCalendarTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCWORKCALENDARTYPEENUM("; }
			if( m_enum == ENUM_FIRSTSHIFT )
			{
				stream << ".FIRSTSHIFT.";
			}
			else if( m_enum == ENUM_SECONDSHIFT )
			{
				stream << ".SECONDSHIFT.";
			}
			else if( m_enum == ENUM_THIRDSHIFT )
			{
				stream << ".THIRDSHIFT.";
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
		shared_ptr<IfcWorkCalendarTypeEnum> IfcWorkCalendarTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcWorkCalendarTypeEnum>(); }
			shared_ptr<IfcWorkCalendarTypeEnum> type_object( new IfcWorkCalendarTypeEnum() );
			if( _stricmp( arg.c_str(), ".FIRSTSHIFT." ) == 0 )
			{
				type_object->m_enum = IfcWorkCalendarTypeEnum::ENUM_FIRSTSHIFT;
			}
			else if( _stricmp( arg.c_str(), ".SECONDSHIFT." ) == 0 )
			{
				type_object->m_enum = IfcWorkCalendarTypeEnum::ENUM_SECONDSHIFT;
			}
			else if( _stricmp( arg.c_str(), ".THIRDSHIFT." ) == 0 )
			{
				type_object->m_enum = IfcWorkCalendarTypeEnum::ENUM_THIRDSHIFT;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcWorkCalendarTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcWorkCalendarTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
