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
#include "include/IfcModulusOfRotationalSubgradeReactionSelect.h"
#include "include/IfcModulusOfSubgradeReactionSelect.h"
#include "include/IfcModulusOfTranslationalSubgradeReactionSelect.h"
#include "include/IfcRotationalStiffnessSelect.h"
#include "include/IfcSimpleValue.h"
#include "include/IfcTranslationalStiffnessSelect.h"
#include "include/IfcWarpingStiffnessSelect.h"
#include "include/IfcBoolean.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcBoolean 
		IfcBoolean::IfcBoolean() {}
		IfcBoolean::IfcBoolean( bool value ) { m_value = value; }
		IfcBoolean::~IfcBoolean() {}
		void IfcBoolean::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBOOLEAN("; }
			//supertype as attribute: bool m_value
			if( m_value == false )
			{
				stream << ".F.";
			}
			else if( m_value == true )
			{
				stream << ".T.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBoolean> IfcBoolean::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBoolean>(); }
			shared_ptr<IfcBoolean> type_object( new IfcBoolean() );
			//supertype as attribute: bool m_value
			if( _stricmp( arg.c_str(), ".F." ) == 0 )
			{
				type_object->m_value = false;
			}
			else if( _stricmp( arg.c_str(), ".T." ) == 0 )
			{
				type_object->m_value = true;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
