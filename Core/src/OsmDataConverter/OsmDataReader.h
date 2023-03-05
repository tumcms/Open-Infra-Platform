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

#pragma once
#ifndef OpenInfraPlatform_Core_OsmDataConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h
#define OpenInfraPlatform_Core_OsmDataConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h

// Qt5 includes
#include <QtXml>
#include <QDebug>
#include <QString>

// external libraries
#include <Eigen/Dense>
#include <igl/triangle/triangulate.h>

#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "namespace.h"
#include "OsmDataModel.h"
#include "OsmDataGeometry.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OSMDATACONVERTER_BEGIN

/**
* @brief The OsmReader class provides methods to read OSM data from a file and create 3D meshes from the data.
*/
class OsmReader
{
private:
	// the OSM geometry
	OsmGeometry									osmGeometry_;

public:
	/**
	* @brief Default constructor.
	*/
	explicit OsmReader();

	/**
	* @brief Destructor.
	*/
	virtual ~OsmReader();

	/**
	* @brief Reads OSM data from a file and returns the resulting OsmModel.
	* @param filename The name of the file to read.
	* @return A shared pointer to the OsmModel created from the file.
	*/
	std::shared_ptr<OsmModel> readFile(const std::string& filename);

	/**
	* @brief Creates a 3D mesh from the given polygon and geometry description.
	* @param polygon The polygon to mesh.
	* @param geometry The geometry description.
	* @param featureType The type of feature.
	*/
	void meshGeometry(Polygon_t& polygon, std::shared_ptr<GeometryDescription> geometry, const QString featureType);


	void surfaceTriangulation(Polygon_t& inputPoly, Eigen::MatrixXd& triangulatedPoints, Eigen::MatrixXi& triangulatedIndices, const QString featureType);

	/**
	* @brief Triangulates the input polygon and returns the resulting triangulated points and indices.
	* @param inputPoly The input polygon to triangulate.
	* @param triangulatedPoints The triangulated points.
	* @param triangulatedIndices The triangulated indices.
	* @param featureType The type of feature.
	* @return A pair of the triangulated points and indices.
	*/
	std::pair<Eigen::MatrixXd, Eigen::MatrixXi> triangulate(Way_t& triInputPoints, std::vector<std::vector<int>>& triInputIndices, Eigen::MatrixXd& holePoints);

	/**
	* @brief Reads a face mesh from the given face mesh points and indices and the feature type.
	* @param points The resulting points of the mesh.
	* @param pointIndices The resulting point indices of the mesh.
	* @param faceMeshPoints The face mesh points.
	* @param faceMeshIndices The face mesh indices.
	* @param featureType The type of feature.
	*/
	void readFaceMesh(std::vector<PointLayout_t>& points, std::vector<int>& pointIndices, const Eigen::MatrixXf& faceMeshPoints,
		const Eigen::MatrixXi& faceMeshIndices, const QString featureType);

	/**
	* @brief Reads a surface plane face from the given polygon and feature type.
	* @param polygon The polygon to create the surface plane face from.
	* @param points The resulting points of the face.
	* @param pointIndices The resulting point indices of the face.
	* @param featureType The type of feature.
	*/
	void readSurfacePlaneFace(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices, const QString featureType);

	/**
	* @brief Reads a side face with arbitrary shape from the given polygon and feature type.
	* @param polygon The polygon to create the side face from.
	* @param points The resulting points of the face.
	* @param pointIndices The resulting point indices of the face.
	*/
	void readSideFaceArbitrary(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices);

	/**
	* @brief Read the side face of a highway feature.
	* @param polygon The polygon to read.
	* @param points The list of mesh points.
	* @param pointIndices The list of indices that connect the mesh points.
	*/
	void readSideFaceHighway(Polygon_t& polygon, std::vector<PointLayout_t>& points, std::vector<int>& pointIndices);

