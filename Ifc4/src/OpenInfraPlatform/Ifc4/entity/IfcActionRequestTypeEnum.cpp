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
#include "include/IfcActionRequestTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcActionRequestTypeEnum 
		IfcActionRequestTypeEnum::IfcActionRequestTypeEnum() {}
		IfcActionRequestTypeEnum::~IfcActionRequestTypeEnum() {}
		void IfcActionRequestTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCACTIONREQUESTTYPEENUM("; }
			if( m_enum == ENUM_EMAIL )
			{
				stream << ".EMAIL.";
			}
			else if( m_enum == ENUM_FAX )
			{
				stream << ".FAX.";
			}
			else if( m_enum == ENUM_PHONE )
			{
				stream << ".PHONE.";
			}
			else if( m_enum == ENUM_POST )
			{
				stream << ".POST.";
			}
			else if( m_enum == ENUM_VERBAL )
			{
				stream << ".VERBAL.";
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
		shared_ptr<IfcActionRequestTypeEnum> IfcActionRequestTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcActionRequestTypeEnum>(); }
			shared_ptr<IfcActionRequestTypeEnum> type_object( new IfcActionRequestTypeEnum() );
			if( _stricmp( arg.c_str(), ".EMAIL." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_EMAIL;
			}
			else if( _stricmp( arg.c_str(), ".FAX." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_FAX;
			}
			else if( _stricmp( arg.c_str(), ".PHONE." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_PHONE;
			}
			else if( _stricmp( arg.c_str(), ".POST." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_POST;
			}
			else if( _stricmp( arg.c_str(), ".VERBAL." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_VERBAL;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcActionRequestTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
