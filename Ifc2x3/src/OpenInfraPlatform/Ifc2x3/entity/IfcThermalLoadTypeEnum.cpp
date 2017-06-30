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
#include "include/IfcThermalLoadTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcThermalLoadTypeEnum 
		IfcThermalLoadTypeEnum::IfcThermalLoadTypeEnum() {}
		IfcThermalLoadTypeEnum::~IfcThermalLoadTypeEnum() {}
		void IfcThermalLoadTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCTHERMALLOADTYPEENUM("; }
			if( m_enum == ENUM_SENSIBLE )
			{
				stream << ".SENSIBLE.";
			}
			else if( m_enum == ENUM_LATENT )
			{
				stream << ".LATENT.";
			}
			else if( m_enum == ENUM_RADIANT )
			{
				stream << ".RADIANT.";
			}
			else if( m_enum == ENUM_NOTDEFINED )
			{
				stream << ".NOTDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcThermalLoadTypeEnum> IfcThermalLoadTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcThermalLoadTypeEnum>(); }
			shared_ptr<IfcThermalLoadTypeEnum> type_object( new IfcThermalLoadTypeEnum() );
			if( _stricmp( arg.c_str(), ".SENSIBLE." ) == 0 )
			{
				type_object->m_enum = IfcThermalLoadTypeEnum::ENUM_SENSIBLE;
			}
			else if( _stricmp( arg.c_str(), ".LATENT." ) == 0 )
			{
				type_object->m_enum = IfcThermalLoadTypeEnum::ENUM_LATENT;
			}
			else if( _stricmp( arg.c_str(), ".RADIANT." ) == 0 )
			{
				type_object->m_enum = IfcThermalLoadTypeEnum::ENUM_RADIANT;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcThermalLoadTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
