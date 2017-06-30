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
#include "../model/IfcBridgeException.h"
#include "include/IfcBridgeSubPartType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeSubPartType 
		IfcBridgeSubPartType::IfcBridgeSubPartType() {}
		IfcBridgeSubPartType::~IfcBridgeSubPartType() {}
		void IfcBridgeSubPartType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGESUBPARTTYPE("; }
			if( m_enum == ENUM_LEFT_WEB )
			{
				stream << ".LEFT_WEB.";
			}
			else if( m_enum == ENUM_RIGHT_WEB )
			{
				stream << ".RIGHT_WEB.";
			}
			else if( m_enum == ENUM_CENTRAL_WEB )
			{
				stream << ".CENTRAL_WEB.";
			}
			else if( m_enum == ENUM_TOP_SLAB )
			{
				stream << ".TOP_SLAB.";
			}
			else if( m_enum == ENUM_LOWER_SLAB )
			{
				stream << ".LOWER_SLAB.";
			}
			else if( m_enum == ENUM_RIGHT_OVERHANG )
			{
				stream << ".RIGHT_OVERHANG.";
			}
			else if( m_enum == ENUM_LEFT_OVERHANG )
			{
				stream << ".LEFT_OVERHANG.";
			}
			else if( m_enum == ENUM_UPPER_FLANGE_ )
			{
				stream << ".UPPER_FLANGE_.";
			}
			else if( m_enum == ENUM_LOWER_FLANGE )
			{
				stream << ".LOWER_FLANGE.";
			}
			else if( m_enum == ENUM_LOWER_FLOORING )
			{
				stream << ".LOWER_FLOORING.";
			}
			else if( m_enum == ENUM_UPPER_FLOORING )
			{
				stream << ".UPPER_FLOORING.";
			}
			else if( m_enum == ENUM_MORPHOLOGY_NODE )
			{
				stream << ".MORPHOLOGY_NODE.";
			}
			else if( m_enum == ENUM_REFERENCE_FIBRE )
			{
				stream << ".REFERENCE_FIBRE.";
			}
			else if( m_enum == ENUM_BRANCH_WALL )
			{
				stream << ".BRANCH_WALL.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeSubPartType> IfcBridgeSubPartType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeSubPartType>(); }
			shared_ptr<IfcBridgeSubPartType> type_object( new IfcBridgeSubPartType() );
			if( _stricmp( arg.c_str(), ".LEFT_WEB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_LEFT_WEB;
			}
			else if( _stricmp( arg.c_str(), ".RIGHT_WEB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_RIGHT_WEB;
			}
			else if( _stricmp( arg.c_str(), ".CENTRAL_WEB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_CENTRAL_WEB;
			}
			else if( _stricmp( arg.c_str(), ".TOP_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_TOP_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".LOWER_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_LOWER_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".RIGHT_OVERHANG." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_RIGHT_OVERHANG;
			}
			else if( _stricmp( arg.c_str(), ".LEFT_OVERHANG." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_LEFT_OVERHANG;
			}
			else if( _stricmp( arg.c_str(), ".UPPER_FLANGE_." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_UPPER_FLANGE_;
			}
			else if( _stricmp( arg.c_str(), ".LOWER_FLANGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_LOWER_FLANGE;
			}
			else if( _stricmp( arg.c_str(), ".LOWER_FLOORING." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_LOWER_FLOORING;
			}
			else if( _stricmp( arg.c_str(), ".UPPER_FLOORING." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_UPPER_FLOORING;
			}
			else if( _stricmp( arg.c_str(), ".MORPHOLOGY_NODE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_MORPHOLOGY_NODE;
			}
			else if( _stricmp( arg.c_str(), ".REFERENCE_FIBRE." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_REFERENCE_FIBRE;
			}
			else if( _stricmp( arg.c_str(), ".BRANCH_WALL." ) == 0 )
			{
				type_object->m_enum = IfcBridgeSubPartType::ENUM_BRANCH_WALL;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
