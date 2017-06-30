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
#include "include/IfcVoidingFeatureTypeEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
	{
		// TYPE IfcVoidingFeatureTypeEnum 
		IfcVoidingFeatureTypeEnum::IfcVoidingFeatureTypeEnum() {}
		IfcVoidingFeatureTypeEnum::~IfcVoidingFeatureTypeEnum() {}
		void IfcVoidingFeatureTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCVOIDINGFEATURETYPEENUM("; }
			if( m_enum == ENUM_CUTOUT )
			{
				stream << ".CUTOUT.";
			}
			else if( m_enum == ENUM_NOTCH )
			{
				stream << ".NOTCH.";
			}
			else if( m_enum == ENUM_HOLE )
			{
				stream << ".HOLE.";
			}
			else if( m_enum == ENUM_MITER )
			{
				stream << ".MITER.";
			}
			else if( m_enum == ENUM_CHAMFER )
			{
				stream << ".CHAMFER.";
			}
			else if( m_enum == ENUM_EDGE )
			{
				stream << ".EDGE.";
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
		shared_ptr<IfcVoidingFeatureTypeEnum> IfcVoidingFeatureTypeEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcVoidingFeatureTypeEnum>(); }
			shared_ptr<IfcVoidingFeatureTypeEnum> type_object( new IfcVoidingFeatureTypeEnum() );
			if( _stricmp( arg.c_str(), ".CUTOUT." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_CUTOUT;
			}
			else if( _stricmp( arg.c_str(), ".NOTCH." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_NOTCH;
			}
			else if( _stricmp( arg.c_str(), ".HOLE." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_HOLE;
			}
			else if( _stricmp( arg.c_str(), ".MITER." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_MITER;
			}
			else if( _stricmp( arg.c_str(), ".CHAMFER." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_CHAMFER;
			}
			else if( _stricmp( arg.c_str(), ".EDGE." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_EDGE;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcVoidingFeatureTypeEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc4
} // end namespace OpenInfraPlatform
