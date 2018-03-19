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
		// TYPE IfcCommunicationsApplianceTypeEnum = ENUMERATION OF(ANTENNACOMPUTERFAXGATEWAYMODEMNETWORKAPPLIANCENETWORKBRIDGENETWORKHUBPRINTERREPEATERROUTERSCANNERUSERDEFINEDNOTDEFINED;
		class IfcCommunicationsApplianceTypeEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcCommunicationsApplianceTypeEnumEnum
			{
				 ENUM_ANTENNA,
				 ENUM_COMPUTER,
				 ENUM_FAX,
				 ENUM_GATEWAY,
				 ENUM_MODEM,
				 ENUM_NETWORKAPPLIANCE,
				 ENUM_NETWORKBRIDGE,
				 ENUM_NETWORKHUB,
				 ENUM_PRINTER,
				 ENUM_REPEATER,
				 ENUM_ROUTER,
				 ENUM_SCANNER,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcCommunicationsApplianceTypeEnum();
			IfcCommunicationsApplianceTypeEnum(IfcCommunicationsApplianceTypeEnumEnum value);
			virtual ~IfcCommunicationsApplianceTypeEnum();
			virtual const char* classname() const { return "IfcCommunicationsApplianceTypeEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcCommunicationsApplianceTypeEnum> readStepData(const std::string& arg);
			IfcCommunicationsApplianceTypeEnumEnum m_enum;
		}; // end class IfcCommunicationsApplianceTypeEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
