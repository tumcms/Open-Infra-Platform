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
#include "include/IfcElectricHeaterTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcElectricHeaterTypeEnum 
		IfcElectricHeaterTypeEnum::IfcElectricHeaterTypeEnum() {}
		IfcElectricHeaterTypeEnum::~IfcElectricHeaterTypeEnum() {}
		void IfcElectricHeaterTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCELECTRICHEATERTYPEENUM("; }
			if( m_enum == ENUM_ELECTRICPOINTHEATER )
			{
				stream << ".ELECTRICPOINTHEATER.";
			}
			else if( m_enum == ENUM_ELECTRICCABLEHEATER )
			{
				stream << ".ELECTRICCABLEHEATER.";
			}
			else if( m_enum == ENUM_ELECTRICMATHEATER )
			{
				stream << ".ELECTRICMATHEATER.";
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
		shared_ptr<IfcElectricHeaterTypeEnum> IfcElectricHeaterTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcElectricHeaterTypeEnum>(); }
			shared_ptr<IfcElectricHeaterTypeEnum> type_object( new IfcElectricHeaterTypeEnum() );
			if( _stricmp( arg.c_str(), ".ELECTRICPOINTHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricHeaterTypeEnum::ENUM_ELECTRICPOINTHEATER;
			}
			else if( _stricmp( arg.c_str(), ".ELECTRICCABLEHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricHeaterTypeEnum::ENUM_ELECTRICCABLEHEATER;
			}
			else if( _stricmp( arg.c_str(), ".ELECTRICMATHEATER." ) == 0 )
			{
				type_object->m_enum = IfcElectricHeaterTypeEnum::ENUM_ELECTRICMATHEATER;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricHeaterTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcElectricHeaterTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
