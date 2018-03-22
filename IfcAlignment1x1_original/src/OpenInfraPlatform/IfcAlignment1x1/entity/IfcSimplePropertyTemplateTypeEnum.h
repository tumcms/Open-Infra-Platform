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
		// TYPE IfcSimplePropertyTemplateTypeEnum = ENUMERATION OF(P_SINGLEVALUEP_ENUMERATEDVALUEP_BOUNDEDVALUEP_LISTVALUEP_TABLEVALUEP_REFERENCEVALUEQ_LENGTHQ_AREAQ_VOLUMEQ_COUNTQ_WEIGHTQ_TIME;
		class IfcSimplePropertyTemplateTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcSimplePropertyTemplateTypeEnumEnum
			{
				 ENUM_P_SINGLEVALUE,
				 ENUM_P_ENUMERATEDVALUE,
				 ENUM_P_BOUNDEDVALUE,
				 ENUM_P_LISTVALUE,
				 ENUM_P_TABLEVALUE,
				 ENUM_P_REFERENCEVALUE,
				 ENUM_Q_LENGTH,
				 ENUM_Q_AREA,
				 ENUM_Q_VOLUME,
				 ENUM_Q_COUNT,
				 ENUM_Q_WEIGHT,
				 ENUM_Q_TIME
			};

			IfcSimplePropertyTemplateTypeEnum();
			IfcSimplePropertyTemplateTypeEnum(IfcSimplePropertyTemplateTypeEnumEnum value);
			virtual ~IfcSimplePropertyTemplateTypeEnum();
			virtual const char* classname() const { return "IfcSimplePropertyTemplateTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcSimplePropertyTemplateTypeEnum> readStepData(const std::string& arg);
			IfcSimplePropertyTemplateTypeEnumEnum m_enum;
		}; // end class IfcSimplePropertyTemplateTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
