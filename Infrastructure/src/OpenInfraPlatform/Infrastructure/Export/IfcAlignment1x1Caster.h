/*
	Copyright (c) 2018 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	TUM Open Infra Platform is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <memory>
#include <typeinfo>
#include <OpenInfraPlatform\IfcAlignment1x1\IfcAlignment1x1Entities.h>
#include <OpenInfraPlatform\IfcAlignment1x1\IfcAlignment1x1Types.h>

namespace OpenInfraPlatform {
	namespace IfcAlignment1x1 {
		template <typename F> bool castAndCall(std::shared_ptr<IfcAlignment1x1Entity> &ptr, F &f)
		{
			std::string name = std::string(typeid(*ptr).name());

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAbsorbedDoseMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAbsorbedDoseMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAccelerationMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAccelerationMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionRequest") {
				f(*(std::dynamic_pointer_cast<IfcActionRequest>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionRequestTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcActionRequestTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionSourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcActionSourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcActionTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActor") {
				f(*(std::dynamic_pointer_cast<IfcActor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActorRole") {
				f(*(std::dynamic_pointer_cast<IfcActorRole>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActorSelect") {
				f(*(std::dynamic_pointer_cast<IfcActorSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuator") {
				f(*(std::dynamic_pointer_cast<IfcActuator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuatorType") {
				f(*(std::dynamic_pointer_cast<IfcActuatorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuatorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcActuatorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAddress") {
				f(*(std::dynamic_pointer_cast<IfcAddress>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAddressTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAddressTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedBrep") {
				f(*(std::dynamic_pointer_cast<IfcAdvancedBrep>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedBrepWithVoids") {
				f(*(std::dynamic_pointer_cast<IfcAdvancedBrepWithVoids>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedFace") {
				f(*(std::dynamic_pointer_cast<IfcAdvancedFace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminal") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBox") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminalBox>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBoxType") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminalBoxType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBoxTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminalBoxTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAirTerminalTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecovery") {
				f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecovery>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecoveryType") {
				f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecoveryType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecoveryTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecoveryTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarm") {
				f(*(std::dynamic_pointer_cast<IfcAlarm>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarmType") {
				f(*(std::dynamic_pointer_cast<IfcAlarmType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarmTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAlarmTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment") {
				f(*(std::dynamic_pointer_cast<IfcAlignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DHorizontal") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DHorizontalSegment") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontalSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DSegment") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegCircularArc") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegCircularArc>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegLine") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegLine>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegParabolicArc") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegParabolicArc>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVertical") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DVertical>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerticalSegment") {
				f(*(std::dynamic_pointer_cast<IfcAlignment2DVerticalSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve") {
				f(*(std::dynamic_pointer_cast<IfcAlignmentCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAlignmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAmountOfSubstanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAmountOfSubstanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnalysisModelTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAnalysisModelTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnalysisTheoryTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAnalysisTheoryTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAngularVelocityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAngularVelocityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnnotation") {
				f(*(std::dynamic_pointer_cast<IfcAnnotation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnnotationFillArea") {
				f(*(std::dynamic_pointer_cast<IfcAnnotationFillArea>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApplication") {
				f(*(std::dynamic_pointer_cast<IfcApplication>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAppliedValue") {
				f(*(std::dynamic_pointer_cast<IfcAppliedValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAppliedValueSelect") {
				f(*(std::dynamic_pointer_cast<IfcAppliedValueSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApproval") {
				f(*(std::dynamic_pointer_cast<IfcApproval>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApprovalRelationship") {
				f(*(std::dynamic_pointer_cast<IfcApprovalRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryClosedProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcArbitraryClosedProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryOpenProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcArbitraryOpenProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryProfileDefWithVoids") {
				f(*(std::dynamic_pointer_cast<IfcArbitraryProfileDefWithVoids>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArcIndex") {
				f(*(std::dynamic_pointer_cast<IfcArcIndex>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAreaDensityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAreaDensityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAreaMeasure") {
				f(*(std::dynamic_pointer_cast<IfcAreaMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArithmeticOperatorEnum") {
				f(*(std::dynamic_pointer_cast<IfcArithmeticOperatorEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAssemblyPlaceEnum") {
				f(*(std::dynamic_pointer_cast<IfcAssemblyPlaceEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAsset") {
				f(*(std::dynamic_pointer_cast<IfcAsset>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAsymmetricIShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcAsymmetricIShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualAppliance") {
				f(*(std::dynamic_pointer_cast<IfcAudioVisualAppliance>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualApplianceType") {
				f(*(std::dynamic_pointer_cast<IfcAudioVisualApplianceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualApplianceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcAudioVisualApplianceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis1Placement") {
				f(*(std::dynamic_pointer_cast<IfcAxis1Placement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement") {
				f(*(std::dynamic_pointer_cast<IfcAxis2Placement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement2D") {
				f(*(std::dynamic_pointer_cast<IfcAxis2Placement2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement3D") {
				f(*(std::dynamic_pointer_cast<IfcAxis2Placement3D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeam") {
				f(*(std::dynamic_pointer_cast<IfcBeam>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcBeamStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamType") {
				f(*(std::dynamic_pointer_cast<IfcBeamType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBeamTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBenchmarkEnum") {
				f(*(std::dynamic_pointer_cast<IfcBenchmarkEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBendingParameterSelect") {
				f(*(std::dynamic_pointer_cast<IfcBendingParameterSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBinary") {
				f(*(std::dynamic_pointer_cast<IfcBinary>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBlobTexture") {
				f(*(std::dynamic_pointer_cast<IfcBlobTexture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBlock") {
				f(*(std::dynamic_pointer_cast<IfcBlock>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoiler") {
				f(*(std::dynamic_pointer_cast<IfcBoiler>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoilerType") {
				f(*(std::dynamic_pointer_cast<IfcBoilerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoilerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBoilerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoolean") {
				f(*(std::dynamic_pointer_cast<IfcBoolean>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanClippingResult") {
				f(*(std::dynamic_pointer_cast<IfcBooleanClippingResult>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanOperand") {
				f(*(std::dynamic_pointer_cast<IfcBooleanOperand>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanOperator") {
				f(*(std::dynamic_pointer_cast<IfcBooleanOperator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanResult") {
				f(*(std::dynamic_pointer_cast<IfcBooleanResult>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryCondition") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryCurve") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryEdgeCondition") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryEdgeCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryFaceCondition") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryFaceCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryNodeCondition") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryNodeCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryNodeConditionWarping") {
				f(*(std::dynamic_pointer_cast<IfcBoundaryNodeConditionWarping>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundedCurve") {
				f(*(std::dynamic_pointer_cast<IfcBoundedCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundedSurface") {
				f(*(std::dynamic_pointer_cast<IfcBoundedSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundingBox") {
				f(*(std::dynamic_pointer_cast<IfcBoundingBox>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoxAlignment") {
				f(*(std::dynamic_pointer_cast<IfcBoxAlignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoxedHalfSpace") {
				f(*(std::dynamic_pointer_cast<IfcBoxedHalfSpace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurve") {
				f(*(std::dynamic_pointer_cast<IfcBSplineCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurveForm") {
				f(*(std::dynamic_pointer_cast<IfcBSplineCurveForm>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurveWithKnots") {
				f(*(std::dynamic_pointer_cast<IfcBSplineCurveWithKnots>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurface") {
				f(*(std::dynamic_pointer_cast<IfcBSplineSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurfaceForm") {
				f(*(std::dynamic_pointer_cast<IfcBSplineSurfaceForm>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurfaceWithKnots") {
				f(*(std::dynamic_pointer_cast<IfcBSplineSurfaceWithKnots>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuilding") {
				f(*(std::dynamic_pointer_cast<IfcBuilding>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElement") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPart") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementPart>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPartType") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementPartType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPartTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementPartTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxy") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementProxy>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxyType") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementProxyType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxyTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementProxyTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementType") {
				f(*(std::dynamic_pointer_cast<IfcBuildingElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingStorey") {
				f(*(std::dynamic_pointer_cast<IfcBuildingStorey>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingSystem") {
				f(*(std::dynamic_pointer_cast<IfcBuildingSystem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingSystemTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBuildingSystemTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurner") {
				f(*(std::dynamic_pointer_cast<IfcBurner>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurnerType") {
				f(*(std::dynamic_pointer_cast<IfcBurnerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurnerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcBurnerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFitting") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierFitting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFittingType") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierFittingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFittingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierFittingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegment") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegmentType") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierSegmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCableCarrierSegmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFitting") {
				f(*(std::dynamic_pointer_cast<IfcCableFitting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFittingType") {
				f(*(std::dynamic_pointer_cast<IfcCableFittingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFittingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCableFittingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegment") {
				f(*(std::dynamic_pointer_cast<IfcCableSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegmentType") {
				f(*(std::dynamic_pointer_cast<IfcCableSegmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCableSegmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCardinalPointReference") {
				f(*(std::dynamic_pointer_cast<IfcCardinalPointReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPoint") {
				f(*(std::dynamic_pointer_cast<IfcCartesianPoint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList") {
				f(*(std::dynamic_pointer_cast<IfcCartesianPointList>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList2D") {
				f(*(std::dynamic_pointer_cast<IfcCartesianPointList2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList2DLabelled") {
				f(*(std::dynamic_pointer_cast<IfcCartesianPointList2DLabelled>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList3D") {
				f(*(std::dynamic_pointer_cast<IfcCartesianPointList3D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator") {
				f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2D") {
				f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2DnonUniform") {
				f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2DnonUniform>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator3D") {
				f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator3DnonUniform") {
				f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3DnonUniform>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCenterLineProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcCenterLineProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChangeActionEnum") {
				f(*(std::dynamic_pointer_cast<IfcChangeActionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChiller") {
				f(*(std::dynamic_pointer_cast<IfcChiller>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChillerType") {
				f(*(std::dynamic_pointer_cast<IfcChillerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChillerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcChillerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimney") {
				f(*(std::dynamic_pointer_cast<IfcChimney>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimneyType") {
				f(*(std::dynamic_pointer_cast<IfcChimneyType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimneyTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcChimneyTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircle") {
				f(*(std::dynamic_pointer_cast<IfcCircle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircleHollowProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcCircleHollowProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircleProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcCircleProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircularArcSegment2D") {
				f(*(std::dynamic_pointer_cast<IfcCircularArcSegment2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCivilElement") {
				f(*(std::dynamic_pointer_cast<IfcCivilElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCivilElementType") {
				f(*(std::dynamic_pointer_cast<IfcCivilElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassification") {
				f(*(std::dynamic_pointer_cast<IfcClassification>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassificationReference") {
				f(*(std::dynamic_pointer_cast<IfcClassificationReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassificationReferenceSelect") {
				f(*(std::dynamic_pointer_cast<IfcClassificationReferenceSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassificationSelect") {
				f(*(std::dynamic_pointer_cast<IfcClassificationSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClosedShell") {
				f(*(std::dynamic_pointer_cast<IfcClosedShell>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClothoidalArcSegment2D") {
				f(*(std::dynamic_pointer_cast<IfcClothoidalArcSegment2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoil") {
				f(*(std::dynamic_pointer_cast<IfcCoil>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoilType") {
				f(*(std::dynamic_pointer_cast<IfcCoilType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoilTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCoilTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColour") {
				f(*(std::dynamic_pointer_cast<IfcColour>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourOrFactor") {
				f(*(std::dynamic_pointer_cast<IfcColourOrFactor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourRgb") {
				f(*(std::dynamic_pointer_cast<IfcColourRgb>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourRgbList") {
				f(*(std::dynamic_pointer_cast<IfcColourRgbList>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourSpecification") {
				f(*(std::dynamic_pointer_cast<IfcColourSpecification>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumn") {
				f(*(std::dynamic_pointer_cast<IfcColumn>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcColumnStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnType") {
				f(*(std::dynamic_pointer_cast<IfcColumnType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcColumnTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsAppliance") {
				f(*(std::dynamic_pointer_cast<IfcCommunicationsAppliance>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsApplianceType") {
				f(*(std::dynamic_pointer_cast<IfcCommunicationsApplianceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsApplianceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCommunicationsApplianceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexNumber") {
				f(*(std::dynamic_pointer_cast<IfcComplexNumber>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexProperty") {
				f(*(std::dynamic_pointer_cast<IfcComplexProperty>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexPropertyTemplate") {
				f(*(std::dynamic_pointer_cast<IfcComplexPropertyTemplate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexPropertyTemplateTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcComplexPropertyTemplateTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurve") {
				f(*(std::dynamic_pointer_cast<IfcCompositeCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurveOnSurface") {
				f(*(std::dynamic_pointer_cast<IfcCompositeCurveOnSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurveSegment") {
				f(*(std::dynamic_pointer_cast<IfcCompositeCurveSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcCompositeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompoundPlaneAngleMeasure") {
				f(*(std::dynamic_pointer_cast<IfcCompoundPlaneAngleMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressor") {
				f(*(std::dynamic_pointer_cast<IfcCompressor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressorType") {
				f(*(std::dynamic_pointer_cast<IfcCompressorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCompressorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenser") {
				f(*(std::dynamic_pointer_cast<IfcCondenser>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenserType") {
				f(*(std::dynamic_pointer_cast<IfcCondenserType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenserTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCondenserTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConic") {
				f(*(std::dynamic_pointer_cast<IfcConic>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectedFaceSet") {
				f(*(std::dynamic_pointer_cast<IfcConnectedFaceSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionCurveGeometry") {
				f(*(std::dynamic_pointer_cast<IfcConnectionCurveGeometry>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionGeometry") {
				f(*(std::dynamic_pointer_cast<IfcConnectionGeometry>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionPointEccentricity") {
				f(*(std::dynamic_pointer_cast<IfcConnectionPointEccentricity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionPointGeometry") {
				f(*(std::dynamic_pointer_cast<IfcConnectionPointGeometry>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionSurfaceGeometry") {
				f(*(std::dynamic_pointer_cast<IfcConnectionSurfaceGeometry>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcConnectionTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionVolumeGeometry") {
				f(*(std::dynamic_pointer_cast<IfcConnectionVolumeGeometry>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstraint") {
				f(*(std::dynamic_pointer_cast<IfcConstraint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstraintEnum") {
				f(*(std::dynamic_pointer_cast<IfcConstraintEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResource") {
				f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResourceType") {
				f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResource") {
				f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResourceType") {
				f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResource") {
				f(*(std::dynamic_pointer_cast<IfcConstructionProductResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResourceType") {
				f(*(std::dynamic_pointer_cast<IfcConstructionProductResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcConstructionProductResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionResource") {
				f(*(std::dynamic_pointer_cast<IfcConstructionResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionResourceType") {
				f(*(std::dynamic_pointer_cast<IfcConstructionResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContext") {
				f(*(std::dynamic_pointer_cast<IfcContext>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContextDependentMeasure") {
				f(*(std::dynamic_pointer_cast<IfcContextDependentMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContextDependentUnit") {
				f(*(std::dynamic_pointer_cast<IfcContextDependentUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControl") {
				f(*(std::dynamic_pointer_cast<IfcControl>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcController") {
				f(*(std::dynamic_pointer_cast<IfcController>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControllerType") {
				f(*(std::dynamic_pointer_cast<IfcControllerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControllerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcControllerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConversionBasedUnit") {
				f(*(std::dynamic_pointer_cast<IfcConversionBasedUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConversionBasedUnitWithOffset") {
				f(*(std::dynamic_pointer_cast<IfcConversionBasedUnitWithOffset>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeam") {
				f(*(std::dynamic_pointer_cast<IfcCooledBeam>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeamType") {
				f(*(std::dynamic_pointer_cast<IfcCooledBeamType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeamTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCooledBeamTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTower") {
				f(*(std::dynamic_pointer_cast<IfcCoolingTower>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTowerType") {
				f(*(std::dynamic_pointer_cast<IfcCoolingTowerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTowerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCoolingTowerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoordinateOperation") {
				f(*(std::dynamic_pointer_cast<IfcCoordinateOperation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoordinateReferenceSystem") {
				f(*(std::dynamic_pointer_cast<IfcCoordinateReferenceSystem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoordinateReferenceSystemSelect") {
				f(*(std::dynamic_pointer_cast<IfcCoordinateReferenceSystemSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostItem") {
				f(*(std::dynamic_pointer_cast<IfcCostItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostItemTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCostItemTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostSchedule") {
				f(*(std::dynamic_pointer_cast<IfcCostSchedule>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostScheduleTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCostScheduleTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostValue") {
				f(*(std::dynamic_pointer_cast<IfcCostValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCountMeasure") {
				f(*(std::dynamic_pointer_cast<IfcCountMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCovering") {
				f(*(std::dynamic_pointer_cast<IfcCovering>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoveringType") {
				f(*(std::dynamic_pointer_cast<IfcCoveringType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoveringTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCoveringTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResource") {
				f(*(std::dynamic_pointer_cast<IfcCrewResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResourceType") {
				f(*(std::dynamic_pointer_cast<IfcCrewResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCrewResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCsgPrimitive3D") {
				f(*(std::dynamic_pointer_cast<IfcCsgPrimitive3D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCsgSelect") {
				f(*(std::dynamic_pointer_cast<IfcCsgSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCsgSolid") {
				f(*(std::dynamic_pointer_cast<IfcCsgSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcCShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurrencyRelationship") {
				f(*(std::dynamic_pointer_cast<IfcCurrencyRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWall") {
				f(*(std::dynamic_pointer_cast<IfcCurtainWall>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWallType") {
				f(*(std::dynamic_pointer_cast<IfcCurtainWallType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWallTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcCurtainWallTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurvatureMeasure") {
				f(*(std::dynamic_pointer_cast<IfcCurvatureMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurve") {
				f(*(std::dynamic_pointer_cast<IfcCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveBoundedPlane") {
				f(*(std::dynamic_pointer_cast<IfcCurveBoundedPlane>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveBoundedSurface") {
				f(*(std::dynamic_pointer_cast<IfcCurveBoundedSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveFontOrScaledCurveFontSelect") {
				f(*(std::dynamic_pointer_cast<IfcCurveFontOrScaledCurveFontSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveInterpolationEnum") {
				f(*(std::dynamic_pointer_cast<IfcCurveInterpolationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveOnSurface") {
				f(*(std::dynamic_pointer_cast<IfcCurveOnSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveOrEdgeCurve") {
				f(*(std::dynamic_pointer_cast<IfcCurveOrEdgeCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveSegment2D") {
				f(*(std::dynamic_pointer_cast<IfcCurveSegment2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyle") {
				f(*(std::dynamic_pointer_cast<IfcCurveStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFont") {
				f(*(std::dynamic_pointer_cast<IfcCurveStyleFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFontAndScaling") {
				f(*(std::dynamic_pointer_cast<IfcCurveStyleFontAndScaling>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFontPattern") {
				f(*(std::dynamic_pointer_cast<IfcCurveStyleFontPattern>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFontSelect") {
				f(*(std::dynamic_pointer_cast<IfcCurveStyleFontSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCylindricalSurface") {
				f(*(std::dynamic_pointer_cast<IfcCylindricalSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamper") {
				f(*(std::dynamic_pointer_cast<IfcDamper>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamperType") {
				f(*(std::dynamic_pointer_cast<IfcDamperType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamperTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDamperTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDataOriginEnum") {
				f(*(std::dynamic_pointer_cast<IfcDataOriginEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDate") {
				f(*(std::dynamic_pointer_cast<IfcDate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDateTime") {
				f(*(std::dynamic_pointer_cast<IfcDateTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDayInMonthNumber") {
				f(*(std::dynamic_pointer_cast<IfcDayInMonthNumber>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDayInWeekNumber") {
				f(*(std::dynamic_pointer_cast<IfcDayInWeekNumber>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDefinitionSelect") {
				f(*(std::dynamic_pointer_cast<IfcDefinitionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedMeasureValue") {
				f(*(std::dynamic_pointer_cast<IfcDerivedMeasureValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcDerivedProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnit") {
				f(*(std::dynamic_pointer_cast<IfcDerivedUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnitElement") {
				f(*(std::dynamic_pointer_cast<IfcDerivedUnitElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnitEnum") {
				f(*(std::dynamic_pointer_cast<IfcDerivedUnitEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDescriptiveMeasure") {
				f(*(std::dynamic_pointer_cast<IfcDescriptiveMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDimensionalExponents") {
				f(*(std::dynamic_pointer_cast<IfcDimensionalExponents>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDimensionCount") {
				f(*(std::dynamic_pointer_cast<IfcDimensionCount>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDirection") {
				f(*(std::dynamic_pointer_cast<IfcDirection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDirectionSenseEnum") {
				f(*(std::dynamic_pointer_cast<IfcDirectionSenseEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessory") {
				f(*(std::dynamic_pointer_cast<IfcDiscreteAccessory>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessoryType") {
				f(*(std::dynamic_pointer_cast<IfcDiscreteAccessoryType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessoryTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDiscreteAccessoryTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistanceExpression") {
				f(*(std::dynamic_pointer_cast<IfcDistanceExpression>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElement") {
				f(*(std::dynamic_pointer_cast<IfcDistributionChamberElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElementType") {
				f(*(std::dynamic_pointer_cast<IfcDistributionChamberElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDistributionChamberElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionCircuit") {
				f(*(std::dynamic_pointer_cast<IfcDistributionCircuit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionControlElement") {
				f(*(std::dynamic_pointer_cast<IfcDistributionControlElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionControlElementType") {
				f(*(std::dynamic_pointer_cast<IfcDistributionControlElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionElement") {
				f(*(std::dynamic_pointer_cast<IfcDistributionElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionElementType") {
				f(*(std::dynamic_pointer_cast<IfcDistributionElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionFlowElement") {
				f(*(std::dynamic_pointer_cast<IfcDistributionFlowElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionFlowElementType") {
				f(*(std::dynamic_pointer_cast<IfcDistributionFlowElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionPort") {
				f(*(std::dynamic_pointer_cast<IfcDistributionPort>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionPortTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDistributionPortTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionSystem") {
				f(*(std::dynamic_pointer_cast<IfcDistributionSystem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionSystemEnum") {
				f(*(std::dynamic_pointer_cast<IfcDistributionSystemEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentConfidentialityEnum") {
				f(*(std::dynamic_pointer_cast<IfcDocumentConfidentialityEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentInformation") {
				f(*(std::dynamic_pointer_cast<IfcDocumentInformation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentInformationRelationship") {
				f(*(std::dynamic_pointer_cast<IfcDocumentInformationRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentReference") {
				f(*(std::dynamic_pointer_cast<IfcDocumentReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentSelect") {
				f(*(std::dynamic_pointer_cast<IfcDocumentSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentStatusEnum") {
				f(*(std::dynamic_pointer_cast<IfcDocumentStatusEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoor") {
				f(*(std::dynamic_pointer_cast<IfcDoor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorLiningProperties") {
				f(*(std::dynamic_pointer_cast<IfcDoorLiningProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorPanelOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelPositionEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorPanelPositionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelProperties") {
				f(*(std::dynamic_pointer_cast<IfcDoorPanelProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcDoorStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyle") {
				f(*(std::dynamic_pointer_cast<IfcDoorStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyleConstructionEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorStyleConstructionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyleOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorStyleOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorType") {
				f(*(std::dynamic_pointer_cast<IfcDoorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorTypeOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcDoorTypeOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoseEquivalentMeasure") {
				f(*(std::dynamic_pointer_cast<IfcDoseEquivalentMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDraughtingPreDefinedColour") {
				f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedColour>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDraughtingPreDefinedCurveFont") {
				f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedCurveFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFitting") {
				f(*(std::dynamic_pointer_cast<IfcDuctFitting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFittingType") {
				f(*(std::dynamic_pointer_cast<IfcDuctFittingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFittingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDuctFittingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegment") {
				f(*(std::dynamic_pointer_cast<IfcDuctSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegmentType") {
				f(*(std::dynamic_pointer_cast<IfcDuctSegmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDuctSegmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencer") {
				f(*(std::dynamic_pointer_cast<IfcDuctSilencer>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencerType") {
				f(*(std::dynamic_pointer_cast<IfcDuctSilencerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcDuctSilencerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuration") {
				f(*(std::dynamic_pointer_cast<IfcDuration>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDynamicViscosityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcDynamicViscosityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdge") {
				f(*(std::dynamic_pointer_cast<IfcEdge>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdgeCurve") {
				f(*(std::dynamic_pointer_cast<IfcEdgeCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdgeLoop") {
				f(*(std::dynamic_pointer_cast<IfcEdgeLoop>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricAppliance") {
				f(*(std::dynamic_pointer_cast<IfcElectricAppliance>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricApplianceType") {
				f(*(std::dynamic_pointer_cast<IfcElectricApplianceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricApplianceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricApplianceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricCapacitanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricCapacitanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricChargeMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricChargeMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricConductanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricConductanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricCurrentMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricCurrentMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoard") {
				f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoard>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoardType") {
				f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoardType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoardTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoardTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDevice") {
				f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGenerator") {
				f(*(std::dynamic_pointer_cast<IfcElectricGenerator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGeneratorType") {
				f(*(std::dynamic_pointer_cast<IfcElectricGeneratorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGeneratorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricGeneratorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotor") {
				f(*(std::dynamic_pointer_cast<IfcElectricMotor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotorType") {
				f(*(std::dynamic_pointer_cast<IfcElectricMotorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricMotorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricResistanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricResistanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControl") {
				f(*(std::dynamic_pointer_cast<IfcElectricTimeControl>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControlType") {
				f(*(std::dynamic_pointer_cast<IfcElectricTimeControlType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControlTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElectricTimeControlTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricVoltageMeasure") {
				f(*(std::dynamic_pointer_cast<IfcElectricVoltageMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElement") {
				f(*(std::dynamic_pointer_cast<IfcElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementarySurface") {
				f(*(std::dynamic_pointer_cast<IfcElementarySurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssembly") {
				f(*(std::dynamic_pointer_cast<IfcElementAssembly>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssemblyType") {
				f(*(std::dynamic_pointer_cast<IfcElementAssemblyType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssemblyTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcElementAssemblyTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementComponent") {
				f(*(std::dynamic_pointer_cast<IfcElementComponent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementComponentType") {
				f(*(std::dynamic_pointer_cast<IfcElementComponentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementCompositionEnum") {
				f(*(std::dynamic_pointer_cast<IfcElementCompositionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementQuantity") {
				f(*(std::dynamic_pointer_cast<IfcElementQuantity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementType") {
				f(*(std::dynamic_pointer_cast<IfcElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEllipse") {
				f(*(std::dynamic_pointer_cast<IfcEllipse>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEllipseProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcEllipseProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyConversionDevice") {
				f(*(std::dynamic_pointer_cast<IfcEnergyConversionDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyConversionDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcEnergyConversionDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyMeasure") {
				f(*(std::dynamic_pointer_cast<IfcEnergyMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngine") {
				f(*(std::dynamic_pointer_cast<IfcEngine>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngineType") {
				f(*(std::dynamic_pointer_cast<IfcEngineType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngineTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcEngineTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCooler") {
				f(*(std::dynamic_pointer_cast<IfcEvaporativeCooler>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCoolerType") {
				f(*(std::dynamic_pointer_cast<IfcEvaporativeCoolerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCoolerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcEvaporativeCoolerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporator") {
				f(*(std::dynamic_pointer_cast<IfcEvaporator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporatorType") {
				f(*(std::dynamic_pointer_cast<IfcEvaporatorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporatorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcEvaporatorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvent") {
				f(*(std::dynamic_pointer_cast<IfcEvent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTime") {
				f(*(std::dynamic_pointer_cast<IfcEventTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTriggerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcEventTriggerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventType") {
				f(*(std::dynamic_pointer_cast<IfcEventType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcEventTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtendedProperties") {
				f(*(std::dynamic_pointer_cast<IfcExtendedProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalInformation") {
				f(*(std::dynamic_pointer_cast<IfcExternalInformation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedHatchStyle") {
				f(*(std::dynamic_pointer_cast<IfcExternallyDefinedHatchStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedSurfaceStyle") {
				f(*(std::dynamic_pointer_cast<IfcExternallyDefinedSurfaceStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedTextFont") {
				f(*(std::dynamic_pointer_cast<IfcExternallyDefinedTextFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalReference") {
				f(*(std::dynamic_pointer_cast<IfcExternalReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalReferenceRelationship") {
				f(*(std::dynamic_pointer_cast<IfcExternalReferenceRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialElement") {
				f(*(std::dynamic_pointer_cast<IfcExternalSpatialElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcExternalSpatialElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialStructureElement") {
				f(*(std::dynamic_pointer_cast<IfcExternalSpatialStructureElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtrudedAreaSolid") {
				f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtrudedAreaSolidTapered") {
				f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolidTapered>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFace") {
				f(*(std::dynamic_pointer_cast<IfcFace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceBasedSurfaceModel") {
				f(*(std::dynamic_pointer_cast<IfcFaceBasedSurfaceModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceBound") {
				f(*(std::dynamic_pointer_cast<IfcFaceBound>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceOuterBound") {
				f(*(std::dynamic_pointer_cast<IfcFaceOuterBound>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceSurface") {
				f(*(std::dynamic_pointer_cast<IfcFaceSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFacetedBrep") {
				f(*(std::dynamic_pointer_cast<IfcFacetedBrep>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFacetedBrepWithVoids") {
				f(*(std::dynamic_pointer_cast<IfcFacetedBrepWithVoids>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFailureConnectionCondition") {
				f(*(std::dynamic_pointer_cast<IfcFailureConnectionCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFan") {
				f(*(std::dynamic_pointer_cast<IfcFan>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFanType") {
				f(*(std::dynamic_pointer_cast<IfcFanType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFanTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFanTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastener") {
				f(*(std::dynamic_pointer_cast<IfcFastener>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastenerType") {
				f(*(std::dynamic_pointer_cast<IfcFastenerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastenerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFastenerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElement") {
				f(*(std::dynamic_pointer_cast<IfcFeatureElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElementAddition") {
				f(*(std::dynamic_pointer_cast<IfcFeatureElementAddition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElementSubtraction") {
				f(*(std::dynamic_pointer_cast<IfcFeatureElementSubtraction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyle") {
				f(*(std::dynamic_pointer_cast<IfcFillAreaStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyleHatching") {
				f(*(std::dynamic_pointer_cast<IfcFillAreaStyleHatching>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyleTiles") {
				f(*(std::dynamic_pointer_cast<IfcFillAreaStyleTiles>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillStyleSelect") {
				f(*(std::dynamic_pointer_cast<IfcFillStyleSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilter") {
				f(*(std::dynamic_pointer_cast<IfcFilter>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilterType") {
				f(*(std::dynamic_pointer_cast<IfcFilterType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilterTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFilterTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminal") {
				f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminalTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminalTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFixedReferenceSweptAreaSolid") {
				f(*(std::dynamic_pointer_cast<IfcFixedReferenceSweptAreaSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowController") {
				f(*(std::dynamic_pointer_cast<IfcFlowController>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowControllerType") {
				f(*(std::dynamic_pointer_cast<IfcFlowControllerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowDirectionEnum") {
				f(*(std::dynamic_pointer_cast<IfcFlowDirectionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowFitting") {
				f(*(std::dynamic_pointer_cast<IfcFlowFitting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowFittingType") {
				f(*(std::dynamic_pointer_cast<IfcFlowFittingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrument") {
				f(*(std::dynamic_pointer_cast<IfcFlowInstrument>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrumentType") {
				f(*(std::dynamic_pointer_cast<IfcFlowInstrumentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrumentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFlowInstrumentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeter") {
				f(*(std::dynamic_pointer_cast<IfcFlowMeter>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeterType") {
				f(*(std::dynamic_pointer_cast<IfcFlowMeterType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeterTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFlowMeterTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMovingDevice") {
				f(*(std::dynamic_pointer_cast<IfcFlowMovingDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMovingDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcFlowMovingDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowSegment") {
				f(*(std::dynamic_pointer_cast<IfcFlowSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowSegmentType") {
				f(*(std::dynamic_pointer_cast<IfcFlowSegmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowStorageDevice") {
				f(*(std::dynamic_pointer_cast<IfcFlowStorageDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowStorageDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcFlowStorageDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTerminal") {
				f(*(std::dynamic_pointer_cast<IfcFlowTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcFlowTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTreatmentDevice") {
				f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTreatmentDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontStyle") {
				f(*(std::dynamic_pointer_cast<IfcFontStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontVariant") {
				f(*(std::dynamic_pointer_cast<IfcFontVariant>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontWeight") {
				f(*(std::dynamic_pointer_cast<IfcFontWeight>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFooting") {
				f(*(std::dynamic_pointer_cast<IfcFooting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFootingType") {
				f(*(std::dynamic_pointer_cast<IfcFootingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFootingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFootingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcForceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcForceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFrequencyMeasure") {
				f(*(std::dynamic_pointer_cast<IfcFrequencyMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnishingElement") {
				f(*(std::dynamic_pointer_cast<IfcFurnishingElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnishingElementType") {
				f(*(std::dynamic_pointer_cast<IfcFurnishingElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurniture") {
				f(*(std::dynamic_pointer_cast<IfcFurniture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnitureType") {
				f(*(std::dynamic_pointer_cast<IfcFurnitureType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnitureTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcFurnitureTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElement") {
				f(*(std::dynamic_pointer_cast<IfcGeographicElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElementType") {
				f(*(std::dynamic_pointer_cast<IfcGeographicElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcGeographicElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricCurveSet") {
				f(*(std::dynamic_pointer_cast<IfcGeometricCurveSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricProjectionEnum") {
				f(*(std::dynamic_pointer_cast<IfcGeometricProjectionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationContext") {
				f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationContext>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationItem") {
				f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationSubContext") {
				f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationSubContext>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricSet") {
				f(*(std::dynamic_pointer_cast<IfcGeometricSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricSetSelect") {
				f(*(std::dynamic_pointer_cast<IfcGeometricSetSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGloballyUniqueId") {
				f(*(std::dynamic_pointer_cast<IfcGloballyUniqueId>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGlobalOrLocalEnum") {
				f(*(std::dynamic_pointer_cast<IfcGlobalOrLocalEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGrid") {
				f(*(std::dynamic_pointer_cast<IfcGrid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridAxis") {
				f(*(std::dynamic_pointer_cast<IfcGridAxis>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridPlacement") {
				f(*(std::dynamic_pointer_cast<IfcGridPlacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridPlacementDirectionSelect") {
				f(*(std::dynamic_pointer_cast<IfcGridPlacementDirectionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcGridTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGroup") {
				f(*(std::dynamic_pointer_cast<IfcGroup>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHalfSpaceSolid") {
				f(*(std::dynamic_pointer_cast<IfcHalfSpaceSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHatchLineDistanceSelect") {
				f(*(std::dynamic_pointer_cast<IfcHatchLineDistanceSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchanger") {
				f(*(std::dynamic_pointer_cast<IfcHeatExchanger>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchangerType") {
				f(*(std::dynamic_pointer_cast<IfcHeatExchangerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchangerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcHeatExchangerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatFluxDensityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcHeatFluxDensityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatingValueMeasure") {
				f(*(std::dynamic_pointer_cast<IfcHeatingValueMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifier") {
				f(*(std::dynamic_pointer_cast<IfcHumidifier>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifierType") {
				f(*(std::dynamic_pointer_cast<IfcHumidifierType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifierTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcHumidifierTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIdentifier") {
				f(*(std::dynamic_pointer_cast<IfcIdentifier>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIlluminanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcIlluminanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcImageTexture") {
				f(*(std::dynamic_pointer_cast<IfcImageTexture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedColourMap") {
				f(*(std::dynamic_pointer_cast<IfcIndexedColourMap>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolyCurve") {
				f(*(std::dynamic_pointer_cast<IfcIndexedPolyCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolygonalFace") {
				f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolygonalFaceWithVoids") {
				f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFaceWithVoids>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedTextureMap") {
				f(*(std::dynamic_pointer_cast<IfcIndexedTextureMap>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedTriangleTextureMap") {
				f(*(std::dynamic_pointer_cast<IfcIndexedTriangleTextureMap>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInductanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcInductanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInteger") {
				f(*(std::dynamic_pointer_cast<IfcInteger>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIntegerCountRateMeasure") {
				f(*(std::dynamic_pointer_cast<IfcIntegerCountRateMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptor") {
				f(*(std::dynamic_pointer_cast<IfcInterceptor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptorType") {
				f(*(std::dynamic_pointer_cast<IfcInterceptorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcInterceptorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInternalOrExternalEnum") {
				f(*(std::dynamic_pointer_cast<IfcInternalOrExternalEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIntersectionCurve") {
				f(*(std::dynamic_pointer_cast<IfcIntersectionCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInventory") {
				f(*(std::dynamic_pointer_cast<IfcInventory>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInventoryTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcInventoryTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIonConcentrationMeasure") {
				f(*(std::dynamic_pointer_cast<IfcIonConcentrationMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIrregularTimeSeries") {
				f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeries>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIrregularTimeSeriesValue") {
				f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeriesValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcIShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIsothermalMoistureCapacityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcIsothermalMoistureCapacityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBox") {
				f(*(std::dynamic_pointer_cast<IfcJunctionBox>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBoxType") {
				f(*(std::dynamic_pointer_cast<IfcJunctionBoxType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBoxTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcJunctionBoxTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcKinematicViscosityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcKinematicViscosityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcKnotType") {
				f(*(std::dynamic_pointer_cast<IfcKnotType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLabel") {
				f(*(std::dynamic_pointer_cast<IfcLabel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResource") {
				f(*(std::dynamic_pointer_cast<IfcLaborResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResourceType") {
				f(*(std::dynamic_pointer_cast<IfcLaborResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcLaborResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLagTime") {
				f(*(std::dynamic_pointer_cast<IfcLagTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLamp") {
				f(*(std::dynamic_pointer_cast<IfcLamp>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLampType") {
				f(*(std::dynamic_pointer_cast<IfcLampType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLampTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcLampTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLanguageId") {
				f(*(std::dynamic_pointer_cast<IfcLanguageId>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLayeredItem") {
				f(*(std::dynamic_pointer_cast<IfcLayeredItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLayerSetDirectionEnum") {
				f(*(std::dynamic_pointer_cast<IfcLayerSetDirectionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLengthMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLibraryInformation") {
				f(*(std::dynamic_pointer_cast<IfcLibraryInformation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLibraryReference") {
				f(*(std::dynamic_pointer_cast<IfcLibraryReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLibrarySelect") {
				f(*(std::dynamic_pointer_cast<IfcLibrarySelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightDistributionCurveEnum") {
				f(*(std::dynamic_pointer_cast<IfcLightDistributionCurveEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightDistributionData") {
				f(*(std::dynamic_pointer_cast<IfcLightDistributionData>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightDistributionDataSourceSelect") {
				f(*(std::dynamic_pointer_cast<IfcLightDistributionDataSourceSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightEmissionSourceEnum") {
				f(*(std::dynamic_pointer_cast<IfcLightEmissionSourceEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixture") {
				f(*(std::dynamic_pointer_cast<IfcLightFixture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixtureType") {
				f(*(std::dynamic_pointer_cast<IfcLightFixtureType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixtureTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcLightFixtureTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightIntensityDistribution") {
				f(*(std::dynamic_pointer_cast<IfcLightIntensityDistribution>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSource") {
				f(*(std::dynamic_pointer_cast<IfcLightSource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceAmbient") {
				f(*(std::dynamic_pointer_cast<IfcLightSourceAmbient>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceDirectional") {
				f(*(std::dynamic_pointer_cast<IfcLightSourceDirectional>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceGoniometric") {
				f(*(std::dynamic_pointer_cast<IfcLightSourceGoniometric>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourcePositional") {
				f(*(std::dynamic_pointer_cast<IfcLightSourcePositional>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceSpot") {
				f(*(std::dynamic_pointer_cast<IfcLightSourceSpot>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLine") {
				f(*(std::dynamic_pointer_cast<IfcLine>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearForceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLinearForceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearMomentMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLinearMomentMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearPlacement") {
				f(*(std::dynamic_pointer_cast<IfcLinearPlacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearPositioningElement") {
				f(*(std::dynamic_pointer_cast<IfcLinearPositioningElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearStiffnessMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLinearStiffnessMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearVelocityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLinearVelocityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLineIndex") {
				f(*(std::dynamic_pointer_cast<IfcLineIndex>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLineSegment2D") {
				f(*(std::dynamic_pointer_cast<IfcLineSegment2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLoadGroupTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcLoadGroupTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLocalPlacement") {
				f(*(std::dynamic_pointer_cast<IfcLocalPlacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLogical") {
				f(*(std::dynamic_pointer_cast<IfcLogical>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLogicalOperatorEnum") {
				f(*(std::dynamic_pointer_cast<IfcLogicalOperatorEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLoop") {
				f(*(std::dynamic_pointer_cast<IfcLoop>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcLShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousFluxMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLuminousFluxMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousIntensityDistributionMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLuminousIntensityDistributionMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousIntensityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcLuminousIntensityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMagneticFluxDensityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMagneticFluxDensityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMagneticFluxMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMagneticFluxMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcManifoldSolidBrep") {
				f(*(std::dynamic_pointer_cast<IfcManifoldSolidBrep>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMapConversion") {
				f(*(std::dynamic_pointer_cast<IfcMapConversion>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMappedItem") {
				f(*(std::dynamic_pointer_cast<IfcMappedItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassDensityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMassDensityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassFlowRateMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMassFlowRateMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMassMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassPerLengthMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMassPerLengthMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterial") {
				f(*(std::dynamic_pointer_cast<IfcMaterial>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialClassificationRelationship") {
				f(*(std::dynamic_pointer_cast<IfcMaterialClassificationRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialConstituent") {
				f(*(std::dynamic_pointer_cast<IfcMaterialConstituent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialConstituentSet") {
				f(*(std::dynamic_pointer_cast<IfcMaterialConstituentSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialDefinition") {
				f(*(std::dynamic_pointer_cast<IfcMaterialDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialDefinitionRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcMaterialDefinitionRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayer") {
				f(*(std::dynamic_pointer_cast<IfcMaterialLayer>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerSet") {
				f(*(std::dynamic_pointer_cast<IfcMaterialLayerSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerSetUsage") {
				f(*(std::dynamic_pointer_cast<IfcMaterialLayerSetUsage>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerWithOffsets") {
				f(*(std::dynamic_pointer_cast<IfcMaterialLayerWithOffsets>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialList") {
				f(*(std::dynamic_pointer_cast<IfcMaterialList>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfile") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProfile>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSet") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProfileSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSetUsage") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsage>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSetUsageTapering") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsageTapering>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileWithOffsets") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProfileWithOffsets>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProperties") {
				f(*(std::dynamic_pointer_cast<IfcMaterialProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialRelationship") {
				f(*(std::dynamic_pointer_cast<IfcMaterialRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialSelect") {
				f(*(std::dynamic_pointer_cast<IfcMaterialSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialUsageDefinition") {
				f(*(std::dynamic_pointer_cast<IfcMaterialUsageDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMeasureValue") {
				f(*(std::dynamic_pointer_cast<IfcMeasureValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMeasureWithUnit") {
				f(*(std::dynamic_pointer_cast<IfcMeasureWithUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastener") {
				f(*(std::dynamic_pointer_cast<IfcMechanicalFastener>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastenerType") {
				f(*(std::dynamic_pointer_cast<IfcMechanicalFastenerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastenerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcMechanicalFastenerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDevice") {
				f(*(std::dynamic_pointer_cast<IfcMedicalDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcMedicalDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcMedicalDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMember") {
				f(*(std::dynamic_pointer_cast<IfcMember>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcMemberStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberType") {
				f(*(std::dynamic_pointer_cast<IfcMemberType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcMemberTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMetric") {
				f(*(std::dynamic_pointer_cast<IfcMetric>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMetricValueSelect") {
				f(*(std::dynamic_pointer_cast<IfcMetricValueSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMirroredProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcMirroredProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfElasticityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfElasticityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfLinearSubgradeReactionMeasure") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfLinearSubgradeReactionMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfRotationalSubgradeReactionMeasure") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfRotationalSubgradeReactionMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfRotationalSubgradeReactionSelect") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfRotationalSubgradeReactionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfSubgradeReactionMeasure") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfSubgradeReactionMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfSubgradeReactionSelect") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfSubgradeReactionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfTranslationalSubgradeReactionSelect") {
				f(*(std::dynamic_pointer_cast<IfcModulusOfTranslationalSubgradeReactionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMoistureDiffusivityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMoistureDiffusivityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMolecularWeightMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMolecularWeightMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMomentOfInertiaMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMomentOfInertiaMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonetaryMeasure") {
				f(*(std::dynamic_pointer_cast<IfcMonetaryMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonetaryUnit") {
				f(*(std::dynamic_pointer_cast<IfcMonetaryUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonthInYearNumber") {
				f(*(std::dynamic_pointer_cast<IfcMonthInYearNumber>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnection") {
				f(*(std::dynamic_pointer_cast<IfcMotorConnection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnectionType") {
				f(*(std::dynamic_pointer_cast<IfcMotorConnectionType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnectionTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcMotorConnectionTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNamedUnit") {
				f(*(std::dynamic_pointer_cast<IfcNamedUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNonNegativeLengthMeasure") {
				f(*(std::dynamic_pointer_cast<IfcNonNegativeLengthMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNormalisedRatioMeasure") {
				f(*(std::dynamic_pointer_cast<IfcNormalisedRatioMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNullStyle") {
				f(*(std::dynamic_pointer_cast<IfcNullStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNumericMeasure") {
				f(*(std::dynamic_pointer_cast<IfcNumericMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObject") {
				f(*(std::dynamic_pointer_cast<IfcObject>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectDefinition") {
				f(*(std::dynamic_pointer_cast<IfcObjectDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjective") {
				f(*(std::dynamic_pointer_cast<IfcObjective>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectiveEnum") {
				f(*(std::dynamic_pointer_cast<IfcObjectiveEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectPlacement") {
				f(*(std::dynamic_pointer_cast<IfcObjectPlacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectReferenceSelect") {
				f(*(std::dynamic_pointer_cast<IfcObjectReferenceSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcObjectTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOccupant") {
				f(*(std::dynamic_pointer_cast<IfcOccupant>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOccupantTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcOccupantTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve") {
				f(*(std::dynamic_pointer_cast<IfcOffsetCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve2D") {
				f(*(std::dynamic_pointer_cast<IfcOffsetCurve2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve3D") {
				f(*(std::dynamic_pointer_cast<IfcOffsetCurve3D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurveByDistances") {
				f(*(std::dynamic_pointer_cast<IfcOffsetCurveByDistances>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningElement") {
				f(*(std::dynamic_pointer_cast<IfcOpeningElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcOpeningElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcOpeningStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpenShell") {
				f(*(std::dynamic_pointer_cast<IfcOpenShell>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrganization") {
				f(*(std::dynamic_pointer_cast<IfcOrganization>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrganizationRelationship") {
				f(*(std::dynamic_pointer_cast<IfcOrganizationRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrientationExpression") {
				f(*(std::dynamic_pointer_cast<IfcOrientationExpression>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrientedEdge") {
				f(*(std::dynamic_pointer_cast<IfcOrientedEdge>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOuterBoundaryCurve") {
				f(*(std::dynamic_pointer_cast<IfcOuterBoundaryCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutlet") {
				f(*(std::dynamic_pointer_cast<IfcOutlet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutletType") {
				f(*(std::dynamic_pointer_cast<IfcOutletType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutletTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcOutletTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOwnerHistory") {
				f(*(std::dynamic_pointer_cast<IfcOwnerHistory>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcParameterizedProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcParameterizedProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcParameterValue") {
				f(*(std::dynamic_pointer_cast<IfcParameterValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPath") {
				f(*(std::dynamic_pointer_cast<IfcPath>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPcurve") {
				f(*(std::dynamic_pointer_cast<IfcPcurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerformanceHistory") {
				f(*(std::dynamic_pointer_cast<IfcPerformanceHistory>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerformanceHistoryTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPerformanceHistoryTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermeableCoveringOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcPermeableCoveringOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermeableCoveringProperties") {
				f(*(std::dynamic_pointer_cast<IfcPermeableCoveringProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermit") {
				f(*(std::dynamic_pointer_cast<IfcPermit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermitTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPermitTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerson") {
				f(*(std::dynamic_pointer_cast<IfcPerson>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPersonAndOrganization") {
				f(*(std::dynamic_pointer_cast<IfcPersonAndOrganization>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPHMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPHMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalComplexQuantity") {
				f(*(std::dynamic_pointer_cast<IfcPhysicalComplexQuantity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalOrVirtualEnum") {
				f(*(std::dynamic_pointer_cast<IfcPhysicalOrVirtualEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalQuantity") {
				f(*(std::dynamic_pointer_cast<IfcPhysicalQuantity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalSimpleQuantity") {
				f(*(std::dynamic_pointer_cast<IfcPhysicalSimpleQuantity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPile") {
				f(*(std::dynamic_pointer_cast<IfcPile>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileConstructionEnum") {
				f(*(std::dynamic_pointer_cast<IfcPileConstructionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileType") {
				f(*(std::dynamic_pointer_cast<IfcPileType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPileTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFitting") {
				f(*(std::dynamic_pointer_cast<IfcPipeFitting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFittingType") {
				f(*(std::dynamic_pointer_cast<IfcPipeFittingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFittingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPipeFittingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegment") {
				f(*(std::dynamic_pointer_cast<IfcPipeSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegmentType") {
				f(*(std::dynamic_pointer_cast<IfcPipeSegmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPipeSegmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPixelTexture") {
				f(*(std::dynamic_pointer_cast<IfcPixelTexture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlacement") {
				f(*(std::dynamic_pointer_cast<IfcPlacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarBox") {
				f(*(std::dynamic_pointer_cast<IfcPlanarBox>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarExtent") {
				f(*(std::dynamic_pointer_cast<IfcPlanarExtent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarForceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPlanarForceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlane") {
				f(*(std::dynamic_pointer_cast<IfcPlane>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlaneAngleMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPlaneAngleMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlate") {
				f(*(std::dynamic_pointer_cast<IfcPlate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcPlateStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateType") {
				f(*(std::dynamic_pointer_cast<IfcPlateType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPlateTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPoint") {
				f(*(std::dynamic_pointer_cast<IfcPoint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPointOnCurve") {
				f(*(std::dynamic_pointer_cast<IfcPointOnCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPointOnSurface") {
				f(*(std::dynamic_pointer_cast<IfcPointOnSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPointOrVertexPoint") {
				f(*(std::dynamic_pointer_cast<IfcPointOrVertexPoint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolygonalBoundedHalfSpace") {
				f(*(std::dynamic_pointer_cast<IfcPolygonalBoundedHalfSpace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolygonalFaceSet") {
				f(*(std::dynamic_pointer_cast<IfcPolygonalFaceSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolyline") {
				f(*(std::dynamic_pointer_cast<IfcPolyline>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolyLoop") {
				f(*(std::dynamic_pointer_cast<IfcPolyLoop>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPort") {
				f(*(std::dynamic_pointer_cast<IfcPort>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositioningElement") {
				f(*(std::dynamic_pointer_cast<IfcPositioningElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger") {
				f(*(std::dynamic_pointer_cast<IfcPositiveInteger>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveLengthMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPositiveLengthMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositivePlaneAngleMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPositivePlaneAngleMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveRatioMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPositiveRatioMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPostalAddress") {
				f(*(std::dynamic_pointer_cast<IfcPostalAddress>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPowerMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPowerMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedColour") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedColour>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedCurveFont") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedCurveFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedItem") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedProperties") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedPropertySet") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedPropertySet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedTextFont") {
				f(*(std::dynamic_pointer_cast<IfcPreDefinedTextFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreferredSurfaceCurveRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcPreferredSurfaceCurveRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentableText") {
				f(*(std::dynamic_pointer_cast<IfcPresentableText>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationItem") {
				f(*(std::dynamic_pointer_cast<IfcPresentationItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationLayerAssignment") {
				f(*(std::dynamic_pointer_cast<IfcPresentationLayerAssignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationLayerWithStyle") {
				f(*(std::dynamic_pointer_cast<IfcPresentationLayerWithStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationStyle") {
				f(*(std::dynamic_pointer_cast<IfcPresentationStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationStyleAssignment") {
				f(*(std::dynamic_pointer_cast<IfcPresentationStyleAssignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationStyleSelect") {
				f(*(std::dynamic_pointer_cast<IfcPresentationStyleSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPressureMeasure") {
				f(*(std::dynamic_pointer_cast<IfcPressureMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedure") {
				f(*(std::dynamic_pointer_cast<IfcProcedure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedureType") {
				f(*(std::dynamic_pointer_cast<IfcProcedureType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedureTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProcedureTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcess") {
				f(*(std::dynamic_pointer_cast<IfcProcess>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcessSelect") {
				f(*(std::dynamic_pointer_cast<IfcProcessSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProduct") {
				f(*(std::dynamic_pointer_cast<IfcProduct>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductDefinitionShape") {
				f(*(std::dynamic_pointer_cast<IfcProductDefinitionShape>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcProductRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductRepresentationSelect") {
				f(*(std::dynamic_pointer_cast<IfcProductRepresentationSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductSelect") {
				f(*(std::dynamic_pointer_cast<IfcProductSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileProperties") {
				f(*(std::dynamic_pointer_cast<IfcProfileProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProfileTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProject") {
				f(*(std::dynamic_pointer_cast<IfcProject>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectedCRS") {
				f(*(std::dynamic_pointer_cast<IfcProjectedCRS>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectedOrTrueLengthEnum") {
				f(*(std::dynamic_pointer_cast<IfcProjectedOrTrueLengthEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectionElement") {
				f(*(std::dynamic_pointer_cast<IfcProjectionElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectionElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProjectionElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectLibrary") {
				f(*(std::dynamic_pointer_cast<IfcProjectLibrary>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectOrder") {
				f(*(std::dynamic_pointer_cast<IfcProjectOrder>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectOrderTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProjectOrderTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProperty") {
				f(*(std::dynamic_pointer_cast<IfcProperty>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyAbstraction") {
				f(*(std::dynamic_pointer_cast<IfcPropertyAbstraction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyBoundedValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertyBoundedValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyDefinition") {
				f(*(std::dynamic_pointer_cast<IfcPropertyDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyDependencyRelationship") {
				f(*(std::dynamic_pointer_cast<IfcPropertyDependencyRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyEnumeratedValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertyEnumeratedValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyEnumeration") {
				f(*(std::dynamic_pointer_cast<IfcPropertyEnumeration>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyListValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertyListValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyReferenceValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertyReferenceValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySet") {
				f(*(std::dynamic_pointer_cast<IfcPropertySet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetDefinition") {
				f(*(std::dynamic_pointer_cast<IfcPropertySetDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetDefinitionSelect") {
				f(*(std::dynamic_pointer_cast<IfcPropertySetDefinitionSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetDefinitionSet") {
				f(*(std::dynamic_pointer_cast<IfcPropertySetDefinitionSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetTemplate") {
				f(*(std::dynamic_pointer_cast<IfcPropertySetTemplate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetTemplateTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPropertySetTemplateTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySingleValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertySingleValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTableValue") {
				f(*(std::dynamic_pointer_cast<IfcPropertyTableValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTemplate") {
				f(*(std::dynamic_pointer_cast<IfcPropertyTemplate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTemplateDefinition") {
				f(*(std::dynamic_pointer_cast<IfcPropertyTemplateDefinition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDevice") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnit") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnitType") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnitType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnitTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnitTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProxy") {
				f(*(std::dynamic_pointer_cast<IfcProxy>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPump") {
				f(*(std::dynamic_pointer_cast<IfcPump>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPumpType") {
				f(*(std::dynamic_pointer_cast<IfcPumpType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPumpTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcPumpTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityArea") {
				f(*(std::dynamic_pointer_cast<IfcQuantityArea>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityCount") {
				f(*(std::dynamic_pointer_cast<IfcQuantityCount>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityLength") {
				f(*(std::dynamic_pointer_cast<IfcQuantityLength>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantitySet") {
				f(*(std::dynamic_pointer_cast<IfcQuantitySet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityTime") {
				f(*(std::dynamic_pointer_cast<IfcQuantityTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityVolume") {
				f(*(std::dynamic_pointer_cast<IfcQuantityVolume>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityWeight") {
				f(*(std::dynamic_pointer_cast<IfcQuantityWeight>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRadioActivityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcRadioActivityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailing") {
				f(*(std::dynamic_pointer_cast<IfcRailing>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailingType") {
				f(*(std::dynamic_pointer_cast<IfcRailingType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailingTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcRailingTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRamp") {
				f(*(std::dynamic_pointer_cast<IfcRamp>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlight") {
				f(*(std::dynamic_pointer_cast<IfcRampFlight>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlightType") {
				f(*(std::dynamic_pointer_cast<IfcRampFlightType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlightTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcRampFlightTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampType") {
				f(*(std::dynamic_pointer_cast<IfcRampType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcRampTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRatioMeasure") {
				f(*(std::dynamic_pointer_cast<IfcRatioMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRationalBSplineCurveWithKnots") {
				f(*(std::dynamic_pointer_cast<IfcRationalBSplineCurveWithKnots>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRationalBSplineSurfaceWithKnots") {
				f(*(std::dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReal") {
				f(*(std::dynamic_pointer_cast<IfcReal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangleHollowProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcRectangleHollowProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangleProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcRectangleProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangularPyramid") {
				f(*(std::dynamic_pointer_cast<IfcRectangularPyramid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangularTrimmedSurface") {
				f(*(std::dynamic_pointer_cast<IfcRectangularTrimmedSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRecurrencePattern") {
				f(*(std::dynamic_pointer_cast<IfcRecurrencePattern>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRecurrenceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcRecurrenceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReference") {
				f(*(std::dynamic_pointer_cast<IfcReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReferent") {
				f(*(std::dynamic_pointer_cast<IfcReferent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReferentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcReferentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReflectanceMethodEnum") {
				f(*(std::dynamic_pointer_cast<IfcReflectanceMethodEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRegularTimeSeries") {
				f(*(std::dynamic_pointer_cast<IfcRegularTimeSeries>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcementBarProperties") {
				f(*(std::dynamic_pointer_cast<IfcReinforcementBarProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcementDefinitionProperties") {
				f(*(std::dynamic_pointer_cast<IfcReinforcementDefinitionProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBar") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingBar>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarRoleEnum") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingBarRoleEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarSurfaceEnum") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingBarSurfaceEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarType") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingBarType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingBarTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingElement") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingElementType") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMesh") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingMesh>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMeshType") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingMeshType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMeshTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcReinforcingMeshTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAggregates") {
				f(*(std::dynamic_pointer_cast<IfcRelAggregates>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssigns") {
				f(*(std::dynamic_pointer_cast<IfcRelAssigns>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToActor") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToActor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToControl") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToControl>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToGroup") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroup>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToGroupByFactor") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroupByFactor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToProcess") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToProcess>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToProduct") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToProduct>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToResource") {
				f(*(std::dynamic_pointer_cast<IfcRelAssignsToResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociates") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociates>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesApproval") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesApproval>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesClassification") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesClassification>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesConstraint") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesConstraint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesDocument") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesDocument>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesLibrary") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesLibrary>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesMaterial") {
				f(*(std::dynamic_pointer_cast<IfcRelAssociatesMaterial>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelationship") {
				f(*(std::dynamic_pointer_cast<IfcRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnects") {
				f(*(std::dynamic_pointer_cast<IfcRelConnects>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsElements") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPathElements") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsPathElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPorts") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsPorts>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPortToElement") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsPortToElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsStructuralActivity") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralActivity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsStructuralMember") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralMember>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsWithEccentricity") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsWithEccentricity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsWithRealizingElements") {
				f(*(std::dynamic_pointer_cast<IfcRelConnectsWithRealizingElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelContainedInSpatialStructure") {
				f(*(std::dynamic_pointer_cast<IfcRelContainedInSpatialStructure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelCoversBldgElements") {
				f(*(std::dynamic_pointer_cast<IfcRelCoversBldgElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelCoversSpaces") {
				f(*(std::dynamic_pointer_cast<IfcRelCoversSpaces>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDeclares") {
				f(*(std::dynamic_pointer_cast<IfcRelDeclares>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDecomposes") {
				f(*(std::dynamic_pointer_cast<IfcRelDecomposes>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefines") {
				f(*(std::dynamic_pointer_cast<IfcRelDefines>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByObject") {
				f(*(std::dynamic_pointer_cast<IfcRelDefinesByObject>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByProperties") {
				f(*(std::dynamic_pointer_cast<IfcRelDefinesByProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByTemplate") {
				f(*(std::dynamic_pointer_cast<IfcRelDefinesByTemplate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByType") {
				f(*(std::dynamic_pointer_cast<IfcRelDefinesByType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelFillsElement") {
				f(*(std::dynamic_pointer_cast<IfcRelFillsElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelFlowControlElements") {
				f(*(std::dynamic_pointer_cast<IfcRelFlowControlElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelInterferesElements") {
				f(*(std::dynamic_pointer_cast<IfcRelInterferesElements>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelNests") {
				f(*(std::dynamic_pointer_cast<IfcRelNests>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelProjectsElement") {
				f(*(std::dynamic_pointer_cast<IfcRelProjectsElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelReferencedInSpatialStructure") {
				f(*(std::dynamic_pointer_cast<IfcRelReferencedInSpatialStructure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSequence") {
				f(*(std::dynamic_pointer_cast<IfcRelSequence>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelServicesBuildings") {
				f(*(std::dynamic_pointer_cast<IfcRelServicesBuildings>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary") {
				f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary1stLevel") {
				f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary1stLevel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary2ndLevel") {
				f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary2ndLevel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelVoidsElement") {
				f(*(std::dynamic_pointer_cast<IfcRelVoidsElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReparametrisedCompositeCurveSegment") {
				f(*(std::dynamic_pointer_cast<IfcReparametrisedCompositeCurveSegment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationContext") {
				f(*(std::dynamic_pointer_cast<IfcRepresentationContext>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationItem") {
				f(*(std::dynamic_pointer_cast<IfcRepresentationItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationMap") {
				f(*(std::dynamic_pointer_cast<IfcRepresentationMap>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResource") {
				f(*(std::dynamic_pointer_cast<IfcResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceApprovalRelationship") {
				f(*(std::dynamic_pointer_cast<IfcResourceApprovalRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceConstraintRelationship") {
				f(*(std::dynamic_pointer_cast<IfcResourceConstraintRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceLevelRelationship") {
				f(*(std::dynamic_pointer_cast<IfcResourceLevelRelationship>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceObjectSelect") {
				f(*(std::dynamic_pointer_cast<IfcResourceObjectSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceSelect") {
				f(*(std::dynamic_pointer_cast<IfcResourceSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceTime") {
				f(*(std::dynamic_pointer_cast<IfcResourceTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRevolvedAreaSolid") {
				f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRevolvedAreaSolidTapered") {
				f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolidTapered>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRightCircularCone") {
				f(*(std::dynamic_pointer_cast<IfcRightCircularCone>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRightCircularCylinder") {
				f(*(std::dynamic_pointer_cast<IfcRightCircularCylinder>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoleEnum") {
				f(*(std::dynamic_pointer_cast<IfcRoleEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoof") {
				f(*(std::dynamic_pointer_cast<IfcRoof>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoofType") {
				f(*(std::dynamic_pointer_cast<IfcRoofType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoofTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcRoofTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoot") {
				f(*(std::dynamic_pointer_cast<IfcRoot>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalFrequencyMeasure") {
				f(*(std::dynamic_pointer_cast<IfcRotationalFrequencyMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalMassMeasure") {
				f(*(std::dynamic_pointer_cast<IfcRotationalMassMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalStiffnessMeasure") {
				f(*(std::dynamic_pointer_cast<IfcRotationalStiffnessMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalStiffnessSelect") {
				f(*(std::dynamic_pointer_cast<IfcRotationalStiffnessSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoundedRectangleProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcRoundedRectangleProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminal") {
				f(*(std::dynamic_pointer_cast<IfcSanitaryTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcSanitaryTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminalTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSanitaryTerminalTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSchedulingTime") {
				f(*(std::dynamic_pointer_cast<IfcSchedulingTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSeamCurve") {
				f(*(std::dynamic_pointer_cast<IfcSeamCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionalAreaIntegralMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSectionalAreaIntegralMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSolid") {
				f(*(std::dynamic_pointer_cast<IfcSectionedSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSolidHorizontal") {
				f(*(std::dynamic_pointer_cast<IfcSectionedSolidHorizontal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSpine") {
				f(*(std::dynamic_pointer_cast<IfcSectionedSpine>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionModulusMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSectionModulusMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionProperties") {
				f(*(std::dynamic_pointer_cast<IfcSectionProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionReinforcementProperties") {
				f(*(std::dynamic_pointer_cast<IfcSectionReinforcementProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSectionTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSegmentIndexSelect") {
				f(*(std::dynamic_pointer_cast<IfcSegmentIndexSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensor") {
				f(*(std::dynamic_pointer_cast<IfcSensor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensorType") {
				f(*(std::dynamic_pointer_cast<IfcSensorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSensorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSequenceEnum") {
				f(*(std::dynamic_pointer_cast<IfcSequenceEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDevice") {
				f(*(std::dynamic_pointer_cast<IfcShadingDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcShadingDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcShadingDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeAspect") {
				f(*(std::dynamic_pointer_cast<IfcShapeAspect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeModel") {
				f(*(std::dynamic_pointer_cast<IfcShapeModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcShapeRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShearModulusMeasure") {
				f(*(std::dynamic_pointer_cast<IfcShearModulusMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShell") {
				f(*(std::dynamic_pointer_cast<IfcShell>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShellBasedSurfaceModel") {
				f(*(std::dynamic_pointer_cast<IfcShellBasedSurfaceModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimpleProperty") {
				f(*(std::dynamic_pointer_cast<IfcSimpleProperty>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimplePropertyTemplate") {
				f(*(std::dynamic_pointer_cast<IfcSimplePropertyTemplate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimplePropertyTemplateTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSimplePropertyTemplateTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimpleValue") {
				f(*(std::dynamic_pointer_cast<IfcSimpleValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIPrefix") {
				f(*(std::dynamic_pointer_cast<IfcSIPrefix>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSite") {
				f(*(std::dynamic_pointer_cast<IfcSite>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIUnit") {
				f(*(std::dynamic_pointer_cast<IfcSIUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIUnitName") {
				f(*(std::dynamic_pointer_cast<IfcSIUnitName>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSizeSelect") {
				f(*(std::dynamic_pointer_cast<IfcSizeSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlab") {
				f(*(std::dynamic_pointer_cast<IfcSlab>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabElementedCase") {
				f(*(std::dynamic_pointer_cast<IfcSlabElementedCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcSlabStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabType") {
				f(*(std::dynamic_pointer_cast<IfcSlabType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSlabTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlippageConnectionCondition") {
				f(*(std::dynamic_pointer_cast<IfcSlippageConnectionCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDevice") {
				f(*(std::dynamic_pointer_cast<IfcSolarDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcSolarDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSolarDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolidAngleMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSolidAngleMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolidModel") {
				f(*(std::dynamic_pointer_cast<IfcSolidModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolidOrShell") {
				f(*(std::dynamic_pointer_cast<IfcSolidOrShell>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPowerLevelMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSoundPowerLevelMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPowerMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSoundPowerMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPressureLevelMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSoundPressureLevelMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPressureMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSoundPressureMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpace") {
				f(*(std::dynamic_pointer_cast<IfcSpace>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceBoundarySelect") {
				f(*(std::dynamic_pointer_cast<IfcSpaceBoundarySelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeater") {
				f(*(std::dynamic_pointer_cast<IfcSpaceHeater>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeaterType") {
				f(*(std::dynamic_pointer_cast<IfcSpaceHeaterType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeaterTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSpaceHeaterTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceType") {
				f(*(std::dynamic_pointer_cast<IfcSpaceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSpaceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialElement") {
				f(*(std::dynamic_pointer_cast<IfcSpatialElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialElementType") {
				f(*(std::dynamic_pointer_cast<IfcSpatialElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialStructureElement") {
				f(*(std::dynamic_pointer_cast<IfcSpatialStructureElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialStructureElementType") {
				f(*(std::dynamic_pointer_cast<IfcSpatialStructureElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZone") {
				f(*(std::dynamic_pointer_cast<IfcSpatialZone>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZoneType") {
				f(*(std::dynamic_pointer_cast<IfcSpatialZoneType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZoneTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSpatialZoneTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecificHeatCapacityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcSpecificHeatCapacityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecularExponent") {
				f(*(std::dynamic_pointer_cast<IfcSpecularExponent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecularHighlightSelect") {
				f(*(std::dynamic_pointer_cast<IfcSpecularHighlightSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecularRoughness") {
				f(*(std::dynamic_pointer_cast<IfcSpecularRoughness>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSphere") {
				f(*(std::dynamic_pointer_cast<IfcSphere>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSphericalSurface") {
				f(*(std::dynamic_pointer_cast<IfcSphericalSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminal") {
				f(*(std::dynamic_pointer_cast<IfcStackTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcStackTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminalTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStackTerminalTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStair") {
				f(*(std::dynamic_pointer_cast<IfcStair>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlight") {
				f(*(std::dynamic_pointer_cast<IfcStairFlight>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlightType") {
				f(*(std::dynamic_pointer_cast<IfcStairFlightType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlightTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStairFlightTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairType") {
				f(*(std::dynamic_pointer_cast<IfcStairType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStairTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStateEnum") {
				f(*(std::dynamic_pointer_cast<IfcStateEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStrippedOptional") {
				f(*(std::dynamic_pointer_cast<IfcStrippedOptional>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralActivity") {
				f(*(std::dynamic_pointer_cast<IfcStructuralActivity>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralActivityAssignmentSelect") {
				f(*(std::dynamic_pointer_cast<IfcStructuralActivityAssignmentSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralAnalysisModel") {
				f(*(std::dynamic_pointer_cast<IfcStructuralAnalysisModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralConnection") {
				f(*(std::dynamic_pointer_cast<IfcStructuralConnection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralConnectionCondition") {
				f(*(std::dynamic_pointer_cast<IfcStructuralConnectionCondition>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveActivityTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveActivityTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveConnection") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveConnection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMember") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveMember>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMemberTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveMemberTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMemberVarying") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveMemberVarying>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveReaction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralCurveReaction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralItem") {
				f(*(std::dynamic_pointer_cast<IfcStructuralItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLinearAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLinearAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoad") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoad>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadCase") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadConfiguration") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadConfiguration>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadGroup") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadGroup>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadLinearForce") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadLinearForce>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadOrResult") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadOrResult>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadPlanarForce") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadPlanarForce>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleDisplacement") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleDisplacementDistortion") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacementDistortion>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleForce") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForce>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleForceWarping") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForceWarping>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadStatic") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadStatic>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadTemperature") {
				f(*(std::dynamic_pointer_cast<IfcStructuralLoadTemperature>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralMember") {
				f(*(std::dynamic_pointer_cast<IfcStructuralMember>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPlanarAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralPlanarAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralPointAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointConnection") {
				f(*(std::dynamic_pointer_cast<IfcStructuralPointConnection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointReaction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralPointReaction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralReaction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralReaction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralResultGroup") {
				f(*(std::dynamic_pointer_cast<IfcStructuralResultGroup>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceAction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceAction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceActivityTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceActivityTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceConnection") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceConnection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMember") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMember>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMemberTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMemberTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMemberVarying") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMemberVarying>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceReaction") {
				f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceReaction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyleAssignmentSelect") {
				f(*(std::dynamic_pointer_cast<IfcStyleAssignmentSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyledItem") {
				f(*(std::dynamic_pointer_cast<IfcStyledItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyledRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcStyledRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyleModel") {
				f(*(std::dynamic_pointer_cast<IfcStyleModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResource") {
				f(*(std::dynamic_pointer_cast<IfcSubContractResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResourceType") {
				f(*(std::dynamic_pointer_cast<IfcSubContractResourceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResourceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSubContractResourceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubedge") {
				f(*(std::dynamic_pointer_cast<IfcSubedge>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurface") {
				f(*(std::dynamic_pointer_cast<IfcSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceCurve") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceCurveSweptAreaSolid") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceCurveSweptAreaSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceFeature") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceFeature>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceFeatureTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceFeatureTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceOfLinearExtrusion") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceOfLinearExtrusion>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceOfRevolution") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceOfRevolution>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceOrFaceSurface") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceOrFaceSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceReinforcementArea") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceReinforcementArea>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceSide") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceSide>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyle") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleElementSelect") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleElementSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleLighting") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleLighting>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleRefraction") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRefraction>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleRendering") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRendering>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleShading") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleShading>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleWithTextures") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceStyleWithTextures>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceTexture") {
				f(*(std::dynamic_pointer_cast<IfcSurfaceTexture>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptAreaSolid") {
				f(*(std::dynamic_pointer_cast<IfcSweptAreaSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptDiskSolid") {
				f(*(std::dynamic_pointer_cast<IfcSweptDiskSolid>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptDiskSolidPolygonal") {
				f(*(std::dynamic_pointer_cast<IfcSweptDiskSolidPolygonal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptSurface") {
				f(*(std::dynamic_pointer_cast<IfcSweptSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDevice") {
				f(*(std::dynamic_pointer_cast<IfcSwitchingDevice>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDeviceType") {
				f(*(std::dynamic_pointer_cast<IfcSwitchingDeviceType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDeviceTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSwitchingDeviceTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystem") {
				f(*(std::dynamic_pointer_cast<IfcSystem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElement") {
				f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElementType") {
				f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTable") {
				f(*(std::dynamic_pointer_cast<IfcTable>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTableColumn") {
				f(*(std::dynamic_pointer_cast<IfcTableColumn>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTableRow") {
				f(*(std::dynamic_pointer_cast<IfcTableRow>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTank") {
				f(*(std::dynamic_pointer_cast<IfcTank>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTankType") {
				f(*(std::dynamic_pointer_cast<IfcTankType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTankTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTankTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTask") {
				f(*(std::dynamic_pointer_cast<IfcTask>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskDurationEnum") {
				f(*(std::dynamic_pointer_cast<IfcTaskDurationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTime") {
				f(*(std::dynamic_pointer_cast<IfcTaskTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTimeRecurring") {
				f(*(std::dynamic_pointer_cast<IfcTaskTimeRecurring>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskType") {
				f(*(std::dynamic_pointer_cast<IfcTaskType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTaskTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTelecomAddress") {
				f(*(std::dynamic_pointer_cast<IfcTelecomAddress>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTemperatureGradientMeasure") {
				f(*(std::dynamic_pointer_cast<IfcTemperatureGradientMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTemperatureRateOfChangeMeasure") {
				f(*(std::dynamic_pointer_cast<IfcTemperatureRateOfChangeMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendon") {
				f(*(std::dynamic_pointer_cast<IfcTendon>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchor") {
				f(*(std::dynamic_pointer_cast<IfcTendonAnchor>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchorType") {
				f(*(std::dynamic_pointer_cast<IfcTendonAnchorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTendonAnchorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonType") {
				f(*(std::dynamic_pointer_cast<IfcTendonType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTendonTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTessellatedFaceSet") {
				f(*(std::dynamic_pointer_cast<IfcTessellatedFaceSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTessellatedItem") {
				f(*(std::dynamic_pointer_cast<IfcTessellatedItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcText") {
				f(*(std::dynamic_pointer_cast<IfcText>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextAlignment") {
				f(*(std::dynamic_pointer_cast<IfcTextAlignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextDecoration") {
				f(*(std::dynamic_pointer_cast<IfcTextDecoration>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextFontName") {
				f(*(std::dynamic_pointer_cast<IfcTextFontName>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextFontSelect") {
				f(*(std::dynamic_pointer_cast<IfcTextFontSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextLiteral") {
				f(*(std::dynamic_pointer_cast<IfcTextLiteral>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextLiteralWithExtent") {
				f(*(std::dynamic_pointer_cast<IfcTextLiteralWithExtent>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextPath") {
				f(*(std::dynamic_pointer_cast<IfcTextPath>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyle") {
				f(*(std::dynamic_pointer_cast<IfcTextStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleFontModel") {
				f(*(std::dynamic_pointer_cast<IfcTextStyleFontModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleForDefinedFont") {
				f(*(std::dynamic_pointer_cast<IfcTextStyleForDefinedFont>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleTextModel") {
				f(*(std::dynamic_pointer_cast<IfcTextStyleTextModel>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextTransformation") {
				f(*(std::dynamic_pointer_cast<IfcTextTransformation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureCoordinate") {
				f(*(std::dynamic_pointer_cast<IfcTextureCoordinate>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureCoordinateGenerator") {
				f(*(std::dynamic_pointer_cast<IfcTextureCoordinateGenerator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureMap") {
				f(*(std::dynamic_pointer_cast<IfcTextureMap>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureVertex") {
				f(*(std::dynamic_pointer_cast<IfcTextureVertex>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureVertexList") {
				f(*(std::dynamic_pointer_cast<IfcTextureVertexList>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalAdmittanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermalAdmittanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalConductivityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermalConductivityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalExpansionCoefficientMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermalExpansionCoefficientMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalResistanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermalResistanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalTransmittanceMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermalTransmittanceMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermodynamicTemperatureMeasure") {
				f(*(std::dynamic_pointer_cast<IfcThermodynamicTemperatureMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTime") {
				f(*(std::dynamic_pointer_cast<IfcTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeMeasure") {
				f(*(std::dynamic_pointer_cast<IfcTimeMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeOrRatioSelect") {
				f(*(std::dynamic_pointer_cast<IfcTimeOrRatioSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimePeriod") {
				f(*(std::dynamic_pointer_cast<IfcTimePeriod>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeries") {
				f(*(std::dynamic_pointer_cast<IfcTimeSeries>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeriesDataTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTimeSeriesDataTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeriesValue") {
				f(*(std::dynamic_pointer_cast<IfcTimeSeriesValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeStamp") {
				f(*(std::dynamic_pointer_cast<IfcTimeStamp>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTopologicalRepresentationItem") {
				f(*(std::dynamic_pointer_cast<IfcTopologicalRepresentationItem>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTopologyRepresentation") {
				f(*(std::dynamic_pointer_cast<IfcTopologyRepresentation>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcToroidalSurface") {
				f(*(std::dynamic_pointer_cast<IfcToroidalSurface>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTorqueMeasure") {
				f(*(std::dynamic_pointer_cast<IfcTorqueMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformer") {
				f(*(std::dynamic_pointer_cast<IfcTransformer>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformerType") {
				f(*(std::dynamic_pointer_cast<IfcTransformerType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformerTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTransformerTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCode") {
				f(*(std::dynamic_pointer_cast<IfcTransitionCode>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCurveSegment2D") {
				f(*(std::dynamic_pointer_cast<IfcTransitionCurveSegment2D>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCurveType") {
				f(*(std::dynamic_pointer_cast<IfcTransitionCurveType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTranslationalStiffnessSelect") {
				f(*(std::dynamic_pointer_cast<IfcTranslationalStiffnessSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElement") {
				f(*(std::dynamic_pointer_cast<IfcTransportElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElementType") {
				f(*(std::dynamic_pointer_cast<IfcTransportElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTransportElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrapeziumProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcTrapeziumProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTriangulatedFaceSet") {
				f(*(std::dynamic_pointer_cast<IfcTriangulatedFaceSet>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTriangulatedIrregularNetwork") {
				f(*(std::dynamic_pointer_cast<IfcTriangulatedIrregularNetwork>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrimmedCurve") {
				f(*(std::dynamic_pointer_cast<IfcTrimmedCurve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrimmingPreference") {
				f(*(std::dynamic_pointer_cast<IfcTrimmingPreference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrimmingSelect") {
				f(*(std::dynamic_pointer_cast<IfcTrimmingSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcTShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundle") {
				f(*(std::dynamic_pointer_cast<IfcTubeBundle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundleType") {
				f(*(std::dynamic_pointer_cast<IfcTubeBundleType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundleTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcTubeBundleTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeObject") {
				f(*(std::dynamic_pointer_cast<IfcTypeObject>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeProcess") {
				f(*(std::dynamic_pointer_cast<IfcTypeProcess>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeProduct") {
				f(*(std::dynamic_pointer_cast<IfcTypeProduct>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeResource") {
				f(*(std::dynamic_pointer_cast<IfcTypeResource>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnit") {
				f(*(std::dynamic_pointer_cast<IfcUnit>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElement") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryControlElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElementType") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryControlElementType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElementTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryControlElementTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipment") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryEquipment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipmentType") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryEquipmentType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipmentTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcUnitaryEquipmentTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitAssignment") {
				f(*(std::dynamic_pointer_cast<IfcUnitAssignment>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitEnum") {
				f(*(std::dynamic_pointer_cast<IfcUnitEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcURIReference") {
				f(*(std::dynamic_pointer_cast<IfcURIReference>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcUShapeProfileDef>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValue") {
				f(*(std::dynamic_pointer_cast<IfcValue>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValve") {
				f(*(std::dynamic_pointer_cast<IfcValve>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValveType") {
				f(*(std::dynamic_pointer_cast<IfcValveType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValveTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcValveTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVaporPermeabilityMeasure") {
				f(*(std::dynamic_pointer_cast<IfcVaporPermeabilityMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVector") {
				f(*(std::dynamic_pointer_cast<IfcVector>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVectorOrDirection") {
				f(*(std::dynamic_pointer_cast<IfcVectorOrDirection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertex") {
				f(*(std::dynamic_pointer_cast<IfcVertex>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertexLoop") {
				f(*(std::dynamic_pointer_cast<IfcVertexLoop>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertexPoint") {
				f(*(std::dynamic_pointer_cast<IfcVertexPoint>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolator") {
				f(*(std::dynamic_pointer_cast<IfcVibrationIsolator>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolatorType") {
				f(*(std::dynamic_pointer_cast<IfcVibrationIsolatorType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolatorTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcVibrationIsolatorTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVirtualElement") {
				f(*(std::dynamic_pointer_cast<IfcVirtualElement>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVirtualGridIntersection") {
				f(*(std::dynamic_pointer_cast<IfcVirtualGridIntersection>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVoidingFeature") {
				f(*(std::dynamic_pointer_cast<IfcVoidingFeature>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVoidingFeatureTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcVoidingFeatureTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVolumeMeasure") {
				f(*(std::dynamic_pointer_cast<IfcVolumeMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVolumetricFlowRateMeasure") {
				f(*(std::dynamic_pointer_cast<IfcVolumetricFlowRateMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWall") {
				f(*(std::dynamic_pointer_cast<IfcWall>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallElementedCase") {
				f(*(std::dynamic_pointer_cast<IfcWallElementedCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcWallStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallType") {
				f(*(std::dynamic_pointer_cast<IfcWallType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWallTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWarpingConstantMeasure") {
				f(*(std::dynamic_pointer_cast<IfcWarpingConstantMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWarpingMomentMeasure") {
				f(*(std::dynamic_pointer_cast<IfcWarpingMomentMeasure>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWarpingStiffnessSelect") {
				f(*(std::dynamic_pointer_cast<IfcWarpingStiffnessSelect>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminal") {
				f(*(std::dynamic_pointer_cast<IfcWasteTerminal>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminalType") {
				f(*(std::dynamic_pointer_cast<IfcWasteTerminalType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminalTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWasteTerminalTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindow") {
				f(*(std::dynamic_pointer_cast<IfcWindow>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowLiningProperties") {
				f(*(std::dynamic_pointer_cast<IfcWindowLiningProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowPanelOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelPositionEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowPanelPositionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelProperties") {
				f(*(std::dynamic_pointer_cast<IfcWindowPanelProperties>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStandardCase") {
				f(*(std::dynamic_pointer_cast<IfcWindowStandardCase>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyle") {
				f(*(std::dynamic_pointer_cast<IfcWindowStyle>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyleConstructionEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowStyleConstructionEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyleOperationEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowStyleOperationEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowType") {
				f(*(std::dynamic_pointer_cast<IfcWindowType>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowTypePartitioningEnum") {
				f(*(std::dynamic_pointer_cast<IfcWindowTypePartitioningEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkCalendar") {
				f(*(std::dynamic_pointer_cast<IfcWorkCalendar>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkCalendarTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWorkCalendarTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkControl") {
				f(*(std::dynamic_pointer_cast<IfcWorkControl>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkPlan") {
				f(*(std::dynamic_pointer_cast<IfcWorkPlan>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkPlanTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWorkPlanTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkSchedule") {
				f(*(std::dynamic_pointer_cast<IfcWorkSchedule>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkScheduleTypeEnum") {
				f(*(std::dynamic_pointer_cast<IfcWorkScheduleTypeEnum>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkTime") {
				f(*(std::dynamic_pointer_cast<IfcWorkTime>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcZone") {
				f(*(std::dynamic_pointer_cast<IfcZone>(ptr)));
				return true;
			}

			if(name == "class OpenInfraPlatform::IfcAlignment1x1::IfcZShapeProfileDef") {
				f(*(std::dynamic_pointer_cast<IfcZShapeProfileDef>(ptr)));
				return true;
			}

			return false;
		}
	}
}
