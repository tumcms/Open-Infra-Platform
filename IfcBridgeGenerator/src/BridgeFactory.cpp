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

#include "BridgeFactory.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h> 
#include <cmath>  

#include "buw.BlueCore.h"

using namespace OpenInfraPlatform::IfcBridge;

BridgeFactory::BridgeFactory(void)
{
}
		
void BridgeFactory::createBridge(const std::string& filename, const bridgeDescription& bridgeDesc)
{
	ifc_model = shared_ptr<IfcBridgeModel> (new IfcBridgeModel());
	bd = shared_ptr<IfcBridgeParamter> (new IfcBridgeParamter(bridgeDesc));

	createProjectStructureBlock();
	createReferencedSectionedSpineBlock(bd);
	createAbutmentBlock(bd);
	createFoundationBlock(bd);
	createPierBlock(bd);
			
	createIfcRelContainedInSpatialStructure(bridgePart_deck, prismaticElementsSuperStructure);
	createIfcRelContainedInSpatialStructure(bridgePart_leftAbutment, substructureElementsLeftAbutment);
	createIfcRelContainedInSpatialStructure(bridgePart_rightAbutment, substructureElementsRightAbutment);
	createIfcRelContainedInSpatialStructure(bridgePart_pier, substructureElementsPier);
			
	for (int i=0; i<current_entities.size(); i++)
	{
		ifc_model->insertEntity(current_entities[i]);
	}

	exportAsStepFile(filename);
}

/************************************************************************/
/* create general information about the project				            */
/************************************************************************/
void BridgeFactory::createProjectStructureBlock()
{
	units.push_back(createIfcSIUnit());
	unit_assignment = createIfcUnitAssignment();
	project = createIfcProject();
	grc = createIfcGeometricRepresentationContext(3);
	bridge = createIfcBridge(bd);
	createIfcRelAggregates(project, bridge);
			
	bridgePart_deck = createIfcBridgePart("DECK");
	//createIfcRelAggregates(bridge, bridgePart_superStructure);
			
	bridgePart_leftAbutment = createIfcBridgePart("SUBSTRUCTURE");
	bridgePart_rightAbutment = createIfcBridgePart("SUBSTRUCTURE");
	bridgePart_pier = createIfcBridgePart("SUBSTRUCTURE");
	//createIfcRelAggregates(bridge, bridgePart_subStructure);*/

	std::vector<shared_ptr<IfcObjectDefinition>> relatedObjectsBridge;
	relatedObjectsBridge.push_back(bridgePart_deck);
	relatedObjectsBridge.push_back(bridgePart_leftAbutment);
	relatedObjectsBridge.push_back(bridgePart_rightAbutment);
	relatedObjectsBridge.push_back(bridgePart_pier);
	createIfcRelAggregates(bridge, relatedObjectsBridge);
}

shared_ptr<IfcProject> BridgeFactory::createIfcProject()
{
	shared_ptr<IfcProject> project(new IfcProject());
	project->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	project->m_Name = shared_ptr<IfcLabel>(new IfcLabel( "myProject" ) );
	project->m_UnitsInContext = unit_assignment;
	current_entities.push_back(project);
	return project;
}

shared_ptr<IfcUnitAssignment> BridgeFactory::createIfcUnitAssignment()
{
	shared_ptr<IfcUnitAssignment> unit_assignment(new IfcUnitAssignment());
	unit_assignment->m_Units = units;
	current_entities.push_back(unit_assignment);
	return unit_assignment;
}

shared_ptr<IfcProductDefinitionShape> BridgeFactory::createProductDefinitionShape(shared_ptr<IfcShapeRepresentation> shapeRepresentation)
{
	shared_ptr<IfcProductDefinitionShape> productDefinitionShape (new IfcProductDefinitionShape());
	productDefinitionShape->m_Representations.push_back(shapeRepresentation);
	current_entities.push_back(productDefinitionShape);
	return productDefinitionShape;
}

shared_ptr<IfcShapeRepresentation> BridgeFactory::createIfcShapeRepresentation(std::vector<shared_ptr<IfcRepresentationItem>> representationItems)
{
	shared_ptr<IfcShapeRepresentation> shapeRepresentation (new IfcShapeRepresentation());
	shapeRepresentation->m_ContextOfItems = grc;
	shapeRepresentation->m_Items = representationItems;
	current_entities.push_back(shapeRepresentation);
	return shapeRepresentation;
}

