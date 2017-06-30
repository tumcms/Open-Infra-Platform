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

#include "Ifc4FileFactory.h"

#include <QtCore>
#include <QMainWindow>

using namespace OpenInfraPlatform::IfcTunnel;

std::string replace(const std::string& str, const std::string& findWhat, const std::string& replaceWith)
{
	std::string context = str;
	size_t lookHere = 0;
	size_t foundHere;
	while ((foundHere = context.find(findWhat, lookHere))
		!= std::string::npos) {
		context.replace(foundHere, findWhat.size(), replaceWith);
		lookHere = foundHere + replaceWith.size();
	}
	return context;
}

std::shared_ptr<IfcGloballyUniqueId> TunnelGeneratorIfc4::createGUID()
{
	return std::make_shared<IfcGloballyUniqueId>(CreateCompressedGuidString());
}

TunnelGeneratorIfc4::TunnelGeneratorIfc4(std::vector <t_part> tunnelparts, std::string  saveName, bool ifc4t) :
id(1),
filename_(saveName),
model_(nullptr)
{	//  create model
	model_ = std::make_shared<IfcTunnelModel>();
	shared_ptr<IfcAxis2Placement3D> axisPlacement = createIfcAxis2Placement3D(createIfcCartesianPoint(0.0f, 0.0f, 0.0f));
	shared_ptr<IfcLocalPlacement> globalPlacement = std::make_shared<IfcLocalPlacement>(id++);// this is the global-placement, because the attribute to make it relative is missing
	model_->insertEntity(globalPlacement);
	globalPlacement->m_RelativePlacement = axisPlacement;
	shared_ptr<IfcGeometricRepresentationContext> GeoRepCon = createIfcGeometricRepresentationContext(axisPlacement);
	shared_ptr<IfcOrganization> organization = createIfcOrganization();
	shared_ptr<IfcApplication> application = createIfcApplication(organization);
	shared_ptr<IfcPerson> person = createIfcPerson();
	auto personAndOrganization = createIfcPersonAndOrganization(person, organization);
	shared_ptr<IfcOwnerHistory> ownerHistory = createIfcOwnerHistory(personAndOrganization, application);

	shared_ptr<IfcProject> project = std::make_shared<IfcProject>(id++);
	insertAttributes(ownerHistory, "Tunnel Project", project);
	project->m_UnitsInContext = createIfcUnitAssignment();
	project->m_RepresentationContexts.push_back(GeoRepCon);
	model_->insertEntity(project);
	shared_ptr<IfcRelAggregates> Aggreg_ProjSite = createIfcRelAggregates(ownerHistory, project);

	/* shared coordinates - it is permissable to share common instances to reduce file size -------- */
	shared_ptr<IfcCartesianPoint> zero = createIfcCartesianPoint(0.0f, 0.0f, 0.0f);// this is in the moment the startpoint of relative coordinat-systems
	shared_ptr<IfcDirection> x_axis=createIfcDirection(1.0f, 0.0f, 0.0f);
	shared_ptr<IfcDirection> y_axis = createIfcDirection(0.0f, 1.0f, 0.0f);
	shared_ptr<IfcDirection> z_axis = createIfcDirection(0.0f, 0.0f, 1.0f);
	shared_ptr<IfcDirection> negx_axis = createIfcDirection(-1.0f, 0.0f, 0.0f);
	shared_ptr<IfcDirection> negy_axis = createIfcDirection(0.0f, -1.0f, 0.0f);
	shared_ptr<IfcDirection> negz_axis = createIfcDirection(0.0f, 0.0f, -1.0f);
	
	shared_ptr<IfcSite> site = std::make_shared<IfcSite>(id++); // site is the sourrounding of the tunnel, for example a river stones or something like that 
	insertAttributes(ownerHistory, "Tunnel Site", site);
	site->m_Description = std::make_shared<IfcText>("Site for a simple tunnel.");
	site->m_ObjectPlacement = globalPlacement;
	site->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);
	//site->m_RefLatitude=(1000,500,0);
	//site->m_RefLongitude = (54, 25, 0);
	//site->m_RefElevation = std::make_shared<IfcLengthMeasure>(10.0);
	model_->insertEntity(site);

	Aggreg_ProjSite->m_RelatedObjects.push_back(site);
	std::vector<shared_ptr<IfcRelAggregates>> aggreg;
	aggreg.push_back(createIfcRelAggregates(ownerHistory, site));
	std::vector<shared_ptr<IfcSpace>> space;// to generate ifc4 file
	std::vector<shared_ptr<IfcProxy>> proxy;// to generate ifc4 file
	std::vector<shared_ptr<IfcTunnnelInstallation>> tunnelInstall;// to generate ifc4_tunnel file
	std::vector<shared_ptr<IfcTunnelSpace>> tunnelSpace;// to generate ifc4_tunnel file
	if (ifc4t == false)
	{
		space.push_back(createIfcSpace(ownerHistory, zero, "IfcTunnel", globalPlacement));// every space and proxy can be placed relative by replacing the paramter zero and globalPlacement
		space[0]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);

		aggreg[0]->m_RelatedObjects.push_back(space[0]);
		aggreg.push_back(createIfcRelAggregates(ownerHistory, space[0]));// Aggreg has a 1:n relationship therefore we initialize it in the floor of its first arguement

		space.push_back(createIfcSpace(ownerHistory, zero, "IfcTunnelPart", globalPlacement));
		space[1]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);

		aggreg[1]->m_RelatedObjects.push_back(space[1]);
		aggreg.push_back(createIfcRelAggregates(ownerHistory, space[1]));
	}
	else
	{
		shared_ptr<IfcTunnel> tunnel = std::make_shared<IfcTunnel>(id++);
		model_->insertEntity(tunnel);
		insertAttributes(ownerHistory, "Tunnel", tunnel);
		tunnel->m_ObjectPlacement = globalPlacement;
		tunnel->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);

		aggreg[0]->m_RelatedObjects.push_back(tunnel);
		aggreg.push_back(createIfcRelAggregates(ownerHistory, tunnel));// Aggreg has a 1:n relationship therefore we initialize it in the floor of its first arguement

		shared_ptr<IfcTunnelPart> tunnelPart = std::make_shared<IfcTunnelPart>(id++);
		model_->insertEntity(tunnelPart);
		insertAttributes(ownerHistory, "Tunnelpart", tunnelPart);
		tunnelPart->m_ObjectPlacement = globalPlacement;
		tunnelPart->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);

		aggreg[1]->m_RelatedObjects.push_back(tunnelPart);
		aggreg.push_back(createIfcRelAggregates(ownerHistory, tunnelPart));
	}
	// from now on we insert the parts of the tunnel
	std::string spaceName[14];
	spaceName[1] = "FullTunnelspace"; spaceName[2] = "AnnularGapspace"; spaceName[3] = "Liningspace"; spaceName[4] = "Interiorspace"; spaceName[5] = "Clearancespace";
	spaceName[6] = "Servicespace"; spaceName[7] = "Trackspace"; spaceName[8] = "Floorspace"; spaceName[9] = "Segment"; spaceName[10] = "Traffic Light";
	spaceName[11] = "Walkway"; spaceName[12] = "Floor Concrete"; spaceName[13] = "Trackbed Concrete";
	std::vector<shared_ptr<IfcRelAggregates>> Aggreg;
	int spacecount=-1;
	int installcount=-1;
	for (int num = 0; num < tunnelparts.size(); num++)
	{
		std::vector<shared_ptr<IfcFace>> faces;
		buw::ObjReader objReader;
		objReader.load(tunnelparts[num].openName);
		buw::ReferenceCounted<buw::SimpleMesh> sm = buw::ConvertToSimpleMesh(objReader.getChunk(0));
		for (int i = 0; i < sm->GetIndexCount(); i += 3)
		{
			int i1 = sm->GetIndexDataPointer()[i];
			int i2 = sm->GetIndexDataPointer()[i + 1];
			int i3 = sm->GetIndexDataPointer()[i + 2];
			buw::VertexPosition3Normal3Texture2 v1, v2, v3;
			sm->GetVertex(i1, v1);
			sm->GetVertex(i2, v2);
			sm->GetVertex(i3, v3);
			std::vector<shared_ptr<IfcCartesianPoint>> points;
			points.push_back(createIfcCartesianPoint(v1.position.x(), v1.position.y(), v1.position.z()));
			points.push_back(createIfcCartesianPoint(v2.position.x(), v2.position.y(), v2.position.z()));
			points.push_back(createIfcCartesianPoint(v3.position.x(), v3.position.y(), v3.position.z()));
			shared_ptr<IfcPolyLoop> polyLoop = createIfcPolyLoop(points);
			shared_ptr<IfcFaceOuterBound> outerBound = createIfcFaceOuterbound(polyLoop);
			faces.push_back(createIfcFace(outerBound));
		}
		std::vector<shared_ptr<IfcRepresentationItem>> representationItems;
		representationItems.push_back(createIfcFacetedBrep(createIfcClosedShell(faces)));
		std::vector<shared_ptr<IfcRepresentation>> representation;
		representation.push_back(createIfcShapeRepresentation(representationItems, GeoRepCon));
		if (num == 0 && ifc4t==false)
		{
			spacecount++;
			space.push_back(createIfcSpace(ownerHistory, zero, spaceName[tunnelparts[num].current], globalPlacement));
			space[num+2]->m_Representation = createIfcProductDefinitionShape(representation);
			aggreg[2]->m_RelatedObjects.push_back(space[num + 2]);
			space[num+2]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);
		}
		if (num >0 && ifc4t == false)
		{			
			if (tunnelparts[num].current >= 1 && tunnelparts[num].current <= 8)
			{
				space.push_back(createIfcSpace(ownerHistory, zero, spaceName[tunnelparts[num].current], globalPlacement));
				if (tunnelparts[num].first == true)
				{
					Aggreg.push_back(createIfcRelAggregates(ownerHistory, space[tunnelparts[num].father_pos + 2]));// we only create an Aggreg if a father-element appears for the first time
				}
				spacecount++;
				space[spacecount + 2]->m_Representation = createIfcProductDefinitionShape(representation);
				Aggreg[tunnelparts[num].aggregate_pos]->m_RelatedObjects.push_back(space[spacecount + 2]);
				space[spacecount + 2]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_PARTIAL);
			}
			if (tunnelparts[num].current >= 9 && tunnelparts[num].current <= 13)// this part has the mistake, that it was not tested and that its aggreg could be wrong further we have to insert createIfcRelSpat
			{
				proxy.push_back(createIfcProxy(ownerHistory, zero, spaceName[tunnelparts[num].current], globalPlacement));
				installcount++;
				proxy[installcount]->m_Representation = createIfcProductDefinitionShape(representation);
				Aggreg[tunnelparts[num].aggregate_pos]->m_RelatedObjects.push_back(proxy[installcount]);
			}
		}
		if (num == 0 && ifc4t == true)
		{
			spacecount++;
			tunnelSpace.push_back(createIfcTunnelSpace(ownerHistory, globalPlacement, tunnelparts[num].current, zero, globalPlacement));
			aggreg[2]->m_RelatedObjects.push_back(tunnelSpace[0]);
			tunnelSpace[0]->m_Representation = createIfcProductDefinitionShape(representation);
			tunnelSpace[0]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);
		}
		if (num > 0 && ifc4t == true)
		{
			if (tunnelparts[num].current >= 1 && tunnelparts[num].current <= 8)
			{
				tunnelSpace.push_back(createIfcTunnelSpace(ownerHistory, globalPlacement, tunnelparts[num].current, zero, globalPlacement));
				if (tunnelparts[num].first == true)
				{
					Aggreg.push_back(createIfcRelAggregates(ownerHistory, tunnelSpace[tunnelparts[num].father_pos]));// we only create an Aggreg if a father-element appears for the first time
				}
				spacecount++;
				tunnelSpace[spacecount]->m_Representation = createIfcProductDefinitionShape(representation);
				tunnelSpace[spacecount]->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_PARTIAL);
				Aggreg[tunnelparts[num].aggregate_pos]->m_RelatedObjects.push_back(tunnelSpace[spacecount]);
			}
			if (tunnelparts[num].current >= 9 && tunnelparts[num].current <= 13)// this part has the mistake, that it was not tested and that its aggreg could be wrong further we need to insert createIfcRelSpat
			{
				tunnelInstall.push_back(createIfcTunnelInstallation(ownerHistory, globalPlacement, tunnelparts[num].current, zero, globalPlacement));
				installcount++;
				tunnelInstall[installcount]->m_Representation = createIfcProductDefinitionShape(representation);
				Aggreg[tunnelparts[installcount].aggregate_pos]->m_RelatedObjects.push_back(tunnelInstall[installcount]);
			}
		}
	}
}

