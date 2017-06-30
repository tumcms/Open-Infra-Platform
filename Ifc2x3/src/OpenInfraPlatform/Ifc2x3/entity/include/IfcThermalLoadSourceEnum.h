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
#include "../../model/Ifc2x3Object.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcThermalLoadSourceEnum = ENUMERATION OF	(PEOPLE	,LIGHTING	,EQUIPMENT	,VENTILATIONINDOORAIR	,VENTILATIONOUTSIDEAIR	,RECIRCULATEDAIR	,EXHAUSTAIR	,AIREXCHANGERATE	,DRYBULBTEMPERATURE	,RELATIVEHUMIDITY	,INFILTRATION	,USERDEFINED	,NOTDEFINED);
		class IfcThermalLoadSourceEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcThermalLoadSourceEnumEnum
			{
				ENUM_PEOPLE,
				ENUM_LIGHTING,
				ENUM_EQUIPMENT,
				ENUM_VENTILATIONINDOORAIR,
				ENUM_VENTILATIONOUTSIDEAIR,
				ENUM_RECIRCULATEDAIR,
				ENUM_EXHAUSTAIR,
				ENUM_AIREXCHANGERATE,
				ENUM_DRYBULBTEMPERATURE,
				ENUM_RELATIVEHUMIDITY,
				ENUM_INFILTRATION,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcThermalLoadSourceEnum();
			IfcThermalLoadSourceEnum( IfcThermalLoadSourceEnumEnum e ) { m_enum = e; }
			~IfcThermalLoadSourceEnum();
			virtual const char* classname() const { return "IfcThermalLoadSourceEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcThermalLoadSourceEnum> readStepData( std::string& arg );
			IfcThermalLoadSourceEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

