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
#ifdef OIP_WITH_POINT_CLOUD_PROCESSING

#include <PointCloudVisualTest.h>
#include <boost/filesystem.hpp>

using namespace testing;

void PointCloudVisualTest::SetUp()
{
	rendererPointCloud = buw::makeReferenceCounted<PointCloudGeometryModelRenderer>(renderSystem_);

	// make a Test directory for test-specific data
	boost::filesystem::create_directory(filePath("Test"));
}

void PointCloudVisualTest::TearDown()
{
	rendererPointCloud.reset();
}

buw::Image4b PointCloudVisualTest::CaptureImage()
{
	return rendererPointCloud->captureImage();
}

boost::filesystem::path PointCloudVisualTest::filePath(const std::string& relPath) const
{
	return executablePath()
		.concat("\\UnitTests\\PointCloud\\")
		.concat(FileType())
		.concat("\\")
		.concat(TestName())
		.concat("\\")
		.concat(relPath);
}
#endif
