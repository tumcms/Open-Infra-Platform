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
			firstLineWithContent = line.find("OFF");
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
		readVertices(nrOfVertices, model, offFile);

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
			}
			//read quad
			else if (faceType == 4)
			{
				readQuadFace(lineStream, indices);
			}
			else
			{
				offFile.close();
				throw oip::UnhandledException("Files that include faces with more than 4 edges are not supported yet.");
			}
		}
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

static void readVertices(const int nrOfVertices, 
	std::shared_ptr<OffModel>& model, 
	std::ifstream& offFile)
{
	std::string line;

	std::vector<buw::VertexPosition3Color3Normal3> allVertices;
	for (int i = 0; i < nrOfVertices; i++)
	{
		std::getline(offFile, line);
		buw::Vector3f position;
		buw::Vector3f color;
		buw::Vector3f normal;
		std::stringstream lineStream(line);

		lineStream >> position[0] >> position[1] >> position[2];
		buw::VertexPosition3Color3Normal3 vector = buw::VertexPosition3Color3Normal3(position, color, normal);
		allVertices.push_back(vector);
	}
	model->addVertices(allVertices);
}

static void readTriangleFace(std::stringstream& lineStream, 
	std::vector<uint32_t>& indices)
{
	std::vector<uint32_t> faceVector;
	int faceType;

	lineStream >> faceType >> faceVector[0] >> faceVector[1] >> faceVector[2];
	for (int j = 0; j < 3; j++)
	{
		indices.push_back(faceVector[j]);
	}
}

static void readQuadFace(std::stringstream& lineStream, 
	std::vector<uint32_t>& indices)
{
	std::vector<uint32_t> faceVector;
	int faceType;

	//read values from lineStream 
	lineStream >> faceType >> faceVector[0] >> faceVector[1] >> faceVector[2] >> faceVector[3];

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

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END