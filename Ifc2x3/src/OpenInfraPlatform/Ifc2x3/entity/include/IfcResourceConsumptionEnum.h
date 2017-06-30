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
		// TYPE IfcResourceConsumptionEnum = ENUMERATION OF	(CONSUMED	,PARTIALLYCONSUMED	,NOTCONSUMED	,OCCUPIED	,PARTIALLYOCCUPIED	,NOTOCCUPIED	,USERDEFINED	,NOTDEFINED);
		class IfcResourceConsumptionEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcResourceConsumptionEnumEnum
			{
				ENUM_CONSUMED,
				ENUM_PARTIALLYCONSUMED,
				ENUM_NOTCONSUMED,
				ENUM_OCCUPIED,
				ENUM_PARTIALLYOCCUPIED,
				ENUM_NOTOCCUPIED,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcResourceConsumptionEnum();
			IfcResourceConsumptionEnum( IfcResourceConsumptionEnumEnum e ) { m_enum = e; }
			~IfcResourceConsumptionEnum();
			virtual const char* classname() const { return "IfcResourceConsumptionEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcResourceConsumptionEnum> readStepData( std::string& arg );
			IfcResourceConsumptionEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

