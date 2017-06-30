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
#include "../model/IfcTunnelException.h"
#include "include/IfcLayerSetDirectionEnum.h"

namespace OpenInfraPlatform
{
	namespace IfcTunnel
	{
		// TYPE IfcLayerSetDirectionEnum 
		IfcLayerSetDirectionEnum::IfcLayerSetDirectionEnum() {}
		IfcLayerSetDirectionEnum::~IfcLayerSetDirectionEnum() {}
		void IfcLayerSetDirectionEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCLAYERSETDIRECTIONENUM("; }
			if( m_enum == ENUM_AXIS1 )
			{
				stream << ".AXIS1.";
			}
			else if( m_enum == ENUM_AXIS2 )
			{
				stream << ".AXIS2.";
			}
			else if( m_enum == ENUM_AXIS3 )
			{
				stream << ".AXIS3.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcLayerSetDirectionEnum> IfcLayerSetDirectionEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcLayerSetDirectionEnum>(); }
			shared_ptr<IfcLayerSetDirectionEnum> type_object( new IfcLayerSetDirectionEnum() );
			if( _stricmp( arg.c_str(), ".AXIS1." ) == 0 )
			{
				type_object->m_enum = IfcLayerSetDirectionEnum::ENUM_AXIS1;
			}
			else if( _stricmp( arg.c_str(), ".AXIS2." ) == 0 )
			{
				type_object->m_enum = IfcLayerSetDirectionEnum::ENUM_AXIS2;
			}
			else if( _stricmp( arg.c_str(), ".AXIS3." ) == 0 )
			{
				type_object->m_enum = IfcLayerSetDirectionEnum::ENUM_AXIS3;
			}
			return type_object;
		}
	} // end namespace IfcTunnel
} // end namespace OpenInfraPlatform
