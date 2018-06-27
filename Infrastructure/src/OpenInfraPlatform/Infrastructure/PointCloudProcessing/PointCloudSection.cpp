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

OpenInfraPlatform::Infrastructure::PointCloudSection::~PointCloudSection()
{
}

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

CCVector3 OpenInfraPlatform::Infrastructure::PointCloudSection::computeCenterOfMass()
{
	if(this->size() > 0) {
		CCVector3 center = CCVector3(0, 0, 0);
		for(size_t i = 0; i < this->size(); i++) {
			center += ((*getPoint(i)) / ((float)this->size()));
		}
		//CCLib::Neighbourhood neighbourhood = CCLib::Neighbourhood(this);
		//return *neighbourhood.getGravityCenter();
		return center;
	}
	else {
		return CCVector3();
	}
}

CCVector3 OpenInfraPlatform::Infrastructure::PointCloudSection::computeCenter()
{
	CCVector3 min, max;
	getBoundingBox(min, max);
	return min + ((max-min)/2.0f);
}

Eigen::Matrix3d OpenInfraPlatform::Infrastructure::PointCloudSection::getOrientation()
{
	auto orientation = createPointCloud3D()->getEigenvectors<3>();

	//auto roll = buw::calculateAngleBetweenVectors(buw::Vector3d(1.0, 0.0, 0.0), orientation.col(2).normalized());
	//auto yaw = buw::calculateAngleBetweenVectors(buw::Vector3d(0.0, 0.0, 1.0), orientation.col(1).normalized());
	//auto pitch = buw::calculateAngleBetweenVectors(buw::Vector3d(0.0, 1.0, 0.0), orientation.col(0).normalized());
	
	double maxX = 0, maxY = 0, maxZ = 0;
	for(int c = 0; c < 3; c++) {
		maxX = std::abs(maxX) < std::abs(Eigen::Vector3d::UnitZ().dot(orientation.col(c))) ? Eigen::Vector3d::UnitZ().dot(orientation.col(c)) : maxX;
		maxY = std::abs(maxY) < std::abs(Eigen::Vector3d::UnitY().dot(orientation.col(c))) ? Eigen::Vector3d::UnitY().dot(orientation.col(c)) : maxY;
		maxZ = std::abs(maxZ) < std::abs(Eigen::Vector3d::UnitX().dot(orientation.col(c))) ? Eigen::Vector3d::UnitX().dot(orientation.col(c)) : maxZ;
	}

	//auto roll = std::acos(Eigen::Vector3d::UnitZ().dot(orientation.col(2)));
	//auto yaw = std::acos(Eigen::Vector3d::UnitY().dot(orientation.col(1)));
	//auto pitch = std::acos(Eigen::Vector3d::UnitX().dot(orientation.col(0)));

	auto roll = std::acos(maxX);
	auto yaw = std::acos(maxY);
	auto pitch = std::acos(maxZ);

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
	Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitZ());

	Eigen::Quaternion<double> q = (rollAngle * yawAngle) * pitchAngle;
	return q.matrix();
}

