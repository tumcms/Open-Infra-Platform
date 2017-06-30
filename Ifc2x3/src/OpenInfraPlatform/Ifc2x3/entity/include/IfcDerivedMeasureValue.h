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

#include <iostream>
#include <sstream>
#include <map>
#include "../../model/shared_ptr.h"
#include "../../model/Ifc2x3Object.h"
#include "IfcValue.h"

// TYPE IfcDerivedMeasureValue = SELECT	(IfcVolumetricFlowRateMeasure	,IfcTimeStamp	,IfcThermalTransmittanceMeasure	,IfcThermalResistanceMeasure	,IfcThermalAdmittanceMeasure	,IfcPressureMeasure	,IfcPowerMeasure	,IfcMassFlowRateMeasure	,IfcMassDensityMeasure	,IfcLinearVelocityMeasure	,IfcKinematicViscosityMeasure	,IfcIntegerCountRateMeasure	,IfcHeatFluxDensityMeasure	,IfcFrequencyMeasure	,IfcEnergyMeasure	,IfcElectricVoltageMeasure	,IfcDynamicViscosityMeasure	,IfcCompoundPlaneAngleMeasure	,IfcAngularVelocityMeasure	,IfcThermalConductivityMeasure	,IfcMolecularWeightMeasure	,IfcVaporPermeabilityMeasure	,IfcMoistureDiffusivityMeasure	,IfcIsothermalMoistureCapacityMeasure	,IfcSpecificHeatCapacityMeasure	,IfcMonetaryMeasure	,IfcMagneticFluxDensityMeasure	,IfcMagneticFluxMeasure	,IfcLuminousFluxMeasure	,IfcForceMeasure	,IfcInductanceMeasure	,IfcIlluminanceMeasure	,IfcElectricResistanceMeasure	,IfcElectricConductanceMeasure	,IfcElectricChargeMeasure	,IfcDoseEquivalentMeasure	,IfcElectricCapacitanceMeasure	,IfcAbsorbedDoseMeasure	,IfcRadioActivityMeasure	,IfcRotationalFrequencyMeasure	,IfcTorqueMeasure	,IfcAccelerationMeasure	,IfcLinearForceMeasure	,IfcLinearStiffnessMeasure	,IfcModulusOfSubgradeReactionMeasure	,IfcModulusOfElasticityMeasure	,IfcMomentOfInertiaMeasure	,IfcPlanarForceMeasure	,IfcRotationalStiffnessMeasure	,IfcShearModulusMeasure	,IfcLinearMomentMeasure	,IfcLuminousIntensityDistributionMeasure	,IfcCurvatureMeasure	,IfcMassPerLengthMeasure	,IfcModulusOfLinearSubgradeReactionMeasure	,IfcModulusOfRotationalSubgradeReactionMeasure	,IfcRotationalMassMeasure	,IfcSectionalAreaIntegralMeasure	,IfcSectionModulusMeasure	,IfcTemperatureGradientMeasure	,IfcThermalExpansionCoefficientMeasure	,IfcWarpingConstantMeasure	,IfcWarpingMomentMeasure	,IfcSoundPowerMeasure	,IfcSoundPressureMeasure	,IfcHeatingValueMeasure	,IfcPHMeasure	,IfcIonConcentrationMeasure);
namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		class IfcDerivedMeasureValue : public IfcValue
		{
		public:
			IfcDerivedMeasureValue();
			~IfcDerivedMeasureValue();
			virtual const char* classname() const { return "IfcDerivedMeasureValue"; }
			virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const = 0; // abstract class
			static shared_ptr<IfcDerivedMeasureValue> readStepData( std::string& arg, const std::map<int,shared_ptr<Ifc2x3Entity> >& map );
		};
	} // end namespace Ifc2x3
} // end namespace OpenInfraPlatform