TunnelGeneratorIfc4::~TunnelGeneratorIfc4()
{}

std::shared_ptr<TunnelGeneratorIfc4> TunnelGeneratorIfc4::create(std::vector <t_part> tunnelparts, std::string  saveName, bool ifc4t)
{
	return std::make_shared<TunnelGeneratorIfc4>(tunnelparts, saveName,ifc4t);
}

void TunnelGeneratorIfc4::store(bool ifc4t)
{
	std::string ending = "'));\n\
													ENDSEC;\n\n";
	if (ifc4t == true)
	{
		ending = "_TUNNEL'));\n\
													ENDSEC;\n\n";
	}
	std::string fakeHeader_part1 = "ISO-10303-21;\n\
HEADER;\n\
/* NOTE a valid model view name has to be asserted, replacing 'notYetAssigned' ----------------- */\n\
FILE_DESCRIPTION(\n\
	( 'ViewDefinition [notYetAssigned]'\n\
	,'Comment [manual creation of example file]'\n\
	)\n\
	, '2;3');\n\
/* NOTE standard header information according to ISO 10303-21 ---------------------------------- */\n\
FILE_NAME(\n\
	'";
	QFileInfo info(QString::fromStdString(filename_));
	std::string topicName = info.baseName().toStdString();
	std::string fakeHeader_part2 = ".ifc',\n\
	'2015-10-20T18:00:00',\n\
	('Julian Amann'),\n\
	('TUM CMS'),\n\
	'OpenInfraPlatform IFC Tunnel generator',\n\
	'reference file created for the IFC Tunnel specification');\n\
FILE_SCHEMA(('IFC4";
	std::string fakeHeader = fakeHeader_part1 + topicName + fakeHeader_part2 + ending;
	model_->setFileHeader(fakeHeader);
	// writer
	shared_ptr<IfcStepWriter> step_writer = std::make_shared<IfcStepWriter>(IfcStepWriter());
	std::stringstream stream;
	stream << std::setprecision(9) << std::showpoint << std::fixed;
	step_writer->writeStream(stream, model_);

	std::string content = stream.str();
	content = replace(content, "()", "$");
	std::ofstream textdatei(filename_);
	textdatei << content.c_str();
	textdatei.close();
}

