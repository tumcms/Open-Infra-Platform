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
#include "include/IfcCoilTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcCoilTypeEnum 
		IfcCoilTypeEnum::IfcCoilTypeEnum() {}
		IfcCoilTypeEnum::~IfcCoilTypeEnum() {}
		void IfcCoilTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCOILTYPEENUM("; }
			if( m_enum == ENUM_DXCOOLINGCOIL )
			{
				stream << ".DXCOOLINGCOIL.";
			}
			else if( m_enum == ENUM_WATERCOOLINGCOIL )
			{
				stream << ".WATERCOOLINGCOIL.";
			}
			else if( m_enum == ENUM_STEAMHEATINGCOIL )
			{
				stream << ".STEAMHEATINGCOIL.";
			}
			else if( m_enum == ENUM_WATERHEATINGCOIL )
			{
				stream << ".WATERHEATINGCOIL.";
			}
			else if( m_enum == ENUM_ELECTRICHEATINGCOIL )
			{
				stream << ".ELECTRICHEATINGCOIL.";
			}
			else if( m_enum == ENUM_GASHEATINGCOIL )
			{
				stream << ".GASHEATINGCOIL.";
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
		shared_ptr<IfcCoilTypeEnum> IfcCoilTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcCoilTypeEnum>(); }
			shared_ptr<IfcCoilTypeEnum> type_object( new IfcCoilTypeEnum() );
			if( _stricmp( arg.c_str(), ".DXCOOLINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_DXCOOLINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".WATERCOOLINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_WATERCOOLINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".STEAMHEATINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_STEAMHEATINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".WATERHEATINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_WATERHEATINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".ELECTRICHEATINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_ELECTRICHEATINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".GASHEATINGCOIL." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_GASHEATINGCOIL;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCoilTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
