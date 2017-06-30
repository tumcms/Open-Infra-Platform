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
		// TYPE IfcElectricApplianceTypeEnum = ENUMERATION OF	(COMPUTER	,DIRECTWATERHEATER	,DISHWASHER	,ELECTRICCOOKER	,ELECTRICHEATER	,FACSIMILE	,FREESTANDINGFAN	,FREEZER	,FRIDGE_FREEZER	,HANDDRYER	,INDIRECTWATERHEATER	,MICROWAVE	,PHOTOCOPIER	,PRINTER	,REFRIGERATOR	,RADIANTHEATER	,SCANNER	,TELEPHONE	,TUMBLEDRYER	,TV	,VENDINGMACHINE	,WASHINGMACHINE	,WATERHEATER	,WATERCOOLER	,USERDEFINED	,NOTDEFINED);
		class IfcElectricApplianceTypeEnum : public Ifc2x3AbstractEnum, public Ifc2x3Type
		{
		public:
			enum IfcElectricApplianceTypeEnumEnum
			{
				ENUM_COMPUTER,
				ENUM_DIRECTWATERHEATER,
				ENUM_DISHWASHER,
				ENUM_ELECTRICCOOKER,
				ENUM_ELECTRICHEATER,
				ENUM_FACSIMILE,
				ENUM_FREESTANDINGFAN,
				ENUM_FREEZER,
				ENUM_FRIDGE_FREEZER,
				ENUM_HANDDRYER,
				ENUM_INDIRECTWATERHEATER,
				ENUM_MICROWAVE,
				ENUM_PHOTOCOPIER,
				ENUM_PRINTER,
				ENUM_REFRIGERATOR,
				ENUM_RADIANTHEATER,
				ENUM_SCANNER,
				ENUM_TELEPHONE,
				ENUM_TUMBLEDRYER,
				ENUM_TV,
				ENUM_VENDINGMACHINE,
				ENUM_WASHINGMACHINE,
				ENUM_WATERHEATER,
				ENUM_WATERCOOLER,
				ENUM_USERDEFINED,
				ENUM_NOTDEFINED
			};

			IfcElectricApplianceTypeEnum();
			IfcElectricApplianceTypeEnum( IfcElectricApplianceTypeEnumEnum e ) { m_enum = e; }
			~IfcElectricApplianceTypeEnum();
			virtual const char* classname() const { return "IfcElectricApplianceTypeEnum"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
			static shared_ptr<IfcElectricApplianceTypeEnum> readStepData( std::string& arg );
			IfcElectricApplianceTypeEnumEnum m_enum;
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