void TunnelGeneratorIfc4::insertAttributes(shared_ptr<IfcOwnerHistory> oH, std::string name, shared_ptr<IfcObjectDefinition> pointer)
{
	pointer->m_GlobalId = createGUID();
	pointer->m_OwnerHistory = oH;
	pointer->m_Name = std::make_shared<IfcLabel>(name);
}

shared_ptr<IfcShapeRepresentation> TunnelGeneratorIfc4::createIfcShapeRepresentation(
	std::vector<shared_ptr<IfcRepresentationItem>> representationItems,
	shared_ptr<IfcRepresentationContext> context)
{
	shared_ptr<IfcShapeRepresentation> shapeRepresentation = std::make_shared<IfcShapeRepresentation>(id++);
	model_->insertEntity(shapeRepresentation);
	shapeRepresentation->m_ContextOfItems = context;
	shapeRepresentation->m_Items = representationItems;
	shapeRepresentation->m_RepresentationIdentifier = std::make_shared<IfcLabel>("test");
	shapeRepresentation->m_RepresentationType = std::make_shared<IfcLabel>("Brep");
	return shapeRepresentation;
}

shared_ptr<IfcRelContainedInSpatialStructure> TunnelGeneratorIfc4::createIfcRelSpat(shared_ptr<IfcOwnerHistory> ownerHistory, shared_ptr<IfcObjectDefinition> something)
{ //this we need for the connection between Space and Installation or between space and proxy
	shared_ptr<IfcRelContainedInSpatialStructure> relSpat = std::make_shared<IfcRelContainedInSpatialStructure>(id++);
	model_->insertEntity(relSpat);
	relSpat->m_GlobalId = createGUID();
	relSpat->m_OwnerHistory = ownerHistory;
	return relSpat;
}
shared_ptr<IfcProductDefinitionShape> TunnelGeneratorIfc4::createIfcProductDefinitionShape(std::vector<shared_ptr<IfcRepresentation>> shapeRepresentation)
{
	shared_ptr<IfcProductDefinitionShape> productDefinitionShape = std::make_shared<IfcProductDefinitionShape>(id++);
	model_->insertEntity(productDefinitionShape);
	productDefinitionShape->m_Representations = shapeRepresentation;
	return productDefinitionShape;
}
shared_ptr<IfcOrganization> TunnelGeneratorIfc4::createIfcOrganization()
{
	shared_ptr<IfcOrganization> organization = std::make_shared<IfcOrganization>(id++);
	model_->insertEntity(organization);
	organization->m_Name = std::make_shared<IfcLabel>("TUM");
	organization->m_Description = std::make_shared<IfcText>("Technische Universitaet Muenchen");
	return organization;
}