shared_ptr<IfcGeometricRepresentationContext> BridgeFactory::createIfcGeometricRepresentationContext (int coordinateSpaceDimension)
{
	shared_ptr<IfcGeometricRepresentationContext> grc (new IfcGeometricRepresentationContext);
	grc->m_CoordinateSpaceDimension = shared_ptr<IfcDimensionCount>(new IfcDimensionCount(coordinateSpaceDimension));
	current_entities.push_back(grc);
	return grc;
}

shared_ptr<IfcBridge> BridgeFactory::createIfcBridge(shared_ptr<IfcBridgeParamter> bd)
{
	shared_ptr<IfcBridge> bridge (new IfcBridge());
	std::string StructureIndicator = bd->bridgeProperties["StructureIndicator"];
	if (StructureIndicator == "COMPOSITE")
	{
		bridge->m_StructureIndicator = shared_ptr<IfcBridgeStructureIndicator> (new IfcBridgeStructureIndicator(IfcBridgeStructureIndicator::ENUM_COMPOSITE));
	}
	else if (StructureIndicator, "COATED")
	{
		bridge->m_StructureIndicator = shared_ptr<IfcBridgeStructureIndicator> (new IfcBridgeStructureIndicator(IfcBridgeStructureIndicator::ENUM_COATED));
	}

	std::string StructureType = bd->bridgeProperties["StructureType"];
	if (StructureType == "SLAB_BRIDGE")
	{
		bridge->m_StructureType = shared_ptr<IfcBridgeStructureType>(new IfcBridgeStructureType(IfcBridgeStructureType::ENUM_SLAB_BRIDGE));
	}

	bridge->m_Name = shared_ptr<IfcLabel>(new IfcLabel("MyBridge"));
	current_entities.push_back(bridge);
	return bridge;
}

shared_ptr<IfcBridgePart> BridgeFactory::createIfcBridgePart(std::string elementType)
{
	shared_ptr<IfcBridgePart> bridgePart (new IfcBridgePart());
	bridgePart->m_StructureIndicator = shared_ptr<IfcBridgeStructureIndicator> 
		(new IfcBridgeStructureIndicator(IfcBridgeStructureIndicator::ENUM_COMPOSITE));

	if (elementType == "DECK")
	{
		bridgePart->m_StrutureElementType = shared_ptr<IfcBridgeStructureElementType> 
			(new IfcBridgeStructureElementType(IfcBridgeStructureElementType::ENUM_DECK));
	}

	else if (elementType == "SUBSTRUCTURE")
	{
		bridgePart->m_StrutureElementType = shared_ptr<IfcBridgeStructureElementType> 
			(new IfcBridgeStructureElementType(IfcBridgeStructureElementType::ENUM_DECK /*ENUM_SUBSTRUCTURE*/));
	}
	current_entities.push_back(bridgePart);
	return bridgePart;
}

shared_ptr<IfcBridgePrismaticElement> BridgeFactory::createIfcBridgePrismaticElement(shared_ptr<IfcProductDefinitionShape> productDefinitionShape)
{
	shared_ptr<IfcBridgePrismaticElement> prismaticElement (new IfcBridgePrismaticElement());
			
	prismaticElement->m_Representation = productDefinitionShape;
	prismaticElement->m_PredefinedType = shared_ptr<IfcBridgePrismaticElementType> (new IfcBridgePrismaticElementType(IfcBridgePrismaticElementType::ENUM_SOLID_SLAB));
	current_entities.push_back(prismaticElement);
	return prismaticElement;
}

shared_ptr<IfcBridgeSubstructureElement> BridgeFactory::createIfcBridgeSubstructureElement (shared_ptr<IfcProductDefinitionShape> productDefinitionShape, std::string substructureType)
{
	shared_ptr<IfcBridgeSubstructureElement> substructureElement (new IfcBridgeSubstructureElement());

	substructureElement->m_Representation = productDefinitionShape;
	if (substructureType == "ABUTMENT")
	{
		substructureElement->m_SubstructureType = shared_ptr<IfcBridgeSubstructureElementType> 
			(new IfcBridgeSubstructureElementType(IfcBridgeSubstructureElementType::ENUM_ABUTMENT));
	}
	else if (substructureType == "PIER")
	{
		substructureElement->m_SubstructureType = shared_ptr<IfcBridgeSubstructureElementType> 
			(new IfcBridgeSubstructureElementType(IfcBridgeSubstructureElementType::ENUM_PIER));
	}

	else if (substructureType == "FOUNDATION")
	{
		substructureElement->m_SubstructureType = shared_ptr<IfcBridgeSubstructureElementType> 
			(new IfcBridgeSubstructureElementType(IfcBridgeSubstructureElementType::ENUM_FOUNDATION));
	}
	current_entities.push_back(substructureElement);
	return substructureElement;
}

