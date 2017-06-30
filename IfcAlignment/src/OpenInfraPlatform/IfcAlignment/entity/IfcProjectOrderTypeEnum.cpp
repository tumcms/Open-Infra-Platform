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
#include "include/IfcProjectOrderTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment
	{
		// TYPE IfcProjectOrderTypeEnum 
		IfcProjectOrderTypeEnum::IfcProjectOrderTypeEnum() {}
		IfcProjectOrderTypeEnum::~IfcProjectOrderTypeEnum() {}
		void IfcProjectOrderTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCPROJECTORDERTYPEENUM("; }
			if( m_enum == ENUM_CHANGEORDER )
			{
				stream << ".CHANGEORDER.";
			}
			else if( m_enum == ENUM_MAINTENANCEWORKORDER )
			{
				stream << ".MAINTENANCEWORKORDER.";
			}
			else if( m_enum == ENUM_MOVEORDER )
			{
				stream << ".MOVEORDER.";
			}
			else if( m_enum == ENUM_PURCHASEORDER )
			{
				stream << ".PURCHASEORDER.";
			}
			else if( m_enum == ENUM_WORKORDER )
			{
				stream << ".WORKORDER.";
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
		shared_ptr<IfcProjectOrderTypeEnum> IfcProjectOrderTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcProjectOrderTypeEnum>(); }
			shared_ptr<IfcProjectOrderTypeEnum> type_object( new IfcProjectOrderTypeEnum() );
			if( _stricmp( arg.c_str(), ".CHANGEORDER." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_CHANGEORDER;
			}
			else if( _stricmp( arg.c_str(), ".MAINTENANCEWORKORDER." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_MAINTENANCEWORKORDER;
			}
			else if( _stricmp( arg.c_str(), ".MOVEORDER." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_MOVEORDER;
			}
			else if( _stricmp( arg.c_str(), ".PURCHASEORDER." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_PURCHASEORDER;
			}
			else if( _stricmp( arg.c_str(), ".WORKORDER." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_WORKORDER;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcProjectOrderTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcAlignment
} // end namespace OpenInfraPlatform
