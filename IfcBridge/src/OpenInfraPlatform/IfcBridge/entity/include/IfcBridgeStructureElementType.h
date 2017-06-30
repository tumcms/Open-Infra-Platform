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
		// TYPE IfcBridgeStructureElementType = ENUMERATION OF (DECK,PIER,SMALL_PIER,PYLON,ARCH,LAUNCHING_NOSE,TEMPORARY_BENT,TRANSVERSE_GIRDER,STRUT,COUNTER_STRUT,CABLE,SUSPENDED_TENDON,SUSPENDER,MOBILE_FALSEWORK,STAYING_MAST,LAUNCHING_BEAM);
		class IfcBridgeStructureElementType : public IfcBridgeAbstractEnum, public IfcBridgeType
		{
		public:
			enum IfcBridgeStructureElementTypeEnum
			{
				ENUM_DECK,
				ENUM_PIER,
				ENUM_SMALL_PIER,
				ENUM_PYLON,
				ENUM_ARCH,
				ENUM_LAUNCHING_NOSE,
				ENUM_TEMPORARY_BENT,
				ENUM_TRANSVERSE_GIRDER,
				ENUM_STRUT,
				ENUM_COUNTER_STRUT,
				ENUM_CABLE,
				ENUM_SUSPENDED_TENDON,
				ENUM_SUSPENDER,
				ENUM_MOBILE_FALSEWORK,
				ENUM_STAYING_MAST,
				ENUM_LAUNCHING_BEAM
			};

			IfcBridgeStructureElementType();
			IfcBridgeStructureElementType( IfcBridgeStructureElementTypeEnum e ) { m_enum = e; }
			~IfcBridgeStructureElementType();
			virtual const char* classname() const { return "IfcBridgeStructureElementType"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcBridgeStructureElementType> readStepData( std::string& arg );
			IfcBridgeStructureElementTypeEnum m_enum;
		};
	} // end namespace IfcBridge
} // end namespace OpenInfraPlatform

