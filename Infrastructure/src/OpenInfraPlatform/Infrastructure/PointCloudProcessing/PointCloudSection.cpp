/*
Copyright (c) 2018 Technical University of Munich
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

#include "PointCloudSection.h"
#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloud.h"
#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloudProcessing.h"

#include <ccScalarField.h>

extern const ccColor::Rgba red;
extern const ccColor::Rgba green;

int OpenInfraPlatform::Infrastructure::PointCloudSection::flagDuplicatePoints(const double minDistance)
{
	buw::ReferenceCounted<buw::PointCloud> cloud2D = createPointCloud2D();
	buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());

	int idx = associatedCloud->getScalarFieldIndexByName("Duplicate");
	if(idx == -1)
		idx = associatedCloud->addScalarField("Duplicate");

	associatedCloud->setCurrentInScalarField(idx);

	cloud2D->flagDuplicatePoints(minDistance);
	cloud2D->for_each([&](size_t i) {
		associatedCloud->setPointScalarValue(this->getPointGlobalIndex(i), cloud2D->getPointScalarValue(i));
	});

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloudSection::computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric, ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	buw::ReferenceCounted<buw::PointCloud> cloud2D = createPointCloud2D();
	buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());

	int idx = associatedCloud->getScalarFieldIndexByName("Density");
	if(idx == -1)
		idx = associatedCloud->addScalarField("Density");

	associatedCloud->setCurrentInScalarField(idx);

	int err = cloud2D->computeLocalDensity(metric, kernelRadius, nullptr);
	if(err == 0) {
		cloud2D->for_each([&](size_t i) {
			associatedCloud->setPointScalarValue(this->getPointGlobalIndex(i), cloud2D->getPointScalarValue(i));
		});
	}
	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloudSection::computePercentiles(float kernelRadius)
{
	//TODO
	return 0;
}

std::set<std::pair<size_t, size_t>> OpenInfraPlatform::Infrastructure::PointCloudSection::computePairs()
{
	if(this->size() > 0) {
		// Project all points in this section onto the LS plane to get 2D coordinates.
		CCLib::Neighbourhood neighbourhood = CCLib::Neighbourhood(this);
		buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());

		// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
		int idx = associatedCloud->getScalarFieldIndexByName("Railway");
		if(idx == -1)
			idx = associatedCloud->addScalarField("Railway");
		associatedCloud->setCurrentInScalarField(idx);

		auto axis = associatedCloud->getMainAxis();
		auto center = neighbourhood.getGravityCenter();
		// Calculate d as projection of the section center onto the main axis.
		float d = axis.dot(*center);

		// Set the plane along the main axis at the position of the projection of the center of mass of the section.
		float plane[4] = { axis.x, axis.y, axis.z, d };

		// Project the points on the plane.
		std::vector<CCVector2> points2D = std::vector<CCVector2>();
		neighbourhood.projectPointsOn2DPlane(points2D, plane);

		// Set up our pairs as set so that every pair is only contained once.
		std::set<std::pair<size_t, size_t>> pairs = std::set<std::pair<size_t, size_t>>();
		
		// Allow 0.1cm of error, standard gauge witdth is 1.435m and the width of the track head itself is 67mm.
		float epsilon = 0.005f;
		float gauge = 1.435f;
		float head = 0.067f;		
		
		// Iterate over all pairs of points, we iterate fully since points are not sorted in x direction.
		//for(size_t i = 0; i < points2D.size() - 1; i++) {
		//	for(size_t ii = i + 1; ii < points2D.size(); ii++) {
		//
		//		// If first point.x + gauge + head - second point.x < 1cm and difference in y direction is less than 1cm, we have found a pair of matching rail points.
		//		float distance = (points2D[i] - points2D[ii]).norm();
		//		float error = std::fabsf(distance - gauge - head);
		//		if(error < epsilon && std::fabsf(points2D[i].y - points2D[ii].y) < 0.05f) {
		//			pairs.insert(std::pair<size_t, size_t>(getPointGlobalIndex(i), getPointGlobalIndex(ii)));
		//		}
		//	}
		//}

		// Iterate over all pairs of points, we iterate fully since points are not sorted in x direction.
		for(size_t i = 0; i < this->size() - 1; i++) {
			for(size_t ii = i + 1; ii < this->size(); ii++) {

				// If first point.x + gauge + head - second point.x < 1cm and difference in y direction is less than 1cm, we have found a pair of matching rail points.
				float distance = (*getPoint(i) - *getPoint(ii)).norm();
				float error = std::fabsf(distance - gauge - head);
				if(error < epsilon && std::fabsf(getPoint(i)->z - getPoint(ii)->z) < 0.1f) {
					pairs.insert(std::pair<size_t, size_t>(getPointGlobalIndex(i), getPointGlobalIndex(ii)));
				}
			}
		}

		// Do some postprocessing on our points to avoid false pairs.
		// This has become obsolete due to symmetrical distances
		if(false) {
			// First of all, a point should always only be on one side of a pair, it should never appear on both sides.
			for(auto elem : pairs) {
				size_t confusionMatrix[2][2] = { {0,0},{0,0} };

				for(auto other : pairs) {
					// Counts how often we find our left index on the left side.
					if(elem.first == other.first)
						confusionMatrix[0][0]++;

					// Counts how often we find our left index on the right side.
					if(elem.first == other.second)
						confusionMatrix[0][1]++;

					// Counts how often we find our right index on the left side.
					if(elem.second == other.first)
						confusionMatrix[1][0]++;

					// Counts how often we find our right index on the right side.
					if(elem.second == other.second)
						confusionMatrix[1][1]++;
				}

				// If this pair is ambiguous - meaning the left side appears more often on the right side and so on, erase it.
				if(!(confusionMatrix[0][0] > confusionMatrix[0][1] && confusionMatrix[1][1] > confusionMatrix[1][0])) {
					pairs.erase(elem);
				}
			}
		}

		// Color the pair points and set the scalar value.
		const ColorCompType red[3] = { 255,0,0 };
		const ColorCompType green[3] = { 0,255,0 };
		const ColorCompType yellow[3] = { 255, 255, 0 };

		for(auto pair : pairs) {
			if(associatedCloud->rgbColors() != nullptr) {
				associatedCloud->setPointColor(pair.first, yellow);
				associatedCloud->setPointColor(pair.second, yellow);
			}
			
			associatedCloud->setPointScalarValue(pair.first, -1);
			associatedCloud->setPointScalarValue(pair.second, 1);
		}

		return pairs;
	}
	else {
		BLUE_LOG(warning) << "Empty section found.";
		return std::set<std::pair<size_t, size_t>>();
	}
}


void OpenInfraPlatform::Infrastructure::PointCloudSection::setLength(double length)
{
	length_ = length;
}

const double OpenInfraPlatform::Infrastructure::PointCloudSection::getLength() const
{
	return length_;
}


buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::Infrastructure::PointCloudSection::createPointCloud2D()
{
	// Create an empty cloud which we return when finished and reserve as much space as we have indices.
	buw::ReferenceCounted<buw::PointCloud> cloud2D = buw::makeReferenceCounted<buw::PointCloud>();
	cloud2D->reserve(size());
	buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());
	CCVector3 axis = associatedCloud->getMainAxis();

	associatedCloud->setCurrentOutScalarField(associatedCloud->getScalarFieldIndexByName("ProjectionLengthAlongMainAxis"));

	for_each([&](size_t i) {
		CCVector3 pointShifted;
		getPoint(i, pointShifted);
		float diff = (std::floorf(length_ * getPointScalarValue(i)) / length_) - getPointScalarValue(i);
		pointShifted += diff * axis;
		cloud2D->addPoint(pointShifted);
	});

	return cloud2D;
}