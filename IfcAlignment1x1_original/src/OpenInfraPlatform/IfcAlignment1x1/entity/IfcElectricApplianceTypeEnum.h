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
#include <memory>
#include <sstream>
#include <string>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		// TYPE IfcElectricApplianceTypeEnum = ENUMERATION OF(DISHWASHERELECTRICCOOKERFREESTANDINGELECTRICHEATERFREESTANDINGFANFREESTANDINGWATERHEATERFREESTANDINGWATERCOOLERFREEZERFRIDGE_FREEZERHANDDRYERKITCHENMACHINEMICROWAVEPHOTOCOPIERREFRIGERATORTUMBLEDRYERVENDINGMACHINEWASHINGMACHINEUSERDEFINEDNOTDEFINED;
		class IfcElectricApplianceTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcElectricApplianceTypeEnumEnum
			{
				 ENUM_DISHWASHER,
				 ENUM_ELECTRICCOOKER,
				 ENUM_FREESTANDINGELECTRICHEATER,
				 ENUM_FREESTANDINGFAN,
				 ENUM_FREESTANDINGWATERHEATER,
				 ENUM_FREESTANDINGWATERCOOLER,
				 ENUM_FREEZER,
				 ENUM_FRIDGE_FREEZER,
				 ENUM_HANDDRYER,
				 ENUM_KITCHENMACHINE,
				 ENUM_MICROWAVE,
				 ENUM_PHOTOCOPIER,
				 ENUM_REFRIGERATOR,
				 ENUM_TUMBLEDRYER,
				 ENUM_VENDINGMACHINE,
				 ENUM_WASHINGMACHINE,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcElectricApplianceTypeEnum();
			IfcElectricApplianceTypeEnum(IfcElectricApplianceTypeEnumEnum value);
			virtual ~IfcElectricApplianceTypeEnum();
			virtual const char* classname() const { return "IfcElectricApplianceTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcElectricApplianceTypeEnum> readStepData(const std::string& arg);
			IfcElectricApplianceTypeEnumEnum m_enum;
		}; // end class IfcElectricApplianceTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
