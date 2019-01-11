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

#pragma once

#include "EMTBasicIFC4X2_DRAFT_1EntityTypes.h"

namespace OpenInfraPlatform
{
	namespace IFC4X2_DRAFT_1
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
		class IfcAlignment;
		class IfcAlignment2DHorizontal;
		class IfcAlignment2DHorizontalSegment;
		class IfcAlignment2DSegment;
		class IfcAlignment2DVerSegCircularArc;
		class IfcAlignment2DVerSegLine;
		class IfcAlignment2DVerSegParabolicArc;
		class IfcAlignment2DVertical;
		class IfcAlignment2DVerticalSegment;
		class IfcAlignmentCurve;
		class IfcAlignmentTypeEnum;
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
		class IfcBearing;
		class IfcBearingType;
		class IfcBearingTypeDisplacementEnum;
		class IfcBearingTypeEnum;
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
		class IfcBridge;
		class IfcBridgePart;
		class IfcBridgePartTypeEnum;
		class IfcBridgeTypeEnum;
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
		class IfcCaissonFoundation;
		class IfcCaissonFoundationType;
		class IfcCaissonFoundationTypeEnum;
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
		class IfcCircularArcSegment2D;
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
		class IfcCurveSegment2D;
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
		class IfcDeepFoundation;
		class IfcDeepFoundationType;
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
		class IfcDistanceExpression;
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
		class IfcFacility;
		class IfcFacilityPart;
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
		class IfcIndexedPolygonalFace;
		class IfcIndexedPolygonalFaceWithVoids;
		class IfcIndexedTextureMap;
		class IfcIndexedTriangleTextureMap;
		class IfcInductanceMeasure;
		class IfcInteger;
		class IfcIntegerCountRateMeasure;
		class IfcInterceptor;
		class IfcInterceptorType;
		class IfcInterceptorTypeEnum;
		class IfcInternalOrExternalEnum;
		class IfcIntersectionCurve;
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
		class IfcLinearPlacement;
		class IfcLinearPositioningElement;
		class IfcLinearStiffnessMeasure;
		class IfcLinearVelocityMeasure;
		class IfcLineIndex;
		class IfcLineSegment2D;
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
		class IfcOffsetCurve;
		class IfcOffsetCurve2D;
		class IfcOffsetCurve3D;
		class IfcOffsetCurveByDistances;
		class IfcOpeningElement;
		class IfcOpeningElementTypeEnum;
		class IfcOpeningStandardCase;
		class IfcOpenShell;
		class IfcOrganization;
		class IfcOrganizationRelationship;
		class IfcOrientationExpression;
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
		class IfcPolygonalFaceSet;
		class IfcPolyline;
		class IfcPolyLoop;
		class IfcPort;
		class IfcPositioningElement;
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
		class IfcPreferredSurfaceCurveRepresentation;
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
		class IfcReferent;
		class IfcReferentTypeEnum;
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
		class IfcRelPositions;
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
		class IfcSeamCurve;
		class IfcSectionalAreaIntegralMeasure;
		class IfcSectionedSolid;
		class IfcSectionedSolidHorizontal;
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
		class IfcSphericalSurface;
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
		class IfcSurfaceCurve;
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
		class IfcTendonConduit;
		class IfcTendonConduitType;
		class IfcTendonConduitTypeEnum;
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
		class IfcToroidalSurface;
		class IfcTorqueMeasure;
		class IfcTransformer;
		class IfcTransformerType;
		class IfcTransformerTypeEnum;
		class IfcTransitionCode;
		class IfcTransitionCurveSegment2D;
		class IfcTransitionCurveType;
		class IfcTranslationalStiffnessSelect;
		class IfcTransportElement;
		class IfcTransportElementType;
		class IfcTransportElementTypeEnum;
		class IfcTrapeziumProfileDef;
		class IfcTriangulatedFaceSet;
		class IfcTriangulatedIrregularNetwork;
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
		class IfcVibrationDamper;
		class IfcVibrationDamperType;
		class IfcVibrationDamperTypeEnum;
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
	typedef BasicIFC4X2_DRAFT_1EntityTypes<
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAbsorbedDoseMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAccelerationMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActionRequest,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActionRequestTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActionSourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActionTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActorRole,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActorSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActuator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActuatorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcActuatorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAddress,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAddressTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAdvancedBrep,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAdvancedBrepWithVoids,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAdvancedFace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminalBox,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminalBoxType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminalBoxTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirToAirHeatRecovery,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirToAirHeatRecoveryType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAirToAirHeatRecoveryTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlarm,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlarmType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlarmTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DHorizontal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DHorizontalSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DVerSegCircularArc,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DVerSegLine,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DVerSegParabolicArc,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DVertical,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignment2DVerticalSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignmentCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAlignmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAmountOfSubstanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAnalysisModelTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAnalysisTheoryTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAngularVelocityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAnnotation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAnnotationFillArea,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcApplication,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAppliedValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAppliedValueSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcApproval,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcApprovalRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcArbitraryClosedProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcArbitraryOpenProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcArbitraryProfileDefWithVoids,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcArcIndex,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAreaDensityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAreaMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcArithmeticOperatorEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAssemblyPlaceEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAsset,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAsymmetricIShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAudioVisualAppliance,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAudioVisualApplianceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAudioVisualApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAxis1Placement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAxis2Placement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAxis2Placement2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcAxis2Placement3D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBeam,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBeamStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBeamType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBeamTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBearing,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBearingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBearingTypeDisplacementEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBearingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBenchmarkEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBendingParameterSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBinary,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBlobTexture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBlock,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoiler,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoilerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoilerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoolean,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBooleanClippingResult,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBooleanOperand,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBooleanOperator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBooleanResult,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryEdgeCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryFaceCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryNodeCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundaryNodeConditionWarping,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundedCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundedSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoundingBox,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoxAlignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBoxedHalfSpace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBridge,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBridgePart,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBridgePartTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBridgeTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineCurveForm,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineCurveWithKnots,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineSurfaceForm,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBSplineSurfaceWithKnots,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuilding,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementPart,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementPartType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementPartTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementProxy,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementProxyType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementProxyTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingStorey,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingSystem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBuildingSystemTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBurner,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBurnerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcBurnerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierFitting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierFittingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierSegmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableCarrierSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableFitting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableFittingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableSegmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCableSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCaissonFoundation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCaissonFoundationType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCaissonFoundationTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCardinalPointReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianPoint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianPointList,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianPointList2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianPointList3D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianTransformationOperator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianTransformationOperator2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianTransformationOperator2DnonUniform,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianTransformationOperator3D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCartesianTransformationOperator3DnonUniform,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCenterLineProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChangeActionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChiller,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChillerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChillerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChimney,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChimneyType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcChimneyTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCircle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCircleHollowProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCircleProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCircularArcSegment2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCivilElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCivilElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcClassification,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcClassificationReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcClassificationReferenceSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcClassificationSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcClosedShell,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoil,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoilType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoilTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColour,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColourOrFactor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColourRgb,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColourRgbList,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColourSpecification,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColumn,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColumnStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColumnType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcColumnTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCommunicationsAppliance,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCommunicationsApplianceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCommunicationsApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcComplexNumber,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcComplexProperty,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcComplexPropertyTemplate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcComplexPropertyTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompositeCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompositeCurveOnSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompositeCurveSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompositeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompoundPlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompressor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompressorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCompressorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCondenser,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCondenserType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCondenserTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConic,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectedFaceSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionCurveGeometry,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionGeometry,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionPointEccentricity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionPointGeometry,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionSurfaceGeometry,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConnectionVolumeGeometry,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstraint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstraintEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionEquipmentResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionEquipmentResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionEquipmentResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionMaterialResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionMaterialResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionMaterialResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionProductResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionProductResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionProductResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConstructionResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcContext,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcContextDependentMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcContextDependentUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcControl,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcController,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcControllerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcControllerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConversionBasedUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcConversionBasedUnitWithOffset,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCooledBeam,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCooledBeamType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCooledBeamTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoolingTower,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoolingTowerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoolingTowerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoordinateOperation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoordinateReferenceSystem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoordinateReferenceSystemSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCostItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCostItemTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCostSchedule,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCostScheduleTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCostValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCountMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCovering,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoveringType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCoveringTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCrewResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCrewResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCrewResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCsgPrimitive3D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCsgSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCsgSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurrencyRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurtainWall,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurtainWallType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurtainWallTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurvatureMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveBoundedPlane,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveBoundedSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveFontOrScaledCurveFontSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveInterpolationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveOnSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveOrEdgeCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveSegment2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveStyleFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveStyleFontAndScaling,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveStyleFontPattern,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCurveStyleFontSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcCylindricalSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDamper,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDamperType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDamperTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDataOriginEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDateTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDayInMonthNumber,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDayInWeekNumber,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDeepFoundation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDeepFoundationType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDefinitionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDerivedMeasureValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDerivedProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDerivedUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDerivedUnitElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDerivedUnitEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDescriptiveMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDimensionalExponents,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDimensionCount,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDirection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDirectionSenseEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDiscreteAccessory,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDiscreteAccessoryType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDiscreteAccessoryTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistanceExpression,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionChamberElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionChamberElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionChamberElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionCircuit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionControlElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionControlElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionFlowElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionFlowElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionPort,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionPortTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionSystem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDistributionSystemEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentConfidentialityEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentInformation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentInformationRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDocumentStatusEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorLiningProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorPanelOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorPanelPositionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorPanelProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorStyleConstructionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorStyleOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoorTypeOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDoseEquivalentMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDraughtingPreDefinedColour,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDraughtingPreDefinedCurveFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctFitting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctFittingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSegmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSilencer,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSilencerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuctSilencerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDuration,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcDynamicViscosityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEdge,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEdgeCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEdgeLoop,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricAppliance,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricApplianceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricCapacitanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricChargeMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricConductanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricCurrentMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricDistributionBoard,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricDistributionBoardType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricDistributionBoardTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricFlowStorageDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricFlowStorageDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricFlowStorageDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricGenerator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricGeneratorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricGeneratorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricMotor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricMotorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricMotorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricResistanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricTimeControl,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricTimeControlType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricTimeControlTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElectricVoltageMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementarySurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementAssembly,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementAssemblyType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementAssemblyTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementComponent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementComponentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementCompositionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementQuantity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEllipse,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEllipseProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEnergyConversionDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEnergyConversionDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEnergyMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEngine,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEngineType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEngineTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporativeCooler,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporativeCoolerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporativeCoolerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporatorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvaporatorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEvent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEventTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEventTriggerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEventType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcEventTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExtendedProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalInformation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternallyDefinedHatchStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternallyDefinedSurfaceStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternallyDefinedTextFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalReferenceRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalSpatialElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalSpatialElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExternalSpatialStructureElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExtrudedAreaSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcExtrudedAreaSolidTapered,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFaceBasedSurfaceModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFaceBound,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFaceOuterBound,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFaceSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFacetedBrep,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFacetedBrepWithVoids,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFacility,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFacilityPart,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFailureConnectionCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFan,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFanType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFanTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFastener,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFastenerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFastenerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFeatureElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFeatureElementAddition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFeatureElementSubtraction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFillAreaStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFillAreaStyleHatching,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFillAreaStyleTiles,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFillStyleSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFilter,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFilterType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFilterTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFireSuppressionTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFireSuppressionTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFireSuppressionTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFixedReferenceSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowController,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowControllerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowDirectionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowFitting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowFittingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowInstrument,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowInstrumentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowInstrumentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowMeter,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowMeterType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowMeterTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowMovingDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowMovingDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowSegmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowStorageDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowStorageDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowTreatmentDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFlowTreatmentDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFontStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFontVariant,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFontWeight,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFooting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFootingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFootingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcForceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFrequencyMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFurnishingElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFurnishingElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFurniture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFurnitureType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcFurnitureTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeographicElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeographicElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeographicElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricCurveSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricProjectionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricRepresentationContext,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricRepresentationItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricRepresentationSubContext,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGeometricSetSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGloballyUniqueId,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGlobalOrLocalEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGrid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGridAxis,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGridPlacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGridPlacementDirectionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGridTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcGroup,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHalfSpaceSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHatchLineDistanceSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHeatExchanger,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHeatExchangerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHeatExchangerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHeatFluxDensityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHeatingValueMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHumidifier,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHumidifierType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcHumidifierTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIdentifier,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIlluminanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcImageTexture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedColourMap,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedPolyCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedPolygonalFace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedPolygonalFaceWithVoids,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedTextureMap,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIndexedTriangleTextureMap,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInductanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInteger,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIntegerCountRateMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInterceptor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInterceptorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInterceptorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInternalOrExternalEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIntersectionCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInventory,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcInventoryTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIonConcentrationMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIrregularTimeSeries,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIrregularTimeSeriesValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcIsothermalMoistureCapacityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcJunctionBox,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcJunctionBoxType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcJunctionBoxTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcKinematicViscosityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcKnotType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLabel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLaborResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLaborResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLaborResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLagTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLamp,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLampType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLampTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLanguageId,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLayeredItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLayerSetDirectionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLengthMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLibraryInformation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLibraryReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLibrarySelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightDistributionCurveEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightDistributionData,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightDistributionDataSourceSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightEmissionSourceEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightFixture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightFixtureType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightFixtureTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightIntensityDistribution,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSourceAmbient,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSourceDirectional,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSourceGoniometric,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSourcePositional,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLightSourceSpot,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLine,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearForceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearMomentMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearPlacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearPositioningElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearStiffnessMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLinearVelocityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLineIndex,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLineSegment2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLoadGroupTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLocalPlacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLogical,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLogicalOperatorEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLoop,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLuminousFluxMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLuminousIntensityDistributionMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcLuminousIntensityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMagneticFluxDensityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMagneticFluxMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcManifoldSolidBrep,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMapConversion,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMappedItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMassDensityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMassFlowRateMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMassMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMassPerLengthMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterial,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialClassificationRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialConstituent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialConstituentSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialDefinitionRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialLayer,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialLayerSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialLayerSetUsage,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialLayerWithOffsets,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialList,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProfile,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProfileSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProfileSetUsage,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProfileSetUsageTapering,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProfileWithOffsets,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMaterialUsageDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMeasureValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMeasureWithUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMechanicalFastener,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMechanicalFastenerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMechanicalFastenerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMedicalDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMedicalDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMedicalDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMember,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMemberStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMemberType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMetric,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMetricValueSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMirroredProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfElasticityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfLinearSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfRotationalSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfRotationalSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcModulusOfTranslationalSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMoistureDiffusivityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMolecularWeightMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMomentOfInertiaMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMonetaryMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMonetaryUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMonthInYearNumber,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMotorConnection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMotorConnectionType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcMotorConnectionTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcNamedUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcNonNegativeLengthMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcNormalisedRatioMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcNullStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcNumericMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObject,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjectDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjective,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjectiveEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjectPlacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjectReferenceSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcObjectTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOccupant,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOccupantTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOffsetCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOffsetCurve2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOffsetCurve3D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOffsetCurveByDistances,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOpeningElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOpeningElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOpeningStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOpenShell,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOrganization,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOrganizationRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOrientationExpression,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOrientedEdge,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOuterBoundaryCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOutlet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOutletType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOutletTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcOwnerHistory,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcParameterizedProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcParameterValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPath,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPcurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPerformanceHistory,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPerformanceHistoryTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPermeableCoveringOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPermeableCoveringProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPermit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPermitTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPerson,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPersonAndOrganization,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPHMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPhysicalComplexQuantity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPhysicalOrVirtualEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPhysicalQuantity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPhysicalSimpleQuantity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPile,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPileConstructionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPileType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPileTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeFitting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeFittingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeSegmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPipeSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPixelTexture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlanarBox,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlanarExtent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlanarForceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlane,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlateStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlateType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPlateTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPoint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPointOnCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPointOnSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPointOrVertexPoint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPolygonalBoundedHalfSpace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPolygonalFaceSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPolyline,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPolyLoop,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPort,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPositioningElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPositiveInteger,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPositiveLengthMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPositivePlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPositiveRatioMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPostalAddress,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPowerMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedColour,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedCurveFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedPropertySet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreDefinedTextFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPreferredSurfaceCurveRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentableText,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationLayerAssignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationLayerWithStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationStyleAssignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPresentationStyleSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPressureMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProcedure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProcedureType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProcedureTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProcess,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProcessSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProduct,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProductDefinitionShape,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProductRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProductRepresentationSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProductSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProfileProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProfileTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProject,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectedCRS,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectedOrTrueLengthEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectionElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectionElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectLibrary,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectOrder,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProjectOrderTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProperty,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyAbstraction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyBoundedValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyDependencyRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyEnumeratedValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyEnumeration,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyListValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyReferenceValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySetDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySetDefinitionSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySetDefinitionSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySetTemplate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySetTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertySingleValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyTableValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyTemplate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPropertyTemplateDefinition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDeviceTrippingUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDeviceTrippingUnitType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDeviceTrippingUnitTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProtectiveDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcProxy,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPump,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPumpType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcPumpTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityArea,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityCount,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityLength,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantitySet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityVolume,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcQuantityWeight,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRadioActivityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRailing,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRailingType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRailingTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRamp,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRampFlight,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRampFlightType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRampFlightTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRampType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRampTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRatioMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRationalBSplineCurveWithKnots,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRationalBSplineSurfaceWithKnots,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRectangleHollowProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRectangleProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRectangularPyramid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRectangularTrimmedSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRecurrencePattern,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRecurrenceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReferent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReferentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReflectanceMethodEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRegularTimeSeries,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcementBarProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcementDefinitionProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingBar,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingBarRoleEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingBarSurfaceEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingBarType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingBarTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingMesh,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingMeshType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReinforcingMeshTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAggregates,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssigns,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToActor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToControl,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToGroup,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToGroupByFactor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToProcess,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToProduct,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssignsToResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociates,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesApproval,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesClassification,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesConstraint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesDocument,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesLibrary,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelAssociatesMaterial,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnects,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsPathElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsPorts,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsPortToElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsStructuralActivity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsStructuralMember,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsWithEccentricity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelConnectsWithRealizingElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelContainedInSpatialStructure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelCoversBldgElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelCoversSpaces,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDeclares,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDecomposes,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDefines,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDefinesByObject,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDefinesByProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDefinesByTemplate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelDefinesByType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelFillsElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelFlowControlElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelInterferesElements,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelNests,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelPositions,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelProjectsElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelReferencedInSpatialStructure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelSequence,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelServicesBuildings,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelSpaceBoundary,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelSpaceBoundary1stLevel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelSpaceBoundary2ndLevel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRelVoidsElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcReparametrisedCompositeCurveSegment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRepresentationContext,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRepresentationItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRepresentationMap,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceApprovalRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceConstraintRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceLevelRelationship,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceObjectSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcResourceTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRevolvedAreaSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRevolvedAreaSolidTapered,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRightCircularCone,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRightCircularCylinder,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoleEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoof,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoofType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoofTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoot,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRotationalFrequencyMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRotationalMassMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRotationalStiffnessMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRotationalStiffnessSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcRoundedRectangleProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSanitaryTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSanitaryTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSanitaryTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSchedulingTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSeamCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionalAreaIntegralMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionedSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionedSolidHorizontal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionedSpine,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionModulusMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionReinforcementProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSectionTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSegmentIndexSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSensor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSensorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSensorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSequenceEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShadingDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShadingDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShadingDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShapeAspect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShapeModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShapeRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShearModulusMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShell,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcShellBasedSurfaceModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSimpleProperty,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSimplePropertyTemplate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSimplePropertyTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSimpleValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSIPrefix,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSite,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSIUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSIUnitName,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSizeSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlab,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlabElementedCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlabStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlabType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlabTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSlippageConnectionCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolarDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolarDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolarDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolidAngleMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolidModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSolidOrShell,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSoundPowerLevelMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSoundPowerMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSoundPressureLevelMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSoundPressureMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpace,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceBoundarySelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceHeater,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceHeaterType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceHeaterTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpaceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialStructureElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialStructureElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialZone,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialZoneType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpatialZoneTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpecificHeatCapacityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpecularExponent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpecularHighlightSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSpecularRoughness,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSphere,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSphericalSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStackTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStackTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStackTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStair,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStairFlight,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStairFlightType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStairFlightTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStairType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStairTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStateEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralActivity,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralActivityAssignmentSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralAnalysisModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralConnection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralConnectionCondition,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveActivityTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveConnection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveMember,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveMemberVarying,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralCurveReaction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLinearAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoad,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadConfiguration,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadGroup,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadLinearForce,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadOrResult,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadPlanarForce,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadSingleDisplacement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadSingleDisplacementDistortion,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadSingleForce,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadSingleForceWarping,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadStatic,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralLoadTemperature,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralMember,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralPlanarAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralPointAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralPointConnection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralPointReaction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralReaction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralResultGroup,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceAction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceActivityTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceConnection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceMember,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceMemberVarying,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStructuralSurfaceReaction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStyleAssignmentSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStyledItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStyledRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcStyleModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSubContractResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSubContractResourceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSubContractResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSubedge,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceCurveSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceFeature,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceFeatureTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceOfLinearExtrusion,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceOfRevolution,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceOrFaceSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceReinforcementArea,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceSide,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleElementSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleLighting,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleRefraction,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleRendering,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleShading,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceStyleWithTextures,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSurfaceTexture,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSweptDiskSolid,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSweptDiskSolidPolygonal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSweptSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSwitchingDevice,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSwitchingDeviceType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSwitchingDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSystem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSystemFurnitureElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSystemFurnitureElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcSystemFurnitureElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTable,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTableColumn,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTableRow,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTank,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTankType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTankTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTask,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTaskDurationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTaskTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTaskTimeRecurring,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTaskType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTaskTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTelecomAddress,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTemperatureGradientMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTemperatureRateOfChangeMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendon,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonAnchor,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonAnchorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonAnchorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonConduit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonConduitType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonConduitTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTendonTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTessellatedFaceSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTessellatedItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcText,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextAlignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextDecoration,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextFontName,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextFontSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextLiteral,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextLiteralWithExtent,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextPath,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextStyleFontModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextStyleForDefinedFont,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextStyleTextModel,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextTransformation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextureCoordinate,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextureCoordinateGenerator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextureMap,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextureVertex,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTextureVertexList,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermalAdmittanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermalConductivityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermalExpansionCoefficientMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermalResistanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermalTransmittanceMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcThermodynamicTemperatureMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeOrRatioSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimePeriod,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeSeries,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeSeriesDataTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeSeriesValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTimeStamp,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTopologicalRepresentationItem,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTopologyRepresentation,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcToroidalSurface,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTorqueMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransformer,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransformerType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransformerTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransitionCode,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransitionCurveSegment2D,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransitionCurveType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTranslationalStiffnessSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransportElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransportElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTransportElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTrapeziumProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTriangulatedFaceSet,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTriangulatedIrregularNetwork,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTrimmedCurve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTrimmingPreference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTrimmingSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTubeBundle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTubeBundleType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTubeBundleTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTypeObject,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTypeProcess,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTypeProduct,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcTypeResource,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnit,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryControlElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryControlElementType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryControlElementTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryEquipment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryEquipmentType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitaryEquipmentTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitAssignment,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUnitEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcURIReference,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcUShapeProfileDef,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcValue,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcValve,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcValveType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcValveTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVaporPermeabilityMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVector,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVectorOrDirection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVertex,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVertexLoop,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVertexPoint,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationDamper,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationDamperType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationDamperTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationIsolator,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationIsolatorType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVibrationIsolatorTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVirtualElement,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVirtualGridIntersection,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVoidingFeature,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVoidingFeatureTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVolumeMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcVolumetricFlowRateMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWall,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWallElementedCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWallStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWallType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWallTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWarpingConstantMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWarpingMomentMeasure,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWarpingStiffnessSelect,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWasteTerminal,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWasteTerminalType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWasteTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindow,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowLiningProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowPanelOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowPanelPositionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowPanelProperties,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowStandardCase,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowStyle,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowStyleConstructionEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowStyleOperationEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowType,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWindowTypePartitioningEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkCalendar,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkCalendarTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkControl,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkPlan,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkPlanTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkSchedule,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkScheduleTypeEnum,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcWorkTime,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcZone,
		OpenInfraPlatform::IFC4X2_DRAFT_1::IfcZShapeProfileDef
	>
	IFC4X2_DRAFT_1EntityTypes;
}
