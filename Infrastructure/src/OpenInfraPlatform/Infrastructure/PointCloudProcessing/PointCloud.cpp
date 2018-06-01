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
#include <CloudSamplingTools.h>

#include <liblas/liblas.hpp>

#include <algorithm>

#include <QDateTime>
#include <QDir>


buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::Infrastructure::PointCloud::FromFile(const char * filename)
{
	buw::ReferenceCounted<buw::PointCloud> pointCloud = buw::makeReferenceCounted<buw::PointCloud>(QString(filename));

	// Initialize the filters for file IO.
	if(FileIOFilter::GetFilters().size() == 0)
		FileIOFilter::InitInternalFilters();

	// Get file extension and try to find the best filter for it.
	QString extension = QString(filename).split(".").last().toUpper();
	auto filter = FileIOFilter::FindBestFilterForExtension(extension);

	BLUE_LOG(trace) << "Importing " << extension.toStdString() << " point cloud " << filename << ".";
	if(filter) {
		CC_FILE_ERROR err;
		// Load the point cloud from file and store it temporarily.
		std::shared_ptr<ccHObject> ccTempObject = std::shared_ptr<ccHObject>(FileIOFilter::LoadFromFile(QString(filename), FileIOFilter::LoadParameters(), FileIOFilter::FindBestFilterForExtension("BIN"), err));
		if(err == CC_FILE_ERROR::CC_FERR_NO_ERROR) {
			BLUE_LOG(trace) << "Number of child objects:" << QString::number(ccTempObject->getChildrenNumber()).toStdString() << ".";
			for(size_t i = 0; i < ccTempObject->getChildrenNumber(); i++) {
				auto child = ccTempObject->getChild(i);
				ccPointCloud* temp = ccHObjectCaster::ToPointCloud(child);
				BLUE_LOG(trace) << "Processing child #" << QString::number(i).toStdString() << ". Name:" << child->getName().toStdString();
				
				if(temp) {
					BLUE_LOG(trace) << "Size:" << QString::number(temp->size()).toStdString() << ".";
					size_t sizeBefore = pointCloud->size();

					pointCloud->reserve(sizeBefore + temp->size());
					for(size_t ii = 0; ii < temp->size(); ii++) {
						pointCloud->addPoint(CCVector3(*(temp->getPoint(ii))));
					}

					//pointCloud->append(temp, sizeBefore);

					if(sizeBefore == pointCloud->size())
						BLUE_LOG(warning) << "No points added. Size:" << QString::number(sizeBefore).toStdString();
				}
				else {
					if(child)
						BLUE_LOG(warning) << "Cast to point cloud failed for child object " << child->getName().toStdString() << ".";
					else
						BLUE_LOG(error) << "Something went terribly wrong...";
				}
			}
		}

		BLUE_LOG(trace) << "Finished processing child objects. Total size:" << QString::number(pointCloud->size()).toStdString() << ".";

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

	BLUE_LOG(trace) << "Finished importing " << filename << ".";


	pointCloud->setName(filename);
	pointCloud->init();

	

	return pointCloud;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	BLUE_LOG(trace) << "Start computing sections. Length:" << length;
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

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections2(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(callback)
		callback->start();

	sections_ = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>();
			
	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(100);
	BLUE_LOG(trace) << "Octree Level:" << (int)level;
	BLUE_LOG(trace) << "Octree Cell Size:" << octree_->getCellSize(level);

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	std::vector<uint32_t> dgmOctreeCells;
	bool success = octree_->getCellIndexes(level, dgmOctreeCells);	

	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;

#pragma omp parallel private(tid) firstprivate(callback) shared(level, dgmOctreeCells, numCells, err)
	{
		// Initialize our variables for callback updates.
		tid = omp_get_thread_num();
		auto octree = CCLib::DgmOctree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;


		// Iterate over all cells to call our nearest neighbour search on consecutive points in a cell for performance reasons.
#pragma omp for schedule(dynamic, 50)
		for(long idx = 0; idx < dgmOctreeCells.size(); idx++) {
			auto cell = dgmOctreeCells[idx];
			auto code = octree.getCellCode(cell);

			// Create and initialize the nearest neighbour search struct as far as possible.
			CCLib::DgmOctree::NearestNeighboursSphericalSearchStruct nss;
			nss.level = level;
			nss.maxSearchSquareDistd = std::pow(100, 2);
			nss.alreadyVisitedNeighbourhoodSize = 0;
			nss.minNumberOfNeighbors = 0;

			// Get the points in the cell specified by the index and store them in points. Compute the cell position and center.
			std::shared_ptr<CCLib::ReferenceCloud> points = std::make_shared<CCLib::ReferenceCloud>(this);
			success = octree.getPointsInCellByCellIndex(points.get(), cell, level);
			octree.getCellPos(code, level, nss.cellPos, false);
			octree.computeCellCenter(nss.cellPos, level, nss.cellCenter);

			if(success) {
				nss.queryPoint = *getPoint(cell);
				int numPoints = octree.findNeighborsInASphereStartingFromCell(nss, 50, false);

				auto getPCA = [&]()->CCVector3 {
					//Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX3d mat;
					mat.resize(numPoints, 3);
					for(size_t i = 0; i < numPoints; i++) {
						auto pos = *nss.pointsInNeighbourhood[i].point;
						mat.row(i) = Eigen::Vector3d(pos.x, pos.y, pos.z);
					}

					//Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1).normalized();

					return CCVector3(vec.x(), vec.y(), vec.z());
				};

				auto axis = getPCA();

				std::vector<std::pair<size_t, double>> indexedProjectionLength = std::vector<std::pair<size_t, double>>();

				for(size_t i = 0; i < points->size(); i++)
					indexedProjectionLength.push_back(std::pair<size_t, double>(points->getPointGlobalIndex(i), axis.dot(*points->getPoint(i))));

				std::sort(indexedProjectionLength.begin(), indexedProjectionLength.end(), [](const std::pair<size_t, double> &lhs, const std::pair<size_t, double> &rhs) -> bool {
					return lhs.second < rhs.second;
				});

				ScalarType min = indexedProjectionLength.front().second, max = indexedProjectionLength.back().second;
				size_t numSections = (std::floorf(length * max) - std::floorf(length * min)) + 1;
				auto sections = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>(numSections);
				const float base = std::floorf(length * min);

				for(auto it : indexedProjectionLength) {
					size_t sectionId = std::floorf(length * it.second) - base;

					if(!sections[sectionId]) {
						sections[sectionId] = buw::makeReferenceCounted<buw::PointCloudSection>(static_cast<GenericIndexedCloudPersist*>(this));
						sections[sectionId]->setLength(length);
						sections[sectionId]->cellCode_ = code;
					}

					sections[sectionId]->addPointIndex(it.first);
				}

				auto end = std::remove_if(sections.begin(), sections.end(), [](const buw::ReferenceCounted<buw::PointCloudSection> &section) -> bool { return section == nullptr; });

#pragma omp critical
				{
					sections_.insert(sections_.end(), sections.begin(), end);
				}

				// Update our callback.
				processedCells++;
				if(processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if(tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			}
			else {
				// Stop the callback if we abort our function.
				if(tid == 0 && callback)
					callback->stop();
#pragma omp critical
				err = -2;
			}
		}
	}

	if(callback)
		callback->stop();

	
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

int OpenInfraPlatform::Infrastructure::PointCloud::applyPositionFilter(const buw::PositionFilterDescription & desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	int err = 0;

	if(callback)
		callback->start();

	if(desc.dimension >= 0 && desc.dimension < 3) {		
		int idx = -1;
		switch(desc.dimension) {
		case 0: idx = addScalarField("Coord. X"); break;
		case 1: idx = addScalarField("Coord. Y"); break;
		case 2: idx = addScalarField("Coord. Z"); break;
		default:
			err = -1;
			break;
		}

		if(idx != -1) {
			setCurrentScalarField(idx);
		}
		else {
			BLUE_LOG(warning) << "No scalar field found.";
			err = -3;
		}
		for_each([&](size_t i) {
			ScalarType value = (*(getPoint(i)))[desc.dimension];
			if(value < desc.minValue || value > desc.maxValue)
				setPointScalarValue(i, 1.0f);
			else
				setPointScalarValue(i, 0.0f);

			if(callback)
				callback->update(100.0f * ((float)i / (float)size()));
		});

		computeIndices();
	}
	else {
		BLUE_LOG(warning) << "Invalid dimension number " << QString::number(desc.dimension).toStdString() << " specified. Choose X=0, Y=1 or Z=2.";
		err = -1;
	}

	if(callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetPositionFilter()
{
	deleteScalarField(getScalarFieldIndexByName("Coord. X"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Y"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Z"));

	computeIndices();
	return 0;
}

void OpenInfraPlatform::Infrastructure::PointCloud::resetScalarField(const char * name)
{
	// Get the specified scalar field.
	int idx = getScalarFieldIndexByName(name);
	if(idx == -1)
		idx = addScalarField(name);

	// Set all values in the scalar field to 0.
	setCurrentInScalarField(idx);
	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});

	// Delete the scalar field.
	deleteScalarField(idx);

	// Recompute our indices.
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
	BLUE_LOG(trace) << "Start initializing point cloud.";

	// If we have no colors, we add white as color to all points.
	if(rgbColors() == nullptr) {
		BLUE_LOG(warning) << "No colors found. Adding color white to each point.";
		if(reserveTheRGBTable()) {
			for_each([&](size_t i) {
				addRGBColor(255, 255, 255);
			});
			BLUE_LOG(trace) << "Successfully added colors.";
		}
		else {
			BLUE_LOG(warning) << "Reserving the color table failed.";
		}
	}

	// Initialize our point cloud for usage - compute main axis, octree and sections.
	remainingIndices_ = std::vector<uint32_t>(this->size());
	for(uint32_t i = 0; i < this->size(); i++) {
		remainingIndices_[(uint32_t)i] = i;
	}
	filteredIndices_ = std::vector<uint32_t>(0);
	segmentedIndices_ = std::vector<uint32_t>(0);

	grid_ = std::map<std::pair<int, int>, std::vector<uint32_t>>();

	computeMainAxis();
	//alignOnMainAxis();
	BLUE_LOG(trace) << "Start building octree.";
	octree_ = buw::makeReferenceCounted<CCLib::DgmOctree>(this);
	octree_->build();
	BLUE_LOG(trace) << "Finished building octree.";

	computeSections2(10.0f);
}

std::vector<buw::ReferenceCounted<buw::PointCloudSection>> OpenInfraPlatform::Infrastructure::PointCloud::getSections()
{
	return sections_;
}

buw::ReferenceCounted<CCLib::ReferenceCloud> OpenInfraPlatform::Infrastructure::PointCloud::subsample(size_t size)
{
	BLUE_LOG(fatal) << "This function should never be called right now.";
	return buw::ReferenceCounted<CCLib::ReferenceCloud>(CCLib::CloudSamplingTools::subsampleCloudWithOctree(this, size, CCLib::CloudSamplingTools::SUBSAMPLING_CELL_METHOD::NEAREST_POINT_TO_CELL_CENTER, nullptr, octree_.get()));
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

	// Get the coordinate filter scalar fields.
	int idx_coordX = getScalarFieldIndexByName("Coord. X");
	int idx_coordY = getScalarFieldIndexByName("Coord. Y");
	int idx_coordZ = getScalarFieldIndexByName("Coord. Z");

	// For each point, check it's Density and Duplicate field and if one of them is true, filter the point.
	for_each([&](size_t i) {
		ScalarType filtered = 0;
		if(idx_duplicate != -1) {
			setCurrentOutScalarField(idx_duplicate);
			filtered += getPointScalarValue(i);
		}

		if(idx_density != -1) {
			setCurrentOutScalarField(idx_density);
			filtered += getPointScalarValue(i);
		}

		if(idx_coordX != -1) {
			setCurrentOutScalarField(idx_coordX);
			filtered += getPointScalarValue(i);
		}

		if(idx_coordY != -1) {
			setCurrentOutScalarField(idx_coordY);
			filtered += getPointScalarValue(i);
		}

		if(idx_coordZ != -1) {
			setCurrentOutScalarField(idx_coordZ);
			filtered += getPointScalarValue(i);
		}

		setPointScalarValue(i, filtered);

		if(filtered > 0) {
			filteredIndices_.push_back(i);
		}
		else {
			remainingIndices_.push_back(i);
		}
	});

	// Clear the segmented indices buffer.
	segmentedIndices_.clear();

	// Get the base segmented sclar field and set is as the write active one.
	int idx_segmented = getScalarFieldIndexByName("Segmented");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("Segmented");
	setCurrentInScalarField(idx_segmented);

	// Reset the base scalar field for segmented 
	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});

	// Get the specific segmentations: percentile, grid and rate of change.
	int idx_percentile = getScalarFieldIndexByName("SegmentedPercentile");
	int idx_grid = getScalarFieldIndexByName("SegmentedGrid");
	int idx_rof = getScalarFieldIndexByName("SegmentedRateOfChange");	
	
	// For each point, set as segmented if all enabled segmentations apply.
	for_each([&](size_t i) {
		int numFilters = 0;
		int numValidFilters = 0;
		auto updateSegmentedValue = [&](size_t i, int index) {
			if(index != -1) {
				numFilters++;
				this->setCurrentOutScalarField(index);
				if(this->getPointScalarValue(i) > 0) {
					numValidFilters++;
				}
			}
		};

		updateSegmentedValue(i, idx_percentile);
		updateSegmentedValue(i, idx_grid);
		updateSegmentedValue(i, idx_rof);

		if(numFilters == numValidFilters && numFilters != 0)
			setPointScalarValue(i, 1);
		else
			setPointScalarValue(i, 0);
	});

	// Set the segmented scalar field to read from and insert the points into the buffer.
	setCurrentOutScalarField(idx_segmented);

	for_each([&](size_t i) {
		if(getPointScalarValue(i) > 0) {
			segmentedIndices_.push_back(i);
		}
	});
}


const std::tuple<ScalarType, ScalarType> OpenInfraPlatform::Infrastructure::PointCloud::getScalarFieldMinAndMax(int idx) const
{
	// Get the min and max for the scalar field and store it in the returned tuple.
	CCLib::ScalarField* field = getScalarField(idx);
	field->computeMinAndMax();
	return std::tuple<ScalarType, ScalarType>(field->getMin(), field->getMax());
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesSegmentation(buw::PercentileSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();
	
	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if(idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");		
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented percentile scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedPercentile");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedPercentile");
	setCurrentInScalarField(idx_segmented);

	for_each([&](size_t i) {
		this->setPointScalarValue(i, 0);
	});

	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(desc.kernelRadius);

	// Start OpenMP parallel region and pass callback as firstprivate to the master thread.
	int tid = 0;
	#pragma omp parallel private(tid) firstprivate(callback) shared(level)
	{
		// Get the OpenMP thread id and initialize variables for progress update.
		tid = omp_get_thread_num();
		float totalPoints = remainingIndices_.size() / omp_get_num_threads();
		float processedPoints = 0;

		// Initialize octree as copy of the original one.
		auto octree = CCLib::DgmOctree(*octree_);

		#pragma omp for
		for(long i = 0; i < remainingIndices_.size(); i++) {
			uint32_t index = remainingIndices_[i];
			
			// Compute the neighbouring points using the octree for the query point.
			CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
			int numPoints = octree.getPointsInSphericalNeighbourhood(*getPoint(index), desc.kernelRadius, neighbours, level);

			// Sort points in neighbourhood according to height.
			std::sort(neighbours.begin(), neighbours.end(), [](const CCLib::DgmOctree::PointDescriptor &lhs, const CCLib::DgmOctree::PointDescriptor &rhs) -> bool { return lhs.point->z < rhs.point->z; });

			// Remove points which have actually been removed due to filtering.
			auto isFilteredPoint = [&](const CCLib::DgmOctree::PointDescriptor point) -> bool {
				return getPointScalarValue(point.pointIndex) > 0;
			};
			auto end = std::remove_if(neighbours.begin(), neighbours.end(), isFilteredPoint);
			neighbours.erase(end, neighbours.end());
			numPoints = neighbours.size();

			// Calculate the 98 percentile as the index of the upper % point after sorting in ascending order, same for the lower % point.
			int idxUpper = (int)std::floor(desc.upperPercentile * numPoints);
			int idxLower = (int)std::floor(desc.lowerPercentile * numPoints);
			float percentileUpper = neighbours[idxUpper].point->z;
			float percentileLower = neighbours[idxLower].point->z;

			// Calculate the absolute difference between the percentiles and if it is larger than 10cm segment the point as rail point.
			float diff = std::fabsf(percentileLower - percentileUpper);
			float totalDiff = std::fabsf((neighbours.front().point->z) - (neighbours.back().point->z));

			// If the diff is larger than the minThreshold and the totalDiff smaller than the maxThreshold, mark all points in the upper percentile.
			if(diff >= desc.minThreshold && totalDiff < desc.maxThreshold) {
				for(int ii = idxUpper; ii < neighbours.size(); ii++) {
					int index_ii = neighbours[ii].pointIndex;
					setPointScalarValue(index_ii, 1.0f);
				}
			}
			

			// Update the number of processed points and update the callback if we are on the main thread.
			processedPoints++;
			if(tid == 0 && callback) {
				callback->update(100.0f * processedPoints / totalPoints);
			}
		}		
	}

	computeIndices();
	
	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesSegmentationHP(const buw::PercentileSegmentationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();
	
	// Get the segmented percentile scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedPercentile");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedPercentile");
	setCurrentInScalarField(idx_segmented);

	// Initialize all scalar values in the field to 0.
	for_each([&](size_t i) {
		this->setPointScalarValue(i, 0);
	});

	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(desc.kernelRadius);

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	std::vector<uint32_t> dgmOctreeCells;
	bool success = octree_->getCellIndexes(level, dgmOctreeCells);
	if(!success)
		return -1;

	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;

#pragma omp parallel private(tid) firstprivate(callback) shared(level, dgmOctreeCells, desc, numCells, err)
	{
		// Initialize our variables for callback updates.
		tid = omp_get_thread_num();
		auto octree = CCLib::DgmOctree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;

		// Iterate over all cells to call our nearest neighbour search on consecutive points in a cell for performance reasons.
#pragma omp for schedule(dynamic, 50)
		for(long idx = 0; idx < dgmOctreeCells.size(); idx++) {
			auto cell = dgmOctreeCells[idx];
			auto code = octree.getCellCode(cell);						

			// Create and initialize the nearest neighbour search struct as far as possible.
			CCLib::DgmOctree::NearestNeighboursSphericalSearchStruct nss;
			nss.level = level;
			nss.maxSearchSquareDistd = std::pow(desc.kernelRadius, 2);
			nss.alreadyVisitedNeighbourhoodSize = 0;
			nss.minNumberOfNeighbors = 0;

			// Get the points in the cell specified by the index and store them in points. Compute the cell position and center.
			std::shared_ptr<CCLib::ReferenceCloud> points = std::make_shared<CCLib::ReferenceCloud>(this);
			success = octree.getPointsInCellByCellIndex(points.get(), cell, level);
			octree.getCellPos(code, level, nss.cellPos, false);
			octree.computeCellCenter(nss.cellPos, level, nss.cellCenter);

			if(success) {
				// If the points were successfully selected, iterate over all points in the cell and search the nearest neighbours.
				for(int i = 0; i < points->size(); i++) {
					nss.queryPoint = *(points->getPoint(i));
					int numPoints = octree.findNeighborsInASphereStartingFromCell(nss, desc.kernelRadius, false);

					// Sort points in neighbourhood according to height.
					std::sort(nss.pointsInNeighbourhood.begin(), nss.pointsInNeighbourhood.begin() + numPoints, [](const CCLib::DgmOctree::PointDescriptor &lhs, const CCLib::DgmOctree::PointDescriptor &rhs) -> bool { return lhs.point->z < rhs.point->z; });


					// Calculate the upper percentile as the index of the upper % point after sorting in ascending order, same for the lower % point.
					int idxUpper = (int)std::floor(desc.upperPercentile * numPoints);
					int idxLower = (int)std::floor(desc.lowerPercentile * numPoints);
					float percentileUpper = nss.pointsInNeighbourhood[idxUpper].point->z;
					float percentileLower = nss.pointsInNeighbourhood[idxLower].point->z;

					// Calculate the absolute difference between the percentiles and if it is larger than the specified threshold, segment the point as rail point.
					float diff = std::fabsf(percentileLower - percentileUpper);
					float totalDiff = std::fabsf((nss.pointsInNeighbourhood[0].point->z) - (nss.pointsInNeighbourhood[numPoints - 1].point->z));

					// If the diff is larger than the minThreshold and the totalDiff smaller than the maxThreshold, mark all points in the upper percentile.
					if(diff >= desc.minThreshold && totalDiff < desc.maxThreshold) {
						for(int ii = idxUpper; ii < numPoints; ii++) {
							size_t index_ii = nss.pointsInNeighbourhood[ii].pointIndex;
							this->setPointScalarValue(index_ii, 1.0f);
						}
					}
				}

				// Update our callback.
				processedCells++;
				if(processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if(tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			}
			else {
				// Stop the callback if we abort our function.
				if(tid == 0 && callback)
					callback->stop();
#pragma omp critical
				err = -2;
			}
		}
	}

	computeIndices();

	if(callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesOnGridSegmentation(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	computeGrid();
	
	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if(idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedGrid");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedGrid");
	setCurrentInScalarField(idx_segmented);

	for_each([&](size_t i) {
		this->setPointScalarValue(i, 0);
	});

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
					setPointScalarValue(elem.pointIndex, 1.0f);
				}
				setPointScalarValue(i, 1.0f);
			}
		}

		processedCells++;
		if(callback) {
			callback->update(100.0f * processedCells / numCells);
		}
	}

	computeIndices();

	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyRateOfChangeSegmentation(RateOfChangeSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedRateOfChange");
	if(idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedRateOfChange");
	setCurrentInScalarField(idx_segmented);

	// Initialize our scalar field.
	for_each([&](size_t i) {
		this->setPointScalarValue(i, 0);
	});

	bool success = false;

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	std::vector<uint32_t> dgmOctreeCells;
	success = octree_->getCellIndexes(10, dgmOctreeCells);
	if(!success)
		return -1;

	// Get the best level for the neighbourhood size, set to 10 currently since it works better than finding it with a library function.
	unsigned char level = 10;


	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;

#pragma omp parallel private(tid) firstprivate(callback) shared(dgmOctreeCells, desc, numCells, err, level)
	{
		// Initialize our variables for callback updates.
		tid = omp_get_thread_num();
		auto octree = CCLib::DgmOctree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;

#pragma omp for schedule(dynamic, 50)
		for(long idx = 0; idx < dgmOctreeCells.size(); idx++) {
			auto cell = dgmOctreeCells[idx];
			auto code = octree.getCellCode(cell);

			// Create and initialize the nearest neighbour search struct as far as possible. Level is 10, maxSearchSquareDistance is calculated from the description parameter.
			CCLib::DgmOctree::NearestNeighboursSearchStruct nss;
			nss.level = level;
			nss.maxSearchSquareDistd = std::pow(desc.maxNeighbourDistance, 2);

			// Get the points in the cell specified by the index and store them in points. Compute the cell position and center.
			std::shared_ptr<CCLib::ReferenceCloud> points = std::make_shared<CCLib::ReferenceCloud>(this);
			success = octree_->getPointsInCellByCellIndex(points.get(), cell, level);
			octree_->getCellPos(code, level, nss.cellPos, false);
			octree_->computeCellCenter(nss.cellPos, level, nss.cellCenter);

			if(success) {
				// If the points were successfully selected, iterate over all points in the cell and search the nearest neighbours.
				for(int i = 0; i < points->size(); i++) {
					nss.queryPoint = *(points->getPoint(i));
					int numNeighbours = octree_->findNearestNeighborsStartingFromCell(nss);

					// Initialize the diff variable and the number of neighbours which are selected for the computation.
					float diff = 0.0f;
					int numSelectedNeighbours = 0;

					// Calculate the mean difference in the specified dimension for all points in the neighbourhood which fulfill the conditions.
					for(auto neighbour : nss.pointsInNeighbourhood) {
						if(neighbour.squareDistd <= nss.maxSearchSquareDistd && neighbour.squareDistd != 0.0) {
							diff += std::fabsf(nss.queryPoint[desc.dim] - (*neighbour.point)[desc.dim]);
							numSelectedNeighbours++;
						}
					}

					// If we found at least one neighbour, compute the average diff and compare with the threshold.
					if(numSelectedNeighbours > 0) {
						diff /= numSelectedNeighbours;
						if(diff <= desc.maxRateOfChangeThreshold) {
							this->setPointScalarValue(points->getPointGlobalIndex(i), 1.0f);
						}
					}
				}

				// Update our callback.
				processedCells++;
				if(processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if(tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			}
			else {
				// Stop the callback if we abort our function.
				if(tid == 0 && callback)
					callback->stop();

				err = -2;
			}
		}
		
	}

	computeIndices();

	// Stop our callback.
	if(callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlines(const buw::CenterlineComputationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	// Add a scalar field for railway and encode the left/right railway index as -1 and 1. Initialize it to 0 and set it as input scalar field.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if(idx_railway == -1)
		idx_railway = addScalarField("Railway");
	setCurrentInScalarField(idx_railway);

	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});

	// Create a global list of all point pairs.
	std::vector<std::pair<size_t, size_t>> rails = std::vector<std::pair<size_t, size_t>>();
	int tid = 0;
#pragma omp parallel private(tid)
	{
		// Setup callback update variables.
		tid = omp_get_thread_num();
		int numSectionsPerThread = (sections_.size() - 2) / omp_get_num_threads();
		int numSectionsPerPercent = numSectionsPerThread / 100;
		int processedSections = 0;
		int percentageCompleted = 0;

		// We iterate over all sections and calculate the pairs of matching points.
		std::vector<std::pair<size_t, size_t>> pairs = std::vector<std::pair<size_t, size_t>>();
#pragma omp for schedule(dynamic, 20)
		for(long i = 0; i < sections_.size() - 1; i++) {

			// Create a new local section. Resize it to be able to hold this and the next section.
			auto section = sections_[i];
			
			//auto section = PointCloudSection(this);
			//section.reserve(sections_[i]->size() + sections_[i + 1]->size());

			// Append the next section.
			//section.add(*(sections_[i]));
			//section.add(*(sections_[i + 1]));

			// Insert all pairs in our local vector.
			auto result = section->computePairs();
			pairs.insert(pairs.end(), result.begin(), result.end());

			// Update our callback.
			processedSections++;
			if(processedSections >= numSectionsPerPercent) {
				percentageCompleted++;
				processedSections = 0;

				if(tid == 0 && callback) {
					callback->update(percentageCompleted);
				}
			}

		}


		// Merge the local vectors in the master vector.
#pragma omp critical
		{
			rails.insert(rails.end(), pairs.begin(), pairs.end());
		}
	}

	// Stop our callback.
	if(callback)
		callback->stop();
	

	// Reserve space for the centerpoints points and color them blue.
	this->reserve(this->size() + rails.size());
	this->reserveTheRGBTable();

	// For each pair, insert the point in the middle as centerpoints point.
	std::vector<CCVector3> centerpoints = std::vector<CCVector3>(rails.size());
	for(auto pair : rails) {
		CCVector3 start = *(getPoint(pair.first));
		CCVector3 end = *(getPoint(pair.second));
		CCVector3 center = 0.5f * (end + start);
		centerpoints.push_back(center);
	}

	// Delete the pairs since we dont need them anymore.
	rails.clear();

	// Sort the centerpoints along the main axis.
	std::sort(centerpoints.begin(), centerpoints.end(), [&](const CCVector3 &lhs, const CCVector3 &rhs)->bool { return mainAxis_.dot(lhs) < mainAxis_.dot(rhs); });

	// Split the centerpoints into different rails and recognize different rails. Only store indices to save memory.
	std::vector<std::vector<size_t>> centerlines = std::vector<std::vector<size_t>>();
	centerlines.push_back(std::vector<size_t>());
	centerlines[0].push_back(0);

	auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) ->float {
		return (rhs - lhs).norm();
	};

	// Start our callback if we have one.
	if(callback)
		callback->start();

	// Initialize variables for callback update.
	float totalPoints = centerpoints.size();
	int pointsPerPercent = totalPoints / 100;
	float processedPoints = 0;
	int percentageCompleted = 0;


	for(size_t i = 1; i < centerpoints.size(); i++) {
		// Store the point to be checked and whether we have inserted it or whether it is ambiguous or not.
		auto point = centerpoints[i];
		bool inserted = false;
		bool ambiguous = false;
		bool unnecessary = false;

		auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end)->CCVector3 {
				//Matrix which is capable of holding all points for PCA.
				Eigen::MatrixX3d mat;
				mat.resize(end - start, 3);
				for(size_t i = start; i < end; i++) {
					auto pos = centerpoints[alignment[i]];
					mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
				}

				//Do PCA to find the largest eigenvector -> main axis.
				Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
				Eigen::MatrixXd cov = centered.adjoint() * centered;
				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
				Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1);

				return CCVector3(vec.x(), vec.y(), vec.z());
			};

		// Initialize the pair min with index and distance
		std::pair<size_t, float> min = std::pair<size_t, float>(centerlines.size(), LONG_MAX);

#pragma omp parallel private(tid) firstprivate(callback) shared(inserted, ambiguous, unnecessary, min)
		{
			tid = omp_get_thread_num();
			// Iterate over all centerlines.
#pragma omp for 
			for(long ii = 0; ii < centerlines.size(); ii++) {

				if(ambiguous || unnecessary)
					break;

				auto &line = centerlines[ii];
				
				// Calculate the distance to the endpoint
				auto endpoint = centerpoints[line.back()];
				float distance = dist(point, endpoint);

				if(distance <= 0.001) {
#pragma omp critical
					unnecessary = true;
					break;
				}

				// If the distance is smaller than 20cm, we would add the point to this line.
				if(distance < desc.maxDistance) {
					long startIndex = line.size() - 1, endIndex = line.size() - 1;

					while(startIndex > 0 && dist(endpoint, centerpoints[line[startIndex]]) < 1)
						startIndex--;

					auto axis = startIndex != endIndex ? getPCA(line, startIndex, endIndex) : (point - endpoint);
					axis.normalize();

					auto direction = (point - endpoint);
					direction.normalize();

					float angle = std::acos(axis.dot(direction)) * 180.0 / M_PI;

					if(angle < 5) {
						// If the point would also be inserted somewhere else, it is labeled as ambiguous and is dropped.
						if(inserted) {
#pragma omp critical
							ambiguous = true;
							break;
						}
						// Otherwise the min distance is updated and inserted is set to true.
						else {
#pragma omp critical 
							{
								inserted = true;
								if(distance < min.second)
									min = std::pair<size_t, float>(ii, distance);
							}
						}
					}
				}
			}
#pragma omp barrier
#pragma omp master
			{

			// If the point is not ambiguous, we either insert it in the matching line or create a new one.
				if(!ambiguous && !unnecessary) {
					if(inserted) {
						centerlines[min.first].push_back(i);
					}
					else {
						// If no matching line has been found, add a new one with this one as the starting point.				
						centerlines.push_back(std::vector<size_t>());
						centerlines.back().push_back(i);
					}
				}

				//Check if we have a centerline which is very small (does not meet the minimum requirements as specified) and remove it to save some computation time.
				if(i % 1000 == 0) {

					// Erase the centerlines which do not fulfill the criteria and where no more points are being added.
					auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) { return std::fabsf(mainAxis_.dot(point) - mainAxis_.dot(centerpoints[line.back()])) > 1.0f && (line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength); });
					centerlines.erase(end, centerlines.end());
				}

				// Update the callback.
				if(callback) {
					if(++processedPoints >= pointsPerPercent) {
						percentageCompleted++;
						processedPoints = 0;
						callback->update(percentageCompleted);
					}
				}
			}
		}
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();



	// Clear all lines having less then 100 points -> probably noise or something.
	auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool { return line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength; });
	centerlines.erase(end, centerlines.end());
	
	if(callback)
		callback->start();

	// Collapse centerlines to have a uniform density.
	std::vector<std::vector<CCVector3>> alignments = std::vector<std::vector<CCVector3>>(centerlines.size());
	percentageCompleted = 0;
	bool update = true;

	// Iterate over all segments and combine the centers of each projection section.
#pragma omp parallel private(tid) firstprivate(callback) shared(percentageCompleted, update, alignments, centerlines, centerpoints)
	{
		tid = omp_get_thread_num();
		int percentPerCenterline = 100 / centerlines.size();
		update = true;

#pragma omp for schedule(dynamic)
		for(long idx = 0; idx < centerlines.size(); idx++) {

			auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end)->CCVector3 {
				//Matrix which is capable of holding all points for PCA.
				Eigen::MatrixX3d mat;
				mat.resize(end - start, 3);
				for(size_t i = start; i < end; i++) {
					auto pos = centerpoints[alignment[i]];
					mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
				}

				//Do PCA to find the largest eigenvector -> main axis.
				Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
				Eigen::MatrixXd cov = centered.adjoint() * centered;
				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
				Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1).normalized();

				return CCVector3(vec.x(), vec.y(), vec.z());
			};


			// Get the line which we are working on and store the start and end index for the section for which we want to combine all points as their center of mass.
			auto &line = centerlines[idx];
			long startIndex = 0, endIndex = 0;
			long lineSize = line.size();

			// Iterate over the line and check how far we make our progress along the main axis. Once we are above a certain threshold, we combine all points in their center of mass.
			for(size_t i = 0; i < lineSize - 1; i++) {
				//auto axis = getPCA(line, std::max(0, (int)i - 100000), std::min((int)line.size() - 1, (int) i + 100000));
				auto startPoint = centerpoints[line[startIndex]];

				long startIndexPCA = startIndex, endIndexPCA = startIndex;

				while((startIndexPCA > 100) && dist(centerpoints[line[startIndexPCA]], startPoint) < 10)
					startIndexPCA-=100;

				while((endIndexPCA < lineSize - 101) && dist(centerpoints[line[endIndexPCA]], startPoint) < 10)
					endIndexPCA+=100;

				auto axis = getPCA(line, startIndexPCA, endIndexPCA);

				float startLength = axis.dot(startPoint);

				while(i < lineSize - 1 && std::fabsf(axis.dot(centerpoints[line[i + 1]]) - startLength) < desc.centerlineDensity)
					i++;
				
				endIndex = i + 1;
				int numPoints = (endIndex - startIndex);
				CCVector3 center = CCVector3(0, 0, 0);
				for(; startIndex < endIndex; startIndex++) {
					center += (centerpoints[line[startIndex]] / (float)numPoints);
				}

				alignments[idx].push_back(center);

				if(tid == 0 && callback && update) {
					callback->update(percentageCompleted);
					update = false;
				}				
			}

#pragma omp critical
			{
				percentageCompleted += percentPerCenterline;
				update = true;
			}
		}
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	// Delete the centerlines buffer since we dont need it anymore.
	std::for_each(centerlines.begin(), centerlines.end(), [](std::vector<size_t> &line) { line.clear(); });
	centerlines.clear();
	
	// Use this vector to store the indices of the new centerline points to properliy set their scalar value.
	std::vector<std::vector<size_t>> centerlinePointIndices = std::vector<std::vector<size_t>>(alignments.size());

	// Only add centerpoints for alignments which are also exported.
	for(size_t idx = 0; idx < alignments.size(); idx++) {
		auto &segment = alignments[idx];
		for(auto point : segment) {
			addPoint(CCVector3(point));
			addRGBColor(255 * (float)idx / (float)alignments.size(), 0, 255);
			centerlinePointIndices[idx].push_back(this->size() - 1);
		}
	}	

	// Add a scalar field for centerline so that we can delete them again when we do the reset.
	int idx_centerline = getScalarFieldIndexByName("Centerline");
	if(idx_centerline == -1)
		idx_centerline = addScalarField("Centerline");
	setCurrentInScalarField(idx_centerline);

	// Initialize all centerline scalar values to -1.
	for_each([&](size_t i) {
		setPointScalarValue(i, -1);
	});

	// Set the index of the centerline as the scalar value.
	for(size_t idx = 0; idx < centerlinePointIndices.size(); idx++) {
		for(auto pointIndex : centerlinePointIndices[idx])
			setPointScalarValue(pointIndex, idx);
	}

	// Update the centerline description so that we know how the centerlines were generated when we export the curvatures etc. from the measurement.
	centerlineDescription_ = desc;

	// Update the indices.
	computeIndices();

	// Return the number of selected alignments.
	return alignments.size();
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetCenterlines()
{
	centerlineDescription_ = buw::CenterlineComputationDescription();
	return resetRailwaySegmentation();
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlineCurvature(const buw::CenterlineCurvatureComputationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Tell the callback that we're done.
	if(callback)
		callback->start();		

	// Add a scalar field for centerline so that we can delete them again when we do the reset.
	int idx_centerline = getScalarFieldIndexByName("Centerline");
	if(idx_centerline == -1) {

		// Stop our callback.
		if(callback)
			callback->stop();

		BLUE_LOG(warning) << "Centerline scalar field not found. Method returning with error.";
		return -1;
	}

	ScalarType min, max;
	std::tie(min, max) = getScalarFieldMinAndMax(idx_centerline);
	size_t numAlignments = max + 1;

	setCurrentOutScalarField(idx_centerline);

	if(numAlignments > 0) {
		BLUE_LOG(trace) << "Found " << QString::number(numAlignments).toStdString() << " centerlines.";
	}
	else {
		BLUE_LOG(warning) << "No centerlines found. Method returning with error.";
		return -2;
	}

	std::vector<std::vector<CCVector3>> alignments = std::vector<std::vector<CCVector3>>(numAlignments);
	for(int i = 0; i < numAlignments; i++)
		alignments[i] = std::vector<CCVector3>();
	
	BLUE_LOG(trace) << "Start collecting centerline points.";

	for_each([&](size_t i) {
		int idx = (int)getPointScalarValue(i);
		if(idx >= 0) {
			CCVector3 &center = CCVector3(*getPoint(i));
			alignments[idx].push_back(center);
		}		
	});

	BLUE_LOG(trace) << "Finished collecting centerline points.";
	std::vector<long> indices = std::vector<long>();

	// Everything besides writing all alignments is not yet implemented
	if(desc.centerlineIndex == -1) {
		for(int i = 0; i < numAlignments; i++)
			indices.push_back(i);
		
	}
	else {
		indices.push_back(desc.centerlineIndex);
	}

	QString date = QDateTime::currentDateTime().date().toString(Qt::ISODate);
	QString time = QDateTime::currentDateTime().time().toString(Qt::ISODate).replace(":", "-");
	QDir root = QDir(QDir::currentPath());
	QDir sub = QDir(QDir::currentPath() + "/" + date);

		// Compute the bearing and write it to a file which we want to plot then.
	for(long idx : indices) {
		auto &alignment = alignments[idx];		

		// Check if our alignment has enough points.
		long numBearingsAndChainages = ((alignment.size() - desc.numPointsForPCA) / desc.curvatureStepSize) + 1;
		long numCurvatures = numBearingsAndChainages - 1;
		long numCurvaturesSmoothed = numCurvatures - desc.numPointsForMeanCurvature;
		
		if(alignment.size() > desc.numPointsForPCA && numCurvaturesSmoothed > 0) {
			
			if(!root.exists(date))
				root.mkdir(date);

			if(!sub.exists(time))
				sub.mkdir(time);
			

			std::sort(alignment.begin(), alignment.end(), [&](const CCVector3 &lhs, const CCVector3 &rhs)->bool { return mainAxis_.dot(lhs) < mainAxis_.dot(rhs); });

			BLUE_LOG(trace) << "Processing Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
			QFile file(sub.absolutePath() + "/" + time + "/" + "Alignment#" + QString::number(idx) + ".txt");
			if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return -1;

			auto filestart = file.pos();

			// Initialize number of points to use for PCA and and the NORTH direction.
			const Eigen::Matrix<double, 3, 1> NORTH(0., 1., 0.);
			const Eigen::Matrix<double, 2, 1> NORTH2D(0., 1.);

			// Initialize the container to hold our angles of the direction vectors
			std::vector<double> bearings = std::vector<double>(numBearingsAndChainages);
			std::vector<double> chainages = std::vector<double>(numBearingsAndChainages);
			std::vector<double> curvatures = std::vector<double>(numCurvatures);
			std::vector<double> curvaturesSmoothed = std::vector<double>(numCurvaturesSmoothed);

			int tid = 0;
			// Compute the bearing for all points as the angle between the principal axis of numPointsForPCA consecutive centerline points and the NORTH direction.
#pragma omp parallel private(tid) firstprivate(callback) shared(desc)
			{
				tid = omp_get_thread_num();
				long processedPoints = 0;
				long pointsPerThread = alignment.size() / omp_get_num_threads();
				long pointsPerPercent = pointsPerThread / 100;
				int percentageCompleted = 0;
				// Pull the lambda declaration into the loop for the openmp construct
				auto getPCA = [](std::vector<CCVector3> alignment, size_t start, size_t end)->Eigen::Matrix<double, 2, 1> {
					//Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX3d mat;
					mat.resize(end - start, 3);
					for(size_t i = start; i < end; i++) {
						auto pos = alignment[i];
						mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
					}

					//Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1).topRows(2);
					return vec;
				};

#pragma omp for
				for(long i = desc.numPointsForPCA / 2; i < alignment.size() - (desc.numPointsForPCA / 2); i += desc.curvatureStepSize) {
					// Get the PCA axis and compute the bearing.
					auto axis = getPCA(alignment, i - (desc.numPointsForPCA / 2), i + (desc.numPointsForPCA / 2));
					axis.normalize();
					bearings[(i - (desc.numPointsForPCA / 2)) / desc.curvatureStepSize] = (std::acos(axis.dot(NORTH2D)) * 180.0 / M_PI);
					chainages[(i - (desc.numPointsForPCA / 2)) / desc.curvatureStepSize] = mainAxis_.dot(alignment[i]);
					processedPoints += desc.curvatureStepSize;

					if(processedPoints >= pointsPerPercent) {
						percentageCompleted++;
						processedPoints = 0;

						if(tid == 0 && callback)
							callback->update(((100.0f *(float)(idx) / (float)alignments.size()) + (1.0f / (float)alignments.size()) * percentageCompleted) * ((float)alignments.size() / (float)indices.size()));
					}
				}
#pragma omp barrier

				int nJumps = 0;
				for(long i = 0; i < bearings.size() - 1; i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					bearings[i] += nJumps;
					if(std::abs(bearings[i] - (bearings[i + 1] + nJumps)) > 170)
						nJumps += 180;
				}


				// Without smoothing
#pragma omp for
				for(long i = 0; i < bearings.size() - 1; i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
					curvatures[i] = ((bearings[i + 1] - bearings[i]) / deltaChainage);
				}
#pragma omp barrier				

				int startOffset = (int)std::floor((float)desc.numPointsForMeanCurvature / 2.0f);
				if(desc.numPointsForMeanCurvature % 2 == 0)
					startOffset++;
				int endOffset = std::ceil((float)desc.numPointsForMeanCurvature / 2.0f);

#pragma omp for
				for(long i = startOffset; i < curvatures.size() - endOffset - 1; i++) {
					double curvature = 0.0;

					for(int offset = -startOffset; offset < endOffset; offset++)
						curvature += curvatures[i + offset];

					curvaturesSmoothed[i - startOffset] = curvature / (double)desc.numPointsForMeanCurvature;
				}
#pragma omp barrier

#pragma omp single
				{
					for(size_t i = 0; i < curvaturesSmoothed.size() - (endOffset - startOffset) - 1; i++) {
						QString text = QString::number(chainages[i + startOffset]).append("\t").append(QString::number(curvaturesSmoothed[i])).append("\t").append(QString::number(bearings[i + startOffset])).append("\n");
						file.write(text.toStdString().data());
					}
				}
			}



			// TODO:If the file is empty we delete it.		
			file.close();
		}
		else {
			BLUE_LOG(trace) << "Skipping Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
		}
	}

	if(root.exists(date) && sub.exists(time)) {
		QFile file(sub.absolutePath() + "/" + time + "/parameters.txt");
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return -1;
		QStringList text = {
			QString("Centerline computation"),
			QString("CenterlineDensity:" + QString::number(centerlineDescription_.centerlineDensity)),
			QString("MaxDistance:" + QString::number(centerlineDescription_.maxDistance)),
			QString("MinSegmentPoints:" + QString::number(centerlineDescription_.minSegmentPoints)),
			QString("MinSegmentLength:" + QString::number(centerlineDescription_.minSegmentLength)),
			QString("Curvature computation"),
			QString("NumPointsForPCA:" + QString::number(desc.numPointsForPCA)),
			QString("CurvatureStepSize:" + QString::number(desc.curvatureStepSize)),
			QString("NumPointsForMeanCurvature:" + QString::number(desc.numPointsForMeanCurvature)) };
		file.write(text.join("\n").toStdString().data());
		file.close();
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::segmentRailways(buw::RailwaySegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// If we have a callback, call start to init the GUI.
	if(callback)
		callback->start();

	// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if(idx_railway == -1)
		idx_railway = addScalarField("Railway");
	setCurrentInScalarField(idx_railway);

	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});

	// Create a global list of all point pairs.
	std::vector<std::pair<size_t, size_t>> rails = std::vector<std::pair<size_t, size_t>>();
#pragma omp parallel for
	for(long i = 0; i < sections_.size(); i++) {
		auto pairs = sections_[i]->computePairs();


#pragma omp critical
		rails.insert(rails.end(), pairs.begin(), pairs.end());
	}

	// Reserve space for the centerpoints points and color them blue.
	this->reserve(this->size() + rails.size());
	this->reserveTheRGBTable();
	const ColorCompType blue[3] = { 0,0,255 };

	// For each pair, insert the point in the middle as centerpoints point.
	std::vector<CCVector3> centerpoints = std::vector<CCVector3>(rails.size());
	for(auto pair : rails) {
		CCVector3 start = *(getPoint(pair.first));
		CCVector3 end = *(getPoint(pair.second));
		CCVector3 center = 0.5f * (end + start);
		centerpoints.push_back(center);
	}

	// Sort the centerpoints along the main axis.
	std::sort(centerpoints.begin(), centerpoints.end(), [&](const CCVector3 &lhs, const CCVector3 &rhs)->bool { return mainAxis_.dot(lhs) < mainAxis_.dot(rhs); });

	// Split the centerpoints into different rails and recognize different rails. Only store indices to save memory.
	std::vector<std::vector<size_t>> centerlines = std::vector<std::vector<size_t>>();
	centerlines.push_back(std::vector<size_t>());
	centerlines[0].push_back(0);
		
	auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) ->float {
		return (rhs - lhs).norm();
	};
			
	float totalPoints = centerpoints.size();
	float processedPoints = 0;
	for(size_t i = 1; i < centerpoints.size(); i++) {
		// Store the point to be checked and whether we have inserted it or whether it is ambiguous or not.
		auto point = centerpoints[i];
		bool inserted = false;
		bool ambiguous = false;

		// Initialize the pair min with index and distance
		std::pair<size_t, float> min = std::pair<size_t, float>(centerlines.size(), LONG_MAX);

		// Iterate over all centerlines.
		for(size_t ii = 0; ii < centerlines.size(); ii++) {
			auto &line = centerlines[ii];

			// Calculate the distance to the endpoint
			auto endpoint = centerpoints[line.back()];
			float distance = dist(point, endpoint);

			// If the distance is smaller than 20cm, we would add the point to this line.
			if(distance < 0.2f) {
				// If the point would also be inserted somewhere else, it is labeled as ambiguous and is dropped.
				if(inserted) {
					ambiguous = true;
					break;
				}
				// Otherwise the min distance is updated and inserted is set to true.
				else {
					inserted = true;
					if(distance < min.second)
						min = std::pair<size_t, float>(ii, distance);
				}
			}

		}

		// If the point is not ambiguous, we either insert it in the matching line or create a new one.
		if(!ambiguous) {
			if(inserted) {
				centerlines[min.first].push_back(i);
			}
			else {
				// If no matching line has been found, add a new one with this one as the starting point.				
				centerlines.push_back(std::vector<size_t>());
				centerlines.back().push_back(i);
			}
		}

		//Check if we have a centerline which is very small (does not meet the minimum requirements as specified) and remove it to save some computation time.
		if(i % 10000 == 0) {
			for(size_t ii = 0; ii < centerlines.size(); ii++) {
				auto &line = centerlines[ii];

				// Calculate the distance to the endpoint
				auto endpoint = centerpoints[line.back()];
				float distance = std::fabsf(mainAxis_.dot(point) - mainAxis_.dot(endpoint));

				if(distance > 1.0f && (line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength)) {
					centerlines.erase(centerlines.begin() + ii);
				}

			}
		}

		if(callback)
			callback->update(100.0 * ++processedPoints / totalPoints);
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();
		
	

	// Clear all lines having less then 100 points -> probably noise or something.
	auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool { return line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength; });
	centerlines.erase(end, centerlines.end());

	// Add a scalar field for centerline so that we can delete them again when we do the reset.
	int idx = getScalarFieldIndexByName("Centerline");
	if(idx == -1)
		idx = addScalarField("Centerline");
	setCurrentInScalarField(idx);

	for_each([&](size_t i) {
		setPointScalarValue(i, -1);
	});

	std::vector<std::vector<CCVector3>> alignments = std::vector<std::vector<CCVector3>>(centerlines.size());

	if(false) {
		// Iterate over all segments and combine the centers of each projection section.
		for(size_t idx = 0; idx < centerlines.size(); idx++) {
			auto &line = centerlines[idx];
			int startIndex = 0, endIndex = 0;

			for(size_t i = 0; i < line.size() - 1; i++) {
				float length = std::fabsf(mainAxis_.dot(centerpoints[line[i + 1]]) - mainAxis_.dot(centerpoints[line[startIndex]]));
				if(length >= desc.centerlinePointDistance) {
					endIndex = i + 1;
					int numPoints = (endIndex - startIndex);
					CCVector3 &center = CCVector3(0, 0, 0);
					for(; startIndex < endIndex; startIndex++) {
						center += (centerpoints[line[startIndex]] / (float)numPoints);
					}

					alignments[idx].push_back(center);

					//this->addPoint(center);
					//this->addRGBColor(255 * (float)idx /(float) centerlines.size(),0,255);
				}
			}
		}
	}

	if(true) {
		for(size_t idx = 0; idx < centerlines.size(); idx++) {
			auto &line = centerlines[idx];
			for(size_t i = 0; i < line.size() - 1; i++) {
				CCVector3 &center = centerpoints[line[i]];
				alignments[idx].push_back(center);
			}
		}
	}

	// Clear all alignments having less then points required for PCA to make visualization better.
	auto endAlignments = std::remove_if(alignments.begin(), alignments.end(), [&](std::vector<CCVector3> &line) -> bool { return line.size() <= desc.numPointsForPCA; });
	alignments.erase(endAlignments, alignments.end());

	// Only add centerpoints for alignments which are also exported.
	for(size_t idx = 0; idx < alignments.size(); idx++) {
		auto &segment = alignments[idx];
		for(auto point : segment) {
			this->addPoint(point);
			this->addRGBColor(255 * (float)idx / (float)alignments.size(), 0, 255);
			this->setPointScalarValue(this->size() - 1, idx);
		}
	}

	computeIndices();

	// Tell the callback that we're done.
	if(callback)
		callback->start();

	if(true) {
		// Compute the bearing and write it to a file which we want to plot then.
		for(long idx = 0; idx < alignments.size(); idx++) {
			auto &alignment = alignments[idx];
			BLUE_LOG(trace) << "Processing Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
			QFile file("Alignment#" + QString::number(idx) + ".txt");
			if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return -1;

			auto filestart = file.pos();


			// Implementation with offset by Stefan Markic.
#ifdef MARKIC
			if(false) {
				const size_t START = 100;
				const CCVector3 NORTH(0., 1., 0.);
				const int halbe = START / 2;

				if(alignment.size() > START) {
					std::vector<float> angles = std::vector<float>();

					for(int i = 0; i < halbe; i++) angles.push_back(0);

					for(size_t i = halbe; i < alignment.size() - halbe; i++) {

						CCVector3 axis = getPCA(alignment, i - halbe, i + halbe);
						axis.normalize();
						angles.push_back(axis.dot(NORTH) * 180.0 / M_PI);
					}

					for(int i = halbe; i < START; i++) angles.push_back(0);

					for(size_t i = halbe; i < angles.size() - halbe; i++) {
						float curvature = (angles[i + 1] - angles[i]) / std::fabsf(mainAxis_.dot(alignment[i + 1]) - mainAxis_.dot(alignment[i]));
						QString text = QString::number(i).append("\t").append(QString::number(curvature)).append("\t").append(QString::number(angles[i])).append("\n");
						file.write(text.toStdString().data());
					}
				}
			}
#endif

			// Implementation without offset but with other stuff by Helge Hecht.
			if(true) {

				// Initialize number of points to use for PCA and and the NORTH direction.
				const Eigen::Matrix<double, 3, 1> NORTH(0., 1., 0.);

				// Check if our alignment has enough points.
				if(alignment.size() > desc.numPointsForPCA) {

					// Initialize the container to hold our angles of the direction vectors
					std::vector<double> bearings = std::vector<double>((alignment.size() - desc.numPointsForPCA) / desc.curvatureStepSize);
					std::vector<double> chainages = std::vector<double>((alignment.size() - desc.numPointsForPCA) / desc.curvatureStepSize);
					std::vector<double> curvatures = std::vector<double>(bearings.size() - 1);
					std::vector<double> curvaturesSmoothed = std::vector<double>(curvatures.size() - desc.numPointsForMeanCurvature);

					int tid = 0;
					// Compute the bearing for all points as the angle between the principal axis of numPointsForPCA consecutive centerline points and the NORTH direction.
#pragma omp parallel private(tid) firstprivate(callback)
					{
						tid = omp_get_thread_num();
						long processedPoints = 0;
						long pointsPerThread = alignment.size() / omp_get_num_threads();
						long pointsPerPercent = pointsPerThread / 100;
						int percentageCompleted = 0;
						// Pull the lambda declaration into the loop for the openmp construct
						auto getPCA = [](std::vector<CCVector3> alignment, size_t start, size_t end)->Eigen::Matrix<double, 3, 1> {
							//Matrix which is capable of holding all points for PCA.
							Eigen::MatrixX3d mat;
							mat.resize(end - start, 3);
							for(size_t i = start; i < end; i++) {
								auto pos = alignment[i];
								mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
							}

							//Do PCA to find the largest eigenvector -> main axis.
							Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
							Eigen::MatrixXd cov = centered.adjoint() * centered;
							Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
							Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1);
							return vec;
						};

#pragma omp for
						for(long i = 0; i < alignment.size() - desc.numPointsForPCA; i+= desc.curvatureStepSize) {
							// Get the PCA axis and compute the bearing.
							auto axis = getPCA(alignment, i, i + desc.numPointsForPCA);
							axis.normalize();
							bearings[i / desc.curvatureStepSize] = (axis.dot(NORTH) * 180.0 / M_PI);
							chainages[i / desc.curvatureStepSize] = mainAxis_.dot(alignment[i]);
							processedPoints+= desc.curvatureStepSize;
							
							if(processedPoints >= pointsPerPercent) {
								percentageCompleted++;
								processedPoints = 0;

								if(tid == 0 && callback)
									callback->update((100.0f *(float)(idx) / (float)alignments.size()) + (1.0f / (float)alignments.size()) * percentageCompleted);
							}							
						}
					}					

					// Without smoothing
#pragma omp for
					for(long i = 0; i < bearings.size() - 1; i++) {
						// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
						double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
						curvatures[i] = ((bearings[i + 1] - bearings[i]) / deltaChainage);						
					}

					int startOffset = std::floor(desc.numPointsForMeanCurvature / 2);
					if(desc.numPointsForMeanCurvature % 2 == 0)
						startOffset++;
					int endOffset = std::ceil(desc.numPointsForMeanCurvature / 2);

#pragma omp for
					for(long i = startOffset; i < curvatures.size() - endOffset; i++) {
						double curvature = 0.0;

						for(int offset = -startOffset; offset < endOffset; offset++)
							curvature += curvatures[i + offset];

						curvaturesSmoothed[i - startOffset] = curvature / (double)desc.numPointsForMeanCurvature;
					}

#pragma omp single
					{
						for(size_t i = 0; i < curvaturesSmoothed.size(); i++) {
							QString text = QString::number(chainages[i + startOffset]).append("\t").append(QString::number(curvaturesSmoothed[i])).append("\t").append(QString::number(bearings[i + startOffset])).append("\n");
							file.write(text.toStdString().data());
						}
					}
				}
			}

			// TODO:If the file is empty we delete it.		
			file.close();
		}
	}

	// Tell the callback that we're done.
	if(callback)
		callback->stop();

	return alignments.size();
}


int OpenInfraPlatform::Infrastructure::PointCloud::resetRailwaySegmentation()
{
	// Reset the railway points color to white.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if(idx_railway == -1)
		return -1;

	setCurrentOutScalarField(idx_railway);
	const ColorCompType white[3] = { 255,255,255 };
	for_each([&](size_t i) {
		if(getPointScalarValue(i) != 0)
			setPointColor(i, white);
	});

	int idx_centerline = getScalarFieldIndexByName("Centerline");

	// Abort if we have no filtered points.
	if(idx_centerline == -1)
		return -1;


	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_centerline);
	float epsilon = -1 + 0.0001f;
	ccPointCloud* original = filterPointsByScalarValue(-1, epsilon);

	original->deleteScalarField(original->getScalarFieldIndexByName("Railway"));
	original->deleteScalarField(original->getScalarFieldIndexByName("Centerline"));

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
	append(original, 0);

	init();
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
	BLUE_LOG(trace) << "Start computing main axis.";
	// Set the main axis as the eigenvector with the largest eigenvalue.
	mainAxis_ = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());
	BLUE_LOG(trace) << "Finished computing main axis.";
}
