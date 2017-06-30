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

#include "OpenInfraPlatform/DataManagement/MeshImport.h"

//#include "buw.BlueEngine.h"

OpenInfraPlatform::DataManagement::MeshImport::MeshImport(const std::string& filename, const buw::Vector3d& offsetViewArea) :
	buw::Import(filename)
{
	/*buw::ReferenceCounted<buw::Surface> s = std::make_shared<buw::Surface>();

	buw::ObjReader objReader;
	objReader.load(filename.c_str());
	int chunkCount = objReader.getChunkCount();

	buw::ReferenceCounted<buw::SimpleMesh> sm = buw::ConvertToSimpleMesh(objReader.getChunk(0));
	for (int i = 0; i < sm->GetVertexCount(); i++)
	{
		buw::VertexPosition3Normal3Texture2 v;
		sm->GetVertex(i, v);
		s->addPoint(buw::Vector3d(v.position.x(), v.position.y(), v.position.z()));
	}

	for (int i = 0; i < sm->GetIndexCount(); i += 3)
	{
		int i1 = sm->GetIndexDataPointer()[i];
		int i2 = sm->GetIndexDataPointer()[i + 1];
		int i3 = sm->GetIndexDataPointer()[i + 2];

		s->addTriangle(buw::Vector3i(i1, i2, i3));
	}

	s->setName("Mesh terrain");

	digitalElevationModel_->addSurface(s);*/
}