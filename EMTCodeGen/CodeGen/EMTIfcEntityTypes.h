#pragma once

namespace emt
{
	template <
		typename IfcAbsorbedDoseMeasureType,
		typename IfcAccelerationMeasureType,
		typename IfcActionRequestType,
		typename IfcActionSourceTypeEnumType,
		typename IfcActionTypeEnumType,
		typename IfcActorType,
		typename IfcActorRoleType,
		typename IfcActorSelectType,
		typename IfcActuatorTypeType,
		typename IfcActuatorTypeEnumType,
		typename IfcAddressType,
		typename IfcAddressTypeEnumType,
		typename IfcAheadOrBehindType,
		typename IfcAirTerminalBoxTypeType,
		typename IfcAirTerminalBoxTypeEnumType,
		typename IfcAirTerminalTypeType,
		typename IfcAirTerminalTypeEnumType,
		typename IfcAirToAirHeatRecoveryTypeType,
		typename IfcAirToAirHeatRecoveryTypeEnumType,
		typename IfcAlarmTypeType,
		typename IfcAlarmTypeEnumType,
		typename IfcAmountOfSubstanceMeasureType,
		typename IfcAnalysisModelTypeEnumType,
		typename IfcAnalysisTheoryTypeEnumType,
		typename IfcAngularDimensionType,
		typename IfcAngularVelocityMeasureType,
		typename IfcAnnotationType,
		typename IfcAnnotationCurveOccurrenceType,
		typename IfcAnnotationFillAreaType,
		typename IfcAnnotationFillAreaOccurrenceType,
		typename IfcAnnotationOccurrenceType,
		typename IfcAnnotationSurfaceType,
		typename IfcAnnotationSurfaceOccurrenceType,
		typename IfcAnnotationSymbolOccurrenceType,
		typename IfcAnnotationTextOccurrenceType,
		typename IfcApplicationType,
		typename IfcAppliedValueType,
		typename IfcAppliedValueRelationshipType,
		typename IfcAppliedValueSelectType,
		typename IfcApprovalType,
		typename IfcApprovalActorRelationshipType,
		typename IfcApprovalPropertyRelationshipType,
		typename IfcApprovalRelationshipType,
		typename IfcArbitraryClosedProfileDefType,
		typename IfcArbitraryOpenProfileDefType,
		typename IfcArbitraryProfileDefWithVoidsType,
		typename IfcAreaMeasureType,
		typename IfcArithmeticOperatorEnumType,
		typename IfcAssemblyPlaceEnumType,
		typename IfcAssetType,
		typename IfcAsymmetricIShapeProfileDefType,
		typename IfcAxis1PlacementType,
		typename IfcAxis2PlacementType,
		typename IfcAxis2Placement2DType,
		typename IfcAxis2Placement3DType,
		typename IfcBeamType,
		typename IfcBeamTypeType,
		typename IfcBeamTypeEnumType,
		typename IfcBenchmarkEnumType,
		typename IfcBezierCurveType,
		typename IfcBlobTextureType,
		typename IfcBlockType,
		typename IfcBoilerTypeType,
		typename IfcBoilerTypeEnumType,
		typename IfcBooleanType,
		typename IfcBooleanClippingResultType,
		typename IfcBooleanOperandType,
		typename IfcBooleanOperatorType,
		typename IfcBooleanResultType,
		typename IfcBoundaryConditionType,
		typename IfcBoundaryEdgeConditionType,
		typename IfcBoundaryFaceConditionType,
		typename IfcBoundaryNodeConditionType,
		typename IfcBoundaryNodeConditionWarpingType,
		typename IfcBoundedCurveType,
		typename IfcBoundedSurfaceType,
		typename IfcBoundingBoxType,
		typename IfcBoxAlignmentType,
		typename IfcBoxedHalfSpaceType,
		typename IfcBSplineCurveType,
		typename IfcBSplineCurveFormType,
		typename IfcBuildingType,
		typename IfcBuildingElementType,
		typename IfcBuildingElementComponentType,
		typename IfcBuildingElementPartType,
		typename IfcBuildingElementProxyType,
		typename IfcBuildingElementProxyTypeType,
		typename IfcBuildingElementProxyTypeEnumType,
		typename IfcBuildingElementTypeType,
		typename IfcBuildingStoreyType,
		typename IfcCableCarrierFittingTypeType,
		typename IfcCableCarrierFittingTypeEnumType,
		typename IfcCableCarrierSegmentTypeType,
		typename IfcCableCarrierSegmentTypeEnumType,
		typename IfcCableSegmentTypeType,
		typename IfcCableSegmentTypeEnumType,
		typename IfcCalendarDateType,
		typename IfcCartesianPointType,
		typename IfcCartesianTransformationOperatorType,
		typename IfcCartesianTransformationOperator2DType,
		typename IfcCartesianTransformationOperator2DnonUniformType,
		typename IfcCartesianTransformationOperator3DType,
		typename IfcCartesianTransformationOperator3DnonUniformType,
		typename IfcCenterLineProfileDefType,
		typename IfcChamferEdgeFeatureType,
		typename IfcChangeActionEnumType,
		typename IfcCharacterStyleSelectType,
		typename IfcChillerTypeType,
		typename IfcChillerTypeEnumType,
		typename IfcCircleType,
		typename IfcCircleHollowProfileDefType,
		typename IfcCircleProfileDefType,
		typename IfcClassificationType,
		typename IfcClassificationItemType,
		typename IfcClassificationItemRelationshipType,
		typename IfcClassificationNotationType,
		typename IfcClassificationNotationFacetType,
		typename IfcClassificationNotationSelectType,
		typename IfcClassificationReferenceType,
		typename IfcClosedShellType,
		typename IfcCoilTypeType,
		typename IfcCoilTypeEnumType,
		typename IfcColourType,
		typename IfcColourOrFactorType,
		typename IfcColourRgbType,
		typename IfcColourSpecificationType,
		typename IfcColumnType,
		typename IfcColumnTypeType,
		typename IfcColumnTypeEnumType,
		typename IfcComplexNumberType,
		typename IfcComplexPropertyType,
		typename IfcCompositeCurveType,
		typename IfcCompositeCurveSegmentType,
		typename IfcCompositeProfileDefType,
		typename IfcCompoundPlaneAngleMeasureType,
		typename IfcCompressorTypeType,
		typename IfcCompressorTypeEnumType,
		typename IfcCondenserTypeType,
		typename IfcCondenserTypeEnumType,
		typename IfcConditionType,
		typename IfcConditionCriterionType,
		typename IfcConditionCriterionSelectType,
		typename IfcConicType,
		typename IfcConnectedFaceSetType,
		typename IfcConnectionCurveGeometryType,
		typename IfcConnectionGeometryType,
		typename IfcConnectionPointEccentricityType,
		typename IfcConnectionPointGeometryType,
		typename IfcConnectionPortGeometryType,
		typename IfcConnectionSurfaceGeometryType,
		typename IfcConnectionTypeEnumType,
		typename IfcConstraintType,
		typename IfcConstraintAggregationRelationshipType,
		typename IfcConstraintClassificationRelationshipType,
		typename IfcConstraintEnumType,
		typename IfcConstraintRelationshipType,
		typename IfcConstructionEquipmentResourceType,
		typename IfcConstructionMaterialResourceType,
		typename IfcConstructionProductResourceType,
		typename IfcConstructionResourceType,
		typename IfcContextDependentMeasureType,
		typename IfcContextDependentUnitType,
		typename IfcControlType,
		typename IfcControllerTypeType,
		typename IfcControllerTypeEnumType,
		typename IfcConversionBasedUnitType,
		typename IfcCooledBeamTypeType,
		typename IfcCooledBeamTypeEnumType,
		typename IfcCoolingTowerTypeType,
		typename IfcCoolingTowerTypeEnumType,
		typename IfcCoordinatedUniversalTimeOffsetType,
		typename IfcCostItemType,
		typename IfcCostScheduleType,
		typename IfcCostScheduleTypeEnumType,
		typename IfcCostValueType,
		typename IfcCountMeasureType,
		typename IfcCoveringType,
		typename IfcCoveringTypeType,
		typename IfcCoveringTypeEnumType,
		typename IfcCraneRailAShapeProfileDefType,
		typename IfcCraneRailFShapeProfileDefType,
		typename IfcCrewResourceType,
		typename IfcCsgPrimitive3DType,
		typename IfcCsgSelectType,
		typename IfcCsgSolidType,
		typename IfcCShapeProfileDefType,
		typename IfcCurrencyEnumType,
		typename IfcCurrencyRelationshipType,
		typename IfcCurtainWallType,
		typename IfcCurtainWallTypeType,
		typename IfcCurtainWallTypeEnumType,
		typename IfcCurvatureMeasureType,
		typename IfcCurveType,
		typename IfcCurveBoundedPlaneType,
		typename IfcCurveFontOrScaledCurveFontSelectType,
		typename IfcCurveOrEdgeCurveType,
		typename IfcCurveStyleType,
		typename IfcCurveStyleFontType,
		typename IfcCurveStyleFontAndScalingType,
		typename IfcCurveStyleFontPatternType,
		typename IfcCurveStyleFontSelectType,
		typename IfcDamperTypeType,
		typename IfcDamperTypeEnumType,
		typename IfcDataOriginEnumType,
		typename IfcDateAndTimeType,
		typename IfcDateTimeSelectType,
		typename IfcDayInMonthNumberType,
		typename IfcDaylightSavingHourType,
		typename IfcDefinedSymbolType,
		typename IfcDefinedSymbolSelectType,
		typename IfcDerivedMeasureValueType,
		typename IfcDerivedProfileDefType,
		typename IfcDerivedUnitType,
		typename IfcDerivedUnitElementType,
		typename IfcDerivedUnitEnumType,
		typename IfcDescriptiveMeasureType,
		typename IfcDiameterDimensionType,
		typename IfcDimensionalExponentsType,
		typename IfcDimensionCalloutRelationshipType,
		typename IfcDimensionCountType,
		typename IfcDimensionCurveType,
		typename IfcDimensionCurveDirectedCalloutType,
		typename IfcDimensionCurveTerminatorType,
		typename IfcDimensionExtentUsageType,
		typename IfcDimensionPairType,
		typename IfcDirectionType,
		typename IfcDirectionSenseEnumType,
		typename IfcDiscreteAccessoryType,
		typename IfcDiscreteAccessoryTypeType,
		typename IfcDistributionChamberElementType,
		typename IfcDistributionChamberElementTypeType,
		typename IfcDistributionChamberElementTypeEnumType,
		typename IfcDistributionControlElementType,
		typename IfcDistributionControlElementTypeType,
		typename IfcDistributionElementType,
		typename IfcDistributionElementTypeType,
		typename IfcDistributionFlowElementType,
		typename IfcDistributionFlowElementTypeType,
		typename IfcDistributionPortType,
		typename IfcDocumentConfidentialityEnumType,
		typename IfcDocumentElectronicFormatType,
		typename IfcDocumentInformationType,
		typename IfcDocumentInformationRelationshipType,
		typename IfcDocumentReferenceType,
		typename IfcDocumentSelectType,
		typename IfcDocumentStatusEnumType,
		typename IfcDoorType,
		typename IfcDoorLiningPropertiesType,
		typename IfcDoorPanelOperationEnumType,
		typename IfcDoorPanelPositionEnumType,
		typename IfcDoorPanelPropertiesType,
		typename IfcDoorStyleType,
		typename IfcDoorStyleConstructionEnumType,
		typename IfcDoorStyleOperationEnumType,
		typename IfcDoseEquivalentMeasureType,
		typename IfcDraughtingCalloutType,
		typename IfcDraughtingCalloutElementType,
		typename IfcDraughtingCalloutRelationshipType,
		typename IfcDraughtingPreDefinedColourType,
		typename IfcDraughtingPreDefinedCurveFontType,
		typename IfcDraughtingPreDefinedTextFontType,
		typename IfcDuctFittingTypeType,
		typename IfcDuctFittingTypeEnumType,
		typename IfcDuctSegmentTypeType,
		typename IfcDuctSegmentTypeEnumType,
		typename IfcDuctSilencerTypeType,
		typename IfcDuctSilencerTypeEnumType,
		typename IfcDynamicViscosityMeasureType,
		typename IfcEdgeType,
		typename IfcEdgeCurveType,
		typename IfcEdgeFeatureType,
		typename IfcEdgeLoopType,
		typename IfcElectricalBasePropertiesType,
		typename IfcElectricalCircuitType,
		typename IfcElectricalElementType,
		typename IfcElectricApplianceTypeType,
		typename IfcElectricApplianceTypeEnumType,
		typename IfcElectricCapacitanceMeasureType,
		typename IfcElectricChargeMeasureType,
		typename IfcElectricConductanceMeasureType,
		typename IfcElectricCurrentEnumType,
		typename IfcElectricCurrentMeasureType,
		typename IfcElectricDistributionPointType,
		typename IfcElectricDistributionPointFunctionEnumType,
		typename IfcElectricFlowStorageDeviceTypeType,
		typename IfcElectricFlowStorageDeviceTypeEnumType,
		typename IfcElectricGeneratorTypeType,
		typename IfcElectricGeneratorTypeEnumType,
		typename IfcElectricHeaterTypeType,
		typename IfcElectricHeaterTypeEnumType,
		typename IfcElectricMotorTypeType,
		typename IfcElectricMotorTypeEnumType,
		typename IfcElectricResistanceMeasureType,
		typename IfcElectricTimeControlTypeType,
		typename IfcElectricTimeControlTypeEnumType,
		typename IfcElectricVoltageMeasureType,
		typename IfcElementType,
		typename IfcElementarySurfaceType,
		typename IfcElementAssemblyType,
		typename IfcElementAssemblyTypeEnumType,
		typename IfcElementComponentType,
		typename IfcElementComponentTypeType,
		typename IfcElementCompositionEnumType,
		typename IfcElementQuantityType,
		typename IfcElementTypeType,
		typename IfcEllipseType,
		typename IfcEllipseProfileDefType,
		typename IfcEnergyConversionDeviceType,
		typename IfcEnergyConversionDeviceTypeType,
		typename IfcEnergyMeasureType,
		typename IfcEnergyPropertiesType,
		typename IfcEnergySequenceEnumType,
		typename IfcEnvironmentalImpactCategoryEnumType,
		typename IfcEnvironmentalImpactValueType,
		typename IfcEquipmentElementType,
		typename IfcEquipmentStandardType,
		typename IfcEvaporativeCoolerTypeType,
		typename IfcEvaporativeCoolerTypeEnumType,
		typename IfcEvaporatorTypeType,
		typename IfcEvaporatorTypeEnumType,
		typename IfcExtendedMaterialPropertiesType,
		typename IfcExternallyDefinedHatchStyleType,
		typename IfcExternallyDefinedSurfaceStyleType,
		typename IfcExternallyDefinedSymbolType,
		typename IfcExternallyDefinedTextFontType,
		typename IfcExternalReferenceType,
		typename IfcExtrudedAreaSolidType,
		typename IfcFaceType,
		typename IfcFaceBasedSurfaceModelType,
		typename IfcFaceBoundType,
		typename IfcFaceOuterBoundType,
		typename IfcFaceSurfaceType,
		typename IfcFacetedBrepType,
		typename IfcFacetedBrepWithVoidsType,
		typename IfcFailureConnectionConditionType,
		typename IfcFanTypeType,
		typename IfcFanTypeEnumType,
		typename IfcFastenerType,
		typename IfcFastenerTypeType,
		typename IfcFeatureElementType,
		typename IfcFeatureElementAdditionType,
		typename IfcFeatureElementSubtractionType,
		typename IfcFillAreaStyleType,
		typename IfcFillAreaStyleHatchingType,
		typename IfcFillAreaStyleTilesType,
		typename IfcFillAreaStyleTileShapeSelectType,
		typename IfcFillAreaStyleTileSymbolWithStyleType,
		typename IfcFillStyleSelectType,
		typename IfcFilterTypeType,
		typename IfcFilterTypeEnumType,
		typename IfcFireSuppressionTerminalTypeType,
		typename IfcFireSuppressionTerminalTypeEnumType,
		typename IfcFlowControllerType,
		typename IfcFlowControllerTypeType,
		typename IfcFlowDirectionEnumType,
		typename IfcFlowFittingType,
		typename IfcFlowFittingTypeType,
		typename IfcFlowInstrumentTypeType,
		typename IfcFlowInstrumentTypeEnumType,
		typename IfcFlowMeterTypeType,
		typename IfcFlowMeterTypeEnumType,
		typename IfcFlowMovingDeviceType,
		typename IfcFlowMovingDeviceTypeType,
		typename IfcFlowSegmentType,
		typename IfcFlowSegmentTypeType,
		typename IfcFlowStorageDeviceType,
		typename IfcFlowStorageDeviceTypeType,
		typename IfcFlowTerminalType,
		typename IfcFlowTerminalTypeType,
		typename IfcFlowTreatmentDeviceType,
		typename IfcFlowTreatmentDeviceTypeType,
		typename IfcFluidFlowPropertiesType,
		typename IfcFontStyleType,
		typename IfcFontVariantType,
		typename IfcFontWeightType,
		typename IfcFootingType,
		typename IfcFootingTypeEnumType,
		typename IfcForceMeasureType,
		typename IfcFrequencyMeasureType,
		typename IfcFuelPropertiesType,
		typename IfcFurnishingElementType,
		typename IfcFurnishingElementTypeType,
		typename IfcFurnitureStandardType,
		typename IfcFurnitureTypeType,
		typename IfcGasTerminalTypeType,
		typename IfcGasTerminalTypeEnumType,
		typename IfcGeneralMaterialPropertiesType,
		typename IfcGeneralProfilePropertiesType,
		typename IfcGeometricCurveSetType,
		typename IfcGeometricProjectionEnumType,
		typename IfcGeometricRepresentationContextType,
		typename IfcGeometricRepresentationItemType,
		typename IfcGeometricRepresentationSubContextType,
		typename IfcGeometricSetType,
		typename IfcGeometricSetSelectType,
		typename IfcGloballyUniqueIdType,
		typename IfcGlobalOrLocalEnumType,
		typename IfcGridType,
		typename IfcGridAxisType,
		typename IfcGridPlacementType,
		typename IfcGroupType,
		typename IfcHalfSpaceSolidType,
		typename IfcHatchLineDistanceSelectType,
		typename IfcHeatExchangerTypeType,
		typename IfcHeatExchangerTypeEnumType,
		typename IfcHeatFluxDensityMeasureType,
		typename IfcHeatingValueMeasureType,
		typename IfcHourInDayType,
		typename IfcHumidifierTypeType,
		typename IfcHumidifierTypeEnumType,
		typename IfcHygroscopicMaterialPropertiesType,
		typename IfcIdentifierType,
		typename IfcIlluminanceMeasureType,
		typename IfcImageTextureType,
		typename IfcInductanceMeasureType,
		typename IfcIntegerType,
		typename IfcIntegerCountRateMeasureType,
		typename IfcInternalOrExternalEnumType,
		typename IfcInventoryType,
		typename IfcInventoryTypeEnumType,
		typename IfcIonConcentrationMeasureType,
		typename IfcIrregularTimeSeriesType,
		typename IfcIrregularTimeSeriesValueType,
		typename IfcIShapeProfileDefType,
		typename IfcIsothermalMoistureCapacityMeasureType,
		typename IfcJunctionBoxTypeType,
		typename IfcJunctionBoxTypeEnumType,
		typename IfcKinematicViscosityMeasureType,
		typename IfcLabelType,
		typename IfcLaborResourceType,
		typename IfcLampTypeType,
		typename IfcLampTypeEnumType,
		typename IfcLayeredItemType,
		typename IfcLayerSetDirectionEnumType,
		typename IfcLengthMeasureType,
		typename IfcLibraryInformationType,
		typename IfcLibraryReferenceType,
		typename IfcLibrarySelectType,
		typename IfcLightDistributionCurveEnumType,
		typename IfcLightDistributionDataType,
		typename IfcLightDistributionDataSourceSelectType,
		typename IfcLightEmissionSourceEnumType,
		typename IfcLightFixtureTypeType,
		typename IfcLightFixtureTypeEnumType,
		typename IfcLightIntensityDistributionType,
		typename IfcLightSourceType,
		typename IfcLightSourceAmbientType,
		typename IfcLightSourceDirectionalType,
		typename IfcLightSourceGoniometricType,
		typename IfcLightSourcePositionalType,
		typename IfcLightSourceSpotType,
		typename IfcLineType,
		typename IfcLinearDimensionType,
		typename IfcLinearForceMeasureType,
		typename IfcLinearMomentMeasureType,
		typename IfcLinearStiffnessMeasureType,
		typename IfcLinearVelocityMeasureType,
		typename IfcLoadGroupTypeEnumType,
		typename IfcLocalPlacementType,
		typename IfcLocalTimeType,
		typename IfcLogicalType,
		typename IfcLogicalOperatorEnumType,
		typename IfcLoopType,
		typename IfcLShapeProfileDefType,
		typename IfcLuminousFluxMeasureType,
		typename IfcLuminousIntensityDistributionMeasureType,
		typename IfcLuminousIntensityMeasureType,
		typename IfcMagneticFluxDensityMeasureType,
		typename IfcMagneticFluxMeasureType,
		typename IfcManifoldSolidBrepType,
		typename IfcMappedItemType,
		typename IfcMassDensityMeasureType,
		typename IfcMassFlowRateMeasureType,
		typename IfcMassMeasureType,
		typename IfcMassPerLengthMeasureType,
		typename IfcMaterialType,
		typename IfcMaterialClassificationRelationshipType,
		typename IfcMaterialDefinitionRepresentationType,
		typename IfcMaterialLayerType,
		typename IfcMaterialLayerSetType,
		typename IfcMaterialLayerSetUsageType,
		typename IfcMaterialListType,
		typename IfcMaterialPropertiesType,
		typename IfcMaterialSelectType,
		typename IfcMeasureValueType,
		typename IfcMeasureWithUnitType,
		typename IfcMechanicalConcreteMaterialPropertiesType,
		typename IfcMechanicalFastenerType,
		typename IfcMechanicalFastenerTypeType,
		typename IfcMechanicalMaterialPropertiesType,
		typename IfcMechanicalSteelMaterialPropertiesType,
		typename IfcMemberType,
		typename IfcMemberTypeType,
		typename IfcMemberTypeEnumType,
		typename IfcMetricType,
		typename IfcMetricValueSelectType,
		typename IfcMinuteInHourType,
		typename IfcModulusOfElasticityMeasureType,
		typename IfcModulusOfLinearSubgradeReactionMeasureType,
		typename IfcModulusOfRotationalSubgradeReactionMeasureType,
		typename IfcModulusOfSubgradeReactionMeasureType,
		typename IfcMoistureDiffusivityMeasureType,
		typename IfcMolecularWeightMeasureType,
		typename IfcMomentOfInertiaMeasureType,
		typename IfcMonetaryMeasureType,
		typename IfcMonetaryUnitType,
		typename IfcMonthInYearNumberType,
		typename IfcMotorConnectionTypeType,
		typename IfcMotorConnectionTypeEnumType,
		typename IfcMoveType,
		typename IfcNamedUnitType,
		typename IfcNormalisedRatioMeasureType,
		typename IfcNullStyleType,
		typename IfcNumericMeasureType,
		typename IfcObjectType,
		typename IfcObjectDefinitionType,
		typename IfcObjectiveType,
		typename IfcObjectiveEnumType,
		typename IfcObjectPlacementType,
		typename IfcObjectReferenceSelectType,
		typename IfcObjectTypeEnumType,
		typename IfcOccupantType,
		typename IfcOccupantTypeEnumType,
		typename IfcOffsetCurve2DType,
		typename IfcOffsetCurve3DType,
		typename IfcOneDirectionRepeatFactorType,
		typename IfcOpeningElementType,
		typename IfcOpenShellType,
		typename IfcOpticalMaterialPropertiesType,
		typename IfcOrderActionType,
		typename IfcOrganizationType,
		typename IfcOrganizationRelationshipType,
		typename IfcOrientationSelectType,
		typename IfcOrientedEdgeType,
		typename IfcOutletTypeType,
		typename IfcOutletTypeEnumType,
		typename IfcOwnerHistoryType,
		typename IfcParameterizedProfileDefType,
		typename IfcParameterValueType,
		typename IfcPathType,
		typename IfcPerformanceHistoryType,
		typename IfcPermeableCoveringOperationEnumType,
		typename IfcPermeableCoveringPropertiesType,
		typename IfcPermitType,
		typename IfcPersonType,
		typename IfcPersonAndOrganizationType,
		typename IfcPHMeasureType,
		typename IfcPhysicalComplexQuantityType,
		typename IfcPhysicalOrVirtualEnumType,
		typename IfcPhysicalQuantityType,
		typename IfcPhysicalSimpleQuantityType,
		typename IfcPileType,
		typename IfcPileConstructionEnumType,
		typename IfcPileTypeEnumType,
		typename IfcPipeFittingTypeType,
		typename IfcPipeFittingTypeEnumType,
		typename IfcPipeSegmentTypeType,
		typename IfcPipeSegmentTypeEnumType,
		typename IfcPixelTextureType,
		typename IfcPlacementType,
		typename IfcPlanarBoxType,
		typename IfcPlanarExtentType,
		typename IfcPlanarForceMeasureType,
		typename IfcPlaneType,
		typename IfcPlaneAngleMeasureType,
		typename IfcPlateType,
		typename IfcPlateTypeType,
		typename IfcPlateTypeEnumType,
		typename IfcPointType,
		typename IfcPointOnCurveType,
		typename IfcPointOnSurfaceType,
		typename IfcPointOrVertexPointType,
		typename IfcPolygonalBoundedHalfSpaceType,
		typename IfcPolylineType,
		typename IfcPolyLoopType,
		typename IfcPortType,
		typename IfcPositiveLengthMeasureType,
		typename IfcPositivePlaneAngleMeasureType,
		typename IfcPositiveRatioMeasureType,
		typename IfcPostalAddressType,
		typename IfcPowerMeasureType,
		typename IfcPreDefinedColourType,
		typename IfcPreDefinedCurveFontType,
		typename IfcPreDefinedDimensionSymbolType,
		typename IfcPreDefinedItemType,
		typename IfcPreDefinedPointMarkerSymbolType,
		typename IfcPreDefinedSymbolType,
		typename IfcPreDefinedTerminatorSymbolType,
		typename IfcPreDefinedTextFontType,
		typename IfcPresentableTextType,
		typename IfcPresentationLayerAssignmentType,
		typename IfcPresentationLayerWithStyleType,
		typename IfcPresentationStyleType,
		typename IfcPresentationStyleAssignmentType,
		typename IfcPresentationStyleSelectType,
		typename IfcPressureMeasureType,
		typename IfcProcedureType,
		typename IfcProcedureTypeEnumType,
		typename IfcProcessType,
		typename IfcProductType,
		typename IfcProductDefinitionShapeType,
		typename IfcProductRepresentationType,
		typename IfcProductsOfCombustionPropertiesType,
		typename IfcProfileDefType,
		typename IfcProfilePropertiesType,
		typename IfcProfileTypeEnumType,
		typename IfcProjectType,
		typename IfcProjectedOrTrueLengthEnumType,
		typename IfcProjectionCurveType,
		typename IfcProjectionElementType,
		typename IfcProjectOrderType,
		typename IfcProjectOrderRecordType,
		typename IfcProjectOrderRecordTypeEnumType,
		typename IfcProjectOrderTypeEnumType,
		typename IfcPropertyType,
		typename IfcPropertyBoundedValueType,
		typename IfcPropertyConstraintRelationshipType,
		typename IfcPropertyDefinitionType,
		typename IfcPropertyDependencyRelationshipType,
		typename IfcPropertyEnumeratedValueType,
		typename IfcPropertyEnumerationType,
		typename IfcPropertyListValueType,
		typename IfcPropertyReferenceValueType,
		typename IfcPropertySetType,
		typename IfcPropertySetDefinitionType,
		typename IfcPropertySingleValueType,
		typename IfcPropertySourceEnumType,
		typename IfcPropertyTableValueType,
		typename IfcProtectiveDeviceTypeType,
		typename IfcProtectiveDeviceTypeEnumType,
		typename IfcProxyType,
		typename IfcPumpTypeType,
		typename IfcPumpTypeEnumType,
		typename IfcQuantityAreaType,
		typename IfcQuantityCountType,
		typename IfcQuantityLengthType,
		typename IfcQuantityTimeType,
		typename IfcQuantityVolumeType,
		typename IfcQuantityWeightType,
		typename IfcRadioActivityMeasureType,
		typename IfcRadiusDimensionType,
		typename IfcRailingType,
		typename IfcRailingTypeType,
		typename IfcRailingTypeEnumType,
		typename IfcRampType,
		typename IfcRampFlightType,
		typename IfcRampFlightTypeType,
		typename IfcRampFlightTypeEnumType,
		typename IfcRampTypeEnumType,
		typename IfcRatioMeasureType,
		typename IfcRationalBezierCurveType,
		typename IfcRealType,
		typename IfcRectangleHollowProfileDefType,
		typename IfcRectangleProfileDefType,
		typename IfcRectangularPyramidType,
		typename IfcRectangularTrimmedSurfaceType,
		typename IfcReferencesValueDocumentType,
		typename IfcReflectanceMethodEnumType,
		typename IfcRegularTimeSeriesType,
		typename IfcReinforcementBarPropertiesType,
		typename IfcReinforcementDefinitionPropertiesType,
		typename IfcReinforcingBarType,
		typename IfcReinforcingBarRoleEnumType,
		typename IfcReinforcingBarSurfaceEnumType,
		typename IfcReinforcingElementType,
		typename IfcReinforcingMeshType,
		typename IfcRelAggregatesType,
		typename IfcRelAssignsType,
		typename IfcRelAssignsTasksType,
		typename IfcRelAssignsToActorType,
		typename IfcRelAssignsToControlType,
		typename IfcRelAssignsToGroupType,
		typename IfcRelAssignsToProcessType,
		typename IfcRelAssignsToProductType,
		typename IfcRelAssignsToProjectOrderType,
		typename IfcRelAssignsToResourceType,
		typename IfcRelAssociatesType,
		typename IfcRelAssociatesAppliedValueType,
		typename IfcRelAssociatesApprovalType,
		typename IfcRelAssociatesClassificationType,
		typename IfcRelAssociatesConstraintType,
		typename IfcRelAssociatesDocumentType,
		typename IfcRelAssociatesLibraryType,
		typename IfcRelAssociatesMaterialType,
		typename IfcRelAssociatesProfilePropertiesType,
		typename IfcRelationshipType,
		typename IfcRelaxationType,
		typename IfcRelConnectsType,
		typename IfcRelConnectsElementsType,
		typename IfcRelConnectsPathElementsType,
		typename IfcRelConnectsPortsType,
		typename IfcRelConnectsPortToElementType,
		typename IfcRelConnectsStructuralActivityType,
		typename IfcRelConnectsStructuralElementType,
		typename IfcRelConnectsStructuralMemberType,
		typename IfcRelConnectsWithEccentricityType,
		typename IfcRelConnectsWithRealizingElementsType,
		typename IfcRelContainedInSpatialStructureType,
		typename IfcRelCoversBldgElementsType,
		typename IfcRelCoversSpacesType,
		typename IfcRelDecomposesType,
		typename IfcRelDefinesType,
		typename IfcRelDefinesByPropertiesType,
		typename IfcRelDefinesByTypeType,
		typename IfcRelFillsElementType,
		typename IfcRelFlowControlElementsType,
		typename IfcRelInteractionRequirementsType,
		typename IfcRelNestsType,
		typename IfcRelOccupiesSpacesType,
		typename IfcRelOverridesPropertiesType,
		typename IfcRelProjectsElementType,
		typename IfcRelReferencedInSpatialStructureType,
		typename IfcRelSchedulesCostItemsType,
		typename IfcRelSequenceType,
		typename IfcRelServicesBuildingsType,
		typename IfcRelSpaceBoundaryType,
		typename IfcRelVoidsElementType,
		typename IfcRepresentationType,
		typename IfcRepresentationContextType,
		typename IfcRepresentationItemType,
		typename IfcRepresentationMapType,
		typename IfcResourceType,
		typename IfcResourceConsumptionEnumType,
		typename IfcRevolvedAreaSolidType,
		typename IfcRibPlateDirectionEnumType,
		typename IfcRibPlateProfilePropertiesType,
		typename IfcRightCircularConeType,
		typename IfcRightCircularCylinderType,
		typename IfcRoleEnumType,
		typename IfcRoofType,
		typename IfcRoofTypeEnumType,
		typename IfcRootType,
		typename IfcRotationalFrequencyMeasureType,
		typename IfcRotationalMassMeasureType,
		typename IfcRotationalStiffnessMeasureType,
		typename IfcRoundedEdgeFeatureType,
		typename IfcRoundedRectangleProfileDefType,
		typename IfcSanitaryTerminalTypeType,
		typename IfcSanitaryTerminalTypeEnumType,
		typename IfcScheduleTimeControlType,
		typename IfcSecondInMinuteType,
		typename IfcSectionalAreaIntegralMeasureType,
		typename IfcSectionedSpineType,
		typename IfcSectionModulusMeasureType,
		typename IfcSectionPropertiesType,
		typename IfcSectionReinforcementPropertiesType,
		typename IfcSectionTypeEnumType,
		typename IfcSensorTypeType,
		typename IfcSensorTypeEnumType,
		typename IfcSequenceEnumType,
		typename IfcServiceLifeType,
		typename IfcServiceLifeFactorType,
		typename IfcServiceLifeFactorTypeEnumType,
		typename IfcServiceLifeTypeEnumType,
		typename IfcShapeAspectType,
		typename IfcShapeModelType,
		typename IfcShapeRepresentationType,
		typename IfcShearModulusMeasureType,
		typename IfcShellType,
		typename IfcShellBasedSurfaceModelType,
		typename IfcSimplePropertyType,
		typename IfcSimpleValueType,
		typename IfcSIPrefixType,
		typename IfcSiteType,
		typename IfcSIUnitType,
		typename IfcSIUnitNameType,
		typename IfcSizeSelectType,
		typename IfcSlabType,
		typename IfcSlabTypeType,
		typename IfcSlabTypeEnumType,
		typename IfcSlippageConnectionConditionType,
		typename IfcSolidAngleMeasureType,
		typename IfcSolidModelType,
		typename IfcSoundPowerMeasureType,
		typename IfcSoundPressureMeasureType,
		typename IfcSoundPropertiesType,
		typename IfcSoundScaleEnumType,
		typename IfcSoundValueType,
		typename IfcSpaceType,
		typename IfcSpaceHeaterTypeType,
		typename IfcSpaceHeaterTypeEnumType,
		typename IfcSpaceProgramType,
		typename IfcSpaceThermalLoadPropertiesType,
		typename IfcSpaceTypeType,
		typename IfcSpaceTypeEnumType,
		typename IfcSpatialStructureElementType,
		typename IfcSpatialStructureElementTypeType,
		typename IfcSpecificHeatCapacityMeasureType,
		typename IfcSpecularExponentType,
		typename IfcSpecularHighlightSelectType,
		typename IfcSpecularRoughnessType,
		typename IfcSphereType,
		typename IfcStackTerminalTypeType,
		typename IfcStackTerminalTypeEnumType,
		typename IfcStairType,
		typename IfcStairFlightType,
		typename IfcStairFlightTypeType,
		typename IfcStairFlightTypeEnumType,
		typename IfcStairTypeEnumType,
		typename IfcStateEnumType,
		typename IfcStructuralActionType,
		typename IfcStructuralActivityType,
		typename IfcStructuralActivityAssignmentSelectType,
		typename IfcStructuralAnalysisModelType,
		typename IfcStructuralConnectionType,
		typename IfcStructuralConnectionConditionType,
		typename IfcStructuralCurveConnectionType,
		typename IfcStructuralCurveMemberType,
		typename IfcStructuralCurveMemberVaryingType,
		typename IfcStructuralCurveTypeEnumType,
		typename IfcStructuralItemType,
		typename IfcStructuralLinearActionType,
		typename IfcStructuralLinearActionVaryingType,
		typename IfcStructuralLoadType,
		typename IfcStructuralLoadGroupType,
		typename IfcStructuralLoadLinearForceType,
		typename IfcStructuralLoadPlanarForceType,
		typename IfcStructuralLoadSingleDisplacementType,
		typename IfcStructuralLoadSingleDisplacementDistortionType,
		typename IfcStructuralLoadSingleForceType,
		typename IfcStructuralLoadSingleForceWarpingType,
		typename IfcStructuralLoadStaticType,
		typename IfcStructuralLoadTemperatureType,
		typename IfcStructuralMemberType,
		typename IfcStructuralPlanarActionType,
		typename IfcStructuralPlanarActionVaryingType,
		typename IfcStructuralPointActionType,
		typename IfcStructuralPointConnectionType,
		typename IfcStructuralPointReactionType,
		typename IfcStructuralProfilePropertiesType,
		typename IfcStructuralReactionType,
		typename IfcStructuralResultGroupType,
		typename IfcStructuralSteelProfilePropertiesType,
		typename IfcStructuralSurfaceConnectionType,
		typename IfcStructuralSurfaceMemberType,
		typename IfcStructuralSurfaceMemberVaryingType,
		typename IfcStructuralSurfaceTypeEnumType,
		typename IfcStructuredDimensionCalloutType,
		typename IfcStyledItemType,
		typename IfcStyledRepresentationType,
		typename IfcStyleModelType,
		typename IfcSubContractResourceType,
		typename IfcSubedgeType,
		typename IfcSurfaceType,
		typename IfcSurfaceCurveSweptAreaSolidType,
		typename IfcSurfaceOfLinearExtrusionType,
		typename IfcSurfaceOfRevolutionType,
		typename IfcSurfaceOrFaceSurfaceType,
		typename IfcSurfaceSideType,
		typename IfcSurfaceStyleType,
		typename IfcSurfaceStyleElementSelectType,
		typename IfcSurfaceStyleLightingType,
		typename IfcSurfaceStyleRefractionType,
		typename IfcSurfaceStyleRenderingType,
		typename IfcSurfaceStyleShadingType,
		typename IfcSurfaceStyleWithTexturesType,
		typename IfcSurfaceTextureType,
		typename IfcSurfaceTextureEnumType,
		typename IfcSweptAreaSolidType,
		typename IfcSweptDiskSolidType,
		typename IfcSweptSurfaceType,
		typename IfcSwitchingDeviceTypeType,
		typename IfcSwitchingDeviceTypeEnumType,
		typename IfcSymbolStyleType,
		typename IfcSymbolStyleSelectType,
		typename IfcSystemType,
		typename IfcSystemFurnitureElementTypeType,
		typename IfcTableType,
		typename IfcTableRowType,
		typename IfcTankTypeType,
		typename IfcTankTypeEnumType,
		typename IfcTaskType,
		typename IfcTelecomAddressType,
		typename IfcTemperatureGradientMeasureType,
		typename IfcTendonType,
		typename IfcTendonAnchorType,
		typename IfcTendonTypeEnumType,
		typename IfcTerminatorSymbolType,
		typename IfcTextType,
		typename IfcTextAlignmentType,
		typename IfcTextDecorationType,
		typename IfcTextFontNameType,
		typename IfcTextFontSelectType,
		typename IfcTextLiteralType,
		typename IfcTextLiteralWithExtentType,
		typename IfcTextPathType,
		typename IfcTextStyleType,
		typename IfcTextStyleFontModelType,
		typename IfcTextStyleForDefinedFontType,
		typename IfcTextStyleSelectType,
		typename IfcTextStyleTextModelType,
		typename IfcTextStyleWithBoxCharacteristicsType,
		typename IfcTextTransformationType,
		typename IfcTextureCoordinateType,
		typename IfcTextureCoordinateGeneratorType,
		typename IfcTextureMapType,
		typename IfcTextureVertexType,
		typename IfcThermalAdmittanceMeasureType,
		typename IfcThermalConductivityMeasureType,
		typename IfcThermalExpansionCoefficientMeasureType,
		typename IfcThermalLoadSourceEnumType,
		typename IfcThermalLoadTypeEnumType,
		typename IfcThermalMaterialPropertiesType,
		typename IfcThermalResistanceMeasureType,
		typename IfcThermalTransmittanceMeasureType,
		typename IfcThermodynamicTemperatureMeasureType,
		typename IfcTimeMeasureType,
		typename IfcTimeSeriesType,
		typename IfcTimeSeriesDataTypeEnumType,
		typename IfcTimeSeriesReferenceRelationshipType,
		typename IfcTimeSeriesScheduleType,
		typename IfcTimeSeriesScheduleTypeEnumType,
		typename IfcTimeSeriesValueType,
		typename IfcTimeStampType,
		typename IfcTopologicalRepresentationItemType,
		typename IfcTopologyRepresentationType,
		typename IfcTorqueMeasureType,
		typename IfcTransformerTypeType,
		typename IfcTransformerTypeEnumType,
		typename IfcTransitionCodeType,
		typename IfcTransportElementType,
		typename IfcTransportElementTypeType,
		typename IfcTransportElementTypeEnumType,
		typename IfcTrapeziumProfileDefType,
		typename IfcTrimmedCurveType,
		typename IfcTrimmingPreferenceType,
		typename IfcTrimmingSelectType,
		typename IfcTShapeProfileDefType,
		typename IfcTubeBundleTypeType,
		typename IfcTubeBundleTypeEnumType,
		typename IfcTwoDirectionRepeatFactorType,
		typename IfcTypeObjectType,
		typename IfcTypeProductType,
		typename IfcUnitType,
		typename IfcUnitaryEquipmentTypeType,
		typename IfcUnitaryEquipmentTypeEnumType,
		typename IfcUnitAssignmentType,
		typename IfcUnitEnumType,
		typename IfcUShapeProfileDefType,
		typename IfcValueType,
		typename IfcValveTypeType,
		typename IfcValveTypeEnumType,
		typename IfcVaporPermeabilityMeasureType,
		typename IfcVectorType,
		typename IfcVectorOrDirectionType,
		typename IfcVertexType,
		typename IfcVertexBasedTextureMapType,
		typename IfcVertexLoopType,
		typename IfcVertexPointType,
		typename IfcVibrationIsolatorTypeType,
		typename IfcVibrationIsolatorTypeEnumType,
		typename IfcVirtualElementType,
		typename IfcVirtualGridIntersectionType,
		typename IfcVolumeMeasureType,
		typename IfcVolumetricFlowRateMeasureType,
		typename IfcWallType,
		typename IfcWallStandardCaseType,
		typename IfcWallTypeType,
		typename IfcWallTypeEnumType,
		typename IfcWarpingConstantMeasureType,
		typename IfcWarpingMomentMeasureType,
		typename IfcWasteTerminalTypeType,
		typename IfcWasteTerminalTypeEnumType,
		typename IfcWaterPropertiesType,
		typename IfcWindowType,
		typename IfcWindowLiningPropertiesType,
		typename IfcWindowPanelOperationEnumType,
		typename IfcWindowPanelPositionEnumType,
		typename IfcWindowPanelPropertiesType,
		typename IfcWindowStyleType,
		typename IfcWindowStyleConstructionEnumType,
		typename IfcWindowStyleOperationEnumType,
		typename IfcWorkControlType,
		typename IfcWorkControlTypeEnumType,
		typename IfcWorkPlanType,
		typename IfcWorkScheduleType,
		typename IfcYearNumberType,
		typename IfcZoneType,
		typename IfcZShapeProfileDefType,
	>
	struct IfcEntityTypes
	{
		typedef IfcAbsorbedDoseMeasureType IfcAbsorbedDoseMeasure;
		typedef IfcAccelerationMeasureType IfcAccelerationMeasure;
		typedef IfcActionRequestType IfcActionRequest;
		typedef IfcActionSourceTypeEnumType IfcActionSourceTypeEnum;
		typedef IfcActionTypeEnumType IfcActionTypeEnum;
		typedef IfcActorType IfcActor;
		typedef IfcActorRoleType IfcActorRole;
		typedef IfcActorSelectType IfcActorSelect;
		typedef IfcActuatorTypeType IfcActuatorType;
		typedef IfcActuatorTypeEnumType IfcActuatorTypeEnum;
		typedef IfcAddressType IfcAddress;
		typedef IfcAddressTypeEnumType IfcAddressTypeEnum;
		typedef IfcAheadOrBehindType IfcAheadOrBehind;
		typedef IfcAirTerminalBoxTypeType IfcAirTerminalBoxType;
		typedef IfcAirTerminalBoxTypeEnumType IfcAirTerminalBoxTypeEnum;
		typedef IfcAirTerminalTypeType IfcAirTerminalType;
		typedef IfcAirTerminalTypeEnumType IfcAirTerminalTypeEnum;
		typedef IfcAirToAirHeatRecoveryTypeType IfcAirToAirHeatRecoveryType;
		typedef IfcAirToAirHeatRecoveryTypeEnumType IfcAirToAirHeatRecoveryTypeEnum;
		typedef IfcAlarmTypeType IfcAlarmType;
		typedef IfcAlarmTypeEnumType IfcAlarmTypeEnum;
		typedef IfcAmountOfSubstanceMeasureType IfcAmountOfSubstanceMeasure;
		typedef IfcAnalysisModelTypeEnumType IfcAnalysisModelTypeEnum;
		typedef IfcAnalysisTheoryTypeEnumType IfcAnalysisTheoryTypeEnum;
		typedef IfcAngularDimensionType IfcAngularDimension;
		typedef IfcAngularVelocityMeasureType IfcAngularVelocityMeasure;
		typedef IfcAnnotationType IfcAnnotation;
		typedef IfcAnnotationCurveOccurrenceType IfcAnnotationCurveOccurrence;
		typedef IfcAnnotationFillAreaType IfcAnnotationFillArea;
		typedef IfcAnnotationFillAreaOccurrenceType IfcAnnotationFillAreaOccurrence;
		typedef IfcAnnotationOccurrenceType IfcAnnotationOccurrence;
		typedef IfcAnnotationSurfaceType IfcAnnotationSurface;
		typedef IfcAnnotationSurfaceOccurrenceType IfcAnnotationSurfaceOccurrence;
		typedef IfcAnnotationSymbolOccurrenceType IfcAnnotationSymbolOccurrence;
		typedef IfcAnnotationTextOccurrenceType IfcAnnotationTextOccurrence;
		typedef IfcApplicationType IfcApplication;
		typedef IfcAppliedValueType IfcAppliedValue;
		typedef IfcAppliedValueRelationshipType IfcAppliedValueRelationship;
		typedef IfcAppliedValueSelectType IfcAppliedValueSelect;
		typedef IfcApprovalType IfcApproval;
		typedef IfcApprovalActorRelationshipType IfcApprovalActorRelationship;
		typedef IfcApprovalPropertyRelationshipType IfcApprovalPropertyRelationship;
		typedef IfcApprovalRelationshipType IfcApprovalRelationship;
		typedef IfcArbitraryClosedProfileDefType IfcArbitraryClosedProfileDef;
		typedef IfcArbitraryOpenProfileDefType IfcArbitraryOpenProfileDef;
		typedef IfcArbitraryProfileDefWithVoidsType IfcArbitraryProfileDefWithVoids;
		typedef IfcAreaMeasureType IfcAreaMeasure;
		typedef IfcArithmeticOperatorEnumType IfcArithmeticOperatorEnum;
		typedef IfcAssemblyPlaceEnumType IfcAssemblyPlaceEnum;
		typedef IfcAssetType IfcAsset;
		typedef IfcAsymmetricIShapeProfileDefType IfcAsymmetricIShapeProfileDef;
		typedef IfcAxis1PlacementType IfcAxis1Placement;
		typedef IfcAxis2PlacementType IfcAxis2Placement;
		typedef IfcAxis2Placement2DType IfcAxis2Placement2D;
		typedef IfcAxis2Placement3DType IfcAxis2Placement3D;
		typedef IfcBeamType IfcBeam;
		typedef IfcBeamTypeType IfcBeamType;
		typedef IfcBeamTypeEnumType IfcBeamTypeEnum;
		typedef IfcBenchmarkEnumType IfcBenchmarkEnum;
		typedef IfcBezierCurveType IfcBezierCurve;
		typedef IfcBlobTextureType IfcBlobTexture;
		typedef IfcBlockType IfcBlock;
		typedef IfcBoilerTypeType IfcBoilerType;
		typedef IfcBoilerTypeEnumType IfcBoilerTypeEnum;
		typedef IfcBooleanType IfcBoolean;
		typedef IfcBooleanClippingResultType IfcBooleanClippingResult;
		typedef IfcBooleanOperandType IfcBooleanOperand;
		typedef IfcBooleanOperatorType IfcBooleanOperator;
		typedef IfcBooleanResultType IfcBooleanResult;
		typedef IfcBoundaryConditionType IfcBoundaryCondition;
		typedef IfcBoundaryEdgeConditionType IfcBoundaryEdgeCondition;
		typedef IfcBoundaryFaceConditionType IfcBoundaryFaceCondition;
		typedef IfcBoundaryNodeConditionType IfcBoundaryNodeCondition;
		typedef IfcBoundaryNodeConditionWarpingType IfcBoundaryNodeConditionWarping;
		typedef IfcBoundedCurveType IfcBoundedCurve;
		typedef IfcBoundedSurfaceType IfcBoundedSurface;
		typedef IfcBoundingBoxType IfcBoundingBox;
		typedef IfcBoxAlignmentType IfcBoxAlignment;
		typedef IfcBoxedHalfSpaceType IfcBoxedHalfSpace;
		typedef IfcBSplineCurveType IfcBSplineCurve;
		typedef IfcBSplineCurveFormType IfcBSplineCurveForm;
		typedef IfcBuildingType IfcBuilding;
		typedef IfcBuildingElementType IfcBuildingElement;
		typedef IfcBuildingElementComponentType IfcBuildingElementComponent;
		typedef IfcBuildingElementPartType IfcBuildingElementPart;
		typedef IfcBuildingElementProxyType IfcBuildingElementProxy;
		typedef IfcBuildingElementProxyTypeType IfcBuildingElementProxyType;
		typedef IfcBuildingElementProxyTypeEnumType IfcBuildingElementProxyTypeEnum;
		typedef IfcBuildingElementTypeType IfcBuildingElementType;
		typedef IfcBuildingStoreyType IfcBuildingStorey;
		typedef IfcCableCarrierFittingTypeType IfcCableCarrierFittingType;
		typedef IfcCableCarrierFittingTypeEnumType IfcCableCarrierFittingTypeEnum;
		typedef IfcCableCarrierSegmentTypeType IfcCableCarrierSegmentType;
		typedef IfcCableCarrierSegmentTypeEnumType IfcCableCarrierSegmentTypeEnum;
		typedef IfcCableSegmentTypeType IfcCableSegmentType;
		typedef IfcCableSegmentTypeEnumType IfcCableSegmentTypeEnum;
		typedef IfcCalendarDateType IfcCalendarDate;
		typedef IfcCartesianPointType IfcCartesianPoint;
		typedef IfcCartesianTransformationOperatorType IfcCartesianTransformationOperator;
		typedef IfcCartesianTransformationOperator2DType IfcCartesianTransformationOperator2D;
		typedef IfcCartesianTransformationOperator2DnonUniformType IfcCartesianTransformationOperator2DnonUniform;
		typedef IfcCartesianTransformationOperator3DType IfcCartesianTransformationOperator3D;
		typedef IfcCartesianTransformationOperator3DnonUniformType IfcCartesianTransformationOperator3DnonUniform;
		typedef IfcCenterLineProfileDefType IfcCenterLineProfileDef;
		typedef IfcChamferEdgeFeatureType IfcChamferEdgeFeature;
		typedef IfcChangeActionEnumType IfcChangeActionEnum;
		typedef IfcCharacterStyleSelectType IfcCharacterStyleSelect;
		typedef IfcChillerTypeType IfcChillerType;
		typedef IfcChillerTypeEnumType IfcChillerTypeEnum;
		typedef IfcCircleType IfcCircle;
		typedef IfcCircleHollowProfileDefType IfcCircleHollowProfileDef;
		typedef IfcCircleProfileDefType IfcCircleProfileDef;
		typedef IfcClassificationType IfcClassification;
		typedef IfcClassificationItemType IfcClassificationItem;
		typedef IfcClassificationItemRelationshipType IfcClassificationItemRelationship;
		typedef IfcClassificationNotationType IfcClassificationNotation;
		typedef IfcClassificationNotationFacetType IfcClassificationNotationFacet;
		typedef IfcClassificationNotationSelectType IfcClassificationNotationSelect;
		typedef IfcClassificationReferenceType IfcClassificationReference;
		typedef IfcClosedShellType IfcClosedShell;
		typedef IfcCoilTypeType IfcCoilType;
		typedef IfcCoilTypeEnumType IfcCoilTypeEnum;
		typedef IfcColourType IfcColour;
		typedef IfcColourOrFactorType IfcColourOrFactor;
		typedef IfcColourRgbType IfcColourRgb;
		typedef IfcColourSpecificationType IfcColourSpecification;
		typedef IfcColumnType IfcColumn;
		typedef IfcColumnTypeType IfcColumnType;
		typedef IfcColumnTypeEnumType IfcColumnTypeEnum;
		typedef IfcComplexNumberType IfcComplexNumber;
		typedef IfcComplexPropertyType IfcComplexProperty;
		typedef IfcCompositeCurveType IfcCompositeCurve;
		typedef IfcCompositeCurveSegmentType IfcCompositeCurveSegment;
		typedef IfcCompositeProfileDefType IfcCompositeProfileDef;
		typedef IfcCompoundPlaneAngleMeasureType IfcCompoundPlaneAngleMeasure;
		typedef IfcCompressorTypeType IfcCompressorType;
		typedef IfcCompressorTypeEnumType IfcCompressorTypeEnum;
		typedef IfcCondenserTypeType IfcCondenserType;
		typedef IfcCondenserTypeEnumType IfcCondenserTypeEnum;
		typedef IfcConditionType IfcCondition;
		typedef IfcConditionCriterionType IfcConditionCriterion;
		typedef IfcConditionCriterionSelectType IfcConditionCriterionSelect;
		typedef IfcConicType IfcConic;
		typedef IfcConnectedFaceSetType IfcConnectedFaceSet;
		typedef IfcConnectionCurveGeometryType IfcConnectionCurveGeometry;
		typedef IfcConnectionGeometryType IfcConnectionGeometry;
		typedef IfcConnectionPointEccentricityType IfcConnectionPointEccentricity;
		typedef IfcConnectionPointGeometryType IfcConnectionPointGeometry;
		typedef IfcConnectionPortGeometryType IfcConnectionPortGeometry;
		typedef IfcConnectionSurfaceGeometryType IfcConnectionSurfaceGeometry;
		typedef IfcConnectionTypeEnumType IfcConnectionTypeEnum;
		typedef IfcConstraintType IfcConstraint;
		typedef IfcConstraintAggregationRelationshipType IfcConstraintAggregationRelationship;
		typedef IfcConstraintClassificationRelationshipType IfcConstraintClassificationRelationship;
		typedef IfcConstraintEnumType IfcConstraintEnum;
		typedef IfcConstraintRelationshipType IfcConstraintRelationship;
		typedef IfcConstructionEquipmentResourceType IfcConstructionEquipmentResource;
		typedef IfcConstructionMaterialResourceType IfcConstructionMaterialResource;
		typedef IfcConstructionProductResourceType IfcConstructionProductResource;
		typedef IfcConstructionResourceType IfcConstructionResource;
		typedef IfcContextDependentMeasureType IfcContextDependentMeasure;
		typedef IfcContextDependentUnitType IfcContextDependentUnit;
		typedef IfcControlType IfcControl;
		typedef IfcControllerTypeType IfcControllerType;
		typedef IfcControllerTypeEnumType IfcControllerTypeEnum;
		typedef IfcConversionBasedUnitType IfcConversionBasedUnit;
		typedef IfcCooledBeamTypeType IfcCooledBeamType;
		typedef IfcCooledBeamTypeEnumType IfcCooledBeamTypeEnum;
		typedef IfcCoolingTowerTypeType IfcCoolingTowerType;
		typedef IfcCoolingTowerTypeEnumType IfcCoolingTowerTypeEnum;
		typedef IfcCoordinatedUniversalTimeOffsetType IfcCoordinatedUniversalTimeOffset;
		typedef IfcCostItemType IfcCostItem;
		typedef IfcCostScheduleType IfcCostSchedule;
		typedef IfcCostScheduleTypeEnumType IfcCostScheduleTypeEnum;
		typedef IfcCostValueType IfcCostValue;
		typedef IfcCountMeasureType IfcCountMeasure;
		typedef IfcCoveringType IfcCovering;
		typedef IfcCoveringTypeType IfcCoveringType;
		typedef IfcCoveringTypeEnumType IfcCoveringTypeEnum;
		typedef IfcCraneRailAShapeProfileDefType IfcCraneRailAShapeProfileDef;
		typedef IfcCraneRailFShapeProfileDefType IfcCraneRailFShapeProfileDef;
		typedef IfcCrewResourceType IfcCrewResource;
		typedef IfcCsgPrimitive3DType IfcCsgPrimitive3D;
		typedef IfcCsgSelectType IfcCsgSelect;
		typedef IfcCsgSolidType IfcCsgSolid;
		typedef IfcCShapeProfileDefType IfcCShapeProfileDef;
		typedef IfcCurrencyEnumType IfcCurrencyEnum;
		typedef IfcCurrencyRelationshipType IfcCurrencyRelationship;
		typedef IfcCurtainWallType IfcCurtainWall;
		typedef IfcCurtainWallTypeType IfcCurtainWallType;
		typedef IfcCurtainWallTypeEnumType IfcCurtainWallTypeEnum;
		typedef IfcCurvatureMeasureType IfcCurvatureMeasure;
		typedef IfcCurveType IfcCurve;
		typedef IfcCurveBoundedPlaneType IfcCurveBoundedPlane;
		typedef IfcCurveFontOrScaledCurveFontSelectType IfcCurveFontOrScaledCurveFontSelect;
		typedef IfcCurveOrEdgeCurveType IfcCurveOrEdgeCurve;
		typedef IfcCurveStyleType IfcCurveStyle;
		typedef IfcCurveStyleFontType IfcCurveStyleFont;
		typedef IfcCurveStyleFontAndScalingType IfcCurveStyleFontAndScaling;
		typedef IfcCurveStyleFontPatternType IfcCurveStyleFontPattern;
		typedef IfcCurveStyleFontSelectType IfcCurveStyleFontSelect;
		typedef IfcDamperTypeType IfcDamperType;
		typedef IfcDamperTypeEnumType IfcDamperTypeEnum;
		typedef IfcDataOriginEnumType IfcDataOriginEnum;
		typedef IfcDateAndTimeType IfcDateAndTime;
		typedef IfcDateTimeSelectType IfcDateTimeSelect;
		typedef IfcDayInMonthNumberType IfcDayInMonthNumber;
		typedef IfcDaylightSavingHourType IfcDaylightSavingHour;
		typedef IfcDefinedSymbolType IfcDefinedSymbol;
		typedef IfcDefinedSymbolSelectType IfcDefinedSymbolSelect;
		typedef IfcDerivedMeasureValueType IfcDerivedMeasureValue;
		typedef IfcDerivedProfileDefType IfcDerivedProfileDef;
		typedef IfcDerivedUnitType IfcDerivedUnit;
		typedef IfcDerivedUnitElementType IfcDerivedUnitElement;
		typedef IfcDerivedUnitEnumType IfcDerivedUnitEnum;
		typedef IfcDescriptiveMeasureType IfcDescriptiveMeasure;
		typedef IfcDiameterDimensionType IfcDiameterDimension;
		typedef IfcDimensionalExponentsType IfcDimensionalExponents;
		typedef IfcDimensionCalloutRelationshipType IfcDimensionCalloutRelationship;
		typedef IfcDimensionCountType IfcDimensionCount;
		typedef IfcDimensionCurveType IfcDimensionCurve;
		typedef IfcDimensionCurveDirectedCalloutType IfcDimensionCurveDirectedCallout;
		typedef IfcDimensionCurveTerminatorType IfcDimensionCurveTerminator;
		typedef IfcDimensionExtentUsageType IfcDimensionExtentUsage;
		typedef IfcDimensionPairType IfcDimensionPair;
		typedef IfcDirectionType IfcDirection;
		typedef IfcDirectionSenseEnumType IfcDirectionSenseEnum;
		typedef IfcDiscreteAccessoryType IfcDiscreteAccessory;
		typedef IfcDiscreteAccessoryTypeType IfcDiscreteAccessoryType;
		typedef IfcDistributionChamberElementType IfcDistributionChamberElement;
		typedef IfcDistributionChamberElementTypeType IfcDistributionChamberElementType;
		typedef IfcDistributionChamberElementTypeEnumType IfcDistributionChamberElementTypeEnum;
		typedef IfcDistributionControlElementType IfcDistributionControlElement;
		typedef IfcDistributionControlElementTypeType IfcDistributionControlElementType;
		typedef IfcDistributionElementType IfcDistributionElement;
		typedef IfcDistributionElementTypeType IfcDistributionElementType;
		typedef IfcDistributionFlowElementType IfcDistributionFlowElement;
		typedef IfcDistributionFlowElementTypeType IfcDistributionFlowElementType;
		typedef IfcDistributionPortType IfcDistributionPort;
		typedef IfcDocumentConfidentialityEnumType IfcDocumentConfidentialityEnum;
		typedef IfcDocumentElectronicFormatType IfcDocumentElectronicFormat;
		typedef IfcDocumentInformationType IfcDocumentInformation;
		typedef IfcDocumentInformationRelationshipType IfcDocumentInformationRelationship;
		typedef IfcDocumentReferenceType IfcDocumentReference;
		typedef IfcDocumentSelectType IfcDocumentSelect;
		typedef IfcDocumentStatusEnumType IfcDocumentStatusEnum;
		typedef IfcDoorType IfcDoor;
		typedef IfcDoorLiningPropertiesType IfcDoorLiningProperties;
		typedef IfcDoorPanelOperationEnumType IfcDoorPanelOperationEnum;
		typedef IfcDoorPanelPositionEnumType IfcDoorPanelPositionEnum;
		typedef IfcDoorPanelPropertiesType IfcDoorPanelProperties;
		typedef IfcDoorStyleType IfcDoorStyle;
		typedef IfcDoorStyleConstructionEnumType IfcDoorStyleConstructionEnum;
		typedef IfcDoorStyleOperationEnumType IfcDoorStyleOperationEnum;
		typedef IfcDoseEquivalentMeasureType IfcDoseEquivalentMeasure;
		typedef IfcDraughtingCalloutType IfcDraughtingCallout;
		typedef IfcDraughtingCalloutElementType IfcDraughtingCalloutElement;
		typedef IfcDraughtingCalloutRelationshipType IfcDraughtingCalloutRelationship;
		typedef IfcDraughtingPreDefinedColourType IfcDraughtingPreDefinedColour;
		typedef IfcDraughtingPreDefinedCurveFontType IfcDraughtingPreDefinedCurveFont;
		typedef IfcDraughtingPreDefinedTextFontType IfcDraughtingPreDefinedTextFont;
		typedef IfcDuctFittingTypeType IfcDuctFittingType;
		typedef IfcDuctFittingTypeEnumType IfcDuctFittingTypeEnum;
		typedef IfcDuctSegmentTypeType IfcDuctSegmentType;
		typedef IfcDuctSegmentTypeEnumType IfcDuctSegmentTypeEnum;
		typedef IfcDuctSilencerTypeType IfcDuctSilencerType;
		typedef IfcDuctSilencerTypeEnumType IfcDuctSilencerTypeEnum;
		typedef IfcDynamicViscosityMeasureType IfcDynamicViscosityMeasure;
		typedef IfcEdgeType IfcEdge;
		typedef IfcEdgeCurveType IfcEdgeCurve;
		typedef IfcEdgeFeatureType IfcEdgeFeature;
		typedef IfcEdgeLoopType IfcEdgeLoop;
		typedef IfcElectricalBasePropertiesType IfcElectricalBaseProperties;
		typedef IfcElectricalCircuitType IfcElectricalCircuit;
		typedef IfcElectricalElementType IfcElectricalElement;
		typedef IfcElectricApplianceTypeType IfcElectricApplianceType;
		typedef IfcElectricApplianceTypeEnumType IfcElectricApplianceTypeEnum;
		typedef IfcElectricCapacitanceMeasureType IfcElectricCapacitanceMeasure;
		typedef IfcElectricChargeMeasureType IfcElectricChargeMeasure;
		typedef IfcElectricConductanceMeasureType IfcElectricConductanceMeasure;
		typedef IfcElectricCurrentEnumType IfcElectricCurrentEnum;
		typedef IfcElectricCurrentMeasureType IfcElectricCurrentMeasure;
		typedef IfcElectricDistributionPointType IfcElectricDistributionPoint;
		typedef IfcElectricDistributionPointFunctionEnumType IfcElectricDistributionPointFunctionEnum;
		typedef IfcElectricFlowStorageDeviceTypeType IfcElectricFlowStorageDeviceType;
		typedef IfcElectricFlowStorageDeviceTypeEnumType IfcElectricFlowStorageDeviceTypeEnum;
		typedef IfcElectricGeneratorTypeType IfcElectricGeneratorType;
		typedef IfcElectricGeneratorTypeEnumType IfcElectricGeneratorTypeEnum;
		typedef IfcElectricHeaterTypeType IfcElectricHeaterType;
		typedef IfcElectricHeaterTypeEnumType IfcElectricHeaterTypeEnum;
		typedef IfcElectricMotorTypeType IfcElectricMotorType;
		typedef IfcElectricMotorTypeEnumType IfcElectricMotorTypeEnum;
		typedef IfcElectricResistanceMeasureType IfcElectricResistanceMeasure;
		typedef IfcElectricTimeControlTypeType IfcElectricTimeControlType;
		typedef IfcElectricTimeControlTypeEnumType IfcElectricTimeControlTypeEnum;
		typedef IfcElectricVoltageMeasureType IfcElectricVoltageMeasure;
		typedef IfcElementType IfcElement;
		typedef IfcElementarySurfaceType IfcElementarySurface;
		typedef IfcElementAssemblyType IfcElementAssembly;
		typedef IfcElementAssemblyTypeEnumType IfcElementAssemblyTypeEnum;
		typedef IfcElementComponentType IfcElementComponent;
		typedef IfcElementComponentTypeType IfcElementComponentType;
		typedef IfcElementCompositionEnumType IfcElementCompositionEnum;
		typedef IfcElementQuantityType IfcElementQuantity;
		typedef IfcElementTypeType IfcElementType;
		typedef IfcEllipseType IfcEllipse;
		typedef IfcEllipseProfileDefType IfcEllipseProfileDef;
		typedef IfcEnergyConversionDeviceType IfcEnergyConversionDevice;
		typedef IfcEnergyConversionDeviceTypeType IfcEnergyConversionDeviceType;
		typedef IfcEnergyMeasureType IfcEnergyMeasure;
		typedef IfcEnergyPropertiesType IfcEnergyProperties;
		typedef IfcEnergySequenceEnumType IfcEnergySequenceEnum;
		typedef IfcEnvironmentalImpactCategoryEnumType IfcEnvironmentalImpactCategoryEnum;
		typedef IfcEnvironmentalImpactValueType IfcEnvironmentalImpactValue;
		typedef IfcEquipmentElementType IfcEquipmentElement;
		typedef IfcEquipmentStandardType IfcEquipmentStandard;
		typedef IfcEvaporativeCoolerTypeType IfcEvaporativeCoolerType;
		typedef IfcEvaporativeCoolerTypeEnumType IfcEvaporativeCoolerTypeEnum;
		typedef IfcEvaporatorTypeType IfcEvaporatorType;
		typedef IfcEvaporatorTypeEnumType IfcEvaporatorTypeEnum;
		typedef IfcExtendedMaterialPropertiesType IfcExtendedMaterialProperties;
		typedef IfcExternallyDefinedHatchStyleType IfcExternallyDefinedHatchStyle;
		typedef IfcExternallyDefinedSurfaceStyleType IfcExternallyDefinedSurfaceStyle;
		typedef IfcExternallyDefinedSymbolType IfcExternallyDefinedSymbol;
		typedef IfcExternallyDefinedTextFontType IfcExternallyDefinedTextFont;
		typedef IfcExternalReferenceType IfcExternalReference;
		typedef IfcExtrudedAreaSolidType IfcExtrudedAreaSolid;
		typedef IfcFaceType IfcFace;
		typedef IfcFaceBasedSurfaceModelType IfcFaceBasedSurfaceModel;
		typedef IfcFaceBoundType IfcFaceBound;
		typedef IfcFaceOuterBoundType IfcFaceOuterBound;
		typedef IfcFaceSurfaceType IfcFaceSurface;
		typedef IfcFacetedBrepType IfcFacetedBrep;
		typedef IfcFacetedBrepWithVoidsType IfcFacetedBrepWithVoids;
		typedef IfcFailureConnectionConditionType IfcFailureConnectionCondition;
		typedef IfcFanTypeType IfcFanType;
		typedef IfcFanTypeEnumType IfcFanTypeEnum;
		typedef IfcFastenerType IfcFastener;
		typedef IfcFastenerTypeType IfcFastenerType;
		typedef IfcFeatureElementType IfcFeatureElement;
		typedef IfcFeatureElementAdditionType IfcFeatureElementAddition;
		typedef IfcFeatureElementSubtractionType IfcFeatureElementSubtraction;
		typedef IfcFillAreaStyleType IfcFillAreaStyle;
		typedef IfcFillAreaStyleHatchingType IfcFillAreaStyleHatching;
		typedef IfcFillAreaStyleTilesType IfcFillAreaStyleTiles;
		typedef IfcFillAreaStyleTileShapeSelectType IfcFillAreaStyleTileShapeSelect;
		typedef IfcFillAreaStyleTileSymbolWithStyleType IfcFillAreaStyleTileSymbolWithStyle;
		typedef IfcFillStyleSelectType IfcFillStyleSelect;
		typedef IfcFilterTypeType IfcFilterType;
		typedef IfcFilterTypeEnumType IfcFilterTypeEnum;
		typedef IfcFireSuppressionTerminalTypeType IfcFireSuppressionTerminalType;
		typedef IfcFireSuppressionTerminalTypeEnumType IfcFireSuppressionTerminalTypeEnum;
		typedef IfcFlowControllerType IfcFlowController;
		typedef IfcFlowControllerTypeType IfcFlowControllerType;
		typedef IfcFlowDirectionEnumType IfcFlowDirectionEnum;
		typedef IfcFlowFittingType IfcFlowFitting;
		typedef IfcFlowFittingTypeType IfcFlowFittingType;
		typedef IfcFlowInstrumentTypeType IfcFlowInstrumentType;
		typedef IfcFlowInstrumentTypeEnumType IfcFlowInstrumentTypeEnum;
		typedef IfcFlowMeterTypeType IfcFlowMeterType;
		typedef IfcFlowMeterTypeEnumType IfcFlowMeterTypeEnum;
		typedef IfcFlowMovingDeviceType IfcFlowMovingDevice;
		typedef IfcFlowMovingDeviceTypeType IfcFlowMovingDeviceType;
		typedef IfcFlowSegmentType IfcFlowSegment;
		typedef IfcFlowSegmentTypeType IfcFlowSegmentType;
		typedef IfcFlowStorageDeviceType IfcFlowStorageDevice;
		typedef IfcFlowStorageDeviceTypeType IfcFlowStorageDeviceType;
		typedef IfcFlowTerminalType IfcFlowTerminal;
		typedef IfcFlowTerminalTypeType IfcFlowTerminalType;
		typedef IfcFlowTreatmentDeviceType IfcFlowTreatmentDevice;
		typedef IfcFlowTreatmentDeviceTypeType IfcFlowTreatmentDeviceType;
		typedef IfcFluidFlowPropertiesType IfcFluidFlowProperties;
		typedef IfcFontStyleType IfcFontStyle;
		typedef IfcFontVariantType IfcFontVariant;
		typedef IfcFontWeightType IfcFontWeight;
		typedef IfcFootingType IfcFooting;
		typedef IfcFootingTypeEnumType IfcFootingTypeEnum;
		typedef IfcForceMeasureType IfcForceMeasure;
		typedef IfcFrequencyMeasureType IfcFrequencyMeasure;
		typedef IfcFuelPropertiesType IfcFuelProperties;
		typedef IfcFurnishingElementType IfcFurnishingElement;
		typedef IfcFurnishingElementTypeType IfcFurnishingElementType;
		typedef IfcFurnitureStandardType IfcFurnitureStandard;
		typedef IfcFurnitureTypeType IfcFurnitureType;
		typedef IfcGasTerminalTypeType IfcGasTerminalType;
		typedef IfcGasTerminalTypeEnumType IfcGasTerminalTypeEnum;
		typedef IfcGeneralMaterialPropertiesType IfcGeneralMaterialProperties;
		typedef IfcGeneralProfilePropertiesType IfcGeneralProfileProperties;
		typedef IfcGeometricCurveSetType IfcGeometricCurveSet;
		typedef IfcGeometricProjectionEnumType IfcGeometricProjectionEnum;
		typedef IfcGeometricRepresentationContextType IfcGeometricRepresentationContext;
		typedef IfcGeometricRepresentationItemType IfcGeometricRepresentationItem;
		typedef IfcGeometricRepresentationSubContextType IfcGeometricRepresentationSubContext;
		typedef IfcGeometricSetType IfcGeometricSet;
		typedef IfcGeometricSetSelectType IfcGeometricSetSelect;
		typedef IfcGloballyUniqueIdType IfcGloballyUniqueId;
		typedef IfcGlobalOrLocalEnumType IfcGlobalOrLocalEnum;
		typedef IfcGridType IfcGrid;
		typedef IfcGridAxisType IfcGridAxis;
		typedef IfcGridPlacementType IfcGridPlacement;
		typedef IfcGroupType IfcGroup;
		typedef IfcHalfSpaceSolidType IfcHalfSpaceSolid;
		typedef IfcHatchLineDistanceSelectType IfcHatchLineDistanceSelect;
		typedef IfcHeatExchangerTypeType IfcHeatExchangerType;
		typedef IfcHeatExchangerTypeEnumType IfcHeatExchangerTypeEnum;
		typedef IfcHeatFluxDensityMeasureType IfcHeatFluxDensityMeasure;
		typedef IfcHeatingValueMeasureType IfcHeatingValueMeasure;
		typedef IfcHourInDayType IfcHourInDay;
		typedef IfcHumidifierTypeType IfcHumidifierType;
		typedef IfcHumidifierTypeEnumType IfcHumidifierTypeEnum;
		typedef IfcHygroscopicMaterialPropertiesType IfcHygroscopicMaterialProperties;
		typedef IfcIdentifierType IfcIdentifier;
		typedef IfcIlluminanceMeasureType IfcIlluminanceMeasure;
		typedef IfcImageTextureType IfcImageTexture;
		typedef IfcInductanceMeasureType IfcInductanceMeasure;
		typedef IfcIntegerType IfcInteger;
		typedef IfcIntegerCountRateMeasureType IfcIntegerCountRateMeasure;
		typedef IfcInternalOrExternalEnumType IfcInternalOrExternalEnum;
		typedef IfcInventoryType IfcInventory;
		typedef IfcInventoryTypeEnumType IfcInventoryTypeEnum;
		typedef IfcIonConcentrationMeasureType IfcIonConcentrationMeasure;
		typedef IfcIrregularTimeSeriesType IfcIrregularTimeSeries;
		typedef IfcIrregularTimeSeriesValueType IfcIrregularTimeSeriesValue;
		typedef IfcIShapeProfileDefType IfcIShapeProfileDef;
		typedef IfcIsothermalMoistureCapacityMeasureType IfcIsothermalMoistureCapacityMeasure;
		typedef IfcJunctionBoxTypeType IfcJunctionBoxType;
		typedef IfcJunctionBoxTypeEnumType IfcJunctionBoxTypeEnum;
		typedef IfcKinematicViscosityMeasureType IfcKinematicViscosityMeasure;
		typedef IfcLabelType IfcLabel;
		typedef IfcLaborResourceType IfcLaborResource;
		typedef IfcLampTypeType IfcLampType;
		typedef IfcLampTypeEnumType IfcLampTypeEnum;
		typedef IfcLayeredItemType IfcLayeredItem;
		typedef IfcLayerSetDirectionEnumType IfcLayerSetDirectionEnum;
		typedef IfcLengthMeasureType IfcLengthMeasure;
		typedef IfcLibraryInformationType IfcLibraryInformation;
		typedef IfcLibraryReferenceType IfcLibraryReference;
		typedef IfcLibrarySelectType IfcLibrarySelect;
		typedef IfcLightDistributionCurveEnumType IfcLightDistributionCurveEnum;
		typedef IfcLightDistributionDataType IfcLightDistributionData;
		typedef IfcLightDistributionDataSourceSelectType IfcLightDistributionDataSourceSelect;
		typedef IfcLightEmissionSourceEnumType IfcLightEmissionSourceEnum;
		typedef IfcLightFixtureTypeType IfcLightFixtureType;
		typedef IfcLightFixtureTypeEnumType IfcLightFixtureTypeEnum;
		typedef IfcLightIntensityDistributionType IfcLightIntensityDistribution;
		typedef IfcLightSourceType IfcLightSource;
		typedef IfcLightSourceAmbientType IfcLightSourceAmbient;
		typedef IfcLightSourceDirectionalType IfcLightSourceDirectional;
		typedef IfcLightSourceGoniometricType IfcLightSourceGoniometric;
		typedef IfcLightSourcePositionalType IfcLightSourcePositional;
		typedef IfcLightSourceSpotType IfcLightSourceSpot;
		typedef IfcLineType IfcLine;
		typedef IfcLinearDimensionType IfcLinearDimension;
		typedef IfcLinearForceMeasureType IfcLinearForceMeasure;
		typedef IfcLinearMomentMeasureType IfcLinearMomentMeasure;
		typedef IfcLinearStiffnessMeasureType IfcLinearStiffnessMeasure;
		typedef IfcLinearVelocityMeasureType IfcLinearVelocityMeasure;
		typedef IfcLoadGroupTypeEnumType IfcLoadGroupTypeEnum;
		typedef IfcLocalPlacementType IfcLocalPlacement;
		typedef IfcLocalTimeType IfcLocalTime;
		typedef IfcLogicalType IfcLogical;
		typedef IfcLogicalOperatorEnumType IfcLogicalOperatorEnum;
		typedef IfcLoopType IfcLoop;
		typedef IfcLShapeProfileDefType IfcLShapeProfileDef;
		typedef IfcLuminousFluxMeasureType IfcLuminousFluxMeasure;
		typedef IfcLuminousIntensityDistributionMeasureType IfcLuminousIntensityDistributionMeasure;
		typedef IfcLuminousIntensityMeasureType IfcLuminousIntensityMeasure;
		typedef IfcMagneticFluxDensityMeasureType IfcMagneticFluxDensityMeasure;
		typedef IfcMagneticFluxMeasureType IfcMagneticFluxMeasure;
		typedef IfcManifoldSolidBrepType IfcManifoldSolidBrep;
		typedef IfcMappedItemType IfcMappedItem;
		typedef IfcMassDensityMeasureType IfcMassDensityMeasure;
		typedef IfcMassFlowRateMeasureType IfcMassFlowRateMeasure;
		typedef IfcMassMeasureType IfcMassMeasure;
		typedef IfcMassPerLengthMeasureType IfcMassPerLengthMeasure;
		typedef IfcMaterialType IfcMaterial;
		typedef IfcMaterialClassificationRelationshipType IfcMaterialClassificationRelationship;
		typedef IfcMaterialDefinitionRepresentationType IfcMaterialDefinitionRepresentation;
		typedef IfcMaterialLayerType IfcMaterialLayer;
		typedef IfcMaterialLayerSetType IfcMaterialLayerSet;
		typedef IfcMaterialLayerSetUsageType IfcMaterialLayerSetUsage;
		typedef IfcMaterialListType IfcMaterialList;
		typedef IfcMaterialPropertiesType IfcMaterialProperties;
		typedef IfcMaterialSelectType IfcMaterialSelect;
		typedef IfcMeasureValueType IfcMeasureValue;
		typedef IfcMeasureWithUnitType IfcMeasureWithUnit;
		typedef IfcMechanicalConcreteMaterialPropertiesType IfcMechanicalConcreteMaterialProperties;
		typedef IfcMechanicalFastenerType IfcMechanicalFastener;
		typedef IfcMechanicalFastenerTypeType IfcMechanicalFastenerType;
		typedef IfcMechanicalMaterialPropertiesType IfcMechanicalMaterialProperties;
		typedef IfcMechanicalSteelMaterialPropertiesType IfcMechanicalSteelMaterialProperties;
		typedef IfcMemberType IfcMember;
		typedef IfcMemberTypeType IfcMemberType;
		typedef IfcMemberTypeEnumType IfcMemberTypeEnum;
		typedef IfcMetricType IfcMetric;
		typedef IfcMetricValueSelectType IfcMetricValueSelect;
		typedef IfcMinuteInHourType IfcMinuteInHour;
		typedef IfcModulusOfElasticityMeasureType IfcModulusOfElasticityMeasure;
		typedef IfcModulusOfLinearSubgradeReactionMeasureType IfcModulusOfLinearSubgradeReactionMeasure;
		typedef IfcModulusOfRotationalSubgradeReactionMeasureType IfcModulusOfRotationalSubgradeReactionMeasure;
		typedef IfcModulusOfSubgradeReactionMeasureType IfcModulusOfSubgradeReactionMeasure;
		typedef IfcMoistureDiffusivityMeasureType IfcMoistureDiffusivityMeasure;
		typedef IfcMolecularWeightMeasureType IfcMolecularWeightMeasure;
		typedef IfcMomentOfInertiaMeasureType IfcMomentOfInertiaMeasure;
		typedef IfcMonetaryMeasureType IfcMonetaryMeasure;
		typedef IfcMonetaryUnitType IfcMonetaryUnit;
		typedef IfcMonthInYearNumberType IfcMonthInYearNumber;
		typedef IfcMotorConnectionTypeType IfcMotorConnectionType;
		typedef IfcMotorConnectionTypeEnumType IfcMotorConnectionTypeEnum;
		typedef IfcMoveType IfcMove;
		typedef IfcNamedUnitType IfcNamedUnit;
		typedef IfcNormalisedRatioMeasureType IfcNormalisedRatioMeasure;
		typedef IfcNullStyleType IfcNullStyle;
		typedef IfcNumericMeasureType IfcNumericMeasure;
		typedef IfcObjectType IfcObject;
		typedef IfcObjectDefinitionType IfcObjectDefinition;
		typedef IfcObjectiveType IfcObjective;
		typedef IfcObjectiveEnumType IfcObjectiveEnum;
		typedef IfcObjectPlacementType IfcObjectPlacement;
		typedef IfcObjectReferenceSelectType IfcObjectReferenceSelect;
		typedef IfcObjectTypeEnumType IfcObjectTypeEnum;
		typedef IfcOccupantType IfcOccupant;
		typedef IfcOccupantTypeEnumType IfcOccupantTypeEnum;
		typedef IfcOffsetCurve2DType IfcOffsetCurve2D;
		typedef IfcOffsetCurve3DType IfcOffsetCurve3D;
		typedef IfcOneDirectionRepeatFactorType IfcOneDirectionRepeatFactor;
		typedef IfcOpeningElementType IfcOpeningElement;
		typedef IfcOpenShellType IfcOpenShell;
		typedef IfcOpticalMaterialPropertiesType IfcOpticalMaterialProperties;
		typedef IfcOrderActionType IfcOrderAction;
		typedef IfcOrganizationType IfcOrganization;
		typedef IfcOrganizationRelationshipType IfcOrganizationRelationship;
		typedef IfcOrientationSelectType IfcOrientationSelect;
		typedef IfcOrientedEdgeType IfcOrientedEdge;
		typedef IfcOutletTypeType IfcOutletType;
		typedef IfcOutletTypeEnumType IfcOutletTypeEnum;
		typedef IfcOwnerHistoryType IfcOwnerHistory;
		typedef IfcParameterizedProfileDefType IfcParameterizedProfileDef;
		typedef IfcParameterValueType IfcParameterValue;
		typedef IfcPathType IfcPath;
		typedef IfcPerformanceHistoryType IfcPerformanceHistory;
		typedef IfcPermeableCoveringOperationEnumType IfcPermeableCoveringOperationEnum;
		typedef IfcPermeableCoveringPropertiesType IfcPermeableCoveringProperties;
		typedef IfcPermitType IfcPermit;
		typedef IfcPersonType IfcPerson;
		typedef IfcPersonAndOrganizationType IfcPersonAndOrganization;
		typedef IfcPHMeasureType IfcPHMeasure;
		typedef IfcPhysicalComplexQuantityType IfcPhysicalComplexQuantity;
		typedef IfcPhysicalOrVirtualEnumType IfcPhysicalOrVirtualEnum;
		typedef IfcPhysicalQuantityType IfcPhysicalQuantity;
		typedef IfcPhysicalSimpleQuantityType IfcPhysicalSimpleQuantity;
		typedef IfcPileType IfcPile;
		typedef IfcPileConstructionEnumType IfcPileConstructionEnum;
		typedef IfcPileTypeEnumType IfcPileTypeEnum;
		typedef IfcPipeFittingTypeType IfcPipeFittingType;
		typedef IfcPipeFittingTypeEnumType IfcPipeFittingTypeEnum;
		typedef IfcPipeSegmentTypeType IfcPipeSegmentType;
		typedef IfcPipeSegmentTypeEnumType IfcPipeSegmentTypeEnum;
		typedef IfcPixelTextureType IfcPixelTexture;
		typedef IfcPlacementType IfcPlacement;
		typedef IfcPlanarBoxType IfcPlanarBox;
		typedef IfcPlanarExtentType IfcPlanarExtent;
		typedef IfcPlanarForceMeasureType IfcPlanarForceMeasure;
		typedef IfcPlaneType IfcPlane;
		typedef IfcPlaneAngleMeasureType IfcPlaneAngleMeasure;
		typedef IfcPlateType IfcPlate;
		typedef IfcPlateTypeType IfcPlateType;
		typedef IfcPlateTypeEnumType IfcPlateTypeEnum;
		typedef IfcPointType IfcPoint;
		typedef IfcPointOnCurveType IfcPointOnCurve;
		typedef IfcPointOnSurfaceType IfcPointOnSurface;
		typedef IfcPointOrVertexPointType IfcPointOrVertexPoint;
		typedef IfcPolygonalBoundedHalfSpaceType IfcPolygonalBoundedHalfSpace;
		typedef IfcPolylineType IfcPolyline;
		typedef IfcPolyLoopType IfcPolyLoop;
		typedef IfcPortType IfcPort;
		typedef IfcPositiveLengthMeasureType IfcPositiveLengthMeasure;
		typedef IfcPositivePlaneAngleMeasureType IfcPositivePlaneAngleMeasure;
		typedef IfcPositiveRatioMeasureType IfcPositiveRatioMeasure;
		typedef IfcPostalAddressType IfcPostalAddress;
		typedef IfcPowerMeasureType IfcPowerMeasure;
		typedef IfcPreDefinedColourType IfcPreDefinedColour;
		typedef IfcPreDefinedCurveFontType IfcPreDefinedCurveFont;
		typedef IfcPreDefinedDimensionSymbolType IfcPreDefinedDimensionSymbol;
		typedef IfcPreDefinedItemType IfcPreDefinedItem;
		typedef IfcPreDefinedPointMarkerSymbolType IfcPreDefinedPointMarkerSymbol;
		typedef IfcPreDefinedSymbolType IfcPreDefinedSymbol;
		typedef IfcPreDefinedTerminatorSymbolType IfcPreDefinedTerminatorSymbol;
		typedef IfcPreDefinedTextFontType IfcPreDefinedTextFont;
		typedef IfcPresentableTextType IfcPresentableText;
		typedef IfcPresentationLayerAssignmentType IfcPresentationLayerAssignment;
		typedef IfcPresentationLayerWithStyleType IfcPresentationLayerWithStyle;
		typedef IfcPresentationStyleType IfcPresentationStyle;
		typedef IfcPresentationStyleAssignmentType IfcPresentationStyleAssignment;
		typedef IfcPresentationStyleSelectType IfcPresentationStyleSelect;
		typedef IfcPressureMeasureType IfcPressureMeasure;
		typedef IfcProcedureType IfcProcedure;
		typedef IfcProcedureTypeEnumType IfcProcedureTypeEnum;
		typedef IfcProcessType IfcProcess;
		typedef IfcProductType IfcProduct;
		typedef IfcProductDefinitionShapeType IfcProductDefinitionShape;
		typedef IfcProductRepresentationType IfcProductRepresentation;
		typedef IfcProductsOfCombustionPropertiesType IfcProductsOfCombustionProperties;
		typedef IfcProfileDefType IfcProfileDef;
		typedef IfcProfilePropertiesType IfcProfileProperties;
		typedef IfcProfileTypeEnumType IfcProfileTypeEnum;
		typedef IfcProjectType IfcProject;
		typedef IfcProjectedOrTrueLengthEnumType IfcProjectedOrTrueLengthEnum;
		typedef IfcProjectionCurveType IfcProjectionCurve;
		typedef IfcProjectionElementType IfcProjectionElement;
		typedef IfcProjectOrderType IfcProjectOrder;
		typedef IfcProjectOrderRecordType IfcProjectOrderRecord;
		typedef IfcProjectOrderRecordTypeEnumType IfcProjectOrderRecordTypeEnum;
		typedef IfcProjectOrderTypeEnumType IfcProjectOrderTypeEnum;
		typedef IfcPropertyType IfcProperty;
		typedef IfcPropertyBoundedValueType IfcPropertyBoundedValue;
		typedef IfcPropertyConstraintRelationshipType IfcPropertyConstraintRelationship;
		typedef IfcPropertyDefinitionType IfcPropertyDefinition;
		typedef IfcPropertyDependencyRelationshipType IfcPropertyDependencyRelationship;
		typedef IfcPropertyEnumeratedValueType IfcPropertyEnumeratedValue;
		typedef IfcPropertyEnumerationType IfcPropertyEnumeration;
		typedef IfcPropertyListValueType IfcPropertyListValue;
		typedef IfcPropertyReferenceValueType IfcPropertyReferenceValue;
		typedef IfcPropertySetType IfcPropertySet;
		typedef IfcPropertySetDefinitionType IfcPropertySetDefinition;
		typedef IfcPropertySingleValueType IfcPropertySingleValue;
		typedef IfcPropertySourceEnumType IfcPropertySourceEnum;
		typedef IfcPropertyTableValueType IfcPropertyTableValue;
		typedef IfcProtectiveDeviceTypeType IfcProtectiveDeviceType;
		typedef IfcProtectiveDeviceTypeEnumType IfcProtectiveDeviceTypeEnum;
		typedef IfcProxyType IfcProxy;
		typedef IfcPumpTypeType IfcPumpType;
		typedef IfcPumpTypeEnumType IfcPumpTypeEnum;
		typedef IfcQuantityAreaType IfcQuantityArea;
		typedef IfcQuantityCountType IfcQuantityCount;
		typedef IfcQuantityLengthType IfcQuantityLength;
		typedef IfcQuantityTimeType IfcQuantityTime;
		typedef IfcQuantityVolumeType IfcQuantityVolume;
		typedef IfcQuantityWeightType IfcQuantityWeight;
		typedef IfcRadioActivityMeasureType IfcRadioActivityMeasure;
		typedef IfcRadiusDimensionType IfcRadiusDimension;
		typedef IfcRailingType IfcRailing;
		typedef IfcRailingTypeType IfcRailingType;
		typedef IfcRailingTypeEnumType IfcRailingTypeEnum;
		typedef IfcRampType IfcRamp;
		typedef IfcRampFlightType IfcRampFlight;
		typedef IfcRampFlightTypeType IfcRampFlightType;
		typedef IfcRampFlightTypeEnumType IfcRampFlightTypeEnum;
		typedef IfcRampTypeEnumType IfcRampTypeEnum;
		typedef IfcRatioMeasureType IfcRatioMeasure;
		typedef IfcRationalBezierCurveType IfcRationalBezierCurve;
		typedef IfcRealType IfcReal;
		typedef IfcRectangleHollowProfileDefType IfcRectangleHollowProfileDef;
		typedef IfcRectangleProfileDefType IfcRectangleProfileDef;
		typedef IfcRectangularPyramidType IfcRectangularPyramid;
		typedef IfcRectangularTrimmedSurfaceType IfcRectangularTrimmedSurface;
		typedef IfcReferencesValueDocumentType IfcReferencesValueDocument;
		typedef IfcReflectanceMethodEnumType IfcReflectanceMethodEnum;
		typedef IfcRegularTimeSeriesType IfcRegularTimeSeries;
		typedef IfcReinforcementBarPropertiesType IfcReinforcementBarProperties;
		typedef IfcReinforcementDefinitionPropertiesType IfcReinforcementDefinitionProperties;
		typedef IfcReinforcingBarType IfcReinforcingBar;
		typedef IfcReinforcingBarRoleEnumType IfcReinforcingBarRoleEnum;
		typedef IfcReinforcingBarSurfaceEnumType IfcReinforcingBarSurfaceEnum;
		typedef IfcReinforcingElementType IfcReinforcingElement;
		typedef IfcReinforcingMeshType IfcReinforcingMesh;
		typedef IfcRelAggregatesType IfcRelAggregates;
		typedef IfcRelAssignsType IfcRelAssigns;
		typedef IfcRelAssignsTasksType IfcRelAssignsTasks;
		typedef IfcRelAssignsToActorType IfcRelAssignsToActor;
		typedef IfcRelAssignsToControlType IfcRelAssignsToControl;
		typedef IfcRelAssignsToGroupType IfcRelAssignsToGroup;
		typedef IfcRelAssignsToProcessType IfcRelAssignsToProcess;
		typedef IfcRelAssignsToProductType IfcRelAssignsToProduct;
		typedef IfcRelAssignsToProjectOrderType IfcRelAssignsToProjectOrder;
		typedef IfcRelAssignsToResourceType IfcRelAssignsToResource;
		typedef IfcRelAssociatesType IfcRelAssociates;
		typedef IfcRelAssociatesAppliedValueType IfcRelAssociatesAppliedValue;
		typedef IfcRelAssociatesApprovalType IfcRelAssociatesApproval;
		typedef IfcRelAssociatesClassificationType IfcRelAssociatesClassification;
		typedef IfcRelAssociatesConstraintType IfcRelAssociatesConstraint;
		typedef IfcRelAssociatesDocumentType IfcRelAssociatesDocument;
		typedef IfcRelAssociatesLibraryType IfcRelAssociatesLibrary;
		typedef IfcRelAssociatesMaterialType IfcRelAssociatesMaterial;
		typedef IfcRelAssociatesProfilePropertiesType IfcRelAssociatesProfileProperties;
		typedef IfcRelationshipType IfcRelationship;
		typedef IfcRelaxationType IfcRelaxation;
		typedef IfcRelConnectsType IfcRelConnects;
		typedef IfcRelConnectsElementsType IfcRelConnectsElements;
		typedef IfcRelConnectsPathElementsType IfcRelConnectsPathElements;
		typedef IfcRelConnectsPortsType IfcRelConnectsPorts;
		typedef IfcRelConnectsPortToElementType IfcRelConnectsPortToElement;
		typedef IfcRelConnectsStructuralActivityType IfcRelConnectsStructuralActivity;
		typedef IfcRelConnectsStructuralElementType IfcRelConnectsStructuralElement;
		typedef IfcRelConnectsStructuralMemberType IfcRelConnectsStructuralMember;
		typedef IfcRelConnectsWithEccentricityType IfcRelConnectsWithEccentricity;
		typedef IfcRelConnectsWithRealizingElementsType IfcRelConnectsWithRealizingElements;
		typedef IfcRelContainedInSpatialStructureType IfcRelContainedInSpatialStructure;
		typedef IfcRelCoversBldgElementsType IfcRelCoversBldgElements;
		typedef IfcRelCoversSpacesType IfcRelCoversSpaces;
		typedef IfcRelDecomposesType IfcRelDecomposes;
		typedef IfcRelDefinesType IfcRelDefines;
		typedef IfcRelDefinesByPropertiesType IfcRelDefinesByProperties;
		typedef IfcRelDefinesByTypeType IfcRelDefinesByType;
		typedef IfcRelFillsElementType IfcRelFillsElement;
		typedef IfcRelFlowControlElementsType IfcRelFlowControlElements;
		typedef IfcRelInteractionRequirementsType IfcRelInteractionRequirements;
		typedef IfcRelNestsType IfcRelNests;
		typedef IfcRelOccupiesSpacesType IfcRelOccupiesSpaces;
		typedef IfcRelOverridesPropertiesType IfcRelOverridesProperties;
		typedef IfcRelProjectsElementType IfcRelProjectsElement;
		typedef IfcRelReferencedInSpatialStructureType IfcRelReferencedInSpatialStructure;
		typedef IfcRelSchedulesCostItemsType IfcRelSchedulesCostItems;
		typedef IfcRelSequenceType IfcRelSequence;
		typedef IfcRelServicesBuildingsType IfcRelServicesBuildings;
		typedef IfcRelSpaceBoundaryType IfcRelSpaceBoundary;
		typedef IfcRelVoidsElementType IfcRelVoidsElement;
		typedef IfcRepresentationType IfcRepresentation;
		typedef IfcRepresentationContextType IfcRepresentationContext;
		typedef IfcRepresentationItemType IfcRepresentationItem;
		typedef IfcRepresentationMapType IfcRepresentationMap;
		typedef IfcResourceType IfcResource;
		typedef IfcResourceConsumptionEnumType IfcResourceConsumptionEnum;
		typedef IfcRevolvedAreaSolidType IfcRevolvedAreaSolid;
		typedef IfcRibPlateDirectionEnumType IfcRibPlateDirectionEnum;
		typedef IfcRibPlateProfilePropertiesType IfcRibPlateProfileProperties;
		typedef IfcRightCircularConeType IfcRightCircularCone;
		typedef IfcRightCircularCylinderType IfcRightCircularCylinder;
		typedef IfcRoleEnumType IfcRoleEnum;
		typedef IfcRoofType IfcRoof;
		typedef IfcRoofTypeEnumType IfcRoofTypeEnum;
		typedef IfcRootType IfcRoot;
		typedef IfcRotationalFrequencyMeasureType IfcRotationalFrequencyMeasure;
		typedef IfcRotationalMassMeasureType IfcRotationalMassMeasure;
		typedef IfcRotationalStiffnessMeasureType IfcRotationalStiffnessMeasure;
		typedef IfcRoundedEdgeFeatureType IfcRoundedEdgeFeature;
		typedef IfcRoundedRectangleProfileDefType IfcRoundedRectangleProfileDef;
		typedef IfcSanitaryTerminalTypeType IfcSanitaryTerminalType;
		typedef IfcSanitaryTerminalTypeEnumType IfcSanitaryTerminalTypeEnum;
		typedef IfcScheduleTimeControlType IfcScheduleTimeControl;
		typedef IfcSecondInMinuteType IfcSecondInMinute;
		typedef IfcSectionalAreaIntegralMeasureType IfcSectionalAreaIntegralMeasure;
		typedef IfcSectionedSpineType IfcSectionedSpine;
		typedef IfcSectionModulusMeasureType IfcSectionModulusMeasure;
		typedef IfcSectionPropertiesType IfcSectionProperties;
		typedef IfcSectionReinforcementPropertiesType IfcSectionReinforcementProperties;
		typedef IfcSectionTypeEnumType IfcSectionTypeEnum;
		typedef IfcSensorTypeType IfcSensorType;
		typedef IfcSensorTypeEnumType IfcSensorTypeEnum;
		typedef IfcSequenceEnumType IfcSequenceEnum;
		typedef IfcServiceLifeType IfcServiceLife;
		typedef IfcServiceLifeFactorType IfcServiceLifeFactor;
		typedef IfcServiceLifeFactorTypeEnumType IfcServiceLifeFactorTypeEnum;
		typedef IfcServiceLifeTypeEnumType IfcServiceLifeTypeEnum;
		typedef IfcShapeAspectType IfcShapeAspect;
		typedef IfcShapeModelType IfcShapeModel;
		typedef IfcShapeRepresentationType IfcShapeRepresentation;
		typedef IfcShearModulusMeasureType IfcShearModulusMeasure;
		typedef IfcShellType IfcShell;
		typedef IfcShellBasedSurfaceModelType IfcShellBasedSurfaceModel;
		typedef IfcSimplePropertyType IfcSimpleProperty;
		typedef IfcSimpleValueType IfcSimpleValue;
		typedef IfcSIPrefixType IfcSIPrefix;
		typedef IfcSiteType IfcSite;
		typedef IfcSIUnitType IfcSIUnit;
		typedef IfcSIUnitNameType IfcSIUnitName;
		typedef IfcSizeSelectType IfcSizeSelect;
		typedef IfcSlabType IfcSlab;
		typedef IfcSlabTypeType IfcSlabType;
		typedef IfcSlabTypeEnumType IfcSlabTypeEnum;
		typedef IfcSlippageConnectionConditionType IfcSlippageConnectionCondition;
		typedef IfcSolidAngleMeasureType IfcSolidAngleMeasure;
		typedef IfcSolidModelType IfcSolidModel;
		typedef IfcSoundPowerMeasureType IfcSoundPowerMeasure;
		typedef IfcSoundPressureMeasureType IfcSoundPressureMeasure;
		typedef IfcSoundPropertiesType IfcSoundProperties;
		typedef IfcSoundScaleEnumType IfcSoundScaleEnum;
		typedef IfcSoundValueType IfcSoundValue;
		typedef IfcSpaceType IfcSpace;
		typedef IfcSpaceHeaterTypeType IfcSpaceHeaterType;
		typedef IfcSpaceHeaterTypeEnumType IfcSpaceHeaterTypeEnum;
		typedef IfcSpaceProgramType IfcSpaceProgram;
		typedef IfcSpaceThermalLoadPropertiesType IfcSpaceThermalLoadProperties;
		typedef IfcSpaceTypeType IfcSpaceType;
		typedef IfcSpaceTypeEnumType IfcSpaceTypeEnum;
		typedef IfcSpatialStructureElementType IfcSpatialStructureElement;
		typedef IfcSpatialStructureElementTypeType IfcSpatialStructureElementType;
		typedef IfcSpecificHeatCapacityMeasureType IfcSpecificHeatCapacityMeasure;
		typedef IfcSpecularExponentType IfcSpecularExponent;
		typedef IfcSpecularHighlightSelectType IfcSpecularHighlightSelect;
		typedef IfcSpecularRoughnessType IfcSpecularRoughness;
		typedef IfcSphereType IfcSphere;
		typedef IfcStackTerminalTypeType IfcStackTerminalType;
		typedef IfcStackTerminalTypeEnumType IfcStackTerminalTypeEnum;
		typedef IfcStairType IfcStair;
		typedef IfcStairFlightType IfcStairFlight;
		typedef IfcStairFlightTypeType IfcStairFlightType;
		typedef IfcStairFlightTypeEnumType IfcStairFlightTypeEnum;
		typedef IfcStairTypeEnumType IfcStairTypeEnum;
		typedef IfcStateEnumType IfcStateEnum;
		typedef IfcStructuralActionType IfcStructuralAction;
		typedef IfcStructuralActivityType IfcStructuralActivity;
		typedef IfcStructuralActivityAssignmentSelectType IfcStructuralActivityAssignmentSelect;
		typedef IfcStructuralAnalysisModelType IfcStructuralAnalysisModel;
		typedef IfcStructuralConnectionType IfcStructuralConnection;
		typedef IfcStructuralConnectionConditionType IfcStructuralConnectionCondition;
		typedef IfcStructuralCurveConnectionType IfcStructuralCurveConnection;
		typedef IfcStructuralCurveMemberType IfcStructuralCurveMember;
		typedef IfcStructuralCurveMemberVaryingType IfcStructuralCurveMemberVarying;
		typedef IfcStructuralCurveTypeEnumType IfcStructuralCurveTypeEnum;
		typedef IfcStructuralItemType IfcStructuralItem;
		typedef IfcStructuralLinearActionType IfcStructuralLinearAction;
		typedef IfcStructuralLinearActionVaryingType IfcStructuralLinearActionVarying;
		typedef IfcStructuralLoadType IfcStructuralLoad;
		typedef IfcStructuralLoadGroupType IfcStructuralLoadGroup;
		typedef IfcStructuralLoadLinearForceType IfcStructuralLoadLinearForce;
		typedef IfcStructuralLoadPlanarForceType IfcStructuralLoadPlanarForce;
		typedef IfcStructuralLoadSingleDisplacementType IfcStructuralLoadSingleDisplacement;
		typedef IfcStructuralLoadSingleDisplacementDistortionType IfcStructuralLoadSingleDisplacementDistortion;
		typedef IfcStructuralLoadSingleForceType IfcStructuralLoadSingleForce;
		typedef IfcStructuralLoadSingleForceWarpingType IfcStructuralLoadSingleForceWarping;
		typedef IfcStructuralLoadStaticType IfcStructuralLoadStatic;
		typedef IfcStructuralLoadTemperatureType IfcStructuralLoadTemperature;
		typedef IfcStructuralMemberType IfcStructuralMember;
		typedef IfcStructuralPlanarActionType IfcStructuralPlanarAction;
		typedef IfcStructuralPlanarActionVaryingType IfcStructuralPlanarActionVarying;
		typedef IfcStructuralPointActionType IfcStructuralPointAction;
		typedef IfcStructuralPointConnectionType IfcStructuralPointConnection;
		typedef IfcStructuralPointReactionType IfcStructuralPointReaction;
		typedef IfcStructuralProfilePropertiesType IfcStructuralProfileProperties;
		typedef IfcStructuralReactionType IfcStructuralReaction;
		typedef IfcStructuralResultGroupType IfcStructuralResultGroup;
		typedef IfcStructuralSteelProfilePropertiesType IfcStructuralSteelProfileProperties;
		typedef IfcStructuralSurfaceConnectionType IfcStructuralSurfaceConnection;
		typedef IfcStructuralSurfaceMemberType IfcStructuralSurfaceMember;
		typedef IfcStructuralSurfaceMemberVaryingType IfcStructuralSurfaceMemberVarying;
		typedef IfcStructuralSurfaceTypeEnumType IfcStructuralSurfaceTypeEnum;
		typedef IfcStructuredDimensionCalloutType IfcStructuredDimensionCallout;
		typedef IfcStyledItemType IfcStyledItem;
		typedef IfcStyledRepresentationType IfcStyledRepresentation;
		typedef IfcStyleModelType IfcStyleModel;
		typedef IfcSubContractResourceType IfcSubContractResource;
		typedef IfcSubedgeType IfcSubedge;
		typedef IfcSurfaceType IfcSurface;
		typedef IfcSurfaceCurveSweptAreaSolidType IfcSurfaceCurveSweptAreaSolid;
		typedef IfcSurfaceOfLinearExtrusionType IfcSurfaceOfLinearExtrusion;
		typedef IfcSurfaceOfRevolutionType IfcSurfaceOfRevolution;
		typedef IfcSurfaceOrFaceSurfaceType IfcSurfaceOrFaceSurface;
		typedef IfcSurfaceSideType IfcSurfaceSide;
		typedef IfcSurfaceStyleType IfcSurfaceStyle;
		typedef IfcSurfaceStyleElementSelectType IfcSurfaceStyleElementSelect;
		typedef IfcSurfaceStyleLightingType IfcSurfaceStyleLighting;
		typedef IfcSurfaceStyleRefractionType IfcSurfaceStyleRefraction;
		typedef IfcSurfaceStyleRenderingType IfcSurfaceStyleRendering;
		typedef IfcSurfaceStyleShadingType IfcSurfaceStyleShading;
		typedef IfcSurfaceStyleWithTexturesType IfcSurfaceStyleWithTextures;
		typedef IfcSurfaceTextureType IfcSurfaceTexture;
		typedef IfcSurfaceTextureEnumType IfcSurfaceTextureEnum;
		typedef IfcSweptAreaSolidType IfcSweptAreaSolid;
		typedef IfcSweptDiskSolidType IfcSweptDiskSolid;
		typedef IfcSweptSurfaceType IfcSweptSurface;
		typedef IfcSwitchingDeviceTypeType IfcSwitchingDeviceType;
		typedef IfcSwitchingDeviceTypeEnumType IfcSwitchingDeviceTypeEnum;
		typedef IfcSymbolStyleType IfcSymbolStyle;
		typedef IfcSymbolStyleSelectType IfcSymbolStyleSelect;
		typedef IfcSystemType IfcSystem;
		typedef IfcSystemFurnitureElementTypeType IfcSystemFurnitureElementType;
		typedef IfcTableType IfcTable;
		typedef IfcTableRowType IfcTableRow;
		typedef IfcTankTypeType IfcTankType;
		typedef IfcTankTypeEnumType IfcTankTypeEnum;
		typedef IfcTaskType IfcTask;
		typedef IfcTelecomAddressType IfcTelecomAddress;
		typedef IfcTemperatureGradientMeasureType IfcTemperatureGradientMeasure;
		typedef IfcTendonType IfcTendon;
		typedef IfcTendonAnchorType IfcTendonAnchor;
		typedef IfcTendonTypeEnumType IfcTendonTypeEnum;
		typedef IfcTerminatorSymbolType IfcTerminatorSymbol;
		typedef IfcTextType IfcText;
		typedef IfcTextAlignmentType IfcTextAlignment;
		typedef IfcTextDecorationType IfcTextDecoration;
		typedef IfcTextFontNameType IfcTextFontName;
		typedef IfcTextFontSelectType IfcTextFontSelect;
		typedef IfcTextLiteralType IfcTextLiteral;
		typedef IfcTextLiteralWithExtentType IfcTextLiteralWithExtent;
		typedef IfcTextPathType IfcTextPath;
		typedef IfcTextStyleType IfcTextStyle;
		typedef IfcTextStyleFontModelType IfcTextStyleFontModel;
		typedef IfcTextStyleForDefinedFontType IfcTextStyleForDefinedFont;
		typedef IfcTextStyleSelectType IfcTextStyleSelect;
		typedef IfcTextStyleTextModelType IfcTextStyleTextModel;
		typedef IfcTextStyleWithBoxCharacteristicsType IfcTextStyleWithBoxCharacteristics;
		typedef IfcTextTransformationType IfcTextTransformation;
		typedef IfcTextureCoordinateType IfcTextureCoordinate;
		typedef IfcTextureCoordinateGeneratorType IfcTextureCoordinateGenerator;
		typedef IfcTextureMapType IfcTextureMap;
		typedef IfcTextureVertexType IfcTextureVertex;
		typedef IfcThermalAdmittanceMeasureType IfcThermalAdmittanceMeasure;
		typedef IfcThermalConductivityMeasureType IfcThermalConductivityMeasure;
		typedef IfcThermalExpansionCoefficientMeasureType IfcThermalExpansionCoefficientMeasure;
		typedef IfcThermalLoadSourceEnumType IfcThermalLoadSourceEnum;
		typedef IfcThermalLoadTypeEnumType IfcThermalLoadTypeEnum;
		typedef IfcThermalMaterialPropertiesType IfcThermalMaterialProperties;
		typedef IfcThermalResistanceMeasureType IfcThermalResistanceMeasure;
		typedef IfcThermalTransmittanceMeasureType IfcThermalTransmittanceMeasure;
		typedef IfcThermodynamicTemperatureMeasureType IfcThermodynamicTemperatureMeasure;
		typedef IfcTimeMeasureType IfcTimeMeasure;
		typedef IfcTimeSeriesType IfcTimeSeries;
		typedef IfcTimeSeriesDataTypeEnumType IfcTimeSeriesDataTypeEnum;
		typedef IfcTimeSeriesReferenceRelationshipType IfcTimeSeriesReferenceRelationship;
		typedef IfcTimeSeriesScheduleType IfcTimeSeriesSchedule;
		typedef IfcTimeSeriesScheduleTypeEnumType IfcTimeSeriesScheduleTypeEnum;
		typedef IfcTimeSeriesValueType IfcTimeSeriesValue;
		typedef IfcTimeStampType IfcTimeStamp;
		typedef IfcTopologicalRepresentationItemType IfcTopologicalRepresentationItem;
		typedef IfcTopologyRepresentationType IfcTopologyRepresentation;
		typedef IfcTorqueMeasureType IfcTorqueMeasure;
		typedef IfcTransformerTypeType IfcTransformerType;
		typedef IfcTransformerTypeEnumType IfcTransformerTypeEnum;
		typedef IfcTransitionCodeType IfcTransitionCode;
		typedef IfcTransportElementType IfcTransportElement;
		typedef IfcTransportElementTypeType IfcTransportElementType;
		typedef IfcTransportElementTypeEnumType IfcTransportElementTypeEnum;
		typedef IfcTrapeziumProfileDefType IfcTrapeziumProfileDef;
		typedef IfcTrimmedCurveType IfcTrimmedCurve;
		typedef IfcTrimmingPreferenceType IfcTrimmingPreference;
		typedef IfcTrimmingSelectType IfcTrimmingSelect;
		typedef IfcTShapeProfileDefType IfcTShapeProfileDef;
		typedef IfcTubeBundleTypeType IfcTubeBundleType;
		typedef IfcTubeBundleTypeEnumType IfcTubeBundleTypeEnum;
		typedef IfcTwoDirectionRepeatFactorType IfcTwoDirectionRepeatFactor;
		typedef IfcTypeObjectType IfcTypeObject;
		typedef IfcTypeProductType IfcTypeProduct;
		typedef IfcUnitType IfcUnit;
		typedef IfcUnitaryEquipmentTypeType IfcUnitaryEquipmentType;
		typedef IfcUnitaryEquipmentTypeEnumType IfcUnitaryEquipmentTypeEnum;
		typedef IfcUnitAssignmentType IfcUnitAssignment;
		typedef IfcUnitEnumType IfcUnitEnum;
		typedef IfcUShapeProfileDefType IfcUShapeProfileDef;
		typedef IfcValueType IfcValue;
		typedef IfcValveTypeType IfcValveType;
		typedef IfcValveTypeEnumType IfcValveTypeEnum;
		typedef IfcVaporPermeabilityMeasureType IfcVaporPermeabilityMeasure;
		typedef IfcVectorType IfcVector;
		typedef IfcVectorOrDirectionType IfcVectorOrDirection;
		typedef IfcVertexType IfcVertex;
		typedef IfcVertexBasedTextureMapType IfcVertexBasedTextureMap;
		typedef IfcVertexLoopType IfcVertexLoop;
		typedef IfcVertexPointType IfcVertexPoint;
		typedef IfcVibrationIsolatorTypeType IfcVibrationIsolatorType;
		typedef IfcVibrationIsolatorTypeEnumType IfcVibrationIsolatorTypeEnum;
		typedef IfcVirtualElementType IfcVirtualElement;
		typedef IfcVirtualGridIntersectionType IfcVirtualGridIntersection;
		typedef IfcVolumeMeasureType IfcVolumeMeasure;
		typedef IfcVolumetricFlowRateMeasureType IfcVolumetricFlowRateMeasure;
		typedef IfcWallType IfcWall;
		typedef IfcWallStandardCaseType IfcWallStandardCase;
		typedef IfcWallTypeType IfcWallType;
		typedef IfcWallTypeEnumType IfcWallTypeEnum;
		typedef IfcWarpingConstantMeasureType IfcWarpingConstantMeasure;
		typedef IfcWarpingMomentMeasureType IfcWarpingMomentMeasure;
		typedef IfcWasteTerminalTypeType IfcWasteTerminalType;
		typedef IfcWasteTerminalTypeEnumType IfcWasteTerminalTypeEnum;
		typedef IfcWaterPropertiesType IfcWaterProperties;
		typedef IfcWindowType IfcWindow;
		typedef IfcWindowLiningPropertiesType IfcWindowLiningProperties;
		typedef IfcWindowPanelOperationEnumType IfcWindowPanelOperationEnum;
		typedef IfcWindowPanelPositionEnumType IfcWindowPanelPositionEnum;
		typedef IfcWindowPanelPropertiesType IfcWindowPanelProperties;
		typedef IfcWindowStyleType IfcWindowStyle;
		typedef IfcWindowStyleConstructionEnumType IfcWindowStyleConstructionEnum;
		typedef IfcWindowStyleOperationEnumType IfcWindowStyleOperationEnum;
		typedef IfcWorkControlType IfcWorkControl;
		typedef IfcWorkControlTypeEnumType IfcWorkControlTypeEnum;
		typedef IfcWorkPlanType IfcWorkPlan;
		typedef IfcWorkScheduleType IfcWorkSchedule;
		typedef IfcYearNumberType IfcYearNumber;
		typedef IfcZoneType IfcZone;
		typedef IfcZShapeProfileDefType IfcZShapeProfileDef;
	};
}