shared_ptr<IfcApplication> TunnelGeneratorIfc4::createIfcApplication(shared_ptr<IfcOrganization> applicationDeveloper)
{
	shared_ptr<IfcApplication> application = std::make_shared<IfcApplication>(id++);
	model_->insertEntity(application);
	application->m_ApplicationDeveloper = applicationDeveloper;
	application->m_Version = std::make_shared<IfcLabel>("2015");
	application->m_ApplicationFullName = std::make_shared<IfcLabel>("BlueIfcTunnelGenerator");
	application->m_ApplicationIdentifier = std::make_shared<IfcIdentifier>("BlueIfcTunnelGenerator");
	return application;
}

shared_ptr<IfcUnitAssignment> TunnelGeneratorIfc4::createIfcUnitAssignment()
{
	shared_ptr<IfcUnitAssignment> unitAssignment = std::make_shared<IfcUnitAssignment>(id++);
	model_->insertEntity(unitAssignment);

	shared_ptr<IfcSIUnit> lengthUnit = std::make_shared<IfcSIUnit>(id++);
	model_->insertEntity(lengthUnit);
	lengthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LENGTHUNIT);
	lengthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_METRE);
	// just for mechanical engineering lengthUnit->m_Prefix = std::make_shared<IfcSIPrefix>(IfcSIPrefix::ENUM_MILLI);
	unitAssignment->m_Units.push_back(lengthUnit);

	shared_ptr<IfcSIUnit> areaUnit = std::make_shared<IfcSIUnit>(id++);
	model_->insertEntity(areaUnit);
	areaUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_AREAUNIT);
	areaUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_SQUARE_METRE);
	unitAssignment->m_Units.push_back(areaUnit);

	shared_ptr<IfcSIUnit> volumeUnit = std::make_shared<IfcSIUnit>(id++);
	model_->insertEntity(volumeUnit);
	volumeUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_VOLUMEUNIT);
	volumeUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_CUBIC_METRE);
	unitAssignment->m_Units.push_back(volumeUnit);

	/*shared_ptr<IfcConversionBasedUnit> convBaseUnit = std::make_shared<IfcConversionBasedUnit>(id++);
	convBaseUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
	convBaseUnit->m_Name = std::make_shared<IfcLabel>("DEGREE");
	unitAssignment->m_Units.push_back(convBaseUnit);

	shared_ptr<IfcDimensionalExponents> dimExpo = std::make_shared<IfcDimensionalExponents>(id++);
	dimExpo->m_MassExponent=0;
	dimExpo->m_TimeExponent = 0;
	dimExpo->m_ElectricCurrentExponent = 0;
	dimExpo->m_ThermodynamicTemperatureExponent = 0;
	dimExpo->m_AmountOfSubstanceExponent = 0;
	dimExpo->m_LuminousIntensityExponent = 0;
	convBaseUnit->m_Dimensions = dimExpo;

	shared_ptr<IfcMeasureWithUnit> measur = std::make_shared<IfcMeasureWithUnit>(id++);
	measur->m_ValueComponent = std::make_shared<IfcPlaneAngleMeasure>(1.745E-2);
	convBaseUnit->m_ConversionFactor = measur;

	shared_ptr<IfcSIUnit> planeAngleUnit = std::make_shared<IfcSIUnit>(id++);
	planeAngleUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_PLANEANGLEUNIT);
	planeAngleUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_RADIAN);
	measur->m_UnitComponent = planeAngleUnit;

	shared_ptr<IfcSIUnit> solidAngleUnit = std::make_shared<IfcSIUnit>(id++);
	solidAngleUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_SOLIDANGLEUNIT);
	solidAngleUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_STERADIAN);
	unitAssignment->m_Units.push_back(solidAngleUnit);

	shared_ptr<IfcSIUnit> massUnit = std::make_shared<IfcSIUnit>(id++);
	massUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_MASSUNIT);
	massUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_GRAM);
	unitAssignment->m_Units.push_back(massUnit);

	shared_ptr<IfcSIUnit> timeUnit = std::make_shared<IfcSIUnit>(id++);
	timeUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_TIMEUNIT);
	timeUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_SECOND);
	unitAssignment->m_Units.push_back(timeUnit);

	shared_ptr<IfcSIUnit> thermoUnit = std::make_shared<IfcSIUnit>(id++);
	thermoUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_THERMODYNAMICTEMPERATUREUNIT);
	thermoUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_DEGREE_CELSIUS);
	unitAssignment->m_Units.push_back(thermoUnit);

	shared_ptr<IfcSIUnit> ligthUnit = std::make_shared<IfcSIUnit>(id++);
	ligthUnit->m_UnitType = std::make_shared<IfcUnitEnum>(IfcUnitEnum::ENUM_LUMINOUSINTENSITYUNIT);
	ligthUnit->m_Name = std::make_shared<IfcSIUnitName>(IfcSIUnitName::ENUM_LUMEN);
	unitAssignment->m_Units.push_back(ligthUnit);*/

	return unitAssignment;
}
/*shared_ptr<IfcSlab> TunnelGeneratorIfc4::createIfcSlab(shared_ptr<IfcOwnerHistory> ownerHistory, shared_ptr<IfcProductRepresentation> representation) // slab german:"Beton-Platte"
{
shared_ptr<IfcSlab> slab = std::make_shared<IfcSlab>(id++);
model_->insertEntity(slab);
slab->m_PredefinedType = std::make_shared<IfcSlabTypeEnum>(IfcSlabTypeEnum::ENUM_ROOF);
insertAttributes(owH, "Tunnel", space);
slab->m_Representation = representation;
return slab;
}
shared_ptr<IfcBuilding> TunnelGeneratorIfc4::createIfcBuilding(shared_ptr<IfcOwnerHistory> ownerHistory,
shared_ptr<IfcLocalPlacement> placemenet)
{
shared_ptr<IfcBuilding> building = std::make_shared<IfcBuilding>(id++);
model_->insertEntity(building);
insertAttributes(ownerHistory, "Default Tunnel Building", building);
building->m_Description = std::make_shared<IfcText>("Description of Default Tunnel Building");
building->m_ObjectPlacement = placemenet;
building->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_PARTIAL);
// here is missing the postaladress but because it is not so important in the moment it is okay
shared_ptr<IfcBuildingStorey> storey = std::make_shared<IfcBuildingStorey>(id++);
insertAttributes(ownerHistory, "Default Tunnel Building Storey", storey);
storey->m_Description = std::make_shared<IfcText>("Description of Default Tunnel Building Storey");
storey->m_CompositionType = std::make_shared<IfcElementCompositionEnum>(IfcElementCompositionEnum::ENUM_ELEMENT);
storey->m_Elevation = std::make_shared<IfcLengthMeasure>(0.0);
storey->m_ObjectPlacement = placemenet;
return building;
}
*/
shared_ptr<IfcSpace> TunnelGeneratorIfc4::createIfcSpace(shared_ptr<IfcOwnerHistory> owH,
	shared_ptr<IfcCartesianPoint> location, std::string name, shared_ptr<IfcObjectPlacement> relative)
{
	shared_ptr<IfcSpace> space = std::make_shared<IfcSpace>(id++);
	model_->insertEntity(space);	
	insertAttributes(owH, name, space);
	shared_ptr<IfcAxis2Placement3D> axis = createIfcAxis2Placement3D(location);
	space->m_ObjectPlacement = createIfcLocalPlacement(axis, relative);
	return space;
}

