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
#include "include/IfcSurfaceTextureEnum.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcSurfaceTextureEnum 
		IfcSurfaceTextureEnum::IfcSurfaceTextureEnum() {}
		IfcSurfaceTextureEnum::~IfcSurfaceTextureEnum() {}
		void IfcSurfaceTextureEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
		{
			if( is_select_type ) { stream << "IFCSURFACETEXTUREENUM("; }
			if( m_enum == ENUM_BUMP )
			{
				stream << ".BUMP.";
			}
			else if( m_enum == ENUM_OPACITY )
			{
				stream << ".OPACITY.";
			}
			else if( m_enum == ENUM_REFLECTION )
			{
				stream << ".REFLECTION.";
			}
			else if( m_enum == ENUM_SELFILLUMINATION )
			{
				stream << ".SELFILLUMINATION.";
			}
			else if( m_enum == ENUM_SHININESS )
			{
				stream << ".SHININESS.";
			}
			else if( m_enum == ENUM_SPECULAR )
			{
				stream << ".SPECULAR.";
			}
			else if( m_enum == ENUM_TEXTURE )
			{
				stream << ".TEXTURE.";
			}
			else if( m_enum == ENUM_TRANSPARENCYMAP )
			{
				stream << ".TRANSPARENCYMAP.";
			}
			else if( m_enum == ENUM_NOTDEFINED )
			{
				stream << ".NOTDEFINED.";
			}
			if( is_select_type ) { stream << ")"; }
		}
		shared_ptr<IfcSurfaceTextureEnum> IfcSurfaceTextureEnum::readStepData( std::string& arg )
		{
			// read TYPE
			if( arg.compare( "$" ) == 0 ) { return shared_ptr<IfcSurfaceTextureEnum>(); }
			shared_ptr<IfcSurfaceTextureEnum> type_object( new IfcSurfaceTextureEnum() );
			if( _stricmp( arg.c_str(), ".BUMP." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_BUMP;
			}
			else if( _stricmp( arg.c_str(), ".OPACITY." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_OPACITY;
			}
			else if( _stricmp( arg.c_str(), ".REFLECTION." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_REFLECTION;
			}
			else if( _stricmp( arg.c_str(), ".SELFILLUMINATION." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_SELFILLUMINATION;
			}
			else if( _stricmp( arg.c_str(), ".SHININESS." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_SHININESS;
			}
			else if( _stricmp( arg.c_str(), ".SPECULAR." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_SPECULAR;
			}
			else if( _stricmp( arg.c_str(), ".TEXTURE." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_TEXTURE;
			}
			else if( _stricmp( arg.c_str(), ".TRANSPARENCYMAP." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_TRANSPARENCYMAP;
			}
			else if( _stricmp( arg.c_str(), ".NOTDEFINED." ) == 0 )
			{
				type_object->m_enum = IfcSurfaceTextureEnum::ENUM_NOTDEFINED;
			}
			return type_object;
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