/************************************************************************/
/* creates the referenced sectioned spine and all entities which depend on that spine */
/************************************************************************/
void BridgeFactory::createReferencedSectionedSpineBlock(shared_ptr<IfcBridgeParamter> bd)
{
	//create the reference curve
	IfcBridgeParamter::ReferenceCurve referenceCurve = bd->getReferenceCurve();
	int numberOfReferenceCurvePoints = sizeof(referenceCurve.points)/sizeof(referenceCurve.points[0]);
	for (int i=0; i<numberOfReferenceCurvePoints; i++){
		auto cartesianPoint = createIfcCartesianPoint(referenceCurve.points[i], 3);
		reference_curve_cartesianPoints.push_back(cartesianPoint);
	}
	curve3D = createIfcPolyline(reference_curve_cartesianPoints);
	spineCurve = createIfcReferenceCurve3D ("my_referenceCurve3D", curve3D);
			
	// create cross sections
	std::map<int, IfcBridgeParamter::CrossSection> cross_sections = bd->getCrossSectionsSet();
	for (int i=0; i<cross_sections.size(); i++){
		//create Points for the outer curve 
		int numberOfPoints = sizeof(cross_sections[i].points)/sizeof(cross_sections[i].points[0]);	
		for (int j=0; j<numberOfPoints; j++){
			auto cartesianPoint = createIfcCartesianPoint(cross_sections[i].points[j], 3);
			cross_section_cartesianPoints.push_back(cartesianPoint);
		}	
		cross_section_outerCurve = createIfcPolyline(cross_section_cartesianPoints);
		auto cross_section = createIfcArbitraryClosedProfileDef(cross_section_outerCurve);
		crossSections.push_back(cross_section);
	}

	//create cross sections positions
	curvePlacementSystem = createIfcReferenceCurvePlacementSystem("my_system", spineCurve);
	std::map<int, IfcBridgeParamter::CrossSectionsPosition>  csPositions = bd->getCrossSectionsPositionsSet();

	for (int i=0; i<csPositions.size(); i++){
		shared_ptr<IfcDirection> axis = createIfcDirection(csPositions[i].axis);
		shared_ptr<IfcDirection> refDirection = createIfcDirection(csPositions[i].refDirection);
		auto csPosition = createIfcReferenceCurvePlacement(csPositions[i].abscissa, curvePlacementSystem, axis, refDirection);
		crossSectionPositions.push_back(csPosition);		
	}
	PosCsTable = bd->pos_cs_table;
	referencedSectionedSpine = createIfcReferencedSectionedSpine();
			
	std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
	representationItems.push_back(referencedSectionedSpine);
			
	//create shape representation for this prismatic element (sectioned spine)
	shared_ptr<IfcShapeRepresentation> shapeRepresentation = createIfcShapeRepresentation(representationItems);
	//create product definition shape for this prismatic element (sectioned spine)
	shared_ptr<IfcProductDefinitionShape> productDefinitionShape = createProductDefinitionShape(shapeRepresentation);
	//create prismatic element
	shared_ptr<IfcBridgePrismaticElement> prismaticElement = createIfcBridgePrismaticElement(productDefinitionShape);
	prismaticElementsSuperStructure.push_back(prismaticElement);
	createIfcRelAggregates(prismaticElement, spineCurve);
}