shared_ptr<IfcProxy> TunnelGeneratorIfc4::createIfcProxy(shared_ptr<IfcOwnerHistory> owH,
	shared_ptr<IfcCartesianPoint> location, std::string name, shared_ptr<IfcObjectPlacement> relative)
{
	shared_ptr<IfcProxy> prox = std::make_shared<IfcProxy>(id++);
	model_->insertEntity(prox);
	insertAttributes(owH, name, prox);
	shared_ptr<IfcAxis2Placement3D> axis = createIfcAxis2Placement3D(location);
	prox->m_ObjectPlacement = createIfcLocalPlacement(axis, relative);
	return prox;
}
shared_ptr<IfcAxis2Placement3D> TunnelGeneratorIfc4::createIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint> location)
{
	shared_ptr<IfcAxis2Placement3D> ap = std::make_shared<IfcAxis2Placement3D>(id++);
	model_->insertEntity(ap);
	ap->m_Location = location;

	return ap;
}
shared_ptr<IfcLocalPlacement> TunnelGeneratorIfc4::createIfcLocalPlacement(shared_ptr<IfcAxis2Placement3D> axisPlacement, shared_ptr<IfcObjectPlacement> relative)
{
	shared_ptr<IfcLocalPlacement> lp = std::make_shared<IfcLocalPlacement>(id++);
	model_->insertEntity(lp);
	lp->m_RelativePlacement = axisPlacement;
	lp->m_PlacementRelTo = relative;
	return lp;
}

