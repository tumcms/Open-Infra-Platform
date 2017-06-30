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
#include "include/IfcOccupantTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcRoad
	{
		// TYPE IfcOccupantTypeEnum 
		IfcOccupantTypeEnum::IfcOccupantTypeEnum() {}
		IfcOccupantTypeEnum::~IfcOccupantTypeEnum() {}
		void IfcOccupantTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCOCCUPANTTYPEENUM("; }
			if( m_enum == ENUM_ASSIGNEE )
			{
				stream << ".ASSIGNEE.";
			}
			else if( m_enum == ENUM_ASSIGNOR )
			{
				stream << ".ASSIGNOR.";
			}
			else if( m_enum == ENUM_LESSEE )
			{
				stream << ".LESSEE.";
			}
			else if( m_enum == ENUM_LESSOR )
			{
				stream << ".LESSOR.";
			}
			else if( m_enum == ENUM_LETTINGAGENT )
			{
				stream << ".LETTINGAGENT.";
			}
			else if( m_enum == ENUM_OWNER )
			{
				stream << ".OWNER.";
			}
			else if( m_enum == ENUM_TENANT )
			{
				stream << ".TENANT.";
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
		shared_ptr<IfcOccupantTypeEnum> IfcOccupantTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcOccupantTypeEnum>(); }
			shared_ptr<IfcOccupantTypeEnum> type_object( new IfcOccupantTypeEnum() );
			if( _stricmp( arg.c_str(), ".ASSIGNEE." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_ASSIGNEE;
			}
			else if( _stricmp( arg.c_str(), ".ASSIGNOR." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_ASSIGNOR;
			}
			else if( _stricmp( arg.c_str(), ".LESSEE." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_LESSEE;
			}
			else if( _stricmp( arg.c_str(), ".LESSOR." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_LESSOR;
			}
			else if( _stricmp( arg.c_str(), ".LETTINGAGENT." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_LETTINGAGENT;
			}
			else if( _stricmp( arg.c_str(), ".OWNER." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_OWNER;
			}
			else if( _stricmp( arg.c_str(), ".TENANT." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_TENANT;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcOccupantTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcRoad
} // end namespace OpenInfraPlatform
