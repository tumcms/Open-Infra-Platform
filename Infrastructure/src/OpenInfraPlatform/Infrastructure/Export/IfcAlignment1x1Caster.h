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
		template <typename F, typename T> T castAndCall(std::shared_ptr<IfcAlignment1x1Entity> ptr, F &f) {
			std::string name = std::string(typeid(*ptr).name());

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAbsorbedDoseMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAbsorbedDoseMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAccelerationMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAccelerationMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionRequest") {
				return f(*(std::dynamic_pointer_cast<IfcActionRequest>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionRequestTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcActionRequestTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionSourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcActionSourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActionTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcActionTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActor") {
				return f(*(std::dynamic_pointer_cast<IfcActor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActorRole") {
				return f(*(std::dynamic_pointer_cast<IfcActorRole>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuator") {
				return f(*(std::dynamic_pointer_cast<IfcActuator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuatorType") {
				return f(*(std::dynamic_pointer_cast<IfcActuatorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcActuatorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcActuatorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAddress") {
				return f(*(std::dynamic_pointer_cast<IfcAddress>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAddressTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAddressTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedBrep") {
				return f(*(std::dynamic_pointer_cast<IfcAdvancedBrep>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedBrepWithVoids") {
				return f(*(std::dynamic_pointer_cast<IfcAdvancedBrepWithVoids>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAdvancedFace") {
				return f(*(std::dynamic_pointer_cast<IfcAdvancedFace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBox") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminalBox>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBoxType") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminalBoxType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalBoxTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminalBoxTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirTerminalTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAirTerminalTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecovery") {
				return f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecovery>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecoveryType") {
				return f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecoveryType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAirToAirHeatRecoveryTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecoveryTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarm") {
				return f(*(std::dynamic_pointer_cast<IfcAlarm>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarmType") {
				return f(*(std::dynamic_pointer_cast<IfcAlarmType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlarmTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAlarmTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DHorizontal") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DHorizontalSegment") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontalSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DSegment") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegCircularArc") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegCircularArc>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegLine") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegLine>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerSegParabolicArc") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegParabolicArc>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVertical") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DVertical>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignment2DVerticalSegment") {
				return f(*(std::dynamic_pointer_cast<IfcAlignment2DVerticalSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentCurve") {
				return f(*(std::dynamic_pointer_cast<IfcAlignmentCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAlignmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAlignmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAmountOfSubstanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAmountOfSubstanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnalysisModelTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAnalysisModelTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnalysisTheoryTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAnalysisTheoryTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAngularVelocityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAngularVelocityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnnotation") {
				return f(*(std::dynamic_pointer_cast<IfcAnnotation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAnnotationFillArea") {
				return f(*(std::dynamic_pointer_cast<IfcAnnotationFillArea>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApplication") {
				return f(*(std::dynamic_pointer_cast<IfcApplication>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAppliedValue") {
				return f(*(std::dynamic_pointer_cast<IfcAppliedValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApproval") {
				return f(*(std::dynamic_pointer_cast<IfcApproval>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcApprovalRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcApprovalRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryClosedProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcArbitraryClosedProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryOpenProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcArbitraryOpenProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArbitraryProfileDefWithVoids") {
				return f(*(std::dynamic_pointer_cast<IfcArbitraryProfileDefWithVoids>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArcIndex") {
				return f(*(std::dynamic_pointer_cast<IfcArcIndex>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAreaDensityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAreaDensityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAreaMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcAreaMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcArithmeticOperatorEnum") {
				return f(*(std::dynamic_pointer_cast<IfcArithmeticOperatorEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAssemblyPlaceEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAssemblyPlaceEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAsset") {
				return f(*(std::dynamic_pointer_cast<IfcAsset>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAsymmetricIShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcAsymmetricIShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualAppliance") {
				return f(*(std::dynamic_pointer_cast<IfcAudioVisualAppliance>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualApplianceType") {
				return f(*(std::dynamic_pointer_cast<IfcAudioVisualApplianceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAudioVisualApplianceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcAudioVisualApplianceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis1Placement") {
				return f(*(std::dynamic_pointer_cast<IfcAxis1Placement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement2D") {
				return f(*(std::dynamic_pointer_cast<IfcAxis2Placement2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcAxis2Placement3D") {
				return f(*(std::dynamic_pointer_cast<IfcAxis2Placement3D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeam") {
				return f(*(std::dynamic_pointer_cast<IfcBeam>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcBeamStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamType") {
				return f(*(std::dynamic_pointer_cast<IfcBeamType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBeamTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBeamTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBenchmarkEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBenchmarkEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBinary") {
				return f(*(std::dynamic_pointer_cast<IfcBinary>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBlobTexture") {
				return f(*(std::dynamic_pointer_cast<IfcBlobTexture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBlock") {
				return f(*(std::dynamic_pointer_cast<IfcBlock>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoiler") {
				return f(*(std::dynamic_pointer_cast<IfcBoiler>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoilerType") {
				return f(*(std::dynamic_pointer_cast<IfcBoilerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoilerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBoilerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoolean") {
				return f(*(std::dynamic_pointer_cast<IfcBoolean>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanClippingResult") {
				return f(*(std::dynamic_pointer_cast<IfcBooleanClippingResult>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanOperator") {
				return f(*(std::dynamic_pointer_cast<IfcBooleanOperator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBooleanResult") {
				return f(*(std::dynamic_pointer_cast<IfcBooleanResult>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryCondition") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryCurve") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryEdgeCondition") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryEdgeCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryFaceCondition") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryFaceCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryNodeCondition") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryNodeCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundaryNodeConditionWarping") {
				return f(*(std::dynamic_pointer_cast<IfcBoundaryNodeConditionWarping>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundedCurve") {
				return f(*(std::dynamic_pointer_cast<IfcBoundedCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundedSurface") {
				return f(*(std::dynamic_pointer_cast<IfcBoundedSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoundingBox") {
				return f(*(std::dynamic_pointer_cast<IfcBoundingBox>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoxAlignment") {
				return f(*(std::dynamic_pointer_cast<IfcBoxAlignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBoxedHalfSpace") {
				return f(*(std::dynamic_pointer_cast<IfcBoxedHalfSpace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurve") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurveForm") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineCurveForm>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineCurveWithKnots") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineCurveWithKnots>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurface") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurfaceForm") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineSurfaceForm>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBSplineSurfaceWithKnots") {
				return f(*(std::dynamic_pointer_cast<IfcBSplineSurfaceWithKnots>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuilding") {
				return f(*(std::dynamic_pointer_cast<IfcBuilding>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElement") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPart") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementPart>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPartType") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementPartType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementPartTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementPartTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxy") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementProxy>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxyType") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementProxyType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementProxyTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementProxyTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingElementType") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingStorey") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingStorey>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingSystem") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingSystem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBuildingSystemTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBuildingSystemTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurner") {
				return f(*(std::dynamic_pointer_cast<IfcBurner>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurnerType") {
				return f(*(std::dynamic_pointer_cast<IfcBurnerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcBurnerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcBurnerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFitting") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierFitting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFittingType") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierFittingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierFittingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierFittingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegment") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegmentType") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierSegmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableCarrierSegmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCableCarrierSegmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFitting") {
				return f(*(std::dynamic_pointer_cast<IfcCableFitting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFittingType") {
				return f(*(std::dynamic_pointer_cast<IfcCableFittingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableFittingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCableFittingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegment") {
				return f(*(std::dynamic_pointer_cast<IfcCableSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegmentType") {
				return f(*(std::dynamic_pointer_cast<IfcCableSegmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCableSegmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCableSegmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCardinalPointReference") {
				return f(*(std::dynamic_pointer_cast<IfcCardinalPointReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPoint") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianPoint>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianPointList>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList2D") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianPointList2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList2DLabelled") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianPointList2DLabelled>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianPointList3D") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianPointList3D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2D") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator2DnonUniform") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2DnonUniform>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator3D") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCartesianTransformationOperator3DnonUniform") {
				return f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3DnonUniform>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCenterLineProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcCenterLineProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChangeActionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcChangeActionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChiller") {
				return f(*(std::dynamic_pointer_cast<IfcChiller>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChillerType") {
				return f(*(std::dynamic_pointer_cast<IfcChillerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChillerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcChillerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimney") {
				return f(*(std::dynamic_pointer_cast<IfcChimney>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimneyType") {
				return f(*(std::dynamic_pointer_cast<IfcChimneyType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcChimneyTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcChimneyTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircle") {
				return f(*(std::dynamic_pointer_cast<IfcCircle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircleHollowProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcCircleHollowProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircleProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcCircleProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCircularArcSegment2D") {
				return f(*(std::dynamic_pointer_cast<IfcCircularArcSegment2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCivilElement") {
				return f(*(std::dynamic_pointer_cast<IfcCivilElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCivilElementType") {
				return f(*(std::dynamic_pointer_cast<IfcCivilElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassification") {
				return f(*(std::dynamic_pointer_cast<IfcClassification>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClassificationReference") {
				return f(*(std::dynamic_pointer_cast<IfcClassificationReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClosedShell") {
				return f(*(std::dynamic_pointer_cast<IfcClosedShell>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcClothoidalArcSegment2D") {
				return f(*(std::dynamic_pointer_cast<IfcClothoidalArcSegment2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoil") {
				return f(*(std::dynamic_pointer_cast<IfcCoil>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoilType") {
				return f(*(std::dynamic_pointer_cast<IfcCoilType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoilTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCoilTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourRgb") {
				return f(*(std::dynamic_pointer_cast<IfcColourRgb>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourRgbList") {
				return f(*(std::dynamic_pointer_cast<IfcColourRgbList>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColourSpecification") {
				return f(*(std::dynamic_pointer_cast<IfcColourSpecification>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumn") {
				return f(*(std::dynamic_pointer_cast<IfcColumn>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcColumnStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnType") {
				return f(*(std::dynamic_pointer_cast<IfcColumnType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcColumnTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcColumnTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsAppliance") {
				return f(*(std::dynamic_pointer_cast<IfcCommunicationsAppliance>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsApplianceType") {
				return f(*(std::dynamic_pointer_cast<IfcCommunicationsApplianceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCommunicationsApplianceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCommunicationsApplianceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexNumber") {
				return f(*(std::dynamic_pointer_cast<IfcComplexNumber>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexProperty") {
				return f(*(std::dynamic_pointer_cast<IfcComplexProperty>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexPropertyTemplate") {
				return f(*(std::dynamic_pointer_cast<IfcComplexPropertyTemplate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcComplexPropertyTemplateTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcComplexPropertyTemplateTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurve") {
				return f(*(std::dynamic_pointer_cast<IfcCompositeCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurveOnSurface") {
				return f(*(std::dynamic_pointer_cast<IfcCompositeCurveOnSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeCurveSegment") {
				return f(*(std::dynamic_pointer_cast<IfcCompositeCurveSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompositeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcCompositeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompoundPlaneAngleMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcCompoundPlaneAngleMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressor") {
				return f(*(std::dynamic_pointer_cast<IfcCompressor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressorType") {
				return f(*(std::dynamic_pointer_cast<IfcCompressorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCompressorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCompressorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenser") {
				return f(*(std::dynamic_pointer_cast<IfcCondenser>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenserType") {
				return f(*(std::dynamic_pointer_cast<IfcCondenserType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCondenserTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCondenserTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConic") {
				return f(*(std::dynamic_pointer_cast<IfcConic>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectedFaceSet") {
				return f(*(std::dynamic_pointer_cast<IfcConnectedFaceSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionCurveGeometry") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionCurveGeometry>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionGeometry") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionGeometry>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionPointEccentricity") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionPointEccentricity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionPointGeometry") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionPointGeometry>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionSurfaceGeometry") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionSurfaceGeometry>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConnectionVolumeGeometry") {
				return f(*(std::dynamic_pointer_cast<IfcConnectionVolumeGeometry>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstraint") {
				return f(*(std::dynamic_pointer_cast<IfcConstraint>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstraintEnum") {
				return f(*(std::dynamic_pointer_cast<IfcConstraintEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResource") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionEquipmentResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResource") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionMaterialResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResource") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionProductResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionProductResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionProductResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionProductResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionResource") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConstructionResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcConstructionResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContext") {
				return f(*(std::dynamic_pointer_cast<IfcContext>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContextDependentMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcContextDependentMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcContextDependentUnit") {
				return f(*(std::dynamic_pointer_cast<IfcContextDependentUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControl") {
				return f(*(std::dynamic_pointer_cast<IfcControl>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcController") {
				return f(*(std::dynamic_pointer_cast<IfcController>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControllerType") {
				return f(*(std::dynamic_pointer_cast<IfcControllerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcControllerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcControllerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConversionBasedUnit") {
				return f(*(std::dynamic_pointer_cast<IfcConversionBasedUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcConversionBasedUnitWithOffset") {
				return f(*(std::dynamic_pointer_cast<IfcConversionBasedUnitWithOffset>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeam") {
				return f(*(std::dynamic_pointer_cast<IfcCooledBeam>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeamType") {
				return f(*(std::dynamic_pointer_cast<IfcCooledBeamType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCooledBeamTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCooledBeamTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTower") {
				return f(*(std::dynamic_pointer_cast<IfcCoolingTower>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTowerType") {
				return f(*(std::dynamic_pointer_cast<IfcCoolingTowerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoolingTowerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCoolingTowerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoordinateOperation") {
				return f(*(std::dynamic_pointer_cast<IfcCoordinateOperation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoordinateReferenceSystem") {
				return f(*(std::dynamic_pointer_cast<IfcCoordinateReferenceSystem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostItem") {
				return f(*(std::dynamic_pointer_cast<IfcCostItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostItemTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCostItemTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostSchedule") {
				return f(*(std::dynamic_pointer_cast<IfcCostSchedule>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostScheduleTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCostScheduleTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCostValue") {
				return f(*(std::dynamic_pointer_cast<IfcCostValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCountMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcCountMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCovering") {
				return f(*(std::dynamic_pointer_cast<IfcCovering>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoveringType") {
				return f(*(std::dynamic_pointer_cast<IfcCoveringType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCoveringTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCoveringTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResource") {
				return f(*(std::dynamic_pointer_cast<IfcCrewResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcCrewResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCrewResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCrewResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCsgPrimitive3D") {
				return f(*(std::dynamic_pointer_cast<IfcCsgPrimitive3D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCsgSolid") {
				return f(*(std::dynamic_pointer_cast<IfcCsgSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcCShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurrencyRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcCurrencyRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWall") {
				return f(*(std::dynamic_pointer_cast<IfcCurtainWall>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWallType") {
				return f(*(std::dynamic_pointer_cast<IfcCurtainWallType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurtainWallTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCurtainWallTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurvatureMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcCurvatureMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurve") {
				return f(*(std::dynamic_pointer_cast<IfcCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveBoundedPlane") {
				return f(*(std::dynamic_pointer_cast<IfcCurveBoundedPlane>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveBoundedSurface") {
				return f(*(std::dynamic_pointer_cast<IfcCurveBoundedSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveInterpolationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcCurveInterpolationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveSegment2D") {
				return f(*(std::dynamic_pointer_cast<IfcCurveSegment2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyle") {
				return f(*(std::dynamic_pointer_cast<IfcCurveStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFont") {
				return f(*(std::dynamic_pointer_cast<IfcCurveStyleFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFontAndScaling") {
				return f(*(std::dynamic_pointer_cast<IfcCurveStyleFontAndScaling>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCurveStyleFontPattern") {
				return f(*(std::dynamic_pointer_cast<IfcCurveStyleFontPattern>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcCylindricalSurface") {
				return f(*(std::dynamic_pointer_cast<IfcCylindricalSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamper") {
				return f(*(std::dynamic_pointer_cast<IfcDamper>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamperType") {
				return f(*(std::dynamic_pointer_cast<IfcDamperType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDamperTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDamperTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDataOriginEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDataOriginEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDate") {
				return f(*(std::dynamic_pointer_cast<IfcDate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDateTime") {
				return f(*(std::dynamic_pointer_cast<IfcDateTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDayInMonthNumber") {
				return f(*(std::dynamic_pointer_cast<IfcDayInMonthNumber>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDayInWeekNumber") {
				return f(*(std::dynamic_pointer_cast<IfcDayInWeekNumber>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcDerivedProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnit") {
				return f(*(std::dynamic_pointer_cast<IfcDerivedUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnitElement") {
				return f(*(std::dynamic_pointer_cast<IfcDerivedUnitElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDerivedUnitEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDerivedUnitEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDescriptiveMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcDescriptiveMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDimensionalExponents") {
				return f(*(std::dynamic_pointer_cast<IfcDimensionalExponents>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDimensionCount") {
				return f(*(std::dynamic_pointer_cast<IfcDimensionCount>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDirection") {
				return f(*(std::dynamic_pointer_cast<IfcDirection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDirectionSenseEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDirectionSenseEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessory") {
				return f(*(std::dynamic_pointer_cast<IfcDiscreteAccessory>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessoryType") {
				return f(*(std::dynamic_pointer_cast<IfcDiscreteAccessoryType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDiscreteAccessoryTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDiscreteAccessoryTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistanceExpression") {
				return f(*(std::dynamic_pointer_cast<IfcDistanceExpression>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElement") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionChamberElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElementType") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionChamberElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionChamberElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionChamberElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionCircuit") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionCircuit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionControlElement") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionControlElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionControlElementType") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionControlElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionElement") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionElementType") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionFlowElement") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionFlowElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionFlowElementType") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionFlowElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionPort") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionPort>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionPortTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionPortTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionSystem") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionSystem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDistributionSystemEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDistributionSystemEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentConfidentialityEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDocumentConfidentialityEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentInformation") {
				return f(*(std::dynamic_pointer_cast<IfcDocumentInformation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentInformationRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcDocumentInformationRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentReference") {
				return f(*(std::dynamic_pointer_cast<IfcDocumentReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDocumentStatusEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDocumentStatusEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoor") {
				return f(*(std::dynamic_pointer_cast<IfcDoor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorLiningProperties") {
				return f(*(std::dynamic_pointer_cast<IfcDoorLiningProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorPanelOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelPositionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorPanelPositionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorPanelProperties") {
				return f(*(std::dynamic_pointer_cast<IfcDoorPanelProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcDoorStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyle") {
				return f(*(std::dynamic_pointer_cast<IfcDoorStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyleConstructionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorStyleConstructionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorStyleOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorStyleOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorType") {
				return f(*(std::dynamic_pointer_cast<IfcDoorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoorTypeOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDoorTypeOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDoseEquivalentMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcDoseEquivalentMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDraughtingPreDefinedColour") {
				return f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedColour>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDraughtingPreDefinedCurveFont") {
				return f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedCurveFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFitting") {
				return f(*(std::dynamic_pointer_cast<IfcDuctFitting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFittingType") {
				return f(*(std::dynamic_pointer_cast<IfcDuctFittingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctFittingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDuctFittingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegment") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegmentType") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSegmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSegmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSegmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencer") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSilencer>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencerType") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSilencerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuctSilencerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcDuctSilencerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDuration") {
				return f(*(std::dynamic_pointer_cast<IfcDuration>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcDynamicViscosityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcDynamicViscosityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdge") {
				return f(*(std::dynamic_pointer_cast<IfcEdge>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdgeCurve") {
				return f(*(std::dynamic_pointer_cast<IfcEdgeCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEdgeLoop") {
				return f(*(std::dynamic_pointer_cast<IfcEdgeLoop>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricAppliance") {
				return f(*(std::dynamic_pointer_cast<IfcElectricAppliance>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricApplianceType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricApplianceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricApplianceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricApplianceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricCapacitanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricCapacitanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricChargeMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricChargeMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricConductanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricConductanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricCurrentMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricCurrentMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoard") {
				return f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoard>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoardType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoardType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricDistributionBoardTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoardTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDevice") {
				return f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricFlowStorageDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGenerator") {
				return f(*(std::dynamic_pointer_cast<IfcElectricGenerator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGeneratorType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricGeneratorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricGeneratorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricGeneratorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotor") {
				return f(*(std::dynamic_pointer_cast<IfcElectricMotor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotorType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricMotorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricMotorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricMotorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricResistanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricResistanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControl") {
				return f(*(std::dynamic_pointer_cast<IfcElectricTimeControl>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControlType") {
				return f(*(std::dynamic_pointer_cast<IfcElectricTimeControlType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricTimeControlTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElectricTimeControlTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElectricVoltageMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcElectricVoltageMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElement") {
				return f(*(std::dynamic_pointer_cast<IfcElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementarySurface") {
				return f(*(std::dynamic_pointer_cast<IfcElementarySurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssembly") {
				return f(*(std::dynamic_pointer_cast<IfcElementAssembly>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssemblyType") {
				return f(*(std::dynamic_pointer_cast<IfcElementAssemblyType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementAssemblyTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElementAssemblyTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementComponent") {
				return f(*(std::dynamic_pointer_cast<IfcElementComponent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementComponentType") {
				return f(*(std::dynamic_pointer_cast<IfcElementComponentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementCompositionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcElementCompositionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementQuantity") {
				return f(*(std::dynamic_pointer_cast<IfcElementQuantity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcElementType") {
				return f(*(std::dynamic_pointer_cast<IfcElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEllipse") {
				return f(*(std::dynamic_pointer_cast<IfcEllipse>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEllipseProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcEllipseProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyConversionDevice") {
				return f(*(std::dynamic_pointer_cast<IfcEnergyConversionDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyConversionDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcEnergyConversionDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEnergyMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcEnergyMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngine") {
				return f(*(std::dynamic_pointer_cast<IfcEngine>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngineType") {
				return f(*(std::dynamic_pointer_cast<IfcEngineType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEngineTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcEngineTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCooler") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporativeCooler>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCoolerType") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporativeCoolerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporativeCoolerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporativeCoolerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporator") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporatorType") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporatorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvaporatorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcEvaporatorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEvent") {
				return f(*(std::dynamic_pointer_cast<IfcEvent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTime") {
				return f(*(std::dynamic_pointer_cast<IfcEventTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTriggerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcEventTriggerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventType") {
				return f(*(std::dynamic_pointer_cast<IfcEventType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcEventTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcEventTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtendedProperties") {
				return f(*(std::dynamic_pointer_cast<IfcExtendedProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalInformation") {
				return f(*(std::dynamic_pointer_cast<IfcExternalInformation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedHatchStyle") {
				return f(*(std::dynamic_pointer_cast<IfcExternallyDefinedHatchStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedSurfaceStyle") {
				return f(*(std::dynamic_pointer_cast<IfcExternallyDefinedSurfaceStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternallyDefinedTextFont") {
				return f(*(std::dynamic_pointer_cast<IfcExternallyDefinedTextFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalReference") {
				return f(*(std::dynamic_pointer_cast<IfcExternalReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalReferenceRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcExternalReferenceRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialElement") {
				return f(*(std::dynamic_pointer_cast<IfcExternalSpatialElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcExternalSpatialElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExternalSpatialStructureElement") {
				return f(*(std::dynamic_pointer_cast<IfcExternalSpatialStructureElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtrudedAreaSolid") {
				return f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcExtrudedAreaSolidTapered") {
				return f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolidTapered>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFace") {
				return f(*(std::dynamic_pointer_cast<IfcFace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceBasedSurfaceModel") {
				return f(*(std::dynamic_pointer_cast<IfcFaceBasedSurfaceModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceBound") {
				return f(*(std::dynamic_pointer_cast<IfcFaceBound>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceOuterBound") {
				return f(*(std::dynamic_pointer_cast<IfcFaceOuterBound>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFaceSurface") {
				return f(*(std::dynamic_pointer_cast<IfcFaceSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFacetedBrep") {
				return f(*(std::dynamic_pointer_cast<IfcFacetedBrep>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFacetedBrepWithVoids") {
				return f(*(std::dynamic_pointer_cast<IfcFacetedBrepWithVoids>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFailureConnectionCondition") {
				return f(*(std::dynamic_pointer_cast<IfcFailureConnectionCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFan") {
				return f(*(std::dynamic_pointer_cast<IfcFan>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFanType") {
				return f(*(std::dynamic_pointer_cast<IfcFanType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFanTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFanTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastener") {
				return f(*(std::dynamic_pointer_cast<IfcFastener>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastenerType") {
				return f(*(std::dynamic_pointer_cast<IfcFastenerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFastenerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFastenerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElement") {
				return f(*(std::dynamic_pointer_cast<IfcFeatureElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElementAddition") {
				return f(*(std::dynamic_pointer_cast<IfcFeatureElementAddition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFeatureElementSubtraction") {
				return f(*(std::dynamic_pointer_cast<IfcFeatureElementSubtraction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyle") {
				return f(*(std::dynamic_pointer_cast<IfcFillAreaStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyleHatching") {
				return f(*(std::dynamic_pointer_cast<IfcFillAreaStyleHatching>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFillAreaStyleTiles") {
				return f(*(std::dynamic_pointer_cast<IfcFillAreaStyleTiles>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilter") {
				return f(*(std::dynamic_pointer_cast<IfcFilter>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilterType") {
				return f(*(std::dynamic_pointer_cast<IfcFilterType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFilterTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFilterTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFireSuppressionTerminalTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminalTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFixedReferenceSweptAreaSolid") {
				return f(*(std::dynamic_pointer_cast<IfcFixedReferenceSweptAreaSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowController") {
				return f(*(std::dynamic_pointer_cast<IfcFlowController>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowControllerType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowControllerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowDirectionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFlowDirectionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowFitting") {
				return f(*(std::dynamic_pointer_cast<IfcFlowFitting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowFittingType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowFittingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrument") {
				return f(*(std::dynamic_pointer_cast<IfcFlowInstrument>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrumentType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowInstrumentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowInstrumentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFlowInstrumentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeter") {
				return f(*(std::dynamic_pointer_cast<IfcFlowMeter>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeterType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowMeterType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMeterTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFlowMeterTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMovingDevice") {
				return f(*(std::dynamic_pointer_cast<IfcFlowMovingDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowMovingDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowMovingDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowSegment") {
				return f(*(std::dynamic_pointer_cast<IfcFlowSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowSegmentType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowSegmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowStorageDevice") {
				return f(*(std::dynamic_pointer_cast<IfcFlowStorageDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowStorageDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowStorageDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcFlowTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTreatmentDevice") {
				return f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFlowTreatmentDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontStyle") {
				return f(*(std::dynamic_pointer_cast<IfcFontStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontVariant") {
				return f(*(std::dynamic_pointer_cast<IfcFontVariant>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFontWeight") {
				return f(*(std::dynamic_pointer_cast<IfcFontWeight>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFooting") {
				return f(*(std::dynamic_pointer_cast<IfcFooting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFootingType") {
				return f(*(std::dynamic_pointer_cast<IfcFootingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFootingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFootingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcForceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcForceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFrequencyMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcFrequencyMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnishingElement") {
				return f(*(std::dynamic_pointer_cast<IfcFurnishingElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnishingElementType") {
				return f(*(std::dynamic_pointer_cast<IfcFurnishingElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurniture") {
				return f(*(std::dynamic_pointer_cast<IfcFurniture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnitureType") {
				return f(*(std::dynamic_pointer_cast<IfcFurnitureType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcFurnitureTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcFurnitureTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElement") {
				return f(*(std::dynamic_pointer_cast<IfcGeographicElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElementType") {
				return f(*(std::dynamic_pointer_cast<IfcGeographicElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeographicElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcGeographicElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricCurveSet") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricCurveSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricProjectionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricProjectionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationContext") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationContext>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationItem") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricRepresentationSubContext") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationSubContext>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGeometricSet") {
				return f(*(std::dynamic_pointer_cast<IfcGeometricSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGloballyUniqueId") {
				return f(*(std::dynamic_pointer_cast<IfcGloballyUniqueId>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGlobalOrLocalEnum") {
				return f(*(std::dynamic_pointer_cast<IfcGlobalOrLocalEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGrid") {
				return f(*(std::dynamic_pointer_cast<IfcGrid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridAxis") {
				return f(*(std::dynamic_pointer_cast<IfcGridAxis>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridPlacement") {
				return f(*(std::dynamic_pointer_cast<IfcGridPlacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGridTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcGridTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcGroup") {
				return f(*(std::dynamic_pointer_cast<IfcGroup>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHalfSpaceSolid") {
				return f(*(std::dynamic_pointer_cast<IfcHalfSpaceSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchanger") {
				return f(*(std::dynamic_pointer_cast<IfcHeatExchanger>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchangerType") {
				return f(*(std::dynamic_pointer_cast<IfcHeatExchangerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatExchangerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcHeatExchangerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatFluxDensityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcHeatFluxDensityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHeatingValueMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcHeatingValueMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifier") {
				return f(*(std::dynamic_pointer_cast<IfcHumidifier>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifierType") {
				return f(*(std::dynamic_pointer_cast<IfcHumidifierType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcHumidifierTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcHumidifierTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIdentifier") {
				return f(*(std::dynamic_pointer_cast<IfcIdentifier>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIlluminanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcIlluminanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcImageTexture") {
				return f(*(std::dynamic_pointer_cast<IfcImageTexture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedColourMap") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedColourMap>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolyCurve") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedPolyCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolygonalFace") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedPolygonalFaceWithVoids") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFaceWithVoids>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedTextureMap") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedTextureMap>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIndexedTriangleTextureMap") {
				return f(*(std::dynamic_pointer_cast<IfcIndexedTriangleTextureMap>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInductanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcInductanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInteger") {
				return f(*(std::dynamic_pointer_cast<IfcInteger>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIntegerCountRateMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcIntegerCountRateMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptor") {
				return f(*(std::dynamic_pointer_cast<IfcInterceptor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptorType") {
				return f(*(std::dynamic_pointer_cast<IfcInterceptorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInterceptorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcInterceptorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInternalOrExternalEnum") {
				return f(*(std::dynamic_pointer_cast<IfcInternalOrExternalEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIntersectionCurve") {
				return f(*(std::dynamic_pointer_cast<IfcIntersectionCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInventory") {
				return f(*(std::dynamic_pointer_cast<IfcInventory>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcInventoryTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcInventoryTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIonConcentrationMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcIonConcentrationMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIrregularTimeSeries") {
				return f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeries>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIrregularTimeSeriesValue") {
				return f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeriesValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcIShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcIsothermalMoistureCapacityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcIsothermalMoistureCapacityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBox") {
				return f(*(std::dynamic_pointer_cast<IfcJunctionBox>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBoxType") {
				return f(*(std::dynamic_pointer_cast<IfcJunctionBoxType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcJunctionBoxTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcJunctionBoxTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcKinematicViscosityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcKinematicViscosityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcKnotType") {
				return f(*(std::dynamic_pointer_cast<IfcKnotType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLabel") {
				return f(*(std::dynamic_pointer_cast<IfcLabel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResource") {
				return f(*(std::dynamic_pointer_cast<IfcLaborResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcLaborResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLaborResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLaborResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLagTime") {
				return f(*(std::dynamic_pointer_cast<IfcLagTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLamp") {
				return f(*(std::dynamic_pointer_cast<IfcLamp>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLampType") {
				return f(*(std::dynamic_pointer_cast<IfcLampType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLampTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLampTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLanguageId") {
				return f(*(std::dynamic_pointer_cast<IfcLanguageId>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLayerSetDirectionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLayerSetDirectionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLengthMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLengthMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLibraryInformation") {
				return f(*(std::dynamic_pointer_cast<IfcLibraryInformation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLibraryReference") {
				return f(*(std::dynamic_pointer_cast<IfcLibraryReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightDistributionCurveEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLightDistributionCurveEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightDistributionData") {
				return f(*(std::dynamic_pointer_cast<IfcLightDistributionData>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightEmissionSourceEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLightEmissionSourceEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixture") {
				return f(*(std::dynamic_pointer_cast<IfcLightFixture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixtureType") {
				return f(*(std::dynamic_pointer_cast<IfcLightFixtureType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightFixtureTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLightFixtureTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightIntensityDistribution") {
				return f(*(std::dynamic_pointer_cast<IfcLightIntensityDistribution>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSource") {
				return f(*(std::dynamic_pointer_cast<IfcLightSource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceAmbient") {
				return f(*(std::dynamic_pointer_cast<IfcLightSourceAmbient>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceDirectional") {
				return f(*(std::dynamic_pointer_cast<IfcLightSourceDirectional>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceGoniometric") {
				return f(*(std::dynamic_pointer_cast<IfcLightSourceGoniometric>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourcePositional") {
				return f(*(std::dynamic_pointer_cast<IfcLightSourcePositional>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLightSourceSpot") {
				return f(*(std::dynamic_pointer_cast<IfcLightSourceSpot>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLine") {
				return f(*(std::dynamic_pointer_cast<IfcLine>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearForceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLinearForceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearMomentMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLinearMomentMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearPlacement") {
				return f(*(std::dynamic_pointer_cast<IfcLinearPlacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearPositioningElement") {
				return f(*(std::dynamic_pointer_cast<IfcLinearPositioningElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearStiffnessMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLinearStiffnessMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLinearVelocityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLinearVelocityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLineIndex") {
				return f(*(std::dynamic_pointer_cast<IfcLineIndex>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLineSegment2D") {
				return f(*(std::dynamic_pointer_cast<IfcLineSegment2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLoadGroupTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLoadGroupTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLocalPlacement") {
				return f(*(std::dynamic_pointer_cast<IfcLocalPlacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLogical") {
				return f(*(std::dynamic_pointer_cast<IfcLogical>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLogicalOperatorEnum") {
				return f(*(std::dynamic_pointer_cast<IfcLogicalOperatorEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLoop") {
				return f(*(std::dynamic_pointer_cast<IfcLoop>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcLShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousFluxMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLuminousFluxMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousIntensityDistributionMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLuminousIntensityDistributionMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcLuminousIntensityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcLuminousIntensityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMagneticFluxDensityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMagneticFluxDensityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMagneticFluxMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMagneticFluxMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcManifoldSolidBrep") {
				return f(*(std::dynamic_pointer_cast<IfcManifoldSolidBrep>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMapConversion") {
				return f(*(std::dynamic_pointer_cast<IfcMapConversion>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMappedItem") {
				return f(*(std::dynamic_pointer_cast<IfcMappedItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassDensityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMassDensityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassFlowRateMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMassFlowRateMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMassMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMassPerLengthMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMassPerLengthMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterial") {
				return f(*(std::dynamic_pointer_cast<IfcMaterial>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialClassificationRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialClassificationRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialConstituent") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialConstituent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialConstituentSet") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialConstituentSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialDefinitionRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialDefinitionRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayer") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialLayer>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerSet") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialLayerSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerSetUsage") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialLayerSetUsage>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialLayerWithOffsets") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialLayerWithOffsets>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialList") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialList>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfile") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProfile>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSet") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProfileSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSetUsage") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsage>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileSetUsageTapering") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsageTapering>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProfileWithOffsets") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProfileWithOffsets>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialProperties") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMaterialUsageDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcMaterialUsageDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMeasureWithUnit") {
				return f(*(std::dynamic_pointer_cast<IfcMeasureWithUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastener") {
				return f(*(std::dynamic_pointer_cast<IfcMechanicalFastener>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastenerType") {
				return f(*(std::dynamic_pointer_cast<IfcMechanicalFastenerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMechanicalFastenerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcMechanicalFastenerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDevice") {
				return f(*(std::dynamic_pointer_cast<IfcMedicalDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcMedicalDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMedicalDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcMedicalDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMember") {
				return f(*(std::dynamic_pointer_cast<IfcMember>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcMemberStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberType") {
				return f(*(std::dynamic_pointer_cast<IfcMemberType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMemberTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcMemberTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMetric") {
				return f(*(std::dynamic_pointer_cast<IfcMetric>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMirroredProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcMirroredProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfElasticityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcModulusOfElasticityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfLinearSubgradeReactionMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcModulusOfLinearSubgradeReactionMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfRotationalSubgradeReactionMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcModulusOfRotationalSubgradeReactionMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcModulusOfSubgradeReactionMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcModulusOfSubgradeReactionMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMoistureDiffusivityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMoistureDiffusivityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMolecularWeightMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMolecularWeightMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMomentOfInertiaMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMomentOfInertiaMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonetaryMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcMonetaryMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonetaryUnit") {
				return f(*(std::dynamic_pointer_cast<IfcMonetaryUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMonthInYearNumber") {
				return f(*(std::dynamic_pointer_cast<IfcMonthInYearNumber>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnection") {
				return f(*(std::dynamic_pointer_cast<IfcMotorConnection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnectionType") {
				return f(*(std::dynamic_pointer_cast<IfcMotorConnectionType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcMotorConnectionTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcMotorConnectionTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNamedUnit") {
				return f(*(std::dynamic_pointer_cast<IfcNamedUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNonNegativeLengthMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcNonNegativeLengthMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNormalisedRatioMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcNormalisedRatioMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNullStyle") {
				return f(*(std::dynamic_pointer_cast<IfcNullStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcNumericMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcNumericMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObject") {
				return f(*(std::dynamic_pointer_cast<IfcObject>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcObjectDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjective") {
				return f(*(std::dynamic_pointer_cast<IfcObjective>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectiveEnum") {
				return f(*(std::dynamic_pointer_cast<IfcObjectiveEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectPlacement") {
				return f(*(std::dynamic_pointer_cast<IfcObjectPlacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcObjectTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcObjectTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOccupant") {
				return f(*(std::dynamic_pointer_cast<IfcOccupant>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOccupantTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcOccupantTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve") {
				return f(*(std::dynamic_pointer_cast<IfcOffsetCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve2D") {
				return f(*(std::dynamic_pointer_cast<IfcOffsetCurve2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurve3D") {
				return f(*(std::dynamic_pointer_cast<IfcOffsetCurve3D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOffsetCurveByDistances") {
				return f(*(std::dynamic_pointer_cast<IfcOffsetCurveByDistances>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningElement") {
				return f(*(std::dynamic_pointer_cast<IfcOpeningElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcOpeningElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpeningStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcOpeningStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOpenShell") {
				return f(*(std::dynamic_pointer_cast<IfcOpenShell>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrganization") {
				return f(*(std::dynamic_pointer_cast<IfcOrganization>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrganizationRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcOrganizationRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrientationExpression") {
				return f(*(std::dynamic_pointer_cast<IfcOrientationExpression>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOrientedEdge") {
				return f(*(std::dynamic_pointer_cast<IfcOrientedEdge>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOuterBoundaryCurve") {
				return f(*(std::dynamic_pointer_cast<IfcOuterBoundaryCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutlet") {
				return f(*(std::dynamic_pointer_cast<IfcOutlet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutletType") {
				return f(*(std::dynamic_pointer_cast<IfcOutletType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOutletTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcOutletTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcOwnerHistory") {
				return f(*(std::dynamic_pointer_cast<IfcOwnerHistory>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcParameterizedProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcParameterizedProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcParameterValue") {
				return f(*(std::dynamic_pointer_cast<IfcParameterValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPath") {
				return f(*(std::dynamic_pointer_cast<IfcPath>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPcurve") {
				return f(*(std::dynamic_pointer_cast<IfcPcurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerformanceHistory") {
				return f(*(std::dynamic_pointer_cast<IfcPerformanceHistory>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerformanceHistoryTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPerformanceHistoryTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermeableCoveringOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPermeableCoveringOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermeableCoveringProperties") {
				return f(*(std::dynamic_pointer_cast<IfcPermeableCoveringProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermit") {
				return f(*(std::dynamic_pointer_cast<IfcPermit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPermitTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPermitTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPerson") {
				return f(*(std::dynamic_pointer_cast<IfcPerson>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPersonAndOrganization") {
				return f(*(std::dynamic_pointer_cast<IfcPersonAndOrganization>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPHMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPHMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalComplexQuantity") {
				return f(*(std::dynamic_pointer_cast<IfcPhysicalComplexQuantity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalOrVirtualEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPhysicalOrVirtualEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalQuantity") {
				return f(*(std::dynamic_pointer_cast<IfcPhysicalQuantity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPhysicalSimpleQuantity") {
				return f(*(std::dynamic_pointer_cast<IfcPhysicalSimpleQuantity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPile") {
				return f(*(std::dynamic_pointer_cast<IfcPile>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileConstructionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPileConstructionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileType") {
				return f(*(std::dynamic_pointer_cast<IfcPileType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPileTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPileTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFitting") {
				return f(*(std::dynamic_pointer_cast<IfcPipeFitting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFittingType") {
				return f(*(std::dynamic_pointer_cast<IfcPipeFittingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeFittingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPipeFittingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegment") {
				return f(*(std::dynamic_pointer_cast<IfcPipeSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegmentType") {
				return f(*(std::dynamic_pointer_cast<IfcPipeSegmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPipeSegmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPipeSegmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPixelTexture") {
				return f(*(std::dynamic_pointer_cast<IfcPixelTexture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlacement") {
				return f(*(std::dynamic_pointer_cast<IfcPlacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarBox") {
				return f(*(std::dynamic_pointer_cast<IfcPlanarBox>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarExtent") {
				return f(*(std::dynamic_pointer_cast<IfcPlanarExtent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlanarForceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPlanarForceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlane") {
				return f(*(std::dynamic_pointer_cast<IfcPlane>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlaneAngleMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPlaneAngleMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlate") {
				return f(*(std::dynamic_pointer_cast<IfcPlate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcPlateStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateType") {
				return f(*(std::dynamic_pointer_cast<IfcPlateType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPlateTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPlateTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPoint") {
				return f(*(std::dynamic_pointer_cast<IfcPoint>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPointOnCurve") {
				return f(*(std::dynamic_pointer_cast<IfcPointOnCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPointOnSurface") {
				return f(*(std::dynamic_pointer_cast<IfcPointOnSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolygonalBoundedHalfSpace") {
				return f(*(std::dynamic_pointer_cast<IfcPolygonalBoundedHalfSpace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolygonalFaceSet") {
				return f(*(std::dynamic_pointer_cast<IfcPolygonalFaceSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolyline") {
				return f(*(std::dynamic_pointer_cast<IfcPolyline>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPolyLoop") {
				return f(*(std::dynamic_pointer_cast<IfcPolyLoop>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPort") {
				return f(*(std::dynamic_pointer_cast<IfcPort>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositioningElement") {
				return f(*(std::dynamic_pointer_cast<IfcPositioningElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveInteger") {
				return f(*(std::dynamic_pointer_cast<IfcPositiveInteger>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveLengthMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPositiveLengthMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositivePlaneAngleMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPositivePlaneAngleMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPositiveRatioMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPositiveRatioMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPostalAddress") {
				return f(*(std::dynamic_pointer_cast<IfcPostalAddress>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPowerMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPowerMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedColour") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedColour>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedCurveFont") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedCurveFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedItem") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedProperties") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedPropertySet") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedPropertySet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreDefinedTextFont") {
				return f(*(std::dynamic_pointer_cast<IfcPreDefinedTextFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPreferredSurfaceCurveRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcPreferredSurfaceCurveRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentableText") {
				return f(*(std::dynamic_pointer_cast<IfcPresentableText>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationItem") {
				return f(*(std::dynamic_pointer_cast<IfcPresentationItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationLayerAssignment") {
				return f(*(std::dynamic_pointer_cast<IfcPresentationLayerAssignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationLayerWithStyle") {
				return f(*(std::dynamic_pointer_cast<IfcPresentationLayerWithStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationStyle") {
				return f(*(std::dynamic_pointer_cast<IfcPresentationStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPresentationStyleAssignment") {
				return f(*(std::dynamic_pointer_cast<IfcPresentationStyleAssignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPressureMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcPressureMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedure") {
				return f(*(std::dynamic_pointer_cast<IfcProcedure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedureType") {
				return f(*(std::dynamic_pointer_cast<IfcProcedureType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcedureTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProcedureTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProcess") {
				return f(*(std::dynamic_pointer_cast<IfcProcess>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProduct") {
				return f(*(std::dynamic_pointer_cast<IfcProduct>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductDefinitionShape") {
				return f(*(std::dynamic_pointer_cast<IfcProductDefinitionShape>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProductRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcProductRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileProperties") {
				return f(*(std::dynamic_pointer_cast<IfcProfileProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProfileTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProfileTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProject") {
				return f(*(std::dynamic_pointer_cast<IfcProject>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectedCRS") {
				return f(*(std::dynamic_pointer_cast<IfcProjectedCRS>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectedOrTrueLengthEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProjectedOrTrueLengthEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectionElement") {
				return f(*(std::dynamic_pointer_cast<IfcProjectionElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectionElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProjectionElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectLibrary") {
				return f(*(std::dynamic_pointer_cast<IfcProjectLibrary>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectOrder") {
				return f(*(std::dynamic_pointer_cast<IfcProjectOrder>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProjectOrderTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProjectOrderTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProperty") {
				return f(*(std::dynamic_pointer_cast<IfcProperty>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyAbstraction") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyAbstraction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyBoundedValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyBoundedValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyDependencyRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyDependencyRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyEnumeratedValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyEnumeratedValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyEnumeration") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyEnumeration>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyListValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyListValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyReferenceValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyReferenceValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySet") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySetDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetDefinitionSet") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySetDefinitionSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetTemplate") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySetTemplate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySetTemplateTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySetTemplateTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertySingleValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertySingleValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTableValue") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyTableValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTemplate") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyTemplate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPropertyTemplateDefinition") {
				return f(*(std::dynamic_pointer_cast<IfcPropertyTemplateDefinition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDevice") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnit") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnitType") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnitType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTrippingUnitTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnitTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProtectiveDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcProxy") {
				return f(*(std::dynamic_pointer_cast<IfcProxy>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPump") {
				return f(*(std::dynamic_pointer_cast<IfcPump>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPumpType") {
				return f(*(std::dynamic_pointer_cast<IfcPumpType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcPumpTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcPumpTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityArea") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityArea>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityCount") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityCount>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityLength") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityLength>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantitySet") {
				return f(*(std::dynamic_pointer_cast<IfcQuantitySet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityTime") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityVolume") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityVolume>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcQuantityWeight") {
				return f(*(std::dynamic_pointer_cast<IfcQuantityWeight>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRadioActivityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcRadioActivityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailing") {
				return f(*(std::dynamic_pointer_cast<IfcRailing>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailingType") {
				return f(*(std::dynamic_pointer_cast<IfcRailingType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRailingTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRailingTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRamp") {
				return f(*(std::dynamic_pointer_cast<IfcRamp>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlight") {
				return f(*(std::dynamic_pointer_cast<IfcRampFlight>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlightType") {
				return f(*(std::dynamic_pointer_cast<IfcRampFlightType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampFlightTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRampFlightTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampType") {
				return f(*(std::dynamic_pointer_cast<IfcRampType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRampTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRampTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRatioMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcRatioMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRationalBSplineCurveWithKnots") {
				return f(*(std::dynamic_pointer_cast<IfcRationalBSplineCurveWithKnots>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRationalBSplineSurfaceWithKnots") {
				return f(*(std::dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReal") {
				return f(*(std::dynamic_pointer_cast<IfcReal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangleHollowProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcRectangleHollowProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangleProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcRectangleProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangularPyramid") {
				return f(*(std::dynamic_pointer_cast<IfcRectangularPyramid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRectangularTrimmedSurface") {
				return f(*(std::dynamic_pointer_cast<IfcRectangularTrimmedSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRecurrencePattern") {
				return f(*(std::dynamic_pointer_cast<IfcRecurrencePattern>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRecurrenceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRecurrenceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReference") {
				return f(*(std::dynamic_pointer_cast<IfcReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReferent") {
				return f(*(std::dynamic_pointer_cast<IfcReferent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReferentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReferentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReflectanceMethodEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReflectanceMethodEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRegularTimeSeries") {
				return f(*(std::dynamic_pointer_cast<IfcRegularTimeSeries>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcementBarProperties") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcementBarProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcementDefinitionProperties") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcementDefinitionProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBar") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingBar>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarRoleEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingBarRoleEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarSurfaceEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingBarSurfaceEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarType") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingBarType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingBarTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingBarTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingElement") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingElementType") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMesh") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingMesh>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMeshType") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingMeshType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReinforcingMeshTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcReinforcingMeshTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAggregates") {
				return f(*(std::dynamic_pointer_cast<IfcRelAggregates>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssigns") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssigns>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToActor") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToActor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToControl") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToControl>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToGroup") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroup>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToGroupByFactor") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroupByFactor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToProcess") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToProcess>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToProduct") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToProduct>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssignsToResource") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssignsToResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociates") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociates>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesApproval") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesApproval>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesClassification") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesClassification>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesConstraint") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesConstraint>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesDocument") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesDocument>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesLibrary") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesLibrary>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelAssociatesMaterial") {
				return f(*(std::dynamic_pointer_cast<IfcRelAssociatesMaterial>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnects") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnects>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPathElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsPathElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPorts") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsPorts>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsPortToElement") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsPortToElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsStructuralActivity") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralActivity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsStructuralMember") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralMember>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsWithEccentricity") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsWithEccentricity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelConnectsWithRealizingElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelConnectsWithRealizingElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelContainedInSpatialStructure") {
				return f(*(std::dynamic_pointer_cast<IfcRelContainedInSpatialStructure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelCoversBldgElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelCoversBldgElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelCoversSpaces") {
				return f(*(std::dynamic_pointer_cast<IfcRelCoversSpaces>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDeclares") {
				return f(*(std::dynamic_pointer_cast<IfcRelDeclares>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDecomposes") {
				return f(*(std::dynamic_pointer_cast<IfcRelDecomposes>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefines") {
				return f(*(std::dynamic_pointer_cast<IfcRelDefines>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByObject") {
				return f(*(std::dynamic_pointer_cast<IfcRelDefinesByObject>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByProperties") {
				return f(*(std::dynamic_pointer_cast<IfcRelDefinesByProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByTemplate") {
				return f(*(std::dynamic_pointer_cast<IfcRelDefinesByTemplate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelDefinesByType") {
				return f(*(std::dynamic_pointer_cast<IfcRelDefinesByType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelFillsElement") {
				return f(*(std::dynamic_pointer_cast<IfcRelFillsElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelFlowControlElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelFlowControlElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelInterferesElements") {
				return f(*(std::dynamic_pointer_cast<IfcRelInterferesElements>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelNests") {
				return f(*(std::dynamic_pointer_cast<IfcRelNests>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelProjectsElement") {
				return f(*(std::dynamic_pointer_cast<IfcRelProjectsElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelReferencedInSpatialStructure") {
				return f(*(std::dynamic_pointer_cast<IfcRelReferencedInSpatialStructure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSequence") {
				return f(*(std::dynamic_pointer_cast<IfcRelSequence>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelServicesBuildings") {
				return f(*(std::dynamic_pointer_cast<IfcRelServicesBuildings>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary") {
				return f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary1stLevel") {
				return f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary1stLevel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelSpaceBoundary2ndLevel") {
				return f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary2ndLevel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRelVoidsElement") {
				return f(*(std::dynamic_pointer_cast<IfcRelVoidsElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcReparametrisedCompositeCurveSegment") {
				return f(*(std::dynamic_pointer_cast<IfcReparametrisedCompositeCurveSegment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationContext") {
				return f(*(std::dynamic_pointer_cast<IfcRepresentationContext>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationItem") {
				return f(*(std::dynamic_pointer_cast<IfcRepresentationItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRepresentationMap") {
				return f(*(std::dynamic_pointer_cast<IfcRepresentationMap>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResource") {
				return f(*(std::dynamic_pointer_cast<IfcResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceApprovalRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcResourceApprovalRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceConstraintRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcResourceConstraintRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceLevelRelationship") {
				return f(*(std::dynamic_pointer_cast<IfcResourceLevelRelationship>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcResourceTime") {
				return f(*(std::dynamic_pointer_cast<IfcResourceTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRevolvedAreaSolid") {
				return f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRevolvedAreaSolidTapered") {
				return f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolidTapered>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRightCircularCone") {
				return f(*(std::dynamic_pointer_cast<IfcRightCircularCone>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRightCircularCylinder") {
				return f(*(std::dynamic_pointer_cast<IfcRightCircularCylinder>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoleEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRoleEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoof") {
				return f(*(std::dynamic_pointer_cast<IfcRoof>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoofType") {
				return f(*(std::dynamic_pointer_cast<IfcRoofType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoofTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcRoofTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoot") {
				return f(*(std::dynamic_pointer_cast<IfcRoot>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalFrequencyMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcRotationalFrequencyMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalMassMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcRotationalMassMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRotationalStiffnessMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcRotationalStiffnessMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcRoundedRectangleProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcRoundedRectangleProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcSanitaryTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcSanitaryTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSanitaryTerminalTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSanitaryTerminalTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSchedulingTime") {
				return f(*(std::dynamic_pointer_cast<IfcSchedulingTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSeamCurve") {
				return f(*(std::dynamic_pointer_cast<IfcSeamCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionalAreaIntegralMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSectionalAreaIntegralMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSolid") {
				return f(*(std::dynamic_pointer_cast<IfcSectionedSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSolidHorizontal") {
				return f(*(std::dynamic_pointer_cast<IfcSectionedSolidHorizontal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionedSpine") {
				return f(*(std::dynamic_pointer_cast<IfcSectionedSpine>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionModulusMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSectionModulusMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionProperties") {
				return f(*(std::dynamic_pointer_cast<IfcSectionProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionReinforcementProperties") {
				return f(*(std::dynamic_pointer_cast<IfcSectionReinforcementProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSectionTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSectionTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensor") {
				return f(*(std::dynamic_pointer_cast<IfcSensor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensorType") {
				return f(*(std::dynamic_pointer_cast<IfcSensorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSensorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSensorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSequenceEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSequenceEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDevice") {
				return f(*(std::dynamic_pointer_cast<IfcShadingDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcShadingDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShadingDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcShadingDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeAspect") {
				return f(*(std::dynamic_pointer_cast<IfcShapeAspect>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeModel") {
				return f(*(std::dynamic_pointer_cast<IfcShapeModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShapeRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcShapeRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShearModulusMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcShearModulusMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcShellBasedSurfaceModel") {
				return f(*(std::dynamic_pointer_cast<IfcShellBasedSurfaceModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimpleProperty") {
				return f(*(std::dynamic_pointer_cast<IfcSimpleProperty>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimplePropertyTemplate") {
				return f(*(std::dynamic_pointer_cast<IfcSimplePropertyTemplate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSimplePropertyTemplateTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSimplePropertyTemplateTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIPrefix") {
				return f(*(std::dynamic_pointer_cast<IfcSIPrefix>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSite") {
				return f(*(std::dynamic_pointer_cast<IfcSite>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIUnit") {
				return f(*(std::dynamic_pointer_cast<IfcSIUnit>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSIUnitName") {
				return f(*(std::dynamic_pointer_cast<IfcSIUnitName>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlab") {
				return f(*(std::dynamic_pointer_cast<IfcSlab>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabElementedCase") {
				return f(*(std::dynamic_pointer_cast<IfcSlabElementedCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcSlabStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabType") {
				return f(*(std::dynamic_pointer_cast<IfcSlabType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlabTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSlabTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSlippageConnectionCondition") {
				return f(*(std::dynamic_pointer_cast<IfcSlippageConnectionCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDevice") {
				return f(*(std::dynamic_pointer_cast<IfcSolarDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcSolarDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolarDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSolarDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolidAngleMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSolidAngleMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSolidModel") {
				return f(*(std::dynamic_pointer_cast<IfcSolidModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPowerLevelMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSoundPowerLevelMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPowerMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSoundPowerMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPressureLevelMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSoundPressureLevelMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSoundPressureMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSoundPressureMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpace") {
				return f(*(std::dynamic_pointer_cast<IfcSpace>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeater") {
				return f(*(std::dynamic_pointer_cast<IfcSpaceHeater>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeaterType") {
				return f(*(std::dynamic_pointer_cast<IfcSpaceHeaterType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceHeaterTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSpaceHeaterTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceType") {
				return f(*(std::dynamic_pointer_cast<IfcSpaceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpaceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSpaceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialElement") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialElementType") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialStructureElement") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialStructureElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialStructureElementType") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialStructureElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZone") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialZone>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZoneType") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialZoneType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpatialZoneTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSpatialZoneTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecificHeatCapacityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcSpecificHeatCapacityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecularExponent") {
				return f(*(std::dynamic_pointer_cast<IfcSpecularExponent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSpecularRoughness") {
				return f(*(std::dynamic_pointer_cast<IfcSpecularRoughness>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSphere") {
				return f(*(std::dynamic_pointer_cast<IfcSphere>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSphericalSurface") {
				return f(*(std::dynamic_pointer_cast<IfcSphericalSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcStackTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcStackTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStackTerminalTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStackTerminalTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStair") {
				return f(*(std::dynamic_pointer_cast<IfcStair>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlight") {
				return f(*(std::dynamic_pointer_cast<IfcStairFlight>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlightType") {
				return f(*(std::dynamic_pointer_cast<IfcStairFlightType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairFlightTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStairFlightTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairType") {
				return f(*(std::dynamic_pointer_cast<IfcStairType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStairTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStairTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStateEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStateEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStrippedOptional") {
				return f(*(std::dynamic_pointer_cast<IfcStrippedOptional>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralActivity") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralActivity>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralAnalysisModel") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralAnalysisModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralConnection") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralConnection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralConnectionCondition") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralConnectionCondition>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveActivityTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveActivityTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveConnection") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveConnection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMember") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveMember>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMemberTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveMemberTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveMemberVarying") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveMemberVarying>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralCurveReaction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralCurveReaction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralItem") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLinearAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLinearAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoad") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoad>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadCase") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadConfiguration") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadConfiguration>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadGroup") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadGroup>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadLinearForce") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadLinearForce>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadOrResult") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadOrResult>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadPlanarForce") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadPlanarForce>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleDisplacement") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleDisplacementDistortion") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacementDistortion>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleForce") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForce>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadSingleForceWarping") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForceWarping>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadStatic") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadStatic>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralLoadTemperature") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralLoadTemperature>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralMember") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralMember>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPlanarAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralPlanarAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralPointAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointConnection") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralPointConnection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralPointReaction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralPointReaction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralReaction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralReaction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralResultGroup") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralResultGroup>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceAction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceAction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceActivityTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceActivityTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceConnection") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceConnection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMember") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMember>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMemberTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMemberTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceMemberVarying") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMemberVarying>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStructuralSurfaceReaction") {
				return f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceReaction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyledItem") {
				return f(*(std::dynamic_pointer_cast<IfcStyledItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyledRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcStyledRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcStyleModel") {
				return f(*(std::dynamic_pointer_cast<IfcStyleModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResource") {
				return f(*(std::dynamic_pointer_cast<IfcSubContractResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResourceType") {
				return f(*(std::dynamic_pointer_cast<IfcSubContractResourceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubContractResourceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSubContractResourceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSubedge") {
				return f(*(std::dynamic_pointer_cast<IfcSubedge>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurface") {
				return f(*(std::dynamic_pointer_cast<IfcSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceCurve") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceCurveSweptAreaSolid") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceCurveSweptAreaSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceFeature") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceFeature>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceFeatureTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceFeatureTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceOfLinearExtrusion") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceOfLinearExtrusion>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceOfRevolution") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceOfRevolution>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceReinforcementArea") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceReinforcementArea>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceSide") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceSide>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyle") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleLighting") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyleLighting>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleRefraction") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRefraction>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleRendering") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRendering>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleShading") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyleShading>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceStyleWithTextures") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceStyleWithTextures>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSurfaceTexture") {
				return f(*(std::dynamic_pointer_cast<IfcSurfaceTexture>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptAreaSolid") {
				return f(*(std::dynamic_pointer_cast<IfcSweptAreaSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptDiskSolid") {
				return f(*(std::dynamic_pointer_cast<IfcSweptDiskSolid>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptDiskSolidPolygonal") {
				return f(*(std::dynamic_pointer_cast<IfcSweptDiskSolidPolygonal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSweptSurface") {
				return f(*(std::dynamic_pointer_cast<IfcSweptSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDevice") {
				return f(*(std::dynamic_pointer_cast<IfcSwitchingDevice>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDeviceType") {
				return f(*(std::dynamic_pointer_cast<IfcSwitchingDeviceType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSwitchingDeviceTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSwitchingDeviceTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystem") {
				return f(*(std::dynamic_pointer_cast<IfcSystem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElement") {
				return f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElementType") {
				return f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcSystemFurnitureElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTable") {
				return f(*(std::dynamic_pointer_cast<IfcTable>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTableColumn") {
				return f(*(std::dynamic_pointer_cast<IfcTableColumn>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTableRow") {
				return f(*(std::dynamic_pointer_cast<IfcTableRow>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTank") {
				return f(*(std::dynamic_pointer_cast<IfcTank>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTankType") {
				return f(*(std::dynamic_pointer_cast<IfcTankType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTankTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTankTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTask") {
				return f(*(std::dynamic_pointer_cast<IfcTask>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskDurationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTaskDurationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTime") {
				return f(*(std::dynamic_pointer_cast<IfcTaskTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTimeRecurring") {
				return f(*(std::dynamic_pointer_cast<IfcTaskTimeRecurring>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskType") {
				return f(*(std::dynamic_pointer_cast<IfcTaskType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTaskTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTaskTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTelecomAddress") {
				return f(*(std::dynamic_pointer_cast<IfcTelecomAddress>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTemperatureGradientMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcTemperatureGradientMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTemperatureRateOfChangeMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcTemperatureRateOfChangeMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendon") {
				return f(*(std::dynamic_pointer_cast<IfcTendon>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchor") {
				return f(*(std::dynamic_pointer_cast<IfcTendonAnchor>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchorType") {
				return f(*(std::dynamic_pointer_cast<IfcTendonAnchorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonAnchorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTendonAnchorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonType") {
				return f(*(std::dynamic_pointer_cast<IfcTendonType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTendonTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTendonTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTessellatedFaceSet") {
				return f(*(std::dynamic_pointer_cast<IfcTessellatedFaceSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTessellatedItem") {
				return f(*(std::dynamic_pointer_cast<IfcTessellatedItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcText") {
				return f(*(std::dynamic_pointer_cast<IfcText>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextAlignment") {
				return f(*(std::dynamic_pointer_cast<IfcTextAlignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextDecoration") {
				return f(*(std::dynamic_pointer_cast<IfcTextDecoration>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextFontName") {
				return f(*(std::dynamic_pointer_cast<IfcTextFontName>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextLiteral") {
				return f(*(std::dynamic_pointer_cast<IfcTextLiteral>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextLiteralWithExtent") {
				return f(*(std::dynamic_pointer_cast<IfcTextLiteralWithExtent>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextPath") {
				return f(*(std::dynamic_pointer_cast<IfcTextPath>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyle") {
				return f(*(std::dynamic_pointer_cast<IfcTextStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleFontModel") {
				return f(*(std::dynamic_pointer_cast<IfcTextStyleFontModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleForDefinedFont") {
				return f(*(std::dynamic_pointer_cast<IfcTextStyleForDefinedFont>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextStyleTextModel") {
				return f(*(std::dynamic_pointer_cast<IfcTextStyleTextModel>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextTransformation") {
				return f(*(std::dynamic_pointer_cast<IfcTextTransformation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureCoordinate") {
				return f(*(std::dynamic_pointer_cast<IfcTextureCoordinate>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureCoordinateGenerator") {
				return f(*(std::dynamic_pointer_cast<IfcTextureCoordinateGenerator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureMap") {
				return f(*(std::dynamic_pointer_cast<IfcTextureMap>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureVertex") {
				return f(*(std::dynamic_pointer_cast<IfcTextureVertex>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTextureVertexList") {
				return f(*(std::dynamic_pointer_cast<IfcTextureVertexList>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalAdmittanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermalAdmittanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalConductivityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermalConductivityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalExpansionCoefficientMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermalExpansionCoefficientMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalResistanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermalResistanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermalTransmittanceMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermalTransmittanceMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcThermodynamicTemperatureMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcThermodynamicTemperatureMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTime") {
				return f(*(std::dynamic_pointer_cast<IfcTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcTimeMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimePeriod") {
				return f(*(std::dynamic_pointer_cast<IfcTimePeriod>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeries") {
				return f(*(std::dynamic_pointer_cast<IfcTimeSeries>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeriesDataTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTimeSeriesDataTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeSeriesValue") {
				return f(*(std::dynamic_pointer_cast<IfcTimeSeriesValue>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTimeStamp") {
				return f(*(std::dynamic_pointer_cast<IfcTimeStamp>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTopologicalRepresentationItem") {
				return f(*(std::dynamic_pointer_cast<IfcTopologicalRepresentationItem>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTopologyRepresentation") {
				return f(*(std::dynamic_pointer_cast<IfcTopologyRepresentation>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcToroidalSurface") {
				return f(*(std::dynamic_pointer_cast<IfcToroidalSurface>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTorqueMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcTorqueMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformer") {
				return f(*(std::dynamic_pointer_cast<IfcTransformer>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformerType") {
				return f(*(std::dynamic_pointer_cast<IfcTransformerType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransformerTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTransformerTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCode") {
				return f(*(std::dynamic_pointer_cast<IfcTransitionCode>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCurveSegment2D") {
				return f(*(std::dynamic_pointer_cast<IfcTransitionCurveSegment2D>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransitionCurveType") {
				return f(*(std::dynamic_pointer_cast<IfcTransitionCurveType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElement") {
				return f(*(std::dynamic_pointer_cast<IfcTransportElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElementType") {
				return f(*(std::dynamic_pointer_cast<IfcTransportElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTransportElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTransportElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrapeziumProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcTrapeziumProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTriangulatedFaceSet") {
				return f(*(std::dynamic_pointer_cast<IfcTriangulatedFaceSet>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTriangulatedIrregularNetwork") {
				return f(*(std::dynamic_pointer_cast<IfcTriangulatedIrregularNetwork>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrimmedCurve") {
				return f(*(std::dynamic_pointer_cast<IfcTrimmedCurve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTrimmingPreference") {
				return f(*(std::dynamic_pointer_cast<IfcTrimmingPreference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcTShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundle") {
				return f(*(std::dynamic_pointer_cast<IfcTubeBundle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundleType") {
				return f(*(std::dynamic_pointer_cast<IfcTubeBundleType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTubeBundleTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcTubeBundleTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeObject") {
				return f(*(std::dynamic_pointer_cast<IfcTypeObject>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeProcess") {
				return f(*(std::dynamic_pointer_cast<IfcTypeProcess>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeProduct") {
				return f(*(std::dynamic_pointer_cast<IfcTypeProduct>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcTypeResource") {
				return f(*(std::dynamic_pointer_cast<IfcTypeResource>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElement") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryControlElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElementType") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryControlElementType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryControlElementTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryControlElementTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipment") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryEquipment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipmentType") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryEquipmentType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitaryEquipmentTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcUnitaryEquipmentTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitAssignment") {
				return f(*(std::dynamic_pointer_cast<IfcUnitAssignment>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUnitEnum") {
				return f(*(std::dynamic_pointer_cast<IfcUnitEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcURIReference") {
				return f(*(std::dynamic_pointer_cast<IfcURIReference>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcUShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcUShapeProfileDef>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValve") {
				return f(*(std::dynamic_pointer_cast<IfcValve>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValveType") {
				return f(*(std::dynamic_pointer_cast<IfcValveType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcValveTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcValveTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVaporPermeabilityMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcVaporPermeabilityMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVector") {
				return f(*(std::dynamic_pointer_cast<IfcVector>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertex") {
				return f(*(std::dynamic_pointer_cast<IfcVertex>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertexLoop") {
				return f(*(std::dynamic_pointer_cast<IfcVertexLoop>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVertexPoint") {
				return f(*(std::dynamic_pointer_cast<IfcVertexPoint>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolator") {
				return f(*(std::dynamic_pointer_cast<IfcVibrationIsolator>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolatorType") {
				return f(*(std::dynamic_pointer_cast<IfcVibrationIsolatorType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVibrationIsolatorTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcVibrationIsolatorTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVirtualElement") {
				return f(*(std::dynamic_pointer_cast<IfcVirtualElement>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVirtualGridIntersection") {
				return f(*(std::dynamic_pointer_cast<IfcVirtualGridIntersection>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVoidingFeature") {
				return f(*(std::dynamic_pointer_cast<IfcVoidingFeature>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVoidingFeatureTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcVoidingFeatureTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVolumeMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcVolumeMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcVolumetricFlowRateMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcVolumetricFlowRateMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWall") {
				return f(*(std::dynamic_pointer_cast<IfcWall>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallElementedCase") {
				return f(*(std::dynamic_pointer_cast<IfcWallElementedCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcWallStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallType") {
				return f(*(std::dynamic_pointer_cast<IfcWallType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWallTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWallTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWarpingConstantMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcWarpingConstantMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWarpingMomentMeasure") {
				return f(*(std::dynamic_pointer_cast<IfcWarpingMomentMeasure>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminal") {
				return f(*(std::dynamic_pointer_cast<IfcWasteTerminal>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminalType") {
				return f(*(std::dynamic_pointer_cast<IfcWasteTerminalType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWasteTerminalTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWasteTerminalTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindow") {
				return f(*(std::dynamic_pointer_cast<IfcWindow>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowLiningProperties") {
				return f(*(std::dynamic_pointer_cast<IfcWindowLiningProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowPanelOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelPositionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowPanelPositionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowPanelProperties") {
				return f(*(std::dynamic_pointer_cast<IfcWindowPanelProperties>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStandardCase") {
				return f(*(std::dynamic_pointer_cast<IfcWindowStandardCase>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyle") {
				return f(*(std::dynamic_pointer_cast<IfcWindowStyle>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyleConstructionEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowStyleConstructionEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowStyleOperationEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowStyleOperationEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowType") {
				return f(*(std::dynamic_pointer_cast<IfcWindowType>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWindowTypePartitioningEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWindowTypePartitioningEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkCalendar") {
				return f(*(std::dynamic_pointer_cast<IfcWorkCalendar>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkCalendarTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWorkCalendarTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkControl") {
				return f(*(std::dynamic_pointer_cast<IfcWorkControl>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkPlan") {
				return f(*(std::dynamic_pointer_cast<IfcWorkPlan>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkPlanTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWorkPlanTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkSchedule") {
				return f(*(std::dynamic_pointer_cast<IfcWorkSchedule>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkScheduleTypeEnum") {
				return f(*(std::dynamic_pointer_cast<IfcWorkScheduleTypeEnum>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcWorkTime") {
				return f(*(std::dynamic_pointer_cast<IfcWorkTime>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcZone") {
				return f(*(std::dynamic_pointer_cast<IfcZone>(ptr)));				
			}

			if (name == "class OpenInfraPlatform::IfcAlignment1x1::IfcZShapeProfileDef") {
				return f(*(std::dynamic_pointer_cast<IfcZShapeProfileDef>(ptr)));				
			}
		
		}
	}
}

