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

#include "PointCloudSection.h"
#include "PointCloud.h"

#include <ccScalarField.h>

OpenInfraPlatform::PointCloudProcessing::PointCloudSection::~PointCloudSection()
{
	pairs_.clear();
}

int OpenInfraPlatform::PointCloudProcessing::PointCloudSection::flagDuplicatePoints(const double minDistance)
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

int OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric, ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
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

int OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computePercentiles(float kernelRadius)
{
	//TODO
	return 0;
}

CCVector3 OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computeCenterOfMass()
{
	if(this->size() > 0) {
		CCVector3 center = CCVector3(0, 0, 0);
		for(size_t i = 0; i < this->size(); i++) {
			center += ((*getPoint(i)) / ((float)this->size()));
		}		
		return center;
	}
	else {
		return CCVector3();
	}
}

CCVector3 OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computeCenter()
{
	CCVector3 min, max;
	getBoundingBox(min, max);
	return min + ((max-min)/2.0f);
}

CCVector3 OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computeMedianCenter()
{
	std::vector<float> x,y,z;

	for_each([&](size_t i) {
		auto point = getPoint(i);
		x.push_back(point->x);
		y.push_back(point->y);
		z.push_back(point->z);
	});

	std::sort(x.begin(), x.end());
	std::sort(y.begin(), y.end());
	std::sort(z.begin(), z.end());

	return CCVector3(x[std::floor(x.size() / 2.0)], y[std::floor(y.size() / 2.0)], z[std::floor(z.size() / 2.0)]);
}

Eigen::Matrix3d OpenInfraPlatform::PointCloudProcessing::PointCloudSection::getOrientation()
{
	Eigen::Matrix3d eigenvectors = createPointCloud3D()->getEigenvectors<3>();
	Eigen::Matrix3d orientation;
	orientation.col(0) = eigenvectors.col(2);
	orientation.col(1) = eigenvectors.col(1);
	orientation.col(2) = eigenvectors.col(0);
	return orientation;
}

