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

#include "PointCloudSection.h"

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

buw::ReferenceCounted<buw::PointCloud> OpenInfraPlatform::PointCloudProcessing::PointCloud::FromFile(const char *filename) {
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
					pointCloud->addRGBColor(*color);
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

OpenInfraPlatform::PointCloudProcessing::PointCloud::PointCloud(PointCloud & other)
{
	// Copy base class attributes.
	other.cloneThis(this, false);

	// Copy indices.
	remainingIndices_ = other.remainingIndices_;
	filteredIndices_ = other.filteredIndices_;
	segmentedIndices_ = other.segmentedIndices_;

	// Copy sections.
	sections_ = std::vector<buw::ReferenceCounted<PointCloudSection>>();
	if(other.sections_.size() > 0) {
		for(auto elem : other.sections_) {
			sections_.push_back(buw::makeReferenceCounted<PointCloudSection>(*elem));
		}
	}

	// Copy other remaining members.
	grid_ = other.grid_;
	mainAxis_ = other.mainAxis_;
	bHasPairs_ = other.bHasPairs_;
	bHasCenterline_ = other.bHasCenterline_;
	octree_ = buw::makeReferenceCounted<Octree>(this);
}

OpenInfraPlatform::PointCloudProcessing::PointCloud::~PointCloud() {

	this->deleteAllScalarFields();

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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::add(const buw::ReferenceCounted<ccPointCloud>& other, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback, ColorCompType* color)
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
		this->setPointColor(startIndex + i, ccColor::Rgb(color));
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

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {

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

	for_each([&](size_t i) { setPointColor(i, ccColor::Rgb(black)); });

#pragma omp parallel for
	for(long i = 0; i < sections_.size(); i++) {
		for(long ii = 0; ii < sections_[i]->size(); ii++) {
			setPointColor(sections_[i]->getPointGlobalIndex(ii), ccColor::Rgb(white));
		}
	}

	if(callback)
		callback->stop();
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeChainage(ChainageComputationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	switch(desc.base) {
	case OpenInfraPlatform::PointCloudProcessing::Enums::eChainageComputationBase::Octree:
		this->computeChainageOctreeBased(callback);
		break;
	case OpenInfraPlatform::PointCloudProcessing::Enums::eChainageComputationBase::Grid:
		this->computeChainageGridBased(desc.interpolation, callback);
		break;
	default:
		BLUE_LOG(error) << "No base method for chainage computation selected.";
	}

	if(desc.bUseSmoothing) {
		int idx_chainage = getScalarFieldIndexByName("Chainage");
		setCurrentOutScalarField(idx_chainage);
		CCLib::ScalarFieldTools::applyScalarFieldGaussianFilter(desc.sigma, this, desc.sigmaSF, callback.get(), octree_.get());
	}
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeChainageOctreeBased(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
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
}


void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeChainageGridBased(OpenInfraPlatform::PointCloudProcessing::Enums::eChainageComputationInterpolationMethod method, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	//TODO: Use different and implement different interpolation methods.
	if(callback)
		callback->start();	

	//TODO: Insert map into a vector, sort it and then use this.
	std::vector<std::pair<int, int>> grid = std::vector<std::pair<int, int>>();
	
	for(auto &it : grid_)
		grid.push_back(it.first);

	// Sort grid cells along main axis.
	std::sort(grid.begin(), grid.end(), [&](std::pair<int, int> &lhs, std::pair<int, int> &rhs)->bool {		
		return mainAxis_.dot(std::get<1>(grid_[lhs])) < mainAxis_.dot(std::get<1>(grid_[rhs]));
	});

	if(false) {
		for(int i = 1; i < grid.size(); i++) {
			auto &start = grid.begin();
			advance(start, i - 1);

			auto axis = std::get<2>(grid_[*start]);
			auto center = std::get<1>(grid_[*start]);

			std::map<std::pair<int, int>, float> indexedProjections;

#pragma omp parallel for
			for(long ii = i; ii < grid.size(); ii++) {
				auto &pair = grid.begin();
				advance(pair, ii);

				auto pos = std::get<1>(grid_[*pair]) - center;
				auto value = axis.dot(CCVector2(pos.x, pos.y));
				indexedProjections.insert({ *pair, value });
			}

			//std::for_each(grid.begin() + i, grid.end(), [&](std::pair<int, int> &pair) {
			//	auto pos = std::get<1>(grid_[pair]) - center;
			//	auto value = axis.dot(CCVector2(pos.x, pos.y));
			//	indexedProjections.insert({ pair, value });
			//});

			//auto compare = [&](std::pair<int, int> &lhs, std::pair<int, int> &rhs)->bool {
			//	auto axis = std::get<2>(grid_[*start]);
			//	auto center = std::get<1>(grid_[*start]);
			//	auto lhsCenter = std::get<1>(grid_[lhs]) - center;
			//	auto rhsCenter = std::get<1>(grid_[rhs]) - center;
			//	return axis.dot(CCVector2(lhsCenter.x, lhsCenter.y)) < axis.dot(CCVector2(rhsCenter.x, rhsCenter.y));
			//};


			std::sort(grid.begin() + i, grid.end(), [&](std::pair<int, int> &lhs, std::pair<int, int> &rhs)->bool {
				return indexedProjections[lhs] < indexedProjections[rhs];
			});

			if(callback) {
				callback->update(100.0f * (float)((float)i / (float)grid.size()));
			}
		}

		// Reset the callback.
		if(callback)
			callback->update(0);
	}

	auto barycentric3D = [](CCVector3 p, CCVector3 a, CCVector3 b, CCVector3 c) ->std::tuple<float, float, float>
	{
		CCVector3 v0 = b - a, v1 = c - a, v2 = p - a;
		float d00 = v0.dot(v0);
		float d01 = v0.dot(v1);
		float d11 = v1.dot(v1);
		float d20 = v2.dot(v0);
		float d21 = v2.dot(v1);
		float denom = d00 * d11 - d01 * d01;
		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
		return { u,v,w };
	};

	auto barycentric2D = [](CCVector2 p, CCVector2 a, CCVector2 b, CCVector2 c) ->std::tuple<float, float, float>
	{
		CCVector2 v0 = b - a, v1 = c - a, v2 = p - a;
		float d00 = v0.dot(v0);
		float d01 = v0.dot(v1);
		float d11 = v1.dot(v1);
		float d20 = v2.dot(v0);
		float d21 = v2.dot(v1);
		float denom = d00 * d11 - d01 * d01;
		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
		return { u,v,w };
	};

	// Init Chainage Scalar Field.
	int idx_chainage = getScalarFieldIndexByName("Chainage");
	if(idx_chainage == -1)
		idx_chainage = addScalarField("Chainage");

	setCurrentInScalarField(idx_chainage);

	// Initialize origin and initial chainage to move from.
	auto origin = CCVector3(0, 0, 0);
	float chainage = 0.0f;

	long numCells = grid.size();
	long numCellsPerPercent = std::max(1, (int) numCells / 100);
	long processedCells = 0;
	float percentageCompleted = 0.0f;

	if(callback)
		callback->update(percentageCompleted);

	// Iterate over all cells in the grid
	for(int i = 0; i < grid.size(); i++) {

		// Move to the correct position in the container
		auto &cell = grid.begin();
		advance(cell, i);

		// Get the indices of all points in the cell
		auto indices = std::get<0>(grid_[*cell]);

		// Iterate over all points in the grid in parallel
#pragma omp parallel for shared(origin, chainage, method)
		for(long ii = 0; ii < indices.size(); ii++) {

			// Get the current index and the corresponding point.
			auto idx = indices[ii];
			CCVector3 point3D = *getPoint(idx);

			// Lambda to compute chainage without interpolation.
			auto computeChainageWithoutInterpolation = [&]() {

				// Get the shifted 2D point.
				CCVector2 pointShifted2D = CCVector2(point3D.x - origin.x, point3D.y - origin.y);

				// Get the grid cells axis.
				auto axis = std::get<2>(grid_[*cell]);

				auto localChainage = axis.dot(pointShifted2D);
#pragma omp critical
				setPointScalarValue(idx, chainage + localChainage);
			};

			// Lambda to compute chainage with linear interpolation.
			auto computeChainageWithLinearInterpolation = [&]() {
				// Get the max floating point value and initialize the nearestNeighbour as (0,0) and fmax as distance.
				float fmax = std::numeric_limits<float>::max();
				std::pair<std::pair<int, int>, float> nearestNeighbour = { { 0,0 }, fmax };

				// Iterate over the neighbouring cells in x and y dimension.
				for(int dx = -1; dx < 2; dx += 2) {
					for(int dy = -1; dy < 2; dy += 2) {

						// Get the neighbouring cell index as "current + dx + dy".
						auto cellIdx = std::pair<int, int>(cell->first + dx, cell->second + dy);

						// Check if the cell exists in the grid.
						if(grid_.count(cellIdx) > 0) {

							// Distance from the point to the neighbouring cell center.
							float dist = (std::get<1>(grid_[cellIdx]) - point3D).norm();

							// Insert the distance among the neighbouring distances.
							if(dist < nearestNeighbour.second) {
								nearestNeighbour = { cellIdx,dist };
							}
						}
					}
				}

				if(!(nearestNeighbour.first == std::pair<int, int>(0, 0) && nearestNeighbour.second == fmax)) {
					// Compute center to point and center to neighbour to interpolate the chainage value.
					auto cellCenter = std::get<1>(grid_[*cell]);
					auto neighbouringCellCenter = std::get<1>(grid_[nearestNeighbour.first]);

					CCVector3 centerToPoint = point3D - cellCenter;
					CCVector3 centerToNeighbour = neighbouringCellCenter - cellCenter;

					float scalarProjection = centerToPoint.dot(centerToNeighbour / centerToNeighbour.norm());
					float w0 = scalarProjection / centerToNeighbour.norm();

					// Get a 2D version of the point having only X and Y coordinate.
					CCVector2 pointShifted2D = CCVector2(point3D.x - origin.x, point3D.y - origin.y);
					float w1 = 1.0f - w0;
					auto a0 = std::get<2>(grid_[nearestNeighbour.first]);
					auto a1 = std::get<2>(grid_[*cell]);
					auto axis = a0 * w0 + a1 * w1;
					auto localChainage = axis.dot(pointShifted2D);
#pragma omp critical
					setPointScalarValue(idx, chainage + localChainage);
				}
				else {
					//BLUE_LOG(warning) << "(" << idx << "): Linear interpolation failed, switching to no interpolation.";
					computeChainageWithoutInterpolation();
				}
			};

			// Lambda to compute chainage with barycentric interpolation.
			auto computeChainageWithBarycentricInterpolation = [&]() {
				// Get the max floating point value and initialize the nearestNeighbour grids as (0,0) and fmax as distance.
				float fmax = std::numeric_limits<float>::max();
				std::pair<std::pair<int, int>, float> nearestNeighbours[3] = { { { 0,0 }, fmax }, { { 0,0 }, fmax } , { { 0,0 }, fmax } };

				// Iterate over the neighbouring cells in x and y dimension.
				for(int dx = -1; dx < 2; dx++) {
					for(int dy = -1; dy < 2; dy++) {

						// Get the neighbouring cell index as "current + dx + dy".
						auto cellIdx = std::pair<int, int>(cell->first + dx, cell->second + dy);

						// Check if the cell exists in the grid.
						if(grid_.count(cellIdx) > 0) {

							// Distance from the point to the neighbouring cell center.
							float dist = (std::get<1>(grid_[cellIdx]) - point3D).norm();

							// Insert the distance among the neighbouring distances.
							if(dist < nearestNeighbours[0].second) {
								nearestNeighbours[2] = nearestNeighbours[1];
								nearestNeighbours[1] = nearestNeighbours[0];
								nearestNeighbours[0] = { cellIdx,dist };
							}
							else if(dist < nearestNeighbours[1].second) {
								nearestNeighbours[2] = nearestNeighbours[1];
								nearestNeighbours[1] = { cellIdx,dist };
							}
							else if(dist < nearestNeighbours[2].second) {
								nearestNeighbours[2] = { cellIdx,dist };
							}
						}
					}
				}

				bool hasSufficientNeighbours = true;
				for(auto neighbour : nearestNeighbours) {
					if(neighbour.first == std::pair<int, int>(0, 0) && neighbour.second == fmax) {
						hasSufficientNeighbours = false;
					}
				}

				if(hasSufficientNeighbours) {

					// Initialize the weights for barycentric3D interpolation w0, w1 and w2.
					float w0, w1, w2;

					// Get the points to interpolate in between into c0,c1 and c2.
					CCVector3 c0 = std::get<1>(grid_[nearestNeighbours[0].first]);
					CCVector3 c1 = std::get<1>(grid_[nearestNeighbours[1].first]);
					CCVector3 c2 = std::get<1>(grid_[nearestNeighbours[2].first]);

					// Get the 2D versions of c points.
					CCVector2 v0 = CCVector2(c0.x, c0.y);
					CCVector2 v1 = CCVector2(c1.x, c1.y);
					CCVector2 v2 = CCVector2(c2.x, c2.y);

					// Get a 2D version of the point having only X and Y coordinate.
					CCVector2 point2D = CCVector2(point3D.x, point3D.y);

					// Compute the barycentric3D interpolation for the point.
					std::tie<float, float, float>(w0, w1, w2) = barycentric2D(point2D, v0, v1, v2);

					// Get a 2D version of the point having only X and Y coordinate.
					CCVector2 pointShifted2D = CCVector2(point3D.x - origin.x, point3D.y - origin.y);


					// Get the neighbouring cell axes.
					auto a0 = std::get<2>(grid_[nearestNeighbours[0].first]);
					auto a1 = std::get<2>(grid_[nearestNeighbours[1].first]);
					auto a2 = std::get<2>(grid_[nearestNeighbours[2].first]);

					// Get the global axis as interpolated axis with the barycentric weights.
					auto axis = (a0 * w0) + (a1 * w1) + (a2 * w2);

					// Compute the chainage projection of the 2D point along the interpolated axes.
					auto localChainage = axis.dot(pointShifted2D);

#pragma omp critical
					setPointScalarValue(idx, chainage + localChainage);
				}
				else {
					//BLUE_LOG(warning) << "(" << idx << "): Barycentric interpolation failed, switching to linear interpolation.";
					computeChainageWithLinearInterpolation();
				}
			};

			if(method == Enums::eChainageComputationInterpolationMethod::Barycentric) {
				computeChainageWithBarycentricInterpolation();
			}
			else if(method == Enums::eChainageComputationInterpolationMethod::Linear) {
				computeChainageWithLinearInterpolation();
			}
			else {
				computeChainageWithoutInterpolation();
			}
		}

		auto shift = std::get<1>(grid_[*cell]) - origin;
		origin += shift;
		chainage += std::get<2>(grid_[*cell]).dot(CCVector2(shift.x, shift.y));

		processedCells++;
		if(callback && processedCells == numCellsPerPercent) {
			percentageCompleted++;
			processedCells = 0;
			callback->update(percentageCompleted);
		}
	}

	if(callback)
		callback->stop();
}

std::vector<std::pair<CCVector3, ScalarType>> OpenInfraPlatform::PointCloudProcessing::PointCloud::getAllPointsAndScalarFieldValue(int index)
{
	setCurrentOutScalarField(index);
	std::vector<std::pair<CCVector3, ScalarType>> pointsAndScalarValues;
	for_each([&](size_t i) {
		pointsAndScalarValues.push_back(std::pair<CCVector3, ScalarType>(CCVector3(*getPoint(i)), getPointScalarValue(i)));
	});

	return pointsAndScalarValues;
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeGrid(buw::GridComputationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	grid_.clear();
	grid_ = std::map<std::pair<int, int>, std::tuple<std::vector<uint32_t>,CCVector3, CCVector2>>();

	// Sort all points into the grid given their position.
	for_each([&](size_t i) {
		auto pos = getPoint(i);
		std::pair<int, int> key = std::pair<int, int>((int)(pos->x / desc.size), (int)(pos->y / desc.size));
		if(grid_.count(key) == 0) {
			std::tuple<std::vector<uint32_t>, CCVector3, CCVector2> value = { std::vector<uint32_t>(), CCVector3(0,0,0), CCVector2(0,0) };
			grid_.insert({ key, value });
		}
		
		std::get<0>(grid_[key]).push_back(i);		
	});

	// Lambda function which computes the center of mass of the given indices.
	auto computeCenter = [&](std::vector<uint32_t> indices)->CCVector3 {
		CCVector3 center = CCVector3(0, 0, 0);
		for(auto idx : indices) {
			center += ((*getPoint(idx)) / (float)indices.size());
		}
		return center;
	};

	// Find the best level for extraction given kernel radius.
	unsigned char level = octree_->findBestLevelForAGivenNeighbourhoodSizeExtraction(desc.kernelRadius);
	int tid = 0;

	if(callback)
		callback->start();

#pragma omp parallel private(tid) shared(level, desc)
	{
		// Setup variables for progress callback.
		tid = omp_get_thread_num();
		long numCells = grid_.size();
		long numCellsPerThread = numCells / omp_get_num_threads();
		long numCellsPerPercent = numCellsPerThread / 100;

		int percentageCompleted = 0;
		long processedCells = 0;

		// Clone the octree for parallelization.
		auto octree = buw::Octree(*octree_);

#pragma omp for schedule(dynamic, 20)
		for(int i = 0; i < grid_.size(); i++) {

			// Move the iterator to the cell processed by this thread.
			auto &cell = grid_.begin();
			advance(cell, i);

			//Number of points in the cell.
			long cellSize = std::get<0>(cell->second).size();

			if(cellSize > 0) {
				// Center of mass of the cell.
				CCVector3 center = computeCenter(std::get<0>(cell->second));
				std::get<1>(cell->second) = center;

				// Points in spherical neighbourhood around the center.
				std::vector<CCLib::DgmOctree::PointDescriptor> neighbours;
				long numPoints = octree.getPointsInSphericalNeighbourhood(center, desc.kernelRadius, neighbours, level);

				// Lambda to compute PCA of all points in the spherical neighbourhood.
				auto getPCA = [&]() -> CCVector2 {
					Eigen::MatrixX2d mat;
					mat.resize(numPoints, 2);
					for(size_t i = 0; i < numPoints; i++) {
						auto pos = *neighbours[i].point;
						mat.row(i) = Eigen::Vector2d(pos.x, pos.y);
					}

					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1).normalized();

					return CCVector2(vec.x(), vec.y());
				};

				// Store the axis in the grid.
				std::get<2>(cell->second) = getPCA();
			}

			processedCells++;

			if(tid == 0 && callback) {
				if(processedCells == numCellsPerPercent) {
					processedCells = 0;
					percentageCompleted++;

					callback->update(percentageCompleted);
				}
			}
		}
	}

	if(callback)
		callback->stop();
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::resetGrid()
{
	if(!grid_.empty())
		grid_.clear();
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::alignOnMainAxis() {
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::flagDuplicatePoints(const double minDistance, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
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

	return CCLib::GeometricalAnalysisTools::FlagDuplicatePoints(this, minDistance, callback.get(), octree_.get());
}

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyLocalDensityFilter(LocalDensityFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	int err = 0;

	// Compute the density, either for the volume or the sections.
	if (desc.dim == Enums::ePointCloudFilterDimension::Volume3D) {
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyDuplicateFilter(DuplicateFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	int err = 0;

	// Call flagDuplicatePoints on this or on all sections.
	if (desc.dim == Enums::ePointCloudFilterDimension::Volume3D) {
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyPositionFilter(const buw::PositionFilterDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyRelativeHeightWithGridFilter(const buw::RelativeHeightFilterDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{

	const double lowerBound = desc.lowerBound;
	const double upperBound = desc.upperBound;

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

	for(auto &gridCell : grid_) {
		auto cell = std::get<0>(gridCell.second);
		if(cell.size() > 0) {
			std::sort(cell.begin(), cell.end(), [&](const size_t &lhs, const size_t &rhs)->bool {
				return getPoint(lhs)->z < getPoint(rhs)->z;
			});

			auto center = getPoint(cell[cell.size() / 2]);
			std::for_each(cell.begin(), cell.end(), [&](const size_t &i) {
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

	computeIndices();

	if(callback)
		callback->stop();

	return 0;
}

int OpenInfraPlatform::PointCloudProcessing::PointCloud::resetPositionFilter() {
	deleteScalarField(getScalarFieldIndexByName("Coord. X"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Y"));
	deleteScalarField(getScalarFieldIndexByName("Coord. Z"));

	computeIndices();
	return 0;
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::resetScalarField(const char *name) {
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric,
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
	//return CCLib::GeometricalAnalysisTools::computeLocalDensity(this, metric, kernelRadius, callback ? callback.get() : nullptr, octree_ ? octree_.get() : nullptr);
	return CCLib::GeometricalAnalysisTools::ComputeCharactersitic(CCLib::GeometricalAnalysisTools::GeomCharacteristic::LocalDensity, metric, this, kernelRadius, callback ? callback.get() : nullptr, octree_ ? octree_.get() : nullptr);

}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::init() {
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

	grid_ = std::map<std::pair<int, int>, std::tuple<std::vector<uint32_t>, CCVector3, CCVector2>>();

	computeMainAxis();
	// alignOnMainAxis();
	//// Main axis has changed!
	// computeMainAxis();

	octree_ = buw::makeReferenceCounted<buw::Octree>(this);
	octree_->build();

	//computeChainageGridBased();
	//applyRelativeHeightWithGridFilter(0.5, 0.5, nullptr);
	//computeIndices();
}

std::vector<buw::ReferenceCounted<buw::PointCloudSection>> OpenInfraPlatform::PointCloudProcessing::PointCloud::getSections() {
	return sections_;
}

buw::ReferenceCounted<CCLib::ReferenceCloud> OpenInfraPlatform::PointCloudProcessing::PointCloud::subsample(size_t size) {
	BLUE_LOG(fatal) << "This function should never be called right now.";
	return buw::ReferenceCounted<CCLib::ReferenceCloud>(
	  CCLib::CloudSamplingTools::subsampleCloudWithOctree(this, size, CCLib::CloudSamplingTools::SUBSAMPLING_CELL_METHOD::NEAREST_POINT_TO_CELL_CENTER, nullptr, octree_.get()));
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeIndices() {
	// Clear the index buffers.
	if(!remainingIndices_.empty())
		remainingIndices_.clear();

	if(!filteredIndices_.empty())
		filteredIndices_.clear();

	int idx_filtered = getScalarFieldIndexByName("Filtered");
	if (idx_filtered == -1)
		idx_filtered = addScalarField("Filtered");

	setCurrentInScalarField(idx_filtered);

	// Get the duplicate scalar field.
	int idx_duplicate = getScalarFieldIndexByName("Duplicate");	

	// Get the density scalar field
	int idx_density = getScalarFieldIndexByName("Density");	

	// Get the coordinate filter scalar fields.
	int idx_coordX = getScalarFieldIndexByName("Coord. X");
	int idx_coordY = getScalarFieldIndexByName("Coord. Y");
	int idx_coordZ = getScalarFieldIndexByName("Coord. Z");

	// For each point, check it's Density and Duplicate field and if one of them is true, filter the point.
	//for_each([&, idx_duplicate, idx_density, idx_coordX, idx_coordY, idx_coordZ](size_t i) {
	//	ScalarType filtered = 0;
	//	if (idx_duplicate != -1) {
	//		setCurrentOutScalarField(idx_duplicate);
	//		filtered += getPointScalarValue(i);
	//	}
	//
	//	if (idx_density != -1) {
	//		setCurrentOutScalarField(idx_density);
	//		filtered += getPointScalarValue(i);
	//	}
	//
	//	if (idx_coordX != -1) {
	//		setCurrentOutScalarField(idx_coordX);
	//		filtered += getPointScalarValue(i);
	//	}
	//
	//	if (idx_coordY != -1) {
	//		setCurrentOutScalarField(idx_coordY);
	//		filtered += getPointScalarValue(i);
	//	}
	//
	//	if (idx_coordZ != -1) {
	//		setCurrentOutScalarField(idx_coordZ);
	//		filtered += getPointScalarValue(i);
	//	}
	//
	//	setPointScalarValue(i, filtered);
	//
	//	if (filtered > 0) {
	//		filteredIndices_.push_back(i);
	//	} else {
	//		remainingIndices_.push_back(i);
	//	}
	//});

	for(size_t i = 0; i < this->size(); i++) {
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
	}

	// Clear the segmented indices buffer.
	if(!segmentedIndices_.empty())
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

	BLUE_LOG(trace) << "Done.";

}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computePairs(const buw::PairComputationDescription &desc, std::vector<std::pair<size_t, size_t>> &o_pairs, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	if(bHasPairs_) {
		resetPairs();
	}

	if(sections_.size() > 0) {
		BLUE_LOG(trace) << "Computing pairs.";

		// If we have a callback, call start to init the GUI.
		if(callback) {
			callback->start();
			callback->setMethodTitle("Computing pairs...");
		}

		// Add a scalar field for railway and encode the left/right railway index as -1 and 1.
		int idx = getScalarFieldIndexByName("Railway");
		if(idx == -1)
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
			for(long i = 0; i < sections_.size() - 1; i++) {
				if(sections_[i]) {
					// Insert all pairs in our local vector.
					auto result = sections_[i + 1] ? sections_[i]->computePairs(desc, sections_[i + 1]) : sections_[i]->computePairs(desc);
					if(result.size() > 0) {
						pairs.insert(pairs.end(), result.begin(), result.end());
					}
				}
				else {
					BLUE_LOG(warning) << "Null section detected. Nr: " << i;
				}

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
//#pragma omp critical
			{
				if(pairs.size() > 0) {
					o_pairs.insert(o_pairs.end(), pairs.begin(), pairs.end());
				}
				else {
					// BLUE_LOG(info) << "No pairs by thread #" << omp_get_thread_num() << " detected.";
				}
			}
		}

		// Stop our callback.
		if(callback)
			callback->stop();

		BLUE_LOG(trace) << "Done.";
		bHasPairs_ = true;
	}
	else {
		BLUE_LOG(warning) << "Aborting. No sections found.";
	}
}

std::vector<buw::ReferenceCounted<CCLib::ReferenceCloud>> OpenInfraPlatform::PointCloudProcessing::PointCloud::extractConnectedComponents(ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
{
	// Vector that holds the individual components.
	std::vector<buw::ReferenceCounted<CCLib::ReferenceCloud>> components;

	// TODO
	return components;
}

const std::tuple<ScalarType, ScalarType> OpenInfraPlatform::PointCloudProcessing::PointCloud::getScalarFieldMinAndMax(int idx) const {
	// Get the min and max for the scalar field and store it in the returned tuple.
	CCLib::ScalarField *field = getScalarField(idx);
	field->computeMinAndMax();
	return std::tuple<ScalarType, ScalarType>(field->getMin(), field->getMax());
}

const std::tuple<size_t, size_t> OpenInfraPlatform::PointCloudProcessing::PointCloud::getScalarFieldMinAndMaxIndex(int idx)
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyPercentilesSegmentation(buw::PercentileSegmentationDescription desc,
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyPercentilesSegmentationHP(const buw::PercentileSegmentationDescription &desc,
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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyPercentilesOnGridSegmentation(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
	// If we have a callback, call start to init the GUI.
	if (callback)
		callback->start();

	computeGrid({});

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

	for (auto gridCell : grid_) {
		auto cell = std::get<0>(gridCell.second);
		auto end = std::remove_if(cell.begin(), cell.end(), isFilteredPoint);
		cell.erase(end, cell.end());
		int numPoints = cell.size();

		std::sort(cell.begin(), cell.end(), [&](const uint32_t &lhs, const uint32_t &rhs) -> bool { return getPoint(lhs)->z < getPoint(rhs)->z; });

		// Calculate the 98 percentile as the index of the 98th % point after sorting in ascending order, same for the 10th % point.
		int idx98 = (int)std::floor(0.98 * numPoints);
		int idx10 = (int)std::floor(0.1 * numPoints);
		float percentile_98 = getPoint(cell[idx98])->z;
		float percentile_10 = getPoint(cell[idx10])->z;

		// Calculate the absolute difference between the percentiles and if it is larger than 10cm segment the point as rail point.
		float diff = std::fabsf(percentile_10 - percentile_98);
		if (diff >= 0.1f) {
			std::set<uint32_t> indices;
			for (int i = idx98; i < numPoints; i++) {
				CCLib::DgmOctree::NeighboursSet neighbours = CCLib::DgmOctree::NeighboursSet();
				int numNeighbours = octree_->getPointsInSphericalNeighbourhood(*getPoint(cell[i]), 0.1f, neighbours, level);

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

int OpenInfraPlatform::PointCloudProcessing::PointCloud::applyRateOfChangeSegmentation(RateOfChangeSegmentationDescription desc,
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


int OpenInfraPlatform::PointCloudProcessing::PointCloud::computeCenterlines(const buw::CenterlineComputationDescription &desc,
                                                                      buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {	

	// Vector holding the rail point pairs (left and right track).
	std::vector<std::pair<size_t, size_t>> pointPairs = std::vector<std::pair<size_t, size_t>>();

	// If we have pairs, get them, otherwise compute them.
	if(bHasPairs_) {
		for(auto &section : sections_) {
			auto pairs = section->getPairs();
			if(!pairs.empty()) {
				pointPairs.insert(pointPairs.end(), pairs.begin(), pairs.end());
			}
		}
	}
	
	// If we couldn't find pairs we abort and return -5;
	bool success = !pointPairs.empty();
	if(!success) {
		BLUE_LOG(warning) << "No pairs found. Aborting.";
		return -5;
	}

	// Create a Point Cloud for the centerline points.
	buw::ReferenceCounted<PointCloud> centerpointsPointCloud = buw::makeReferenceCounted<PointCloud>();

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
	centerpointsPointCloud->getCurrentInScalarField()->resize(pointPairs.size());

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
		ScalarType chainage = 0.5f * (getPointScalarValue(pair.first) + getPointScalarValue(pair.second));
		CCVector3 center = 0.5f * (end + start);

		centerpointsPointCloud->addPoint(center);
		centerpointsPointCloud->setPointScalarValue(i, chainage);
	}

	// Defaults to false.
	bool useSubsampling = false;

	if(useSubsampling) {
		//Subsample the centerpoints cloud 10 times to include more randomnness and therefore remove patterns.
		buw::ReferenceCounted<PointCloud> subsampled = buw::makeReferenceCounted<PointCloud>();
		subsampled->enableScalarField();
		int idxSS_chainage = subsampled->addScalarField("Chainage");
		subsampled->setCurrentInScalarField(idxSS_chainage);
		centerpointsPointCloud->setCurrentOutScalarField(idxCPC_chainage);

		int numIterations = 1000;
		for(int i = 0; i < numIterations; i++) {
			auto sampledPoints = buw::ReferenceCounted<CCLib::ReferenceCloud>(CCLib::CloudSamplingTools::subsampleCloudRandomly(centerpointsPointCloud.get(), (int)((1.0 / numIterations) * centerpointsPointCloud->size()), nullptr));
			int startIndex = subsampled->size();
			subsampled->reserve(subsampled->size() + sampledPoints->size());

			for(int idx = 0; idx < sampledPoints->size(); idx++) {
				subsampled->addPoint(*sampledPoints->getPoint(idx));
				subsampled->setPointScalarValue(startIndex + idx, sampledPoints->getPointScalarValue(idx));
			}
		}

		centerpointsPointCloud.swap(subsampled);
		idxCPC_chainage = idxSS_chainage;
	}

	centerpointsPointCloud->getDGMOctree()->build(callback.get());
	centerpointsPointCloud->computeIndices();

	

	if(desc.filterDuplicates) {
		// Remove points closer than 1mm to avoid "black holes" of insane density.
		buw::DuplicateFilterDescription dfd;
		dfd.dim = Enums::ePointCloudFilterDimension::Volume3D;
		dfd.minDistance = desc.duplicateDistance;
		centerpointsPointCloud->applyDuplicateFilter(dfd, callback);
		centerpointsPointCloud->computeIndices();
		centerpointsPointCloud->removeFilteredPoints(callback);
		centerpointsPointCloud->computeIndices();
		centerpointsPointCloud->getDGMOctree()->clear();
		centerpointsPointCloud->getDGMOctree()->build(callback.get());
	}

	if(desc.filterDensity) {
		// Remove centerline points which are outliers.	
		buw::LocalDensityFilterDescription ldfd;
		ldfd.density = CCLib::GeometricalAnalysisTools::DENSITY_KNN;
		ldfd.dim = Enums::ePointCloudFilterDimension::Volume3D;
		ldfd.kernelRadius = desc.densityKernelRadius;
		ldfd.minThreshold = desc.densityThreshold;
		centerpointsPointCloud->applyLocalDensityFilter(ldfd, callback);
		centerpointsPointCloud->computeIndices();
		centerpointsPointCloud->removeFilteredPoints(callback);
		centerpointsPointCloud->computeIndices();
		centerpointsPointCloud->getDGMOctree()->clear();
		centerpointsPointCloud->getDGMOctree()->build(callback.get());
	}

	auto centerpoints = centerpointsPointCloud->getAllPointsAndScalarFieldValue(idxCPC_chainage);
	
	//centerpointsPointCloud = nullptr;
		
	int tid = 0;
	
	auto sortCenterpointsIntoCenterlines = [&](const std::vector<std::pair<CCVector3, ScalarType>> &centerpoints, std::vector<std::vector<size_t>> &centerlines,
	                                           buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr) {
		centerlines.push_back(std::vector<size_t>());
		centerlines[0].push_back(0);

		auto dist = [](const CCVector3 &lhs, const CCVector3 &rhs) -> float { return (rhs - lhs).norm(); };

		// Start our callback if we have one.
		if(callback) {
			callback->start();
			callback->setMethodTitle("Sorting centerpoints into centerlines...");
		}

		// Initialize variables for callback update.
		float totalPoints = centerpoints.size();
		int pointsPerPercent = totalPoints / 100;
		float processedPoints = 0;
		int percentageCompleted = 0;

		for(size_t i = 1; i < centerpoints.size(); i++) {
			// Store the point to be checked and whether we have inserted it or whether it is ambiguous or not.
			auto point = centerpoints[i].first;
			auto chainage = centerpoints[i].second;

			bool inserted = false;
			bool discarded = false;						

			
				// Iterate over all tracks.
			for(long ii = 0; ii < centerlines.size(); ii++) {
				auto &line = centerlines[ii];

				// Calculate the distance to the endpoint
				for(int offset = 1; offset < 100 && offset <= line.size(); offset++) {
					auto endpoint = centerpoints[line[line.size() - offset]].first;
					float endpointChainage = centerpoints[line[line.size() - offset]].second;
					float distance = dist(point, endpoint);

					// Compute the ratio between chainage change and distance.
					float dChainage = chainage - endpointChainage;
					float ratio = dChainage / distance;
					if(distance < desc.sortingFarDistance) {
						if(ratio > desc.sortingFarRatio || (distance < desc.sortingCloseDistance && ratio > desc.sortingCloseRatio)) {
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
				}

				if(discarded || inserted)
					break;
			}

			if(!inserted && !discarded) {
				centerlines.push_back(std::vector<size_t>());
				centerlines.back().push_back(i);
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
		

		// Tell the callback that we're done.
		if (callback)
			callback->stop();
	};

	// Sort the centerpoints regarding their chainage.
	std::sort(centerpoints.begin(), centerpoints.end(), [](std::pair<CCVector3, ScalarType> &lhs, std::pair<CCVector3, ScalarType> &rhs) -> bool { return lhs.second < rhs.second; });

	// Split the centerpoints into different rails and recognize different rails. Only store indices to save memory.
	std::vector<std::vector<size_t>> centerlines = std::vector<std::vector<size_t>>();
	sortCenterpointsIntoCenterlines(centerpoints, centerlines, callback);

	std::sort(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &lhs, std::vector<size_t> &rhs) -> bool {
		return centerpoints[lhs.front()].second < centerpoints[rhs.front()].second;
	});

	std::for_each(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) {
		std::sort(line.begin(), line.end(), [&](size_t &lhs, size_t &rhs) -> bool {
			return centerpoints[lhs].second < centerpoints[rhs].second;
		});
	});

	if(desc.fuseCenterlines) {
		auto fuseCenterlines = [&](std::vector<std::vector<size_t>> &centerlines) {
			for(int idx_line = 0; idx_line < centerlines.size(); idx_line++) {
				auto &line = centerlines[idx_line];

				for(int offset = 1; offset < centerlines.size() - idx_line; offset++) {
					auto &nextline = centerlines[idx_line + offset];
					// Get the respective start and end points.
					auto endpoint = centerpoints[line.back()];
					auto startpoint = centerpoints[nextline.front()];

					float distance = (startpoint.first - endpoint.first).norm();
					// Compute the ratio between chainage change and distance.
					float dChainage = std::abs(endpoint.second - startpoint.second);
					float ratio = dChainage / distance;
					if(distance < desc.fuseCenterlinesCloseDistance || (distance <= desc.fuseCenterlinesFarDistance && ratio > desc.fuseCenterlinesFarRatio)) {// Old additional condition: || (startpoint.second < endpoint.second && distance <= 4.0f && ratio > 0.8f)) {
						line.insert(line.end(), nextline.begin(), nextline.end());

						nextline.clear();
						centerlines.erase(centerlines.begin() + idx_line + offset);
						offset--;
					}
				}
			}
		};
		
		fuseCenterlines(centerlines);

		std::sort(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &lhs, std::vector<size_t> &rhs) -> bool {
			return centerpoints[lhs.front()].second < centerpoints[rhs.front()].second;
		});

		std::for_each(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) {
			std::sort(line.begin(), line.end(), [&](size_t &lhs, size_t &rhs) -> bool {
				return centerpoints[lhs].second < centerpoints[rhs].second;
			});
		});

	}

	
	// Clear all lines having less then 100 points -> probably noise or something.
	auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool {
		//float centerlineLength = (centerpoints[line.back()].first - centerpoints[line.front()].first).norm();
		float centerlineLength = std::fabsf(centerpoints[line.back()].second - centerpoints[line.front()].second);
		size_t numCenterlinePoints = line.size();
		return numCenterlinePoints < desc.minCenterlinePoints || centerlineLength < desc.minCenterlineLength;
	});
	
	centerlines.erase(end, centerlines.end());
	
	if (centerlines.empty()) {
		BLUE_LOG(trace) << "No centerlines remaining after sorting. Choose a lower \"minCenterlinePoints\" threshold and/or lower \"minCenterlineLength\" threshold.";
		return 0;
	}

	std::sort(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &lhs, std::vector<size_t> &rhs) -> bool {
		return centerpoints[lhs.front()].second < centerpoints[rhs.front()].second;
	});

	std::for_each(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) {
		std::sort(line.begin(), line.end(), [&](size_t &lhs, size_t &rhs) -> bool {
			return centerpoints[lhs].second < centerpoints[rhs].second;
		});
	});
	
	
	// Collapse tracks to have a uniform density.
	std::vector<std::vector<std::pair<CCVector3, ScalarType>>> alignments = std::vector<std::vector<std::pair<CCVector3, ScalarType>>>(centerlines.size());
	
	// Set this to true which means create alignments by smoothing the centerpoints.
	if(desc.centerlineSmoothing) {
		if(callback) {
			callback->start();
			callback->setMethodTitle("Smoothing centerlines...");
		}
		
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
		if(callback)
			callback->stop();

		BLUE_LOG(trace) << "Done.";
	} else if(desc.centerlineSampling) {

		if(callback) {
			callback->start();
			callback->setMethodTitle("Sampling centerlines...");
		}

		// Clear all lines being shorter than the required segment length.
		auto end = std::remove_if(centerlines.begin(), centerlines.end(), [&](std::vector<size_t> &line) -> bool {
			float centerlineLength = std::fabsf(centerpoints[line.back()].second - centerpoints[line.front()].second);
			return centerlineLength < desc.samplingLengthForPCA;
		});

		centerlines.erase(end, centerlines.end());

		if(centerlines.empty()) {
			BLUE_LOG(trace) << "No centerlines remaining after removing too short ones. Choose a lower \"minCenterlinePoints\" threshold and/or lower \"minCenterlineLength\" threshold.";
			return 0;
		}

		alignments.resize(centerlines.size());
		
		int percentageCompleted = 0;
		bool update = true;

#pragma omp parallel private(tid) firstprivate(callback) shared(percentageCompleted, update, alignments, centerlines, centerpoints)
		{
			tid = omp_get_thread_num();
			int percentPerCenterline = 100 / centerlines.size();
			update = true;

			// Init step size and segment length.
			double stepSize = desc.samplingStepSize;
			double segmentLength = desc.samplingLengthForPCA / 2.0;

			// Pull the lambda declaration into the loop for the openmp construct
			auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end) -> CCVector3 {
				// Matrix which is capable of holding all points for PCA.
				Eigen::MatrixX3d mat;
				mat.resize(end - start, 3);
				for(size_t ii = start; ii < end; ii++) {
					auto pos = centerpoints[alignment[ii]].first;
					mat.row(ii - start) = Eigen::Vector3d(pos.x, pos.y, pos.z);
				}

				// Do PCA to find the largest eigenvector -> main axis.
				Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
				Eigen::MatrixXd cov = centered.adjoint() * centered;
				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
				Eigen::Matrix<double, 3, 1> vec = eig.eigenvectors().rightCols(1).normalized();
				return CCVector3(vec.x(), vec.y(), vec.z());
			};

#pragma omp for schedule(dynamic)
			for(long idx_line = 0; idx_line < centerlines.size(); idx_line++) {
				auto &line = centerlines[idx_line];
				float lineSize = line.size();
				long pointsPerPercent = lineSize / 100;
				float percentPerPoint = 100.0f / (float)lineSize;
				int percentageOfLineCompleted = 0;

				// Origin from which we look for points to compute the direction. Is updated after each iteration.
				std::pair<CCVector3,float> origin = { CCVector3(0,0,0),0 };

				int c = 0;
				while(c < line.size() - 1 && std::abs(centerpoints[line[c]].second - centerpoints[line[0]].second) < (segmentLength * 2.0)) {
					origin.first += centerpoints[line[c]].first;
					origin.second += centerpoints[line[c]].second;
					c++;
				}

				origin.first /= (float) c;
				origin.second /= (float)c;

				// Last direction into which we moved. Init to have an initial direction which points towards the main axis.
				auto lastDirection = getPCA(line, 0, c);

				if(lastDirection.dot(mainAxis_) < 0)
					lastDirection *= -1.0f;

				for(long i = (c / 2); i < line.size() - 1;) {

					float chainage = origin.second;

					// Lambda to compute the difference in chainage
					auto diff = [&](long index)->double {
						return std::abs(centerpoints[line[index]].second - chainage);
					};

					// Old computation method: auto axis = getPCA(alignment, i - (desc.bearingComputationSegmentLength / 2), i + (desc.bearingComputationSegmentLength / 2));
					long startIndex = i, endIndex = i;

					while(startIndex > 0L && diff(startIndex) < segmentLength)
						startIndex--;

					while(endIndex < (long)(line.size() - 1) && diff(endIndex) < segmentLength)
						endIndex++;

					// Get the main direction of the point set using PCA to move into this direction.
					if(startIndex != endIndex) {
						auto axis = getPCA(line, startIndex, endIndex);

						// If the axis points into the opposite direction of the last one due to symmetry, invert it.
						if(lastDirection.dot(axis) < 0) {
							axis *= -1.0f;
						}

						auto directionChange = axis - lastDirection;
						axis = axis + (directionChange * stepSize);
						axis.normalize();
						auto posShift = axis * stepSize;
						auto chainageShift = stepSize;

						std::pair<CCVector3, ScalarType> point = { origin.first + posShift, origin.second + chainageShift };

						alignments[idx_line].push_back(point);
						origin = point;
						lastDirection = axis;


						// Move our counting variable to the point which is closest to the chainage value of the point we just added.
						while(i < (line.size() - 1) && centerpoints[line[i]].second < point.second)
							i++;
					}
					else {
#pragma omp critical
						BLUE_LOG(warning) <<"diff: " << diff(i) <<", i: " << i << ", startIndex: " << startIndex << ", endIndex: " << endIndex << ", lineSize: " << lineSize << ", c: " << c;
						break;
					}

					if(pointsPerPercent > 0) {
						if(i > (pointsPerPercent * percentageOfLineCompleted)) {
							percentageOfLineCompleted++;
#pragma omp critical
							{
								percentageCompleted++;
								update = true;
							}
						}
					}
					
					if(tid == 0 && callback && update) {
						callback->update((float) percentageCompleted / (float)centerlines.size());
						update = false;
					}
				}

				if(pointsPerPercent == 0) {
#pragma omp critical
					{
						percentageCompleted+= 100;
						update = true;
					}
				}
			}
#pragma omp barrier

			if(tid == 0 && callback && update) {
				callback->update((float)percentageCompleted / (float)centerlines.size());
				update = false;
			}
		}

		// Tell the callback that we're done.
		if(callback)
			callback->stop();

	}
	else {
		if(callback) {
			callback->start();
			callback->setMethodTitle("Creating centerlines...");
		}

		long percentageCompleted = 0;
		bool update = true;
#pragma omp parallel private(tid) firstprivate(callback) shared(percentageCompleted, update, alignments, centerlines, centerpoints)
		{
			tid = omp_get_thread_num();
			update = true;

#pragma omp for schedule(dynamic)
			for(long idx_line = 0; idx_line < centerlines.size(); idx_line++) {
				auto &line = centerlines[idx_line];
				float lineSize = line.size();
				long pointsPerPercent = lineSize / 100;
				long processedPoints = 0;

				for(long i = 0; i < line.size(); i++) {
					size_t idx_point = line[i];
					std::pair<CCVector3, ScalarType> point = { centerpoints[idx_point].first, centerpoints[idx_point].second };
					alignments[idx_line].push_back(std::pair<CCVector3, ScalarType>(point.first, point.second));

					processedPoints++;

					if(processedPoints == pointsPerPercent) {
						processedPoints = 0;
#pragma omp critical
						{
							percentageCompleted++;
							update = true;
						}
					}

#pragma omp critical
					{
						if(tid == 0 && callback && update) {
							callback->update((float)percentageCompleted / (float)centerlines.size());
							update = false;
						}
					}
				}
			}
		}

		if(callback)
			callback->stop();
	}

	std::sort(alignments.begin(), alignments.end(), [&](std::vector<std::pair<CCVector3, ScalarType>> &lhs, std::vector<std::pair<CCVector3, ScalarType>> &rhs) -> bool {
		return lhs.front().second < rhs.front().second;
	});

	std::for_each(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &line) {
		std::sort(line.begin(), line.end(), [&](std::pair<CCVector3, ScalarType> &lhs, std::pair<CCVector3, ScalarType> &rhs) -> bool {
			return lhs.second < rhs.second;
		});
	});

	if(desc.fuseAlignments) {
		auto fuseAlignments = [&](std::vector<std::vector<std::pair<CCVector3, ScalarType>>> &alignments) {
			for(int idx_line = 0; idx_line < alignments.size(); idx_line++) {
				auto &line = alignments[idx_line];

				for(int offset = 1; offset < alignments.size() - idx_line; offset++) {
					auto endpoint = line.back();
					auto &nextline = alignments[idx_line + offset];

					// Get the respective start and end points.
					auto startpoint = nextline.front();

					float distance = (startpoint.first - endpoint.first).norm();
					// Compute the ratio between chainage change and distance.
					float dChainage = std::abs(startpoint.second - endpoint.second);
					float ratio = dChainage / distance;
					if(distance < desc.fuseAlignmentsCloseDistance || (distance <= desc.fuseAlignmentsFarDistance && ratio > desc.fuseAlignmentsFarRatio)) {
						line.insert(line.end(), nextline.begin(), nextline.end());

						std::sort(line.begin(), line.end(), [&](std::pair<CCVector3, ScalarType> &lhs, std::pair<CCVector3, ScalarType> &rhs) -> bool {
							return lhs.second < rhs.second;
						});

						nextline.clear();
						alignments.erase(alignments.begin() + idx_line + offset);
						offset--;
					}
				}
			}
		};

		fuseAlignments(alignments);

		std::sort(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &lhs, std::vector<std::pair<CCVector3, ScalarType>> &rhs) -> bool {
			return lhs.front().second < rhs.front().second;
		});

		std::for_each(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &line) {
			std::sort(line.begin(), line.end(), [](std::pair<CCVector3, ScalarType> &lhs, std::pair<CCVector3, ScalarType> &rhs) -> bool {
				return lhs.second < rhs.second;
			});
		});
	}

	auto endAlignments = std::remove_if(alignments.begin(), alignments.end(), [&](std::vector<std::pair<CCVector3, ScalarType>> &line) -> bool {
		//float centerlineLength = (centerpoints[line.back()].first - centerpoints[line.front()].first).norm();
		float centerlineLength = std::fabsf(line.back().second - line.front().second);
		size_t numCenterlinePoints = line.size();
		return numCenterlinePoints < desc.minSegmentPoints || centerlineLength < desc.minSegmentLength;
	});

	alignments.erase(endAlignments, alignments.end());

	if(alignments.empty()) {
		return 0;
	}
	else {
	}

	std::sort(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &lhs, std::vector<std::pair<CCVector3, ScalarType>> &rhs) -> bool {
		return lhs.front().second < rhs.front().second;
	});

	std::for_each(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &line) {
		std::sort(line.begin(), line.end(), [](std::pair<CCVector3, ScalarType> &lhs, std::pair<CCVector3, ScalarType> &rhs) -> bool {
			return lhs.second < rhs.second;
		});
	});

	// Reserve space for the centerpoints points and color them blue.
	long totalPoints = 0;

#pragma omp parallel for reduction(+:totalPoints)
	for(long i = 0; i < alignments.size(); i++) {
		totalPoints += alignments[i].size();
	}

	if(!this->reserve(this->size() + totalPoints)) {
		BLUE_LOG(warning) << "Not enough memory available for all points. Aborting.";
		return -6;
	}

	if(!this->reserveTheRGBTable()) {
		BLUE_LOG(warning) << "Not enough memory available to reserve the RGB table for all points. Aborting.";
		return -7;
	}
	
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

		BLUE_LOG(trace) << "Done.";
	};

	addAlignmentPoints();

	int numAlignments = alignments.size();

	// Delete the alignments buffer since we dont need it anymore.
	std::for_each(alignments.begin(), alignments.end(), [](std::vector<std::pair<CCVector3, ScalarType>> &line) { line.clear(); });
	alignments.clear();

	centerpoints.clear();

	// Update the centerline description so that we know how the tracks were generated when we export the curvatures etc. from the measurement.
	centerlineDescription_ = desc;

	// Update the indices.
	computeIndices();

	// Return the number of selected alignments.
	return numAlignments;
}


int OpenInfraPlatform::PointCloudProcessing::PointCloud::resetCenterlines() {
	centerlineDescription_ = buw::CenterlineComputationDescription();
	return resetRailwaySegmentation();
}

int OpenInfraPlatform::PointCloudProcessing::PointCloud::resetPairs() {
	// If there are pairs, reset them. Otherwise return -2 and print trace to log.
	if(bHasPairs_) {
		// Get the railway scalar field and set it to read from. If not existing, abort and return -1.
		int idx_railway = getScalarFieldIndexByName("Railway");
		if(idx_railway == -1) {
			return -1;
		}
		else {
			setCurrentOutScalarField(idx_railway);
		}

		// Reset the railway points color to white.
		const ColorCompType white[3] = { 255, 255, 255 };
		for_each([&](size_t i) {
			if(getPointScalarValue(i) != 0)
				setPointColor(i, ccColor::Rgb(white));
		});

		// Reset the 'Railway' scalar field.
		resetScalarField("Railway");

		// Clear all pairs from the sections.
		for(auto &section : sections_) {
			section->resetPairs();
		}

		bHasPairs_ = false;
		return 0;
	}
	else {
		BLUE_LOG(trace) << "There are no pairs to reset.";
		return -2;
	}
}

int OpenInfraPlatform::PointCloudProcessing::PointCloud::computeCenterlineCurvature(const buw::CenterlineCurvatureComputationDescription &desc,
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

		// Sort the alignment points after increasing chainage values.
		std::sort(alignment.begin(), alignment.end(), [&](const size_t &lhs, const size_t &rhs) -> bool { return getPointScalarValue(lhs) < getPointScalarValue(rhs); });

		// We take bearing and chainage for each point.
		long numBearingsAndChainages = alignment.size();// Old value: ((alignment.size() - desc.bearingComputationSegmentLength) / desc.curvatureStepSize) + 1;

		// We have one less value since we take the change between the current and the next or last element.
		long numCurvatures = numBearingsAndChainages - 1;

		long numDeltaCurvatures = numCurvatures - 1;

		long numCurvaturesSmoothed = numCurvatures - desc.numPointsForMeanCurvature;

		double alignmentLength = std::abs(getPointScalarValue(alignment.back()) - getPointScalarValue(alignment.front()));

		if (alignmentLength > desc.bearingComputationSegmentLength) {

			// Create and initialize the necessary folders.
			if (!root.exists(date))
				root.mkdir(date);

			if (!sub.exists(time))
				sub.mkdir(time);

			// Open the file to write the data to.
			BLUE_LOG(trace) << "Processing Alignment#" + QString::number(idx).toStdString() << ". Size:" << QString::number(alignment.size()).toStdString();
			QFile file(sub.absolutePath() + "/" + time + "/" + "Alignment#" + QString::number(idx) + ".txt");
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return -1;

			auto filestart = file.pos();

			// Initialize number of points to use for PCA and and the NORTH direction.
			const Eigen::Matrix<double, 3, 1> NORTH(0., 1., 0.);
			const Eigen::Matrix<double, 2, 1> NORTH2D(0., 1.);
			const Eigen::Matrix<double, 2, 1> EAST2D(1., 0.);

			// Initialize the container to hold our angles of the direction vectors
			std::vector<double> bearings = std::vector<double>(numBearingsAndChainages);
			std::vector<double> chainages = std::vector<double>(numBearingsAndChainages);
			std::vector<double> curvatures = std::vector<double>(numCurvatures);
			std::vector<double> deltaCurvatures = std::vector<double>(numDeltaCurvatures);
			//std::vector<double> curvaturesFiltered = std::vector<double>(numCurvatures);
			//std::vector<double> curvaturesSmoothed = std::vector<double>(numCurvaturesSmoothed);

			int tid = 0;
			// Compute the bearing for all points as the angle between the principal axis of bearingComputationSegmentLength consecutive centerline points and the NORTH direction.
#pragma omp parallel private(tid) firstprivate(callback) shared(bearings, curvatures, chainages)
			{
				tid = omp_get_thread_num();
				long processedPoints = 0;
				long pointsPerThread = alignment.size() / omp_get_num_threads();
				long pointsPerPercent = pointsPerThread / 100;
				int percentageCompleted = 0;
				//buw::CenterlineCurvatureComputationDescription desc = buw::CenterlineCurvatureComputationDescription(description);

				// Pull the lambda declaration into the loop for the openmp construct
				auto getPCA = [&](std::vector<size_t> alignment, size_t start, size_t end) -> Eigen::Matrix<double, 2, 1> {
					// Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX2d mat;
					mat.resize(end - start, 2);
					for(size_t ii = start; ii < end; ii++) {
						auto pos = *getPoint(alignment[ii]);
						mat.row(ii - start) = Eigen::Vector2d(pos.x, pos.y);
					}

					// Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 2, 1> vec = eig.eigenvectors().rightCols(1);
					return vec;
				};

				double segmentLength = desc.bearingComputationSegmentLength / 2.0;


				// Old for loop: for (long i = desc.bearingComputationSegmentLength / 2; i < alignment.size() - (desc.bearingComputationSegmentLength / 2); i += desc.curvatureStepSize) {
#pragma omp for
				for(long i = 0; i < alignment.size(); i++) {

					float chainage = getPointScalarValue(alignment[i]);

					// Lambda to compute the difference in chainage
					auto diff = [&](long index)->double {
						return std::abs(getPointScalarValue(alignment[index]) - chainage);
					};

					// Old computation method: auto axis = getPCA(alignment, i - (desc.bearingComputationSegmentLength / 2), i + (desc.bearingComputationSegmentLength / 2));
					long startIndex = i, endIndex = i;

					while(startIndex > 0 && diff(startIndex) < segmentLength)
						startIndex--;

					while(endIndex < alignment.size() - 1 && diff(endIndex) < segmentLength)
						endIndex++;

					// Get the PCA axis and compute the bearing.
					auto axis = getPCA(alignment, startIndex, endIndex);
					//axis.normalize();

					// Old versions: bearings[(i - (desc.bearingComputationSegmentLength / 2)) / desc.curvatureStepSize] = (std::acos(axis.dot(NORTH2D)) * 180.0 / M_PI);
					// Old versions: chainages[(i - (desc.bearingComputationSegmentLength / 2)) / desc.curvatureStepSize] = getPointScalarValue(alignment[i]);// mainAxis_.dot(alignment[i]);
					// Old versions: processedPoints += desc.curvatureStepSize;

					auto northing = axis.dot(NORTH2D);
					auto easting = axis.dot(EAST2D);

					if(easting < 0)
						northing *= -1;

					auto bearing = (std::acos(northing) * 180.0 / M_PI);

					if(easting < 0)
						bearing += 180;

					bearings[i] = bearing;
					chainages[i] = chainage;
					processedPoints++;

					if(processedPoints >= pointsPerPercent) {
						percentageCompleted++;
						processedPoints = 0;

						if(tid == 0 && callback)
							callback->update(((100.0f * (float)(idx) / (float)alignments.size()) + (1.0f / (float)alignments.size()) * percentageCompleted)
								* ((float)alignments.size() / (float)indices.size()));
					}
				}
#pragma omp barrier
			}

				//int nJumps = 0;
				//for (long i = 0; i < bearings.size(); i++) {
				//	// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
				//	bearings[i] += nJumps;
				//	if(i < bearings.size() - 1) {
				//		if(std::abs(bearings[i] - (bearings[i + 1] + nJumps)) > 170)
				//			nJumps += 180;
				//	}
				//}


				if(desc.numPointsForMedianBearing > 1) {
					// Copy bearings values to allow for median filtering.
					std::vector<double> bearingsOld = std::vector<double>(bearings.size());
					std::copy(bearings.begin(), bearings.end(), bearingsOld.begin());
														
					long startOffset = (long)std::floor((float)desc.numPointsForMedianBearing / 2.0f);

					if(desc.numPointsForMedianBearing % 2 == 0)
						startOffset--;

					long endOffset = (long)std::floor((float)desc.numPointsForMedianBearing / 2.0f);

					BLUE_LOG(trace) << startOffset << " " << endOffset;
#pragma omp parallel for
					for(long i = 0; i < bearings.size(); i++) {
						std::vector<double> values = std::vector<double>();

						for(long ii = std::max(0L, i - startOffset); ii <= std::min(((long)bearings.size()) - 1L, i + endOffset); ii++) {
							values.push_back(bearingsOld[ii]);
						}
						
						std::sort(values.begin(), values.end(), [](const double &lhs, const double &rhs)->bool { return lhs < rhs; });

						double bearing = values[(int)std::ceilf((float)values.size() / 2.0f) - 1];
						
						bearings[i] = bearing;							
					}
					
				}
				

				if(desc.numPointsForMeanBearing > 1) {
					// Copy bearings values to allow for averaging smoothing.
					std::vector<double> bearingsOld = std::vector<double>(bearings.size());
					std::copy(bearings.begin(), bearings.end(), bearingsOld.begin());

					// Copy bearings values to allow for averaging smoothing.
					std::vector<double> chainagesOld = std::vector<double>(chainages.size());
					std::copy(chainages.begin(), chainages.end(), chainagesOld.begin());
					
					long startOffset = (long)std::floor((float)desc.numPointsForMeanBearing / 2.0f);
					if(desc.numPointsForMeanBearing % 2 == 0)
						startOffset--;
					long endOffset = (long)std::floor((float)desc.numPointsForMeanBearing / 2.0f);

#pragma omp parallel for
					for(long i = 0; i < bearings.size(); i++) {
						double bearing = 0.0;
						double chainage = 0.0;
						double numPoints = 0.0;

						for(long ii = std::max(0L, i - startOffset); ii <= std::min((long)bearings.size() - 1L, i + endOffset); ii++) {
							bearing += bearingsOld[ii];
							chainage += chainagesOld[ii];
							numPoints++;
						}
						bearing /= numPoints;
						chainage /= numPoints;

						bearings[i] = bearing;
						chainages[i] = chainage;
					}
					
				}

					// Without smoothing
#pragma omp parallel for
				for (long i = 0; i < curvatures.size(); i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
					curvatures[i] = ((bearings[i + 1] - bearings[i]) / deltaChainage);
				}

				if(desc.numPointsForMedianCurvature > 1) {
					// Copy bearings values to allow for median filtering.
					std::vector<double> curvaturesOld = std::vector<double>(curvatures.size());
					std::copy(curvatures.begin(), curvatures.end(), curvaturesOld.begin());
					
					long startOffset = (long)std::floor((float)desc.numPointsForMedianCurvature / 2.0f);
					if(desc.numPointsForMedianCurvature % 2 == 0)
						startOffset--;

					long endOffset = (long)std::floor((float)desc.numPointsForMedianCurvature / 2.0f);

#pragma omp parallel for
					for(long i = 0; i < curvatures.size(); i++) {
						std::vector<double> values = std::vector<double>();

						for(long ii = std::max(0L, i - startOffset); ii <= std::min((long)curvatures.size() - 1L, i + endOffset); ii++) {
							values.push_back(curvaturesOld[ii]);
						}

						std::sort(values.begin(), values.end(), [](const double &lhs, const double &rhs)->bool { return lhs < rhs; });

						curvatures[i] = values[(int)std::ceilf((float)values.size() / 2.0f) - 1];
					}
					
				}

				if(desc.numPointsForMeanCurvature > 1) {
					// Copy bearings values to allow for averaging smoothing.
					std::vector<double> curvaturesOld = std::vector<double>(curvatures.size());
					std::copy(curvatures.begin(), curvatures.end(), curvaturesOld.begin());
					
					long startOffset = (long)std::floor((float)desc.numPointsForMeanCurvature / 2.0f);
					if(desc.numPointsForMeanCurvature % 2 == 0)
						startOffset--;
					long endOffset = (long)std::floor((float)desc.numPointsForMeanCurvature / 2.0f);

#pragma omp parallel for
					for(long i = 0; i < curvatures.size(); i++) {
						double value = 0.0;
						double numPoints = 0.0;

						for(long ii = std::max(0L, i - startOffset); ii <= std::min((long)curvatures.size() - 1L, i + endOffset); ii++) {
							value += curvaturesOld[ii];
							numPoints++;
						}
						value /= numPoints;

						curvatures[i] = value;
					}
					
				}

#pragma omp parallel for
				for(long i = 0; i < deltaCurvatures.size(); i++) {
					// Compute the curvature as the difference between the bearings divided by the change in stationing (movement along main axis of the dataset).
					double deltaChainage = std::abs(chainages[i + 1] - chainages[i]);
					deltaCurvatures[i] = ((curvatures[i + 1] - curvatures[i]) / deltaChainage);
				}

				// Old version for median curvature filtering.
//				curvaturesFiltered[0] = curvatures[0];
//				curvaturesFiltered[1] = curvatures[1];
//				curvaturesFiltered[numCurvatures - 1] = curvatures[numCurvatures - 1];
//				curvaturesFiltered[numCurvatures - 2] = curvatures[numCurvatures - 2];
//				// Sliding median filtering.
//#pragma omp for
//				for(long i = 2; i < curvatures.size() - 2; i++) {
//					std::vector<double> neighbours = { curvatures[i - 2], curvatures[i - 1], curvatures[i], curvatures[i + 1], curvatures[i + 2] };
//					std::sort(neighbours.begin(), neighbours.end());
//
//					// Choose the median value.
//					curvaturesFiltered[i] = neighbours[2];
//				}
//#pragma omp barrier

				// Old version for mean curvature computation.
//				if(desc.numPointsForMeanCurvature > 1) {
//					int startOffset = (int)std::floor((float)desc.numPointsForMeanCurvature / 2.0f);
//					if(desc.numPointsForMeanCurvature % 2 == 0)
//						startOffset++;
//					int endOffset = std::ceil((float)desc.numPointsForMeanCurvature / 2.0f);
//
//#pragma omp for
//					for(long i = startOffset; i < curvatures.size() - endOffset - 1; i++) {
//						double curvature = 0.0;
//
//						for(int offset = -startOffset; offset < endOffset; offset++)
//							curvature += curvaturesFiltered[i + offset];
//
//						curvaturesSmoothed[i - startOffset] = curvature / (double)desc.numPointsForMeanCurvature;
//					}
//#pragma omp barrier
//				}

				
					// Old version of writing stuff to file.
					//for (size_t i = 0; i < curvaturesSmoothed.size() - (endOffset - startOffset) - 1; i++) {
					//	QString text = QString::number(chainages[i + startOffset], 'g',10)
					//	                 .append("\t")
					//	                 .append(QString::number(curvaturesSmoothed[i],'g', 10))
					//	                 .append("\t")
					//	                 .append(QString::number(bearings[i + startOffset], 'g', 10))
					//	                 .append("\n");
					//	file.write(text.toStdString().data());
					//}

			for(size_t i = 0; i < deltaCurvatures.size(); i++) {
				QString text = QString::number(chainages[i], 'g', 20)
					.append("\t")
					.append(QString::number(curvatures[i], 'g', 20))
					.append("\t")
					.append(QString::number(bearings[i], 'g', 20))
					.append("\n")
					.append(QString::number(deltaCurvatures[i], 'g', 20))
					.append("\t");
				file.write(text.toStdString().data());
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
		                    QString("MaxDistance:" + QString::number(centerlineDescription_.sortingCloseDistance)),
		                    QString("MinSegmentPoints:" + QString::number(centerlineDescription_.minSegmentPoints)),
		                    QString("MinSegmentLength:" + QString::number(centerlineDescription_.minSegmentLength)),
		                    QString("Curvature computation"),
		                    QString("SegmentLengthForPCA:" + QString::number(desc.bearingComputationSegmentLength)),
		                    QString("CurvatureStepSize:" + QString::number(desc.curvatureStepSize)),
		                    QString("NumPointsForMedianBearing:" + QString::number(desc.numPointsForMedianBearing)),
							QString("NumPointsForMeanBearing:" + QString::number(desc.numPointsForMeanBearing)),
							QString("NumPointsForMedianCurvature:" + QString::number(desc.numPointsForMedianCurvature)),
							QString("NumPointsForMeanCurvature:" + QString::number(desc.numPointsForMeanCurvature)) };
		file.write(text.join("\n").toStdString().data());
		file.close();
	}

	// Tell the callback that we're done.
	if (callback)
		callback->stop();

	return 0;
}


int OpenInfraPlatform::PointCloudProcessing::PointCloud::resetRailwaySegmentation() {
	// Reset the railway points color to white.
	int idx_railway = getScalarFieldIndexByName("Railway");
	if (idx_railway == -1)
		return -1;

	setCurrentOutScalarField(idx_railway);
	const ColorCompType white[3] = {255, 255, 255};
	for_each([&](size_t i) {
		if (getPointScalarValue(i) != 0)
			setPointColor(i, ccColor::Rgb(white));
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

void OpenInfraPlatform::PointCloudProcessing::PointCloud::removeNotSegmentedPoints() {
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

void OpenInfraPlatform::PointCloudProcessing::PointCloud::removeFilteredPoints(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback) {
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

const CCVector3 OpenInfraPlatform::PointCloudProcessing::PointCloud::getMainAxis() const {
	return mainAxis_;
}

const double OpenInfraPlatform::PointCloudProcessing::PointCloud::getSectionLength() const {
	// If sections are initialized, return the length of the first section since all are equally long.
	if (sections_.size() > 0 && sections_[0]) {
		return sections_[0]->getLength();
	}
	else {
		return 0;
	}
}

const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> OpenInfraPlatform::PointCloudProcessing::PointCloud::getIndices() const {
	return std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>>(remainingIndices_, filteredIndices_, segmentedIndices_);
}

buw::ReferenceCounted<buw::Octree> OpenInfraPlatform::PointCloudProcessing::PointCloud::getDGMOctree() {
	if (!octree_)
		octree_ = std::make_shared<buw::Octree>(this);
	return octree_;
}

void OpenInfraPlatform::PointCloudProcessing::PointCloud::computeMainAxis() {
	BLUE_LOG(trace) << "Start computing main axis.";
	// Set the main axis as the eigenvector with the largest eigenvalue.
	mainAxis_ = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());
	BLUE_LOG(trace) << "Finished computing main axis.";
}
