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
#include "include/IfcSoundScaleEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcSoundScaleEnum 
		IfcSoundScaleEnum::IfcSoundScaleEnum() {}
		IfcSoundScaleEnum::~IfcSoundScaleEnum() {}
		void IfcSoundScaleEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSOUNDSCALEENUM("; }
			if( m_enum == ENUM_DBA )
			{
				stream << ".DBA.";
			}
			else if( m_enum == ENUM_DBB )
			{
				stream << ".DBB.";
			}
			else if( m_enum == ENUM_DBC )
			{
				stream << ".DBC.";
			}
			else if( m_enum == ENUM_NC )
			{
				stream << ".NC.";
			}
			else if( m_enum == ENUM_NR )
			{
				stream << ".NR.";
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
		shared_ptr<IfcSoundScaleEnum> IfcSoundScaleEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcSoundScaleEnum>(); }
			shared_ptr<IfcSoundScaleEnum> type_object( new IfcSoundScaleEnum() );
			if( _stricmp( arg.c_str(), ".DBA." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_DBA;
			}
			else if( _stricmp( arg.c_str(), ".DBB." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_DBB;
			}
			else if( _stricmp( arg.c_str(), ".DBC." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_DBC;
			}
			else if( _stricmp( arg.c_str(), ".NC." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_NC;
			}
			else if( _stricmp( arg.c_str(), ".NR." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_NR;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSoundScaleEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
