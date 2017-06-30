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

#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeModel.h"
#include "OpenInfraPlatform/IfcBridge/model/IfcBridgeException.h"
#include "OpenInfraPlatform/IfcBridge/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcBridge/writer/IfcStepWriter.h"
#include "OpenInfraPlatform/IfcBridge/reader/IfcBridgeReader.h"
#include "OpenInfraPlatform/IfcBridge/model/UnitConverter.h"
#include "IfcBridgeParamter.h"
#include "IfcBridgeEntities.h"

using namespace OpenInfraPlatform::IfcBridge;

class BridgeFactory
{
public:
	BridgeFactory(void);
	~BridgeFactory(void);
	void createBridge(const std::string& filename, const bridgeDescription& bridgeDesc);
private:
	void exportAsStepFile(const std::string& filename);

	//methods for the Creation of entities
	void createProjectStructureBlock();
	shared_ptr<IfcShapeRepresentation> createIfcShapeRepresentation(std::vector<shared_ptr<IfcRepresentationItem>>);
	shared_ptr<IfcProject> createIfcProject();
	shared_ptr<IfcUnitAssignment> createIfcUnitAssignment();
	shared_ptr<IfcProductDefinitionShape> createProductDefinitionShape(shared_ptr<IfcShapeRepresentation>);
	shared_ptr<IfcGeometricRepresentationContext> createIfcGeometricRepresentationContext(int);
	shared_ptr<IfcBridge> createIfcBridge(shared_ptr<IfcBridgeParamter>);
	shared_ptr<IfcBridgePart> createIfcBridgePart(std::string);
	shared_ptr<IfcBridgePrismaticElement> createIfcBridgePrismaticElement (shared_ptr<IfcProductDefinitionShape>);
	shared_ptr<IfcBridgeSubstructureElement> createIfcBridgeSubstructureElement (shared_ptr<IfcProductDefinitionShape>, std::string);

	void createReferencedSectionedSpineBlock(shared_ptr<IfcBridgeParamter>);
	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint (IfcBridgeParamter::Point, int);
	shared_ptr<IfcPolyline> createIfcPolyline (std::vector<shared_ptr<IfcCartesianPoint>>);
	shared_ptr<IfcReferenceCurve3D> createIfcReferenceCurve3D (std::string, shared_ptr<IfcCurve>);
	shared_ptr<IfcDirection> createIfcDirection(IfcBridgeParamter::Point);
	shared_ptr<IfcReferenceCurvePlacement> createIfcReferenceCurvePlacement (double, shared_ptr<IfcReferenceCurvePlacementSystem>, shared_ptr<IfcDirection>, shared_ptr<IfcDirection>);
	shared_ptr<IfcReferenceCurvePlacementSystem> createIfcReferenceCurvePlacementSystem (std::string, shared_ptr<IfcReferenceCurve3D>);

	void createAbutmentBlock(shared_ptr<IfcBridgeParamter>);
	shared_ptr<IfcExtrudedAreaSolid> createIfcExtrudedAreaSolid(shared_ptr<IfcArbitraryClosedProfileDef>, shared_ptr<IfcAxis2Placement3D>, shared_ptr<IfcDirection>, double);
	shared_ptr<IfcAxis2Placement3D> createIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint>, shared_ptr<IfcDirection>, shared_ptr<IfcDirection>);

	void createFoundationBlock (shared_ptr<IfcBridgeParamter>);
	void createPierBlock(shared_ptr<IfcBridgeParamter>);
	//relationships
	shared_ptr<IfcRelAggregates> createIfcRelAggregates(shared_ptr<IfcObjectDefinition>, std::vector<shared_ptr<IfcObjectDefinition>>);
	shared_ptr<IfcRelAggregates> createIfcRelAggregates(shared_ptr<IfcObjectDefinition>, shared_ptr<IfcObjectDefinition>);
	shared_ptr<IfcRelContainedInSpatialStructure> createIfcRelContainedInSpatialStructure (shared_ptr<IfcSpatialStructureElement>, std::vector<shared_ptr<IfcProduct>>);

	shared_ptr<IfcSIUnit> createIfcSIUnit ();
	shared_ptr<IfcArbitraryClosedProfileDef> createIfcArbitraryClosedProfileDef (shared_ptr<IfcCurve>);
	shared_ptr<IfcReferencedSectionedSpine> createIfcReferencedSectionedSpine ();
	//ENTITIES
	shared_ptr<IfcBridgeModel>					ifc_model;
	shared_ptr<IfcBridgeParamter>				bd;
	shared_ptr<IfcProject>							project;
	shared_ptr<IfcUnitAssignment>					unit_assignment;
	std::vector<shared_ptr<IfcUnit>>				units;
	
	shared_ptr<IfcGeometricRepresentationContext>	grc;

	shared_ptr<IfcReferenceCurvePlacementSystem>	curvePlacementSystem;
	shared_ptr<IfcReferenceCurve3D>					spineCurve;
	std::vector<shared_ptr<IfcCartesianPoint>>		cross_section_cartesianPoints;
	std::vector<shared_ptr<IfcCartesianPoint>>		reference_curve_cartesianPoints;
	shared_ptr<IfcPolyline>							curve3D;
	shared_ptr<IfcPolyline>							cross_section_outerCurve;
	std::vector<shared_ptr<IfcArbitraryClosedProfileDef>>	crossSections;
	std::map<int, int>								PosCsTable;
	std::vector<shared_ptr<IfcReferenceCurvePlacement>> crossSectionPositions;
	shared_ptr<IfcReferencedSectionedSpine>			referencedSectionedSpine;

	std::vector<shared_ptr<IfcBridgeEntity>>			current_entities;
	std::vector<shared_ptr<IfcCartesianPoint>>		cartesianPoints;
	std::vector<shared_ptr<IfcRelAggregates>>		aggregatesRelations;
	shared_ptr<IfcBridge>							bridge;
	shared_ptr<IfcBridgePart>						bridgePart_deck;
	shared_ptr<IfcBridgePart>						bridgePart_leftAbutment;
	shared_ptr<IfcBridgePart>						bridgePart_rightAbutment;
	shared_ptr<IfcBridgePart>						bridgePart_pier;
	std::vector<shared_ptr<IfcProduct>>				prismaticElementsSuperStructure;
	std::vector<shared_ptr<IfcProduct>>				substructureElementsLeftAbutment;
	std::vector<shared_ptr<IfcProduct>>				substructureElementsRightAbutment;
	std::vector<shared_ptr<IfcProduct>>				substructureElementsPier;
	
};

