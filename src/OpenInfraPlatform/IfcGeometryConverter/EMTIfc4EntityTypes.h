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

#include "EMTBasicIfc4EntityTypes.h"

namespace OpenInfraPlatform
{
	namespace Ifc4
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
		 class IfcAmountOfSubstanceMeasure;
		 class IfcAnalysisModelTypeEnum;
		 class IfcAnalysisTheoryTypeEnum;
		 class IfcAngularVelocityMeasure;
		 class IfcAnnotation;
		 class IfcAnnotationFillArea;
		 class IfcApplication;
		 class IfcAppliedValue;
		 class IfcAppliedValueSelect;
		 class IfcApproval;
		 class IfcApprovalRelationship;
		 class IfcArbitraryClosedProfileDef;
		 class IfcArbitraryOpenProfileDef;
		 class IfcArbitraryProfileDefWithVoids;
		 class IfcArcIndex;
		 class IfcAreaDensityMeasure;
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
		 class IfcBinary;
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
		 class IfcCartesianPointList2D;
		 class IfcCartesianPointList3D;
		 class IfcCartesianTransformationOperator;
		 class IfcCartesianTransformationOperator2D;
		 class IfcCartesianTransformationOperator2DnonUniform;
		 class IfcCartesianTransformationOperator3D;
		 class IfcCartesianTransformationOperator3DnonUniform;
		 class IfcCenterLineProfileDef;
		 class IfcChangeActionEnum;
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
		 class IfcCivilElementType;
		 class IfcClassification;
		 class IfcClassificationReference;
		 class IfcClassificationReferenceSelect;
		 class IfcClassificationSelect;
		 class IfcClosedShell;
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
		 class IfcDistributionPortTypeEnum;
		 class IfcDistributionSystem;
		 class IfcDistributionSystemEnum;
		 class IfcDocumentConfidentialityEnum;
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
		 class IfcIndexedPolyCurve;
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
		 class IfcLineIndex;
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
		 class IfcPositiveInteger;
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
		 class IfcProductRepresentationSelect;
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
		 class IfcPropertySetDefinitionSelect;
		 class IfcPropertySetDefinitionSet;
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
		 class IfcReference;
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
		 class IfcSegmentIndexSelect;
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
		 class IfcSoundPowerLevelMeasure;
		 class IfcSoundPowerMeasure;
		 class IfcSoundPressureLevelMeasure;
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
		 class IfcStrippedOptional;
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
		 class IfcTextStyleTextModel;
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
	typedef BasicIfc4EntityTypes<
		OpenInfraPlatform::Ifc4::IfcAbsorbedDoseMeasure,
		OpenInfraPlatform::Ifc4::IfcAccelerationMeasure,
		OpenInfraPlatform::Ifc4::IfcActionRequest,
		OpenInfraPlatform::Ifc4::IfcActionRequestTypeEnum,
		OpenInfraPlatform::Ifc4::IfcActionSourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcActionTypeEnum,
		OpenInfraPlatform::Ifc4::IfcActor,
		OpenInfraPlatform::Ifc4::IfcActorRole,
		OpenInfraPlatform::Ifc4::IfcActorSelect,
		OpenInfraPlatform::Ifc4::IfcActuator,
		OpenInfraPlatform::Ifc4::IfcActuatorType,
		OpenInfraPlatform::Ifc4::IfcActuatorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAddress,
		OpenInfraPlatform::Ifc4::IfcAddressTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAdvancedBrep,
		OpenInfraPlatform::Ifc4::IfcAdvancedBrepWithVoids,
		OpenInfraPlatform::Ifc4::IfcAdvancedFace,
		OpenInfraPlatform::Ifc4::IfcAirTerminal,
		OpenInfraPlatform::Ifc4::IfcAirTerminalBox,
		OpenInfraPlatform::Ifc4::IfcAirTerminalBoxType,
		OpenInfraPlatform::Ifc4::IfcAirTerminalBoxTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAirTerminalType,
		OpenInfraPlatform::Ifc4::IfcAirTerminalTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAirToAirHeatRecovery,
		OpenInfraPlatform::Ifc4::IfcAirToAirHeatRecoveryType,
		OpenInfraPlatform::Ifc4::IfcAirToAirHeatRecoveryTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAlarm,
		OpenInfraPlatform::Ifc4::IfcAlarmType,
		OpenInfraPlatform::Ifc4::IfcAlarmTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAmountOfSubstanceMeasure,
		OpenInfraPlatform::Ifc4::IfcAnalysisModelTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAnalysisTheoryTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAngularVelocityMeasure,
		OpenInfraPlatform::Ifc4::IfcAnnotation,
		OpenInfraPlatform::Ifc4::IfcAnnotationFillArea,
		OpenInfraPlatform::Ifc4::IfcApplication,
		OpenInfraPlatform::Ifc4::IfcAppliedValue,
		OpenInfraPlatform::Ifc4::IfcAppliedValueSelect,
		OpenInfraPlatform::Ifc4::IfcApproval,
		OpenInfraPlatform::Ifc4::IfcApprovalRelationship,
		OpenInfraPlatform::Ifc4::IfcArbitraryClosedProfileDef,
		OpenInfraPlatform::Ifc4::IfcArbitraryOpenProfileDef,
		OpenInfraPlatform::Ifc4::IfcArbitraryProfileDefWithVoids,
		OpenInfraPlatform::Ifc4::IfcArcIndex,
		OpenInfraPlatform::Ifc4::IfcAreaDensityMeasure,
		OpenInfraPlatform::Ifc4::IfcAreaMeasure,
		OpenInfraPlatform::Ifc4::IfcArithmeticOperatorEnum,
		OpenInfraPlatform::Ifc4::IfcAssemblyPlaceEnum,
		OpenInfraPlatform::Ifc4::IfcAsset,
		OpenInfraPlatform::Ifc4::IfcAsymmetricIShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcAudioVisualAppliance,
		OpenInfraPlatform::Ifc4::IfcAudioVisualApplianceType,
		OpenInfraPlatform::Ifc4::IfcAudioVisualApplianceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcAxis1Placement,
		OpenInfraPlatform::Ifc4::IfcAxis2Placement,
		OpenInfraPlatform::Ifc4::IfcAxis2Placement2D,
		OpenInfraPlatform::Ifc4::IfcAxis2Placement3D,
		OpenInfraPlatform::Ifc4::IfcBeam,
		OpenInfraPlatform::Ifc4::IfcBeamStandardCase,
		OpenInfraPlatform::Ifc4::IfcBeamType,
		OpenInfraPlatform::Ifc4::IfcBeamTypeEnum,
		OpenInfraPlatform::Ifc4::IfcBenchmarkEnum,
		OpenInfraPlatform::Ifc4::IfcBendingParameterSelect,
		OpenInfraPlatform::Ifc4::IfcBinary,
		OpenInfraPlatform::Ifc4::IfcBlobTexture,
		OpenInfraPlatform::Ifc4::IfcBlock,
		OpenInfraPlatform::Ifc4::IfcBoiler,
		OpenInfraPlatform::Ifc4::IfcBoilerType,
		OpenInfraPlatform::Ifc4::IfcBoilerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcBoolean,
		OpenInfraPlatform::Ifc4::IfcBooleanClippingResult,
		OpenInfraPlatform::Ifc4::IfcBooleanOperand,
		OpenInfraPlatform::Ifc4::IfcBooleanOperator,
		OpenInfraPlatform::Ifc4::IfcBooleanResult,
		OpenInfraPlatform::Ifc4::IfcBoundaryCondition,
		OpenInfraPlatform::Ifc4::IfcBoundaryCurve,
		OpenInfraPlatform::Ifc4::IfcBoundaryEdgeCondition,
		OpenInfraPlatform::Ifc4::IfcBoundaryFaceCondition,
		OpenInfraPlatform::Ifc4::IfcBoundaryNodeCondition,
		OpenInfraPlatform::Ifc4::IfcBoundaryNodeConditionWarping,
		OpenInfraPlatform::Ifc4::IfcBoundedCurve,
		OpenInfraPlatform::Ifc4::IfcBoundedSurface,
		OpenInfraPlatform::Ifc4::IfcBoundingBox,
		OpenInfraPlatform::Ifc4::IfcBoxAlignment,
		OpenInfraPlatform::Ifc4::IfcBoxedHalfSpace,
		OpenInfraPlatform::Ifc4::IfcBSplineCurve,
		OpenInfraPlatform::Ifc4::IfcBSplineCurveForm,
		OpenInfraPlatform::Ifc4::IfcBSplineCurveWithKnots,
		OpenInfraPlatform::Ifc4::IfcBSplineSurface,
		OpenInfraPlatform::Ifc4::IfcBSplineSurfaceForm,
		OpenInfraPlatform::Ifc4::IfcBSplineSurfaceWithKnots,
		OpenInfraPlatform::Ifc4::IfcBuilding,
		OpenInfraPlatform::Ifc4::IfcBuildingElement,
		OpenInfraPlatform::Ifc4::IfcBuildingElementPart,
		OpenInfraPlatform::Ifc4::IfcBuildingElementPartType,
		OpenInfraPlatform::Ifc4::IfcBuildingElementPartTypeEnum,
		OpenInfraPlatform::Ifc4::IfcBuildingElementProxy,
		OpenInfraPlatform::Ifc4::IfcBuildingElementProxyType,
		OpenInfraPlatform::Ifc4::IfcBuildingElementProxyTypeEnum,
		OpenInfraPlatform::Ifc4::IfcBuildingElementType,
		OpenInfraPlatform::Ifc4::IfcBuildingStorey,
		OpenInfraPlatform::Ifc4::IfcBuildingSystem,
		OpenInfraPlatform::Ifc4::IfcBuildingSystemTypeEnum,
		OpenInfraPlatform::Ifc4::IfcBurner,
		OpenInfraPlatform::Ifc4::IfcBurnerType,
		OpenInfraPlatform::Ifc4::IfcBurnerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCableCarrierFitting,
		OpenInfraPlatform::Ifc4::IfcCableCarrierFittingType,
		OpenInfraPlatform::Ifc4::IfcCableCarrierFittingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCableCarrierSegment,
		OpenInfraPlatform::Ifc4::IfcCableCarrierSegmentType,
		OpenInfraPlatform::Ifc4::IfcCableCarrierSegmentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCableFitting,
		OpenInfraPlatform::Ifc4::IfcCableFittingType,
		OpenInfraPlatform::Ifc4::IfcCableFittingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCableSegment,
		OpenInfraPlatform::Ifc4::IfcCableSegmentType,
		OpenInfraPlatform::Ifc4::IfcCableSegmentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCardinalPointReference,
		OpenInfraPlatform::Ifc4::IfcCartesianPoint,
		OpenInfraPlatform::Ifc4::IfcCartesianPointList,
		OpenInfraPlatform::Ifc4::IfcCartesianPointList2D,
		OpenInfraPlatform::Ifc4::IfcCartesianPointList3D,
		OpenInfraPlatform::Ifc4::IfcCartesianTransformationOperator,
		OpenInfraPlatform::Ifc4::IfcCartesianTransformationOperator2D,
		OpenInfraPlatform::Ifc4::IfcCartesianTransformationOperator2DnonUniform,
		OpenInfraPlatform::Ifc4::IfcCartesianTransformationOperator3D,
		OpenInfraPlatform::Ifc4::IfcCartesianTransformationOperator3DnonUniform,
		OpenInfraPlatform::Ifc4::IfcCenterLineProfileDef,
		OpenInfraPlatform::Ifc4::IfcChangeActionEnum,
		OpenInfraPlatform::Ifc4::IfcChiller,
		OpenInfraPlatform::Ifc4::IfcChillerType,
		OpenInfraPlatform::Ifc4::IfcChillerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcChimney,
		OpenInfraPlatform::Ifc4::IfcChimneyType,
		OpenInfraPlatform::Ifc4::IfcChimneyTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCircle,
		OpenInfraPlatform::Ifc4::IfcCircleHollowProfileDef,
		OpenInfraPlatform::Ifc4::IfcCircleProfileDef,
		OpenInfraPlatform::Ifc4::IfcCivilElement,
		OpenInfraPlatform::Ifc4::IfcCivilElementType,
		OpenInfraPlatform::Ifc4::IfcClassification,
		OpenInfraPlatform::Ifc4::IfcClassificationReference,
		OpenInfraPlatform::Ifc4::IfcClassificationReferenceSelect,
		OpenInfraPlatform::Ifc4::IfcClassificationSelect,
		OpenInfraPlatform::Ifc4::IfcClosedShell,
		OpenInfraPlatform::Ifc4::IfcCoil,
		OpenInfraPlatform::Ifc4::IfcCoilType,
		OpenInfraPlatform::Ifc4::IfcCoilTypeEnum,
		OpenInfraPlatform::Ifc4::IfcColour,
		OpenInfraPlatform::Ifc4::IfcColourOrFactor,
		OpenInfraPlatform::Ifc4::IfcColourRgb,
		OpenInfraPlatform::Ifc4::IfcColourRgbList,
		OpenInfraPlatform::Ifc4::IfcColourSpecification,
		OpenInfraPlatform::Ifc4::IfcColumn,
		OpenInfraPlatform::Ifc4::IfcColumnStandardCase,
		OpenInfraPlatform::Ifc4::IfcColumnType,
		OpenInfraPlatform::Ifc4::IfcColumnTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCommunicationsAppliance,
		OpenInfraPlatform::Ifc4::IfcCommunicationsApplianceType,
		OpenInfraPlatform::Ifc4::IfcCommunicationsApplianceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcComplexNumber,
		OpenInfraPlatform::Ifc4::IfcComplexProperty,
		OpenInfraPlatform::Ifc4::IfcComplexPropertyTemplate,
		OpenInfraPlatform::Ifc4::IfcComplexPropertyTemplateTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCompositeCurve,
		OpenInfraPlatform::Ifc4::IfcCompositeCurveOnSurface,
		OpenInfraPlatform::Ifc4::IfcCompositeCurveSegment,
		OpenInfraPlatform::Ifc4::IfcCompositeProfileDef,
		OpenInfraPlatform::Ifc4::IfcCompoundPlaneAngleMeasure,
		OpenInfraPlatform::Ifc4::IfcCompressor,
		OpenInfraPlatform::Ifc4::IfcCompressorType,
		OpenInfraPlatform::Ifc4::IfcCompressorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCondenser,
		OpenInfraPlatform::Ifc4::IfcCondenserType,
		OpenInfraPlatform::Ifc4::IfcCondenserTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConic,
		OpenInfraPlatform::Ifc4::IfcConnectedFaceSet,
		OpenInfraPlatform::Ifc4::IfcConnectionCurveGeometry,
		OpenInfraPlatform::Ifc4::IfcConnectionGeometry,
		OpenInfraPlatform::Ifc4::IfcConnectionPointEccentricity,
		OpenInfraPlatform::Ifc4::IfcConnectionPointGeometry,
		OpenInfraPlatform::Ifc4::IfcConnectionSurfaceGeometry,
		OpenInfraPlatform::Ifc4::IfcConnectionTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConnectionVolumeGeometry,
		OpenInfraPlatform::Ifc4::IfcConstraint,
		OpenInfraPlatform::Ifc4::IfcConstraintEnum,
		OpenInfraPlatform::Ifc4::IfcConstructionEquipmentResource,
		OpenInfraPlatform::Ifc4::IfcConstructionEquipmentResourceType,
		OpenInfraPlatform::Ifc4::IfcConstructionEquipmentResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConstructionMaterialResource,
		OpenInfraPlatform::Ifc4::IfcConstructionMaterialResourceType,
		OpenInfraPlatform::Ifc4::IfcConstructionMaterialResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConstructionProductResource,
		OpenInfraPlatform::Ifc4::IfcConstructionProductResourceType,
		OpenInfraPlatform::Ifc4::IfcConstructionProductResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConstructionResource,
		OpenInfraPlatform::Ifc4::IfcConstructionResourceType,
		OpenInfraPlatform::Ifc4::IfcContext,
		OpenInfraPlatform::Ifc4::IfcContextDependentMeasure,
		OpenInfraPlatform::Ifc4::IfcContextDependentUnit,
		OpenInfraPlatform::Ifc4::IfcControl,
		OpenInfraPlatform::Ifc4::IfcController,
		OpenInfraPlatform::Ifc4::IfcControllerType,
		OpenInfraPlatform::Ifc4::IfcControllerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcConversionBasedUnit,
		OpenInfraPlatform::Ifc4::IfcConversionBasedUnitWithOffset,
		OpenInfraPlatform::Ifc4::IfcCooledBeam,
		OpenInfraPlatform::Ifc4::IfcCooledBeamType,
		OpenInfraPlatform::Ifc4::IfcCooledBeamTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCoolingTower,
		OpenInfraPlatform::Ifc4::IfcCoolingTowerType,
		OpenInfraPlatform::Ifc4::IfcCoolingTowerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCoordinateOperation,
		OpenInfraPlatform::Ifc4::IfcCoordinateReferenceSystem,
		OpenInfraPlatform::Ifc4::IfcCoordinateReferenceSystemSelect,
		OpenInfraPlatform::Ifc4::IfcCostItem,
		OpenInfraPlatform::Ifc4::IfcCostItemTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCostSchedule,
		OpenInfraPlatform::Ifc4::IfcCostScheduleTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCostValue,
		OpenInfraPlatform::Ifc4::IfcCountMeasure,
		OpenInfraPlatform::Ifc4::IfcCovering,
		OpenInfraPlatform::Ifc4::IfcCoveringType,
		OpenInfraPlatform::Ifc4::IfcCoveringTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCrewResource,
		OpenInfraPlatform::Ifc4::IfcCrewResourceType,
		OpenInfraPlatform::Ifc4::IfcCrewResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCsgPrimitive3D,
		OpenInfraPlatform::Ifc4::IfcCsgSelect,
		OpenInfraPlatform::Ifc4::IfcCsgSolid,
		OpenInfraPlatform::Ifc4::IfcCShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcCurrencyRelationship,
		OpenInfraPlatform::Ifc4::IfcCurtainWall,
		OpenInfraPlatform::Ifc4::IfcCurtainWallType,
		OpenInfraPlatform::Ifc4::IfcCurtainWallTypeEnum,
		OpenInfraPlatform::Ifc4::IfcCurvatureMeasure,
		OpenInfraPlatform::Ifc4::IfcCurve,
		OpenInfraPlatform::Ifc4::IfcCurveBoundedPlane,
		OpenInfraPlatform::Ifc4::IfcCurveBoundedSurface,
		OpenInfraPlatform::Ifc4::IfcCurveFontOrScaledCurveFontSelect,
		OpenInfraPlatform::Ifc4::IfcCurveInterpolationEnum,
		OpenInfraPlatform::Ifc4::IfcCurveOnSurface,
		OpenInfraPlatform::Ifc4::IfcCurveOrEdgeCurve,
		OpenInfraPlatform::Ifc4::IfcCurveStyle,
		OpenInfraPlatform::Ifc4::IfcCurveStyleFont,
		OpenInfraPlatform::Ifc4::IfcCurveStyleFontAndScaling,
		OpenInfraPlatform::Ifc4::IfcCurveStyleFontPattern,
		OpenInfraPlatform::Ifc4::IfcCurveStyleFontSelect,
		OpenInfraPlatform::Ifc4::IfcCylindricalSurface,
		OpenInfraPlatform::Ifc4::IfcDamper,
		OpenInfraPlatform::Ifc4::IfcDamperType,
		OpenInfraPlatform::Ifc4::IfcDamperTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDataOriginEnum,
		OpenInfraPlatform::Ifc4::IfcDate,
		OpenInfraPlatform::Ifc4::IfcDateTime,
		OpenInfraPlatform::Ifc4::IfcDayInMonthNumber,
		OpenInfraPlatform::Ifc4::IfcDayInWeekNumber,
		OpenInfraPlatform::Ifc4::IfcDefinitionSelect,
		OpenInfraPlatform::Ifc4::IfcDerivedMeasureValue,
		OpenInfraPlatform::Ifc4::IfcDerivedProfileDef,
		OpenInfraPlatform::Ifc4::IfcDerivedUnit,
		OpenInfraPlatform::Ifc4::IfcDerivedUnitElement,
		OpenInfraPlatform::Ifc4::IfcDerivedUnitEnum,
		OpenInfraPlatform::Ifc4::IfcDescriptiveMeasure,
		OpenInfraPlatform::Ifc4::IfcDimensionalExponents,
		OpenInfraPlatform::Ifc4::IfcDimensionCount,
		OpenInfraPlatform::Ifc4::IfcDirection,
		OpenInfraPlatform::Ifc4::IfcDirectionSenseEnum,
		OpenInfraPlatform::Ifc4::IfcDiscreteAccessory,
		OpenInfraPlatform::Ifc4::IfcDiscreteAccessoryType,
		OpenInfraPlatform::Ifc4::IfcDiscreteAccessoryTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDistributionChamberElement,
		OpenInfraPlatform::Ifc4::IfcDistributionChamberElementType,
		OpenInfraPlatform::Ifc4::IfcDistributionChamberElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDistributionCircuit,
		OpenInfraPlatform::Ifc4::IfcDistributionControlElement,
		OpenInfraPlatform::Ifc4::IfcDistributionControlElementType,
		OpenInfraPlatform::Ifc4::IfcDistributionElement,
		OpenInfraPlatform::Ifc4::IfcDistributionElementType,
		OpenInfraPlatform::Ifc4::IfcDistributionFlowElement,
		OpenInfraPlatform::Ifc4::IfcDistributionFlowElementType,
		OpenInfraPlatform::Ifc4::IfcDistributionPort,
		OpenInfraPlatform::Ifc4::IfcDistributionPortTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDistributionSystem,
		OpenInfraPlatform::Ifc4::IfcDistributionSystemEnum,
		OpenInfraPlatform::Ifc4::IfcDocumentConfidentialityEnum,
		OpenInfraPlatform::Ifc4::IfcDocumentInformation,
		OpenInfraPlatform::Ifc4::IfcDocumentInformationRelationship,
		OpenInfraPlatform::Ifc4::IfcDocumentReference,
		OpenInfraPlatform::Ifc4::IfcDocumentSelect,
		OpenInfraPlatform::Ifc4::IfcDocumentStatusEnum,
		OpenInfraPlatform::Ifc4::IfcDoor,
		OpenInfraPlatform::Ifc4::IfcDoorLiningProperties,
		OpenInfraPlatform::Ifc4::IfcDoorPanelOperationEnum,
		OpenInfraPlatform::Ifc4::IfcDoorPanelPositionEnum,
		OpenInfraPlatform::Ifc4::IfcDoorPanelProperties,
		OpenInfraPlatform::Ifc4::IfcDoorStandardCase,
		OpenInfraPlatform::Ifc4::IfcDoorStyle,
		OpenInfraPlatform::Ifc4::IfcDoorStyleConstructionEnum,
		OpenInfraPlatform::Ifc4::IfcDoorStyleOperationEnum,
		OpenInfraPlatform::Ifc4::IfcDoorType,
		OpenInfraPlatform::Ifc4::IfcDoorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDoorTypeOperationEnum,
		OpenInfraPlatform::Ifc4::IfcDoseEquivalentMeasure,
		OpenInfraPlatform::Ifc4::IfcDraughtingPreDefinedColour,
		OpenInfraPlatform::Ifc4::IfcDraughtingPreDefinedCurveFont,
		OpenInfraPlatform::Ifc4::IfcDuctFitting,
		OpenInfraPlatform::Ifc4::IfcDuctFittingType,
		OpenInfraPlatform::Ifc4::IfcDuctFittingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDuctSegment,
		OpenInfraPlatform::Ifc4::IfcDuctSegmentType,
		OpenInfraPlatform::Ifc4::IfcDuctSegmentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDuctSilencer,
		OpenInfraPlatform::Ifc4::IfcDuctSilencerType,
		OpenInfraPlatform::Ifc4::IfcDuctSilencerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcDuration,
		OpenInfraPlatform::Ifc4::IfcDynamicViscosityMeasure,
		OpenInfraPlatform::Ifc4::IfcEdge,
		OpenInfraPlatform::Ifc4::IfcEdgeCurve,
		OpenInfraPlatform::Ifc4::IfcEdgeLoop,
		OpenInfraPlatform::Ifc4::IfcElectricAppliance,
		OpenInfraPlatform::Ifc4::IfcElectricApplianceType,
		OpenInfraPlatform::Ifc4::IfcElectricApplianceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricCapacitanceMeasure,
		OpenInfraPlatform::Ifc4::IfcElectricChargeMeasure,
		OpenInfraPlatform::Ifc4::IfcElectricConductanceMeasure,
		OpenInfraPlatform::Ifc4::IfcElectricCurrentMeasure,
		OpenInfraPlatform::Ifc4::IfcElectricDistributionBoard,
		OpenInfraPlatform::Ifc4::IfcElectricDistributionBoardType,
		OpenInfraPlatform::Ifc4::IfcElectricDistributionBoardTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricFlowStorageDevice,
		OpenInfraPlatform::Ifc4::IfcElectricFlowStorageDeviceType,
		OpenInfraPlatform::Ifc4::IfcElectricFlowStorageDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricGenerator,
		OpenInfraPlatform::Ifc4::IfcElectricGeneratorType,
		OpenInfraPlatform::Ifc4::IfcElectricGeneratorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricMotor,
		OpenInfraPlatform::Ifc4::IfcElectricMotorType,
		OpenInfraPlatform::Ifc4::IfcElectricMotorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricResistanceMeasure,
		OpenInfraPlatform::Ifc4::IfcElectricTimeControl,
		OpenInfraPlatform::Ifc4::IfcElectricTimeControlType,
		OpenInfraPlatform::Ifc4::IfcElectricTimeControlTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElectricVoltageMeasure,
		OpenInfraPlatform::Ifc4::IfcElement,
		OpenInfraPlatform::Ifc4::IfcElementarySurface,
		OpenInfraPlatform::Ifc4::IfcElementAssembly,
		OpenInfraPlatform::Ifc4::IfcElementAssemblyType,
		OpenInfraPlatform::Ifc4::IfcElementAssemblyTypeEnum,
		OpenInfraPlatform::Ifc4::IfcElementComponent,
		OpenInfraPlatform::Ifc4::IfcElementComponentType,
		OpenInfraPlatform::Ifc4::IfcElementCompositionEnum,
		OpenInfraPlatform::Ifc4::IfcElementQuantity,
		OpenInfraPlatform::Ifc4::IfcElementType,
		OpenInfraPlatform::Ifc4::IfcEllipse,
		OpenInfraPlatform::Ifc4::IfcEllipseProfileDef,
		OpenInfraPlatform::Ifc4::IfcEnergyConversionDevice,
		OpenInfraPlatform::Ifc4::IfcEnergyConversionDeviceType,
		OpenInfraPlatform::Ifc4::IfcEnergyMeasure,
		OpenInfraPlatform::Ifc4::IfcEngine,
		OpenInfraPlatform::Ifc4::IfcEngineType,
		OpenInfraPlatform::Ifc4::IfcEngineTypeEnum,
		OpenInfraPlatform::Ifc4::IfcEvaporativeCooler,
		OpenInfraPlatform::Ifc4::IfcEvaporativeCoolerType,
		OpenInfraPlatform::Ifc4::IfcEvaporativeCoolerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcEvaporator,
		OpenInfraPlatform::Ifc4::IfcEvaporatorType,
		OpenInfraPlatform::Ifc4::IfcEvaporatorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcEvent,
		OpenInfraPlatform::Ifc4::IfcEventTime,
		OpenInfraPlatform::Ifc4::IfcEventTriggerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcEventType,
		OpenInfraPlatform::Ifc4::IfcEventTypeEnum,
		OpenInfraPlatform::Ifc4::IfcExtendedProperties,
		OpenInfraPlatform::Ifc4::IfcExternalInformation,
		OpenInfraPlatform::Ifc4::IfcExternallyDefinedHatchStyle,
		OpenInfraPlatform::Ifc4::IfcExternallyDefinedSurfaceStyle,
		OpenInfraPlatform::Ifc4::IfcExternallyDefinedTextFont,
		OpenInfraPlatform::Ifc4::IfcExternalReference,
		OpenInfraPlatform::Ifc4::IfcExternalReferenceRelationship,
		OpenInfraPlatform::Ifc4::IfcExternalSpatialElement,
		OpenInfraPlatform::Ifc4::IfcExternalSpatialElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcExternalSpatialStructureElement,
		OpenInfraPlatform::Ifc4::IfcExtrudedAreaSolid,
		OpenInfraPlatform::Ifc4::IfcExtrudedAreaSolidTapered,
		OpenInfraPlatform::Ifc4::IfcFace,
		OpenInfraPlatform::Ifc4::IfcFaceBasedSurfaceModel,
		OpenInfraPlatform::Ifc4::IfcFaceBound,
		OpenInfraPlatform::Ifc4::IfcFaceOuterBound,
		OpenInfraPlatform::Ifc4::IfcFaceSurface,
		OpenInfraPlatform::Ifc4::IfcFacetedBrep,
		OpenInfraPlatform::Ifc4::IfcFacetedBrepWithVoids,
		OpenInfraPlatform::Ifc4::IfcFailureConnectionCondition,
		OpenInfraPlatform::Ifc4::IfcFan,
		OpenInfraPlatform::Ifc4::IfcFanType,
		OpenInfraPlatform::Ifc4::IfcFanTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFastener,
		OpenInfraPlatform::Ifc4::IfcFastenerType,
		OpenInfraPlatform::Ifc4::IfcFastenerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFeatureElement,
		OpenInfraPlatform::Ifc4::IfcFeatureElementAddition,
		OpenInfraPlatform::Ifc4::IfcFeatureElementSubtraction,
		OpenInfraPlatform::Ifc4::IfcFillAreaStyle,
		OpenInfraPlatform::Ifc4::IfcFillAreaStyleHatching,
		OpenInfraPlatform::Ifc4::IfcFillAreaStyleTiles,
		OpenInfraPlatform::Ifc4::IfcFillStyleSelect,
		OpenInfraPlatform::Ifc4::IfcFilter,
		OpenInfraPlatform::Ifc4::IfcFilterType,
		OpenInfraPlatform::Ifc4::IfcFilterTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFireSuppressionTerminal,
		OpenInfraPlatform::Ifc4::IfcFireSuppressionTerminalType,
		OpenInfraPlatform::Ifc4::IfcFireSuppressionTerminalTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFixedReferenceSweptAreaSolid,
		OpenInfraPlatform::Ifc4::IfcFlowController,
		OpenInfraPlatform::Ifc4::IfcFlowControllerType,
		OpenInfraPlatform::Ifc4::IfcFlowDirectionEnum,
		OpenInfraPlatform::Ifc4::IfcFlowFitting,
		OpenInfraPlatform::Ifc4::IfcFlowFittingType,
		OpenInfraPlatform::Ifc4::IfcFlowInstrument,
		OpenInfraPlatform::Ifc4::IfcFlowInstrumentType,
		OpenInfraPlatform::Ifc4::IfcFlowInstrumentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFlowMeter,
		OpenInfraPlatform::Ifc4::IfcFlowMeterType,
		OpenInfraPlatform::Ifc4::IfcFlowMeterTypeEnum,
		OpenInfraPlatform::Ifc4::IfcFlowMovingDevice,
		OpenInfraPlatform::Ifc4::IfcFlowMovingDeviceType,
		OpenInfraPlatform::Ifc4::IfcFlowSegment,
		OpenInfraPlatform::Ifc4::IfcFlowSegmentType,
		OpenInfraPlatform::Ifc4::IfcFlowStorageDevice,
		OpenInfraPlatform::Ifc4::IfcFlowStorageDeviceType,
		OpenInfraPlatform::Ifc4::IfcFlowTerminal,
		OpenInfraPlatform::Ifc4::IfcFlowTerminalType,
		OpenInfraPlatform::Ifc4::IfcFlowTreatmentDevice,
		OpenInfraPlatform::Ifc4::IfcFlowTreatmentDeviceType,
		OpenInfraPlatform::Ifc4::IfcFontStyle,
		OpenInfraPlatform::Ifc4::IfcFontVariant,
		OpenInfraPlatform::Ifc4::IfcFontWeight,
		OpenInfraPlatform::Ifc4::IfcFooting,
		OpenInfraPlatform::Ifc4::IfcFootingType,
		OpenInfraPlatform::Ifc4::IfcFootingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcForceMeasure,
		OpenInfraPlatform::Ifc4::IfcFrequencyMeasure,
		OpenInfraPlatform::Ifc4::IfcFurnishingElement,
		OpenInfraPlatform::Ifc4::IfcFurnishingElementType,
		OpenInfraPlatform::Ifc4::IfcFurniture,
		OpenInfraPlatform::Ifc4::IfcFurnitureType,
		OpenInfraPlatform::Ifc4::IfcFurnitureTypeEnum,
		OpenInfraPlatform::Ifc4::IfcGeographicElement,
		OpenInfraPlatform::Ifc4::IfcGeographicElementType,
		OpenInfraPlatform::Ifc4::IfcGeographicElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcGeometricCurveSet,
		OpenInfraPlatform::Ifc4::IfcGeometricProjectionEnum,
		OpenInfraPlatform::Ifc4::IfcGeometricRepresentationContext,
		OpenInfraPlatform::Ifc4::IfcGeometricRepresentationItem,
		OpenInfraPlatform::Ifc4::IfcGeometricRepresentationSubContext,
		OpenInfraPlatform::Ifc4::IfcGeometricSet,
		OpenInfraPlatform::Ifc4::IfcGeometricSetSelect,
		OpenInfraPlatform::Ifc4::IfcGloballyUniqueId,
		OpenInfraPlatform::Ifc4::IfcGlobalOrLocalEnum,
		OpenInfraPlatform::Ifc4::IfcGrid,
		OpenInfraPlatform::Ifc4::IfcGridAxis,
		OpenInfraPlatform::Ifc4::IfcGridPlacement,
		OpenInfraPlatform::Ifc4::IfcGridPlacementDirectionSelect,
		OpenInfraPlatform::Ifc4::IfcGridTypeEnum,
		OpenInfraPlatform::Ifc4::IfcGroup,
		OpenInfraPlatform::Ifc4::IfcHalfSpaceSolid,
		OpenInfraPlatform::Ifc4::IfcHatchLineDistanceSelect,
		OpenInfraPlatform::Ifc4::IfcHeatExchanger,
		OpenInfraPlatform::Ifc4::IfcHeatExchangerType,
		OpenInfraPlatform::Ifc4::IfcHeatExchangerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcHeatFluxDensityMeasure,
		OpenInfraPlatform::Ifc4::IfcHeatingValueMeasure,
		OpenInfraPlatform::Ifc4::IfcHumidifier,
		OpenInfraPlatform::Ifc4::IfcHumidifierType,
		OpenInfraPlatform::Ifc4::IfcHumidifierTypeEnum,
		OpenInfraPlatform::Ifc4::IfcIdentifier,
		OpenInfraPlatform::Ifc4::IfcIlluminanceMeasure,
		OpenInfraPlatform::Ifc4::IfcImageTexture,
		OpenInfraPlatform::Ifc4::IfcIndexedColourMap,
		OpenInfraPlatform::Ifc4::IfcIndexedPolyCurve,
		OpenInfraPlatform::Ifc4::IfcIndexedTextureMap,
		OpenInfraPlatform::Ifc4::IfcIndexedTriangleTextureMap,
		OpenInfraPlatform::Ifc4::IfcInductanceMeasure,
		OpenInfraPlatform::Ifc4::IfcInteger,
		OpenInfraPlatform::Ifc4::IfcIntegerCountRateMeasure,
		OpenInfraPlatform::Ifc4::IfcInterceptor,
		OpenInfraPlatform::Ifc4::IfcInterceptorType,
		OpenInfraPlatform::Ifc4::IfcInterceptorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcInternalOrExternalEnum,
		OpenInfraPlatform::Ifc4::IfcInventory,
		OpenInfraPlatform::Ifc4::IfcInventoryTypeEnum,
		OpenInfraPlatform::Ifc4::IfcIonConcentrationMeasure,
		OpenInfraPlatform::Ifc4::IfcIrregularTimeSeries,
		OpenInfraPlatform::Ifc4::IfcIrregularTimeSeriesValue,
		OpenInfraPlatform::Ifc4::IfcIShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcIsothermalMoistureCapacityMeasure,
		OpenInfraPlatform::Ifc4::IfcJunctionBox,
		OpenInfraPlatform::Ifc4::IfcJunctionBoxType,
		OpenInfraPlatform::Ifc4::IfcJunctionBoxTypeEnum,
		OpenInfraPlatform::Ifc4::IfcKinematicViscosityMeasure,
		OpenInfraPlatform::Ifc4::IfcKnotType,
		OpenInfraPlatform::Ifc4::IfcLabel,
		OpenInfraPlatform::Ifc4::IfcLaborResource,
		OpenInfraPlatform::Ifc4::IfcLaborResourceType,
		OpenInfraPlatform::Ifc4::IfcLaborResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcLagTime,
		OpenInfraPlatform::Ifc4::IfcLamp,
		OpenInfraPlatform::Ifc4::IfcLampType,
		OpenInfraPlatform::Ifc4::IfcLampTypeEnum,
		OpenInfraPlatform::Ifc4::IfcLanguageId,
		OpenInfraPlatform::Ifc4::IfcLayeredItem,
		OpenInfraPlatform::Ifc4::IfcLayerSetDirectionEnum,
		OpenInfraPlatform::Ifc4::IfcLengthMeasure,
		OpenInfraPlatform::Ifc4::IfcLibraryInformation,
		OpenInfraPlatform::Ifc4::IfcLibraryReference,
		OpenInfraPlatform::Ifc4::IfcLibrarySelect,
		OpenInfraPlatform::Ifc4::IfcLightDistributionCurveEnum,
		OpenInfraPlatform::Ifc4::IfcLightDistributionData,
		OpenInfraPlatform::Ifc4::IfcLightDistributionDataSourceSelect,
		OpenInfraPlatform::Ifc4::IfcLightEmissionSourceEnum,
		OpenInfraPlatform::Ifc4::IfcLightFixture,
		OpenInfraPlatform::Ifc4::IfcLightFixtureType,
		OpenInfraPlatform::Ifc4::IfcLightFixtureTypeEnum,
		OpenInfraPlatform::Ifc4::IfcLightIntensityDistribution,
		OpenInfraPlatform::Ifc4::IfcLightSource,
		OpenInfraPlatform::Ifc4::IfcLightSourceAmbient,
		OpenInfraPlatform::Ifc4::IfcLightSourceDirectional,
		OpenInfraPlatform::Ifc4::IfcLightSourceGoniometric,
		OpenInfraPlatform::Ifc4::IfcLightSourcePositional,
		OpenInfraPlatform::Ifc4::IfcLightSourceSpot,
		OpenInfraPlatform::Ifc4::IfcLine,
		OpenInfraPlatform::Ifc4::IfcLinearForceMeasure,
		OpenInfraPlatform::Ifc4::IfcLinearMomentMeasure,
		OpenInfraPlatform::Ifc4::IfcLinearStiffnessMeasure,
		OpenInfraPlatform::Ifc4::IfcLinearVelocityMeasure,
		OpenInfraPlatform::Ifc4::IfcLineIndex,
		OpenInfraPlatform::Ifc4::IfcLoadGroupTypeEnum,
		OpenInfraPlatform::Ifc4::IfcLocalPlacement,
		OpenInfraPlatform::Ifc4::IfcLogical,
		OpenInfraPlatform::Ifc4::IfcLogicalOperatorEnum,
		OpenInfraPlatform::Ifc4::IfcLoop,
		OpenInfraPlatform::Ifc4::IfcLShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcLuminousFluxMeasure,
		OpenInfraPlatform::Ifc4::IfcLuminousIntensityDistributionMeasure,
		OpenInfraPlatform::Ifc4::IfcLuminousIntensityMeasure,
		OpenInfraPlatform::Ifc4::IfcMagneticFluxDensityMeasure,
		OpenInfraPlatform::Ifc4::IfcMagneticFluxMeasure,
		OpenInfraPlatform::Ifc4::IfcManifoldSolidBrep,
		OpenInfraPlatform::Ifc4::IfcMapConversion,
		OpenInfraPlatform::Ifc4::IfcMappedItem,
		OpenInfraPlatform::Ifc4::IfcMassDensityMeasure,
		OpenInfraPlatform::Ifc4::IfcMassFlowRateMeasure,
		OpenInfraPlatform::Ifc4::IfcMassMeasure,
		OpenInfraPlatform::Ifc4::IfcMassPerLengthMeasure,
		OpenInfraPlatform::Ifc4::IfcMaterial,
		OpenInfraPlatform::Ifc4::IfcMaterialClassificationRelationship,
		OpenInfraPlatform::Ifc4::IfcMaterialConstituent,
		OpenInfraPlatform::Ifc4::IfcMaterialConstituentSet,
		OpenInfraPlatform::Ifc4::IfcMaterialDefinition,
		OpenInfraPlatform::Ifc4::IfcMaterialDefinitionRepresentation,
		OpenInfraPlatform::Ifc4::IfcMaterialLayer,
		OpenInfraPlatform::Ifc4::IfcMaterialLayerSet,
		OpenInfraPlatform::Ifc4::IfcMaterialLayerSetUsage,
		OpenInfraPlatform::Ifc4::IfcMaterialLayerWithOffsets,
		OpenInfraPlatform::Ifc4::IfcMaterialList,
		OpenInfraPlatform::Ifc4::IfcMaterialProfile,
		OpenInfraPlatform::Ifc4::IfcMaterialProfileSet,
		OpenInfraPlatform::Ifc4::IfcMaterialProfileSetUsage,
		OpenInfraPlatform::Ifc4::IfcMaterialProfileSetUsageTapering,
		OpenInfraPlatform::Ifc4::IfcMaterialProfileWithOffsets,
		OpenInfraPlatform::Ifc4::IfcMaterialProperties,
		OpenInfraPlatform::Ifc4::IfcMaterialRelationship,
		OpenInfraPlatform::Ifc4::IfcMaterialSelect,
		OpenInfraPlatform::Ifc4::IfcMaterialUsageDefinition,
		OpenInfraPlatform::Ifc4::IfcMeasureValue,
		OpenInfraPlatform::Ifc4::IfcMeasureWithUnit,
		OpenInfraPlatform::Ifc4::IfcMechanicalFastener,
		OpenInfraPlatform::Ifc4::IfcMechanicalFastenerType,
		OpenInfraPlatform::Ifc4::IfcMechanicalFastenerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcMedicalDevice,
		OpenInfraPlatform::Ifc4::IfcMedicalDeviceType,
		OpenInfraPlatform::Ifc4::IfcMedicalDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcMember,
		OpenInfraPlatform::Ifc4::IfcMemberStandardCase,
		OpenInfraPlatform::Ifc4::IfcMemberType,
		OpenInfraPlatform::Ifc4::IfcMemberTypeEnum,
		OpenInfraPlatform::Ifc4::IfcMetric,
		OpenInfraPlatform::Ifc4::IfcMetricValueSelect,
		OpenInfraPlatform::Ifc4::IfcMirroredProfileDef,
		OpenInfraPlatform::Ifc4::IfcModulusOfElasticityMeasure,
		OpenInfraPlatform::Ifc4::IfcModulusOfLinearSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc4::IfcModulusOfRotationalSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc4::IfcModulusOfRotationalSubgradeReactionSelect,
		OpenInfraPlatform::Ifc4::IfcModulusOfSubgradeReactionMeasure,
		OpenInfraPlatform::Ifc4::IfcModulusOfSubgradeReactionSelect,
		OpenInfraPlatform::Ifc4::IfcModulusOfTranslationalSubgradeReactionSelect,
		OpenInfraPlatform::Ifc4::IfcMoistureDiffusivityMeasure,
		OpenInfraPlatform::Ifc4::IfcMolecularWeightMeasure,
		OpenInfraPlatform::Ifc4::IfcMomentOfInertiaMeasure,
		OpenInfraPlatform::Ifc4::IfcMonetaryMeasure,
		OpenInfraPlatform::Ifc4::IfcMonetaryUnit,
		OpenInfraPlatform::Ifc4::IfcMonthInYearNumber,
		OpenInfraPlatform::Ifc4::IfcMotorConnection,
		OpenInfraPlatform::Ifc4::IfcMotorConnectionType,
		OpenInfraPlatform::Ifc4::IfcMotorConnectionTypeEnum,
		OpenInfraPlatform::Ifc4::IfcNamedUnit,
		OpenInfraPlatform::Ifc4::IfcNonNegativeLengthMeasure,
		OpenInfraPlatform::Ifc4::IfcNormalisedRatioMeasure,
		OpenInfraPlatform::Ifc4::IfcNullStyle,
		OpenInfraPlatform::Ifc4::IfcNumericMeasure,
		OpenInfraPlatform::Ifc4::IfcObject,
		OpenInfraPlatform::Ifc4::IfcObjectDefinition,
		OpenInfraPlatform::Ifc4::IfcObjective,
		OpenInfraPlatform::Ifc4::IfcObjectiveEnum,
		OpenInfraPlatform::Ifc4::IfcObjectPlacement,
		OpenInfraPlatform::Ifc4::IfcObjectReferenceSelect,
		OpenInfraPlatform::Ifc4::IfcObjectTypeEnum,
		OpenInfraPlatform::Ifc4::IfcOccupant,
		OpenInfraPlatform::Ifc4::IfcOccupantTypeEnum,
		OpenInfraPlatform::Ifc4::IfcOffsetCurve2D,
		OpenInfraPlatform::Ifc4::IfcOffsetCurve3D,
		OpenInfraPlatform::Ifc4::IfcOpeningElement,
		OpenInfraPlatform::Ifc4::IfcOpeningElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcOpeningStandardCase,
		OpenInfraPlatform::Ifc4::IfcOpenShell,
		OpenInfraPlatform::Ifc4::IfcOrganization,
		OpenInfraPlatform::Ifc4::IfcOrganizationRelationship,
		OpenInfraPlatform::Ifc4::IfcOrientedEdge,
		OpenInfraPlatform::Ifc4::IfcOuterBoundaryCurve,
		OpenInfraPlatform::Ifc4::IfcOutlet,
		OpenInfraPlatform::Ifc4::IfcOutletType,
		OpenInfraPlatform::Ifc4::IfcOutletTypeEnum,
		OpenInfraPlatform::Ifc4::IfcOwnerHistory,
		OpenInfraPlatform::Ifc4::IfcParameterizedProfileDef,
		OpenInfraPlatform::Ifc4::IfcParameterValue,
		OpenInfraPlatform::Ifc4::IfcPath,
		OpenInfraPlatform::Ifc4::IfcPcurve,
		OpenInfraPlatform::Ifc4::IfcPerformanceHistory,
		OpenInfraPlatform::Ifc4::IfcPerformanceHistoryTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPermeableCoveringOperationEnum,
		OpenInfraPlatform::Ifc4::IfcPermeableCoveringProperties,
		OpenInfraPlatform::Ifc4::IfcPermit,
		OpenInfraPlatform::Ifc4::IfcPermitTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPerson,
		OpenInfraPlatform::Ifc4::IfcPersonAndOrganization,
		OpenInfraPlatform::Ifc4::IfcPHMeasure,
		OpenInfraPlatform::Ifc4::IfcPhysicalComplexQuantity,
		OpenInfraPlatform::Ifc4::IfcPhysicalOrVirtualEnum,
		OpenInfraPlatform::Ifc4::IfcPhysicalQuantity,
		OpenInfraPlatform::Ifc4::IfcPhysicalSimpleQuantity,
		OpenInfraPlatform::Ifc4::IfcPile,
		OpenInfraPlatform::Ifc4::IfcPileConstructionEnum,
		OpenInfraPlatform::Ifc4::IfcPileType,
		OpenInfraPlatform::Ifc4::IfcPileTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPipeFitting,
		OpenInfraPlatform::Ifc4::IfcPipeFittingType,
		OpenInfraPlatform::Ifc4::IfcPipeFittingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPipeSegment,
		OpenInfraPlatform::Ifc4::IfcPipeSegmentType,
		OpenInfraPlatform::Ifc4::IfcPipeSegmentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPixelTexture,
		OpenInfraPlatform::Ifc4::IfcPlacement,
		OpenInfraPlatform::Ifc4::IfcPlanarBox,
		OpenInfraPlatform::Ifc4::IfcPlanarExtent,
		OpenInfraPlatform::Ifc4::IfcPlanarForceMeasure,
		OpenInfraPlatform::Ifc4::IfcPlane,
		OpenInfraPlatform::Ifc4::IfcPlaneAngleMeasure,
		OpenInfraPlatform::Ifc4::IfcPlate,
		OpenInfraPlatform::Ifc4::IfcPlateStandardCase,
		OpenInfraPlatform::Ifc4::IfcPlateType,
		OpenInfraPlatform::Ifc4::IfcPlateTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPoint,
		OpenInfraPlatform::Ifc4::IfcPointOnCurve,
		OpenInfraPlatform::Ifc4::IfcPointOnSurface,
		OpenInfraPlatform::Ifc4::IfcPointOrVertexPoint,
		OpenInfraPlatform::Ifc4::IfcPolygonalBoundedHalfSpace,
		OpenInfraPlatform::Ifc4::IfcPolyline,
		OpenInfraPlatform::Ifc4::IfcPolyLoop,
		OpenInfraPlatform::Ifc4::IfcPort,
		OpenInfraPlatform::Ifc4::IfcPositiveInteger,
		OpenInfraPlatform::Ifc4::IfcPositiveLengthMeasure,
		OpenInfraPlatform::Ifc4::IfcPositivePlaneAngleMeasure,
		OpenInfraPlatform::Ifc4::IfcPositiveRatioMeasure,
		OpenInfraPlatform::Ifc4::IfcPostalAddress,
		OpenInfraPlatform::Ifc4::IfcPowerMeasure,
		OpenInfraPlatform::Ifc4::IfcPreDefinedColour,
		OpenInfraPlatform::Ifc4::IfcPreDefinedCurveFont,
		OpenInfraPlatform::Ifc4::IfcPreDefinedItem,
		OpenInfraPlatform::Ifc4::IfcPreDefinedProperties,
		OpenInfraPlatform::Ifc4::IfcPreDefinedPropertySet,
		OpenInfraPlatform::Ifc4::IfcPreDefinedTextFont,
		OpenInfraPlatform::Ifc4::IfcPresentableText,
		OpenInfraPlatform::Ifc4::IfcPresentationItem,
		OpenInfraPlatform::Ifc4::IfcPresentationLayerAssignment,
		OpenInfraPlatform::Ifc4::IfcPresentationLayerWithStyle,
		OpenInfraPlatform::Ifc4::IfcPresentationStyle,
		OpenInfraPlatform::Ifc4::IfcPresentationStyleAssignment,
		OpenInfraPlatform::Ifc4::IfcPresentationStyleSelect,
		OpenInfraPlatform::Ifc4::IfcPressureMeasure,
		OpenInfraPlatform::Ifc4::IfcProcedure,
		OpenInfraPlatform::Ifc4::IfcProcedureType,
		OpenInfraPlatform::Ifc4::IfcProcedureTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProcess,
		OpenInfraPlatform::Ifc4::IfcProcessSelect,
		OpenInfraPlatform::Ifc4::IfcProduct,
		OpenInfraPlatform::Ifc4::IfcProductDefinitionShape,
		OpenInfraPlatform::Ifc4::IfcProductRepresentation,
		OpenInfraPlatform::Ifc4::IfcProductRepresentationSelect,
		OpenInfraPlatform::Ifc4::IfcProductSelect,
		OpenInfraPlatform::Ifc4::IfcProfileDef,
		OpenInfraPlatform::Ifc4::IfcProfileProperties,
		OpenInfraPlatform::Ifc4::IfcProfileTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProject,
		OpenInfraPlatform::Ifc4::IfcProjectedCRS,
		OpenInfraPlatform::Ifc4::IfcProjectedOrTrueLengthEnum,
		OpenInfraPlatform::Ifc4::IfcProjectionElement,
		OpenInfraPlatform::Ifc4::IfcProjectionElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProjectLibrary,
		OpenInfraPlatform::Ifc4::IfcProjectOrder,
		OpenInfraPlatform::Ifc4::IfcProjectOrderTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProperty,
		OpenInfraPlatform::Ifc4::IfcPropertyAbstraction,
		OpenInfraPlatform::Ifc4::IfcPropertyBoundedValue,
		OpenInfraPlatform::Ifc4::IfcPropertyDefinition,
		OpenInfraPlatform::Ifc4::IfcPropertyDependencyRelationship,
		OpenInfraPlatform::Ifc4::IfcPropertyEnumeratedValue,
		OpenInfraPlatform::Ifc4::IfcPropertyEnumeration,
		OpenInfraPlatform::Ifc4::IfcPropertyListValue,
		OpenInfraPlatform::Ifc4::IfcPropertyReferenceValue,
		OpenInfraPlatform::Ifc4::IfcPropertySet,
		OpenInfraPlatform::Ifc4::IfcPropertySetDefinition,
		OpenInfraPlatform::Ifc4::IfcPropertySetDefinitionSelect,
		OpenInfraPlatform::Ifc4::IfcPropertySetDefinitionSet,
		OpenInfraPlatform::Ifc4::IfcPropertySetTemplate,
		OpenInfraPlatform::Ifc4::IfcPropertySetTemplateTypeEnum,
		OpenInfraPlatform::Ifc4::IfcPropertySingleValue,
		OpenInfraPlatform::Ifc4::IfcPropertyTableValue,
		OpenInfraPlatform::Ifc4::IfcPropertyTemplate,
		OpenInfraPlatform::Ifc4::IfcPropertyTemplateDefinition,
		OpenInfraPlatform::Ifc4::IfcProtectiveDevice,
		OpenInfraPlatform::Ifc4::IfcProtectiveDeviceTrippingUnit,
		OpenInfraPlatform::Ifc4::IfcProtectiveDeviceTrippingUnitType,
		OpenInfraPlatform::Ifc4::IfcProtectiveDeviceTrippingUnitTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProtectiveDeviceType,
		OpenInfraPlatform::Ifc4::IfcProtectiveDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcProxy,
		OpenInfraPlatform::Ifc4::IfcPump,
		OpenInfraPlatform::Ifc4::IfcPumpType,
		OpenInfraPlatform::Ifc4::IfcPumpTypeEnum,
		OpenInfraPlatform::Ifc4::IfcQuantityArea,
		OpenInfraPlatform::Ifc4::IfcQuantityCount,
		OpenInfraPlatform::Ifc4::IfcQuantityLength,
		OpenInfraPlatform::Ifc4::IfcQuantitySet,
		OpenInfraPlatform::Ifc4::IfcQuantityTime,
		OpenInfraPlatform::Ifc4::IfcQuantityVolume,
		OpenInfraPlatform::Ifc4::IfcQuantityWeight,
		OpenInfraPlatform::Ifc4::IfcRadioActivityMeasure,
		OpenInfraPlatform::Ifc4::IfcRailing,
		OpenInfraPlatform::Ifc4::IfcRailingType,
		OpenInfraPlatform::Ifc4::IfcRailingTypeEnum,
		OpenInfraPlatform::Ifc4::IfcRamp,
		OpenInfraPlatform::Ifc4::IfcRampFlight,
		OpenInfraPlatform::Ifc4::IfcRampFlightType,
		OpenInfraPlatform::Ifc4::IfcRampFlightTypeEnum,
		OpenInfraPlatform::Ifc4::IfcRampType,
		OpenInfraPlatform::Ifc4::IfcRampTypeEnum,
		OpenInfraPlatform::Ifc4::IfcRatioMeasure,
		OpenInfraPlatform::Ifc4::IfcRationalBSplineCurveWithKnots,
		OpenInfraPlatform::Ifc4::IfcRationalBSplineSurfaceWithKnots,
		OpenInfraPlatform::Ifc4::IfcReal,
		OpenInfraPlatform::Ifc4::IfcRectangleHollowProfileDef,
		OpenInfraPlatform::Ifc4::IfcRectangleProfileDef,
		OpenInfraPlatform::Ifc4::IfcRectangularPyramid,
		OpenInfraPlatform::Ifc4::IfcRectangularTrimmedSurface,
		OpenInfraPlatform::Ifc4::IfcRecurrencePattern,
		OpenInfraPlatform::Ifc4::IfcRecurrenceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcReference,
		OpenInfraPlatform::Ifc4::IfcReflectanceMethodEnum,
		OpenInfraPlatform::Ifc4::IfcRegularTimeSeries,
		OpenInfraPlatform::Ifc4::IfcReinforcementBarProperties,
		OpenInfraPlatform::Ifc4::IfcReinforcementDefinitionProperties,
		OpenInfraPlatform::Ifc4::IfcReinforcingBar,
		OpenInfraPlatform::Ifc4::IfcReinforcingBarRoleEnum,
		OpenInfraPlatform::Ifc4::IfcReinforcingBarSurfaceEnum,
		OpenInfraPlatform::Ifc4::IfcReinforcingBarType,
		OpenInfraPlatform::Ifc4::IfcReinforcingBarTypeEnum,
		OpenInfraPlatform::Ifc4::IfcReinforcingElement,
		OpenInfraPlatform::Ifc4::IfcReinforcingElementType,
		OpenInfraPlatform::Ifc4::IfcReinforcingMesh,
		OpenInfraPlatform::Ifc4::IfcReinforcingMeshType,
		OpenInfraPlatform::Ifc4::IfcReinforcingMeshTypeEnum,
		OpenInfraPlatform::Ifc4::IfcRelAggregates,
		OpenInfraPlatform::Ifc4::IfcRelAssigns,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToActor,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToControl,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToGroup,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToGroupByFactor,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToProcess,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToProduct,
		OpenInfraPlatform::Ifc4::IfcRelAssignsToResource,
		OpenInfraPlatform::Ifc4::IfcRelAssociates,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesApproval,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesClassification,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesConstraint,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesDocument,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesLibrary,
		OpenInfraPlatform::Ifc4::IfcRelAssociatesMaterial,
		OpenInfraPlatform::Ifc4::IfcRelationship,
		OpenInfraPlatform::Ifc4::IfcRelConnects,
		OpenInfraPlatform::Ifc4::IfcRelConnectsElements,
		OpenInfraPlatform::Ifc4::IfcRelConnectsPathElements,
		OpenInfraPlatform::Ifc4::IfcRelConnectsPorts,
		OpenInfraPlatform::Ifc4::IfcRelConnectsPortToElement,
		OpenInfraPlatform::Ifc4::IfcRelConnectsStructuralActivity,
		OpenInfraPlatform::Ifc4::IfcRelConnectsStructuralMember,
		OpenInfraPlatform::Ifc4::IfcRelConnectsWithEccentricity,
		OpenInfraPlatform::Ifc4::IfcRelConnectsWithRealizingElements,
		OpenInfraPlatform::Ifc4::IfcRelContainedInSpatialStructure,
		OpenInfraPlatform::Ifc4::IfcRelCoversBldgElements,
		OpenInfraPlatform::Ifc4::IfcRelCoversSpaces,
		OpenInfraPlatform::Ifc4::IfcRelDeclares,
		OpenInfraPlatform::Ifc4::IfcRelDecomposes,
		OpenInfraPlatform::Ifc4::IfcRelDefines,
		OpenInfraPlatform::Ifc4::IfcRelDefinesByObject,
		OpenInfraPlatform::Ifc4::IfcRelDefinesByProperties,
		OpenInfraPlatform::Ifc4::IfcRelDefinesByTemplate,
		OpenInfraPlatform::Ifc4::IfcRelDefinesByType,
		OpenInfraPlatform::Ifc4::IfcRelFillsElement,
		OpenInfraPlatform::Ifc4::IfcRelFlowControlElements,
		OpenInfraPlatform::Ifc4::IfcRelInterferesElements,
		OpenInfraPlatform::Ifc4::IfcRelNests,
		OpenInfraPlatform::Ifc4::IfcRelProjectsElement,
		OpenInfraPlatform::Ifc4::IfcRelReferencedInSpatialStructure,
		OpenInfraPlatform::Ifc4::IfcRelSequence,
		OpenInfraPlatform::Ifc4::IfcRelServicesBuildings,
		OpenInfraPlatform::Ifc4::IfcRelSpaceBoundary,
		OpenInfraPlatform::Ifc4::IfcRelSpaceBoundary1stLevel,
		OpenInfraPlatform::Ifc4::IfcRelSpaceBoundary2ndLevel,
		OpenInfraPlatform::Ifc4::IfcRelVoidsElement,
		OpenInfraPlatform::Ifc4::IfcReparametrisedCompositeCurveSegment,
		OpenInfraPlatform::Ifc4::IfcRepresentation,
		OpenInfraPlatform::Ifc4::IfcRepresentationContext,
		OpenInfraPlatform::Ifc4::IfcRepresentationItem,
		OpenInfraPlatform::Ifc4::IfcRepresentationMap,
		OpenInfraPlatform::Ifc4::IfcResource,
		OpenInfraPlatform::Ifc4::IfcResourceApprovalRelationship,
		OpenInfraPlatform::Ifc4::IfcResourceConstraintRelationship,
		OpenInfraPlatform::Ifc4::IfcResourceLevelRelationship,
		OpenInfraPlatform::Ifc4::IfcResourceObjectSelect,
		OpenInfraPlatform::Ifc4::IfcResourceSelect,
		OpenInfraPlatform::Ifc4::IfcResourceTime,
		OpenInfraPlatform::Ifc4::IfcRevolvedAreaSolid,
		OpenInfraPlatform::Ifc4::IfcRevolvedAreaSolidTapered,
		OpenInfraPlatform::Ifc4::IfcRightCircularCone,
		OpenInfraPlatform::Ifc4::IfcRightCircularCylinder,
		OpenInfraPlatform::Ifc4::IfcRoleEnum,
		OpenInfraPlatform::Ifc4::IfcRoof,
		OpenInfraPlatform::Ifc4::IfcRoofType,
		OpenInfraPlatform::Ifc4::IfcRoofTypeEnum,
		OpenInfraPlatform::Ifc4::IfcRoot,
		OpenInfraPlatform::Ifc4::IfcRotationalFrequencyMeasure,
		OpenInfraPlatform::Ifc4::IfcRotationalMassMeasure,
		OpenInfraPlatform::Ifc4::IfcRotationalStiffnessMeasure,
		OpenInfraPlatform::Ifc4::IfcRotationalStiffnessSelect,
		OpenInfraPlatform::Ifc4::IfcRoundedRectangleProfileDef,
		OpenInfraPlatform::Ifc4::IfcSanitaryTerminal,
		OpenInfraPlatform::Ifc4::IfcSanitaryTerminalType,
		OpenInfraPlatform::Ifc4::IfcSanitaryTerminalTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSchedulingTime,
		OpenInfraPlatform::Ifc4::IfcSectionalAreaIntegralMeasure,
		OpenInfraPlatform::Ifc4::IfcSectionedSpine,
		OpenInfraPlatform::Ifc4::IfcSectionModulusMeasure,
		OpenInfraPlatform::Ifc4::IfcSectionProperties,
		OpenInfraPlatform::Ifc4::IfcSectionReinforcementProperties,
		OpenInfraPlatform::Ifc4::IfcSectionTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSegmentIndexSelect,
		OpenInfraPlatform::Ifc4::IfcSensor,
		OpenInfraPlatform::Ifc4::IfcSensorType,
		OpenInfraPlatform::Ifc4::IfcSensorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSequenceEnum,
		OpenInfraPlatform::Ifc4::IfcShadingDevice,
		OpenInfraPlatform::Ifc4::IfcShadingDeviceType,
		OpenInfraPlatform::Ifc4::IfcShadingDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcShapeAspect,
		OpenInfraPlatform::Ifc4::IfcShapeModel,
		OpenInfraPlatform::Ifc4::IfcShapeRepresentation,
		OpenInfraPlatform::Ifc4::IfcShearModulusMeasure,
		OpenInfraPlatform::Ifc4::IfcShell,
		OpenInfraPlatform::Ifc4::IfcShellBasedSurfaceModel,
		OpenInfraPlatform::Ifc4::IfcSimpleProperty,
		OpenInfraPlatform::Ifc4::IfcSimplePropertyTemplate,
		OpenInfraPlatform::Ifc4::IfcSimplePropertyTemplateTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSimpleValue,
		OpenInfraPlatform::Ifc4::IfcSIPrefix,
		OpenInfraPlatform::Ifc4::IfcSite,
		OpenInfraPlatform::Ifc4::IfcSIUnit,
		OpenInfraPlatform::Ifc4::IfcSIUnitName,
		OpenInfraPlatform::Ifc4::IfcSizeSelect,
		OpenInfraPlatform::Ifc4::IfcSlab,
		OpenInfraPlatform::Ifc4::IfcSlabElementedCase,
		OpenInfraPlatform::Ifc4::IfcSlabStandardCase,
		OpenInfraPlatform::Ifc4::IfcSlabType,
		OpenInfraPlatform::Ifc4::IfcSlabTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSlippageConnectionCondition,
		OpenInfraPlatform::Ifc4::IfcSolarDevice,
		OpenInfraPlatform::Ifc4::IfcSolarDeviceType,
		OpenInfraPlatform::Ifc4::IfcSolarDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSolidAngleMeasure,
		OpenInfraPlatform::Ifc4::IfcSolidModel,
		OpenInfraPlatform::Ifc4::IfcSolidOrShell,
		OpenInfraPlatform::Ifc4::IfcSoundPowerLevelMeasure,
		OpenInfraPlatform::Ifc4::IfcSoundPowerMeasure,
		OpenInfraPlatform::Ifc4::IfcSoundPressureLevelMeasure,
		OpenInfraPlatform::Ifc4::IfcSoundPressureMeasure,
		OpenInfraPlatform::Ifc4::IfcSpace,
		OpenInfraPlatform::Ifc4::IfcSpaceBoundarySelect,
		OpenInfraPlatform::Ifc4::IfcSpaceHeater,
		OpenInfraPlatform::Ifc4::IfcSpaceHeaterType,
		OpenInfraPlatform::Ifc4::IfcSpaceHeaterTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSpaceType,
		OpenInfraPlatform::Ifc4::IfcSpaceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSpatialElement,
		OpenInfraPlatform::Ifc4::IfcSpatialElementType,
		OpenInfraPlatform::Ifc4::IfcSpatialStructureElement,
		OpenInfraPlatform::Ifc4::IfcSpatialStructureElementType,
		OpenInfraPlatform::Ifc4::IfcSpatialZone,
		OpenInfraPlatform::Ifc4::IfcSpatialZoneType,
		OpenInfraPlatform::Ifc4::IfcSpatialZoneTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSpecificHeatCapacityMeasure,
		OpenInfraPlatform::Ifc4::IfcSpecularExponent,
		OpenInfraPlatform::Ifc4::IfcSpecularHighlightSelect,
		OpenInfraPlatform::Ifc4::IfcSpecularRoughness,
		OpenInfraPlatform::Ifc4::IfcSphere,
		OpenInfraPlatform::Ifc4::IfcStackTerminal,
		OpenInfraPlatform::Ifc4::IfcStackTerminalType,
		OpenInfraPlatform::Ifc4::IfcStackTerminalTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStair,
		OpenInfraPlatform::Ifc4::IfcStairFlight,
		OpenInfraPlatform::Ifc4::IfcStairFlightType,
		OpenInfraPlatform::Ifc4::IfcStairFlightTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStairType,
		OpenInfraPlatform::Ifc4::IfcStairTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStateEnum,
		OpenInfraPlatform::Ifc4::IfcStrippedOptional,
		OpenInfraPlatform::Ifc4::IfcStructuralAction,
		OpenInfraPlatform::Ifc4::IfcStructuralActivity,
		OpenInfraPlatform::Ifc4::IfcStructuralActivityAssignmentSelect,
		OpenInfraPlatform::Ifc4::IfcStructuralAnalysisModel,
		OpenInfraPlatform::Ifc4::IfcStructuralConnection,
		OpenInfraPlatform::Ifc4::IfcStructuralConnectionCondition,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveAction,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveActivityTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveConnection,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveMember,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveMemberTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveMemberVarying,
		OpenInfraPlatform::Ifc4::IfcStructuralCurveReaction,
		OpenInfraPlatform::Ifc4::IfcStructuralItem,
		OpenInfraPlatform::Ifc4::IfcStructuralLinearAction,
		OpenInfraPlatform::Ifc4::IfcStructuralLoad,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadCase,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadConfiguration,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadGroup,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadLinearForce,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadOrResult,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadPlanarForce,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadSingleDisplacement,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadSingleDisplacementDistortion,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadSingleForce,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadSingleForceWarping,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadStatic,
		OpenInfraPlatform::Ifc4::IfcStructuralLoadTemperature,
		OpenInfraPlatform::Ifc4::IfcStructuralMember,
		OpenInfraPlatform::Ifc4::IfcStructuralPlanarAction,
		OpenInfraPlatform::Ifc4::IfcStructuralPointAction,
		OpenInfraPlatform::Ifc4::IfcStructuralPointConnection,
		OpenInfraPlatform::Ifc4::IfcStructuralPointReaction,
		OpenInfraPlatform::Ifc4::IfcStructuralReaction,
		OpenInfraPlatform::Ifc4::IfcStructuralResultGroup,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceAction,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceActivityTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceConnection,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceMember,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceMemberTypeEnum,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceMemberVarying,
		OpenInfraPlatform::Ifc4::IfcStructuralSurfaceReaction,
		OpenInfraPlatform::Ifc4::IfcStyleAssignmentSelect,
		OpenInfraPlatform::Ifc4::IfcStyledItem,
		OpenInfraPlatform::Ifc4::IfcStyledRepresentation,
		OpenInfraPlatform::Ifc4::IfcStyleModel,
		OpenInfraPlatform::Ifc4::IfcSubContractResource,
		OpenInfraPlatform::Ifc4::IfcSubContractResourceType,
		OpenInfraPlatform::Ifc4::IfcSubContractResourceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSubedge,
		OpenInfraPlatform::Ifc4::IfcSurface,
		OpenInfraPlatform::Ifc4::IfcSurfaceCurveSweptAreaSolid,
		OpenInfraPlatform::Ifc4::IfcSurfaceFeature,
		OpenInfraPlatform::Ifc4::IfcSurfaceFeatureTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSurfaceOfLinearExtrusion,
		OpenInfraPlatform::Ifc4::IfcSurfaceOfRevolution,
		OpenInfraPlatform::Ifc4::IfcSurfaceOrFaceSurface,
		OpenInfraPlatform::Ifc4::IfcSurfaceReinforcementArea,
		OpenInfraPlatform::Ifc4::IfcSurfaceSide,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyle,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleElementSelect,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleLighting,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleRefraction,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleRendering,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleShading,
		OpenInfraPlatform::Ifc4::IfcSurfaceStyleWithTextures,
		OpenInfraPlatform::Ifc4::IfcSurfaceTexture,
		OpenInfraPlatform::Ifc4::IfcSweptAreaSolid,
		OpenInfraPlatform::Ifc4::IfcSweptDiskSolid,
		OpenInfraPlatform::Ifc4::IfcSweptDiskSolidPolygonal,
		OpenInfraPlatform::Ifc4::IfcSweptSurface,
		OpenInfraPlatform::Ifc4::IfcSwitchingDevice,
		OpenInfraPlatform::Ifc4::IfcSwitchingDeviceType,
		OpenInfraPlatform::Ifc4::IfcSwitchingDeviceTypeEnum,
		OpenInfraPlatform::Ifc4::IfcSystem,
		OpenInfraPlatform::Ifc4::IfcSystemFurnitureElement,
		OpenInfraPlatform::Ifc4::IfcSystemFurnitureElementType,
		OpenInfraPlatform::Ifc4::IfcSystemFurnitureElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTable,
		OpenInfraPlatform::Ifc4::IfcTableColumn,
		OpenInfraPlatform::Ifc4::IfcTableRow,
		OpenInfraPlatform::Ifc4::IfcTank,
		OpenInfraPlatform::Ifc4::IfcTankType,
		OpenInfraPlatform::Ifc4::IfcTankTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTask,
		OpenInfraPlatform::Ifc4::IfcTaskDurationEnum,
		OpenInfraPlatform::Ifc4::IfcTaskTime,
		OpenInfraPlatform::Ifc4::IfcTaskTimeRecurring,
		OpenInfraPlatform::Ifc4::IfcTaskType,
		OpenInfraPlatform::Ifc4::IfcTaskTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTelecomAddress,
		OpenInfraPlatform::Ifc4::IfcTemperatureGradientMeasure,
		OpenInfraPlatform::Ifc4::IfcTemperatureRateOfChangeMeasure,
		OpenInfraPlatform::Ifc4::IfcTendon,
		OpenInfraPlatform::Ifc4::IfcTendonAnchor,
		OpenInfraPlatform::Ifc4::IfcTendonAnchorType,
		OpenInfraPlatform::Ifc4::IfcTendonAnchorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTendonType,
		OpenInfraPlatform::Ifc4::IfcTendonTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTessellatedFaceSet,
		OpenInfraPlatform::Ifc4::IfcTessellatedItem,
		OpenInfraPlatform::Ifc4::IfcText,
		OpenInfraPlatform::Ifc4::IfcTextAlignment,
		OpenInfraPlatform::Ifc4::IfcTextDecoration,
		OpenInfraPlatform::Ifc4::IfcTextFontName,
		OpenInfraPlatform::Ifc4::IfcTextFontSelect,
		OpenInfraPlatform::Ifc4::IfcTextLiteral,
		OpenInfraPlatform::Ifc4::IfcTextLiteralWithExtent,
		OpenInfraPlatform::Ifc4::IfcTextPath,
		OpenInfraPlatform::Ifc4::IfcTextStyle,
		OpenInfraPlatform::Ifc4::IfcTextStyleFontModel,
		OpenInfraPlatform::Ifc4::IfcTextStyleForDefinedFont,
		OpenInfraPlatform::Ifc4::IfcTextStyleTextModel,
		OpenInfraPlatform::Ifc4::IfcTextTransformation,
		OpenInfraPlatform::Ifc4::IfcTextureCoordinate,
		OpenInfraPlatform::Ifc4::IfcTextureCoordinateGenerator,
		OpenInfraPlatform::Ifc4::IfcTextureMap,
		OpenInfraPlatform::Ifc4::IfcTextureVertex,
		OpenInfraPlatform::Ifc4::IfcTextureVertexList,
		OpenInfraPlatform::Ifc4::IfcThermalAdmittanceMeasure,
		OpenInfraPlatform::Ifc4::IfcThermalConductivityMeasure,
		OpenInfraPlatform::Ifc4::IfcThermalExpansionCoefficientMeasure,
		OpenInfraPlatform::Ifc4::IfcThermalResistanceMeasure,
		OpenInfraPlatform::Ifc4::IfcThermalTransmittanceMeasure,
		OpenInfraPlatform::Ifc4::IfcThermodynamicTemperatureMeasure,
		OpenInfraPlatform::Ifc4::IfcTime,
		OpenInfraPlatform::Ifc4::IfcTimeMeasure,
		OpenInfraPlatform::Ifc4::IfcTimeOrRatioSelect,
		OpenInfraPlatform::Ifc4::IfcTimePeriod,
		OpenInfraPlatform::Ifc4::IfcTimeSeries,
		OpenInfraPlatform::Ifc4::IfcTimeSeriesDataTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTimeSeriesValue,
		OpenInfraPlatform::Ifc4::IfcTimeStamp,
		OpenInfraPlatform::Ifc4::IfcTopologicalRepresentationItem,
		OpenInfraPlatform::Ifc4::IfcTopologyRepresentation,
		OpenInfraPlatform::Ifc4::IfcTorqueMeasure,
		OpenInfraPlatform::Ifc4::IfcTransformer,
		OpenInfraPlatform::Ifc4::IfcTransformerType,
		OpenInfraPlatform::Ifc4::IfcTransformerTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTransitionCode,
		OpenInfraPlatform::Ifc4::IfcTranslationalStiffnessSelect,
		OpenInfraPlatform::Ifc4::IfcTransportElement,
		OpenInfraPlatform::Ifc4::IfcTransportElementType,
		OpenInfraPlatform::Ifc4::IfcTransportElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTrapeziumProfileDef,
		OpenInfraPlatform::Ifc4::IfcTriangulatedFaceSet,
		OpenInfraPlatform::Ifc4::IfcTrimmedCurve,
		OpenInfraPlatform::Ifc4::IfcTrimmingPreference,
		OpenInfraPlatform::Ifc4::IfcTrimmingSelect,
		OpenInfraPlatform::Ifc4::IfcTShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcTubeBundle,
		OpenInfraPlatform::Ifc4::IfcTubeBundleType,
		OpenInfraPlatform::Ifc4::IfcTubeBundleTypeEnum,
		OpenInfraPlatform::Ifc4::IfcTypeObject,
		OpenInfraPlatform::Ifc4::IfcTypeProcess,
		OpenInfraPlatform::Ifc4::IfcTypeProduct,
		OpenInfraPlatform::Ifc4::IfcTypeResource,
		OpenInfraPlatform::Ifc4::IfcUnit,
		OpenInfraPlatform::Ifc4::IfcUnitaryControlElement,
		OpenInfraPlatform::Ifc4::IfcUnitaryControlElementType,
		OpenInfraPlatform::Ifc4::IfcUnitaryControlElementTypeEnum,
		OpenInfraPlatform::Ifc4::IfcUnitaryEquipment,
		OpenInfraPlatform::Ifc4::IfcUnitaryEquipmentType,
		OpenInfraPlatform::Ifc4::IfcUnitaryEquipmentTypeEnum,
		OpenInfraPlatform::Ifc4::IfcUnitAssignment,
		OpenInfraPlatform::Ifc4::IfcUnitEnum,
		OpenInfraPlatform::Ifc4::IfcURIReference,
		OpenInfraPlatform::Ifc4::IfcUShapeProfileDef,
		OpenInfraPlatform::Ifc4::IfcValue,
		OpenInfraPlatform::Ifc4::IfcValve,
		OpenInfraPlatform::Ifc4::IfcValveType,
		OpenInfraPlatform::Ifc4::IfcValveTypeEnum,
		OpenInfraPlatform::Ifc4::IfcVaporPermeabilityMeasure,
		OpenInfraPlatform::Ifc4::IfcVector,
		OpenInfraPlatform::Ifc4::IfcVectorOrDirection,
		OpenInfraPlatform::Ifc4::IfcVertex,
		OpenInfraPlatform::Ifc4::IfcVertexLoop,
		OpenInfraPlatform::Ifc4::IfcVertexPoint,
		OpenInfraPlatform::Ifc4::IfcVibrationIsolator,
		OpenInfraPlatform::Ifc4::IfcVibrationIsolatorType,
		OpenInfraPlatform::Ifc4::IfcVibrationIsolatorTypeEnum,
		OpenInfraPlatform::Ifc4::IfcVirtualElement,
		OpenInfraPlatform::Ifc4::IfcVirtualGridIntersection,
		OpenInfraPlatform::Ifc4::IfcVoidingFeature,
		OpenInfraPlatform::Ifc4::IfcVoidingFeatureTypeEnum,
		OpenInfraPlatform::Ifc4::IfcVolumeMeasure,
		OpenInfraPlatform::Ifc4::IfcVolumetricFlowRateMeasure,
		OpenInfraPlatform::Ifc4::IfcWall,
		OpenInfraPlatform::Ifc4::IfcWallElementedCase,
		OpenInfraPlatform::Ifc4::IfcWallStandardCase,
		OpenInfraPlatform::Ifc4::IfcWallType,
		OpenInfraPlatform::Ifc4::IfcWallTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWarpingConstantMeasure,
		OpenInfraPlatform::Ifc4::IfcWarpingMomentMeasure,
		OpenInfraPlatform::Ifc4::IfcWarpingStiffnessSelect,
		OpenInfraPlatform::Ifc4::IfcWasteTerminal,
		OpenInfraPlatform::Ifc4::IfcWasteTerminalType,
		OpenInfraPlatform::Ifc4::IfcWasteTerminalTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWindow,
		OpenInfraPlatform::Ifc4::IfcWindowLiningProperties,
		OpenInfraPlatform::Ifc4::IfcWindowPanelOperationEnum,
		OpenInfraPlatform::Ifc4::IfcWindowPanelPositionEnum,
		OpenInfraPlatform::Ifc4::IfcWindowPanelProperties,
		OpenInfraPlatform::Ifc4::IfcWindowStandardCase,
		OpenInfraPlatform::Ifc4::IfcWindowStyle,
		OpenInfraPlatform::Ifc4::IfcWindowStyleConstructionEnum,
		OpenInfraPlatform::Ifc4::IfcWindowStyleOperationEnum,
		OpenInfraPlatform::Ifc4::IfcWindowType,
		OpenInfraPlatform::Ifc4::IfcWindowTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWindowTypePartitioningEnum,
		OpenInfraPlatform::Ifc4::IfcWorkCalendar,
		OpenInfraPlatform::Ifc4::IfcWorkCalendarTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWorkControl,
		OpenInfraPlatform::Ifc4::IfcWorkPlan,
		OpenInfraPlatform::Ifc4::IfcWorkPlanTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWorkSchedule,
		OpenInfraPlatform::Ifc4::IfcWorkScheduleTypeEnum,
		OpenInfraPlatform::Ifc4::IfcWorkTime,
		OpenInfraPlatform::Ifc4::IfcZone,
		OpenInfraPlatform::Ifc4::IfcZShapeProfileDef
	>
	Ifc4EntityTypes;
}
