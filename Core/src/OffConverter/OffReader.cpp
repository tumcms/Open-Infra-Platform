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

#include "OffReader.h"
#include "../Exception/OffReaderException.h"
#include "../Exception/UnhandledException.h"
#include "namespace.h"
#include "../IfcGeometryConverter/CarveHeaders.h"

#include <fstream>
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_BEGIN

OffReader::OffReader()
{

}

OffReader::~OffReader()
{

}

std::shared_ptr<OffModel> OffReader::readFile(const std::string& filename)
{
	std::ifstream offFile(filename);

	if (!offFile.is_open())
	{
		throw oip::OffReaderException("Could not open OFF file <" + filename + "> in OffReader.");
	}

	try
	{
		std::string line;
		//search line which specifies the number of vertices, faces and edges
		bool firstLineWithContent = false;
		while (!firstLineWithContent)
		{
			std::getline(offFile, line);
			if (line == "OFF")
				firstLineWithContent = true;
		}

		//read number of elements
		getline(offFile, line);
		std::vector<int>	lineData;
		std::stringstream	lineStream(line);

		int value;
		while (lineStream >> value)
		{
			lineData.push_back(value);
		}

		int nrOfVertices, nrOfFaces, nrOfEdges;
		nrOfVertices = lineData[0];
		nrOfFaces = lineData[1];
		nrOfEdges = lineData[2];

		//create new OffModel
		std::shared_ptr<OffModel> model = std::make_shared<OffModel>();
		model->reset();
		model->setFilename(filename);

		//read vertices 
		std::vector<buw::Vector3f> verticesPosition;
		verticesPosition = readVertices(nrOfVertices, offFile);
		std::vector<buw::VertexPosition3Color3Normal3> allVertices;

		//read faces (special case: after indices of face the color is given in RGB value -> to be considered later on)
		std::vector<uint32_t> indices;
		for (int i = 0; i < nrOfFaces; i++)
		{
			//which type of face (triangle, quad, ...)
			std::getline(offFile, line);
			std::vector<uint32_t> faceVector;
			std::stringstream lineStream(line);

			int faceType;
			lineStream >> faceType;

			//read triangle 
			if (faceType == 3)
			{
				readTriangleFace(lineStream, indices);
				//read normal and color
				int size = indices.size();
				buw::Vector3f vector1 = verticesPosition.at(indices.at(size - 3));
				buw::Vector3f vector2 = verticesPosition.at(indices.at(size - 2));
				buw::Vector3f vector3 = verticesPosition.at(indices.at(size - 1));
				buw::Vector3f color(1.0f, 0.0f, 0.0f); //to be changed later on 
				buw::Vector3f normal = calcNormal(vector1, vector2, vector3);

				//create vertices with position, color and normal and add to list of all vertices
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color, normal));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector2, color, normal));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color, normal));
			}
			//read quad
			else if (faceType == 4)
			{
				readQuadFace(lineStream, indices);
				//read normal
				int size = indices.size();
				buw::Vector3f vector1 = verticesPosition.at(indices.at(size - 6));
				buw::Vector3f vector2 = verticesPosition.at(indices.at(size - 5));
				buw::Vector3f vector3 = verticesPosition.at(indices.at(size - 4));
				buw::Vector3f vector4 = verticesPosition.at(indices.at(size - 2));
				buw::Vector3f color1(1.0f, 0.0f, 0.0f); //to be changed later on 
				buw::Vector3f normal1 = calcNormal(vector1, vector2, vector3);
				buw::Vector3f color2(1.0f, 0.0f, 0.0f); //to be changed later on 
				buw::Vector3f normal2 = calcNormal(vector3, vector4, vector1);

				//create vertices with position, color and normal and add to list of all vertices
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color1, normal1));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector2, color1, normal1));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color1, normal1));

				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color2, normal2));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector4, color2, normal2));
				allVertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color2, normal2));
			}
			else
			{
				offFile.close();
				throw oip::UnhandledException("Files that include faces with more than 4 edges are not supported yet.");
			}
		}
		model->addVertices(allVertices);

		int nrOfAllVertices = allVertices.size();
		for (int i = 0; i < nrOfAllVertices; i++) //proably no need; give vertices without indexBuffer to shader
			indices.at(i) = i;

		model->addIndices(indices);

		offFile.close();
		return model;
	}
	catch (const std::exception& e)
	{
		offFile.close();
		throw std::exception("Error in Off file");
	}
}

std::vector<buw::Vector3f> OffReader::readVertices(const int nrOfVertices, 
	std::ifstream& offFile)
{
	std::string line;

	std::vector<buw::Vector3f> allVertices;
	for (int i = 0; i < nrOfVertices; i++)
	{
		std::getline(offFile, line);
		buw::Vector3f position;
		std::stringstream lineStream(line);

		lineStream >> position[0] >> position[1] >> position[2];
		allVertices.push_back(position);
	}
	return allVertices;
}

void OffReader::readTriangleFace(std::stringstream& lineStream, 
	std::vector<uint32_t>& indices)
{
	std::vector<uint32_t> faceVector;

	lineStream >> faceVector[0] >> faceVector[1] >> faceVector[2];
	for (int j = 0; j < 3; j++)
	{
		indices.push_back(faceVector[j]);
	}
}

void OffReader::readQuadFace(std::stringstream& lineStream, 
	std::vector<uint32_t>& indices)
{
	std::vector<uint32_t> faceVector(4);

	//read values from lineStream 
	lineStream >> faceVector[0] >> faceVector[1] >> faceVector[2] >> faceVector[3];

	//Convert quads into triangles
	//first triangle
	indices.push_back(faceVector[0]);
	indices.push_back(faceVector[1]);
	indices.push_back(faceVector[2]);
	//second triangle
	indices.push_back(faceVector[2]);
	indices.push_back(faceVector[3]);
	indices.push_back(faceVector[0]);
}

buw::Vector3f OffReader::calcNormal(const buw::Vector3f& vertex1,
	const buw::Vector3f& vertex2,
	const buw::Vector3f& vertex3)
{
	carve::geom::vector<3> vector1;
	vector1.x = vertex1.x();
	vector1.y = vertex1.y();
	vector1.z = vertex1.z();
	carve::geom::vector<3> vector2;
	vector2.x = vertex2.x();
	vector2.y = vertex2.y();
	vector2.z = vertex2.z();
	carve::geom::vector<3> vector3;
	vector3.x = vertex3.x();
	vector3.y = vertex3.y();
	vector3.z = vertex3.z();

	carve::geom::vector<3> normal = carve::geom::cross(vector1 - vector2, vector2 - vector3);
	normal.normalize();

	return buw::Vector3f(normal.x, normal.y, normal.z);
}


OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END