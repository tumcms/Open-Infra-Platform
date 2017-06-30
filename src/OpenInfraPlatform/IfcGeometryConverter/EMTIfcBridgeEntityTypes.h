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

#include "EMTBasicIfcBridgeEntityTypes.h"

namespace OpenInfraPlatform
{
	namespace IfcBridge
	{
		 class IfcAbsorbedDoseMeasure;
		 class IfcAccelerationMeasure;
		 class IfcActionRequest;
		 class IfcActionRequestTypeEnum;
		 class IfcActionSourceTypeEnum;
		 class IfcActionTypeEnum;
		 class IfcActor;
		 class IfcActorRole;
		 class IfcActorSelect;
		 class IfcActuator;
		 class IfcActuatorType;
		 class IfcActuatorTypeEnum;
		 class IfcAddress;
		 class IfcAddressTypeEnum;
		 class IfcAdvancedBrep;
		 class IfcAdvancedBrepWithVoids;
		 class IfcAdvancedFace;
		 class IfcAirTerminal;
		 class IfcAirTerminalBox;
		 class IfcAirTerminalBoxType;
		 class IfcAirTerminalBoxTypeEnum;
		 class IfcAirTerminalType;
		 class IfcAirTerminalTypeEnum;
		 class IfcAirToAirHeatRecovery;
		 class IfcAirToAirHeatRecoveryType;
		 class IfcAirToAirHeatRecoveryTypeEnum;
		 class IfcAlarm;
		 class IfcAlarmType;
		 class IfcAlarmTypeEnum;
		 class IfcAlignmentElement;
		 class IfcAmountOfSubstanceMeasure;
		 class IfcAnalysisModelTypeEnum;
		 class IfcAnalysisTheoryTypeEnum;
		 class IfcAngularVelocityMeasure;
		 class IfcAnnotation;
		 class IfcAnnotationFillArea;
		 class IfcApplication;
		 class IfcAppliedValue;
		 class IfcAppliedValueRelationship;
		 class IfcAppliedValueSelect;
		 class IfcApproval;
		 class IfcApprovalRelationship;
		 class IfcArbitraryClosedProfileDef;
		 class IfcArbitraryOpenProfileDef;
		 class IfcArbitraryProfileDefWithVoids;
		 class IfcAreaMeasure;
		 class IfcArithmeticOperatorEnum;
		 class IfcAssemblyPlaceEnum;
		 class IfcAsset;
		 class IfcAsymmetricIShapeProfileDef;
		 class IfcAudioVisualAppliance;
		 class IfcAudioVisualApplianceType;
		 class IfcAudioVisualApplianceTypeEnum;
		 class IfcAxis1Placement;
		 class IfcAxis2Placement;
		 class IfcAxis2Placement2D;
		 class IfcAxis2Placement3D;
		 class IfcBeam;
		 class IfcBeamStandardCase;
		 class IfcBeamType;
		 class IfcBeamTypeEnum;
		 class IfcBenchmarkEnum;
		 class IfcBendingParameterSelect;
		 class IfcBlobTexture;
		 class IfcBlock;
		 class IfcBoiler;
		 class IfcBoilerType;
		 class IfcBoilerTypeEnum;
		 class IfcBoolean;
		 class IfcBooleanClippingResult;
		 class IfcBooleanOperand;
		 class IfcBooleanOperator;
		 class IfcBooleanResult;
		 class IfcBoundaryCondition;
		 class IfcBoundaryCurve;
		 class IfcBoundaryEdgeCondition;
		 class IfcBoundaryFaceCondition;
		 class IfcBoundaryNodeCondition;
		 class IfcBoundaryNodeConditionWarping;
		 class IfcBoundedCurve;
		 class IfcBoundedSurface;
		 class IfcBoundingBox;
		 class IfcBoxAlignment;
		 class IfcBoxedHalfSpace;
		 class IfcBridge;
		 class IfcBridgeContactElement;
		 class IfcBridgeContactType;
		 class IfcBridgeElement;
		 class IfcBridgeMechanicalRoleType;
		 class IfcBridgePart;
		 class IfcBridgePrismaticElement;
		 class IfcBridgePrismaticElementType;
		 class IfcBridgeSegment;
		 class IfcBridgeSegmentPart;
		 class IfcBridgeSegmentType;
		 class IfcBridgeStructureElement;
		 class IfcBridgeStructureElementType;
		 class IfcBridgeStructureIndicator;
		 class IfcBridgeStructureType;
		 class IfcBridgeSubPartType;
		 class IfcBridgeTechnologicalElementType;
		 class IfcBSplineCurve;
		 class IfcBSplineCurveForm;
		 class IfcBSplineCurveWithKnots;
		 class IfcBSplineSurface;
		 class IfcBSplineSurfaceForm;
		 class IfcBSplineSurfaceWithKnots;
		 class IfcBuilding;
		 class IfcBuildingElement;
		 class IfcBuildingElementPart;
		 class IfcBuildingElementPartType;
		 class IfcBuildingElementPartTypeEnum;
		 class IfcBuildingElementProxy;
		 class IfcBuildingElementProxyType;
		 class IfcBuildingElementProxyTypeEnum;
		 class IfcBuildingElementType;
		 class IfcBuildingStorey;
		 class IfcBuildingSystem;
		 class IfcBuildingSystemTypeEnum;
		 class IfcBurner;
		 class IfcBurnerType;
		 class IfcBurnerTypeEnum;
		 class IfcCableCarrierFitting;
		 class IfcCableCarrierFittingType;
		 class IfcCableCarrierFittingTypeEnum;
		 class IfcCableCarrierSegment;
		 class IfcCableCarrierSegmentType;
		 class IfcCableCarrierSegmentTypeEnum;
		 class IfcCableFitting;
		 class IfcCableFittingType;
		 class IfcCableFittingTypeEnum;
		 class IfcCableSegment;
		 class IfcCableSegmentType;
		 class IfcCableSegmentTypeEnum;
		 class IfcCardinalPointReference;
		 class IfcCartesianPoint;
		 class IfcCartesianPointList;
		 class IfcCartesianTransformationOperator;
		 class IfcCartesianTransformationOperator2D;
		 class IfcCartesianTransformationOperator2DnonUniform;
		 class IfcCartesianTransformationOperator3D;
		 class IfcCartesianTransformationOperator3DnonUniform;
		 class IfcCenterLineProfileDef;
		 class IfcChangeActionEnum;
		 class IfcCharacterStyleSelect;
		 class IfcChiller;
		 class IfcChillerType;
		 class IfcChillerTypeEnum;
		 class IfcChimney;
		 class IfcChimneyType;
		 class IfcChimneyTypeEnum;
		 class IfcCircle;
		 class IfcCircleHollowProfileDef;
		 class IfcCircleProfileDef;
		 class IfcCivilElement;
		 class IfcCivilElementPart;
		 class IfcCivilSheath;
		 class IfcCivilStructureElement;
		 class IfcCivilVoid;
		 class IfcClassification;
		 class IfcClassificationReference;
		 class IfcClassificationReferenceSelect;
		 class IfcClassificationSelect;
		 class IfcClosedShell;
		 class IfcClothoid;
		 class IfcCoil;
		 class IfcCoilType;
		 class IfcCoilTypeEnum;
		 class IfcColour;
		 class IfcColourOrFactor;
		 class IfcColourRgb;
		 class IfcColourRgbList;
		 class IfcColourSpecification;
		 class IfcColumn;
		 class IfcColumnStandardCase;
		 class IfcColumnType;
		 class IfcColumnTypeEnum;
		 class IfcCommunicationsAppliance;
		 class IfcCommunicationsApplianceType;
		 class IfcCommunicationsApplianceTypeEnum;
		 class IfcComplexNumber;
		 class IfcComplexProperty;
		 class IfcComplexPropertyTemplate;
		 class IfcComplexPropertyTemplateTypeEnum;
		 class IfcCompositeCurve;
		 class IfcCompositeCurveOnSurface;
		 class IfcCompositeCurveSegment;
		 class IfcCompositeProfileDef;
		 class IfcCompoundPlaneAngleMeasure;
		 class IfcCompressor;
		 class IfcCompressorType;
		 class IfcCompressorTypeEnum;
		 class IfcCondenser;
		 class IfcCondenserType;
		 class IfcCondenserTypeEnum;
		 class IfcConic;
		 class IfcConnectedFaceSet;
		 class IfcConnectionCurveGeometry;
		 class IfcConnectionGeometry;
		 class IfcConnectionPointEccentricity;
		 class IfcConnectionPointGeometry;
		 class IfcConnectionSurfaceGeometry;
		 class IfcConnectionTypeEnum;
		 class IfcConnectionVolumeGeometry;
		 class IfcConstraint;
		 class IfcConstraintEnum;
		 class IfcConstructionEquipmentResource;
		 class IfcConstructionEquipmentResourceType;
		 class IfcConstructionEquipmentResourceTypeEnum;
		 class IfcConstructionMaterialResource;
		 class IfcConstructionMaterialResourceType;
		 class IfcConstructionMaterialResourceTypeEnum;
		 class IfcConstructionProductResource;
		 class IfcConstructionProductResourceType;
		 class IfcConstructionProductResourceTypeEnum;
		 class IfcConstructionResource;
		 class IfcConstructionResourceType;
		 class IfcContext;
		 class IfcContextDependentMeasure;
		 class IfcContextDependentUnit;
		 class IfcControl;
		 class IfcController;
		 class IfcControllerType;
		 class IfcControllerTypeEnum;
		 class IfcConversionBasedUnit;
		 class IfcConversionBasedUnitWithOffset;
		 class IfcCooledBeam;
		 class IfcCooledBeamType;
		 class IfcCooledBeamTypeEnum;
		 class IfcCoolingTower;
		 class IfcCoolingTowerType;
		 class IfcCoolingTowerTypeEnum;
		 class IfcCoordinateOperation;
		 class IfcCoordinateReferenceSystem;
		 class IfcCoordinateReferenceSystemSelect;
		 class IfcCostItem;
		 class IfcCostItemTypeEnum;
		 class IfcCostSchedule;
		 class IfcCostScheduleTypeEnum;
		 class IfcCostValue;
		 class IfcCountMeasure;
		 class IfcCovering;
		 class IfcCoveringType;
		 class IfcCoveringTypeEnum;
		 class IfcCrewResource;
		 class IfcCrewResourceType;
		 class IfcCrewResourceTypeEnum;
		 class IfcCsgPrimitive3D;
		 class IfcCsgSelect;
		 class IfcCsgSolid;
		 class IfcCShapeProfileDef;
		 class IfcCurrencyRelationship;
		 class IfcCurtainWall;
		 class IfcCurtainWallType;
		 class IfcCurtainWallTypeEnum;
		 class IfcCurvatureMeasure;
		 class IfcCurve;
		 class IfcCurveBoundedPlane;
		 class IfcCurveBoundedSurface;
		 class IfcCurveFontOrScaledCurveFontSelect;
		 class IfcCurveInterpolationEnum;
		 class IfcCurveOnSurface;
		 class IfcCurveOrEdgeCurve;
		 class IfcCurveStyle;
		 class IfcCurveStyleFont;
		 class IfcCurveStyleFontAndScaling;
		 class IfcCurveStyleFontPattern;
		 class IfcCurveStyleFontSelect;
		 class IfcCylindricalSurface;
		 class IfcDamper;
		 class IfcDamperType;
		 class IfcDamperTypeEnum;
		 class IfcDataOriginEnum;
		 class IfcDate;
		 class IfcDateTime;
		 class IfcDayInMonthNumber;
		 class IfcDayInWeekNumber;
		 class IfcDefinedSymbol;
		 class IfcDefinedSymbolSelect;
		 class IfcDefinitionSelect;
		 class IfcDerivedMeasureValue;
		 class IfcDerivedProfileDef;
		 class IfcDerivedUnit;
		 class IfcDerivedUnitElement;
		 class IfcDerivedUnitEnum;
		 class IfcDescriptiveMeasure;
		 class IfcDimensionalExponents;
		 class IfcDimensionCount;
		 class IfcDirection;
		 class IfcDirectionList;
		 class IfcDirectionSenseEnum;
		 class IfcDiscreteAccessory;
		 class IfcDiscreteAccessoryType;
		 class IfcDiscreteAccessoryTypeEnum;
		 class IfcDistributionChamberElement;
		 class IfcDistributionChamberElementType;
		 class IfcDistributionChamberElementTypeEnum;
		 class IfcDistributionCircuit;
		 class IfcDistributionControlElement;
		 class IfcDistributionControlElementType;
		 class IfcDistributionElement;
		 class IfcDistributionElementType;
		 class IfcDistributionFlowElement;
		 class IfcDistributionFlowElementType;
		 class IfcDistributionPort;
		 class IfcDistributionSystem;
		 class IfcDistributionSystemEnum;
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
		 class IfcDoorStandardCase;
		 class IfcDoorStyle;
		 class IfcDoorStyleConstructionEnum;
		 class IfcDoorStyleOperationEnum;
		 class IfcDoorType;
		 class IfcDoorTypeEnum;
		 class IfcDoorTypeOperationEnum;
		 class IfcDoseEquivalentMeasure;
		 class IfcDraughtingPreDefinedColour;
		 class IfcDraughtingPreDefinedCurveFont;
		 class IfcDraughtingPreDefinedTextFont;
		 class IfcDuctFitting;
		 class IfcDuctFittingType;
		 class IfcDuctFittingTypeEnum;
		 class IfcDuctSegment;
		 class IfcDuctSegmentType;
		 class IfcDuctSegmentTypeEnum;
		 class IfcDuctSilencer;
		 class IfcDuctSilencerType;
		 class IfcDuctSilencerTypeEnum;
		 class IfcDuration;
		 class IfcDynamicViscosityMeasure;
		 class IfcEdge;
		 class IfcEdgeCurve;
		 class IfcEdgeLoop;
		 class IfcElectricAppliance;
		 class IfcElectricApplianceType;
		 class IfcElectricApplianceTypeEnum;
		 class IfcElectricCapacitanceMeasure;
		 class IfcElectricChargeMeasure;
		 class IfcElectricConductanceMeasure;
		 class IfcElectricCurrentMeasure;
		 class IfcElectricDistributionBoard;
		 class IfcElectricDistributionBoardType;
		 class IfcElectricDistributionBoardTypeEnum;
		 class IfcElectricFlowStorageDevice;
		 class IfcElectricFlowStorageDeviceType;
		 class IfcElectricFlowStorageDeviceTypeEnum;
		 class IfcElectricGenerator;
		 class IfcElectricGeneratorType;
		 class IfcElectricGeneratorTypeEnum;
		 class IfcElectricMotor;
		 class IfcElectricMotorType;
		 class IfcElectricMotorTypeEnum;
		 class IfcElectricResistanceMeasure;
		 class IfcElectricTimeControl;
		 class IfcElectricTimeControlType;
		 class IfcElectricTimeControlTypeEnum;
		 class IfcElectricVoltageMeasure;
		 class IfcElement;
		 class IfcElementarySurface;
		 class IfcElementAssembly;
		 class IfcElementAssemblyType;
		 class IfcElementAssemblyTypeEnum;
		 class IfcElementComponent;
		 class IfcElementComponentType;
		 class IfcElementCompositionEnum;
		 class IfcElementPart;
		 class IfcElementQuantity;
		 class IfcElementType;
		 class IfcEllipse;
		 class IfcEllipseProfileDef;
		 class IfcEnergyConversionDevice;
		 class IfcEnergyConversionDeviceType;
		 class IfcEnergyMeasure;
		 class IfcEngine;
		 class IfcEngineType;
		 class IfcEngineTypeEnum;
		 class IfcEvaporativeCooler;
		 class IfcEvaporativeCoolerType;
		 class IfcEvaporativeCoolerTypeEnum;
		 class IfcEvaporator;
		 class IfcEvaporatorType;
		 class IfcEvaporatorTypeEnum;
		 class IfcEvent;
		 class IfcEventTime;
		 class IfcEventTriggerTypeEnum;
		 class IfcEventType;
		 class IfcEventTypeEnum;
		 class IfcExtendedProperties;
		 class IfcExternalInformation;
		 class IfcExternallyDefinedHatchStyle;
		 class IfcExternallyDefinedSurfaceStyle;
		 class IfcExternallyDefinedSymbol;
		 class IfcExternallyDefinedTextFont;
		 class IfcExternalReference;
		 class IfcExternalReferenceRelationship;
		 class IfcExternalSpatialElement;
		 class IfcExternalSpatialElementTypeEnum;
		 class IfcExternalSpatialStructureElement;
		 class IfcExtrudedAreaSolid;
		 class IfcExtrudedAreaSolidTapered;
		 class IfcFace;
		 class IfcFaceBasedSurfaceModel;
		 class IfcFaceBound;
		 class IfcFaceOuterBound;
		 class IfcFaceSurface;
		 class IfcFacetedBrep;
		 class IfcFacetedBrepWithVoids;
		 class IfcFailureConnectionCondition;
		 class IfcFan;
		 class IfcFanType;
		 class IfcFanTypeEnum;
		 class IfcFastener;
		 class IfcFastenerType;
		 class IfcFastenerTypeEnum;
		 class IfcFeatureElement;
		 class IfcFeatureElementAddition;
		 class IfcFeatureElementSubtraction;
		 class IfcFillAreaStyle;
		 class IfcFillAreaStyleHatching;
		 class IfcFillAreaStyleTiles;
		 class IfcFillAreaStyleTileShapeSelect;
		 class IfcFillAreaStyleTileSymbolWithStyle;
		 class IfcFillStyleSelect;
		 class IfcFilter;
		 class IfcFilterType;
		 class IfcFilterTypeEnum;
		 class IfcFireSuppressionTerminal;
		 class IfcFireSuppressionTerminalType;
		 class IfcFireSuppressionTerminalTypeEnum;
		 class IfcFixedReferenceSweptAreaSolid;
		 class IfcFlowController;
		 class IfcFlowControllerType;
		 class IfcFlowDirectionEnum;
		 class IfcFlowFitting;
		 class IfcFlowFittingType;
		 class IfcFlowInstrument;
		 class IfcFlowInstrumentType;
		 class IfcFlowInstrumentTypeEnum;
		 class IfcFlowMeter;
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
		 class IfcFontStyle;
		 class IfcFontVariant;
		 class IfcFontWeight;
		 class IfcFooting;
		 class IfcFootingType;
		 class IfcFootingTypeEnum;
		 class IfcForceMeasure;
		 class IfcFrequencyMeasure;
		 class IfcFurnishingElement;
		 class IfcFurnishingElementType;
		 class IfcFurniture;
		 class IfcFurnitureType;
		 class IfcFurnitureTypeEnum;
		 class IfcGeographicElement;
		 class IfcGeographicElementType;
		 class IfcGeographicElementTypeEnum;
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
		 class IfcGridPlacementDirectionSelect;
		 class IfcGridTypeEnum;
		 class IfcGroup;
		 class IfcHalfSpaceSolid;
		 class IfcHatchLineDistanceSelect;
		 class IfcHeatExchanger;
		 class IfcHeatExchangerType;
		 class IfcHeatExchangerTypeEnum;
		 class IfcHeatFluxDensityMeasure;
		 class IfcHeatingValueMeasure;
		 class IfcHumidifier;
		 class IfcHumidifierType;
		 class IfcHumidifierTypeEnum;
		 class IfcIdentifier;
		 class IfcIlluminanceMeasure;
		 class IfcImageTexture;
		 class IfcIndexedColourMap;
		 class IfcIndexedTextureMap;
		 class IfcIndexedTriangleTextureMap;
		 class IfcInductanceMeasure;
		 class IfcInteger;
		 class IfcIntegerCountRateMeasure;
		 class IfcInterceptor;
		 class IfcInterceptorType;
		 class IfcInterceptorTypeEnum;
		 class IfcInternalOrExternalEnum;
		 class IfcInventory;
		 class IfcInventoryTypeEnum;
		 class IfcIonConcentrationMeasure;
		 class IfcIrregularTimeSeries;
		 class IfcIrregularTimeSeriesValue;
		 class IfcIShapeProfileDef;
		 class IfcIsothermalMoistureCapacityMeasure;
		 class IfcJunctionBox;
		 class IfcJunctionBoxType;
		 class IfcJunctionBoxTypeEnum;
		 class IfcKinematicViscosityMeasure;
		 class IfcKnotType;
		 class IfcLabel;
		 class IfcLaborResource;
		 class IfcLaborResourceType;
		 class IfcLaborResourceTypeEnum;
		 class IfcLagTime;
		 class IfcLamp;
		 class IfcLampType;
		 class IfcLampTypeEnum;
		 class IfcLanguageId;
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
		 class IfcLightFixture;
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
		 class IfcLinearForceMeasure;
		 class IfcLinearMomentMeasure;
		 class IfcLinearStiffnessMeasure;
		 class IfcLinearVelocityMeasure;
		 class IfcLoadGroupTypeEnum;
		 class IfcLocalPlacement;
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
		 class IfcMapConversion;
		 class IfcMappedItem;
		 class IfcMassDensityMeasure;
		 class IfcMassFlowRateMeasure;
		 class IfcMassMeasure;
		 class IfcMassPerLengthMeasure;
		 class IfcMaterial;
		 class IfcMaterialClassificationRelationship;
		 class IfcMaterialConstituent;
		 class IfcMaterialConstituentSet;
		 class IfcMaterialDefinition;
		 class IfcMaterialDefinitionRepresentation;
		 class IfcMaterialLayer;
		 class IfcMaterialLayerSet;
		 class IfcMaterialLayerSetUsage;
		 class IfcMaterialLayerWithOffsets;
		 class IfcMaterialList;
		 class IfcMaterialProfile;
		 class IfcMaterialProfileSet;
		 class IfcMaterialProfileSetUsage;
		 class IfcMaterialProfileSetUsageTapering;
		 class IfcMaterialProfileWithOffsets;
		 class IfcMaterialProperties;
		 class IfcMaterialRelationship;
		 class IfcMaterialSelect;
		 class IfcMaterialUsageDefinition;
		 class IfcMeasureValue;
		 class IfcMeasureWithUnit;
		 class IfcMechanicalFastener;
		 class IfcMechanicalFastenerType;
		 class IfcMechanicalFastenerTypeEnum;
		 class IfcMedicalDevice;
		 class IfcMedicalDeviceType;
		 class IfcMedicalDeviceTypeEnum;
		 class IfcMember;
		 class IfcMemberStandardCase;
		 class IfcMemberType;
		 class IfcMemberTypeEnum;
		 class IfcMetric;
		 class IfcMetricValueSelect;
		 class IfcMirroredProfileDef;
		 class IfcModulusOfElasticityMeasure;
		 class IfcModulusOfLinearSubgradeReactionMeasure;
		 class IfcModulusOfRotationalSubgradeReactionMeasure;
		 class IfcModulusOfRotationalSubgradeReactionSelect;
		 class IfcModulusOfSubgradeReactionMeasure;
		 class IfcModulusOfSubgradeReactionSelect;
		 class IfcModulusOfTranslationalSubgradeReactionSelect;
		 class IfcMoistureDiffusivityMeasure;
		 class IfcMolecularWeightMeasure;
		 class IfcMomentOfInertiaMeasure;
		 class IfcMonetaryMeasure;
		 class IfcMonetaryUnit;
		 class IfcMonthInYearNumber;
		 class IfcMotorConnection;
		 class IfcMotorConnectionType;
		 class IfcMotorConnectionTypeEnum;
		 class IfcNamedUnit;
		 class IfcNonNegativeLengthMeasure;
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
		 class IfcOpeningElementTypeEnum;
		 class IfcOpeningStandardCase;
		 class IfcOpenShell;
		 class IfcOrganization;
		 class IfcOrganizationRelationship;
		 class IfcOrientedEdge;
		 class IfcOuterBoundaryCurve;
		 class IfcOutlet;
		 class IfcOutletType;
		 class IfcOutletTypeEnum;
		 class IfcOwnerHistory;
		 class IfcParameterizedProfileDef;
		 class IfcParameterValue;
		 class IfcPath;
		 class IfcPcurve;
		 class IfcPerformanceHistory;
		 class IfcPerformanceHistoryTypeEnum;
		 class IfcPermeableCoveringOperationEnum;
		 class IfcPermeableCoveringProperties;
		 class IfcPermit;
		 class IfcPermitTypeEnum;
		 class IfcPerson;
		 class IfcPersonAndOrganization;
		 class IfcPHMeasure;
		 class IfcPhysicalComplexQuantity;
		 class IfcPhysicalOrVirtualEnum;
		 class IfcPhysicalQuantity;
		 class IfcPhysicalSimpleQuantity;
		 class IfcPile;
		 class IfcPileConstructionEnum;
		 class IfcPileType;
		 class IfcPileTypeEnum;
		 class IfcPipeFitting;
		 class IfcPipeFittingType;
		 class IfcPipeFittingTypeEnum;
		 class IfcPipeSegment;
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
		 class IfcPlateStandardCase;
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
		 class IfcPreDefinedItem;
		 class IfcPreDefinedProperties;
		 class IfcPreDefinedPropertySet;
		 class IfcPreDefinedSymbol;
		 class IfcPreDefinedTextFont;
		 class IfcPresentableText;
		 class IfcPresentationItem;
		 class IfcPresentationLayerAssignment;
		 class IfcPresentationLayerWithStyle;
		 class IfcPresentationStyle;
		 class IfcPresentationStyleAssignment;
		 class IfcPresentationStyleSelect;
		 class IfcPressureMeasure;
		 class IfcProcedure;
		 class IfcProcedureType;
		 class IfcProcedureTypeEnum;
		 class IfcProcess;
		 class IfcProcessSelect;
		 class IfcProduct;
		 class IfcProductDefinitionShape;
		 class IfcProductRepresentation;
		 class IfcProductSelect;
		 class IfcProfileDef;
		 class IfcProfileProperties;
		 class IfcProfileTypeEnum;
		 class IfcProject;
		 class IfcProjectedCRS;
		 class IfcProjectedOrTrueLengthEnum;
		 class IfcProjectionElement;
		 class IfcProjectionElementTypeEnum;
		 class IfcProjectLibrary;
		 class IfcProjectOrder;
		 class IfcProjectOrderTypeEnum;
		 class IfcProperty;
		 class IfcPropertyAbstraction;
		 class IfcPropertyBoundedValue;
		 class IfcPropertyDefinition;
		 class IfcPropertyDependencyRelationship;
		 class IfcPropertyEnumeratedValue;
		 class IfcPropertyEnumeration;
		 class IfcPropertyListValue;
		 class IfcPropertyReferenceValue;
		 class IfcPropertySet;
		 class IfcPropertySetDefinition;
		 class IfcPropertySetTemplate;
		 class IfcPropertySetTemplateTypeEnum;
		 class IfcPropertySingleValue;
		 class IfcPropertyTableValue;
		 class IfcPropertyTemplate;
		 class IfcPropertyTemplateDefinition;
		 class IfcProtectiveDevice;
		 class IfcProtectiveDeviceTrippingUnit;
		 class IfcProtectiveDeviceTrippingUnitType;
		 class IfcProtectiveDeviceTrippingUnitTypeEnum;
		 class IfcProtectiveDeviceType;
		 class IfcProtectiveDeviceTypeEnum;
		 class IfcProxy;
		 class IfcPump;
		 class IfcPumpType;
		 class IfcPumpTypeEnum;
		 class IfcQuantityArea;
		 class IfcQuantityCount;
		 class IfcQuantityLength;
		 class IfcQuantitySet;
		 class IfcQuantityTime;
		 class IfcQuantityVolume;
		 class IfcQuantityWeight;
		 class IfcRadioActivityMeasure;
		 class IfcRailing;
		 class IfcRailingType;
		 class IfcRailingTypeEnum;
		 class IfcRamp;
		 class IfcRampFlight;
		 class IfcRampFlightType;
		 class IfcRampFlightTypeEnum;
		 class IfcRampType;
		 class IfcRampTypeEnum;
		 class IfcRatioMeasure;
		 class IfcRationalBSplineCurveWithKnots;
		 class IfcRationalBSplineSurfaceWithKnots;
		 class IfcReal;
		 class IfcRectangleHollowProfileDef;
		 class IfcRectangleProfileDef;
		 class IfcRectangularPyramid;
		 class IfcRectangularTrimmedSurface;
		 class IfcRecurrencePattern;
		 class IfcRecurrenceTypeEnum;
		 class IfcReferenceCurve;
		 class IfcReferenceCurve3D;
		 class IfcReferenceCurveAlignment2D;
		 class IfcReferenceCurvePlacement;
		 class IfcReferenceCurvePlacementSystem;
		 class IfcReferencedSectionedSpine;
		 class IfcReferenceElement;
		 class IfcReferencePlacement;
		 class IfcReflectanceMethodEnum;
		 class IfcRegularTimeSeries;
		 class IfcReinforcementBarProperties;
		 class IfcReinforcementDefinitionProperties;
		 class IfcReinforcingBar;
		 class IfcReinforcingBarRoleEnum;
		 class IfcReinforcingBarSurfaceEnum;
		 class IfcReinforcingBarType;
		 class IfcReinforcingBarTypeEnum;
		 class IfcReinforcingElement;
		 class IfcReinforcingElementType;
		 class IfcReinforcingMesh;
		 class IfcReinforcingMeshType;
		 class IfcReinforcingMeshTypeEnum;
		 class IfcRelAggregates;
		 class IfcRelAssigns;
		 class IfcRelAssignsToActor;
		 class IfcRelAssignsToControl;
		 class IfcRelAssignsToGroup;
		 class IfcRelAssignsToGroupByFactor;
		 class IfcRelAssignsToProcess;
		 class IfcRelAssignsToProduct;
		 class IfcRelAssignsToResource;
		 class IfcRelAssociates;
		 class IfcRelAssociatesApproval;
		 class IfcRelAssociatesClassification;
		 class IfcRelAssociatesConstraint;
		 class IfcRelAssociatesDocument;
		 class IfcRelAssociatesLibrary;
		 class IfcRelAssociatesMaterial;
		 class IfcRelationship;
		 class IfcRelConnects;
		 class IfcRelConnectsElements;
		 class IfcRelConnectsPathElements;
		 class IfcRelConnectsPorts;
		 class IfcRelConnectsPortToElement;
		 class IfcRelConnectsStructuralActivity;
		 class IfcRelConnectsStructuralMember;
		 class IfcRelConnectsWithEccentricity;
		 class IfcRelConnectsWithRealizingElements;
		 class IfcRelContainedInSpatialStructure;
		 class IfcRelCoversBldgElements;
		 class IfcRelCoversSpaces;
		 class IfcRelDeclares;
		 class IfcRelDecomposes;
		 class IfcRelDefines;
		 class IfcRelDefinesByObject;
		 class IfcRelDefinesByProperties;
		 class IfcRelDefinesByTemplate;
		 class IfcRelDefinesByType;
		 class IfcRelFillsElement;
		 class IfcRelFlowControlElements;
		 class IfcRelInterferesElements;
		 class IfcRelNests;
		 class IfcRelProjectsElement;
		 class IfcRelReferencedInSpatialStructure;
		 class IfcRelSequence;
		 class IfcRelServicesBuildings;
		 class IfcRelSpaceBoundary;
		 class IfcRelSpaceBoundary1stLevel;
		 class IfcRelSpaceBoundary2ndLevel;
		 class IfcRelVoidsElement;
		 class IfcReparametrisedCompositeCurveSegment;
		 class IfcRepresentation;
		 class IfcRepresentationContext;
		 class IfcRepresentationItem;
		 class IfcRepresentationMap;
		 class IfcResource;
		 class IfcResourceApprovalRelationship;
		 class IfcResourceConstraintRelationship;
		 class IfcResourceConsumptionEnum;
		 class IfcResourceCost;
		 class IfcResourceLevelRelationship;
		 class IfcResourceObjectSelect;
		 class IfcResourceSelect;
		 class IfcResourceTime;
		 class IfcRevolvedAreaSolid;
		 class IfcRevolvedAreaSolidTapered;
		 class IfcRightCircularCone;
		 class IfcRightCircularCylinder;
		 class IfcRoleEnum;
		 class IfcRoof;
		 class IfcRoofType;
		 class IfcRoofTypeEnum;
		 class IfcRoot;
		 class IfcRotationalFrequencyMeasure;
		 class IfcRotationalMassMeasure;
		 class IfcRotationalStiffnessMeasure;
		 class IfcRotationalStiffnessSelect;
		 class IfcRoundedRectangleProfileDef;
		 class IfcSanitaryTerminal;
		 class IfcSanitaryTerminalType;
		 class IfcSanitaryTerminalTypeEnum;
		 class IfcSchedulingTime;
		 class IfcSectionalAreaIntegralMeasure;
		 class IfcSectionedSpine;
		 class IfcSectionModulusMeasure;
		 class IfcSectionProperties;
		 class IfcSectionReinforcementProperties;
		 class IfcSectionTypeEnum;
		 class IfcSensor;
		 class IfcSensorType;
		 class IfcSensorTypeEnum;
		 class IfcSequenceEnum;
		 class IfcShadingDevice;
		 class IfcShadingDeviceType;
		 class IfcShadingDeviceTypeEnum;
		 class IfcShapeAspect;
		 class IfcShapeModel;
		 class IfcShapeRepresentation;
		 class IfcShearModulusMeasure;
		 class IfcShell;
		 class IfcShellBasedSurfaceModel;
		 class IfcSimpleProperty;
		 class IfcSimplePropertyTemplate;
		 class IfcSimplePropertyTemplateTypeEnum;
		 class IfcSimpleValue;
		 class IfcSIPrefix;
		 class IfcSite;
		 class IfcSIUnit;
		 class IfcSIUnitName;
		 class IfcSizeSelect;
		 class IfcSlab;
		 class IfcSlabElementedCase;
		 class IfcSlabStandardCase;
		 class IfcSlabType;
		 class IfcSlabTypeEnum;
		 class IfcSlippageConnectionCondition;
		 class IfcSolarDevice;
		 class IfcSolarDeviceType;
		 class IfcSolarDeviceTypeEnum;
		 class IfcSolidAngleMeasure;
		 class IfcSolidModel;
		 class IfcSolidOrShell;
		 class IfcSoundPowerMeasure;
		 class IfcSoundPressureMeasure;
		 class IfcSpace;
		 class IfcSpaceBoundarySelect;
		 class IfcSpaceHeater;
		 class IfcSpaceHeaterType;
		 class IfcSpaceHeaterTypeEnum;
		 class IfcSpaceType;
		 class IfcSpaceTypeEnum;
		 class IfcSpatialElement;
		 class IfcSpatialElementType;
		 class IfcSpatialStructureElement;
		 class IfcSpatialStructureElementType;
		 class IfcSpatialZone;
		 class IfcSpatialZoneType;
		 class IfcSpatialZoneTypeEnum;
		 class IfcSpecificHeatCapacityMeasure;
		 class IfcSpecularExponent;
		 class IfcSpecularHighlightSelect;
		 class IfcSpecularRoughness;
		 class IfcSphere;
		 class IfcStackTerminal;
		 class IfcStackTerminalType;
		 class IfcStackTerminalTypeEnum;
		 class IfcStair;
		 class IfcStairFlight;
		 class IfcStairFlightType;
		 class IfcStairFlightTypeEnum;
		 class IfcStairType;
		 class IfcStairTypeEnum;
		 class IfcStateEnum;
		 class IfcStructuralAction;
		 class IfcStructuralActivity;
		 class IfcStructuralActivityAssignmentSelect;
		 class IfcStructuralAnalysisModel;
		 class IfcStructuralConnection;
		 class IfcStructuralConnectionCondition;
		 class IfcStructuralCurveAction;
		 class IfcStructuralCurveActivityTypeEnum;
		 class IfcStructuralCurveConnection;
		 class IfcStructuralCurveMember;
		 class IfcStructuralCurveMemberTypeEnum;
		 class IfcStructuralCurveMemberVarying;
		 class IfcStructuralCurveReaction;
		 class IfcStructuralItem;
		 class IfcStructuralLinearAction;
		 class IfcStructuralLoad;
		 class IfcStructuralLoadCase;
		 class IfcStructuralLoadConfiguration;
		 class IfcStructuralLoadGroup;
		 class IfcStructuralLoadLinearForce;
		 class IfcStructuralLoadOrResult;
		 class IfcStructuralLoadPlanarForce;
		 class IfcStructuralLoadSingleDisplacement;
		 class IfcStructuralLoadSingleDisplacementDistortion;
		 class IfcStructuralLoadSingleForce;
		 class IfcStructuralLoadSingleForceWarping;
		 class IfcStructuralLoadStatic;
		 class IfcStructuralLoadTemperature;
		 class IfcStructuralMember;
		 class IfcStructuralPlanarAction;
		 class IfcStructuralPointAction;
		 class IfcStructuralPointConnection;
		 class IfcStructuralPointReaction;
		 class IfcStructuralReaction;
		 class IfcStructuralResultGroup;
		 class IfcStructuralSurfaceAction;
		 class IfcStructuralSurfaceActivityTypeEnum;
		 class IfcStructuralSurfaceConnection;
		 class IfcStructuralSurfaceMember;
		 class IfcStructuralSurfaceMemberTypeEnum;
		 class IfcStructuralSurfaceMemberVarying;
		 class IfcStructuralSurfaceReaction;
		 class IfcStyleAssignmentSelect;
		 class IfcStyledItem;
		 class IfcStyledRepresentation;
		 class IfcStyleModel;
		 class IfcSubContractResource;
		 class IfcSubContractResourceType;
		 class IfcSubContractResourceTypeEnum;
		 class IfcSubedge;
		 class IfcSurface;
		 class IfcSurfaceCurveSweptAreaSolid;
		 class IfcSurfaceFeature;
		 class IfcSurfaceFeatureTypeEnum;
		 class IfcSurfaceOfLinearExtrusion;
		 class IfcSurfaceOfRevolution;
		 class IfcSurfaceOrFaceSurface;
		 class IfcSurfaceReinforcementArea;
		 class IfcSurfaceSide;
		 class IfcSurfaceStyle;
		 class IfcSurfaceStyleElementSelect;
		 class IfcSurfaceStyleLighting;
		 class IfcSurfaceStyleRefraction;
		 class IfcSurfaceStyleRendering;
		 class IfcSurfaceStyleShading;
		 class IfcSurfaceStyleWithTextures;
		 class IfcSurfaceTexture;
		 class IfcSweptAreaSolid;
		 class IfcSweptDiskSolid;
		 class IfcSweptDiskSolidPolygonal;
		 class IfcSweptSurface;
		 class IfcSwitchingDevice;
		 class IfcSwitchingDeviceType;
		 class IfcSwitchingDeviceTypeEnum;
		 class IfcSymbolStyle;
		 class IfcSymbolStyleSelect;
		 class IfcSystem;
		 class IfcSystemFurnitureElement;
		 class IfcSystemFurnitureElementType;
		 class IfcSystemFurnitureElementTypeEnum;
		 class IfcTable;
		 class IfcTableColumn;
		 class IfcTableRow;
		 class IfcTank;
		 class IfcTankType;
		 class IfcTankTypeEnum;
		 class IfcTask;
		 class IfcTaskDurationEnum;
		 class IfcTaskTime;
		 class IfcTaskTimeRecurring;
		 class IfcTaskType;
		 class IfcTaskTypeEnum;
		 class IfcTelecomAddress;
		 class IfcTemperatureGradientMeasure;
		 class IfcTemperatureRateOfChangeMeasure;
		 class IfcTendon;
		 class IfcTendonAnchor;
		 class IfcTendonAnchorType;
		 class IfcTendonAnchorTypeEnum;
		 class IfcTendonType;
		 class IfcTendonTypeEnum;
		 class IfcTessellatedFaceSet;
		 class IfcTessellatedItem;
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
		 class IfcTextureVertexList;
		 class IfcThermalAdmittanceMeasure;
		 class IfcThermalConductivityMeasure;
		 class IfcThermalExpansionCoefficientMeasure;
		 class IfcThermalResistanceMeasure;
		 class IfcThermalTransmittanceMeasure;
		 class IfcThermodynamicTemperatureMeasure;
		 class IfcTime;
		 class IfcTimeMeasure;
		 class IfcTimeOrRatioSelect;
		 class IfcTimePeriod;
		 class IfcTimeSeries;
		 class IfcTimeSeriesDataTypeEnum;
		 class IfcTimeSeriesValue;
		 class IfcTimeStamp;
		 class IfcTopologicalRepresentationItem;
		 class IfcTopologyRepresentation;
		 class IfcTorqueMeasure;
		 class IfcTransformer;
		 class IfcTransformerType;
		 class IfcTransformerTypeEnum;
		 class IfcTransitionCode;
		 class IfcTranslationalStiffnessSelect;
		 class IfcTransportElement;
		 class IfcTransportElementType;
		 class IfcTransportElementTypeEnum;
		 class IfcTrapeziumProfileDef;
		 class IfcTriangulatedFaceSet;
		 class IfcTrimmedCurve;
		 class IfcTrimmingPreference;
		 class IfcTrimmingSelect;
		 class IfcTShapeProfileDef;
		 class IfcTubeBundle;
		 class IfcTubeBundleType;
		 class IfcTubeBundleTypeEnum;
		 class IfcTwoDirectionRepeatFactor;
		 class IfcTypeObject;
		 class IfcTypeProcess;
		 class IfcTypeProduct;
		 class IfcTypeResource;
		 class IfcUnit;
		 class IfcUnitaryControlElement;
		 class IfcUnitaryControlElementType;
		 class IfcUnitaryControlElementTypeEnum;
		 class IfcUnitaryEquipment;
		 class IfcUnitaryEquipmentType;
		 class IfcUnitaryEquipmentTypeEnum;
		 class IfcUnitAssignment;
		 class IfcUnitEnum;
		 class IfcURIReference;
		 class IfcUShapeProfileDef;
		 class IfcValue;
		 class IfcValve;
		 class IfcValveType;
		 class IfcValveTypeEnum;
		 class IfcVaporPermeabilityMeasure;
		 class IfcVector;
		 class IfcVectorOrDirection;
		 class IfcVertex;
		 class IfcVertexLoop;
		 class IfcVertexPoint;
		 class IfcVibrationIsolator;
		 class IfcVibrationIsolatorType;
		 class IfcVibrationIsolatorTypeEnum;
		 class IfcVirtualElement;
		 class IfcVirtualGridIntersection;
		 class IfcVoidingFeature;
		 class IfcVoidingFeatureTypeEnum;
		 class IfcVolumeMeasure;
		 class IfcVolumetricFlowRateMeasure;
		 class IfcWall;
		 class IfcWallElementedCase;
		 class IfcWallStandardCase;
		 class IfcWallType;
		 class IfcWallTypeEnum;
		 class IfcWarpingConstantMeasure;
		 class IfcWarpingMomentMeasure;
		 class IfcWarpingStiffnessSelect;
		 class IfcWasteTerminal;
		 class IfcWasteTerminalType;
		 class IfcWasteTerminalTypeEnum;
		 class IfcWindow;
		 class IfcWindowLiningProperties;
		 class IfcWindowPanelOperationEnum;
		 class IfcWindowPanelPositionEnum;
		 class IfcWindowPanelProperties;
		 class IfcWindowStandardCase;
		 class IfcWindowStyle;
		 class IfcWindowStyleConstructionEnum;
		 class IfcWindowStyleOperationEnum;
		 class IfcWindowType;
		 class IfcWindowTypeEnum;
		 class IfcWindowTypePartitioningEnum;
		 class IfcWorkCalendar;
		 class IfcWorkCalendarTypeEnum;
		 class IfcWorkControl;
		 class IfcWorkPlan;
		 class IfcWorkPlanTypeEnum;
		 class IfcWorkSchedule;
		 class IfcWorkScheduleTypeEnum;
		 class IfcWorkTime;
		 class IfcZone;
		 class IfcZShapeProfileDef;
	}
}

namespace emt
{
	typedef BasicIfcBridgeEntityTypes<
		OpenInfraPlatform::IfcBridge::IfcAbsorbedDoseMeasure,
		OpenInfraPlatform::IfcBridge::IfcAccelerationMeasure,
		OpenInfraPlatform::IfcBridge::IfcActionRequest,
		OpenInfraPlatform::IfcBridge::IfcActionRequestTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcActionSourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcActionTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcActor,
		OpenInfraPlatform::IfcBridge::IfcActorRole,
		OpenInfraPlatform::IfcBridge::IfcActorSelect,
		OpenInfraPlatform::IfcBridge::IfcActuator,
		OpenInfraPlatform::IfcBridge::IfcActuatorType,
		OpenInfraPlatform::IfcBridge::IfcActuatorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAddress,
		OpenInfraPlatform::IfcBridge::IfcAddressTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAdvancedBrep,
		OpenInfraPlatform::IfcBridge::IfcAdvancedBrepWithVoids,
		OpenInfraPlatform::IfcBridge::IfcAdvancedFace,
		OpenInfraPlatform::IfcBridge::IfcAirTerminal,
		OpenInfraPlatform::IfcBridge::IfcAirTerminalBox,
		OpenInfraPlatform::IfcBridge::IfcAirTerminalBoxType,
		OpenInfraPlatform::IfcBridge::IfcAirTerminalBoxTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAirTerminalType,
		OpenInfraPlatform::IfcBridge::IfcAirTerminalTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAirToAirHeatRecovery,
		OpenInfraPlatform::IfcBridge::IfcAirToAirHeatRecoveryType,
		OpenInfraPlatform::IfcBridge::IfcAirToAirHeatRecoveryTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAlarm,
		OpenInfraPlatform::IfcBridge::IfcAlarmType,
		OpenInfraPlatform::IfcBridge::IfcAlarmTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAlignmentElement,
		OpenInfraPlatform::IfcBridge::IfcAmountOfSubstanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcAnalysisModelTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAnalysisTheoryTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAngularVelocityMeasure,
		OpenInfraPlatform::IfcBridge::IfcAnnotation,
		OpenInfraPlatform::IfcBridge::IfcAnnotationFillArea,
		OpenInfraPlatform::IfcBridge::IfcApplication,
		OpenInfraPlatform::IfcBridge::IfcAppliedValue,
		OpenInfraPlatform::IfcBridge::IfcAppliedValueRelationship,
		OpenInfraPlatform::IfcBridge::IfcAppliedValueSelect,
		OpenInfraPlatform::IfcBridge::IfcApproval,
		OpenInfraPlatform::IfcBridge::IfcApprovalRelationship,
		OpenInfraPlatform::IfcBridge::IfcArbitraryClosedProfileDef,
		OpenInfraPlatform::IfcBridge::IfcArbitraryOpenProfileDef,
		OpenInfraPlatform::IfcBridge::IfcArbitraryProfileDefWithVoids,
		OpenInfraPlatform::IfcBridge::IfcAreaMeasure,
		OpenInfraPlatform::IfcBridge::IfcArithmeticOperatorEnum,
		OpenInfraPlatform::IfcBridge::IfcAssemblyPlaceEnum,
		OpenInfraPlatform::IfcBridge::IfcAsset,
		OpenInfraPlatform::IfcBridge::IfcAsymmetricIShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcAudioVisualAppliance,
		OpenInfraPlatform::IfcBridge::IfcAudioVisualApplianceType,
		OpenInfraPlatform::IfcBridge::IfcAudioVisualApplianceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcAxis1Placement,
		OpenInfraPlatform::IfcBridge::IfcAxis2Placement,
		OpenInfraPlatform::IfcBridge::IfcAxis2Placement2D,
		OpenInfraPlatform::IfcBridge::IfcAxis2Placement3D,
		OpenInfraPlatform::IfcBridge::IfcBeam,
		OpenInfraPlatform::IfcBridge::IfcBeamStandardCase,
		OpenInfraPlatform::IfcBridge::IfcBeamType,
		OpenInfraPlatform::IfcBridge::IfcBeamTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcBenchmarkEnum,
		OpenInfraPlatform::IfcBridge::IfcBendingParameterSelect,
		OpenInfraPlatform::IfcBridge::IfcBlobTexture,
		OpenInfraPlatform::IfcBridge::IfcBlock,
		OpenInfraPlatform::IfcBridge::IfcBoiler,
		OpenInfraPlatform::IfcBridge::IfcBoilerType,
		OpenInfraPlatform::IfcBridge::IfcBoilerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcBoolean,
		OpenInfraPlatform::IfcBridge::IfcBooleanClippingResult,
		OpenInfraPlatform::IfcBridge::IfcBooleanOperand,
		OpenInfraPlatform::IfcBridge::IfcBooleanOperator,
		OpenInfraPlatform::IfcBridge::IfcBooleanResult,
		OpenInfraPlatform::IfcBridge::IfcBoundaryCondition,
		OpenInfraPlatform::IfcBridge::IfcBoundaryCurve,
		OpenInfraPlatform::IfcBridge::IfcBoundaryEdgeCondition,
		OpenInfraPlatform::IfcBridge::IfcBoundaryFaceCondition,
		OpenInfraPlatform::IfcBridge::IfcBoundaryNodeCondition,
		OpenInfraPlatform::IfcBridge::IfcBoundaryNodeConditionWarping,
		OpenInfraPlatform::IfcBridge::IfcBoundedCurve,
		OpenInfraPlatform::IfcBridge::IfcBoundedSurface,
		OpenInfraPlatform::IfcBridge::IfcBoundingBox,
		OpenInfraPlatform::IfcBridge::IfcBoxAlignment,
		OpenInfraPlatform::IfcBridge::IfcBoxedHalfSpace,
		OpenInfraPlatform::IfcBridge::IfcBridge,
		OpenInfraPlatform::IfcBridge::IfcBridgeContactElement,
		OpenInfraPlatform::IfcBridge::IfcBridgeContactType,
		OpenInfraPlatform::IfcBridge::IfcBridgeElement,
		OpenInfraPlatform::IfcBridge::IfcBridgeMechanicalRoleType,
		OpenInfraPlatform::IfcBridge::IfcBridgePart,
		OpenInfraPlatform::IfcBridge::IfcBridgePrismaticElement,
		OpenInfraPlatform::IfcBridge::IfcBridgePrismaticElementType,
		OpenInfraPlatform::IfcBridge::IfcBridgeSegment,
		OpenInfraPlatform::IfcBridge::IfcBridgeSegmentPart,
		OpenInfraPlatform::IfcBridge::IfcBridgeSegmentType,
		OpenInfraPlatform::IfcBridge::IfcBridgeStructureElement,
		OpenInfraPlatform::IfcBridge::IfcBridgeStructureElementType,
		OpenInfraPlatform::IfcBridge::IfcBridgeStructureIndicator,
		OpenInfraPlatform::IfcBridge::IfcBridgeStructureType,
		OpenInfraPlatform::IfcBridge::IfcBridgeSubPartType,
		OpenInfraPlatform::IfcBridge::IfcBridgeTechnologicalElementType,
		OpenInfraPlatform::IfcBridge::IfcBSplineCurve,
		OpenInfraPlatform::IfcBridge::IfcBSplineCurveForm,
		OpenInfraPlatform::IfcBridge::IfcBSplineCurveWithKnots,
		OpenInfraPlatform::IfcBridge::IfcBSplineSurface,
		OpenInfraPlatform::IfcBridge::IfcBSplineSurfaceForm,
		OpenInfraPlatform::IfcBridge::IfcBSplineSurfaceWithKnots,
		OpenInfraPlatform::IfcBridge::IfcBuilding,
		OpenInfraPlatform::IfcBridge::IfcBuildingElement,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementPart,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementPartType,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementPartTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementProxy,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementProxyType,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementProxyTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcBuildingElementType,
		OpenInfraPlatform::IfcBridge::IfcBuildingStorey,
		OpenInfraPlatform::IfcBridge::IfcBuildingSystem,
		OpenInfraPlatform::IfcBridge::IfcBuildingSystemTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcBurner,
		OpenInfraPlatform::IfcBridge::IfcBurnerType,
		OpenInfraPlatform::IfcBridge::IfcBurnerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierFitting,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierFittingType,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierFittingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierSegment,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierSegmentType,
		OpenInfraPlatform::IfcBridge::IfcCableCarrierSegmentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCableFitting,
		OpenInfraPlatform::IfcBridge::IfcCableFittingType,
		OpenInfraPlatform::IfcBridge::IfcCableFittingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCableSegment,
		OpenInfraPlatform::IfcBridge::IfcCableSegmentType,
		OpenInfraPlatform::IfcBridge::IfcCableSegmentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCardinalPointReference,
		OpenInfraPlatform::IfcBridge::IfcCartesianPoint,
		OpenInfraPlatform::IfcBridge::IfcCartesianPointList,
		OpenInfraPlatform::IfcBridge::IfcCartesianTransformationOperator,
		OpenInfraPlatform::IfcBridge::IfcCartesianTransformationOperator2D,
		OpenInfraPlatform::IfcBridge::IfcCartesianTransformationOperator2DnonUniform,
		OpenInfraPlatform::IfcBridge::IfcCartesianTransformationOperator3D,
		OpenInfraPlatform::IfcBridge::IfcCartesianTransformationOperator3DnonUniform,
		OpenInfraPlatform::IfcBridge::IfcCenterLineProfileDef,
		OpenInfraPlatform::IfcBridge::IfcChangeActionEnum,
		OpenInfraPlatform::IfcBridge::IfcCharacterStyleSelect,
		OpenInfraPlatform::IfcBridge::IfcChiller,
		OpenInfraPlatform::IfcBridge::IfcChillerType,
		OpenInfraPlatform::IfcBridge::IfcChillerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcChimney,
		OpenInfraPlatform::IfcBridge::IfcChimneyType,
		OpenInfraPlatform::IfcBridge::IfcChimneyTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCircle,
		OpenInfraPlatform::IfcBridge::IfcCircleHollowProfileDef,
		OpenInfraPlatform::IfcBridge::IfcCircleProfileDef,
		OpenInfraPlatform::IfcBridge::IfcCivilElement,
		OpenInfraPlatform::IfcBridge::IfcCivilElementPart,
		OpenInfraPlatform::IfcBridge::IfcCivilSheath,
		OpenInfraPlatform::IfcBridge::IfcCivilStructureElement,
		OpenInfraPlatform::IfcBridge::IfcCivilVoid,
		OpenInfraPlatform::IfcBridge::IfcClassification,
		OpenInfraPlatform::IfcBridge::IfcClassificationReference,
		OpenInfraPlatform::IfcBridge::IfcClassificationReferenceSelect,
		OpenInfraPlatform::IfcBridge::IfcClassificationSelect,
		OpenInfraPlatform::IfcBridge::IfcClosedShell,
		OpenInfraPlatform::IfcBridge::IfcClothoid,
		OpenInfraPlatform::IfcBridge::IfcCoil,
		OpenInfraPlatform::IfcBridge::IfcCoilType,
		OpenInfraPlatform::IfcBridge::IfcCoilTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcColour,
		OpenInfraPlatform::IfcBridge::IfcColourOrFactor,
		OpenInfraPlatform::IfcBridge::IfcColourRgb,
		OpenInfraPlatform::IfcBridge::IfcColourRgbList,
		OpenInfraPlatform::IfcBridge::IfcColourSpecification,
		OpenInfraPlatform::IfcBridge::IfcColumn,
		OpenInfraPlatform::IfcBridge::IfcColumnStandardCase,
		OpenInfraPlatform::IfcBridge::IfcColumnType,
		OpenInfraPlatform::IfcBridge::IfcColumnTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCommunicationsAppliance,
		OpenInfraPlatform::IfcBridge::IfcCommunicationsApplianceType,
		OpenInfraPlatform::IfcBridge::IfcCommunicationsApplianceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcComplexNumber,
		OpenInfraPlatform::IfcBridge::IfcComplexProperty,
		OpenInfraPlatform::IfcBridge::IfcComplexPropertyTemplate,
		OpenInfraPlatform::IfcBridge::IfcComplexPropertyTemplateTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCompositeCurve,
		OpenInfraPlatform::IfcBridge::IfcCompositeCurveOnSurface,
		OpenInfraPlatform::IfcBridge::IfcCompositeCurveSegment,
		OpenInfraPlatform::IfcBridge::IfcCompositeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcCompoundPlaneAngleMeasure,
		OpenInfraPlatform::IfcBridge::IfcCompressor,
		OpenInfraPlatform::IfcBridge::IfcCompressorType,
		OpenInfraPlatform::IfcBridge::IfcCompressorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCondenser,
		OpenInfraPlatform::IfcBridge::IfcCondenserType,
		OpenInfraPlatform::IfcBridge::IfcCondenserTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConic,
		OpenInfraPlatform::IfcBridge::IfcConnectedFaceSet,
		OpenInfraPlatform::IfcBridge::IfcConnectionCurveGeometry,
		OpenInfraPlatform::IfcBridge::IfcConnectionGeometry,
		OpenInfraPlatform::IfcBridge::IfcConnectionPointEccentricity,
		OpenInfraPlatform::IfcBridge::IfcConnectionPointGeometry,
		OpenInfraPlatform::IfcBridge::IfcConnectionSurfaceGeometry,
		OpenInfraPlatform::IfcBridge::IfcConnectionTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConnectionVolumeGeometry,
		OpenInfraPlatform::IfcBridge::IfcConstraint,
		OpenInfraPlatform::IfcBridge::IfcConstraintEnum,
		OpenInfraPlatform::IfcBridge::IfcConstructionEquipmentResource,
		OpenInfraPlatform::IfcBridge::IfcConstructionEquipmentResourceType,
		OpenInfraPlatform::IfcBridge::IfcConstructionEquipmentResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConstructionMaterialResource,
		OpenInfraPlatform::IfcBridge::IfcConstructionMaterialResourceType,
		OpenInfraPlatform::IfcBridge::IfcConstructionMaterialResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConstructionProductResource,
		OpenInfraPlatform::IfcBridge::IfcConstructionProductResourceType,
		OpenInfraPlatform::IfcBridge::IfcConstructionProductResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConstructionResource,
		OpenInfraPlatform::IfcBridge::IfcConstructionResourceType,
		OpenInfraPlatform::IfcBridge::IfcContext,
		OpenInfraPlatform::IfcBridge::IfcContextDependentMeasure,
		OpenInfraPlatform::IfcBridge::IfcContextDependentUnit,
		OpenInfraPlatform::IfcBridge::IfcControl,
		OpenInfraPlatform::IfcBridge::IfcController,
		OpenInfraPlatform::IfcBridge::IfcControllerType,
		OpenInfraPlatform::IfcBridge::IfcControllerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcConversionBasedUnit,
		OpenInfraPlatform::IfcBridge::IfcConversionBasedUnitWithOffset,
		OpenInfraPlatform::IfcBridge::IfcCooledBeam,
		OpenInfraPlatform::IfcBridge::IfcCooledBeamType,
		OpenInfraPlatform::IfcBridge::IfcCooledBeamTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCoolingTower,
		OpenInfraPlatform::IfcBridge::IfcCoolingTowerType,
		OpenInfraPlatform::IfcBridge::IfcCoolingTowerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCoordinateOperation,
		OpenInfraPlatform::IfcBridge::IfcCoordinateReferenceSystem,
		OpenInfraPlatform::IfcBridge::IfcCoordinateReferenceSystemSelect,
		OpenInfraPlatform::IfcBridge::IfcCostItem,
		OpenInfraPlatform::IfcBridge::IfcCostItemTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCostSchedule,
		OpenInfraPlatform::IfcBridge::IfcCostScheduleTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCostValue,
		OpenInfraPlatform::IfcBridge::IfcCountMeasure,
		OpenInfraPlatform::IfcBridge::IfcCovering,
		OpenInfraPlatform::IfcBridge::IfcCoveringType,
		OpenInfraPlatform::IfcBridge::IfcCoveringTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCrewResource,
		OpenInfraPlatform::IfcBridge::IfcCrewResourceType,
		OpenInfraPlatform::IfcBridge::IfcCrewResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCsgPrimitive3D,
		OpenInfraPlatform::IfcBridge::IfcCsgSelect,
		OpenInfraPlatform::IfcBridge::IfcCsgSolid,
		OpenInfraPlatform::IfcBridge::IfcCShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcCurrencyRelationship,
		OpenInfraPlatform::IfcBridge::IfcCurtainWall,
		OpenInfraPlatform::IfcBridge::IfcCurtainWallType,
		OpenInfraPlatform::IfcBridge::IfcCurtainWallTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcCurvatureMeasure,
		OpenInfraPlatform::IfcBridge::IfcCurve,
		OpenInfraPlatform::IfcBridge::IfcCurveBoundedPlane,
		OpenInfraPlatform::IfcBridge::IfcCurveBoundedSurface,
		OpenInfraPlatform::IfcBridge::IfcCurveFontOrScaledCurveFontSelect,
		OpenInfraPlatform::IfcBridge::IfcCurveInterpolationEnum,
		OpenInfraPlatform::IfcBridge::IfcCurveOnSurface,
		OpenInfraPlatform::IfcBridge::IfcCurveOrEdgeCurve,
		OpenInfraPlatform::IfcBridge::IfcCurveStyle,
		OpenInfraPlatform::IfcBridge::IfcCurveStyleFont,
		OpenInfraPlatform::IfcBridge::IfcCurveStyleFontAndScaling,
		OpenInfraPlatform::IfcBridge::IfcCurveStyleFontPattern,
		OpenInfraPlatform::IfcBridge::IfcCurveStyleFontSelect,
		OpenInfraPlatform::IfcBridge::IfcCylindricalSurface,
		OpenInfraPlatform::IfcBridge::IfcDamper,
		OpenInfraPlatform::IfcBridge::IfcDamperType,
		OpenInfraPlatform::IfcBridge::IfcDamperTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDataOriginEnum,
		OpenInfraPlatform::IfcBridge::IfcDate,
		OpenInfraPlatform::IfcBridge::IfcDateTime,
		OpenInfraPlatform::IfcBridge::IfcDayInMonthNumber,
		OpenInfraPlatform::IfcBridge::IfcDayInWeekNumber,
		OpenInfraPlatform::IfcBridge::IfcDefinedSymbol,
		OpenInfraPlatform::IfcBridge::IfcDefinedSymbolSelect,
		OpenInfraPlatform::IfcBridge::IfcDefinitionSelect,
		OpenInfraPlatform::IfcBridge::IfcDerivedMeasureValue,
		OpenInfraPlatform::IfcBridge::IfcDerivedProfileDef,
		OpenInfraPlatform::IfcBridge::IfcDerivedUnit,
		OpenInfraPlatform::IfcBridge::IfcDerivedUnitElement,
		OpenInfraPlatform::IfcBridge::IfcDerivedUnitEnum,
		OpenInfraPlatform::IfcBridge::IfcDescriptiveMeasure,
		OpenInfraPlatform::IfcBridge::IfcDimensionalExponents,
		OpenInfraPlatform::IfcBridge::IfcDimensionCount,
		OpenInfraPlatform::IfcBridge::IfcDirection,
		OpenInfraPlatform::IfcBridge::IfcDirectionList,
		OpenInfraPlatform::IfcBridge::IfcDirectionSenseEnum,
		OpenInfraPlatform::IfcBridge::IfcDiscreteAccessory,
		OpenInfraPlatform::IfcBridge::IfcDiscreteAccessoryType,
		OpenInfraPlatform::IfcBridge::IfcDiscreteAccessoryTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDistributionChamberElement,
		OpenInfraPlatform::IfcBridge::IfcDistributionChamberElementType,
		OpenInfraPlatform::IfcBridge::IfcDistributionChamberElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDistributionCircuit,
		OpenInfraPlatform::IfcBridge::IfcDistributionControlElement,
		OpenInfraPlatform::IfcBridge::IfcDistributionControlElementType,
		OpenInfraPlatform::IfcBridge::IfcDistributionElement,
		OpenInfraPlatform::IfcBridge::IfcDistributionElementType,
		OpenInfraPlatform::IfcBridge::IfcDistributionFlowElement,
		OpenInfraPlatform::IfcBridge::IfcDistributionFlowElementType,
		OpenInfraPlatform::IfcBridge::IfcDistributionPort,
		OpenInfraPlatform::IfcBridge::IfcDistributionSystem,
		OpenInfraPlatform::IfcBridge::IfcDistributionSystemEnum,
		OpenInfraPlatform::IfcBridge::IfcDocumentConfidentialityEnum,
		OpenInfraPlatform::IfcBridge::IfcDocumentElectronicFormat,
		OpenInfraPlatform::IfcBridge::IfcDocumentInformation,
		OpenInfraPlatform::IfcBridge::IfcDocumentInformationRelationship,
		OpenInfraPlatform::IfcBridge::IfcDocumentReference,
		OpenInfraPlatform::IfcBridge::IfcDocumentSelect,
		OpenInfraPlatform::IfcBridge::IfcDocumentStatusEnum,
		OpenInfraPlatform::IfcBridge::IfcDoor,
		OpenInfraPlatform::IfcBridge::IfcDoorLiningProperties,
		OpenInfraPlatform::IfcBridge::IfcDoorPanelOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcDoorPanelPositionEnum,
		OpenInfraPlatform::IfcBridge::IfcDoorPanelProperties,
		OpenInfraPlatform::IfcBridge::IfcDoorStandardCase,
		OpenInfraPlatform::IfcBridge::IfcDoorStyle,
		OpenInfraPlatform::IfcBridge::IfcDoorStyleConstructionEnum,
		OpenInfraPlatform::IfcBridge::IfcDoorStyleOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcDoorType,
		OpenInfraPlatform::IfcBridge::IfcDoorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDoorTypeOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcDoseEquivalentMeasure,
		OpenInfraPlatform::IfcBridge::IfcDraughtingPreDefinedColour,
		OpenInfraPlatform::IfcBridge::IfcDraughtingPreDefinedCurveFont,
		OpenInfraPlatform::IfcBridge::IfcDraughtingPreDefinedTextFont,
		OpenInfraPlatform::IfcBridge::IfcDuctFitting,
		OpenInfraPlatform::IfcBridge::IfcDuctFittingType,
		OpenInfraPlatform::IfcBridge::IfcDuctFittingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDuctSegment,
		OpenInfraPlatform::IfcBridge::IfcDuctSegmentType,
		OpenInfraPlatform::IfcBridge::IfcDuctSegmentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDuctSilencer,
		OpenInfraPlatform::IfcBridge::IfcDuctSilencerType,
		OpenInfraPlatform::IfcBridge::IfcDuctSilencerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcDuration,
		OpenInfraPlatform::IfcBridge::IfcDynamicViscosityMeasure,
		OpenInfraPlatform::IfcBridge::IfcEdge,
		OpenInfraPlatform::IfcBridge::IfcEdgeCurve,
		OpenInfraPlatform::IfcBridge::IfcEdgeLoop,
		OpenInfraPlatform::IfcBridge::IfcElectricAppliance,
		OpenInfraPlatform::IfcBridge::IfcElectricApplianceType,
		OpenInfraPlatform::IfcBridge::IfcElectricApplianceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricCapacitanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcElectricChargeMeasure,
		OpenInfraPlatform::IfcBridge::IfcElectricConductanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcElectricCurrentMeasure,
		OpenInfraPlatform::IfcBridge::IfcElectricDistributionBoard,
		OpenInfraPlatform::IfcBridge::IfcElectricDistributionBoardType,
		OpenInfraPlatform::IfcBridge::IfcElectricDistributionBoardTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricFlowStorageDevice,
		OpenInfraPlatform::IfcBridge::IfcElectricFlowStorageDeviceType,
		OpenInfraPlatform::IfcBridge::IfcElectricFlowStorageDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricGenerator,
		OpenInfraPlatform::IfcBridge::IfcElectricGeneratorType,
		OpenInfraPlatform::IfcBridge::IfcElectricGeneratorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricMotor,
		OpenInfraPlatform::IfcBridge::IfcElectricMotorType,
		OpenInfraPlatform::IfcBridge::IfcElectricMotorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricResistanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcElectricTimeControl,
		OpenInfraPlatform::IfcBridge::IfcElectricTimeControlType,
		OpenInfraPlatform::IfcBridge::IfcElectricTimeControlTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElectricVoltageMeasure,
		OpenInfraPlatform::IfcBridge::IfcElement,
		OpenInfraPlatform::IfcBridge::IfcElementarySurface,
		OpenInfraPlatform::IfcBridge::IfcElementAssembly,
		OpenInfraPlatform::IfcBridge::IfcElementAssemblyType,
		OpenInfraPlatform::IfcBridge::IfcElementAssemblyTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcElementComponent,
		OpenInfraPlatform::IfcBridge::IfcElementComponentType,
		OpenInfraPlatform::IfcBridge::IfcElementCompositionEnum,
		OpenInfraPlatform::IfcBridge::IfcElementPart,
		OpenInfraPlatform::IfcBridge::IfcElementQuantity,
		OpenInfraPlatform::IfcBridge::IfcElementType,
		OpenInfraPlatform::IfcBridge::IfcEllipse,
		OpenInfraPlatform::IfcBridge::IfcEllipseProfileDef,
		OpenInfraPlatform::IfcBridge::IfcEnergyConversionDevice,
		OpenInfraPlatform::IfcBridge::IfcEnergyConversionDeviceType,
		OpenInfraPlatform::IfcBridge::IfcEnergyMeasure,
		OpenInfraPlatform::IfcBridge::IfcEngine,
		OpenInfraPlatform::IfcBridge::IfcEngineType,
		OpenInfraPlatform::IfcBridge::IfcEngineTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcEvaporativeCooler,
		OpenInfraPlatform::IfcBridge::IfcEvaporativeCoolerType,
		OpenInfraPlatform::IfcBridge::IfcEvaporativeCoolerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcEvaporator,
		OpenInfraPlatform::IfcBridge::IfcEvaporatorType,
		OpenInfraPlatform::IfcBridge::IfcEvaporatorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcEvent,
		OpenInfraPlatform::IfcBridge::IfcEventTime,
		OpenInfraPlatform::IfcBridge::IfcEventTriggerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcEventType,
		OpenInfraPlatform::IfcBridge::IfcEventTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcExtendedProperties,
		OpenInfraPlatform::IfcBridge::IfcExternalInformation,
		OpenInfraPlatform::IfcBridge::IfcExternallyDefinedHatchStyle,
		OpenInfraPlatform::IfcBridge::IfcExternallyDefinedSurfaceStyle,
		OpenInfraPlatform::IfcBridge::IfcExternallyDefinedSymbol,
		OpenInfraPlatform::IfcBridge::IfcExternallyDefinedTextFont,
		OpenInfraPlatform::IfcBridge::IfcExternalReference,
		OpenInfraPlatform::IfcBridge::IfcExternalReferenceRelationship,
		OpenInfraPlatform::IfcBridge::IfcExternalSpatialElement,
		OpenInfraPlatform::IfcBridge::IfcExternalSpatialElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcExternalSpatialStructureElement,
		OpenInfraPlatform::IfcBridge::IfcExtrudedAreaSolid,
		OpenInfraPlatform::IfcBridge::IfcExtrudedAreaSolidTapered,
		OpenInfraPlatform::IfcBridge::IfcFace,
		OpenInfraPlatform::IfcBridge::IfcFaceBasedSurfaceModel,
		OpenInfraPlatform::IfcBridge::IfcFaceBound,
		OpenInfraPlatform::IfcBridge::IfcFaceOuterBound,
		OpenInfraPlatform::IfcBridge::IfcFaceSurface,
		OpenInfraPlatform::IfcBridge::IfcFacetedBrep,
		OpenInfraPlatform::IfcBridge::IfcFacetedBrepWithVoids,
		OpenInfraPlatform::IfcBridge::IfcFailureConnectionCondition,
		OpenInfraPlatform::IfcBridge::IfcFan,
		OpenInfraPlatform::IfcBridge::IfcFanType,
		OpenInfraPlatform::IfcBridge::IfcFanTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFastener,
		OpenInfraPlatform::IfcBridge::IfcFastenerType,
		OpenInfraPlatform::IfcBridge::IfcFastenerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFeatureElement,
		OpenInfraPlatform::IfcBridge::IfcFeatureElementAddition,
		OpenInfraPlatform::IfcBridge::IfcFeatureElementSubtraction,
		OpenInfraPlatform::IfcBridge::IfcFillAreaStyle,
		OpenInfraPlatform::IfcBridge::IfcFillAreaStyleHatching,
		OpenInfraPlatform::IfcBridge::IfcFillAreaStyleTiles,
		OpenInfraPlatform::IfcBridge::IfcFillAreaStyleTileShapeSelect,
		OpenInfraPlatform::IfcBridge::IfcFillAreaStyleTileSymbolWithStyle,
		OpenInfraPlatform::IfcBridge::IfcFillStyleSelect,
		OpenInfraPlatform::IfcBridge::IfcFilter,
		OpenInfraPlatform::IfcBridge::IfcFilterType,
		OpenInfraPlatform::IfcBridge::IfcFilterTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFireSuppressionTerminal,
		OpenInfraPlatform::IfcBridge::IfcFireSuppressionTerminalType,
		OpenInfraPlatform::IfcBridge::IfcFireSuppressionTerminalTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFixedReferenceSweptAreaSolid,
		OpenInfraPlatform::IfcBridge::IfcFlowController,
		OpenInfraPlatform::IfcBridge::IfcFlowControllerType,
		OpenInfraPlatform::IfcBridge::IfcFlowDirectionEnum,
		OpenInfraPlatform::IfcBridge::IfcFlowFitting,
		OpenInfraPlatform::IfcBridge::IfcFlowFittingType,
		OpenInfraPlatform::IfcBridge::IfcFlowInstrument,
		OpenInfraPlatform::IfcBridge::IfcFlowInstrumentType,
		OpenInfraPlatform::IfcBridge::IfcFlowInstrumentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFlowMeter,
		OpenInfraPlatform::IfcBridge::IfcFlowMeterType,
		OpenInfraPlatform::IfcBridge::IfcFlowMeterTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcFlowMovingDevice,
		OpenInfraPlatform::IfcBridge::IfcFlowMovingDeviceType,
		OpenInfraPlatform::IfcBridge::IfcFlowSegment,
		OpenInfraPlatform::IfcBridge::IfcFlowSegmentType,
		OpenInfraPlatform::IfcBridge::IfcFlowStorageDevice,
		OpenInfraPlatform::IfcBridge::IfcFlowStorageDeviceType,
		OpenInfraPlatform::IfcBridge::IfcFlowTerminal,
		OpenInfraPlatform::IfcBridge::IfcFlowTerminalType,
		OpenInfraPlatform::IfcBridge::IfcFlowTreatmentDevice,
		OpenInfraPlatform::IfcBridge::IfcFlowTreatmentDeviceType,
		OpenInfraPlatform::IfcBridge::IfcFontStyle,
		OpenInfraPlatform::IfcBridge::IfcFontVariant,
		OpenInfraPlatform::IfcBridge::IfcFontWeight,
		OpenInfraPlatform::IfcBridge::IfcFooting,
		OpenInfraPlatform::IfcBridge::IfcFootingType,
		OpenInfraPlatform::IfcBridge::IfcFootingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcForceMeasure,
		OpenInfraPlatform::IfcBridge::IfcFrequencyMeasure,
		OpenInfraPlatform::IfcBridge::IfcFurnishingElement,
		OpenInfraPlatform::IfcBridge::IfcFurnishingElementType,
		OpenInfraPlatform::IfcBridge::IfcFurniture,
		OpenInfraPlatform::IfcBridge::IfcFurnitureType,
		OpenInfraPlatform::IfcBridge::IfcFurnitureTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcGeographicElement,
		OpenInfraPlatform::IfcBridge::IfcGeographicElementType,
		OpenInfraPlatform::IfcBridge::IfcGeographicElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcGeometricCurveSet,
		OpenInfraPlatform::IfcBridge::IfcGeometricProjectionEnum,
		OpenInfraPlatform::IfcBridge::IfcGeometricRepresentationContext,
		OpenInfraPlatform::IfcBridge::IfcGeometricRepresentationItem,
		OpenInfraPlatform::IfcBridge::IfcGeometricRepresentationSubContext,
		OpenInfraPlatform::IfcBridge::IfcGeometricSet,
		OpenInfraPlatform::IfcBridge::IfcGeometricSetSelect,
		OpenInfraPlatform::IfcBridge::IfcGloballyUniqueId,
		OpenInfraPlatform::IfcBridge::IfcGlobalOrLocalEnum,
		OpenInfraPlatform::IfcBridge::IfcGrid,
		OpenInfraPlatform::IfcBridge::IfcGridAxis,
		OpenInfraPlatform::IfcBridge::IfcGridPlacement,
		OpenInfraPlatform::IfcBridge::IfcGridPlacementDirectionSelect,
		OpenInfraPlatform::IfcBridge::IfcGridTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcGroup,
		OpenInfraPlatform::IfcBridge::IfcHalfSpaceSolid,
		OpenInfraPlatform::IfcBridge::IfcHatchLineDistanceSelect,
		OpenInfraPlatform::IfcBridge::IfcHeatExchanger,
		OpenInfraPlatform::IfcBridge::IfcHeatExchangerType,
		OpenInfraPlatform::IfcBridge::IfcHeatExchangerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcHeatFluxDensityMeasure,
		OpenInfraPlatform::IfcBridge::IfcHeatingValueMeasure,
		OpenInfraPlatform::IfcBridge::IfcHumidifier,
		OpenInfraPlatform::IfcBridge::IfcHumidifierType,
		OpenInfraPlatform::IfcBridge::IfcHumidifierTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcIdentifier,
		OpenInfraPlatform::IfcBridge::IfcIlluminanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcImageTexture,
		OpenInfraPlatform::IfcBridge::IfcIndexedColourMap,
		OpenInfraPlatform::IfcBridge::IfcIndexedTextureMap,
		OpenInfraPlatform::IfcBridge::IfcIndexedTriangleTextureMap,
		OpenInfraPlatform::IfcBridge::IfcInductanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcInteger,
		OpenInfraPlatform::IfcBridge::IfcIntegerCountRateMeasure,
		OpenInfraPlatform::IfcBridge::IfcInterceptor,
		OpenInfraPlatform::IfcBridge::IfcInterceptorType,
		OpenInfraPlatform::IfcBridge::IfcInterceptorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcInternalOrExternalEnum,
		OpenInfraPlatform::IfcBridge::IfcInventory,
		OpenInfraPlatform::IfcBridge::IfcInventoryTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcIonConcentrationMeasure,
		OpenInfraPlatform::IfcBridge::IfcIrregularTimeSeries,
		OpenInfraPlatform::IfcBridge::IfcIrregularTimeSeriesValue,
		OpenInfraPlatform::IfcBridge::IfcIShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcIsothermalMoistureCapacityMeasure,
		OpenInfraPlatform::IfcBridge::IfcJunctionBox,
		OpenInfraPlatform::IfcBridge::IfcJunctionBoxType,
		OpenInfraPlatform::IfcBridge::IfcJunctionBoxTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcKinematicViscosityMeasure,
		OpenInfraPlatform::IfcBridge::IfcKnotType,
		OpenInfraPlatform::IfcBridge::IfcLabel,
		OpenInfraPlatform::IfcBridge::IfcLaborResource,
		OpenInfraPlatform::IfcBridge::IfcLaborResourceType,
		OpenInfraPlatform::IfcBridge::IfcLaborResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcLagTime,
		OpenInfraPlatform::IfcBridge::IfcLamp,
		OpenInfraPlatform::IfcBridge::IfcLampType,
		OpenInfraPlatform::IfcBridge::IfcLampTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcLanguageId,
		OpenInfraPlatform::IfcBridge::IfcLayeredItem,
		OpenInfraPlatform::IfcBridge::IfcLayerSetDirectionEnum,
		OpenInfraPlatform::IfcBridge::IfcLengthMeasure,
		OpenInfraPlatform::IfcBridge::IfcLibraryInformation,
		OpenInfraPlatform::IfcBridge::IfcLibraryReference,
		OpenInfraPlatform::IfcBridge::IfcLibrarySelect,
		OpenInfraPlatform::IfcBridge::IfcLightDistributionCurveEnum,
		OpenInfraPlatform::IfcBridge::IfcLightDistributionData,
		OpenInfraPlatform::IfcBridge::IfcLightDistributionDataSourceSelect,
		OpenInfraPlatform::IfcBridge::IfcLightEmissionSourceEnum,
		OpenInfraPlatform::IfcBridge::IfcLightFixture,
		OpenInfraPlatform::IfcBridge::IfcLightFixtureType,
		OpenInfraPlatform::IfcBridge::IfcLightFixtureTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcLightIntensityDistribution,
		OpenInfraPlatform::IfcBridge::IfcLightSource,
		OpenInfraPlatform::IfcBridge::IfcLightSourceAmbient,
		OpenInfraPlatform::IfcBridge::IfcLightSourceDirectional,
		OpenInfraPlatform::IfcBridge::IfcLightSourceGoniometric,
		OpenInfraPlatform::IfcBridge::IfcLightSourcePositional,
		OpenInfraPlatform::IfcBridge::IfcLightSourceSpot,
		OpenInfraPlatform::IfcBridge::IfcLine,
		OpenInfraPlatform::IfcBridge::IfcLinearForceMeasure,
		OpenInfraPlatform::IfcBridge::IfcLinearMomentMeasure,
		OpenInfraPlatform::IfcBridge::IfcLinearStiffnessMeasure,
		OpenInfraPlatform::IfcBridge::IfcLinearVelocityMeasure,
		OpenInfraPlatform::IfcBridge::IfcLoadGroupTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcLocalPlacement,
		OpenInfraPlatform::IfcBridge::IfcLogical,
		OpenInfraPlatform::IfcBridge::IfcLogicalOperatorEnum,
		OpenInfraPlatform::IfcBridge::IfcLoop,
		OpenInfraPlatform::IfcBridge::IfcLShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcLuminousFluxMeasure,
		OpenInfraPlatform::IfcBridge::IfcLuminousIntensityDistributionMeasure,
		OpenInfraPlatform::IfcBridge::IfcLuminousIntensityMeasure,
		OpenInfraPlatform::IfcBridge::IfcMagneticFluxDensityMeasure,
		OpenInfraPlatform::IfcBridge::IfcMagneticFluxMeasure,
		OpenInfraPlatform::IfcBridge::IfcManifoldSolidBrep,
		OpenInfraPlatform::IfcBridge::IfcMapConversion,
		OpenInfraPlatform::IfcBridge::IfcMappedItem,
		OpenInfraPlatform::IfcBridge::IfcMassDensityMeasure,
		OpenInfraPlatform::IfcBridge::IfcMassFlowRateMeasure,
		OpenInfraPlatform::IfcBridge::IfcMassMeasure,
		OpenInfraPlatform::IfcBridge::IfcMassPerLengthMeasure,
		OpenInfraPlatform::IfcBridge::IfcMaterial,
		OpenInfraPlatform::IfcBridge::IfcMaterialClassificationRelationship,
		OpenInfraPlatform::IfcBridge::IfcMaterialConstituent,
		OpenInfraPlatform::IfcBridge::IfcMaterialConstituentSet,
		OpenInfraPlatform::IfcBridge::IfcMaterialDefinition,
		OpenInfraPlatform::IfcBridge::IfcMaterialDefinitionRepresentation,
		OpenInfraPlatform::IfcBridge::IfcMaterialLayer,
		OpenInfraPlatform::IfcBridge::IfcMaterialLayerSet,
		OpenInfraPlatform::IfcBridge::IfcMaterialLayerSetUsage,
		OpenInfraPlatform::IfcBridge::IfcMaterialLayerWithOffsets,
		OpenInfraPlatform::IfcBridge::IfcMaterialList,
		OpenInfraPlatform::IfcBridge::IfcMaterialProfile,
		OpenInfraPlatform::IfcBridge::IfcMaterialProfileSet,
		OpenInfraPlatform::IfcBridge::IfcMaterialProfileSetUsage,
		OpenInfraPlatform::IfcBridge::IfcMaterialProfileSetUsageTapering,
		OpenInfraPlatform::IfcBridge::IfcMaterialProfileWithOffsets,
		OpenInfraPlatform::IfcBridge::IfcMaterialProperties,
		OpenInfraPlatform::IfcBridge::IfcMaterialRelationship,
		OpenInfraPlatform::IfcBridge::IfcMaterialSelect,
		OpenInfraPlatform::IfcBridge::IfcMaterialUsageDefinition,
		OpenInfraPlatform::IfcBridge::IfcMeasureValue,
		OpenInfraPlatform::IfcBridge::IfcMeasureWithUnit,
		OpenInfraPlatform::IfcBridge::IfcMechanicalFastener,
		OpenInfraPlatform::IfcBridge::IfcMechanicalFastenerType,
		OpenInfraPlatform::IfcBridge::IfcMechanicalFastenerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcMedicalDevice,
		OpenInfraPlatform::IfcBridge::IfcMedicalDeviceType,
		OpenInfraPlatform::IfcBridge::IfcMedicalDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcMember,
		OpenInfraPlatform::IfcBridge::IfcMemberStandardCase,
		OpenInfraPlatform::IfcBridge::IfcMemberType,
		OpenInfraPlatform::IfcBridge::IfcMemberTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcMetric,
		OpenInfraPlatform::IfcBridge::IfcMetricValueSelect,
		OpenInfraPlatform::IfcBridge::IfcMirroredProfileDef,
		OpenInfraPlatform::IfcBridge::IfcModulusOfElasticityMeasure,
		OpenInfraPlatform::IfcBridge::IfcModulusOfLinearSubgradeReactionMeasure,
		OpenInfraPlatform::IfcBridge::IfcModulusOfRotationalSubgradeReactionMeasure,
		OpenInfraPlatform::IfcBridge::IfcModulusOfRotationalSubgradeReactionSelect,
		OpenInfraPlatform::IfcBridge::IfcModulusOfSubgradeReactionMeasure,
		OpenInfraPlatform::IfcBridge::IfcModulusOfSubgradeReactionSelect,
		OpenInfraPlatform::IfcBridge::IfcModulusOfTranslationalSubgradeReactionSelect,
		OpenInfraPlatform::IfcBridge::IfcMoistureDiffusivityMeasure,
		OpenInfraPlatform::IfcBridge::IfcMolecularWeightMeasure,
		OpenInfraPlatform::IfcBridge::IfcMomentOfInertiaMeasure,
		OpenInfraPlatform::IfcBridge::IfcMonetaryMeasure,
		OpenInfraPlatform::IfcBridge::IfcMonetaryUnit,
		OpenInfraPlatform::IfcBridge::IfcMonthInYearNumber,
		OpenInfraPlatform::IfcBridge::IfcMotorConnection,
		OpenInfraPlatform::IfcBridge::IfcMotorConnectionType,
		OpenInfraPlatform::IfcBridge::IfcMotorConnectionTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcNamedUnit,
		OpenInfraPlatform::IfcBridge::IfcNonNegativeLengthMeasure,
		OpenInfraPlatform::IfcBridge::IfcNormalisedRatioMeasure,
		OpenInfraPlatform::IfcBridge::IfcNullStyle,
		OpenInfraPlatform::IfcBridge::IfcNumericMeasure,
		OpenInfraPlatform::IfcBridge::IfcObject,
		OpenInfraPlatform::IfcBridge::IfcObjectDefinition,
		OpenInfraPlatform::IfcBridge::IfcObjective,
		OpenInfraPlatform::IfcBridge::IfcObjectiveEnum,
		OpenInfraPlatform::IfcBridge::IfcObjectPlacement,
		OpenInfraPlatform::IfcBridge::IfcObjectReferenceSelect,
		OpenInfraPlatform::IfcBridge::IfcObjectTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcOccupant,
		OpenInfraPlatform::IfcBridge::IfcOccupantTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcOffsetCurve2D,
		OpenInfraPlatform::IfcBridge::IfcOffsetCurve3D,
		OpenInfraPlatform::IfcBridge::IfcOneDirectionRepeatFactor,
		OpenInfraPlatform::IfcBridge::IfcOpeningElement,
		OpenInfraPlatform::IfcBridge::IfcOpeningElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcOpeningStandardCase,
		OpenInfraPlatform::IfcBridge::IfcOpenShell,
		OpenInfraPlatform::IfcBridge::IfcOrganization,
		OpenInfraPlatform::IfcBridge::IfcOrganizationRelationship,
		OpenInfraPlatform::IfcBridge::IfcOrientedEdge,
		OpenInfraPlatform::IfcBridge::IfcOuterBoundaryCurve,
		OpenInfraPlatform::IfcBridge::IfcOutlet,
		OpenInfraPlatform::IfcBridge::IfcOutletType,
		OpenInfraPlatform::IfcBridge::IfcOutletTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcOwnerHistory,
		OpenInfraPlatform::IfcBridge::IfcParameterizedProfileDef,
		OpenInfraPlatform::IfcBridge::IfcParameterValue,
		OpenInfraPlatform::IfcBridge::IfcPath,
		OpenInfraPlatform::IfcBridge::IfcPcurve,
		OpenInfraPlatform::IfcBridge::IfcPerformanceHistory,
		OpenInfraPlatform::IfcBridge::IfcPerformanceHistoryTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPermeableCoveringOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcPermeableCoveringProperties,
		OpenInfraPlatform::IfcBridge::IfcPermit,
		OpenInfraPlatform::IfcBridge::IfcPermitTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPerson,
		OpenInfraPlatform::IfcBridge::IfcPersonAndOrganization,
		OpenInfraPlatform::IfcBridge::IfcPHMeasure,
		OpenInfraPlatform::IfcBridge::IfcPhysicalComplexQuantity,
		OpenInfraPlatform::IfcBridge::IfcPhysicalOrVirtualEnum,
		OpenInfraPlatform::IfcBridge::IfcPhysicalQuantity,
		OpenInfraPlatform::IfcBridge::IfcPhysicalSimpleQuantity,
		OpenInfraPlatform::IfcBridge::IfcPile,
		OpenInfraPlatform::IfcBridge::IfcPileConstructionEnum,
		OpenInfraPlatform::IfcBridge::IfcPileType,
		OpenInfraPlatform::IfcBridge::IfcPileTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPipeFitting,
		OpenInfraPlatform::IfcBridge::IfcPipeFittingType,
		OpenInfraPlatform::IfcBridge::IfcPipeFittingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPipeSegment,
		OpenInfraPlatform::IfcBridge::IfcPipeSegmentType,
		OpenInfraPlatform::IfcBridge::IfcPipeSegmentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPixelTexture,
		OpenInfraPlatform::IfcBridge::IfcPlacement,
		OpenInfraPlatform::IfcBridge::IfcPlanarBox,
		OpenInfraPlatform::IfcBridge::IfcPlanarExtent,
		OpenInfraPlatform::IfcBridge::IfcPlanarForceMeasure,
		OpenInfraPlatform::IfcBridge::IfcPlane,
		OpenInfraPlatform::IfcBridge::IfcPlaneAngleMeasure,
		OpenInfraPlatform::IfcBridge::IfcPlate,
		OpenInfraPlatform::IfcBridge::IfcPlateStandardCase,
		OpenInfraPlatform::IfcBridge::IfcPlateType,
		OpenInfraPlatform::IfcBridge::IfcPlateTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPoint,
		OpenInfraPlatform::IfcBridge::IfcPointOnCurve,
		OpenInfraPlatform::IfcBridge::IfcPointOnSurface,
		OpenInfraPlatform::IfcBridge::IfcPointOrVertexPoint,
		OpenInfraPlatform::IfcBridge::IfcPolygonalBoundedHalfSpace,
		OpenInfraPlatform::IfcBridge::IfcPolyline,
		OpenInfraPlatform::IfcBridge::IfcPolyLoop,
		OpenInfraPlatform::IfcBridge::IfcPort,
		OpenInfraPlatform::IfcBridge::IfcPositiveLengthMeasure,
		OpenInfraPlatform::IfcBridge::IfcPositivePlaneAngleMeasure,
		OpenInfraPlatform::IfcBridge::IfcPositiveRatioMeasure,
		OpenInfraPlatform::IfcBridge::IfcPostalAddress,
		OpenInfraPlatform::IfcBridge::IfcPowerMeasure,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedColour,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedCurveFont,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedItem,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedProperties,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedPropertySet,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedSymbol,
		OpenInfraPlatform::IfcBridge::IfcPreDefinedTextFont,
		OpenInfraPlatform::IfcBridge::IfcPresentableText,
		OpenInfraPlatform::IfcBridge::IfcPresentationItem,
		OpenInfraPlatform::IfcBridge::IfcPresentationLayerAssignment,
		OpenInfraPlatform::IfcBridge::IfcPresentationLayerWithStyle,
		OpenInfraPlatform::IfcBridge::IfcPresentationStyle,
		OpenInfraPlatform::IfcBridge::IfcPresentationStyleAssignment,
		OpenInfraPlatform::IfcBridge::IfcPresentationStyleSelect,
		OpenInfraPlatform::IfcBridge::IfcPressureMeasure,
		OpenInfraPlatform::IfcBridge::IfcProcedure,
		OpenInfraPlatform::IfcBridge::IfcProcedureType,
		OpenInfraPlatform::IfcBridge::IfcProcedureTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProcess,
		OpenInfraPlatform::IfcBridge::IfcProcessSelect,
		OpenInfraPlatform::IfcBridge::IfcProduct,
		OpenInfraPlatform::IfcBridge::IfcProductDefinitionShape,
		OpenInfraPlatform::IfcBridge::IfcProductRepresentation,
		OpenInfraPlatform::IfcBridge::IfcProductSelect,
		OpenInfraPlatform::IfcBridge::IfcProfileDef,
		OpenInfraPlatform::IfcBridge::IfcProfileProperties,
		OpenInfraPlatform::IfcBridge::IfcProfileTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProject,
		OpenInfraPlatform::IfcBridge::IfcProjectedCRS,
		OpenInfraPlatform::IfcBridge::IfcProjectedOrTrueLengthEnum,
		OpenInfraPlatform::IfcBridge::IfcProjectionElement,
		OpenInfraPlatform::IfcBridge::IfcProjectionElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProjectLibrary,
		OpenInfraPlatform::IfcBridge::IfcProjectOrder,
		OpenInfraPlatform::IfcBridge::IfcProjectOrderTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProperty,
		OpenInfraPlatform::IfcBridge::IfcPropertyAbstraction,
		OpenInfraPlatform::IfcBridge::IfcPropertyBoundedValue,
		OpenInfraPlatform::IfcBridge::IfcPropertyDefinition,
		OpenInfraPlatform::IfcBridge::IfcPropertyDependencyRelationship,
		OpenInfraPlatform::IfcBridge::IfcPropertyEnumeratedValue,
		OpenInfraPlatform::IfcBridge::IfcPropertyEnumeration,
		OpenInfraPlatform::IfcBridge::IfcPropertyListValue,
		OpenInfraPlatform::IfcBridge::IfcPropertyReferenceValue,
		OpenInfraPlatform::IfcBridge::IfcPropertySet,
		OpenInfraPlatform::IfcBridge::IfcPropertySetDefinition,
		OpenInfraPlatform::IfcBridge::IfcPropertySetTemplate,
		OpenInfraPlatform::IfcBridge::IfcPropertySetTemplateTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcPropertySingleValue,
		OpenInfraPlatform::IfcBridge::IfcPropertyTableValue,
		OpenInfraPlatform::IfcBridge::IfcPropertyTemplate,
		OpenInfraPlatform::IfcBridge::IfcPropertyTemplateDefinition,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDevice,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDeviceTrippingUnit,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDeviceTrippingUnitType,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDeviceTrippingUnitTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDeviceType,
		OpenInfraPlatform::IfcBridge::IfcProtectiveDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcProxy,
		OpenInfraPlatform::IfcBridge::IfcPump,
		OpenInfraPlatform::IfcBridge::IfcPumpType,
		OpenInfraPlatform::IfcBridge::IfcPumpTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcQuantityArea,
		OpenInfraPlatform::IfcBridge::IfcQuantityCount,
		OpenInfraPlatform::IfcBridge::IfcQuantityLength,
		OpenInfraPlatform::IfcBridge::IfcQuantitySet,
		OpenInfraPlatform::IfcBridge::IfcQuantityTime,
		OpenInfraPlatform::IfcBridge::IfcQuantityVolume,
		OpenInfraPlatform::IfcBridge::IfcQuantityWeight,
		OpenInfraPlatform::IfcBridge::IfcRadioActivityMeasure,
		OpenInfraPlatform::IfcBridge::IfcRailing,
		OpenInfraPlatform::IfcBridge::IfcRailingType,
		OpenInfraPlatform::IfcBridge::IfcRailingTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcRamp,
		OpenInfraPlatform::IfcBridge::IfcRampFlight,
		OpenInfraPlatform::IfcBridge::IfcRampFlightType,
		OpenInfraPlatform::IfcBridge::IfcRampFlightTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcRampType,
		OpenInfraPlatform::IfcBridge::IfcRampTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcRatioMeasure,
		OpenInfraPlatform::IfcBridge::IfcRationalBSplineCurveWithKnots,
		OpenInfraPlatform::IfcBridge::IfcRationalBSplineSurfaceWithKnots,
		OpenInfraPlatform::IfcBridge::IfcReal,
		OpenInfraPlatform::IfcBridge::IfcRectangleHollowProfileDef,
		OpenInfraPlatform::IfcBridge::IfcRectangleProfileDef,
		OpenInfraPlatform::IfcBridge::IfcRectangularPyramid,
		OpenInfraPlatform::IfcBridge::IfcRectangularTrimmedSurface,
		OpenInfraPlatform::IfcBridge::IfcRecurrencePattern,
		OpenInfraPlatform::IfcBridge::IfcRecurrenceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcReferenceCurve,
		OpenInfraPlatform::IfcBridge::IfcReferenceCurve3D,
		OpenInfraPlatform::IfcBridge::IfcReferenceCurveAlignment2D,
		OpenInfraPlatform::IfcBridge::IfcReferenceCurvePlacement,
		OpenInfraPlatform::IfcBridge::IfcReferenceCurvePlacementSystem,
		OpenInfraPlatform::IfcBridge::IfcReferencedSectionedSpine,
		OpenInfraPlatform::IfcBridge::IfcReferenceElement,
		OpenInfraPlatform::IfcBridge::IfcReferencePlacement,
		OpenInfraPlatform::IfcBridge::IfcReflectanceMethodEnum,
		OpenInfraPlatform::IfcBridge::IfcRegularTimeSeries,
		OpenInfraPlatform::IfcBridge::IfcReinforcementBarProperties,
		OpenInfraPlatform::IfcBridge::IfcReinforcementDefinitionProperties,
		OpenInfraPlatform::IfcBridge::IfcReinforcingBar,
		OpenInfraPlatform::IfcBridge::IfcReinforcingBarRoleEnum,
		OpenInfraPlatform::IfcBridge::IfcReinforcingBarSurfaceEnum,
		OpenInfraPlatform::IfcBridge::IfcReinforcingBarType,
		OpenInfraPlatform::IfcBridge::IfcReinforcingBarTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcReinforcingElement,
		OpenInfraPlatform::IfcBridge::IfcReinforcingElementType,
		OpenInfraPlatform::IfcBridge::IfcReinforcingMesh,
		OpenInfraPlatform::IfcBridge::IfcReinforcingMeshType,
		OpenInfraPlatform::IfcBridge::IfcReinforcingMeshTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcRelAggregates,
		OpenInfraPlatform::IfcBridge::IfcRelAssigns,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToActor,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToControl,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToGroup,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToGroupByFactor,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToProcess,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToProduct,
		OpenInfraPlatform::IfcBridge::IfcRelAssignsToResource,
		OpenInfraPlatform::IfcBridge::IfcRelAssociates,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesApproval,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesClassification,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesConstraint,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesDocument,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesLibrary,
		OpenInfraPlatform::IfcBridge::IfcRelAssociatesMaterial,
		OpenInfraPlatform::IfcBridge::IfcRelationship,
		OpenInfraPlatform::IfcBridge::IfcRelConnects,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsElements,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsPathElements,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsPorts,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsPortToElement,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsStructuralActivity,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsStructuralMember,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsWithEccentricity,
		OpenInfraPlatform::IfcBridge::IfcRelConnectsWithRealizingElements,
		OpenInfraPlatform::IfcBridge::IfcRelContainedInSpatialStructure,
		OpenInfraPlatform::IfcBridge::IfcRelCoversBldgElements,
		OpenInfraPlatform::IfcBridge::IfcRelCoversSpaces,
		OpenInfraPlatform::IfcBridge::IfcRelDeclares,
		OpenInfraPlatform::IfcBridge::IfcRelDecomposes,
		OpenInfraPlatform::IfcBridge::IfcRelDefines,
		OpenInfraPlatform::IfcBridge::IfcRelDefinesByObject,
		OpenInfraPlatform::IfcBridge::IfcRelDefinesByProperties,
		OpenInfraPlatform::IfcBridge::IfcRelDefinesByTemplate,
		OpenInfraPlatform::IfcBridge::IfcRelDefinesByType,
		OpenInfraPlatform::IfcBridge::IfcRelFillsElement,
		OpenInfraPlatform::IfcBridge::IfcRelFlowControlElements,
		OpenInfraPlatform::IfcBridge::IfcRelInterferesElements,
		OpenInfraPlatform::IfcBridge::IfcRelNests,
		OpenInfraPlatform::IfcBridge::IfcRelProjectsElement,
		OpenInfraPlatform::IfcBridge::IfcRelReferencedInSpatialStructure,
		OpenInfraPlatform::IfcBridge::IfcRelSequence,
		OpenInfraPlatform::IfcBridge::IfcRelServicesBuildings,
		OpenInfraPlatform::IfcBridge::IfcRelSpaceBoundary,
		OpenInfraPlatform::IfcBridge::IfcRelSpaceBoundary1stLevel,
		OpenInfraPlatform::IfcBridge::IfcRelSpaceBoundary2ndLevel,
		OpenInfraPlatform::IfcBridge::IfcRelVoidsElement,
		OpenInfraPlatform::IfcBridge::IfcReparametrisedCompositeCurveSegment,
		OpenInfraPlatform::IfcBridge::IfcRepresentation,
		OpenInfraPlatform::IfcBridge::IfcRepresentationContext,
		OpenInfraPlatform::IfcBridge::IfcRepresentationItem,
		OpenInfraPlatform::IfcBridge::IfcRepresentationMap,
		OpenInfraPlatform::IfcBridge::IfcResource,
		OpenInfraPlatform::IfcBridge::IfcResourceApprovalRelationship,
		OpenInfraPlatform::IfcBridge::IfcResourceConstraintRelationship,
		OpenInfraPlatform::IfcBridge::IfcResourceConsumptionEnum,
		OpenInfraPlatform::IfcBridge::IfcResourceCost,
		OpenInfraPlatform::IfcBridge::IfcResourceLevelRelationship,
		OpenInfraPlatform::IfcBridge::IfcResourceObjectSelect,
		OpenInfraPlatform::IfcBridge::IfcResourceSelect,
		OpenInfraPlatform::IfcBridge::IfcResourceTime,
		OpenInfraPlatform::IfcBridge::IfcRevolvedAreaSolid,
		OpenInfraPlatform::IfcBridge::IfcRevolvedAreaSolidTapered,
		OpenInfraPlatform::IfcBridge::IfcRightCircularCone,
		OpenInfraPlatform::IfcBridge::IfcRightCircularCylinder,
		OpenInfraPlatform::IfcBridge::IfcRoleEnum,
		OpenInfraPlatform::IfcBridge::IfcRoof,
		OpenInfraPlatform::IfcBridge::IfcRoofType,
		OpenInfraPlatform::IfcBridge::IfcRoofTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcRoot,
		OpenInfraPlatform::IfcBridge::IfcRotationalFrequencyMeasure,
		OpenInfraPlatform::IfcBridge::IfcRotationalMassMeasure,
		OpenInfraPlatform::IfcBridge::IfcRotationalStiffnessMeasure,
		OpenInfraPlatform::IfcBridge::IfcRotationalStiffnessSelect,
		OpenInfraPlatform::IfcBridge::IfcRoundedRectangleProfileDef,
		OpenInfraPlatform::IfcBridge::IfcSanitaryTerminal,
		OpenInfraPlatform::IfcBridge::IfcSanitaryTerminalType,
		OpenInfraPlatform::IfcBridge::IfcSanitaryTerminalTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSchedulingTime,
		OpenInfraPlatform::IfcBridge::IfcSectionalAreaIntegralMeasure,
		OpenInfraPlatform::IfcBridge::IfcSectionedSpine,
		OpenInfraPlatform::IfcBridge::IfcSectionModulusMeasure,
		OpenInfraPlatform::IfcBridge::IfcSectionProperties,
		OpenInfraPlatform::IfcBridge::IfcSectionReinforcementProperties,
		OpenInfraPlatform::IfcBridge::IfcSectionTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSensor,
		OpenInfraPlatform::IfcBridge::IfcSensorType,
		OpenInfraPlatform::IfcBridge::IfcSensorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSequenceEnum,
		OpenInfraPlatform::IfcBridge::IfcShadingDevice,
		OpenInfraPlatform::IfcBridge::IfcShadingDeviceType,
		OpenInfraPlatform::IfcBridge::IfcShadingDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcShapeAspect,
		OpenInfraPlatform::IfcBridge::IfcShapeModel,
		OpenInfraPlatform::IfcBridge::IfcShapeRepresentation,
		OpenInfraPlatform::IfcBridge::IfcShearModulusMeasure,
		OpenInfraPlatform::IfcBridge::IfcShell,
		OpenInfraPlatform::IfcBridge::IfcShellBasedSurfaceModel,
		OpenInfraPlatform::IfcBridge::IfcSimpleProperty,
		OpenInfraPlatform::IfcBridge::IfcSimplePropertyTemplate,
		OpenInfraPlatform::IfcBridge::IfcSimplePropertyTemplateTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSimpleValue,
		OpenInfraPlatform::IfcBridge::IfcSIPrefix,
		OpenInfraPlatform::IfcBridge::IfcSite,
		OpenInfraPlatform::IfcBridge::IfcSIUnit,
		OpenInfraPlatform::IfcBridge::IfcSIUnitName,
		OpenInfraPlatform::IfcBridge::IfcSizeSelect,
		OpenInfraPlatform::IfcBridge::IfcSlab,
		OpenInfraPlatform::IfcBridge::IfcSlabElementedCase,
		OpenInfraPlatform::IfcBridge::IfcSlabStandardCase,
		OpenInfraPlatform::IfcBridge::IfcSlabType,
		OpenInfraPlatform::IfcBridge::IfcSlabTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSlippageConnectionCondition,
		OpenInfraPlatform::IfcBridge::IfcSolarDevice,
		OpenInfraPlatform::IfcBridge::IfcSolarDeviceType,
		OpenInfraPlatform::IfcBridge::IfcSolarDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSolidAngleMeasure,
		OpenInfraPlatform::IfcBridge::IfcSolidModel,
		OpenInfraPlatform::IfcBridge::IfcSolidOrShell,
		OpenInfraPlatform::IfcBridge::IfcSoundPowerMeasure,
		OpenInfraPlatform::IfcBridge::IfcSoundPressureMeasure,
		OpenInfraPlatform::IfcBridge::IfcSpace,
		OpenInfraPlatform::IfcBridge::IfcSpaceBoundarySelect,
		OpenInfraPlatform::IfcBridge::IfcSpaceHeater,
		OpenInfraPlatform::IfcBridge::IfcSpaceHeaterType,
		OpenInfraPlatform::IfcBridge::IfcSpaceHeaterTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSpaceType,
		OpenInfraPlatform::IfcBridge::IfcSpaceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSpatialElement,
		OpenInfraPlatform::IfcBridge::IfcSpatialElementType,
		OpenInfraPlatform::IfcBridge::IfcSpatialStructureElement,
		OpenInfraPlatform::IfcBridge::IfcSpatialStructureElementType,
		OpenInfraPlatform::IfcBridge::IfcSpatialZone,
		OpenInfraPlatform::IfcBridge::IfcSpatialZoneType,
		OpenInfraPlatform::IfcBridge::IfcSpatialZoneTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSpecificHeatCapacityMeasure,
		OpenInfraPlatform::IfcBridge::IfcSpecularExponent,
		OpenInfraPlatform::IfcBridge::IfcSpecularHighlightSelect,
		OpenInfraPlatform::IfcBridge::IfcSpecularRoughness,
		OpenInfraPlatform::IfcBridge::IfcSphere,
		OpenInfraPlatform::IfcBridge::IfcStackTerminal,
		OpenInfraPlatform::IfcBridge::IfcStackTerminalType,
		OpenInfraPlatform::IfcBridge::IfcStackTerminalTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStair,
		OpenInfraPlatform::IfcBridge::IfcStairFlight,
		OpenInfraPlatform::IfcBridge::IfcStairFlightType,
		OpenInfraPlatform::IfcBridge::IfcStairFlightTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStairType,
		OpenInfraPlatform::IfcBridge::IfcStairTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStateEnum,
		OpenInfraPlatform::IfcBridge::IfcStructuralAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralActivity,
		OpenInfraPlatform::IfcBridge::IfcStructuralActivityAssignmentSelect,
		OpenInfraPlatform::IfcBridge::IfcStructuralAnalysisModel,
		OpenInfraPlatform::IfcBridge::IfcStructuralConnection,
		OpenInfraPlatform::IfcBridge::IfcStructuralConnectionCondition,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveActivityTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveConnection,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveMember,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveMemberTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveMemberVarying,
		OpenInfraPlatform::IfcBridge::IfcStructuralCurveReaction,
		OpenInfraPlatform::IfcBridge::IfcStructuralItem,
		OpenInfraPlatform::IfcBridge::IfcStructuralLinearAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoad,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadCase,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadConfiguration,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadGroup,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadLinearForce,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadOrResult,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadPlanarForce,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadSingleDisplacement,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadSingleDisplacementDistortion,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadSingleForce,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadSingleForceWarping,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadStatic,
		OpenInfraPlatform::IfcBridge::IfcStructuralLoadTemperature,
		OpenInfraPlatform::IfcBridge::IfcStructuralMember,
		OpenInfraPlatform::IfcBridge::IfcStructuralPlanarAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralPointAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralPointConnection,
		OpenInfraPlatform::IfcBridge::IfcStructuralPointReaction,
		OpenInfraPlatform::IfcBridge::IfcStructuralReaction,
		OpenInfraPlatform::IfcBridge::IfcStructuralResultGroup,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceAction,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceActivityTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceConnection,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceMember,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceMemberTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceMemberVarying,
		OpenInfraPlatform::IfcBridge::IfcStructuralSurfaceReaction,
		OpenInfraPlatform::IfcBridge::IfcStyleAssignmentSelect,
		OpenInfraPlatform::IfcBridge::IfcStyledItem,
		OpenInfraPlatform::IfcBridge::IfcStyledRepresentation,
		OpenInfraPlatform::IfcBridge::IfcStyleModel,
		OpenInfraPlatform::IfcBridge::IfcSubContractResource,
		OpenInfraPlatform::IfcBridge::IfcSubContractResourceType,
		OpenInfraPlatform::IfcBridge::IfcSubContractResourceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSubedge,
		OpenInfraPlatform::IfcBridge::IfcSurface,
		OpenInfraPlatform::IfcBridge::IfcSurfaceCurveSweptAreaSolid,
		OpenInfraPlatform::IfcBridge::IfcSurfaceFeature,
		OpenInfraPlatform::IfcBridge::IfcSurfaceFeatureTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSurfaceOfLinearExtrusion,
		OpenInfraPlatform::IfcBridge::IfcSurfaceOfRevolution,
		OpenInfraPlatform::IfcBridge::IfcSurfaceOrFaceSurface,
		OpenInfraPlatform::IfcBridge::IfcSurfaceReinforcementArea,
		OpenInfraPlatform::IfcBridge::IfcSurfaceSide,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyle,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleElementSelect,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleLighting,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleRefraction,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleRendering,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleShading,
		OpenInfraPlatform::IfcBridge::IfcSurfaceStyleWithTextures,
		OpenInfraPlatform::IfcBridge::IfcSurfaceTexture,
		OpenInfraPlatform::IfcBridge::IfcSweptAreaSolid,
		OpenInfraPlatform::IfcBridge::IfcSweptDiskSolid,
		OpenInfraPlatform::IfcBridge::IfcSweptDiskSolidPolygonal,
		OpenInfraPlatform::IfcBridge::IfcSweptSurface,
		OpenInfraPlatform::IfcBridge::IfcSwitchingDevice,
		OpenInfraPlatform::IfcBridge::IfcSwitchingDeviceType,
		OpenInfraPlatform::IfcBridge::IfcSwitchingDeviceTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcSymbolStyle,
		OpenInfraPlatform::IfcBridge::IfcSymbolStyleSelect,
		OpenInfraPlatform::IfcBridge::IfcSystem,
		OpenInfraPlatform::IfcBridge::IfcSystemFurnitureElement,
		OpenInfraPlatform::IfcBridge::IfcSystemFurnitureElementType,
		OpenInfraPlatform::IfcBridge::IfcSystemFurnitureElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTable,
		OpenInfraPlatform::IfcBridge::IfcTableColumn,
		OpenInfraPlatform::IfcBridge::IfcTableRow,
		OpenInfraPlatform::IfcBridge::IfcTank,
		OpenInfraPlatform::IfcBridge::IfcTankType,
		OpenInfraPlatform::IfcBridge::IfcTankTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTask,
		OpenInfraPlatform::IfcBridge::IfcTaskDurationEnum,
		OpenInfraPlatform::IfcBridge::IfcTaskTime,
		OpenInfraPlatform::IfcBridge::IfcTaskTimeRecurring,
		OpenInfraPlatform::IfcBridge::IfcTaskType,
		OpenInfraPlatform::IfcBridge::IfcTaskTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTelecomAddress,
		OpenInfraPlatform::IfcBridge::IfcTemperatureGradientMeasure,
		OpenInfraPlatform::IfcBridge::IfcTemperatureRateOfChangeMeasure,
		OpenInfraPlatform::IfcBridge::IfcTendon,
		OpenInfraPlatform::IfcBridge::IfcTendonAnchor,
		OpenInfraPlatform::IfcBridge::IfcTendonAnchorType,
		OpenInfraPlatform::IfcBridge::IfcTendonAnchorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTendonType,
		OpenInfraPlatform::IfcBridge::IfcTendonTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTessellatedFaceSet,
		OpenInfraPlatform::IfcBridge::IfcTessellatedItem,
		OpenInfraPlatform::IfcBridge::IfcText,
		OpenInfraPlatform::IfcBridge::IfcTextAlignment,
		OpenInfraPlatform::IfcBridge::IfcTextDecoration,
		OpenInfraPlatform::IfcBridge::IfcTextFontName,
		OpenInfraPlatform::IfcBridge::IfcTextFontSelect,
		OpenInfraPlatform::IfcBridge::IfcTextLiteral,
		OpenInfraPlatform::IfcBridge::IfcTextLiteralWithExtent,
		OpenInfraPlatform::IfcBridge::IfcTextPath,
		OpenInfraPlatform::IfcBridge::IfcTextStyle,
		OpenInfraPlatform::IfcBridge::IfcTextStyleFontModel,
		OpenInfraPlatform::IfcBridge::IfcTextStyleForDefinedFont,
		OpenInfraPlatform::IfcBridge::IfcTextStyleSelect,
		OpenInfraPlatform::IfcBridge::IfcTextStyleTextModel,
		OpenInfraPlatform::IfcBridge::IfcTextStyleWithBoxCharacteristics,
		OpenInfraPlatform::IfcBridge::IfcTextTransformation,
		OpenInfraPlatform::IfcBridge::IfcTextureCoordinate,
		OpenInfraPlatform::IfcBridge::IfcTextureCoordinateGenerator,
		OpenInfraPlatform::IfcBridge::IfcTextureMap,
		OpenInfraPlatform::IfcBridge::IfcTextureVertex,
		OpenInfraPlatform::IfcBridge::IfcTextureVertexList,
		OpenInfraPlatform::IfcBridge::IfcThermalAdmittanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcThermalConductivityMeasure,
		OpenInfraPlatform::IfcBridge::IfcThermalExpansionCoefficientMeasure,
		OpenInfraPlatform::IfcBridge::IfcThermalResistanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcThermalTransmittanceMeasure,
		OpenInfraPlatform::IfcBridge::IfcThermodynamicTemperatureMeasure,
		OpenInfraPlatform::IfcBridge::IfcTime,
		OpenInfraPlatform::IfcBridge::IfcTimeMeasure,
		OpenInfraPlatform::IfcBridge::IfcTimeOrRatioSelect,
		OpenInfraPlatform::IfcBridge::IfcTimePeriod,
		OpenInfraPlatform::IfcBridge::IfcTimeSeries,
		OpenInfraPlatform::IfcBridge::IfcTimeSeriesDataTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTimeSeriesValue,
		OpenInfraPlatform::IfcBridge::IfcTimeStamp,
		OpenInfraPlatform::IfcBridge::IfcTopologicalRepresentationItem,
		OpenInfraPlatform::IfcBridge::IfcTopologyRepresentation,
		OpenInfraPlatform::IfcBridge::IfcTorqueMeasure,
		OpenInfraPlatform::IfcBridge::IfcTransformer,
		OpenInfraPlatform::IfcBridge::IfcTransformerType,
		OpenInfraPlatform::IfcBridge::IfcTransformerTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTransitionCode,
		OpenInfraPlatform::IfcBridge::IfcTranslationalStiffnessSelect,
		OpenInfraPlatform::IfcBridge::IfcTransportElement,
		OpenInfraPlatform::IfcBridge::IfcTransportElementType,
		OpenInfraPlatform::IfcBridge::IfcTransportElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTrapeziumProfileDef,
		OpenInfraPlatform::IfcBridge::IfcTriangulatedFaceSet,
		OpenInfraPlatform::IfcBridge::IfcTrimmedCurve,
		OpenInfraPlatform::IfcBridge::IfcTrimmingPreference,
		OpenInfraPlatform::IfcBridge::IfcTrimmingSelect,
		OpenInfraPlatform::IfcBridge::IfcTShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcTubeBundle,
		OpenInfraPlatform::IfcBridge::IfcTubeBundleType,
		OpenInfraPlatform::IfcBridge::IfcTubeBundleTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcTwoDirectionRepeatFactor,
		OpenInfraPlatform::IfcBridge::IfcTypeObject,
		OpenInfraPlatform::IfcBridge::IfcTypeProcess,
		OpenInfraPlatform::IfcBridge::IfcTypeProduct,
		OpenInfraPlatform::IfcBridge::IfcTypeResource,
		OpenInfraPlatform::IfcBridge::IfcUnit,
		OpenInfraPlatform::IfcBridge::IfcUnitaryControlElement,
		OpenInfraPlatform::IfcBridge::IfcUnitaryControlElementType,
		OpenInfraPlatform::IfcBridge::IfcUnitaryControlElementTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcUnitaryEquipment,
		OpenInfraPlatform::IfcBridge::IfcUnitaryEquipmentType,
		OpenInfraPlatform::IfcBridge::IfcUnitaryEquipmentTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcUnitAssignment,
		OpenInfraPlatform::IfcBridge::IfcUnitEnum,
		OpenInfraPlatform::IfcBridge::IfcURIReference,
		OpenInfraPlatform::IfcBridge::IfcUShapeProfileDef,
		OpenInfraPlatform::IfcBridge::IfcValue,
		OpenInfraPlatform::IfcBridge::IfcValve,
		OpenInfraPlatform::IfcBridge::IfcValveType,
		OpenInfraPlatform::IfcBridge::IfcValveTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcVaporPermeabilityMeasure,
		OpenInfraPlatform::IfcBridge::IfcVector,
		OpenInfraPlatform::IfcBridge::IfcVectorOrDirection,
		OpenInfraPlatform::IfcBridge::IfcVertex,
		OpenInfraPlatform::IfcBridge::IfcVertexLoop,
		OpenInfraPlatform::IfcBridge::IfcVertexPoint,
		OpenInfraPlatform::IfcBridge::IfcVibrationIsolator,
		OpenInfraPlatform::IfcBridge::IfcVibrationIsolatorType,
		OpenInfraPlatform::IfcBridge::IfcVibrationIsolatorTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcVirtualElement,
		OpenInfraPlatform::IfcBridge::IfcVirtualGridIntersection,
		OpenInfraPlatform::IfcBridge::IfcVoidingFeature,
		OpenInfraPlatform::IfcBridge::IfcVoidingFeatureTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcVolumeMeasure,
		OpenInfraPlatform::IfcBridge::IfcVolumetricFlowRateMeasure,
		OpenInfraPlatform::IfcBridge::IfcWall,
		OpenInfraPlatform::IfcBridge::IfcWallElementedCase,
		OpenInfraPlatform::IfcBridge::IfcWallStandardCase,
		OpenInfraPlatform::IfcBridge::IfcWallType,
		OpenInfraPlatform::IfcBridge::IfcWallTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWarpingConstantMeasure,
		OpenInfraPlatform::IfcBridge::IfcWarpingMomentMeasure,
		OpenInfraPlatform::IfcBridge::IfcWarpingStiffnessSelect,
		OpenInfraPlatform::IfcBridge::IfcWasteTerminal,
		OpenInfraPlatform::IfcBridge::IfcWasteTerminalType,
		OpenInfraPlatform::IfcBridge::IfcWasteTerminalTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWindow,
		OpenInfraPlatform::IfcBridge::IfcWindowLiningProperties,
		OpenInfraPlatform::IfcBridge::IfcWindowPanelOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcWindowPanelPositionEnum,
		OpenInfraPlatform::IfcBridge::IfcWindowPanelProperties,
		OpenInfraPlatform::IfcBridge::IfcWindowStandardCase,
		OpenInfraPlatform::IfcBridge::IfcWindowStyle,
		OpenInfraPlatform::IfcBridge::IfcWindowStyleConstructionEnum,
		OpenInfraPlatform::IfcBridge::IfcWindowStyleOperationEnum,
		OpenInfraPlatform::IfcBridge::IfcWindowType,
		OpenInfraPlatform::IfcBridge::IfcWindowTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWindowTypePartitioningEnum,
		OpenInfraPlatform::IfcBridge::IfcWorkCalendar,
		OpenInfraPlatform::IfcBridge::IfcWorkCalendarTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWorkControl,
		OpenInfraPlatform::IfcBridge::IfcWorkPlan,
		OpenInfraPlatform::IfcBridge::IfcWorkPlanTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWorkSchedule,
		OpenInfraPlatform::IfcBridge::IfcWorkScheduleTypeEnum,
		OpenInfraPlatform::IfcBridge::IfcWorkTime,
		OpenInfraPlatform::IfcBridge::IfcZone,
		OpenInfraPlatform::IfcBridge::IfcZShapeProfileDef
	>
	IfcBridgeEntityTypes;
}
