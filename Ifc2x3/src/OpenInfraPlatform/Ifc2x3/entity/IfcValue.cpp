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

#include <map>
#include "../model/shared_ptr.h"
#include "../model/Ifc2x3Exception.h"
#include "reader/ReaderUtil.h"
#include "include/IfcMeasureValue.h"
#include "include/IfcVolumeMeasure.h"
#include "include/IfcTimeMeasure.h"
#include "include/IfcThermodynamicTemperatureMeasure.h"
#include "include/IfcSolidAngleMeasure.h"
#include "include/IfcPositiveRatioMeasure.h"
#include "include/IfcRatioMeasure.h"
#include "include/IfcPositivePlaneAngleMeasure.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcParameterValue.h"
#include "include/IfcNumericMeasure.h"
#include "include/IfcMassMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcElectricCurrentMeasure.h"
#include "include/IfcDescriptiveMeasure.h"
#include "include/IfcCountMeasure.h"
#include "include/IfcContextDependentMeasure.h"
#include "include/IfcAreaMeasure.h"
#include "include/IfcAmountOfSubstanceMeasure.h"
#include "include/IfcLuminousIntensityMeasure.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcComplexNumber.h"
#include "include/IfcSimpleValue.h"
#include "include/IfcInteger.h"
#include "include/IfcReal.h"
#include "include/IfcBoolean.h"
#include "include/IfcIdentifier.h"
#include "include/IfcText.h"
#include "include/IfcLabel.h"
#include "include/IfcLogical.h"
#include "include/IfcDerivedMeasureValue.h"
#include "include/IfcVolumetricFlowRateMeasure.h"
#include "include/IfcTimeStamp.h"
#include "include/IfcThermalTransmittanceMeasure.h"
#include "include/IfcThermalResistanceMeasure.h"
#include "include/IfcThermalAdmittanceMeasure.h"
#include "include/IfcPressureMeasure.h"
#include "include/IfcPowerMeasure.h"
#include "include/IfcMassFlowRateMeasure.h"
#include "include/IfcMassDensityMeasure.h"
#include "include/IfcLinearVelocityMeasure.h"
#include "include/IfcKinematicViscosityMeasure.h"
#include "include/IfcIntegerCountRateMeasure.h"
#include "include/IfcHeatFluxDensityMeasure.h"
#include "include/IfcFrequencyMeasure.h"
#include "include/IfcEnergyMeasure.h"
#include "include/IfcElectricVoltageMeasure.h"
#include "include/IfcDynamicViscosityMeasure.h"
#include "include/IfcCompoundPlaneAngleMeasure.h"
#include "include/IfcAngularVelocityMeasure.h"
#include "include/IfcThermalConductivityMeasure.h"
#include "include/IfcMolecularWeightMeasure.h"
#include "include/IfcVaporPermeabilityMeasure.h"
#include "include/IfcMoistureDiffusivityMeasure.h"
#include "include/IfcIsothermalMoistureCapacityMeasure.h"
#include "include/IfcSpecificHeatCapacityMeasure.h"
#include "include/IfcMonetaryMeasure.h"
#include "include/IfcMagneticFluxDensityMeasure.h"
#include "include/IfcMagneticFluxMeasure.h"
#include "include/IfcLuminousFluxMeasure.h"
#include "include/IfcForceMeasure.h"
#include "include/IfcInductanceMeasure.h"
#include "include/IfcIlluminanceMeasure.h"
#include "include/IfcElectricResistanceMeasure.h"
#include "include/IfcElectricConductanceMeasure.h"
#include "include/IfcElectricChargeMeasure.h"
#include "include/IfcDoseEquivalentMeasure.h"
#include "include/IfcElectricCapacitanceMeasure.h"
#include "include/IfcAbsorbedDoseMeasure.h"
#include "include/IfcRadioActivityMeasure.h"
#include "include/IfcRotationalFrequencyMeasure.h"
#include "include/IfcTorqueMeasure.h"
#include "include/IfcAccelerationMeasure.h"
#include "include/IfcLinearForceMeasure.h"
#include "include/IfcLinearStiffnessMeasure.h"
#include "include/IfcModulusOfSubgradeReactionMeasure.h"
#include "include/IfcModulusOfElasticityMeasure.h"
#include "include/IfcMomentOfInertiaMeasure.h"
#include "include/IfcPlanarForceMeasure.h"
#include "include/IfcRotationalStiffnessMeasure.h"
#include "include/IfcShearModulusMeasure.h"
#include "include/IfcLinearMomentMeasure.h"
#include "include/IfcLuminousIntensityDistributionMeasure.h"
#include "include/IfcCurvatureMeasure.h"
#include "include/IfcMassPerLengthMeasure.h"
#include "include/IfcModulusOfLinearSubgradeReactionMeasure.h"
#include "include/IfcModulusOfRotationalSubgradeReactionMeasure.h"
#include "include/IfcRotationalMassMeasure.h"
#include "include/IfcSectionalAreaIntegralMeasure.h"
#include "include/IfcSectionModulusMeasure.h"
#include "include/IfcTemperatureGradientMeasure.h"
#include "include/IfcThermalExpansionCoefficientMeasure.h"
#include "include/IfcWarpingConstantMeasure.h"
#include "include/IfcWarpingMomentMeasure.h"
#include "include/IfcSoundPowerMeasure.h"
#include "include/IfcSoundPressureMeasure.h"
#include "include/IfcHeatingValueMeasure.h"
#include "include/IfcPHMeasure.h"
#include "include/IfcIonConcentrationMeasure.h"
#include "include/IfcValue.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		// TYPE IfcValue 
		IfcValue::IfcValue() {}
		IfcValue::~IfcValue() {}
		shared_ptr<IfcValue> IfcValue::readStepData( std::string& arg, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
		{
			// Read SELECT TYPE
			if( arg.size() == 0 ){ return shared_ptr<IfcValue>(); }
			if( arg[0] == '#' )
			{
				int id=atoi( arg.substr(1,arg.length()-1).c_str() );
				std::map<int,shared_ptr<Ifc2x3Entity> >::const_iterator it_entity = map.find( id );
				if( it_entity != map.end() )
				{
					shared_ptr<IfcValue> type_object = dynamic_pointer_cast<IfcValue>(it_entity->second);
					return type_object;
				}
				else
				{
					std::stringstream strs;
					strs << "Object width id " << id << " not found";
					throw Ifc2x3Exception( strs.str() );
				}
			}
			else if( arg.compare("$")==0 )
			{
				return shared_ptr<IfcValue>();
			}
			else if( arg.compare("*")==0 )
			{
				return shared_ptr<IfcValue>();
			}
			else
			{
				// inline arguments
				std::string keyword;
				std::string inline_arg;
				tokenizeInlineArgument( arg, keyword, inline_arg );
				if( keyword.compare("IFCMEASUREVALUE")== 0 )
				{
					return IfcMeasureValue::readStepData( inline_arg, map );
				}
				else if( keyword.compare("IFCVOLUMEMEASURE")== 0 )
				{
					return IfcVolumeMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTIMEMEASURE")== 0 )
				{
					return IfcTimeMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMODYNAMICTEMPERATUREMEASURE")== 0 )
				{
					return IfcThermodynamicTemperatureMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSOLIDANGLEMEASURE")== 0 )
				{
					return IfcSolidAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVERATIOMEASURE")== 0 )
				{
					return IfcPositiveRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCRATIOMEASURE")== 0 )
				{
					return IfcRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVEPLANEANGLEMEASURE")== 0 )
				{
					return IfcPositivePlaneAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPLANEANGLEMEASURE")== 0 )
				{
					return IfcPlaneAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPARAMETERVALUE")== 0 )
				{
					return IfcParameterValue::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCNUMERICMEASURE")== 0 )
				{
					return IfcNumericMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMASSMEASURE")== 0 )
				{
					return IfcMassMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOSITIVELENGTHMEASURE")== 0 )
				{
					return IfcPositiveLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLENGTHMEASURE")== 0 )
				{
					return IfcLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICCURRENTMEASURE")== 0 )
				{
					return IfcElectricCurrentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCDESCRIPTIVEMEASURE")== 0 )
				{
					return IfcDescriptiveMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCOUNTMEASURE")== 0 )
				{
					return IfcCountMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCONTEXTDEPENDENTMEASURE")== 0 )
				{
					return IfcContextDependentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCAREAMEASURE")== 0 )
				{
					return IfcAreaMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCAMOUNTOFSUBSTANCEMEASURE")== 0 )
				{
					return IfcAmountOfSubstanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLUMINOUSINTENSITYMEASURE")== 0 )
				{
					return IfcLuminousIntensityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCNORMALISEDRATIOMEASURE")== 0 )
				{
					return IfcNormalisedRatioMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCOMPLEXNUMBER")== 0 )
				{
					return IfcComplexNumber::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSIMPLEVALUE")== 0 )
				{
					return IfcSimpleValue::readStepData( inline_arg, map );
				}
				else if( keyword.compare("IFCINTEGER")== 0 )
				{
					return IfcInteger::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCREAL")== 0 )
				{
					return IfcReal::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCBOOLEAN")== 0 )
				{
					return IfcBoolean::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCIDENTIFIER")== 0 )
				{
					return IfcIdentifier::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTEXT")== 0 )
				{
					return IfcText::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLABEL")== 0 )
				{
					return IfcLabel::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLOGICAL")== 0 )
				{
					return IfcLogical::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCDERIVEDMEASUREVALUE")== 0 )
				{
					return IfcDerivedMeasureValue::readStepData( inline_arg, map );
				}
				else if( keyword.compare("IFCVOLUMETRICFLOWRATEMEASURE")== 0 )
				{
					return IfcVolumetricFlowRateMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTIMESTAMP")== 0 )
				{
					return IfcTimeStamp::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMALTRANSMITTANCEMEASURE")== 0 )
				{
					return IfcThermalTransmittanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMALRESISTANCEMEASURE")== 0 )
				{
					return IfcThermalResistanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMALADMITTANCEMEASURE")== 0 )
				{
					return IfcThermalAdmittanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPRESSUREMEASURE")== 0 )
				{
					return IfcPressureMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPOWERMEASURE")== 0 )
				{
					return IfcPowerMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMASSFLOWRATEMEASURE")== 0 )
				{
					return IfcMassFlowRateMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMASSDENSITYMEASURE")== 0 )
				{
					return IfcMassDensityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLINEARVELOCITYMEASURE")== 0 )
				{
					return IfcLinearVelocityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCKINEMATICVISCOSITYMEASURE")== 0 )
				{
					return IfcKinematicViscosityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCINTEGERCOUNTRATEMEASURE")== 0 )
				{
					return IfcIntegerCountRateMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCHEATFLUXDENSITYMEASURE")== 0 )
				{
					return IfcHeatFluxDensityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCFREQUENCYMEASURE")== 0 )
				{
					return IfcFrequencyMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCENERGYMEASURE")== 0 )
				{
					return IfcEnergyMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICVOLTAGEMEASURE")== 0 )
				{
					return IfcElectricVoltageMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCDYNAMICVISCOSITYMEASURE")== 0 )
				{
					return IfcDynamicViscosityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCOMPOUNDPLANEANGLEMEASURE")== 0 )
				{
					return IfcCompoundPlaneAngleMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCANGULARVELOCITYMEASURE")== 0 )
				{
					return IfcAngularVelocityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMALCONDUCTIVITYMEASURE")== 0 )
				{
					return IfcThermalConductivityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMOLECULARWEIGHTMEASURE")== 0 )
				{
					return IfcMolecularWeightMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCVAPORPERMEABILITYMEASURE")== 0 )
				{
					return IfcVaporPermeabilityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMOISTUREDIFFUSIVITYMEASURE")== 0 )
				{
					return IfcMoistureDiffusivityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCISOTHERMALMOISTURECAPACITYMEASURE")== 0 )
				{
					return IfcIsothermalMoistureCapacityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSPECIFICHEATCAPACITYMEASURE")== 0 )
				{
					return IfcSpecificHeatCapacityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMONETARYMEASURE")== 0 )
				{
					return IfcMonetaryMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMAGNETICFLUXDENSITYMEASURE")== 0 )
				{
					return IfcMagneticFluxDensityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMAGNETICFLUXMEASURE")== 0 )
				{
					return IfcMagneticFluxMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLUMINOUSFLUXMEASURE")== 0 )
				{
					return IfcLuminousFluxMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCFORCEMEASURE")== 0 )
				{
					return IfcForceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCINDUCTANCEMEASURE")== 0 )
				{
					return IfcInductanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCILLUMINANCEMEASURE")== 0 )
				{
					return IfcIlluminanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICRESISTANCEMEASURE")== 0 )
				{
					return IfcElectricResistanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICCONDUCTANCEMEASURE")== 0 )
				{
					return IfcElectricConductanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICCHARGEMEASURE")== 0 )
				{
					return IfcElectricChargeMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCDOSEEQUIVALENTMEASURE")== 0 )
				{
					return IfcDoseEquivalentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCELECTRICCAPACITANCEMEASURE")== 0 )
				{
					return IfcElectricCapacitanceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCABSORBEDDOSEMEASURE")== 0 )
				{
					return IfcAbsorbedDoseMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCRADIOACTIVITYMEASURE")== 0 )
				{
					return IfcRadioActivityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCROTATIONALFREQUENCYMEASURE")== 0 )
				{
					return IfcRotationalFrequencyMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTORQUEMEASURE")== 0 )
				{
					return IfcTorqueMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCACCELERATIONMEASURE")== 0 )
				{
					return IfcAccelerationMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLINEARFORCEMEASURE")== 0 )
				{
					return IfcLinearForceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLINEARSTIFFNESSMEASURE")== 0 )
				{
					return IfcLinearStiffnessMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMODULUSOFSUBGRADEREACTIONMEASURE")== 0 )
				{
					return IfcModulusOfSubgradeReactionMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMODULUSOFELASTICITYMEASURE")== 0 )
				{
					return IfcModulusOfElasticityMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMOMENTOFINERTIAMEASURE")== 0 )
				{
					return IfcMomentOfInertiaMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPLANARFORCEMEASURE")== 0 )
				{
					return IfcPlanarForceMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCROTATIONALSTIFFNESSMEASURE")== 0 )
				{
					return IfcRotationalStiffnessMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSHEARMODULUSMEASURE")== 0 )
				{
					return IfcShearModulusMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLINEARMOMENTMEASURE")== 0 )
				{
					return IfcLinearMomentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCLUMINOUSINTENSITYDISTRIBUTIONMEASURE")== 0 )
				{
					return IfcLuminousIntensityDistributionMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCCURVATUREMEASURE")== 0 )
				{
					return IfcCurvatureMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMASSPERLENGTHMEASURE")== 0 )
				{
					return IfcMassPerLengthMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMODULUSOFLINEARSUBGRADEREACTIONMEASURE")== 0 )
				{
					return IfcModulusOfLinearSubgradeReactionMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCMODULUSOFROTATIONALSUBGRADEREACTIONMEASURE")== 0 )
				{
					return IfcModulusOfRotationalSubgradeReactionMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCROTATIONALMASSMEASURE")== 0 )
				{
					return IfcRotationalMassMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSECTIONALAREAINTEGRALMEASURE")== 0 )
				{
					return IfcSectionalAreaIntegralMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSECTIONMODULUSMEASURE")== 0 )
				{
					return IfcSectionModulusMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTEMPERATUREGRADIENTMEASURE")== 0 )
				{
					return IfcTemperatureGradientMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCTHERMALEXPANSIONCOEFFICIENTMEASURE")== 0 )
				{
					return IfcThermalExpansionCoefficientMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCWARPINGCONSTANTMEASURE")== 0 )
				{
					return IfcWarpingConstantMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCWARPINGMOMENTMEASURE")== 0 )
				{
					return IfcWarpingMomentMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSOUNDPOWERMEASURE")== 0 )
				{
					return IfcSoundPowerMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCSOUNDPRESSUREMEASURE")== 0 )
				{
					return IfcSoundPressureMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCHEATINGVALUEMEASURE")== 0 )
				{
					return IfcHeatingValueMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCPHMEASURE")== 0 )
				{
					return IfcPHMeasure::readStepData( inline_arg );
				}
				else if( keyword.compare("IFCIONCONCENTRATIONMEASURE")== 0 )
				{
					return IfcIonConcentrationMeasure::readStepData( inline_arg );
				}
				std::stringstream strs;
				strs << "unhandled inline argument: " << arg << " in function IFC2X3::IfcValue::readStepData" << std::endl;
				throw Ifc2x3Exception( strs.str() );
			}
			return shared_ptr<IfcValue>();
		}
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform
