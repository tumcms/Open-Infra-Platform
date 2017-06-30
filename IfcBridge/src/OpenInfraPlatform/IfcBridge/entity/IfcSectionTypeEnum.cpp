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
#include "include/IfcSectionTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcSectionTypeEnum 
		IfcSectionTypeEnum::IfcSectionTypeEnum() {}
		IfcSectionTypeEnum::~IfcSectionTypeEnum() {}
		void IfcSectionTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSECTIONTYPEENUM("; }
			if( m_enum == ENUM_UNIFORM )
			{
				stream << ".UNIFORM.";
			}
			else if( m_enum == ENUM_TAPERED )
			{
				stream << ".TAPERED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcSectionTypeEnum> IfcSectionTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcSectionTypeEnum>(); }
			shared_ptr<IfcSectionTypeEnum> type_object( new IfcSectionTypeEnum() );
			if( _stricmp( arg.c_str(), ".UNIFORM." ) == 0 )
			{
				type_object->m_enum = IfcSectionTypeEnum::ENUM_UNIFORM;
			}
			else if( _stricmp( arg.c_str(), ".TAPERED." ) == 0 )
			{
				type_object->m_enum = IfcSectionTypeEnum::ENUM_TAPERED;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
