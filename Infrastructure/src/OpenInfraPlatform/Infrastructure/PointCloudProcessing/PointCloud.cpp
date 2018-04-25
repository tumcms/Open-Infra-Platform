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

#include "PointCloud.h"

#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloudSection.h"

#include <BlueFramework/Core/Diagnostics/log.h>

#include <ccScalarField.h>
#include <FileIOFilter.h>
#include <GenericProgressCallback.h>
#include <ScalarFieldTools.h>

#include <liblas/liblas.hpp>

#include <algorithm>


buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::Infrastructure::PointCloud::FromFile(const char * filename)
{
	buw::ReferenceCounted<buw::PointCloud> pointCloud = buw::makeReferenceCounted<buw::PointCloud>(QString(filename));

	// Initialize the filters for file IO.
	if(FileIOFilter::GetFilters().size() == 0)
		FileIOFilter::InitInternalFilters();

	// Get file extension and try to find the best filter for it.
	QString extension = QString(filename).split(".").last().toUpper();
	auto filter = FileIOFilter::FindBestFilterForExtension(extension);

	if(filter) {
		CC_FILE_ERROR err;
		// Load the point cloud from file and store it temporarily.
		std::shared_ptr<ccHObject> ccTempObject = std::shared_ptr<ccHObject>(FileIOFilter::LoadFromFile(QString(filename), FileIOFilter::LoadParameters(), FileIOFilter::FindBestFilterForExtension("BIN"), err));
		if(err == CC_FILE_ERROR::CC_FERR_NO_ERROR) {
			for(size_t i = 0; i < ccTempObject->getChildrenNumber(); i++) {
				ccPointCloud* temp = ccHObjectCaster::ToPointCloud(ccTempObject->getChild(i));
				if(temp) {
					pointCloud->append(temp, pointCloud->size());
				}
			}
		}

		//Delete our temporary parrent object.
		ccTempObject = nullptr;	
	}
	else {
		if(extension == "LAS") {
			// see http://www.liblas.org/tutorial/cpp.html
			std::ifstream ifs;

			ifs.open(filename, std::ios::in | std::ios::binary);

			liblas::ReaderFactory f;
			liblas::Reader reader = f.CreateWithStream(ifs);

			liblas::Header const& header = reader.GetHeader();

			BLUE_LOG(info) << "Compressed: " << ((header.Compressed() == true) ? "true" : "false");
			BLUE_LOG(info) << "Signature: " << header.GetFileSignature();
			BLUE_LOG(info) << "Points count: " << header.GetPointRecordsCount();

			buw::Vector3d minv(0, 0, 0);
			buw::Vector3d maxv(0, 0, 0);

			pointCloud->clear();

			//Reserve the points.
			pointCloud->reserve(header.GetPointRecordsCount());
			pointCloud->reserveTheRGBTable();

			bool first = true;
			CCVector3d scale = CCVector3d(header.GetScaleX(), header.GetScaleY(), header.GetScaleZ());
			for(size_t i = 0; i < header.GetPointRecordsCount(); i++) {
				if(reader.ReadNextPoint()) {
					liblas::Point const& p = reader.GetPoint();
					float colorRange = std::numeric_limits<liblas::Color::value_type>::max();

					int32_t posLiblas[3] = { p.GetRawX(), p.GetRawY(), p.GetRawZ() };
					liblas::Color colLiblas = p.GetColor();
					const ccColor::Rgb* color = new ccColor::Rgb(ccColor::FromRgbf(ccColor::Rgbf(colLiblas.GetRed() / colorRange, colLiblas.GetGreen() / colorRange, colLiblas.GetBlue() / colorRange)).rgb);
					pointCloud->addPoint(CCVector3(posLiblas[0] * scale.x, posLiblas[1] * scale.y, posLiblas[2] * scale.z));
					pointCloud->addRGBColor(color->rgb);
				}
			}
		}
		else {
			// TODO
		}
	}
	pointCloud->setName(filename);
	pointCloud->init();
	return pointCloud;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Get the main axis and compute the length of the projection along this axis for each point.
	CCVector3 axis = mainAxis_;

	int idx_plamn = getScalarFieldIndexByName("ProjectionLengthAlongMainAxis");
	if(idx_plamn == -1)
		idx_plamn = addScalarField("ProjectionLengthAlongMainAxis");

	setCurrentInScalarField(idx_plamn);
	auto setProjectionLengthAlongMainAxis = [&](size_t i) {
		this->setPointScalarValue(i, axis.dot(*(this->getPoint(i))));
	};

	for_each(setProjectionLengthAlongMainAxis);

	// Compute and get the scalar fields min and max value.
	getScalarField(idx_plamn)->computeMinAndMax();
	ScalarType min, max;
	std::tie(min, max) = getScalarFieldMinAndMax(idx_plamn);

	// Compute the number of sections and initialize the variable.
	size_t numSections = (std::floorf(length * max) - std::floorf(length * min)) + 1;
	sections_ = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>(numSections);
	setCurrentOutScalarField(idx_plamn);

	// Get or create the scalar field SectionId.
	int idx_sid = getScalarFieldIndexByName("SectionId");
	if(idx_sid == -1)
		idx_sid = addScalarField("SectionId");

	// Assign the sectionId depending on the projection length.
	setCurrentInScalarField(idx_sid);
	const float base = std::floorf(length * min);
	for_each([&](size_t i) {

		// Calculate the sectionId and add it as ScalarValue.
		size_t sectionId = std::floorf(length *getPointScalarValue(i)) - base;
		setPointScalarValue(i, sectionId);

		// Create the sections reference cloud if it doesn't exist.
		if(!sections_[sectionId]) {
			sections_[sectionId] = buw::makeReferenceCounted<buw::PointCloudSection>(static_cast<GenericIndexedCloudPersist*>(this));
			sections_[sectionId]->setLength(length);
		}

		sections_[sectionId]->addPointIndex(i);

	});

	// Create empty sections to avoid nullptrs.
	for(auto& section : sections_) {
		if(!section)
			section = buw::makeReferenceCounted<buw::PointCloudSection>(static_cast<GenericIndexedCloudPersist*>(this));
		section->setLength(length);
	}
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeGrid()
{
	grid_.clear();
	grid_ = std::map<std::pair<int, int>, std::vector<uint32_t>>();
	for_each([&](size_t i) {
		auto pos = getPoint(i);
		std::pair<int, int> key = std::pair<int, int>((int)pos->x, (int)pos->y);
		grid_[key].push_back(i);
	});
}

void OpenInfraPlatform::Infrastructure::PointCloud::alignOnMainAxis()
{
	
	auto roll = buw::calculateAngleBetweenVectors(buw::Vector3d(1.0, 0.0, 0.0), buw::Vector3d(mainAxis_.x, mainAxis_.y, mainAxis_.z).normalized());

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(0, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(0, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;
	Eigen::Matrix3d rotationMatrix = q.matrix();

	ccGLMatrix rotation;
	rotation.initFromParameters(-roll, 0, 0, CCVector3(0, 0, 0));
	applyRigidTransformation(rotation);
}


int OpenInfraPlatform::Infrastructure::PointCloud::flagDuplicatePoints(const double minDistance, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Get octree or build it if not yet built.
	if(!octree_) {
		octree_ = buw::makeReferenceCounted<CCLib::DgmOctree>(this);
		octree_->build();
	}

	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName("Duplicate");
	if(idx == -1)
		idx = addScalarField("Duplicate");

	// Set it as input scalar field to write explicitly to it - not sure if this is really necessary..
	// Set it to be the current output scalar field to avoid overriding another one since flagDuplicatePoints uses this field.
	setCurrentInScalarField(idx);
	setCurrentOutScalarField(idx);

	return CCLib::GeometricalAnalysisTools::flagDuplicatePoints(this, minDistance, callback.get(), octree_.get());
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyLocalDensityFilter(LocalDensityFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	int err = 0;

	// Compute the density, either for the volume or the sections.
	if(desc.dim == ePointCloudFilterDimension::Volume3D) {
		err = computeLocalDensity((CCLib::GeometricalAnalysisTools::Density) desc.density, desc.kernelRadius, callback);
	}
	else {
		// Start the callback and set the progress as percentage of sections processed.
		callback->start();
		for(size_t i = 0; i < sections_.size(); i++) {
			// We don't save the error code since it sometimes fails with sparse sections.
			sections_[i]->computeLocalDensity(desc.density, desc.kernelRadius, nullptr);
			callback->update(100.0* ((double)i / (double)sections_.size()));
		}
		callback->stop();
	}

	// If everything worked - at least for 3D volume.
	if(err == 0) {

		// Get our scalar field. If we cant find our scalar field, something went wrong and we abort and return -1.
		int idx = getScalarFieldIndexByName("Density");
		if(idx == -1) {
			err = idx;			
		}
		else {
			// Set the Density Scalar field as in and output field since we want to read it and threshold it.
			setCurrentInScalarField(idx);
			setCurrentOutScalarField(idx);

			// Compare the scalar value for each point with the threshold and write the result into the scalar field since we're not interested in the real densities.
			for_each([&](size_t i) {
				ScalarType density = getPointScalarValue(i);
				setPointScalarValue(i, (int)(density < desc.minThreshold));
			});

			// Update our indices for filtered etc.
			computeIndices();
		}
	}
	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyDuplicateFilter(DuplicateFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	int err = 0;

	// Call flagDuplicatePoints on this or on all sections.
	if(desc.dim == buw::ePointCloudFilterDimension::Volume3D) {
		err = flagDuplicatePoints(desc.minDistance, callback);

		// Manually stop the callback if one has been passed.
		if(callback)
			callback->stop();
	}
	else {
		// Start the callback and set the progress as percentage of sections processed.
		callback->start();
		for(size_t i = 0; i < sections_.size(); i++) {
			err = sections_[i]->flagDuplicatePoints(desc.minDistance);
			callback->update(100.0* ((double)i / (double)sections_.size()));						
		}
		callback->stop();
	}
	
	// Update the indices about which points are filtered or not.
	computeIndices();

	return err;
}

void OpenInfraPlatform::Infrastructure::PointCloud::resetFilter(const char * name)
{
	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName(name);
	if(idx == -1)
		idx = addScalarField(name);

	// Set Duplicate as Scalar field to write to and flag each point with duplicate 0
	setCurrentInScalarField(idx);
	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});

	computeIndices();
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric, ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName("Density");
	if(idx == -1)
		idx = addScalarField("Density");

	// Set it as input scalar field to write explicitly to it - not sure if this is really necessary..
	// Set it to be the current output scalar field to avoid overriding another one since computeLocalDensity uses this field.
	setCurrentInScalarField(idx);
	//setCurrentOutScalarField(idx);

	// Compute the local density and retirn the error code.
	return CCLib::GeometricalAnalysisTools::computeLocalDensity(this, metric, kernelRadius, callback ? callback.get() : nullptr, octree_ ? octree_.get() : nullptr);
}

void OpenInfraPlatform::Infrastructure::PointCloud::init()
{
	// Initialize our point cloud for usage - compute main axis, octree and sections.
	remainingIndices_ = std::vector<uint32_t>(size());
	#pragma omp parallel for
	for(long i = 0; i < size(); i++) {
		remainingIndices_[(uint32_t)i] = i;
	}
	filteredIndices_ = std::vector<uint32_t>(0);
	segmentedIndices_ = std::vector<uint32_t>(0);

	grid_ = std::map<std::pair<int, int>, std::vector<uint32_t>>();

	computeMainAxis();
	//alignOnMainAxis();
	octree_ = buw::makeReferenceCounted<CCLib::DgmOctree>(this);
	octree_->build();
	computeSections(10.0f);
}

std::vector<buw::ReferenceCounted<buw::PointCloudSection>> OpenInfraPlatform::Infrastructure::PointCloud::getSections()
{
	return sections_;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeIndices()
{
	// Clear the index buffers.
	remainingIndices_.clear();
	filteredIndices_.clear();

	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if(idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");		
	
	setCurrentInScalarField(idx_filtered);
	
	// Get the duplicate scalar field.
	int idx_duplicate = getScalarFieldIndexByName("Duplicate");
	if(idx_duplicate == -1)
		idx_duplicate = addScalarField("Duplicate");

	// Get the density scalar field
	int idx_density = getScalarFieldIndexByName("Density");
	if(idx_density == -1)
		idx_density = addScalarField("Density");

	// For each point, check it's Density and Duplicate field and if one of them is true, filter the point.
	for_each([&](size_t i) {
		ScalarType filtered = 0;
		setCurrentOutScalarField(idx_duplicate);
		filtered += getPointScalarValue(i);

		setCurrentOutScalarField(idx_density);
		filtered += getPointScalarValue(i);
		setPointScalarValue(i, filtered);

		if(filtered > 0) {
			filteredIndices_.push_back(i);
		}
		else {
			remainingIndices_.push_back(i);
		}
	});
}


const std::tuple<ScalarType, ScalarType> OpenInfraPlatform::Infrastructure::PointCloud::getScalarFieldMinAndMax(int idx) const
{
	// Get the min and max for the scalar field and store it in the returned tuple.
	CCLib::ScalarField* field = getScalarField(idx);
	return std::tuple<ScalarType, ScalarType>(field->getMin(), field->getMax());
}

int OpenInfraPlatform::Infrastructure::PointCloud::computePercentiles(float kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	// Clear all segmented indices -> should be changed to work with scalar fields to allow multiple segmentation methods, same as in filtering.
	segmentedIndices_.clear();

	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if(idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");		
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("Segmented");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("Segmented");
	setCurrentInScalarField(idx_segmented);

	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(kernelRadius);

	// Start OpenMP parallel region and pass callback as firstprivate to the master thread.
	int tid = 0;
	#pragma omp parallel private(tid) firstprivate(callback) shared(level)
	{
		// Get the OpenMP thread id and initialize variables for progress update.
		tid = omp_get_thread_num();
		float totalPoints = remainingIndices_.size() / omp_get_num_threads();
		float processedPoints = 0;

		// Initialize a thread local index buffer and octree as copy of the original one.
		auto indices = std::set<uint32_t>();
		auto octree = CCLib::DgmOctree(*octree_);

		#pragma omp for
		for(long i = 0; i < remainingIndices_.size(); i++) {
			uint32_t index = remainingIndices_[i];
			
			// Compute the neighbouring points using the octree for the query point.
			CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
			int numPoints = octree.getPointsInSphericalNeighbourhood(*getPoint(index), kernelRadius, neighbours, level);

			// Sort points in neighbourhood according to height.
			std::sort(neighbours.begin(), neighbours.end(), [](const CCLib::DgmOctree::PointDescriptor &lhs, const CCLib::DgmOctree::PointDescriptor &rhs) -> bool { return lhs.point->z < rhs.point->z; });

			// Remove points which have actually been removed due to filtering.
			auto isFilteredPoint = [&](const CCLib::DgmOctree::PointDescriptor point) -> bool {
				return getPointScalarValue(point.pointIndex) > 0;
			};

			auto end = std::remove_if(neighbours.begin(), neighbours.end(), isFilteredPoint);
			neighbours.erase(end, neighbours.end());
			numPoints = neighbours.size();

			// Calculate the 98 percentile as the index of the 98th % point after sorting in ascending order, same for the 10th % point.
			int idx98 = (int)std::floor(0.98 * numPoints);
			int idx10 = (int)std::floor(0.1 * numPoints);
			float percentile_98 = neighbours[idx98].point->z;
			float percentile_10 = neighbours[idx10].point->z;

			// Calculate the absolute difference between the percentiles and if it is larger than 10cm segment the point as rail point.
			float diff = std::fabsf(percentile_10 - percentile_98);
			float totalDiff = std::fabsf((neighbours.front().point->z) - (neighbours.back().point->z));
			// Edited to exclude points if total diff in neigbourhood is larger than 25cm
			if(diff >= 0.1f) {
				for(int ii = idx98; ii < neighbours.size(); ii++) {
					int index_ii = neighbours[ii].pointIndex;
					setPointScalarValue(index_ii, 1.0f);
					indices.insert(index_ii);
				}
			}
			

			// Update the number of processed points and update the callback if we are on the main thread.
			processedPoints++;
			if(tid == 0 && callback) {
				callback->update(100.0f * processedPoints / totalPoints);
			}
		}

		// Reduce the individual buffers in the global buffer.
		#pragma omp critical
		{
			segmentedIndices_.insert(segmentedIndices_.end(), indices.begin(), indices.end());
		}
	}
	
	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::computePercentilesOnGrid(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	computeGrid();

	// Clear all segmented indices -> should be changed to work with scalar fields to allow multiple segmentation methods, same as in filtering.
	segmentedIndices_.clear();

	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if(idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("Segmented");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("Segmented");
	setCurrentInScalarField(idx_segmented);

	auto isFilteredPoint = [&](const uint32_t &idx) -> bool {
		return getPointScalarValue(idx) > 0;
	};

	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(0.1f);
	size_t processedCells = 0;
	size_t numCells = grid_.size();

	for(auto cell : grid_) {
		auto end = std::remove_if(cell.second.begin(), cell.second.end(), isFilteredPoint);
		cell.second.erase(end, cell.second.end());
		int numPoints = cell.second.size();


		std::sort(cell.second.begin(), cell.second.end(), [&](const uint32_t &lhs, const uint32_t &rhs)-> bool {
			return getPoint(lhs)->z < getPoint(rhs)->z;
		});

		// Calculate the 98 percentile as the index of the 98th % point after sorting in ascending order, same for the 10th % point.
		int idx98 = (int)std::floor(0.98 * numPoints);
		int idx10 = (int)std::floor(0.1 * numPoints);
		float percentile_98 = getPoint(cell.second[idx98])->z;
		float percentile_10 = getPoint(cell.second[idx10])->z;

		// Calculate the absolute difference between the percentiles and if it is larger than 10cm segment the point as rail point.
		float diff = std::fabsf(percentile_10 - percentile_98);
		if(diff >= 0.1f) {
			std::set<uint32_t> indices;
			for(int i = idx98; i < numPoints; i++) {
				CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
				int numNeighbours = octree_->getPointsInSphericalNeighbourhood(*getPoint(cell.second[i]), 0.1f, neighbours, level);

				for(auto elem : neighbours) {
					indices.insert(elem.pointIndex);
					setPointScalarValue(elem.pointIndex, 1.0f);
				}
				indices.insert(i);
				setPointScalarValue(i, 1.0f);
			}
			segmentedIndices_.insert(segmentedIndices_.end(), indices.begin(), indices.end());
		}

		processedCells++;
		if(callback) {
			callback->update(100.0f * processedCells / numCells);
		}
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return 0;
}

void OpenInfraPlatform::Infrastructure::PointCloud::removeNotSegmentedPoints()
{
	int idx_segmented = getScalarFieldIndexByName("Segmented");

	// Abort if we have no filtered points.
	if(idx_segmented == -1)
		return;

	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_segmented);
	float epsilon = 0.0001f;
	ccPointCloud* segmented = filterPointsByScalarValue(0, epsilon, true);

	// Clear all points from the point cloud.
	clear();

	// Clear the index buffers.
	remainingIndices_.clear();
	filteredIndices_.clear();
	segmentedIndices_.clear();

	// Clear all sections.
	sections_.clear();

	// Remove all scalar fields.
	deleteAllScalarFields();

	// Append the filtered cloud and initialize the cloud.
	append(segmented, 0);

	init();
}

void OpenInfraPlatform::Infrastructure::PointCloud::removeFilteredPoints(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(callback)
		callback->start();

	int idx_filtered = getScalarFieldIndexByName("Filtered");

	// Abort if we have no filtered points.
	if(idx_filtered == -1)
		return;

	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_filtered);
	float epsilon = 0.0001f;
	ccPointCloud* filtered = filterPointsByScalarValue(0, epsilon);	
	
	// Clear all points from the point cloud.
	clear();

	// Clear the index buffers.
	remainingIndices_.clear();
	filteredIndices_.clear();
	segmentedIndices_.clear();

	// Clear all sections.
	sections_.clear();

	// Remove all scalar fields.
	deleteAllScalarFields();

	// Append the filtered cloud and initialize the cloud.
	append(filtered, 0);

	init();

	if(callback)
		callback->stop();
}

const CCVector3 OpenInfraPlatform::Infrastructure::PointCloud::getMainAxis() const
{
	return mainAxis_;
}

const double OpenInfraPlatform::Infrastructure::PointCloud::getSectionLength() const
{
	// If sections are initialized, return the length of the first section since all are equally long.
	if(sections_[0]) {
		return sections_[0]->getLength();
	}
}

const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> OpenInfraPlatform::Infrastructure::PointCloud::getIndices() const
{
	return std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>>(remainingIndices_, filteredIndices_, segmentedIndices_);
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeMainAxis()
{
	// Set the main axis as the eigenvector with the largest eigenvalue.
	mainAxis_ = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());
}