void BridgeFactory::createAbutmentBlock(shared_ptr<IfcBridgeParamter>)
{
	// create abutment ground sketches
	std::map<std::string, IfcBridgeParamter::AbutmentGroundSketch> abutments = bd->getAbutments();
	int numberOfPoints;
	for (std::map<std::string, IfcBridgeParamter::AbutmentGroundSketch>::iterator it = abutments.begin() ; it != abutments.end(); ++it)
	{
		//create Points for the abutment
		numberOfPoints = sizeof(it->second.points)/sizeof(it->second.points[0]);	
		for (int j=0; j<numberOfPoints; j++)
		{
			auto cartesianPoint = createIfcCartesianPoint(it->second.points[j], 2);
			cartesianPoints.push_back(cartesianPoint);
		}	
		shared_ptr<IfcPolyline> abutment_outercurve = createIfcPolyline(cartesianPoints);
		cartesianPoints.clear();
		auto sweptAreaAbutment = createIfcArbitraryClosedProfileDef(abutment_outercurve);
		// create axis 2 placement 3d
		shared_ptr<IfcCartesianPoint> location = createIfcCartesianPoint(it->second.foundationPoint, 3);
		shared_ptr<IfcDirection> axis = createIfcDirection(bd->normal_z);
		shared_ptr<IfcDirection> refDirection = createIfcDirection(bd->normal_x);
		shared_ptr<IfcAxis2Placement3D> position = createIfcAxis2Placement3D(location, axis, refDirection);
		shared_ptr<IfcDirection> extrudedDirection = createIfcDirection(bd->normal_z);
		//create extruded area solid
			
		//double b;
		//it->first == "left" ? b = bd->start_point.coordinates[2] : b = bd->end_point.coordinates[2];
		//
		//double depth = fabs(it->second.foundationPoint.coordinates[2] - b);
			
		shared_ptr<IfcExtrudedAreaSolid> abutmentExtruded = createIfcExtrudedAreaSolid(sweptAreaAbutment, position, extrudedDirection, it->second.extrusionDepth );


		numberOfPoints = sizeof(it->second.subtractionPoints)/sizeof(it->second.subtractionPoints[0]);	
		for (int j=0; j<numberOfPoints; j++)
		{
			auto cartesianPoint = createIfcCartesianPoint(it->second.subtractionPoints[j], 2);
			cartesianPoints.push_back(cartesianPoint);
		}	
		shared_ptr<IfcPolyline> subtraction_outercurve = createIfcPolyline(cartesianPoints);
		cartesianPoints.clear();
		auto sweptAreaSubtraction = createIfcArbitraryClosedProfileDef(subtraction_outercurve);
		// create axis 2 placement 3d
		shared_ptr<IfcCartesianPoint> subtraction_location = createIfcCartesianPoint(it->second.subtractionPoint, 3);
		shared_ptr<IfcDirection> subtraction_axis = createIfcDirection(bd->normal_y);
		shared_ptr<IfcAxis2Placement3D> subtraction_position = createIfcAxis2Placement3D(subtraction_location, subtraction_axis, refDirection);
		shared_ptr<IfcDirection> extrudedSubtractionDirection = createIfcDirection(bd->normal_z);

		shared_ptr<IfcExtrudedAreaSolid> subtractionExtruded = createIfcExtrudedAreaSolid(sweptAreaSubtraction, subtraction_position, extrudedSubtractionDirection, bd->width );

		shared_ptr<IfcBooleanResult> abutment (new IfcBooleanResult());
		abutment->m_Operator = shared_ptr<IfcBooleanOperator> (new IfcBooleanOperator(IfcBooleanOperator::ENUM_DIFFERENCE));
		abutment->m_FirstOperand = abutmentExtruded;
		abutment->m_SecondOperand = subtractionExtruded;
		current_entities.push_back(abutment);

		std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
		representationItems.push_back(abutment);

		//create shape representation for this substructure element (abutment)
		shared_ptr<IfcShapeRepresentation> shapeRepresentation = createIfcShapeRepresentation(representationItems);
		//create product definition shape for this substructure element (abutment)
		shared_ptr<IfcProductDefinitionShape> productDefinitionShape = createProductDefinitionShape(shapeRepresentation);
		//create prismatic element+

		if (it->first == "left")
		{
			shared_ptr<IfcBridgeSubstructureElement> substructureElementLeftAbutment = createIfcBridgeSubstructureElement(productDefinitionShape, "ABUTMENT");
			substructureElementsLeftAbutment.push_back(substructureElementLeftAbutment);
		}

		else if (it->first == "right")
		{
			shared_ptr<IfcBridgeSubstructureElement> substructureElementRightAbutment = createIfcBridgeSubstructureElement(productDefinitionShape, "ABUTMENT");
			substructureElementsRightAbutment.push_back(substructureElementRightAbutment);
		}
		representationItems.clear();
			
			

		int numberOfPoints;
		std::map<std::string, IfcBridgeParamter::AbutmentFoundation> foundations = bd->getAbutmentFoundations();
		for (std::map<std::string, IfcBridgeParamter::AbutmentFoundation>::iterator it_f = foundations.begin() ; it_f != foundations.end(); ++it_f)
		{ 
			std::cout << "it->first: " << it->first << std::endl;
			std::cout << "it_f->first: " << it_f->first << std::endl;
			if (it->first == it_f->first)
			{
				numberOfPoints = sizeof(it_f->second.points)/sizeof(it_f->second.points[0]);
				//create Points for the abutment foundation	
				for (int j=0; j<numberOfPoints; j++)
				{
					auto cartesianPoint = createIfcCartesianPoint(it_f->second.points[j], 2);
					cartesianPoints.push_back(cartesianPoint);
				}	
				shared_ptr<IfcPolyline> foundation_outercurve = createIfcPolyline(cartesianPoints);
				cartesianPoints.clear();
				auto sweptAreaFoundation = createIfcArbitraryClosedProfileDef(foundation_outercurve);

				shared_ptr<IfcCartesianPoint> locationFoundation = createIfcCartesianPoint(it->second.foundationPoint, 3);
				shared_ptr<IfcDirection> axis = createIfcDirection(bd->normal_z);
				shared_ptr<IfcDirection> refDirection = createIfcDirection(bd->normal_x);
				shared_ptr<IfcDirection> extrudedDirectionFoundation = createIfcDirection(bd->negative_z);
				shared_ptr<IfcAxis2Placement3D> positionFoundation = createIfcAxis2Placement3D(locationFoundation, axis, refDirection);
				double depth;
				depth = it_f->second.thickness;
				shared_ptr<IfcExtrudedAreaSolid> foundationExtruded = createIfcExtrudedAreaSolid(sweptAreaFoundation, positionFoundation, extrudedDirectionFoundation, depth );
				
				representationItems.push_back(foundationExtruded);

				//create shape representation for this prismatic element (abutment)
				shared_ptr<IfcShapeRepresentation> shapeRepresentation = createIfcShapeRepresentation(representationItems);
				//create product definition shape for this prismatic element (abutment)
				shared_ptr<IfcProductDefinitionShape> productDefinitionShape = createProductDefinitionShape(shapeRepresentation);
				//create prismatic element
				shared_ptr<IfcBridgeSubstructureElement> foundation = createIfcBridgeSubstructureElement(productDefinitionShape, "FOUNDATION");
						
				if (it->first == "left")
				{
					substructureElementsLeftAbutment.push_back(foundation);
				}
				else if (it->first == "right")
				{
					substructureElementsRightAbutment.push_back(foundation);
				}
			}

		
				
		}

		////try to create foundation curve as an offset curve of the abutment
		//shared_ptr<IfcOffsetCurve3D> foundation_curve (new IfcOffsetCurve3D());
		//foundation_curve->m_BasisCurve = abutment_outercurve;
		//foundation_curve->m_Distance = shared_ptr<IfcLengthMeasure> (new IfcLengthMeasure(5));
		//foundation_curve->m_SelfIntersect = false;
		//foundation_curve->m_RefDirection = refDirection;
		//current_entities.push_back(foundation_curve);
		//auto sweptFoundationArea = createIfcArbitraryClosedProfileDef(foundation_curve);

		//shared_ptr<IfcAxis2Placement3D> position_foundation = createIfcAxis2Placement3D(location, axis, refDirection);
		//depth = 5;
		//shared_ptr<IfcExtrudedAreaSolid> foundationExtruded = createIfcExtrudedAreaSolid(sweptFoundationArea, position_foundation, extrudedDirection, depth );

		//std::vector<shared_ptr<IfcRepresentationItem>> representationItemsF;
		//representationItemsF.push_back(foundationExtruded);
		////create shape representation for this prismatic element (abutment)
		//shared_ptr<IfcShapeRepresentation> shapeRepresentationF = createIfcShapeRepresentation(representationItemsF);
		////create product definition shape for this prismatic element (abutment)
		//shared_ptr<IfcProductDefinitionShape> productDefinitionShapeF = createProductDefinitionShape(shapeRepresentationF);
		////create prismatic element
		//shared_ptr<IfcBridgePrismaticElement> prismaticElementF = createIfcBridgePrismaticElement(productDefinitionShapeF);
		//prismaticElementsSubStructure.push_back(prismaticElementF);
	}


}

