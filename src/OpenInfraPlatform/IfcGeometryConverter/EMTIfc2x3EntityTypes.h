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

#include "EMTBasicIfc2x3EntityTypes.h"

namespace OpenInfraPlatform
{
	namespace Ifc2x3
	{
		 class Ifc2DCompositeCurve;
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
	typedef BasicIfc2x3EntityTypes<
		OpenInfraPlatform::Ifc2x3::Ifc2DCompositeCurve,
		OpenInfraPlatform::Ifc2x3::IfcAbsorbedDoseMeasure,
		OpenInfraPlatform::Ifc2x3::IfcAccelerationMeasure,
		OpenInfraPlatform::Ifc2x3::IfcActionRequest,
		OpenInfraPlatform::Ifc2x3::IfcActionSourceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcActionTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcActor,
		OpenInfraPlatform::Ifc2x3::IfcActorRole,
		OpenInfraPlatform::Ifc2x3::IfcActorSelect,
		OpenInfraPlatform::Ifc2x3::IfcActuatorType,
		OpenInfraPlatform::Ifc2x3::IfcActuatorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAddress,
		OpenInfraPlatform::Ifc2x3::IfcAddressTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAheadOrBehind,
		OpenInfraPlatform::Ifc2x3::IfcAirTerminalBoxType,
		OpenInfraPlatform::Ifc2x3::IfcAirTerminalBoxTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAirTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcAirTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAirToAirHeatRecoveryType,
		OpenInfraPlatform::Ifc2x3::IfcAirToAirHeatRecoveryTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAlarmType,
		OpenInfraPlatform::Ifc2x3::IfcAlarmTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAmountOfSubstanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcAnalysisModelTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAnalysisTheoryTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcAngularDimension,
		OpenInfraPlatform::Ifc2x3::IfcAngularVelocityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcAnnotation,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationCurveOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationFillArea,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationFillAreaOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationSurface,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationSurfaceOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationSymbolOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcAnnotationTextOccurrence,
		OpenInfraPlatform::Ifc2x3::IfcApplication,
		OpenInfraPlatform::Ifc2x3::IfcAppliedValue,
		OpenInfraPlatform::Ifc2x3::IfcAppliedValueRelationship,
		OpenInfraPlatform::Ifc2x3::IfcAppliedValueSelect,
		OpenInfraPlatform::Ifc2x3::IfcApproval,
		OpenInfraPlatform::Ifc2x3::IfcApprovalActorRelationship,
		OpenInfraPlatform::Ifc2x3::IfcApprovalPropertyRelationship,
		OpenInfraPlatform::Ifc2x3::IfcApprovalRelationship,
		OpenInfraPlatform::Ifc2x3::IfcArbitraryClosedProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcArbitraryOpenProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcArbitraryProfileDefWithVoids,
		OpenInfraPlatform::Ifc2x3::IfcAreaMeasure,
		OpenInfraPlatform::Ifc2x3::IfcArithmeticOperatorEnum,
		OpenInfraPlatform::Ifc2x3::IfcAssemblyPlaceEnum,
		OpenInfraPlatform::Ifc2x3::IfcAsset,
		OpenInfraPlatform::Ifc2x3::IfcAsymmetricIShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcAxis1Placement,
		OpenInfraPlatform::Ifc2x3::IfcAxis2Placement,
		OpenInfraPlatform::Ifc2x3::IfcAxis2Placement2D,
		OpenInfraPlatform::Ifc2x3::IfcAxis2Placement3D,
		OpenInfraPlatform::Ifc2x3::IfcBeam,
		OpenInfraPlatform::Ifc2x3::IfcBeamType,
		OpenInfraPlatform::Ifc2x3::IfcBeamTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcBenchmarkEnum,
		OpenInfraPlatform::Ifc2x3::IfcBezierCurve,
		OpenInfraPlatform::Ifc2x3::IfcBlobTexture,
		OpenInfraPlatform::Ifc2x3::IfcBlock,
		OpenInfraPlatform::Ifc2x3::IfcBoilerType,
		OpenInfraPlatform::Ifc2x3::IfcBoilerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcBoolean,
		OpenInfraPlatform::Ifc2x3::IfcBooleanClippingResult,
		OpenInfraPlatform::Ifc2x3::IfcBooleanOperand,
		OpenInfraPlatform::Ifc2x3::IfcBooleanOperator,
		OpenInfraPlatform::Ifc2x3::IfcBooleanResult,
		OpenInfraPlatform::Ifc2x3::IfcBoundaryCondition,
		OpenInfraPlatform::Ifc2x3::IfcBoundaryEdgeCondition,
		OpenInfraPlatform::Ifc2x3::IfcBoundaryFaceCondition,
		OpenInfraPlatform::Ifc2x3::IfcBoundaryNodeCondition,
		OpenInfraPlatform::Ifc2x3::IfcBoundaryNodeConditionWarping,
		OpenInfraPlatform::Ifc2x3::IfcBoundedCurve,
		OpenInfraPlatform::Ifc2x3::IfcBoundedSurface,
		OpenInfraPlatform::Ifc2x3::IfcBoundingBox,
		OpenInfraPlatform::Ifc2x3::IfcBoxAlignment,
		OpenInfraPlatform::Ifc2x3::IfcBoxedHalfSpace,
		OpenInfraPlatform::Ifc2x3::IfcBSplineCurve,
		OpenInfraPlatform::Ifc2x3::IfcBSplineCurveForm,
		OpenInfraPlatform::Ifc2x3::IfcBuilding,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElement,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementComponent,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementPart,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementProxy,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementProxyType,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementProxyTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcBuildingElementType,
		OpenInfraPlatform::Ifc2x3::IfcBuildingStorey,
		OpenInfraPlatform::Ifc2x3::IfcCableCarrierFittingType,
		OpenInfraPlatform::Ifc2x3::IfcCableCarrierFittingTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCableCarrierSegmentType,
		OpenInfraPlatform::Ifc2x3::IfcCableCarrierSegmentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCableSegmentType,
		OpenInfraPlatform::Ifc2x3::IfcCableSegmentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCalendarDate,
		OpenInfraPlatform::Ifc2x3::IfcCartesianPoint,
		OpenInfraPlatform::Ifc2x3::IfcCartesianTransformationOperator,
		OpenInfraPlatform::Ifc2x3::IfcCartesianTransformationOperator2D,
		OpenInfraPlatform::Ifc2x3::IfcCartesianTransformationOperator2DnonUniform,
		OpenInfraPlatform::Ifc2x3::IfcCartesianTransformationOperator3D,
		OpenInfraPlatform::Ifc2x3::IfcCartesianTransformationOperator3DnonUniform,
		OpenInfraPlatform::Ifc2x3::IfcCenterLineProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcChamferEdgeFeature,
		OpenInfraPlatform::Ifc2x3::IfcChangeActionEnum,
		OpenInfraPlatform::Ifc2x3::IfcCharacterStyleSelect,
		OpenInfraPlatform::Ifc2x3::IfcChillerType,
		OpenInfraPlatform::Ifc2x3::IfcChillerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCircle,
		OpenInfraPlatform::Ifc2x3::IfcCircleHollowProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcCircleProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcClassification,
		OpenInfraPlatform::Ifc2x3::IfcClassificationItem,
		OpenInfraPlatform::Ifc2x3::IfcClassificationItemRelationship,
		OpenInfraPlatform::Ifc2x3::IfcClassificationNotation,
		OpenInfraPlatform::Ifc2x3::IfcClassificationNotationFacet,
		OpenInfraPlatform::Ifc2x3::IfcClassificationNotationSelect,
		OpenInfraPlatform::Ifc2x3::IfcClassificationReference,
		OpenInfraPlatform::Ifc2x3::IfcClosedShell,
		OpenInfraPlatform::Ifc2x3::IfcCoilType,
		OpenInfraPlatform::Ifc2x3::IfcCoilTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcColour,
		OpenInfraPlatform::Ifc2x3::IfcColourOrFactor,
		OpenInfraPlatform::Ifc2x3::IfcColourRgb,
		OpenInfraPlatform::Ifc2x3::IfcColourSpecification,
		OpenInfraPlatform::Ifc2x3::IfcColumn,
		OpenInfraPlatform::Ifc2x3::IfcColumnType,
		OpenInfraPlatform::Ifc2x3::IfcColumnTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcComplexNumber,
		OpenInfraPlatform::Ifc2x3::IfcComplexProperty,
		OpenInfraPlatform::Ifc2x3::IfcCompositeCurve,
		OpenInfraPlatform::Ifc2x3::IfcCompositeCurveSegment,
		OpenInfraPlatform::Ifc2x3::IfcCompositeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcCompoundPlaneAngleMeasure,
		OpenInfraPlatform::Ifc2x3::IfcCompressorType,
		OpenInfraPlatform::Ifc2x3::IfcCompressorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCondenserType,
		OpenInfraPlatform::Ifc2x3::IfcCondenserTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCondition,
		OpenInfraPlatform::Ifc2x3::IfcConditionCriterion,
		OpenInfraPlatform::Ifc2x3::IfcConditionCriterionSelect,
		OpenInfraPlatform::Ifc2x3::IfcConic,
		OpenInfraPlatform::Ifc2x3::IfcConnectedFaceSet,
		OpenInfraPlatform::Ifc2x3::IfcConnectionCurveGeometry,
		OpenInfraPlatform::Ifc2x3::IfcConnectionGeometry,
		OpenInfraPlatform::Ifc2x3::IfcConnectionPointEccentricity,
		OpenInfraPlatform::Ifc2x3::IfcConnectionPointGeometry,
		OpenInfraPlatform::Ifc2x3::IfcConnectionPortGeometry,
		OpenInfraPlatform::Ifc2x3::IfcConnectionSurfaceGeometry,
		OpenInfraPlatform::Ifc2x3::IfcConnectionTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcConstraint,
		OpenInfraPlatform::Ifc2x3::IfcConstraintAggregationRelationship,
		OpenInfraPlatform::Ifc2x3::IfcConstraintClassificationRelationship,
		OpenInfraPlatform::Ifc2x3::IfcConstraintEnum,
		OpenInfraPlatform::Ifc2x3::IfcConstraintRelationship,
		OpenInfraPlatform::Ifc2x3::IfcConstructionEquipmentResource,
		OpenInfraPlatform::Ifc2x3::IfcConstructionMaterialResource,
		OpenInfraPlatform::Ifc2x3::IfcConstructionProductResource,
		OpenInfraPlatform::Ifc2x3::IfcConstructionResource,
		OpenInfraPlatform::Ifc2x3::IfcContextDependentMeasure,
		OpenInfraPlatform::Ifc2x3::IfcContextDependentUnit,
		OpenInfraPlatform::Ifc2x3::IfcControl,
		OpenInfraPlatform::Ifc2x3::IfcControllerType,
		OpenInfraPlatform::Ifc2x3::IfcControllerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcConversionBasedUnit,
		OpenInfraPlatform::Ifc2x3::IfcCooledBeamType,
		OpenInfraPlatform::Ifc2x3::IfcCooledBeamTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCoolingTowerType,
		OpenInfraPlatform::Ifc2x3::IfcCoolingTowerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCoordinatedUniversalTimeOffset,
		OpenInfraPlatform::Ifc2x3::IfcCostItem,
		OpenInfraPlatform::Ifc2x3::IfcCostSchedule,
		OpenInfraPlatform::Ifc2x3::IfcCostScheduleTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCostValue,
		OpenInfraPlatform::Ifc2x3::IfcCountMeasure,
		OpenInfraPlatform::Ifc2x3::IfcCovering,
		OpenInfraPlatform::Ifc2x3::IfcCoveringType,
		OpenInfraPlatform::Ifc2x3::IfcCoveringTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCraneRailAShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcCraneRailFShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcCrewResource,
		OpenInfraPlatform::Ifc2x3::IfcCsgPrimitive3D,
		OpenInfraPlatform::Ifc2x3::IfcCsgSelect,
		OpenInfraPlatform::Ifc2x3::IfcCsgSolid,
		OpenInfraPlatform::Ifc2x3::IfcCShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcCurrencyEnum,
		OpenInfraPlatform::Ifc2x3::IfcCurrencyRelationship,
		OpenInfraPlatform::Ifc2x3::IfcCurtainWall,
		OpenInfraPlatform::Ifc2x3::IfcCurtainWallType,
		OpenInfraPlatform::Ifc2x3::IfcCurtainWallTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcCurvatureMeasure,
		OpenInfraPlatform::Ifc2x3::IfcCurve,
		OpenInfraPlatform::Ifc2x3::IfcCurveBoundedPlane,
		OpenInfraPlatform::Ifc2x3::IfcCurveFontOrScaledCurveFontSelect,
		OpenInfraPlatform::Ifc2x3::IfcCurveOrEdgeCurve,
		OpenInfraPlatform::Ifc2x3::IfcCurveStyle,
		OpenInfraPlatform::Ifc2x3::IfcCurveStyleFont,
		OpenInfraPlatform::Ifc2x3::IfcCurveStyleFontAndScaling,
		OpenInfraPlatform::Ifc2x3::IfcCurveStyleFontPattern,
		OpenInfraPlatform::Ifc2x3::IfcCurveStyleFontSelect,
		OpenInfraPlatform::Ifc2x3::IfcDamperType,
		OpenInfraPlatform::Ifc2x3::IfcDamperTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcDataOriginEnum,
		OpenInfraPlatform::Ifc2x3::IfcDateAndTime,
		OpenInfraPlatform::Ifc2x3::IfcDateTimeSelect,
		OpenInfraPlatform::Ifc2x3::IfcDayInMonthNumber,
		OpenInfraPlatform::Ifc2x3::IfcDaylightSavingHour,
		OpenInfraPlatform::Ifc2x3::IfcDefinedSymbol,
		OpenInfraPlatform::Ifc2x3::IfcDefinedSymbolSelect,
		OpenInfraPlatform::Ifc2x3::IfcDerivedMeasureValue,
		OpenInfraPlatform::Ifc2x3::IfcDerivedProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcDerivedUnit,
		OpenInfraPlatform::Ifc2x3::IfcDerivedUnitElement,
		OpenInfraPlatform::Ifc2x3::IfcDerivedUnitEnum,
		OpenInfraPlatform::Ifc2x3::IfcDescriptiveMeasure,
		OpenInfraPlatform::Ifc2x3::IfcDiameterDimension,
		OpenInfraPlatform::Ifc2x3::IfcDimensionalExponents,
		OpenInfraPlatform::Ifc2x3::IfcDimensionCalloutRelationship,
		OpenInfraPlatform::Ifc2x3::IfcDimensionCount,
		OpenInfraPlatform::Ifc2x3::IfcDimensionCurve,
		OpenInfraPlatform::Ifc2x3::IfcDimensionCurveDirectedCallout,
		OpenInfraPlatform::Ifc2x3::IfcDimensionCurveTerminator,
		OpenInfraPlatform::Ifc2x3::IfcDimensionExtentUsage,
		OpenInfraPlatform::Ifc2x3::IfcDimensionPair,
		OpenInfraPlatform::Ifc2x3::IfcDirection,
		OpenInfraPlatform::Ifc2x3::IfcDirectionSenseEnum,
		OpenInfraPlatform::Ifc2x3::IfcDiscreteAccessory,
		OpenInfraPlatform::Ifc2x3::IfcDiscreteAccessoryType,
		OpenInfraPlatform::Ifc2x3::IfcDistributionChamberElement,
		OpenInfraPlatform::Ifc2x3::IfcDistributionChamberElementType,
		OpenInfraPlatform::Ifc2x3::IfcDistributionChamberElementTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcDistributionControlElement,
		OpenInfraPlatform::Ifc2x3::IfcDistributionControlElementType,
		OpenInfraPlatform::Ifc2x3::IfcDistributionElement,
		OpenInfraPlatform::Ifc2x3::IfcDistributionElementType,
		OpenInfraPlatform::Ifc2x3::IfcDistributionFlowElement,
		OpenInfraPlatform::Ifc2x3::IfcDistributionFlowElementType,
		OpenInfraPlatform::Ifc2x3::IfcDistributionPort,
		OpenInfraPlatform::Ifc2x3::IfcDocumentConfidentialityEnum,
		OpenInfraPlatform::Ifc2x3::IfcDocumentElectronicFormat,
		OpenInfraPlatform::Ifc2x3::IfcDocumentInformation,
		OpenInfraPlatform::Ifc2x3::IfcDocumentInformationRelationship,
		OpenInfraPlatform::Ifc2x3::IfcDocumentReference,
		OpenInfraPlatform::Ifc2x3::IfcDocumentSelect,
		OpenInfraPlatform::Ifc2x3::IfcDocumentStatusEnum,
		OpenInfraPlatform::Ifc2x3::IfcDoor,
		OpenInfraPlatform::Ifc2x3::IfcDoorLiningProperties,
		OpenInfraPlatform::Ifc2x3::IfcDoorPanelOperationEnum,
		OpenInfraPlatform::Ifc2x3::IfcDoorPanelPositionEnum,
		OpenInfraPlatform::Ifc2x3::IfcDoorPanelProperties,
		OpenInfraPlatform::Ifc2x3::IfcDoorStyle,
		OpenInfraPlatform::Ifc2x3::IfcDoorStyleConstructionEnum,
		OpenInfraPlatform::Ifc2x3::IfcDoorStyleOperationEnum,
		OpenInfraPlatform::Ifc2x3::IfcDoseEquivalentMeasure,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingCallout,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingCalloutElement,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingCalloutRelationship,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingPreDefinedColour,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingPreDefinedCurveFont,
		OpenInfraPlatform::Ifc2x3::IfcDraughtingPreDefinedTextFont,
		OpenInfraPlatform::Ifc2x3::IfcDuctFittingType,
		OpenInfraPlatform::Ifc2x3::IfcDuctFittingTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcDuctSegmentType,
		OpenInfraPlatform::Ifc2x3::IfcDuctSegmentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcDuctSilencerType,
		OpenInfraPlatform::Ifc2x3::IfcDuctSilencerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcDynamicViscosityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcEdge,
		OpenInfraPlatform::Ifc2x3::IfcEdgeCurve,
		OpenInfraPlatform::Ifc2x3::IfcEdgeFeature,
		OpenInfraPlatform::Ifc2x3::IfcEdgeLoop,
		OpenInfraPlatform::Ifc2x3::IfcElectricalBaseProperties,
		OpenInfraPlatform::Ifc2x3::IfcElectricalCircuit,
		OpenInfraPlatform::Ifc2x3::IfcElectricalElement,
		OpenInfraPlatform::Ifc2x3::IfcElectricApplianceType,
		OpenInfraPlatform::Ifc2x3::IfcElectricApplianceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricCapacitanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElectricChargeMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElectricConductanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElectricCurrentEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricCurrentMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElectricDistributionPoint,
		OpenInfraPlatform::Ifc2x3::IfcElectricDistributionPointFunctionEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricFlowStorageDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcElectricFlowStorageDeviceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricGeneratorType,
		OpenInfraPlatform::Ifc2x3::IfcElectricGeneratorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricHeaterType,
		OpenInfraPlatform::Ifc2x3::IfcElectricHeaterTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricMotorType,
		OpenInfraPlatform::Ifc2x3::IfcElectricMotorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricResistanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElectricTimeControlType,
		OpenInfraPlatform::Ifc2x3::IfcElectricTimeControlTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElectricVoltageMeasure,
		OpenInfraPlatform::Ifc2x3::IfcElement,
		OpenInfraPlatform::Ifc2x3::IfcElementarySurface,
		OpenInfraPlatform::Ifc2x3::IfcElementAssembly,
		OpenInfraPlatform::Ifc2x3::IfcElementAssemblyTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcElementComponent,
		OpenInfraPlatform::Ifc2x3::IfcElementComponentType,
		OpenInfraPlatform::Ifc2x3::IfcElementCompositionEnum,
		OpenInfraPlatform::Ifc2x3::IfcElementQuantity,
		OpenInfraPlatform::Ifc2x3::IfcElementType,
		OpenInfraPlatform::Ifc2x3::IfcEllipse,
		OpenInfraPlatform::Ifc2x3::IfcEllipseProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcEnergyConversionDevice,
		OpenInfraPlatform::Ifc2x3::IfcEnergyConversionDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcEnergyMeasure,
		OpenInfraPlatform::Ifc2x3::IfcEnergyProperties,
		OpenInfraPlatform::Ifc2x3::IfcEnergySequenceEnum,
		OpenInfraPlatform::Ifc2x3::IfcEnvironmentalImpactCategoryEnum,
		OpenInfraPlatform::Ifc2x3::IfcEnvironmentalImpactValue,
		OpenInfraPlatform::Ifc2x3::IfcEquipmentElement,
		OpenInfraPlatform::Ifc2x3::IfcEquipmentStandard,
		OpenInfraPlatform::Ifc2x3::IfcEvaporativeCoolerType,
		OpenInfraPlatform::Ifc2x3::IfcEvaporativeCoolerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcEvaporatorType,
		OpenInfraPlatform::Ifc2x3::IfcEvaporatorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcExtendedMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcExternallyDefinedHatchStyle,
		OpenInfraPlatform::Ifc2x3::IfcExternallyDefinedSurfaceStyle,
		OpenInfraPlatform::Ifc2x3::IfcExternallyDefinedSymbol,
		OpenInfraPlatform::Ifc2x3::IfcExternallyDefinedTextFont,
		OpenInfraPlatform::Ifc2x3::IfcExternalReference,
		OpenInfraPlatform::Ifc2x3::IfcExtrudedAreaSolid,
		OpenInfraPlatform::Ifc2x3::IfcFace,
		OpenInfraPlatform::Ifc2x3::IfcFaceBasedSurfaceModel,
		OpenInfraPlatform::Ifc2x3::IfcFaceBound,
		OpenInfraPlatform::Ifc2x3::IfcFaceOuterBound,
		OpenInfraPlatform::Ifc2x3::IfcFaceSurface,
		OpenInfraPlatform::Ifc2x3::IfcFacetedBrep,
		OpenInfraPlatform::Ifc2x3::IfcFacetedBrepWithVoids,
		OpenInfraPlatform::Ifc2x3::IfcFailureConnectionCondition,
		OpenInfraPlatform::Ifc2x3::IfcFanType,
		OpenInfraPlatform::Ifc2x3::IfcFanTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcFastener,
		OpenInfraPlatform::Ifc2x3::IfcFastenerType,
		OpenInfraPlatform::Ifc2x3::IfcFeatureElement,
		OpenInfraPlatform::Ifc2x3::IfcFeatureElementAddition,
		OpenInfraPlatform::Ifc2x3::IfcFeatureElementSubtraction,
		OpenInfraPlatform::Ifc2x3::IfcFillAreaStyle,
		OpenInfraPlatform::Ifc2x3::IfcFillAreaStyleHatching,
		OpenInfraPlatform::Ifc2x3::IfcFillAreaStyleTiles,
		OpenInfraPlatform::Ifc2x3::IfcFillAreaStyleTileShapeSelect,
		OpenInfraPlatform::Ifc2x3::IfcFillAreaStyleTileSymbolWithStyle,
		OpenInfraPlatform::Ifc2x3::IfcFillStyleSelect,
		OpenInfraPlatform::Ifc2x3::IfcFilterType,
		OpenInfraPlatform::Ifc2x3::IfcFilterTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcFireSuppressionTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcFireSuppressionTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcFlowController,
		OpenInfraPlatform::Ifc2x3::IfcFlowControllerType,
		OpenInfraPlatform::Ifc2x3::IfcFlowDirectionEnum,
		OpenInfraPlatform::Ifc2x3::IfcFlowFitting,
		OpenInfraPlatform::Ifc2x3::IfcFlowFittingType,
		OpenInfraPlatform::Ifc2x3::IfcFlowInstrumentType,
		OpenInfraPlatform::Ifc2x3::IfcFlowInstrumentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcFlowMeterType,
		OpenInfraPlatform::Ifc2x3::IfcFlowMeterTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcFlowMovingDevice,
		OpenInfraPlatform::Ifc2x3::IfcFlowMovingDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcFlowSegment,
		OpenInfraPlatform::Ifc2x3::IfcFlowSegmentType,
		OpenInfraPlatform::Ifc2x3::IfcFlowStorageDevice,
		OpenInfraPlatform::Ifc2x3::IfcFlowStorageDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcFlowTerminal,
		OpenInfraPlatform::Ifc2x3::IfcFlowTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcFlowTreatmentDevice,
		OpenInfraPlatform::Ifc2x3::IfcFlowTreatmentDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcFluidFlowProperties,
		OpenInfraPlatform::Ifc2x3::IfcFontStyle,
		OpenInfraPlatform::Ifc2x3::IfcFontVariant,
		OpenInfraPlatform::Ifc2x3::IfcFontWeight,
		OpenInfraPlatform::Ifc2x3::IfcFooting,
		OpenInfraPlatform::Ifc2x3::IfcFootingTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcForceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcFrequencyMeasure,
		OpenInfraPlatform::Ifc2x3::IfcFuelProperties,
		OpenInfraPlatform::Ifc2x3::IfcFurnishingElement,
		OpenInfraPlatform::Ifc2x3::IfcFurnishingElementType,
		OpenInfraPlatform::Ifc2x3::IfcFurnitureStandard,
		OpenInfraPlatform::Ifc2x3::IfcFurnitureType,
		OpenInfraPlatform::Ifc2x3::IfcGasTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcGasTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcGeneralMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcGeneralProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcGeometricCurveSet,
		OpenInfraPlatform::Ifc2x3::IfcGeometricProjectionEnum,
		OpenInfraPlatform::Ifc2x3::IfcGeometricRepresentationContext,
		OpenInfraPlatform::Ifc2x3::IfcGeometricRepresentationItem,
		OpenInfraPlatform::Ifc2x3::IfcGeometricRepresentationSubContext,
		OpenInfraPlatform::Ifc2x3::IfcGeometricSet,
		OpenInfraPlatform::Ifc2x3::IfcGeometricSetSelect,
		OpenInfraPlatform::Ifc2x3::IfcGloballyUniqueId,
		OpenInfraPlatform::Ifc2x3::IfcGlobalOrLocalEnum,
		OpenInfraPlatform::Ifc2x3::IfcGrid,
		OpenInfraPlatform::Ifc2x3::IfcGridAxis,
		OpenInfraPlatform::Ifc2x3::IfcGridPlacement,
		OpenInfraPlatform::Ifc2x3::IfcGroup,
		OpenInfraPlatform::Ifc2x3::IfcHalfSpaceSolid,
		OpenInfraPlatform::Ifc2x3::IfcHatchLineDistanceSelect,
		OpenInfraPlatform::Ifc2x3::IfcHeatExchangerType,
		OpenInfraPlatform::Ifc2x3::IfcHeatExchangerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcHeatFluxDensityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcHeatingValueMeasure,
		OpenInfraPlatform::Ifc2x3::IfcHourInDay,
		OpenInfraPlatform::Ifc2x3::IfcHumidifierType,
		OpenInfraPlatform::Ifc2x3::IfcHumidifierTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcHygroscopicMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcIdentifier,
		OpenInfraPlatform::Ifc2x3::IfcIlluminanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcImageTexture,
		OpenInfraPlatform::Ifc2x3::IfcInductanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcInteger,
		OpenInfraPlatform::Ifc2x3::IfcIntegerCountRateMeasure,
		OpenInfraPlatform::Ifc2x3::IfcInternalOrExternalEnum,
		OpenInfraPlatform::Ifc2x3::IfcInventory,
		OpenInfraPlatform::Ifc2x3::IfcInventoryTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcIonConcentrationMeasure,
		OpenInfraPlatform::Ifc2x3::IfcIrregularTimeSeries,
		OpenInfraPlatform::Ifc2x3::IfcIrregularTimeSeriesValue,
		OpenInfraPlatform::Ifc2x3::IfcIShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcIsothermalMoistureCapacityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcJunctionBoxType,
		OpenInfraPlatform::Ifc2x3::IfcJunctionBoxTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcKinematicViscosityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLabel,
		OpenInfraPlatform::Ifc2x3::IfcLaborResource,
		OpenInfraPlatform::Ifc2x3::IfcLampType,
		OpenInfraPlatform::Ifc2x3::IfcLampTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcLayeredItem,
		OpenInfraPlatform::Ifc2x3::IfcLayerSetDirectionEnum,
		OpenInfraPlatform::Ifc2x3::IfcLengthMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLibraryInformation,
		OpenInfraPlatform::Ifc2x3::IfcLibraryReference,
		OpenInfraPlatform::Ifc2x3::IfcLibrarySelect,
		OpenInfraPlatform::Ifc2x3::IfcLightDistributionCurveEnum,
		OpenInfraPlatform::Ifc2x3::IfcLightDistributionData,
		OpenInfraPlatform::Ifc2x3::IfcLightDistributionDataSourceSelect,
		OpenInfraPlatform::Ifc2x3::IfcLightEmissionSourceEnum,
		OpenInfraPlatform::Ifc2x3::IfcLightFixtureType,
		OpenInfraPlatform::Ifc2x3::IfcLightFixtureTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcLightIntensityDistribution,
		OpenInfraPlatform::Ifc2x3::IfcLightSource,
		OpenInfraPlatform::Ifc2x3::IfcLightSourceAmbient,
		OpenInfraPlatform::Ifc2x3::IfcLightSourceDirectional,
		OpenInfraPlatform::Ifc2x3::IfcLightSourceGoniometric,
		OpenInfraPlatform::Ifc2x3::IfcLightSourcePositional,
		OpenInfraPlatform::Ifc2x3::IfcLightSourceSpot,
		OpenInfraPlatform::Ifc2x3::IfcLine,
		OpenInfraPlatform::Ifc2x3::IfcLinearDimension,
		OpenInfraPlatform::Ifc2x3::IfcLinearForceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLinearMomentMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLinearStiffnessMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLinearVelocityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLoadGroupTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcLocalPlacement,
		OpenInfraPlatform::Ifc2x3::IfcLocalTime,
		OpenInfraPlatform::Ifc2x3::IfcLogical,
		OpenInfraPlatform::Ifc2x3::IfcLogicalOperatorEnum,
		OpenInfraPlatform::Ifc2x3::IfcLoop,
		OpenInfraPlatform::Ifc2x3::IfcLShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcLuminousFluxMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLuminousIntensityDistributionMeasure,
		OpenInfraPlatform::Ifc2x3::IfcLuminousIntensityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMagneticFluxDensityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMagneticFluxMeasure,
		OpenInfraPlatform::Ifc2x3::IfcManifoldSolidBrep,
		OpenInfraPlatform::Ifc2x3::IfcMappedItem,
		OpenInfraPlatform::Ifc2x3::IfcMassDensityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMassFlowRateMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMassMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMassPerLengthMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMaterial,
		OpenInfraPlatform::Ifc2x3::IfcMaterialClassificationRelationship,
		OpenInfraPlatform::Ifc2x3::IfcMaterialDefinitionRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcMaterialLayer,
		OpenInfraPlatform::Ifc2x3::IfcMaterialLayerSet,
		OpenInfraPlatform::Ifc2x3::IfcMaterialLayerSetUsage,
		OpenInfraPlatform::Ifc2x3::IfcMaterialList,
		OpenInfraPlatform::Ifc2x3::IfcMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcMaterialSelect,
		OpenInfraPlatform::Ifc2x3::IfcMeasureValue,
		OpenInfraPlatform::Ifc2x3::IfcMeasureWithUnit,
		OpenInfraPlatform::Ifc2x3::IfcMechanicalConcreteMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcMechanicalFastener,
		OpenInfraPlatform::Ifc2x3::IfcMechanicalFastenerType,
		OpenInfraPlatform::Ifc2x3::IfcMechanicalMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcMechanicalSteelMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcMember,
		OpenInfraPlatform::Ifc2x3::IfcMemberType,
		OpenInfraPlatform::Ifc2x3::IfcMemberTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcMetric,
		OpenInfraPlatform::Ifc2x3::IfcMetricValueSelect,
		OpenInfraPlatform::Ifc2x3::IfcMinuteInHour,
		OpenInfraPlatform::Ifc2x3::IfcModulusOfElasticityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcModulusOfLinearSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc2x3::IfcModulusOfRotationalSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc2x3::IfcModulusOfSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMoistureDiffusivityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMolecularWeightMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMomentOfInertiaMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMonetaryMeasure,
		OpenInfraPlatform::Ifc2x3::IfcMonetaryUnit,
		OpenInfraPlatform::Ifc2x3::IfcMonthInYearNumber,
		OpenInfraPlatform::Ifc2x3::IfcMotorConnectionType,
		OpenInfraPlatform::Ifc2x3::IfcMotorConnectionTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcMove,
		OpenInfraPlatform::Ifc2x3::IfcNamedUnit,
		OpenInfraPlatform::Ifc2x3::IfcNormalisedRatioMeasure,
		OpenInfraPlatform::Ifc2x3::IfcNullStyle,
		OpenInfraPlatform::Ifc2x3::IfcNumericMeasure,
		OpenInfraPlatform::Ifc2x3::IfcObject,
		OpenInfraPlatform::Ifc2x3::IfcObjectDefinition,
		OpenInfraPlatform::Ifc2x3::IfcObjective,
		OpenInfraPlatform::Ifc2x3::IfcObjectiveEnum,
		OpenInfraPlatform::Ifc2x3::IfcObjectPlacement,
		OpenInfraPlatform::Ifc2x3::IfcObjectReferenceSelect,
		OpenInfraPlatform::Ifc2x3::IfcObjectTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcOccupant,
		OpenInfraPlatform::Ifc2x3::IfcOccupantTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcOffsetCurve2D,
		OpenInfraPlatform::Ifc2x3::IfcOffsetCurve3D,
		OpenInfraPlatform::Ifc2x3::IfcOneDirectionRepeatFactor,
		OpenInfraPlatform::Ifc2x3::IfcOpeningElement,
		OpenInfraPlatform::Ifc2x3::IfcOpenShell,
		OpenInfraPlatform::Ifc2x3::IfcOpticalMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcOrderAction,
		OpenInfraPlatform::Ifc2x3::IfcOrganization,
		OpenInfraPlatform::Ifc2x3::IfcOrganizationRelationship,
		OpenInfraPlatform::Ifc2x3::IfcOrientationSelect,
		OpenInfraPlatform::Ifc2x3::IfcOrientedEdge,
		OpenInfraPlatform::Ifc2x3::IfcOutletType,
		OpenInfraPlatform::Ifc2x3::IfcOutletTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcOwnerHistory,
		OpenInfraPlatform::Ifc2x3::IfcParameterizedProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcParameterValue,
		OpenInfraPlatform::Ifc2x3::IfcPath,
		OpenInfraPlatform::Ifc2x3::IfcPerformanceHistory,
		OpenInfraPlatform::Ifc2x3::IfcPermeableCoveringOperationEnum,
		OpenInfraPlatform::Ifc2x3::IfcPermeableCoveringProperties,
		OpenInfraPlatform::Ifc2x3::IfcPermit,
		OpenInfraPlatform::Ifc2x3::IfcPerson,
		OpenInfraPlatform::Ifc2x3::IfcPersonAndOrganization,
		OpenInfraPlatform::Ifc2x3::IfcPHMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPhysicalComplexQuantity,
		OpenInfraPlatform::Ifc2x3::IfcPhysicalOrVirtualEnum,
		OpenInfraPlatform::Ifc2x3::IfcPhysicalQuantity,
		OpenInfraPlatform::Ifc2x3::IfcPhysicalSimpleQuantity,
		OpenInfraPlatform::Ifc2x3::IfcPile,
		OpenInfraPlatform::Ifc2x3::IfcPileConstructionEnum,
		OpenInfraPlatform::Ifc2x3::IfcPileTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcPipeFittingType,
		OpenInfraPlatform::Ifc2x3::IfcPipeFittingTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcPipeSegmentType,
		OpenInfraPlatform::Ifc2x3::IfcPipeSegmentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcPixelTexture,
		OpenInfraPlatform::Ifc2x3::IfcPlacement,
		OpenInfraPlatform::Ifc2x3::IfcPlanarBox,
		OpenInfraPlatform::Ifc2x3::IfcPlanarExtent,
		OpenInfraPlatform::Ifc2x3::IfcPlanarForceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPlane,
		OpenInfraPlatform::Ifc2x3::IfcPlaneAngleMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPlate,
		OpenInfraPlatform::Ifc2x3::IfcPlateType,
		OpenInfraPlatform::Ifc2x3::IfcPlateTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcPoint,
		OpenInfraPlatform::Ifc2x3::IfcPointOnCurve,
		OpenInfraPlatform::Ifc2x3::IfcPointOnSurface,
		OpenInfraPlatform::Ifc2x3::IfcPointOrVertexPoint,
		OpenInfraPlatform::Ifc2x3::IfcPolygonalBoundedHalfSpace,
		OpenInfraPlatform::Ifc2x3::IfcPolyline,
		OpenInfraPlatform::Ifc2x3::IfcPolyLoop,
		OpenInfraPlatform::Ifc2x3::IfcPort,
		OpenInfraPlatform::Ifc2x3::IfcPositiveLengthMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPositivePlaneAngleMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPositiveRatioMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPostalAddress,
		OpenInfraPlatform::Ifc2x3::IfcPowerMeasure,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedColour,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedCurveFont,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedDimensionSymbol,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedItem,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedPointMarkerSymbol,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedSymbol,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedTerminatorSymbol,
		OpenInfraPlatform::Ifc2x3::IfcPreDefinedTextFont,
		OpenInfraPlatform::Ifc2x3::IfcPresentableText,
		OpenInfraPlatform::Ifc2x3::IfcPresentationLayerAssignment,
		OpenInfraPlatform::Ifc2x3::IfcPresentationLayerWithStyle,
		OpenInfraPlatform::Ifc2x3::IfcPresentationStyle,
		OpenInfraPlatform::Ifc2x3::IfcPresentationStyleAssignment,
		OpenInfraPlatform::Ifc2x3::IfcPresentationStyleSelect,
		OpenInfraPlatform::Ifc2x3::IfcPressureMeasure,
		OpenInfraPlatform::Ifc2x3::IfcProcedure,
		OpenInfraPlatform::Ifc2x3::IfcProcedureTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcProcess,
		OpenInfraPlatform::Ifc2x3::IfcProduct,
		OpenInfraPlatform::Ifc2x3::IfcProductDefinitionShape,
		OpenInfraPlatform::Ifc2x3::IfcProductRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcProductsOfCombustionProperties,
		OpenInfraPlatform::Ifc2x3::IfcProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcProfileTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcProject,
		OpenInfraPlatform::Ifc2x3::IfcProjectedOrTrueLengthEnum,
		OpenInfraPlatform::Ifc2x3::IfcProjectionCurve,
		OpenInfraPlatform::Ifc2x3::IfcProjectionElement,
		OpenInfraPlatform::Ifc2x3::IfcProjectOrder,
		OpenInfraPlatform::Ifc2x3::IfcProjectOrderRecord,
		OpenInfraPlatform::Ifc2x3::IfcProjectOrderRecordTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcProjectOrderTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcProperty,
		OpenInfraPlatform::Ifc2x3::IfcPropertyBoundedValue,
		OpenInfraPlatform::Ifc2x3::IfcPropertyConstraintRelationship,
		OpenInfraPlatform::Ifc2x3::IfcPropertyDefinition,
		OpenInfraPlatform::Ifc2x3::IfcPropertyDependencyRelationship,
		OpenInfraPlatform::Ifc2x3::IfcPropertyEnumeratedValue,
		OpenInfraPlatform::Ifc2x3::IfcPropertyEnumeration,
		OpenInfraPlatform::Ifc2x3::IfcPropertyListValue,
		OpenInfraPlatform::Ifc2x3::IfcPropertyReferenceValue,
		OpenInfraPlatform::Ifc2x3::IfcPropertySet,
		OpenInfraPlatform::Ifc2x3::IfcPropertySetDefinition,
		OpenInfraPlatform::Ifc2x3::IfcPropertySingleValue,
		OpenInfraPlatform::Ifc2x3::IfcPropertySourceEnum,
		OpenInfraPlatform::Ifc2x3::IfcPropertyTableValue,
		OpenInfraPlatform::Ifc2x3::IfcProtectiveDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcProtectiveDeviceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcProxy,
		OpenInfraPlatform::Ifc2x3::IfcPumpType,
		OpenInfraPlatform::Ifc2x3::IfcPumpTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcQuantityArea,
		OpenInfraPlatform::Ifc2x3::IfcQuantityCount,
		OpenInfraPlatform::Ifc2x3::IfcQuantityLength,
		OpenInfraPlatform::Ifc2x3::IfcQuantityTime,
		OpenInfraPlatform::Ifc2x3::IfcQuantityVolume,
		OpenInfraPlatform::Ifc2x3::IfcQuantityWeight,
		OpenInfraPlatform::Ifc2x3::IfcRadioActivityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcRadiusDimension,
		OpenInfraPlatform::Ifc2x3::IfcRailing,
		OpenInfraPlatform::Ifc2x3::IfcRailingType,
		OpenInfraPlatform::Ifc2x3::IfcRailingTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcRamp,
		OpenInfraPlatform::Ifc2x3::IfcRampFlight,
		OpenInfraPlatform::Ifc2x3::IfcRampFlightType,
		OpenInfraPlatform::Ifc2x3::IfcRampFlightTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcRampTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcRatioMeasure,
		OpenInfraPlatform::Ifc2x3::IfcRationalBezierCurve,
		OpenInfraPlatform::Ifc2x3::IfcReal,
		OpenInfraPlatform::Ifc2x3::IfcRectangleHollowProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcRectangleProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcRectangularPyramid,
		OpenInfraPlatform::Ifc2x3::IfcRectangularTrimmedSurface,
		OpenInfraPlatform::Ifc2x3::IfcReferencesValueDocument,
		OpenInfraPlatform::Ifc2x3::IfcReflectanceMethodEnum,
		OpenInfraPlatform::Ifc2x3::IfcRegularTimeSeries,
		OpenInfraPlatform::Ifc2x3::IfcReinforcementBarProperties,
		OpenInfraPlatform::Ifc2x3::IfcReinforcementDefinitionProperties,
		OpenInfraPlatform::Ifc2x3::IfcReinforcingBar,
		OpenInfraPlatform::Ifc2x3::IfcReinforcingBarRoleEnum,
		OpenInfraPlatform::Ifc2x3::IfcReinforcingBarSurfaceEnum,
		OpenInfraPlatform::Ifc2x3::IfcReinforcingElement,
		OpenInfraPlatform::Ifc2x3::IfcReinforcingMesh,
		OpenInfraPlatform::Ifc2x3::IfcRelAggregates,
		OpenInfraPlatform::Ifc2x3::IfcRelAssigns,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsTasks,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToActor,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToControl,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToGroup,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToProcess,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToProduct,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToProjectOrder,
		OpenInfraPlatform::Ifc2x3::IfcRelAssignsToResource,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociates,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesAppliedValue,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesApproval,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesClassification,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesConstraint,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesDocument,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesLibrary,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesMaterial,
		OpenInfraPlatform::Ifc2x3::IfcRelAssociatesProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcRelationship,
		OpenInfraPlatform::Ifc2x3::IfcRelaxation,
		OpenInfraPlatform::Ifc2x3::IfcRelConnects,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsElements,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsPathElements,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsPorts,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsPortToElement,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsStructuralActivity,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsStructuralElement,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsStructuralMember,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsWithEccentricity,
		OpenInfraPlatform::Ifc2x3::IfcRelConnectsWithRealizingElements,
		OpenInfraPlatform::Ifc2x3::IfcRelContainedInSpatialStructure,
		OpenInfraPlatform::Ifc2x3::IfcRelCoversBldgElements,
		OpenInfraPlatform::Ifc2x3::IfcRelCoversSpaces,
		OpenInfraPlatform::Ifc2x3::IfcRelDecomposes,
		OpenInfraPlatform::Ifc2x3::IfcRelDefines,
		OpenInfraPlatform::Ifc2x3::IfcRelDefinesByProperties,
		OpenInfraPlatform::Ifc2x3::IfcRelDefinesByType,
		OpenInfraPlatform::Ifc2x3::IfcRelFillsElement,
		OpenInfraPlatform::Ifc2x3::IfcRelFlowControlElements,
		OpenInfraPlatform::Ifc2x3::IfcRelInteractionRequirements,
		OpenInfraPlatform::Ifc2x3::IfcRelNests,
		OpenInfraPlatform::Ifc2x3::IfcRelOccupiesSpaces,
		OpenInfraPlatform::Ifc2x3::IfcRelOverridesProperties,
		OpenInfraPlatform::Ifc2x3::IfcRelProjectsElement,
		OpenInfraPlatform::Ifc2x3::IfcRelReferencedInSpatialStructure,
		OpenInfraPlatform::Ifc2x3::IfcRelSchedulesCostItems,
		OpenInfraPlatform::Ifc2x3::IfcRelSequence,
		OpenInfraPlatform::Ifc2x3::IfcRelServicesBuildings,
		OpenInfraPlatform::Ifc2x3::IfcRelSpaceBoundary,
		OpenInfraPlatform::Ifc2x3::IfcRelVoidsElement,
		OpenInfraPlatform::Ifc2x3::IfcRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcRepresentationContext,
		OpenInfraPlatform::Ifc2x3::IfcRepresentationItem,
		OpenInfraPlatform::Ifc2x3::IfcRepresentationMap,
		OpenInfraPlatform::Ifc2x3::IfcResource,
		OpenInfraPlatform::Ifc2x3::IfcResourceConsumptionEnum,
		OpenInfraPlatform::Ifc2x3::IfcRevolvedAreaSolid,
		OpenInfraPlatform::Ifc2x3::IfcRibPlateDirectionEnum,
		OpenInfraPlatform::Ifc2x3::IfcRibPlateProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcRightCircularCone,
		OpenInfraPlatform::Ifc2x3::IfcRightCircularCylinder,
		OpenInfraPlatform::Ifc2x3::IfcRoleEnum,
		OpenInfraPlatform::Ifc2x3::IfcRoof,
		OpenInfraPlatform::Ifc2x3::IfcRoofTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcRoot,
		OpenInfraPlatform::Ifc2x3::IfcRotationalFrequencyMeasure,
		OpenInfraPlatform::Ifc2x3::IfcRotationalMassMeasure,
		OpenInfraPlatform::Ifc2x3::IfcRotationalStiffnessMeasure,
		OpenInfraPlatform::Ifc2x3::IfcRoundedEdgeFeature,
		OpenInfraPlatform::Ifc2x3::IfcRoundedRectangleProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcSanitaryTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcSanitaryTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcScheduleTimeControl,
		OpenInfraPlatform::Ifc2x3::IfcSecondInMinute,
		OpenInfraPlatform::Ifc2x3::IfcSectionalAreaIntegralMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSectionedSpine,
		OpenInfraPlatform::Ifc2x3::IfcSectionModulusMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSectionProperties,
		OpenInfraPlatform::Ifc2x3::IfcSectionReinforcementProperties,
		OpenInfraPlatform::Ifc2x3::IfcSectionTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSensorType,
		OpenInfraPlatform::Ifc2x3::IfcSensorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSequenceEnum,
		OpenInfraPlatform::Ifc2x3::IfcServiceLife,
		OpenInfraPlatform::Ifc2x3::IfcServiceLifeFactor,
		OpenInfraPlatform::Ifc2x3::IfcServiceLifeFactorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcServiceLifeTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcShapeAspect,
		OpenInfraPlatform::Ifc2x3::IfcShapeModel,
		OpenInfraPlatform::Ifc2x3::IfcShapeRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcShearModulusMeasure,
		OpenInfraPlatform::Ifc2x3::IfcShell,
		OpenInfraPlatform::Ifc2x3::IfcShellBasedSurfaceModel,
		OpenInfraPlatform::Ifc2x3::IfcSimpleProperty,
		OpenInfraPlatform::Ifc2x3::IfcSimpleValue,
		OpenInfraPlatform::Ifc2x3::IfcSIPrefix,
		OpenInfraPlatform::Ifc2x3::IfcSite,
		OpenInfraPlatform::Ifc2x3::IfcSIUnit,
		OpenInfraPlatform::Ifc2x3::IfcSIUnitName,
		OpenInfraPlatform::Ifc2x3::IfcSizeSelect,
		OpenInfraPlatform::Ifc2x3::IfcSlab,
		OpenInfraPlatform::Ifc2x3::IfcSlabType,
		OpenInfraPlatform::Ifc2x3::IfcSlabTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSlippageConnectionCondition,
		OpenInfraPlatform::Ifc2x3::IfcSolidAngleMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSolidModel,
		OpenInfraPlatform::Ifc2x3::IfcSoundPowerMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSoundPressureMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSoundProperties,
		OpenInfraPlatform::Ifc2x3::IfcSoundScaleEnum,
		OpenInfraPlatform::Ifc2x3::IfcSoundValue,
		OpenInfraPlatform::Ifc2x3::IfcSpace,
		OpenInfraPlatform::Ifc2x3::IfcSpaceHeaterType,
		OpenInfraPlatform::Ifc2x3::IfcSpaceHeaterTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSpaceProgram,
		OpenInfraPlatform::Ifc2x3::IfcSpaceThermalLoadProperties,
		OpenInfraPlatform::Ifc2x3::IfcSpaceType,
		OpenInfraPlatform::Ifc2x3::IfcSpaceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSpatialStructureElement,
		OpenInfraPlatform::Ifc2x3::IfcSpatialStructureElementType,
		OpenInfraPlatform::Ifc2x3::IfcSpecificHeatCapacityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcSpecularExponent,
		OpenInfraPlatform::Ifc2x3::IfcSpecularHighlightSelect,
		OpenInfraPlatform::Ifc2x3::IfcSpecularRoughness,
		OpenInfraPlatform::Ifc2x3::IfcSphere,
		OpenInfraPlatform::Ifc2x3::IfcStackTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcStackTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcStair,
		OpenInfraPlatform::Ifc2x3::IfcStairFlight,
		OpenInfraPlatform::Ifc2x3::IfcStairFlightType,
		OpenInfraPlatform::Ifc2x3::IfcStairFlightTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcStairTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcStateEnum,
		OpenInfraPlatform::Ifc2x3::IfcStructuralAction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralActivity,
		OpenInfraPlatform::Ifc2x3::IfcStructuralActivityAssignmentSelect,
		OpenInfraPlatform::Ifc2x3::IfcStructuralAnalysisModel,
		OpenInfraPlatform::Ifc2x3::IfcStructuralConnection,
		OpenInfraPlatform::Ifc2x3::IfcStructuralConnectionCondition,
		OpenInfraPlatform::Ifc2x3::IfcStructuralCurveConnection,
		OpenInfraPlatform::Ifc2x3::IfcStructuralCurveMember,
		OpenInfraPlatform::Ifc2x3::IfcStructuralCurveMemberVarying,
		OpenInfraPlatform::Ifc2x3::IfcStructuralCurveTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcStructuralItem,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLinearAction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLinearActionVarying,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoad,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadGroup,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadLinearForce,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadPlanarForce,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadSingleDisplacement,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadSingleDisplacementDistortion,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadSingleForce,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadSingleForceWarping,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadStatic,
		OpenInfraPlatform::Ifc2x3::IfcStructuralLoadTemperature,
		OpenInfraPlatform::Ifc2x3::IfcStructuralMember,
		OpenInfraPlatform::Ifc2x3::IfcStructuralPlanarAction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralPlanarActionVarying,
		OpenInfraPlatform::Ifc2x3::IfcStructuralPointAction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralPointConnection,
		OpenInfraPlatform::Ifc2x3::IfcStructuralPointReaction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcStructuralReaction,
		OpenInfraPlatform::Ifc2x3::IfcStructuralResultGroup,
		OpenInfraPlatform::Ifc2x3::IfcStructuralSteelProfileProperties,
		OpenInfraPlatform::Ifc2x3::IfcStructuralSurfaceConnection,
		OpenInfraPlatform::Ifc2x3::IfcStructuralSurfaceMember,
		OpenInfraPlatform::Ifc2x3::IfcStructuralSurfaceMemberVarying,
		OpenInfraPlatform::Ifc2x3::IfcStructuralSurfaceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcStructuredDimensionCallout,
		OpenInfraPlatform::Ifc2x3::IfcStyledItem,
		OpenInfraPlatform::Ifc2x3::IfcStyledRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcStyleModel,
		OpenInfraPlatform::Ifc2x3::IfcSubContractResource,
		OpenInfraPlatform::Ifc2x3::IfcSubedge,
		OpenInfraPlatform::Ifc2x3::IfcSurface,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceCurveSweptAreaSolid,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceOfLinearExtrusion,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceOfRevolution,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceOrFaceSurface,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceSide,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyle,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleElementSelect,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleLighting,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleRefraction,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleRendering,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleShading,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceStyleWithTextures,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceTexture,
		OpenInfraPlatform::Ifc2x3::IfcSurfaceTextureEnum,
		OpenInfraPlatform::Ifc2x3::IfcSweptAreaSolid,
		OpenInfraPlatform::Ifc2x3::IfcSweptDiskSolid,
		OpenInfraPlatform::Ifc2x3::IfcSweptSurface,
		OpenInfraPlatform::Ifc2x3::IfcSwitchingDeviceType,
		OpenInfraPlatform::Ifc2x3::IfcSwitchingDeviceTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcSymbolStyle,
		OpenInfraPlatform::Ifc2x3::IfcSymbolStyleSelect,
		OpenInfraPlatform::Ifc2x3::IfcSystem,
		OpenInfraPlatform::Ifc2x3::IfcSystemFurnitureElementType,
		OpenInfraPlatform::Ifc2x3::IfcTable,
		OpenInfraPlatform::Ifc2x3::IfcTableRow,
		OpenInfraPlatform::Ifc2x3::IfcTankType,
		OpenInfraPlatform::Ifc2x3::IfcTankTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTask,
		OpenInfraPlatform::Ifc2x3::IfcTelecomAddress,
		OpenInfraPlatform::Ifc2x3::IfcTemperatureGradientMeasure,
		OpenInfraPlatform::Ifc2x3::IfcTendon,
		OpenInfraPlatform::Ifc2x3::IfcTendonAnchor,
		OpenInfraPlatform::Ifc2x3::IfcTendonTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTerminatorSymbol,
		OpenInfraPlatform::Ifc2x3::IfcText,
		OpenInfraPlatform::Ifc2x3::IfcTextAlignment,
		OpenInfraPlatform::Ifc2x3::IfcTextDecoration,
		OpenInfraPlatform::Ifc2x3::IfcTextFontName,
		OpenInfraPlatform::Ifc2x3::IfcTextFontSelect,
		OpenInfraPlatform::Ifc2x3::IfcTextLiteral,
		OpenInfraPlatform::Ifc2x3::IfcTextLiteralWithExtent,
		OpenInfraPlatform::Ifc2x3::IfcTextPath,
		OpenInfraPlatform::Ifc2x3::IfcTextStyle,
		OpenInfraPlatform::Ifc2x3::IfcTextStyleFontModel,
		OpenInfraPlatform::Ifc2x3::IfcTextStyleForDefinedFont,
		OpenInfraPlatform::Ifc2x3::IfcTextStyleSelect,
		OpenInfraPlatform::Ifc2x3::IfcTextStyleTextModel,
		OpenInfraPlatform::Ifc2x3::IfcTextStyleWithBoxCharacteristics,
		OpenInfraPlatform::Ifc2x3::IfcTextTransformation,
		OpenInfraPlatform::Ifc2x3::IfcTextureCoordinate,
		OpenInfraPlatform::Ifc2x3::IfcTextureCoordinateGenerator,
		OpenInfraPlatform::Ifc2x3::IfcTextureMap,
		OpenInfraPlatform::Ifc2x3::IfcTextureVertex,
		OpenInfraPlatform::Ifc2x3::IfcThermalAdmittanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcThermalConductivityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcThermalExpansionCoefficientMeasure,
		OpenInfraPlatform::Ifc2x3::IfcThermalLoadSourceEnum,
		OpenInfraPlatform::Ifc2x3::IfcThermalLoadTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcThermalMaterialProperties,
		OpenInfraPlatform::Ifc2x3::IfcThermalResistanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcThermalTransmittanceMeasure,
		OpenInfraPlatform::Ifc2x3::IfcThermodynamicTemperatureMeasure,
		OpenInfraPlatform::Ifc2x3::IfcTimeMeasure,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeries,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeriesDataTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeriesReferenceRelationship,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeriesSchedule,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeriesScheduleTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTimeSeriesValue,
		OpenInfraPlatform::Ifc2x3::IfcTimeStamp,
		OpenInfraPlatform::Ifc2x3::IfcTopologicalRepresentationItem,
		OpenInfraPlatform::Ifc2x3::IfcTopologyRepresentation,
		OpenInfraPlatform::Ifc2x3::IfcTorqueMeasure,
		OpenInfraPlatform::Ifc2x3::IfcTransformerType,
		OpenInfraPlatform::Ifc2x3::IfcTransformerTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTransitionCode,
		OpenInfraPlatform::Ifc2x3::IfcTransportElement,
		OpenInfraPlatform::Ifc2x3::IfcTransportElementType,
		OpenInfraPlatform::Ifc2x3::IfcTransportElementTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTrapeziumProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcTrimmedCurve,
		OpenInfraPlatform::Ifc2x3::IfcTrimmingPreference,
		OpenInfraPlatform::Ifc2x3::IfcTrimmingSelect,
		OpenInfraPlatform::Ifc2x3::IfcTShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcTubeBundleType,
		OpenInfraPlatform::Ifc2x3::IfcTubeBundleTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcTwoDirectionRepeatFactor,
		OpenInfraPlatform::Ifc2x3::IfcTypeObject,
		OpenInfraPlatform::Ifc2x3::IfcTypeProduct,
		OpenInfraPlatform::Ifc2x3::IfcUnit,
		OpenInfraPlatform::Ifc2x3::IfcUnitaryEquipmentType,
		OpenInfraPlatform::Ifc2x3::IfcUnitaryEquipmentTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcUnitAssignment,
		OpenInfraPlatform::Ifc2x3::IfcUnitEnum,
		OpenInfraPlatform::Ifc2x3::IfcUShapeProfileDef,
		OpenInfraPlatform::Ifc2x3::IfcValue,
		OpenInfraPlatform::Ifc2x3::IfcValveType,
		OpenInfraPlatform::Ifc2x3::IfcValveTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcVaporPermeabilityMeasure,
		OpenInfraPlatform::Ifc2x3::IfcVector,
		OpenInfraPlatform::Ifc2x3::IfcVectorOrDirection,
		OpenInfraPlatform::Ifc2x3::IfcVertex,
		OpenInfraPlatform::Ifc2x3::IfcVertexBasedTextureMap,
		OpenInfraPlatform::Ifc2x3::IfcVertexLoop,
		OpenInfraPlatform::Ifc2x3::IfcVertexPoint,
		OpenInfraPlatform::Ifc2x3::IfcVibrationIsolatorType,
		OpenInfraPlatform::Ifc2x3::IfcVibrationIsolatorTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcVirtualElement,
		OpenInfraPlatform::Ifc2x3::IfcVirtualGridIntersection,
		OpenInfraPlatform::Ifc2x3::IfcVolumeMeasure,
		OpenInfraPlatform::Ifc2x3::IfcVolumetricFlowRateMeasure,
		OpenInfraPlatform::Ifc2x3::IfcWall,
		OpenInfraPlatform::Ifc2x3::IfcWallStandardCase,
		OpenInfraPlatform::Ifc2x3::IfcWallType,
		OpenInfraPlatform::Ifc2x3::IfcWallTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcWarpingConstantMeasure,
		OpenInfraPlatform::Ifc2x3::IfcWarpingMomentMeasure,
		OpenInfraPlatform::Ifc2x3::IfcWasteTerminalType,
		OpenInfraPlatform::Ifc2x3::IfcWasteTerminalTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcWaterProperties,
		OpenInfraPlatform::Ifc2x3::IfcWindow,
		OpenInfraPlatform::Ifc2x3::IfcWindowLiningProperties,
		OpenInfraPlatform::Ifc2x3::IfcWindowPanelOperationEnum,
		OpenInfraPlatform::Ifc2x3::IfcWindowPanelPositionEnum,
		OpenInfraPlatform::Ifc2x3::IfcWindowPanelProperties,
		OpenInfraPlatform::Ifc2x3::IfcWindowStyle,
		OpenInfraPlatform::Ifc2x3::IfcWindowStyleConstructionEnum,
		OpenInfraPlatform::Ifc2x3::IfcWindowStyleOperationEnum,
		OpenInfraPlatform::Ifc2x3::IfcWorkControl,
		OpenInfraPlatform::Ifc2x3::IfcWorkControlTypeEnum,
		OpenInfraPlatform::Ifc2x3::IfcWorkPlan,
		OpenInfraPlatform::Ifc2x3::IfcWorkSchedule,
		OpenInfraPlatform::Ifc2x3::IfcYearNumber,
		OpenInfraPlatform::Ifc2x3::IfcZone,
		OpenInfraPlatform::Ifc2x3::IfcZShapeProfileDef
	>
	Ifc2x3EntityTypes;
}
