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
#include "include/IfcArithmeticOperatorEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcArithmeticOperatorEnum 
		IfcArithmeticOperatorEnum::IfcArithmeticOperatorEnum() {}
		IfcArithmeticOperatorEnum::~IfcArithmeticOperatorEnum() {}
		void IfcArithmeticOperatorEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCARITHMETICOPERATORENUM("; }
			if( m_enum == ENUM_ADD )
			{
				stream << ".ADD.";
			}
			else if( m_enum == ENUM_DIVIDE )
			{
				stream << ".DIVIDE.";
			}
			else if( m_enum == ENUM_MULTIPLY )
			{
				stream << ".MULTIPLY.";
			}
			else if( m_enum == ENUM_SUBTRACT )
			{
				stream << ".SUBTRACT.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcArithmeticOperatorEnum> IfcArithmeticOperatorEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcArithmeticOperatorEnum>(); }
			shared_ptr<IfcArithmeticOperatorEnum> type_object( new IfcArithmeticOperatorEnum() );
			if( _stricmp( arg.c_str(), ".ADD." ) == 0 )
			{
				type_object->m_enum = IfcArithmeticOperatorEnum::ENUM_ADD;
			}
			else if( _stricmp( arg.c_str(), ".DIVIDE." ) == 0 )
			{
				type_object->m_enum = IfcArithmeticOperatorEnum::ENUM_DIVIDE;
			}
			else if( _stricmp( arg.c_str(), ".MULTIPLY." ) == 0 )
			{
				type_object->m_enum = IfcArithmeticOperatorEnum::ENUM_MULTIPLY;
			}
			else if( _stricmp( arg.c_str(), ".SUBTRACT." ) == 0 )
			{
				type_object->m_enum = IfcArithmeticOperatorEnum::ENUM_SUBTRACT;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