void BridgeFactory::createFoundationBlock (shared_ptr<IfcBridgeParamter>)
{
			
}

void BridgeFactory::createPierBlock(shared_ptr<IfcBridgeParamter> bd)
{
	int numberOfPoints;
	std::vector<IfcBridgeParamter::Pier> pierSet = bd->getPierSet();
	for (std::vector<IfcBridgeParamter::Pier>::iterator it = pierSet.begin(); it != pierSet.end(); ++it)
	{
		numberOfPoints = sizeof(it->points)/sizeof(it->points[0]);
		for (int i=0; i<numberOfPoints; i++){
			auto cartesianPoint = createIfcCartesianPoint(it->points[i], 2);
			cartesianPoints.push_back(cartesianPoint);
		}
		shared_ptr<IfcPolyline> pier_outercurve = createIfcPolyline(cartesianPoints);
		cartesianPoints.clear();
		auto sweptAreaPier = createIfcArbitraryClosedProfileDef(pier_outercurve);

		shared_ptr<IfcCartesianPoint> locationPier = createIfcCartesianPoint(it->foundationPoint, 3);
		shared_ptr<IfcDirection> axis = createIfcDirection(bd->normal_z);
		shared_ptr<IfcDirection> refDirection = createIfcDirection(bd->normal_x);
		shared_ptr<IfcDirection> extrudedDirectionPier = createIfcDirection(bd->normal_z);
		shared_ptr<IfcAxis2Placement3D> positionPier = createIfcAxis2Placement3D(locationPier, axis, refDirection);
		shared_ptr<IfcExtrudedAreaSolid> pierExtruded = createIfcExtrudedAreaSolid(sweptAreaPier, positionPier, extrudedDirectionPier, it->extrusionDepth );
				
		std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
		representationItems.push_back(pierExtruded);
				
		//create shape representation for this substructure element (pier)
		shared_ptr<IfcShapeRepresentation> shapeRepresentationPier = createIfcShapeRepresentation(representationItems);
		//create product definition shape for this substructure element (pier)
		shared_ptr<IfcProductDefinitionShape> productDefinitionShapePier = createProductDefinitionShape(shapeRepresentationPier);
		//create substructure element
		shared_ptr<IfcBridgeSubstructureElement> pier = createIfcBridgeSubstructureElement(productDefinitionShapePier, "PIER");
		substructureElementsPier.push_back(pier);
		representationItems.clear();
		//create foundation
		for (int i=0; i<numberOfPoints; i++){
			auto cartesianPoint = createIfcCartesianPoint(it->foundation.points[i], 2);
			cartesianPoints.push_back(cartesianPoint);
		}
		shared_ptr<IfcPolyline> pier_foundation_outercurve = createIfcPolyline(cartesianPoints);
		cartesianPoints.clear();
		auto sweptAreaPierFoundation = createIfcArbitraryClosedProfileDef(pier_foundation_outercurve);
		shared_ptr<IfcDirection> extrudedDirectionPierFoundation = createIfcDirection(bd->negative_z);
		shared_ptr<IfcExtrudedAreaSolid> pierFoundationExtruded = createIfcExtrudedAreaSolid(sweptAreaPierFoundation, positionPier, extrudedDirectionPierFoundation, it->foundation.extrusionDepth);

				
				
		representationItems.push_back(pierFoundationExtruded);

		//create shape representation for the pier foundation
		shared_ptr<IfcShapeRepresentation> shapeRepresentationFoundation = createIfcShapeRepresentation(representationItems);
		//create product definition shape for this prismatic element (abutment foundation)
		shared_ptr<IfcProductDefinitionShape> productDefinitionShapeFoundation = createProductDefinitionShape(shapeRepresentationFoundation);
		//create pier foundation
		shared_ptr<IfcBridgeSubstructureElement> pierFoundation = createIfcBridgeSubstructureElement(productDefinitionShapeFoundation, "FOUNDATION");
		substructureElementsPier.push_back(pierFoundation);
	}
}

