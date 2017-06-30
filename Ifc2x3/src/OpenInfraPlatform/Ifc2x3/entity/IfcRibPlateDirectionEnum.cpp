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
#include "include/IfcRibPlateDirectionEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcRibPlateDirectionEnum 
		IfcRibPlateDirectionEnum::IfcRibPlateDirectionEnum() {}
		IfcRibPlateDirectionEnum::~IfcRibPlateDirectionEnum() {}
		void IfcRibPlateDirectionEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCRIBPLATEDIRECTIONENUM("; }
			if( m_enum == ENUM_DIRECTION_X )
			{
				stream << ".DIRECTION_X.";
			}
			else if( m_enum == ENUM_DIRECTION_Y )
			{
				stream << ".DIRECTION_Y.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcRibPlateDirectionEnum> IfcRibPlateDirectionEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcRibPlateDirectionEnum>(); }
			shared_ptr<IfcRibPlateDirectionEnum> type_object( new IfcRibPlateDirectionEnum() );
			if( _stricmp( arg.c_str(), ".DIRECTION_X." ) == 0 )
			{
				type_object->m_enum = IfcRibPlateDirectionEnum::ENUM_DIRECTION_X;
			}
			else if( _stricmp( arg.c_str(), ".DIRECTION_Y." ) == 0 )
			{
				type_object->m_enum = IfcRibPlateDirectionEnum::ENUM_DIRECTION_Y;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
