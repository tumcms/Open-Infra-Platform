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

#include <CloudSamplingTools.h>
#include <FileIOFilter.h>
#include <GenericProgressCallback.h>
#include <ScalarFieldTools.h>
#include <ccScalarField.h>
#include <AutoSegmentationTools.h>

#include <liblas/liblas.hpp>

#include <algorithm>

#include <QDateTime>
#include <QDir>

buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::Infrastructure::PointCloud::FromFile(const char *filename) {
	buw::ReferenceCounted<buw::PointCloud> pointCloud = buw::makeReferenceCounted<buw::PointCloud>(QString(filename));

	// Initialize the filters for file IO.
	if (FileIOFilter::GetFilters().size() == 0)
		FileIOFilter::InitInternalFilters();

	// Get file extension and try to find the best filter for it.
	QString extension = QString(filename).split(".").last().toUpper();
	auto filter = FileIOFilter::FindBestFilterForExtension(extension);

	BLUE_LOG(trace) << "Importing " << extension.toStdString() << " point cloud " << filename << ".";
	if (filter) {
		CC_FILE_ERROR err;
		// Load the point cloud from file and store it temporarily.
		std::shared_ptr<ccHObject> ccTempObject =
		  std::shared_ptr<ccHObject>(FileIOFilter::LoadFromFile(QString(filename), FileIOFilter::LoadParameters(), FileIOFilter::FindBestFilterForExtension("BIN"), err));
		if (err == CC_FILE_ERROR::CC_FERR_NO_ERROR) {
			BLUE_LOG(trace) << "Number of child objects:" << QString::number(ccTempObject->getChildrenNumber()).toStdString() << ".";
			for (size_t i = 0; i < ccTempObject->getChildrenNumber(); i++) {
				auto child = ccTempObject->getChild(i);
				ccPointCloud *temp = ccHObjectCaster::ToPointCloud(child);
				BLUE_LOG(trace) << "Processing child #" << QString::number(i).toStdString() << ". Name:" << child->getName().toStdString();

				if (temp) {
					BLUE_LOG(trace) << "Size:" << QString::number(temp->size()).toStdString() << ".";
					size_t sizeBefore = pointCloud->size();

					pointCloud->reserve(sizeBefore + temp->size());
					for (size_t ii = 0; ii < temp->size(); ii++) {
						pointCloud->addPoint(CCVector3(*(temp->getPoint(ii))));
					}

					// pointCloud->append(temp, sizeBefore);

					if (sizeBefore == pointCloud->size())
						BLUE_LOG(warning) << "No points added. Size:" << QString::number(sizeBefore).toStdString();
				} else {
					if (child)
						BLUE_LOG(warning) << "Cast to point cloud failed for child object " << child->getName().toStdString() << ".";
					else
						BLUE_LOG(error) << "Something went terribly wrong...";
				}
			}
		}

		BLUE_LOG(trace) << "Finished processing child objects. Total size:" << QString::number(pointCloud->size()).toStdString() << ".";

		// Delete our temporary parrent object.
		ccTempObject = nullptr;
	} else {
		if (extension == "LAS") {
			// see http://www.liblas.org/tutorial/cpp.html
			std::ifstream ifs;

			ifs.open(filename, std::ios::in | std::ios::binary);

			liblas::ReaderFactory f;
			liblas::Reader reader = f.CreateWithStream(ifs);

			liblas::Header const &header = reader.GetHeader();

			BLUE_LOG(info) << "Compressed: " << ((header.Compressed() == true) ? "true" : "false");
			BLUE_LOG(info) << "Signature: " << header.GetFileSignature();
			BLUE_LOG(info) << "Points count: " << header.GetPointRecordsCount();

			buw::Vector3d minv(0, 0, 0);
			buw::Vector3d maxv(0, 0, 0);

			pointCloud->clear();

			// Reserve the points.
			pointCloud->reserve(header.GetPointRecordsCount());
			pointCloud->reserveTheRGBTable();

			bool first = true;
			CCVector3d scale = CCVector3d(header.GetScaleX(), header.GetScaleY(), header.GetScaleZ());
			for (size_t i = 0; i < header.GetPointRecordsCount(); i++) {
				if (reader.ReadNextPoint()) {
					liblas::Point const &p = reader.GetPoint();
					float colorRange = std::numeric_limits<liblas::Color::value_type>::max();

					int32_t posLiblas[3] = {p.GetRawX(), p.GetRawY(), p.GetRawZ()};
					liblas::Color colLiblas = p.GetColor();
					const ccColor::Rgb *color =
					  new ccColor::Rgb(ccColor::FromRgbf(ccColor::Rgbf(colLiblas.GetRed() / colorRange, colLiblas.GetGreen() / colorRange, colLiblas.GetBlue() / colorRange)).rgb);
					pointCloud->addPoint(CCVector3(posLiblas[0] * scale.x, posLiblas[1] * scale.y, posLiblas[2] * scale.z));
					pointCloud->addRGBColor(color->rgb);
				}
			}
		} else {
			// TODO
		}
	}

	BLUE_LOG(trace) << "Finished importing " << filename << ".";

	pointCloud->setName(filename);
	pointCloud->init();

	return pointCloud;
}

OpenInfraPlatform::Infrastructure::PointCloud::~PointCloud() {
	if (!remainingIndices_.empty())
		remainingIndices_.clear();
	if (!segmentedIndices_.empty())
		segmentedIndices_.clear();
	if (!filteredIndices_.empty())
		filteredIndices_.clear();

	if (!sections_.empty())
		sections_.clear();

	if (!grid_.empty())
		grid_.clear();

	if (octree_)
		octree_ = nullptr;
}

