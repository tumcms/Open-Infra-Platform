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
		throw oip::OffReaderException("Could not open OFF file <" + filename + "in OffReader.>");
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
		std::vector<buw::Vector3d> allVertices;
		for (int i = 0; i < nrOfVertices; i++)
		{
			std::getline(offFile, line);
			buw::Vector3d vector;
			std::stringstream lineStream(line);

			lineStream >> vector[0] >> vector[1] >> vector[2];
			allVertices.push_back(vector);
		}
		model->addVertices(allVertices);

		//read faces
		//... still to be added

		offFile.close();
		return model;
	}
	catch (const std::exception& e)
	{
		offFile.close();
		throw std::exception("Error in Off file");
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END