std::vector<std::pair<size_t, size_t>> OpenInfraPlatform::PointCloudProcessing::PointCloudSection::computePairs(buw::PairComputationDescription desc, buw::ReferenceCounted<PointCloudSection> nextSection)
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
		float epsilon = desc.maxError;
		float gauge = 1.435f;
		float head = 0.067f;		
		
		
		// Iterate over all pairs of points, we iterate fully since points are not sorted in x direction.
		for(size_t i = 0; i < this->size() - 1; i++) {
			std::vector<std::pair<size_t, size_t>> pairsForPoint = std::vector<std::pair<size_t, size_t>>();
			auto firstPoint = *getPoint(i);

			for(size_t ii = i + 1; ii < this->size(); ii++) {
				auto secondPoint = *getPoint(ii);

				// If first point.x + gauge + head - second point.x < 1cm and difference in y direction is less than 1cm, we have found a pair of matching rail points.
				float distance = (firstPoint - secondPoint).norm();
				float error = std::fabsf(distance - gauge - head);
				float elevationChange = std::fabsf(firstPoint.z - secondPoint.z);
				if(error < epsilon && elevationChange < desc.maxElevationChange) {
					
					// If we already have a pair where the second point is close to this one, compare the error. If this one is better, change it, otherwise skip. Otherwise add.
					bool hasPointInProximity = false;
					for(auto &pair : pairsForPoint) {
						if((*getPoint(pair.second) - secondPoint).norm() < desc.pointProximityDistance) {							
							hasPointInProximity = true;
							break;							
						}
					}
					if(!hasPointInProximity)
						pairsForPoint.push_back(std::pair<size_t, size_t>(i, ii));
				}
			}

			if(desc.includeNextSection && nextSection) {
				std::vector<std::pair<size_t, size_t>> pairsForPointWithNextSection = std::vector<std::pair<size_t, size_t>>();

				for(size_t ii = 0; ii < nextSection->size(); ii++) {
					auto secondPoint = *nextSection->getPoint(ii);
					// If first point.x + gauge + head - second point.x < 1cm and difference in y direction is less than 1cm, we have found a pair of matching rail points.
					float distance = (firstPoint - secondPoint).norm();
					float error = std::fabsf(distance - gauge - head);
					float elevationChange = std::fabsf(firstPoint.z - secondPoint.z);
					if(error < epsilon && elevationChange < desc.maxElevationChange) {
						
						// If we already have a pair where the second point is close to this one, compare the error. If this one is better, change it, otherwise skip. Otherwise add.
						bool hasPointInProximity = false;
						for(auto &pair : pairsForPoint) {
							if((*getPoint(pair.second) - secondPoint).norm() < desc.pointProximityDistance) {
								hasPointInProximity = true;
								break;
							}
						}

						for(auto &pair : pairsForPointWithNextSection) {
							if((*nextSection->getPoint(pair.second) - secondPoint).norm() < desc.pointProximityDistance) {
								hasPointInProximity = true;
								break;
							}
						}
						if(!hasPointInProximity)
							pairsForPointWithNextSection.push_back(std::pair<size_t, size_t>(i, ii));
					}
				}

				std::for_each(pairsForPointWithNextSection.begin(), pairsForPointWithNextSection.end(), [&](std::pair<size_t, size_t> &pair) {
					pair.second += this->size();
				});

				pairs.insert(pairs.end(), pairsForPointWithNextSection.begin(), pairsForPointWithNextSection.end());
			}

			pairs.insert(pairs.end(), pairsForPoint.begin(), pairsForPoint.end());
		}

		std::for_each(pairs.begin(), pairs.end(), [&](std::pair<size_t, size_t> &pair) {
			pair.first = getPointGlobalIndex(pair.first);
			if(desc.includeNextSection && nextSection && pair.second >= this->size())
				pair.second = nextSection->getPointGlobalIndex(pair.second - this->size());
			else
				pair.second = getPointGlobalIndex(pair.second);
		});

		// Do some postprocessing on our points to avoid false pairs.

		// Create a 3D cloud from the pairs to filter it after density and other metrics.
		if(pairs.size() > 0) {

			if(desc.applyDensityFilter) {
				// Do mean density filtering.
				buw::ReferenceCounted<buw::PointCloud> cloud3D = buw::makeReferenceCounted<buw::PointCloud>();
				cloud3D->enableScalarField();
				cloud3D->reserve(pairs.size() * 2);

				for(auto pair : pairs) {
					cloud3D->addPoint(*(associatedCloud->getPoint(pair.first)));
					cloud3D->addPoint(*(associatedCloud->getPoint(pair.second)));
				}

				// Method to compute local density changed some time in CloudCompare.
				//int error = CCLib::GeometricalAnalysisTools::computeLocalDensity(cloud3D.get(), CCLib::GeometricalAnalysisTools::Density::DENSITY_KNN, desc.localDensityKernelRadius, nullptr, nullptr);
				int error = CCLib::GeometricalAnalysisTools::ComputeCharactersitic(CCLib::GeometricalAnalysisTools::GeomCharacteristic::LocalDensity, CCLib::GeometricalAnalysisTools::Density::DENSITY_KNN, cloud3D.get(), desc.localDensityKernelRadius);

				if(error == 0) {
					ScalarType mean;
					cloud3D->getCurrentInScalarField()->computeMinAndMax();
					cloud3D->getCurrentInScalarField()->computeMeanAndVariance(mean);
					cloud3D->setCurrentOutScalarField(cloud3D->getCurrentInScalarFieldIndex());

					// Vector to store the indices of invalid pairs to delete them later;
					std::vector<size_t> invalidPairIndices = std::vector<size_t>();
					for(int i = 0; i < cloud3D->size() - 1; i += 2) {
						if(cloud3D->getPointScalarValue(i) < desc.localDensityThreshold || cloud3D->getPointScalarValue(i + 1) < desc.localDensityThreshold)
							invalidPairIndices.push_back(i / 2);
					}

					size_t offset = 0;
					for(auto index : invalidPairIndices) {
						pairs.erase(pairs.begin() + (index - offset));
						offset++;
					}

				}

				cloud3D = nullptr;
			}

			// Color the pair points and set the scalar value.
			const ColorCompType red[3] = { 255,0,0 };
			const ColorCompType green[3] = { 0,255,0 };
			const ColorCompType yellow[3] = { 255, 255, 0 };

			auto orientation = getOrientation();
			CCVector3 mainAxis = CCVector3(orientation.col(0)[0], orientation.col(0)[1], orientation.col(0)[2]);

			std::for_each(pairs.begin(), pairs.end(), [&](std::pair<size_t, size_t> &pair) {
				if(mainAxis.dot(*associatedCloud->getPoint(pair.first)) < mainAxis.dot(*associatedCloud->getPoint(pair.second))) {
					auto temp = pair.first;
					pair.first = pair.second;
					pair.second = temp;
				}
			});

			std::sort(pairs.begin(), pairs.end(), [&](std::pair<size_t, size_t> &lhs, std::pair<size_t, size_t> &rhs)->bool {
				return mainAxis.dot(*associatedCloud->getPoint(lhs.first)) < mainAxis.dot(*associatedCloud->getPoint(rhs.first));
			});

			if(desc.applyClusterFilter) {
				int current = 0;
				std::vector<std::vector<size_t>> clusters = std::vector<std::vector<size_t>>();
				clusters.push_back(std::vector<size_t>());

				for(int i = 0; i < pairs.size(); i++) {
					clusters[current].push_back(i);

					if(i < pairs.size() - 1) {
						auto point = *associatedCloud->getPoint(pairs[i].first);
						auto nextPoint = *associatedCloud->getPoint(pairs[i + 1].first);
						if((CCVector2(point.x, point.y) - CCVector2(nextPoint.x, nextPoint.y)).norm() > desc.clusterDistance2D) {
							clusters.push_back(std::vector<size_t>());
							current++;
						}
					}
				}

				std::for_each(clusters.begin(), clusters.end(), [&](std::vector<size_t> &vec) {
					std::sort(vec.begin(), vec.end(), [&](size_t &lhs, size_t &rhs)->bool {
						float lhsHeight = 0.5* (associatedCloud->getPoint(pairs[lhs].first)->z + associatedCloud->getPoint(pairs[lhs].second)->z);
						float rhsHeight = 0.5* (associatedCloud->getPoint(pairs[rhs].first)->z + associatedCloud->getPoint(pairs[rhs].second)->z);

						return lhsHeight < rhsHeight;
					});
				});

				std::set<size_t> invalidPairIndices = std::set<size_t>();

				for(auto it : clusters) {
					if(it.size() > 0) {
						auto upperBound = 0.5* (associatedCloud->getPoint(pairs[it[it.size() - 1]].first)->z + associatedCloud->getPoint(pairs[it[it.size() - 1]].second)->z);
						auto lowerBound = 0.5* (associatedCloud->getPoint(pairs[it[0]].first)->z + associatedCloud->getPoint(pairs[it[0]].second)->z);

						if(std::abs(upperBound - lowerBound) > desc.clusterHeightRange) {
							float heightLimit = upperBound - desc.clusterHeightTreshold;

							std::for_each(it.begin(), it.end(), [&](size_t &index) {
								auto height = 0.5* (associatedCloud->getPoint(pairs[index].first)->z + associatedCloud->getPoint(pairs[index].second)->z);
								if(height < heightLimit)
									invalidPairIndices.insert(index);
							});
						}
					}
				}

				std::vector<size_t> invalidPairIndicesSorted = std::vector<size_t>();
				for(auto index : invalidPairIndices) {
					invalidPairIndicesSorted.push_back(index);
				}

				std::sort(invalidPairIndicesSorted.begin(), invalidPairIndicesSorted.end(), [&](size_t &lhs, size_t &rhs)->bool {
					return lhs < rhs;
				});

				size_t offset = 0;
				for(auto index : invalidPairIndicesSorted) {
					pairs.erase(pairs.begin() + (index - offset));
					offset++;
				}
			}

			if(!pairs.empty()) {
				for(auto pair : pairs) {
					if(associatedCloud->rgbColors() != nullptr) {
						associatedCloud->setPointColor(pair.first, ccColor::Rgb(green));
						associatedCloud->setPointColor(pair.second, ccColor::Rgb(red));
					}

					associatedCloud->setPointScalarValue(pair.first, -1);
					associatedCloud->setPointScalarValue(pair.second, 1);
				}
			}
		}
		pairs_ = pairs;
	}
	else {
		//BLUE_LOG(warning) << "Empty section found.";
		pairs_ = std::vector<std::pair<size_t, size_t>>();
	}
	return getPairs();
}