shared_ptr<IfcRelSpaceBoundary> TunnelGeneratorIfc4::createIfcRelSpace(shared_ptr<IfcOwnerHistory> ownerHistory, shared_ptr<IfcSpaceBoundarySelect> something)
{
	shared_ptr<IfcRelSpaceBoundary> rS = std::make_shared<IfcRelSpaceBoundary>(id++);
	model_->insertEntity(rS);
	rS->m_GlobalId = createGUID();
	rS->m_OwnerHistory = ownerHistory;
	rS->m_RelatingSpace = something;
	return rS;
}
shared_ptr<IfcRelAggregates> TunnelGeneratorIfc4::createIfcRelAggregates(shared_ptr<IfcOwnerHistory> ownerHistory, shared_ptr<IfcObjectDefinition> something)
{
	shared_ptr<IfcRelAggregates> ra = std::make_shared<IfcRelAggregates>(id++);
	model_->insertEntity(ra);
	ra->m_GlobalId = createGUID();
	ra->m_OwnerHistory = ownerHistory;
	ra->m_RelatingObject = something;
	return ra;
}

shared_ptr<IfcGeometricRepresentationContext> TunnelGeneratorIfc4::createIfcGeometricRepresentationContext(shared_ptr<IfcAxis2Placement3D> ap)
{
	shared_ptr<IfcGeometricRepresentationContext> grc = std::make_shared<IfcGeometricRepresentationContext>(id++);
	model_->insertEntity(grc);
	grc->m_WorldCoordinateSystem = ap;
	grc->m_ContextType = std::make_shared<IfcLabel>("Model");
	grc->m_CoordinateSpaceDimension = std::make_shared<IfcDimensionCount>(3);
	grc->m_Precision = 1.E-9;// very important in order to see the elements in fzk-viewer
	//grc->m_TrueNorth = createIfcDirection(0.0f,1.0f,0.0f);
	return grc;
}

