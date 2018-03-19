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
		// TYPE IfcDistributionSystemEnum = ENUMERATION OF(AIRCONDITIONINGAUDIOVISUALCHEMICALCHILLEDWATERCOMMUNICATIONCOMPRESSEDAIRCONDENSERWATERCONTROLCONVEYINGDATADISPOSALDOMESTICCOLDWATERDOMESTICHOTWATERDRAINAGEEARTHINGELECTRICALELECTROACOUSTICEXHAUSTFIREPROTECTIONFUELGASHAZARDOUSHEATINGLIGHTINGLIGHTNINGPROTECTIONMUNICIPALSOLIDWASTEOILOPERATIONALPOWERGENERATIONRAINWATERREFRIGERATIONSECURITYSEWAGESIGNALSTORMWATERTELEPHONETVVACUUMVENTVENTILATIONWASTEWATERWATERSUPPLYUSERDEFINEDNOTDEFINED;
		class IfcDistributionSystemEnum : public IfcAlignment1x1Type, public IfcAlignment1x1AbstractEnum
		{
		public:
			enum IfcDistributionSystemEnumEnum
			{
				 ENUM_AIRCONDITIONING,
				 ENUM_AUDIOVISUAL,
				 ENUM_CHEMICAL,
				 ENUM_CHILLEDWATER,
				 ENUM_COMMUNICATION,
				 ENUM_COMPRESSEDAIR,
				 ENUM_CONDENSERWATER,
				 ENUM_CONTROL,
				 ENUM_CONVEYING,
				 ENUM_DATA,
				 ENUM_DISPOSAL,
				 ENUM_DOMESTICCOLDWATER,
				 ENUM_DOMESTICHOTWATER,
				 ENUM_DRAINAGE,
				 ENUM_EARTHING,
				 ENUM_ELECTRICAL,
				 ENUM_ELECTROACOUSTIC,
				 ENUM_EXHAUST,
				 ENUM_FIREPROTECTION,
				 ENUM_FUEL,
				 ENUM_GAS,
				 ENUM_HAZARDOUS,
				 ENUM_HEATING,
				 ENUM_LIGHTING,
				 ENUM_LIGHTNINGPROTECTION,
				 ENUM_MUNICIPALSOLIDWASTE,
				 ENUM_OIL,
				 ENUM_OPERATIONAL,
				 ENUM_POWERGENERATION,
				 ENUM_RAINWATER,
				 ENUM_REFRIGERATION,
				 ENUM_SECURITY,
				 ENUM_SEWAGE,
				 ENUM_SIGNAL,
				 ENUM_STORMWATER,
				 ENUM_TELEPHONE,
				 ENUM_TV,
				 ENUM_VACUUM,
				 ENUM_VENT,
				 ENUM_VENTILATION,
				 ENUM_WASTEWATER,
				 ENUM_WATERSUPPLY,
				 ENUM_USERDEFINED,
				 ENUM_NOTDEFINED
			};

			IfcDistributionSystemEnum();
			IfcDistributionSystemEnum(IfcDistributionSystemEnumEnum value);
			virtual ~IfcDistributionSystemEnum();
			virtual const char* classname() const { return "IfcDistributionSystemEnum"; }
			virtual void getStepParameter(std::stringstream& stream, bool is_select_type = false) const;
			static std::shared_ptr<IfcDistributionSystemEnum> readStepData(const std::string& arg);
			IfcDistributionSystemEnumEnum m_enum;
		}; // end class IfcDistributionSystemEnum
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
