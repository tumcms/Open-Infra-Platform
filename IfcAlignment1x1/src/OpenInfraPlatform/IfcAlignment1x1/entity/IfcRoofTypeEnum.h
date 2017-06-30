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
		// TYPE IfcRoofTypeEnum = ENUMERATION OF(FLAT_ROOFSHED_ROOFGABLE_ROOFHIP_ROOFHIPPED_GABLE_ROOFGAMBREL_ROOFMANSARD_ROOFBARREL_ROOFRAINBOW_ROOFBUTTERFLY_ROOFPAVILION_ROOFDOME_ROOFFREEFORMUSERDEFINEDNOTDEFINED;
		class IfcRoofTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcRoofTypeEnumEnum
			{
				 ENUM_FLAT_ROOF,
				 ENUM_SHED_ROOF,
				 ENUM_GABLE_ROOF,
				 ENUM_HIP_ROOF,
				 ENUM_HIPPED_GABLE_ROOF,
				 ENUM_GAMBREL_ROOF,
				 ENUM_MANSARD_ROOF,
				 ENUM_BARREL_ROOF,
				 ENUM_RAINBOW_ROOF,
				 ENUM_BUTTERFLY_ROOF,
				 ENUM_PAVILION_ROOF,
				 ENUM_DOME_ROOF,
				 ENUM_FREEFORM,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcRoofTypeEnum();
			IfcRoofTypeEnum(IfcRoofTypeEnumEnum value);
			virtual ~IfcRoofTypeEnum();
			virtual const char* classname() const { return "IfcRoofTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcRoofTypeEnum> readStepData(const std::string& arg);
			IfcRoofTypeEnumEnum m_enum;
		}; // end class IfcRoofTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
