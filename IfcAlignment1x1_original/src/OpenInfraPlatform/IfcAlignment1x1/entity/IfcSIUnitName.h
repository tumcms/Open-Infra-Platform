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
		// TYPE IfcSIUnitName = ENUMERATION OF(AMPEREBECQUERELCANDELACOULOMBCUBIC_METREDEGREE_CELSIUSFARADGRAMGRAYHENRYHERTZJOULEKELVINLUMENLUXMETREMOLENEWTONOHMPASCALRADIANSECONDSIEMENSSIEVERTSQUARE_METRESTERADIANTESLAVOLTWATTWEBER;
		class IfcSIUnitName : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcSIUnitNameEnum
			{
				 ENUM_AMPERE,
				 ENUM_BECQUEREL,
				 ENUM_CANDELA,
				 ENUM_COULOMB,
				 ENUM_CUBIC_METRE,
				 ENUM_DEGREE_CELSIUS,
				 ENUM_FARAD,
				 ENUM_GRAM,
				 ENUM_GRAY,
				 ENUM_HENRY,
				 ENUM_HERTZ,
				 ENUM_JOULE,
				 ENUM_KELVIN,
				 ENUM_LUMEN,
				 ENUM_LUX,
				 ENUM_METRE,
				 ENUM_MOLE,
				 ENUM_NEWTON,
				 ENUM_OHM,
				 ENUM_PASCAL,
				 ENUM_RADIAN,
				 ENUM_SECOND,
				 ENUM_SIEMENS,
				 ENUM_SIEVERT,
				 ENUM_SQUARE_METRE,
				 ENUM_STERADIAN,
				 ENUM_TESLA,
				 ENUM_VOLT,
				 ENUM_WATT,
				 ENUM_WEBER
			};

			IfcSIUnitName();
			IfcSIUnitName(IfcSIUnitNameEnum value);
			virtual ~IfcSIUnitName();
			virtual const char* classname() const { return "IfcSIUnitName"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcSIUnitName> readStepData(const std::string& arg);
			IfcSIUnitNameEnum m_enum;
		}; // end class IfcSIUnitName
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
