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
class OffReader
{
public:
	explicit OffReader();
	virtual ~OffReader();

	static std::shared_ptr<OffModel> readFile(const std::string& filename);

	static void readTriangleFace(std::stringstream& lineStream,
		std::vector<uint32_t>& indices,
		std::vector<buw::VertexPosition3Color3Normal3>& vertices,
		std::vector<buw::Vector3f>& offVertices);
	static void readQuadFace(std::stringstream& lineStream,
		std::vector<uint32_t>& indices,
		std::vector<buw::VertexPosition3Color3Normal3>& vertices,
		std::vector<buw::Vector3f>& offVertices);
	static std::vector<buw::Vector3f> readVertices(const int nrOfVertices,
		std::ifstream& offFile);
	static buw::Vector3f calcNormal(const buw::Vector3f& vertex1,
		const buw::Vector3f& vertex2,
		const buw::Vector3f& vertex3);
};
OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_OFFCONVERTER_END

EMBED_CORE_OFFCONVERTER_INTO_OIP_NAMESPACE(OffReader)

#endif //end define OpenInfraPlatform_Core_OffConverter_51f00dc0_473e_4406_a0c2_2847806ff341_h