shared_ptr<IfcDirection> TunnelGeneratorIfc4::createIfcDirection(const float x, const float y, const float z)
{
shared_ptr<IfcDirection> dir = std::make_shared<IfcDirection>(id++);
model_->insertEntity(dir);
dir->m_DirectionRatios.push_back(x);// x-direction
dir->m_DirectionRatios.push_back(y);// y-direction
dir->m_DirectionRatios.push_back(z);// z-direction
return dir;
}
shared_ptr<IfcRepresentationContext> TunnelGeneratorIfc4::createIfcRepresentationContext()
{
	shared_ptr<IfcRepresentationContext> rc = std::make_shared<IfcRepresentationContext>(id++);
	model_->insertEntity(rc);
	return rc;
}

shared_ptr<IfcPerson> TunnelGeneratorIfc4::createIfcPerson()
{
	shared_ptr<IfcPerson> person = std::make_shared<IfcPerson>(id++);
	model_->insertEntity(person);
	person->m_FamilyName = std::make_shared<IfcLabel>("Amann");
	person->m_GivenName = std::make_shared<IfcLabel>("Julian");
	return person;
}
shared_ptr<IfcPersonAndOrganization> TunnelGeneratorIfc4::createIfcPersonAndOrganization(shared_ptr<IfcPerson> person, shared_ptr<IfcOrganization> organization)
{
	shared_ptr<IfcPersonAndOrganization> pao = std::make_shared<IfcPersonAndOrganization>(id++);
	model_->insertEntity(pao);
	pao->m_ThePerson = person;
	pao->m_TheOrganization = organization;
	return pao;
}
shared_ptr<IfcOwnerHistory> TunnelGeneratorIfc4::createIfcOwnerHistory(
	shared_ptr<IfcPersonAndOrganization> personAndOrganization,
	shared_ptr<IfcApplication> application)
{
	shared_ptr<IfcOwnerHistory> oh = std::make_shared<IfcOwnerHistory>(id++);
	model_->insertEntity(oh);
	oh->m_OwningUser = personAndOrganization;
	oh->m_OwningApplication = application;
	// oh->m_State = std::make_shared<IfcStateEnum>( IfcStateEnum::ENUM_READONLY );
	oh->m_ChangeAction = std::make_shared<IfcChangeActionEnum>(IfcChangeActionEnum::ENUM_NOCHANGE);
	oh->m_CreationDate = std::make_shared<IfcTimeStamp>(0);
	return oh;
}
shared_ptr<IfcCartesianPoint> TunnelGeneratorIfc4::createIfcCartesianPoint(
	const float x,
	const float y,
	const float z)
{
	shared_ptr<IfcCartesianPoint> point = std::make_shared<IfcCartesianPoint>(id++);
	model_->insertEntity(point);
	point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(x));
	point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(y));
	point->m_Coordinates.push_back(std::make_shared<IfcLengthMeasure>(z));
	return point;
}
shared_ptr<IfcPolyLoop> TunnelGeneratorIfc4::createIfcPolyLoop(std::vector<shared_ptr<IfcCartesianPoint>> points)
{
	shared_ptr<IfcPolyLoop> polyLoop = std::make_shared<IfcPolyLoop>(id++);
	polyLoop->m_Polygon = points;
	model_->insertEntity(polyLoop);
	return polyLoop;
}
shared_ptr<IfcFaceOuterBound> TunnelGeneratorIfc4::createIfcFaceOuterbound(shared_ptr<IfcPolyLoop> polyLoop)
{
	shared_ptr<IfcFaceOuterBound> outerBound = std::make_shared<IfcFaceOuterBound>(id++);
	model_->insertEntity(outerBound);
	outerBound->m_Bound = polyLoop;
	outerBound->m_Orientation = true;
	return outerBound;
}
shared_ptr<IfcFace> TunnelGeneratorIfc4::createIfcFace(shared_ptr<IfcFaceOuterBound> outerBound)
{
	shared_ptr<IfcFace> face = std::make_shared<IfcFace>(id++);
	model_->insertEntity(face);
	face->m_Bounds.push_back(outerBound);
	return face;
}
shared_ptr<IfcClosedShell> TunnelGeneratorIfc4::createIfcClosedShell(std::vector<shared_ptr<IfcFace>> faces)
{
	shared_ptr<IfcClosedShell> shell = std::make_shared<IfcClosedShell>(id++);
	model_->insertEntity(shell);

	shell->m_CfsFaces = faces;

	return shell;
}
shared_ptr<IfcFacetedBrep> TunnelGeneratorIfc4::createIfcFacetedBrep(shared_ptr<IfcClosedShell> closedShell)
{
	shared_ptr<IfcFacetedBrep> facetedBrep = std::make_shared<IfcFacetedBrep>(id++);
	model_->insertEntity(facetedBrep);
	facetedBrep->m_Outer = closedShell;
	return facetedBrep;
}

