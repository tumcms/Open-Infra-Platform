#pragma once

#include "EMTIfcEntityTypes.h"

namespace BlueFramework
{
	namespace Ifc2x3
	{
		class IfcAbsorbedDoseMeasure;
		class IfcAccelerationMeasure;
		class IfcActionRequest;
		class IfcActionSourceTypeEnum;
		class IfcActionTypeEnum;
		class IfcActor;
		class IfcActorRole;
		class IfcActorSelect;
		class IfcActuatorType;
		class IfcActuatorTypeEnum;
		class IfcAddress;
		class IfcAddressTypeEnum;
		class IfcAheadOrBehind;
		class IfcAirTerminalBoxType;
		class IfcAirTerminalBoxTypeEnum;
		class IfcAirTerminalType;
		class IfcAirTerminalTypeEnum;
		class IfcAirToAirHeatRecoveryType;
		class IfcAirToAirHeatRecoveryTypeEnum;
		class IfcAlarmType;
		class IfcAlarmTypeEnum;
		class IfcAmountOfSubstanceMeasure;
		class IfcAnalysisModelTypeEnum;
		class IfcAnalysisTheoryTypeEnum;
		class IfcAngularDimension;
		class IfcAngularVelocityMeasure;
		class IfcAnnotation;
		class IfcAnnotationCurveOccurrence;
		class IfcAnnotationFillArea;
		class IfcAnnotationFillAreaOccurrence;
		class IfcAnnotationOccurrence;
		class IfcAnnotationSurface;
		class IfcAnnotationSurfaceOccurrence;
		class IfcAnnotationSymbolOccurrence;
		class IfcAnnotationTextOccurrence;
		class IfcApplication;
		class IfcAppliedValue;
		class IfcAppliedValueRelationship;
		class IfcAppliedValueSelect;
		class IfcApproval;
		class IfcApprovalActorRelationship;
		class IfcApprovalPropertyRelationship;
		class IfcApprovalRelationship;
		class IfcArbitraryClosedProfileDef;
		class IfcArbitraryOpenProfileDef;
		class IfcArbitraryProfileDefWithVoids;
		class IfcAreaMeasure;
		class IfcArithmeticOperatorEnum;
		class IfcAssemblyPlaceEnum;
		class IfcAsset;
		class IfcAsymmetricIShapeProfileDef;
		class IfcAxis1Placement;
		class IfcAxis2Placement;
		class IfcAxis2Placement2D;
		class IfcAxis2Placement3D;
		class IfcBeam;
		class IfcBeamType;
		class IfcBeamTypeEnum;
		class IfcBenchmarkEnum;
		class IfcBezierCurve;
		class IfcBlobTexture;
		class IfcBlock;
		class IfcBoilerType;
		class IfcBoilerTypeEnum;
		class IfcBoolean;
		class IfcBooleanClippingResult;
		class IfcBooleanOperand;
		class IfcBooleanOperator;
		class IfcBooleanResult;
		class IfcBoundaryCondition;
		class IfcBoundaryEdgeCondition;
		class IfcBoundaryFaceCondition;
		class IfcBoundaryNodeCondition;
		class IfcBoundaryNodeConditionWarping;
		class IfcBoundedCurve;
		class IfcBoundedSurface;
		class IfcBoundingBox;
		class IfcBoxAlignment;
		class IfcBoxedHalfSpace;
		class IfcBSplineCurve;
		class IfcBSplineCurveForm;
		class IfcBuilding;
		class IfcBuildingElement;
		class IfcBuildingElementComponent;
		class IfcBuildingElementPart;
		class IfcBuildingElementProxy;
		class IfcBuildingElementProxyType;
		class IfcBuildingElementProxyTypeEnum;
		class IfcBuildingElementType;
		class IfcBuildingStorey;
		class IfcCableCarrierFittingType;
		class IfcCableCarrierFittingTypeEnum;
		class IfcCableCarrierSegmentType;
		class IfcCableCarrierSegmentTypeEnum;
		class IfcCableSegmentType;
		class IfcCableSegmentTypeEnum;
		class IfcCalendarDate;
		class IfcCartesianPoint;
		class IfcCartesianTransformationOperator;
		class IfcCartesianTransformationOperator2D;
		class IfcCartesianTransformationOperator2DnonUniform;
		class IfcCartesianTransformationOperator3D;
		class IfcCartesianTransformationOperator3DnonUniform;
		class IfcCenterLineProfileDef;
		class IfcChamferEdgeFeature;
		class IfcChangeActionEnum;
		class IfcCharacterStyleSelect;
		class IfcChillerType;
		class IfcChillerTypeEnum;
		class IfcCircle;
		class IfcCircleHollowProfileDef;
		class IfcCircleProfileDef;
		class IfcClassification;
		class IfcClassificationItem;
		class IfcClassificationItemRelationship;
		class IfcClassificationNotation;
		class IfcClassificationNotationFacet;
		class IfcClassificationNotationSelect;
		class IfcClassificationReference;
		class IfcClosedShell;
		class IfcCoilType;
		class IfcCoilTypeEnum;
		class IfcColour;
		class IfcColourOrFactor;
		class IfcColourRgb;
		class IfcColourSpecification;
		class IfcColumn;
		class IfcColumnType;
		class IfcColumnTypeEnum;
		class IfcComplexNumber;
		class IfcComplexProperty;
		class IfcCompositeCurve;
		class IfcCompositeCurveSegment;
		class IfcCompositeProfileDef;
		class IfcCompoundPlaneAngleMeasure;
		class IfcCompressorType;
		class IfcCompressorTypeEnum;
		class IfcCondenserType;
		class IfcCondenserTypeEnum;
		class IfcCondition;
		class IfcConditionCriterion;
		class IfcConditionCriterionSelect;
		class IfcConic;
		class IfcConnectedFaceSet;
		class IfcConnectionCurveGeometry;
		class IfcConnectionGeometry;
		class IfcConnectionPointEccentricity;
		class IfcConnectionPointGeometry;
		class IfcConnectionPortGeometry;
		class IfcConnectionSurfaceGeometry;
		class IfcConnectionTypeEnum;
		class IfcConstraint;
		class IfcConstraintAggregationRelationship;
		class IfcConstraintClassificationRelationship;
		class IfcConstraintEnum;
		class IfcConstraintRelationship;
		class IfcConstructionEquipmentResource;
		class IfcConstructionMaterialResource;
		class IfcConstructionProductResource;
		class IfcConstructionResource;
		class IfcContextDependentMeasure;
		class IfcContextDependentUnit;
		class IfcControl;
		class IfcControllerType;
		class IfcControllerTypeEnum;
		class IfcConversionBasedUnit;
		class IfcCooledBeamType;
		class IfcCooledBeamTypeEnum;
		class IfcCoolingTowerType;
		class IfcCoolingTowerTypeEnum;
		class IfcCoordinatedUniversalTimeOffset;
		class IfcCostItem;
		class IfcCostSchedule;
		class IfcCostScheduleTypeEnum;
		class IfcCostValue;
		class IfcCountMeasure;
		class IfcCovering;
		class IfcCoveringType;
		class IfcCoveringTypeEnum;
		class IfcCraneRailAShapeProfileDef;
		class IfcCraneRailFShapeProfileDef;
		class IfcCrewResource;
		class IfcCsgPrimitive3D;
		class IfcCsgSelect;
		class IfcCsgSolid;
		class IfcCShapeProfileDef;
		class IfcCurrencyEnum;
		class IfcCurrencyRelationship;
		class IfcCurtainWall;
		class IfcCurtainWallType;
		class IfcCurtainWallTypeEnum;
		class IfcCurvatureMeasure;
		class IfcCurve;
		class IfcCurveBoundedPlane;
		class IfcCurveFontOrScaledCurveFontSelect;
		class IfcCurveOrEdgeCurve;
		class IfcCurveStyle;
		class IfcCurveStyleFont;
		class IfcCurveStyleFontAndScaling;
		class IfcCurveStyleFontPattern;
		class IfcCurveStyleFontSelect;
		class IfcDamperType;
		class IfcDamperTypeEnum;
		class IfcDataOriginEnum;
		class IfcDateAndTime;
		class IfcDateTimeSelect;
		class IfcDayInMonthNumber;
		class IfcDaylightSavingHour;
		class IfcDefinedSymbol;
		class IfcDefinedSymbolSelect;
		class IfcDerivedMeasureValue;
		class IfcDerivedProfileDef;
		class IfcDerivedUnit;
		class IfcDerivedUnitElement;
		class IfcDerivedUnitEnum;
		class IfcDescriptiveMeasure;
		class IfcDiameterDimension;
		class IfcDimensionalExponents;
		class IfcDimensionCalloutRelationship;
		class IfcDimensionCount;
		class IfcDimensionCurve;
		class IfcDimensionCurveDirectedCallout;
		class IfcDimensionCurveTerminator;
		class IfcDimensionExtentUsage;
		class IfcDimensionPair;
		class IfcDirection;
		class IfcDirectionSenseEnum;
		class IfcDiscreteAccessory;
		class IfcDiscreteAccessoryType;
		class IfcDistributionChamberElement;
		class IfcDistributionChamberElementType;
		class IfcDistributionChamberElementTypeEnum;
		class IfcDistributionControlElement;
		class IfcDistributionControlElementType;
		class IfcDistributionElement;
		class IfcDistributionElementType;
		class IfcDistributionFlowElement;
		class IfcDistributionFlowElementType;
		class IfcDistributionPort;
		class IfcDocumentConfidentialityEnum;
		class IfcDocumentElectronicFormat;
		class IfcDocumentInformation;
		class IfcDocumentInformationRelationship;
		class IfcDocumentReference;
		class IfcDocumentSelect;
		class IfcDocumentStatusEnum;
		class IfcDoor;
		class IfcDoorLiningProperties;
		class IfcDoorPanelOperationEnum;
		class IfcDoorPanelPositionEnum;
		class IfcDoorPanelProperties;
		class IfcDoorStyle;
		class IfcDoorStyleConstructionEnum;
		class IfcDoorStyleOperationEnum;
		class IfcDoseEquivalentMeasure;
		class IfcDraughtingCallout;
		class IfcDraughtingCalloutElement;
		class IfcDraughtingCalloutRelationship;
		class IfcDraughtingPreDefinedColour;
		class IfcDraughtingPreDefinedCurveFont;
		class IfcDraughtingPreDefinedTextFont;
		class IfcDuctFittingType;
		class IfcDuctFittingTypeEnum;
		class IfcDuctSegmentType;
		class IfcDuctSegmentTypeEnum;
		class IfcDuctSilencerType;
		class IfcDuctSilencerTypeEnum;
		class IfcDynamicViscosityMeasure;
		class IfcEdge;
		class IfcEdgeCurve;
		class IfcEdgeFeature;
		class IfcEdgeLoop;
		class IfcElectricalBaseProperties;
		class IfcElectricalCircuit;
		class IfcElectricalElement;
		class IfcElectricApplianceType;
		class IfcElectricApplianceTypeEnum;
		class IfcElectricCapacitanceMeasure;
		class IfcElectricChargeMeasure;
		class IfcElectricConductanceMeasure;
		class IfcElectricCurrentEnum;
		class IfcElectricCurrentMeasure;
		class IfcElectricDistributionPoint;
		class IfcElectricDistributionPointFunctionEnum;
		class IfcElectricFlowStorageDeviceType;
		class IfcElectricFlowStorageDeviceTypeEnum;
		class IfcElectricGeneratorType;
		class IfcElectricGeneratorTypeEnum;
		class IfcElectricHeaterType;
		class IfcElectricHeaterTypeEnum;
		class IfcElectricMotorType;
		class IfcElectricMotorTypeEnum;
		class IfcElectricResistanceMeasure;
		class IfcElectricTimeControlType;
		class IfcElectricTimeControlTypeEnum;
		class IfcElectricVoltageMeasure;
		class IfcElement;
		class IfcElementarySurface;
		class IfcElementAssembly;
		class IfcElementAssemblyTypeEnum;
		class IfcElementComponent;
		class IfcElementComponentType;
		class IfcElementCompositionEnum;
		class IfcElementQuantity;
		class IfcElementType;
		class IfcEllipse;
		class IfcEllipseProfileDef;
		class IfcEnergyConversionDevice;
		class IfcEnergyConversionDeviceType;
		class IfcEnergyMeasure;
		class IfcEnergyProperties;
		class IfcEnergySequenceEnum;
		class IfcEnvironmentalImpactCategoryEnum;
		class IfcEnvironmentalImpactValue;
		class IfcEquipmentElement;
		class IfcEquipmentStandard;
		class IfcEvaporativeCoolerType;
		class IfcEvaporativeCoolerTypeEnum;
		class IfcEvaporatorType;
		class IfcEvaporatorTypeEnum;
		class IfcExtendedMaterialProperties;
		class IfcExternallyDefinedHatchStyle;
		class IfcExternallyDefinedSurfaceStyle;
		class IfcExternallyDefinedSymbol;
		class IfcExternallyDefinedTextFont;
		class IfcExternalReference;
		class IfcExtrudedAreaSolid;
		class IfcFace;
		class IfcFaceBasedSurfaceModel;
		class IfcFaceBound;
		class IfcFaceOuterBound;
		class IfcFaceSurface;
		class IfcFacetedBrep;
		class IfcFacetedBrepWithVoids;
		class IfcFailureConnectionCondition;
		class IfcFanType;
		class IfcFanTypeEnum;
		class IfcFastener;
		class IfcFastenerType;
		class IfcFeatureElement;
		class IfcFeatureElementAddition;
		class IfcFeatureElementSubtraction;
		class IfcFillAreaStyle;
		class IfcFillAreaStyleHatching;
		class IfcFillAreaStyleTiles;
		class IfcFillAreaStyleTileShapeSelect;
		class IfcFillAreaStyleTileSymbolWithStyle;
		class IfcFillStyleSelect;
		class IfcFilterType;
		class IfcFilterTypeEnum;
		class IfcFireSuppressionTerminalType;
		class IfcFireSuppressionTerminalTypeEnum;
		class IfcFlowController;
		class IfcFlowControllerType;
		class IfcFlowDirectionEnum;
		class IfcFlowFitting;
		class IfcFlowFittingType;
		class IfcFlowInstrumentType;
		class IfcFlowInstrumentTypeEnum;
		class IfcFlowMeterType;
		class IfcFlowMeterTypeEnum;
		class IfcFlowMovingDevice;
		class IfcFlowMovingDeviceType;
		class IfcFlowSegment;
		class IfcFlowSegmentType;
		class IfcFlowStorageDevice;
		class IfcFlowStorageDeviceType;
		class IfcFlowTerminal;
		class IfcFlowTerminalType;
		class IfcFlowTreatmentDevice;
		class IfcFlowTreatmentDeviceType;
		class IfcFluidFlowProperties;
		class IfcFontStyle;
		class IfcFontVariant;
		class IfcFontWeight;
		class IfcFooting;
		class IfcFootingTypeEnum;
		class IfcForceMeasure;
		class IfcFrequencyMeasure;
		class IfcFuelProperties;
		class IfcFurnishingElement;
		class IfcFurnishingElementType;
		class IfcFurnitureStandard;
		class IfcFurnitureType;
		class IfcGasTerminalType;
		class IfcGasTerminalTypeEnum;
		class IfcGeneralMaterialProperties;
		class IfcGeneralProfileProperties;
		class IfcGeometricCurveSet;
		class IfcGeometricProjectionEnum;
		class IfcGeometricRepresentationContext;
		class IfcGeometricRepresentationItem;
		class IfcGeometricRepresentationSubContext;
		class IfcGeometricSet;
		class IfcGeometricSetSelect;
		class IfcGloballyUniqueId;
		class IfcGlobalOrLocalEnum;
		class IfcGrid;
		class IfcGridAxis;
		class IfcGridPlacement;
		class IfcGroup;
		class IfcHalfSpaceSolid;
		class IfcHatchLineDistanceSelect;
		class IfcHeatExchangerType;
		class IfcHeatExchangerTypeEnum;
		class IfcHeatFluxDensityMeasure;
		class IfcHeatingValueMeasure;
		class IfcHourInDay;
		class IfcHumidifierType;
		class IfcHumidifierTypeEnum;
		class IfcHygroscopicMaterialProperties;
		class IfcIdentifier;
		class IfcIlluminanceMeasure;
		class IfcImageTexture;
		class IfcInductanceMeasure;
		class IfcInteger;
		class IfcIntegerCountRateMeasure;
		class IfcInternalOrExternalEnum;
		class IfcInventory;
		class IfcInventoryTypeEnum;
		class IfcIonConcentrationMeasure;
		class IfcIrregularTimeSeries;
		class IfcIrregularTimeSeriesValue;
		class IfcIShapeProfileDef;
		class IfcIsothermalMoistureCapacityMeasure;
		class IfcJunctionBoxType;
		class IfcJunctionBoxTypeEnum;
		class IfcKinematicViscosityMeasure;
		class IfcLabel;
		class IfcLaborResource;
		class IfcLampType;
		class IfcLampTypeEnum;
		class IfcLayeredItem;
		class IfcLayerSetDirectionEnum;
		class IfcLengthMeasure;
		class IfcLibraryInformation;
		class IfcLibraryReference;
		class IfcLibrarySelect;
		class IfcLightDistributionCurveEnum;
		class IfcLightDistributionData;
		class IfcLightDistributionDataSourceSelect;
		class IfcLightEmissionSourceEnum;
		class IfcLightFixtureType;
		class IfcLightFixtureTypeEnum;
		class IfcLightIntensityDistribution;
		class IfcLightSource;
		class IfcLightSourceAmbient;
		class IfcLightSourceDirectional;
		class IfcLightSourceGoniometric;
		class IfcLightSourcePositional;
		class IfcLightSourceSpot;
		class IfcLine;
		class IfcLinearDimension;
		class IfcLinearForceMeasure;
		class IfcLinearMomentMeasure;
		class IfcLinearStiffnessMeasure;
		class IfcLinearVelocityMeasure;
		class IfcLoadGroupTypeEnum;
		class IfcLocalPlacement;
		class IfcLocalTime;
		class IfcLogical;
		class IfcLogicalOperatorEnum;
		class IfcLoop;
		class IfcLShapeProfileDef;
		class IfcLuminousFluxMeasure;
		class IfcLuminousIntensityDistributionMeasure;
		class IfcLuminousIntensityMeasure;
		class IfcMagneticFluxDensityMeasure;
		class IfcMagneticFluxMeasure;
		class IfcManifoldSolidBrep;
		class IfcMappedItem;
		class IfcMassDensityMeasure;
		class IfcMassFlowRateMeasure;
		class IfcMassMeasure;
		class IfcMassPerLengthMeasure;
		class IfcMaterial;
		class IfcMaterialClassificationRelationship;
		class IfcMaterialDefinitionRepresentation;
		class IfcMaterialLayer;
		class IfcMaterialLayerSet;
		class IfcMaterialLayerSetUsage;
		class IfcMaterialList;
		class IfcMaterialProperties;
		class IfcMaterialSelect;
		class IfcMeasureValue;
		class IfcMeasureWithUnit;
		class IfcMechanicalConcreteMaterialProperties;
		class IfcMechanicalFastener;
		class IfcMechanicalFastenerType;
		class IfcMechanicalMaterialProperties;
		class IfcMechanicalSteelMaterialProperties;
		class IfcMember;
		class IfcMemberType;
		class IfcMemberTypeEnum;
		class IfcMetric;
		class IfcMetricValueSelect;
		class IfcMinuteInHour;
		class IfcModulusOfElasticityMeasure;
		class IfcModulusOfLinearSubgradeReactionMeasure;
		class IfcModulusOfRotationalSubgradeReactionMeasure;
		class IfcModulusOfSubgradeReactionMeasure;
		class IfcMoistureDiffusivityMeasure;
		class IfcMolecularWeightMeasure;
		class IfcMomentOfInertiaMeasure;
		class IfcMonetaryMeasure;
		class IfcMonetaryUnit;
		class IfcMonthInYearNumber;
		class IfcMotorConnectionType;
		class IfcMotorConnectionTypeEnum;
		class IfcMove;
		class IfcNamedUnit;
		class IfcNormalisedRatioMeasure;
		class IfcNullStyle;
		class IfcNumericMeasure;
		class IfcObject;
		class IfcObjectDefinition;
		class IfcObjective;
		class IfcObjectiveEnum;
		class IfcObjectPlacement;
		class IfcObjectReferenceSelect;
		class IfcObjectTypeEnum;
		class IfcOccupant;
		class IfcOccupantTypeEnum;
		class IfcOffsetCurve2D;
		class IfcOffsetCurve3D;
		class IfcOneDirectionRepeatFactor;
		class IfcOpeningElement;
		class IfcOpenShell;
		class IfcOpticalMaterialProperties;
		class IfcOrderAction;
		class IfcOrganization;
		class IfcOrganizationRelationship;
		class IfcOrientationSelect;
		class IfcOrientedEdge;
		class IfcOutletType;
		class IfcOutletTypeEnum;
		class IfcOwnerHistory;
		class IfcParameterizedProfileDef;
		class IfcParameterValue;
		class IfcPath;
		class IfcPerformanceHistory;
		class IfcPermeableCoveringOperationEnum;
		class IfcPermeableCoveringProperties;
		class IfcPermit;
		class IfcPerson;
		class IfcPersonAndOrganization;
		class IfcPHMeasure;
		class IfcPhysicalComplexQuantity;
		class IfcPhysicalOrVirtualEnum;
		class IfcPhysicalQuantity;
		class IfcPhysicalSimpleQuantity;
		class IfcPile;
		class IfcPileConstructionEnum;
		class IfcPileTypeEnum;
		class IfcPipeFittingType;
		class IfcPipeFittingTypeEnum;
		class IfcPipeSegmentType;
		class IfcPipeSegmentTypeEnum;
		class IfcPixelTexture;
		class IfcPlacement;
		class IfcPlanarBox;
		class IfcPlanarExtent;
		class IfcPlanarForceMeasure;
		class IfcPlane;
		class IfcPlaneAngleMeasure;
		class IfcPlate;
		class IfcPlateType;
		class IfcPlateTypeEnum;
		class IfcPoint;
		class IfcPointOnCurve;
		class IfcPointOnSurface;
		class IfcPointOrVertexPoint;
		class IfcPolygonalBoundedHalfSpace;
		class IfcPolyline;
		class IfcPolyLoop;
		class IfcPort;
		class IfcPositiveLengthMeasure;
		class IfcPositivePlaneAngleMeasure;
		class IfcPositiveRatioMeasure;
		class IfcPostalAddress;
		class IfcPowerMeasure;
		class IfcPreDefinedColour;
		class IfcPreDefinedCurveFont;
		class IfcPreDefinedDimensionSymbol;
		class IfcPreDefinedItem;
		class IfcPreDefinedPointMarkerSymbol;
		class IfcPreDefinedSymbol;
		class IfcPreDefinedTerminatorSymbol;
		class IfcPreDefinedTextFont;
		class IfcPresentableText;
		class IfcPresentationLayerAssignment;
		class IfcPresentationLayerWithStyle;
		class IfcPresentationStyle;
		class IfcPresentationStyleAssignment;
		class IfcPresentationStyleSelect;
		class IfcPressureMeasure;
		class IfcProcedure;
		class IfcProcedureTypeEnum;
		class IfcProcess;
		class IfcProduct;
		class IfcProductDefinitionShape;
		class IfcProductRepresentation;
		class IfcProductsOfCombustionProperties;
		class IfcProfileDef;
		class IfcProfileProperties;
		class IfcProfileTypeEnum;
		class IfcProject;
		class IfcProjectedOrTrueLengthEnum;
		class IfcProjectionCurve;
		class IfcProjectionElement;
		class IfcProjectOrder;
		class IfcProjectOrderRecord;
		class IfcProjectOrderRecordTypeEnum;
		class IfcProjectOrderTypeEnum;
		class IfcProperty;
		class IfcPropertyBoundedValue;
		class IfcPropertyConstraintRelationship;
		class IfcPropertyDefinition;
		class IfcPropertyDependencyRelationship;
		class IfcPropertyEnumeratedValue;
		class IfcPropertyEnumeration;
		class IfcPropertyListValue;
		class IfcPropertyReferenceValue;
		class IfcPropertySet;
		class IfcPropertySetDefinition;
		class IfcPropertySingleValue;
		class IfcPropertySourceEnum;
		class IfcPropertyTableValue;
		class IfcProtectiveDeviceType;
		class IfcProtectiveDeviceTypeEnum;
		class IfcProxy;
		class IfcPumpType;
		class IfcPumpTypeEnum;
		class IfcQuantityArea;
		class IfcQuantityCount;
		class IfcQuantityLength;
		class IfcQuantityTime;
		class IfcQuantityVolume;
		class IfcQuantityWeight;
		class IfcRadioActivityMeasure;
		class IfcRadiusDimension;
		class IfcRailing;
		class IfcRailingType;
		class IfcRailingTypeEnum;
		class IfcRamp;
		class IfcRampFlight;
		class IfcRampFlightType;
		class IfcRampFlightTypeEnum;
		class IfcRampTypeEnum;
		class IfcRatioMeasure;
		class IfcRationalBezierCurve;
		class IfcReal;
		class IfcRectangleHollowProfileDef;
		class IfcRectangleProfileDef;
		class IfcRectangularPyramid;
		class IfcRectangularTrimmedSurface;
		class IfcReferencesValueDocument;
		class IfcReflectanceMethodEnum;
		class IfcRegularTimeSeries;
		class IfcReinforcementBarProperties;
		class IfcReinforcementDefinitionProperties;
		class IfcReinforcingBar;
		class IfcReinforcingBarRoleEnum;
		class IfcReinforcingBarSurfaceEnum;
		class IfcReinforcingElement;
		class IfcReinforcingMesh;
		class IfcRelAggregates;
		class IfcRelAssigns;
		class IfcRelAssignsTasks;
		class IfcRelAssignsToActor;
		class IfcRelAssignsToControl;
		class IfcRelAssignsToGroup;
		class IfcRelAssignsToProcess;
		class IfcRelAssignsToProduct;
		class IfcRelAssignsToProjectOrder;
		class IfcRelAssignsToResource;
		class IfcRelAssociates;
		class IfcRelAssociatesAppliedValue;
		class IfcRelAssociatesApproval;
		class IfcRelAssociatesClassification;
		class IfcRelAssociatesConstraint;
		class IfcRelAssociatesDocument;
		class IfcRelAssociatesLibrary;
		class IfcRelAssociatesMaterial;
		class IfcRelAssociatesProfileProperties;
		class IfcRelationship;
		class IfcRelaxation;
		class IfcRelConnects;
		class IfcRelConnectsElements;
		class IfcRelConnectsPathElements;
		class IfcRelConnectsPorts;
		class IfcRelConnectsPortToElement;
		class IfcRelConnectsStructuralActivity;
		class IfcRelConnectsStructuralElement;
		class IfcRelConnectsStructuralMember;
		class IfcRelConnectsWithEccentricity;
		class IfcRelConnectsWithRealizingElements;
		class IfcRelContainedInSpatialStructure;
		class IfcRelCoversBldgElements;
		class IfcRelCoversSpaces;
		class IfcRelDecomposes;
		class IfcRelDefines;
		class IfcRelDefinesByProperties;
		class IfcRelDefinesByType;
		class IfcRelFillsElement;
		class IfcRelFlowControlElements;
		class IfcRelInteractionRequirements;
		class IfcRelNests;
		class IfcRelOccupiesSpaces;
		class IfcRelOverridesProperties;
		class IfcRelProjectsElement;
		class IfcRelReferencedInSpatialStructure;
		class IfcRelSchedulesCostItems;
		class IfcRelSequence;
		class IfcRelServicesBuildings;
		class IfcRelSpaceBoundary;
		class IfcRelVoidsElement;
		class IfcRepresentation;
		class IfcRepresentationContext;
		class IfcRepresentationItem;
		class IfcRepresentationMap;
		class IfcResource;
		class IfcResourceConsumptionEnum;
		class IfcRevolvedAreaSolid;
		class IfcRibPlateDirectionEnum;
		class IfcRibPlateProfileProperties;
		class IfcRightCircularCone;
		class IfcRightCircularCylinder;
		class IfcRoleEnum;
		class IfcRoof;
		class IfcRoofTypeEnum;
		class IfcRoot;
		class IfcRotationalFrequencyMeasure;
		class IfcRotationalMassMeasure;
		class IfcRotationalStiffnessMeasure;
		class IfcRoundedEdgeFeature;
		class IfcRoundedRectangleProfileDef;
		class IfcSanitaryTerminalType;
		class IfcSanitaryTerminalTypeEnum;
		class IfcScheduleTimeControl;
		class IfcSecondInMinute;
		class IfcSectionalAreaIntegralMeasure;
		class IfcSectionedSpine;
		class IfcSectionModulusMeasure;
		class IfcSectionProperties;
		class IfcSectionReinforcementProperties;
		class IfcSectionTypeEnum;
		class IfcSensorType;
		class IfcSensorTypeEnum;
		class IfcSequenceEnum;
		class IfcServiceLife;
		class IfcServiceLifeFactor;
		class IfcServiceLifeFactorTypeEnum;
		class IfcServiceLifeTypeEnum;
		class IfcShapeAspect;
		class IfcShapeModel;
		class IfcShapeRepresentation;
		class IfcShearModulusMeasure;
		class IfcShell;
		class IfcShellBasedSurfaceModel;
		class IfcSimpleProperty;
		class IfcSimpleValue;
		class IfcSIPrefix;
		class IfcSite;
		class IfcSIUnit;
		class IfcSIUnitName;
		class IfcSizeSelect;
		class IfcSlab;
		class IfcSlabType;
		class IfcSlabTypeEnum;
		class IfcSlippageConnectionCondition;
		class IfcSolidAngleMeasure;
		class IfcSolidModel;
		class IfcSoundPowerMeasure;
		class IfcSoundPressureMeasure;
		class IfcSoundProperties;
		class IfcSoundScaleEnum;
		class IfcSoundValue;
		class IfcSpace;
		class IfcSpaceHeaterType;
		class IfcSpaceHeaterTypeEnum;
		class IfcSpaceProgram;
		class IfcSpaceThermalLoadProperties;
		class IfcSpaceType;
		class IfcSpaceTypeEnum;
		class IfcSpatialStructureElement;
		class IfcSpatialStructureElementType;
		class IfcSpecificHeatCapacityMeasure;
		class IfcSpecularExponent;
		class IfcSpecularHighlightSelect;
		class IfcSpecularRoughness;
		class IfcSphere;
		class IfcStackTerminalType;
		class IfcStackTerminalTypeEnum;
		class IfcStair;
		class IfcStairFlight;
		class IfcStairFlightType;
		class IfcStairFlightTypeEnum;
		class IfcStairTypeEnum;
		class IfcStateEnum;
		class IfcStructuralAction;
		class IfcStructuralActivity;
		class IfcStructuralActivityAssignmentSelect;
		class IfcStructuralAnalysisModel;
		class IfcStructuralConnection;
		class IfcStructuralConnectionCondition;
		class IfcStructuralCurveConnection;
		class IfcStructuralCurveMember;
		class IfcStructuralCurveMemberVarying;
		class IfcStructuralCurveTypeEnum;
		class IfcStructuralItem;
		class IfcStructuralLinearAction;
		class IfcStructuralLinearActionVarying;
		class IfcStructuralLoad;
		class IfcStructuralLoadGroup;
		class IfcStructuralLoadLinearForce;
		class IfcStructuralLoadPlanarForce;
		class IfcStructuralLoadSingleDisplacement;
		class IfcStructuralLoadSingleDisplacementDistortion;
		class IfcStructuralLoadSingleForce;
		class IfcStructuralLoadSingleForceWarping;
		class IfcStructuralLoadStatic;
		class IfcStructuralLoadTemperature;
		class IfcStructuralMember;
		class IfcStructuralPlanarAction;
		class IfcStructuralPlanarActionVarying;
		class IfcStructuralPointAction;
		class IfcStructuralPointConnection;
		class IfcStructuralPointReaction;
		class IfcStructuralProfileProperties;
		class IfcStructuralReaction;
		class IfcStructuralResultGroup;
		class IfcStructuralSteelProfileProperties;
		class IfcStructuralSurfaceConnection;
		class IfcStructuralSurfaceMember;
		class IfcStructuralSurfaceMemberVarying;
		class IfcStructuralSurfaceTypeEnum;
		class IfcStructuredDimensionCallout;
		class IfcStyledItem;
		class IfcStyledRepresentation;
		class IfcStyleModel;
		class IfcSubContractResource;
		class IfcSubedge;
		class IfcSurface;
		class IfcSurfaceCurveSweptAreaSolid;
		class IfcSurfaceOfLinearExtrusion;
		class IfcSurfaceOfRevolution;
		class IfcSurfaceOrFaceSurface;
		class IfcSurfaceSide;
		class IfcSurfaceStyle;
		class IfcSurfaceStyleElementSelect;
		class IfcSurfaceStyleLighting;
		class IfcSurfaceStyleRefraction;
		class IfcSurfaceStyleRendering;
		class IfcSurfaceStyleShading;
		class IfcSurfaceStyleWithTextures;
		class IfcSurfaceTexture;
		class IfcSurfaceTextureEnum;
		class IfcSweptAreaSolid;
		class IfcSweptDiskSolid;
		class IfcSweptSurface;
		class IfcSwitchingDeviceType;
		class IfcSwitchingDeviceTypeEnum;
		class IfcSymbolStyle;
		class IfcSymbolStyleSelect;
		class IfcSystem;
		class IfcSystemFurnitureElementType;
		class IfcTable;
		class IfcTableRow;
		class IfcTankType;
		class IfcTankTypeEnum;
		class IfcTask;
		class IfcTelecomAddress;
		class IfcTemperatureGradientMeasure;
		class IfcTendon;
		class IfcTendonAnchor;
		class IfcTendonTypeEnum;
		class IfcTerminatorSymbol;
		class IfcText;
		class IfcTextAlignment;
		class IfcTextDecoration;
		class IfcTextFontName;
		class IfcTextFontSelect;
		class IfcTextLiteral;
		class IfcTextLiteralWithExtent;
		class IfcTextPath;
		class IfcTextStyle;
		class IfcTextStyleFontModel;
		class IfcTextStyleForDefinedFont;
		class IfcTextStyleSelect;
		class IfcTextStyleTextModel;
		class IfcTextStyleWithBoxCharacteristics;
		class IfcTextTransformation;
		class IfcTextureCoordinate;
		class IfcTextureCoordinateGenerator;
		class IfcTextureMap;
		class IfcTextureVertex;
		class IfcThermalAdmittanceMeasure;
		class IfcThermalConductivityMeasure;
		class IfcThermalExpansionCoefficientMeasure;
		class IfcThermalLoadSourceEnum;
		class IfcThermalLoadTypeEnum;
		class IfcThermalMaterialProperties;
		class IfcThermalResistanceMeasure;
		class IfcThermalTransmittanceMeasure;
		class IfcThermodynamicTemperatureMeasure;
		class IfcTimeMeasure;
		class IfcTimeSeries;
		class IfcTimeSeriesDataTypeEnum;
		class IfcTimeSeriesReferenceRelationship;
		class IfcTimeSeriesSchedule;
		class IfcTimeSeriesScheduleTypeEnum;
		class IfcTimeSeriesValue;
		class IfcTimeStamp;
		class IfcTopologicalRepresentationItem;
		class IfcTopologyRepresentation;
		class IfcTorqueMeasure;
		class IfcTransformerType;
		class IfcTransformerTypeEnum;
		class IfcTransitionCode;
		class IfcTransportElement;
		class IfcTransportElementType;
		class IfcTransportElementTypeEnum;
		class IfcTrapeziumProfileDef;
		class IfcTrimmedCurve;
		class IfcTrimmingPreference;
		class IfcTrimmingSelect;
		class IfcTShapeProfileDef;
		class IfcTubeBundleType;
		class IfcTubeBundleTypeEnum;
		class IfcTwoDirectionRepeatFactor;
		class IfcTypeObject;
		class IfcTypeProduct;
		class IfcUnit;
		class IfcUnitaryEquipmentType;
		class IfcUnitaryEquipmentTypeEnum;
		class IfcUnitAssignment;
		class IfcUnitEnum;
		class IfcUShapeProfileDef;
		class IfcValue;
		class IfcValveType;
		class IfcValveTypeEnum;
		class IfcVaporPermeabilityMeasure;
		class IfcVector;
		class IfcVectorOrDirection;
		class IfcVertex;
		class IfcVertexBasedTextureMap;
		class IfcVertexLoop;
		class IfcVertexPoint;
		class IfcVibrationIsolatorType;
		class IfcVibrationIsolatorTypeEnum;
		class IfcVirtualElement;
		class IfcVirtualGridIntersection;
		class IfcVolumeMeasure;
		class IfcVolumetricFlowRateMeasure;
		class IfcWall;
		class IfcWallStandardCase;
		class IfcWallType;
		class IfcWallTypeEnum;
		class IfcWarpingConstantMeasure;
		class IfcWarpingMomentMeasure;
		class IfcWasteTerminalType;
		class IfcWasteTerminalTypeEnum;
		class IfcWaterProperties;
		class IfcWindow;
		class IfcWindowLiningProperties;
		class IfcWindowPanelOperationEnum;
		class IfcWindowPanelPositionEnum;
		class IfcWindowPanelProperties;
		class IfcWindowStyle;
		class IfcWindowStyleConstructionEnum;
		class IfcWindowStyleOperationEnum;
		class IfcWorkControl;
		class IfcWorkControlTypeEnum;
		class IfcWorkPlan;
		class IfcWorkSchedule;
		class IfcYearNumber;
		class IfcZone;
		class IfcZShapeProfileDef;
	}
}

