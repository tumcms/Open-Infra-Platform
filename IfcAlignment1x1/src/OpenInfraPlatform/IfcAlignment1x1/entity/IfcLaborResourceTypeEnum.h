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
		// TYPE IfcLaborResourceTypeEnum = ENUMERATION OF(ADMINISTRATIONCARPENTRYCLEANINGCONCRETEDRYWALLELECTRICFINISHINGFLOORINGGENERALHVACLANDSCAPINGMASONRYPAINTINGPAVINGPLUMBINGROOFINGSITEGRADINGSTEELWORKSURVEYINGUSERDEFINEDNOTDEFINED;
		class IfcLaborResourceTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcLaborResourceTypeEnumEnum
			{
				 ENUM_ADMINISTRATION,
				 ENUM_CARPENTRY,
				 ENUM_CLEANING,
				 ENUM_CONCRETE,
				 ENUM_DRYWALL,
				 ENUM_ELECTRIC,
				 ENUM_FINISHING,
				 ENUM_FLOORING,
				 ENUM_GENERAL,
				 ENUM_HVAC,
				 ENUM_LANDSCAPING,
				 ENUM_MASONRY,
				 ENUM_PAINTING,
				 ENUM_PAVING,
				 ENUM_PLUMBING,
				 ENUM_ROOFING,
				 ENUM_SITEGRADING,
				 ENUM_STEELWORK,
				 ENUM_SURVEYING,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcLaborResourceTypeEnum();
			IfcLaborResourceTypeEnum(IfcLaborResourceTypeEnumEnum value);
			virtual ~IfcLaborResourceTypeEnum();
			virtual const char* classname() const { return "IfcLaborResourceTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcLaborResourceTypeEnum> readStepData(const std::string& arg);
			IfcLaborResourceTypeEnumEnum m_enum;
		}; // end class IfcLaborResourceTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