shared_ptr<IfcTunnnelInstallation> TunnelGeneratorIfc4::createIfcTunnelInstallation(shared_ptr<IfcOwnerHistory> owH,
	shared_ptr<IfcLocalPlacement> placemenet, int current, shared_ptr<IfcCartesianPoint> location, shared_ptr<IfcObjectPlacement> relative)
{
	shared_ptr<IfcTunnnelInstallation> inst = std::make_shared<IfcTunnnelInstallation>(id++);
	model_->insertEntity(inst);
	inst->m_ObjectPlacement = placemenet;
	std::string name;
	switch (current){// here we need some changes Floor Concrete and Segment
	case 9:	inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_SEGMENT); name = "Segment"; break;
	case 10:	inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_TRAFFICLIGHT); name = "Traffic Light"; break;
	case 11:	inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_WALKWAY); name = " Walkway"; break;
	case 12:	inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_FLOORCONCRETE); name = "Floor Concrete"; break;
	case 13:	inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_TRACKBEDCONCRETE); name = "Trackbed Concrete"; break;
	default:inst->m_TunnelInstallationType = std::make_shared<IfcTunnelInstallationEnum>(IfcTunnelInstallationEnum::ENUM_NOTDEFINED); name = "Not Defined"; break;
	}
	insertAttributes(owH, name, inst);
	shared_ptr<IfcAxis2Placement3D> axis = createIfcAxis2Placement3D(location);
	inst->m_ObjectPlacement = createIfcLocalPlacement(axis, relative);
	return inst;
}

shared_ptr<IfcTunnelSpace> TunnelGeneratorIfc4::createIfcTunnelSpace(shared_ptr<IfcOwnerHistory> owH,
	shared_ptr<IfcLocalPlacement> placemenet, int current, shared_ptr<IfcCartesianPoint> location, shared_ptr<IfcObjectPlacement> relative)
{
	std::string name;
	shared_ptr<IfcTunnelSpace> spa = std::make_shared<IfcTunnelSpace>(id++);
	model_->insertEntity(spa);
	spa->m_ObjectPlacement = placemenet;
	switch (current){// here we need some changes Trackspace
	case 1:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_FULLTUNNELSPACE); name = "FullTunnelSpace"; break;
	case 2:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_ANNULARGAPSPACE); name = "AnnularGapSpace"; break;
	case 3:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_LININGSPACE); name = "LiningSpace"; break;
	case 4:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_INTERIORSPACE); name = "InteriorSpace"; break;
	case 5:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_CLEARANCESPACE); name = "ClearanceSpace"; break;
	case 6:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_SERVICESPACE); name = "ServiceSpace"; break;
	case 7:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_TRACKSPACE); name = "TrackSpace"; break;
	case 8:	spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_FLOORSPACE); name = "FloorSpace"; break;
	default:spa->m_SpaceType = std::make_shared<IfcTunnelSpaceEnum>(IfcTunnelSpaceEnum::ENUM_NOTDEFINED); name = "Not Defined"; break;
	}
	insertAttributes(owH, name, spa);
	shared_ptr<IfcAxis2Placement3D> axis = createIfcAxis2Placement3D(location);
	spa->m_ObjectPlacement = createIfcLocalPlacement(axis, relative);
	return spa;
}

