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


using namespace OpenInfraPlatform::IfcAlignment1x1;
template <typename F> void castAndCall(std::shared_ptr<IfcAlignment1x1Entity> ptr, F &f) {
	switch (ptr->m_entity_enum) {

		case IFCACTIONREQUEST:
			f(*(std::dynamic_pointer_cast<IfcActionRequest>(ptr)));
			break;

		case IFCACTOR:
			f(*(std::dynamic_pointer_cast<IfcActor>(ptr)));
			break;

		case IFCACTORROLE:
			f(*(std::dynamic_pointer_cast<IfcActorRole>(ptr)));
			break;

		case IFCACTUATOR:
			f(*(std::dynamic_pointer_cast<IfcActuator>(ptr)));
			break;

		case IFCACTUATORTYPE:
			f(*(std::dynamic_pointer_cast<IfcActuatorType>(ptr)));
			break;

		case IFCADDRESS:
			f(*(std::dynamic_pointer_cast<IfcAddress>(ptr)));
			break;

		case IFCADVANCEDBREP:
			f(*(std::dynamic_pointer_cast<IfcAdvancedBrep>(ptr)));
			break;

		case IFCADVANCEDBREPWITHVOIDS:
			f(*(std::dynamic_pointer_cast<IfcAdvancedBrepWithVoids>(ptr)));
			break;

		case IFCADVANCEDFACE:
			f(*(std::dynamic_pointer_cast<IfcAdvancedFace>(ptr)));
			break;

		case IFCAIRTERMINAL:
			f(*(std::dynamic_pointer_cast<IfcAirTerminal>(ptr)));
			break;

		case IFCAIRTERMINALBOX:
			f(*(std::dynamic_pointer_cast<IfcAirTerminalBox>(ptr)));
			break;

		case IFCAIRTERMINALBOXTYPE:
			f(*(std::dynamic_pointer_cast<IfcAirTerminalBoxType>(ptr)));
			break;

		case IFCAIRTERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcAirTerminalType>(ptr)));
			break;

		case IFCAIRTOAIRHEATRECOVERY:
			f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecovery>(ptr)));
			break;

		case IFCAIRTOAIRHEATRECOVERYTYPE:
			f(*(std::dynamic_pointer_cast<IfcAirToAirHeatRecoveryType>(ptr)));
			break;

		case IFCALARM:
			f(*(std::dynamic_pointer_cast<IfcAlarm>(ptr)));
			break;

		case IFCALARMTYPE:
			f(*(std::dynamic_pointer_cast<IfcAlarmType>(ptr)));
			break;

		case IFCALIGNMENT:
			f(*(std::dynamic_pointer_cast<IfcAlignment>(ptr)));
			break;

		case IFCALIGNMENT2DHORIZONTAL:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontal>(ptr)));
			break;

		case IFCALIGNMENT2DHORIZONTALSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DHorizontalSegment>(ptr)));
			break;

		case IFCALIGNMENT2DSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DSegment>(ptr)));
			break;

		case IFCALIGNMENT2DVERSEGCIRCULARARC:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegCircularArc>(ptr)));
			break;

		case IFCALIGNMENT2DVERSEGLINE:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegLine>(ptr)));
			break;

		case IFCALIGNMENT2DVERSEGPARABOLICARC:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DVerSegParabolicArc>(ptr)));
			break;

		case IFCALIGNMENT2DVERTICAL:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DVertical>(ptr)));
			break;

		case IFCALIGNMENT2DVERTICALSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcAlignment2DVerticalSegment>(ptr)));
			break;

		case IFCALIGNMENTCURVE:
			f(*(std::dynamic_pointer_cast<IfcAlignmentCurve>(ptr)));
			break;

		case IFCANNOTATION:
			f(*(std::dynamic_pointer_cast<IfcAnnotation>(ptr)));
			break;

		case IFCANNOTATIONFILLAREA:
			f(*(std::dynamic_pointer_cast<IfcAnnotationFillArea>(ptr)));
			break;

		case IFCAPPLICATION:
			f(*(std::dynamic_pointer_cast<IfcApplication>(ptr)));
			break;

		case IFCAPPLIEDVALUE:
			f(*(std::dynamic_pointer_cast<IfcAppliedValue>(ptr)));
			break;

		case IFCAPPROVAL:
			f(*(std::dynamic_pointer_cast<IfcApproval>(ptr)));
			break;

		case IFCAPPROVALRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcApprovalRelationship>(ptr)));
			break;

		case IFCARBITRARYCLOSEDPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcArbitraryClosedProfileDef>(ptr)));
			break;

		case IFCARBITRARYOPENPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcArbitraryOpenProfileDef>(ptr)));
			break;

		case IFCARBITRARYPROFILEDEFWITHVOIDS:
			f(*(std::dynamic_pointer_cast<IfcArbitraryProfileDefWithVoids>(ptr)));
			break;

		case IFCASSET:
			f(*(std::dynamic_pointer_cast<IfcAsset>(ptr)));
			break;

		case IFCASYMMETRICISHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcAsymmetricIShapeProfileDef>(ptr)));
			break;

		case IFCAUDIOVISUALAPPLIANCE:
			f(*(std::dynamic_pointer_cast<IfcAudioVisualAppliance>(ptr)));
			break;

		case IFCAUDIOVISUALAPPLIANCETYPE:
			f(*(std::dynamic_pointer_cast<IfcAudioVisualApplianceType>(ptr)));
			break;

		case IFCAXIS1PLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcAxis1Placement>(ptr)));
			break;

		case IFCAXIS2PLACEMENT2D:
			f(*(std::dynamic_pointer_cast<IfcAxis2Placement2D>(ptr)));
			break;

		case IFCAXIS2PLACEMENT3D:
			f(*(std::dynamic_pointer_cast<IfcAxis2Placement3D>(ptr)));
			break;

		case IFCBSPLINECURVE:
			f(*(std::dynamic_pointer_cast<IfcBSplineCurve>(ptr)));
			break;

		case IFCBSPLINECURVEWITHKNOTS:
			f(*(std::dynamic_pointer_cast<IfcBSplineCurveWithKnots>(ptr)));
			break;

		case IFCBSPLINESURFACE:
			f(*(std::dynamic_pointer_cast<IfcBSplineSurface>(ptr)));
			break;

		case IFCBSPLINESURFACEWITHKNOTS:
			f(*(std::dynamic_pointer_cast<IfcBSplineSurfaceWithKnots>(ptr)));
			break;

		case IFCBEAM:
			f(*(std::dynamic_pointer_cast<IfcBeam>(ptr)));
			break;

		case IFCBEAMSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcBeamStandardCase>(ptr)));
			break;

		case IFCBEAMTYPE:
			f(*(std::dynamic_pointer_cast<IfcBeamType>(ptr)));
			break;

		case IFCBLOBTEXTURE:
			f(*(std::dynamic_pointer_cast<IfcBlobTexture>(ptr)));
			break;

		case IFCBLOCK:
			f(*(std::dynamic_pointer_cast<IfcBlock>(ptr)));
			break;

		case IFCBOILER:
			f(*(std::dynamic_pointer_cast<IfcBoiler>(ptr)));
			break;

		case IFCBOILERTYPE:
			f(*(std::dynamic_pointer_cast<IfcBoilerType>(ptr)));
			break;

		case IFCBOOLEANCLIPPINGRESULT:
			f(*(std::dynamic_pointer_cast<IfcBooleanClippingResult>(ptr)));
			break;

		case IFCBOOLEANRESULT:
			f(*(std::dynamic_pointer_cast<IfcBooleanResult>(ptr)));
			break;

		case IFCBOUNDARYCONDITION:
			f(*(std::dynamic_pointer_cast<IfcBoundaryCondition>(ptr)));
			break;

		case IFCBOUNDARYCURVE:
			f(*(std::dynamic_pointer_cast<IfcBoundaryCurve>(ptr)));
			break;

		case IFCBOUNDARYEDGECONDITION:
			f(*(std::dynamic_pointer_cast<IfcBoundaryEdgeCondition>(ptr)));
			break;

		case IFCBOUNDARYFACECONDITION:
			f(*(std::dynamic_pointer_cast<IfcBoundaryFaceCondition>(ptr)));
			break;

		case IFCBOUNDARYNODECONDITION:
			f(*(std::dynamic_pointer_cast<IfcBoundaryNodeCondition>(ptr)));
			break;

		case IFCBOUNDARYNODECONDITIONWARPING:
			f(*(std::dynamic_pointer_cast<IfcBoundaryNodeConditionWarping>(ptr)));
			break;

		case IFCBOUNDEDCURVE:
			f(*(std::dynamic_pointer_cast<IfcBoundedCurve>(ptr)));
			break;

		case IFCBOUNDEDSURFACE:
			f(*(std::dynamic_pointer_cast<IfcBoundedSurface>(ptr)));
			break;

		case IFCBOUNDINGBOX:
			f(*(std::dynamic_pointer_cast<IfcBoundingBox>(ptr)));
			break;

		case IFCBOXEDHALFSPACE:
			f(*(std::dynamic_pointer_cast<IfcBoxedHalfSpace>(ptr)));
			break;

		case IFCBUILDING:
			f(*(std::dynamic_pointer_cast<IfcBuilding>(ptr)));
			break;

		case IFCBUILDINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcBuildingElement>(ptr)));
			break;

		case IFCBUILDINGELEMENTPART:
			f(*(std::dynamic_pointer_cast<IfcBuildingElementPart>(ptr)));
			break;

		case IFCBUILDINGELEMENTPARTTYPE:
			f(*(std::dynamic_pointer_cast<IfcBuildingElementPartType>(ptr)));
			break;

		case IFCBUILDINGELEMENTPROXY:
			f(*(std::dynamic_pointer_cast<IfcBuildingElementProxy>(ptr)));
			break;

		case IFCBUILDINGELEMENTPROXYTYPE:
			f(*(std::dynamic_pointer_cast<IfcBuildingElementProxyType>(ptr)));
			break;

		case IFCBUILDINGELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcBuildingElementType>(ptr)));
			break;

		case IFCBUILDINGSTOREY:
			f(*(std::dynamic_pointer_cast<IfcBuildingStorey>(ptr)));
			break;

		case IFCBUILDINGSYSTEM:
			f(*(std::dynamic_pointer_cast<IfcBuildingSystem>(ptr)));
			break;

		case IFCBURNER:
			f(*(std::dynamic_pointer_cast<IfcBurner>(ptr)));
			break;

		case IFCBURNERTYPE:
			f(*(std::dynamic_pointer_cast<IfcBurnerType>(ptr)));
			break;

		case IFCCSHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcCShapeProfileDef>(ptr)));
			break;

		case IFCCABLECARRIERFITTING:
			f(*(std::dynamic_pointer_cast<IfcCableCarrierFitting>(ptr)));
			break;

		case IFCCABLECARRIERFITTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcCableCarrierFittingType>(ptr)));
			break;

		case IFCCABLECARRIERSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcCableCarrierSegment>(ptr)));
			break;

		case IFCCABLECARRIERSEGMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcCableCarrierSegmentType>(ptr)));
			break;

		case IFCCABLEFITTING:
			f(*(std::dynamic_pointer_cast<IfcCableFitting>(ptr)));
			break;

		case IFCCABLEFITTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcCableFittingType>(ptr)));
			break;

		case IFCCABLESEGMENT:
			f(*(std::dynamic_pointer_cast<IfcCableSegment>(ptr)));
			break;

		case IFCCABLESEGMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcCableSegmentType>(ptr)));
			break;

		case IFCCARTESIANPOINT:
			f(*(std::dynamic_pointer_cast<IfcCartesianPoint>(ptr)));
			break;

		case IFCCARTESIANPOINTLIST:
			f(*(std::dynamic_pointer_cast<IfcCartesianPointList>(ptr)));
			break;

		case IFCCARTESIANPOINTLIST2D:
			f(*(std::dynamic_pointer_cast<IfcCartesianPointList2D>(ptr)));
			break;

		case IFCCARTESIANPOINTLIST2DLABELLED:
			f(*(std::dynamic_pointer_cast<IfcCartesianPointList2DLabelled>(ptr)));
			break;

		case IFCCARTESIANPOINTLIST3D:
			f(*(std::dynamic_pointer_cast<IfcCartesianPointList3D>(ptr)));
			break;

		case IFCCARTESIANTRANSFORMATIONOPERATOR:
			f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator>(ptr)));
			break;

		case IFCCARTESIANTRANSFORMATIONOPERATOR2D:
			f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2D>(ptr)));
			break;

		case IFCCARTESIANTRANSFORMATIONOPERATOR2DNONUNIFORM:
			f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator2DnonUniform>(ptr)));
			break;

		case IFCCARTESIANTRANSFORMATIONOPERATOR3D:
			f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3D>(ptr)));
			break;

		case IFCCARTESIANTRANSFORMATIONOPERATOR3DNONUNIFORM:
			f(*(std::dynamic_pointer_cast<IfcCartesianTransformationOperator3DnonUniform>(ptr)));
			break;

		case IFCCENTERLINEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcCenterLineProfileDef>(ptr)));
			break;

		case IFCCHILLER:
			f(*(std::dynamic_pointer_cast<IfcChiller>(ptr)));
			break;

		case IFCCHILLERTYPE:
			f(*(std::dynamic_pointer_cast<IfcChillerType>(ptr)));
			break;

		case IFCCHIMNEY:
			f(*(std::dynamic_pointer_cast<IfcChimney>(ptr)));
			break;

		case IFCCHIMNEYTYPE:
			f(*(std::dynamic_pointer_cast<IfcChimneyType>(ptr)));
			break;

		case IFCCIRCLE:
			f(*(std::dynamic_pointer_cast<IfcCircle>(ptr)));
			break;

		case IFCCIRCLEHOLLOWPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcCircleHollowProfileDef>(ptr)));
			break;

		case IFCCIRCLEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcCircleProfileDef>(ptr)));
			break;

		case IFCCIRCULARARCSEGMENT2D:
			f(*(std::dynamic_pointer_cast<IfcCircularArcSegment2D>(ptr)));
			break;

		case IFCCIVILELEMENT:
			f(*(std::dynamic_pointer_cast<IfcCivilElement>(ptr)));
			break;

		case IFCCIVILELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcCivilElementType>(ptr)));
			break;

		case IFCCLASSIFICATION:
			f(*(std::dynamic_pointer_cast<IfcClassification>(ptr)));
			break;

		case IFCCLASSIFICATIONREFERENCE:
			f(*(std::dynamic_pointer_cast<IfcClassificationReference>(ptr)));
			break;

		case IFCCLOSEDSHELL:
			f(*(std::dynamic_pointer_cast<IfcClosedShell>(ptr)));
			break;

		case IFCCLOTHOIDALARCSEGMENT2D:
			f(*(std::dynamic_pointer_cast<IfcClothoidalArcSegment2D>(ptr)));
			break;

		case IFCCOIL:
			f(*(std::dynamic_pointer_cast<IfcCoil>(ptr)));
			break;

		case IFCCOILTYPE:
			f(*(std::dynamic_pointer_cast<IfcCoilType>(ptr)));
			break;

		case IFCCOLOURRGB:
			f(*(std::dynamic_pointer_cast<IfcColourRgb>(ptr)));
			break;

		case IFCCOLOURRGBLIST:
			f(*(std::dynamic_pointer_cast<IfcColourRgbList>(ptr)));
			break;

		case IFCCOLOURSPECIFICATION:
			f(*(std::dynamic_pointer_cast<IfcColourSpecification>(ptr)));
			break;

		case IFCCOLUMN:
			f(*(std::dynamic_pointer_cast<IfcColumn>(ptr)));
			break;

		case IFCCOLUMNSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcColumnStandardCase>(ptr)));
			break;

		case IFCCOLUMNTYPE:
			f(*(std::dynamic_pointer_cast<IfcColumnType>(ptr)));
			break;

		case IFCCOMMUNICATIONSAPPLIANCE:
			f(*(std::dynamic_pointer_cast<IfcCommunicationsAppliance>(ptr)));
			break;

		case IFCCOMMUNICATIONSAPPLIANCETYPE:
			f(*(std::dynamic_pointer_cast<IfcCommunicationsApplianceType>(ptr)));
			break;

		case IFCCOMPLEXPROPERTY:
			f(*(std::dynamic_pointer_cast<IfcComplexProperty>(ptr)));
			break;

		case IFCCOMPLEXPROPERTYTEMPLATE:
			f(*(std::dynamic_pointer_cast<IfcComplexPropertyTemplate>(ptr)));
			break;

		case IFCCOMPOSITECURVE:
			f(*(std::dynamic_pointer_cast<IfcCompositeCurve>(ptr)));
			break;

		case IFCCOMPOSITECURVEONSURFACE:
			f(*(std::dynamic_pointer_cast<IfcCompositeCurveOnSurface>(ptr)));
			break;

		case IFCCOMPOSITECURVESEGMENT:
			f(*(std::dynamic_pointer_cast<IfcCompositeCurveSegment>(ptr)));
			break;

		case IFCCOMPOSITEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcCompositeProfileDef>(ptr)));
			break;

		case IFCCOMPRESSOR:
			f(*(std::dynamic_pointer_cast<IfcCompressor>(ptr)));
			break;

		case IFCCOMPRESSORTYPE:
			f(*(std::dynamic_pointer_cast<IfcCompressorType>(ptr)));
			break;

		case IFCCONDENSER:
			f(*(std::dynamic_pointer_cast<IfcCondenser>(ptr)));
			break;

		case IFCCONDENSERTYPE:
			f(*(std::dynamic_pointer_cast<IfcCondenserType>(ptr)));
			break;

		case IFCCONIC:
			f(*(std::dynamic_pointer_cast<IfcConic>(ptr)));
			break;

		case IFCCONNECTEDFACESET:
			f(*(std::dynamic_pointer_cast<IfcConnectedFaceSet>(ptr)));
			break;

		case IFCCONNECTIONCURVEGEOMETRY:
			f(*(std::dynamic_pointer_cast<IfcConnectionCurveGeometry>(ptr)));
			break;

		case IFCCONNECTIONGEOMETRY:
			f(*(std::dynamic_pointer_cast<IfcConnectionGeometry>(ptr)));
			break;

		case IFCCONNECTIONPOINTECCENTRICITY:
			f(*(std::dynamic_pointer_cast<IfcConnectionPointEccentricity>(ptr)));
			break;

		case IFCCONNECTIONPOINTGEOMETRY:
			f(*(std::dynamic_pointer_cast<IfcConnectionPointGeometry>(ptr)));
			break;

		case IFCCONNECTIONSURFACEGEOMETRY:
			f(*(std::dynamic_pointer_cast<IfcConnectionSurfaceGeometry>(ptr)));
			break;

		case IFCCONNECTIONVOLUMEGEOMETRY:
			f(*(std::dynamic_pointer_cast<IfcConnectionVolumeGeometry>(ptr)));
			break;

		case IFCCONSTRAINT:
			f(*(std::dynamic_pointer_cast<IfcConstraint>(ptr)));
			break;

		case IFCCONSTRUCTIONEQUIPMENTRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResource>(ptr)));
			break;

		case IFCCONSTRUCTIONEQUIPMENTRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcConstructionEquipmentResourceType>(ptr)));
			break;

		case IFCCONSTRUCTIONMATERIALRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResource>(ptr)));
			break;

		case IFCCONSTRUCTIONMATERIALRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcConstructionMaterialResourceType>(ptr)));
			break;

		case IFCCONSTRUCTIONPRODUCTRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcConstructionProductResource>(ptr)));
			break;

		case IFCCONSTRUCTIONPRODUCTRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcConstructionProductResourceType>(ptr)));
			break;

		case IFCCONSTRUCTIONRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcConstructionResource>(ptr)));
			break;

		case IFCCONSTRUCTIONRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcConstructionResourceType>(ptr)));
			break;

		case IFCCONTEXT:
			f(*(std::dynamic_pointer_cast<IfcContext>(ptr)));
			break;

		case IFCCONTEXTDEPENDENTUNIT:
			f(*(std::dynamic_pointer_cast<IfcContextDependentUnit>(ptr)));
			break;

		case IFCCONTROL:
			f(*(std::dynamic_pointer_cast<IfcControl>(ptr)));
			break;

		case IFCCONTROLLER:
			f(*(std::dynamic_pointer_cast<IfcController>(ptr)));
			break;

		case IFCCONTROLLERTYPE:
			f(*(std::dynamic_pointer_cast<IfcControllerType>(ptr)));
			break;

		case IFCCONVERSIONBASEDUNIT:
			f(*(std::dynamic_pointer_cast<IfcConversionBasedUnit>(ptr)));
			break;

		case IFCCONVERSIONBASEDUNITWITHOFFSET:
			f(*(std::dynamic_pointer_cast<IfcConversionBasedUnitWithOffset>(ptr)));
			break;

		case IFCCOOLEDBEAM:
			f(*(std::dynamic_pointer_cast<IfcCooledBeam>(ptr)));
			break;

		case IFCCOOLEDBEAMTYPE:
			f(*(std::dynamic_pointer_cast<IfcCooledBeamType>(ptr)));
			break;

		case IFCCOOLINGTOWER:
			f(*(std::dynamic_pointer_cast<IfcCoolingTower>(ptr)));
			break;

		case IFCCOOLINGTOWERTYPE:
			f(*(std::dynamic_pointer_cast<IfcCoolingTowerType>(ptr)));
			break;

		case IFCCOORDINATEOPERATION:
			f(*(std::dynamic_pointer_cast<IfcCoordinateOperation>(ptr)));
			break;

		case IFCCOORDINATEREFERENCESYSTEM:
			f(*(std::dynamic_pointer_cast<IfcCoordinateReferenceSystem>(ptr)));
			break;

		case IFCCOSTITEM:
			f(*(std::dynamic_pointer_cast<IfcCostItem>(ptr)));
			break;

		case IFCCOSTSCHEDULE:
			f(*(std::dynamic_pointer_cast<IfcCostSchedule>(ptr)));
			break;

		case IFCCOSTVALUE:
			f(*(std::dynamic_pointer_cast<IfcCostValue>(ptr)));
			break;

		case IFCCOVERING:
			f(*(std::dynamic_pointer_cast<IfcCovering>(ptr)));
			break;

		case IFCCOVERINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcCoveringType>(ptr)));
			break;

		case IFCCREWRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcCrewResource>(ptr)));
			break;

		case IFCCREWRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcCrewResourceType>(ptr)));
			break;

		case IFCCSGPRIMITIVE3D:
			f(*(std::dynamic_pointer_cast<IfcCsgPrimitive3D>(ptr)));
			break;

		case IFCCSGSOLID:
			f(*(std::dynamic_pointer_cast<IfcCsgSolid>(ptr)));
			break;

		case IFCCURRENCYRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcCurrencyRelationship>(ptr)));
			break;

		case IFCCURTAINWALL:
			f(*(std::dynamic_pointer_cast<IfcCurtainWall>(ptr)));
			break;

		case IFCCURTAINWALLTYPE:
			f(*(std::dynamic_pointer_cast<IfcCurtainWallType>(ptr)));
			break;

		case IFCCURVE:
			f(*(std::dynamic_pointer_cast<IfcCurve>(ptr)));
			break;

		case IFCCURVEBOUNDEDPLANE:
			f(*(std::dynamic_pointer_cast<IfcCurveBoundedPlane>(ptr)));
			break;

		case IFCCURVEBOUNDEDSURFACE:
			f(*(std::dynamic_pointer_cast<IfcCurveBoundedSurface>(ptr)));
			break;

		case IFCCURVESEGMENT2D:
			f(*(std::dynamic_pointer_cast<IfcCurveSegment2D>(ptr)));
			break;

		case IFCCURVESTYLE:
			f(*(std::dynamic_pointer_cast<IfcCurveStyle>(ptr)));
			break;

		case IFCCURVESTYLEFONT:
			f(*(std::dynamic_pointer_cast<IfcCurveStyleFont>(ptr)));
			break;

		case IFCCURVESTYLEFONTANDSCALING:
			f(*(std::dynamic_pointer_cast<IfcCurveStyleFontAndScaling>(ptr)));
			break;

		case IFCCURVESTYLEFONTPATTERN:
			f(*(std::dynamic_pointer_cast<IfcCurveStyleFontPattern>(ptr)));
			break;

		case IFCCYLINDRICALSURFACE:
			f(*(std::dynamic_pointer_cast<IfcCylindricalSurface>(ptr)));
			break;

		case IFCDAMPER:
			f(*(std::dynamic_pointer_cast<IfcDamper>(ptr)));
			break;

		case IFCDAMPERTYPE:
			f(*(std::dynamic_pointer_cast<IfcDamperType>(ptr)));
			break;

		case IFCDERIVEDPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcDerivedProfileDef>(ptr)));
			break;

		case IFCDERIVEDUNIT:
			f(*(std::dynamic_pointer_cast<IfcDerivedUnit>(ptr)));
			break;

		case IFCDERIVEDUNITELEMENT:
			f(*(std::dynamic_pointer_cast<IfcDerivedUnitElement>(ptr)));
			break;

		case IFCDIMENSIONALEXPONENTS:
			f(*(std::dynamic_pointer_cast<IfcDimensionalExponents>(ptr)));
			break;

		case IFCDIRECTION:
			f(*(std::dynamic_pointer_cast<IfcDirection>(ptr)));
			break;

		case IFCDISCRETEACCESSORY:
			f(*(std::dynamic_pointer_cast<IfcDiscreteAccessory>(ptr)));
			break;

		case IFCDISCRETEACCESSORYTYPE:
			f(*(std::dynamic_pointer_cast<IfcDiscreteAccessoryType>(ptr)));
			break;

		case IFCDISTANCEEXPRESSION:
			f(*(std::dynamic_pointer_cast<IfcDistanceExpression>(ptr)));
			break;

		case IFCDISTRIBUTIONCHAMBERELEMENT:
			f(*(std::dynamic_pointer_cast<IfcDistributionChamberElement>(ptr)));
			break;

		case IFCDISTRIBUTIONCHAMBERELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcDistributionChamberElementType>(ptr)));
			break;

		case IFCDISTRIBUTIONCIRCUIT:
			f(*(std::dynamic_pointer_cast<IfcDistributionCircuit>(ptr)));
			break;

		case IFCDISTRIBUTIONCONTROLELEMENT:
			f(*(std::dynamic_pointer_cast<IfcDistributionControlElement>(ptr)));
			break;

		case IFCDISTRIBUTIONCONTROLELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcDistributionControlElementType>(ptr)));
			break;

		case IFCDISTRIBUTIONELEMENT:
			f(*(std::dynamic_pointer_cast<IfcDistributionElement>(ptr)));
			break;

		case IFCDISTRIBUTIONELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcDistributionElementType>(ptr)));
			break;

		case IFCDISTRIBUTIONFLOWELEMENT:
			f(*(std::dynamic_pointer_cast<IfcDistributionFlowElement>(ptr)));
			break;

		case IFCDISTRIBUTIONFLOWELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcDistributionFlowElementType>(ptr)));
			break;

		case IFCDISTRIBUTIONPORT:
			f(*(std::dynamic_pointer_cast<IfcDistributionPort>(ptr)));
			break;

		case IFCDISTRIBUTIONSYSTEM:
			f(*(std::dynamic_pointer_cast<IfcDistributionSystem>(ptr)));
			break;

		case IFCDOCUMENTINFORMATION:
			f(*(std::dynamic_pointer_cast<IfcDocumentInformation>(ptr)));
			break;

		case IFCDOCUMENTINFORMATIONRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcDocumentInformationRelationship>(ptr)));
			break;

		case IFCDOCUMENTREFERENCE:
			f(*(std::dynamic_pointer_cast<IfcDocumentReference>(ptr)));
			break;

		case IFCDOOR:
			f(*(std::dynamic_pointer_cast<IfcDoor>(ptr)));
			break;

		case IFCDOORLININGPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcDoorLiningProperties>(ptr)));
			break;

		case IFCDOORPANELPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcDoorPanelProperties>(ptr)));
			break;

		case IFCDOORSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcDoorStandardCase>(ptr)));
			break;

		case IFCDOORSTYLE:
			f(*(std::dynamic_pointer_cast<IfcDoorStyle>(ptr)));
			break;

		case IFCDOORTYPE:
			f(*(std::dynamic_pointer_cast<IfcDoorType>(ptr)));
			break;

		case IFCDRAUGHTINGPREDEFINEDCOLOUR:
			f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedColour>(ptr)));
			break;

		case IFCDRAUGHTINGPREDEFINEDCURVEFONT:
			f(*(std::dynamic_pointer_cast<IfcDraughtingPreDefinedCurveFont>(ptr)));
			break;

		case IFCDUCTFITTING:
			f(*(std::dynamic_pointer_cast<IfcDuctFitting>(ptr)));
			break;

		case IFCDUCTFITTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcDuctFittingType>(ptr)));
			break;

		case IFCDUCTSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcDuctSegment>(ptr)));
			break;

		case IFCDUCTSEGMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcDuctSegmentType>(ptr)));
			break;

		case IFCDUCTSILENCER:
			f(*(std::dynamic_pointer_cast<IfcDuctSilencer>(ptr)));
			break;

		case IFCDUCTSILENCERTYPE:
			f(*(std::dynamic_pointer_cast<IfcDuctSilencerType>(ptr)));
			break;

		case IFCEDGE:
			f(*(std::dynamic_pointer_cast<IfcEdge>(ptr)));
			break;

		case IFCEDGECURVE:
			f(*(std::dynamic_pointer_cast<IfcEdgeCurve>(ptr)));
			break;

		case IFCEDGELOOP:
			f(*(std::dynamic_pointer_cast<IfcEdgeLoop>(ptr)));
			break;

		case IFCELECTRICAPPLIANCE:
			f(*(std::dynamic_pointer_cast<IfcElectricAppliance>(ptr)));
			break;

		case IFCELECTRICAPPLIANCETYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricApplianceType>(ptr)));
			break;

		case IFCELECTRICDISTRIBUTIONBOARD:
			f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoard>(ptr)));
			break;

		case IFCELECTRICDISTRIBUTIONBOARDTYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricDistributionBoardType>(ptr)));
			break;

		case IFCELECTRICFLOWSTORAGEDEVICE:
			f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDevice>(ptr)));
			break;

		case IFCELECTRICFLOWSTORAGEDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricFlowStorageDeviceType>(ptr)));
			break;

		case IFCELECTRICGENERATOR:
			f(*(std::dynamic_pointer_cast<IfcElectricGenerator>(ptr)));
			break;

		case IFCELECTRICGENERATORTYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricGeneratorType>(ptr)));
			break;

		case IFCELECTRICMOTOR:
			f(*(std::dynamic_pointer_cast<IfcElectricMotor>(ptr)));
			break;

		case IFCELECTRICMOTORTYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricMotorType>(ptr)));
			break;

		case IFCELECTRICTIMECONTROL:
			f(*(std::dynamic_pointer_cast<IfcElectricTimeControl>(ptr)));
			break;

		case IFCELECTRICTIMECONTROLTYPE:
			f(*(std::dynamic_pointer_cast<IfcElectricTimeControlType>(ptr)));
			break;

		case IFCELEMENT:
			f(*(std::dynamic_pointer_cast<IfcElement>(ptr)));
			break;

		case IFCELEMENTASSEMBLY:
			f(*(std::dynamic_pointer_cast<IfcElementAssembly>(ptr)));
			break;

		case IFCELEMENTASSEMBLYTYPE:
			f(*(std::dynamic_pointer_cast<IfcElementAssemblyType>(ptr)));
			break;

		case IFCELEMENTCOMPONENT:
			f(*(std::dynamic_pointer_cast<IfcElementComponent>(ptr)));
			break;

		case IFCELEMENTCOMPONENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcElementComponentType>(ptr)));
			break;

		case IFCELEMENTQUANTITY:
			f(*(std::dynamic_pointer_cast<IfcElementQuantity>(ptr)));
			break;

		case IFCELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcElementType>(ptr)));
			break;

		case IFCELEMENTARYSURFACE:
			f(*(std::dynamic_pointer_cast<IfcElementarySurface>(ptr)));
			break;

		case IFCELLIPSE:
			f(*(std::dynamic_pointer_cast<IfcEllipse>(ptr)));
			break;

		case IFCELLIPSEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcEllipseProfileDef>(ptr)));
			break;

		case IFCENERGYCONVERSIONDEVICE:
			f(*(std::dynamic_pointer_cast<IfcEnergyConversionDevice>(ptr)));
			break;

		case IFCENERGYCONVERSIONDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcEnergyConversionDeviceType>(ptr)));
			break;

		case IFCENGINE:
			f(*(std::dynamic_pointer_cast<IfcEngine>(ptr)));
			break;

		case IFCENGINETYPE:
			f(*(std::dynamic_pointer_cast<IfcEngineType>(ptr)));
			break;

		case IFCEVAPORATIVECOOLER:
			f(*(std::dynamic_pointer_cast<IfcEvaporativeCooler>(ptr)));
			break;

		case IFCEVAPORATIVECOOLERTYPE:
			f(*(std::dynamic_pointer_cast<IfcEvaporativeCoolerType>(ptr)));
			break;

		case IFCEVAPORATOR:
			f(*(std::dynamic_pointer_cast<IfcEvaporator>(ptr)));
			break;

		case IFCEVAPORATORTYPE:
			f(*(std::dynamic_pointer_cast<IfcEvaporatorType>(ptr)));
			break;

		case IFCEVENT:
			f(*(std::dynamic_pointer_cast<IfcEvent>(ptr)));
			break;

		case IFCEVENTTIME:
			f(*(std::dynamic_pointer_cast<IfcEventTime>(ptr)));
			break;

		case IFCEVENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcEventType>(ptr)));
			break;

		case IFCEXTENDEDPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcExtendedProperties>(ptr)));
			break;

		case IFCEXTERNALINFORMATION:
			f(*(std::dynamic_pointer_cast<IfcExternalInformation>(ptr)));
			break;

		case IFCEXTERNALREFERENCE:
			f(*(std::dynamic_pointer_cast<IfcExternalReference>(ptr)));
			break;

		case IFCEXTERNALREFERENCERELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcExternalReferenceRelationship>(ptr)));
			break;

		case IFCEXTERNALSPATIALELEMENT:
			f(*(std::dynamic_pointer_cast<IfcExternalSpatialElement>(ptr)));
			break;

		case IFCEXTERNALSPATIALSTRUCTUREELEMENT:
			f(*(std::dynamic_pointer_cast<IfcExternalSpatialStructureElement>(ptr)));
			break;

		case IFCEXTERNALLYDEFINEDHATCHSTYLE:
			f(*(std::dynamic_pointer_cast<IfcExternallyDefinedHatchStyle>(ptr)));
			break;

		case IFCEXTERNALLYDEFINEDSURFACESTYLE:
			f(*(std::dynamic_pointer_cast<IfcExternallyDefinedSurfaceStyle>(ptr)));
			break;

		case IFCEXTERNALLYDEFINEDTEXTFONT:
			f(*(std::dynamic_pointer_cast<IfcExternallyDefinedTextFont>(ptr)));
			break;

		case IFCEXTRUDEDAREASOLID:
			f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolid>(ptr)));
			break;

		case IFCEXTRUDEDAREASOLIDTAPERED:
			f(*(std::dynamic_pointer_cast<IfcExtrudedAreaSolidTapered>(ptr)));
			break;

		case IFCFACE:
			f(*(std::dynamic_pointer_cast<IfcFace>(ptr)));
			break;

		case IFCFACEBASEDSURFACEMODEL:
			f(*(std::dynamic_pointer_cast<IfcFaceBasedSurfaceModel>(ptr)));
			break;

		case IFCFACEBOUND:
			f(*(std::dynamic_pointer_cast<IfcFaceBound>(ptr)));
			break;

		case IFCFACEOUTERBOUND:
			f(*(std::dynamic_pointer_cast<IfcFaceOuterBound>(ptr)));
			break;

		case IFCFACESURFACE:
			f(*(std::dynamic_pointer_cast<IfcFaceSurface>(ptr)));
			break;

		case IFCFACETEDBREP:
			f(*(std::dynamic_pointer_cast<IfcFacetedBrep>(ptr)));
			break;

		case IFCFACETEDBREPWITHVOIDS:
			f(*(std::dynamic_pointer_cast<IfcFacetedBrepWithVoids>(ptr)));
			break;

		case IFCFAILURECONNECTIONCONDITION:
			f(*(std::dynamic_pointer_cast<IfcFailureConnectionCondition>(ptr)));
			break;

		case IFCFAN:
			f(*(std::dynamic_pointer_cast<IfcFan>(ptr)));
			break;

		case IFCFANTYPE:
			f(*(std::dynamic_pointer_cast<IfcFanType>(ptr)));
			break;

		case IFCFASTENER:
			f(*(std::dynamic_pointer_cast<IfcFastener>(ptr)));
			break;

		case IFCFASTENERTYPE:
			f(*(std::dynamic_pointer_cast<IfcFastenerType>(ptr)));
			break;

		case IFCFEATUREELEMENT:
			f(*(std::dynamic_pointer_cast<IfcFeatureElement>(ptr)));
			break;

		case IFCFEATUREELEMENTADDITION:
			f(*(std::dynamic_pointer_cast<IfcFeatureElementAddition>(ptr)));
			break;

		case IFCFEATUREELEMENTSUBTRACTION:
			f(*(std::dynamic_pointer_cast<IfcFeatureElementSubtraction>(ptr)));
			break;

		case IFCFILLAREASTYLE:
			f(*(std::dynamic_pointer_cast<IfcFillAreaStyle>(ptr)));
			break;

		case IFCFILLAREASTYLEHATCHING:
			f(*(std::dynamic_pointer_cast<IfcFillAreaStyleHatching>(ptr)));
			break;

		case IFCFILLAREASTYLETILES:
			f(*(std::dynamic_pointer_cast<IfcFillAreaStyleTiles>(ptr)));
			break;

		case IFCFILTER:
			f(*(std::dynamic_pointer_cast<IfcFilter>(ptr)));
			break;

		case IFCFILTERTYPE:
			f(*(std::dynamic_pointer_cast<IfcFilterType>(ptr)));
			break;

		case IFCFIRESUPPRESSIONTERMINAL:
			f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminal>(ptr)));
			break;

		case IFCFIRESUPPRESSIONTERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcFireSuppressionTerminalType>(ptr)));
			break;

		case IFCFIXEDREFERENCESWEPTAREASOLID:
			f(*(std::dynamic_pointer_cast<IfcFixedReferenceSweptAreaSolid>(ptr)));
			break;

		case IFCFLOWCONTROLLER:
			f(*(std::dynamic_pointer_cast<IfcFlowController>(ptr)));
			break;

		case IFCFLOWCONTROLLERTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowControllerType>(ptr)));
			break;

		case IFCFLOWFITTING:
			f(*(std::dynamic_pointer_cast<IfcFlowFitting>(ptr)));
			break;

		case IFCFLOWFITTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowFittingType>(ptr)));
			break;

		case IFCFLOWINSTRUMENT:
			f(*(std::dynamic_pointer_cast<IfcFlowInstrument>(ptr)));
			break;

		case IFCFLOWINSTRUMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowInstrumentType>(ptr)));
			break;

		case IFCFLOWMETER:
			f(*(std::dynamic_pointer_cast<IfcFlowMeter>(ptr)));
			break;

		case IFCFLOWMETERTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowMeterType>(ptr)));
			break;

		case IFCFLOWMOVINGDEVICE:
			f(*(std::dynamic_pointer_cast<IfcFlowMovingDevice>(ptr)));
			break;

		case IFCFLOWMOVINGDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowMovingDeviceType>(ptr)));
			break;

		case IFCFLOWSEGMENT:
			f(*(std::dynamic_pointer_cast<IfcFlowSegment>(ptr)));
			break;

		case IFCFLOWSEGMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowSegmentType>(ptr)));
			break;

		case IFCFLOWSTORAGEDEVICE:
			f(*(std::dynamic_pointer_cast<IfcFlowStorageDevice>(ptr)));
			break;

		case IFCFLOWSTORAGEDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowStorageDeviceType>(ptr)));
			break;

		case IFCFLOWTERMINAL:
			f(*(std::dynamic_pointer_cast<IfcFlowTerminal>(ptr)));
			break;

		case IFCFLOWTERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowTerminalType>(ptr)));
			break;

		case IFCFLOWTREATMENTDEVICE:
			f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDevice>(ptr)));
			break;

		case IFCFLOWTREATMENTDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcFlowTreatmentDeviceType>(ptr)));
			break;

		case IFCFOOTING:
			f(*(std::dynamic_pointer_cast<IfcFooting>(ptr)));
			break;

		case IFCFOOTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcFootingType>(ptr)));
			break;

		case IFCFURNISHINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcFurnishingElement>(ptr)));
			break;

		case IFCFURNISHINGELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcFurnishingElementType>(ptr)));
			break;

		case IFCFURNITURE:
			f(*(std::dynamic_pointer_cast<IfcFurniture>(ptr)));
			break;

		case IFCFURNITURETYPE:
			f(*(std::dynamic_pointer_cast<IfcFurnitureType>(ptr)));
			break;

		case IFCGEOGRAPHICELEMENT:
			f(*(std::dynamic_pointer_cast<IfcGeographicElement>(ptr)));
			break;

		case IFCGEOGRAPHICELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcGeographicElementType>(ptr)));
			break;

		case IFCGEOMETRICCURVESET:
			f(*(std::dynamic_pointer_cast<IfcGeometricCurveSet>(ptr)));
			break;

		case IFCGEOMETRICREPRESENTATIONCONTEXT:
			f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationContext>(ptr)));
			break;

		case IFCGEOMETRICREPRESENTATIONITEM:
			f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationItem>(ptr)));
			break;

		case IFCGEOMETRICREPRESENTATIONSUBCONTEXT:
			f(*(std::dynamic_pointer_cast<IfcGeometricRepresentationSubContext>(ptr)));
			break;

		case IFCGEOMETRICSET:
			f(*(std::dynamic_pointer_cast<IfcGeometricSet>(ptr)));
			break;

		case IFCGRID:
			f(*(std::dynamic_pointer_cast<IfcGrid>(ptr)));
			break;

		case IFCGRIDAXIS:
			f(*(std::dynamic_pointer_cast<IfcGridAxis>(ptr)));
			break;

		case IFCGRIDPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcGridPlacement>(ptr)));
			break;

		case IFCGROUP:
			f(*(std::dynamic_pointer_cast<IfcGroup>(ptr)));
			break;

		case IFCHALFSPACESOLID:
			f(*(std::dynamic_pointer_cast<IfcHalfSpaceSolid>(ptr)));
			break;

		case IFCHEATEXCHANGER:
			f(*(std::dynamic_pointer_cast<IfcHeatExchanger>(ptr)));
			break;

		case IFCHEATEXCHANGERTYPE:
			f(*(std::dynamic_pointer_cast<IfcHeatExchangerType>(ptr)));
			break;

		case IFCHUMIDIFIER:
			f(*(std::dynamic_pointer_cast<IfcHumidifier>(ptr)));
			break;

		case IFCHUMIDIFIERTYPE:
			f(*(std::dynamic_pointer_cast<IfcHumidifierType>(ptr)));
			break;

		case IFCISHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcIShapeProfileDef>(ptr)));
			break;

		case IFCIMAGETEXTURE:
			f(*(std::dynamic_pointer_cast<IfcImageTexture>(ptr)));
			break;

		case IFCINDEXEDCOLOURMAP:
			f(*(std::dynamic_pointer_cast<IfcIndexedColourMap>(ptr)));
			break;

		case IFCINDEXEDPOLYCURVE:
			f(*(std::dynamic_pointer_cast<IfcIndexedPolyCurve>(ptr)));
			break;

		case IFCINDEXEDPOLYGONALFACE:
			f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFace>(ptr)));
			break;

		case IFCINDEXEDPOLYGONALFACEWITHVOIDS:
			f(*(std::dynamic_pointer_cast<IfcIndexedPolygonalFaceWithVoids>(ptr)));
			break;

		case IFCINDEXEDTEXTUREMAP:
			f(*(std::dynamic_pointer_cast<IfcIndexedTextureMap>(ptr)));
			break;

		case IFCINDEXEDTRIANGLETEXTUREMAP:
			f(*(std::dynamic_pointer_cast<IfcIndexedTriangleTextureMap>(ptr)));
			break;

		case IFCINTERCEPTOR:
			f(*(std::dynamic_pointer_cast<IfcInterceptor>(ptr)));
			break;

		case IFCINTERCEPTORTYPE:
			f(*(std::dynamic_pointer_cast<IfcInterceptorType>(ptr)));
			break;

		case IFCINTERSECTIONCURVE:
			f(*(std::dynamic_pointer_cast<IfcIntersectionCurve>(ptr)));
			break;

		case IFCINVENTORY:
			f(*(std::dynamic_pointer_cast<IfcInventory>(ptr)));
			break;

		case IFCIRREGULARTIMESERIES:
			f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeries>(ptr)));
			break;

		case IFCIRREGULARTIMESERIESVALUE:
			f(*(std::dynamic_pointer_cast<IfcIrregularTimeSeriesValue>(ptr)));
			break;

		case IFCJUNCTIONBOX:
			f(*(std::dynamic_pointer_cast<IfcJunctionBox>(ptr)));
			break;

		case IFCJUNCTIONBOXTYPE:
			f(*(std::dynamic_pointer_cast<IfcJunctionBoxType>(ptr)));
			break;

		case IFCLSHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcLShapeProfileDef>(ptr)));
			break;

		case IFCLABORRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcLaborResource>(ptr)));
			break;

		case IFCLABORRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcLaborResourceType>(ptr)));
			break;

		case IFCLAGTIME:
			f(*(std::dynamic_pointer_cast<IfcLagTime>(ptr)));
			break;

		case IFCLAMP:
			f(*(std::dynamic_pointer_cast<IfcLamp>(ptr)));
			break;

		case IFCLAMPTYPE:
			f(*(std::dynamic_pointer_cast<IfcLampType>(ptr)));
			break;

		case IFCLIBRARYINFORMATION:
			f(*(std::dynamic_pointer_cast<IfcLibraryInformation>(ptr)));
			break;

		case IFCLIBRARYREFERENCE:
			f(*(std::dynamic_pointer_cast<IfcLibraryReference>(ptr)));
			break;

		case IFCLIGHTDISTRIBUTIONDATA:
			f(*(std::dynamic_pointer_cast<IfcLightDistributionData>(ptr)));
			break;

		case IFCLIGHTFIXTURE:
			f(*(std::dynamic_pointer_cast<IfcLightFixture>(ptr)));
			break;

		case IFCLIGHTFIXTURETYPE:
			f(*(std::dynamic_pointer_cast<IfcLightFixtureType>(ptr)));
			break;

		case IFCLIGHTINTENSITYDISTRIBUTION:
			f(*(std::dynamic_pointer_cast<IfcLightIntensityDistribution>(ptr)));
			break;

		case IFCLIGHTSOURCE:
			f(*(std::dynamic_pointer_cast<IfcLightSource>(ptr)));
			break;

		case IFCLIGHTSOURCEAMBIENT:
			f(*(std::dynamic_pointer_cast<IfcLightSourceAmbient>(ptr)));
			break;

		case IFCLIGHTSOURCEDIRECTIONAL:
			f(*(std::dynamic_pointer_cast<IfcLightSourceDirectional>(ptr)));
			break;

		case IFCLIGHTSOURCEGONIOMETRIC:
			f(*(std::dynamic_pointer_cast<IfcLightSourceGoniometric>(ptr)));
			break;

		case IFCLIGHTSOURCEPOSITIONAL:
			f(*(std::dynamic_pointer_cast<IfcLightSourcePositional>(ptr)));
			break;

		case IFCLIGHTSOURCESPOT:
			f(*(std::dynamic_pointer_cast<IfcLightSourceSpot>(ptr)));
			break;

		case IFCLINE:
			f(*(std::dynamic_pointer_cast<IfcLine>(ptr)));
			break;

		case IFCLINESEGMENT2D:
			f(*(std::dynamic_pointer_cast<IfcLineSegment2D>(ptr)));
			break;

		case IFCLINEARPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcLinearPlacement>(ptr)));
			break;

		case IFCLINEARPOSITIONINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcLinearPositioningElement>(ptr)));
			break;

		case IFCLOCALPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcLocalPlacement>(ptr)));
			break;

		case IFCLOOP:
			f(*(std::dynamic_pointer_cast<IfcLoop>(ptr)));
			break;

		case IFCMANIFOLDSOLIDBREP:
			f(*(std::dynamic_pointer_cast<IfcManifoldSolidBrep>(ptr)));
			break;

		case IFCMAPCONVERSION:
			f(*(std::dynamic_pointer_cast<IfcMapConversion>(ptr)));
			break;

		case IFCMAPPEDITEM:
			f(*(std::dynamic_pointer_cast<IfcMappedItem>(ptr)));
			break;

		case IFCMATERIAL:
			f(*(std::dynamic_pointer_cast<IfcMaterial>(ptr)));
			break;

		case IFCMATERIALCLASSIFICATIONRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcMaterialClassificationRelationship>(ptr)));
			break;

		case IFCMATERIALCONSTITUENT:
			f(*(std::dynamic_pointer_cast<IfcMaterialConstituent>(ptr)));
			break;

		case IFCMATERIALCONSTITUENTSET:
			f(*(std::dynamic_pointer_cast<IfcMaterialConstituentSet>(ptr)));
			break;

		case IFCMATERIALDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcMaterialDefinition>(ptr)));
			break;

		case IFCMATERIALDEFINITIONREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcMaterialDefinitionRepresentation>(ptr)));
			break;

		case IFCMATERIALLAYER:
			f(*(std::dynamic_pointer_cast<IfcMaterialLayer>(ptr)));
			break;

		case IFCMATERIALLAYERSET:
			f(*(std::dynamic_pointer_cast<IfcMaterialLayerSet>(ptr)));
			break;

		case IFCMATERIALLAYERSETUSAGE:
			f(*(std::dynamic_pointer_cast<IfcMaterialLayerSetUsage>(ptr)));
			break;

		case IFCMATERIALLAYERWITHOFFSETS:
			f(*(std::dynamic_pointer_cast<IfcMaterialLayerWithOffsets>(ptr)));
			break;

		case IFCMATERIALLIST:
			f(*(std::dynamic_pointer_cast<IfcMaterialList>(ptr)));
			break;

		case IFCMATERIALPROFILE:
			f(*(std::dynamic_pointer_cast<IfcMaterialProfile>(ptr)));
			break;

		case IFCMATERIALPROFILESET:
			f(*(std::dynamic_pointer_cast<IfcMaterialProfileSet>(ptr)));
			break;

		case IFCMATERIALPROFILESETUSAGE:
			f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsage>(ptr)));
			break;

		case IFCMATERIALPROFILESETUSAGETAPERING:
			f(*(std::dynamic_pointer_cast<IfcMaterialProfileSetUsageTapering>(ptr)));
			break;

		case IFCMATERIALPROFILEWITHOFFSETS:
			f(*(std::dynamic_pointer_cast<IfcMaterialProfileWithOffsets>(ptr)));
			break;

		case IFCMATERIALPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcMaterialProperties>(ptr)));
			break;

		case IFCMATERIALRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcMaterialRelationship>(ptr)));
			break;

		case IFCMATERIALUSAGEDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcMaterialUsageDefinition>(ptr)));
			break;

		case IFCMEASUREWITHUNIT:
			f(*(std::dynamic_pointer_cast<IfcMeasureWithUnit>(ptr)));
			break;

		case IFCMECHANICALFASTENER:
			f(*(std::dynamic_pointer_cast<IfcMechanicalFastener>(ptr)));
			break;

		case IFCMECHANICALFASTENERTYPE:
			f(*(std::dynamic_pointer_cast<IfcMechanicalFastenerType>(ptr)));
			break;

		case IFCMEDICALDEVICE:
			f(*(std::dynamic_pointer_cast<IfcMedicalDevice>(ptr)));
			break;

		case IFCMEDICALDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcMedicalDeviceType>(ptr)));
			break;

		case IFCMEMBER:
			f(*(std::dynamic_pointer_cast<IfcMember>(ptr)));
			break;

		case IFCMEMBERSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcMemberStandardCase>(ptr)));
			break;

		case IFCMEMBERTYPE:
			f(*(std::dynamic_pointer_cast<IfcMemberType>(ptr)));
			break;

		case IFCMETRIC:
			f(*(std::dynamic_pointer_cast<IfcMetric>(ptr)));
			break;

		case IFCMIRROREDPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcMirroredProfileDef>(ptr)));
			break;

		case IFCMONETARYUNIT:
			f(*(std::dynamic_pointer_cast<IfcMonetaryUnit>(ptr)));
			break;

		case IFCMOTORCONNECTION:
			f(*(std::dynamic_pointer_cast<IfcMotorConnection>(ptr)));
			break;

		case IFCMOTORCONNECTIONTYPE:
			f(*(std::dynamic_pointer_cast<IfcMotorConnectionType>(ptr)));
			break;

		case IFCNAMEDUNIT:
			f(*(std::dynamic_pointer_cast<IfcNamedUnit>(ptr)));
			break;

		case IFCOBJECT:
			f(*(std::dynamic_pointer_cast<IfcObject>(ptr)));
			break;

		case IFCOBJECTDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcObjectDefinition>(ptr)));
			break;

		case IFCOBJECTPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcObjectPlacement>(ptr)));
			break;

		case IFCOBJECTIVE:
			f(*(std::dynamic_pointer_cast<IfcObjective>(ptr)));
			break;

		case IFCOCCUPANT:
			f(*(std::dynamic_pointer_cast<IfcOccupant>(ptr)));
			break;

		case IFCOFFSETCURVE:
			f(*(std::dynamic_pointer_cast<IfcOffsetCurve>(ptr)));
			break;

		case IFCOFFSETCURVE2D:
			f(*(std::dynamic_pointer_cast<IfcOffsetCurve2D>(ptr)));
			break;

		case IFCOFFSETCURVE3D:
			f(*(std::dynamic_pointer_cast<IfcOffsetCurve3D>(ptr)));
			break;

		case IFCOFFSETCURVEBYDISTANCES:
			f(*(std::dynamic_pointer_cast<IfcOffsetCurveByDistances>(ptr)));
			break;

		case IFCOPENSHELL:
			f(*(std::dynamic_pointer_cast<IfcOpenShell>(ptr)));
			break;

		case IFCOPENINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcOpeningElement>(ptr)));
			break;

		case IFCOPENINGSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcOpeningStandardCase>(ptr)));
			break;

		case IFCORGANIZATION:
			f(*(std::dynamic_pointer_cast<IfcOrganization>(ptr)));
			break;

		case IFCORGANIZATIONRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcOrganizationRelationship>(ptr)));
			break;

		case IFCORIENTATIONEXPRESSION:
			f(*(std::dynamic_pointer_cast<IfcOrientationExpression>(ptr)));
			break;

		case IFCORIENTEDEDGE:
			f(*(std::dynamic_pointer_cast<IfcOrientedEdge>(ptr)));
			break;

		case IFCOUTERBOUNDARYCURVE:
			f(*(std::dynamic_pointer_cast<IfcOuterBoundaryCurve>(ptr)));
			break;

		case IFCOUTLET:
			f(*(std::dynamic_pointer_cast<IfcOutlet>(ptr)));
			break;

		case IFCOUTLETTYPE:
			f(*(std::dynamic_pointer_cast<IfcOutletType>(ptr)));
			break;

		case IFCOWNERHISTORY:
			f(*(std::dynamic_pointer_cast<IfcOwnerHistory>(ptr)));
			break;

		case IFCPARAMETERIZEDPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcParameterizedProfileDef>(ptr)));
			break;

		case IFCPATH:
			f(*(std::dynamic_pointer_cast<IfcPath>(ptr)));
			break;

		case IFCPCURVE:
			f(*(std::dynamic_pointer_cast<IfcPcurve>(ptr)));
			break;

		case IFCPERFORMANCEHISTORY:
			f(*(std::dynamic_pointer_cast<IfcPerformanceHistory>(ptr)));
			break;

		case IFCPERMEABLECOVERINGPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcPermeableCoveringProperties>(ptr)));
			break;

		case IFCPERMIT:
			f(*(std::dynamic_pointer_cast<IfcPermit>(ptr)));
			break;

		case IFCPERSON:
			f(*(std::dynamic_pointer_cast<IfcPerson>(ptr)));
			break;

		case IFCPERSONANDORGANIZATION:
			f(*(std::dynamic_pointer_cast<IfcPersonAndOrganization>(ptr)));
			break;

		case IFCPHYSICALCOMPLEXQUANTITY:
			f(*(std::dynamic_pointer_cast<IfcPhysicalComplexQuantity>(ptr)));
			break;

		case IFCPHYSICALQUANTITY:
			f(*(std::dynamic_pointer_cast<IfcPhysicalQuantity>(ptr)));
			break;

		case IFCPHYSICALSIMPLEQUANTITY:
			f(*(std::dynamic_pointer_cast<IfcPhysicalSimpleQuantity>(ptr)));
			break;

		case IFCPILE:
			f(*(std::dynamic_pointer_cast<IfcPile>(ptr)));
			break;

		case IFCPILETYPE:
			f(*(std::dynamic_pointer_cast<IfcPileType>(ptr)));
			break;

		case IFCPIPEFITTING:
			f(*(std::dynamic_pointer_cast<IfcPipeFitting>(ptr)));
			break;

		case IFCPIPEFITTINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcPipeFittingType>(ptr)));
			break;

		case IFCPIPESEGMENT:
			f(*(std::dynamic_pointer_cast<IfcPipeSegment>(ptr)));
			break;

		case IFCPIPESEGMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcPipeSegmentType>(ptr)));
			break;

		case IFCPIXELTEXTURE:
			f(*(std::dynamic_pointer_cast<IfcPixelTexture>(ptr)));
			break;

		case IFCPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcPlacement>(ptr)));
			break;

		case IFCPLANARBOX:
			f(*(std::dynamic_pointer_cast<IfcPlanarBox>(ptr)));
			break;

		case IFCPLANAREXTENT:
			f(*(std::dynamic_pointer_cast<IfcPlanarExtent>(ptr)));
			break;

		case IFCPLANE:
			f(*(std::dynamic_pointer_cast<IfcPlane>(ptr)));
			break;

		case IFCPLATE:
			f(*(std::dynamic_pointer_cast<IfcPlate>(ptr)));
			break;

		case IFCPLATESTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcPlateStandardCase>(ptr)));
			break;

		case IFCPLATETYPE:
			f(*(std::dynamic_pointer_cast<IfcPlateType>(ptr)));
			break;

		case IFCPOINT:
			f(*(std::dynamic_pointer_cast<IfcPoint>(ptr)));
			break;

		case IFCPOINTONCURVE:
			f(*(std::dynamic_pointer_cast<IfcPointOnCurve>(ptr)));
			break;

		case IFCPOINTONSURFACE:
			f(*(std::dynamic_pointer_cast<IfcPointOnSurface>(ptr)));
			break;

		case IFCPOLYLOOP:
			f(*(std::dynamic_pointer_cast<IfcPolyLoop>(ptr)));
			break;

		case IFCPOLYGONALBOUNDEDHALFSPACE:
			f(*(std::dynamic_pointer_cast<IfcPolygonalBoundedHalfSpace>(ptr)));
			break;

		case IFCPOLYGONALFACESET:
			f(*(std::dynamic_pointer_cast<IfcPolygonalFaceSet>(ptr)));
			break;

		case IFCPOLYLINE:
			f(*(std::dynamic_pointer_cast<IfcPolyline>(ptr)));
			break;

		case IFCPORT:
			f(*(std::dynamic_pointer_cast<IfcPort>(ptr)));
			break;

		case IFCPOSITIONINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcPositioningElement>(ptr)));
			break;

		case IFCPOSTALADDRESS:
			f(*(std::dynamic_pointer_cast<IfcPostalAddress>(ptr)));
			break;

		case IFCPREDEFINEDCOLOUR:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedColour>(ptr)));
			break;

		case IFCPREDEFINEDCURVEFONT:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedCurveFont>(ptr)));
			break;

		case IFCPREDEFINEDITEM:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedItem>(ptr)));
			break;

		case IFCPREDEFINEDPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedProperties>(ptr)));
			break;

		case IFCPREDEFINEDPROPERTYSET:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedPropertySet>(ptr)));
			break;

		case IFCPREDEFINEDTEXTFONT:
			f(*(std::dynamic_pointer_cast<IfcPreDefinedTextFont>(ptr)));
			break;

		case IFCPRESENTATIONITEM:
			f(*(std::dynamic_pointer_cast<IfcPresentationItem>(ptr)));
			break;

		case IFCPRESENTATIONLAYERASSIGNMENT:
			f(*(std::dynamic_pointer_cast<IfcPresentationLayerAssignment>(ptr)));
			break;

		case IFCPRESENTATIONLAYERWITHSTYLE:
			f(*(std::dynamic_pointer_cast<IfcPresentationLayerWithStyle>(ptr)));
			break;

		case IFCPRESENTATIONSTYLE:
			f(*(std::dynamic_pointer_cast<IfcPresentationStyle>(ptr)));
			break;

		case IFCPRESENTATIONSTYLEASSIGNMENT:
			f(*(std::dynamic_pointer_cast<IfcPresentationStyleAssignment>(ptr)));
			break;

		case IFCPROCEDURE:
			f(*(std::dynamic_pointer_cast<IfcProcedure>(ptr)));
			break;

		case IFCPROCEDURETYPE:
			f(*(std::dynamic_pointer_cast<IfcProcedureType>(ptr)));
			break;

		case IFCPROCESS:
			f(*(std::dynamic_pointer_cast<IfcProcess>(ptr)));
			break;

		case IFCPRODUCT:
			f(*(std::dynamic_pointer_cast<IfcProduct>(ptr)));
			break;

		case IFCPRODUCTDEFINITIONSHAPE:
			f(*(std::dynamic_pointer_cast<IfcProductDefinitionShape>(ptr)));
			break;

		case IFCPRODUCTREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcProductRepresentation>(ptr)));
			break;

		case IFCPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcProfileDef>(ptr)));
			break;

		case IFCPROFILEPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcProfileProperties>(ptr)));
			break;

		case IFCPROJECT:
			f(*(std::dynamic_pointer_cast<IfcProject>(ptr)));
			break;

		case IFCPROJECTLIBRARY:
			f(*(std::dynamic_pointer_cast<IfcProjectLibrary>(ptr)));
			break;

		case IFCPROJECTORDER:
			f(*(std::dynamic_pointer_cast<IfcProjectOrder>(ptr)));
			break;

		case IFCPROJECTEDCRS:
			f(*(std::dynamic_pointer_cast<IfcProjectedCRS>(ptr)));
			break;

		case IFCPROJECTIONELEMENT:
			f(*(std::dynamic_pointer_cast<IfcProjectionElement>(ptr)));
			break;

		case IFCPROPERTY:
			f(*(std::dynamic_pointer_cast<IfcProperty>(ptr)));
			break;

		case IFCPROPERTYABSTRACTION:
			f(*(std::dynamic_pointer_cast<IfcPropertyAbstraction>(ptr)));
			break;

		case IFCPROPERTYBOUNDEDVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertyBoundedValue>(ptr)));
			break;

		case IFCPROPERTYDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcPropertyDefinition>(ptr)));
			break;

		case IFCPROPERTYDEPENDENCYRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcPropertyDependencyRelationship>(ptr)));
			break;

		case IFCPROPERTYENUMERATEDVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertyEnumeratedValue>(ptr)));
			break;

		case IFCPROPERTYENUMERATION:
			f(*(std::dynamic_pointer_cast<IfcPropertyEnumeration>(ptr)));
			break;

		case IFCPROPERTYLISTVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertyListValue>(ptr)));
			break;

		case IFCPROPERTYREFERENCEVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertyReferenceValue>(ptr)));
			break;

		case IFCPROPERTYSET:
			f(*(std::dynamic_pointer_cast<IfcPropertySet>(ptr)));
			break;

		case IFCPROPERTYSETDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcPropertySetDefinition>(ptr)));
			break;

		case IFCPROPERTYSETTEMPLATE:
			f(*(std::dynamic_pointer_cast<IfcPropertySetTemplate>(ptr)));
			break;

		case IFCPROPERTYSINGLEVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertySingleValue>(ptr)));
			break;

		case IFCPROPERTYTABLEVALUE:
			f(*(std::dynamic_pointer_cast<IfcPropertyTableValue>(ptr)));
			break;

		case IFCPROPERTYTEMPLATE:
			f(*(std::dynamic_pointer_cast<IfcPropertyTemplate>(ptr)));
			break;

		case IFCPROPERTYTEMPLATEDEFINITION:
			f(*(std::dynamic_pointer_cast<IfcPropertyTemplateDefinition>(ptr)));
			break;

		case IFCPROTECTIVEDEVICE:
			f(*(std::dynamic_pointer_cast<IfcProtectiveDevice>(ptr)));
			break;

		case IFCPROTECTIVEDEVICETRIPPINGUNIT:
			f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnit>(ptr)));
			break;

		case IFCPROTECTIVEDEVICETRIPPINGUNITTYPE:
			f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceTrippingUnitType>(ptr)));
			break;

		case IFCPROTECTIVEDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcProtectiveDeviceType>(ptr)));
			break;

		case IFCPROXY:
			f(*(std::dynamic_pointer_cast<IfcProxy>(ptr)));
			break;

		case IFCPUMP:
			f(*(std::dynamic_pointer_cast<IfcPump>(ptr)));
			break;

		case IFCPUMPTYPE:
			f(*(std::dynamic_pointer_cast<IfcPumpType>(ptr)));
			break;

		case IFCQUANTITYAREA:
			f(*(std::dynamic_pointer_cast<IfcQuantityArea>(ptr)));
			break;

		case IFCQUANTITYCOUNT:
			f(*(std::dynamic_pointer_cast<IfcQuantityCount>(ptr)));
			break;

		case IFCQUANTITYLENGTH:
			f(*(std::dynamic_pointer_cast<IfcQuantityLength>(ptr)));
			break;

		case IFCQUANTITYSET:
			f(*(std::dynamic_pointer_cast<IfcQuantitySet>(ptr)));
			break;

		case IFCQUANTITYTIME:
			f(*(std::dynamic_pointer_cast<IfcQuantityTime>(ptr)));
			break;

		case IFCQUANTITYVOLUME:
			f(*(std::dynamic_pointer_cast<IfcQuantityVolume>(ptr)));
			break;

		case IFCQUANTITYWEIGHT:
			f(*(std::dynamic_pointer_cast<IfcQuantityWeight>(ptr)));
			break;

		case IFCRAILING:
			f(*(std::dynamic_pointer_cast<IfcRailing>(ptr)));
			break;

		case IFCRAILINGTYPE:
			f(*(std::dynamic_pointer_cast<IfcRailingType>(ptr)));
			break;

		case IFCRAMP:
			f(*(std::dynamic_pointer_cast<IfcRamp>(ptr)));
			break;

		case IFCRAMPFLIGHT:
			f(*(std::dynamic_pointer_cast<IfcRampFlight>(ptr)));
			break;

		case IFCRAMPFLIGHTTYPE:
			f(*(std::dynamic_pointer_cast<IfcRampFlightType>(ptr)));
			break;

		case IFCRAMPTYPE:
			f(*(std::dynamic_pointer_cast<IfcRampType>(ptr)));
			break;

		case IFCRATIONALBSPLINECURVEWITHKNOTS:
			f(*(std::dynamic_pointer_cast<IfcRationalBSplineCurveWithKnots>(ptr)));
			break;

		case IFCRATIONALBSPLINESURFACEWITHKNOTS:
			f(*(std::dynamic_pointer_cast<IfcRationalBSplineSurfaceWithKnots>(ptr)));
			break;

		case IFCRECTANGLEHOLLOWPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcRectangleHollowProfileDef>(ptr)));
			break;

		case IFCRECTANGLEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcRectangleProfileDef>(ptr)));
			break;

		case IFCRECTANGULARPYRAMID:
			f(*(std::dynamic_pointer_cast<IfcRectangularPyramid>(ptr)));
			break;

		case IFCRECTANGULARTRIMMEDSURFACE:
			f(*(std::dynamic_pointer_cast<IfcRectangularTrimmedSurface>(ptr)));
			break;

		case IFCRECURRENCEPATTERN:
			f(*(std::dynamic_pointer_cast<IfcRecurrencePattern>(ptr)));
			break;

		case IFCREFERENCE:
			f(*(std::dynamic_pointer_cast<IfcReference>(ptr)));
			break;

		case IFCREFERENT:
			f(*(std::dynamic_pointer_cast<IfcReferent>(ptr)));
			break;

		case IFCREGULARTIMESERIES:
			f(*(std::dynamic_pointer_cast<IfcRegularTimeSeries>(ptr)));
			break;

		case IFCREINFORCEMENTBARPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcReinforcementBarProperties>(ptr)));
			break;

		case IFCREINFORCEMENTDEFINITIONPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcReinforcementDefinitionProperties>(ptr)));
			break;

		case IFCREINFORCINGBAR:
			f(*(std::dynamic_pointer_cast<IfcReinforcingBar>(ptr)));
			break;

		case IFCREINFORCINGBARTYPE:
			f(*(std::dynamic_pointer_cast<IfcReinforcingBarType>(ptr)));
			break;

		case IFCREINFORCINGELEMENT:
			f(*(std::dynamic_pointer_cast<IfcReinforcingElement>(ptr)));
			break;

		case IFCREINFORCINGELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcReinforcingElementType>(ptr)));
			break;

		case IFCREINFORCINGMESH:
			f(*(std::dynamic_pointer_cast<IfcReinforcingMesh>(ptr)));
			break;

		case IFCREINFORCINGMESHTYPE:
			f(*(std::dynamic_pointer_cast<IfcReinforcingMeshType>(ptr)));
			break;

		case IFCRELAGGREGATES:
			f(*(std::dynamic_pointer_cast<IfcRelAggregates>(ptr)));
			break;

		case IFCRELASSIGNS:
			f(*(std::dynamic_pointer_cast<IfcRelAssigns>(ptr)));
			break;

		case IFCRELASSIGNSTOACTOR:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToActor>(ptr)));
			break;

		case IFCRELASSIGNSTOCONTROL:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToControl>(ptr)));
			break;

		case IFCRELASSIGNSTOGROUP:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroup>(ptr)));
			break;

		case IFCRELASSIGNSTOGROUPBYFACTOR:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToGroupByFactor>(ptr)));
			break;

		case IFCRELASSIGNSTOPROCESS:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToProcess>(ptr)));
			break;

		case IFCRELASSIGNSTOPRODUCT:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToProduct>(ptr)));
			break;

		case IFCRELASSIGNSTORESOURCE:
			f(*(std::dynamic_pointer_cast<IfcRelAssignsToResource>(ptr)));
			break;

		case IFCRELASSOCIATES:
			f(*(std::dynamic_pointer_cast<IfcRelAssociates>(ptr)));
			break;

		case IFCRELASSOCIATESAPPROVAL:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesApproval>(ptr)));
			break;

		case IFCRELASSOCIATESCLASSIFICATION:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesClassification>(ptr)));
			break;

		case IFCRELASSOCIATESCONSTRAINT:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesConstraint>(ptr)));
			break;

		case IFCRELASSOCIATESDOCUMENT:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesDocument>(ptr)));
			break;

		case IFCRELASSOCIATESLIBRARY:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesLibrary>(ptr)));
			break;

		case IFCRELASSOCIATESMATERIAL:
			f(*(std::dynamic_pointer_cast<IfcRelAssociatesMaterial>(ptr)));
			break;

		case IFCRELCONNECTS:
			f(*(std::dynamic_pointer_cast<IfcRelConnects>(ptr)));
			break;

		case IFCRELCONNECTSELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsElements>(ptr)));
			break;

		case IFCRELCONNECTSPATHELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsPathElements>(ptr)));
			break;

		case IFCRELCONNECTSPORTTOELEMENT:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsPortToElement>(ptr)));
			break;

		case IFCRELCONNECTSPORTS:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsPorts>(ptr)));
			break;

		case IFCRELCONNECTSSTRUCTURALACTIVITY:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralActivity>(ptr)));
			break;

		case IFCRELCONNECTSSTRUCTURALMEMBER:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsStructuralMember>(ptr)));
			break;

		case IFCRELCONNECTSWITHECCENTRICITY:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsWithEccentricity>(ptr)));
			break;

		case IFCRELCONNECTSWITHREALIZINGELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelConnectsWithRealizingElements>(ptr)));
			break;

		case IFCRELCONTAINEDINSPATIALSTRUCTURE:
			f(*(std::dynamic_pointer_cast<IfcRelContainedInSpatialStructure>(ptr)));
			break;

		case IFCRELCOVERSBLDGELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelCoversBldgElements>(ptr)));
			break;

		case IFCRELCOVERSSPACES:
			f(*(std::dynamic_pointer_cast<IfcRelCoversSpaces>(ptr)));
			break;

		case IFCRELDECLARES:
			f(*(std::dynamic_pointer_cast<IfcRelDeclares>(ptr)));
			break;

		case IFCRELDECOMPOSES:
			f(*(std::dynamic_pointer_cast<IfcRelDecomposes>(ptr)));
			break;

		case IFCRELDEFINES:
			f(*(std::dynamic_pointer_cast<IfcRelDefines>(ptr)));
			break;

		case IFCRELDEFINESBYOBJECT:
			f(*(std::dynamic_pointer_cast<IfcRelDefinesByObject>(ptr)));
			break;

		case IFCRELDEFINESBYPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcRelDefinesByProperties>(ptr)));
			break;

		case IFCRELDEFINESBYTEMPLATE:
			f(*(std::dynamic_pointer_cast<IfcRelDefinesByTemplate>(ptr)));
			break;

		case IFCRELDEFINESBYTYPE:
			f(*(std::dynamic_pointer_cast<IfcRelDefinesByType>(ptr)));
			break;

		case IFCRELFILLSELEMENT:
			f(*(std::dynamic_pointer_cast<IfcRelFillsElement>(ptr)));
			break;

		case IFCRELFLOWCONTROLELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelFlowControlElements>(ptr)));
			break;

		case IFCRELINTERFERESELEMENTS:
			f(*(std::dynamic_pointer_cast<IfcRelInterferesElements>(ptr)));
			break;

		case IFCRELNESTS:
			f(*(std::dynamic_pointer_cast<IfcRelNests>(ptr)));
			break;

		case IFCRELPROJECTSELEMENT:
			f(*(std::dynamic_pointer_cast<IfcRelProjectsElement>(ptr)));
			break;

		case IFCRELREFERENCEDINSPATIALSTRUCTURE:
			f(*(std::dynamic_pointer_cast<IfcRelReferencedInSpatialStructure>(ptr)));
			break;

		case IFCRELSEQUENCE:
			f(*(std::dynamic_pointer_cast<IfcRelSequence>(ptr)));
			break;

		case IFCRELSERVICESBUILDINGS:
			f(*(std::dynamic_pointer_cast<IfcRelServicesBuildings>(ptr)));
			break;

		case IFCRELSPACEBOUNDARY:
			f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary>(ptr)));
			break;

		case IFCRELSPACEBOUNDARY1STLEVEL:
			f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary1stLevel>(ptr)));
			break;

		case IFCRELSPACEBOUNDARY2NDLEVEL:
			f(*(std::dynamic_pointer_cast<IfcRelSpaceBoundary2ndLevel>(ptr)));
			break;

		case IFCRELVOIDSELEMENT:
			f(*(std::dynamic_pointer_cast<IfcRelVoidsElement>(ptr)));
			break;

		case IFCRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcRelationship>(ptr)));
			break;

		case IFCREPARAMETRISEDCOMPOSITECURVESEGMENT:
			f(*(std::dynamic_pointer_cast<IfcReparametrisedCompositeCurveSegment>(ptr)));
			break;

		case IFCREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcRepresentation>(ptr)));
			break;

		case IFCREPRESENTATIONCONTEXT:
			f(*(std::dynamic_pointer_cast<IfcRepresentationContext>(ptr)));
			break;

		case IFCREPRESENTATIONITEM:
			f(*(std::dynamic_pointer_cast<IfcRepresentationItem>(ptr)));
			break;

		case IFCREPRESENTATIONMAP:
			f(*(std::dynamic_pointer_cast<IfcRepresentationMap>(ptr)));
			break;

		case IFCRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcResource>(ptr)));
			break;

		case IFCRESOURCEAPPROVALRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcResourceApprovalRelationship>(ptr)));
			break;

		case IFCRESOURCECONSTRAINTRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcResourceConstraintRelationship>(ptr)));
			break;

		case IFCRESOURCELEVELRELATIONSHIP:
			f(*(std::dynamic_pointer_cast<IfcResourceLevelRelationship>(ptr)));
			break;

		case IFCRESOURCETIME:
			f(*(std::dynamic_pointer_cast<IfcResourceTime>(ptr)));
			break;

		case IFCREVOLVEDAREASOLID:
			f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolid>(ptr)));
			break;

		case IFCREVOLVEDAREASOLIDTAPERED:
			f(*(std::dynamic_pointer_cast<IfcRevolvedAreaSolidTapered>(ptr)));
			break;

		case IFCRIGHTCIRCULARCONE:
			f(*(std::dynamic_pointer_cast<IfcRightCircularCone>(ptr)));
			break;

		case IFCRIGHTCIRCULARCYLINDER:
			f(*(std::dynamic_pointer_cast<IfcRightCircularCylinder>(ptr)));
			break;

		case IFCROOF:
			f(*(std::dynamic_pointer_cast<IfcRoof>(ptr)));
			break;

		case IFCROOFTYPE:
			f(*(std::dynamic_pointer_cast<IfcRoofType>(ptr)));
			break;

		case IFCROOT:
			f(*(std::dynamic_pointer_cast<IfcRoot>(ptr)));
			break;

		case IFCROUNDEDRECTANGLEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcRoundedRectangleProfileDef>(ptr)));
			break;

		case IFCSIUNIT:
			f(*(std::dynamic_pointer_cast<IfcSIUnit>(ptr)));
			break;

		case IFCSANITARYTERMINAL:
			f(*(std::dynamic_pointer_cast<IfcSanitaryTerminal>(ptr)));
			break;

		case IFCSANITARYTERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcSanitaryTerminalType>(ptr)));
			break;

		case IFCSCHEDULINGTIME:
			f(*(std::dynamic_pointer_cast<IfcSchedulingTime>(ptr)));
			break;

		case IFCSEAMCURVE:
			f(*(std::dynamic_pointer_cast<IfcSeamCurve>(ptr)));
			break;

		case IFCSECTIONPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcSectionProperties>(ptr)));
			break;

		case IFCSECTIONREINFORCEMENTPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcSectionReinforcementProperties>(ptr)));
			break;

		case IFCSECTIONEDSOLID:
			f(*(std::dynamic_pointer_cast<IfcSectionedSolid>(ptr)));
			break;

		case IFCSECTIONEDSOLIDHORIZONTAL:
			f(*(std::dynamic_pointer_cast<IfcSectionedSolidHorizontal>(ptr)));
			break;

		case IFCSECTIONEDSPINE:
			f(*(std::dynamic_pointer_cast<IfcSectionedSpine>(ptr)));
			break;

		case IFCSENSOR:
			f(*(std::dynamic_pointer_cast<IfcSensor>(ptr)));
			break;

		case IFCSENSORTYPE:
			f(*(std::dynamic_pointer_cast<IfcSensorType>(ptr)));
			break;

		case IFCSHADINGDEVICE:
			f(*(std::dynamic_pointer_cast<IfcShadingDevice>(ptr)));
			break;

		case IFCSHADINGDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcShadingDeviceType>(ptr)));
			break;

		case IFCSHAPEASPECT:
			f(*(std::dynamic_pointer_cast<IfcShapeAspect>(ptr)));
			break;

		case IFCSHAPEMODEL:
			f(*(std::dynamic_pointer_cast<IfcShapeModel>(ptr)));
			break;

		case IFCSHAPEREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcShapeRepresentation>(ptr)));
			break;

		case IFCSHELLBASEDSURFACEMODEL:
			f(*(std::dynamic_pointer_cast<IfcShellBasedSurfaceModel>(ptr)));
			break;

		case IFCSIMPLEPROPERTY:
			f(*(std::dynamic_pointer_cast<IfcSimpleProperty>(ptr)));
			break;

		case IFCSIMPLEPROPERTYTEMPLATE:
			f(*(std::dynamic_pointer_cast<IfcSimplePropertyTemplate>(ptr)));
			break;

		case IFCSITE:
			f(*(std::dynamic_pointer_cast<IfcSite>(ptr)));
			break;

		case IFCSLAB:
			f(*(std::dynamic_pointer_cast<IfcSlab>(ptr)));
			break;

		case IFCSLABELEMENTEDCASE:
			f(*(std::dynamic_pointer_cast<IfcSlabElementedCase>(ptr)));
			break;

		case IFCSLABSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcSlabStandardCase>(ptr)));
			break;

		case IFCSLABTYPE:
			f(*(std::dynamic_pointer_cast<IfcSlabType>(ptr)));
			break;

		case IFCSLIPPAGECONNECTIONCONDITION:
			f(*(std::dynamic_pointer_cast<IfcSlippageConnectionCondition>(ptr)));
			break;

		case IFCSOLARDEVICE:
			f(*(std::dynamic_pointer_cast<IfcSolarDevice>(ptr)));
			break;

		case IFCSOLARDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcSolarDeviceType>(ptr)));
			break;

		case IFCSOLIDMODEL:
			f(*(std::dynamic_pointer_cast<IfcSolidModel>(ptr)));
			break;

		case IFCSPACE:
			f(*(std::dynamic_pointer_cast<IfcSpace>(ptr)));
			break;

		case IFCSPACEHEATER:
			f(*(std::dynamic_pointer_cast<IfcSpaceHeater>(ptr)));
			break;

		case IFCSPACEHEATERTYPE:
			f(*(std::dynamic_pointer_cast<IfcSpaceHeaterType>(ptr)));
			break;

		case IFCSPACETYPE:
			f(*(std::dynamic_pointer_cast<IfcSpaceType>(ptr)));
			break;

		case IFCSPATIALELEMENT:
			f(*(std::dynamic_pointer_cast<IfcSpatialElement>(ptr)));
			break;

		case IFCSPATIALELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcSpatialElementType>(ptr)));
			break;

		case IFCSPATIALSTRUCTUREELEMENT:
			f(*(std::dynamic_pointer_cast<IfcSpatialStructureElement>(ptr)));
			break;

		case IFCSPATIALSTRUCTUREELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcSpatialStructureElementType>(ptr)));
			break;

		case IFCSPATIALZONE:
			f(*(std::dynamic_pointer_cast<IfcSpatialZone>(ptr)));
			break;

		case IFCSPATIALZONETYPE:
			f(*(std::dynamic_pointer_cast<IfcSpatialZoneType>(ptr)));
			break;

		case IFCSPHERE:
			f(*(std::dynamic_pointer_cast<IfcSphere>(ptr)));
			break;

		case IFCSPHERICALSURFACE:
			f(*(std::dynamic_pointer_cast<IfcSphericalSurface>(ptr)));
			break;

		case IFCSTACKTERMINAL:
			f(*(std::dynamic_pointer_cast<IfcStackTerminal>(ptr)));
			break;

		case IFCSTACKTERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcStackTerminalType>(ptr)));
			break;

		case IFCSTAIR:
			f(*(std::dynamic_pointer_cast<IfcStair>(ptr)));
			break;

		case IFCSTAIRFLIGHT:
			f(*(std::dynamic_pointer_cast<IfcStairFlight>(ptr)));
			break;

		case IFCSTAIRFLIGHTTYPE:
			f(*(std::dynamic_pointer_cast<IfcStairFlightType>(ptr)));
			break;

		case IFCSTAIRTYPE:
			f(*(std::dynamic_pointer_cast<IfcStairType>(ptr)));
			break;

		case IFCSTRUCTURALACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralAction>(ptr)));
			break;

		case IFCSTRUCTURALACTIVITY:
			f(*(std::dynamic_pointer_cast<IfcStructuralActivity>(ptr)));
			break;

		case IFCSTRUCTURALANALYSISMODEL:
			f(*(std::dynamic_pointer_cast<IfcStructuralAnalysisModel>(ptr)));
			break;

		case IFCSTRUCTURALCONNECTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralConnection>(ptr)));
			break;

		case IFCSTRUCTURALCONNECTIONCONDITION:
			f(*(std::dynamic_pointer_cast<IfcStructuralConnectionCondition>(ptr)));
			break;

		case IFCSTRUCTURALCURVEACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralCurveAction>(ptr)));
			break;

		case IFCSTRUCTURALCURVECONNECTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralCurveConnection>(ptr)));
			break;

		case IFCSTRUCTURALCURVEMEMBER:
			f(*(std::dynamic_pointer_cast<IfcStructuralCurveMember>(ptr)));
			break;

		case IFCSTRUCTURALCURVEMEMBERVARYING:
			f(*(std::dynamic_pointer_cast<IfcStructuralCurveMemberVarying>(ptr)));
			break;

		case IFCSTRUCTURALCURVEREACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralCurveReaction>(ptr)));
			break;

		case IFCSTRUCTURALITEM:
			f(*(std::dynamic_pointer_cast<IfcStructuralItem>(ptr)));
			break;

		case IFCSTRUCTURALLINEARACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralLinearAction>(ptr)));
			break;

		case IFCSTRUCTURALLOAD:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoad>(ptr)));
			break;

		case IFCSTRUCTURALLOADCASE:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadCase>(ptr)));
			break;

		case IFCSTRUCTURALLOADCONFIGURATION:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadConfiguration>(ptr)));
			break;

		case IFCSTRUCTURALLOADGROUP:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadGroup>(ptr)));
			break;

		case IFCSTRUCTURALLOADLINEARFORCE:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadLinearForce>(ptr)));
			break;

		case IFCSTRUCTURALLOADORRESULT:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadOrResult>(ptr)));
			break;

		case IFCSTRUCTURALLOADPLANARFORCE:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadPlanarForce>(ptr)));
			break;

		case IFCSTRUCTURALLOADSINGLEDISPLACEMENT:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacement>(ptr)));
			break;

		case IFCSTRUCTURALLOADSINGLEDISPLACEMENTDISTORTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleDisplacementDistortion>(ptr)));
			break;

		case IFCSTRUCTURALLOADSINGLEFORCE:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForce>(ptr)));
			break;

		case IFCSTRUCTURALLOADSINGLEFORCEWARPING:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadSingleForceWarping>(ptr)));
			break;

		case IFCSTRUCTURALLOADSTATIC:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadStatic>(ptr)));
			break;

		case IFCSTRUCTURALLOADTEMPERATURE:
			f(*(std::dynamic_pointer_cast<IfcStructuralLoadTemperature>(ptr)));
			break;

		case IFCSTRUCTURALMEMBER:
			f(*(std::dynamic_pointer_cast<IfcStructuralMember>(ptr)));
			break;

		case IFCSTRUCTURALPLANARACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralPlanarAction>(ptr)));
			break;

		case IFCSTRUCTURALPOINTACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralPointAction>(ptr)));
			break;

		case IFCSTRUCTURALPOINTCONNECTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralPointConnection>(ptr)));
			break;

		case IFCSTRUCTURALPOINTREACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralPointReaction>(ptr)));
			break;

		case IFCSTRUCTURALREACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralReaction>(ptr)));
			break;

		case IFCSTRUCTURALRESULTGROUP:
			f(*(std::dynamic_pointer_cast<IfcStructuralResultGroup>(ptr)));
			break;

		case IFCSTRUCTURALSURFACEACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceAction>(ptr)));
			break;

		case IFCSTRUCTURALSURFACECONNECTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceConnection>(ptr)));
			break;

		case IFCSTRUCTURALSURFACEMEMBER:
			f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMember>(ptr)));
			break;

		case IFCSTRUCTURALSURFACEMEMBERVARYING:
			f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceMemberVarying>(ptr)));
			break;

		case IFCSTRUCTURALSURFACEREACTION:
			f(*(std::dynamic_pointer_cast<IfcStructuralSurfaceReaction>(ptr)));
			break;

		case IFCSTYLEMODEL:
			f(*(std::dynamic_pointer_cast<IfcStyleModel>(ptr)));
			break;

		case IFCSTYLEDITEM:
			f(*(std::dynamic_pointer_cast<IfcStyledItem>(ptr)));
			break;

		case IFCSTYLEDREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcStyledRepresentation>(ptr)));
			break;

		case IFCSUBCONTRACTRESOURCE:
			f(*(std::dynamic_pointer_cast<IfcSubContractResource>(ptr)));
			break;

		case IFCSUBCONTRACTRESOURCETYPE:
			f(*(std::dynamic_pointer_cast<IfcSubContractResourceType>(ptr)));
			break;

		case IFCSUBEDGE:
			f(*(std::dynamic_pointer_cast<IfcSubedge>(ptr)));
			break;

		case IFCSURFACE:
			f(*(std::dynamic_pointer_cast<IfcSurface>(ptr)));
			break;

		case IFCSURFACECURVE:
			f(*(std::dynamic_pointer_cast<IfcSurfaceCurve>(ptr)));
			break;

		case IFCSURFACECURVESWEPTAREASOLID:
			f(*(std::dynamic_pointer_cast<IfcSurfaceCurveSweptAreaSolid>(ptr)));
			break;

		case IFCSURFACEFEATURE:
			f(*(std::dynamic_pointer_cast<IfcSurfaceFeature>(ptr)));
			break;

		case IFCSURFACEOFLINEAREXTRUSION:
			f(*(std::dynamic_pointer_cast<IfcSurfaceOfLinearExtrusion>(ptr)));
			break;

		case IFCSURFACEOFREVOLUTION:
			f(*(std::dynamic_pointer_cast<IfcSurfaceOfRevolution>(ptr)));
			break;

		case IFCSURFACEREINFORCEMENTAREA:
			f(*(std::dynamic_pointer_cast<IfcSurfaceReinforcementArea>(ptr)));
			break;

		case IFCSURFACESTYLE:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyle>(ptr)));
			break;

		case IFCSURFACESTYLELIGHTING:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyleLighting>(ptr)));
			break;

		case IFCSURFACESTYLEREFRACTION:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRefraction>(ptr)));
			break;

		case IFCSURFACESTYLERENDERING:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyleRendering>(ptr)));
			break;

		case IFCSURFACESTYLESHADING:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyleShading>(ptr)));
			break;

		case IFCSURFACESTYLEWITHTEXTURES:
			f(*(std::dynamic_pointer_cast<IfcSurfaceStyleWithTextures>(ptr)));
			break;

		case IFCSURFACETEXTURE:
			f(*(std::dynamic_pointer_cast<IfcSurfaceTexture>(ptr)));
			break;

		case IFCSWEPTAREASOLID:
			f(*(std::dynamic_pointer_cast<IfcSweptAreaSolid>(ptr)));
			break;

		case IFCSWEPTDISKSOLID:
			f(*(std::dynamic_pointer_cast<IfcSweptDiskSolid>(ptr)));
			break;

		case IFCSWEPTDISKSOLIDPOLYGONAL:
			f(*(std::dynamic_pointer_cast<IfcSweptDiskSolidPolygonal>(ptr)));
			break;

		case IFCSWEPTSURFACE:
			f(*(std::dynamic_pointer_cast<IfcSweptSurface>(ptr)));
			break;

		case IFCSWITCHINGDEVICE:
			f(*(std::dynamic_pointer_cast<IfcSwitchingDevice>(ptr)));
			break;

		case IFCSWITCHINGDEVICETYPE:
			f(*(std::dynamic_pointer_cast<IfcSwitchingDeviceType>(ptr)));
			break;

		case IFCSYSTEM:
			f(*(std::dynamic_pointer_cast<IfcSystem>(ptr)));
			break;

		case IFCSYSTEMFURNITUREELEMENT:
			f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElement>(ptr)));
			break;

		case IFCSYSTEMFURNITUREELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcSystemFurnitureElementType>(ptr)));
			break;

		case IFCTSHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcTShapeProfileDef>(ptr)));
			break;

		case IFCTABLE:
			f(*(std::dynamic_pointer_cast<IfcTable>(ptr)));
			break;

		case IFCTABLECOLUMN:
			f(*(std::dynamic_pointer_cast<IfcTableColumn>(ptr)));
			break;

		case IFCTABLEROW:
			f(*(std::dynamic_pointer_cast<IfcTableRow>(ptr)));
			break;

		case IFCTANK:
			f(*(std::dynamic_pointer_cast<IfcTank>(ptr)));
			break;

		case IFCTANKTYPE:
			f(*(std::dynamic_pointer_cast<IfcTankType>(ptr)));
			break;

		case IFCTASK:
			f(*(std::dynamic_pointer_cast<IfcTask>(ptr)));
			break;

		case IFCTASKTIME:
			f(*(std::dynamic_pointer_cast<IfcTaskTime>(ptr)));
			break;

		case IFCTASKTIMERECURRING:
			f(*(std::dynamic_pointer_cast<IfcTaskTimeRecurring>(ptr)));
			break;

		case IFCTASKTYPE:
			f(*(std::dynamic_pointer_cast<IfcTaskType>(ptr)));
			break;

		case IFCTELECOMADDRESS:
			f(*(std::dynamic_pointer_cast<IfcTelecomAddress>(ptr)));
			break;

		case IFCTENDON:
			f(*(std::dynamic_pointer_cast<IfcTendon>(ptr)));
			break;

		case IFCTENDONANCHOR:
			f(*(std::dynamic_pointer_cast<IfcTendonAnchor>(ptr)));
			break;

		case IFCTENDONANCHORTYPE:
			f(*(std::dynamic_pointer_cast<IfcTendonAnchorType>(ptr)));
			break;

		case IFCTENDONTYPE:
			f(*(std::dynamic_pointer_cast<IfcTendonType>(ptr)));
			break;

		case IFCTESSELLATEDFACESET:
			f(*(std::dynamic_pointer_cast<IfcTessellatedFaceSet>(ptr)));
			break;

		case IFCTESSELLATEDITEM:
			f(*(std::dynamic_pointer_cast<IfcTessellatedItem>(ptr)));
			break;

		case IFCTEXTLITERAL:
			f(*(std::dynamic_pointer_cast<IfcTextLiteral>(ptr)));
			break;

		case IFCTEXTLITERALWITHEXTENT:
			f(*(std::dynamic_pointer_cast<IfcTextLiteralWithExtent>(ptr)));
			break;

		case IFCTEXTSTYLE:
			f(*(std::dynamic_pointer_cast<IfcTextStyle>(ptr)));
			break;

		case IFCTEXTSTYLEFONTMODEL:
			f(*(std::dynamic_pointer_cast<IfcTextStyleFontModel>(ptr)));
			break;

		case IFCTEXTSTYLEFORDEFINEDFONT:
			f(*(std::dynamic_pointer_cast<IfcTextStyleForDefinedFont>(ptr)));
			break;

		case IFCTEXTSTYLETEXTMODEL:
			f(*(std::dynamic_pointer_cast<IfcTextStyleTextModel>(ptr)));
			break;

		case IFCTEXTURECOORDINATE:
			f(*(std::dynamic_pointer_cast<IfcTextureCoordinate>(ptr)));
			break;

		case IFCTEXTURECOORDINATEGENERATOR:
			f(*(std::dynamic_pointer_cast<IfcTextureCoordinateGenerator>(ptr)));
			break;

		case IFCTEXTUREMAP:
			f(*(std::dynamic_pointer_cast<IfcTextureMap>(ptr)));
			break;

		case IFCTEXTUREVERTEX:
			f(*(std::dynamic_pointer_cast<IfcTextureVertex>(ptr)));
			break;

		case IFCTEXTUREVERTEXLIST:
			f(*(std::dynamic_pointer_cast<IfcTextureVertexList>(ptr)));
			break;

		case IFCTIMEPERIOD:
			f(*(std::dynamic_pointer_cast<IfcTimePeriod>(ptr)));
			break;

		case IFCTIMESERIES:
			f(*(std::dynamic_pointer_cast<IfcTimeSeries>(ptr)));
			break;

		case IFCTIMESERIESVALUE:
			f(*(std::dynamic_pointer_cast<IfcTimeSeriesValue>(ptr)));
			break;

		case IFCTOPOLOGICALREPRESENTATIONITEM:
			f(*(std::dynamic_pointer_cast<IfcTopologicalRepresentationItem>(ptr)));
			break;

		case IFCTOPOLOGYREPRESENTATION:
			f(*(std::dynamic_pointer_cast<IfcTopologyRepresentation>(ptr)));
			break;

		case IFCTOROIDALSURFACE:
			f(*(std::dynamic_pointer_cast<IfcToroidalSurface>(ptr)));
			break;

		case IFCTRANSFORMER:
			f(*(std::dynamic_pointer_cast<IfcTransformer>(ptr)));
			break;

		case IFCTRANSFORMERTYPE:
			f(*(std::dynamic_pointer_cast<IfcTransformerType>(ptr)));
			break;

		case IFCTRANSITIONCURVESEGMENT2D:
			f(*(std::dynamic_pointer_cast<IfcTransitionCurveSegment2D>(ptr)));
			break;

		case IFCTRANSPORTELEMENT:
			f(*(std::dynamic_pointer_cast<IfcTransportElement>(ptr)));
			break;

		case IFCTRANSPORTELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcTransportElementType>(ptr)));
			break;

		case IFCTRAPEZIUMPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcTrapeziumProfileDef>(ptr)));
			break;

		case IFCTRIANGULATEDFACESET:
			f(*(std::dynamic_pointer_cast<IfcTriangulatedFaceSet>(ptr)));
			break;

		case IFCTRIANGULATEDIRREGULARNETWORK:
			f(*(std::dynamic_pointer_cast<IfcTriangulatedIrregularNetwork>(ptr)));
			break;

		case IFCTRIMMEDCURVE:
			f(*(std::dynamic_pointer_cast<IfcTrimmedCurve>(ptr)));
			break;

		case IFCTUBEBUNDLE:
			f(*(std::dynamic_pointer_cast<IfcTubeBundle>(ptr)));
			break;

		case IFCTUBEBUNDLETYPE:
			f(*(std::dynamic_pointer_cast<IfcTubeBundleType>(ptr)));
			break;

		case IFCTYPEOBJECT:
			f(*(std::dynamic_pointer_cast<IfcTypeObject>(ptr)));
			break;

		case IFCTYPEPROCESS:
			f(*(std::dynamic_pointer_cast<IfcTypeProcess>(ptr)));
			break;

		case IFCTYPEPRODUCT:
			f(*(std::dynamic_pointer_cast<IfcTypeProduct>(ptr)));
			break;

		case IFCTYPERESOURCE:
			f(*(std::dynamic_pointer_cast<IfcTypeResource>(ptr)));
			break;

		case IFCUSHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcUShapeProfileDef>(ptr)));
			break;

		case IFCUNITASSIGNMENT:
			f(*(std::dynamic_pointer_cast<IfcUnitAssignment>(ptr)));
			break;

		case IFCUNITARYCONTROLELEMENT:
			f(*(std::dynamic_pointer_cast<IfcUnitaryControlElement>(ptr)));
			break;

		case IFCUNITARYCONTROLELEMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcUnitaryControlElementType>(ptr)));
			break;

		case IFCUNITARYEQUIPMENT:
			f(*(std::dynamic_pointer_cast<IfcUnitaryEquipment>(ptr)));
			break;

		case IFCUNITARYEQUIPMENTTYPE:
			f(*(std::dynamic_pointer_cast<IfcUnitaryEquipmentType>(ptr)));
			break;

		case IFCVALVE:
			f(*(std::dynamic_pointer_cast<IfcValve>(ptr)));
			break;

		case IFCVALVETYPE:
			f(*(std::dynamic_pointer_cast<IfcValveType>(ptr)));
			break;

		case IFCVECTOR:
			f(*(std::dynamic_pointer_cast<IfcVector>(ptr)));
			break;

		case IFCVERTEX:
			f(*(std::dynamic_pointer_cast<IfcVertex>(ptr)));
			break;

		case IFCVERTEXLOOP:
			f(*(std::dynamic_pointer_cast<IfcVertexLoop>(ptr)));
			break;

		case IFCVERTEXPOINT:
			f(*(std::dynamic_pointer_cast<IfcVertexPoint>(ptr)));
			break;

		case IFCVIBRATIONISOLATOR:
			f(*(std::dynamic_pointer_cast<IfcVibrationIsolator>(ptr)));
			break;

		case IFCVIBRATIONISOLATORTYPE:
			f(*(std::dynamic_pointer_cast<IfcVibrationIsolatorType>(ptr)));
			break;

		case IFCVIRTUALELEMENT:
			f(*(std::dynamic_pointer_cast<IfcVirtualElement>(ptr)));
			break;

		case IFCVIRTUALGRIDINTERSECTION:
			f(*(std::dynamic_pointer_cast<IfcVirtualGridIntersection>(ptr)));
			break;

		case IFCVOIDINGFEATURE:
			f(*(std::dynamic_pointer_cast<IfcVoidingFeature>(ptr)));
			break;

		case IFCWALL:
			f(*(std::dynamic_pointer_cast<IfcWall>(ptr)));
			break;

		case IFCWALLELEMENTEDCASE:
			f(*(std::dynamic_pointer_cast<IfcWallElementedCase>(ptr)));
			break;

		case IFCWALLSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcWallStandardCase>(ptr)));
			break;

		case IFCWALLTYPE:
			f(*(std::dynamic_pointer_cast<IfcWallType>(ptr)));
			break;

		case IFCWASTETERMINAL:
			f(*(std::dynamic_pointer_cast<IfcWasteTerminal>(ptr)));
			break;

		case IFCWASTETERMINALTYPE:
			f(*(std::dynamic_pointer_cast<IfcWasteTerminalType>(ptr)));
			break;

		case IFCWINDOW:
			f(*(std::dynamic_pointer_cast<IfcWindow>(ptr)));
			break;

		case IFCWINDOWLININGPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcWindowLiningProperties>(ptr)));
			break;

		case IFCWINDOWPANELPROPERTIES:
			f(*(std::dynamic_pointer_cast<IfcWindowPanelProperties>(ptr)));
			break;

		case IFCWINDOWSTANDARDCASE:
			f(*(std::dynamic_pointer_cast<IfcWindowStandardCase>(ptr)));
			break;

		case IFCWINDOWSTYLE:
			f(*(std::dynamic_pointer_cast<IfcWindowStyle>(ptr)));
			break;

		case IFCWINDOWTYPE:
			f(*(std::dynamic_pointer_cast<IfcWindowType>(ptr)));
			break;

		case IFCWORKCALENDAR:
			f(*(std::dynamic_pointer_cast<IfcWorkCalendar>(ptr)));
			break;

		case IFCWORKCONTROL:
			f(*(std::dynamic_pointer_cast<IfcWorkControl>(ptr)));
			break;

		case IFCWORKPLAN:
			f(*(std::dynamic_pointer_cast<IfcWorkPlan>(ptr)));
			break;

		case IFCWORKSCHEDULE:
			f(*(std::dynamic_pointer_cast<IfcWorkSchedule>(ptr)));
			break;

		case IFCWORKTIME:
			f(*(std::dynamic_pointer_cast<IfcWorkTime>(ptr)));
			break;

		case IFCZSHAPEPROFILEDEF:
			f(*(std::dynamic_pointer_cast<IfcZShapeProfileDef>(ptr)));
			break;

		case IFCZONE:
			f(*(std::dynamic_pointer_cast<IfcZone>(ptr)));
			break;

		default: break;
	}
}

