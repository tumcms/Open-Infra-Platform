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
		typename Ifc2DCompositeCurveT,
		typename IfcAbsorbedDoseMeasureT,
		typename IfcAccelerationMeasureT,
		typename IfcActionRequestT,
		typename IfcActionSourceTypeEnumT,
		typename IfcActionTypeEnumT,
		typename IfcActorT,
		typename IfcActorRoleT,
		typename IfcActorSelectT,
		typename IfcActuatorTypeT,
		typename IfcActuatorTypeEnumT,
		typename IfcAddressT,
		typename IfcAddressTypeEnumT,
		typename IfcAheadOrBehindT,
		typename IfcAirTerminalBoxTypeT,
		typename IfcAirTerminalBoxTypeEnumT,
		typename IfcAirTerminalTypeT,
		typename IfcAirTerminalTypeEnumT,
		typename IfcAirToAirHeatRecoveryTypeT,
		typename IfcAirToAirHeatRecoveryTypeEnumT,
		typename IfcAlarmTypeT,
		typename IfcAlarmTypeEnumT,
		typename IfcAmountOfSubstanceMeasureT,
		typename IfcAnalysisModelTypeEnumT,
		typename IfcAnalysisTheoryTypeEnumT,
		typename IfcAngularDimensionT,
		typename IfcAngularVelocityMeasureT,
		typename IfcAnnotationT,
		typename IfcAnnotationCurveOccurrenceT,
		typename IfcAnnotationFillAreaT,
		typename IfcAnnotationFillAreaOccurrenceT,
		typename IfcAnnotationOccurrenceT,
		typename IfcAnnotationSurfaceT,
		typename IfcAnnotationSurfaceOccurrenceT,
		typename IfcAnnotationSymbolOccurrenceT,
		typename IfcAnnotationTextOccurrenceT,
		typename IfcApplicationT,
		typename IfcAppliedValueT,
		typename IfcAppliedValueRelationshipT,
		typename IfcAppliedValueSelectT,
		typename IfcApprovalT,
		typename IfcApprovalActorRelationshipT,
		typename IfcApprovalPropertyRelationshipT,
		typename IfcApprovalRelationshipT,
		typename IfcArbitraryClosedProfileDefT,
		typename IfcArbitraryOpenProfileDefT,
		typename IfcArbitraryProfileDefWithVoidsT,
		typename IfcAreaMeasureT,
		typename IfcArithmeticOperatorEnumT,
		typename IfcAssemblyPlaceEnumT,
		typename IfcAssetT,
		typename IfcAsymmetricIShapeProfileDefT,
		typename IfcAxis1PlacementT,
		typename IfcAxis2PlacementT,
		typename IfcAxis2Placement2DT,
		typename IfcAxis2Placement3DT,
		typename IfcBeamT,
		typename IfcBeamTypeT,
		typename IfcBeamTypeEnumT,
		typename IfcBenchmarkEnumT,
		typename IfcBezierCurveT,
		typename IfcBlobTextureT,
		typename IfcBlockT,
		typename IfcBoilerTypeT,
		typename IfcBoilerTypeEnumT,
		typename IfcBooleanT,
		typename IfcBooleanClippingResultT,
		typename IfcBooleanOperandT,
		typename IfcBooleanOperatorT,
		typename IfcBooleanResultT,
		typename IfcBoundaryConditionT,
		typename IfcBoundaryEdgeConditionT,
		typename IfcBoundaryFaceConditionT,
		typename IfcBoundaryNodeConditionT,
		typename IfcBoundaryNodeConditionWarpingT,
		typename IfcBoundedCurveT,
		typename IfcBoundedSurfaceT,
		typename IfcBoundingBoxT,
		typename IfcBoxAlignmentT,
		typename IfcBoxedHalfSpaceT,
		typename IfcBSplineCurveT,
		typename IfcBSplineCurveFormT,
		typename IfcBuildingT,
		typename IfcBuildingElementT,
		typename IfcBuildingElementComponentT,
		typename IfcBuildingElementPartT,
		typename IfcBuildingElementProxyT,
		typename IfcBuildingElementProxyTypeT,
		typename IfcBuildingElementProxyTypeEnumT,
		typename IfcBuildingElementTypeT,
		typename IfcBuildingStoreyT,
		typename IfcCableCarrierFittingTypeT,
		typename IfcCableCarrierFittingTypeEnumT,
		typename IfcCableCarrierSegmentTypeT,
		typename IfcCableCarrierSegmentTypeEnumT,
		typename IfcCableSegmentTypeT,
		typename IfcCableSegmentTypeEnumT,
		typename IfcCalendarDateT,
		typename IfcCartesianPointT,
		typename IfcCartesianTransformationOperatorT,
		typename IfcCartesianTransformationOperator2DT,
		typename IfcCartesianTransformationOperator2DnonUniformT,
		typename IfcCartesianTransformationOperator3DT,
		typename IfcCartesianTransformationOperator3DnonUniformT,
		typename IfcCenterLineProfileDefT,
		typename IfcChamferEdgeFeatureT,
		typename IfcChangeActionEnumT,
		typename IfcCharacterStyleSelectT,
		typename IfcChillerTypeT,
		typename IfcChillerTypeEnumT,
		typename IfcCircleT,
		typename IfcCircleHollowProfileDefT,
		typename IfcCircleProfileDefT,
		typename IfcClassificationT,
		typename IfcClassificationItemT,
		typename IfcClassificationItemRelationshipT,
		typename IfcClassificationNotationT,
		typename IfcClassificationNotationFacetT,
		typename IfcClassificationNotationSelectT,
		typename IfcClassificationReferenceT,
		typename IfcClosedShellT,
		typename IfcCoilTypeT,
		typename IfcCoilTypeEnumT,
		typename IfcColourT,
		typename IfcColourOrFactorT,
		typename IfcColourRgbT,
		typename IfcColourSpecificationT,
		typename IfcColumnT,
		typename IfcColumnTypeT,
		typename IfcColumnTypeEnumT,
		typename IfcComplexNumberT,
		typename IfcComplexPropertyT,
		typename IfcCompositeCurveT,
		typename IfcCompositeCurveSegmentT,
		typename IfcCompositeProfileDefT,
		typename IfcCompoundPlaneAngleMeasureT,
		typename IfcCompressorTypeT,
		typename IfcCompressorTypeEnumT,
		typename IfcCondenserTypeT,
		typename IfcCondenserTypeEnumT,
		typename IfcConditionT,
		typename IfcConditionCriterionT,
		typename IfcConditionCriterionSelectT,
		typename IfcConicT,
		typename IfcConnectedFaceSetT,
		typename IfcConnectionCurveGeometryT,
		typename IfcConnectionGeometryT,
		typename IfcConnectionPointEccentricityT,
		typename IfcConnectionPointGeometryT,
		typename IfcConnectionPortGeometryT,
		typename IfcConnectionSurfaceGeometryT,
		typename IfcConnectionTypeEnumT,
		typename IfcConstraintT,
		typename IfcConstraintAggregationRelationshipT,
		typename IfcConstraintClassificationRelationshipT,
		typename IfcConstraintEnumT,
		typename IfcConstraintRelationshipT,
		typename IfcConstructionEquipmentResourceT,
		typename IfcConstructionMaterialResourceT,
		typename IfcConstructionProductResourceT,
		typename IfcConstructionResourceT,
		typename IfcContextDependentMeasureT,
		typename IfcContextDependentUnitT,
		typename IfcControlT,
		typename IfcControllerTypeT,
		typename IfcControllerTypeEnumT,
		typename IfcConversionBasedUnitT,
		typename IfcCooledBeamTypeT,
		typename IfcCooledBeamTypeEnumT,
		typename IfcCoolingTowerTypeT,
		typename IfcCoolingTowerTypeEnumT,
		typename IfcCoordinatedUniversalTimeOffsetT,
		typename IfcCostItemT,
		typename IfcCostScheduleT,
		typename IfcCostScheduleTypeEnumT,
		typename IfcCostValueT,
		typename IfcCountMeasureT,
		typename IfcCoveringT,
		typename IfcCoveringTypeT,
		typename IfcCoveringTypeEnumT,
		typename IfcCraneRailAShapeProfileDefT,
		typename IfcCraneRailFShapeProfileDefT,
		typename IfcCrewResourceT,
		typename IfcCsgPrimitive3DT,
		typename IfcCsgSelectT,
		typename IfcCsgSolidT,
		typename IfcCShapeProfileDefT,
		typename IfcCurrencyEnumT,
		typename IfcCurrencyRelationshipT,
		typename IfcCurtainWallT,
		typename IfcCurtainWallTypeT,
		typename IfcCurtainWallTypeEnumT,
		typename IfcCurvatureMeasureT,
		typename IfcCurveT,
		typename IfcCurveBoundedPlaneT,
		typename IfcCurveFontOrScaledCurveFontSelectT,
		typename IfcCurveOrEdgeCurveT,
		typename IfcCurveStyleT,
		typename IfcCurveStyleFontT,
		typename IfcCurveStyleFontAndScalingT,
		typename IfcCurveStyleFontPatternT,
		typename IfcCurveStyleFontSelectT,
		typename IfcDamperTypeT,
		typename IfcDamperTypeEnumT,
		typename IfcDataOriginEnumT,
		typename IfcDateAndTimeT,
		typename IfcDateTimeSelectT,
		typename IfcDayInMonthNumberT,
		typename IfcDaylightSavingHourT,
		typename IfcDefinedSymbolT,
		typename IfcDefinedSymbolSelectT,
		typename IfcDerivedMeasureValueT,
		typename IfcDerivedProfileDefT,
		typename IfcDerivedUnitT,
		typename IfcDerivedUnitElementT,
		typename IfcDerivedUnitEnumT,
		typename IfcDescriptiveMeasureT,
		typename IfcDiameterDimensionT,
		typename IfcDimensionalExponentsT,
		typename IfcDimensionCalloutRelationshipT,
		typename IfcDimensionCountT,
		typename IfcDimensionCurveT,
		typename IfcDimensionCurveDirectedCalloutT,
		typename IfcDimensionCurveTerminatorT,
		typename IfcDimensionExtentUsageT,
		typename IfcDimensionPairT,
		typename IfcDirectionT,
		typename IfcDirectionSenseEnumT,
		typename IfcDiscreteAccessoryT,
		typename IfcDiscreteAccessoryTypeT,
		typename IfcDistributionChamberElementT,
		typename IfcDistributionChamberElementTypeT,
		typename IfcDistributionChamberElementTypeEnumT,
		typename IfcDistributionControlElementT,
		typename IfcDistributionControlElementTypeT,
		typename IfcDistributionElementT,
		typename IfcDistributionElementTypeT,
		typename IfcDistributionFlowElementT,
		typename IfcDistributionFlowElementTypeT,
		typename IfcDistributionPortT,
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
		typename IfcDoorStyleT,
		typename IfcDoorStyleConstructionEnumT,
		typename IfcDoorStyleOperationEnumT,
		typename IfcDoseEquivalentMeasureT,
		typename IfcDraughtingCalloutT,
		typename IfcDraughtingCalloutElementT,
		typename IfcDraughtingCalloutRelationshipT,
		typename IfcDraughtingPreDefinedColourT,
		typename IfcDraughtingPreDefinedCurveFontT,
		typename IfcDraughtingPreDefinedTextFontT,
		typename IfcDuctFittingTypeT,
		typename IfcDuctFittingTypeEnumT,
		typename IfcDuctSegmentTypeT,
		typename IfcDuctSegmentTypeEnumT,
		typename IfcDuctSilencerTypeT,
		typename IfcDuctSilencerTypeEnumT,
		typename IfcDynamicViscosityMeasureT,
		typename IfcEdgeT,
		typename IfcEdgeCurveT,
		typename IfcEdgeFeatureT,
		typename IfcEdgeLoopT,
		typename IfcElectricalBasePropertiesT,
		typename IfcElectricalCircuitT,
		typename IfcElectricalElementT,
		typename IfcElectricApplianceTypeT,
		typename IfcElectricApplianceTypeEnumT,
		typename IfcElectricCapacitanceMeasureT,
		typename IfcElectricChargeMeasureT,
		typename IfcElectricConductanceMeasureT,
		typename IfcElectricCurrentEnumT,
		typename IfcElectricCurrentMeasureT,
		typename IfcElectricDistributionPointT,
		typename IfcElectricDistributionPointFunctionEnumT,
		typename IfcElectricFlowStorageDeviceTypeT,
		typename IfcElectricFlowStorageDeviceTypeEnumT,
		typename IfcElectricGeneratorTypeT,
		typename IfcElectricGeneratorTypeEnumT,
		typename IfcElectricHeaterTypeT,
		typename IfcElectricHeaterTypeEnumT,
		typename IfcElectricMotorTypeT,
		typename IfcElectricMotorTypeEnumT,
		typename IfcElectricResistanceMeasureT,
		typename IfcElectricTimeControlTypeT,
		typename IfcElectricTimeControlTypeEnumT,
		typename IfcElectricVoltageMeasureT,
		typename IfcElementT,
		typename IfcElementarySurfaceT,
		typename IfcElementAssemblyT,
		typename IfcElementAssemblyTypeEnumT,
		typename IfcElementComponentT,
		typename IfcElementComponentTypeT,
		typename IfcElementCompositionEnumT,
		typename IfcElementQuantityT,
		typename IfcElementTypeT,
		typename IfcEllipseT,
		typename IfcEllipseProfileDefT,
		typename IfcEnergyConversionDeviceT,
		typename IfcEnergyConversionDeviceTypeT,
		typename IfcEnergyMeasureT,
		typename IfcEnergyPropertiesT,
		typename IfcEnergySequenceEnumT,
		typename IfcEnvironmentalImpactCategoryEnumT,
		typename IfcEnvironmentalImpactValueT,
		typename IfcEquipmentElementT,
		typename IfcEquipmentStandardT,
		typename IfcEvaporativeCoolerTypeT,
		typename IfcEvaporativeCoolerTypeEnumT,
		typename IfcEvaporatorTypeT,
		typename IfcEvaporatorTypeEnumT,
		typename IfcExtendedMaterialPropertiesT,
		typename IfcExternallyDefinedHatchStyleT,
		typename IfcExternallyDefinedSurfaceStyleT,
		typename IfcExternallyDefinedSymbolT,
		typename IfcExternallyDefinedTextFontT,
		typename IfcExternalReferenceT,
		typename IfcExtrudedAreaSolidT,
		typename IfcFaceT,
		typename IfcFaceBasedSurfaceModelT,
		typename IfcFaceBoundT,
		typename IfcFaceOuterBoundT,
		typename IfcFaceSurfaceT,
		typename IfcFacetedBrepT,
		typename IfcFacetedBrepWithVoidsT,
		typename IfcFailureConnectionConditionT,
		typename IfcFanTypeT,
		typename IfcFanTypeEnumT,
		typename IfcFastenerT,
		typename IfcFastenerTypeT,
		typename IfcFeatureElementT,
		typename IfcFeatureElementAdditionT,
		typename IfcFeatureElementSubtractionT,
		typename IfcFillAreaStyleT,
		typename IfcFillAreaStyleHatchingT,
		typename IfcFillAreaStyleTilesT,
		typename IfcFillAreaStyleTileShapeSelectT,
		typename IfcFillAreaStyleTileSymbolWithStyleT,
		typename IfcFillStyleSelectT,
		typename IfcFilterTypeT,
		typename IfcFilterTypeEnumT,
		typename IfcFireSuppressionTerminalTypeT,
		typename IfcFireSuppressionTerminalTypeEnumT,
		typename IfcFlowControllerT,
		typename IfcFlowControllerTypeT,
		typename IfcFlowDirectionEnumT,
		typename IfcFlowFittingT,
		typename IfcFlowFittingTypeT,
		typename IfcFlowInstrumentTypeT,
		typename IfcFlowInstrumentTypeEnumT,
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
		typename IfcFluidFlowPropertiesT,
		typename IfcFontStyleT,
		typename IfcFontVariantT,
		typename IfcFontWeightT,
		typename IfcFootingT,
		typename IfcFootingTypeEnumT,
		typename IfcForceMeasureT,
		typename IfcFrequencyMeasureT,
		typename IfcFuelPropertiesT,
		typename IfcFurnishingElementT,
		typename IfcFurnishingElementTypeT,
		typename IfcFurnitureStandardT,
		typename IfcFurnitureTypeT,
		typename IfcGasTerminalTypeT,
		typename IfcGasTerminalTypeEnumT,
		typename IfcGeneralMaterialPropertiesT,
		typename IfcGeneralProfilePropertiesT,
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
		typename IfcGroupT,
		typename IfcHalfSpaceSolidT,
		typename IfcHatchLineDistanceSelectT,
		typename IfcHeatExchangerTypeT,
		typename IfcHeatExchangerTypeEnumT,
		typename IfcHeatFluxDensityMeasureT,
		typename IfcHeatingValueMeasureT,
		typename IfcHourInDayT,
		typename IfcHumidifierTypeT,
		typename IfcHumidifierTypeEnumT,
		typename IfcHygroscopicMaterialPropertiesT,
		typename IfcIdentifierT,
		typename IfcIlluminanceMeasureT,
		typename IfcImageTextureT,
		typename IfcInductanceMeasureT,
		typename IfcIntegerT,
		typename IfcIntegerCountRateMeasureT,
		typename IfcInternalOrExternalEnumT,
		typename IfcInventoryT,
		typename IfcInventoryTypeEnumT,
		typename IfcIonConcentrationMeasureT,
		typename IfcIrregularTimeSeriesT,
		typename IfcIrregularTimeSeriesValueT,
		typename IfcIShapeProfileDefT,
		typename IfcIsothermalMoistureCapacityMeasureT,
		typename IfcJunctionBoxTypeT,
		typename IfcJunctionBoxTypeEnumT,
		typename IfcKinematicViscosityMeasureT,
		typename IfcLabelT,
		typename IfcLaborResourceT,
		typename IfcLampTypeT,
		typename IfcLampTypeEnumT,
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
		typename IfcLinearDimensionT,
		typename IfcLinearForceMeasureT,
		typename IfcLinearMomentMeasureT,
		typename IfcLinearStiffnessMeasureT,
		typename IfcLinearVelocityMeasureT,
		typename IfcLoadGroupTypeEnumT,
		typename IfcLocalPlacementT,
		typename IfcLocalTimeT,
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
		typename IfcMappedItemT,
		typename IfcMassDensityMeasureT,
		typename IfcMassFlowRateMeasureT,
		typename IfcMassMeasureT,
		typename IfcMassPerLengthMeasureT,
		typename IfcMaterialT,
		typename IfcMaterialClassificationRelationshipT,
		typename IfcMaterialDefinitionRepresentationT,
		typename IfcMaterialLayerT,
		typename IfcMaterialLayerSetT,
		typename IfcMaterialLayerSetUsageT,
		typename IfcMaterialListT,
		typename IfcMaterialPropertiesT,
		typename IfcMaterialSelectT,
		typename IfcMeasureValueT,
		typename IfcMeasureWithUnitT,
		typename IfcMechanicalConcreteMaterialPropertiesT,
		typename IfcMechanicalFastenerT,
		typename IfcMechanicalFastenerTypeT,
		typename IfcMechanicalMaterialPropertiesT,
		typename IfcMechanicalSteelMaterialPropertiesT,
		typename IfcMemberT,
		typename IfcMemberTypeT,
		typename IfcMemberTypeEnumT,
		typename IfcMetricT,
		typename IfcMetricValueSelectT,
		typename IfcMinuteInHourT,
		typename IfcModulusOfElasticityMeasureT,
		typename IfcModulusOfLinearSubgradeReactionMeasureT,
		typename IfcModulusOfRotationalSubgradeReactionMeasureT,
		typename IfcModulusOfSubgradeReactionMeasureT,
		typename IfcMoistureDiffusivityMeasureT,
		typename IfcMolecularWeightMeasureT,
		typename IfcMomentOfInertiaMeasureT,
		typename IfcMonetaryMeasureT,
		typename IfcMonetaryUnitT,
		typename IfcMonthInYearNumberT,
		typename IfcMotorConnectionTypeT,
		typename IfcMotorConnectionTypeEnumT,
		typename IfcMoveT,
		typename IfcNamedUnitT,
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
		typename IfcOpenShellT,
		typename IfcOpticalMaterialPropertiesT,
		typename IfcOrderActionT,
		typename IfcOrganizationT,
		typename IfcOrganizationRelationshipT,
		typename IfcOrientationSelectT,
		typename IfcOrientedEdgeT,
		typename IfcOutletTypeT,
		typename IfcOutletTypeEnumT,
		typename IfcOwnerHistoryT,
		typename IfcParameterizedProfileDefT,
		typename IfcParameterValueT,
		typename IfcPathT,
		typename IfcPerformanceHistoryT,
		typename IfcPermeableCoveringOperationEnumT,
		typename IfcPermeableCoveringPropertiesT,
		typename IfcPermitT,
		typename IfcPersonT,
		typename IfcPersonAndOrganizationT,
		typename IfcPHMeasureT,
		typename IfcPhysicalComplexQuantityT,
		typename IfcPhysicalOrVirtualEnumT,
		typename IfcPhysicalQuantityT,
		typename IfcPhysicalSimpleQuantityT,
		typename IfcPileT,
		typename IfcPileConstructionEnumT,
		typename IfcPileTypeEnumT,
		typename IfcPipeFittingTypeT,
		typename IfcPipeFittingTypeEnumT,
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
		typename IfcPreDefinedDimensionSymbolT,
		typename IfcPreDefinedItemT,
		typename IfcPreDefinedPointMarkerSymbolT,
		typename IfcPreDefinedSymbolT,
		typename IfcPreDefinedTerminatorSymbolT,
		typename IfcPreDefinedTextFontT,
		typename IfcPresentableTextT,
		typename IfcPresentationLayerAssignmentT,
		typename IfcPresentationLayerWithStyleT,
		typename IfcPresentationStyleT,
		typename IfcPresentationStyleAssignmentT,
		typename IfcPresentationStyleSelectT,
		typename IfcPressureMeasureT,
		typename IfcProcedureT,
		typename IfcProcedureTypeEnumT,
		typename IfcProcessT,
		typename IfcProductT,
		typename IfcProductDefinitionShapeT,
		typename IfcProductRepresentationT,
		typename IfcProductsOfCombustionPropertiesT,
		typename IfcProfileDefT,
		typename IfcProfilePropertiesT,
		typename IfcProfileTypeEnumT,
		typename IfcProjectT,
		typename IfcProjectedOrTrueLengthEnumT,
		typename IfcProjectionCurveT,
		typename IfcProjectionElementT,
		typename IfcProjectOrderT,
		typename IfcProjectOrderRecordT,
		typename IfcProjectOrderRecordTypeEnumT,
		typename IfcProjectOrderTypeEnumT,
		typename IfcPropertyT,
		typename IfcPropertyBoundedValueT,
		typename IfcPropertyConstraintRelationshipT,
		typename IfcPropertyDefinitionT,
		typename IfcPropertyDependencyRelationshipT,
		typename IfcPropertyEnumeratedValueT,
		typename IfcPropertyEnumerationT,
		typename IfcPropertyListValueT,
		typename IfcPropertyReferenceValueT,
		typename IfcPropertySetT,
		typename IfcPropertySetDefinitionT,
		typename IfcPropertySingleValueT,
		typename IfcPropertySourceEnumT,
		typename IfcPropertyTableValueT,
		typename IfcProtectiveDeviceTypeT,
		typename IfcProtectiveDeviceTypeEnumT,
		typename IfcProxyT,
		typename IfcPumpTypeT,
		typename IfcPumpTypeEnumT,
		typename IfcQuantityAreaT,
		typename IfcQuantityCountT,
		typename IfcQuantityLengthT,
		typename IfcQuantityTimeT,
		typename IfcQuantityVolumeT,
		typename IfcQuantityWeightT,
		typename IfcRadioActivityMeasureT,
		typename IfcRadiusDimensionT,
		typename IfcRailingT,
		typename IfcRailingTypeT,
		typename IfcRailingTypeEnumT,
		typename IfcRampT,
		typename IfcRampFlightT,
		typename IfcRampFlightTypeT,
		typename IfcRampFlightTypeEnumT,
		typename IfcRampTypeEnumT,
		typename IfcRatioMeasureT,
		typename IfcRationalBezierCurveT,
		typename IfcRealT,
		typename IfcRectangleHollowProfileDefT,
		typename IfcRectangleProfileDefT,
		typename IfcRectangularPyramidT,
		typename IfcRectangularTrimmedSurfaceT,
		typename IfcReferencesValueDocumentT,
		typename IfcReflectanceMethodEnumT,
		typename IfcRegularTimeSeriesT,
		typename IfcReinforcementBarPropertiesT,
		typename IfcReinforcementDefinitionPropertiesT,
		typename IfcReinforcingBarT,
		typename IfcReinforcingBarRoleEnumT,
		typename IfcReinforcingBarSurfaceEnumT,
		typename IfcReinforcingElementT,
		typename IfcReinforcingMeshT,
		typename IfcRelAggregatesT,
		typename IfcRelAssignsT,
		typename IfcRelAssignsTasksT,
		typename IfcRelAssignsToActorT,
		typename IfcRelAssignsToControlT,
		typename IfcRelAssignsToGroupT,
		typename IfcRelAssignsToProcessT,
		typename IfcRelAssignsToProductT,
		typename IfcRelAssignsToProjectOrderT,
		typename IfcRelAssignsToResourceT,
		typename IfcRelAssociatesT,
		typename IfcRelAssociatesAppliedValueT,
		typename IfcRelAssociatesApprovalT,
		typename IfcRelAssociatesClassificationT,
		typename IfcRelAssociatesConstraintT,
		typename IfcRelAssociatesDocumentT,
		typename IfcRelAssociatesLibraryT,
		typename IfcRelAssociatesMaterialT,
		typename IfcRelAssociatesProfilePropertiesT,
		typename IfcRelationshipT,
		typename IfcRelaxationT,
		typename IfcRelConnectsT,
		typename IfcRelConnectsElementsT,
		typename IfcRelConnectsPathElementsT,
		typename IfcRelConnectsPortsT,
		typename IfcRelConnectsPortToElementT,
		typename IfcRelConnectsStructuralActivityT,
		typename IfcRelConnectsStructuralElementT,
		typename IfcRelConnectsStructuralMemberT,
		typename IfcRelConnectsWithEccentricityT,
		typename IfcRelConnectsWithRealizingElementsT,
		typename IfcRelContainedInSpatialStructureT,
		typename IfcRelCoversBldgElementsT,
		typename IfcRelCoversSpacesT,
		typename IfcRelDecomposesT,
		typename IfcRelDefinesT,
		typename IfcRelDefinesByPropertiesT,
		typename IfcRelDefinesByTypeT,
		typename IfcRelFillsElementT,
		typename IfcRelFlowControlElementsT,
		typename IfcRelInteractionRequirementsT,
		typename IfcRelNestsT,
		typename IfcRelOccupiesSpacesT,
		typename IfcRelOverridesPropertiesT,
		typename IfcRelProjectsElementT,
		typename IfcRelReferencedInSpatialStructureT,
		typename IfcRelSchedulesCostItemsT,
		typename IfcRelSequenceT,
		typename IfcRelServicesBuildingsT,
		typename IfcRelSpaceBoundaryT,
		typename IfcRelVoidsElementT,
		typename IfcRepresentationT,
		typename IfcRepresentationContextT,
		typename IfcRepresentationItemT,
		typename IfcRepresentationMapT,
		typename IfcResourceT,
		typename IfcResourceConsumptionEnumT,
		typename IfcRevolvedAreaSolidT,
		typename IfcRibPlateDirectionEnumT,
		typename IfcRibPlateProfilePropertiesT,
		typename IfcRightCircularConeT,
		typename IfcRightCircularCylinderT,
		typename IfcRoleEnumT,
		typename IfcRoofT,
		typename IfcRoofTypeEnumT,
		typename IfcRootT,
		typename IfcRotationalFrequencyMeasureT,
		typename IfcRotationalMassMeasureT,
		typename IfcRotationalStiffnessMeasureT,
		typename IfcRoundedEdgeFeatureT,
		typename IfcRoundedRectangleProfileDefT,
		typename IfcSanitaryTerminalTypeT,
		typename IfcSanitaryTerminalTypeEnumT,
		typename IfcScheduleTimeControlT,
		typename IfcSecondInMinuteT,
		typename IfcSectionalAreaIntegralMeasureT,
		typename IfcSectionedSpineT,
		typename IfcSectionModulusMeasureT,
		typename IfcSectionPropertiesT,
		typename IfcSectionReinforcementPropertiesT,
		typename IfcSectionTypeEnumT,
		typename IfcSensorTypeT,
		typename IfcSensorTypeEnumT,
		typename IfcSequenceEnumT,
		typename IfcServiceLifeT,
		typename IfcServiceLifeFactorT,
		typename IfcServiceLifeFactorTypeEnumT,
		typename IfcServiceLifeTypeEnumT,
		typename IfcShapeAspectT,
		typename IfcShapeModelT,
		typename IfcShapeRepresentationT,
		typename IfcShearModulusMeasureT,
		typename IfcShellT,
		typename IfcShellBasedSurfaceModelT,
		typename IfcSimplePropertyT,
		typename IfcSimpleValueT,
		typename IfcSIPrefixT,
		typename IfcSiteT,
		typename IfcSIUnitT,
		typename IfcSIUnitNameT,
		typename IfcSizeSelectT,
		typename IfcSlabT,
		typename IfcSlabTypeT,
		typename IfcSlabTypeEnumT,
		typename IfcSlippageConnectionConditionT,
		typename IfcSolidAngleMeasureT,
		typename IfcSolidModelT,
		typename IfcSoundPowerMeasureT,
		typename IfcSoundPressureMeasureT,
		typename IfcSoundPropertiesT,
		typename IfcSoundScaleEnumT,
		typename IfcSoundValueT,
		typename IfcSpaceT,
		typename IfcSpaceHeaterTypeT,
		typename IfcSpaceHeaterTypeEnumT,
		typename IfcSpaceProgramT,
		typename IfcSpaceThermalLoadPropertiesT,
		typename IfcSpaceTypeT,
		typename IfcSpaceTypeEnumT,
		typename IfcSpatialStructureElementT,
		typename IfcSpatialStructureElementTypeT,
		typename IfcSpecificHeatCapacityMeasureT,
		typename IfcSpecularExponentT,
		typename IfcSpecularHighlightSelectT,
		typename IfcSpecularRoughnessT,
		typename IfcSphereT,
		typename IfcStackTerminalTypeT,
		typename IfcStackTerminalTypeEnumT,
		typename IfcStairT,
		typename IfcStairFlightT,
		typename IfcStairFlightTypeT,
		typename IfcStairFlightTypeEnumT,
		typename IfcStairTypeEnumT,
		typename IfcStateEnumT,
		typename IfcStructuralActionT,
		typename IfcStructuralActivityT,
		typename IfcStructuralActivityAssignmentSelectT,
		typename IfcStructuralAnalysisModelT,
		typename IfcStructuralConnectionT,
		typename IfcStructuralConnectionConditionT,
		typename IfcStructuralCurveConnectionT,
		typename IfcStructuralCurveMemberT,
		typename IfcStructuralCurveMemberVaryingT,
		typename IfcStructuralCurveTypeEnumT,
		typename IfcStructuralItemT,
		typename IfcStructuralLinearActionT,
		typename IfcStructuralLinearActionVaryingT,
		typename IfcStructuralLoadT,
		typename IfcStructuralLoadGroupT,
		typename IfcStructuralLoadLinearForceT,
		typename IfcStructuralLoadPlanarForceT,
		typename IfcStructuralLoadSingleDisplacementT,
		typename IfcStructuralLoadSingleDisplacementDistortionT,
		typename IfcStructuralLoadSingleForceT,
		typename IfcStructuralLoadSingleForceWarpingT,
		typename IfcStructuralLoadStaticT,
		typename IfcStructuralLoadTemperatureT,
		typename IfcStructuralMemberT,
		typename IfcStructuralPlanarActionT,
		typename IfcStructuralPlanarActionVaryingT,
		typename IfcStructuralPointActionT,
		typename IfcStructuralPointConnectionT,
		typename IfcStructuralPointReactionT,
		typename IfcStructuralProfilePropertiesT,
		typename IfcStructuralReactionT,
		typename IfcStructuralResultGroupT,
		typename IfcStructuralSteelProfilePropertiesT,
		typename IfcStructuralSurfaceConnectionT,
		typename IfcStructuralSurfaceMemberT,
		typename IfcStructuralSurfaceMemberVaryingT,
		typename IfcStructuralSurfaceTypeEnumT,
		typename IfcStructuredDimensionCalloutT,
		typename IfcStyledItemT,
		typename IfcStyledRepresentationT,
		typename IfcStyleModelT,
		typename IfcSubContractResourceT,
		typename IfcSubedgeT,
		typename IfcSurfaceT,
		typename IfcSurfaceCurveSweptAreaSolidT,
		typename IfcSurfaceOfLinearExtrusionT,
		typename IfcSurfaceOfRevolutionT,
		typename IfcSurfaceOrFaceSurfaceT,
		typename IfcSurfaceSideT,
		typename IfcSurfaceStyleT,
		typename IfcSurfaceStyleElementSelectT,
		typename IfcSurfaceStyleLightingT,
		typename IfcSurfaceStyleRefractionT,
		typename IfcSurfaceStyleRenderingT,
		typename IfcSurfaceStyleShadingT,
		typename IfcSurfaceStyleWithTexturesT,
		typename IfcSurfaceTextureT,
		typename IfcSurfaceTextureEnumT,
		typename IfcSweptAreaSolidT,
		typename IfcSweptDiskSolidT,
		typename IfcSweptSurfaceT,
		typename IfcSwitchingDeviceTypeT,
		typename IfcSwitchingDeviceTypeEnumT,
		typename IfcSymbolStyleT,
		typename IfcSymbolStyleSelectT,
		typename IfcSystemT,
		typename IfcSystemFurnitureElementTypeT,
		typename IfcTableT,
		typename IfcTableRowT,
		typename IfcTankTypeT,
		typename IfcTankTypeEnumT,
		typename IfcTaskT,
		typename IfcTelecomAddressT,
		typename IfcTemperatureGradientMeasureT,
		typename IfcTendonT,
		typename IfcTendonAnchorT,
		typename IfcTendonTypeEnumT,
		typename IfcTerminatorSymbolT,
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
		typename IfcThermalAdmittanceMeasureT,
		typename IfcThermalConductivityMeasureT,
		typename IfcThermalExpansionCoefficientMeasureT,
		typename IfcThermalLoadSourceEnumT,
		typename IfcThermalLoadTypeEnumT,
		typename IfcThermalMaterialPropertiesT,
		typename IfcThermalResistanceMeasureT,
		typename IfcThermalTransmittanceMeasureT,
		typename IfcThermodynamicTemperatureMeasureT,
		typename IfcTimeMeasureT,
		typename IfcTimeSeriesT,
		typename IfcTimeSeriesDataTypeEnumT,
		typename IfcTimeSeriesReferenceRelationshipT,
		typename IfcTimeSeriesScheduleT,
		typename IfcTimeSeriesScheduleTypeEnumT,
		typename IfcTimeSeriesValueT,
		typename IfcTimeStampT,
		typename IfcTopologicalRepresentationItemT,
		typename IfcTopologyRepresentationT,
		typename IfcTorqueMeasureT,
		typename IfcTransformerTypeT,
		typename IfcTransformerTypeEnumT,
		typename IfcTransitionCodeT,
		typename IfcTransportElementT,
		typename IfcTransportElementTypeT,
		typename IfcTransportElementTypeEnumT,
		typename IfcTrapeziumProfileDefT,
		typename IfcTrimmedCurveT,
		typename IfcTrimmingPreferenceT,
		typename IfcTrimmingSelectT,
		typename IfcTShapeProfileDefT,
		typename IfcTubeBundleTypeT,
		typename IfcTubeBundleTypeEnumT,
		typename IfcTwoDirectionRepeatFactorT,
		typename IfcTypeObjectT,
		typename IfcTypeProductT,
		typename IfcUnitT,
		typename IfcUnitaryEquipmentTypeT,
		typename IfcUnitaryEquipmentTypeEnumT,
		typename IfcUnitAssignmentT,
		typename IfcUnitEnumT,
		typename IfcUShapeProfileDefT,
		typename IfcValueT,
		typename IfcValveTypeT,
		typename IfcValveTypeEnumT,
		typename IfcVaporPermeabilityMeasureT,
		typename IfcVectorT,
		typename IfcVectorOrDirectionT,
		typename IfcVertexT,
		typename IfcVertexBasedTextureMapT,
		typename IfcVertexLoopT,
		typename IfcVertexPointT,
		typename IfcVibrationIsolatorTypeT,
		typename IfcVibrationIsolatorTypeEnumT,
		typename IfcVirtualElementT,
		typename IfcVirtualGridIntersectionT,
		typename IfcVolumeMeasureT,
		typename IfcVolumetricFlowRateMeasureT,
		typename IfcWallT,
		typename IfcWallStandardCaseT,
		typename IfcWallTypeT,
		typename IfcWallTypeEnumT,
		typename IfcWarpingConstantMeasureT,
		typename IfcWarpingMomentMeasureT,
		typename IfcWasteTerminalTypeT,
		typename IfcWasteTerminalTypeEnumT,
		typename IfcWaterPropertiesT,
		typename IfcWindowT,
		typename IfcWindowLiningPropertiesT,
		typename IfcWindowPanelOperationEnumT,
		typename IfcWindowPanelPositionEnumT,
		typename IfcWindowPanelPropertiesT,
		typename IfcWindowStyleT,
		typename IfcWindowStyleConstructionEnumT,
		typename IfcWindowStyleOperationEnumT,
		typename IfcWorkControlT,
		typename IfcWorkControlTypeEnumT,
		typename IfcWorkPlanT,
		typename IfcWorkScheduleT,
		typename IfcYearNumberT,
		typename IfcZoneT,
		typename IfcZShapeProfileDefT
	>
	struct BasicIfc2x3EntityTypes
	{
		typedef Ifc2DCompositeCurveT Ifc2DCompositeCurve;
		typedef IfcAbsorbedDoseMeasureT IfcAbsorbedDoseMeasure;
		typedef IfcAccelerationMeasureT IfcAccelerationMeasure;
		typedef IfcActionRequestT IfcActionRequest;
		typedef IfcActionSourceTypeEnumT IfcActionSourceTypeEnum;
		typedef IfcActionTypeEnumT IfcActionTypeEnum;
		typedef IfcActorT IfcActor;
		typedef IfcActorRoleT IfcActorRole;
		typedef IfcActorSelectT IfcActorSelect;
		typedef IfcActuatorTypeT IfcActuatorType;
		typedef IfcActuatorTypeEnumT IfcActuatorTypeEnum;
		typedef IfcAddressT IfcAddress;
		typedef IfcAddressTypeEnumT IfcAddressTypeEnum;
		typedef IfcAheadOrBehindT IfcAheadOrBehind;
		typedef IfcAirTerminalBoxTypeT IfcAirTerminalBoxType;
		typedef IfcAirTerminalBoxTypeEnumT IfcAirTerminalBoxTypeEnum;
		typedef IfcAirTerminalTypeT IfcAirTerminalType;
		typedef IfcAirTerminalTypeEnumT IfcAirTerminalTypeEnum;
		typedef IfcAirToAirHeatRecoveryTypeT IfcAirToAirHeatRecoveryType;
		typedef IfcAirToAirHeatRecoveryTypeEnumT IfcAirToAirHeatRecoveryTypeEnum;
		typedef IfcAlarmTypeT IfcAlarmType;
		typedef IfcAlarmTypeEnumT IfcAlarmTypeEnum;
		typedef IfcAmountOfSubstanceMeasureT IfcAmountOfSubstanceMeasure;
		typedef IfcAnalysisModelTypeEnumT IfcAnalysisModelTypeEnum;
		typedef IfcAnalysisTheoryTypeEnumT IfcAnalysisTheoryTypeEnum;
		typedef IfcAngularDimensionT IfcAngularDimension;
		typedef IfcAngularVelocityMeasureT IfcAngularVelocityMeasure;
		typedef IfcAnnotationT IfcAnnotation;
		typedef IfcAnnotationCurveOccurrenceT IfcAnnotationCurveOccurrence;
		typedef IfcAnnotationFillAreaT IfcAnnotationFillArea;
		typedef IfcAnnotationFillAreaOccurrenceT IfcAnnotationFillAreaOccurrence;
		typedef IfcAnnotationOccurrenceT IfcAnnotationOccurrence;
		typedef IfcAnnotationSurfaceT IfcAnnotationSurface;
		typedef IfcAnnotationSurfaceOccurrenceT IfcAnnotationSurfaceOccurrence;
		typedef IfcAnnotationSymbolOccurrenceT IfcAnnotationSymbolOccurrence;
		typedef IfcAnnotationTextOccurrenceT IfcAnnotationTextOccurrence;
		typedef IfcApplicationT IfcApplication;
		typedef IfcAppliedValueT IfcAppliedValue;
		typedef IfcAppliedValueRelationshipT IfcAppliedValueRelationship;
		typedef IfcAppliedValueSelectT IfcAppliedValueSelect;
		typedef IfcApprovalT IfcApproval;
		typedef IfcApprovalActorRelationshipT IfcApprovalActorRelationship;
		typedef IfcApprovalPropertyRelationshipT IfcApprovalPropertyRelationship;
		typedef IfcApprovalRelationshipT IfcApprovalRelationship;
		typedef IfcArbitraryClosedProfileDefT IfcArbitraryClosedProfileDef;
		typedef IfcArbitraryOpenProfileDefT IfcArbitraryOpenProfileDef;
		typedef IfcArbitraryProfileDefWithVoidsT IfcArbitraryProfileDefWithVoids;
		typedef IfcAreaMeasureT IfcAreaMeasure;
		typedef IfcArithmeticOperatorEnumT IfcArithmeticOperatorEnum;
		typedef IfcAssemblyPlaceEnumT IfcAssemblyPlaceEnum;
		typedef IfcAssetT IfcAsset;
		typedef IfcAsymmetricIShapeProfileDefT IfcAsymmetricIShapeProfileDef;
		typedef IfcAxis1PlacementT IfcAxis1Placement;
		typedef IfcAxis2PlacementT IfcAxis2Placement;
		typedef IfcAxis2Placement2DT IfcAxis2Placement2D;
		typedef IfcAxis2Placement3DT IfcAxis2Placement3D;
		typedef IfcBeamT IfcBeam;
		typedef IfcBeamTypeT IfcBeamType;
		typedef IfcBeamTypeEnumT IfcBeamTypeEnum;
		typedef IfcBenchmarkEnumT IfcBenchmarkEnum;
		typedef IfcBezierCurveT IfcBezierCurve;
		typedef IfcBlobTextureT IfcBlobTexture;
		typedef IfcBlockT IfcBlock;
		typedef IfcBoilerTypeT IfcBoilerType;
		typedef IfcBoilerTypeEnumT IfcBoilerTypeEnum;
		typedef IfcBooleanT IfcBoolean;
		typedef IfcBooleanClippingResultT IfcBooleanClippingResult;
		typedef IfcBooleanOperandT IfcBooleanOperand;
		typedef IfcBooleanOperatorT IfcBooleanOperator;
		typedef IfcBooleanResultT IfcBooleanResult;
		typedef IfcBoundaryConditionT IfcBoundaryCondition;
		typedef IfcBoundaryEdgeConditionT IfcBoundaryEdgeCondition;
		typedef IfcBoundaryFaceConditionT IfcBoundaryFaceCondition;
		typedef IfcBoundaryNodeConditionT IfcBoundaryNodeCondition;
		typedef IfcBoundaryNodeConditionWarpingT IfcBoundaryNodeConditionWarping;
		typedef IfcBoundedCurveT IfcBoundedCurve;
		typedef IfcBoundedSurfaceT IfcBoundedSurface;
		typedef IfcBoundingBoxT IfcBoundingBox;
		typedef IfcBoxAlignmentT IfcBoxAlignment;
		typedef IfcBoxedHalfSpaceT IfcBoxedHalfSpace;
		typedef IfcBSplineCurveT IfcBSplineCurve;
		typedef IfcBSplineCurveFormT IfcBSplineCurveForm;
		typedef IfcBuildingT IfcBuilding;
		typedef IfcBuildingElementT IfcBuildingElement;
		typedef IfcBuildingElementComponentT IfcBuildingElementComponent;
		typedef IfcBuildingElementPartT IfcBuildingElementPart;
		typedef IfcBuildingElementProxyT IfcBuildingElementProxy;
		typedef IfcBuildingElementProxyTypeT IfcBuildingElementProxyType;
		typedef IfcBuildingElementProxyTypeEnumT IfcBuildingElementProxyTypeEnum;
		typedef IfcBuildingElementTypeT IfcBuildingElementType;
		typedef IfcBuildingStoreyT IfcBuildingStorey;
		typedef IfcCableCarrierFittingTypeT IfcCableCarrierFittingType;
		typedef IfcCableCarrierFittingTypeEnumT IfcCableCarrierFittingTypeEnum;
		typedef IfcCableCarrierSegmentTypeT IfcCableCarrierSegmentType;
		typedef IfcCableCarrierSegmentTypeEnumT IfcCableCarrierSegmentTypeEnum;
		typedef IfcCableSegmentTypeT IfcCableSegmentType;
		typedef IfcCableSegmentTypeEnumT IfcCableSegmentTypeEnum;
		typedef IfcCalendarDateT IfcCalendarDate;
		typedef IfcCartesianPointT IfcCartesianPoint;
		typedef IfcCartesianTransformationOperatorT IfcCartesianTransformationOperator;
		typedef IfcCartesianTransformationOperator2DT IfcCartesianTransformationOperator2D;
		typedef IfcCartesianTransformationOperator2DnonUniformT IfcCartesianTransformationOperator2DnonUniform;
		typedef IfcCartesianTransformationOperator3DT IfcCartesianTransformationOperator3D;
		typedef IfcCartesianTransformationOperator3DnonUniformT IfcCartesianTransformationOperator3DnonUniform;
		typedef IfcCenterLineProfileDefT IfcCenterLineProfileDef;
		typedef IfcChamferEdgeFeatureT IfcChamferEdgeFeature;
		typedef IfcChangeActionEnumT IfcChangeActionEnum;
		typedef IfcCharacterStyleSelectT IfcCharacterStyleSelect;
		typedef IfcChillerTypeT IfcChillerType;
		typedef IfcChillerTypeEnumT IfcChillerTypeEnum;
		typedef IfcCircleT IfcCircle;
		typedef IfcCircleHollowProfileDefT IfcCircleHollowProfileDef;
		typedef IfcCircleProfileDefT IfcCircleProfileDef;
		typedef IfcClassificationT IfcClassification;
		typedef IfcClassificationItemT IfcClassificationItem;
		typedef IfcClassificationItemRelationshipT IfcClassificationItemRelationship;
		typedef IfcClassificationNotationT IfcClassificationNotation;
		typedef IfcClassificationNotationFacetT IfcClassificationNotationFacet;
		typedef IfcClassificationNotationSelectT IfcClassificationNotationSelect;
		typedef IfcClassificationReferenceT IfcClassificationReference;
		typedef IfcClosedShellT IfcClosedShell;
		typedef IfcCoilTypeT IfcCoilType;
		typedef IfcCoilTypeEnumT IfcCoilTypeEnum;
		typedef IfcColourT IfcColour;
		typedef IfcColourOrFactorT IfcColourOrFactor;
		typedef IfcColourRgbT IfcColourRgb;
		typedef IfcColourSpecificationT IfcColourSpecification;
		typedef IfcColumnT IfcColumn;
		typedef IfcColumnTypeT IfcColumnType;
		typedef IfcColumnTypeEnumT IfcColumnTypeEnum;
		typedef IfcComplexNumberT IfcComplexNumber;
		typedef IfcComplexPropertyT IfcComplexProperty;
		typedef IfcCompositeCurveT IfcCompositeCurve;
		typedef IfcCompositeCurveSegmentT IfcCompositeCurveSegment;
		typedef IfcCompositeProfileDefT IfcCompositeProfileDef;
		typedef IfcCompoundPlaneAngleMeasureT IfcCompoundPlaneAngleMeasure;
		typedef IfcCompressorTypeT IfcCompressorType;
		typedef IfcCompressorTypeEnumT IfcCompressorTypeEnum;
		typedef IfcCondenserTypeT IfcCondenserType;
		typedef IfcCondenserTypeEnumT IfcCondenserTypeEnum;
		typedef IfcConditionT IfcCondition;
		typedef IfcConditionCriterionT IfcConditionCriterion;
		typedef IfcConditionCriterionSelectT IfcConditionCriterionSelect;
		typedef IfcConicT IfcConic;
		typedef IfcConnectedFaceSetT IfcConnectedFaceSet;
		typedef IfcConnectionCurveGeometryT IfcConnectionCurveGeometry;
		typedef IfcConnectionGeometryT IfcConnectionGeometry;
		typedef IfcConnectionPointEccentricityT IfcConnectionPointEccentricity;
		typedef IfcConnectionPointGeometryT IfcConnectionPointGeometry;
		typedef IfcConnectionPortGeometryT IfcConnectionPortGeometry;
		typedef IfcConnectionSurfaceGeometryT IfcConnectionSurfaceGeometry;
		typedef IfcConnectionTypeEnumT IfcConnectionTypeEnum;
		typedef IfcConstraintT IfcConstraint;
		typedef IfcConstraintAggregationRelationshipT IfcConstraintAggregationRelationship;
		typedef IfcConstraintClassificationRelationshipT IfcConstraintClassificationRelationship;
		typedef IfcConstraintEnumT IfcConstraintEnum;
		typedef IfcConstraintRelationshipT IfcConstraintRelationship;
		typedef IfcConstructionEquipmentResourceT IfcConstructionEquipmentResource;
		typedef IfcConstructionMaterialResourceT IfcConstructionMaterialResource;
		typedef IfcConstructionProductResourceT IfcConstructionProductResource;
		typedef IfcConstructionResourceT IfcConstructionResource;
		typedef IfcContextDependentMeasureT IfcContextDependentMeasure;
		typedef IfcContextDependentUnitT IfcContextDependentUnit;
		typedef IfcControlT IfcControl;
		typedef IfcControllerTypeT IfcControllerType;
		typedef IfcControllerTypeEnumT IfcControllerTypeEnum;
		typedef IfcConversionBasedUnitT IfcConversionBasedUnit;
		typedef IfcCooledBeamTypeT IfcCooledBeamType;
		typedef IfcCooledBeamTypeEnumT IfcCooledBeamTypeEnum;
		typedef IfcCoolingTowerTypeT IfcCoolingTowerType;
		typedef IfcCoolingTowerTypeEnumT IfcCoolingTowerTypeEnum;
		typedef IfcCoordinatedUniversalTimeOffsetT IfcCoordinatedUniversalTimeOffset;
		typedef IfcCostItemT IfcCostItem;
		typedef IfcCostScheduleT IfcCostSchedule;
		typedef IfcCostScheduleTypeEnumT IfcCostScheduleTypeEnum;
		typedef IfcCostValueT IfcCostValue;
		typedef IfcCountMeasureT IfcCountMeasure;
		typedef IfcCoveringT IfcCovering;
		typedef IfcCoveringTypeT IfcCoveringType;
		typedef IfcCoveringTypeEnumT IfcCoveringTypeEnum;
		typedef IfcCraneRailAShapeProfileDefT IfcCraneRailAShapeProfileDef;
		typedef IfcCraneRailFShapeProfileDefT IfcCraneRailFShapeProfileDef;
		typedef IfcCrewResourceT IfcCrewResource;
		typedef IfcCsgPrimitive3DT IfcCsgPrimitive3D;
		typedef IfcCsgSelectT IfcCsgSelect;
		typedef IfcCsgSolidT IfcCsgSolid;
		typedef IfcCShapeProfileDefT IfcCShapeProfileDef;
		typedef IfcCurrencyEnumT IfcCurrencyEnum;
		typedef IfcCurrencyRelationshipT IfcCurrencyRelationship;
		typedef IfcCurtainWallT IfcCurtainWall;
		typedef IfcCurtainWallTypeT IfcCurtainWallType;
		typedef IfcCurtainWallTypeEnumT IfcCurtainWallTypeEnum;
		typedef IfcCurvatureMeasureT IfcCurvatureMeasure;
		typedef IfcCurveT IfcCurve;
		typedef IfcCurveBoundedPlaneT IfcCurveBoundedPlane;
		typedef IfcCurveFontOrScaledCurveFontSelectT IfcCurveFontOrScaledCurveFontSelect;
		typedef IfcCurveOrEdgeCurveT IfcCurveOrEdgeCurve;
		typedef IfcCurveStyleT IfcCurveStyle;
		typedef IfcCurveStyleFontT IfcCurveStyleFont;
		typedef IfcCurveStyleFontAndScalingT IfcCurveStyleFontAndScaling;
		typedef IfcCurveStyleFontPatternT IfcCurveStyleFontPattern;
		typedef IfcCurveStyleFontSelectT IfcCurveStyleFontSelect;
		typedef IfcDamperTypeT IfcDamperType;
		typedef IfcDamperTypeEnumT IfcDamperTypeEnum;
		typedef IfcDataOriginEnumT IfcDataOriginEnum;
		typedef IfcDateAndTimeT IfcDateAndTime;
		typedef IfcDateTimeSelectT IfcDateTimeSelect;
		typedef IfcDayInMonthNumberT IfcDayInMonthNumber;
		typedef IfcDaylightSavingHourT IfcDaylightSavingHour;
		typedef IfcDefinedSymbolT IfcDefinedSymbol;
		typedef IfcDefinedSymbolSelectT IfcDefinedSymbolSelect;
		typedef IfcDerivedMeasureValueT IfcDerivedMeasureValue;
		typedef IfcDerivedProfileDefT IfcDerivedProfileDef;
		typedef IfcDerivedUnitT IfcDerivedUnit;
		typedef IfcDerivedUnitElementT IfcDerivedUnitElement;
		typedef IfcDerivedUnitEnumT IfcDerivedUnitEnum;
		typedef IfcDescriptiveMeasureT IfcDescriptiveMeasure;
		typedef IfcDiameterDimensionT IfcDiameterDimension;
		typedef IfcDimensionalExponentsT IfcDimensionalExponents;
		typedef IfcDimensionCalloutRelationshipT IfcDimensionCalloutRelationship;
		typedef IfcDimensionCountT IfcDimensionCount;
		typedef IfcDimensionCurveT IfcDimensionCurve;
		typedef IfcDimensionCurveDirectedCalloutT IfcDimensionCurveDirectedCallout;
		typedef IfcDimensionCurveTerminatorT IfcDimensionCurveTerminator;
		typedef IfcDimensionExtentUsageT IfcDimensionExtentUsage;
		typedef IfcDimensionPairT IfcDimensionPair;
		typedef IfcDirectionT IfcDirection;
		typedef IfcDirectionSenseEnumT IfcDirectionSenseEnum;
		typedef IfcDiscreteAccessoryT IfcDiscreteAccessory;
		typedef IfcDiscreteAccessoryTypeT IfcDiscreteAccessoryType;
		typedef IfcDistributionChamberElementT IfcDistributionChamberElement;
		typedef IfcDistributionChamberElementTypeT IfcDistributionChamberElementType;
		typedef IfcDistributionChamberElementTypeEnumT IfcDistributionChamberElementTypeEnum;
		typedef IfcDistributionControlElementT IfcDistributionControlElement;
		typedef IfcDistributionControlElementTypeT IfcDistributionControlElementType;
		typedef IfcDistributionElementT IfcDistributionElement;
		typedef IfcDistributionElementTypeT IfcDistributionElementType;
		typedef IfcDistributionFlowElementT IfcDistributionFlowElement;
		typedef IfcDistributionFlowElementTypeT IfcDistributionFlowElementType;
		typedef IfcDistributionPortT IfcDistributionPort;
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
		typedef IfcDoorStyleT IfcDoorStyle;
		typedef IfcDoorStyleConstructionEnumT IfcDoorStyleConstructionEnum;
		typedef IfcDoorStyleOperationEnumT IfcDoorStyleOperationEnum;
		typedef IfcDoseEquivalentMeasureT IfcDoseEquivalentMeasure;
		typedef IfcDraughtingCalloutT IfcDraughtingCallout;
		typedef IfcDraughtingCalloutElementT IfcDraughtingCalloutElement;
		typedef IfcDraughtingCalloutRelationshipT IfcDraughtingCalloutRelationship;
		typedef IfcDraughtingPreDefinedColourT IfcDraughtingPreDefinedColour;
		typedef IfcDraughtingPreDefinedCurveFontT IfcDraughtingPreDefinedCurveFont;
		typedef IfcDraughtingPreDefinedTextFontT IfcDraughtingPreDefinedTextFont;
		typedef IfcDuctFittingTypeT IfcDuctFittingType;
		typedef IfcDuctFittingTypeEnumT IfcDuctFittingTypeEnum;
		typedef IfcDuctSegmentTypeT IfcDuctSegmentType;
		typedef IfcDuctSegmentTypeEnumT IfcDuctSegmentTypeEnum;
		typedef IfcDuctSilencerTypeT IfcDuctSilencerType;
		typedef IfcDuctSilencerTypeEnumT IfcDuctSilencerTypeEnum;
		typedef IfcDynamicViscosityMeasureT IfcDynamicViscosityMeasure;
		typedef IfcEdgeT IfcEdge;
		typedef IfcEdgeCurveT IfcEdgeCurve;
		typedef IfcEdgeFeatureT IfcEdgeFeature;
		typedef IfcEdgeLoopT IfcEdgeLoop;
		typedef IfcElectricalBasePropertiesT IfcElectricalBaseProperties;
		typedef IfcElectricalCircuitT IfcElectricalCircuit;
		typedef IfcElectricalElementT IfcElectricalElement;
		typedef IfcElectricApplianceTypeT IfcElectricApplianceType;
		typedef IfcElectricApplianceTypeEnumT IfcElectricApplianceTypeEnum;
		typedef IfcElectricCapacitanceMeasureT IfcElectricCapacitanceMeasure;
		typedef IfcElectricChargeMeasureT IfcElectricChargeMeasure;
		typedef IfcElectricConductanceMeasureT IfcElectricConductanceMeasure;
		typedef IfcElectricCurrentEnumT IfcElectricCurrentEnum;
		typedef IfcElectricCurrentMeasureT IfcElectricCurrentMeasure;
		typedef IfcElectricDistributionPointT IfcElectricDistributionPoint;
		typedef IfcElectricDistributionPointFunctionEnumT IfcElectricDistributionPointFunctionEnum;
		typedef IfcElectricFlowStorageDeviceTypeT IfcElectricFlowStorageDeviceType;
		typedef IfcElectricFlowStorageDeviceTypeEnumT IfcElectricFlowStorageDeviceTypeEnum;
		typedef IfcElectricGeneratorTypeT IfcElectricGeneratorType;
		typedef IfcElectricGeneratorTypeEnumT IfcElectricGeneratorTypeEnum;
		typedef IfcElectricHeaterTypeT IfcElectricHeaterType;
		typedef IfcElectricHeaterTypeEnumT IfcElectricHeaterTypeEnum;
		typedef IfcElectricMotorTypeT IfcElectricMotorType;
		typedef IfcElectricMotorTypeEnumT IfcElectricMotorTypeEnum;
		typedef IfcElectricResistanceMeasureT IfcElectricResistanceMeasure;
		typedef IfcElectricTimeControlTypeT IfcElectricTimeControlType;
		typedef IfcElectricTimeControlTypeEnumT IfcElectricTimeControlTypeEnum;
		typedef IfcElectricVoltageMeasureT IfcElectricVoltageMeasure;
		typedef IfcElementT IfcElement;
		typedef IfcElementarySurfaceT IfcElementarySurface;
		typedef IfcElementAssemblyT IfcElementAssembly;
		typedef IfcElementAssemblyTypeEnumT IfcElementAssemblyTypeEnum;
		typedef IfcElementComponentT IfcElementComponent;
		typedef IfcElementComponentTypeT IfcElementComponentType;
		typedef IfcElementCompositionEnumT IfcElementCompositionEnum;
		typedef IfcElementQuantityT IfcElementQuantity;
		typedef IfcElementTypeT IfcElementType;
		typedef IfcEllipseT IfcEllipse;
		typedef IfcEllipseProfileDefT IfcEllipseProfileDef;
		typedef IfcEnergyConversionDeviceT IfcEnergyConversionDevice;
		typedef IfcEnergyConversionDeviceTypeT IfcEnergyConversionDeviceType;
		typedef IfcEnergyMeasureT IfcEnergyMeasure;
		typedef IfcEnergyPropertiesT IfcEnergyProperties;
		typedef IfcEnergySequenceEnumT IfcEnergySequenceEnum;
		typedef IfcEnvironmentalImpactCategoryEnumT IfcEnvironmentalImpactCategoryEnum;
		typedef IfcEnvironmentalImpactValueT IfcEnvironmentalImpactValue;
		typedef IfcEquipmentElementT IfcEquipmentElement;
		typedef IfcEquipmentStandardT IfcEquipmentStandard;
		typedef IfcEvaporativeCoolerTypeT IfcEvaporativeCoolerType;
		typedef IfcEvaporativeCoolerTypeEnumT IfcEvaporativeCoolerTypeEnum;
		typedef IfcEvaporatorTypeT IfcEvaporatorType;
		typedef IfcEvaporatorTypeEnumT IfcEvaporatorTypeEnum;
		typedef IfcExtendedMaterialPropertiesT IfcExtendedMaterialProperties;
		typedef IfcExternallyDefinedHatchStyleT IfcExternallyDefinedHatchStyle;
		typedef IfcExternallyDefinedSurfaceStyleT IfcExternallyDefinedSurfaceStyle;
		typedef IfcExternallyDefinedSymbolT IfcExternallyDefinedSymbol;
		typedef IfcExternallyDefinedTextFontT IfcExternallyDefinedTextFont;
		typedef IfcExternalReferenceT IfcExternalReference;
		typedef IfcExtrudedAreaSolidT IfcExtrudedAreaSolid;
		typedef IfcFaceT IfcFace;
		typedef IfcFaceBasedSurfaceModelT IfcFaceBasedSurfaceModel;
		typedef IfcFaceBoundT IfcFaceBound;
		typedef IfcFaceOuterBoundT IfcFaceOuterBound;
		typedef IfcFaceSurfaceT IfcFaceSurface;
		typedef IfcFacetedBrepT IfcFacetedBrep;
		typedef IfcFacetedBrepWithVoidsT IfcFacetedBrepWithVoids;
		typedef IfcFailureConnectionConditionT IfcFailureConnectionCondition;
		typedef IfcFanTypeT IfcFanType;
		typedef IfcFanTypeEnumT IfcFanTypeEnum;
		typedef IfcFastenerT IfcFastener;
		typedef IfcFastenerTypeT IfcFastenerType;
		typedef IfcFeatureElementT IfcFeatureElement;
		typedef IfcFeatureElementAdditionT IfcFeatureElementAddition;
		typedef IfcFeatureElementSubtractionT IfcFeatureElementSubtraction;
		typedef IfcFillAreaStyleT IfcFillAreaStyle;
		typedef IfcFillAreaStyleHatchingT IfcFillAreaStyleHatching;
		typedef IfcFillAreaStyleTilesT IfcFillAreaStyleTiles;
		typedef IfcFillAreaStyleTileShapeSelectT IfcFillAreaStyleTileShapeSelect;
		typedef IfcFillAreaStyleTileSymbolWithStyleT IfcFillAreaStyleTileSymbolWithStyle;
		typedef IfcFillStyleSelectT IfcFillStyleSelect;
		typedef IfcFilterTypeT IfcFilterType;
		typedef IfcFilterTypeEnumT IfcFilterTypeEnum;
		typedef IfcFireSuppressionTerminalTypeT IfcFireSuppressionTerminalType;
		typedef IfcFireSuppressionTerminalTypeEnumT IfcFireSuppressionTerminalTypeEnum;
		typedef IfcFlowControllerT IfcFlowController;
		typedef IfcFlowControllerTypeT IfcFlowControllerType;
		typedef IfcFlowDirectionEnumT IfcFlowDirectionEnum;
		typedef IfcFlowFittingT IfcFlowFitting;
		typedef IfcFlowFittingTypeT IfcFlowFittingType;
		typedef IfcFlowInstrumentTypeT IfcFlowInstrumentType;
		typedef IfcFlowInstrumentTypeEnumT IfcFlowInstrumentTypeEnum;
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
		typedef IfcFluidFlowPropertiesT IfcFluidFlowProperties;
		typedef IfcFontStyleT IfcFontStyle;
		typedef IfcFontVariantT IfcFontVariant;
		typedef IfcFontWeightT IfcFontWeight;
		typedef IfcFootingT IfcFooting;
		typedef IfcFootingTypeEnumT IfcFootingTypeEnum;
		typedef IfcForceMeasureT IfcForceMeasure;
		typedef IfcFrequencyMeasureT IfcFrequencyMeasure;
		typedef IfcFuelPropertiesT IfcFuelProperties;
		typedef IfcFurnishingElementT IfcFurnishingElement;
		typedef IfcFurnishingElementTypeT IfcFurnishingElementType;
		typedef IfcFurnitureStandardT IfcFurnitureStandard;
		typedef IfcFurnitureTypeT IfcFurnitureType;
		typedef IfcGasTerminalTypeT IfcGasTerminalType;
		typedef IfcGasTerminalTypeEnumT IfcGasTerminalTypeEnum;
		typedef IfcGeneralMaterialPropertiesT IfcGeneralMaterialProperties;
		typedef IfcGeneralProfilePropertiesT IfcGeneralProfileProperties;
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
		typedef IfcGroupT IfcGroup;
		typedef IfcHalfSpaceSolidT IfcHalfSpaceSolid;
		typedef IfcHatchLineDistanceSelectT IfcHatchLineDistanceSelect;
		typedef IfcHeatExchangerTypeT IfcHeatExchangerType;
		typedef IfcHeatExchangerTypeEnumT IfcHeatExchangerTypeEnum;
		typedef IfcHeatFluxDensityMeasureT IfcHeatFluxDensityMeasure;
		typedef IfcHeatingValueMeasureT IfcHeatingValueMeasure;
		typedef IfcHourInDayT IfcHourInDay;
		typedef IfcHumidifierTypeT IfcHumidifierType;
		typedef IfcHumidifierTypeEnumT IfcHumidifierTypeEnum;
		typedef IfcHygroscopicMaterialPropertiesT IfcHygroscopicMaterialProperties;
		typedef IfcIdentifierT IfcIdentifier;
		typedef IfcIlluminanceMeasureT IfcIlluminanceMeasure;
		typedef IfcImageTextureT IfcImageTexture;
		typedef IfcInductanceMeasureT IfcInductanceMeasure;
		typedef IfcIntegerT IfcInteger;
		typedef IfcIntegerCountRateMeasureT IfcIntegerCountRateMeasure;
		typedef IfcInternalOrExternalEnumT IfcInternalOrExternalEnum;
		typedef IfcInventoryT IfcInventory;
		typedef IfcInventoryTypeEnumT IfcInventoryTypeEnum;
		typedef IfcIonConcentrationMeasureT IfcIonConcentrationMeasure;
		typedef IfcIrregularTimeSeriesT IfcIrregularTimeSeries;
		typedef IfcIrregularTimeSeriesValueT IfcIrregularTimeSeriesValue;
		typedef IfcIShapeProfileDefT IfcIShapeProfileDef;
		typedef IfcIsothermalMoistureCapacityMeasureT IfcIsothermalMoistureCapacityMeasure;
		typedef IfcJunctionBoxTypeT IfcJunctionBoxType;
		typedef IfcJunctionBoxTypeEnumT IfcJunctionBoxTypeEnum;
		typedef IfcKinematicViscosityMeasureT IfcKinematicViscosityMeasure;
		typedef IfcLabelT IfcLabel;
		typedef IfcLaborResourceT IfcLaborResource;
		typedef IfcLampTypeT IfcLampType;
		typedef IfcLampTypeEnumT IfcLampTypeEnum;
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
		typedef IfcLinearDimensionT IfcLinearDimension;
		typedef IfcLinearForceMeasureT IfcLinearForceMeasure;
		typedef IfcLinearMomentMeasureT IfcLinearMomentMeasure;
		typedef IfcLinearStiffnessMeasureT IfcLinearStiffnessMeasure;
		typedef IfcLinearVelocityMeasureT IfcLinearVelocityMeasure;
		typedef IfcLoadGroupTypeEnumT IfcLoadGroupTypeEnum;
		typedef IfcLocalPlacementT IfcLocalPlacement;
		typedef IfcLocalTimeT IfcLocalTime;
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
		typedef IfcMappedItemT IfcMappedItem;
		typedef IfcMassDensityMeasureT IfcMassDensityMeasure;
		typedef IfcMassFlowRateMeasureT IfcMassFlowRateMeasure;
		typedef IfcMassMeasureT IfcMassMeasure;
		typedef IfcMassPerLengthMeasureT IfcMassPerLengthMeasure;
		typedef IfcMaterialT IfcMaterial;
		typedef IfcMaterialClassificationRelationshipT IfcMaterialClassificationRelationship;
		typedef IfcMaterialDefinitionRepresentationT IfcMaterialDefinitionRepresentation;
		typedef IfcMaterialLayerT IfcMaterialLayer;
		typedef IfcMaterialLayerSetT IfcMaterialLayerSet;
		typedef IfcMaterialLayerSetUsageT IfcMaterialLayerSetUsage;
		typedef IfcMaterialListT IfcMaterialList;
		typedef IfcMaterialPropertiesT IfcMaterialProperties;
		typedef IfcMaterialSelectT IfcMaterialSelect;
		typedef IfcMeasureValueT IfcMeasureValue;
		typedef IfcMeasureWithUnitT IfcMeasureWithUnit;
		typedef IfcMechanicalConcreteMaterialPropertiesT IfcMechanicalConcreteMaterialProperties;
		typedef IfcMechanicalFastenerT IfcMechanicalFastener;
		typedef IfcMechanicalFastenerTypeT IfcMechanicalFastenerType;
		typedef IfcMechanicalMaterialPropertiesT IfcMechanicalMaterialProperties;
		typedef IfcMechanicalSteelMaterialPropertiesT IfcMechanicalSteelMaterialProperties;
		typedef IfcMemberT IfcMember;
		typedef IfcMemberTypeT IfcMemberType;
		typedef IfcMemberTypeEnumT IfcMemberTypeEnum;
		typedef IfcMetricT IfcMetric;
		typedef IfcMetricValueSelectT IfcMetricValueSelect;
		typedef IfcMinuteInHourT IfcMinuteInHour;
		typedef IfcModulusOfElasticityMeasureT IfcModulusOfElasticityMeasure;
		typedef IfcModulusOfLinearSubgradeReactionMeasureT IfcModulusOfLinearSubgradeReactionMeasure;
		typedef IfcModulusOfRotationalSubgradeReactionMeasureT IfcModulusOfRotationalSubgradeReactionMeasure;
		typedef IfcModulusOfSubgradeReactionMeasureT IfcModulusOfSubgradeReactionMeasure;
		typedef IfcMoistureDiffusivityMeasureT IfcMoistureDiffusivityMeasure;
		typedef IfcMolecularWeightMeasureT IfcMolecularWeightMeasure;
		typedef IfcMomentOfInertiaMeasureT IfcMomentOfInertiaMeasure;
		typedef IfcMonetaryMeasureT IfcMonetaryMeasure;
		typedef IfcMonetaryUnitT IfcMonetaryUnit;
		typedef IfcMonthInYearNumberT IfcMonthInYearNumber;
		typedef IfcMotorConnectionTypeT IfcMotorConnectionType;
		typedef IfcMotorConnectionTypeEnumT IfcMotorConnectionTypeEnum;
		typedef IfcMoveT IfcMove;
		typedef IfcNamedUnitT IfcNamedUnit;
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
		typedef IfcOpenShellT IfcOpenShell;
		typedef IfcOpticalMaterialPropertiesT IfcOpticalMaterialProperties;
		typedef IfcOrderActionT IfcOrderAction;
		typedef IfcOrganizationT IfcOrganization;
		typedef IfcOrganizationRelationshipT IfcOrganizationRelationship;
		typedef IfcOrientationSelectT IfcOrientationSelect;
		typedef IfcOrientedEdgeT IfcOrientedEdge;
		typedef IfcOutletTypeT IfcOutletType;
		typedef IfcOutletTypeEnumT IfcOutletTypeEnum;
		typedef IfcOwnerHistoryT IfcOwnerHistory;
		typedef IfcParameterizedProfileDefT IfcParameterizedProfileDef;
		typedef IfcParameterValueT IfcParameterValue;
		typedef IfcPathT IfcPath;
		typedef IfcPerformanceHistoryT IfcPerformanceHistory;
		typedef IfcPermeableCoveringOperationEnumT IfcPermeableCoveringOperationEnum;
		typedef IfcPermeableCoveringPropertiesT IfcPermeableCoveringProperties;
		typedef IfcPermitT IfcPermit;
		typedef IfcPersonT IfcPerson;
		typedef IfcPersonAndOrganizationT IfcPersonAndOrganization;
		typedef IfcPHMeasureT IfcPHMeasure;
		typedef IfcPhysicalComplexQuantityT IfcPhysicalComplexQuantity;
		typedef IfcPhysicalOrVirtualEnumT IfcPhysicalOrVirtualEnum;
		typedef IfcPhysicalQuantityT IfcPhysicalQuantity;
		typedef IfcPhysicalSimpleQuantityT IfcPhysicalSimpleQuantity;
		typedef IfcPileT IfcPile;
		typedef IfcPileConstructionEnumT IfcPileConstructionEnum;
		typedef IfcPileTypeEnumT IfcPileTypeEnum;
		typedef IfcPipeFittingTypeT IfcPipeFittingType;
		typedef IfcPipeFittingTypeEnumT IfcPipeFittingTypeEnum;
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
		typedef IfcPreDefinedDimensionSymbolT IfcPreDefinedDimensionSymbol;
		typedef IfcPreDefinedItemT IfcPreDefinedItem;
		typedef IfcPreDefinedPointMarkerSymbolT IfcPreDefinedPointMarkerSymbol;
		typedef IfcPreDefinedSymbolT IfcPreDefinedSymbol;
		typedef IfcPreDefinedTerminatorSymbolT IfcPreDefinedTerminatorSymbol;
		typedef IfcPreDefinedTextFontT IfcPreDefinedTextFont;
		typedef IfcPresentableTextT IfcPresentableText;
		typedef IfcPresentationLayerAssignmentT IfcPresentationLayerAssignment;
		typedef IfcPresentationLayerWithStyleT IfcPresentationLayerWithStyle;
		typedef IfcPresentationStyleT IfcPresentationStyle;
		typedef IfcPresentationStyleAssignmentT IfcPresentationStyleAssignment;
		typedef IfcPresentationStyleSelectT IfcPresentationStyleSelect;
		typedef IfcPressureMeasureT IfcPressureMeasure;
		typedef IfcProcedureT IfcProcedure;
		typedef IfcProcedureTypeEnumT IfcProcedureTypeEnum;
		typedef IfcProcessT IfcProcess;
		typedef IfcProductT IfcProduct;
		typedef IfcProductDefinitionShapeT IfcProductDefinitionShape;
		typedef IfcProductRepresentationT IfcProductRepresentation;
		typedef IfcProductsOfCombustionPropertiesT IfcProductsOfCombustionProperties;
		typedef IfcProfileDefT IfcProfileDef;
		typedef IfcProfilePropertiesT IfcProfileProperties;
		typedef IfcProfileTypeEnumT IfcProfileTypeEnum;
		typedef IfcProjectT IfcProject;
		typedef IfcProjectedOrTrueLengthEnumT IfcProjectedOrTrueLengthEnum;
		typedef IfcProjectionCurveT IfcProjectionCurve;
		typedef IfcProjectionElementT IfcProjectionElement;
		typedef IfcProjectOrderT IfcProjectOrder;
		typedef IfcProjectOrderRecordT IfcProjectOrderRecord;
		typedef IfcProjectOrderRecordTypeEnumT IfcProjectOrderRecordTypeEnum;
		typedef IfcProjectOrderTypeEnumT IfcProjectOrderTypeEnum;
		typedef IfcPropertyT IfcProperty;
		typedef IfcPropertyBoundedValueT IfcPropertyBoundedValue;
		typedef IfcPropertyConstraintRelationshipT IfcPropertyConstraintRelationship;
		typedef IfcPropertyDefinitionT IfcPropertyDefinition;
		typedef IfcPropertyDependencyRelationshipT IfcPropertyDependencyRelationship;
		typedef IfcPropertyEnumeratedValueT IfcPropertyEnumeratedValue;
		typedef IfcPropertyEnumerationT IfcPropertyEnumeration;
		typedef IfcPropertyListValueT IfcPropertyListValue;
		typedef IfcPropertyReferenceValueT IfcPropertyReferenceValue;
		typedef IfcPropertySetT IfcPropertySet;
		typedef IfcPropertySetDefinitionT IfcPropertySetDefinition;
		typedef IfcPropertySingleValueT IfcPropertySingleValue;
		typedef IfcPropertySourceEnumT IfcPropertySourceEnum;
		typedef IfcPropertyTableValueT IfcPropertyTableValue;
		typedef IfcProtectiveDeviceTypeT IfcProtectiveDeviceType;
		typedef IfcProtectiveDeviceTypeEnumT IfcProtectiveDeviceTypeEnum;
		typedef IfcProxyT IfcProxy;
		typedef IfcPumpTypeT IfcPumpType;
		typedef IfcPumpTypeEnumT IfcPumpTypeEnum;
		typedef IfcQuantityAreaT IfcQuantityArea;
		typedef IfcQuantityCountT IfcQuantityCount;
		typedef IfcQuantityLengthT IfcQuantityLength;
		typedef IfcQuantityTimeT IfcQuantityTime;
		typedef IfcQuantityVolumeT IfcQuantityVolume;
		typedef IfcQuantityWeightT IfcQuantityWeight;
		typedef IfcRadioActivityMeasureT IfcRadioActivityMeasure;
		typedef IfcRadiusDimensionT IfcRadiusDimension;
		typedef IfcRailingT IfcRailing;
		typedef IfcRailingTypeT IfcRailingType;
		typedef IfcRailingTypeEnumT IfcRailingTypeEnum;
		typedef IfcRampT IfcRamp;
		typedef IfcRampFlightT IfcRampFlight;
		typedef IfcRampFlightTypeT IfcRampFlightType;
		typedef IfcRampFlightTypeEnumT IfcRampFlightTypeEnum;
		typedef IfcRampTypeEnumT IfcRampTypeEnum;
		typedef IfcRatioMeasureT IfcRatioMeasure;
		typedef IfcRationalBezierCurveT IfcRationalBezierCurve;
		typedef IfcRealT IfcReal;
		typedef IfcRectangleHollowProfileDefT IfcRectangleHollowProfileDef;
		typedef IfcRectangleProfileDefT IfcRectangleProfileDef;
		typedef IfcRectangularPyramidT IfcRectangularPyramid;
		typedef IfcRectangularTrimmedSurfaceT IfcRectangularTrimmedSurface;
		typedef IfcReferencesValueDocumentT IfcReferencesValueDocument;
		typedef IfcReflectanceMethodEnumT IfcReflectanceMethodEnum;
		typedef IfcRegularTimeSeriesT IfcRegularTimeSeries;
		typedef IfcReinforcementBarPropertiesT IfcReinforcementBarProperties;
		typedef IfcReinforcementDefinitionPropertiesT IfcReinforcementDefinitionProperties;
		typedef IfcReinforcingBarT IfcReinforcingBar;
		typedef IfcReinforcingBarRoleEnumT IfcReinforcingBarRoleEnum;
		typedef IfcReinforcingBarSurfaceEnumT IfcReinforcingBarSurfaceEnum;
		typedef IfcReinforcingElementT IfcReinforcingElement;
		typedef IfcReinforcingMeshT IfcReinforcingMesh;
		typedef IfcRelAggregatesT IfcRelAggregates;
		typedef IfcRelAssignsT IfcRelAssigns;
		typedef IfcRelAssignsTasksT IfcRelAssignsTasks;
		typedef IfcRelAssignsToActorT IfcRelAssignsToActor;
		typedef IfcRelAssignsToControlT IfcRelAssignsToControl;
		typedef IfcRelAssignsToGroupT IfcRelAssignsToGroup;
		typedef IfcRelAssignsToProcessT IfcRelAssignsToProcess;
		typedef IfcRelAssignsToProductT IfcRelAssignsToProduct;
		typedef IfcRelAssignsToProjectOrderT IfcRelAssignsToProjectOrder;
		typedef IfcRelAssignsToResourceT IfcRelAssignsToResource;
		typedef IfcRelAssociatesT IfcRelAssociates;
		typedef IfcRelAssociatesAppliedValueT IfcRelAssociatesAppliedValue;
		typedef IfcRelAssociatesApprovalT IfcRelAssociatesApproval;
		typedef IfcRelAssociatesClassificationT IfcRelAssociatesClassification;
		typedef IfcRelAssociatesConstraintT IfcRelAssociatesConstraint;
		typedef IfcRelAssociatesDocumentT IfcRelAssociatesDocument;
		typedef IfcRelAssociatesLibraryT IfcRelAssociatesLibrary;
		typedef IfcRelAssociatesMaterialT IfcRelAssociatesMaterial;
		typedef IfcRelAssociatesProfilePropertiesT IfcRelAssociatesProfileProperties;
		typedef IfcRelationshipT IfcRelationship;
		typedef IfcRelaxationT IfcRelaxation;
		typedef IfcRelConnectsT IfcRelConnects;
		typedef IfcRelConnectsElementsT IfcRelConnectsElements;
		typedef IfcRelConnectsPathElementsT IfcRelConnectsPathElements;
		typedef IfcRelConnectsPortsT IfcRelConnectsPorts;
		typedef IfcRelConnectsPortToElementT IfcRelConnectsPortToElement;
		typedef IfcRelConnectsStructuralActivityT IfcRelConnectsStructuralActivity;
		typedef IfcRelConnectsStructuralElementT IfcRelConnectsStructuralElement;
		typedef IfcRelConnectsStructuralMemberT IfcRelConnectsStructuralMember;
		typedef IfcRelConnectsWithEccentricityT IfcRelConnectsWithEccentricity;
		typedef IfcRelConnectsWithRealizingElementsT IfcRelConnectsWithRealizingElements;
		typedef IfcRelContainedInSpatialStructureT IfcRelContainedInSpatialStructure;
		typedef IfcRelCoversBldgElementsT IfcRelCoversBldgElements;
		typedef IfcRelCoversSpacesT IfcRelCoversSpaces;
		typedef IfcRelDecomposesT IfcRelDecomposes;
		typedef IfcRelDefinesT IfcRelDefines;
		typedef IfcRelDefinesByPropertiesT IfcRelDefinesByProperties;
		typedef IfcRelDefinesByTypeT IfcRelDefinesByType;
		typedef IfcRelFillsElementT IfcRelFillsElement;
		typedef IfcRelFlowControlElementsT IfcRelFlowControlElements;
		typedef IfcRelInteractionRequirementsT IfcRelInteractionRequirements;
		typedef IfcRelNestsT IfcRelNests;
		typedef IfcRelOccupiesSpacesT IfcRelOccupiesSpaces;
		typedef IfcRelOverridesPropertiesT IfcRelOverridesProperties;
		typedef IfcRelProjectsElementT IfcRelProjectsElement;
		typedef IfcRelReferencedInSpatialStructureT IfcRelReferencedInSpatialStructure;
		typedef IfcRelSchedulesCostItemsT IfcRelSchedulesCostItems;
		typedef IfcRelSequenceT IfcRelSequence;
		typedef IfcRelServicesBuildingsT IfcRelServicesBuildings;
		typedef IfcRelSpaceBoundaryT IfcRelSpaceBoundary;
		typedef IfcRelVoidsElementT IfcRelVoidsElement;
		typedef IfcRepresentationT IfcRepresentation;
		typedef IfcRepresentationContextT IfcRepresentationContext;
		typedef IfcRepresentationItemT IfcRepresentationItem;
		typedef IfcRepresentationMapT IfcRepresentationMap;
		typedef IfcResourceT IfcResource;
		typedef IfcResourceConsumptionEnumT IfcResourceConsumptionEnum;
		typedef IfcRevolvedAreaSolidT IfcRevolvedAreaSolid;
		typedef IfcRibPlateDirectionEnumT IfcRibPlateDirectionEnum;
		typedef IfcRibPlateProfilePropertiesT IfcRibPlateProfileProperties;
		typedef IfcRightCircularConeT IfcRightCircularCone;
		typedef IfcRightCircularCylinderT IfcRightCircularCylinder;
		typedef IfcRoleEnumT IfcRoleEnum;
		typedef IfcRoofT IfcRoof;
		typedef IfcRoofTypeEnumT IfcRoofTypeEnum;
		typedef IfcRootT IfcRoot;
		typedef IfcRotationalFrequencyMeasureT IfcRotationalFrequencyMeasure;
		typedef IfcRotationalMassMeasureT IfcRotationalMassMeasure;
		typedef IfcRotationalStiffnessMeasureT IfcRotationalStiffnessMeasure;
		typedef IfcRoundedEdgeFeatureT IfcRoundedEdgeFeature;
		typedef IfcRoundedRectangleProfileDefT IfcRoundedRectangleProfileDef;
		typedef IfcSanitaryTerminalTypeT IfcSanitaryTerminalType;
		typedef IfcSanitaryTerminalTypeEnumT IfcSanitaryTerminalTypeEnum;
		typedef IfcScheduleTimeControlT IfcScheduleTimeControl;
		typedef IfcSecondInMinuteT IfcSecondInMinute;
		typedef IfcSectionalAreaIntegralMeasureT IfcSectionalAreaIntegralMeasure;
		typedef IfcSectionedSpineT IfcSectionedSpine;
		typedef IfcSectionModulusMeasureT IfcSectionModulusMeasure;
		typedef IfcSectionPropertiesT IfcSectionProperties;
		typedef IfcSectionReinforcementPropertiesT IfcSectionReinforcementProperties;
		typedef IfcSectionTypeEnumT IfcSectionTypeEnum;
		typedef IfcSensorTypeT IfcSensorType;
		typedef IfcSensorTypeEnumT IfcSensorTypeEnum;
		typedef IfcSequenceEnumT IfcSequenceEnum;
		typedef IfcServiceLifeT IfcServiceLife;
		typedef IfcServiceLifeFactorT IfcServiceLifeFactor;
		typedef IfcServiceLifeFactorTypeEnumT IfcServiceLifeFactorTypeEnum;
		typedef IfcServiceLifeTypeEnumT IfcServiceLifeTypeEnum;
		typedef IfcShapeAspectT IfcShapeAspect;
		typedef IfcShapeModelT IfcShapeModel;
		typedef IfcShapeRepresentationT IfcShapeRepresentation;
		typedef IfcShearModulusMeasureT IfcShearModulusMeasure;
		typedef IfcShellT IfcShell;
		typedef IfcShellBasedSurfaceModelT IfcShellBasedSurfaceModel;
		typedef IfcSimplePropertyT IfcSimpleProperty;
		typedef IfcSimpleValueT IfcSimpleValue;
		typedef IfcSIPrefixT IfcSIPrefix;
		typedef IfcSiteT IfcSite;
		typedef IfcSIUnitT IfcSIUnit;
		typedef IfcSIUnitNameT IfcSIUnitName;
		typedef IfcSizeSelectT IfcSizeSelect;
		typedef IfcSlabT IfcSlab;
		typedef IfcSlabTypeT IfcSlabType;
		typedef IfcSlabTypeEnumT IfcSlabTypeEnum;
		typedef IfcSlippageConnectionConditionT IfcSlippageConnectionCondition;
		typedef IfcSolidAngleMeasureT IfcSolidAngleMeasure;
		typedef IfcSolidModelT IfcSolidModel;
		typedef IfcSoundPowerMeasureT IfcSoundPowerMeasure;
		typedef IfcSoundPressureMeasureT IfcSoundPressureMeasure;
		typedef IfcSoundPropertiesT IfcSoundProperties;
		typedef IfcSoundScaleEnumT IfcSoundScaleEnum;
		typedef IfcSoundValueT IfcSoundValue;
		typedef IfcSpaceT IfcSpace;
		typedef IfcSpaceHeaterTypeT IfcSpaceHeaterType;
		typedef IfcSpaceHeaterTypeEnumT IfcSpaceHeaterTypeEnum;
		typedef IfcSpaceProgramT IfcSpaceProgram;
		typedef IfcSpaceThermalLoadPropertiesT IfcSpaceThermalLoadProperties;
		typedef IfcSpaceTypeT IfcSpaceType;
		typedef IfcSpaceTypeEnumT IfcSpaceTypeEnum;
		typedef IfcSpatialStructureElementT IfcSpatialStructureElement;
		typedef IfcSpatialStructureElementTypeT IfcSpatialStructureElementType;
		typedef IfcSpecificHeatCapacityMeasureT IfcSpecificHeatCapacityMeasure;
		typedef IfcSpecularExponentT IfcSpecularExponent;
		typedef IfcSpecularHighlightSelectT IfcSpecularHighlightSelect;
		typedef IfcSpecularRoughnessT IfcSpecularRoughness;
		typedef IfcSphereT IfcSphere;
		typedef IfcStackTerminalTypeT IfcStackTerminalType;
		typedef IfcStackTerminalTypeEnumT IfcStackTerminalTypeEnum;
		typedef IfcStairT IfcStair;
		typedef IfcStairFlightT IfcStairFlight;
		typedef IfcStairFlightTypeT IfcStairFlightType;
		typedef IfcStairFlightTypeEnumT IfcStairFlightTypeEnum;
		typedef IfcStairTypeEnumT IfcStairTypeEnum;
		typedef IfcStateEnumT IfcStateEnum;
		typedef IfcStructuralActionT IfcStructuralAction;
		typedef IfcStructuralActivityT IfcStructuralActivity;
		typedef IfcStructuralActivityAssignmentSelectT IfcStructuralActivityAssignmentSelect;
		typedef IfcStructuralAnalysisModelT IfcStructuralAnalysisModel;
		typedef IfcStructuralConnectionT IfcStructuralConnection;
		typedef IfcStructuralConnectionConditionT IfcStructuralConnectionCondition;
		typedef IfcStructuralCurveConnectionT IfcStructuralCurveConnection;
		typedef IfcStructuralCurveMemberT IfcStructuralCurveMember;
		typedef IfcStructuralCurveMemberVaryingT IfcStructuralCurveMemberVarying;
		typedef IfcStructuralCurveTypeEnumT IfcStructuralCurveTypeEnum;
		typedef IfcStructuralItemT IfcStructuralItem;
		typedef IfcStructuralLinearActionT IfcStructuralLinearAction;
		typedef IfcStructuralLinearActionVaryingT IfcStructuralLinearActionVarying;
		typedef IfcStructuralLoadT IfcStructuralLoad;
		typedef IfcStructuralLoadGroupT IfcStructuralLoadGroup;
		typedef IfcStructuralLoadLinearForceT IfcStructuralLoadLinearForce;
		typedef IfcStructuralLoadPlanarForceT IfcStructuralLoadPlanarForce;
		typedef IfcStructuralLoadSingleDisplacementT IfcStructuralLoadSingleDisplacement;
		typedef IfcStructuralLoadSingleDisplacementDistortionT IfcStructuralLoadSingleDisplacementDistortion;
		typedef IfcStructuralLoadSingleForceT IfcStructuralLoadSingleForce;
		typedef IfcStructuralLoadSingleForceWarpingT IfcStructuralLoadSingleForceWarping;
		typedef IfcStructuralLoadStaticT IfcStructuralLoadStatic;
		typedef IfcStructuralLoadTemperatureT IfcStructuralLoadTemperature;
		typedef IfcStructuralMemberT IfcStructuralMember;
		typedef IfcStructuralPlanarActionT IfcStructuralPlanarAction;
		typedef IfcStructuralPlanarActionVaryingT IfcStructuralPlanarActionVarying;
		typedef IfcStructuralPointActionT IfcStructuralPointAction;
		typedef IfcStructuralPointConnectionT IfcStructuralPointConnection;
		typedef IfcStructuralPointReactionT IfcStructuralPointReaction;
		typedef IfcStructuralProfilePropertiesT IfcStructuralProfileProperties;
		typedef IfcStructuralReactionT IfcStructuralReaction;
		typedef IfcStructuralResultGroupT IfcStructuralResultGroup;
		typedef IfcStructuralSteelProfilePropertiesT IfcStructuralSteelProfileProperties;
		typedef IfcStructuralSurfaceConnectionT IfcStructuralSurfaceConnection;
		typedef IfcStructuralSurfaceMemberT IfcStructuralSurfaceMember;
		typedef IfcStructuralSurfaceMemberVaryingT IfcStructuralSurfaceMemberVarying;
		typedef IfcStructuralSurfaceTypeEnumT IfcStructuralSurfaceTypeEnum;
		typedef IfcStructuredDimensionCalloutT IfcStructuredDimensionCallout;
		typedef IfcStyledItemT IfcStyledItem;
		typedef IfcStyledRepresentationT IfcStyledRepresentation;
		typedef IfcStyleModelT IfcStyleModel;
		typedef IfcSubContractResourceT IfcSubContractResource;
		typedef IfcSubedgeT IfcSubedge;
		typedef IfcSurfaceT IfcSurface;
		typedef IfcSurfaceCurveSweptAreaSolidT IfcSurfaceCurveSweptAreaSolid;
		typedef IfcSurfaceOfLinearExtrusionT IfcSurfaceOfLinearExtrusion;
		typedef IfcSurfaceOfRevolutionT IfcSurfaceOfRevolution;
		typedef IfcSurfaceOrFaceSurfaceT IfcSurfaceOrFaceSurface;
		typedef IfcSurfaceSideT IfcSurfaceSide;
		typedef IfcSurfaceStyleT IfcSurfaceStyle;
		typedef IfcSurfaceStyleElementSelectT IfcSurfaceStyleElementSelect;
		typedef IfcSurfaceStyleLightingT IfcSurfaceStyleLighting;
		typedef IfcSurfaceStyleRefractionT IfcSurfaceStyleRefraction;
		typedef IfcSurfaceStyleRenderingT IfcSurfaceStyleRendering;
		typedef IfcSurfaceStyleShadingT IfcSurfaceStyleShading;
		typedef IfcSurfaceStyleWithTexturesT IfcSurfaceStyleWithTextures;
		typedef IfcSurfaceTextureT IfcSurfaceTexture;
		typedef IfcSurfaceTextureEnumT IfcSurfaceTextureEnum;
		typedef IfcSweptAreaSolidT IfcSweptAreaSolid;
		typedef IfcSweptDiskSolidT IfcSweptDiskSolid;
		typedef IfcSweptSurfaceT IfcSweptSurface;
		typedef IfcSwitchingDeviceTypeT IfcSwitchingDeviceType;
		typedef IfcSwitchingDeviceTypeEnumT IfcSwitchingDeviceTypeEnum;
		typedef IfcSymbolStyleT IfcSymbolStyle;
		typedef IfcSymbolStyleSelectT IfcSymbolStyleSelect;
		typedef IfcSystemT IfcSystem;
		typedef IfcSystemFurnitureElementTypeT IfcSystemFurnitureElementType;
		typedef IfcTableT IfcTable;
		typedef IfcTableRowT IfcTableRow;
		typedef IfcTankTypeT IfcTankType;
		typedef IfcTankTypeEnumT IfcTankTypeEnum;
		typedef IfcTaskT IfcTask;
		typedef IfcTelecomAddressT IfcTelecomAddress;
		typedef IfcTemperatureGradientMeasureT IfcTemperatureGradientMeasure;
		typedef IfcTendonT IfcTendon;
		typedef IfcTendonAnchorT IfcTendonAnchor;
		typedef IfcTendonTypeEnumT IfcTendonTypeEnum;
		typedef IfcTerminatorSymbolT IfcTerminatorSymbol;
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
		typedef IfcThermalAdmittanceMeasureT IfcThermalAdmittanceMeasure;
		typedef IfcThermalConductivityMeasureT IfcThermalConductivityMeasure;
		typedef IfcThermalExpansionCoefficientMeasureT IfcThermalExpansionCoefficientMeasure;
		typedef IfcThermalLoadSourceEnumT IfcThermalLoadSourceEnum;
		typedef IfcThermalLoadTypeEnumT IfcThermalLoadTypeEnum;
		typedef IfcThermalMaterialPropertiesT IfcThermalMaterialProperties;
		typedef IfcThermalResistanceMeasureT IfcThermalResistanceMeasure;
		typedef IfcThermalTransmittanceMeasureT IfcThermalTransmittanceMeasure;
		typedef IfcThermodynamicTemperatureMeasureT IfcThermodynamicTemperatureMeasure;
		typedef IfcTimeMeasureT IfcTimeMeasure;
		typedef IfcTimeSeriesT IfcTimeSeries;
		typedef IfcTimeSeriesDataTypeEnumT IfcTimeSeriesDataTypeEnum;
		typedef IfcTimeSeriesReferenceRelationshipT IfcTimeSeriesReferenceRelationship;
		typedef IfcTimeSeriesScheduleT IfcTimeSeriesSchedule;
		typedef IfcTimeSeriesScheduleTypeEnumT IfcTimeSeriesScheduleTypeEnum;
		typedef IfcTimeSeriesValueT IfcTimeSeriesValue;
		typedef IfcTimeStampT IfcTimeStamp;
		typedef IfcTopologicalRepresentationItemT IfcTopologicalRepresentationItem;
		typedef IfcTopologyRepresentationT IfcTopologyRepresentation;
		typedef IfcTorqueMeasureT IfcTorqueMeasure;
		typedef IfcTransformerTypeT IfcTransformerType;
		typedef IfcTransformerTypeEnumT IfcTransformerTypeEnum;
		typedef IfcTransitionCodeT IfcTransitionCode;
		typedef IfcTransportElementT IfcTransportElement;
		typedef IfcTransportElementTypeT IfcTransportElementType;
		typedef IfcTransportElementTypeEnumT IfcTransportElementTypeEnum;
		typedef IfcTrapeziumProfileDefT IfcTrapeziumProfileDef;
		typedef IfcTrimmedCurveT IfcTrimmedCurve;
		typedef IfcTrimmingPreferenceT IfcTrimmingPreference;
		typedef IfcTrimmingSelectT IfcTrimmingSelect;
		typedef IfcTShapeProfileDefT IfcTShapeProfileDef;
		typedef IfcTubeBundleTypeT IfcTubeBundleType;
		typedef IfcTubeBundleTypeEnumT IfcTubeBundleTypeEnum;
		typedef IfcTwoDirectionRepeatFactorT IfcTwoDirectionRepeatFactor;
		typedef IfcTypeObjectT IfcTypeObject;
		typedef IfcTypeProductT IfcTypeProduct;
		typedef IfcUnitT IfcUnit;
		typedef IfcUnitaryEquipmentTypeT IfcUnitaryEquipmentType;
		typedef IfcUnitaryEquipmentTypeEnumT IfcUnitaryEquipmentTypeEnum;
		typedef IfcUnitAssignmentT IfcUnitAssignment;
		typedef IfcUnitEnumT IfcUnitEnum;
		typedef IfcUShapeProfileDefT IfcUShapeProfileDef;
		typedef IfcValueT IfcValue;
		typedef IfcValveTypeT IfcValveType;
		typedef IfcValveTypeEnumT IfcValveTypeEnum;
		typedef IfcVaporPermeabilityMeasureT IfcVaporPermeabilityMeasure;
		typedef IfcVectorT IfcVector;
		typedef IfcVectorOrDirectionT IfcVectorOrDirection;
		typedef IfcVertexT IfcVertex;
		typedef IfcVertexBasedTextureMapT IfcVertexBasedTextureMap;
		typedef IfcVertexLoopT IfcVertexLoop;
		typedef IfcVertexPointT IfcVertexPoint;
		typedef IfcVibrationIsolatorTypeT IfcVibrationIsolatorType;
		typedef IfcVibrationIsolatorTypeEnumT IfcVibrationIsolatorTypeEnum;
		typedef IfcVirtualElementT IfcVirtualElement;
		typedef IfcVirtualGridIntersectionT IfcVirtualGridIntersection;
		typedef IfcVolumeMeasureT IfcVolumeMeasure;
		typedef IfcVolumetricFlowRateMeasureT IfcVolumetricFlowRateMeasure;
		typedef IfcWallT IfcWall;
		typedef IfcWallStandardCaseT IfcWallStandardCase;
		typedef IfcWallTypeT IfcWallType;
		typedef IfcWallTypeEnumT IfcWallTypeEnum;
		typedef IfcWarpingConstantMeasureT IfcWarpingConstantMeasure;
		typedef IfcWarpingMomentMeasureT IfcWarpingMomentMeasure;
		typedef IfcWasteTerminalTypeT IfcWasteTerminalType;
		typedef IfcWasteTerminalTypeEnumT IfcWasteTerminalTypeEnum;
		typedef IfcWaterPropertiesT IfcWaterProperties;
		typedef IfcWindowT IfcWindow;
		typedef IfcWindowLiningPropertiesT IfcWindowLiningProperties;
		typedef IfcWindowPanelOperationEnumT IfcWindowPanelOperationEnum;
		typedef IfcWindowPanelPositionEnumT IfcWindowPanelPositionEnum;
		typedef IfcWindowPanelPropertiesT IfcWindowPanelProperties;
		typedef IfcWindowStyleT IfcWindowStyle;
		typedef IfcWindowStyleConstructionEnumT IfcWindowStyleConstructionEnum;
		typedef IfcWindowStyleOperationEnumT IfcWindowStyleOperationEnum;
		typedef IfcWorkControlT IfcWorkControl;
		typedef IfcWorkControlTypeEnumT IfcWorkControlTypeEnum;
		typedef IfcWorkPlanT IfcWorkPlan;
		typedef IfcWorkScheduleT IfcWorkSchedule;
		typedef IfcYearNumberT IfcYearNumber;
		typedef IfcZoneT IfcZone;
		typedef IfcZShapeProfileDefT IfcZShapeProfileDef;
	};
}