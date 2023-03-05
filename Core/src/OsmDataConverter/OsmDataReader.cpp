/*
Copyright (c) 2021 Technical University of Munich
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

#include <iostream>
#include <chrono>

#include "OsmDataReader.h"
#include "../Exception/OsmDataReaderException.h"
#include "../Exception/UnhandledException.h"


OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OSMDATACONVERTER_BEGIN

OsmReader::OsmReader()
{

}


OsmReader::~OsmReader()
{

}


std::shared_ptr<OsmModel> OsmReader::readFile(const std::string& filename)
{
	// Create document to write XML
	QDomDocument document;

	QString qFilename = QString::fromStdString(filename);

	// Initialize file_ member variable
	QFile* file = new QFile(qFilename);

	// Open file for reading	#TODO: catch error using OIP error logger
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
		delete file;
		throw oip::OsmReaderException("Could not open Xml file <" + filename + "> in OsmReader.");
	}
	else {
		// load file
		if (!document.setContent(file)) {
			file->close();
			delete file;
			throw oip::OsmReaderException("Could not load the Xml file <" + filename + "> for reading in OsmReader.");
		}
	}

	try
	{
		// intialize osm model
		std::shared_ptr<OsmModel> osmModel = std::make_shared<OsmModel>();

		// start timer 
		auto start = std::chrono::high_resolution_clock::now();

		// get child root element (<osm>)
		QDomElement root = document.documentElement();

		// all osm features
		// initialize OSM data
		osmGeometry_.initializeContainer(root, "id");

		// read osm feature
		std::vector<OsmFeature_t> osmData = osmGeometry_.readOsmGeometry(root);

		for (auto& osmFeature : osmData)
		{
			if (!osmFeature.second.empty())
			{
				for (auto& polygon : osmFeature.second)
				{
					std::shared_ptr<GeometryDescription> geometry = std::make_shared<GeometryDescription>();
					geometry->reset();

					// mesh geometry
					meshGeometry(polygon, geometry, osmFeature.first);

					// add to osm model
					osmModel->addGeometry(geometry);
				}
			}
		}

		// osm terrain
		Polygon_t terrainGeo = osmGeometry_.createTerrain(root, "bounds");
		std::shared_ptr<GeometryDescription> terrain = std::make_shared<GeometryDescription>();
		terrain->reset();
		// mesh terrain
		meshGeometry(terrainGeo, terrain, "terrain");
		// add to osmModel
		osmModel->addGeometry(terrain);

		// end timer
		auto end = std::chrono::high_resolution_clock::now();
		// compute elapsed time
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// deallocate
		QFile::remove(QString::fromStdString(filename));
		delete file;
		return osmModel;
	}
	catch (const std::exception& e)
	{
		QFile::remove(QString::fromStdString(filename));
		delete file;
		throw std::exception("Error in Xml file");
	}
}


void OsmReader::meshGeometry(Polygon_t& polygon, std::shared_ptr<GeometryDescription> geometry, const QString featureType)
{
	// container
	std::vector<PointLayout_t> meshPoints;
	std::vector<int> meshIndices;

	// surface plane mesh
	readSurfacePlaneFace(polygon, meshPoints, meshIndices, featureType);

	// side face (quads)
	if (featureType == "highway")
		readSideFaceHighway(polygon, meshPoints, meshIndices);
	else
		readSideFaceArbitrary(polygon, meshPoints, meshIndices);

	// add points to geometry
	geometry->addPoints(meshPoints);

	// add indices to geometry (reset numbering)
	int numOfPoints = meshPoints.size();
	for (int i = 0; i < numOfPoints; i++)
		meshIndices.at(i) = i;

	// add indices
	geometry->addIndices(meshIndices);

	// update bbox
	geometry->updateBBox();
}


void OsmReader::readSurfacePlaneFace(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices, const QString featureType)
{
	// get surface plane reference
	Polygon_t surfacePlane = osmGeometry_.getSurfacePlane(polygon, featureType);

	// triangulate output
	Eigen::MatrixXd triOutPoints;
	Eigen::MatrixXi triOutIndices;

	// final output
	Eigen::MatrixXf surfacePlanePoints;
	Eigen::MatrixXi surfacePlaneIndices;

	if (surfacePlane.first == "site") {

		// container for all site meshes
		std::vector<Eigen::MatrixXf, Eigen::aligned_allocator<Eigen::MatrixXf >> allSiteMeshes;
		std::vector<Eigen::MatrixXi, Eigen::aligned_allocator<Eigen::MatrixXi >> allSiteIndices;

		// container for storing individual member mesh
		// points
		Eigen::MatrixXf siteMesh;
		Eigen::MatrixXf bottomFacePoints;
		Eigen::MatrixXf topFacePoints;
		// indices
		Eigen::MatrixXi siteIndices;
		Eigen::MatrixXi bottomFaceIndices;
		Eigen::MatrixXi topFaceIndices;

		// iterators
		int localMeshRows = 0, localIndexRows = 0;
		int globalMeshRows = 0, globalIndexRows = 0;

		// triangulatation input
		Way_t inputPoints;
		std::vector<std::vector<int>> inputIndices;
		Eigen::MatrixXd holePoints;

		// for each site member
		for (unsigned int i = 0; i < surfacePlane.second.size(); i++) {

			// set points
			inputPoints = surfacePlane.second.at(i);

			// reset indices
			if (inputIndices.size())
				inputIndices.clear();

			// site indices
			int size = inputPoints.size();
			for (int index = 0; index < size; index++)
				inputIndices.push_back({ index, (index + 1) % size });

			// get 2D
			// mesh each site member individually
			std::pair<Eigen::MatrixXd, Eigen::MatrixXi> mesh = triangulate(inputPoints, inputIndices, holePoints);

			// get 3D
			// bottom face
			createMeshPoints(mesh.first, bottomFacePoints, polygon.second[i][0].z());
			createMeshIndices(mesh.second, bottomFaceIndices, globalMeshRows);

			// top face
			createMeshPoints(mesh.first, topFacePoints, polygon.second[i][1].z());
			createMeshIndices(mesh.second, topFaceIndices, globalMeshRows + mesh.first.rows());

			// set local iterators
			localMeshRows = bottomFacePoints.rows() + topFacePoints.rows();
			localIndexRows = bottomFaceIndices.rows() + topFaceIndices.rows();

			// combine mesh
			mergeMeshes(siteMesh, std::vector<Eigen::MatrixXf, Eigen::aligned_allocator<Eigen::MatrixXf >>{bottomFacePoints, topFacePoints}, localMeshRows);
			mergeMeshes(siteIndices, std::vector<Eigen::MatrixXi, Eigen::aligned_allocator<Eigen::MatrixXi >>{bottomFaceIndices, topFaceIndices}, localIndexRows);

			// store in container
			allSiteMeshes.push_back(siteMesh);
			allSiteIndices.push_back(siteIndices);

			// increment global iterators
			globalMeshRows += bottomFacePoints.rows() + topFacePoints.rows();
			globalIndexRows += bottomFaceIndices.rows() + topFaceIndices.rows();
		}

		// create final output
		mergeMeshes(surfacePlanePoints, allSiteMeshes, globalMeshRows);
		mergeMeshes(surfacePlaneIndices, allSiteIndices, globalIndexRows);

	}
	else {

		// 2D mesh
		surfaceTriangulation(surfacePlane, triOutPoints, triOutIndices, featureType);

		// z-plane constant
		std::vector<double> zPlane = { polygon.second[0][0].z(), polygon.second[0][1].z() };
		surfaceMesh3D(triOutPoints, triOutIndices, surfacePlanePoints, surfacePlaneIndices, zPlane);
	}

	// read the triangle mesh for the complete mesh
	readFaceMesh(points, pointIndices, surfacePlanePoints, surfacePlaneIndices, polygon.first);
}


void OsmReader::readSideFaceArbitrary(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices)
{
	// create side face for boundary and hole
	for (const auto& boundary : polygon.second)
	{
		// each face is a quad which is to be broken down into 2 triangles
		unsigned int totalFacePoints = boundary.size();
		unsigned int faces = (totalFacePoints / 2) - 1;

		for (unsigned int face = 0; face < faces; face++)
		{
			// indexes required for setting up the triangles
			unsigned int index1 = (face * 2);
			unsigned int index2 = (face * 2) + 1;
			unsigned int index3 = (face * 2) + 2;
			unsigned int index4 = (face * 2) + 3;

			// read quad indices
			// triangle 1
			readTriangleIndices(pointIndices, index1, index2, index3);
			// triangle 2
			readTriangleIndices(pointIndices, index3, index2, index4);

			// face points
			buw::Vector3f point1 = boundary[index1].cast<float>();
			buw::Vector3f point2 = boundary[index2].cast<float>();
			buw::Vector3f point3 = boundary[index3].cast<float>();
			buw::Vector3f point4 = boundary[index4].cast<float>();

			// calculate triangle normals
			// triangle1
			buw::Vector3f normal1 = calcNormal(point1, point2, point3);
			// triangle2
			buw::Vector3f normal2 = calcNormal(point3, point2, point4);

			// read color
			buw::Vector3f color = osmGeometry_.getColor(polygon.first);

			// read quad points
			// triangle1
			readTrianglePoints(points, point1, point2, point3, color, normal1);
			// triangle 2
			readTrianglePoints(points, point3, point2, point4, color, normal2);
		}
	}
}


void OsmReader::readSideFaceHighway(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices)
{
	Way_t outerBoundary = polygon.second.at(0);
	unsigned int totalPoints = outerBoundary.size();
	unsigned int faces = totalPoints / 2, lastQuadStart = totalPoints - 4;

	// front & back face
	for (unsigned int face = 0; face < 2; face++)
	{
		unsigned int index1 = (lastQuadStart * face);
		unsigned int index2 = (lastQuadStart * face) + 1;
		unsigned int index3 = (lastQuadStart * face) + 2;
		unsigned int index4 = (lastQuadStart * face) + 3;

		// read quad indices
		// triangle 1
		readTriangleIndices(pointIndices, index1, index2, index3);
		// triangle 2
		readTriangleIndices(pointIndices, index3, index2, index4);

		// face points
		buw::Vector3f point1 = outerBoundary[index1].cast<float>();
		buw::Vector3f point2 = outerBoundary[index2].cast<float>();
		buw::Vector3f point3 = outerBoundary[index3].cast<float>();
		buw::Vector3f point4 = outerBoundary[index4].cast<float>();

		// calculate triangle normals
		// triangle1
		buw::Vector3f normal1 = calcNormal(point1, point2, point3);
		// triangle2
		buw::Vector3f normal2 = calcNormal(point3, point2, point4);

		// read color
		buw::Vector3f color = osmGeometry_.getColor(polygon.first);

		// read quad points
		// triangle1
		readTrianglePoints(points, point1, point2, point3, color, normal1);
		// triangle 2
		readTrianglePoints(points, point3, point2, point4, color, normal2);
	}

	// side face
	for (unsigned int face = 0; face < faces - 2; face++)
	{
		unsigned int index1 = (face * 2);
		unsigned int index2 = (face * 2) + 1;
		unsigned int index3 = (face * 2) + 4;
		unsigned int index4 = (face * 2) + 5;

		// read quad indices
		// triangle 1
		readTriangleIndices(pointIndices, index1, index2, index3);
		// triangle 2
		readTriangleIndices(pointIndices, index3, index2, index4);

		// face points
		buw::Vector3f point1 = outerBoundary[index1].cast<float>();
		buw::Vector3f point2 = outerBoundary[index2].cast<float>();
		buw::Vector3f point3 = outerBoundary[index3].cast<float>();
		buw::Vector3f point4 = outerBoundary[index4].cast<float>();

		// calculate triangle normals
		// triangle1
		buw::Vector3f normal1 = calcNormal(point1, point2, point3);
		// triangle2
		buw::Vector3f normal2 = calcNormal(point3, point2, point4);

		// read color
		buw::Vector3f color = osmGeometry_.getColor(polygon.first);

		// read quad points
		// triangle1
		readTrianglePoints(points, point1, point2, point3, color, normal1);
		// triangle 2
		readTrianglePoints(points, point3, point2, point4, color, normal2);
	}
}


void OsmReader::surfaceMesh3D(Eigen::MatrixXd& tri2DPoints, Eigen::MatrixXi& tri2DIndices, Eigen::MatrixXf& surface3DPoints, Eigen::MatrixXi& surface3DIndices, const std::vector<double> zPlane)
{
	// points
	Eigen::MatrixXf bottomFacePoints;
	createMeshPoints(tri2DPoints, bottomFacePoints, zPlane[0]);
	Eigen::MatrixXf topFacePoints;
	createMeshPoints(tri2DPoints, topFacePoints, zPlane[1]);
	int meshRows = bottomFacePoints.rows() + topFacePoints.rows();

	// indices
	Eigen::MatrixXi bottomFaceIndices;
	createMeshIndices(tri2DIndices, bottomFaceIndices);
	Eigen::MatrixXi topFaceIndices;
	createMeshIndices(tri2DIndices, topFaceIndices, tri2DPoints.rows());
	int indexRows = bottomFaceIndices.rows() + topFaceIndices.rows();

	// complete mesh
	// points
	mergeMeshes(surface3DPoints, std::vector<Eigen::MatrixXf, Eigen::aligned_allocator<Eigen::MatrixXf >>{bottomFacePoints, topFacePoints}, meshRows);
	// indices
	mergeMeshes(surface3DIndices, std::vector<Eigen::MatrixXi, Eigen::aligned_allocator<Eigen::MatrixXi >>{bottomFaceIndices, topFaceIndices}, indexRows);
}


void OsmReader::surfaceTriangulation(Polygon_t& inputPoly, Eigen::MatrixXd& triangulatedPoints, Eigen::MatrixXi& triangulatedIndices, const QString featureType)
{
	// all ways and indices container
	Way_t allNodes; std::vector<std::vector<int>> allIndices;

	// add hole midpoints [triangulation algorithm omits triangulation in holes]
	Eigen::MatrixXd holePoints;
	if (inputPoly.second.size() > 1 && inputPoly.first == "multipolygon" && featureType == "building") {
		// get all inner elements
		//std::vector<Way_t> inner( inputPoly.second.begin() + 1, inputPoly.second.end() );
		std::vector<Way_t> inner(inputPoly.second.begin() + 1, inputPoly.second.end());
		// seperate hole from sub-element
		osmGeometry_.getHoles(inner, holePoints);
	}

	// for different features
	if (featureType == "highway")
		osmGeometry_.combineHighway(inputPoly, allNodes, allIndices);
	else
		osmGeometry_.combineWayArbitrary(inputPoly, allNodes, allIndices);

	// 2D mesh
	std::pair<Eigen::MatrixXd, Eigen::MatrixXi> mesh = triangulate(allNodes, allIndices, holePoints);
	triangulatedPoints = mesh.first;
	triangulatedIndices = mesh.second;
}


std::pair<Eigen::MatrixXd, Eigen::MatrixXi> OsmReader::triangulate(Way_t& wayNodes, std::vector<std::vector<int>>& wayIndices, Eigen::MatrixXd& holePoints)
{
	// map stl to Eigen (nodes and indices)
	Eigen::MatrixXd triInputPoints(wayNodes.size(), 2);
	Eigen::MatrixXi triInputIndices(wayIndices.size(), 2);
	osmGeometry_.mapStlToEigen(triInputPoints, triInputIndices, wayNodes, wayIndices);

	Eigen::MatrixXd triangulatedPoints;
	Eigen::MatrixXi triangulatedIndices;
	igl::triangle::triangulate(triInputPoints, triInputIndices, holePoints, "q", triangulatedPoints, triangulatedIndices);

	return std::pair<Eigen::MatrixXd, Eigen::MatrixXi>(triangulatedPoints, triangulatedIndices);
}


void OsmReader::createMeshPoints(Eigen::MatrixXd triPoints, Eigen::MatrixXf& surfacePoints, const double& zPlane)
{
	// 2D to 3D
	triPoints.conservativeResize(triPoints.rows(), triPoints.cols() + 1);
	// convert from Xd to Xf 
	Eigen::MatrixXf triPointsFloat = triPoints.cast <float>();
	// fill z
	triPointsFloat.col(2).fill(zPlane);
	// copy the result to output
	surfacePoints = triPointsFloat.replicate(1, 1);
}


void OsmReader::createMeshIndices(Eigen::MatrixXi triIndices, Eigen::MatrixXi& surfaceIndices, int lastPoint)
{
	if (lastPoint != 0)
		triIndices.array() += lastPoint;

	surfaceIndices = triIndices.replicate(1, 1);
}


void OsmReader::readFaceMesh(std::vector<PointLayout_t>& points, std::vector<int>& pointIndices, const Eigen::MatrixXf& faceMeshPoints,
	const Eigen::MatrixXi& faceMeshIndices, const QString featureType)
{
	// get the triangles
	int numOfTri = faceMeshIndices.rows();

	for (int i = 0; i < numOfTri; i++)
	{
		// get the triangle points
		buw::Vector3f point1 = faceMeshPoints.row(faceMeshIndices.row(i)[0]);
		buw::Vector3f point2 = faceMeshPoints.row(faceMeshIndices.row(i)[1]);
		buw::Vector3f point3 = faceMeshPoints.row(faceMeshIndices.row(i)[2]);

		// calculate the normal
		buw::Vector3f normal = calcNormal(point1, point2, point3);

		// get the color
		buw::Vector3f color = osmGeometry_.getColor(featureType);

		// create points with position, color and normal
		points.push_back(PointLayout_t(point1, color, normal));
		points.push_back(PointLayout_t(point2, color, normal));
		points.push_back(PointLayout_t(point3, color, normal));
	}

	// create the indices
	pointIndices.insert(pointIndices.end(), faceMeshIndices.data(), faceMeshIndices.data() + faceMeshIndices.size());
}


void OsmReader::readTrianglePoints(std::vector<PointLayout_t>& points, const buw::Vector3f& point1, const buw::Vector3f& point2, const buw::Vector3f& point3,
	const buw::Vector3f& color, const buw::Vector3f& normal)
{
	// create points with position, color and normal
	points.push_back(PointLayout_t(point1, color, normal));
	points.push_back(PointLayout_t(point2, color, normal));
	points.push_back(PointLayout_t(point3, color, normal));
}


void OsmReader::readTriangleIndices(std::vector<int>& pointIndices, const unsigned int index1, const unsigned int index2, const unsigned int index3)
{
	// triangle
	pointIndices.push_back(index1);
	pointIndices.push_back(index2);
	pointIndices.push_back(index3);
}


buw::Vector3f OsmReader::calcNormal(const buw::Vector3f& point1, const buw::Vector3f& point2, const buw::Vector3f& point3)
{
	carve::geom::vector<3> vector1;
	vector1.x = point1.x();
	vector1.y = point1.y();
	vector1.z = point1.z();
	carve::geom::vector<3> vector2;
	vector2.x = point2.x();
	vector2.y = point2.y();
	vector2.z = point2.z();
	carve::geom::vector<3> vector3;
	vector3.x = point3.x();
	vector3.y = point3.y();
	vector3.z = point3.z();

	carve::geom::vector<3> normal = carve::geom::cross(vector1 - vector2, vector2 - vector3);
	normal.normalize();

	return buw::Vector3f(normal.x, normal.y, normal.z);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OSMDATACONVERTER_END