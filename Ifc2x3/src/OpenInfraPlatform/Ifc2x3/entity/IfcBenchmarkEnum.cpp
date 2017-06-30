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
#include "include/IfcBenchmarkEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcBenchmarkEnum 
		IfcBenchmarkEnum::IfcBenchmarkEnum() {}
		IfcBenchmarkEnum::~IfcBenchmarkEnum() {}
		void IfcBenchmarkEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBENCHMARKENUM("; }
			if( m_enum == ENUM_GREATERTHAN )
			{
				stream << ".GREATERTHAN.";
			}
			else if( m_enum == ENUM_GREATERTHANOREQUALTO )
			{
				stream << ".GREATERTHANOREQUALTO.";
			}
			else if( m_enum == ENUM_LESSTHAN )
			{
				stream << ".LESSTHAN.";
			}
			else if( m_enum == ENUM_LESSTHANOREQUALTO )
			{
				stream << ".LESSTHANOREQUALTO.";
			}
			else if( m_enum == ENUM_EQUALTO )
			{
				stream << ".EQUALTO.";
			}
			else if( m_enum == ENUM_NOTEQUALTO )
			{
				stream << ".NOTEQUALTO.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBenchmarkEnum> IfcBenchmarkEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBenchmarkEnum>(); }
			shared_ptr<IfcBenchmarkEnum> type_object( new IfcBenchmarkEnum() );
			if( _stricmp( arg.c_str(), ".GREATERTHAN." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_GREATERTHAN;
			}
			else if( _stricmp( arg.c_str(), ".GREATERTHANOREQUALTO." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_GREATERTHANOREQUALTO;
			}
			else if( _stricmp( arg.c_str(), ".LESSTHAN." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_LESSTHAN;
			}
			else if( _stricmp( arg.c_str(), ".LESSTHANOREQUALTO." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_LESSTHANOREQUALTO;
			}
			else if( _stricmp( arg.c_str(), ".EQUALTO." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_EQUALTO;
			}
			else if( _stricmp( arg.c_str(), ".NOTEQUALTO." ) == 0 )
			{
				type_object->m_enum = IfcBenchmarkEnum::ENUM_NOTEQUALTO;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