shared_ptr<IfcAxis2Placement3D> BridgeFactory::createIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint> location, shared_ptr<IfcDirection> axis, shared_ptr<IfcDirection> refDirection)
{
	shared_ptr<IfcAxis2Placement3D> axis2Placement3D (new IfcAxis2Placement3D());
	axis2Placement3D->m_Location = location;
	axis2Placement3D->m_Axis = axis;
	axis2Placement3D->m_RefDirection = refDirection;
	current_entities.push_back(axis2Placement3D);
	return axis2Placement3D;
}

shared_ptr<IfcExtrudedAreaSolid> BridgeFactory::createIfcExtrudedAreaSolid(shared_ptr<IfcArbitraryClosedProfileDef> sweptArea, shared_ptr<IfcAxis2Placement3D> position, shared_ptr<IfcDirection> extrudedDirection, double depth)
{
	shared_ptr<IfcExtrudedAreaSolid> extrudedAreaSolid (new IfcExtrudedAreaSolid());
	extrudedAreaSolid->m_SweptArea = sweptArea;
	extrudedAreaSolid->m_Position = position;
	extrudedAreaSolid->m_ExtrudedDirection = extrudedDirection;
	shared_ptr<IfcPositiveLengthMeasure> m_depth (new IfcPositiveLengthMeasure());
	m_depth->m_value = depth;
	extrudedAreaSolid->m_Depth = m_depth;
	current_entities.push_back(extrudedAreaSolid);
	return extrudedAreaSolid;
}

