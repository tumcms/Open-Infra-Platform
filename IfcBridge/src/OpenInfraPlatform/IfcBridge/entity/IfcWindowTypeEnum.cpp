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
#include "include/IfcWindowTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcWindowTypeEnum 
		IfcWindowTypeEnum::IfcWindowTypeEnum() {}
		IfcWindowTypeEnum::~IfcWindowTypeEnum() {}
		void IfcWindowTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCWINDOWTYPEENUM("; }
			if( m_enum == ENUM_WINDOW )
			{
				stream << ".WINDOW.";
			}
			else if( m_enum == ENUM_SKYLIGHT )
			{
				stream << ".SKYLIGHT.";
			}
			else if( m_enum == ENUM_LIGHTDOME )
			{
				stream << ".LIGHTDOME.";
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
		shared_ptr<IfcWindowTypeEnum> IfcWindowTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcWindowTypeEnum>(); }
			shared_ptr<IfcWindowTypeEnum> type_object( new IfcWindowTypeEnum() );
			if( _stricmp( arg.c_str(), ".WINDOW." ) == 0 )
			{
				type_object->m_enum = IfcWindowTypeEnum::ENUM_WINDOW;
			}
			else if( _stricmp( arg.c_str(), ".SKYLIGHT." ) == 0 )
			{
				type_object->m_enum = IfcWindowTypeEnum::ENUM_SKYLIGHT;
			}
			else if( _stricmp( arg.c_str(), ".LIGHTDOME." ) == 0 )
			{
				type_object->m_enum = IfcWindowTypeEnum::ENUM_LIGHTDOME;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcWindowTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcWindowTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
