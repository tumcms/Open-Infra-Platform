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
#include "include/IfcBridgeTechnologicalElementType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeTechnologicalElementType 
		IfcBridgeTechnologicalElementType::IfcBridgeTechnologicalElementType() {}
		IfcBridgeTechnologicalElementType::~IfcBridgeTechnologicalElementType() {}
		void IfcBridgeTechnologicalElementType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGETECHNOLOGICALELEMENTTYPE("; }
			if( m_enum == ENUM_UNICELLULAR_MONO_BOX_GIRDER )
			{
				stream << ".UNICELLULAR_MONO_BOX_GIRDER.";
			}
			else if( m_enum == ENUM_MULTICELLULAR_MONO_BOX_GIRDER )
			{
				stream << ".MULTICELLULAR_MONO_BOX_GIRDER.";
			}
			else if( m_enum == ENUM_UNICELLULAR_MULTI_BOX_GIRDER )
			{
				stream << ".UNICELLULAR_MULTI_BOX_GIRDER.";
			}
			else if( m_enum == ENUM_MULTICELLULAR_MULTI_BOX_GIRDER )
			{
				stream << ".MULTICELLULAR_MULTI_BOX_GIRDER.";
			}
			else if( m_enum == ENUM_SOLID_SLAB )
			{
				stream << ".SOLID_SLAB.";
			}
			else if( m_enum == ENUM_HOLLOW_SLAB )
			{
				stream << ".HOLLOW_SLAB.";
			}
			else if( m_enum == ENUM_SLAB_WITH_BROAD_CANTILEVER )
			{
				stream << ".SLAB_WITH_BROAD_CANTILEVER.";
			}
			else if( m_enum == ENUM_DOUBLE_BEAM_RIBBED_SLAB )
			{
				stream << ".DOUBLE_BEAM_RIBBED_SLAB.";
			}
			else if( m_enum == ENUM_MULTI_BEAM_RIBBED_SLAB )
			{
				stream << ".MULTI_BEAM_RIBBED_SLAB.";
			}
			else if( m_enum == ENUM_MASSIVE_SECTION_ELEMENT )
			{
				stream << ".MASSIVE_SECTION_ELEMENT.";
			}
			else if( m_enum == ENUM_HOLLOW_SECTION_ELEMENT )
			{
				stream << ".HOLLOW_SECTION_ELEMENT.";
			}
			else if( m_enum == ENUM_MARKETED_SECTION_GIRDER )
			{
				stream << ".MARKETED_SECTION_GIRDER.";
			}
			else if( m_enum == ENUM_RE_ASSEMBLED_SECTION_GIRDER )
			{
				stream << ".RE_ASSEMBLED_SECTION_GIRDER.";
			}
			else if( m_enum == ENUM_TRUSS )
			{
				stream << ".TRUSS.";
			}
			else if( m_enum == ENUM_LADDER_OR_VIERENDEEL )
			{
				stream << ".LADDER_OR_VIERENDEEL.";
			}
			else if( m_enum == ENUM_BOW_STRING )
			{
				stream << ".BOW_STRING.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgeTechnologicalElementType> IfcBridgeTechnologicalElementType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgeTechnologicalElementType>(); }
			shared_ptr<IfcBridgeTechnologicalElementType> type_object( new IfcBridgeTechnologicalElementType() );
			if( _stricmp( arg.c_str(), ".UNICELLULAR_MONO_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_UNICELLULAR_MONO_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".MULTICELLULAR_MONO_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_MULTICELLULAR_MONO_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".UNICELLULAR_MULTI_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_UNICELLULAR_MULTI_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".MULTICELLULAR_MULTI_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_MULTICELLULAR_MULTI_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".SOLID_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_SOLID_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".HOLLOW_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_HOLLOW_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".SLAB_WITH_BROAD_CANTILEVER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_SLAB_WITH_BROAD_CANTILEVER;
			}
			else if( _stricmp( arg.c_str(), ".DOUBLE_BEAM_RIBBED_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_DOUBLE_BEAM_RIBBED_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".MULTI_BEAM_RIBBED_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_MULTI_BEAM_RIBBED_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".MASSIVE_SECTION_ELEMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_MASSIVE_SECTION_ELEMENT;
			}
			else if( _stricmp( arg.c_str(), ".HOLLOW_SECTION_ELEMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_HOLLOW_SECTION_ELEMENT;
			}
			else if( _stricmp( arg.c_str(), ".MARKETED_SECTION_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_MARKETED_SECTION_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".RE_ASSEMBLED_SECTION_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_RE_ASSEMBLED_SECTION_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".TRUSS." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_TRUSS;
			}
			else if( _stricmp( arg.c_str(), ".LADDER_OR_VIERENDEEL." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_LADDER_OR_VIERENDEEL;
			}
			else if( _stricmp( arg.c_str(), ".BOW_STRING." ) == 0 )
			{
				type_object->m_enum = IfcBridgeTechnologicalElementType::ENUM_BOW_STRING;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
