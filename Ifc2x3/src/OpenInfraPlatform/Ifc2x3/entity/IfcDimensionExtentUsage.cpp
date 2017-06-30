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
#include "include/IfcDimensionExtentUsage.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcDimensionExtentUsage 
		IfcDimensionExtentUsage::IfcDimensionExtentUsage() {}
		IfcDimensionExtentUsage::~IfcDimensionExtentUsage() {}
		void IfcDimensionExtentUsage::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCDIMENSIONEXTENTUSAGE("; }
			if( m_enum == ENUM_ORIGIN )
			{
				stream << ".ORIGIN.";
			}
			else if( m_enum == ENUM_TARGET )
			{
				stream << ".TARGET.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcDimensionExtentUsage> IfcDimensionExtentUsage::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcDimensionExtentUsage>(); }
			shared_ptr<IfcDimensionExtentUsage> type_object( new IfcDimensionExtentUsage() );
			if( _stricmp( arg.c_str(), ".ORIGIN." ) == 0 )
			{
				type_object->m_enum = IfcDimensionExtentUsage::ENUM_ORIGIN;
			}
			else if( _stricmp( arg.c_str(), ".TARGET." ) == 0 )
			{
				type_object->m_enum = IfcDimensionExtentUsage::ENUM_TARGET;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
