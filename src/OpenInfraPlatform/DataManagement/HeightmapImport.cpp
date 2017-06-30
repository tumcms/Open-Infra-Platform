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

#include "OpenInfraPlatform/DataManagement/HeightmapImport.h"


#include <iostream>
//#include "buw.BlueEngine.h"

OpenInfraPlatform::DataManagement::HeightmapImport::HeightmapImport(const std::string& filename, const buw::Vector3d& offsetViewArea) :
    buw::Import(filename)
{
    buw::ReferenceCounted<buw::Image4b> heightmap = buw::makeReferenceCounted<buw::Image4b>(buw::loadImage4b(filename));
    buw::ReferenceCounted<buw::Surface> s = std::make_shared<buw::Surface>();
    s->setName("Random terrain");

    buw::Vector3d p;
    float tileSize = 1;// td.tileSize;

    for(int y = 0; y < heightmap->getHeight(); y++)
        for(int x = 0; x < heightmap->getWidth(); x++) {
            float v = heightmap->getPixelColor(x, y).red();

            // Generating the vertex positions
            p = buw::Vector3d((x - heightmap->getWidth()/2.0) * tileSize, (y - heightmap->getHeight() / 2.0) * tileSize, v) + offsetViewArea;
            p.z() -= offsetViewArea.z();
            s->addPoint(p);
        }

    // Generating the triangle indicies
    for(int y = 0; y < heightmap->getHeight() - 1; y++) {
        for(int x = 0; x < heightmap->getWidth() - 1; x++) {
            float a = x + y      * heightmap->getWidth();
            float b = x + (y + 1) * heightmap->getWidth();
            float c = (x + 1) + y	    * heightmap->getWidth();

            buw::Vector3i indicies(a, b, c);
            s->addTriangle(indicies);

            a = (x + 1) + y		 * heightmap->getWidth();
            b = x + (y + 1)	 * heightmap->getWidth();
            c = (x + 1) + (y + 1)	 * heightmap->getWidth();

            buw::Vector3i indicies2(a, b, c);
            s->addTriangle(indicies2);
        }
    }

    digitalElevationModel_->addSurface(s);

}