void OpenInfraPlatform::PointCloudProcessing::PointCloudSection::resetPairs()
{
	pairs_.clear();
}

std::vector<std::pair<size_t, size_t>> OpenInfraPlatform::PointCloudProcessing::PointCloudSection::getPairs()
{
	return pairs_;
}

void OpenInfraPlatform::PointCloudProcessing::PointCloudSection::getAxisAlignedBoundingBox(CCVector3 & min, CCVector3 & max)
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

void OpenInfraPlatform::PointCloudProcessing::PointCloudSection::getObjectOrientedBoundingBox(CCVector3 & min, CCVector3 & max)
{
	// Initialize min to maximal possible value and max to minimal possible value.
	min = CCVector3(LONG_MAX, LONG_MAX, LONG_MAX);
	max = CCVector3(LONG_MIN, LONG_MIN, LONG_MIN);

	
	Eigen::Matrix3d rotationMatrix = getOrientation().inverse();	

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

	//CCVector3 shiftedCenter = min + ((max - min) / 2.0f);
	//
	//min -= shiftedCenter;
	//max -= shiftedCenter;	
}


void OpenInfraPlatform::PointCloudProcessing::PointCloudSection::setLength(double length)
{
	length_ = length;
}

const double OpenInfraPlatform::PointCloudProcessing::PointCloudSection::getLength() const
{
	return length_;
}

OpenInfraPlatform::PointCloudProcessing::PointCloudSection::PointCloudSection(GenericIndexedCloudPersist * associatedCloud) : ReferenceCloud(associatedCloud) {
	pairs_ = std::vector<std::pair<size_t, size_t>>();
}

OpenInfraPlatform::PointCloudProcessing::PointCloudSection::PointCloudSection(PointCloudSection & other) : ReferenceCloud(other) {
	pairs_ = other.pairs_;
	length_ = other.length_;
	mainAxis_ = other.mainAxis_;
	cellCode_ = other.cellCode_;
}


buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::PointCloudProcessing::PointCloudSection::createPointCloud2D()
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

buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::PointCloudProcessing::PointCloudSection::createPointCloud3D()
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
