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

#include "EMTBasicIFC4X2_BIM4ROADEntityTypes.h"

namespace OpenInfraPlatform
{
	namespace IFC4X2_BIM4ROAD
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
		class IfcCourse;
		class IfcCourseType;
		class IfcCourseTypeEnum;
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
		class IfcRoad;
		class IfcRoadPart;
		class IfcRoadPartTypeEnum;
		class IfcRoadTypeEnum;
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
	typedef BasicIFC4X2_BIM4ROADEntityTypes<
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAbsorbedDoseMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAccelerationMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActionRequest,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActionRequestTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActionSourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActionTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActorRole,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActorSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActuator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActuatorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcActuatorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAddress,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAddressTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAdvancedBrep,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAdvancedBrepWithVoids,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAdvancedFace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminalBox,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminalBoxType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminalBoxTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirToAirHeatRecovery,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirToAirHeatRecoveryType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAirToAirHeatRecoveryTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlarm,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlarmType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlarmTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DHorizontal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DHorizontalSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DVerSegCircularArc,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DVerSegLine,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DVerSegParabolicArc,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DVertical,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignment2DVerticalSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignmentCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAlignmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAmountOfSubstanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAnalysisModelTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAnalysisTheoryTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAngularVelocityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAnnotation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAnnotationFillArea,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcApplication,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAppliedValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAppliedValueSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcApproval,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcApprovalRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcArbitraryClosedProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcArbitraryOpenProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcArbitraryProfileDefWithVoids,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcArcIndex,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAreaDensityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAreaMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcArithmeticOperatorEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAssemblyPlaceEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAsset,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAsymmetricIShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAudioVisualAppliance,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAudioVisualApplianceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAudioVisualApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAxis1Placement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAxis2Placement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAxis2Placement2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcAxis2Placement3D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBeam,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBeamStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBeamType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBeamTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBearing,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBearingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBearingTypeDisplacementEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBearingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBenchmarkEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBendingParameterSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBinary,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBlobTexture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBlock,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoiler,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoilerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoilerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoolean,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBooleanClippingResult,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBooleanOperand,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBooleanOperator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBooleanResult,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryEdgeCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryFaceCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryNodeCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundaryNodeConditionWarping,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundedCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundedSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoundingBox,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoxAlignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBoxedHalfSpace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBridge,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBridgePart,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBridgePartTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBridgeTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineCurveForm,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineCurveWithKnots,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineSurfaceForm,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBSplineSurfaceWithKnots,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuilding,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementPart,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementPartType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementPartTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementProxy,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementProxyType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementProxyTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingStorey,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingSystem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBuildingSystemTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBurner,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBurnerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcBurnerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierFitting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierFittingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierSegmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableCarrierSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableFitting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableFittingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableSegmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCableSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCaissonFoundation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCaissonFoundationType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCaissonFoundationTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCardinalPointReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianPoint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianPointList,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianPointList2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianPointList3D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianTransformationOperator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianTransformationOperator2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianTransformationOperator2DnonUniform,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianTransformationOperator3D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCartesianTransformationOperator3DnonUniform,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCenterLineProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChangeActionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChiller,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChillerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChillerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChimney,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChimneyType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcChimneyTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCircle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCircleHollowProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCircleProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCircularArcSegment2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCivilElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCivilElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcClassification,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcClassificationReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcClassificationReferenceSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcClassificationSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcClosedShell,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoil,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoilType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoilTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColour,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColourOrFactor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColourRgb,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColourRgbList,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColourSpecification,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColumn,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColumnStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColumnType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcColumnTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCommunicationsAppliance,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCommunicationsApplianceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCommunicationsApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcComplexNumber,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcComplexProperty,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcComplexPropertyTemplate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcComplexPropertyTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompositeCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompositeCurveOnSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompositeCurveSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompositeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompoundPlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompressor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompressorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCompressorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCondenser,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCondenserType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCondenserTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConic,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectedFaceSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionCurveGeometry,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionGeometry,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionPointEccentricity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionPointGeometry,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionSurfaceGeometry,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConnectionVolumeGeometry,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstraint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstraintEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionEquipmentResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionEquipmentResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionEquipmentResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionMaterialResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionMaterialResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionMaterialResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionProductResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionProductResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionProductResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConstructionResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcContext,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcContextDependentMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcContextDependentUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcControl,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcController,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcControllerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcControllerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConversionBasedUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcConversionBasedUnitWithOffset,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCooledBeam,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCooledBeamType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCooledBeamTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoolingTower,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoolingTowerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoolingTowerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoordinateOperation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoordinateReferenceSystem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoordinateReferenceSystemSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCostItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCostItemTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCostSchedule,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCostScheduleTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCostValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCountMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCourse,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCourseType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCourseTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCovering,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoveringType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCoveringTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCrewResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCrewResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCrewResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCsgPrimitive3D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCsgSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCsgSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurrencyRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurtainWall,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurtainWallType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurtainWallTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurvatureMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveBoundedPlane,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveBoundedSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveFontOrScaledCurveFontSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveInterpolationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveOnSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveOrEdgeCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveSegment2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveStyleFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveStyleFontAndScaling,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveStyleFontPattern,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCurveStyleFontSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcCylindricalSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDamper,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDamperType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDamperTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDataOriginEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDateTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDayInMonthNumber,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDayInWeekNumber,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDeepFoundation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDeepFoundationType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDefinitionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDerivedMeasureValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDerivedProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDerivedUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDerivedUnitElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDerivedUnitEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDescriptiveMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDimensionalExponents,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDimensionCount,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDirection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDirectionSenseEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDiscreteAccessory,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDiscreteAccessoryType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDiscreteAccessoryTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistanceExpression,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionChamberElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionChamberElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionChamberElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionCircuit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionControlElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionControlElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionFlowElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionFlowElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionPort,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionPortTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionSystem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDistributionSystemEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentConfidentialityEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentInformation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentInformationRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDocumentStatusEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorLiningProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorPanelOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorPanelPositionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorPanelProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorStyleConstructionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorStyleOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoorTypeOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDoseEquivalentMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDraughtingPreDefinedColour,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDraughtingPreDefinedCurveFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctFitting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctFittingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSegmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSilencer,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSilencerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuctSilencerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDuration,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcDynamicViscosityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEdge,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEdgeCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEdgeLoop,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricAppliance,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricApplianceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricApplianceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricCapacitanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricChargeMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricConductanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricCurrentMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricDistributionBoard,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricDistributionBoardType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricDistributionBoardTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricFlowStorageDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricFlowStorageDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricFlowStorageDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricGenerator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricGeneratorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricGeneratorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricMotor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricMotorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricMotorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricResistanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricTimeControl,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricTimeControlType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricTimeControlTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElectricVoltageMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementarySurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementAssembly,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementAssemblyType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementAssemblyTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementComponent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementComponentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementCompositionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementQuantity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEllipse,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEllipseProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEnergyConversionDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEnergyConversionDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEnergyMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEngine,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEngineType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEngineTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporativeCooler,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporativeCoolerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporativeCoolerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporatorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvaporatorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEvent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEventTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEventTriggerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEventType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcEventTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExtendedProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalInformation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternallyDefinedHatchStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternallyDefinedSurfaceStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternallyDefinedTextFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalReferenceRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalSpatialElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalSpatialElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExternalSpatialStructureElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExtrudedAreaSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcExtrudedAreaSolidTapered,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFaceBasedSurfaceModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFaceBound,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFaceOuterBound,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFaceSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFacetedBrep,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFacetedBrepWithVoids,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFacility,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFacilityPart,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFailureConnectionCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFan,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFanType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFanTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFastener,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFastenerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFastenerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFeatureElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFeatureElementAddition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFeatureElementSubtraction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFillAreaStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFillAreaStyleHatching,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFillAreaStyleTiles,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFillStyleSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFilter,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFilterType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFilterTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFireSuppressionTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFireSuppressionTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFireSuppressionTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFixedReferenceSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowController,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowControllerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowDirectionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowFitting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowFittingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowInstrument,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowInstrumentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowInstrumentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowMeter,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowMeterType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowMeterTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowMovingDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowMovingDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowSegmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowStorageDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowStorageDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowTreatmentDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFlowTreatmentDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFontStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFontVariant,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFontWeight,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFooting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFootingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFootingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcForceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFrequencyMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFurnishingElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFurnishingElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFurniture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFurnitureType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcFurnitureTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeographicElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeographicElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeographicElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricCurveSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricProjectionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricRepresentationContext,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricRepresentationItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricRepresentationSubContext,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGeometricSetSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGloballyUniqueId,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGlobalOrLocalEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGrid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGridAxis,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGridPlacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGridPlacementDirectionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGridTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcGroup,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHalfSpaceSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHatchLineDistanceSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHeatExchanger,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHeatExchangerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHeatExchangerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHeatFluxDensityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHeatingValueMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHumidifier,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHumidifierType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcHumidifierTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIdentifier,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIlluminanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcImageTexture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedColourMap,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedPolyCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedPolygonalFace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedPolygonalFaceWithVoids,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedTextureMap,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIndexedTriangleTextureMap,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInductanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInteger,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIntegerCountRateMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInterceptor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInterceptorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInterceptorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInternalOrExternalEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIntersectionCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInventory,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcInventoryTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIonConcentrationMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIrregularTimeSeries,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIrregularTimeSeriesValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcIsothermalMoistureCapacityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcJunctionBox,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcJunctionBoxType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcJunctionBoxTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcKinematicViscosityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcKnotType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLabel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLaborResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLaborResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLaborResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLagTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLamp,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLampType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLampTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLanguageId,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLayeredItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLayerSetDirectionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLengthMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLibraryInformation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLibraryReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLibrarySelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightDistributionCurveEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightDistributionData,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightDistributionDataSourceSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightEmissionSourceEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightFixture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightFixtureType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightFixtureTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightIntensityDistribution,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSourceAmbient,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSourceDirectional,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSourceGoniometric,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSourcePositional,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLightSourceSpot,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLine,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearForceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearMomentMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearPlacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearPositioningElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearStiffnessMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLinearVelocityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLineIndex,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLineSegment2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLoadGroupTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLocalPlacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLogical,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLogicalOperatorEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLoop,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLuminousFluxMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLuminousIntensityDistributionMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcLuminousIntensityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMagneticFluxDensityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMagneticFluxMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcManifoldSolidBrep,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMapConversion,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMappedItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMassDensityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMassFlowRateMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMassMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMassPerLengthMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterial,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialClassificationRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialConstituent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialConstituentSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialDefinitionRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialLayer,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialLayerSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialLayerSetUsage,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialLayerWithOffsets,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialList,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProfile,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProfileSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProfileSetUsage,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProfileSetUsageTapering,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProfileWithOffsets,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMaterialUsageDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMeasureValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMeasureWithUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMechanicalFastener,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMechanicalFastenerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMechanicalFastenerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMedicalDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMedicalDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMedicalDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMember,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMemberStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMemberType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMetric,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMetricValueSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMirroredProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfElasticityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfLinearSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfRotationalSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfRotationalSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfSubgradeReactionMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcModulusOfTranslationalSubgradeReactionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMoistureDiffusivityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMolecularWeightMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMomentOfInertiaMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMonetaryMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMonetaryUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMonthInYearNumber,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMotorConnection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMotorConnectionType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcMotorConnectionTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcNamedUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcNonNegativeLengthMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcNormalisedRatioMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcNullStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcNumericMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObject,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjectDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjective,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjectiveEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjectPlacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjectReferenceSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcObjectTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOccupant,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOccupantTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOffsetCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOffsetCurve2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOffsetCurve3D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOffsetCurveByDistances,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOpeningElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOpeningElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOpeningStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOpenShell,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOrganization,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOrganizationRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOrientationExpression,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOrientedEdge,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOuterBoundaryCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOutlet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOutletType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOutletTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcOwnerHistory,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcParameterizedProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcParameterValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPath,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPcurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPerformanceHistory,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPerformanceHistoryTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPermeableCoveringOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPermeableCoveringProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPermit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPermitTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPerson,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPersonAndOrganization,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPHMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPhysicalComplexQuantity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPhysicalOrVirtualEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPhysicalQuantity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPhysicalSimpleQuantity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPile,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPileConstructionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPileType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPileTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeFitting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeFittingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeFittingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeSegmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPipeSegmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPixelTexture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlanarBox,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlanarExtent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlanarForceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlane,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlateStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlateType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPlateTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPoint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPointOnCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPointOnSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPointOrVertexPoint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPolygonalBoundedHalfSpace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPolygonalFaceSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPolyline,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPolyLoop,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPort,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPositioningElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPositiveInteger,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPositiveLengthMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPositivePlaneAngleMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPositiveRatioMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPostalAddress,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPowerMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedColour,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedCurveFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedPropertySet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreDefinedTextFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPreferredSurfaceCurveRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentableText,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationLayerAssignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationLayerWithStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationStyleAssignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPresentationStyleSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPressureMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProcedure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProcedureType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProcedureTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProcess,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProcessSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProduct,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProductDefinitionShape,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProductRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProductRepresentationSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProductSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProfileProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProfileTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProject,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectedCRS,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectedOrTrueLengthEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectionElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectionElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectLibrary,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectOrder,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProjectOrderTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProperty,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyAbstraction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyBoundedValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyDependencyRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyEnumeratedValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyEnumeration,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyListValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyReferenceValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySetDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySetDefinitionSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySetDefinitionSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySetTemplate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySetTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertySingleValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyTableValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyTemplate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPropertyTemplateDefinition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDeviceTrippingUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDeviceTrippingUnitType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDeviceTrippingUnitTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProtectiveDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcProxy,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPump,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPumpType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcPumpTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityArea,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityCount,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityLength,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantitySet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityVolume,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcQuantityWeight,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRadioActivityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRailing,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRailingType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRailingTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRamp,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRampFlight,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRampFlightType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRampFlightTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRampType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRampTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRatioMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRationalBSplineCurveWithKnots,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRationalBSplineSurfaceWithKnots,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRectangleHollowProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRectangleProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRectangularPyramid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRectangularTrimmedSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRecurrencePattern,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRecurrenceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReferent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReferentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReflectanceMethodEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRegularTimeSeries,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcementBarProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcementDefinitionProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingBar,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingBarRoleEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingBarSurfaceEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingBarType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingBarTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingMesh,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingMeshType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReinforcingMeshTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAggregates,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssigns,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToActor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToControl,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToGroup,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToGroupByFactor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToProcess,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToProduct,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssignsToResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociates,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesApproval,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesClassification,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesConstraint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesDocument,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesLibrary,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelAssociatesMaterial,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnects,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsPathElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsPorts,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsPortToElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsStructuralActivity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsStructuralMember,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsWithEccentricity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelConnectsWithRealizingElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelContainedInSpatialStructure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelCoversBldgElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelCoversSpaces,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDeclares,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDecomposes,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDefines,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDefinesByObject,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDefinesByProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDefinesByTemplate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelDefinesByType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelFillsElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelFlowControlElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelInterferesElements,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelNests,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelPositions,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelProjectsElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelReferencedInSpatialStructure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelSequence,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelServicesBuildings,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelSpaceBoundary,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelSpaceBoundary1stLevel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelSpaceBoundary2ndLevel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRelVoidsElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcReparametrisedCompositeCurveSegment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRepresentationContext,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRepresentationItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRepresentationMap,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceApprovalRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceConstraintRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceLevelRelationship,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceObjectSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcResourceTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRevolvedAreaSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRevolvedAreaSolidTapered,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRightCircularCone,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRightCircularCylinder,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoad,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoadPart,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoadPartTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoadTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoleEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoof,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoofType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoofTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoot,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRotationalFrequencyMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRotationalMassMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRotationalStiffnessMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRotationalStiffnessSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcRoundedRectangleProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSanitaryTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSanitaryTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSanitaryTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSchedulingTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSeamCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionalAreaIntegralMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionedSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionedSolidHorizontal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionedSpine,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionModulusMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionReinforcementProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSectionTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSegmentIndexSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSensor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSensorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSensorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSequenceEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShadingDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShadingDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShadingDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShapeAspect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShapeModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShapeRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShearModulusMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShell,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcShellBasedSurfaceModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSimpleProperty,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSimplePropertyTemplate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSimplePropertyTemplateTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSimpleValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSIPrefix,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSite,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSIUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSIUnitName,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSizeSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlab,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlabElementedCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlabStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlabType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlabTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSlippageConnectionCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolarDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolarDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolarDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolidAngleMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolidModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSolidOrShell,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSoundPowerLevelMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSoundPowerMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSoundPressureLevelMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSoundPressureMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpace,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceBoundarySelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceHeater,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceHeaterType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceHeaterTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpaceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialStructureElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialStructureElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialZone,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialZoneType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpatialZoneTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpecificHeatCapacityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpecularExponent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpecularHighlightSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSpecularRoughness,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSphere,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSphericalSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStackTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStackTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStackTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStair,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStairFlight,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStairFlightType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStairFlightTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStairType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStairTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStateEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralActivity,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralActivityAssignmentSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralAnalysisModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralConnection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralConnectionCondition,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveActivityTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveConnection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveMember,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveMemberVarying,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralCurveReaction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLinearAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoad,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadConfiguration,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadGroup,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadLinearForce,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadOrResult,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadPlanarForce,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadSingleDisplacement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadSingleDisplacementDistortion,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadSingleForce,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadSingleForceWarping,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadStatic,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralLoadTemperature,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralMember,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralPlanarAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralPointAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralPointConnection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralPointReaction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralReaction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralResultGroup,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceAction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceActivityTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceConnection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceMember,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceMemberTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceMemberVarying,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStructuralSurfaceReaction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStyleAssignmentSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStyledItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStyledRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcStyleModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSubContractResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSubContractResourceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSubContractResourceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSubedge,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceCurveSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceFeature,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceFeatureTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceOfLinearExtrusion,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceOfRevolution,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceOrFaceSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceReinforcementArea,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceSide,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleElementSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleLighting,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleRefraction,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleRendering,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleShading,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceStyleWithTextures,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSurfaceTexture,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSweptAreaSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSweptDiskSolid,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSweptDiskSolidPolygonal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSweptSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSwitchingDevice,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSwitchingDeviceType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSwitchingDeviceTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSystem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSystemFurnitureElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSystemFurnitureElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcSystemFurnitureElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTable,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTableColumn,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTableRow,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTank,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTankType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTankTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTask,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTaskDurationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTaskTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTaskTimeRecurring,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTaskType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTaskTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTelecomAddress,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTemperatureGradientMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTemperatureRateOfChangeMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendon,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonAnchor,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonAnchorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonAnchorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonConduit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonConduitType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonConduitTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTendonTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTessellatedFaceSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTessellatedItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcText,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextAlignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextDecoration,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextFontName,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextFontSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextLiteral,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextLiteralWithExtent,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextPath,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextStyleFontModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextStyleForDefinedFont,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextStyleTextModel,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextTransformation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextureCoordinate,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextureCoordinateGenerator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextureMap,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextureVertex,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTextureVertexList,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermalAdmittanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermalConductivityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermalExpansionCoefficientMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermalResistanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermalTransmittanceMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcThermodynamicTemperatureMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeOrRatioSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimePeriod,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeSeries,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeSeriesDataTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeSeriesValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTimeStamp,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTopologicalRepresentationItem,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTopologyRepresentation,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcToroidalSurface,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTorqueMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransformer,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransformerType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransformerTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransitionCode,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransitionCurveSegment2D,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransitionCurveType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTranslationalStiffnessSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransportElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransportElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTransportElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTrapeziumProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTriangulatedFaceSet,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTriangulatedIrregularNetwork,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTrimmedCurve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTrimmingPreference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTrimmingSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTubeBundle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTubeBundleType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTubeBundleTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTypeObject,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTypeProcess,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTypeProduct,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcTypeResource,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnit,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryControlElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryControlElementType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryControlElementTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryEquipment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryEquipmentType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitaryEquipmentTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitAssignment,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUnitEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcURIReference,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcUShapeProfileDef,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcValue,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcValve,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcValveType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcValveTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVaporPermeabilityMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVector,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVectorOrDirection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVertex,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVertexLoop,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVertexPoint,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationDamper,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationDamperType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationDamperTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationIsolator,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationIsolatorType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVibrationIsolatorTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVirtualElement,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVirtualGridIntersection,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVoidingFeature,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVoidingFeatureTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVolumeMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcVolumetricFlowRateMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWall,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWallElementedCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWallStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWallType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWallTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWarpingConstantMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWarpingMomentMeasure,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWarpingStiffnessSelect,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWasteTerminal,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWasteTerminalType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWasteTerminalTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindow,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowLiningProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowPanelOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowPanelPositionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowPanelProperties,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowStandardCase,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowStyle,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowStyleConstructionEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowStyleOperationEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowType,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWindowTypePartitioningEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkCalendar,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkCalendarTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkControl,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkPlan,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkPlanTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkSchedule,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkScheduleTypeEnum,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcWorkTime,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcZone,
		OpenInfraPlatform::IFC4X2_BIM4ROAD::IfcZShapeProfileDef
	>
	IFC4X2_BIM4ROADEntityTypes;
}
