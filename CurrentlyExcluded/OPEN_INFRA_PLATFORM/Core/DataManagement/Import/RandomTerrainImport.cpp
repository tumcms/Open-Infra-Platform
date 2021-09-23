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

#include "OpenInfraPlatform/DataManagement/RandomTerrainImport.h"
#include <BlueFramework/ImageProcessing/proceduralTextureGeneration.h>
#include <BlueFramework/ImageProcessing/ImageFilter.h>

#include <iostream>
//#include "buw.BlueEngine.h"
//#include <BlueFramework/Core/Math/Perlin.h>

OpenInfraPlatform::DataManagement::RandomTerrainImport::RandomTerrainImport(const buw::terrainDescription& td, const buw::Vector3d& offsetViewArea) :
	buw::Import("")
{
    buw::ReferenceCounted<buw::Image4b> imported = buw::makeReferenceCounted<buw::Image4b>(buw::generateRandomHeightmap(td.lod, td.roughness, td.mean, td.deviation));
	buw::ReferenceCounted<buw::Surface> s = buw::claimOwnership<buw::Surface>(buw::Surface::createFromHeightmap(buw::generateRandomHeightmap(td.lod, td.roughness, td.mean, td.deviation), td.tileSize));
    digitalElevationModel_->addSurface(s);
}