shared_ptr<IfcDirection> BridgeFactory::createIfcDirection(IfcBridgeParamter::Point point)
{
	shared_ptr<IfcDirection> direction (new IfcDirection());
	for (int i=0; i<3; i++)
	{
		direction->m_DirectionRatios.push_back(point.coordinates[i]);
	}
	current_entities.push_back(direction);
	return direction;
}

shared_ptr<IfcReferenceCurvePlacement> BridgeFactory::createIfcReferenceCurvePlacement (double abscissa, shared_ptr<IfcReferenceCurvePlacementSystem> rcps,
	shared_ptr<IfcDirection> axis, shared_ptr<IfcDirection> refDirection)
{
	shared_ptr<IfcReferenceCurvePlacement> rcp (new IfcReferenceCurvePlacement());
	rcp->m_CurvilinearAbscissa = shared_ptr<IfcLengthMeasure> (new IfcLengthMeasure(abscissa));
	rcp->m_RelativeTo = rcps;
	rcp->m_Axis = axis;
	rcp->m_RefDirection = refDirection;
	current_entities.push_back(rcp);
	return rcp;
}

shared_ptr<IfcReferenceCurvePlacementSystem> BridgeFactory::createIfcReferenceCurvePlacementSystem (std::string label, shared_ptr<IfcReferenceCurve3D> basedOn)
{
	shared_ptr<IfcReferenceCurvePlacementSystem> rcps (new IfcReferenceCurvePlacementSystem());
	rcps->m_Label = label;
	rcps->m_BasedOn = basedOn;
	current_entities.push_back(rcps);
	return rcps;
}

shared_ptr<IfcReferenceCurve3D> BridgeFactory::createIfcReferenceCurve3D (std::string name, shared_ptr<IfcCurve> curve3D)
{
	shared_ptr<IfcReferenceCurve3D> rc3d (new IfcReferenceCurve3D());
	rc3d->m_Name = shared_ptr<IfcLabel> (new IfcLabel(name));
	rc3d->m_Curve3D = curve3D;
	rc3d->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	current_entities.push_back(rc3d);
	return rc3d;
}

shared_ptr<IfcCartesianPoint> BridgeFactory::createIfcCartesianPoint (IfcBridgeParamter::Point point, int dimension)
{
	shared_ptr<IfcCartesianPoint> cartesianPoint (new IfcCartesianPoint());
			
	switch (dimension){
	case 2:
		for (int i=0; i<2; i++){
			cartesianPoint->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure> (new IfcLengthMeasure(point.coordinates[i])));
		}
		break;
	case 3:
		for (int i=0; i<3; i++){
			cartesianPoint->m_Coordinates.push_back(shared_ptr<IfcLengthMeasure> (new IfcLengthMeasure(point.coordinates[i])));
		}
		break;
	}
			
	current_entities.push_back(cartesianPoint);
	return cartesianPoint;
}

shared_ptr<IfcPolyline> BridgeFactory::createIfcPolyline (std::vector<shared_ptr<IfcCartesianPoint>> points)
{

	shared_ptr<IfcPolyline> polyline (new IfcPolyline());
	for (int i=0; i<points.size(); i++){
		polyline->m_Points.push_back(points[i]);
	}
	current_entities.push_back(polyline);
	return polyline;
}

