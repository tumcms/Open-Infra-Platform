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
		// TYPE IfcCostScheduleTypeEnum = ENUMERATION OF(BUDGETCOSTPLANESTIMATETENDERPRICEDBILLOFQUANTITIESUNPRICEDBILLOFQUANTITIESSCHEDULEOFRATESUSERDEFINEDNOTDEFINED;
		class IfcCostScheduleTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcCostScheduleTypeEnumEnum
			{
				 ENUM_BUDGET,
				 ENUM_COSTPLAN,
				 ENUM_ESTIMATE,
				 ENUM_TENDER,
				 ENUM_PRICEDBILLOFQUANTITIES,
				 ENUM_UNPRICEDBILLOFQUANTITIES,
				 ENUM_SCHEDULEOFRATES,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcCostScheduleTypeEnum();
			IfcCostScheduleTypeEnum(IfcCostScheduleTypeEnumEnum value);
			virtual ~IfcCostScheduleTypeEnum();
			virtual const char* classname() const { return "IfcCostScheduleTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcCostScheduleTypeEnum> readStepData(const std::string& arg);
			IfcCostScheduleTypeEnumEnum m_enum;
		}; // end class IfcCostScheduleTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
