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

#include "IfcDerivedUnitEnum.h"
#include "OpenInfraPlatform/IfcAlignment1x1/reader/ReaderUtil.h"
#include "OpenInfraPlatform/IfcAlignment1x1/writer/WriterUtil.h"

namespace OpenInfraPlatform
{
	namespace IfcAlignment1x1
	{
		IfcDerivedUnitEnum::IfcDerivedUnitEnum() {}
		IfcDerivedUnitEnum::IfcDerivedUnitEnum(IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum value) { m_enum = value; }
		IfcDerivedUnitEnum::~IfcDerivedUnitEnum() {}
		void IfcDerivedUnitEnum::getStepParameter(std::stringstream& stream, bool is_select_type) const
			{
				if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ANGULARVELOCITYUNIT)
				{
					stream << ".ANGULARVELOCITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_AREADENSITYUNIT)
				{
					stream << ".AREADENSITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_COMPOUNDPLANEANGLEUNIT)
				{
					stream << ".COMPOUNDPLANEANGLEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_DYNAMICVISCOSITYUNIT)
				{
					stream << ".DYNAMICVISCOSITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_HEATFLUXDENSITYUNIT)
				{
					stream << ".HEATFLUXDENSITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_INTEGERCOUNTRATEUNIT)
				{
					stream << ".INTEGERCOUNTRATEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ISOTHERMALMOISTURECAPACITYUNIT)
				{
					stream << ".ISOTHERMALMOISTURECAPACITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_KINEMATICVISCOSITYUNIT)
				{
					stream << ".KINEMATICVISCOSITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_LINEARVELOCITYUNIT)
				{
					stream << ".LINEARVELOCITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MASSDENSITYUNIT)
				{
					stream << ".MASSDENSITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MASSFLOWRATEUNIT)
				{
					stream << ".MASSFLOWRATEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MOISTUREDIFFUSIVITYUNIT)
				{
					stream << ".MOISTUREDIFFUSIVITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MOLECULARWEIGHTUNIT)
				{
					stream << ".MOLECULARWEIGHTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SPECIFICHEATCAPACITYUNIT)
				{
					stream << ".SPECIFICHEATCAPACITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_THERMALADMITTANCEUNIT)
				{
					stream << ".THERMALADMITTANCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_THERMALCONDUCTANCEUNIT)
				{
					stream << ".THERMALCONDUCTANCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_THERMALRESISTANCEUNIT)
				{
					stream << ".THERMALRESISTANCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_THERMALTRANSMITTANCEUNIT)
				{
					stream << ".THERMALTRANSMITTANCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_VAPORPERMEABILITYUNIT)
				{
					stream << ".VAPORPERMEABILITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_VOLUMETRICFLOWRATEUNIT)
				{
					stream << ".VOLUMETRICFLOWRATEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ROTATIONALFREQUENCYUNIT)
				{
					stream << ".ROTATIONALFREQUENCYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_TORQUEUNIT)
				{
					stream << ".TORQUEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MOMENTOFINERTIAUNIT)
				{
					stream << ".MOMENTOFINERTIAUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_LINEARMOMENTUNIT)
				{
					stream << ".LINEARMOMENTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_LINEARFORCEUNIT)
				{
					stream << ".LINEARFORCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_PLANARFORCEUNIT)
				{
					stream << ".PLANARFORCEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MODULUSOFELASTICITYUNIT)
				{
					stream << ".MODULUSOFELASTICITYUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SHEARMODULUSUNIT)
				{
					stream << ".SHEARMODULUSUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_LINEARSTIFFNESSUNIT)
				{
					stream << ".LINEARSTIFFNESSUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ROTATIONALSTIFFNESSUNIT)
				{
					stream << ".ROTATIONALSTIFFNESSUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MODULUSOFSUBGRADEREACTIONUNIT)
				{
					stream << ".MODULUSOFSUBGRADEREACTIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ACCELERATIONUNIT)
				{
					stream << ".ACCELERATIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_CURVATUREUNIT)
				{
					stream << ".CURVATUREUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_HEATINGVALUEUNIT)
				{
					stream << ".HEATINGVALUEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_IONCONCENTRATIONUNIT)
				{
					stream << ".IONCONCENTRATIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_LUMINOUSINTENSITYDISTRIBUTIONUNIT)
				{
					stream << ".LUMINOUSINTENSITYDISTRIBUTIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MASSPERLENGTHUNIT)
				{
					stream << ".MASSPERLENGTHUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MODULUSOFLINEARSUBGRADEREACTIONUNIT)
				{
					stream << ".MODULUSOFLINEARSUBGRADEREACTIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_MODULUSOFROTATIONALSUBGRADEREACTIONUNIT)
				{
					stream << ".MODULUSOFROTATIONALSUBGRADEREACTIONUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_PHUNIT)
				{
					stream << ".PHUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_ROTATIONALMASSUNIT)
				{
					stream << ".ROTATIONALMASSUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SECTIONAREAINTEGRALUNIT)
				{
					stream << ".SECTIONAREAINTEGRALUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SECTIONMODULUSUNIT)
				{
					stream << ".SECTIONMODULUSUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SOUNDPOWERLEVELUNIT)
				{
					stream << ".SOUNDPOWERLEVELUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SOUNDPOWERUNIT)
				{
					stream << ".SOUNDPOWERUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SOUNDPRESSURELEVELUNIT)
				{
					stream << ".SOUNDPRESSURELEVELUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_SOUNDPRESSUREUNIT)
				{
					stream << ".SOUNDPRESSUREUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_TEMPERATUREGRADIENTUNIT)
				{
					stream << ".TEMPERATUREGRADIENTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_TEMPERATURERATEOFCHANGEUNIT)
				{
					stream << ".TEMPERATURERATEOFCHANGEUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_THERMALEXPANSIONCOEFFICIENTUNIT)
				{
					stream << ".THERMALEXPANSIONCOEFFICIENTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_WARPINGCONSTANTUNIT)
				{
					stream << ".WARPINGCONSTANTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_WARPINGMOMENTUNIT)
				{
					stream << ".WARPINGMOMENTUNIT.";
				}
				else if ( m_enum == IfcDerivedUnitEnumEnum::ENUM_USERDEFINED)
				{
					stream << ".USERDEFINED.";
				}
				if (is_select_type) { stream << ")"; }
			}
			std::shared_ptr<IfcDerivedUnitEnum> IfcDerivedUnitEnum::readStepData(const std::string& arg)
			{
				if( arg.compare( "$" ) == 0 ) { return std::shared_ptr<IfcDerivedUnitEnum>(); }
				std::shared_ptr<IfcDerivedUnitEnum> type_object(new IfcDerivedUnitEnum() );
				if ( _stricmp( arg.c_str(), ".ANGULARVELOCITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ANGULARVELOCITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".AREADENSITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_AREADENSITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".COMPOUNDPLANEANGLEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_COMPOUNDPLANEANGLEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".DYNAMICVISCOSITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_DYNAMICVISCOSITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".HEATFLUXDENSITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_HEATFLUXDENSITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".INTEGERCOUNTRATEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_INTEGERCOUNTRATEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".ISOTHERMALMOISTURECAPACITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ISOTHERMALMOISTURECAPACITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".KINEMATICVISCOSITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_KINEMATICVISCOSITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".LINEARVELOCITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_LINEARVELOCITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MASSDENSITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MASSDENSITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MASSFLOWRATEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MASSFLOWRATEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MOISTUREDIFFUSIVITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MOISTUREDIFFUSIVITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MOLECULARWEIGHTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MOLECULARWEIGHTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SPECIFICHEATCAPACITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SPECIFICHEATCAPACITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMALADMITTANCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_THERMALADMITTANCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMALCONDUCTANCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_THERMALCONDUCTANCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMALRESISTANCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_THERMALRESISTANCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMALTRANSMITTANCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_THERMALTRANSMITTANCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".VAPORPERMEABILITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_VAPORPERMEABILITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".VOLUMETRICFLOWRATEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_VOLUMETRICFLOWRATEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".ROTATIONALFREQUENCYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ROTATIONALFREQUENCYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".TORQUEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_TORQUEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MOMENTOFINERTIAUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MOMENTOFINERTIAUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".LINEARMOMENTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_LINEARMOMENTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".LINEARFORCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_LINEARFORCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".PLANARFORCEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_PLANARFORCEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MODULUSOFELASTICITYUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MODULUSOFELASTICITYUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SHEARMODULUSUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SHEARMODULUSUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".LINEARSTIFFNESSUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_LINEARSTIFFNESSUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".ROTATIONALSTIFFNESSUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ROTATIONALSTIFFNESSUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MODULUSOFSUBGRADEREACTIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MODULUSOFSUBGRADEREACTIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".ACCELERATIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ACCELERATIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".CURVATUREUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_CURVATUREUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".HEATINGVALUEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_HEATINGVALUEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".IONCONCENTRATIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_IONCONCENTRATIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".LUMINOUSINTENSITYDISTRIBUTIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_LUMINOUSINTENSITYDISTRIBUTIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MASSPERLENGTHUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MASSPERLENGTHUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MODULUSOFLINEARSUBGRADEREACTIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MODULUSOFLINEARSUBGRADEREACTIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".MODULUSOFROTATIONALSUBGRADEREACTIONUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_MODULUSOFROTATIONALSUBGRADEREACTIONUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".PHUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_PHUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".ROTATIONALMASSUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_ROTATIONALMASSUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SECTIONAREAINTEGRALUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SECTIONAREAINTEGRALUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SECTIONMODULUSUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SECTIONMODULUSUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SOUNDPOWERLEVELUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SOUNDPOWERLEVELUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SOUNDPOWERUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SOUNDPOWERUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SOUNDPRESSURELEVELUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SOUNDPRESSURELEVELUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".SOUNDPRESSUREUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_SOUNDPRESSUREUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".TEMPERATUREGRADIENTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_TEMPERATUREGRADIENTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".TEMPERATURERATEOFCHANGEUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_TEMPERATURERATEOFCHANGEUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".THERMALEXPANSIONCOEFFICIENTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_THERMALEXPANSIONCOEFFICIENTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".WARPINGCONSTANTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_WARPINGCONSTANTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".WARPINGMOMENTUNIT.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_WARPINGMOMENTUNIT;
				}
				else if ( _stricmp( arg.c_str(), ".USERDEFINED.") == 0)
				{
					type_object->m_enum = IfcDerivedUnitEnum::IfcDerivedUnitEnumEnum::ENUM_USERDEFINED;
				}
				return type_object;
			}
	} // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
