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