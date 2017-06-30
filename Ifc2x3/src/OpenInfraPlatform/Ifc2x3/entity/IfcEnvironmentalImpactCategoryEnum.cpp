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
#include "include/IfcEnvironmentalImpactCategoryEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcEnvironmentalImpactCategoryEnum 
		IfcEnvironmentalImpactCategoryEnum::IfcEnvironmentalImpactCategoryEnum() {}
		IfcEnvironmentalImpactCategoryEnum::~IfcEnvironmentalImpactCategoryEnum() {}
		void IfcEnvironmentalImpactCategoryEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCENVIRONMENTALIMPACTCATEGORYENUM("; }
			if( m_enum == ENUM_COMBINEDVALUE )
			{
				stream << ".COMBINEDVALUE.";
			}
			else if( m_enum == ENUM_DISPOSAL )
			{
				stream << ".DISPOSAL.";
			}
			else if( m_enum == ENUM_EXTRACTION )
			{
				stream << ".EXTRACTION.";
			}
			else if( m_enum == ENUM_INSTALLATION )
			{
				stream << ".INSTALLATION.";
			}
			else if( m_enum == ENUM_MANUFACTURE )
			{
				stream << ".MANUFACTURE.";
			}
			else if( m_enum == ENUM_TRANSPORTATION )
			{
				stream << ".TRANSPORTATION.";
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
		shared_ptr<IfcEnvironmentalImpactCategoryEnum> IfcEnvironmentalImpactCategoryEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcEnvironmentalImpactCategoryEnum>(); }
			shared_ptr<IfcEnvironmentalImpactCategoryEnum> type_object( new IfcEnvironmentalImpactCategoryEnum() );
			if( _stricmp( arg.c_str(), ".COMBINEDVALUE." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_COMBINEDVALUE;
			}
			else if( _stricmp( arg.c_str(), ".DISPOSAL." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_DISPOSAL;
			}
			else if( _stricmp( arg.c_str(), ".EXTRACTION." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_EXTRACTION;
			}
			else if( _stricmp( arg.c_str(), ".INSTALLATION." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_INSTALLATION;
			}
			else if( _stricmp( arg.c_str(), ".MANUFACTURE." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_MANUFACTURE;
			}
			else if( _stricmp( arg.c_str(), ".TRANSPORTATION." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_TRANSPORTATION;
			}
			else if( _stricmp( arg.c_str(), ".USERDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_USERDEFINED;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcEnvironmentalImpactCategoryEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