	/**
	* @brief Generate a 3D surface mesh from 2D triangulated points.
	* @param tri2DPoints The 2D triangulated points.
	* @param tri2DIndices The indices of the 2D triangulated points.
	* @param surface3DPoints The output 3D surface points.
	* @param surface3DIndices The output 3D surface indices.
	* @param zPlane The Z values for each 2D point.
	*/
	void surfaceMesh3D(Eigen::MatrixXd& tri2DPoints, Eigen::MatrixXi& tri2DIndices, Eigen::MatrixXf& surface3DPoints, Eigen::MatrixXi& surface3DIndices, const std::vector<double> zPlane);

	/**
	* @brief Create 3D mesh points from 2D triangulated points.
	* @param triPoints The 2D triangulated points.
	* @param surfacePoints The output 3D surface points.
	* @param zPlane The Z values for each 2D point.
	*/
	void createMeshPoints(Eigen::MatrixXd triPoints, Eigen::MatrixXf& surfacePoints, const double& zPlane = 0);

	/**
	* @brief Create 3D mesh indices from 2D triangulated indices.
	* @param triIndices The 2D triangulated indices.
	* @param surfaceIndices The output 3D surface indices.
	* @param lastPoint The last point in the mesh.
	*/
	void createMeshIndices(Eigen::MatrixXi triIndices, Eigen::MatrixXi& surfaceIndices, int lastPoint = 0);

	/**
	* @brief Merge multiple meshes into one final mesh.
	* @tparam T The type of the mesh element.
	* @tparam Container The type of container for the mesh element.
	* @tparam Args The arguments for the container.
	* @param finalMesh The final merged mesh.
	* @param meshElement The mesh element to merge.
	* @param numRows The number of rows in the mesh.
	*/
	template<typename T, template<typename U, typename...> class Container, typename... Args>
	void mergeMeshes(T& finalMesh, const Container<T, Args...>& meshElement, const int numRows);

	/**
	* @brief Read triangle points from 3 given points.
	* @param points The list of mesh points.
	* @param point1 The first point of the triangle.
	* @param point2 The second point of the triangle.
	* @param point3 The third point of the triangle.
	* @param color The color of the triangle.
	* @param normal The normal vector of the triangle.
	*/
	void readTrianglePoints(std::vector<PointLayout_t>& points, const buw::Vector3f& point1, const buw::Vector3f& point2, const buw::Vector3f& point3,
		const buw::Vector3f& color, const buw::Vector3f& normal);

	/**
	* @brief Reads triangle indices and adds them to a vector.
	* @param pointIndices Vector of point indices to add triangle indices.
	* @param index1 The first index of a point in a triangle.
	* @param index2 The second index of a point in a triangle.
	* @param index3 The third index of a point in a triangle.
	*/
	void readTriangleIndices(std::vector<int>& pointIndices, const unsigned int index1, const unsigned int index2, const unsigned int index3);

	/**
	* @brief Calculates the normal vector to a triangle defined by three points.
	* @param point1 The first point in the triangle.
	* @param point2 The second point in the triangle.
	* @param point3 The third point in the triangle.
	* @return The normal vector to the triangle.
	*/
	buw::Vector3f calcNormal(const buw::Vector3f& point1, const buw::Vector3f& point2, const buw::Vector3f& point3);
};

// typename should be an Eigen::Matrix
template<typename T, template<typename U, typename...> class Container, typename... Args>
void OsmReader::mergeMeshes(T& finalMesh, const Container<T, Args...>& meshElement, const int numRows)
{
	finalMesh.resize(numRows, meshElement.at(0).cols());
	int startIndex = 0;
	for (auto& element : meshElement) {
		finalMesh.block(startIndex, 0, element.rows(), meshElement.at(0).cols()) = element;
		startIndex += element.rows();
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OSMDATACONVERTER_END

EMBED_CORE_OSMDATACONVERTER_INTO_OIP_NAMESPACE(OsmReader)

#endif // end define OpenInfraPlatform_Core_OsmDataConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h