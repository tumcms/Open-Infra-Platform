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

#ifndef IFC4FILEFACTORY_H
#define IFC4FILEFACTORY_H // this program generates ifc4_tunnel files and ifc4 files
#pragma once

#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcSIUnit.h"
#include "OpenInfraPlatform/IfcTunnel/guid/CreateGuid_64.h"
#include "OpenInfraPlatform/IfcTunnel/IfcTunnelEntities.h"
#include "link2.h"
#include "OpenInfraPlatform/IfcTunnel/model/IfcTunnelException.h"
#include "OpenInfraPlatform/IfcTunnel/model/IfcTunnelModel.h"
#include "OpenInfraPlatform/IfcTunnel/model/UnitConverter.h"
#include "OpenInfraPlatform/IfcTunnel/reader/IfcStepReader.h"
#include "OpenInfraPlatform/IfcTunnel/reader/IfcTunnelReader.h"
#include "OpenInfraPlatform/IfcTunnel/writer/IfcStepWriter.h"
#include <buw.Core.h>
#include <buw.Engine.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnel.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnelElement.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnelInstallationEnum.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnelPart.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnelSpace.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnelSpaceEnum.h"
#include "OpenInfraPlatform/IfcTunnel/entity/include/IfcTunnnelInstallation.h"


struct t_part
{
	int previous;
	int current;
	int father_pos;
	int aggregate_pos;
	std::string openName;
	bool first;
};

using namespace OpenInfraPlatform::IfcTunnel;

class TunnelGeneratorIfc4 {

public:
	TunnelGeneratorIfc4(std::vector <t_part>, std::string, bool );
	~TunnelGeneratorIfc4();
	std::shared_ptr<IfcGloballyUniqueId> createGUID();
	static std::shared_ptr<TunnelGeneratorIfc4> create(std::vector <t_part>, std::string, bool );
	void store(bool);

private:
	shared_ptr<IfcApplication> createIfcApplication(shared_ptr<IfcOrganization> applicationDeveloper);
	shared_ptr<IfcOrganization> createIfcOrganization();
	shared_ptr<IfcUnitAssignment> createIfcUnitAssignment();
	void insertAttributes(shared_ptr<IfcOwnerHistory>, std::string, shared_ptr<IfcObjectDefinition>);
	//shared_ptr<IfcSlab> createIfcSlab(shared_ptr<IfcOwnerHistory> , shared_ptr<IfcProductRepresentation> representation);
	//shared_ptr<IfcBuilding> createIfcBuilding(shared_ptr<IfcOwnerHistory> ,shared_ptr<IfcLocalPlacement> );
	shared_ptr<IfcRelContainedInSpatialStructure> createIfcRelSpat(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcObjectDefinition>);
	shared_ptr<IfcRepresentationContext> createIfcRepresentationContext();
	shared_ptr<IfcPerson> createIfcPerson();
	shared_ptr<IfcPersonAndOrganization> createIfcPersonAndOrganization(shared_ptr<IfcPerson>, shared_ptr<IfcOrganization>);
	shared_ptr<IfcOwnerHistory> createIfcOwnerHistory(shared_ptr<IfcPersonAndOrganization>, shared_ptr<IfcApplication>);
	shared_ptr<IfcCartesianPoint> createIfcCartesianPoint(const float x, const float y, const float z);
	shared_ptr<IfcPolyLoop> createIfcPolyLoop(std::vector<shared_ptr<IfcCartesianPoint>>);
	shared_ptr<IfcFaceOuterBound> createIfcFaceOuterbound(shared_ptr<IfcPolyLoop>);
	shared_ptr<IfcFace> createIfcFace(shared_ptr<IfcFaceOuterBound>);
	shared_ptr<IfcDirection> createIfcDirection(const float x, const float y, const float z);
	shared_ptr<IfcClosedShell> createIfcClosedShell(std::vector<shared_ptr<IfcFace>>);
	shared_ptr<IfcShapeRepresentation> createIfcShapeRepresentation(std::vector<shared_ptr<IfcRepresentationItem>>, shared_ptr<IfcRepresentationContext>);
	shared_ptr<IfcProductDefinitionShape> createIfcProductDefinitionShape(std::vector<shared_ptr<IfcRepresentation>>);
	shared_ptr<IfcFacetedBrep> createIfcFacetedBrep(shared_ptr<IfcClosedShell>);
	shared_ptr<IfcSpace> createIfcSpace(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcCartesianPoint>, std::string, shared_ptr<IfcObjectPlacement>);
	shared_ptr<IfcProxy> createIfcProxy(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcCartesianPoint>, std::string, shared_ptr<IfcObjectPlacement>);
	shared_ptr<IfcRelAggregates> createIfcRelAggregates(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcObjectDefinition>);
	shared_ptr<IfcGeometricRepresentationContext> createIfcGeometricRepresentationContext(shared_ptr<IfcAxis2Placement3D>);
	shared_ptr<IfcRelSpaceBoundary> createIfcRelSpace(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcSpaceBoundarySelect>);
	shared_ptr<IfcAxis2Placement3D> createIfcAxis2Placement3D(shared_ptr<IfcCartesianPoint>);
	shared_ptr<IfcLocalPlacement> createIfcLocalPlacement(shared_ptr<IfcAxis2Placement3D>, shared_ptr<IfcObjectPlacement>);
	shared_ptr<IfcTunnelSpace> createIfcTunnelSpace(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcLocalPlacement>, int, shared_ptr<IfcCartesianPoint>, shared_ptr<IfcObjectPlacement>);
	shared_ptr<IfcTunnnelInstallation> createIfcTunnelInstallation(shared_ptr<IfcOwnerHistory>, shared_ptr<IfcLocalPlacement>, int, shared_ptr<IfcCartesianPoint>, shared_ptr<IfcObjectPlacement>);
private:
	int id;
	shared_ptr<IfcTunnelModel> model_;
	std::string filename_;
};

#endif

