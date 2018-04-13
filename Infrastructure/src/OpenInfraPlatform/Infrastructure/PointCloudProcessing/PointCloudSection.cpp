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

int OpenInfraPlatform::Infrastructure::PointCloudSection::flagDuplicatePoints(const double minDistance)
{
	buw::ReferenceCounted<buw::PointCloud> cloud2D = createPointCloud2D();
	cloud2D->flagDuplicatePoints(minDistance);
	cloud2D->for_each([&](size_t i) {
		if(cloud2D->getPointScalarValue(i) == 1) {
			filteredIndices_.push_back(this->getPointGlobalIndex(i));
		}		
	});

	return 0;
}


void OpenInfraPlatform::Infrastructure::PointCloudSection::setLength(double length)
{
	length_ = length;
}

const double OpenInfraPlatform::Infrastructure::PointCloudSection::getLength() const
{
	return length_;
}

const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> OpenInfraPlatform::Infrastructure::PointCloudSection::getIndices()
{
	return std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>>(remainingIndices_, filteredIndices_, segmentedIndices_);
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