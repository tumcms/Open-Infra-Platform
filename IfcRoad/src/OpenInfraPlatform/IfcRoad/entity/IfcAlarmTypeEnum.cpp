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
#include "OpenInfraPlatform/IfcRoad/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcRoad/writer/WriterUtil.h"
#include "OpenInfraPlatform/IfcRoad/model/shared_ptr.h"
#include "OpenInfraPlatform/IfcRoad/model/IfcRoadException.h"
#include "include/IfcAlarmTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// TYPE IfcAlarmTypeEnum 
		IfcAlarmTypeEnum::IfcAlarmTypeEnum() {}
		IfcAlarmTypeEnum::~IfcAlarmTypeEnum() {}
		void IfcAlarmTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCALARMTYPEENUM("; }
			if( m_enum == ENUM_BELL )
			{
				stream << ".BELL.";
			}
			else if( m_enum == ENUM_BREAKGLASSBUTTON )
			{
				stream << ".BREAKGLASSBUTTON.";
			}
			else if( m_enum == ENUM_LIGHT )
			{
				stream << ".LIGHT.";
			}
			else if( m_enum == ENUM_MANUALPULLBOX )
			{
				stream << ".MANUALPULLBOX.";
			}
			else if( m_enum == ENUM_SIREN )
			{
				stream << ".SIREN.";
			}
			else if( m_enum == ENUM_WHISTLE )
			{
				stream << ".WHISTLE.";
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
		shared_ptr<IfcAlarmTypeEnum> IfcAlarmTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcAlarmTypeEnum>(); }
			shared_ptr<IfcAlarmTypeEnum> type_object( new IfcAlarmTypeEnum() );
			if( _stricmp( arg.c_str(), ".BELL." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_BELL;
			}
			else if( _stricmp( arg.c_str(), ".BREAKGLASSBUTTON." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_BREAKGLASSBUTTON;
			}
			else if( _stricmp( arg.c_str(), ".LIGHT." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_LIGHT;
			}
			else if( _stricmp( arg.c_str(), ".MANUALPULLBOX." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_MANUALPULLBOX;
			}
			else if( _stricmp( arg.c_str(), ".SIREN." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_SIREN;
			}
			else if( _stricmp( arg.c_str(), ".WHISTLE." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_WHISTLE;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcAlarmTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
