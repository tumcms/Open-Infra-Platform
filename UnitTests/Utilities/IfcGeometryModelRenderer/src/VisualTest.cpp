/*
    Copyright (c) 2020 Technical University of Munich
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

#include <VisualTest.h>

using namespace testing;

VisualTest::VisualTest()
{
    buw::renderSystemDescription scd;
    scd.width = 640;
    scd.height = 480;
    scd.windowId = static_cast<void*>(this);
    scd.forceWarpDevice = false;
    scd.enableMSAA = true;
    scd.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;

    renderSystem_ = BlueFramework::Rasterizer::createRenderSystem(scd);
}

VisualTest::~VisualTest()
{
    renderSystem_.reset();
}

void VisualTest::SetUp()
{
    renderer = buw::makeReferenceCounted<IfcGeometryModelRenderer>(renderSystem_);
}

void VisualTest::TearDown()
{
    renderer.reset();
}

buw::Image4b VisualTest::CaptureImage()
{
	return renderer->captureImage();
}

boost::filesystem::path VisualTest::executablePath() const
{
	return boost::dll::program_location().parent_path();
}

boost::filesystem::path VisualTest::filePath(const std::string& relPath) const
{
	return executablePath()
		.concat("\\UnitTests\\Schemas\\")
		.concat(Schema())
		.concat("\\")
		.concat(TestName())
		.concat("\\")
		.concat(relPath);
}

boost::filesystem::path VisualTest::dataPath(const std::string& relPath) const
{
	return filePath("Data\\" + relPath);
}

boost::filesystem::path VisualTest::testPath(const std::string& relPath) const
{
	return filePath("Test\\" + relPath);
}