namespace emt
{
	typedef IfcEntityTypes<
		BlueFramework::Ifc2x3::IfcAbsorbedDoseMeasure,
		BlueFramework::Ifc2x3::IfcAccelerationMeasure,
		BlueFramework::Ifc2x3::IfcActionRequest,
		BlueFramework::Ifc2x3::IfcActionSourceTypeEnum,
		BlueFramework::Ifc2x3::IfcActionTypeEnum,
		BlueFramework::Ifc2x3::IfcActor,
		BlueFramework::Ifc2x3::IfcActorRole,
		BlueFramework::Ifc2x3::IfcActorSelect,
		BlueFramework::Ifc2x3::IfcActuatorType,
		BlueFramework::Ifc2x3::IfcActuatorTypeEnum,
		BlueFramework::Ifc2x3::IfcAddress,
		BlueFramework::Ifc2x3::IfcAddressTypeEnum,
		BlueFramework::Ifc2x3::IfcAheadOrBehind,
		BlueFramework::Ifc2x3::IfcAirTerminalBoxType,
		BlueFramework::Ifc2x3::IfcAirTerminalBoxTypeEnum,
		BlueFramework::Ifc2x3::IfcAirTerminalType,
		BlueFramework::Ifc2x3::IfcAirTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcAirToAirHeatRecoveryType,
		BlueFramework::Ifc2x3::IfcAirToAirHeatRecoveryTypeEnum,
		BlueFramework::Ifc2x3::IfcAlarmType,
		BlueFramework::Ifc2x3::IfcAlarmTypeEnum,
		BlueFramework::Ifc2x3::IfcAmountOfSubstanceMeasure,
		BlueFramework::Ifc2x3::IfcAnalysisModelTypeEnum,
		BlueFramework::Ifc2x3::IfcAnalysisTheoryTypeEnum,
		BlueFramework::Ifc2x3::IfcAngularDimension,
		BlueFramework::Ifc2x3::IfcAngularVelocityMeasure,
		BlueFramework::Ifc2x3::IfcAnnotation,
		BlueFramework::Ifc2x3::IfcAnnotationCurveOccurrence,
		BlueFramework::Ifc2x3::IfcAnnotationFillArea,
		BlueFramework::Ifc2x3::IfcAnnotationFillAreaOccurrence,
		BlueFramework::Ifc2x3::IfcAnnotationOccurrence,
		BlueFramework::Ifc2x3::IfcAnnotationSurface,
		BlueFramework::Ifc2x3::IfcAnnotationSurfaceOccurrence,
		BlueFramework::Ifc2x3::IfcAnnotationSymbolOccurrence,
		BlueFramework::Ifc2x3::IfcAnnotationTextOccurrence,
		BlueFramework::Ifc2x3::IfcApplication,
		BlueFramework::Ifc2x3::IfcAppliedValue,
		BlueFramework::Ifc2x3::IfcAppliedValueRelationship,
		BlueFramework::Ifc2x3::IfcAppliedValueSelect,
		BlueFramework::Ifc2x3::IfcApproval,
		BlueFramework::Ifc2x3::IfcApprovalActorRelationship,
		BlueFramework::Ifc2x3::IfcApprovalPropertyRelationship,
		BlueFramework::Ifc2x3::IfcApprovalRelationship,
		BlueFramework::Ifc2x3::IfcArbitraryClosedProfileDef,
		BlueFramework::Ifc2x3::IfcArbitraryOpenProfileDef,
		BlueFramework::Ifc2x3::IfcArbitraryProfileDefWithVoids,
		BlueFramework::Ifc2x3::IfcAreaMeasure,
		BlueFramework::Ifc2x3::IfcArithmeticOperatorEnum,
		BlueFramework::Ifc2x3::IfcAssemblyPlaceEnum,
		BlueFramework::Ifc2x3::IfcAsset,
		BlueFramework::Ifc2x3::IfcAsymmetricIShapeProfileDef,
		BlueFramework::Ifc2x3::IfcAxis1Placement,
		BlueFramework::Ifc2x3::IfcAxis2Placement,
		BlueFramework::Ifc2x3::IfcAxis2Placement2D,
		BlueFramework::Ifc2x3::IfcAxis2Placement3D,
		BlueFramework::Ifc2x3::IfcBeam,
		BlueFramework::Ifc2x3::IfcBeamType,
		BlueFramework::Ifc2x3::IfcBeamTypeEnum,
		BlueFramework::Ifc2x3::IfcBenchmarkEnum,
		BlueFramework::Ifc2x3::IfcBezierCurve,
		BlueFramework::Ifc2x3::IfcBlobTexture,
		BlueFramework::Ifc2x3::IfcBlock,
		BlueFramework::Ifc2x3::IfcBoilerType,
		BlueFramework::Ifc2x3::IfcBoilerTypeEnum,
		BlueFramework::Ifc2x3::IfcBoolean,
		BlueFramework::Ifc2x3::IfcBooleanClippingResult,
		BlueFramework::Ifc2x3::IfcBooleanOperand,
		BlueFramework::Ifc2x3::IfcBooleanOperator,
		BlueFramework::Ifc2x3::IfcBooleanResult,
		BlueFramework::Ifc2x3::IfcBoundaryCondition,
		BlueFramework::Ifc2x3::IfcBoundaryEdgeCondition,
		BlueFramework::Ifc2x3::IfcBoundaryFaceCondition,
		BlueFramework::Ifc2x3::IfcBoundaryNodeCondition,
		BlueFramework::Ifc2x3::IfcBoundaryNodeConditionWarping,
		BlueFramework::Ifc2x3::IfcBoundedCurve,
		BlueFramework::Ifc2x3::IfcBoundedSurface,
		BlueFramework::Ifc2x3::IfcBoundingBox,
		BlueFramework::Ifc2x3::IfcBoxAlignment,
		BlueFramework::Ifc2x3::IfcBoxedHalfSpace,
		BlueFramework::Ifc2x3::IfcBSplineCurve,
		BlueFramework::Ifc2x3::IfcBSplineCurveForm,
		BlueFramework::Ifc2x3::IfcBuilding,
		BlueFramework::Ifc2x3::IfcBuildingElement,
		BlueFramework::Ifc2x3::IfcBuildingElementComponent,
		BlueFramework::Ifc2x3::IfcBuildingElementPart,
		BlueFramework::Ifc2x3::IfcBuildingElementProxy,
		BlueFramework::Ifc2x3::IfcBuildingElementProxyType,
		BlueFramework::Ifc2x3::IfcBuildingElementProxyTypeEnum,
		BlueFramework::Ifc2x3::IfcBuildingElementType,
		BlueFramework::Ifc2x3::IfcBuildingStorey,
		BlueFramework::Ifc2x3::IfcCableCarrierFittingType,
		BlueFramework::Ifc2x3::IfcCableCarrierFittingTypeEnum,
		BlueFramework::Ifc2x3::IfcCableCarrierSegmentType,
		BlueFramework::Ifc2x3::IfcCableCarrierSegmentTypeEnum,
		BlueFramework::Ifc2x3::IfcCableSegmentType,
		BlueFramework::Ifc2x3::IfcCableSegmentTypeEnum,
		BlueFramework::Ifc2x3::IfcCalendarDate,
		BlueFramework::Ifc2x3::IfcCartesianPoint,
		BlueFramework::Ifc2x3::IfcCartesianTransformationOperator,
		BlueFramework::Ifc2x3::IfcCartesianTransformationOperator2D,
		BlueFramework::Ifc2x3::IfcCartesianTransformationOperator2DnonUniform,
		BlueFramework::Ifc2x3::IfcCartesianTransformationOperator3D,
		BlueFramework::Ifc2x3::IfcCartesianTransformationOperator3DnonUniform,
		BlueFramework::Ifc2x3::IfcCenterLineProfileDef,
		BlueFramework::Ifc2x3::IfcChamferEdgeFeature,
		BlueFramework::Ifc2x3::IfcChangeActionEnum,
		BlueFramework::Ifc2x3::IfcCharacterStyleSelect,
		BlueFramework::Ifc2x3::IfcChillerType,
		BlueFramework::Ifc2x3::IfcChillerTypeEnum,
		BlueFramework::Ifc2x3::IfcCircle,
		BlueFramework::Ifc2x3::IfcCircleHollowProfileDef,
		BlueFramework::Ifc2x3::IfcCircleProfileDef,
		BlueFramework::Ifc2x3::IfcClassification,
		BlueFramework::Ifc2x3::IfcClassificationItem,
		BlueFramework::Ifc2x3::IfcClassificationItemRelationship,
		BlueFramework::Ifc2x3::IfcClassificationNotation,
		BlueFramework::Ifc2x3::IfcClassificationNotationFacet,
		BlueFramework::Ifc2x3::IfcClassificationNotationSelect,
		BlueFramework::Ifc2x3::IfcClassificationReference,
		BlueFramework::Ifc2x3::IfcClosedShell,
		BlueFramework::Ifc2x3::IfcCoilType,
		BlueFramework::Ifc2x3::IfcCoilTypeEnum,
		BlueFramework::Ifc2x3::IfcColour,
		BlueFramework::Ifc2x3::IfcColourOrFactor,
		BlueFramework::Ifc2x3::IfcColourRgb,
		BlueFramework::Ifc2x3::IfcColourSpecification,
		BlueFramework::Ifc2x3::IfcColumn,
		BlueFramework::Ifc2x3::IfcColumnType,
		BlueFramework::Ifc2x3::IfcColumnTypeEnum,
		BlueFramework::Ifc2x3::IfcComplexNumber,
		BlueFramework::Ifc2x3::IfcComplexProperty,
		BlueFramework::Ifc2x3::IfcCompositeCurve,
		BlueFramework::Ifc2x3::IfcCompositeCurveSegment,
		BlueFramework::Ifc2x3::IfcCompositeProfileDef,
		BlueFramework::Ifc2x3::IfcCompoundPlaneAngleMeasure,
		BlueFramework::Ifc2x3::IfcCompressorType,
		BlueFramework::Ifc2x3::IfcCompressorTypeEnum,
		BlueFramework::Ifc2x3::IfcCondenserType,
		BlueFramework::Ifc2x3::IfcCondenserTypeEnum,
		BlueFramework::Ifc2x3::IfcCondition,
		BlueFramework::Ifc2x3::IfcConditionCriterion,
		BlueFramework::Ifc2x3::IfcConditionCriterionSelect,
		BlueFramework::Ifc2x3::IfcConic,
		BlueFramework::Ifc2x3::IfcConnectedFaceSet,
		BlueFramework::Ifc2x3::IfcConnectionCurveGeometry,
		BlueFramework::Ifc2x3::IfcConnectionGeometry,
		BlueFramework::Ifc2x3::IfcConnectionPointEccentricity,
		BlueFramework::Ifc2x3::IfcConnectionPointGeometry,
		BlueFramework::Ifc2x3::IfcConnectionPortGeometry,
		BlueFramework::Ifc2x3::IfcConnectionSurfaceGeometry,
		BlueFramework::Ifc2x3::IfcConnectionTypeEnum,
		BlueFramework::Ifc2x3::IfcConstraint,
		BlueFramework::Ifc2x3::IfcConstraintAggregationRelationship,
		BlueFramework::Ifc2x3::IfcConstraintClassificationRelationship,
		BlueFramework::Ifc2x3::IfcConstraintEnum,
		BlueFramework::Ifc2x3::IfcConstraintRelationship,
		BlueFramework::Ifc2x3::IfcConstructionEquipmentResource,
		BlueFramework::Ifc2x3::IfcConstructionMaterialResource,
		BlueFramework::Ifc2x3::IfcConstructionProductResource,
		BlueFramework::Ifc2x3::IfcConstructionResource,
		BlueFramework::Ifc2x3::IfcContextDependentMeasure,
		BlueFramework::Ifc2x3::IfcContextDependentUnit,
		BlueFramework::Ifc2x3::IfcControl,
		BlueFramework::Ifc2x3::IfcControllerType,
		BlueFramework::Ifc2x3::IfcControllerTypeEnum,
		BlueFramework::Ifc2x3::IfcConversionBasedUnit,
		BlueFramework::Ifc2x3::IfcCooledBeamType,
		BlueFramework::Ifc2x3::IfcCooledBeamTypeEnum,
		BlueFramework::Ifc2x3::IfcCoolingTowerType,
		BlueFramework::Ifc2x3::IfcCoolingTowerTypeEnum,
		BlueFramework::Ifc2x3::IfcCoordinatedUniversalTimeOffset,
		BlueFramework::Ifc2x3::IfcCostItem,
		BlueFramework::Ifc2x3::IfcCostSchedule,
		BlueFramework::Ifc2x3::IfcCostScheduleTypeEnum,
		BlueFramework::Ifc2x3::IfcCostValue,
		BlueFramework::Ifc2x3::IfcCountMeasure,
		BlueFramework::Ifc2x3::IfcCovering,
		BlueFramework::Ifc2x3::IfcCoveringType,
		BlueFramework::Ifc2x3::IfcCoveringTypeEnum,
		BlueFramework::Ifc2x3::IfcCraneRailAShapeProfileDef,
		BlueFramework::Ifc2x3::IfcCraneRailFShapeProfileDef,
		BlueFramework::Ifc2x3::IfcCrewResource,
		BlueFramework::Ifc2x3::IfcCsgPrimitive3D,
		BlueFramework::Ifc2x3::IfcCsgSelect,
		BlueFramework::Ifc2x3::IfcCsgSolid,
		BlueFramework::Ifc2x3::IfcCShapeProfileDef,
		BlueFramework::Ifc2x3::IfcCurrencyEnum,
		BlueFramework::Ifc2x3::IfcCurrencyRelationship,
		BlueFramework::Ifc2x3::IfcCurtainWall,
		BlueFramework::Ifc2x3::IfcCurtainWallType,
		BlueFramework::Ifc2x3::IfcCurtainWallTypeEnum,
		BlueFramework::Ifc2x3::IfcCurvatureMeasure,
		BlueFramework::Ifc2x3::IfcCurve,
		BlueFramework::Ifc2x3::IfcCurveBoundedPlane,
		BlueFramework::Ifc2x3::IfcCurveFontOrScaledCurveFontSelect,
		BlueFramework::Ifc2x3::IfcCurveOrEdgeCurve,
		BlueFramework::Ifc2x3::IfcCurveStyle,
		BlueFramework::Ifc2x3::IfcCurveStyleFont,
		BlueFramework::Ifc2x3::IfcCurveStyleFontAndScaling,
		BlueFramework::Ifc2x3::IfcCurveStyleFontPattern,
		BlueFramework::Ifc2x3::IfcCurveStyleFontSelect,
		BlueFramework::Ifc2x3::IfcDamperType,
		BlueFramework::Ifc2x3::IfcDamperTypeEnum,
		BlueFramework::Ifc2x3::IfcDataOriginEnum,
		BlueFramework::Ifc2x3::IfcDateAndTime,
		BlueFramework::Ifc2x3::IfcDateTimeSelect,
		BlueFramework::Ifc2x3::IfcDayInMonthNumber,
		BlueFramework::Ifc2x3::IfcDaylightSavingHour,
		BlueFramework::Ifc2x3::IfcDefinedSymbol,
		BlueFramework::Ifc2x3::IfcDefinedSymbolSelect,
		BlueFramework::Ifc2x3::IfcDerivedMeasureValue,
		BlueFramework::Ifc2x3::IfcDerivedProfileDef,
		BlueFramework::Ifc2x3::IfcDerivedUnit,
		BlueFramework::Ifc2x3::IfcDerivedUnitElement,
		BlueFramework::Ifc2x3::IfcDerivedUnitEnum,
		BlueFramework::Ifc2x3::IfcDescriptiveMeasure,
		BlueFramework::Ifc2x3::IfcDiameterDimension,
		BlueFramework::Ifc2x3::IfcDimensionalExponents,
		BlueFramework::Ifc2x3::IfcDimensionCalloutRelationship,
		BlueFramework::Ifc2x3::IfcDimensionCount,
		BlueFramework::Ifc2x3::IfcDimensionCurve,
		BlueFramework::Ifc2x3::IfcDimensionCurveDirectedCallout,
		BlueFramework::Ifc2x3::IfcDimensionCurveTerminator,
		BlueFramework::Ifc2x3::IfcDimensionExtentUsage,
		BlueFramework::Ifc2x3::IfcDimensionPair,
		BlueFramework::Ifc2x3::IfcDirection,
		BlueFramework::Ifc2x3::IfcDirectionSenseEnum,
		BlueFramework::Ifc2x3::IfcDiscreteAccessory,
		BlueFramework::Ifc2x3::IfcDiscreteAccessoryType,
		BlueFramework::Ifc2x3::IfcDistributionChamberElement,
		BlueFramework::Ifc2x3::IfcDistributionChamberElementType,
		BlueFramework::Ifc2x3::IfcDistributionChamberElementTypeEnum,
		BlueFramework::Ifc2x3::IfcDistributionControlElement,
		BlueFramework::Ifc2x3::IfcDistributionControlElementType,
		BlueFramework::Ifc2x3::IfcDistributionElement,
		BlueFramework::Ifc2x3::IfcDistributionElementType,
		BlueFramework::Ifc2x3::IfcDistributionFlowElement,
		BlueFramework::Ifc2x3::IfcDistributionFlowElementType,
		BlueFramework::Ifc2x3::IfcDistributionPort,
		BlueFramework::Ifc2x3::IfcDocumentConfidentialityEnum,
		BlueFramework::Ifc2x3::IfcDocumentElectronicFormat,
		BlueFramework::Ifc2x3::IfcDocumentInformation,
		BlueFramework::Ifc2x3::IfcDocumentInformationRelationship,
		BlueFramework::Ifc2x3::IfcDocumentReference,
		BlueFramework::Ifc2x3::IfcDocumentSelect,
		BlueFramework::Ifc2x3::IfcDocumentStatusEnum,
		BlueFramework::Ifc2x3::IfcDoor,
		BlueFramework::Ifc2x3::IfcDoorLiningProperties,
		BlueFramework::Ifc2x3::IfcDoorPanelOperationEnum,
		BlueFramework::Ifc2x3::IfcDoorPanelPositionEnum,
		BlueFramework::Ifc2x3::IfcDoorPanelProperties,
		BlueFramework::Ifc2x3::IfcDoorStyle,
		BlueFramework::Ifc2x3::IfcDoorStyleConstructionEnum,
		BlueFramework::Ifc2x3::IfcDoorStyleOperationEnum,
		BlueFramework::Ifc2x3::IfcDoseEquivalentMeasure,
		BlueFramework::Ifc2x3::IfcDraughtingCallout,
		BlueFramework::Ifc2x3::IfcDraughtingCalloutElement,
		BlueFramework::Ifc2x3::IfcDraughtingCalloutRelationship,
		BlueFramework::Ifc2x3::IfcDraughtingPreDefinedColour,
		BlueFramework::Ifc2x3::IfcDraughtingPreDefinedCurveFont,
		BlueFramework::Ifc2x3::IfcDraughtingPreDefinedTextFont,
		BlueFramework::Ifc2x3::IfcDuctFittingType,
		BlueFramework::Ifc2x3::IfcDuctFittingTypeEnum,
		BlueFramework::Ifc2x3::IfcDuctSegmentType,
		BlueFramework::Ifc2x3::IfcDuctSegmentTypeEnum,
		BlueFramework::Ifc2x3::IfcDuctSilencerType,
		BlueFramework::Ifc2x3::IfcDuctSilencerTypeEnum,
		BlueFramework::Ifc2x3::IfcDynamicViscosityMeasure,
		BlueFramework::Ifc2x3::IfcEdge,
		BlueFramework::Ifc2x3::IfcEdgeCurve,
		BlueFramework::Ifc2x3::IfcEdgeFeature,
		BlueFramework::Ifc2x3::IfcEdgeLoop,
		BlueFramework::Ifc2x3::IfcElectricalBaseProperties,
		BlueFramework::Ifc2x3::IfcElectricalCircuit,
		BlueFramework::Ifc2x3::IfcElectricalElement,
		BlueFramework::Ifc2x3::IfcElectricApplianceType,
		BlueFramework::Ifc2x3::IfcElectricApplianceTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricCapacitanceMeasure,
		BlueFramework::Ifc2x3::IfcElectricChargeMeasure,
		BlueFramework::Ifc2x3::IfcElectricConductanceMeasure,
		BlueFramework::Ifc2x3::IfcElectricCurrentEnum,
		BlueFramework::Ifc2x3::IfcElectricCurrentMeasure,
		BlueFramework::Ifc2x3::IfcElectricDistributionPoint,
		BlueFramework::Ifc2x3::IfcElectricDistributionPointFunctionEnum,
		BlueFramework::Ifc2x3::IfcElectricFlowStorageDeviceType,
		BlueFramework::Ifc2x3::IfcElectricFlowStorageDeviceTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricGeneratorType,
		BlueFramework::Ifc2x3::IfcElectricGeneratorTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricHeaterType,
		BlueFramework::Ifc2x3::IfcElectricHeaterTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricMotorType,
		BlueFramework::Ifc2x3::IfcElectricMotorTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricResistanceMeasure,
		BlueFramework::Ifc2x3::IfcElectricTimeControlType,
		BlueFramework::Ifc2x3::IfcElectricTimeControlTypeEnum,
		BlueFramework::Ifc2x3::IfcElectricVoltageMeasure,
		BlueFramework::Ifc2x3::IfcElement,
		BlueFramework::Ifc2x3::IfcElementarySurface,
		BlueFramework::Ifc2x3::IfcElementAssembly,
		BlueFramework::Ifc2x3::IfcElementAssemblyTypeEnum,
		BlueFramework::Ifc2x3::IfcElementComponent,
		BlueFramework::Ifc2x3::IfcElementComponentType,
		BlueFramework::Ifc2x3::IfcElementCompositionEnum,
		BlueFramework::Ifc2x3::IfcElementQuantity,
		BlueFramework::Ifc2x3::IfcElementType,
		BlueFramework::Ifc2x3::IfcEllipse,
		BlueFramework::Ifc2x3::IfcEllipseProfileDef,
		BlueFramework::Ifc2x3::IfcEnergyConversionDevice,
		BlueFramework::Ifc2x3::IfcEnergyConversionDeviceType,
		BlueFramework::Ifc2x3::IfcEnergyMeasure,
		BlueFramework::Ifc2x3::IfcEnergyProperties,
		BlueFramework::Ifc2x3::IfcEnergySequenceEnum,
		BlueFramework::Ifc2x3::IfcEnvironmentalImpactCategoryEnum,
		BlueFramework::Ifc2x3::IfcEnvironmentalImpactValue,
		BlueFramework::Ifc2x3::IfcEquipmentElement,
		BlueFramework::Ifc2x3::IfcEquipmentStandard,
		BlueFramework::Ifc2x3::IfcEvaporativeCoolerType,
		BlueFramework::Ifc2x3::IfcEvaporativeCoolerTypeEnum,
		BlueFramework::Ifc2x3::IfcEvaporatorType,
		BlueFramework::Ifc2x3::IfcEvaporatorTypeEnum,
		BlueFramework::Ifc2x3::IfcExtendedMaterialProperties,
		BlueFramework::Ifc2x3::IfcExternallyDefinedHatchStyle,
		BlueFramework::Ifc2x3::IfcExternallyDefinedSurfaceStyle,
		BlueFramework::Ifc2x3::IfcExternallyDefinedSymbol,
		BlueFramework::Ifc2x3::IfcExternallyDefinedTextFont,
		BlueFramework::Ifc2x3::IfcExternalReference,
		BlueFramework::Ifc2x3::IfcExtrudedAreaSolid,
		BlueFramework::Ifc2x3::IfcFace,
		BlueFramework::Ifc2x3::IfcFaceBasedSurfaceModel,
		BlueFramework::Ifc2x3::IfcFaceBound,
		BlueFramework::Ifc2x3::IfcFaceOuterBound,
		BlueFramework::Ifc2x3::IfcFaceSurface,
		BlueFramework::Ifc2x3::IfcFacetedBrep,
		BlueFramework::Ifc2x3::IfcFacetedBrepWithVoids,
		BlueFramework::Ifc2x3::IfcFailureConnectionCondition,
		BlueFramework::Ifc2x3::IfcFanType,
		BlueFramework::Ifc2x3::IfcFanTypeEnum,
		BlueFramework::Ifc2x3::IfcFastener,
		BlueFramework::Ifc2x3::IfcFastenerType,
		BlueFramework::Ifc2x3::IfcFeatureElement,
		BlueFramework::Ifc2x3::IfcFeatureElementAddition,
		BlueFramework::Ifc2x3::IfcFeatureElementSubtraction,
		BlueFramework::Ifc2x3::IfcFillAreaStyle,
		BlueFramework::Ifc2x3::IfcFillAreaStyleHatching,
		BlueFramework::Ifc2x3::IfcFillAreaStyleTiles,
		BlueFramework::Ifc2x3::IfcFillAreaStyleTileShapeSelect,
		BlueFramework::Ifc2x3::IfcFillAreaStyleTileSymbolWithStyle,
		BlueFramework::Ifc2x3::IfcFillStyleSelect,
		BlueFramework::Ifc2x3::IfcFilterType,
		BlueFramework::Ifc2x3::IfcFilterTypeEnum,
		BlueFramework::Ifc2x3::IfcFireSuppressionTerminalType,
		BlueFramework::Ifc2x3::IfcFireSuppressionTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcFlowController,
		BlueFramework::Ifc2x3::IfcFlowControllerType,
		BlueFramework::Ifc2x3::IfcFlowDirectionEnum,
		BlueFramework::Ifc2x3::IfcFlowFitting,
		BlueFramework::Ifc2x3::IfcFlowFittingType,
		BlueFramework::Ifc2x3::IfcFlowInstrumentType,
		BlueFramework::Ifc2x3::IfcFlowInstrumentTypeEnum,
		BlueFramework::Ifc2x3::IfcFlowMeterType,
		BlueFramework::Ifc2x3::IfcFlowMeterTypeEnum,
		BlueFramework::Ifc2x3::IfcFlowMovingDevice,
		BlueFramework::Ifc2x3::IfcFlowMovingDeviceType,
		BlueFramework::Ifc2x3::IfcFlowSegment,
		BlueFramework::Ifc2x3::IfcFlowSegmentType,
		BlueFramework::Ifc2x3::IfcFlowStorageDevice,
		BlueFramework::Ifc2x3::IfcFlowStorageDeviceType,
		BlueFramework::Ifc2x3::IfcFlowTerminal,
		BlueFramework::Ifc2x3::IfcFlowTerminalType,
		BlueFramework::Ifc2x3::IfcFlowTreatmentDevice,
		BlueFramework::Ifc2x3::IfcFlowTreatmentDeviceType,
		BlueFramework::Ifc2x3::IfcFluidFlowProperties,
		BlueFramework::Ifc2x3::IfcFontStyle,
		BlueFramework::Ifc2x3::IfcFontVariant,
		BlueFramework::Ifc2x3::IfcFontWeight,
		BlueFramework::Ifc2x3::IfcFooting,
		BlueFramework::Ifc2x3::IfcFootingTypeEnum,
		BlueFramework::Ifc2x3::IfcForceMeasure,
		BlueFramework::Ifc2x3::IfcFrequencyMeasure,
		BlueFramework::Ifc2x3::IfcFuelProperties,
		BlueFramework::Ifc2x3::IfcFurnishingElement,
		BlueFramework::Ifc2x3::IfcFurnishingElementType,
		BlueFramework::Ifc2x3::IfcFurnitureStandard,
		BlueFramework::Ifc2x3::IfcFurnitureType,
		BlueFramework::Ifc2x3::IfcGasTerminalType,
		BlueFramework::Ifc2x3::IfcGasTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcGeneralMaterialProperties,
		BlueFramework::Ifc2x3::IfcGeneralProfileProperties,
		BlueFramework::Ifc2x3::IfcGeometricCurveSet,
		BlueFramework::Ifc2x3::IfcGeometricProjectionEnum,
		BlueFramework::Ifc2x3::IfcGeometricRepresentationContext,
		BlueFramework::Ifc2x3::IfcGeometricRepresentationItem,
		BlueFramework::Ifc2x3::IfcGeometricRepresentationSubContext,
		BlueFramework::Ifc2x3::IfcGeometricSet,
		BlueFramework::Ifc2x3::IfcGeometricSetSelect,
		BlueFramework::Ifc2x3::IfcGloballyUniqueId,
		BlueFramework::Ifc2x3::IfcGlobalOrLocalEnum,
		BlueFramework::Ifc2x3::IfcGrid,
		BlueFramework::Ifc2x3::IfcGridAxis,
		BlueFramework::Ifc2x3::IfcGridPlacement,
		BlueFramework::Ifc2x3::IfcGroup,
		BlueFramework::Ifc2x3::IfcHalfSpaceSolid,
		BlueFramework::Ifc2x3::IfcHatchLineDistanceSelect,
		BlueFramework::Ifc2x3::IfcHeatExchangerType,
		BlueFramework::Ifc2x3::IfcHeatExchangerTypeEnum,
		BlueFramework::Ifc2x3::IfcHeatFluxDensityMeasure,
		BlueFramework::Ifc2x3::IfcHeatingValueMeasure,
		BlueFramework::Ifc2x3::IfcHourInDay,
		BlueFramework::Ifc2x3::IfcHumidifierType,
		BlueFramework::Ifc2x3::IfcHumidifierTypeEnum,
		BlueFramework::Ifc2x3::IfcHygroscopicMaterialProperties,
		BlueFramework::Ifc2x3::IfcIdentifier,
		BlueFramework::Ifc2x3::IfcIlluminanceMeasure,
		BlueFramework::Ifc2x3::IfcImageTexture,
		BlueFramework::Ifc2x3::IfcInductanceMeasure,
		BlueFramework::Ifc2x3::IfcInteger,
		BlueFramework::Ifc2x3::IfcIntegerCountRateMeasure,
		BlueFramework::Ifc2x3::IfcInternalOrExternalEnum,
		BlueFramework::Ifc2x3::IfcInventory,
		BlueFramework::Ifc2x3::IfcInventoryTypeEnum,
		BlueFramework::Ifc2x3::IfcIonConcentrationMeasure,
		BlueFramework::Ifc2x3::IfcIrregularTimeSeries,
		BlueFramework::Ifc2x3::IfcIrregularTimeSeriesValue,
		BlueFramework::Ifc2x3::IfcIShapeProfileDef,
		BlueFramework::Ifc2x3::IfcIsothermalMoistureCapacityMeasure,
		BlueFramework::Ifc2x3::IfcJunctionBoxType,
		BlueFramework::Ifc2x3::IfcJunctionBoxTypeEnum,
		BlueFramework::Ifc2x3::IfcKinematicViscosityMeasure,
		BlueFramework::Ifc2x3::IfcLabel,
		BlueFramework::Ifc2x3::IfcLaborResource,
		BlueFramework::Ifc2x3::IfcLampType,
		BlueFramework::Ifc2x3::IfcLampTypeEnum,
		BlueFramework::Ifc2x3::IfcLayeredItem,
		BlueFramework::Ifc2x3::IfcLayerSetDirectionEnum,
		BlueFramework::Ifc2x3::IfcLengthMeasure,
		BlueFramework::Ifc2x3::IfcLibraryInformation,
		BlueFramework::Ifc2x3::IfcLibraryReference,
		BlueFramework::Ifc2x3::IfcLibrarySelect,
		BlueFramework::Ifc2x3::IfcLightDistributionCurveEnum,
		BlueFramework::Ifc2x3::IfcLightDistributionData,
		BlueFramework::Ifc2x3::IfcLightDistributionDataSourceSelect,
		BlueFramework::Ifc2x3::IfcLightEmissionSourceEnum,
		BlueFramework::Ifc2x3::IfcLightFixtureType,
		BlueFramework::Ifc2x3::IfcLightFixtureTypeEnum,
		BlueFramework::Ifc2x3::IfcLightIntensityDistribution,
		BlueFramework::Ifc2x3::IfcLightSource,
		BlueFramework::Ifc2x3::IfcLightSourceAmbient,
		BlueFramework::Ifc2x3::IfcLightSourceDirectional,
		BlueFramework::Ifc2x3::IfcLightSourceGoniometric,
		BlueFramework::Ifc2x3::IfcLightSourcePositional,
		BlueFramework::Ifc2x3::IfcLightSourceSpot,
		BlueFramework::Ifc2x3::IfcLine,
		BlueFramework::Ifc2x3::IfcLinearDimension,
		BlueFramework::Ifc2x3::IfcLinearForceMeasure,
		BlueFramework::Ifc2x3::IfcLinearMomentMeasure,
		BlueFramework::Ifc2x3::IfcLinearStiffnessMeasure,
		BlueFramework::Ifc2x3::IfcLinearVelocityMeasure,
		BlueFramework::Ifc2x3::IfcLoadGroupTypeEnum,
		BlueFramework::Ifc2x3::IfcLocalPlacement,
		BlueFramework::Ifc2x3::IfcLocalTime,
		BlueFramework::Ifc2x3::IfcLogical,
		BlueFramework::Ifc2x3::IfcLogicalOperatorEnum,
		BlueFramework::Ifc2x3::IfcLoop,
		BlueFramework::Ifc2x3::IfcLShapeProfileDef,
		BlueFramework::Ifc2x3::IfcLuminousFluxMeasure,
		BlueFramework::Ifc2x3::IfcLuminousIntensityDistributionMeasure,
		BlueFramework::Ifc2x3::IfcLuminousIntensityMeasure,
		BlueFramework::Ifc2x3::IfcMagneticFluxDensityMeasure,
		BlueFramework::Ifc2x3::IfcMagneticFluxMeasure,
		BlueFramework::Ifc2x3::IfcManifoldSolidBrep,
		BlueFramework::Ifc2x3::IfcMappedItem,
		BlueFramework::Ifc2x3::IfcMassDensityMeasure,
		BlueFramework::Ifc2x3::IfcMassFlowRateMeasure,
		BlueFramework::Ifc2x3::IfcMassMeasure,
		BlueFramework::Ifc2x3::IfcMassPerLengthMeasure,
		BlueFramework::Ifc2x3::IfcMaterial,
		BlueFramework::Ifc2x3::IfcMaterialClassificationRelationship,
		BlueFramework::Ifc2x3::IfcMaterialDefinitionRepresentation,
		BlueFramework::Ifc2x3::IfcMaterialLayer,
		BlueFramework::Ifc2x3::IfcMaterialLayerSet,
		BlueFramework::Ifc2x3::IfcMaterialLayerSetUsage,
		BlueFramework::Ifc2x3::IfcMaterialList,
		BlueFramework::Ifc2x3::IfcMaterialProperties,
		BlueFramework::Ifc2x3::IfcMaterialSelect,
		BlueFramework::Ifc2x3::IfcMeasureValue,
		BlueFramework::Ifc2x3::IfcMeasureWithUnit,
		BlueFramework::Ifc2x3::IfcMechanicalConcreteMaterialProperties,
		BlueFramework::Ifc2x3::IfcMechanicalFastener,
		BlueFramework::Ifc2x3::IfcMechanicalFastenerType,
		BlueFramework::Ifc2x3::IfcMechanicalMaterialProperties,
		BlueFramework::Ifc2x3::IfcMechanicalSteelMaterialProperties,
		BlueFramework::Ifc2x3::IfcMember,
		BlueFramework::Ifc2x3::IfcMemberType,
		BlueFramework::Ifc2x3::IfcMemberTypeEnum,
		BlueFramework::Ifc2x3::IfcMetric,
		BlueFramework::Ifc2x3::IfcMetricValueSelect,
		BlueFramework::Ifc2x3::IfcMinuteInHour,
		BlueFramework::Ifc2x3::IfcModulusOfElasticityMeasure,
		BlueFramework::Ifc2x3::IfcModulusOfLinearSubgradeReactionMeasure,
		BlueFramework::Ifc2x3::IfcModulusOfRotationalSubgradeReactionMeasure,
		BlueFramework::Ifc2x3::IfcModulusOfSubgradeReactionMeasure,
		BlueFramework::Ifc2x3::IfcMoistureDiffusivityMeasure,
		BlueFramework::Ifc2x3::IfcMolecularWeightMeasure,
		BlueFramework::Ifc2x3::IfcMomentOfInertiaMeasure,
		BlueFramework::Ifc2x3::IfcMonetaryMeasure,
		BlueFramework::Ifc2x3::IfcMonetaryUnit,
		BlueFramework::Ifc2x3::IfcMonthInYearNumber,
		BlueFramework::Ifc2x3::IfcMotorConnectionType,
		BlueFramework::Ifc2x3::IfcMotorConnectionTypeEnum,
		BlueFramework::Ifc2x3::IfcMove,
		BlueFramework::Ifc2x3::IfcNamedUnit,
		BlueFramework::Ifc2x3::IfcNormalisedRatioMeasure,
		BlueFramework::Ifc2x3::IfcNullStyle,
		BlueFramework::Ifc2x3::IfcNumericMeasure,
		BlueFramework::Ifc2x3::IfcObject,
		BlueFramework::Ifc2x3::IfcObjectDefinition,
		BlueFramework::Ifc2x3::IfcObjective,
		BlueFramework::Ifc2x3::IfcObjectiveEnum,
		BlueFramework::Ifc2x3::IfcObjectPlacement,
		BlueFramework::Ifc2x3::IfcObjectReferenceSelect,
		BlueFramework::Ifc2x3::IfcObjectTypeEnum,
		BlueFramework::Ifc2x3::IfcOccupant,
		BlueFramework::Ifc2x3::IfcOccupantTypeEnum,
		BlueFramework::Ifc2x3::IfcOffsetCurve2D,
		BlueFramework::Ifc2x3::IfcOffsetCurve3D,
		BlueFramework::Ifc2x3::IfcOneDirectionRepeatFactor,
		BlueFramework::Ifc2x3::IfcOpeningElement,
		BlueFramework::Ifc2x3::IfcOpenShell,
		BlueFramework::Ifc2x3::IfcOpticalMaterialProperties,
		BlueFramework::Ifc2x3::IfcOrderAction,
		BlueFramework::Ifc2x3::IfcOrganization,
		BlueFramework::Ifc2x3::IfcOrganizationRelationship,
		BlueFramework::Ifc2x3::IfcOrientationSelect,
		BlueFramework::Ifc2x3::IfcOrientedEdge,
		BlueFramework::Ifc2x3::IfcOutletType,
		BlueFramework::Ifc2x3::IfcOutletTypeEnum,
		BlueFramework::Ifc2x3::IfcOwnerHistory,
		BlueFramework::Ifc2x3::IfcParameterizedProfileDef,
		BlueFramework::Ifc2x3::IfcParameterValue,
		BlueFramework::Ifc2x3::IfcPath,
		BlueFramework::Ifc2x3::IfcPerformanceHistory,
		BlueFramework::Ifc2x3::IfcPermeableCoveringOperationEnum,
		BlueFramework::Ifc2x3::IfcPermeableCoveringProperties,
		BlueFramework::Ifc2x3::IfcPermit,
		BlueFramework::Ifc2x3::IfcPerson,
		BlueFramework::Ifc2x3::IfcPersonAndOrganization,
		BlueFramework::Ifc2x3::IfcPHMeasure,
		BlueFramework::Ifc2x3::IfcPhysicalComplexQuantity,
		BlueFramework::Ifc2x3::IfcPhysicalOrVirtualEnum,
		BlueFramework::Ifc2x3::IfcPhysicalQuantity,
		BlueFramework::Ifc2x3::IfcPhysicalSimpleQuantity,
		BlueFramework::Ifc2x3::IfcPile,
		BlueFramework::Ifc2x3::IfcPileConstructionEnum,
		BlueFramework::Ifc2x3::IfcPileTypeEnum,
		BlueFramework::Ifc2x3::IfcPipeFittingType,
		BlueFramework::Ifc2x3::IfcPipeFittingTypeEnum,
		BlueFramework::Ifc2x3::IfcPipeSegmentType,
		BlueFramework::Ifc2x3::IfcPipeSegmentTypeEnum,
		BlueFramework::Ifc2x3::IfcPixelTexture,
		BlueFramework::Ifc2x3::IfcPlacement,
		BlueFramework::Ifc2x3::IfcPlanarBox,
		BlueFramework::Ifc2x3::IfcPlanarExtent,
		BlueFramework::Ifc2x3::IfcPlanarForceMeasure,
		BlueFramework::Ifc2x3::IfcPlane,
		BlueFramework::Ifc2x3::IfcPlaneAngleMeasure,
		BlueFramework::Ifc2x3::IfcPlate,
		BlueFramework::Ifc2x3::IfcPlateType,
		BlueFramework::Ifc2x3::IfcPlateTypeEnum,
		BlueFramework::Ifc2x3::IfcPoint,
		BlueFramework::Ifc2x3::IfcPointOnCurve,
		BlueFramework::Ifc2x3::IfcPointOnSurface,
		BlueFramework::Ifc2x3::IfcPointOrVertexPoint,
		BlueFramework::Ifc2x3::IfcPolygonalBoundedHalfSpace,
		BlueFramework::Ifc2x3::IfcPolyline,
		BlueFramework::Ifc2x3::IfcPolyLoop,
		BlueFramework::Ifc2x3::IfcPort,
		BlueFramework::Ifc2x3::IfcPositiveLengthMeasure,
		BlueFramework::Ifc2x3::IfcPositivePlaneAngleMeasure,
		BlueFramework::Ifc2x3::IfcPositiveRatioMeasure,
		BlueFramework::Ifc2x3::IfcPostalAddress,
		BlueFramework::Ifc2x3::IfcPowerMeasure,
		BlueFramework::Ifc2x3::IfcPreDefinedColour,
		BlueFramework::Ifc2x3::IfcPreDefinedCurveFont,
		BlueFramework::Ifc2x3::IfcPreDefinedDimensionSymbol,
		BlueFramework::Ifc2x3::IfcPreDefinedItem,
		BlueFramework::Ifc2x3::IfcPreDefinedPointMarkerSymbol,
		BlueFramework::Ifc2x3::IfcPreDefinedSymbol,
		BlueFramework::Ifc2x3::IfcPreDefinedTerminatorSymbol,
		BlueFramework::Ifc2x3::IfcPreDefinedTextFont,
		BlueFramework::Ifc2x3::IfcPresentableText,
		BlueFramework::Ifc2x3::IfcPresentationLayerAssignment,
		BlueFramework::Ifc2x3::IfcPresentationLayerWithStyle,
		BlueFramework::Ifc2x3::IfcPresentationStyle,
		BlueFramework::Ifc2x3::IfcPresentationStyleAssignment,
		BlueFramework::Ifc2x3::IfcPresentationStyleSelect,
		BlueFramework::Ifc2x3::IfcPressureMeasure,
		BlueFramework::Ifc2x3::IfcProcedure,
		BlueFramework::Ifc2x3::IfcProcedureTypeEnum,
		BlueFramework::Ifc2x3::IfcProcess,
		BlueFramework::Ifc2x3::IfcProduct,
		BlueFramework::Ifc2x3::IfcProductDefinitionShape,
		BlueFramework::Ifc2x3::IfcProductRepresentation,
		BlueFramework::Ifc2x3::IfcProductsOfCombustionProperties,
		BlueFramework::Ifc2x3::IfcProfileDef,
		BlueFramework::Ifc2x3::IfcProfileProperties,
		BlueFramework::Ifc2x3::IfcProfileTypeEnum,
		BlueFramework::Ifc2x3::IfcProject,
		BlueFramework::Ifc2x3::IfcProjectedOrTrueLengthEnum,
		BlueFramework::Ifc2x3::IfcProjectionCurve,
		BlueFramework::Ifc2x3::IfcProjectionElement,
		BlueFramework::Ifc2x3::IfcProjectOrder,
		BlueFramework::Ifc2x3::IfcProjectOrderRecord,
		BlueFramework::Ifc2x3::IfcProjectOrderRecordTypeEnum,
		BlueFramework::Ifc2x3::IfcProjectOrderTypeEnum,
		BlueFramework::Ifc2x3::IfcProperty,
		BlueFramework::Ifc2x3::IfcPropertyBoundedValue,
		BlueFramework::Ifc2x3::IfcPropertyConstraintRelationship,
		BlueFramework::Ifc2x3::IfcPropertyDefinition,
		BlueFramework::Ifc2x3::IfcPropertyDependencyRelationship,
		BlueFramework::Ifc2x3::IfcPropertyEnumeratedValue,
		BlueFramework::Ifc2x3::IfcPropertyEnumeration,
		BlueFramework::Ifc2x3::IfcPropertyListValue,
		BlueFramework::Ifc2x3::IfcPropertyReferenceValue,
		BlueFramework::Ifc2x3::IfcPropertySet,
		BlueFramework::Ifc2x3::IfcPropertySetDefinition,
		BlueFramework::Ifc2x3::IfcPropertySingleValue,
		BlueFramework::Ifc2x3::IfcPropertySourceEnum,
		BlueFramework::Ifc2x3::IfcPropertyTableValue,
		BlueFramework::Ifc2x3::IfcProtectiveDeviceType,
		BlueFramework::Ifc2x3::IfcProtectiveDeviceTypeEnum,
		BlueFramework::Ifc2x3::IfcProxy,
		BlueFramework::Ifc2x3::IfcPumpType,
		BlueFramework::Ifc2x3::IfcPumpTypeEnum,
		BlueFramework::Ifc2x3::IfcQuantityArea,
		BlueFramework::Ifc2x3::IfcQuantityCount,
		BlueFramework::Ifc2x3::IfcQuantityLength,
		BlueFramework::Ifc2x3::IfcQuantityTime,
		BlueFramework::Ifc2x3::IfcQuantityVolume,
		BlueFramework::Ifc2x3::IfcQuantityWeight,
		BlueFramework::Ifc2x3::IfcRadioActivityMeasure,
		BlueFramework::Ifc2x3::IfcRadiusDimension,
		BlueFramework::Ifc2x3::IfcRailing,
		BlueFramework::Ifc2x3::IfcRailingType,
		BlueFramework::Ifc2x3::IfcRailingTypeEnum,
		BlueFramework::Ifc2x3::IfcRamp,
		BlueFramework::Ifc2x3::IfcRampFlight,
		BlueFramework::Ifc2x3::IfcRampFlightType,
		BlueFramework::Ifc2x3::IfcRampFlightTypeEnum,
		BlueFramework::Ifc2x3::IfcRampTypeEnum,
		BlueFramework::Ifc2x3::IfcRatioMeasure,
		BlueFramework::Ifc2x3::IfcRationalBezierCurve,
		BlueFramework::Ifc2x3::IfcReal,
		BlueFramework::Ifc2x3::IfcRectangleHollowProfileDef,
		BlueFramework::Ifc2x3::IfcRectangleProfileDef,
		BlueFramework::Ifc2x3::IfcRectangularPyramid,
		BlueFramework::Ifc2x3::IfcRectangularTrimmedSurface,
		BlueFramework::Ifc2x3::IfcReferencesValueDocument,
		BlueFramework::Ifc2x3::IfcReflectanceMethodEnum,
		BlueFramework::Ifc2x3::IfcRegularTimeSeries,
		BlueFramework::Ifc2x3::IfcReinforcementBarProperties,
		BlueFramework::Ifc2x3::IfcReinforcementDefinitionProperties,
		BlueFramework::Ifc2x3::IfcReinforcingBar,
		BlueFramework::Ifc2x3::IfcReinforcingBarRoleEnum,
		BlueFramework::Ifc2x3::IfcReinforcingBarSurfaceEnum,
		BlueFramework::Ifc2x3::IfcReinforcingElement,
		BlueFramework::Ifc2x3::IfcReinforcingMesh,
		BlueFramework::Ifc2x3::IfcRelAggregates,
		BlueFramework::Ifc2x3::IfcRelAssigns,
		BlueFramework::Ifc2x3::IfcRelAssignsTasks,
		BlueFramework::Ifc2x3::IfcRelAssignsToActor,
		BlueFramework::Ifc2x3::IfcRelAssignsToControl,
		BlueFramework::Ifc2x3::IfcRelAssignsToGroup,
		BlueFramework::Ifc2x3::IfcRelAssignsToProcess,
		BlueFramework::Ifc2x3::IfcRelAssignsToProduct,
		BlueFramework::Ifc2x3::IfcRelAssignsToProjectOrder,
		BlueFramework::Ifc2x3::IfcRelAssignsToResource,
		BlueFramework::Ifc2x3::IfcRelAssociates,
		BlueFramework::Ifc2x3::IfcRelAssociatesAppliedValue,
		BlueFramework::Ifc2x3::IfcRelAssociatesApproval,
		BlueFramework::Ifc2x3::IfcRelAssociatesClassification,
		BlueFramework::Ifc2x3::IfcRelAssociatesConstraint,
		BlueFramework::Ifc2x3::IfcRelAssociatesDocument,
		BlueFramework::Ifc2x3::IfcRelAssociatesLibrary,
		BlueFramework::Ifc2x3::IfcRelAssociatesMaterial,
		BlueFramework::Ifc2x3::IfcRelAssociatesProfileProperties,
		BlueFramework::Ifc2x3::IfcRelationship,
		BlueFramework::Ifc2x3::IfcRelaxation,
		BlueFramework::Ifc2x3::IfcRelConnects,
		BlueFramework::Ifc2x3::IfcRelConnectsElements,
		BlueFramework::Ifc2x3::IfcRelConnectsPathElements,
		BlueFramework::Ifc2x3::IfcRelConnectsPorts,
		BlueFramework::Ifc2x3::IfcRelConnectsPortToElement,
		BlueFramework::Ifc2x3::IfcRelConnectsStructuralActivity,
		BlueFramework::Ifc2x3::IfcRelConnectsStructuralElement,
		BlueFramework::Ifc2x3::IfcRelConnectsStructuralMember,
		BlueFramework::Ifc2x3::IfcRelConnectsWithEccentricity,
		BlueFramework::Ifc2x3::IfcRelConnectsWithRealizingElements,
		BlueFramework::Ifc2x3::IfcRelContainedInSpatialStructure,
		BlueFramework::Ifc2x3::IfcRelCoversBldgElements,
		BlueFramework::Ifc2x3::IfcRelCoversSpaces,
		BlueFramework::Ifc2x3::IfcRelDecomposes,
		BlueFramework::Ifc2x3::IfcRelDefines,
		BlueFramework::Ifc2x3::IfcRelDefinesByProperties,
		BlueFramework::Ifc2x3::IfcRelDefinesByType,
		BlueFramework::Ifc2x3::IfcRelFillsElement,
		BlueFramework::Ifc2x3::IfcRelFlowControlElements,
		BlueFramework::Ifc2x3::IfcRelInteractionRequirements,
		BlueFramework::Ifc2x3::IfcRelNests,
		BlueFramework::Ifc2x3::IfcRelOccupiesSpaces,
		BlueFramework::Ifc2x3::IfcRelOverridesProperties,
		BlueFramework::Ifc2x3::IfcRelProjectsElement,
		BlueFramework::Ifc2x3::IfcRelReferencedInSpatialStructure,
		BlueFramework::Ifc2x3::IfcRelSchedulesCostItems,
		BlueFramework::Ifc2x3::IfcRelSequence,
		BlueFramework::Ifc2x3::IfcRelServicesBuildings,
		BlueFramework::Ifc2x3::IfcRelSpaceBoundary,
		BlueFramework::Ifc2x3::IfcRelVoidsElement,
		BlueFramework::Ifc2x3::IfcRepresentation,
		BlueFramework::Ifc2x3::IfcRepresentationContext,
		BlueFramework::Ifc2x3::IfcRepresentationItem,
		BlueFramework::Ifc2x3::IfcRepresentationMap,
		BlueFramework::Ifc2x3::IfcResource,
		BlueFramework::Ifc2x3::IfcResourceConsumptionEnum,
		BlueFramework::Ifc2x3::IfcRevolvedAreaSolid,
		BlueFramework::Ifc2x3::IfcRibPlateDirectionEnum,
		BlueFramework::Ifc2x3::IfcRibPlateProfileProperties,
		BlueFramework::Ifc2x3::IfcRightCircularCone,
		BlueFramework::Ifc2x3::IfcRightCircularCylinder,
		BlueFramework::Ifc2x3::IfcRoleEnum,
		BlueFramework::Ifc2x3::IfcRoof,
		BlueFramework::Ifc2x3::IfcRoofTypeEnum,
		BlueFramework::Ifc2x3::IfcRoot,
		BlueFramework::Ifc2x3::IfcRotationalFrequencyMeasure,
		BlueFramework::Ifc2x3::IfcRotationalMassMeasure,
		BlueFramework::Ifc2x3::IfcRotationalStiffnessMeasure,
		BlueFramework::Ifc2x3::IfcRoundedEdgeFeature,
		BlueFramework::Ifc2x3::IfcRoundedRectangleProfileDef,
		BlueFramework::Ifc2x3::IfcSanitaryTerminalType,
		BlueFramework::Ifc2x3::IfcSanitaryTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcScheduleTimeControl,
		BlueFramework::Ifc2x3::IfcSecondInMinute,
		BlueFramework::Ifc2x3::IfcSectionalAreaIntegralMeasure,
		BlueFramework::Ifc2x3::IfcSectionedSpine,
		BlueFramework::Ifc2x3::IfcSectionModulusMeasure,
		BlueFramework::Ifc2x3::IfcSectionProperties,
		BlueFramework::Ifc2x3::IfcSectionReinforcementProperties,
		BlueFramework::Ifc2x3::IfcSectionTypeEnum,
		BlueFramework::Ifc2x3::IfcSensorType,
		BlueFramework::Ifc2x3::IfcSensorTypeEnum,
		BlueFramework::Ifc2x3::IfcSequenceEnum,
		BlueFramework::Ifc2x3::IfcServiceLife,
		BlueFramework::Ifc2x3::IfcServiceLifeFactor,
		BlueFramework::Ifc2x3::IfcServiceLifeFactorTypeEnum,
		BlueFramework::Ifc2x3::IfcServiceLifeTypeEnum,
		BlueFramework::Ifc2x3::IfcShapeAspect,
		BlueFramework::Ifc2x3::IfcShapeModel,
		BlueFramework::Ifc2x3::IfcShapeRepresentation,
		BlueFramework::Ifc2x3::IfcShearModulusMeasure,
		BlueFramework::Ifc2x3::IfcShell,
		BlueFramework::Ifc2x3::IfcShellBasedSurfaceModel,
		BlueFramework::Ifc2x3::IfcSimpleProperty,
		BlueFramework::Ifc2x3::IfcSimpleValue,
		BlueFramework::Ifc2x3::IfcSIPrefix,
		BlueFramework::Ifc2x3::IfcSite,
		BlueFramework::Ifc2x3::IfcSIUnit,
		BlueFramework::Ifc2x3::IfcSIUnitName,
		BlueFramework::Ifc2x3::IfcSizeSelect,
		BlueFramework::Ifc2x3::IfcSlab,
		BlueFramework::Ifc2x3::IfcSlabType,
		BlueFramework::Ifc2x3::IfcSlabTypeEnum,
		BlueFramework::Ifc2x3::IfcSlippageConnectionCondition,
		BlueFramework::Ifc2x3::IfcSolidAngleMeasure,
		BlueFramework::Ifc2x3::IfcSolidModel,
		BlueFramework::Ifc2x3::IfcSoundPowerMeasure,
		BlueFramework::Ifc2x3::IfcSoundPressureMeasure,
		BlueFramework::Ifc2x3::IfcSoundProperties,
		BlueFramework::Ifc2x3::IfcSoundScaleEnum,
		BlueFramework::Ifc2x3::IfcSoundValue,
		BlueFramework::Ifc2x3::IfcSpace,
		BlueFramework::Ifc2x3::IfcSpaceHeaterType,
		BlueFramework::Ifc2x3::IfcSpaceHeaterTypeEnum,
		BlueFramework::Ifc2x3::IfcSpaceProgram,
		BlueFramework::Ifc2x3::IfcSpaceThermalLoadProperties,
		BlueFramework::Ifc2x3::IfcSpaceType,
		BlueFramework::Ifc2x3::IfcSpaceTypeEnum,
		BlueFramework::Ifc2x3::IfcSpatialStructureElement,
		BlueFramework::Ifc2x3::IfcSpatialStructureElementType,
		BlueFramework::Ifc2x3::IfcSpecificHeatCapacityMeasure,
		BlueFramework::Ifc2x3::IfcSpecularExponent,
		BlueFramework::Ifc2x3::IfcSpecularHighlightSelect,
		BlueFramework::Ifc2x3::IfcSpecularRoughness,
		BlueFramework::Ifc2x3::IfcSphere,
		BlueFramework::Ifc2x3::IfcStackTerminalType,
		BlueFramework::Ifc2x3::IfcStackTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcStair,
		BlueFramework::Ifc2x3::IfcStairFlight,
		BlueFramework::Ifc2x3::IfcStairFlightType,
		BlueFramework::Ifc2x3::IfcStairFlightTypeEnum,
		BlueFramework::Ifc2x3::IfcStairTypeEnum,
		BlueFramework::Ifc2x3::IfcStateEnum,
		BlueFramework::Ifc2x3::IfcStructuralAction,
		BlueFramework::Ifc2x3::IfcStructuralActivity,
		BlueFramework::Ifc2x3::IfcStructuralActivityAssignmentSelect,
		BlueFramework::Ifc2x3::IfcStructuralAnalysisModel,
		BlueFramework::Ifc2x3::IfcStructuralConnection,
		BlueFramework::Ifc2x3::IfcStructuralConnectionCondition,
		BlueFramework::Ifc2x3::IfcStructuralCurveConnection,
		BlueFramework::Ifc2x3::IfcStructuralCurveMember,
		BlueFramework::Ifc2x3::IfcStructuralCurveMemberVarying,
		BlueFramework::Ifc2x3::IfcStructuralCurveTypeEnum,
		BlueFramework::Ifc2x3::IfcStructuralItem,
		BlueFramework::Ifc2x3::IfcStructuralLinearAction,
		BlueFramework::Ifc2x3::IfcStructuralLinearActionVarying,
		BlueFramework::Ifc2x3::IfcStructuralLoad,
		BlueFramework::Ifc2x3::IfcStructuralLoadGroup,
		BlueFramework::Ifc2x3::IfcStructuralLoadLinearForce,
		BlueFramework::Ifc2x3::IfcStructuralLoadPlanarForce,
		BlueFramework::Ifc2x3::IfcStructuralLoadSingleDisplacement,
		BlueFramework::Ifc2x3::IfcStructuralLoadSingleDisplacementDistortion,
		BlueFramework::Ifc2x3::IfcStructuralLoadSingleForce,
		BlueFramework::Ifc2x3::IfcStructuralLoadSingleForceWarping,
		BlueFramework::Ifc2x3::IfcStructuralLoadStatic,
		BlueFramework::Ifc2x3::IfcStructuralLoadTemperature,
		BlueFramework::Ifc2x3::IfcStructuralMember,
		BlueFramework::Ifc2x3::IfcStructuralPlanarAction,
		BlueFramework::Ifc2x3::IfcStructuralPlanarActionVarying,
		BlueFramework::Ifc2x3::IfcStructuralPointAction,
		BlueFramework::Ifc2x3::IfcStructuralPointConnection,
		BlueFramework::Ifc2x3::IfcStructuralPointReaction,
		BlueFramework::Ifc2x3::IfcStructuralProfileProperties,
		BlueFramework::Ifc2x3::IfcStructuralReaction,
		BlueFramework::Ifc2x3::IfcStructuralResultGroup,
		BlueFramework::Ifc2x3::IfcStructuralSteelProfileProperties,
		BlueFramework::Ifc2x3::IfcStructuralSurfaceConnection,
		BlueFramework::Ifc2x3::IfcStructuralSurfaceMember,
		BlueFramework::Ifc2x3::IfcStructuralSurfaceMemberVarying,
		BlueFramework::Ifc2x3::IfcStructuralSurfaceTypeEnum,
		BlueFramework::Ifc2x3::IfcStructuredDimensionCallout,
		BlueFramework::Ifc2x3::IfcStyledItem,
		BlueFramework::Ifc2x3::IfcStyledRepresentation,
		BlueFramework::Ifc2x3::IfcStyleModel,
		BlueFramework::Ifc2x3::IfcSubContractResource,
		BlueFramework::Ifc2x3::IfcSubedge,
		BlueFramework::Ifc2x3::IfcSurface,
		BlueFramework::Ifc2x3::IfcSurfaceCurveSweptAreaSolid,
		BlueFramework::Ifc2x3::IfcSurfaceOfLinearExtrusion,
		BlueFramework::Ifc2x3::IfcSurfaceOfRevolution,
		BlueFramework::Ifc2x3::IfcSurfaceOrFaceSurface,
		BlueFramework::Ifc2x3::IfcSurfaceSide,
		BlueFramework::Ifc2x3::IfcSurfaceStyle,
		BlueFramework::Ifc2x3::IfcSurfaceStyleElementSelect,
		BlueFramework::Ifc2x3::IfcSurfaceStyleLighting,
		BlueFramework::Ifc2x3::IfcSurfaceStyleRefraction,
		BlueFramework::Ifc2x3::IfcSurfaceStyleRendering,
		BlueFramework::Ifc2x3::IfcSurfaceStyleShading,
		BlueFramework::Ifc2x3::IfcSurfaceStyleWithTextures,
		BlueFramework::Ifc2x3::IfcSurfaceTexture,
		BlueFramework::Ifc2x3::IfcSurfaceTextureEnum,
		BlueFramework::Ifc2x3::IfcSweptAreaSolid,
		BlueFramework::Ifc2x3::IfcSweptDiskSolid,
		BlueFramework::Ifc2x3::IfcSweptSurface,
		BlueFramework::Ifc2x3::IfcSwitchingDeviceType,
		BlueFramework::Ifc2x3::IfcSwitchingDeviceTypeEnum,
		BlueFramework::Ifc2x3::IfcSymbolStyle,
		BlueFramework::Ifc2x3::IfcSymbolStyleSelect,
		BlueFramework::Ifc2x3::IfcSystem,
		BlueFramework::Ifc2x3::IfcSystemFurnitureElementType,
		BlueFramework::Ifc2x3::IfcTable,
		BlueFramework::Ifc2x3::IfcTableRow,
		BlueFramework::Ifc2x3::IfcTankType,
		BlueFramework::Ifc2x3::IfcTankTypeEnum,
		BlueFramework::Ifc2x3::IfcTask,
		BlueFramework::Ifc2x3::IfcTelecomAddress,
		BlueFramework::Ifc2x3::IfcTemperatureGradientMeasure,
		BlueFramework::Ifc2x3::IfcTendon,
		BlueFramework::Ifc2x3::IfcTendonAnchor,
		BlueFramework::Ifc2x3::IfcTendonTypeEnum,
		BlueFramework::Ifc2x3::IfcTerminatorSymbol,
		BlueFramework::Ifc2x3::IfcText,
		BlueFramework::Ifc2x3::IfcTextAlignment,
		BlueFramework::Ifc2x3::IfcTextDecoration,
		BlueFramework::Ifc2x3::IfcTextFontName,
		BlueFramework::Ifc2x3::IfcTextFontSelect,
		BlueFramework::Ifc2x3::IfcTextLiteral,
		BlueFramework::Ifc2x3::IfcTextLiteralWithExtent,
		BlueFramework::Ifc2x3::IfcTextPath,
		BlueFramework::Ifc2x3::IfcTextStyle,
		BlueFramework::Ifc2x3::IfcTextStyleFontModel,
		BlueFramework::Ifc2x3::IfcTextStyleForDefinedFont,
		BlueFramework::Ifc2x3::IfcTextStyleSelect,
		BlueFramework::Ifc2x3::IfcTextStyleTextModel,
		BlueFramework::Ifc2x3::IfcTextStyleWithBoxCharacteristics,
		BlueFramework::Ifc2x3::IfcTextTransformation,
		BlueFramework::Ifc2x3::IfcTextureCoordinate,
		BlueFramework::Ifc2x3::IfcTextureCoordinateGenerator,
		BlueFramework::Ifc2x3::IfcTextureMap,
		BlueFramework::Ifc2x3::IfcTextureVertex,
		BlueFramework::Ifc2x3::IfcThermalAdmittanceMeasure,
		BlueFramework::Ifc2x3::IfcThermalConductivityMeasure,
		BlueFramework::Ifc2x3::IfcThermalExpansionCoefficientMeasure,
		BlueFramework::Ifc2x3::IfcThermalLoadSourceEnum,
		BlueFramework::Ifc2x3::IfcThermalLoadTypeEnum,
		BlueFramework::Ifc2x3::IfcThermalMaterialProperties,
		BlueFramework::Ifc2x3::IfcThermalResistanceMeasure,
		BlueFramework::Ifc2x3::IfcThermalTransmittanceMeasure,
		BlueFramework::Ifc2x3::IfcThermodynamicTemperatureMeasure,
		BlueFramework::Ifc2x3::IfcTimeMeasure,
		BlueFramework::Ifc2x3::IfcTimeSeries,
		BlueFramework::Ifc2x3::IfcTimeSeriesDataTypeEnum,
		BlueFramework::Ifc2x3::IfcTimeSeriesReferenceRelationship,
		BlueFramework::Ifc2x3::IfcTimeSeriesSchedule,
		BlueFramework::Ifc2x3::IfcTimeSeriesScheduleTypeEnum,
		BlueFramework::Ifc2x3::IfcTimeSeriesValue,
		BlueFramework::Ifc2x3::IfcTimeStamp,
		BlueFramework::Ifc2x3::IfcTopologicalRepresentationItem,
		BlueFramework::Ifc2x3::IfcTopologyRepresentation,
		BlueFramework::Ifc2x3::IfcTorqueMeasure,
		BlueFramework::Ifc2x3::IfcTransformerType,
		BlueFramework::Ifc2x3::IfcTransformerTypeEnum,
		BlueFramework::Ifc2x3::IfcTransitionCode,
		BlueFramework::Ifc2x3::IfcTransportElement,
		BlueFramework::Ifc2x3::IfcTransportElementType,
		BlueFramework::Ifc2x3::IfcTransportElementTypeEnum,
		BlueFramework::Ifc2x3::IfcTrapeziumProfileDef,
		BlueFramework::Ifc2x3::IfcTrimmedCurve,
		BlueFramework::Ifc2x3::IfcTrimmingPreference,
		BlueFramework::Ifc2x3::IfcTrimmingSelect,
		BlueFramework::Ifc2x3::IfcTShapeProfileDef,
		BlueFramework::Ifc2x3::IfcTubeBundleType,
		BlueFramework::Ifc2x3::IfcTubeBundleTypeEnum,
		BlueFramework::Ifc2x3::IfcTwoDirectionRepeatFactor,
		BlueFramework::Ifc2x3::IfcTypeObject,
		BlueFramework::Ifc2x3::IfcTypeProduct,
		BlueFramework::Ifc2x3::IfcUnit,
		BlueFramework::Ifc2x3::IfcUnitaryEquipmentType,
		BlueFramework::Ifc2x3::IfcUnitaryEquipmentTypeEnum,
		BlueFramework::Ifc2x3::IfcUnitAssignment,
		BlueFramework::Ifc2x3::IfcUnitEnum,
		BlueFramework::Ifc2x3::IfcUShapeProfileDef,
		BlueFramework::Ifc2x3::IfcValue,
		BlueFramework::Ifc2x3::IfcValveType,
		BlueFramework::Ifc2x3::IfcValveTypeEnum,
		BlueFramework::Ifc2x3::IfcVaporPermeabilityMeasure,
		BlueFramework::Ifc2x3::IfcVector,
		BlueFramework::Ifc2x3::IfcVectorOrDirection,
		BlueFramework::Ifc2x3::IfcVertex,
		BlueFramework::Ifc2x3::IfcVertexBasedTextureMap,
		BlueFramework::Ifc2x3::IfcVertexLoop,
		BlueFramework::Ifc2x3::IfcVertexPoint,
		BlueFramework::Ifc2x3::IfcVibrationIsolatorType,
		BlueFramework::Ifc2x3::IfcVibrationIsolatorTypeEnum,
		BlueFramework::Ifc2x3::IfcVirtualElement,
		BlueFramework::Ifc2x3::IfcVirtualGridIntersection,
		BlueFramework::Ifc2x3::IfcVolumeMeasure,
		BlueFramework::Ifc2x3::IfcVolumetricFlowRateMeasure,
		BlueFramework::Ifc2x3::IfcWall,
		BlueFramework::Ifc2x3::IfcWallStandardCase,
		BlueFramework::Ifc2x3::IfcWallType,
		BlueFramework::Ifc2x3::IfcWallTypeEnum,
		BlueFramework::Ifc2x3::IfcWarpingConstantMeasure,
		BlueFramework::Ifc2x3::IfcWarpingMomentMeasure,
		BlueFramework::Ifc2x3::IfcWasteTerminalType,
		BlueFramework::Ifc2x3::IfcWasteTerminalTypeEnum,
		BlueFramework::Ifc2x3::IfcWaterProperties,
		BlueFramework::Ifc2x3::IfcWindow,
		BlueFramework::Ifc2x3::IfcWindowLiningProperties,
		BlueFramework::Ifc2x3::IfcWindowPanelOperationEnum,
		BlueFramework::Ifc2x3::IfcWindowPanelPositionEnum,
		BlueFramework::Ifc2x3::IfcWindowPanelProperties,
		BlueFramework::Ifc2x3::IfcWindowStyle,
		BlueFramework::Ifc2x3::IfcWindowStyleConstructionEnum,
		BlueFramework::Ifc2x3::IfcWindowStyleOperationEnum,
		BlueFramework::Ifc2x3::IfcWorkControl,
		BlueFramework::Ifc2x3::IfcWorkControlTypeEnum,
		BlueFramework::Ifc2x3::IfcWorkPlan,
		BlueFramework::Ifc2x3::IfcWorkSchedule,
		BlueFramework::Ifc2x3::IfcYearNumber,
		BlueFramework::Ifc2x3::IfcZone,
		BlueFramework::Ifc2x3::IfcZShapeProfileDef,
	>
	Ifc2x3EntityTypes;
}
