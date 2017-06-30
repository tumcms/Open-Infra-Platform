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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_Surface_f463f8cf_46d8_48e6_960a_4d45f66a5771_h
#define OpenInfraPlatform_Infrastructure_Surface_f463f8cf_46d8_48e6_960a_4d45f66a5771_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/ColorConverter.h>
#include <map>

#include <BlueFramework/Rasterizer/IRenderSystem.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API Surface
{
public:
	Surface();
	virtual ~Surface();

	void clear();

	static Surface* createFlatCopy(const Surface& src);

	//! Checks if a point is within the bounds of this specific surface element.
	bool contains(buw::Vector2d& p) const;

	double getZ(buw::Vector2d& xy) const;				

	// checks if all indices are valid
	bool validate() const;

	buw::Vector3d getBoundsMax() const;
	buw::Vector3d getBoundsMin() const;
			
	//---------------------------------------------------------------------------//
	// Name
	//---------------------------------------------------------------------------//

	void setName(const char* str);

	const char* getName() const;
			
	//---------------------------------------------------------------------------//
	// Points
	//---------------------------------------------------------------------------//

	void setPoints(const std::vector<buw::Vector3d>& points);

	void addPoint(const buw::Vector3d& p);

	int getPointCount() const;
			
	const std::vector<buw::Vector3d>& getPoints() const;

	//---------------------------------------------------------------------------//
	// Triangles
	//---------------------------------------------------------------------------//

	void setTriangles(const std::vector<buw::Vector3i>& indices);

	void addTriangle(const buw::Vector3i& indices);

	int getTriangleCount() const;
			
	const std::vector<buw::Vector3i>&getTriangeFaces() const;

	template<typename T, size_t N> static Surface* createFromHeightmap(buw::Image<buw::Color<T, N>> image, double tileSize) {
		buw::ReferenceCounted<buw::Image<buw::Color<T, N>>> imported = buw::makeReferenceCounted<buw::Image<buw::Color<T, N>>>(image);
		Surface* s = new Surface();
		s->setName("Heightmap terrain");

		buw::Vector3d p;

		buw::ReferenceCounted<buw::Image<buw::Color1f>> heightmap = buw::makeReferenceCounted<buw::Image<buw::Color1f>>(imported->getWidth(), imported->getHeight());
		for(int y = 0; y < heightmap->getHeight(); y++) {
			for(int x = 0; x < heightmap->getWidth(); x++) {
				heightmap->setPixelColor(x, y, buw::ColorConverter::convertTo<buw::Color1f>(imported->getPixelColor(x, y)));
			}
		}
		heightmap = buw::makeReferenceCounted<buw::Image<buw::Color1f>>(BlueFramework::ImageProcessing::applyGaussian<float, 1, buw::eFilterSize::Large>(*heightmap.get(), buw::Matrix22f::Identity()));

		for(int y = 0; y < heightmap->getHeight(); y++)
			for(int x = 0; x < heightmap->getWidth(); x++) {
				float v = heightmap->getPixelColor(x, y)[0];

				// Generating the vertex positions
				p = buw::Vector3d((x - heightmap->getWidth() / 2.0) * tileSize, (y - heightmap->getHeight() / 2.0) * tileSize, v);
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
		return s;
	}

private:
	double zRay(buw::Vector2d& xy, int faceID) const;

	bool pointInTriangle(buw::Vector2d& pt, int faceID) const;

	double sign(buw::Vector2d p1, buw::Vector2d p2, buw::Vector2d p3) const;

	void updateBounds(const buw::Vector3d& p);

private:
	std::vector<buw::Vector3d>			points_;
	std::vector<buw::Vector3i>			triangeIndices_;
	std::string							name_;

	// cached data
	buw::Vector3d						boundsMax_;
	buw::Vector3d						boundsMin_;
};	

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Surface;
}			
			
#endif // end define OpenInfraPlatform_Infrastructure_Surface_f463f8cf_46d8_48e6_960a_4d45f66a5771_h
