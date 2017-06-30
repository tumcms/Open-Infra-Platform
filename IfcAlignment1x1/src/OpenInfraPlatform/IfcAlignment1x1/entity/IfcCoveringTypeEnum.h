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
		// TYPE IfcCoveringTypeEnum = ENUMERATION OF(CEILINGFLOORINGCLADDINGROOFINGMOLDINGSKIRTINGBOARDINSULATIONMEMBRANESLEEVINGWRAPPINGUSERDEFINEDNOTDEFINED;
		class IfcCoveringTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcCoveringTypeEnumEnum
			{
				 ENUM_CEILING,
				 ENUM_FLOORING,
				 ENUM_CLADDING,
				 ENUM_ROOFING,
				 ENUM_MOLDING,
				 ENUM_SKIRTINGBOARD,
				 ENUM_INSULATION,
				 ENUM_MEMBRANE,
				 ENUM_SLEEVING,
				 ENUM_WRAPPING,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcCoveringTypeEnum();
			IfcCoveringTypeEnum(IfcCoveringTypeEnumEnum value);
			virtual ~IfcCoveringTypeEnum();
			virtual const char* classname() const { return "IfcCoveringTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcCoveringTypeEnum> readStepData(const std::string& arg);
			IfcCoveringTypeEnumEnum m_enum;
		}; // end class IfcCoveringTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
