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
		// TYPE IfcDoorStyleOperationEnum = ENUMERATION OF(SINGLE_SWING_LEFTSINGLE_SWING_RIGHTDOUBLE_DOOR_SINGLE_SWINGDOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFTDOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHTDOUBLE_SWING_LEFTDOUBLE_SWING_RIGHTDOUBLE_DOOR_DOUBLE_SWINGSLIDING_TO_LEFTSLIDING_TO_RIGHTDOUBLE_DOOR_SLIDINGFOLDING_TO_LEFTFOLDING_TO_RIGHTDOUBLE_DOOR_FOLDINGREVOLVINGROLLINGUPUSERDEFINEDNOTDEFINED;
		class IfcDoorStyleOperationEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcDoorStyleOperationEnumEnum
			{
				 ENUM_SINGLE_SWING_LEFT,
				 ENUM_SINGLE_SWING_RIGHT,
				 ENUM_DOUBLE_DOOR_SINGLE_SWING,
				 ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT,
				 ENUM_DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT,
				 ENUM_DOUBLE_SWING_LEFT,
				 ENUM_DOUBLE_SWING_RIGHT,
				 ENUM_DOUBLE_DOOR_DOUBLE_SWING,
				 ENUM_SLIDING_TO_LEFT,
				 ENUM_SLIDING_TO_RIGHT,
				 ENUM_DOUBLE_DOOR_SLIDING,
				 ENUM_FOLDING_TO_LEFT,
				 ENUM_FOLDING_TO_RIGHT,
				 ENUM_DOUBLE_DOOR_FOLDING,
				 ENUM_REVOLVING,
				 ENUM_ROLLINGUP,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcDoorStyleOperationEnum();
			IfcDoorStyleOperationEnum(IfcDoorStyleOperationEnumEnum value);
			virtual ~IfcDoorStyleOperationEnum();
			virtual const char* classname() const { return "IfcDoorStyleOperationEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcDoorStyleOperationEnum> readStepData(const std::string& arg);
			IfcDoorStyleOperationEnumEnum m_enum;
		}; // end class IfcDoorStyleOperationEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