int OpenInfraPlatform::Infrastructure::PointCloud::add(const buw::ReferenceCounted<ccPointCloud>& other, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback, ColorCompType* color)
{
	if(callback)
		callback->start();

	ColorCompType white[3] = { 255,255,255 };
	if(!color)
		color = white;

	bool result = true;
	result &= this->reserve(this->size() + other->size());

	// If we have an error, return -1.
	if(!result)
		return -1;

	result &= this->reserveTheRGBTable();

	// If we have an error, return -2.
	if(!result)
		return -2;

	std::vector<std::pair<int, int>> commonScalarFields = std::vector<std::pair<int, int>>();
	uint numScalarFields = this->getNumberOfScalarFields();
	for(size_t idxThis = 0; idxThis < numScalarFields; idxThis++) {
		std::string name = getScalarFieldName(idxThis);
		int idxOther = other->getScalarFieldIndexByName(name.data());
		if(idxOther != -1)
			commonScalarFields.push_back(std::pair<int, int>(idxThis, idxOther));
	}



	long processedPoints = 0;
	long numPoints = other->size();
	long pointsPerPercent = std::max(1l, numPoints / 100);
	short percentageCompleted = 0;
	size_t startIndex = this->size();
	ColorCompType red[3] = { 255,0,0 };
	for(long i = 0; i < numPoints; i++) {
		this->addPoint(*other->getPoint(i));
		this->addRGBColor(other->getPointColor(i));		
		this->setPointColor(startIndex + i, color);
		processedPoints++;
		if(processedPoints % pointsPerPercent == 0) {
			percentageCompleted++;
			if(callback)
				callback->update(percentageCompleted);
		}
	}

	this->resize(startIndex + processedPoints);

	for(auto indices : commonScalarFields) {
		this->setCurrentInScalarField(indices.first);
		other->setCurrentOutScalarField(indices.second);

		for(long i = 0; i < processedPoints; i++) {
			ScalarType value = other->getPointScalarValue(i);
			this->setPointScalarValue(startIndex + i, value);
		}
	}

	if(callback)
		callback->stop();

	return 0;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {

	if(callback)
		callback->start();

	int idx_chainage = getScalarFieldIndexByName("Chainage");

	// Try new approach
	sections_.clear();
	setCurrentOutScalarField(idx_chainage);
	ScalarType min, max;
	getCurrentOutScalarField()->computeMinAndMax();
	std::tie(min, max) = getScalarFieldMinAndMax(idx_chainage);
	size_t numSections = (std::floorf(length * max) - std::floorf(length * min)) + 1;
	int base = std::floorf(length * min);

	sections_ = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>(numSections);

	long processedPoints = 0;
	long numPoints = this->size();
	long pointsPerPercent = numPoints / 100;
	int percentageCompleted = 0;

	for_each([&](size_t i) {
		size_t sectionId = std::floorf(length * getPointScalarValue(i)) - base;

		if(!sections_[sectionId]) {
			sections_[sectionId] = buw::makeReferenceCounted<buw::PointCloudSection>(static_cast<GenericIndexedCloudPersist *>(this));
			sections_[sectionId]->setLength(length);
		}

		sections_[sectionId]->addPointIndex(i);

		processedPoints++;

		if(processedPoints == pointsPerPercent) {
			percentageCompleted++;
			processedPoints = 0;
			if(callback)
				callback->update(percentageCompleted);
		}
	});

	auto end = std::remove_if(sections_.begin(), sections_.end(), [](const buw::ReferenceCounted<buw::PointCloudSection> &section) -> bool { return section == nullptr; });
	sections_.erase(end, sections_.end());

#pragma omp parallel for
	for(long i = 0; i < sections_.size(); i++) {
		auto &section = sections_[i];
		auto median = section->computeMedianCenter();

		section->for_each([&](size_t i) {
			auto height = section->getPoint(i)->z;
			if(std::abs(median.z - height) > 0.25f) {
				section->removePointGlobalIndex(i);
			}
		});
	}

	// Color all points which are not in a section black.
	const ColorCompType black[3] = { 0, 0, 0 };
	const ColorCompType white[3] = { 255, 255, 255 };

	for_each([&](size_t i) { setPointColor(i, black); });

#pragma omp parallel for
	for(long i = 0; i < sections_.size(); i++) {
		for(long ii = 0; ii < sections_[i]->size(); ii++) {
			setPointColor(sections_[i]->getPointGlobalIndex(ii), white);
		}
	}

	if(callback)
		callback->stop();
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeChainage(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	if (callback)
		callback->start();

	// Init Chainage Scalar Field.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	if (idx_chainage == -1)
		idx_chainage = addScalarField("Chainage");

	setCurrentInScalarField(idx_chainage);

	sections_ = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>();

	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(200);

	// If the level is to low, we can't get the indices etc. so we manually increase it.
	while (octree_->getCellSize(level) == 0)
		level++;

	BLUE_LOG(trace) << "Octree Level:" << (int)level;
	BLUE_LOG(trace) << "Octree Cell Size:" << octree_->getCellSize(level);

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	CCLib::DgmOctree::cellsContainer dgmOctreeCells;
	bool success = octree_->getCellCodesAndIndexes(level, dgmOctreeCells, true);

	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;

	std::map<CCLib::DgmOctree::CellCode, std::tuple<CCVector3, float, CCVector2, float>> octreeCellMap = std::map<CCLib::DgmOctree::CellCode, std::tuple<CCVector3, float, CCVector2, float>>();

#pragma omp parallel private(tid) firstprivate(callback) shared(level, dgmOctreeCells, numCells, err, octreeCellMap)
	{
		// Initialize our variables for callback updates.
		tid = omp_get_thread_num();
		auto octree = buw::Octree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;


		// Iterate over all cells to call our nearest neighbour search on consecutive points in a cell for performance reasons.
#pragma omp for schedule(dynamic)
		for (long idx = 0; idx < dgmOctreeCells.size(); idx++) {
			auto cell = dgmOctreeCells[idx].theIndex;
			auto code = dgmOctreeCells[idx].theCode;

			// Create and initialize the nearest neighbour search struct as far as possible.
			CCLib::DgmOctree::NearestNeighboursSphericalSearchStruct nss;
			nss.level = level;
			nss.maxSearchSquareDistd = std::pow(100, 2);
			nss.alreadyVisitedNeighbourhoodSize = 0;
			nss.minNumberOfNeighbors = 0;

			// Get the points in the cell specified by the index and store them in points. Compute the cell position and center.
			std::shared_ptr<CCLib::ReferenceCloud> points = std::make_shared<CCLib::ReferenceCloud>(this);
			success = octree.getPointsInCellByCellIndex(points.get(), cell, level);
			octree.getCellPos(code, level, nss.cellPos, true);
			octree.computeCellCenter(nss.cellPos, level, nss.cellCenter);

			if (success) {
				nss.queryPoint = *CCLib::Neighbourhood(points.get()).getGravityCenter();
				int numPoints = octree.findNeighborsInASphereStartingFromCell(nss, 100, false);

				auto getPCA = [&]() -> CCVector2 {
					// Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX2d mat;
					mat.resize(numPoints, 2);
					for(size_t i = 0; i < numPoints; i++) {
						auto pos = *nss.pointsInNeighbourhood[i].point;
						mat.row(i) = Eigen::Vector2d(pos.x, pos.y);
					}

					// Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1).normalized();

					return CCVector2(vec.x(), vec.y());
				};

				auto axis = getPCA();

				//TODO fill in the cell map.
				std::tuple<CCVector3, float, CCVector2, float> cellCenterWithProjectionLengthAlongAxis = std::tuple<CCVector3, float, CCVector2, float>(nss.queryPoint, axis.dot(CCVector2(nss.queryPoint.x, nss.queryPoint.y)), axis, points->size());
#pragma omp critical
				octreeCellMap.insert(std::pair<CCLib::DgmOctree::CellCode, std::tuple<CCVector3, float, CCVector2, float>>(code, cellCenterWithProjectionLengthAlongAxis));

				//std::vector<std::pair<size_t, double>> indexedProjectionLength;

				//for (size_t i = 0; i < points->size(); i++) {
				//	auto point3d = *points->getPoint(i);
				//	CCVector2 point2d = CCVector2(point3d.x, point3d.y);
				//	ScalarType value = axis.dot(point2d);
				//	size_t index = points->getPointGlobalIndex(i);
				//	setPointScalarValue(index, value);
				//	//indexedProjectionLength.push_back(std::pair<size_t, double>(index, value));
				//}

				//float length = 10.0f;
				// std::sort(indexedProjectionLength.begin(), indexedProjectionLength.end(),
				//          [](const std::pair<size_t, double> &lhs, const std::pair<size_t, double> &rhs) -> bool { return lhs.second < rhs.second; });
				//
				// ScalarType min = indexedProjectionLength.front().second, max = indexedProjectionLength.back().second;
				// size_t numSections = (std::floorf(length * max) - std::floorf(length * min)) + 1;
				// auto sections = std::vector<buw::ReferenceCounted<buw::PointCloudSection>>(numSections);
				// int base = std::floorf(length * min);
				//
				// for (auto it : indexedProjectionLength) {
				//	size_t sectionId = std::floorf(length * it.second) - base;
				//
				//	if (!sections[sectionId]) {
				//		sections[sectionId] = buw::makeReferenceCounted<buw::PointCloudSection>(static_cast<GenericIndexedCloudPersist *>(this));
				//		sections[sectionId]->setLength(length);
				//		sections[sectionId]->cellCode_ = code;
				//	}
				//
				//	sections[sectionId]->addPointIndex(it.first);
				//}
				//
				// auto end =
				//  std::remove_if(sections.begin(), sections.end(), [](const buw::ReferenceCounted<buw::PointCloudSection> &section) -> bool { return section == nullptr; });
				// std::for_each(sections.begin(), end, [](buw::ReferenceCounted<buw::PointCloudSection> &section) { section->resize(section->size()); });
				//
				//#pragma omp critical
				//{ sections_.insert(sections_.end(), sections.begin(), end); }
				
				// Update our callback.
				 processedCells++;
				 if (processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if (tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			} else {
				// Stop the callback if we abort our function.
				if (tid == 0 && callback)
					callback->stop();
				//#pragma omp critical
				err = -2;
			}
		}
	}

	if (callback)
		callback->stop();

	if(callback)
		callback->start();

	long processedPoints = 0;
	long pointsPerPercent = this->size() / 100;
	int percentageCompleted = 0;

	// Interpolate the chainages.
	for(long i = 0; i < this->size(); i++) {
		// Get the cell pos and code which contain the point.
		const CCVector3* point = getPoint(i);
		Tuple3i cellPos;
		octree_->getTheCellPosWhichIncludesThePoint(point, cellPos, level);
		auto code = octree_->getTruncatedCellCode(cellPos, level);

		// Get the triple of center, projectionlength and axis.
		CCVector3 cellCenter;
		float projectionLength;
		CCVector2 axis;
		float density;
		std::tie<CCVector3, float, CCVector2, float>(cellCenter, projectionLength, axis, density) = octreeCellMap[code];

		// Get all neigthbouring cells.
		std::vector<Tuple3i> neighbouringCells = octree_->getNeighborCellPositionsAround(cellPos, 1, level);
		auto end = std::remove_if(neighbouringCells.begin(), neighbouringCells.end(), [&](Tuple3i cell) {
			return cell.x == cellPos.x && cell.z != cellPos.z && cell.y == cellPos.y;
		});

		neighbouringCells.erase(end, neighbouringCells.end());

		double meanDensity = octree_->computeMeanOctreeDensity(level);

		// Interate over the neighbours to find the code of the closest center.
		std::pair<float, CCLib::DgmOctree::CellCode> minDistCode = std::pair<float, CCLib::DgmOctree::CellCode>(LONG_MAX, code);
		for(auto cell : neighbouringCells) {
			auto neighbourCode = octree_->getTruncatedCellCode(cell, level);			
			auto cellDesc = octreeCellMap[neighbourCode];
			if(std::get<3>(cellDesc) >= 0.2 * meanDensity) {
				float distance = (*point - std::get<0>(cellDesc)).norm();
				if(distance < minDistCode.first) {
					minDistCode.first = distance;
					minDistCode.second = neighbourCode;
				}
			}
		}
		// Get the triple of center, projectionLength and axis from the map.
		std::tuple<CCVector3, float, CCVector2, float> nearestCell = octreeCellMap[minDistCode.second];

		// Compute center to point and center to neighbour to interpolate the chainage value.
		CCVector3 centerToPoint = (*point - cellCenter);
		
		CCVector3 centerToNeighbour = std::get<0>(nearestCell) - cellCenter;

		float scalarProjection = centerToPoint.dot(centerToNeighbour/centerToNeighbour.norm());
		float interpolation = scalarProjection / centerToNeighbour.norm();

		CCVector2 point2D = CCVector2(point->x, point->y);
		setPointScalarValue(i, interpolation * std::get<2>(nearestCell).dot(point2D) + (1.0f - interpolation) * axis.dot(point2D));

		// Update the callback.
		processedPoints++;
		if(processedPoints == pointsPerPercent) {
			percentageCompleted++;
			processedPoints = 0;
			if(callback)
				callback->update(percentageCompleted);
		}
	}

	if(callback)
		callback->stop();

	//Smooth chainage scalar field.
	if(callback)
		callback->start();
	
	setCurrentOutScalarField(idx_chainage);
	CCLib::ScalarFieldTools::applyScalarFieldGaussianFilter(2, this, -1, callback.get(), octree_.get());
	
	if(callback)
		callback->stop();
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeChainage2(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(callback)
		callback->start();

	computeGrid(1);
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(100);
	std::map<std::pair<int, int>, CCVector2> axes;
	int tid = 0;

#pragma omp parallel private(tid) shared(level,axes)
	{
		tid = omp_get_thread_num();
		auto octree = buw::Octree(*octree_);
#pragma omp for
		for(int i = 0; i < grid_.size(); i++) {
			auto &cell = grid_.begin();
			advance(cell, i);
			if(cell->second.size() > 0) {
				CCVector3 center = CCVector3(0, 0, 0);
				for(auto idx : cell->second) {
					center += (*getPoint(idx) / (float)cell->second.size());
				}
				std::vector<CCLib::DgmOctree::PointDescriptor> neighbours;
				int numPoints = octree.getPointsInSphericalNeighbourhood(center, 100, neighbours, level);

				auto getPCA = [&]() -> CCVector2 {
					// Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX2d mat;
					mat.resize(numPoints, 2);
					for(size_t i = 0; i < numPoints; i++) {
						auto pos = *neighbours[i].point;
						mat.row(i) = Eigen::Vector2d(pos.x, pos.y);
					}

					// Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1).normalized();

					return CCVector2(vec.x(), vec.y());
				};

				auto axis = getPCA();
#pragma omp critical
				axes.insert(std::pair<std::pair<int, int>, CCVector2>(cell->first, axis));
			}
		}
	}

	// Init Chainage Scalar Field.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	if(idx_chainage == -1)
		idx_chainage = addScalarField("Chainage");

	setCurrentInScalarField(idx_chainage);

	for(auto cell : grid_) {
		for(auto idx : cell.second) {
			CCVector3 point3D = *getPoint(idx);
			setPointScalarValue(idx, axes[cell.first].dot(CCVector2(point3D.x, point3D.y)));
		}
	}

	setCurrentOutScalarField(idx_chainage);
	CCLib::ScalarFieldTools::applyScalarFieldGaussianFilter(2, this, -1, callback.get(), octree_.get());

	if(callback)
		callback->stop();
}

std::vector<std::pair<CCVector3, ScalarType>> OpenInfraPlatform::Infrastructure::PointCloud::getAllPointsAndScalarFieldValue(int index)
{
	setCurrentOutScalarField(index);
	std::vector<std::pair<CCVector3, ScalarType>> pointsAndScalarValues;
	for_each([&](size_t i) {
		pointsAndScalarValues.push_back(std::pair<CCVector3, ScalarType>(CCVector3(*getPoint(i)), getPointScalarValue(i)));
	});

	return pointsAndScalarValues;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeGrid(int size) {
	grid_.clear();
	grid_ = std::map<std::pair<int, int>, std::vector<uint32_t>>();
	for_each([&](size_t i) {
		auto pos = getPoint(i);
		std::pair<int, int> key = std::pair<int, int>((int)(pos->x / size), (int)(pos->y / size));
		grid_[key].push_back(i);
	});
}

void OpenInfraPlatform::Infrastructure::PointCloud::alignOnMainAxis() {
	auto orientation = getEigenvectors<3>();
	bool isOrthgonal = true;
	for (int i = 0; i < 2; i++) {
		for (int ii = i + 1; ii < 3; ii++) {
			double epsilon = 0.000001;
			double error = std::abs(orientation.col(i).dot(orientation.col(ii)));
			if (error > epsilon)
				isOrthgonal = false;
		}
	}

	if (!isOrthgonal) {
		BLUE_LOG(warning) << "Aborting. Eigenvectors are not orthogonal!";
		return;
	}

	auto roll = std::acos(Eigen::Vector3d::UnitY().dot(orientation.col(1)));
	auto yaw = std::acos(Eigen::Vector3d::UnitZ().dot(orientation.col(0)));
	auto pitch = std::acos(Eigen::Vector3d::UnitX().dot(orientation.col(2)));

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
	Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitZ());

	Eigen::Quaternion<double> q = Eigen::Quaternion<double>(rollAngle);
	applyRigidTransformation(ccGLMatrix::FromQuaternion((std::vector<double>({q.x(), q.y(), q.z(), q.w()})).data()));
}

int OpenInfraPlatform::Infrastructure::PointCloud::flagDuplicatePoints(const double minDistance, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// Get octree or build it if not yet built.
	if (!octree_) {
		octree_ = buw::makeReferenceCounted<buw::Octree> (this);
		octree_->build();
	}

	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName("Duplicate");
	if (idx == -1)
		idx = addScalarField("Duplicate");

	// Set it as input scalar field to write explicitly to it - not sure if this is really necessary..
	// Set it to be the current output scalar field to avoid overriding another one since flagDuplicatePoints uses this field.
	setCurrentInScalarField(idx);
	setCurrentOutScalarField(idx);

	return CCLib::GeometricalAnalysisTools::flagDuplicatePoints(this, minDistance, callback.get(), octree_.get());
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyLocalDensityFilter(LocalDensityFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	int err = 0;

	// Compute the density, either for the volume or the sections.
	if (desc.dim == ePointCloudFilterDimension::Volume3D) {
		err = computeLocalDensity((CCLib::GeometricalAnalysisTools::Density)desc.density, desc.kernelRadius, callback);
	} else {
		// Start the callback and set the progress as percentage of sections processed.
		callback->start();
		for (size_t i = 0; i < sections_.size(); i++) {
			// We don't save the error code since it sometimes fails with sparse sections.
			sections_[i]->computeLocalDensity(desc.density, desc.kernelRadius, nullptr);
			callback->update(100.0 * ((double)i / (double)sections_.size()));
		}
		callback->stop();
	}

	// If everything worked - at least for 3D volume.
	if (err == 0) {
		// Get our scalar field. If we cant find our scalar field, something went wrong and we abort and return -1.
		int idx = getScalarFieldIndexByName("Density");
		if (idx == -1) {
			err = idx;
		} else {
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

int OpenInfraPlatform::Infrastructure::PointCloud::applyDuplicateFilter(DuplicateFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	int err = 0;

	// Call flagDuplicatePoints on this or on all sections.
	if (desc.dim == buw::ePointCloudFilterDimension::Volume3D) {
		err = flagDuplicatePoints(desc.minDistance, callback);

		// Manually stop the callback if one has been passed.
		if (callback)
			callback->stop();
	} else {
		// Start the callback and set the progress as percentage of sections processed.
		callback->start();
		for (size_t i = 0; i < sections_.size(); i++) {
			err = sections_[i]->flagDuplicatePoints(desc.minDistance);
			callback->update(100.0 * ((double)i / (double)sections_.size()));
		}
		callback->stop();
	}

	// Update the indices about which points are filtered or not.
	computeIndices();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPositionFilter(const buw::PositionFilterDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	int err = 0;

	if (callback)
		callback->start();

	if (desc.dimension >= 0 && desc.dimension < 3) {
		int idx = -1;
		switch (desc.dimension) {
		case 0: idx = addScalarField("Coord. X"); break;
		case 1: idx = addScalarField("Coord. Y"); break;
		case 2: idx = addScalarField("Coord. Z"); break;
		default: err = -1; break;
		}

		if (idx != -1) {
			setCurrentScalarField(idx);
		} else {
			BLUE_LOG(warning) << "No scalar field found.";
			err = -3;
		}
		for_each([&](size_t i) {
			ScalarType value = (*(getPoint(i)))[desc.dimension];
			if (value < desc.minValue || value > desc.maxValue)
				setPointScalarValue(i, 1.0f);
			else
				setPointScalarValue(i, 0.0f);

			if (callback)
				callback->update(100.0f * ((float)i / (float)size()));
		});

		computeIndices();
	} else {
		BLUE_LOG(warning) << "Invalid dimension number " << QString::number(desc.dimension).toStdString() << " specified. Choose X=0, Y=1 or Z=2.";
		err = -1;
	}

	if (callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::filterRelativeHeightWithGrid(const float lowerBound, const float upperBound, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(callback)
		callback->start();

	int idx_coordz = getScalarFieldIndexByName("Coord. Z");
	if(idx_coordz == -1)
		idx_coordz = addScalarField("Coord. Z");

	setCurrentInScalarField(idx_coordz);

	int processedCells = 0;
	int totalCells = grid_.size();
	int cellsPerPercent = totalCells / 100;
	int percentageCompleted = 0;

	for(auto &cell : grid_) {
		if(cell.second.size() > 0) {
			std::sort(cell.second.begin(), cell.second.end(), [&](const size_t &lhs, const size_t &rhs)->bool {
				return getPoint(lhs)->z < getPoint(rhs)->z;
			});

			auto center = getPoint(cell.second[cell.second.size() / 2]);
			std::for_each(cell.second.begin(), cell.second.end(), [&](const size_t &i) {
				auto point = getPoint(i);
				if(point->z < (center->z - lowerBound) || point->z >(center->z + upperBound))
					setPointScalarValue(i, 1);
				else
					setPointScalarValue(i, 0);
			});
		}

		processedCells++;
		if(processedCells == cellsPerPercent) {
			percentageCompleted++;
			processedCells = 0;

			if(callback)
				callback->update(percentageCompleted);
		}
	}

	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetPositionFilter() {
	deleteScalarField(getScalarFieldIndexByName("Coord. X"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Y"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Z"));

	computeIndices();
	return 0;
}

void OpenInfraPlatform::Infrastructure::PointCloud::resetScalarField(const char *name) {
	// Get the specified scalar field.
	int idx = getScalarFieldIndexByName(name);
	if (idx == -1)
		idx = addScalarField(name);

	// Set all values in the scalar field to 0.
	setCurrentInScalarField(idx);
	for_each([&](size_t i) { setPointScalarValue(i, 0); });

	// Delete the scalar field.
	deleteScalarField(idx);

	// Recompute our indices.
	computeIndices();
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric,
                                                                       ScalarType kernelRadius,
                                                                       buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	if (!isScalarFieldEnabled())
		if (enableScalarField() != true)
			return -1;

	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName("Density");
	if (idx == -1)
		idx = addScalarField("Density");

	// Set it as input scalar field to write explicitly to it - not sure if this is really necessary..
	// Set it to be the current output scalar field to avoid overriding another one since computeLocalDensity uses this field.
	setCurrentInScalarField(idx);
	// setCurrentOutScalarField(idx);

	// Compute the local density and retirn the error code.
	return CCLib::GeometricalAnalysisTools::computeLocalDensity(this, metric, kernelRadius, callback ? callback.get() : nullptr, octree_ ? octree_.get() : nullptr);
}

void OpenInfraPlatform::Infrastructure::PointCloud::init() {
	BLUE_LOG(trace) << "Start initializing point cloud.";

	// If we have no colors, we add white as color to all points.
	if (rgbColors() == nullptr) {
		BLUE_LOG(warning) << "No colors found. Adding color white to each point.";
		if (reserveTheRGBTable()) {
			for_each([&](size_t i) { addRGBColor(255, 255, 255); });
			BLUE_LOG(trace) << "Successfully added colors.";
		} else {
			BLUE_LOG(warning) << "Reserving the color table failed.";
		}
	}

	// Initialize our point cloud for usage - compute main axis, octree and sections.
	remainingIndices_ = std::vector<uint32_t>(this->size());
	for (uint32_t i = 0; i < this->size(); i++) {
		remainingIndices_[(uint32_t)i] = i;
	}
	filteredIndices_ = std::vector<uint32_t>(0);
	segmentedIndices_ = std::vector<uint32_t>(0);

	grid_ = std::map<std::pair<int, int>, std::vector<uint32_t>>();

	computeMainAxis();
	// alignOnMainAxis();
	//// Main axis has changed!
	// computeMainAxis();

	BLUE_LOG(trace) << "Start building octree.";
	octree_ = buw::makeReferenceCounted<buw::Octree>(this);
	octree_->build();
	BLUE_LOG(trace) << "Finished building octree.";

	computeChainage2();
	//filterRelativeHeightWithGrid(0.5, 0.5, nullptr);
	//computeIndices();
}

std::vector<buw::ReferenceCounted<buw::PointCloudSection>> OpenInfraPlatform::Infrastructure::PointCloud::getSections() {
	return sections_;
}

buw::ReferenceCounted<CCLib::ReferenceCloud> OpenInfraPlatform::Infrastructure::PointCloud::subsample(size_t size) {
	BLUE_LOG(fatal) << "This function should never be called right now.";
	return buw::ReferenceCounted<CCLib::ReferenceCloud>(
	  CCLib::CloudSamplingTools::subsampleCloudWithOctree(this, size, CCLib::CloudSamplingTools::SUBSAMPLING_CELL_METHOD::NEAREST_POINT_TO_CELL_CENTER, nullptr, octree_.get()));
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeIndices() {
	// Clear the index buffers.
	remainingIndices_.clear();
	filteredIndices_.clear();

	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if (idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");

	setCurrentInScalarField(idx_filtered);

	// Get the duplicate scalar field.
	int idx_duplicate = getScalarFieldIndexByName("Duplicate");
	if (idx_duplicate == -1)
		idx_duplicate = addScalarField("Duplicate");

	// Get the density scalar field
	int idx_density = getScalarFieldIndexByName("Density");
	if (idx_density == -1)
		idx_density = addScalarField("Density");

	// Get the coordinate filter scalar fields.
	int idx_coordX = getScalarFieldIndexByName("Coord. X");
	int idx_coordY = getScalarFieldIndexByName("Coord. Y");
	int idx_coordZ = getScalarFieldIndexByName("Coord. Z");

	// For each point, check it's Density and Duplicate field and if one of them is true, filter the point.
	for_each([&](size_t i) {
		ScalarType filtered = 0;
		if (idx_duplicate != -1) {
			setCurrentOutScalarField(idx_duplicate);
			filtered += getPointScalarValue(i);
		}

		if (idx_density != -1) {
			setCurrentOutScalarField(idx_density);
			filtered += getPointScalarValue(i);
		}

		if (idx_coordX != -1) {
			setCurrentOutScalarField(idx_coordX);
			filtered += getPointScalarValue(i);
		}

		if (idx_coordY != -1) {
			setCurrentOutScalarField(idx_coordY);
			filtered += getPointScalarValue(i);
		}

		if (idx_coordZ != -1) {
			setCurrentOutScalarField(idx_coordZ);
			filtered += getPointScalarValue(i);
		}

		setPointScalarValue(i, filtered);

		if (filtered > 0) {
			filteredIndices_.push_back(i);
		} else {
			remainingIndices_.push_back(i);
		}
	});

	// Clear the segmented indices buffer.
	segmentedIndices_.clear();

	// Get the base segmented sclar field and set is as the write active one.
	int idx_segmented = getScalarFieldIndexByName("Segmented");
	if (idx_segmented == -1)
		idx_segmented = addScalarField("Segmented");
	setCurrentInScalarField(idx_segmented);

	// Reset the base scalar field for segmented
	for_each([&](size_t i) { setPointScalarValue(i, 0); });

	// Get the specific segmentations: percentile, grid and rate of change.
	int idx_percentile = getScalarFieldIndexByName("SegmentedPercentile");
	int idx_grid = getScalarFieldIndexByName("SegmentedGrid");
	int idx_rof = getScalarFieldIndexByName("SegmentedRateOfChange");

	// For each point, set as segmented if all enabled segmentations apply.
	for_each([&](size_t i) {
		int numFilters = 0;
		int numValidFilters = 0;
		auto updateSegmentedValue = [&](size_t i, int index) {
			if (index != -1) {
				numFilters++;
				this->setCurrentOutScalarField(index);
				if (this->getPointScalarValue(i) > 0) {
					numValidFilters++;
				}
			}
		};

		updateSegmentedValue(i, idx_percentile);
		updateSegmentedValue(i, idx_grid);
		updateSegmentedValue(i, idx_rof);

		if (numFilters == numValidFilters && numFilters != 0)
			setPointScalarValue(i, 1);
		else
			setPointScalarValue(i, 0);
	});

	// Set the segmented scalar field to read from and insert the points into the buffer.
	setCurrentOutScalarField(idx_segmented);

	for_each([&](size_t i) {
		if (getPointScalarValue(i) > 0) {
			segmentedIndices_.push_back(i);
		}
	});
}

void OpenInfraPlatform::Infrastructure::PointCloud::computePairs(std::vector<std::pair<size_t, size_t>> &o_pairs, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	if (sections_.size() > 0) {
		BLUE_LOG(trace) << "Computing pairs.";

		// If we have a callback, call start to init the GUI.
		if (callback)
			callback->start();

		// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
		int idx = getScalarFieldIndexByName("Railway");
		if (idx == -1)
			idx = addScalarField("Railway");
		setCurrentInScalarField(idx);

		// Create a global list of all point pairs.
		int tid = 0;
		//#pragma omp parallel private(tid)
		{
			// Setup callback update variables.
			tid = omp_get_thread_num();
			int numSectionsPerThread = (sections_.size()) / omp_get_num_threads();
			int numSectionsPerPercent = numSectionsPerThread / 100;
			int processedSections = 0;
			int percentageCompleted = 0;

			// We iterate over all sections and calculate the pairs of matching points.
			std::vector<std::pair<size_t, size_t>> pairs = std::vector<std::pair<size_t, size_t>>();
			//#pragma omp for
			for (long i = 0; i < sections_.size(); i++) {
				if (sections_[i]) {
					// Insert all pairs in our local vector.
					auto result = sections_[i]->computePairs();
					if (result.size() > 0) {
						pairs.insert(pairs.end(), result.begin(), result.end());
					}
				} else {
					BLUE_LOG(warning) << "Null section detected. Nr: " << i;
				}

				// Update our callback.
				processedSections++;
				if (processedSections >= numSectionsPerPercent) {
					percentageCompleted++;
					processedSections = 0;

					if (tid == 0 && callback) {
						callback->update(percentageCompleted);
					}
				}
			}

				// Merge the local vectors in the master vector.
//#pragma omp critical
			{
				if (pairs.size() > 0) {
					o_pairs.insert(o_pairs.end(), pairs.begin(), pairs.end());
				} else {
					// BLUE_LOG(info) << "No pairs by thread #" << omp_get_thread_num() << " detected.";
				}
			}
		}

		// Stop our callback.
		if (callback)
			callback->stop();

		BLUE_LOG(trace) << "Done.";
	} else {
		BLUE_LOG(warning) << "Aborting. No sections found.";
	}
}

std::vector<buw::ReferenceCounted<CCLib::ReferenceCloud>> OpenInfraPlatform::Infrastructure::PointCloud::extractConnectedComponents(ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Vector that holds the individual components.
	std::vector<buw::ReferenceCounted<CCLib::ReferenceCloud>> components;

	// TODO
	return components;
}

const std::tuple<ScalarType, ScalarType> OpenInfraPlatform::Infrastructure::PointCloud::getScalarFieldMinAndMax(int idx) const {
	// Get the min and max for the scalar field and store it in the returned tuple.
	CCLib::ScalarField *field = getScalarField(idx);
	field->computeMinAndMax();
	return std::tuple<ScalarType, ScalarType>(field->getMin(), field->getMax());
}

const std::tuple<size_t, size_t> OpenInfraPlatform::Infrastructure::PointCloud::getScalarFieldMinAndMaxIndex(int idx)
{
	// Get the min and max for the scalar field and store it in the returned tuple.
	auto temp = getCurrentOutScalarFieldIndex();
	setCurrentOutScalarField(idx);
	std::tuple<size_t, size_t> idxMinMax = std::tuple<size_t, size_t>(0,0);
	for_each([&](size_t i) {
		auto value = getPointScalarValue(i);
		if(value < getPointScalarValue(std::get<0>(idxMinMax))) {
			std::get<0>(idxMinMax) = i;
		}

		if(value > getPointScalarValue(std::get<1>(idxMinMax))) {
			std::get<1>(idxMinMax) = i;
		}
	});

	setCurrentOutScalarField(temp);

	return idxMinMax;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesSegmentation(buw::PercentileSegmentationDescription desc,
                                                                                buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if (idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented percentile scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedPercentile");
	if (idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedPercentile");
	setCurrentInScalarField(idx_segmented);

	for_each([&](size_t i) { this->setPointScalarValue(i, 0); });

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
		auto octree = buw::Octree(*octree_);

#pragma omp for
		for (long i = 0; i < remainingIndices_.size(); i++) {
			uint32_t index = remainingIndices_[i];

			// Compute the neighbouring points using the octree for the query point.
			CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
			int numPoints = octree.getPointsInSphericalNeighbourhood(*getPoint(index), desc.kernelRadius, neighbours, level);

			// Sort points in neighbourhood according to height.
			std::sort(neighbours.begin(), neighbours.end(),
			          [](const CCLib::DgmOctree::PointDescriptor &lhs, const CCLib::DgmOctree::PointDescriptor &rhs) -> bool { return lhs.point->z < rhs.point->z; });

			// Remove points which have actually been removed due to filtering.
			auto isFilteredPoint = [&](const CCLib::DgmOctree::PointDescriptor point) -> bool { return getPointScalarValue(point.pointIndex) > 0; };
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
			if (diff >= desc.minThreshold && totalDiff < desc.maxThreshold) {
				for (int ii = idxUpper; ii < neighbours.size(); ii++) {
					int index_ii = neighbours[ii].pointIndex;
					setPointScalarValue(index_ii, 1.0f);
				}
			}

			// Update the number of processed points and update the callback if we are on the main thread.
			processedPoints++;
			if (tid == 0 && callback) {
				callback->update(100.0f * processedPoints / totalPoints);
			}
		}
	}

	computeIndices();

	// Tell the callback that we're done.
	if (callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesSegmentationHP(const buw::PercentileSegmentationDescription &desc,
                                                                                  buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	// Get the segmented percentile scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedPercentile");
	if (idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedPercentile");
	setCurrentInScalarField(idx_segmented);

	// Initialize all scalar values in the field to 0.
	for_each([&](size_t i) { this->setPointScalarValue(i, 0); });

	// Call this once to find the best level for the radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(desc.kernelRadius);

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	std::vector<uint32_t> dgmOctreeCells;
	bool success = octree_->getCellIndexes(level, dgmOctreeCells);
	if (!success)
		return -1;

	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;

#pragma omp parallel private(tid) firstprivate(callback) shared(level, dgmOctreeCells, desc, numCells, err)
	{
		// Initialize our variables for callback updates.
		tid = omp_get_thread_num();
		auto octree = buw::Octree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;

		// Iterate over all cells to call our nearest neighbour search on consecutive points in a cell for performance reasons.
#pragma omp for schedule(dynamic, 50)
		for (long idx = 0; idx < dgmOctreeCells.size(); idx++) {
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

			if (success) {
				// If the points were successfully selected, iterate over all points in the cell and search the nearest neighbours.
				for (int i = 0; i < points->size(); i++) {
					nss.queryPoint = *(points->getPoint(i));
					int numPoints = octree.findNeighborsInASphereStartingFromCell(nss, desc.kernelRadius, false);

					// Sort points in neighbourhood according to height.
					std::sort(nss.pointsInNeighbourhood.begin(), nss.pointsInNeighbourhood.begin() + numPoints,
					          [](const CCLib::DgmOctree::PointDescriptor &lhs, const CCLib::DgmOctree::PointDescriptor &rhs) -> bool { return lhs.point->z < rhs.point->z; });

					// Calculate the upper percentile as the index of the upper % point after sorting in ascending order, same for the lower % point.
					int idxUpper = (int)std::floor(desc.upperPercentile * numPoints);
					int idxLower = (int)std::floor(desc.lowerPercentile * numPoints);
					float percentileUpper = nss.pointsInNeighbourhood[idxUpper].point->z;
					float percentileLower = nss.pointsInNeighbourhood[idxLower].point->z;

					// Calculate the absolute difference between the percentiles and if it is larger than the specified threshold, segment the point as rail point.
					float diff = std::fabsf(percentileLower - percentileUpper);
					float totalDiff = std::fabsf((nss.pointsInNeighbourhood[0].point->z) - (nss.pointsInNeighbourhood[numPoints - 1].point->z));

					// If the diff is larger than the minThreshold and the totalDiff smaller than the maxThreshold, mark all points in the upper percentile.
					if (diff >= desc.minThreshold && totalDiff < desc.maxThreshold) {
						for (int ii = idxUpper; ii < numPoints; ii++) {
							size_t index_ii = nss.pointsInNeighbourhood[ii].pointIndex;
							this->setPointScalarValue(index_ii, 1.0f);
						}
					}
				}

				// Update our callback.
				processedCells++;
				if (processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if (tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			} else {
				// Stop the callback if we abort our function.
				if (tid == 0 && callback)
					callback->stop();
#pragma omp critical
				err = -2;
			}
		}
	}

	computeIndices();

	if (callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyPercentilesOnGridSegmentation(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	computeGrid();

	// Get the filtered scalar field.
	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if (idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");
	setCurrentOutScalarField(idx_filtered);

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedGrid");
	if (idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedGrid");
	setCurrentInScalarField(idx_segmented);

	for_each([&](size_t i) { this->setPointScalarValue(i, 0); });

	auto isFilteredPoint = [&](const uint32_t &idx) -> bool { return getPointScalarValue(idx) > 0; };

	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(0.1f);
	size_t processedCells = 0;
	size_t numCells = grid_.size();

	for (auto cell : grid_) {
		auto end = std::remove_if(cell.second.begin(), cell.second.end(), isFilteredPoint);
		cell.second.erase(end, cell.second.end());
		int numPoints = cell.second.size();

		std::sort(cell.second.begin(), cell.second.end(), [&](const uint32_t &lhs, const uint32_t &rhs) -> bool { return getPoint(lhs)->z < getPoint(rhs)->z; });

		// Calculate the 98 percentile as the index of the 98th % point after sorting in ascending order, same for the 10th % point.
		int idx98 = (int)std::floor(0.98 * numPoints);
		int idx10 = (int)std::floor(0.1 * numPoints);
		float percentile_98 = getPoint(cell.second[idx98])->z;
		float percentile_10 = getPoint(cell.second[idx10])->z;

		// Calculate the absolute difference between the percentiles and if it is larger than 10cm segment the point as rail point.
		float diff = std::fabsf(percentile_10 - percentile_98);
		if (diff >= 0.1f) {
			std::set<uint32_t> indices;
			for (int i = idx98; i < numPoints; i++) {
				CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
				int numNeighbours = octree_->getPointsInSphericalNeighbourhood(*getPoint(cell.second[i]), 0.1f, neighbours, level);

				for (auto elem : neighbours) {
					setPointScalarValue(elem.pointIndex, 1.0f);
				}
				setPointScalarValue(i, 1.0f);
			}
		}

		processedCells++;
		if (callback) {
			callback->update(100.0f * processedCells / numCells);
		}
	}

	computeIndices();

	// Tell the callback that we're done.
	if (callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::applyRateOfChangeSegmentation(RateOfChangeSegmentationDescription desc,
                                                                                 buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	// Get the segmented scalar field.
	int idx_segmented = getScalarFieldIndexByName("SegmentedRateOfChange");
	if (idx_segmented == -1)
		idx_segmented = addScalarField("SegmentedRateOfChange");
	setCurrentInScalarField(idx_segmented);

	// Initialize our scalar field.
	for_each([&](size_t i) { this->setPointScalarValue(i, 0); });

	bool success = false;

	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	std::vector<uint32_t> dgmOctreeCells;
	success = octree_->getCellIndexes(10, dgmOctreeCells);
	if (!success)
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
		auto octree = buw::Octree(*octree_);
		int numCellsPerThread = numCells / omp_get_num_threads();
		int processedCells = 0;
		int numCellsPerPercent = numCellsPerThread / 100;
		int percentageCompleted = 0;

#pragma omp for schedule(dynamic, 50)
		for (long idx = 0; idx < dgmOctreeCells.size(); idx++) {
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

			if (success) {
				// If the points were successfully selected, iterate over all points in the cell and search the nearest neighbours.
				for (int i = 0; i < points->size(); i++) {
					nss.queryPoint = *(points->getPoint(i));
					int numNeighbours = octree_->findNearestNeighborsStartingFromCell(nss);

					// Initialize the diff variable and the number of neighbours which are selected for the computation.
					float diff = 0.0f;
					int numSelectedNeighbours = 0;

					// Calculate the mean difference in the specified dimension for all points in the neighbourhood which fulfill the conditions.
					for (auto neighbour : nss.pointsInNeighbourhood) {
						if (neighbour.squareDistd <= nss.maxSearchSquareDistd && neighbour.squareDistd != 0.0) {
							diff += std::fabsf(nss.queryPoint[desc.dim] - (*neighbour.point)[desc.dim]);
							numSelectedNeighbours++;
						}
					}

					// If we found at least one neighbour, compute the average diff and compare with the threshold.
					if (numSelectedNeighbours > 0) {
						diff /= numSelectedNeighbours;
						if (diff <= desc.maxRateOfChangeThreshold) {
							this->setPointScalarValue(points->getPointGlobalIndex(i), 1.0f);
						}
					}
				}

				// Update our callback.
				processedCells++;
				if (processedCells >= numCellsPerPercent) {
					percentageCompleted++;
					processedCells = 0;
					if (tid == 0 && callback)
						callback->update(percentageCompleted);
				}
			} else {
				// Stop the callback if we abort our function.
				if (tid == 0 && callback)
					callback->stop();

				err = -2;
			}
		}
	}

	computeIndices();

	// Stop our callback.
	if (callback)
		callback->stop();

	return err;
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlines(const buw::CenterlineComputationDescription &desc,
                                                                      buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// Add a scalar field for railway and encode the left/right railway index as -1 and 1. Initialize it to 0 and set it as input scalar field.
	// int idx_railway = getScalarFieldIndexByName("Railway");
	// if (idx_railway == -1)
	//	idx_railway = addScalarField("Railway");
	// setCurrentInScalarField(idx_railway);

	// for_each([&](size_t i) { setPointScalarValue(i, 0); });

	// Get the rail pair points.
	std::vector<std::pair<size_t, size_t>> pointPairs = std::vector<std::pair<size_t, size_t>>();
	computePairs(pointPairs, callback);

	// Create a Point Cloud for the centerline points.
	buw::ReferenceCounted<PointCloud> centerpointsPointCloud = buw::makeReferenceCounted<PointCloud>();
	bool success = true;

	// Reserve the memory for the point data.
	success &= centerpointsPointCloud->reserve(pointPairs.size());
	if(!success)
		return -3;

	// Enable scalar fields.
	success &= centerpointsPointCloud->enableScalarField();
	if(!success)
		return -4;
		
	// Initialize the chainage scalar field to write to.
	int idxCPC_chainage = centerpointsPointCloud->addScalarField("Chainage");
	if(idxCPC_chainage == -1) {
		return -1;
	}
	centerpointsPointCloud->setCurrentInScalarField(idxCPC_chainage);

	// Get chainage scalar field from original point cloud to read from.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	if(idx_chainage == -1) {
		return -2;
	}
	setCurrentOutScalarField(idx_chainage);

	// Compute centerpoints witch chanaige and add the computed points to the centerpointsPointCloud.
	for(long i = 0; i < pointPairs.size(); i++) {
		auto pair = pointPairs[i];

		CCVector3 start = *(getPoint(pair.first));
		CCVector3 end = *(getPoint(pair.second));
		ScalarType chainage = 0.5f * (getPointScalarValue(pair.first) + getPointScalarValue(pair.first));
		CCVector3 center = 0.5f * (end + start);

		centerpointsPointCloud->addPoint(center);
		centerpointsPointCloud->setPointScalarValue(i, chainage);
	}
	
	// Remove points closer than 1mm to avoid "black holes" of insane density.
	centerpointsPointCloud->getDGMOctree()->build(callback.get());
	buw::DuplicateFilterDescription dfd;
	dfd.dim = buw::ePointCloudFilterDimension::Volume3D;
	dfd.minDistance = 0.002;
	centerpointsPointCloud->applyDuplicateFilter(dfd, callback);
	centerpointsPointCloud->computeIndices();
	centerpointsPointCloud->removeFilteredPoints(callback);
	centerpointsPointCloud->getDGMOctree()->clear();
	centerpointsPointCloud->getDGMOctree()->build(callback.get());

	//// Remove centerline points which are outliers.	
	//buw::LocalDensityFilterDescription ldfd;
	//ldfd.density = CCLib::GeometricalAnalysisTools::DENSITY_KNN;
	//ldfd.dim = buw::ePointCloudFilterDimension::Volume3D;
	//ldfd.kernelRadius = 0.1f;
	//ldfd.minThreshold = 15;
	//centerpointsPointCloud->applyLocalDensityFilter(ldfd, callback);
	//centerpointsPointCloud->computeIndices();
	//centerpointsPointCloud->removeFilteredPoints(callback);
	//centerpointsPointCloud->getDGMOctree()->clear();
	//centerpointsPointCloud->getDGMOctree()->build(callback.get());

	auto centerpoints = centerpointsPointCloud->getAllPointsAndScalarFieldValue(idxCPC_chainage);
	
	//// Create a global list of all point pairs.
	//std::vector<std::pair<size_t, size_t>> rails = std::vector<std::pair<size_t, size_t>>();
	//
	//computePairs(rails, callback);
	int tid = 0;
	//
	//
	//auto computeCenterpoints = [&](const std::vector<std::pair<size_t, size_t>> rails, std::vector<CCVector3> &o_centerpoints) {
	//	BLUE_LOG(trace) << "Computing centerpoints.";
	//
	//	// Reserve space for the centerpoints points and color them blue.
	//	this->reserve(this->size() + rails.size());
	//	this->reserveTheRGBTable();
	//
	//	// For each pair, insert the point in the middle as centerpoints point.
	//	for (auto pair : rails) {
	//		CCVector3 start = *(getPoint(pair.first));
	//		CCVector3 end = *(getPoint(pair.second));
	//		CCVector3 center = 0.5f * (end + start);
	//		o_centerpoints.push_back(center);
	//	}
	//
	//	BLUE_LOG(trace) << "Done.";
	//};
	//
	//// For each pair, insert the point in the middle as centerpoints point.
	//std::vector<CCVector3> centerpoints = std::vector<CCVector3>();
	//computeCenterpoints(rails, centerpoints);
	//
	//// Delete the pairs since we dont need them anymore.
	//rails.clear();

	auto sortCenterpointsIntoCenterlines = [&](const std::vector<std::pair<CCVector3, ScalarType>> &centerpoints, std::vector<std::vector<size_t>> &centerlines,
	                                           buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr) {
		centerlines.push_back(std::vector<size_t>());
		centerlines[0].push_back(0);

		auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) -> float { return (rhs - lhs).norm(); };

		// Start our callback if we have one.
		if (callback)
			callback->start();

		BLUE_LOG(trace) << "Sorting centerpoints into centerlines.";

		// Initialize variables for callback update.
		float totalPoints = centerpoints.size();
		int pointsPerPercent = totalPoints / 100;
		float processedPoints = 0;
		int percentageCompleted = 0;

		for (size_t i = 1; i < centerpoints.size(); i++) {
			// Store the point to be checked and whether we have inserted it or whether it is ambiguous or not.
			auto point = centerpoints[i].first;
			auto chainage = centerpoints[i].second;

			bool inserted = false;
			bool discarded = false;
			bool ambiguous = false;
			bool unnecessary = false;

			auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end) -> CCVector2 {
				// Matrix which is capable of holding all points for PCA.
				Eigen::MatrixX2d mat;
				mat.resize(end - start, 2);
				for (size_t i = start; i < end; i++) {
					auto pos = centerpoints[alignment[i]].first;
					mat.row(i - start) = Eigen::Vector2d(pos.x, pos.y);
				}

				// Do PCA to find the largest eigenvector -> main axis.
				Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
				Eigen::MatrixXd cov = centered.adjoint() * centered;
				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
				Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1);

				return CCVector2(vec.x(), vec.y());
			};

			// Initialize the pair min with index and distance
			std::tuple<size_t, float, float> min = std::tuple<size_t, float, float>(centerlines.size(), 0, LONG_MAX);
			int tid = 0;

//#pragma omp parallel private(tid) firstprivate(callback) shared(inserted, ambiguous, unnecessary, min)
			{
				tid = omp_get_thread_num();

				// Iterate over all tracks.
				//#pragma omp for
				for(long ii = 0; ii < centerlines.size(); ii++) {
					if(ambiguous || unnecessary)
						break;

					auto &line = centerlines[ii];

					// Calculate the distance to the endpoint
					for(int offset = 1; offset < 100 && offset <= line.size(); offset++) {
						auto endpoint = centerpoints[line[line.size() - offset]].first;
						float endpointChainage = centerpoints[line[line.size() - offset]].second;
						float distance = dist(point, endpoint);

						// Compute the ratio between chainage change and distance.
						float dChainage = chainage - endpointChainage;
						float ratio = dChainage / distance;
						if(distance < 5) {
							if(ratio > 0.9 || distance < desc.maxDistance) {
								inserted = true;
								discarded = false;
								line.push_back(i);
								break;
							}
							else {
								continue;
							}
						}
						else {
							break;
						}

						//if(ratio > 0.9f && distance < 2.0f) {
						//	inserted = true;
						//	discarded = false;
						//	line.push_back(i);
						//	break;
						//}
						//else if(distance < desc.maxDistance && ratio > 0.7f) {
						//	inserted = true;
						//	discarded = false;
						//	line.push_back(i);
						//	break;
						//}
						//else if(distance < desc.maxDistance && ratio < 0.5f) {
						//	discarded = true;
						//	continue;
						//}
						//else {
						//	continue;
						//}
					}
					if(discarded || inserted)
						break;
				}

				if(!inserted && !discarded) {
					centerlines.push_back(std::vector<size_t>());
					centerlines.back().push_back(i);
				}
			}

						


//					if (distance <= 0.001) {
//						//#pragma omp critical
//						unnecessary = true;
//						break;
//					}
//
//					// If the distance is smaller than 20cm, we would add the point to this line.
//					if (distance < desc.maxDistance) {						
//						if (inserted) {
//#pragma omp critical
//							ambiguous = true;
//							break;
//						}
//						// Otherwise the min distance is updated and inserted is set to true.
//						else {
//#pragma omp critical
//							{
//								if (angle > std::get<1>(min) && distance < std::get<2>(min)) {
//									inserted = true;
//									min = std::tuple<size_t, float, float>(ii, angle, distance);
//								}
//							}
//						}
//					}
//					
//				}
//#pragma omp barrier
//#pragma omp master
//				{
//					// If the point is not ambiguous, we either insert it in the matching line or create a new one.
//					if (!ambiguous && !unnecessary) {
//						if (inserted) {
//							tracks[std::get<0>(min)].push_back(i);
//						}
//						// Only add this as a new line currently if it far enough away!
//						else {
//							bool hasMinDistanceThreshold = true;
//
//#pragma omp parallel for shared(point, hasMinDistanceThreshold) schedule(dynamic)
//							for (long line_idx = 0; line_idx < tracks.size(); line_idx++) {
//								auto line = tracks[line_idx];
//								for (auto point_idx : line)
//									if (dist(point, centerpoints[point_idx].first) < 0.16f)
//										hasMinDistanceThreshold = false;
//							}
//
//							if (hasMinDistanceThreshold) {
//								// If no matching line has been found, add a new one with this one as the starting point.
//								tracks.push_back(std::vector<size_t>());
//								tracks.back().push_back(i);
//							}
//						}
//					}

					// Check if we have a centerline which is very small (does not meet the minimum requirements as specified) and remove it to save some computation time.
					if (i % 1000 == 0) {
						// Erase the tracks which do not fulfill the criteria and where no more points are being added.
						auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) {
							float dChainage = std::fabsf(chainage -centerpoints[line.back()].second);
							//float centerlineLength = (centerpoints[line.back()].first - centerpoints[line.front()].first).norm();
							float centerlineLength = std::fabsf(centerpoints[line.back()].second - centerpoints[line.front()].second);
							size_t numCenterlinePoints = line.size();
							return dChainage > 10.0f  && (numCenterlinePoints < desc.minSegmentPoints || centerlineLength < desc.minSegmentLength);
						});

						centerlines.erase(end, centerlines.end());
						std::sort(centerlines.begin(), centerlines.end(), [](const std::vector<size_t> &lhs, const std::vector<size_t> &rhs) -> bool {
							return lhs.size() > rhs.size();
						});
					}

					// Update the callback.
					if (callback) {
						if (++processedPoints >= pointsPerPercent) {
							percentageCompleted++;
							processedPoints = 0;
							callback->update(percentageCompleted);
						}
					}
				}
		//	}
		//}

		// Tell the callback that we're done.
		if (callback)
			callback->stop();

		// Clear all lines having less then 100 points -> probably noise or something.
		auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool {
			//float centerlineLength = (centerpoints[line.back()].first - centerpoints[line.front()].first).norm();
			float centerlineLength = std::fabsf(centerpoints[line.back()].second - centerpoints[line.front()].second);
			size_t numCenterlinePoints = line.size();
			return numCenterlinePoints < desc.minSegmentPoints || centerlineLength < desc.minSegmentLength;
		});

		centerlines.erase(end, centerlines.end());

		BLUE_LOG(trace) << "Done.";
	};

	// Sort the centerpoints along the main axis.
	std::sort(centerpoints.begin(), centerpoints.end(), [&](const std::pair<CCVector3, ScalarType> &lhs, const std::pair<CCVector3, ScalarType> &rhs) -> bool { return lhs.second < rhs.second; });

	// Split the centerpoints into different rails and recognize different rails. Only store indices to save memory.
	std::vector<std::vector<size_t>> centerlines = std::vector<std::vector<size_t>>();
	sortCenterpointsIntoCenterlines(centerpoints, centerlines, callback);

	auto fuseCenterlines = [&](std::vector<std::vector<size_t>> &centerlines) {

	};

	if (centerlines.empty()) {
		BLUE_LOG(trace) << "No centerlines remaining after sorting. Choose a lower \"minSegmentPoints\" threshold and/or lower \"minSegmentLength\" threshold.";
		return 0;
	}

	if (callback)
		callback->start();

	BLUE_LOG(trace) << "Smoothing centerlines.";

	// Collapse tracks to have a uniform density.
	std::vector<std::vector<std::pair<CCVector3, ScalarType>>> alignments = std::vector<std::vector<std::pair<CCVector3, ScalarType>>>(centerlines.size());
	int percentageCompleted = 0;
	bool update = true;

#pragma omp parallel private(tid) firstprivate(callback) shared(percentageCompleted, update, alignments, centerlines, centerpoints)
	{
		tid = omp_get_thread_num();
		int percentPerCenterline = 100 / centerlines.size();
		update = true;

#pragma omp for schedule(dynamic)
		for(long idx_line = 0; idx_line < centerlines.size(); idx_line++) {
			auto &line = centerlines[idx_line];

			long startIndex = 0, endIndex = 0;

			while(endIndex < line.size()) {

				auto dChainage = [&]()->float {
					return std::fabsf(centerpoints[line[endIndex]].second - centerpoints[line[startIndex]].second);
				};

				while(endIndex < line.size() && dChainage() < desc.centerlineDensity) {
					endIndex++;
				}

				int numPoints = (endIndex - startIndex);
				CCVector3 center = CCVector3(0, 0, 0);
				ScalarType chainage = 0;
				for(; startIndex < endIndex; startIndex++) {
					center += (centerpoints[line[startIndex]].first / (float)numPoints);
					chainage += (centerpoints[line[startIndex]].second / (float)numPoints);
				}
				alignments[idx_line].push_back(std::pair<CCVector3, ScalarType>(center, chainage));

				if(tid == 0 && callback && update) {
					callback->update(percentageCompleted);
					update = false;
				}
			}			
		}
#pragma omp critical
		{
			percentageCompleted += percentPerCenterline;
			update = true;
		}
	}

	// Tell the callback that we're done.
	if (callback)
		callback->stop();
	
	BLUE_LOG(trace) << "Done.";

	// Reserve space for the centerpoints points and color them blue.
	long totalPoints = 0;

#pragma omp parallel for reduction(+:totalPoints)
	for(int i = 0; i < alignments.size(); i++)
		totalPoints += alignments[i].size();

	this->reserve(this->size() + totalPoints);
	this->reserveTheRGBTable();

	// Iterate over all segments and combine the centers of each projection section.
//#pragma omp parallel private(tid) firstprivate(callback) shared(percentageCompleted, update, alignments, tracks, centerpoints)
//	{
//		tid = omp_get_thread_num();
//		int percentPerCenterline = 100 / tracks.size();
//		update = true;
//
//		auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) -> float { return (rhs - lhs).norm(); };
//
//#pragma omp for schedule(dynamic)
//		for (long idx = 0; idx < tracks.size(); idx++) {
//			auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end) -> CCVector3 {
//				// Matrix which is capable of holding all points for PCA.
//				Eigen::MatrixX3d mat;
//				mat.resize(end - start, 3);
//				for (size_t i = start; i < end; i++) {
//					auto pos = centerpoints[alignment[i]];
//					mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
//				}
//
//				// Do PCA to find the largest eigenvector -> main axis.
//				Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
//				Eigen::MatrixXd cov = centered.adjoint() * centered;
//				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
//				Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1).normalized();
//
//				return CCVector3(vec.x(), vec.y(), vec.z());
//			};
//
//			// Get the line which we are working on and store the start and end index for the section for which we want to combine all points as their center of mass.
//			auto &line = tracks[idx];
//			long startIndex = 0, endIndex = 0;
//			long lineSize = line.size();
//
//			// Iterate over the line and check how far we make our progress along the main axis. Once we are above a certain threshold, we combine all points in their center of
//			// mass.
//			for (size_t i = 0; i < lineSize - 1; i++) {
//				// auto axis = getPCA(line, std::max(0, (int)i - 100000), std::min((int)line.size() - 1, (int) i + 100000));
//				auto startPoint = centerpoints[line[startIndex]];
//				
//				long startIndexPCA = startIndex, endIndexPCA = startIndex;
//				
//				while ((startIndexPCA > 0) && dist(centerpoints[line[startIndexPCA]], startPoint) < 10)
//					startIndexPCA -= 1;
//				
//				while ((endIndexPCA < lineSize - 1) && dist(centerpoints[line[endIndexPCA]], startPoint) < 10)
//					endIndexPCA += 1;
//				
//				auto axis = getPCA(line, startIndexPCA, endIndexPCA);
//				
//				float startLength = axis.dot(startPoint);
//				
//				while (i < lineSize - 1 && std::fabsf(axis.dot(centerpoints[line[i + 1]]) - startLength) < desc.centerlineDensity)
//					i++;
//				
//
//				endIndex = i + 1;
//				int numPoints = (endIndex - startIndex);
//				CCVector3 center = CCVector3(0, 0, 0);
//				for (; startIndex < endIndex; startIndex++) {
//					center += (centerpoints[line[startIndex]] / (float)numPoints);
//				}
//
//				alignments[idx].push_back(center);
//
//				if (tid == 0 && callback && update) {
//					callback->update(percentageCompleted);
//					update = false;
//				}
//			}
//
//#pragma omp critical
//			{
//				percentageCompleted += percentPerCenterline;
//				update = true;
//			}
//		}
//	}
//
//	// Tell the callback that we're done.
//	if (callback)
//		callback->stop();
//
//	BLUE_LOG(trace) << "Done.";

	// Delete the tracks buffer since we dont need it anymore.
	std::for_each(centerlines.begin(), centerlines.end(), [](std::vector<size_t> &line) { line.clear(); });
	centerlines.clear();

	auto addAlignmentPoints = [&]() {
		// Use this vector to store the indices of the new centerline points to properliy set their scalar value.
		std::vector<std::vector<size_t>> centerlinePointIndices = std::vector<std::vector<size_t>>(alignments.size());

		// Only add centerpoints for alignments which are also exported.
		for (size_t idx = 0; idx < alignments.size(); idx++) {
			auto &segment = alignments[idx];
			for (auto point : segment) {
				addPoint(CCVector3(point.first));
				addRGBColor(255 * (float)idx / (float)alignments.size(), 0, 255);
				centerlinePointIndices[idx].push_back(this->size() - 1);
			}
		}

		// Add a scalar field for centerline so that we can delete them again when we do the reset.
		int idx_centerline = getScalarFieldIndexByName("Centerline");
		if (idx_centerline == -1)
			idx_centerline = addScalarField("Centerline");
		setCurrentInScalarField(idx_centerline);		

		// Initialize all centerline scalar values to -1.
		for_each([&](size_t i) { setPointScalarValue(i, -1); });

		// Set the index of the centerline as the scalar value.
		for (size_t idx = 0; idx < centerlinePointIndices.size(); idx++) {
			for(size_t i = 0; i < centerlinePointIndices[idx].size(); i++) {
				auto pointIndex = centerlinePointIndices[idx][i];
				setCurrentInScalarField(idx_centerline);
				setPointScalarValue(pointIndex, idx);
				setCurrentInScalarField(idx_chainage);
				setPointScalarValue(pointIndex, alignments[idx][i].second);
			}
		}
	};

	addAlignmentPoints();

	// Update the centerline description so that we know how the tracks were generated when we export the curvatures etc. from the measurement.
	centerlineDescription_ = desc;

	// Update the indices.
	computeIndices();

	// Return the number of selected alignments.
	return alignments.size();
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlines2(const buw::CenterlineComputationDescription &desc,
                                                                       buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// Get the rail pair points.
	std::vector<std::pair<size_t, size_t>> pointPairs = std::vector<std::pair<size_t, size_t>>();
	computePairs(pointPairs, callback);	
	
	// Create a Point Cloud for the centerline points.
	buw::ReferenceCounted<PointCloud> centerpointsPointCloud = buw::makeReferenceCounted<PointCloud>();
	bool success = true;

	// Reserve the memory for the point data.
	success &= centerpointsPointCloud->reserve(pointPairs.size());
	if(!success)
		return -3;

	// Enable scalar fields.
	success &= centerpointsPointCloud->enableScalarField();
	if(!success)
		return -4;
	
	// Reserve the color table.
	success &= centerpointsPointCloud->reserveTheRGBTable();
	if(!success)
		return -5;

	// Initialize the chainage scalar field to write to.
	int idxCPC_chainage = centerpointsPointCloud->addScalarField("Chainage");
	if(idxCPC_chainage == -1) {
		return -1;
	}
	centerpointsPointCloud->setCurrentInScalarField(idxCPC_chainage);

	// Get chainage scalar field from original point cloud to read from.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	if (idx_chainage == -1) {
		return -2;
	}
	setCurrentOutScalarField(idx_chainage);

	const ColorCompType red[3] = { 255,0,0 };

	// Compute centerpoints witch chanaige and add the computed points to the centerpointsPointCloud.
	for(long i = 0; i < pointPairs.size(); i++) {
		auto pair = pointPairs[i];

		CCVector3 start = *(getPoint(pair.first));
		CCVector3 end = *(getPoint(pair.second));
		ScalarType chainage = 0.5f * (getPointScalarValue(pair.first) + getPointScalarValue(pair.first));
		CCVector3 center = 0.5f * (end + start);

		centerpointsPointCloud->addPoint(center);
		centerpointsPointCloud->setPointScalarValue(i, chainage);
	}

	centerpointsPointCloud->resizeTheRGBTable(centerpointsPointCloud->size());

	centerpointsPointCloud->for_each([&](size_t i) {
		centerpointsPointCloud->setPointColor(i, red);
	});

	// Remove points closer than 1mm to avoid "black holes" of insane density.
	centerpointsPointCloud->getDGMOctree()->build(callback.get());
	buw::DuplicateFilterDescription dfd;
	dfd.dim = buw::ePointCloudFilterDimension::Volume3D;
	dfd.minDistance = 0.002;
	centerpointsPointCloud->applyDuplicateFilter(dfd, callback);
	centerpointsPointCloud->computeIndices();
	centerpointsPointCloud->removeFilteredPoints(callback);
	centerpointsPointCloud->getDGMOctree()->clear();
	centerpointsPointCloud->getDGMOctree()->build(callback.get());

	// Remove centerline points which are outliers.	
	buw::LocalDensityFilterDescription ldfd;
	ldfd.density = CCLib::GeometricalAnalysisTools::DENSITY_KNN;
	ldfd.dim = buw::ePointCloudFilterDimension::Volume3D;
	ldfd.kernelRadius = 0.05f;
	ldfd.minThreshold = 15;
	centerpointsPointCloud->applyLocalDensityFilter(ldfd, callback);
	centerpointsPointCloud->computeIndices();
	centerpointsPointCloud->removeFilteredPoints(callback);
	centerpointsPointCloud->getDGMOctree()->clear();
	centerpointsPointCloud->getDGMOctree()->build(callback.get());

	// Extract the connected component based on chainage.
	centerpointsPointCloud->setCurrentOutScalarField(idxCPC_chainage);

	// Add a component scalar field to label connected components.
	int idxCPC_component = centerpointsPointCloud->addScalarField("Component");
	centerpointsPointCloud->setCurrentInScalarField(idxCPC_component);
	centerpointsPointCloud->for_each([&](size_t i) { centerpointsPointCloud->setPointScalarValue(i, -1); });
	centerpointsPointCloud->getCurrentInScalarField()->computeMinAndMax();

	// Get min and max chainage.
	centerpointsPointCloud->getCurrentOutScalarField()->computeMinAndMax();
	ScalarType minChainage, maxChainage;
	std::tie<ScalarType, ScalarType>(minChainage, maxChainage) = centerpointsPointCloud->getScalarFieldMinAndMax(idxCPC_chainage);

	auto cpcOctree = centerpointsPointCloud->getDGMOctree();
	char level = cpcOctree->findBestLevelForAGivenNeighbourhoodSizeExtraction(0.7);	
	
	// Get the octree cell indices to iterate over the cells, return -1 if an error occurs.
	CCLib::DgmOctree::cellsContainer dgmOctreeCells;
	success = cpcOctree->getCellCodesAndIndexes(level, dgmOctreeCells, true);
	
	// Initialize counter variables for our callback update.
	int numCells = dgmOctreeCells.size();
	int tid = 0;
	int err = 0;
	
	// Create and initialize the nearest neighbour search struct as far as possible.
	CCLib::DgmOctree::NearestNeighboursSphericalSearchStruct nss;
	nss.level = level;
	nss.maxSearchSquareDistd = std::pow(0.7, 2);
	
	int component = 0;

	while(false/*std::get<0>(centerpointsPointCloud->getScalarFieldMinAndMax(idxCPC_component)) == -1*/) {
		std::set<size_t> border = std::set<size_t>();

		// Get the first point which does not have a component.
		centerpointsPointCloud->setCurrentOutScalarField(idxCPC_component);
		centerpointsPointCloud->for_each([&](size_t i) {
			if(border.size() == 0) {
				if(centerpointsPointCloud->getPointScalarValue(i) == -1) {
					border.insert(i);
					return;
				}
			}
			else {
				return;
			}
		});

		centerpointsPointCloud->setCurrentOutScalarField(idxCPC_chainage);

		while(!border.empty()) {
			//Start at random point, get points in neighbourhood.
			//Add points which fulfill chainage criterion to border.
			//Expand all points in border in the same way.
			//Maybe recompute chainage on the centerline cloud.
			//Maybe use Box neighbourhood with the cells axis.
			auto startIndex = *border.begin();
			auto startPoint = centerpointsPointCloud->getPoint(startIndex);
			ScalarType startChainage = centerpointsPointCloud->getPointScalarValue(startIndex);

			cpcOctree->getTheCellPosWhichIncludesThePoint(startPoint, nss.cellPos, level);
			auto code = cpcOctree->getTruncatedCellCode(nss.cellPos, level);
			nss.alreadyVisitedNeighbourhoodSize = 0;
			nss.minNumberOfNeighbors = 0;
			nss.queryPoint = *startPoint;
			cpcOctree->computeCellCenter(nss.cellPos, level, nss.cellCenter);

			int numPoints = cpcOctree->findNeighborsInASphereStartingFromCell(nss, 0.7);

			for(int i = 0; i < numPoints; i++) {
				auto point = nss.pointsInNeighbourhood[i];
				float dChainage = centerpointsPointCloud->getPointScalarValue(point.pointIndex) - startChainage;
				float distance = std::sqrt(point.squareDistd);
				centerpointsPointCloud->setCurrentOutScalarField(idxCPC_component);
				bool explored = centerpointsPointCloud->getPointScalarValue(point.pointIndex) != -1;

				if(!explored && (std::abs(dChainage / distance) > 0.7 || distance < 0.067)) {
					border.insert(point.pointIndex);
					centerpointsPointCloud->setPointScalarValue(point.pointIndex, component);
				}

				centerpointsPointCloud->setCurrentOutScalarField(idxCPC_chainage);
			}

			// Remove the point that we just explored
			border.erase(startIndex);
			centerpointsPointCloud->setPointScalarValue(startIndex, component);

			BLUE_LOG(trace) <<"Component #" << component << ". Explored point #" << startIndex << ". " << border.size() << " points in border.";
		}

		component++;
		centerpointsPointCloud->getCurrentInScalarField()->computeMinAndMax();
	}

	
	level = centerpointsPointCloud->getDGMOctree()->findBestLevelForAGivenNeighbourhoodSizeExtraction(0.7);
	BLUE_LOG(trace) << "Level:" << (int)level;
	float cellSize = centerpointsPointCloud->getDGMOctree()->getCellSize(level);
	BLUE_LOG(trace) << "Cell Size:" << cellSize;
	
	if(cellSize < 0.7f) {
		BLUE_LOG(warning) << "Cell size below 0.7m, adjusting.";
	
		while(centerpointsPointCloud->getDGMOctree()->getCellSize(level) < 0.7f)
			level--;
	
		BLUE_LOG(trace) << "Level:" << (int)level;
		cellSize = centerpointsPointCloud->getDGMOctree()->getCellSize(level);
		BLUE_LOG(trace) << "Cell Size:" << cellSize;
	}
	
	int numComponents = CCLib::AutoSegmentationTools::labelConnectedComponents(centerpointsPointCloud.get(), level, false, callback.get(), centerpointsPointCloud->getDGMOctree().get());
	CCLib::ReferenceCloudContainer container = CCLib::ReferenceCloudContainer(numComponents);
	
	if(numComponents > 0) {
		CCLib::AutoSegmentationTools::extractConnectedComponents(centerpointsPointCloud.get(), container);
	
		std::sort(container.begin(), container.end(), [](CCLib::ReferenceCloud* &lhs, CCLib::ReferenceCloud* &rhs)->bool { return lhs->size() > rhs->size(); });
	
		// Append the centerpointsPointCloud to this one.
		if(!hasColors() || !centerpointsPointCloud->hasColors())
			BLUE_LOG(warning) << "Appending cloud without colors.";
	
		ColorCompType red[3] = { 255,0,0 };
		ColorCompType green[3] = { 0,255,0 };
		ColorCompType blue[3] = { 0,0,255 };
	
		auto centerline = std::shared_ptr<ccPointCloud>(centerpointsPointCloud->partialClone(container[0]));
		
	
		add(centerline, callback, red);
		add(std::shared_ptr<ccPointCloud>(centerpointsPointCloud->partialClone(container[1])), callback, blue);
		add(std::shared_ptr<ccPointCloud>(centerpointsPointCloud->partialClone(container[2])), callback, green);
	
		computeIndices();
		octree_->clear();
		octree_->build();
	}		

	return 1;
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlines3(const buw::CenterlineComputationDescription & desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(callback)
		callback->start();

	// Set the chainage scalar field to read from.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	setCurrentOutScalarField(idx_chainage);

	// Init the tracks with the first point pair.
	std::vector<std::vector<std::pair<size_t, size_t>>> tracks = std::vector<std::vector<std::pair<size_t, size_t>>>();
	tracks.push_back(std::vector<std::pair<size_t, size_t>>());
	int i = 0;
	auto firstpairs = sections_[i]->computePairs();
	while(firstpairs.empty())
		firstpairs = sections_[++i]->computePairs();

	auto sortPairsChainageAsc = [&](std::vector<std::pair<size_t, size_t>> &pairs) {
		std::sort(pairs.begin(), pairs.end(), [&](std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs)->bool {
			float lhs_chainage = 0.5f * getPointScalarValue(lhs.first) + 0.5f * getPointScalarValue(lhs.second);
			float rhs_chainage = 0.5f * getPointScalarValue(rhs.first) + 0.5f * getPointScalarValue(rhs.second);
			return lhs_chainage < rhs_chainage;
		});
	};

	sortPairsChainageAsc(firstpairs);
	tracks[0].push_back(firstpairs[0]);

	auto pairDist = [&](std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs) -> double {
		return (*getPoint(lhs.first) - *getPoint(rhs.first)).norm() + (*getPoint(lhs.second) - *getPoint(rhs.second)).norm();
	};

	// Compute the pairs for all sections and immediately sort them.
	for(long i = 0; i < sections_.size(); i++) {
		auto pairs = sections_[i]->computePairs();
		sortPairsChainageAsc(pairs);

		for(auto &it : pairs) {
			bool inserted = false;
			for(auto &line : tracks) {
				if(pairDist(line.back(), it) < 0.32 || pairDist(line[line.size() - 2], it) < 0.32) {
					line.push_back(it);
					inserted = true;
					break;
				}
			}
			if(!inserted) {
				tracks.push_back(std::vector<std::pair<size_t, size_t>>());
				tracks.back().push_back(it);
			}
		}

		if(callback)
			callback->update(((float)i / (float)sections_.size()) * 100.0f);
	}
	
	auto end = std::remove_if(tracks.begin(), tracks.end(), [&](std::vector<std::pair<size_t, size_t>> track)->bool {
		return 0.5*pairDist(track.front(), track.back()) < 10;
	});

	tracks.erase(end, tracks.end());

	if(callback)
		callback->stop();

	return tracks.size();
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetCenterlines() {
	centerlineDescription_ = buw::CenterlineComputationDescription();
	return resetRailwaySegmentation();
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetPairs() {
	// Reset the railway points color to white.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if (idx_railway == -1)
		return -1;

	setCurrentOutScalarField(idx_railway);
	const ColorCompType white[3] = {255, 255, 255};
	for_each([&](size_t i) {
		if (getPointScalarValue(i) != 0)
			setPointColor(i, white);
	});

	resetScalarField("Railway");
	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::computeCenterlineCurvature(const buw::CenterlineCurvatureComputationDescription &desc,
                                                                              buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// Tell the callback that we're done.
	if (callback)
		callback->start();

	// Add a scalar field for centerline so that we can delete them again when we do the reset.
	int idx_centerline = getScalarFieldIndexByName("Centerline");
	if (idx_centerline == -1) {
		// Stop our callback.
		if (callback)
			callback->stop();

		BLUE_LOG(warning) << "Centerline scalar field not found. Method returning with error.";
		return -1;
	}

	ScalarType min, max;
	std::tie(min, max) = getScalarFieldMinAndMax(idx_centerline);
	size_t numAlignments = max + 1;

	setCurrentOutScalarField(idx_centerline);

	if (numAlignments > 0) {
		BLUE_LOG(trace) << "Found " << QString::number(numAlignments).toStdString() << " centerlines.";
	} else {
		BLUE_LOG(warning) << "No centerlines found. Method returning with error.";
		return -2;
	}

	std::vector<std::vector<size_t>> alignments = std::vector<std::vector<size_t>>(numAlignments);
	for (int i = 0; i < numAlignments; i++)
		alignments[i] = std::vector<size_t>();

	BLUE_LOG(trace) << "Start collecting centerline points.";

	for_each([&](size_t i) {
		int idx = (int)getPointScalarValue(i);
		if (idx >= 0) {
			//CCVector3 &center = CCVector3(*getPoint(i));
			alignments[idx].push_back(i);
		}
	});

	BLUE_LOG(trace) << "Finished collecting centerline points.";
	std::vector<long> indices = std::vector<long>();

	// Everything besides writing all alignments is not yet implemented
	if (desc.centerlineIndex == -1) {
		for (int i = 0; i < numAlignments; i++)
			indices.push_back(i);

	} else {
		indices.push_back(desc.centerlineIndex);
	}

	QString date = QDateTime::currentDateTime().date().toString(Qt::ISODate);
	QString time = QDateTime::currentDateTime().time().toString(Qt::ISODate).replace(":", "-");
	QDir root = QDir(QDir::currentPath());
	QDir sub = QDir(QDir::currentPath() + "/" + date);

	int idx_chainage = getScalarFieldIndexByName("Chainage");
	setCurrentOutScalarField(idx_chainage);


	// Compute the bearing and write it to a file which we want to plot then.
	for (long idx : indices) {
		auto &alignment = alignments[idx];

		// Check if our alignment has enough points.
		long numBearingsAndChainages = ((alignment.size() - desc.numPointsForPCA) / desc.curvatureStepSize) + 1;
		long numCurvatures = numBearingsAndChainages - 1;
		long numCurvaturesSmoothed = numCurvatures - desc.numPointsForMeanCurvature;

		if (alignment.size() > desc.numPointsForPCA && numCurvaturesSmoothed > 0) {
			if (!root.exists(date))
				root.mkdir(date);

			if (!sub.exists(time))
				sub.mkdir(time);

			//std::sort(alignment.begin(), alignment.end(), [&](const CCVector3 &lhs, const CCVector3 &rhs) -> bool { return mainAxis_.dot(lhs) < mainAxis_.dot(rhs); });
			std::sort(alignment.begin(), alignment.end(), [&](const size_t &lhs, const size_t &rhs) -> bool { return getPointScalarValue(lhs) < getPointScalarValue(rhs); });

			BLUE_LOG(trace) << "Processing Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
			QFile file(sub.absolutePath() + "/" + time + "/" + "Alignment#" + QString::number(idx) + ".txt");
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
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
				auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end) -> Eigen::Matrix<double, 2, 1> {
					// Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX3d mat;
					mat.resize(end - start, 3);
					for (size_t i = start; i < end; i++) {
						auto pos = *getPoint(alignment[i]);
						mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
					}

					// Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1).topRows(2);
					return vec;
				};

#pragma omp for
				for (long i = desc.numPointsForPCA / 2; i < alignment.size() - (desc.numPointsForPCA / 2); i += desc.curvatureStepSize) {
					// Get the PCA axis and compute the bearing.
					auto axis = getPCA(alignment, i - (desc.numPointsForPCA / 2), i + (desc.numPointsForPCA / 2));
					axis.normalize();
					bearings[(i - (desc.numPointsForPCA / 2)) / desc.curvatureStepSize] = (std::acos(axis.dot(NORTH2D)) * 180.0 / M_PI);
					chainages[(i - (desc.numPointsForPCA / 2)) / desc.curvatureStepSize] = getPointScalarValue(alignment[i]);// mainAxis_.dot(alignment[i]);
					processedPoints += desc.curvatureStepSize;

					if (processedPoints >= pointsPerPercent) {
						percentageCompleted++;
						processedPoints = 0;

						if (tid == 0 && callback)
							callback->update(((100.0f * (float)(idx) / (float)alignments.size()) + (1.0f / (float)alignments.size()) * percentageCompleted)
							                 * ((float)alignments.size() / (float)indices.size()));
					}
				}
#pragma omp barrier

				int nJumps = 0;
				for (long i = 0; i < bearings.size() - 1; i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					bearings[i] += nJumps;
					if (std::abs(bearings[i] - (bearings[i + 1] + nJumps)) > 170)
						nJumps += 180;
				}

					// Without smoothing
#pragma omp for
				for (long i = 0; i < bearings.size() - 1; i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
					curvatures[i] = ((bearings[i + 1] - bearings[i]) / deltaChainage);
				}
#pragma omp barrier

				int startOffset = (int)std::floor((float)desc.numPointsForMeanCurvature / 2.0f);
				if (desc.numPointsForMeanCurvature % 2 == 0)
					startOffset++;
				int endOffset = std::ceil((float)desc.numPointsForMeanCurvature / 2.0f);

#pragma omp for
				for (long i = startOffset; i < curvatures.size() - endOffset - 1; i++) {
					double curvature = 0.0;

					for (int offset = -startOffset; offset < endOffset; offset++)
						curvature += curvatures[i + offset];

					curvaturesSmoothed[i - startOffset] = curvature / (double)desc.numPointsForMeanCurvature;
				}
#pragma omp barrier

#pragma omp single
				{
					for (size_t i = 0; i < curvaturesSmoothed.size() - (endOffset - startOffset) - 1; i++) {
						QString text = QString::number(chainages[i + startOffset], 'g',10)
						                 .append("\t")
						                 .append(QString::number(curvaturesSmoothed[i],'g', 10))
						                 .append("\t")
						                 .append(QString::number(bearings[i + startOffset], 'g', 10))
						                 .append("\n");
						file.write(text.toStdString().data());
					}
				}
			}

			// TODO:If the file is empty we delete it.
			file.close();
		} else {
			BLUE_LOG(trace) << "Skipping Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
		}
	}

	if (root.exists(date) && sub.exists(time)) {
		QFile file(sub.absolutePath() + "/" + time + "/parameters.txt");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return -1;
		QStringList text = {QString("Centerline computation"),
		                    QString("CenterlineDensity:" + QString::number(centerlineDescription_.centerlineDensity)),
		                    QString("MaxDistance:" + QString::number(centerlineDescription_.maxDistance)),
		                    QString("MinSegmentPoints:" + QString::number(centerlineDescription_.minSegmentPoints)),
		                    QString("MinSegmentLength:" + QString::number(centerlineDescription_.minSegmentLength)),
		                    QString("Curvature computation"),
		                    QString("NumPointsForPCA:" + QString::number(desc.numPointsForPCA)),
		                    QString("CurvatureStepSize:" + QString::number(desc.curvatureStepSize)),
		                    QString("NumPointsForMeanCurvature:" + QString::number(desc.numPointsForMeanCurvature))};
		file.write(text.join("\n").toStdString().data());
		file.close();
	}

	// Tell the callback that we're done.
	if (callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::Infrastructure::PointCloud::segmentRailways(buw::RailwaySegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if (idx_railway == -1)
		idx_railway = addScalarField("Railway");
	setCurrentInScalarField(idx_railway);

	for_each([&](size_t i) { setPointScalarValue(i, 0); });

	// Create a global list of all point pairs.
	std::vector<std::pair<size_t, size_t>> rails = std::vector<std::pair<size_t, size_t>>();
#pragma omp parallel for
	for (long i = 0; i < sections_.size(); i++) {
		auto pairs = sections_[i]->computePairs();

#pragma omp critical
		rails.insert(rails.end(), pairs.begin(), pairs.end());
	}

	// Reserve space for the centerpoints points and color them blue.
	this->reserve(this->size() + rails.size());
	this->reserveTheRGBTable();
	const ColorCompType blue[3] = {0, 0, 255};

	// For each pair, insert the point in the middle as centerpoints point.
	std::vector<CCVector3> centerpoints = std::vector<CCVector3>(rails.size());
	for (auto pair : rails) {
		CCVector3 start = *(getPoint(pair.first));
		CCVector3 end = *(getPoint(pair.second));
		CCVector3 center = 0.5f * (end + start);
		centerpoints.push_back(center);
	}

	// Sort the centerpoints along the main axis.
	std::sort(centerpoints.begin(), centerpoints.end(), [&](const CCVector3 &lhs, const CCVector3 &rhs) -> bool { return mainAxis_.dot(lhs) < mainAxis_.dot(rhs); });

	// Split the centerpoints into different rails and recognize different rails. Only store indices to save memory.
	std::vector<std::vector<size_t>> centerlines = std::vector<std::vector<size_t>>();
	centerlines.push_back(std::vector<size_t>());
	centerlines[0].push_back(0);

	auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) -> float { return (rhs - lhs).norm(); };

	float totalPoints = centerpoints.size();
	float processedPoints = 0;
	for (size_t i = 1; i < centerpoints.size(); i++) {
		// Store the point to be checked and whether we have inserted it or whether it is ambiguous or not.
		auto point = centerpoints[i];
		bool inserted = false;
		bool ambiguous = false;

		// Initialize the pair min with index and distance
		std::pair<size_t, float> min = std::pair<size_t, float>(centerlines.size(), LONG_MAX);

		// Iterate over all tracks.
		for (size_t ii = 0; ii < centerlines.size(); ii++) {
			auto &line = centerlines[ii];

			// Calculate the distance to the endpoint
			auto endpoint = centerpoints[line.back()];
			float distance = dist(point, endpoint);

			// If the distance is smaller than 20cm, we would add the point to this line.
			if (distance < 0.2f) {
				// If the point would also be inserted somewhere else, it is labeled as ambiguous and is dropped.
				if (inserted) {
					ambiguous = true;
					break;
				}
				// Otherwise the min distance is updated and inserted is set to true.
				else {
					inserted = true;
					if (distance < min.second)
						min = std::pair<size_t, float>(ii, distance);
				}
			}
		}

		// If the point is not ambiguous, we either insert it in the matching line or create a new one.
		if (!ambiguous) {
			if (inserted) {
				centerlines[min.first].push_back(i);
			} else {
				// If no matching line has been found, add a new one with this one as the starting point.
				centerlines.push_back(std::vector<size_t>());
				centerlines.back().push_back(i);
			}
		}

		// Check if we have a centerline which is very small (does not meet the minimum requirements as specified) and remove it to save some computation time.
		if (i % 10000 == 0) {
			for (size_t ii = 0; ii < centerlines.size(); ii++) {
				auto &line = centerlines[ii];

				// Calculate the distance to the endpoint
				auto endpoint = centerpoints[line.back()];
				float distance = std::fabsf(mainAxis_.dot(point) - mainAxis_.dot(endpoint));

				if (distance > 1.0f && (line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength)) {
					centerlines.erase(centerlines.begin() + ii);
				}
			}
		}

		if (callback)
			callback->update(100.0 * ++processedPoints / totalPoints);
	}

	// Tell the callback that we're done.
	if (callback)
		callback->stop();

	// Clear all lines having less then 100 points -> probably noise or something.
	auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool {
		return line.size() < desc.minSegmentPoints || (centerpoints[line.back()] - centerpoints[line.front()]).norm() < desc.minSegmentLength;
	});
	centerlines.erase(end, centerlines.end());

	// Add a scalar field for centerline so that we can delete them again when we do the reset.
	int idx = getScalarFieldIndexByName("Centerline");
	if (idx == -1)
		idx = addScalarField("Centerline");
	setCurrentInScalarField(idx);

	for_each([&](size_t i) { setPointScalarValue(i, -1); });

	std::vector<std::vector<CCVector3>> alignments = std::vector<std::vector<CCVector3>>(centerlines.size());

	if (false) {
		// Iterate over all segments and combine the centers of each projection section.
		for (size_t idx = 0; idx < centerlines.size(); idx++) {
			auto &line = centerlines[idx];
			int startIndex = 0, endIndex = 0;

			for (size_t i = 0; i < line.size() - 1; i++) {
				float length = std::fabsf(mainAxis_.dot(centerpoints[line[i + 1]]) - mainAxis_.dot(centerpoints[line[startIndex]]));
				if (length >= desc.centerlinePointDistance) {
					endIndex = i + 1;
					int numPoints = (endIndex - startIndex);
					CCVector3 &center = CCVector3(0, 0, 0);
					for (; startIndex < endIndex; startIndex++) {
						center += (centerpoints[line[startIndex]] / (float)numPoints);
					}

					alignments[idx].push_back(center);

					// this->addPoint(center);
					// this->addRGBColor(255 * (float)idx /(float) tracks.size(),0,255);
				}
			}
		}
	}

	if (true) {
		for (size_t idx = 0; idx < centerlines.size(); idx++) {
			auto &line = centerlines[idx];
			for (size_t i = 0; i < line.size() - 1; i++) {
				CCVector3 &center = centerpoints[line[i]];
				alignments[idx].push_back(center);
			}
		}
	}

	// Clear all alignments having less then points required for PCA to make visualization better.
	auto endAlignments = std::remove_if(alignments.begin(), alignments.end(), [&](std::vector<CCVector3> &line) -> bool { return line.size() <= desc.numPointsForPCA; });
	alignments.erase(endAlignments, alignments.end());

	// Only add centerpoints for alignments which are also exported.
	for (size_t idx = 0; idx < alignments.size(); idx++) {
		auto &segment = alignments[idx];
		for (auto point : segment) {
			this->addPoint(point);
			this->addRGBColor(255 * (float)idx / (float)alignments.size(), 0, 255);
			this->setPointScalarValue(this->size() - 1, idx);
		}
	}

	computeIndices();

	// Tell the callback that we're done.
	if (callback)
		callback->start();

	if (true) {
		// Compute the bearing and write it to a file which we want to plot then.
		for (long idx = 0; idx < alignments.size(); idx++) {
			auto &alignment = alignments[idx];
			BLUE_LOG(trace) << "Processing Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
			QFile file("Alignment#" + QString::number(idx) + ".txt");
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return -1;

			auto filestart = file.pos();

			// Implementation with offset by Stefan Markic.
#ifdef MARKIC
			if (false) {
				const size_t START = 100;
				const CCVector3 NORTH(0., 1., 0.);
				const int halbe = START / 2;

				if (alignment.size() > START) {
					std::vector<float> angles = std::vector<float>();

					for (int i = 0; i < halbe; i++)
						angles.push_back(0);

					for (size_t i = halbe; i < alignment.size() - halbe; i++) {
						CCVector3 axis = getPCA(alignment, i - halbe, i + halbe);
						axis.normalize();
						angles.push_back(axis.dot(NORTH) * 180.0 / M_PI);
					}

					for (int i = halbe; i < START; i++)
						angles.push_back(0);

					for (size_t i = halbe; i < angles.size() - halbe; i++) {
						float curvature = (angles[i + 1] - angles[i]) / std::fabsf(mainAxis_.dot(alignment[i + 1]) - mainAxis_.dot(alignment[i]));
						QString text = QString::number(i).append("\t").append(QString::number(curvature)).append("\t").append(QString::number(angles[i])).append("\n");
						file.write(text.toStdString().data());
					}
				}
			}
#endif

			// Implementation without offset but with other stuff by Helge Hecht.
			if (true) {
				// Initialize number of points to use for PCA and and the NORTH direction.
				const Eigen::Matrix<double, 3, 1> NORTH(0., 1., 0.);

				// Check if our alignment has enough points.
				if (alignment.size() > desc.numPointsForPCA) {
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
						auto getPCA = [](std::vector<CCVector3> alignment, size_t start, size_t end) -> Eigen::Matrix<double, 3, 1> {
							// Matrix which is capable of holding all points for PCA.
							Eigen::MatrixX3d mat;
							mat.resize(end - start, 3);
							for (size_t i = start; i < end; i++) {
								auto pos = alignment[i];
								mat.row(i - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
							}

							// Do PCA to find the largest eigenvector -> main axis.
							Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
							Eigen::MatrixXd cov = centered.adjoint() * centered;
							Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
							Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1);
							return vec;
						};

#pragma omp for
						for (long i = 0; i < alignment.size() - desc.numPointsForPCA; i += desc.curvatureStepSize) {
							// Get the PCA axis and compute the bearing.
							auto axis = getPCA(alignment, i, i + desc.numPointsForPCA);
							axis.normalize();
							bearings[i / desc.curvatureStepSize] = (axis.dot(NORTH) * 180.0 / M_PI);
							chainages[i / desc.curvatureStepSize] = mainAxis_.dot(alignment[i]);
							processedPoints += desc.curvatureStepSize;

							if (processedPoints >= pointsPerPercent) {
								percentageCompleted++;
								processedPoints = 0;

								if (tid == 0 && callback)
									callback->update((100.0f * (float)(idx) / (float)alignments.size()) + (1.0f / (float)alignments.size()) * percentageCompleted);
							}
						}
					}

						// Without smoothing
#pragma omp for
					for (long i = 0; i < bearings.size() - 1; i++) {
						// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
						double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
						curvatures[i] = ((bearings[i + 1] - bearings[i]) / deltaChainage);
					}

					int startOffset = std::floor(desc.numPointsForMeanCurvature / 2);
					if (desc.numPointsForMeanCurvature % 2 == 0)
						startOffset++;
					int endOffset = std::ceil(desc.numPointsForMeanCurvature / 2);

#pragma omp for
					for (long i = startOffset; i < curvatures.size() - endOffset; i++) {
						double curvature = 0.0;

						for (int offset = -startOffset; offset < endOffset; offset++)
							curvature += curvatures[i + offset];

						curvaturesSmoothed[i - startOffset] = curvature / (double)desc.numPointsForMeanCurvature;
					}

#pragma omp single
					{
						for (size_t i = 0; i < curvaturesSmoothed.size(); i++) {
							QString text = QString::number(chainages[i + startOffset])
							                 .append("\t")
							                 .append(QString::number(curvaturesSmoothed[i]))
							                 .append("\t")
							                 .append(QString::number(bearings[i + startOffset]))
							                 .append("\n");
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
	if (callback)
		callback->stop();

	return alignments.size();
}

int OpenInfraPlatform::Infrastructure::PointCloud::resetRailwaySegmentation() {
	// Reset the railway points color to white.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if (idx_railway == -1)
		return -1;

	setCurrentOutScalarField(idx_railway);
	const ColorCompType white[3] = {255, 255, 255};
	for_each([&](size_t i) {
		if (getPointScalarValue(i) != 0)
			setPointColor(i, white);
	});

	int idx_centerline = getScalarFieldIndexByName("Centerline");

	// Abort if we have no filtered points.
	if (idx_centerline == -1)
		return -1;

	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_centerline);
	float epsilon = -1 + 0.0001f;
	ccPointCloud *original = filterPointsByScalarValue(-1, epsilon);

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

void OpenInfraPlatform::Infrastructure::PointCloud::removeNotSegmentedPoints() {
	int idx_segmented = getScalarFieldIndexByName("Segmented");

	// Abort if we have no filtered points.
	if (idx_segmented == -1)
		return;

	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_segmented);
	float epsilon = 0.0001f;
	ccPointCloud *segmented = filterPointsByScalarValue(0, epsilon, true);

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

void OpenInfraPlatform::Infrastructure::PointCloud::removeFilteredPoints(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	if (callback)
		callback->start();

	int idx_filtered = getScalarFieldIndexByName("Filtered");

	// Abort if we have no filtered points.
	if (idx_filtered == -1)
		return;

	// Set the scalar field to read from and filter all points with non 0 value, choose 0.1f due to accuracy issues.
	setCurrentOutScalarField(idx_filtered);
	float epsilon = 0.0001f;
	ccPointCloud *filtered = filterPointsByScalarValue(0, epsilon);

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

	if (callback)
		callback->stop();
}

const CCVector3 OpenInfraPlatform::Infrastructure::PointCloud::getMainAxis() const {
	return mainAxis_;
}

const double OpenInfraPlatform::Infrastructure::PointCloud::getSectionLength() const {
	// If sections are initialized, return the length of the first section since all are equally long.
	if (sections_.size() > 0 && sections_[0]) {
		return sections_[0]->getLength();
	}
	else {
		return 0;
	}
}

const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> OpenInfraPlatform::Infrastructure::PointCloud::getIndices() const {
	return std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>>(remainingIndices_, filteredIndices_, segmentedIndices_);
}

buw::ReferenceCounted<buw::Octree> OpenInfraPlatform::Infrastructure::PointCloud::getDGMOctree() {
	if (!octree_)
		octree_ = std::make_shared<Octree>(this);
	return octree_;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeMainAxis() {
	BLUE_LOG(trace) << "Start computing main axis.";
	// Set the main axis as the eigenvector with the largest eigenvalue.
	mainAxis_ = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());
	BLUE_LOG(trace) << "Finished computing main axis.";
}
