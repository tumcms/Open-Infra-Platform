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
		// TYPE IfcStairTypeEnum = ENUMERATION OF(STRAIGHT_RUN_STAIRTWO_STRAIGHT_RUN_STAIRQUARTER_WINDING_STAIRQUARTER_TURN_STAIRHALF_WINDING_STAIRHALF_TURN_STAIRTWO_QUARTER_WINDING_STAIRTWO_QUARTER_TURN_STAIRTHREE_QUARTER_WINDING_STAIRTHREE_QUARTER_TURN_STAIRSPIRAL_STAIRDOUBLE_RETURN_STAIRCURVED_RUN_STAIRTWO_CURVED_RUN_STAIRUSERDEFINEDNOTDEFINED;
		class IfcStairTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcStairTypeEnumEnum
			{
				 ENUM_STRAIGHT_RUN_STAIR,
				 ENUM_TWO_STRAIGHT_RUN_STAIR,
				 ENUM_QUARTER_WINDING_STAIR,
				 ENUM_QUARTER_TURN_STAIR,
				 ENUM_HALF_WINDING_STAIR,
				 ENUM_HALF_TURN_STAIR,
				 ENUM_TWO_QUARTER_WINDING_STAIR,
				 ENUM_TWO_QUARTER_TURN_STAIR,
				 ENUM_THREE_QUARTER_WINDING_STAIR,
				 ENUM_THREE_QUARTER_TURN_STAIR,
				 ENUM_SPIRAL_STAIR,
				 ENUM_DOUBLE_RETURN_STAIR,
				 ENUM_CURVED_RUN_STAIR,
				 ENUM_TWO_CURVED_RUN_STAIR,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcStairTypeEnum();
			IfcStairTypeEnum(IfcStairTypeEnumEnum value);
			virtual ~IfcStairTypeEnum();
			virtual const char* classname() const { return "IfcStairTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcStairTypeEnum> readStepData(const std::string& arg);
			IfcStairTypeEnumEnum m_enum;
		}; // end class IfcStairTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
