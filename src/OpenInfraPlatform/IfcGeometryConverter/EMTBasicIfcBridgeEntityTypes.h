/*
    Copyright (c) 2017 Technical University of Munich
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

#pragma once

namespace emt
{
	template <
		typename IfcAbsorbedDoseMeasureT,
		typename IfcAccelerationMeasureT,
		typename IfcActionRequestT,
		typename IfcActionRequestTypeEnumT,
		typename IfcActionSourceTypeEnumT,
		typename IfcActionTypeEnumT,
		typename IfcActorT,
		typename IfcActorRoleT,
		typename IfcActorSelectT,
		typename IfcActuatorT,
		typename IfcActuatorTypeT,
		typename IfcActuatorTypeEnumT,
		typename IfcAddressT,
		typename IfcAddressTypeEnumT,
		typename IfcAdvancedBrepT,
		typename IfcAdvancedBrepWithVoidsT,
		typename IfcAdvancedFaceT,
		typename IfcAirTerminalT,
		typename IfcAirTerminalBoxT,
		typename IfcAirTerminalBoxTypeT,
		typename IfcAirTerminalBoxTypeEnumT,
		typename IfcAirTerminalTypeT,
		typename IfcAirTerminalTypeEnumT,
		typename IfcAirToAirHeatRecoveryT,
		typename IfcAirToAirHeatRecoveryTypeT,
		typename IfcAirToAirHeatRecoveryTypeEnumT,
		typename IfcAlarmT,
		typename IfcAlarmTypeT,
		typename IfcAlarmTypeEnumT,
		typename IfcAlignmentElementT,
		typename IfcAmountOfSubstanceMeasureT,
		typename IfcAnalysisModelTypeEnumT,
		typename IfcAnalysisTheoryTypeEnumT,
		typename IfcAngularVelocityMeasureT,
		typename IfcAnnotationT,
		typename IfcAnnotationFillAreaT,
		typename IfcApplicationT,
		typename IfcAppliedValueT,
		typename IfcAppliedValueRelationshipT,
		typename IfcAppliedValueSelectT,
		typename IfcApprovalT,
		typename IfcApprovalRelationshipT,
		typename IfcArbitraryClosedProfileDefT,
		typename IfcArbitraryOpenProfileDefT,
		typename IfcArbitraryProfileDefWithVoidsT,
		typename IfcAreaMeasureT,
		typename IfcArithmeticOperatorEnumT,
		typename IfcAssemblyPlaceEnumT,
		typename IfcAssetT,
		typename IfcAsymmetricIShapeProfileDefT,
		typename IfcAudioVisualApplianceT,
		typename IfcAudioVisualApplianceTypeT,
		typename IfcAudioVisualApplianceTypeEnumT,
		typename IfcAxis1PlacementT,
		typename IfcAxis2PlacementT,
		typename IfcAxis2Placement2DT,
		typename IfcAxis2Placement3DT,
		typename IfcBeamT,
		typename IfcBeamStandardCaseT,
		typename IfcBeamTypeT,
		typename IfcBeamTypeEnumT,
		typename IfcBenchmarkEnumT,
		typename IfcBendingParameterSelectT,
		typename IfcBlobTextureT,
		typename IfcBlockT,
		typename IfcBoilerT,
		typename IfcBoilerTypeT,
		typename IfcBoilerTypeEnumT,
		typename IfcBooleanT,
		typename IfcBooleanClippingResultT,
		typename IfcBooleanOperandT,
		typename IfcBooleanOperatorT,
		typename IfcBooleanResultT,
		typename IfcBoundaryConditionT,
		typename IfcBoundaryCurveT,
		typename IfcBoundaryEdgeConditionT,
		typename IfcBoundaryFaceConditionT,
		typename IfcBoundaryNodeConditionT,
		typename IfcBoundaryNodeConditionWarpingT,
		typename IfcBoundedCurveT,
		typename IfcBoundedSurfaceT,
		typename IfcBoundingBoxT,
		typename IfcBoxAlignmentT,
		typename IfcBoxedHalfSpaceT,
		typename IfcBridgeT,
		typename IfcBridgeContactElementT,
		typename IfcBridgeContactTypeT,
		typename IfcBridgeElementT,
		typename IfcBridgeMechanicalRoleTypeT,
		typename IfcBridgePartT,
		typename IfcBridgePrismaticElementT,
		typename IfcBridgePrismaticElementTypeT,
		typename IfcBridgeSegmentT,
		typename IfcBridgeSegmentPartT,
		typename IfcBridgeSegmentTypeT,
		typename IfcBridgeStructureElementT,
		typename IfcBridgeStructureElementTypeT,
		typename IfcBridgeStructureIndicatorT,
		typename IfcBridgeStructureTypeT,
		typename IfcBridgeSubPartTypeT,
		typename IfcBridgeTechnologicalElementTypeT,
		typename IfcBSplineCurveT,
		typename IfcBSplineCurveFormT,
		typename IfcBSplineCurveWithKnotsT,
		typename IfcBSplineSurfaceT,
		typename IfcBSplineSurfaceFormT,
		typename IfcBSplineSurfaceWithKnotsT,
		typename IfcBuildingT,
		typename IfcBuildingElementT,
		typename IfcBuildingElementPartT,
		typename IfcBuildingElementPartTypeT,
		typename IfcBuildingElementPartTypeEnumT,
		typename IfcBuildingElementProxyT,
		typename IfcBuildingElementProxyTypeT,
		typename IfcBuildingElementProxyTypeEnumT,
		typename IfcBuildingElementTypeT,
		typename IfcBuildingStoreyT,
		typename IfcBuildingSystemT,
		typename IfcBuildingSystemTypeEnumT,
		typename IfcBurnerT,
		typename IfcBurnerTypeT,
		typename IfcBurnerTypeEnumT,
		typename IfcCableCarrierFittingT,
		typename IfcCableCarrierFittingTypeT,
		typename IfcCableCarrierFittingTypeEnumT,
		typename IfcCableCarrierSegmentT,
		typename IfcCableCarrierSegmentTypeT,
		typename IfcCableCarrierSegmentTypeEnumT,
		typename IfcCableFittingT,
		typename IfcCableFittingTypeT,
		typename IfcCableFittingTypeEnumT,
		typename IfcCableSegmentT,
		typename IfcCableSegmentTypeT,
		typename IfcCableSegmentTypeEnumT,
		typename IfcCardinalPointReferenceT,
		typename IfcCartesianPointT,
		typename IfcCartesianPointListT,
		typename IfcCartesianTransformationOperatorT,
		typename IfcCartesianTransformationOperator2DT,
		typename IfcCartesianTransformationOperator2DnonUniformT,
		typename IfcCartesianTransformationOperator3DT,
		typename IfcCartesianTransformationOperator3DnonUniformT,
		typename IfcCenterLineProfileDefT,
		typename IfcChangeActionEnumT,
		typename IfcCharacterStyleSelectT,
		typename IfcChillerT,
		typename IfcChillerTypeT,
		typename IfcChillerTypeEnumT,
		typename IfcChimneyT,
		typename IfcChimneyTypeT,
		typename IfcChimneyTypeEnumT,
		typename IfcCircleT,
		typename IfcCircleHollowProfileDefT,
		typename IfcCircleProfileDefT,
		typename IfcCivilElementT,
		typename IfcCivilElementPartT,
		typename IfcCivilSheathT,
		typename IfcCivilStructureElementT,
		typename IfcCivilVoidT,
		typename IfcClassificationT,
		typename IfcClassificationReferenceT,
		typename IfcClassificationReferenceSelectT,
		typename IfcClassificationSelectT,
		typename IfcClosedShellT,
		typename IfcClothoidT,
		typename IfcCoilT,
		typename IfcCoilTypeT,
		typename IfcCoilTypeEnumT,
		typename IfcColourT,
		typename IfcColourOrFactorT,
		typename IfcColourRgbT,
		typename IfcColourRgbListT,
		typename IfcColourSpecificationT,
		typename IfcColumnT,
		typename IfcColumnStandardCaseT,
		typename IfcColumnTypeT,
		typename IfcColumnTypeEnumT,
		typename IfcCommunicationsApplianceT,
		typename IfcCommunicationsApplianceTypeT,
		typename IfcCommunicationsApplianceTypeEnumT,
		typename IfcComplexNumberT,
		typename IfcComplexPropertyT,
		typename IfcComplexPropertyTemplateT,
		typename IfcComplexPropertyTemplateTypeEnumT,
		typename IfcCompositeCurveT,
		typename IfcCompositeCurveOnSurfaceT,
		typename IfcCompositeCurveSegmentT,
		typename IfcCompositeProfileDefT,
		typename IfcCompoundPlaneAngleMeasureT,
		typename IfcCompressorT,
		typename IfcCompressorTypeT,
		typename IfcCompressorTypeEnumT,
		typename IfcCondenserT,
		typename IfcCondenserTypeT,
		typename IfcCondenserTypeEnumT,
		typename IfcConicT,
		typename IfcConnectedFaceSetT,
		typename IfcConnectionCurveGeometryT,
		typename IfcConnectionGeometryT,
		typename IfcConnectionPointEccentricityT,
		typename IfcConnectionPointGeometryT,
		typename IfcConnectionSurfaceGeometryT,
		typename IfcConnectionTypeEnumT,
		typename IfcConnectionVolumeGeometryT,
		typename IfcConstraintT,
		typename IfcConstraintEnumT,
		typename IfcConstructionEquipmentResourceT,
		typename IfcConstructionEquipmentResourceTypeT,
		typename IfcConstructionEquipmentResourceTypeEnumT,
		typename IfcConstructionMaterialResourceT,
		typename IfcConstructionMaterialResourceTypeT,
		typename IfcConstructionMaterialResourceTypeEnumT,
		typename IfcConstructionProductResourceT,
		typename IfcConstructionProductResourceTypeT,
		typename IfcConstructionProductResourceTypeEnumT,
		typename IfcConstructionResourceT,
		typename IfcConstructionResourceTypeT,
		typename IfcContextT,
		typename IfcContextDependentMeasureT,
		typename IfcContextDependentUnitT,
		typename IfcControlT,
		typename IfcControllerT,
		typename IfcControllerTypeT,
		typename IfcControllerTypeEnumT,
		typename IfcConversionBasedUnitT,
		typename IfcConversionBasedUnitWithOffsetT,
		typename IfcCooledBeamT,
		typename IfcCooledBeamTypeT,
		typename IfcCooledBeamTypeEnumT,
		typename IfcCoolingTowerT,
		typename IfcCoolingTowerTypeT,
		typename IfcCoolingTowerTypeEnumT,
		typename IfcCoordinateOperationT,
		typename IfcCoordinateReferenceSystemT,
		typename IfcCoordinateReferenceSystemSelectT,
		typename IfcCostItemT,
		typename IfcCostItemTypeEnumT,
		typename IfcCostScheduleT,
		typename IfcCostScheduleTypeEnumT,
		typename IfcCostValueT,
		typename IfcCountMeasureT,
		typename IfcCoveringT,
		typename IfcCoveringTypeT,
		typename IfcCoveringTypeEnumT,
		typename IfcCrewResourceT,
		typename IfcCrewResourceTypeT,
		typename IfcCrewResourceTypeEnumT,
		typename IfcCsgPrimitive3DT,
		typename IfcCsgSelectT,
		typename IfcCsgSolidT,
		typename IfcCShapeProfileDefT,
		typename IfcCurrencyRelationshipT,
		typename IfcCurtainWallT,
		typename IfcCurtainWallTypeT,
		typename IfcCurtainWallTypeEnumT,
		typename IfcCurvatureMeasureT,
		typename IfcCurveT,
		typename IfcCurveBoundedPlaneT,
		typename IfcCurveBoundedSurfaceT,
		typename IfcCurveFontOrScaledCurveFontSelectT,
		typename IfcCurveInterpolationEnumT,
		typename IfcCurveOnSurfaceT,
		typename IfcCurveOrEdgeCurveT,
		typename IfcCurveStyleT,
		typename IfcCurveStyleFontT,
		typename IfcCurveStyleFontAndScalingT,
		typename IfcCurveStyleFontPatternT,
		typename IfcCurveStyleFontSelectT,
		typename IfcCylindricalSurfaceT,
		typename IfcDamperT,
		typename IfcDamperTypeT,
		typename IfcDamperTypeEnumT,
		typename IfcDataOriginEnumT,
		typename IfcDateT,
		typename IfcDateTimeT,
		typename IfcDayInMonthNumberT,
		typename IfcDayInWeekNumberT,
		typename IfcDefinedSymbolT,
		typename IfcDefinedSymbolSelectT,
		typename IfcDefinitionSelectT,
		typename IfcDerivedMeasureValueT,
		typename IfcDerivedProfileDefT,
		typename IfcDerivedUnitT,
		typename IfcDerivedUnitElementT,
		typename IfcDerivedUnitEnumT,
		typename IfcDescriptiveMeasureT,
		typename IfcDimensionalExponentsT,
		typename IfcDimensionCountT,
		typename IfcDirectionT,
		typename IfcDirectionListT,
		typename IfcDirectionSenseEnumT,
		typename IfcDiscreteAccessoryT,
		typename IfcDiscreteAccessoryTypeT,
		typename IfcDiscreteAccessoryTypeEnumT,
		typename IfcDistributionChamberElementT,
		typename IfcDistributionChamberElementTypeT,
		typename IfcDistributionChamberElementTypeEnumT,
		typename IfcDistributionCircuitT,
		typename IfcDistributionControlElementT,
		typename IfcDistributionControlElementTypeT,
		typename IfcDistributionElementT,
		typename IfcDistributionElementTypeT,
		typename IfcDistributionFlowElementT,
		typename IfcDistributionFlowElementTypeT,
		typename IfcDistributionPortT,
		typename IfcDistributionSystemT,
		typename IfcDistributionSystemEnumT,
		typename IfcDocumentConfidentialityEnumT,
		typename IfcDocumentElectronicFormatT,
		typename IfcDocumentInformationT,
		typename IfcDocumentInformationRelationshipT,
		typename IfcDocumentReferenceT,
		typename IfcDocumentSelectT,
		typename IfcDocumentStatusEnumT,
		typename IfcDoorT,
		typename IfcDoorLiningPropertiesT,
		typename IfcDoorPanelOperationEnumT,
		typename IfcDoorPanelPositionEnumT,
		typename IfcDoorPanelPropertiesT,
		typename IfcDoorStandardCaseT,
		typename IfcDoorStyleT,
		typename IfcDoorStyleConstructionEnumT,
		typename IfcDoorStyleOperationEnumT,
		typename IfcDoorTypeT,
		typename IfcDoorTypeEnumT,
		typename IfcDoorTypeOperationEnumT,
		typename IfcDoseEquivalentMeasureT,
		typename IfcDraughtingPreDefinedColourT,
		typename IfcDraughtingPreDefinedCurveFontT,
		typename IfcDraughtingPreDefinedTextFontT,
		typename IfcDuctFittingT,
		typename IfcDuctFittingTypeT,
		typename IfcDuctFittingTypeEnumT,
		typename IfcDuctSegmentT,
		typename IfcDuctSegmentTypeT,
		typename IfcDuctSegmentTypeEnumT,
		typename IfcDuctSilencerT,
		typename IfcDuctSilencerTypeT,
		typename IfcDuctSilencerTypeEnumT,
		typename IfcDurationT,
		typename IfcDynamicViscosityMeasureT,
		typename IfcEdgeT,
		typename IfcEdgeCurveT,
		typename IfcEdgeLoopT,
		typename IfcElectricApplianceT,
		typename IfcElectricApplianceTypeT,
		typename IfcElectricApplianceTypeEnumT,
		typename IfcElectricCapacitanceMeasureT,
		typename IfcElectricChargeMeasureT,
		typename IfcElectricConductanceMeasureT,
		typename IfcElectricCurrentMeasureT,
		typename IfcElectricDistributionBoardT,
		typename IfcElectricDistributionBoardTypeT,
		typename IfcElectricDistributionBoardTypeEnumT,
		typename IfcElectricFlowStorageDeviceT,
		typename IfcElectricFlowStorageDeviceTypeT,
		typename IfcElectricFlowStorageDeviceTypeEnumT,
		typename IfcElectricGeneratorT,
		typename IfcElectricGeneratorTypeT,
		typename IfcElectricGeneratorTypeEnumT,
		typename IfcElectricMotorT,
		typename IfcElectricMotorTypeT,
		typename IfcElectricMotorTypeEnumT,
		typename IfcElectricResistanceMeasureT,
		typename IfcElectricTimeControlT,
		typename IfcElectricTimeControlTypeT,
		typename IfcElectricTimeControlTypeEnumT,
		typename IfcElectricVoltageMeasureT,
		typename IfcElementT,
		typename IfcElementarySurfaceT,
		typename IfcElementAssemblyT,
		typename IfcElementAssemblyTypeT,
		typename IfcElementAssemblyTypeEnumT,
		typename IfcElementComponentT,
		typename IfcElementComponentTypeT,
		typename IfcElementCompositionEnumT,
		typename IfcElementPartT,
		typename IfcElementQuantityT,
		typename IfcElementTypeT,
		typename IfcEllipseT,
		typename IfcEllipseProfileDefT,
		typename IfcEnergyConversionDeviceT,
		typename IfcEnergyConversionDeviceTypeT,
		typename IfcEnergyMeasureT,
		typename IfcEngineT,
		typename IfcEngineTypeT,
		typename IfcEngineTypeEnumT,
		typename IfcEvaporativeCoolerT,
		typename IfcEvaporativeCoolerTypeT,
		typename IfcEvaporativeCoolerTypeEnumT,
		typename IfcEvaporatorT,
		typename IfcEvaporatorTypeT,
		typename IfcEvaporatorTypeEnumT,
		typename IfcEventT,
		typename IfcEventTimeT,
		typename IfcEventTriggerTypeEnumT,
		typename IfcEventTypeT,
		typename IfcEventTypeEnumT,
		typename IfcExtendedPropertiesT,
		typename IfcExternalInformationT,
		typename IfcExternallyDefinedHatchStyleT,
		typename IfcExternallyDefinedSurfaceStyleT,
		typename IfcExternallyDefinedSymbolT,
		typename IfcExternallyDefinedTextFontT,
		typename IfcExternalReferenceT,
		typename IfcExternalReferenceRelationshipT,
		typename IfcExternalSpatialElementT,
		typename IfcExternalSpatialElementTypeEnumT,
		typename IfcExternalSpatialStructureElementT,
		typename IfcExtrudedAreaSolidT,
		typename IfcExtrudedAreaSolidTaperedT,
		typename IfcFaceT,
		typename IfcFaceBasedSurfaceModelT,
		typename IfcFaceBoundT,
		typename IfcFaceOuterBoundT,
		typename IfcFaceSurfaceT,
		typename IfcFacetedBrepT,
		typename IfcFacetedBrepWithVoidsT,
		typename IfcFailureConnectionConditionT,
		typename IfcFanT,
		typename IfcFanTypeT,
		typename IfcFanTypeEnumT,
		typename IfcFastenerT,
		typename IfcFastenerTypeT,
		typename IfcFastenerTypeEnumT,
		typename IfcFeatureElementT,
		typename IfcFeatureElementAdditionT,
		typename IfcFeatureElementSubtractionT,
		typename IfcFillAreaStyleT,
		typename IfcFillAreaStyleHatchingT,
		typename IfcFillAreaStyleTilesT,
		typename IfcFillAreaStyleTileShapeSelectT,
		typename IfcFillAreaStyleTileSymbolWithStyleT,
		typename IfcFillStyleSelectT,
		typename IfcFilterT,
		typename IfcFilterTypeT,
		typename IfcFilterTypeEnumT,
		typename IfcFireSuppressionTerminalT,
		typename IfcFireSuppressionTerminalTypeT,
		typename IfcFireSuppressionTerminalTypeEnumT,
		typename IfcFixedReferenceSweptAreaSolidT,
		typename IfcFlowControllerT,
		typename IfcFlowControllerTypeT,
		typename IfcFlowDirectionEnumT,
		typename IfcFlowFittingT,
		typename IfcFlowFittingTypeT,
		typename IfcFlowInstrumentT,
		typename IfcFlowInstrumentTypeT,
		typename IfcFlowInstrumentTypeEnumT,
		typename IfcFlowMeterT,
		typename IfcFlowMeterTypeT,
		typename IfcFlowMeterTypeEnumT,
		typename IfcFlowMovingDeviceT,
		typename IfcFlowMovingDeviceTypeT,
		typename IfcFlowSegmentT,
		typename IfcFlowSegmentTypeT,
		typename IfcFlowStorageDeviceT,
		typename IfcFlowStorageDeviceTypeT,
		typename IfcFlowTerminalT,
		typename IfcFlowTerminalTypeT,
		typename IfcFlowTreatmentDeviceT,
		typename IfcFlowTreatmentDeviceTypeT,
		typename IfcFontStyleT,
		typename IfcFontVariantT,
		typename IfcFontWeightT,
		typename IfcFootingT,
		typename IfcFootingTypeT,
		typename IfcFootingTypeEnumT,
		typename IfcForceMeasureT,
		typename IfcFrequencyMeasureT,
		typename IfcFurnishingElementT,
		typename IfcFurnishingElementTypeT,
		typename IfcFurnitureT,
		typename IfcFurnitureTypeT,
		typename IfcFurnitureTypeEnumT,
		typename IfcGeographicElementT,
		typename IfcGeographicElementTypeT,
		typename IfcGeographicElementTypeEnumT,
		typename IfcGeometricCurveSetT,
		typename IfcGeometricProjectionEnumT,
		typename IfcGeometricRepresentationContextT,
		typename IfcGeometricRepresentationItemT,
		typename IfcGeometricRepresentationSubContextT,
		typename IfcGeometricSetT,
		typename IfcGeometricSetSelectT,
		typename IfcGloballyUniqueIdT,
		typename IfcGlobalOrLocalEnumT,
		typename IfcGridT,
		typename IfcGridAxisT,
		typename IfcGridPlacementT,
		typename IfcGridPlacementDirectionSelectT,
		typename IfcGridTypeEnumT,
		typename IfcGroupT,
		typename IfcHalfSpaceSolidT,
		typename IfcHatchLineDistanceSelectT,
		typename IfcHeatExchangerT,
		typename IfcHeatExchangerTypeT,
		typename IfcHeatExchangerTypeEnumT,
		typename IfcHeatFluxDensityMeasureT,
		typename IfcHeatingValueMeasureT,
		typename IfcHumidifierT,
		typename IfcHumidifierTypeT,
		typename IfcHumidifierTypeEnumT,
		typename IfcIdentifierT,
		typename IfcIlluminanceMeasureT,
		typename IfcImageTextureT,
		typename IfcIndexedColourMapT,
		typename IfcIndexedTextureMapT,
		typename IfcIndexedTriangleTextureMapT,
		typename IfcInductanceMeasureT,
		typename IfcIntegerT,
		typename IfcIntegerCountRateMeasureT,
		typename IfcInterceptorT,
		typename IfcInterceptorTypeT,
		typename IfcInterceptorTypeEnumT,
		typename IfcInternalOrExternalEnumT,
		typename IfcInventoryT,
		typename IfcInventoryTypeEnumT,
		typename IfcIonConcentrationMeasureT,
		typename IfcIrregularTimeSeriesT,
		typename IfcIrregularTimeSeriesValueT,
		typename IfcIShapeProfileDefT,
		typename IfcIsothermalMoistureCapacityMeasureT,
		typename IfcJunctionBoxT,
		typename IfcJunctionBoxTypeT,
		typename IfcJunctionBoxTypeEnumT,
		typename IfcKinematicViscosityMeasureT,
		typename IfcKnotTypeT,
		typename IfcLabelT,
		typename IfcLaborResourceT,
		typename IfcLaborResourceTypeT,
		typename IfcLaborResourceTypeEnumT,
		typename IfcLagTimeT,
		typename IfcLampT,
		typename IfcLampTypeT,
		typename IfcLampTypeEnumT,
		typename IfcLanguageIdT,
		typename IfcLayeredItemT,
		typename IfcLayerSetDirectionEnumT,
		typename IfcLengthMeasureT,
		typename IfcLibraryInformationT,
		typename IfcLibraryReferenceT,
		typename IfcLibrarySelectT,
		typename IfcLightDistributionCurveEnumT,
		typename IfcLightDistributionDataT,
		typename IfcLightDistributionDataSourceSelectT,
		typename IfcLightEmissionSourceEnumT,
		typename IfcLightFixtureT,
		typename IfcLightFixtureTypeT,
		typename IfcLightFixtureTypeEnumT,
		typename IfcLightIntensityDistributionT,
		typename IfcLightSourceT,
		typename IfcLightSourceAmbientT,
		typename IfcLightSourceDirectionalT,
		typename IfcLightSourceGoniometricT,
		typename IfcLightSourcePositionalT,
		typename IfcLightSourceSpotT,
		typename IfcLineT,
		typename IfcLinearForceMeasureT,
		typename IfcLinearMomentMeasureT,
		typename IfcLinearStiffnessMeasureT,
		typename IfcLinearVelocityMeasureT,
		typename IfcLoadGroupTypeEnumT,
		typename IfcLocalPlacementT,
		typename IfcLogicalT,
		typename IfcLogicalOperatorEnumT,
		typename IfcLoopT,
		typename IfcLShapeProfileDefT,
		typename IfcLuminousFluxMeasureT,
		typename IfcLuminousIntensityDistributionMeasureT,
		typename IfcLuminousIntensityMeasureT,
		typename IfcMagneticFluxDensityMeasureT,
		typename IfcMagneticFluxMeasureT,
		typename IfcManifoldSolidBrepT,
		typename IfcMapConversionT,
		typename IfcMappedItemT,
		typename IfcMassDensityMeasureT,
		typename IfcMassFlowRateMeasureT,
		typename IfcMassMeasureT,
		typename IfcMassPerLengthMeasureT,
		typename IfcMaterialT,
		typename IfcMaterialClassificationRelationshipT,
		typename IfcMaterialConstituentT,
		typename IfcMaterialConstituentSetT,
		typename IfcMaterialDefinitionT,
		typename IfcMaterialDefinitionRepresentationT,
		typename IfcMaterialLayerT,
		typename IfcMaterialLayerSetT,
		typename IfcMaterialLayerSetUsageT,
		typename IfcMaterialLayerWithOffsetsT,
		typename IfcMaterialListT,
		typename IfcMaterialProfileT,
		typename IfcMaterialProfileSetT,
		typename IfcMaterialProfileSetUsageT,
		typename IfcMaterialProfileSetUsageTaperingT,
		typename IfcMaterialProfileWithOffsetsT,
		typename IfcMaterialPropertiesT,
		typename IfcMaterialRelationshipT,
		typename IfcMaterialSelectT,
		typename IfcMaterialUsageDefinitionT,
		typename IfcMeasureValueT,
		typename IfcMeasureWithUnitT,
		typename IfcMechanicalFastenerT,
		typename IfcMechanicalFastenerTypeT,
		typename IfcMechanicalFastenerTypeEnumT,
		typename IfcMedicalDeviceT,
		typename IfcMedicalDeviceTypeT,
		typename IfcMedicalDeviceTypeEnumT,
		typename IfcMemberT,
		typename IfcMemberStandardCaseT,
		typename IfcMemberTypeT,
		typename IfcMemberTypeEnumT,
		typename IfcMetricT,
		typename IfcMetricValueSelectT,
		typename IfcMirroredProfileDefT,
		typename IfcModulusOfElasticityMeasureT,
		typename IfcModulusOfLinearSubgradeReactionMeasureT,
		typename IfcModulusOfRotationalSubgradeReactionMeasureT,
		typename IfcModulusOfRotationalSubgradeReactionSelectT,
		typename IfcModulusOfSubgradeReactionMeasureT,
		typename IfcModulusOfSubgradeReactionSelectT,
		typename IfcModulusOfTranslationalSubgradeReactionSelectT,
		typename IfcMoistureDiffusivityMeasureT,
		typename IfcMolecularWeightMeasureT,
		typename IfcMomentOfInertiaMeasureT,
		typename IfcMonetaryMeasureT,
		typename IfcMonetaryUnitT,
		typename IfcMonthInYearNumberT,
		typename IfcMotorConnectionT,
		typename IfcMotorConnectionTypeT,
		typename IfcMotorConnectionTypeEnumT,
		typename IfcNamedUnitT,
		typename IfcNonNegativeLengthMeasureT,
		typename IfcNormalisedRatioMeasureT,
		typename IfcNullStyleT,
		typename IfcNumericMeasureT,
		typename IfcObjectT,
		typename IfcObjectDefinitionT,
		typename IfcObjectiveT,
		typename IfcObjectiveEnumT,
		typename IfcObjectPlacementT,
		typename IfcObjectReferenceSelectT,
		typename IfcObjectTypeEnumT,
		typename IfcOccupantT,
		typename IfcOccupantTypeEnumT,
		typename IfcOffsetCurve2DT,
		typename IfcOffsetCurve3DT,
		typename IfcOneDirectionRepeatFactorT,
		typename IfcOpeningElementT,
		typename IfcOpeningElementTypeEnumT,
		typename IfcOpeningStandardCaseT,
		typename IfcOpenShellT,
		typename IfcOrganizationT,
		typename IfcOrganizationRelationshipT,
		typename IfcOrientedEdgeT,
		typename IfcOuterBoundaryCurveT,
		typename IfcOutletT,
		typename IfcOutletTypeT,
		typename IfcOutletTypeEnumT,
		typename IfcOwnerHistoryT,
		typename IfcParameterizedProfileDefT,
		typename IfcParameterValueT,
		typename IfcPathT,
		typename IfcPcurveT,
		typename IfcPerformanceHistoryT,
		typename IfcPerformanceHistoryTypeEnumT,
		typename IfcPermeableCoveringOperationEnumT,
		typename IfcPermeableCoveringPropertiesT,
		typename IfcPermitT,
		typename IfcPermitTypeEnumT,
		typename IfcPersonT,
		typename IfcPersonAndOrganizationT,
		typename IfcPHMeasureT,
		typename IfcPhysicalComplexQuantityT,
		typename IfcPhysicalOrVirtualEnumT,
		typename IfcPhysicalQuantityT,
		typename IfcPhysicalSimpleQuantityT,
		typename IfcPileT,
		typename IfcPileConstructionEnumT,
		typename IfcPileTypeT,
		typename IfcPileTypeEnumT,
		typename IfcPipeFittingT,
		typename IfcPipeFittingTypeT,
		typename IfcPipeFittingTypeEnumT,
		typename IfcPipeSegmentT,
		typename IfcPipeSegmentTypeT,
		typename IfcPipeSegmentTypeEnumT,
		typename IfcPixelTextureT,
		typename IfcPlacementT,
		typename IfcPlanarBoxT,
		typename IfcPlanarExtentT,
		typename IfcPlanarForceMeasureT,
		typename IfcPlaneT,
		typename IfcPlaneAngleMeasureT,
		typename IfcPlateT,
		typename IfcPlateStandardCaseT,
		typename IfcPlateTypeT,
		typename IfcPlateTypeEnumT,
		typename IfcPointT,
		typename IfcPointOnCurveT,
		typename IfcPointOnSurfaceT,
		typename IfcPointOrVertexPointT,
		typename IfcPolygonalBoundedHalfSpaceT,
		typename IfcPolylineT,
		typename IfcPolyLoopT,
		typename IfcPortT,
		typename IfcPositiveLengthMeasureT,
		typename IfcPositivePlaneAngleMeasureT,
		typename IfcPositiveRatioMeasureT,
		typename IfcPostalAddressT,
		typename IfcPowerMeasureT,
		typename IfcPreDefinedColourT,
		typename IfcPreDefinedCurveFontT,
		typename IfcPreDefinedItemT,
		typename IfcPreDefinedPropertiesT,
		typename IfcPreDefinedPropertySetT,
		typename IfcPreDefinedSymbolT,
		typename IfcPreDefinedTextFontT,
		typename IfcPresentableTextT,
		typename IfcPresentationItemT,
		typename IfcPresentationLayerAssignmentT,
		typename IfcPresentationLayerWithStyleT,
		typename IfcPresentationStyleT,
		typename IfcPresentationStyleAssignmentT,
		typename IfcPresentationStyleSelectT,
		typename IfcPressureMeasureT,
		typename IfcProcedureT,
		typename IfcProcedureTypeT,
		typename IfcProcedureTypeEnumT,
		typename IfcProcessT,
		typename IfcProcessSelectT,
		typename IfcProductT,
		typename IfcProductDefinitionShapeT,
		typename IfcProductRepresentationT,
		typename IfcProductSelectT,
		typename IfcProfileDefT,
		typename IfcProfilePropertiesT,
		typename IfcProfileTypeEnumT,
		typename IfcProjectT,
		typename IfcProjectedCRST,
		typename IfcProjectedOrTrueLengthEnumT,
		typename IfcProjectionElementT,
		typename IfcProjectionElementTypeEnumT,
		typename IfcProjectLibraryT,
		typename IfcProjectOrderT,
		typename IfcProjectOrderTypeEnumT,
		typename IfcPropertyT,
		typename IfcPropertyAbstractionT,
		typename IfcPropertyBoundedValueT,
		typename IfcPropertyDefinitionT,
		typename IfcPropertyDependencyRelationshipT,
		typename IfcPropertyEnumeratedValueT,
		typename IfcPropertyEnumerationT,
		typename IfcPropertyListValueT,
		typename IfcPropertyReferenceValueT,
		typename IfcPropertySetT,
		typename IfcPropertySetDefinitionT,
		typename IfcPropertySetTemplateT,
		typename IfcPropertySetTemplateTypeEnumT,
		typename IfcPropertySingleValueT,
		typename IfcPropertyTableValueT,
		typename IfcPropertyTemplateT,
		typename IfcPropertyTemplateDefinitionT,
		typename IfcProtectiveDeviceT,
		typename IfcProtectiveDeviceTrippingUnitT,
		typename IfcProtectiveDeviceTrippingUnitTypeT,
		typename IfcProtectiveDeviceTrippingUnitTypeEnumT,
		typename IfcProtectiveDeviceTypeT,
		typename IfcProtectiveDeviceTypeEnumT,
		typename IfcProxyT,
		typename IfcPumpT,
		typename IfcPumpTypeT,
		typename IfcPumpTypeEnumT,
		typename IfcQuantityAreaT,
		typename IfcQuantityCountT,
		typename IfcQuantityLengthT,
		typename IfcQuantitySetT,
		typename IfcQuantityTimeT,
		typename IfcQuantityVolumeT,
		typename IfcQuantityWeightT,
		typename IfcRadioActivityMeasureT,
		typename IfcRailingT,
		typename IfcRailingTypeT,
		typename IfcRailingTypeEnumT,
		typename IfcRampT,
		typename IfcRampFlightT,
		typename IfcRampFlightTypeT,
		typename IfcRampFlightTypeEnumT,
		typename IfcRampTypeT,
		typename IfcRampTypeEnumT,
		typename IfcRatioMeasureT,
		typename IfcRationalBSplineCurveWithKnotsT,
		typename IfcRationalBSplineSurfaceWithKnotsT,
		typename IfcRealT,
		typename IfcRectangleHollowProfileDefT,
		typename IfcRectangleProfileDefT,
		typename IfcRectangularPyramidT,
		typename IfcRectangularTrimmedSurfaceT,
		typename IfcRecurrencePatternT,
		typename IfcRecurrenceTypeEnumT,
		typename IfcReferenceCurveT,
		typename IfcReferenceCurve3DT,
		typename IfcReferenceCurveAlignment2DT,
		typename IfcReferenceCurvePlacementT,
		typename IfcReferenceCurvePlacementSystemT,
		typename IfcReferencedSectionedSpineT,
		typename IfcReferenceElementT,
		typename IfcReferencePlacementT,
		typename IfcReflectanceMethodEnumT,
		typename IfcRegularTimeSeriesT,
		typename IfcReinforcementBarPropertiesT,
		typename IfcReinforcementDefinitionPropertiesT,
		typename IfcReinforcingBarT,
		typename IfcReinforcingBarRoleEnumT,
		typename IfcReinforcingBarSurfaceEnumT,
		typename IfcReinforcingBarTypeT,
		typename IfcReinforcingBarTypeEnumT,
		typename IfcReinforcingElementT,
		typename IfcReinforcingElementTypeT,
		typename IfcReinforcingMeshT,
		typename IfcReinforcingMeshTypeT,
		typename IfcReinforcingMeshTypeEnumT,
		typename IfcRelAggregatesT,
		typename IfcRelAssignsT,
		typename IfcRelAssignsToActorT,
		typename IfcRelAssignsToControlT,
		typename IfcRelAssignsToGroupT,
		typename IfcRelAssignsToGroupByFactorT,
		typename IfcRelAssignsToProcessT,
		typename IfcRelAssignsToProductT,
		typename IfcRelAssignsToResourceT,
		typename IfcRelAssociatesT,
		typename IfcRelAssociatesApprovalT,
		typename IfcRelAssociatesClassificationT,
		typename IfcRelAssociatesConstraintT,
		typename IfcRelAssociatesDocumentT,
		typename IfcRelAssociatesLibraryT,
		typename IfcRelAssociatesMaterialT,
		typename IfcRelationshipT,
		typename IfcRelConnectsT,
		typename IfcRelConnectsElementsT,
		typename IfcRelConnectsPathElementsT,
		typename IfcRelConnectsPortsT,
		typename IfcRelConnectsPortToElementT,
		typename IfcRelConnectsStructuralActivityT,
		typename IfcRelConnectsStructuralMemberT,
		typename IfcRelConnectsWithEccentricityT,
		typename IfcRelConnectsWithRealizingElementsT,
		typename IfcRelContainedInSpatialStructureT,
		typename IfcRelCoversBldgElementsT,
		typename IfcRelCoversSpacesT,
		typename IfcRelDeclaresT,
		typename IfcRelDecomposesT,
		typename IfcRelDefinesT,
		typename IfcRelDefinesByObjectT,
		typename IfcRelDefinesByPropertiesT,
		typename IfcRelDefinesByTemplateT,
		typename IfcRelDefinesByTypeT,
		typename IfcRelFillsElementT,
		typename IfcRelFlowControlElementsT,
		typename IfcRelInterferesElementsT,
		typename IfcRelNestsT,
		typename IfcRelProjectsElementT,
		typename IfcRelReferencedInSpatialStructureT,
		typename IfcRelSequenceT,
		typename IfcRelServicesBuildingsT,
		typename IfcRelSpaceBoundaryT,
		typename IfcRelSpaceBoundary1stLevelT,
		typename IfcRelSpaceBoundary2ndLevelT,
		typename IfcRelVoidsElementT,
		typename IfcReparametrisedCompositeCurveSegmentT,
		typename IfcRepresentationT,
		typename IfcRepresentationContextT,
		typename IfcRepresentationItemT,
		typename IfcRepresentationMapT,
		typename IfcResourceT,
		typename IfcResourceApprovalRelationshipT,
		typename IfcResourceConstraintRelationshipT,
		typename IfcResourceConsumptionEnumT,
		typename IfcResourceCostT,
		typename IfcResourceLevelRelationshipT,
		typename IfcResourceObjectSelectT,
		typename IfcResourceSelectT,
		typename IfcResourceTimeT,
		typename IfcRevolvedAreaSolidT,
		typename IfcRevolvedAreaSolidTaperedT,
		typename IfcRightCircularConeT,
		typename IfcRightCircularCylinderT,
		typename IfcRoleEnumT,
		typename IfcRoofT,
		typename IfcRoofTypeT,
		typename IfcRoofTypeEnumT,
		typename IfcRootT,
		typename IfcRotationalFrequencyMeasureT,
		typename IfcRotationalMassMeasureT,
		typename IfcRotationalStiffnessMeasureT,
		typename IfcRotationalStiffnessSelectT,
		typename IfcRoundedRectangleProfileDefT,
		typename IfcSanitaryTerminalT,
		typename IfcSanitaryTerminalTypeT,
		typename IfcSanitaryTerminalTypeEnumT,
		typename IfcSchedulingTimeT,
		typename IfcSectionalAreaIntegralMeasureT,
		typename IfcSectionedSpineT,
		typename IfcSectionModulusMeasureT,
		typename IfcSectionPropertiesT,
		typename IfcSectionReinforcementPropertiesT,
		typename IfcSectionTypeEnumT,
		typename IfcSensorT,
		typename IfcSensorTypeT,
		typename IfcSensorTypeEnumT,
		typename IfcSequenceEnumT,
		typename IfcShadingDeviceT,
		typename IfcShadingDeviceTypeT,
		typename IfcShadingDeviceTypeEnumT,
		typename IfcShapeAspectT,
		typename IfcShapeModelT,
		typename IfcShapeRepresentationT,
		typename IfcShearModulusMeasureT,
		typename IfcShellT,
		typename IfcShellBasedSurfaceModelT,
		typename IfcSimplePropertyT,
		typename IfcSimplePropertyTemplateT,
		typename IfcSimplePropertyTemplateTypeEnumT,
		typename IfcSimpleValueT,
		typename IfcSIPrefixT,
		typename IfcSiteT,
		typename IfcSIUnitT,
		typename IfcSIUnitNameT,
		typename IfcSizeSelectT,
		typename IfcSlabT,
		typename IfcSlabElementedCaseT,
		typename IfcSlabStandardCaseT,
		typename IfcSlabTypeT,
		typename IfcSlabTypeEnumT,
		typename IfcSlippageConnectionConditionT,
		typename IfcSolarDeviceT,
		typename IfcSolarDeviceTypeT,
		typename IfcSolarDeviceTypeEnumT,
		typename IfcSolidAngleMeasureT,
		typename IfcSolidModelT,
		typename IfcSolidOrShellT,
		typename IfcSoundPowerMeasureT,
		typename IfcSoundPressureMeasureT,
		typename IfcSpaceT,
		typename IfcSpaceBoundarySelectT,
		typename IfcSpaceHeaterT,
		typename IfcSpaceHeaterTypeT,
		typename IfcSpaceHeaterTypeEnumT,
		typename IfcSpaceTypeT,
		typename IfcSpaceTypeEnumT,
		typename IfcSpatialElementT,
		typename IfcSpatialElementTypeT,
		typename IfcSpatialStructureElementT,
		typename IfcSpatialStructureElementTypeT,
		typename IfcSpatialZoneT,
		typename IfcSpatialZoneTypeT,
		typename IfcSpatialZoneTypeEnumT,
		typename IfcSpecificHeatCapacityMeasureT,
		typename IfcSpecularExponentT,
		typename IfcSpecularHighlightSelectT,
		typename IfcSpecularRoughnessT,
		typename IfcSphereT,
		typename IfcStackTerminalT,
		typename IfcStackTerminalTypeT,
		typename IfcStackTerminalTypeEnumT,
		typename IfcStairT,
		typename IfcStairFlightT,
		typename IfcStairFlightTypeT,
		typename IfcStairFlightTypeEnumT,
		typename IfcStairTypeT,
		typename IfcStairTypeEnumT,
		typename IfcStateEnumT,
		typename IfcStructuralActionT,
		typename IfcStructuralActivityT,
		typename IfcStructuralActivityAssignmentSelectT,
		typename IfcStructuralAnalysisModelT,
		typename IfcStructuralConnectionT,
		typename IfcStructuralConnectionConditionT,
		typename IfcStructuralCurveActionT,
		typename IfcStructuralCurveActivityTypeEnumT,
		typename IfcStructuralCurveConnectionT,
		typename IfcStructuralCurveMemberT,
		typename IfcStructuralCurveMemberTypeEnumT,
		typename IfcStructuralCurveMemberVaryingT,
		typename IfcStructuralCurveReactionT,
		typename IfcStructuralItemT,
		typename IfcStructuralLinearActionT,
		typename IfcStructuralLoadT,
		typename IfcStructuralLoadCaseT,
		typename IfcStructuralLoadConfigurationT,
		typename IfcStructuralLoadGroupT,
		typename IfcStructuralLoadLinearForceT,
		typename IfcStructuralLoadOrResultT,
		typename IfcStructuralLoadPlanarForceT,
		typename IfcStructuralLoadSingleDisplacementT,
		typename IfcStructuralLoadSingleDisplacementDistortionT,
		typename IfcStructuralLoadSingleForceT,
		typename IfcStructuralLoadSingleForceWarpingT,
		typename IfcStructuralLoadStaticT,
		typename IfcStructuralLoadTemperatureT,
		typename IfcStructuralMemberT,
		typename IfcStructuralPlanarActionT,
		typename IfcStructuralPointActionT,
		typename IfcStructuralPointConnectionT,
		typename IfcStructuralPointReactionT,
		typename IfcStructuralReactionT,
		typename IfcStructuralResultGroupT,
		typename IfcStructuralSurfaceActionT,
		typename IfcStructuralSurfaceActivityTypeEnumT,
		typename IfcStructuralSurfaceConnectionT,
		typename IfcStructuralSurfaceMemberT,
		typename IfcStructuralSurfaceMemberTypeEnumT,
		typename IfcStructuralSurfaceMemberVaryingT,
		typename IfcStructuralSurfaceReactionT,
		typename IfcStyleAssignmentSelectT,
		typename IfcStyledItemT,
		typename IfcStyledRepresentationT,
		typename IfcStyleModelT,
		typename IfcSubContractResourceT,
		typename IfcSubContractResourceTypeT,
		typename IfcSubContractResourceTypeEnumT,
		typename IfcSubedgeT,
		typename IfcSurfaceT,
		typename IfcSurfaceCurveSweptAreaSolidT,
		typename IfcSurfaceFeatureT,
		typename IfcSurfaceFeatureTypeEnumT,
		typename IfcSurfaceOfLinearExtrusionT,
		typename IfcSurfaceOfRevolutionT,
		typename IfcSurfaceOrFaceSurfaceT,
		typename IfcSurfaceReinforcementAreaT,
		typename IfcSurfaceSideT,
		typename IfcSurfaceStyleT,
		typename IfcSurfaceStyleElementSelectT,
		typename IfcSurfaceStyleLightingT,
		typename IfcSurfaceStyleRefractionT,
		typename IfcSurfaceStyleRenderingT,
		typename IfcSurfaceStyleShadingT,
		typename IfcSurfaceStyleWithTexturesT,
		typename IfcSurfaceTextureT,
		typename IfcSweptAreaSolidT,
		typename IfcSweptDiskSolidT,
		typename IfcSweptDiskSolidPolygonalT,
		typename IfcSweptSurfaceT,
		typename IfcSwitchingDeviceT,
		typename IfcSwitchingDeviceTypeT,
		typename IfcSwitchingDeviceTypeEnumT,
		typename IfcSymbolStyleT,
		typename IfcSymbolStyleSelectT,
		typename IfcSystemT,
		typename IfcSystemFurnitureElementT,
		typename IfcSystemFurnitureElementTypeT,
		typename IfcSystemFurnitureElementTypeEnumT,
		typename IfcTableT,
		typename IfcTableColumnT,
		typename IfcTableRowT,
		typename IfcTankT,
		typename IfcTankTypeT,
		typename IfcTankTypeEnumT,
		typename IfcTaskT,
		typename IfcTaskDurationEnumT,
		typename IfcTaskTimeT,
		typename IfcTaskTimeRecurringT,
		typename IfcTaskTypeT,
		typename IfcTaskTypeEnumT,
		typename IfcTelecomAddressT,
		typename IfcTemperatureGradientMeasureT,
		typename IfcTemperatureRateOfChangeMeasureT,
		typename IfcTendonT,
		typename IfcTendonAnchorT,
		typename IfcTendonAnchorTypeT,
		typename IfcTendonAnchorTypeEnumT,
		typename IfcTendonTypeT,
		typename IfcTendonTypeEnumT,
		typename IfcTessellatedFaceSetT,
		typename IfcTessellatedItemT,
		typename IfcTextT,
		typename IfcTextAlignmentT,
		typename IfcTextDecorationT,
		typename IfcTextFontNameT,
		typename IfcTextFontSelectT,
		typename IfcTextLiteralT,
		typename IfcTextLiteralWithExtentT,
		typename IfcTextPathT,
		typename IfcTextStyleT,
		typename IfcTextStyleFontModelT,
		typename IfcTextStyleForDefinedFontT,
		typename IfcTextStyleSelectT,
		typename IfcTextStyleTextModelT,
		typename IfcTextStyleWithBoxCharacteristicsT,
		typename IfcTextTransformationT,
		typename IfcTextureCoordinateT,
		typename IfcTextureCoordinateGeneratorT,
		typename IfcTextureMapT,
		typename IfcTextureVertexT,
		typename IfcTextureVertexListT,
		typename IfcThermalAdmittanceMeasureT,
		typename IfcThermalConductivityMeasureT,
		typename IfcThermalExpansionCoefficientMeasureT,
		typename IfcThermalResistanceMeasureT,
		typename IfcThermalTransmittanceMeasureT,
		typename IfcThermodynamicTemperatureMeasureT,
		typename IfcTimeT,
		typename IfcTimeMeasureT,
		typename IfcTimeOrRatioSelectT,
		typename IfcTimePeriodT,
		typename IfcTimeSeriesT,
		typename IfcTimeSeriesDataTypeEnumT,
		typename IfcTimeSeriesValueT,
		typename IfcTimeStampT,
		typename IfcTopologicalRepresentationItemT,
		typename IfcTopologyRepresentationT,
		typename IfcTorqueMeasureT,
		typename IfcTransformerT,
		typename IfcTransformerTypeT,
		typename IfcTransformerTypeEnumT,
		typename IfcTransitionCodeT,
		typename IfcTranslationalStiffnessSelectT,
		typename IfcTransportElementT,
		typename IfcTransportElementTypeT,
		typename IfcTransportElementTypeEnumT,
		typename IfcTrapeziumProfileDefT,
		typename IfcTriangulatedFaceSetT,
		typename IfcTrimmedCurveT,
		typename IfcTrimmingPreferenceT,
		typename IfcTrimmingSelectT,
		typename IfcTShapeProfileDefT,
		typename IfcTubeBundleT,
		typename IfcTubeBundleTypeT,
		typename IfcTubeBundleTypeEnumT,
		typename IfcTwoDirectionRepeatFactorT,
		typename IfcTypeObjectT,
		typename IfcTypeProcessT,
		typename IfcTypeProductT,
		typename IfcTypeResourceT,
		typename IfcUnitT,
		typename IfcUnitaryControlElementT,
		typename IfcUnitaryControlElementTypeT,
		typename IfcUnitaryControlElementTypeEnumT,
		typename IfcUnitaryEquipmentT,
		typename IfcUnitaryEquipmentTypeT,
		typename IfcUnitaryEquipmentTypeEnumT,
		typename IfcUnitAssignmentT,
		typename IfcUnitEnumT,
		typename IfcURIReferenceT,
		typename IfcUShapeProfileDefT,
		typename IfcValueT,
		typename IfcValveT,
		typename IfcValveTypeT,
		typename IfcValveTypeEnumT,
		typename IfcVaporPermeabilityMeasureT,
		typename IfcVectorT,
		typename IfcVectorOrDirectionT,
		typename IfcVertexT,
		typename IfcVertexLoopT,
		typename IfcVertexPointT,
		typename IfcVibrationIsolatorT,
		typename IfcVibrationIsolatorTypeT,
		typename IfcVibrationIsolatorTypeEnumT,
		typename IfcVirtualElementT,
		typename IfcVirtualGridIntersectionT,
		typename IfcVoidingFeatureT,
		typename IfcVoidingFeatureTypeEnumT,
		typename IfcVolumeMeasureT,
		typename IfcVolumetricFlowRateMeasureT,
		typename IfcWallT,
		typename IfcWallElementedCaseT,
		typename IfcWallStandardCaseT,
		typename IfcWallTypeT,
		typename IfcWallTypeEnumT,
		typename IfcWarpingConstantMeasureT,
		typename IfcWarpingMomentMeasureT,
		typename IfcWarpingStiffnessSelectT,
		typename IfcWasteTerminalT,
		typename IfcWasteTerminalTypeT,
		typename IfcWasteTerminalTypeEnumT,
		typename IfcWindowT,
		typename IfcWindowLiningPropertiesT,
		typename IfcWindowPanelOperationEnumT,
		typename IfcWindowPanelPositionEnumT,
		typename IfcWindowPanelPropertiesT,
		typename IfcWindowStandardCaseT,
		typename IfcWindowStyleT,
		typename IfcWindowStyleConstructionEnumT,
		typename IfcWindowStyleOperationEnumT,
		typename IfcWindowTypeT,
		typename IfcWindowTypeEnumT,
		typename IfcWindowTypePartitioningEnumT,
		typename IfcWorkCalendarT,
		typename IfcWorkCalendarTypeEnumT,
		typename IfcWorkControlT,
		typename IfcWorkPlanT,
		typename IfcWorkPlanTypeEnumT,
		typename IfcWorkScheduleT,
		typename IfcWorkScheduleTypeEnumT,
		typename IfcWorkTimeT,
		typename IfcZoneT,
		typename IfcZShapeProfileDefT
	>
	struct BasicIfcBridgeEntityTypes
	{
		typedef IfcAbsorbedDoseMeasureT IfcAbsorbedDoseMeasure;
		typedef IfcAccelerationMeasureT IfcAccelerationMeasure;
		typedef IfcActionRequestT IfcActionRequest;
		typedef IfcActionRequestTypeEnumT IfcActionRequestTypeEnum;
		typedef IfcActionSourceTypeEnumT IfcActionSourceTypeEnum;
		typedef IfcActionTypeEnumT IfcActionTypeEnum;
		typedef IfcActorT IfcActor;
		typedef IfcActorRoleT IfcActorRole;
		typedef IfcActorSelectT IfcActorSelect;
		typedef IfcActuatorT IfcActuator;
		typedef IfcActuatorTypeT IfcActuatorType;
		typedef IfcActuatorTypeEnumT IfcActuatorTypeEnum;
		typedef IfcAddressT IfcAddress;
		typedef IfcAddressTypeEnumT IfcAddressTypeEnum;
		typedef IfcAdvancedBrepT IfcAdvancedBrep;
		typedef IfcAdvancedBrepWithVoidsT IfcAdvancedBrepWithVoids;
		typedef IfcAdvancedFaceT IfcAdvancedFace;
		typedef IfcAirTerminalT IfcAirTerminal;
		typedef IfcAirTerminalBoxT IfcAirTerminalBox;
		typedef IfcAirTerminalBoxTypeT IfcAirTerminalBoxType;
		typedef IfcAirTerminalBoxTypeEnumT IfcAirTerminalBoxTypeEnum;
		typedef IfcAirTerminalTypeT IfcAirTerminalType;
		typedef IfcAirTerminalTypeEnumT IfcAirTerminalTypeEnum;
		typedef IfcAirToAirHeatRecoveryT IfcAirToAirHeatRecovery;
		typedef IfcAirToAirHeatRecoveryTypeT IfcAirToAirHeatRecoveryType;
		typedef IfcAirToAirHeatRecoveryTypeEnumT IfcAirToAirHeatRecoveryTypeEnum;
		typedef IfcAlarmT IfcAlarm;
		typedef IfcAlarmTypeT IfcAlarmType;
		typedef IfcAlarmTypeEnumT IfcAlarmTypeEnum;
		typedef IfcAlignmentElementT IfcAlignmentElement;
		typedef IfcAmountOfSubstanceMeasureT IfcAmountOfSubstanceMeasure;
		typedef IfcAnalysisModelTypeEnumT IfcAnalysisModelTypeEnum;
		typedef IfcAnalysisTheoryTypeEnumT IfcAnalysisTheoryTypeEnum;
		typedef IfcAngularVelocityMeasureT IfcAngularVelocityMeasure;
		typedef IfcAnnotationT IfcAnnotation;
		typedef IfcAnnotationFillAreaT IfcAnnotationFillArea;
		typedef IfcApplicationT IfcApplication;
		typedef IfcAppliedValueT IfcAppliedValue;
		typedef IfcAppliedValueRelationshipT IfcAppliedValueRelationship;
		typedef IfcAppliedValueSelectT IfcAppliedValueSelect;
		typedef IfcApprovalT IfcApproval;
		typedef IfcApprovalRelationshipT IfcApprovalRelationship;
		typedef IfcArbitraryClosedProfileDefT IfcArbitraryClosedProfileDef;
		typedef IfcArbitraryOpenProfileDefT IfcArbitraryOpenProfileDef;
		typedef IfcArbitraryProfileDefWithVoidsT IfcArbitraryProfileDefWithVoids;
		typedef IfcAreaMeasureT IfcAreaMeasure;
		typedef IfcArithmeticOperatorEnumT IfcArithmeticOperatorEnum;
		typedef IfcAssemblyPlaceEnumT IfcAssemblyPlaceEnum;
		typedef IfcAssetT IfcAsset;
		typedef IfcAsymmetricIShapeProfileDefT IfcAsymmetricIShapeProfileDef;
		typedef IfcAudioVisualApplianceT IfcAudioVisualAppliance;
		typedef IfcAudioVisualApplianceTypeT IfcAudioVisualApplianceType;
		typedef IfcAudioVisualApplianceTypeEnumT IfcAudioVisualApplianceTypeEnum;
		typedef IfcAxis1PlacementT IfcAxis1Placement;
		typedef IfcAxis2PlacementT IfcAxis2Placement;
		typedef IfcAxis2Placement2DT IfcAxis2Placement2D;
		typedef IfcAxis2Placement3DT IfcAxis2Placement3D;
		typedef IfcBeamT IfcBeam;
		typedef IfcBeamStandardCaseT IfcBeamStandardCase;
		typedef IfcBeamTypeT IfcBeamType;
		typedef IfcBeamTypeEnumT IfcBeamTypeEnum;
		typedef IfcBenchmarkEnumT IfcBenchmarkEnum;
		typedef IfcBendingParameterSelectT IfcBendingParameterSelect;
		typedef IfcBlobTextureT IfcBlobTexture;
		typedef IfcBlockT IfcBlock;
		typedef IfcBoilerT IfcBoiler;
		typedef IfcBoilerTypeT IfcBoilerType;
		typedef IfcBoilerTypeEnumT IfcBoilerTypeEnum;
		typedef IfcBooleanT IfcBoolean;
		typedef IfcBooleanClippingResultT IfcBooleanClippingResult;
		typedef IfcBooleanOperandT IfcBooleanOperand;
		typedef IfcBooleanOperatorT IfcBooleanOperator;
		typedef IfcBooleanResultT IfcBooleanResult;
		typedef IfcBoundaryConditionT IfcBoundaryCondition;
		typedef IfcBoundaryCurveT IfcBoundaryCurve;
		typedef IfcBoundaryEdgeConditionT IfcBoundaryEdgeCondition;
		typedef IfcBoundaryFaceConditionT IfcBoundaryFaceCondition;
		typedef IfcBoundaryNodeConditionT IfcBoundaryNodeCondition;
		typedef IfcBoundaryNodeConditionWarpingT IfcBoundaryNodeConditionWarping;
		typedef IfcBoundedCurveT IfcBoundedCurve;
		typedef IfcBoundedSurfaceT IfcBoundedSurface;
		typedef IfcBoundingBoxT IfcBoundingBox;
		typedef IfcBoxAlignmentT IfcBoxAlignment;
		typedef IfcBoxedHalfSpaceT IfcBoxedHalfSpace;
		typedef IfcBridgeT IfcBridge;
		typedef IfcBridgeContactElementT IfcBridgeContactElement;
		typedef IfcBridgeContactTypeT IfcBridgeContactType;
		typedef IfcBridgeElementT IfcBridgeElement;
		typedef IfcBridgeMechanicalRoleTypeT IfcBridgeMechanicalRoleType;
		typedef IfcBridgePartT IfcBridgePart;
		typedef IfcBridgePrismaticElementT IfcBridgePrismaticElement;
		typedef IfcBridgePrismaticElementTypeT IfcBridgePrismaticElementType;
		typedef IfcBridgeSegmentT IfcBridgeSegment;
		typedef IfcBridgeSegmentPartT IfcBridgeSegmentPart;
		typedef IfcBridgeSegmentTypeT IfcBridgeSegmentType;
		typedef IfcBridgeStructureElementT IfcBridgeStructureElement;
		typedef IfcBridgeStructureElementTypeT IfcBridgeStructureElementType;
		typedef IfcBridgeStructureIndicatorT IfcBridgeStructureIndicator;
		typedef IfcBridgeStructureTypeT IfcBridgeStructureType;
		typedef IfcBridgeSubPartTypeT IfcBridgeSubPartType;
		typedef IfcBridgeTechnologicalElementTypeT IfcBridgeTechnologicalElementType;
		typedef IfcBSplineCurveT IfcBSplineCurve;
		typedef IfcBSplineCurveFormT IfcBSplineCurveForm;
		typedef IfcBSplineCurveWithKnotsT IfcBSplineCurveWithKnots;
		typedef IfcBSplineSurfaceT IfcBSplineSurface;
		typedef IfcBSplineSurfaceFormT IfcBSplineSurfaceForm;
		typedef IfcBSplineSurfaceWithKnotsT IfcBSplineSurfaceWithKnots;
		typedef IfcBuildingT IfcBuilding;
		typedef IfcBuildingElementT IfcBuildingElement;
		typedef IfcBuildingElementPartT IfcBuildingElementPart;
		typedef IfcBuildingElementPartTypeT IfcBuildingElementPartType;
		typedef IfcBuildingElementPartTypeEnumT IfcBuildingElementPartTypeEnum;
		typedef IfcBuildingElementProxyT IfcBuildingElementProxy;
		typedef IfcBuildingElementProxyTypeT IfcBuildingElementProxyType;
		typedef IfcBuildingElementProxyTypeEnumT IfcBuildingElementProxyTypeEnum;
		typedef IfcBuildingElementTypeT IfcBuildingElementType;
		typedef IfcBuildingStoreyT IfcBuildingStorey;
		typedef IfcBuildingSystemT IfcBuildingSystem;
		typedef IfcBuildingSystemTypeEnumT IfcBuildingSystemTypeEnum;
		typedef IfcBurnerT IfcBurner;
		typedef IfcBurnerTypeT IfcBurnerType;
		typedef IfcBurnerTypeEnumT IfcBurnerTypeEnum;
		typedef IfcCableCarrierFittingT IfcCableCarrierFitting;
		typedef IfcCableCarrierFittingTypeT IfcCableCarrierFittingType;
		typedef IfcCableCarrierFittingTypeEnumT IfcCableCarrierFittingTypeEnum;
		typedef IfcCableCarrierSegmentT IfcCableCarrierSegment;
		typedef IfcCableCarrierSegmentTypeT IfcCableCarrierSegmentType;
		typedef IfcCableCarrierSegmentTypeEnumT IfcCableCarrierSegmentTypeEnum;
		typedef IfcCableFittingT IfcCableFitting;
		typedef IfcCableFittingTypeT IfcCableFittingType;
		typedef IfcCableFittingTypeEnumT IfcCableFittingTypeEnum;
		typedef IfcCableSegmentT IfcCableSegment;
		typedef IfcCableSegmentTypeT IfcCableSegmentType;
		typedef IfcCableSegmentTypeEnumT IfcCableSegmentTypeEnum;
		typedef IfcCardinalPointReferenceT IfcCardinalPointReference;
		typedef IfcCartesianPointT IfcCartesianPoint;
		typedef IfcCartesianPointListT IfcCartesianPointList;
		typedef IfcCartesianTransformationOperatorT IfcCartesianTransformationOperator;
		typedef IfcCartesianTransformationOperator2DT IfcCartesianTransformationOperator2D;
		typedef IfcCartesianTransformationOperator2DnonUniformT IfcCartesianTransformationOperator2DnonUniform;
		typedef IfcCartesianTransformationOperator3DT IfcCartesianTransformationOperator3D;
		typedef IfcCartesianTransformationOperator3DnonUniformT IfcCartesianTransformationOperator3DnonUniform;
		typedef IfcCenterLineProfileDefT IfcCenterLineProfileDef;
		typedef IfcChangeActionEnumT IfcChangeActionEnum;
		typedef IfcCharacterStyleSelectT IfcCharacterStyleSelect;
		typedef IfcChillerT IfcChiller;
		typedef IfcChillerTypeT IfcChillerType;
		typedef IfcChillerTypeEnumT IfcChillerTypeEnum;
		typedef IfcChimneyT IfcChimney;
		typedef IfcChimneyTypeT IfcChimneyType;
		typedef IfcChimneyTypeEnumT IfcChimneyTypeEnum;
		typedef IfcCircleT IfcCircle;
		typedef IfcCircleHollowProfileDefT IfcCircleHollowProfileDef;
		typedef IfcCircleProfileDefT IfcCircleProfileDef;
		typedef IfcCivilElementT IfcCivilElement;
		typedef IfcCivilElementPartT IfcCivilElementPart;
		typedef IfcCivilSheathT IfcCivilSheath;
		typedef IfcCivilStructureElementT IfcCivilStructureElement;
		typedef IfcCivilVoidT IfcCivilVoid;
		typedef IfcClassificationT IfcClassification;
		typedef IfcClassificationReferenceT IfcClassificationReference;
		typedef IfcClassificationReferenceSelectT IfcClassificationReferenceSelect;
		typedef IfcClassificationSelectT IfcClassificationSelect;
		typedef IfcClosedShellT IfcClosedShell;
		typedef IfcClothoidT IfcClothoid;
		typedef IfcCoilT IfcCoil;
		typedef IfcCoilTypeT IfcCoilType;
		typedef IfcCoilTypeEnumT IfcCoilTypeEnum;
		typedef IfcColourT IfcColour;
		typedef IfcColourOrFactorT IfcColourOrFactor;
		typedef IfcColourRgbT IfcColourRgb;
		typedef IfcColourRgbListT IfcColourRgbList;
		typedef IfcColourSpecificationT IfcColourSpecification;
		typedef IfcColumnT IfcColumn;
		typedef IfcColumnStandardCaseT IfcColumnStandardCase;
		typedef IfcColumnTypeT IfcColumnType;
		typedef IfcColumnTypeEnumT IfcColumnTypeEnum;
		typedef IfcCommunicationsApplianceT IfcCommunicationsAppliance;
		typedef IfcCommunicationsApplianceTypeT IfcCommunicationsApplianceType;
		typedef IfcCommunicationsApplianceTypeEnumT IfcCommunicationsApplianceTypeEnum;
		typedef IfcComplexNumberT IfcComplexNumber;
		typedef IfcComplexPropertyT IfcComplexProperty;
		typedef IfcComplexPropertyTemplateT IfcComplexPropertyTemplate;
		typedef IfcComplexPropertyTemplateTypeEnumT IfcComplexPropertyTemplateTypeEnum;
		typedef IfcCompositeCurveT IfcCompositeCurve;
		typedef IfcCompositeCurveOnSurfaceT IfcCompositeCurveOnSurface;
		typedef IfcCompositeCurveSegmentT IfcCompositeCurveSegment;
		typedef IfcCompositeProfileDefT IfcCompositeProfileDef;
		typedef IfcCompoundPlaneAngleMeasureT IfcCompoundPlaneAngleMeasure;
		typedef IfcCompressorT IfcCompressor;
		typedef IfcCompressorTypeT IfcCompressorType;
		typedef IfcCompressorTypeEnumT IfcCompressorTypeEnum;
		typedef IfcCondenserT IfcCondenser;
		typedef IfcCondenserTypeT IfcCondenserType;
		typedef IfcCondenserTypeEnumT IfcCondenserTypeEnum;
		typedef IfcConicT IfcConic;
		typedef IfcConnectedFaceSetT IfcConnectedFaceSet;
		typedef IfcConnectionCurveGeometryT IfcConnectionCurveGeometry;
		typedef IfcConnectionGeometryT IfcConnectionGeometry;
		typedef IfcConnectionPointEccentricityT IfcConnectionPointEccentricity;
		typedef IfcConnectionPointGeometryT IfcConnectionPointGeometry;
		typedef IfcConnectionSurfaceGeometryT IfcConnectionSurfaceGeometry;
		typedef IfcConnectionTypeEnumT IfcConnectionTypeEnum;
		typedef IfcConnectionVolumeGeometryT IfcConnectionVolumeGeometry;
		typedef IfcConstraintT IfcConstraint;
		typedef IfcConstraintEnumT IfcConstraintEnum;
		typedef IfcConstructionEquipmentResourceT IfcConstructionEquipmentResource;
		typedef IfcConstructionEquipmentResourceTypeT IfcConstructionEquipmentResourceType;
		typedef IfcConstructionEquipmentResourceTypeEnumT IfcConstructionEquipmentResourceTypeEnum;
		typedef IfcConstructionMaterialResourceT IfcConstructionMaterialResource;
		typedef IfcConstructionMaterialResourceTypeT IfcConstructionMaterialResourceType;
		typedef IfcConstructionMaterialResourceTypeEnumT IfcConstructionMaterialResourceTypeEnum;
		typedef IfcConstructionProductResourceT IfcConstructionProductResource;
		typedef IfcConstructionProductResourceTypeT IfcConstructionProductResourceType;
		typedef IfcConstructionProductResourceTypeEnumT IfcConstructionProductResourceTypeEnum;
		typedef IfcConstructionResourceT IfcConstructionResource;
		typedef IfcConstructionResourceTypeT IfcConstructionResourceType;
		typedef IfcContextT IfcContext;
		typedef IfcContextDependentMeasureT IfcContextDependentMeasure;
		typedef IfcContextDependentUnitT IfcContextDependentUnit;
		typedef IfcControlT IfcControl;
		typedef IfcControllerT IfcController;
		typedef IfcControllerTypeT IfcControllerType;
		typedef IfcControllerTypeEnumT IfcControllerTypeEnum;
		typedef IfcConversionBasedUnitT IfcConversionBasedUnit;
		typedef IfcConversionBasedUnitWithOffsetT IfcConversionBasedUnitWithOffset;
		typedef IfcCooledBeamT IfcCooledBeam;
		typedef IfcCooledBeamTypeT IfcCooledBeamType;
		typedef IfcCooledBeamTypeEnumT IfcCooledBeamTypeEnum;
		typedef IfcCoolingTowerT IfcCoolingTower;
		typedef IfcCoolingTowerTypeT IfcCoolingTowerType;
		typedef IfcCoolingTowerTypeEnumT IfcCoolingTowerTypeEnum;
		typedef IfcCoordinateOperationT IfcCoordinateOperation;
		typedef IfcCoordinateReferenceSystemT IfcCoordinateReferenceSystem;
		typedef IfcCoordinateReferenceSystemSelectT IfcCoordinateReferenceSystemSelect;
		typedef IfcCostItemT IfcCostItem;
		typedef IfcCostItemTypeEnumT IfcCostItemTypeEnum;
		typedef IfcCostScheduleT IfcCostSchedule;
		typedef IfcCostScheduleTypeEnumT IfcCostScheduleTypeEnum;
		typedef IfcCostValueT IfcCostValue;
		typedef IfcCountMeasureT IfcCountMeasure;
		typedef IfcCoveringT IfcCovering;
		typedef IfcCoveringTypeT IfcCoveringType;
		typedef IfcCoveringTypeEnumT IfcCoveringTypeEnum;
		typedef IfcCrewResourceT IfcCrewResource;
		typedef IfcCrewResourceTypeT IfcCrewResourceType;
		typedef IfcCrewResourceTypeEnumT IfcCrewResourceTypeEnum;
		typedef IfcCsgPrimitive3DT IfcCsgPrimitive3D;
		typedef IfcCsgSelectT IfcCsgSelect;
		typedef IfcCsgSolidT IfcCsgSolid;
		typedef IfcCShapeProfileDefT IfcCShapeProfileDef;
		typedef IfcCurrencyRelationshipT IfcCurrencyRelationship;
		typedef IfcCurtainWallT IfcCurtainWall;
		typedef IfcCurtainWallTypeT IfcCurtainWallType;
		typedef IfcCurtainWallTypeEnumT IfcCurtainWallTypeEnum;
		typedef IfcCurvatureMeasureT IfcCurvatureMeasure;
		typedef IfcCurveT IfcCurve;
		typedef IfcCurveBoundedPlaneT IfcCurveBoundedPlane;
		typedef IfcCurveBoundedSurfaceT IfcCurveBoundedSurface;
		typedef IfcCurveFontOrScaledCurveFontSelectT IfcCurveFontOrScaledCurveFontSelect;
		typedef IfcCurveInterpolationEnumT IfcCurveInterpolationEnum;
		typedef IfcCurveOnSurfaceT IfcCurveOnSurface;
		typedef IfcCurveOrEdgeCurveT IfcCurveOrEdgeCurve;
		typedef IfcCurveStyleT IfcCurveStyle;
		typedef IfcCurveStyleFontT IfcCurveStyleFont;
		typedef IfcCurveStyleFontAndScalingT IfcCurveStyleFontAndScaling;
		typedef IfcCurveStyleFontPatternT IfcCurveStyleFontPattern;
		typedef IfcCurveStyleFontSelectT IfcCurveStyleFontSelect;
		typedef IfcCylindricalSurfaceT IfcCylindricalSurface;
		typedef IfcDamperT IfcDamper;
		typedef IfcDamperTypeT IfcDamperType;
		typedef IfcDamperTypeEnumT IfcDamperTypeEnum;
		typedef IfcDataOriginEnumT IfcDataOriginEnum;
		typedef IfcDateT IfcDate;
		typedef IfcDateTimeT IfcDateTime;
		typedef IfcDayInMonthNumberT IfcDayInMonthNumber;
		typedef IfcDayInWeekNumberT IfcDayInWeekNumber;
		typedef IfcDefinedSymbolT IfcDefinedSymbol;
		typedef IfcDefinedSymbolSelectT IfcDefinedSymbolSelect;
		typedef IfcDefinitionSelectT IfcDefinitionSelect;
		typedef IfcDerivedMeasureValueT IfcDerivedMeasureValue;
		typedef IfcDerivedProfileDefT IfcDerivedProfileDef;
		typedef IfcDerivedUnitT IfcDerivedUnit;
		typedef IfcDerivedUnitElementT IfcDerivedUnitElement;
		typedef IfcDerivedUnitEnumT IfcDerivedUnitEnum;
		typedef IfcDescriptiveMeasureT IfcDescriptiveMeasure;
		typedef IfcDimensionalExponentsT IfcDimensionalExponents;
		typedef IfcDimensionCountT IfcDimensionCount;
		typedef IfcDirectionT IfcDirection;
		typedef IfcDirectionListT IfcDirectionList;
		typedef IfcDirectionSenseEnumT IfcDirectionSenseEnum;
		typedef IfcDiscreteAccessoryT IfcDiscreteAccessory;
		typedef IfcDiscreteAccessoryTypeT IfcDiscreteAccessoryType;
		typedef IfcDiscreteAccessoryTypeEnumT IfcDiscreteAccessoryTypeEnum;
		typedef IfcDistributionChamberElementT IfcDistributionChamberElement;
		typedef IfcDistributionChamberElementTypeT IfcDistributionChamberElementType;
		typedef IfcDistributionChamberElementTypeEnumT IfcDistributionChamberElementTypeEnum;
		typedef IfcDistributionCircuitT IfcDistributionCircuit;
		typedef IfcDistributionControlElementT IfcDistributionControlElement;
		typedef IfcDistributionControlElementTypeT IfcDistributionControlElementType;
		typedef IfcDistributionElementT IfcDistributionElement;
		typedef IfcDistributionElementTypeT IfcDistributionElementType;
		typedef IfcDistributionFlowElementT IfcDistributionFlowElement;
		typedef IfcDistributionFlowElementTypeT IfcDistributionFlowElementType;
		typedef IfcDistributionPortT IfcDistributionPort;
		typedef IfcDistributionSystemT IfcDistributionSystem;
		typedef IfcDistributionSystemEnumT IfcDistributionSystemEnum;
		typedef IfcDocumentConfidentialityEnumT IfcDocumentConfidentialityEnum;
		typedef IfcDocumentElectronicFormatT IfcDocumentElectronicFormat;
		typedef IfcDocumentInformationT IfcDocumentInformation;
		typedef IfcDocumentInformationRelationshipT IfcDocumentInformationRelationship;
		typedef IfcDocumentReferenceT IfcDocumentReference;
		typedef IfcDocumentSelectT IfcDocumentSelect;
		typedef IfcDocumentStatusEnumT IfcDocumentStatusEnum;
		typedef IfcDoorT IfcDoor;
		typedef IfcDoorLiningPropertiesT IfcDoorLiningProperties;
		typedef IfcDoorPanelOperationEnumT IfcDoorPanelOperationEnum;
		typedef IfcDoorPanelPositionEnumT IfcDoorPanelPositionEnum;
		typedef IfcDoorPanelPropertiesT IfcDoorPanelProperties;
		typedef IfcDoorStandardCaseT IfcDoorStandardCase;
		typedef IfcDoorStyleT IfcDoorStyle;
		typedef IfcDoorStyleConstructionEnumT IfcDoorStyleConstructionEnum;
		typedef IfcDoorStyleOperationEnumT IfcDoorStyleOperationEnum;
		typedef IfcDoorTypeT IfcDoorType;
		typedef IfcDoorTypeEnumT IfcDoorTypeEnum;
		typedef IfcDoorTypeOperationEnumT IfcDoorTypeOperationEnum;
		typedef IfcDoseEquivalentMeasureT IfcDoseEquivalentMeasure;
		typedef IfcDraughtingPreDefinedColourT IfcDraughtingPreDefinedColour;
		typedef IfcDraughtingPreDefinedCurveFontT IfcDraughtingPreDefinedCurveFont;
		typedef IfcDraughtingPreDefinedTextFontT IfcDraughtingPreDefinedTextFont;
		typedef IfcDuctFittingT IfcDuctFitting;
		typedef IfcDuctFittingTypeT IfcDuctFittingType;
		typedef IfcDuctFittingTypeEnumT IfcDuctFittingTypeEnum;
		typedef IfcDuctSegmentT IfcDuctSegment;
		typedef IfcDuctSegmentTypeT IfcDuctSegmentType;
		typedef IfcDuctSegmentTypeEnumT IfcDuctSegmentTypeEnum;
		typedef IfcDuctSilencerT IfcDuctSilencer;
		typedef IfcDuctSilencerTypeT IfcDuctSilencerType;
		typedef IfcDuctSilencerTypeEnumT IfcDuctSilencerTypeEnum;
		typedef IfcDurationT IfcDuration;
		typedef IfcDynamicViscosityMeasureT IfcDynamicViscosityMeasure;
		typedef IfcEdgeT IfcEdge;
		typedef IfcEdgeCurveT IfcEdgeCurve;
		typedef IfcEdgeLoopT IfcEdgeLoop;
		typedef IfcElectricApplianceT IfcElectricAppliance;
		typedef IfcElectricApplianceTypeT IfcElectricApplianceType;
		typedef IfcElectricApplianceTypeEnumT IfcElectricApplianceTypeEnum;
		typedef IfcElectricCapacitanceMeasureT IfcElectricCapacitanceMeasure;
		typedef IfcElectricChargeMeasureT IfcElectricChargeMeasure;
		typedef IfcElectricConductanceMeasureT IfcElectricConductanceMeasure;
		typedef IfcElectricCurrentMeasureT IfcElectricCurrentMeasure;
		typedef IfcElectricDistributionBoardT IfcElectricDistributionBoard;
		typedef IfcElectricDistributionBoardTypeT IfcElectricDistributionBoardType;
		typedef IfcElectricDistributionBoardTypeEnumT IfcElectricDistributionBoardTypeEnum;
		typedef IfcElectricFlowStorageDeviceT IfcElectricFlowStorageDevice;
		typedef IfcElectricFlowStorageDeviceTypeT IfcElectricFlowStorageDeviceType;
		typedef IfcElectricFlowStorageDeviceTypeEnumT IfcElectricFlowStorageDeviceTypeEnum;
		typedef IfcElectricGeneratorT IfcElectricGenerator;
		typedef IfcElectricGeneratorTypeT IfcElectricGeneratorType;
		typedef IfcElectricGeneratorTypeEnumT IfcElectricGeneratorTypeEnum;
		typedef IfcElectricMotorT IfcElectricMotor;
		typedef IfcElectricMotorTypeT IfcElectricMotorType;
		typedef IfcElectricMotorTypeEnumT IfcElectricMotorTypeEnum;
		typedef IfcElectricResistanceMeasureT IfcElectricResistanceMeasure;
		typedef IfcElectricTimeControlT IfcElectricTimeControl;
		typedef IfcElectricTimeControlTypeT IfcElectricTimeControlType;
		typedef IfcElectricTimeControlTypeEnumT IfcElectricTimeControlTypeEnum;
		typedef IfcElectricVoltageMeasureT IfcElectricVoltageMeasure;
		typedef IfcElementT IfcElement;
		typedef IfcElementarySurfaceT IfcElementarySurface;
		typedef IfcElementAssemblyT IfcElementAssembly;
		typedef IfcElementAssemblyTypeT IfcElementAssemblyType;
		typedef IfcElementAssemblyTypeEnumT IfcElementAssemblyTypeEnum;
		typedef IfcElementComponentT IfcElementComponent;
		typedef IfcElementComponentTypeT IfcElementComponentType;
		typedef IfcElementCompositionEnumT IfcElementCompositionEnum;
		typedef IfcElementPartT IfcElementPart;
		typedef IfcElementQuantityT IfcElementQuantity;
		typedef IfcElementTypeT IfcElementType;
		typedef IfcEllipseT IfcEllipse;
		typedef IfcEllipseProfileDefT IfcEllipseProfileDef;
		typedef IfcEnergyConversionDeviceT IfcEnergyConversionDevice;
		typedef IfcEnergyConversionDeviceTypeT IfcEnergyConversionDeviceType;
		typedef IfcEnergyMeasureT IfcEnergyMeasure;
		typedef IfcEngineT IfcEngine;
		typedef IfcEngineTypeT IfcEngineType;
		typedef IfcEngineTypeEnumT IfcEngineTypeEnum;
		typedef IfcEvaporativeCoolerT IfcEvaporativeCooler;
		typedef IfcEvaporativeCoolerTypeT IfcEvaporativeCoolerType;
		typedef IfcEvaporativeCoolerTypeEnumT IfcEvaporativeCoolerTypeEnum;
		typedef IfcEvaporatorT IfcEvaporator;
		typedef IfcEvaporatorTypeT IfcEvaporatorType;
		typedef IfcEvaporatorTypeEnumT IfcEvaporatorTypeEnum;
		typedef IfcEventT IfcEvent;
		typedef IfcEventTimeT IfcEventTime;
		typedef IfcEventTriggerTypeEnumT IfcEventTriggerTypeEnum;
		typedef IfcEventTypeT IfcEventType;
		typedef IfcEventTypeEnumT IfcEventTypeEnum;
		typedef IfcExtendedPropertiesT IfcExtendedProperties;
		typedef IfcExternalInformationT IfcExternalInformation;
		typedef IfcExternallyDefinedHatchStyleT IfcExternallyDefinedHatchStyle;
		typedef IfcExternallyDefinedSurfaceStyleT IfcExternallyDefinedSurfaceStyle;
		typedef IfcExternallyDefinedSymbolT IfcExternallyDefinedSymbol;
		typedef IfcExternallyDefinedTextFontT IfcExternallyDefinedTextFont;
		typedef IfcExternalReferenceT IfcExternalReference;
		typedef IfcExternalReferenceRelationshipT IfcExternalReferenceRelationship;
		typedef IfcExternalSpatialElementT IfcExternalSpatialElement;
		typedef IfcExternalSpatialElementTypeEnumT IfcExternalSpatialElementTypeEnum;
		typedef IfcExternalSpatialStructureElementT IfcExternalSpatialStructureElement;
		typedef IfcExtrudedAreaSolidT IfcExtrudedAreaSolid;
		typedef IfcExtrudedAreaSolidTaperedT IfcExtrudedAreaSolidTapered;
		typedef IfcFaceT IfcFace;
		typedef IfcFaceBasedSurfaceModelT IfcFaceBasedSurfaceModel;
		typedef IfcFaceBoundT IfcFaceBound;
		typedef IfcFaceOuterBoundT IfcFaceOuterBound;
		typedef IfcFaceSurfaceT IfcFaceSurface;
		typedef IfcFacetedBrepT IfcFacetedBrep;
		typedef IfcFacetedBrepWithVoidsT IfcFacetedBrepWithVoids;
		typedef IfcFailureConnectionConditionT IfcFailureConnectionCondition;
		typedef IfcFanT IfcFan;
		typedef IfcFanTypeT IfcFanType;
		typedef IfcFanTypeEnumT IfcFanTypeEnum;
		typedef IfcFastenerT IfcFastener;
		typedef IfcFastenerTypeT IfcFastenerType;
		typedef IfcFastenerTypeEnumT IfcFastenerTypeEnum;
		typedef IfcFeatureElementT IfcFeatureElement;
		typedef IfcFeatureElementAdditionT IfcFeatureElementAddition;
		typedef IfcFeatureElementSubtractionT IfcFeatureElementSubtraction;
		typedef IfcFillAreaStyleT IfcFillAreaStyle;
		typedef IfcFillAreaStyleHatchingT IfcFillAreaStyleHatching;
		typedef IfcFillAreaStyleTilesT IfcFillAreaStyleTiles;
		typedef IfcFillAreaStyleTileShapeSelectT IfcFillAreaStyleTileShapeSelect;
		typedef IfcFillAreaStyleTileSymbolWithStyleT IfcFillAreaStyleTileSymbolWithStyle;
		typedef IfcFillStyleSelectT IfcFillStyleSelect;
		typedef IfcFilterT IfcFilter;
		typedef IfcFilterTypeT IfcFilterType;
		typedef IfcFilterTypeEnumT IfcFilterTypeEnum;
		typedef IfcFireSuppressionTerminalT IfcFireSuppressionTerminal;
		typedef IfcFireSuppressionTerminalTypeT IfcFireSuppressionTerminalType;
		typedef IfcFireSuppressionTerminalTypeEnumT IfcFireSuppressionTerminalTypeEnum;
		typedef IfcFixedReferenceSweptAreaSolidT IfcFixedReferenceSweptAreaSolid;
		typedef IfcFlowControllerT IfcFlowController;
		typedef IfcFlowControllerTypeT IfcFlowControllerType;
		typedef IfcFlowDirectionEnumT IfcFlowDirectionEnum;
		typedef IfcFlowFittingT IfcFlowFitting;
		typedef IfcFlowFittingTypeT IfcFlowFittingType;
		typedef IfcFlowInstrumentT IfcFlowInstrument;
		typedef IfcFlowInstrumentTypeT IfcFlowInstrumentType;
		typedef IfcFlowInstrumentTypeEnumT IfcFlowInstrumentTypeEnum;
		typedef IfcFlowMeterT IfcFlowMeter;
		typedef IfcFlowMeterTypeT IfcFlowMeterType;
		typedef IfcFlowMeterTypeEnumT IfcFlowMeterTypeEnum;
		typedef IfcFlowMovingDeviceT IfcFlowMovingDevice;
		typedef IfcFlowMovingDeviceTypeT IfcFlowMovingDeviceType;
		typedef IfcFlowSegmentT IfcFlowSegment;
		typedef IfcFlowSegmentTypeT IfcFlowSegmentType;
		typedef IfcFlowStorageDeviceT IfcFlowStorageDevice;
		typedef IfcFlowStorageDeviceTypeT IfcFlowStorageDeviceType;
		typedef IfcFlowTerminalT IfcFlowTerminal;
		typedef IfcFlowTerminalTypeT IfcFlowTerminalType;
		typedef IfcFlowTreatmentDeviceT IfcFlowTreatmentDevice;
		typedef IfcFlowTreatmentDeviceTypeT IfcFlowTreatmentDeviceType;
		typedef IfcFontStyleT IfcFontStyle;
		typedef IfcFontVariantT IfcFontVariant;
		typedef IfcFontWeightT IfcFontWeight;
		typedef IfcFootingT IfcFooting;
		typedef IfcFootingTypeT IfcFootingType;
		typedef IfcFootingTypeEnumT IfcFootingTypeEnum;
		typedef IfcForceMeasureT IfcForceMeasure;
		typedef IfcFrequencyMeasureT IfcFrequencyMeasure;
		typedef IfcFurnishingElementT IfcFurnishingElement;
		typedef IfcFurnishingElementTypeT IfcFurnishingElementType;
		typedef IfcFurnitureT IfcFurniture;
		typedef IfcFurnitureTypeT IfcFurnitureType;
		typedef IfcFurnitureTypeEnumT IfcFurnitureTypeEnum;
		typedef IfcGeographicElementT IfcGeographicElement;
		typedef IfcGeographicElementTypeT IfcGeographicElementType;
		typedef IfcGeographicElementTypeEnumT IfcGeographicElementTypeEnum;
		typedef IfcGeometricCurveSetT IfcGeometricCurveSet;
		typedef IfcGeometricProjectionEnumT IfcGeometricProjectionEnum;
		typedef IfcGeometricRepresentationContextT IfcGeometricRepresentationContext;
		typedef IfcGeometricRepresentationItemT IfcGeometricRepresentationItem;
		typedef IfcGeometricRepresentationSubContextT IfcGeometricRepresentationSubContext;
		typedef IfcGeometricSetT IfcGeometricSet;
		typedef IfcGeometricSetSelectT IfcGeometricSetSelect;
		typedef IfcGloballyUniqueIdT IfcGloballyUniqueId;
		typedef IfcGlobalOrLocalEnumT IfcGlobalOrLocalEnum;
		typedef IfcGridT IfcGrid;
		typedef IfcGridAxisT IfcGridAxis;
		typedef IfcGridPlacementT IfcGridPlacement;
		typedef IfcGridPlacementDirectionSelectT IfcGridPlacementDirectionSelect;
		typedef IfcGridTypeEnumT IfcGridTypeEnum;
		typedef IfcGroupT IfcGroup;
		typedef IfcHalfSpaceSolidT IfcHalfSpaceSolid;
		typedef IfcHatchLineDistanceSelectT IfcHatchLineDistanceSelect;
		typedef IfcHeatExchangerT IfcHeatExchanger;
		typedef IfcHeatExchangerTypeT IfcHeatExchangerType;
		typedef IfcHeatExchangerTypeEnumT IfcHeatExchangerTypeEnum;
		typedef IfcHeatFluxDensityMeasureT IfcHeatFluxDensityMeasure;
		typedef IfcHeatingValueMeasureT IfcHeatingValueMeasure;
		typedef IfcHumidifierT IfcHumidifier;
		typedef IfcHumidifierTypeT IfcHumidifierType;
		typedef IfcHumidifierTypeEnumT IfcHumidifierTypeEnum;
		typedef IfcIdentifierT IfcIdentifier;
		typedef IfcIlluminanceMeasureT IfcIlluminanceMeasure;
		typedef IfcImageTextureT IfcImageTexture;
		typedef IfcIndexedColourMapT IfcIndexedColourMap;
		typedef IfcIndexedTextureMapT IfcIndexedTextureMap;
		typedef IfcIndexedTriangleTextureMapT IfcIndexedTriangleTextureMap;
		typedef IfcInductanceMeasureT IfcInductanceMeasure;
		typedef IfcIntegerT IfcInteger;
		typedef IfcIntegerCountRateMeasureT IfcIntegerCountRateMeasure;
		typedef IfcInterceptorT IfcInterceptor;
		typedef IfcInterceptorTypeT IfcInterceptorType;
		typedef IfcInterceptorTypeEnumT IfcInterceptorTypeEnum;
		typedef IfcInternalOrExternalEnumT IfcInternalOrExternalEnum;
		typedef IfcInventoryT IfcInventory;
		typedef IfcInventoryTypeEnumT IfcInventoryTypeEnum;
		typedef IfcIonConcentrationMeasureT IfcIonConcentrationMeasure;
		typedef IfcIrregularTimeSeriesT IfcIrregularTimeSeries;
		typedef IfcIrregularTimeSeriesValueT IfcIrregularTimeSeriesValue;
		typedef IfcIShapeProfileDefT IfcIShapeProfileDef;
		typedef IfcIsothermalMoistureCapacityMeasureT IfcIsothermalMoistureCapacityMeasure;
		typedef IfcJunctionBoxT IfcJunctionBox;
		typedef IfcJunctionBoxTypeT IfcJunctionBoxType;
		typedef IfcJunctionBoxTypeEnumT IfcJunctionBoxTypeEnum;
		typedef IfcKinematicViscosityMeasureT IfcKinematicViscosityMeasure;
		typedef IfcKnotTypeT IfcKnotType;
		typedef IfcLabelT IfcLabel;
		typedef IfcLaborResourceT IfcLaborResource;
		typedef IfcLaborResourceTypeT IfcLaborResourceType;
		typedef IfcLaborResourceTypeEnumT IfcLaborResourceTypeEnum;
		typedef IfcLagTimeT IfcLagTime;
		typedef IfcLampT IfcLamp;
		typedef IfcLampTypeT IfcLampType;
		typedef IfcLampTypeEnumT IfcLampTypeEnum;
		typedef IfcLanguageIdT IfcLanguageId;
		typedef IfcLayeredItemT IfcLayeredItem;
		typedef IfcLayerSetDirectionEnumT IfcLayerSetDirectionEnum;
		typedef IfcLengthMeasureT IfcLengthMeasure;
		typedef IfcLibraryInformationT IfcLibraryInformation;
		typedef IfcLibraryReferenceT IfcLibraryReference;
		typedef IfcLibrarySelectT IfcLibrarySelect;
		typedef IfcLightDistributionCurveEnumT IfcLightDistributionCurveEnum;
		typedef IfcLightDistributionDataT IfcLightDistributionData;
		typedef IfcLightDistributionDataSourceSelectT IfcLightDistributionDataSourceSelect;
		typedef IfcLightEmissionSourceEnumT IfcLightEmissionSourceEnum;
		typedef IfcLightFixtureT IfcLightFixture;
		typedef IfcLightFixtureTypeT IfcLightFixtureType;
		typedef IfcLightFixtureTypeEnumT IfcLightFixtureTypeEnum;
		typedef IfcLightIntensityDistributionT IfcLightIntensityDistribution;
		typedef IfcLightSourceT IfcLightSource;
		typedef IfcLightSourceAmbientT IfcLightSourceAmbient;
		typedef IfcLightSourceDirectionalT IfcLightSourceDirectional;
		typedef IfcLightSourceGoniometricT IfcLightSourceGoniometric;
		typedef IfcLightSourcePositionalT IfcLightSourcePositional;
		typedef IfcLightSourceSpotT IfcLightSourceSpot;
		typedef IfcLineT IfcLine;
		typedef IfcLinearForceMeasureT IfcLinearForceMeasure;
		typedef IfcLinearMomentMeasureT IfcLinearMomentMeasure;
		typedef IfcLinearStiffnessMeasureT IfcLinearStiffnessMeasure;
		typedef IfcLinearVelocityMeasureT IfcLinearVelocityMeasure;
		typedef IfcLoadGroupTypeEnumT IfcLoadGroupTypeEnum;
		typedef IfcLocalPlacementT IfcLocalPlacement;
		typedef IfcLogicalT IfcLogical;
		typedef IfcLogicalOperatorEnumT IfcLogicalOperatorEnum;
		typedef IfcLoopT IfcLoop;
		typedef IfcLShapeProfileDefT IfcLShapeProfileDef;
		typedef IfcLuminousFluxMeasureT IfcLuminousFluxMeasure;
		typedef IfcLuminousIntensityDistributionMeasureT IfcLuminousIntensityDistributionMeasure;
		typedef IfcLuminousIntensityMeasureT IfcLuminousIntensityMeasure;
		typedef IfcMagneticFluxDensityMeasureT IfcMagneticFluxDensityMeasure;
		typedef IfcMagneticFluxMeasureT IfcMagneticFluxMeasure;
		typedef IfcManifoldSolidBrepT IfcManifoldSolidBrep;
		typedef IfcMapConversionT IfcMapConversion;
		typedef IfcMappedItemT IfcMappedItem;
		typedef IfcMassDensityMeasureT IfcMassDensityMeasure;
		typedef IfcMassFlowRateMeasureT IfcMassFlowRateMeasure;
		typedef IfcMassMeasureT IfcMassMeasure;
		typedef IfcMassPerLengthMeasureT IfcMassPerLengthMeasure;
		typedef IfcMaterialT IfcMaterial;
		typedef IfcMaterialClassificationRelationshipT IfcMaterialClassificationRelationship;
		typedef IfcMaterialConstituentT IfcMaterialConstituent;
		typedef IfcMaterialConstituentSetT IfcMaterialConstituentSet;
		typedef IfcMaterialDefinitionT IfcMaterialDefinition;
		typedef IfcMaterialDefinitionRepresentationT IfcMaterialDefinitionRepresentation;
		typedef IfcMaterialLayerT IfcMaterialLayer;
		typedef IfcMaterialLayerSetT IfcMaterialLayerSet;
		typedef IfcMaterialLayerSetUsageT IfcMaterialLayerSetUsage;
		typedef IfcMaterialLayerWithOffsetsT IfcMaterialLayerWithOffsets;
		typedef IfcMaterialListT IfcMaterialList;
		typedef IfcMaterialProfileT IfcMaterialProfile;
		typedef IfcMaterialProfileSetT IfcMaterialProfileSet;
		typedef IfcMaterialProfileSetUsageT IfcMaterialProfileSetUsage;
		typedef IfcMaterialProfileSetUsageTaperingT IfcMaterialProfileSetUsageTapering;
		typedef IfcMaterialProfileWithOffsetsT IfcMaterialProfileWithOffsets;
		typedef IfcMaterialPropertiesT IfcMaterialProperties;
		typedef IfcMaterialRelationshipT IfcMaterialRelationship;
		typedef IfcMaterialSelectT IfcMaterialSelect;
		typedef IfcMaterialUsageDefinitionT IfcMaterialUsageDefinition;
		typedef IfcMeasureValueT IfcMeasureValue;
		typedef IfcMeasureWithUnitT IfcMeasureWithUnit;
		typedef IfcMechanicalFastenerT IfcMechanicalFastener;
		typedef IfcMechanicalFastenerTypeT IfcMechanicalFastenerType;
		typedef IfcMechanicalFastenerTypeEnumT IfcMechanicalFastenerTypeEnum;
		typedef IfcMedicalDeviceT IfcMedicalDevice;
		typedef IfcMedicalDeviceTypeT IfcMedicalDeviceType;
		typedef IfcMedicalDeviceTypeEnumT IfcMedicalDeviceTypeEnum;
		typedef IfcMemberT IfcMember;
		typedef IfcMemberStandardCaseT IfcMemberStandardCase;
		typedef IfcMemberTypeT IfcMemberType;
		typedef IfcMemberTypeEnumT IfcMemberTypeEnum;
		typedef IfcMetricT IfcMetric;
		typedef IfcMetricValueSelectT IfcMetricValueSelect;
		typedef IfcMirroredProfileDefT IfcMirroredProfileDef;
		typedef IfcModulusOfElasticityMeasureT IfcModulusOfElasticityMeasure;
		typedef IfcModulusOfLinearSubgradeReactionMeasureT IfcModulusOfLinearSubgradeReactionMeasure;
		typedef IfcModulusOfRotationalSubgradeReactionMeasureT IfcModulusOfRotationalSubgradeReactionMeasure;
		typedef IfcModulusOfRotationalSubgradeReactionSelectT IfcModulusOfRotationalSubgradeReactionSelect;
		typedef IfcModulusOfSubgradeReactionMeasureT IfcModulusOfSubgradeReactionMeasure;
		typedef IfcModulusOfSubgradeReactionSelectT IfcModulusOfSubgradeReactionSelect;
		typedef IfcModulusOfTranslationalSubgradeReactionSelectT IfcModulusOfTranslationalSubgradeReactionSelect;
		typedef IfcMoistureDiffusivityMeasureT IfcMoistureDiffusivityMeasure;
		typedef IfcMolecularWeightMeasureT IfcMolecularWeightMeasure;
		typedef IfcMomentOfInertiaMeasureT IfcMomentOfInertiaMeasure;
		typedef IfcMonetaryMeasureT IfcMonetaryMeasure;
		typedef IfcMonetaryUnitT IfcMonetaryUnit;
		typedef IfcMonthInYearNumberT IfcMonthInYearNumber;
		typedef IfcMotorConnectionT IfcMotorConnection;
		typedef IfcMotorConnectionTypeT IfcMotorConnectionType;
		typedef IfcMotorConnectionTypeEnumT IfcMotorConnectionTypeEnum;
		typedef IfcNamedUnitT IfcNamedUnit;
		typedef IfcNonNegativeLengthMeasureT IfcNonNegativeLengthMeasure;
		typedef IfcNormalisedRatioMeasureT IfcNormalisedRatioMeasure;
		typedef IfcNullStyleT IfcNullStyle;
		typedef IfcNumericMeasureT IfcNumericMeasure;
		typedef IfcObjectT IfcObject;
		typedef IfcObjectDefinitionT IfcObjectDefinition;
		typedef IfcObjectiveT IfcObjective;
		typedef IfcObjectiveEnumT IfcObjectiveEnum;
		typedef IfcObjectPlacementT IfcObjectPlacement;
		typedef IfcObjectReferenceSelectT IfcObjectReferenceSelect;
		typedef IfcObjectTypeEnumT IfcObjectTypeEnum;
		typedef IfcOccupantT IfcOccupant;
		typedef IfcOccupantTypeEnumT IfcOccupantTypeEnum;
		typedef IfcOffsetCurve2DT IfcOffsetCurve2D;
		typedef IfcOffsetCurve3DT IfcOffsetCurve3D;
		typedef IfcOneDirectionRepeatFactorT IfcOneDirectionRepeatFactor;
		typedef IfcOpeningElementT IfcOpeningElement;
		typedef IfcOpeningElementTypeEnumT IfcOpeningElementTypeEnum;
		typedef IfcOpeningStandardCaseT IfcOpeningStandardCase;
		typedef IfcOpenShellT IfcOpenShell;
		typedef IfcOrganizationT IfcOrganization;
		typedef IfcOrganizationRelationshipT IfcOrganizationRelationship;
		typedef IfcOrientedEdgeT IfcOrientedEdge;
		typedef IfcOuterBoundaryCurveT IfcOuterBoundaryCurve;
		typedef IfcOutletT IfcOutlet;
		typedef IfcOutletTypeT IfcOutletType;
		typedef IfcOutletTypeEnumT IfcOutletTypeEnum;
		typedef IfcOwnerHistoryT IfcOwnerHistory;
		typedef IfcParameterizedProfileDefT IfcParameterizedProfileDef;
		typedef IfcParameterValueT IfcParameterValue;
		typedef IfcPathT IfcPath;
		typedef IfcPcurveT IfcPcurve;
		typedef IfcPerformanceHistoryT IfcPerformanceHistory;
		typedef IfcPerformanceHistoryTypeEnumT IfcPerformanceHistoryTypeEnum;
		typedef IfcPermeableCoveringOperationEnumT IfcPermeableCoveringOperationEnum;
		typedef IfcPermeableCoveringPropertiesT IfcPermeableCoveringProperties;
		typedef IfcPermitT IfcPermit;
		typedef IfcPermitTypeEnumT IfcPermitTypeEnum;
		typedef IfcPersonT IfcPerson;
		typedef IfcPersonAndOrganizationT IfcPersonAndOrganization;
		typedef IfcPHMeasureT IfcPHMeasure;
		typedef IfcPhysicalComplexQuantityT IfcPhysicalComplexQuantity;
		typedef IfcPhysicalOrVirtualEnumT IfcPhysicalOrVirtualEnum;
		typedef IfcPhysicalQuantityT IfcPhysicalQuantity;
		typedef IfcPhysicalSimpleQuantityT IfcPhysicalSimpleQuantity;
		typedef IfcPileT IfcPile;
		typedef IfcPileConstructionEnumT IfcPileConstructionEnum;
		typedef IfcPileTypeT IfcPileType;
		typedef IfcPileTypeEnumT IfcPileTypeEnum;
		typedef IfcPipeFittingT IfcPipeFitting;
		typedef IfcPipeFittingTypeT IfcPipeFittingType;
		typedef IfcPipeFittingTypeEnumT IfcPipeFittingTypeEnum;
		typedef IfcPipeSegmentT IfcPipeSegment;
		typedef IfcPipeSegmentTypeT IfcPipeSegmentType;
		typedef IfcPipeSegmentTypeEnumT IfcPipeSegmentTypeEnum;
		typedef IfcPixelTextureT IfcPixelTexture;
		typedef IfcPlacementT IfcPlacement;
		typedef IfcPlanarBoxT IfcPlanarBox;
		typedef IfcPlanarExtentT IfcPlanarExtent;
		typedef IfcPlanarForceMeasureT IfcPlanarForceMeasure;
		typedef IfcPlaneT IfcPlane;
		typedef IfcPlaneAngleMeasureT IfcPlaneAngleMeasure;
		typedef IfcPlateT IfcPlate;
		typedef IfcPlateStandardCaseT IfcPlateStandardCase;
		typedef IfcPlateTypeT IfcPlateType;
		typedef IfcPlateTypeEnumT IfcPlateTypeEnum;
		typedef IfcPointT IfcPoint;
		typedef IfcPointOnCurveT IfcPointOnCurve;
		typedef IfcPointOnSurfaceT IfcPointOnSurface;
		typedef IfcPointOrVertexPointT IfcPointOrVertexPoint;
		typedef IfcPolygonalBoundedHalfSpaceT IfcPolygonalBoundedHalfSpace;
		typedef IfcPolylineT IfcPolyline;
		typedef IfcPolyLoopT IfcPolyLoop;
		typedef IfcPortT IfcPort;
		typedef IfcPositiveLengthMeasureT IfcPositiveLengthMeasure;
		typedef IfcPositivePlaneAngleMeasureT IfcPositivePlaneAngleMeasure;
		typedef IfcPositiveRatioMeasureT IfcPositiveRatioMeasure;
		typedef IfcPostalAddressT IfcPostalAddress;
		typedef IfcPowerMeasureT IfcPowerMeasure;
		typedef IfcPreDefinedColourT IfcPreDefinedColour;
		typedef IfcPreDefinedCurveFontT IfcPreDefinedCurveFont;
		typedef IfcPreDefinedItemT IfcPreDefinedItem;
		typedef IfcPreDefinedPropertiesT IfcPreDefinedProperties;
		typedef IfcPreDefinedPropertySetT IfcPreDefinedPropertySet;
		typedef IfcPreDefinedSymbolT IfcPreDefinedSymbol;
		typedef IfcPreDefinedTextFontT IfcPreDefinedTextFont;
		typedef IfcPresentableTextT IfcPresentableText;
		typedef IfcPresentationItemT IfcPresentationItem;
		typedef IfcPresentationLayerAssignmentT IfcPresentationLayerAssignment;
		typedef IfcPresentationLayerWithStyleT IfcPresentationLayerWithStyle;
		typedef IfcPresentationStyleT IfcPresentationStyle;
		typedef IfcPresentationStyleAssignmentT IfcPresentationStyleAssignment;
		typedef IfcPresentationStyleSelectT IfcPresentationStyleSelect;
		typedef IfcPressureMeasureT IfcPressureMeasure;
		typedef IfcProcedureT IfcProcedure;
		typedef IfcProcedureTypeT IfcProcedureType;
		typedef IfcProcedureTypeEnumT IfcProcedureTypeEnum;
		typedef IfcProcessT IfcProcess;
		typedef IfcProcessSelectT IfcProcessSelect;
		typedef IfcProductT IfcProduct;
		typedef IfcProductDefinitionShapeT IfcProductDefinitionShape;
		typedef IfcProductRepresentationT IfcProductRepresentation;
		typedef IfcProductSelectT IfcProductSelect;
		typedef IfcProfileDefT IfcProfileDef;
		typedef IfcProfilePropertiesT IfcProfileProperties;
		typedef IfcProfileTypeEnumT IfcProfileTypeEnum;
		typedef IfcProjectT IfcProject;
		typedef IfcProjectedCRST IfcProjectedCRS;
		typedef IfcProjectedOrTrueLengthEnumT IfcProjectedOrTrueLengthEnum;
		typedef IfcProjectionElementT IfcProjectionElement;
		typedef IfcProjectionElementTypeEnumT IfcProjectionElementTypeEnum;
		typedef IfcProjectLibraryT IfcProjectLibrary;
		typedef IfcProjectOrderT IfcProjectOrder;
		typedef IfcProjectOrderTypeEnumT IfcProjectOrderTypeEnum;
		typedef IfcPropertyT IfcProperty;
		typedef IfcPropertyAbstractionT IfcPropertyAbstraction;
		typedef IfcPropertyBoundedValueT IfcPropertyBoundedValue;
		typedef IfcPropertyDefinitionT IfcPropertyDefinition;
		typedef IfcPropertyDependencyRelationshipT IfcPropertyDependencyRelationship;
		typedef IfcPropertyEnumeratedValueT IfcPropertyEnumeratedValue;
		typedef IfcPropertyEnumerationT IfcPropertyEnumeration;
		typedef IfcPropertyListValueT IfcPropertyListValue;
		typedef IfcPropertyReferenceValueT IfcPropertyReferenceValue;
		typedef IfcPropertySetT IfcPropertySet;
		typedef IfcPropertySetDefinitionT IfcPropertySetDefinition;
		typedef IfcPropertySetTemplateT IfcPropertySetTemplate;
		typedef IfcPropertySetTemplateTypeEnumT IfcPropertySetTemplateTypeEnum;
		typedef IfcPropertySingleValueT IfcPropertySingleValue;
		typedef IfcPropertyTableValueT IfcPropertyTableValue;
		typedef IfcPropertyTemplateT IfcPropertyTemplate;
		typedef IfcPropertyTemplateDefinitionT IfcPropertyTemplateDefinition;
		typedef IfcProtectiveDeviceT IfcProtectiveDevice;
		typedef IfcProtectiveDeviceTrippingUnitT IfcProtectiveDeviceTrippingUnit;
		typedef IfcProtectiveDeviceTrippingUnitTypeT IfcProtectiveDeviceTrippingUnitType;
		typedef IfcProtectiveDeviceTrippingUnitTypeEnumT IfcProtectiveDeviceTrippingUnitTypeEnum;
		typedef IfcProtectiveDeviceTypeT IfcProtectiveDeviceType;
		typedef IfcProtectiveDeviceTypeEnumT IfcProtectiveDeviceTypeEnum;
		typedef IfcProxyT IfcProxy;
		typedef IfcPumpT IfcPump;
		typedef IfcPumpTypeT IfcPumpType;
		typedef IfcPumpTypeEnumT IfcPumpTypeEnum;
		typedef IfcQuantityAreaT IfcQuantityArea;
		typedef IfcQuantityCountT IfcQuantityCount;
		typedef IfcQuantityLengthT IfcQuantityLength;
		typedef IfcQuantitySetT IfcQuantitySet;
		typedef IfcQuantityTimeT IfcQuantityTime;
		typedef IfcQuantityVolumeT IfcQuantityVolume;
		typedef IfcQuantityWeightT IfcQuantityWeight;
		typedef IfcRadioActivityMeasureT IfcRadioActivityMeasure;
		typedef IfcRailingT IfcRailing;
		typedef IfcRailingTypeT IfcRailingType;
		typedef IfcRailingTypeEnumT IfcRailingTypeEnum;
		typedef IfcRampT IfcRamp;
		typedef IfcRampFlightT IfcRampFlight;
		typedef IfcRampFlightTypeT IfcRampFlightType;
		typedef IfcRampFlightTypeEnumT IfcRampFlightTypeEnum;
		typedef IfcRampTypeT IfcRampType;
		typedef IfcRampTypeEnumT IfcRampTypeEnum;
		typedef IfcRatioMeasureT IfcRatioMeasure;
		typedef IfcRationalBSplineCurveWithKnotsT IfcRationalBSplineCurveWithKnots;
		typedef IfcRationalBSplineSurfaceWithKnotsT IfcRationalBSplineSurfaceWithKnots;
		typedef IfcRealT IfcReal;
		typedef IfcRectangleHollowProfileDefT IfcRectangleHollowProfileDef;
		typedef IfcRectangleProfileDefT IfcRectangleProfileDef;
		typedef IfcRectangularPyramidT IfcRectangularPyramid;
		typedef IfcRectangularTrimmedSurfaceT IfcRectangularTrimmedSurface;
		typedef IfcRecurrencePatternT IfcRecurrencePattern;
		typedef IfcRecurrenceTypeEnumT IfcRecurrenceTypeEnum;
		typedef IfcReferenceCurveT IfcReferenceCurve;
		typedef IfcReferenceCurve3DT IfcReferenceCurve3D;
		typedef IfcReferenceCurveAlignment2DT IfcReferenceCurveAlignment2D;
		typedef IfcReferenceCurvePlacementT IfcReferenceCurvePlacement;
		typedef IfcReferenceCurvePlacementSystemT IfcReferenceCurvePlacementSystem;
		typedef IfcReferencedSectionedSpineT IfcReferencedSectionedSpine;
		typedef IfcReferenceElementT IfcReferenceElement;
		typedef IfcReferencePlacementT IfcReferencePlacement;
		typedef IfcReflectanceMethodEnumT IfcReflectanceMethodEnum;
		typedef IfcRegularTimeSeriesT IfcRegularTimeSeries;
		typedef IfcReinforcementBarPropertiesT IfcReinforcementBarProperties;
		typedef IfcReinforcementDefinitionPropertiesT IfcReinforcementDefinitionProperties;
		typedef IfcReinforcingBarT IfcReinforcingBar;
		typedef IfcReinforcingBarRoleEnumT IfcReinforcingBarRoleEnum;
		typedef IfcReinforcingBarSurfaceEnumT IfcReinforcingBarSurfaceEnum;
		typedef IfcReinforcingBarTypeT IfcReinforcingBarType;
		typedef IfcReinforcingBarTypeEnumT IfcReinforcingBarTypeEnum;
		typedef IfcReinforcingElementT IfcReinforcingElement;
		typedef IfcReinforcingElementTypeT IfcReinforcingElementType;
		typedef IfcReinforcingMeshT IfcReinforcingMesh;
		typedef IfcReinforcingMeshTypeT IfcReinforcingMeshType;
		typedef IfcReinforcingMeshTypeEnumT IfcReinforcingMeshTypeEnum;
		typedef IfcRelAggregatesT IfcRelAggregates;
		typedef IfcRelAssignsT IfcRelAssigns;
		typedef IfcRelAssignsToActorT IfcRelAssignsToActor;
		typedef IfcRelAssignsToControlT IfcRelAssignsToControl;
		typedef IfcRelAssignsToGroupT IfcRelAssignsToGroup;
		typedef IfcRelAssignsToGroupByFactorT IfcRelAssignsToGroupByFactor;
		typedef IfcRelAssignsToProcessT IfcRelAssignsToProcess;
		typedef IfcRelAssignsToProductT IfcRelAssignsToProduct;
		typedef IfcRelAssignsToResourceT IfcRelAssignsToResource;
		typedef IfcRelAssociatesT IfcRelAssociates;
		typedef IfcRelAssociatesApprovalT IfcRelAssociatesApproval;
		typedef IfcRelAssociatesClassificationT IfcRelAssociatesClassification;
		typedef IfcRelAssociatesConstraintT IfcRelAssociatesConstraint;
		typedef IfcRelAssociatesDocumentT IfcRelAssociatesDocument;
		typedef IfcRelAssociatesLibraryT IfcRelAssociatesLibrary;
		typedef IfcRelAssociatesMaterialT IfcRelAssociatesMaterial;
		typedef IfcRelationshipT IfcRelationship;
		typedef IfcRelConnectsT IfcRelConnects;
		typedef IfcRelConnectsElementsT IfcRelConnectsElements;
		typedef IfcRelConnectsPathElementsT IfcRelConnectsPathElements;
		typedef IfcRelConnectsPortsT IfcRelConnectsPorts;
		typedef IfcRelConnectsPortToElementT IfcRelConnectsPortToElement;
		typedef IfcRelConnectsStructuralActivityT IfcRelConnectsStructuralActivity;
		typedef IfcRelConnectsStructuralMemberT IfcRelConnectsStructuralMember;
		typedef IfcRelConnectsWithEccentricityT IfcRelConnectsWithEccentricity;
		typedef IfcRelConnectsWithRealizingElementsT IfcRelConnectsWithRealizingElements;
		typedef IfcRelContainedInSpatialStructureT IfcRelContainedInSpatialStructure;
		typedef IfcRelCoversBldgElementsT IfcRelCoversBldgElements;
		typedef IfcRelCoversSpacesT IfcRelCoversSpaces;
		typedef IfcRelDeclaresT IfcRelDeclares;
		typedef IfcRelDecomposesT IfcRelDecomposes;
		typedef IfcRelDefinesT IfcRelDefines;
		typedef IfcRelDefinesByObjectT IfcRelDefinesByObject;
		typedef IfcRelDefinesByPropertiesT IfcRelDefinesByProperties;
		typedef IfcRelDefinesByTemplateT IfcRelDefinesByTemplate;
		typedef IfcRelDefinesByTypeT IfcRelDefinesByType;
		typedef IfcRelFillsElementT IfcRelFillsElement;
		typedef IfcRelFlowControlElementsT IfcRelFlowControlElements;
		typedef IfcRelInterferesElementsT IfcRelInterferesElements;
		typedef IfcRelNestsT IfcRelNests;
		typedef IfcRelProjectsElementT IfcRelProjectsElement;
		typedef IfcRelReferencedInSpatialStructureT IfcRelReferencedInSpatialStructure;
		typedef IfcRelSequenceT IfcRelSequence;
		typedef IfcRelServicesBuildingsT IfcRelServicesBuildings;
		typedef IfcRelSpaceBoundaryT IfcRelSpaceBoundary;
		typedef IfcRelSpaceBoundary1stLevelT IfcRelSpaceBoundary1stLevel;
		typedef IfcRelSpaceBoundary2ndLevelT IfcRelSpaceBoundary2ndLevel;
		typedef IfcRelVoidsElementT IfcRelVoidsElement;
		typedef IfcReparametrisedCompositeCurveSegmentT IfcReparametrisedCompositeCurveSegment;
		typedef IfcRepresentationT IfcRepresentation;
		typedef IfcRepresentationContextT IfcRepresentationContext;
		typedef IfcRepresentationItemT IfcRepresentationItem;
		typedef IfcRepresentationMapT IfcRepresentationMap;
		typedef IfcResourceT IfcResource;
		typedef IfcResourceApprovalRelationshipT IfcResourceApprovalRelationship;
		typedef IfcResourceConstraintRelationshipT IfcResourceConstraintRelationship;
		typedef IfcResourceConsumptionEnumT IfcResourceConsumptionEnum;
		typedef IfcResourceCostT IfcResourceCost;
		typedef IfcResourceLevelRelationshipT IfcResourceLevelRelationship;
		typedef IfcResourceObjectSelectT IfcResourceObjectSelect;
		typedef IfcResourceSelectT IfcResourceSelect;
		typedef IfcResourceTimeT IfcResourceTime;
		typedef IfcRevolvedAreaSolidT IfcRevolvedAreaSolid;
		typedef IfcRevolvedAreaSolidTaperedT IfcRevolvedAreaSolidTapered;
		typedef IfcRightCircularConeT IfcRightCircularCone;
		typedef IfcRightCircularCylinderT IfcRightCircularCylinder;
		typedef IfcRoleEnumT IfcRoleEnum;
		typedef IfcRoofT IfcRoof;
		typedef IfcRoofTypeT IfcRoofType;
		typedef IfcRoofTypeEnumT IfcRoofTypeEnum;
		typedef IfcRootT IfcRoot;
		typedef IfcRotationalFrequencyMeasureT IfcRotationalFrequencyMeasure;
		typedef IfcRotationalMassMeasureT IfcRotationalMassMeasure;
		typedef IfcRotationalStiffnessMeasureT IfcRotationalStiffnessMeasure;
		typedef IfcRotationalStiffnessSelectT IfcRotationalStiffnessSelect;
		typedef IfcRoundedRectangleProfileDefT IfcRoundedRectangleProfileDef;
		typedef IfcSanitaryTerminalT IfcSanitaryTerminal;
		typedef IfcSanitaryTerminalTypeT IfcSanitaryTerminalType;
		typedef IfcSanitaryTerminalTypeEnumT IfcSanitaryTerminalTypeEnum;
		typedef IfcSchedulingTimeT IfcSchedulingTime;
		typedef IfcSectionalAreaIntegralMeasureT IfcSectionalAreaIntegralMeasure;
		typedef IfcSectionedSpineT IfcSectionedSpine;
		typedef IfcSectionModulusMeasureT IfcSectionModulusMeasure;
		typedef IfcSectionPropertiesT IfcSectionProperties;
		typedef IfcSectionReinforcementPropertiesT IfcSectionReinforcementProperties;
		typedef IfcSectionTypeEnumT IfcSectionTypeEnum;
		typedef IfcSensorT IfcSensor;
		typedef IfcSensorTypeT IfcSensorType;
		typedef IfcSensorTypeEnumT IfcSensorTypeEnum;
		typedef IfcSequenceEnumT IfcSequenceEnum;
		typedef IfcShadingDeviceT IfcShadingDevice;
		typedef IfcShadingDeviceTypeT IfcShadingDeviceType;
		typedef IfcShadingDeviceTypeEnumT IfcShadingDeviceTypeEnum;
		typedef IfcShapeAspectT IfcShapeAspect;
		typedef IfcShapeModelT IfcShapeModel;
		typedef IfcShapeRepresentationT IfcShapeRepresentation;
		typedef IfcShearModulusMeasureT IfcShearModulusMeasure;
		typedef IfcShellT IfcShell;
		typedef IfcShellBasedSurfaceModelT IfcShellBasedSurfaceModel;
		typedef IfcSimplePropertyT IfcSimpleProperty;
		typedef IfcSimplePropertyTemplateT IfcSimplePropertyTemplate;
		typedef IfcSimplePropertyTemplateTypeEnumT IfcSimplePropertyTemplateTypeEnum;
		typedef IfcSimpleValueT IfcSimpleValue;
		typedef IfcSIPrefixT IfcSIPrefix;
		typedef IfcSiteT IfcSite;
		typedef IfcSIUnitT IfcSIUnit;
		typedef IfcSIUnitNameT IfcSIUnitName;
		typedef IfcSizeSelectT IfcSizeSelect;
		typedef IfcSlabT IfcSlab;
		typedef IfcSlabElementedCaseT IfcSlabElementedCase;
		typedef IfcSlabStandardCaseT IfcSlabStandardCase;
		typedef IfcSlabTypeT IfcSlabType;
		typedef IfcSlabTypeEnumT IfcSlabTypeEnum;
		typedef IfcSlippageConnectionConditionT IfcSlippageConnectionCondition;
		typedef IfcSolarDeviceT IfcSolarDevice;
		typedef IfcSolarDeviceTypeT IfcSolarDeviceType;
		typedef IfcSolarDeviceTypeEnumT IfcSolarDeviceTypeEnum;
		typedef IfcSolidAngleMeasureT IfcSolidAngleMeasure;
		typedef IfcSolidModelT IfcSolidModel;
		typedef IfcSolidOrShellT IfcSolidOrShell;
		typedef IfcSoundPowerMeasureT IfcSoundPowerMeasure;
		typedef IfcSoundPressureMeasureT IfcSoundPressureMeasure;
		typedef IfcSpaceT IfcSpace;
		typedef IfcSpaceBoundarySelectT IfcSpaceBoundarySelect;
		typedef IfcSpaceHeaterT IfcSpaceHeater;
		typedef IfcSpaceHeaterTypeT IfcSpaceHeaterType;
		typedef IfcSpaceHeaterTypeEnumT IfcSpaceHeaterTypeEnum;
		typedef IfcSpaceTypeT IfcSpaceType;
		typedef IfcSpaceTypeEnumT IfcSpaceTypeEnum;
		typedef IfcSpatialElementT IfcSpatialElement;
		typedef IfcSpatialElementTypeT IfcSpatialElementType;
		typedef IfcSpatialStructureElementT IfcSpatialStructureElement;
		typedef IfcSpatialStructureElementTypeT IfcSpatialStructureElementType;
		typedef IfcSpatialZoneT IfcSpatialZone;
		typedef IfcSpatialZoneTypeT IfcSpatialZoneType;
		typedef IfcSpatialZoneTypeEnumT IfcSpatialZoneTypeEnum;
		typedef IfcSpecificHeatCapacityMeasureT IfcSpecificHeatCapacityMeasure;
		typedef IfcSpecularExponentT IfcSpecularExponent;
		typedef IfcSpecularHighlightSelectT IfcSpecularHighlightSelect;
		typedef IfcSpecularRoughnessT IfcSpecularRoughness;
		typedef IfcSphereT IfcSphere;
		typedef IfcStackTerminalT IfcStackTerminal;
		typedef IfcStackTerminalTypeT IfcStackTerminalType;
		typedef IfcStackTerminalTypeEnumT IfcStackTerminalTypeEnum;
		typedef IfcStairT IfcStair;
		typedef IfcStairFlightT IfcStairFlight;
		typedef IfcStairFlightTypeT IfcStairFlightType;
		typedef IfcStairFlightTypeEnumT IfcStairFlightTypeEnum;
		typedef IfcStairTypeT IfcStairType;
		typedef IfcStairTypeEnumT IfcStairTypeEnum;
		typedef IfcStateEnumT IfcStateEnum;
		typedef IfcStructuralActionT IfcStructuralAction;
		typedef IfcStructuralActivityT IfcStructuralActivity;
		typedef IfcStructuralActivityAssignmentSelectT IfcStructuralActivityAssignmentSelect;
		typedef IfcStructuralAnalysisModelT IfcStructuralAnalysisModel;
		typedef IfcStructuralConnectionT IfcStructuralConnection;
		typedef IfcStructuralConnectionConditionT IfcStructuralConnectionCondition;
		typedef IfcStructuralCurveActionT IfcStructuralCurveAction;
		typedef IfcStructuralCurveActivityTypeEnumT IfcStructuralCurveActivityTypeEnum;
		typedef IfcStructuralCurveConnectionT IfcStructuralCurveConnection;
		typedef IfcStructuralCurveMemberT IfcStructuralCurveMember;
		typedef IfcStructuralCurveMemberTypeEnumT IfcStructuralCurveMemberTypeEnum;
		typedef IfcStructuralCurveMemberVaryingT IfcStructuralCurveMemberVarying;
		typedef IfcStructuralCurveReactionT IfcStructuralCurveReaction;
		typedef IfcStructuralItemT IfcStructuralItem;
		typedef IfcStructuralLinearActionT IfcStructuralLinearAction;
		typedef IfcStructuralLoadT IfcStructuralLoad;
		typedef IfcStructuralLoadCaseT IfcStructuralLoadCase;
		typedef IfcStructuralLoadConfigurationT IfcStructuralLoadConfiguration;
		typedef IfcStructuralLoadGroupT IfcStructuralLoadGroup;
		typedef IfcStructuralLoadLinearForceT IfcStructuralLoadLinearForce;
		typedef IfcStructuralLoadOrResultT IfcStructuralLoadOrResult;
		typedef IfcStructuralLoadPlanarForceT IfcStructuralLoadPlanarForce;
		typedef IfcStructuralLoadSingleDisplacementT IfcStructuralLoadSingleDisplacement;
		typedef IfcStructuralLoadSingleDisplacementDistortionT IfcStructuralLoadSingleDisplacementDistortion;
		typedef IfcStructuralLoadSingleForceT IfcStructuralLoadSingleForce;
		typedef IfcStructuralLoadSingleForceWarpingT IfcStructuralLoadSingleForceWarping;
		typedef IfcStructuralLoadStaticT IfcStructuralLoadStatic;
		typedef IfcStructuralLoadTemperatureT IfcStructuralLoadTemperature;
		typedef IfcStructuralMemberT IfcStructuralMember;
		typedef IfcStructuralPlanarActionT IfcStructuralPlanarAction;
		typedef IfcStructuralPointActionT IfcStructuralPointAction;
		typedef IfcStructuralPointConnectionT IfcStructuralPointConnection;
		typedef IfcStructuralPointReactionT IfcStructuralPointReaction;
		typedef IfcStructuralReactionT IfcStructuralReaction;
		typedef IfcStructuralResultGroupT IfcStructuralResultGroup;
		typedef IfcStructuralSurfaceActionT IfcStructuralSurfaceAction;
		typedef IfcStructuralSurfaceActivityTypeEnumT IfcStructuralSurfaceActivityTypeEnum;
		typedef IfcStructuralSurfaceConnectionT IfcStructuralSurfaceConnection;
		typedef IfcStructuralSurfaceMemberT IfcStructuralSurfaceMember;
		typedef IfcStructuralSurfaceMemberTypeEnumT IfcStructuralSurfaceMemberTypeEnum;
		typedef IfcStructuralSurfaceMemberVaryingT IfcStructuralSurfaceMemberVarying;
		typedef IfcStructuralSurfaceReactionT IfcStructuralSurfaceReaction;
		typedef IfcStyleAssignmentSelectT IfcStyleAssignmentSelect;
		typedef IfcStyledItemT IfcStyledItem;
		typedef IfcStyledRepresentationT IfcStyledRepresentation;
		typedef IfcStyleModelT IfcStyleModel;
		typedef IfcSubContractResourceT IfcSubContractResource;
		typedef IfcSubContractResourceTypeT IfcSubContractResourceType;
		typedef IfcSubContractResourceTypeEnumT IfcSubContractResourceTypeEnum;
		typedef IfcSubedgeT IfcSubedge;
		typedef IfcSurfaceT IfcSurface;
		typedef IfcSurfaceCurveSweptAreaSolidT IfcSurfaceCurveSweptAreaSolid;
		typedef IfcSurfaceFeatureT IfcSurfaceFeature;
		typedef IfcSurfaceFeatureTypeEnumT IfcSurfaceFeatureTypeEnum;
		typedef IfcSurfaceOfLinearExtrusionT IfcSurfaceOfLinearExtrusion;
		typedef IfcSurfaceOfRevolutionT IfcSurfaceOfRevolution;
		typedef IfcSurfaceOrFaceSurfaceT IfcSurfaceOrFaceSurface;
		typedef IfcSurfaceReinforcementAreaT IfcSurfaceReinforcementArea;
		typedef IfcSurfaceSideT IfcSurfaceSide;
		typedef IfcSurfaceStyleT IfcSurfaceStyle;
		typedef IfcSurfaceStyleElementSelectT IfcSurfaceStyleElementSelect;
		typedef IfcSurfaceStyleLightingT IfcSurfaceStyleLighting;
		typedef IfcSurfaceStyleRefractionT IfcSurfaceStyleRefraction;
		typedef IfcSurfaceStyleRenderingT IfcSurfaceStyleRendering;
		typedef IfcSurfaceStyleShadingT IfcSurfaceStyleShading;
		typedef IfcSurfaceStyleWithTexturesT IfcSurfaceStyleWithTextures;
		typedef IfcSurfaceTextureT IfcSurfaceTexture;
		typedef IfcSweptAreaSolidT IfcSweptAreaSolid;
		typedef IfcSweptDiskSolidT IfcSweptDiskSolid;
		typedef IfcSweptDiskSolidPolygonalT IfcSweptDiskSolidPolygonal;
		typedef IfcSweptSurfaceT IfcSweptSurface;
		typedef IfcSwitchingDeviceT IfcSwitchingDevice;
		typedef IfcSwitchingDeviceTypeT IfcSwitchingDeviceType;
		typedef IfcSwitchingDeviceTypeEnumT IfcSwitchingDeviceTypeEnum;
		typedef IfcSymbolStyleT IfcSymbolStyle;
		typedef IfcSymbolStyleSelectT IfcSymbolStyleSelect;
		typedef IfcSystemT IfcSystem;
		typedef IfcSystemFurnitureElementT IfcSystemFurnitureElement;
		typedef IfcSystemFurnitureElementTypeT IfcSystemFurnitureElementType;
		typedef IfcSystemFurnitureElementTypeEnumT IfcSystemFurnitureElementTypeEnum;
		typedef IfcTableT IfcTable;
		typedef IfcTableColumnT IfcTableColumn;
		typedef IfcTableRowT IfcTableRow;
		typedef IfcTankT IfcTank;
		typedef IfcTankTypeT IfcTankType;
		typedef IfcTankTypeEnumT IfcTankTypeEnum;
		typedef IfcTaskT IfcTask;
		typedef IfcTaskDurationEnumT IfcTaskDurationEnum;
		typedef IfcTaskTimeT IfcTaskTime;
		typedef IfcTaskTimeRecurringT IfcTaskTimeRecurring;
		typedef IfcTaskTypeT IfcTaskType;
		typedef IfcTaskTypeEnumT IfcTaskTypeEnum;
		typedef IfcTelecomAddressT IfcTelecomAddress;
		typedef IfcTemperatureGradientMeasureT IfcTemperatureGradientMeasure;
		typedef IfcTemperatureRateOfChangeMeasureT IfcTemperatureRateOfChangeMeasure;
		typedef IfcTendonT IfcTendon;
		typedef IfcTendonAnchorT IfcTendonAnchor;
		typedef IfcTendonAnchorTypeT IfcTendonAnchorType;
		typedef IfcTendonAnchorTypeEnumT IfcTendonAnchorTypeEnum;
		typedef IfcTendonTypeT IfcTendonType;
		typedef IfcTendonTypeEnumT IfcTendonTypeEnum;
		typedef IfcTessellatedFaceSetT IfcTessellatedFaceSet;
		typedef IfcTessellatedItemT IfcTessellatedItem;
		typedef IfcTextT IfcText;
		typedef IfcTextAlignmentT IfcTextAlignment;
		typedef IfcTextDecorationT IfcTextDecoration;
		typedef IfcTextFontNameT IfcTextFontName;
		typedef IfcTextFontSelectT IfcTextFontSelect;
		typedef IfcTextLiteralT IfcTextLiteral;
		typedef IfcTextLiteralWithExtentT IfcTextLiteralWithExtent;
		typedef IfcTextPathT IfcTextPath;
		typedef IfcTextStyleT IfcTextStyle;
		typedef IfcTextStyleFontModelT IfcTextStyleFontModel;
		typedef IfcTextStyleForDefinedFontT IfcTextStyleForDefinedFont;
		typedef IfcTextStyleSelectT IfcTextStyleSelect;
		typedef IfcTextStyleTextModelT IfcTextStyleTextModel;
		typedef IfcTextStyleWithBoxCharacteristicsT IfcTextStyleWithBoxCharacteristics;
		typedef IfcTextTransformationT IfcTextTransformation;
		typedef IfcTextureCoordinateT IfcTextureCoordinate;
		typedef IfcTextureCoordinateGeneratorT IfcTextureCoordinateGenerator;
		typedef IfcTextureMapT IfcTextureMap;
		typedef IfcTextureVertexT IfcTextureVertex;
		typedef IfcTextureVertexListT IfcTextureVertexList;
		typedef IfcThermalAdmittanceMeasureT IfcThermalAdmittanceMeasure;
		typedef IfcThermalConductivityMeasureT IfcThermalConductivityMeasure;
		typedef IfcThermalExpansionCoefficientMeasureT IfcThermalExpansionCoefficientMeasure;
		typedef IfcThermalResistanceMeasureT IfcThermalResistanceMeasure;
		typedef IfcThermalTransmittanceMeasureT IfcThermalTransmittanceMeasure;
		typedef IfcThermodynamicTemperatureMeasureT IfcThermodynamicTemperatureMeasure;
		typedef IfcTimeT IfcTime;
		typedef IfcTimeMeasureT IfcTimeMeasure;
		typedef IfcTimeOrRatioSelectT IfcTimeOrRatioSelect;
		typedef IfcTimePeriodT IfcTimePeriod;
		typedef IfcTimeSeriesT IfcTimeSeries;
		typedef IfcTimeSeriesDataTypeEnumT IfcTimeSeriesDataTypeEnum;
		typedef IfcTimeSeriesValueT IfcTimeSeriesValue;
		typedef IfcTimeStampT IfcTimeStamp;
		typedef IfcTopologicalRepresentationItemT IfcTopologicalRepresentationItem;
		typedef IfcTopologyRepresentationT IfcTopologyRepresentation;
		typedef IfcTorqueMeasureT IfcTorqueMeasure;
		typedef IfcTransformerT IfcTransformer;
		typedef IfcTransformerTypeT IfcTransformerType;
		typedef IfcTransformerTypeEnumT IfcTransformerTypeEnum;
		typedef IfcTransitionCodeT IfcTransitionCode;
		typedef IfcTranslationalStiffnessSelectT IfcTranslationalStiffnessSelect;
		typedef IfcTransportElementT IfcTransportElement;
		typedef IfcTransportElementTypeT IfcTransportElementType;
		typedef IfcTransportElementTypeEnumT IfcTransportElementTypeEnum;
		typedef IfcTrapeziumProfileDefT IfcTrapeziumProfileDef;
		typedef IfcTriangulatedFaceSetT IfcTriangulatedFaceSet;
		typedef IfcTrimmedCurveT IfcTrimmedCurve;
		typedef IfcTrimmingPreferenceT IfcTrimmingPreference;
		typedef IfcTrimmingSelectT IfcTrimmingSelect;
		typedef IfcTShapeProfileDefT IfcTShapeProfileDef;
		typedef IfcTubeBundleT IfcTubeBundle;
		typedef IfcTubeBundleTypeT IfcTubeBundleType;
		typedef IfcTubeBundleTypeEnumT IfcTubeBundleTypeEnum;
		typedef IfcTwoDirectionRepeatFactorT IfcTwoDirectionRepeatFactor;
		typedef IfcTypeObjectT IfcTypeObject;
		typedef IfcTypeProcessT IfcTypeProcess;
		typedef IfcTypeProductT IfcTypeProduct;
		typedef IfcTypeResourceT IfcTypeResource;
		typedef IfcUnitT IfcUnit;
		typedef IfcUnitaryControlElementT IfcUnitaryControlElement;
		typedef IfcUnitaryControlElementTypeT IfcUnitaryControlElementType;
		typedef IfcUnitaryControlElementTypeEnumT IfcUnitaryControlElementTypeEnum;
		typedef IfcUnitaryEquipmentT IfcUnitaryEquipment;
		typedef IfcUnitaryEquipmentTypeT IfcUnitaryEquipmentType;
		typedef IfcUnitaryEquipmentTypeEnumT IfcUnitaryEquipmentTypeEnum;
		typedef IfcUnitAssignmentT IfcUnitAssignment;
		typedef IfcUnitEnumT IfcUnitEnum;
		typedef IfcURIReferenceT IfcURIReference;
		typedef IfcUShapeProfileDefT IfcUShapeProfileDef;
		typedef IfcValueT IfcValue;
		typedef IfcValveT IfcValve;
		typedef IfcValveTypeT IfcValveType;
		typedef IfcValveTypeEnumT IfcValveTypeEnum;
		typedef IfcVaporPermeabilityMeasureT IfcVaporPermeabilityMeasure;
		typedef IfcVectorT IfcVector;
		typedef IfcVectorOrDirectionT IfcVectorOrDirection;
		typedef IfcVertexT IfcVertex;
		typedef IfcVertexLoopT IfcVertexLoop;
		typedef IfcVertexPointT IfcVertexPoint;
		typedef IfcVibrationIsolatorT IfcVibrationIsolator;
		typedef IfcVibrationIsolatorTypeT IfcVibrationIsolatorType;
		typedef IfcVibrationIsolatorTypeEnumT IfcVibrationIsolatorTypeEnum;
		typedef IfcVirtualElementT IfcVirtualElement;
		typedef IfcVirtualGridIntersectionT IfcVirtualGridIntersection;
		typedef IfcVoidingFeatureT IfcVoidingFeature;
		typedef IfcVoidingFeatureTypeEnumT IfcVoidingFeatureTypeEnum;
		typedef IfcVolumeMeasureT IfcVolumeMeasure;
		typedef IfcVolumetricFlowRateMeasureT IfcVolumetricFlowRateMeasure;
		typedef IfcWallT IfcWall;
		typedef IfcWallElementedCaseT IfcWallElementedCase;
		typedef IfcWallStandardCaseT IfcWallStandardCase;
		typedef IfcWallTypeT IfcWallType;
		typedef IfcWallTypeEnumT IfcWallTypeEnum;
		typedef IfcWarpingConstantMeasureT IfcWarpingConstantMeasure;
		typedef IfcWarpingMomentMeasureT IfcWarpingMomentMeasure;
		typedef IfcWarpingStiffnessSelectT IfcWarpingStiffnessSelect;
		typedef IfcWasteTerminalT IfcWasteTerminal;
		typedef IfcWasteTerminalTypeT IfcWasteTerminalType;
		typedef IfcWasteTerminalTypeEnumT IfcWasteTerminalTypeEnum;
		typedef IfcWindowT IfcWindow;
		typedef IfcWindowLiningPropertiesT IfcWindowLiningProperties;
		typedef IfcWindowPanelOperationEnumT IfcWindowPanelOperationEnum;
		typedef IfcWindowPanelPositionEnumT IfcWindowPanelPositionEnum;
		typedef IfcWindowPanelPropertiesT IfcWindowPanelProperties;
		typedef IfcWindowStandardCaseT IfcWindowStandardCase;
		typedef IfcWindowStyleT IfcWindowStyle;
		typedef IfcWindowStyleConstructionEnumT IfcWindowStyleConstructionEnum;
		typedef IfcWindowStyleOperationEnumT IfcWindowStyleOperationEnum;
		typedef IfcWindowTypeT IfcWindowType;
		typedef IfcWindowTypeEnumT IfcWindowTypeEnum;
		typedef IfcWindowTypePartitioningEnumT IfcWindowTypePartitioningEnum;
		typedef IfcWorkCalendarT IfcWorkCalendar;
		typedef IfcWorkCalendarTypeEnumT IfcWorkCalendarTypeEnum;
		typedef IfcWorkControlT IfcWorkControl;
		typedef IfcWorkPlanT IfcWorkPlan;
		typedef IfcWorkPlanTypeEnumT IfcWorkPlanTypeEnum;
		typedef IfcWorkScheduleT IfcWorkSchedule;
		typedef IfcWorkScheduleTypeEnumT IfcWorkScheduleTypeEnum;
		typedef IfcWorkTimeT IfcWorkTime;
		typedef IfcZoneT IfcZone;
		typedef IfcZShapeProfileDefT IfcZShapeProfileDef;
	};
}