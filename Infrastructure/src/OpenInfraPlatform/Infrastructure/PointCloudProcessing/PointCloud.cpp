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

#include <ccScalarField.h>
#include <FileIOFilter.h>

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
		pointCloud->computeMainAxis();
		pointCloud->computeSections(10.0f);
	}
	else {
		//TODO
	}
	return pointCloud;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections(const float length)
{
	CCVector3 axis = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());

	int idx_plamn = getScalarFieldIndexByName("ProjectionLengthAlongMainAxis");

	if(idx_plamn == -1)
		idx_plamn = addScalarField("ProjectionLengthAlongMainAxis");

	setCurrentInScalarField(idx_plamn);

	auto setProjectionLengthAlongMainAxis = [&](size_t i) {
		this->setPointScalarValue(i, axis.dot(*(this->getPoint(i))));
	};

	for_each(setProjectionLengthAlongMainAxis);

	getScalarField(idx_plamn)->computeMinAndMax();

	ScalarType min, max;
	std::tie(min, max) = getScalarFieldMinAndMax(idx_plamn);


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

int OpenInfraPlatform::Infrastructure::PointCloud::flagDuplicatePoints(const double minDistance)
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

	// Set it as input scalar field to write explicitly to it - not sure if this is really necessary - and copy the values from this output scalar field to it.
	setCurrentInScalarField(idx);
		
	CCLib::GeometricalAnalysisTools::flagDuplicatePoints(this, minDistance, nullptr, octree_.get());

	// Set it to be the current output scalar field to avoid overriding another one since flagDuplicatePoints uses this field.
	setCurrentOutScalarField(idx);

	for_each([&](size_t i) {
		setPointScalarValue(i, getPointScalarValue(i));
	});

	return 0;
}

std::vector<uint32_t> OpenInfraPlatform::Infrastructure::PointCloud::getDuplicatePointIndices()
{
	std::vector<uint32_t> indices = std::vector<uint32_t>();

	// Get the Duplicate scalar field or if not there create it and flag nothing.
	int idx = getScalarFieldIndexByName("Duplicate");
	if(idx == -1)
		flagDuplicatePoints(0.0);

	// Set the Duplicate scalar field as output to read from it.
	idx = getScalarFieldIndexByName("Duplicate");
	setCurrentOutScalarField(idx);

	// For each point, check whether it is a duplicate, if yes, insert it into the vector.
	for_each([&](size_t i) {
		if(getPointScalarValue(i) == 1)
			indices.push_back(i);
	});

	return indices;
}

const std::tuple<ScalarType, ScalarType> OpenInfraPlatform::Infrastructure::PointCloud::getScalarFieldMinAndMax(int idx) const
{
	CCLib::ScalarField* field = getScalarField(idx);
	return std::tuple<ScalarType, ScalarType>(field->getMin(), field->getMax());
}

const CCVector3 OpenInfraPlatform::Infrastructure::PointCloud::getMainAxis() const
{
	return mainAxis_;
}

const double OpenInfraPlatform::Infrastructure::PointCloud::getSectionLength() const
{
	if(sections_[0]) {
		return sections_[0]->getLength();
	}
}

const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> OpenInfraPlatform::Infrastructure::PointCloud::getIndices()
{
	return std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>>(remainingIndices_, filteredIndices_, segmentedIndices_);
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeMainAxis()
{
	mainAxis_ = CCVector3(getEigenvectors<1>().cast<float>().normalized().data());
}
