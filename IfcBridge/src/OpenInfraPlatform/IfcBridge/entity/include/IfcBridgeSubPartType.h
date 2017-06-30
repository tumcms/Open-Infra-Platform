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
		// TYPE IfcBridgeSubPartType = ENUMERATION OF (LEFT_WEB,RIGHT_WEB,CENTRAL_WEB,TOP_SLAB,LOWER_SLAB,RIGHT_OVERHANG,LEFT_OVERHANG,UPPER_FLANGE_,LOWER_FLANGE,LOWER_FLOORING,UPPER_FLOORING,MORPHOLOGY_NODE,REFERENCE_FIBRE,BRANCH_WALL);
		class IfcBridgeSubPartType : public IfcBridgeAbstractEnum, public IfcBridgeType
		{
		public:
			enum IfcBridgeSubPartTypeEnum
			{
				ENUM_LEFT_WEB,
				ENUM_RIGHT_WEB,
				ENUM_CENTRAL_WEB,
				ENUM_TOP_SLAB,
				ENUM_LOWER_SLAB,
				ENUM_RIGHT_OVERHANG,
				ENUM_LEFT_OVERHANG,
				ENUM_UPPER_FLANGE_,
				ENUM_LOWER_FLANGE,
				ENUM_LOWER_FLOORING,
				ENUM_UPPER_FLOORING,
				ENUM_MORPHOLOGY_NODE,
				ENUM_REFERENCE_FIBRE,
				ENUM_BRANCH_WALL
			};

			IfcBridgeSubPartType();
			IfcBridgeSubPartType( IfcBridgeSubPartTypeEnum e ) { m_enum = e; }
			~IfcBridgeSubPartType();
			virtual const char* classname() const { return "IfcBridgeSubPartType"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcBridgeSubPartType> readStepData( std::string& arg );
			IfcBridgeSubPartTypeEnum m_enum;
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

