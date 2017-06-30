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
#include "include/IfcBridgePrismaticElementType.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgePrismaticElementType 
		IfcBridgePrismaticElementType::IfcBridgePrismaticElementType() {}
		IfcBridgePrismaticElementType::~IfcBridgePrismaticElementType() {}
		void IfcBridgePrismaticElementType::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCBRIDGEPRISMATICELEMENTTYPE("; }
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
			else if( m_enum == ENUM_MASTER_BEAM )
			{
				stream << ".MASTER_BEAM.";
			}
			else if( m_enum == ENUM_LONGITUDINAL_GIRDER )
			{
				stream << ".LONGITUDINAL_GIRDER.";
			}
			else if( m_enum == ENUM_RIGIDITY_BEAM )
			{
				stream << ".RIGIDITY_BEAM.";
			}
			else if( m_enum == ENUM_BRACING )
			{
				stream << ".BRACING.";
			}
			else if( m_enum == ENUM_UPPER_FLANGE )
			{
				stream << ".UPPER_FLANGE.";
			}
			else if( m_enum == ENUM_LOWER_FLANGE )
			{
				stream << ".LOWER_FLANGE.";
			}
			else if( m_enum == ENUM_UPPER_FOOTING )
			{
				stream << ".UPPER_FOOTING.";
			}
			else if( m_enum == ENUM_LOWER_FOOTING )
			{
				stream << ".LOWER_FOOTING.";
			}
			else if( m_enum == ENUM_WEB )
			{
				stream << ".WEB.";
			}
			else if( m_enum == ENUM_FLOORING_SHEET )
			{
				stream << ".FLOORING_SHEET.";
			}
			else if( m_enum == ENUM_BOTTOM_SHEET )
			{
				stream << ".BOTTOM_SHEET.";
			}
			else if( m_enum == ENUM_KERB_SHEET )
			{
				stream << ".KERB_SHEET.";
			}
			else if( m_enum == ENUM_CANTILEVER_SHEET )
			{
				stream << ".CANTILEVER_SHEET.";
			}
			else if( m_enum == ENUM_PAVEMENT_SHEET )
			{
				stream << ".PAVEMENT_SHEET.";
			}
			else if( m_enum == ENUM_AUGET )
			{
				stream << ".AUGET.";
			}
			else if( m_enum == ENUM_LONGITUDINAL_WEB_STIFFENER )
			{
				stream << ".LONGITUDINAL_WEB_STIFFENER.";
			}
			else if( m_enum == ENUM_RAKER )
			{
				stream << ".RAKER.";
			}
			else if( m_enum == ENUM_TRANSVERSE_GIRDER )
			{
				stream << ".TRANSVERSE_GIRDER.";
			}
			else if( m_enum == ENUM_DEFLECTER )
			{
				stream << ".DEFLECTER.";
			}
			else if( m_enum == ENUM_TRANSVERSE_MEMBER )
			{
				stream << ".TRANSVERSE_MEMBER.";
			}
			else if( m_enum == ENUM_TRANSVERSE )
			{
				stream << ".TRANSVERSE.";
			}
			else if( m_enum == ENUM_DIAGONALE )
			{
				stream << ".DIAGONALE.";
			}
			else if( m_enum == ENUM_JAMB )
			{
				stream << ".JAMB.";
			}
			else if( m_enum == ENUM_TENSION_MEMBER )
			{
				stream << ".TENSION_MEMBER.";
			}
			else if( m_enum == ENUM_BONDING_BAR )
			{
				stream << ".BONDING_BAR.";
			}
			else if( m_enum == ENUM_TRANSVERSAL_STIFFENER )
			{
				stream << ".TRANSVERSAL_STIFFENER.";
			}
			else if( m_enum == ENUM_STIFFENER_FOOTING )
			{
				stream << ".STIFFENER_FOOTING.";
			}
			else if( m_enum == ENUM_TENDON )
			{
				stream << ".TENDON.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcBridgePrismaticElementType> IfcBridgePrismaticElementType::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcBridgePrismaticElementType>(); }
			shared_ptr<IfcBridgePrismaticElementType> type_object( new IfcBridgePrismaticElementType() );
			if( _stricmp( arg.c_str(), ".UNICELLULAR_MONO_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_UNICELLULAR_MONO_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".MULTICELLULAR_MONO_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_MULTICELLULAR_MONO_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".UNICELLULAR_MULTI_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_UNICELLULAR_MULTI_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".MULTICELLULAR_MULTI_BOX_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_MULTICELLULAR_MULTI_BOX_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".DOUBLE_BEAM_RIBBED_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_DOUBLE_BEAM_RIBBED_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".MULTI_BEAM_RIBBED_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_MULTI_BEAM_RIBBED_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".MASSIVE_SECTION_ELEMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_MASSIVE_SECTION_ELEMENT;
			}
			else if( _stricmp( arg.c_str(), ".HOLLOW_SECTION_ELEMENT." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_HOLLOW_SECTION_ELEMENT;
			}
			else if( _stricmp( arg.c_str(), ".SOLID_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_SOLID_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".HOLLOW_SLAB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_HOLLOW_SLAB;
			}
			else if( _stricmp( arg.c_str(), ".SLAB_WITH_BROAD_CANTILEVER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_SLAB_WITH_BROAD_CANTILEVER;
			}
			else if( _stricmp( arg.c_str(), ".MASTER_BEAM." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_MASTER_BEAM;
			}
			else if( _stricmp( arg.c_str(), ".LONGITUDINAL_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_LONGITUDINAL_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".RIGIDITY_BEAM." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_RIGIDITY_BEAM;
			}
			else if( _stricmp( arg.c_str(), ".BRACING." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_BRACING;
			}
			else if( _stricmp( arg.c_str(), ".UPPER_FLANGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_UPPER_FLANGE;
			}
			else if( _stricmp( arg.c_str(), ".LOWER_FLANGE." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_LOWER_FLANGE;
			}
			else if( _stricmp( arg.c_str(), ".UPPER_FOOTING." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_UPPER_FOOTING;
			}
			else if( _stricmp( arg.c_str(), ".LOWER_FOOTING." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_LOWER_FOOTING;
			}
			else if( _stricmp( arg.c_str(), ".WEB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_WEB;
			}
			else if( _stricmp( arg.c_str(), ".FLOORING_SHEET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_FLOORING_SHEET;
			}
			else if( _stricmp( arg.c_str(), ".BOTTOM_SHEET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_BOTTOM_SHEET;
			}
			else if( _stricmp( arg.c_str(), ".KERB_SHEET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_KERB_SHEET;
			}
			else if( _stricmp( arg.c_str(), ".CANTILEVER_SHEET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_CANTILEVER_SHEET;
			}
			else if( _stricmp( arg.c_str(), ".PAVEMENT_SHEET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_PAVEMENT_SHEET;
			}
			else if( _stricmp( arg.c_str(), ".AUGET." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_AUGET;
			}
			else if( _stricmp( arg.c_str(), ".LONGITUDINAL_WEB_STIFFENER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_LONGITUDINAL_WEB_STIFFENER;
			}
			else if( _stricmp( arg.c_str(), ".RAKER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_RAKER;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSE_GIRDER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TRANSVERSE_GIRDER;
			}
			else if( _stricmp( arg.c_str(), ".DEFLECTER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_DEFLECTER;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSE_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TRANSVERSE_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSE." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TRANSVERSE;
			}
			else if( _stricmp( arg.c_str(), ".DIAGONALE." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_DIAGONALE;
			}
			else if( _stricmp( arg.c_str(), ".JAMB." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_JAMB;
			}
			else if( _stricmp( arg.c_str(), ".TENSION_MEMBER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TENSION_MEMBER;
			}
			else if( _stricmp( arg.c_str(), ".BONDING_BAR." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_BONDING_BAR;
			}
			else if( _stricmp( arg.c_str(), ".TRANSVERSAL_STIFFENER." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TRANSVERSAL_STIFFENER;
			}
			else if( _stricmp( arg.c_str(), ".STIFFENER_FOOTING." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_STIFFENER_FOOTING;
			}
			else if( _stricmp( arg.c_str(), ".TENDON." ) == 0 )
			{
				type_object->m_enum = IfcBridgePrismaticElementType::ENUM_TENDON;
			}
			return type_object;
		}
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform
