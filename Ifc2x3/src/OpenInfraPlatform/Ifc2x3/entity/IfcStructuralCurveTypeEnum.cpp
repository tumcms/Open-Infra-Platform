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
#include "include/IfcStructuralCurveTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcStructuralCurveTypeEnum 
		IfcStructuralCurveTypeEnum::IfcStructuralCurveTypeEnum() {}
		IfcStructuralCurveTypeEnum::~IfcStructuralCurveTypeEnum() {}
		void IfcStructuralCurveTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSTRUCTURALCURVETYPEENUM("; }
			if( m_enum == ENUM_RIGID_JOINED_MEMBER )
			{
				stream << ".RIGID_JOINED_MEMBER.";
			}
			else if( m_enum == ENUM_PIN_JOINED_MEMBER )
			{
				stream << ".PIN_JOINED_MEMBER.";
			}
			else if( m_enum == ENUM_CABLE )
			{
				stream << ".CABLE.";
			}
			else if( m_enum == ENUM_TENSION_MEMBER )
			{
				stream << ".TENSION_MEMBER.";
			}
			else if( m_enum == ENUM_COMPRESSION_MEMBER )
			{
				stream << ".COMPRESSION_MEMBER.";
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
		shared_ptr<IfcStructuralCurveTypeEnum> IfcStructuralCurveTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcStructuralCurveTypeEnum>(); }
			shared_ptr<IfcStructuralCurveTypeEnum> type_object( new IfcStructuralCurveTypeEnum() );
			if( _stricmp( arg.c_str(), ".RIGID_JOINED_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_RIGID_JOINED_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".PIN_JOINED_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_PIN_JOINED_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".CABLE." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_CABLE;
			}
			else if( _stricmp( arg.c_str(), ".TENSION_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_TENSION_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".COMPRESSION_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_COMPRESSION_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcStructuralCurveTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
