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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "../../model/shared_ptr.h"
#include "../../model/IfcBridgeObject.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		// TYPE IfcBridgeTechnologicalElementType = ENUMERATION OF (UNICELLULAR_MONO_BOX_GIRDER,MULTICELLULAR_MONO_BOX_GIRDER,UNICELLULAR_MULTI_BOX_GIRDER,MULTICELLULAR_MULTI_BOX_GIRDER,SOLID_SLAB,HOLLOW_SLAB,SLAB_WITH_BROAD_CANTILEVER,DOUBLE_BEAM_RIBBED_SLAB,MULTI_BEAM_RIBBED_SLAB,MASSIVE_SECTION_ELEMENT,HOLLOW_SECTION_ELEMENT,MARKETED_SECTION_GIRDER,RE_ASSEMBLED_SECTION_GIRDER,TRUSS,LADDER_OR_VIERENDEEL,BOW_STRING);
		class IfcBridgeTechnologicalElementType : public IfcBridgeAbstractEnum, public IfcBridgeType
		{
		public:
			enum IfcBridgeTechnologicalElementTypeEnum
			{
				ENUM_UNICELLULAR_MONO_BOX_GIRDER,
				ENUM_MULTICELLULAR_MONO_BOX_GIRDER,
				ENUM_UNICELLULAR_MULTI_BOX_GIRDER,
				ENUM_MULTICELLULAR_MULTI_BOX_GIRDER,
				ENUM_SOLID_SLAB,
				ENUM_HOLLOW_SLAB,
				ENUM_SLAB_WITH_BROAD_CANTILEVER,
				ENUM_DOUBLE_BEAM_RIBBED_SLAB,
				ENUM_MULTI_BEAM_RIBBED_SLAB,
				ENUM_MASSIVE_SECTION_ELEMENT,
				ENUM_HOLLOW_SECTION_ELEMENT,
				ENUM_MARKETED_SECTION_GIRDER,
				ENUM_RE_ASSEMBLED_SECTION_GIRDER,
				ENUM_TRUSS,
				ENUM_LADDER_OR_VIERENDEEL,
				ENUM_BOW_STRING
			};

			IfcBridgeTechnologicalElementType();
			IfcBridgeTechnologicalElementType( IfcBridgeTechnologicalElementTypeEnum e ) { m_enum = e; }
			~IfcBridgeTechnologicalElementType();
			virtual const char* classname() const { return "IfcBridgeTechnologicalElementType"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcBridgeTechnologicalElementType> readStepData( std::string& arg );
			IfcBridgeTechnologicalElementTypeEnum m_enum;
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