shared_ptr<IfcSIUnit> BridgeFactory::createIfcSIUnit()
{
	shared_ptr<IfcSIUnit> si_unit (new IfcSIUnit());
	si_unit->m_UnitType = shared_ptr<IfcUnitEnum> (new IfcUnitEnum(IfcUnitEnum::ENUM_LENGTHUNIT));
	si_unit->m_Name = shared_ptr<IfcSIUnitName> (new IfcSIUnitName(IfcSIUnitName::ENUM_METRE));
	current_entities.push_back(si_unit);
	return si_unit;
}

shared_ptr<IfcArbitraryClosedProfileDef> BridgeFactory::createIfcArbitraryClosedProfileDef (shared_ptr<IfcCurve> outer_curve)
{
	shared_ptr<IfcArbitraryClosedProfileDef> profile (new IfcArbitraryClosedProfileDef());
	profile->m_ProfileType = shared_ptr<IfcProfileTypeEnum>(new IfcProfileTypeEnum(IfcProfileTypeEnum::ENUM_CURVE));
	profile->m_OuterCurve = outer_curve;
	current_entities.push_back(profile);
	return profile;
}

shared_ptr<IfcReferencedSectionedSpine> BridgeFactory::createIfcReferencedSectionedSpine ()
{
	shared_ptr<IfcReferencedSectionedSpine> spine (new IfcReferencedSectionedSpine());
	spine->m_SpineCurve = spineCurve;

	for (int i=0; i<crossSectionPositions.size(); i++){
		spine->m_CrossSectionPositions.push_back(crossSectionPositions[i]);
		int csId = PosCsTable[i];
		spine->m_CrossSections.push_back(crossSections[csId]);
	}
	current_entities.push_back(spine);
	return spine;
}


	
/************************************************************************/
/* writes the step file                                                 */
/************************************************************************/
void BridgeFactory::exportAsStepFile(const std::string& filename)
{
	shared_ptr<IfcStepWriter> step_writer = shared_ptr<IfcStepWriter>(new IfcStepWriter());
	//std::stringstream::fixed;
	//std::defaultfloat;
	std::stringstream stream;
	//stream.unsetf(std::ios::floatfield);
	stream.setf(std::ios::showpoint);
	//stream.unsetf( std::ios::floatfield );
	stream.precision(4);
	step_writer->writeStream( stream, ifc_model );
			
	std::ofstream textdatei( filename );

	std::string s1 = stream.str();
	s1 = buw::replace(s1, "IFCBRIDGESUBSTRUCTUREELEMENT", "IFCBRIDGEPRISMATICELEMENT");
			
	textdatei << s1.c_str();
}

/************************************************************************/
/* creat relationships											*/
/************************************************************************/

shared_ptr<IfcRelAggregates> BridgeFactory::createIfcRelAggregates(shared_ptr<IfcObjectDefinition> relatingObject, std::vector<shared_ptr<IfcObjectDefinition>> relatedObjects)
{
	shared_ptr<IfcRelAggregates> relation (new IfcRelAggregates());
	relation->m_RelatingObject = relatingObject;
	for (int i=0; i<relatedObjects.size(); i++){
		relation->m_RelatedObjects.push_back(relatedObjects[i]);
	}
	relation->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));

	current_entities.push_back(relation);
	return relation;
}

shared_ptr<IfcRelAggregates> BridgeFactory::createIfcRelAggregates(shared_ptr<IfcObjectDefinition> relatingObject, shared_ptr<IfcObjectDefinition> relatedObject)
{
	shared_ptr<IfcRelAggregates> relation (new IfcRelAggregates());
	relation->m_RelatingObject = relatingObject;
	relation->m_RelatedObjects.push_back(relatedObject);
	relation->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	current_entities.push_back(relation);
	return relation;
}

shared_ptr<IfcRelContainedInSpatialStructure> BridgeFactory::createIfcRelContainedInSpatialStructure(shared_ptr<IfcSpatialStructureElement> relatingStructure, std::vector<shared_ptr<IfcProduct>> relatedElements)
{
	shared_ptr<IfcRelContainedInSpatialStructure> relation (new IfcRelContainedInSpatialStructure());
	relation->m_RelatingStructure = relatingStructure;
	relation->m_RelatedElements = relatedElements;
	relation->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId(CreateCompressedGuidString22()));
	current_entities.push_back(relation);
	return relation;
}

BridgeFactory::~BridgeFactory(void)
{
}