std::vector<std::pair<size_t, size_t>> OpenInfraPlatform::Infrastructure::PointCloudSection::computePairs()
{
	if(this->size() > 0) {
		// Project all points in this section onto the LS plane to get 2D coordinates.
		buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());

		// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
		int idx = associatedCloud->getScalarFieldIndexByName("Railway");
		if(idx == -1) {
			//BLUE_LOG(warning) << "No Scalar Field called \"Railway\" detected.";
			return std::vector<std::pair<size_t, size_t>>();
		}

		associatedCloud->setCurrentInScalarField(idx);
		
		// Set up our pairs as set so that every pair is only contained once.
		std::vector<std::pair<size_t, size_t>> pairs = std::vector<std::pair<size_t, size_t>>();
		// Allow 0.1cm of error, standard gauge witdth is 1.435m and the width of the track head itself is 67mm.
		float epsilon = 0.01f;
		float gauge = 1.435f;
		float head = 0.067f;		
		
		
		// Iterate over all pairs of points, we iterate fully since points are not sorted in x direction.
		for(size_t i = 0; i < this->size() - 1; i++) {
			for(size_t ii = i + 1; ii < this->size(); ii++) {

				// If first point.x + gauge + head - second point.x < 1cm and difference in y direction is less than 1cm, we have found a pair of matching rail points.
				float distance = (*getPoint(i) - *getPoint(ii)).norm();
				float error = std::fabsf(distance - gauge - head);
				if(error < epsilon && std::fabsf(getPoint(i)->z - getPoint(ii)->z) < 0.2f) {
					pairs.push_back(std::pair<size_t, size_t>(getPointGlobalIndex(i), getPointGlobalIndex(ii)));
					break;
				}
			}
		}

		// Do some postprocessing on our points to avoid false pairs.

		// Create a 3D cloud from the pairs to filter it after density and other metrics.
		if(pairs.size() > 0) {
			
			buw::ReferenceCounted<buw::PointCloud> cloud3D = buw::makeReferenceCounted<buw::PointCloud>();
			cloud3D->enableScalarField();
			cloud3D->reserve(pairs.size() * 2);

			for(auto pair : pairs) {
				cloud3D->addPoint(*(associatedCloud->getPoint(pair.first)));
				cloud3D->addPoint(*(associatedCloud->getPoint(pair.second)));
			}

			int error = CCLib::GeometricalAnalysisTools::computeLocalDensity(cloud3D.get(), CCLib::GeometricalAnalysisTools::Density::DENSITY_KNN, gauge/2.0f, nullptr, nullptr);

			if(error == 0) {
				ScalarType mean;
				cloud3D->getCurrentInScalarField()->computeMinAndMax();
				cloud3D->getCurrentInScalarField()->computeMeanAndVariance(mean);
				cloud3D->setCurrentOutScalarField(cloud3D->getCurrentInScalarFieldIndex());
				
				// Vector to store the indices of invalid pairs to delete them later;
				std::vector<size_t> invalidPairIndices = std::vector<size_t>();
				for(int i = 0; i < cloud3D->size() - 1; i += 2) {
					if(cloud3D->getPointScalarValue(i) < 0.75f * mean || cloud3D->getPointScalarValue(i + 1) < 0.75f * mean)
						invalidPairIndices.push_back(i / 2);
				}
				
				size_t offset = 0;
				for(auto index : invalidPairIndices) {
					pairs.erase(pairs.begin() + (index - offset));
					offset++;
				}
			
			}

			cloud3D = nullptr;

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
		}

		return pairs;
	}
	else {
		//BLUE_LOG(warning) << "Empty section found.";
		return std::vector<std::pair<size_t, size_t>>();
	}
}

void OpenInfraPlatform::Infrastructure::PointCloudSection::getAxisAlignedBoundingBox(CCVector3 & min, CCVector3 & max)
{
	// Initialize min to maximal possible value and max to minimal possible value.
	min = CCVector3(LONG_MAX, LONG_MAX, LONG_MAX);
	max = CCVector3(LONG_MIN, LONG_MIN, LONG_MIN);
	
	for_each([&](size_t i) {
		auto point = getPoint(i);
		min.x = std::min(min.x, point->x);
		min.y = std::min(min.y, point->y);
		min.z = std::min(min.z, point->z);
	
		max.x = std::max(max.x, point->x);
		max.y = std::max(max.y, point->y);
		max.z = std::max(max.z, point->z);
	});
}

void OpenInfraPlatform::Infrastructure::PointCloudSection::getObjectOrientedBoundingBox(CCVector3 & min, CCVector3 & max)
{
	// Initialize min to maximal possible value and max to minimal possible value.
	min = CCVector3(LONG_MAX, LONG_MAX, LONG_MAX);
	max = CCVector3(LONG_MIN, LONG_MIN, LONG_MIN);

	
	Eigen::Matrix3d rotationMatrix = getOrientation();	

	auto center = computeCenter();
	for_each([&](size_t i) {
		auto ccPoint = *getPoint(i) - center;
		auto point = buw::Vector3d(ccPoint.x, ccPoint.y, ccPoint.z);

		buw::Vector3f rotated = (rotationMatrix * point).cast<float>();

		min.x = std::min(min.x, rotated.x());
		min.y = std::min(min.y, rotated.y());
		min.z = std::min(min.z, rotated.z());

		max.x = std::max(max.x, rotated.x());
		max.y = std::max(max.y, rotated.y());
		max.z = std::max(max.z, rotated.z());
	});

	min += center;
	max += center;
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

buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::Infrastructure::PointCloudSection::createPointCloud3D()
{
	// Create an empty cloud which we return when finished and reserve as much space as we have indices.
	buw::ReferenceCounted<buw::PointCloud> cloud3D = buw::makeReferenceCounted<buw::PointCloud>();
	cloud3D->reserve(size());
	buw::PointCloud* associatedCloud = dynamic_cast<buw::PointCloud*>(getAssociatedCloud());

	for_each([&](size_t i) {
		CCVector3 pointShifted;
		getPoint(i, pointShifted);		
		cloud3D->addPoint(pointShifted);
	});

	return cloud3D;
}