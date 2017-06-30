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
#include "include/IfcCableFittingTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcCableFittingTypeEnum 
		IfcCableFittingTypeEnum::IfcCableFittingTypeEnum() {}
		IfcCableFittingTypeEnum::~IfcCableFittingTypeEnum() {}
		void IfcCableFittingTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCCABLEFITTINGTYPEENUM("; }
			if( m_enum == ENUM_CONNECTOR )
			{
				stream << ".CONNECTOR.";
			}
			else if( m_enum == ENUM_ENTRY )
			{
				stream << ".ENTRY.";
			}
			else if( m_enum == ENUM_EXIT )
			{
				stream << ".EXIT.";
			}
			else if( m_enum == ENUM_JUNCTION )
			{
				stream << ".JUNCTION.";
			}
			else if( m_enum == ENUM_TRANSITION )
			{
				stream << ".TRANSITION.";
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
		shared_ptr<IfcCableFittingTypeEnum> IfcCableFittingTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcCableFittingTypeEnum>(); }
			shared_ptr<IfcCableFittingTypeEnum> type_object( new IfcCableFittingTypeEnum() );
			if( _stricmp( arg.c_str(), ".CONNECTOR." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_CONNECTOR;
			}
			else if( _stricmp( arg.c_str(), ".ENTRY." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_ENTRY;
			}
			else if( _stricmp( arg.c_str(), ".EXIT." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_EXIT;
			}
			else if( _stricmp( arg.c_str(), ".JUNCTION." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_JUNCTION;
			}
			else if( _stricmp( arg.c_str(), ".TRANSITION." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_TRANSITION;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcCableFittingTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
