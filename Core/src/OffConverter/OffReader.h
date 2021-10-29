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
#ifndef OpenInfraPlatform_Core_OffConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h
#define OpenInfraPlatform_Core_OffConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h

#include <thread>
#include <string>

#include "namespace.h"
#include "OffModel.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_BEGIN

/*! \brief The Off reader class
*
* This class is used to read the information from an .off file and pass it to the Off Model
*/
class OffReader
{
public:
	//! constructor
	explicit OffReader();

	//! destructor
	virtual ~OffReader();

	/**
	* \brief Does all the reading and calls the other functions
	*
	* This is the function to call to read all the information from the .off file
	*
	* \param[in] filename The name of the .off file
	* \return The pointer that points to the Off model
	*/
	static std::shared_ptr<OffModel> readFile(const std::string& filename);

	/**
	* \brief Reads a triangle face from the line stream
	*
	* This function is called to read one triangle from a line stream.
	* It searches the correspondig indices and vertices and saves the result the vertex list meant for rendering.
	*
	* \param[in] lineStream The line stream obtained from file reading (getline).
	* \param[in] indices The list of indices that was already red from the .off file.
	* \param[in] vertices The list of vertices that was already red from the .off file.
	* \param[in] offVertices The list of vertices read from the .off file meant for the vertex buffer.
	*/
	static void readTriangleFace(std::stringstream& lineStream,
		std::vector<uint32_t>& indices,
		std::vector<buw::VertexPosition3Color3Normal3>& vertices,
		std::vector<buw::Vector3f>& offVertices);

	/**
	* \brief Reads a quad face from the line stream
	*
	* This function is called to read one quadrilateral from a line stream and creates to triangles from it.
	* It searches the correspondig indices and vertices and saves the result the vertex list meant for rendering.
	*
	* \param[in] lineStream The line stream obtained from file reading (getline).
	* \param[in] indices The list of indices that was already red from the .off file.
	* \param[in] vertices The list of vertices that was already red from the .off file.
	* \param[in] offVertices The list of vertices read from the .off file meant for the vertex buffer.
	*/
	static void readQuadFace(std::stringstream& lineStream,
		std::vector<uint32_t>& indices,
		std::vector<buw::VertexPosition3Color3Normal3>& vertices,
		std::vector<buw::Vector3f>& offVertices);

	/**
	* \brief Reads and interprets all the vertices from the .off file
	*
	* This function reads through all the lines  in the .off file that specify vertices.
	* It saves them in a vector that is being returned.
	*
	* \param[in] nrOfVertices The number of vertices specified in he .off file.
	* \param[in] offFile The .off file all the information is red from.
	* \return The vector with all vertices from the .off file.
	*/
	static std::vector<buw::Vector3f> readVertices(const int nrOfVertices,
		std::ifstream& offFile);

	/**
	* \brief Calculates the normal of a triangle
	*
	* This function calculates the normal based on a triangle given by three vertices.
	*
	* \param[in] vertex1 The first vertex of the triangle.
	* \param[in] vertex2 The second vertex of the triangle.
	* \param[in] vertex3 The third vertex of the triangle.
	* \return The calculated normal vector
	*/
	static buw::Vector3f calcNormal(const buw::Vector3f& vertex1,
		const buw::Vector3f& vertex2,
		const buw::Vector3f& vertex3);

	/**
	* \brief read color from the line
	*
	* This function read color vector from the text line
	*
	* \param[in] vertex1 The first vertex of the triangle.
	* \return The vector wich includes the numbers of RGB color
	*/

	static buw::Vector3f OffReader::readColorsFromFace(std::stringstream& lineStream);

};
OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END

EMBED_CORE_OFFCONVERTER_INTO_OIP_NAMESPACE(OffReader)

#endif //end define OpenInfraPlatform_Core_OffConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h