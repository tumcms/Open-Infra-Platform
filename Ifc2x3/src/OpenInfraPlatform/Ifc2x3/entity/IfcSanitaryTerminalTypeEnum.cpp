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
#include "include/IfcSanitaryTerminalTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcSanitaryTerminalTypeEnum 
		IfcSanitaryTerminalTypeEnum::IfcSanitaryTerminalTypeEnum() {}
		IfcSanitaryTerminalTypeEnum::~IfcSanitaryTerminalTypeEnum() {}
		void IfcSanitaryTerminalTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSANITARYTERMINALTYPEENUM("; }
			if( m_enum == ENUM_BATH )
			{
				stream << ".BATH.";
			}
			else if( m_enum == ENUM_BIDET )
			{
				stream << ".BIDET.";
			}
			else if( m_enum == ENUM_CISTERN )
			{
				stream << ".CISTERN.";
			}
			else if( m_enum == ENUM_SHOWER )
			{
				stream << ".SHOWER.";
			}
			else if( m_enum == ENUM_SINK )
			{
				stream << ".SINK.";
			}
			else if( m_enum == ENUM_SANITARYFOUNTAIN )
			{
				stream << ".SANITARYFOUNTAIN.";
			}
			else if( m_enum == ENUM_TOILETPAN )
			{
				stream << ".TOILETPAN.";
			}
			else if( m_enum == ENUM_URINAL )
			{
				stream << ".URINAL.";
			}
			else if( m_enum == ENUM_WASHHANDBASIN )
			{
				stream << ".WASHHANDBASIN.";
			}
			else if( m_enum == ENUM_WCSEAT )
			{
				stream << ".WCSEAT.";
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
		shared_ptr<IfcSanitaryTerminalTypeEnum> IfcSanitaryTerminalTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcSanitaryTerminalTypeEnum>(); }
			shared_ptr<IfcSanitaryTerminalTypeEnum> type_object( new IfcSanitaryTerminalTypeEnum() );
			if( _stricmp( arg.c_str(), ".BATH." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_BATH;
			}
			else if( _stricmp( arg.c_str(), ".BIDET." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_BIDET;
			}
			else if( _stricmp( arg.c_str(), ".CISTERN." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_CISTERN;
			}
			else if( _stricmp( arg.c_str(), ".SHOWER." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_SHOWER;
			}
			else if( _stricmp( arg.c_str(), ".SINK." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_SINK;
			}
			else if( _stricmp( arg.c_str(), ".SANITARYFOUNTAIN." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_SANITARYFOUNTAIN;
			}
			else if( _stricmp( arg.c_str(), ".TOILETPAN." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_TOILETPAN;
			}
			else if( _stricmp( arg.c_str(), ".URINAL." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_URINAL;
			}
			else if( _stricmp( arg.c_str(), ".WASHHANDBASIN." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_WASHHANDBASIN;
			}
			else if( _stricmp( arg.c_str(), ".WCSEAT." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_WCSEAT;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSanitaryTerminalTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
