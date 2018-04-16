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

#include <liblas/liblas.hpp>


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
	pointCloud->init();
	return pointCloud;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback)
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

	if(desc.dim == ePointCloudFilterDimension::Volume3D)
		err = computeLocalDensity((CCLib::GeometricalAnalysisTools::Density) desc.density, desc.kernelRadius, callback);

	if(err == 0) {

		// Get our scalar field. If we cant find our scalar field, something went wrong and we abort and return -1.
		int idx = getScalarFieldIndexByName("Density");
		if(idx == -1) {
			err = idx;
			return err;
		}
		else {
			// Set the Density Scalar field as in and output field since we want to read it and threshold it.
			setCurrentInScalarField(idx);
			setCurrentOutScalarField(idx);

			// Compare the scalar value for each point with the threshold and write the result into the scalar field since we're not interested in the real densities.
			for_each([&](size_t i) {
				setPointScalarValue(i, (int)(getPointScalarValue(i) < desc.minThreshold));
			});

			// Update our indices for filtered etc.
			computeIndices();
		}
	}
	return err;
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
	setCurrentOutScalarField(idx);

	// Compute the local density and retirn the error code.
	return CCLib::GeometricalAnalysisTools::computeLocalDensity(this, metric, kernelRadius, callback.get(), octree_.get());
}

void OpenInfraPlatform::Infrastructure::PointCloud::init()
{
	computeMainAxis();
	octree_ = buw::makeReferenceCounted<CCLib::DgmOctree>(this);
	octree_->build();
	computeSections(10.0f);
}

void OpenInfraPlatform::Infrastructure::PointCloud::unflagDuplicatePoints()
{
	// Get the duplicate scalar field.
	int idx = getScalarFieldIndexByName("Duplicate");
	if(idx == -1)
		idx = addScalarField("Duplicate");

	// Set Duplicate as Scalar field to write to and flag each point with duplicate 0
	setCurrentInScalarField(idx);
	for_each([&](size_t i) {
		setPointScalarValue(i, 0);
	});
}

std::vector<buw::ReferenceCounted<buw::PointCloudSection>> OpenInfraPlatform::Infrastructure::PointCloud::getSections()
{
	return sections_;
}

void OpenInfraPlatform::Infrastructure::PointCloud::computeIndices()
{
	remainingIndices_.clear();
	filteredIndices_.clear();

	// Get the duplicate scalar field.
	int idx_duplicate = getScalarFieldIndexByName("Duplicate");
	if(idx_duplicate == -1)
		idx_duplicate = addScalarField("Duplicate");

	int idx_density = getScalarFieldIndexByName("Density");
	if(idx_density == -1)
		idx_density = addScalarField("Density");

	for_each([&](size_t i) {
		ScalarType filtered = 0;
		setCurrentOutScalarField(idx_duplicate);
		filtered += getPointScalarValue(i);

		setCurrentOutScalarField(idx_density);
		filtered += getPointScalarValue(i);

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
