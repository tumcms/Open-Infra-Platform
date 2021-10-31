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
		while (std::getline(offFile, line) && line != "OFF");

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
		std::vector<buw::Vector3f> offVertices = readVertices(nrOfVertices, offFile);
		std::vector<buw::VertexPosition3Color3Normal3> buwVertices;

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
				readTriangleFace(lineStream, indices, buwVertices, offVertices);
			}
			//read quad
			else if (faceType == 4)
			{
				readQuadFace(lineStream, indices, buwVertices, offVertices);
			}
			//read color
			else if (nrOfFaces-1)
			{
				readColorsFromFace(lineStream);
			}
			else
			{
				offFile.close();
				throw oip::UnhandledException("Files that include faces with more than 4 edges are not supported yet.");
			}
		}
		model->addVertices(buwVertices);

		size_t nrOfAllVertices = buwVertices.size();
		for (int i = 0; i < nrOfAllVertices; i++)
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
	std::vector<uint32_t>& indices,
	std::vector<buw::VertexPosition3Color3Normal3>& vertices,
	std::vector<buw::Vector3f>& offVertices)
{
	//read indices
	std::vector<uint32_t> faceVector(3);

	lineStream >> faceVector[0] >> faceVector[1] >> faceVector[2];
	for (int j = 0; j < 3; j++)
	{
		indices.push_back(faceVector[j]);
	}

	//selete used vertices 
	buw::Vector3f vector1 = offVertices.at(faceVector[0]);
	buw::Vector3f vector2 = offVertices.at(faceVector[1]);
	buw::Vector3f vector3 = offVertices.at(faceVector[2]);

	//calculate normal
	buw::Vector3f normal = calcNormal(vector1, vector2, vector3);

	//read color
	buw::Vector3f color = OffReader::readColorsFromFace(lineStream);
	//buw::Vector3f color2 = OffReader::readColorsFromFace(lineStream);
	//buw::Vector3f color3 = OffReader::readColorsFromFace(lineStream);
	//buw::Vector3f color(0.0f, 0.0f, 1.0f); //default color; to be changed later on 

	//create vertices with position, color and normal and add to list of all vertices
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color, normal));
	//vertices.push_back(buw::VertexPosition3Color3Normal3(vector2, color2, normal));
	//vertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color3, normal));
}

void OffReader::readQuadFace(std::stringstream& lineStream, 
	std::vector<uint32_t>& indices,
	std::vector<buw::VertexPosition3Color3Normal3>& vertices,
	std::vector<buw::Vector3f>& offVertices)
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

	//select used vertices 
	int size = indices.size();
	buw::Vector3f vector1 = offVertices.at(faceVector[0]);
	buw::Vector3f vector2 = offVertices.at(faceVector[1]);
	buw::Vector3f vector3 = offVertices.at(faceVector[2]);
	buw::Vector3f vector4 = offVertices.at(faceVector[3]);

	//calculate normal
	buw::Vector3f normal1 = calcNormal(vector1, vector2, vector3);
	buw::Vector3f normal2 = calcNormal(vector3, vector4, vector1);

	//read colors
	//buw::Vector3f color1(0.0f, 0.0f, 1.0f); //default color; to be changed later on 
	//buw::Vector3f color2(0.0f, 0.0f, 1.0f); //default color; to be changed later on 
	//buw::Vector3f color3(0.0f, 0.0f, 1.0f); //default color; to be changed later on

	buw::Vector3f color = OffReader::readColorsFromFace(lineStream);
	//buw::Vector3f color2 = OffReader::readColorsFromFace(lineStream);
	//buw::Vector3f color3 = OffReader::readColorsFromFace(lineStream);

	//create vertices with position, color and normal and add to list of all vertices
	//first triangle
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color, normal1));
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector2, color, normal1));
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color, normal1));

	//second triangle
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector3, color, normal2));
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector4, color, normal2));
	vertices.push_back(buw::VertexPosition3Color3Normal3(vector1, color, normal2));
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
buw::Vector3f OffReader::readColorsFromFace(std::stringstream& lineStream)
{
	carve::geom::vector<3> colorVector;
	lineStream >> colorVector[0] >> colorVector[1] >> colorVector[2];
	//this code read now only 3 colors -> to be change later, it must support other RGB colors
	//RGB Red #FF0000 255 000 000 -> 1.0f, 0.0f, 0.0f
	//RGB Green #00FF00 000 255 000 -> 0.0f, 1.0f, 0.0f
	//RGB Blue #0000FF 000 000 255-> 0.0f, 0.0f, 1.0f
	if (colorVector[5] == 255)//red
		colorVector.x = 1.0f;
	else if (colorVector[6] ==255)//green
		colorVector.y = 1.0f;
	else if (colorVector[7] == 255)//blue
		colorVector.z = 1.0f;

	return buw::Vector3f(colorVector.x, colorVector.y, colorVector.z);
}


OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END