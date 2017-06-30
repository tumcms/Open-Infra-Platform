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
#include "include/IfcProjectOrderRecordTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcProjectOrderRecordTypeEnum 
		IfcProjectOrderRecordTypeEnum::IfcProjectOrderRecordTypeEnum() {}
		IfcProjectOrderRecordTypeEnum::~IfcProjectOrderRecordTypeEnum() {}
		void IfcProjectOrderRecordTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCPROJECTORDERRECORDTYPEENUM("; }
			if( m_enum == ENUM_CHANGE )
			{
				stream << ".CHANGE.";
			}
			else if( m_enum == ENUM_MAINTENANCE )
			{
				stream << ".MAINTENANCE.";
			}
			else if( m_enum == ENUM_MOVE )
			{
				stream << ".MOVE.";
			}
			else if( m_enum == ENUM_PURCHASE )
			{
				stream << ".PURCHASE.";
			}
			else if( m_enum == ENUM_WORK )
			{
				stream << ".WORK.";
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
		shared_ptr<IfcProjectOrderRecordTypeEnum> IfcProjectOrderRecordTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcProjectOrderRecordTypeEnum>(); }
			shared_ptr<IfcProjectOrderRecordTypeEnum> type_object( new IfcProjectOrderRecordTypeEnum() );
			if( _stricmp( arg.c_str(), ".CHANGE." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_CHANGE;
			}
			else if( _stricmp( arg.c_str(), ".MAINTENANCE." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_MAINTENANCE;
			}
			else if( _stricmp( arg.c_str(), ".MOVE." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_MOVE;
			}
			else if( _stricmp( arg.c_str(), ".PURCHASE." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_PURCHASE;
			}
			else if( _stricmp( arg.c_str(), ".WORK." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_WORK;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderRecordTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
