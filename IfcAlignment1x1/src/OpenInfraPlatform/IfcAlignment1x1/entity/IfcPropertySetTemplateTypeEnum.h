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
		// TYPE IfcPropertySetTemplateTypeEnum = ENUMERATION OF(PSET_TYPEDRIVENONLYPSET_TYPEDRIVENOVERRIDEPSET_OCCURRENCEDRIVENPSET_PERFORMANCEDRIVENQTO_TYPEDRIVENONLYQTO_TYPEDRIVENOVERRIDEQTO_OCCURRENCEDRIVENNOTDEFINED;
		class IfcPropertySetTemplateTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcPropertySetTemplateTypeEnumEnum
			{
				 ENUM_PSET_TYPEDRIVENONLY,
				 ENUM_PSET_TYPEDRIVENOVERRIDE,
				 ENUM_PSET_OCCURRENCEDRIVEN,
				 ENUM_PSET_PERFORMANCEDRIVEN,
				 ENUM_QTO_TYPEDRIVENONLY,
				 ENUM_QTO_TYPEDRIVENOVERRIDE,
				 ENUM_QTO_OCCURRENCEDRIVEN,
				 ENUM_NOTDEFINED
			};

			IfcPropertySetTemplateTypeEnum();
			IfcPropertySetTemplateTypeEnum(IfcPropertySetTemplateTypeEnumEnum value);
			virtual ~IfcPropertySetTemplateTypeEnum();
			virtual const char* classname() const { return "IfcPropertySetTemplateTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcPropertySetTemplateTypeEnum> readStepData(const std::string& arg);
			IfcPropertySetTemplateTypeEnumEnum m_enum;
		}; // end class IfcPropertySetTemplateTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
