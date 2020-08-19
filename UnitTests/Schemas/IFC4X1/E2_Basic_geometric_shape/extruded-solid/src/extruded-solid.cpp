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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <reader/IFC4x1Reader.h>
#include <namespace.h>

#include <IfcGeometryModelRenderer.h>

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <IfcGeometryConverter/IfcImporterImpl.h>
#include <IfcGeometryConverter/ConverterBuw.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace testing;

class VisualTest : public Test
{
protected:

	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_ = nullptr;
	buw::ReferenceCounted<IfcGeometryModelRenderer> renderer = nullptr;

	VisualTest()
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

	virtual ~VisualTest()
	{
		renderSystem_.reset();
	}

	virtual void SetUp() override
	{
		renderer = buw::makeReferenceCounted<IfcGeometryModelRenderer>(renderSystem_);

	}

	virtual void TearDown() override
	{
		renderer.reset();
	}
};

class ExtrudedSolidTest : public VisualTest {
    protected:

    // Test standard values
    buw::Image4b _background = buw::Image4b(0, 0);

    virtual void SetUp() override {
        VisualTest::SetUp();

        express_model = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename.string());

        importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>>();
        importer->collectGeometryData(express_model);
	    oip::ConverterBuwT<emt::IFC4X1EntityTypes>::createGeometryModel(model, importer->getShapeDatas());

        _background = renderer->captureImage();
        renderer->setModel(model);

    }

    virtual void TearDown() override {
        express_model.reset();
        VisualTest::TearDown();
    }

    const boost::filesystem::path filename = boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\extruded-solid\\Data\\extruded-solid.ifc");

    const boost::filesystem::path baseImageFilename_ = boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\extruded-solid\\Data\\extruded-solid.png");


    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
	
	void compareImageWithView(const std::string filename) {

	// Arrange
	const auto expected = buw::loadImage4b(boost::dll::program_location().parent_path().concat(filename).string());

	// Act
	const buw::Image4b image = renderer->captureImage();

	// Assert
	EXPECT_EQ(image, expected);

	// Annihilate
	}
};

TEST_F(ExtrudedSolidTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(30));
}

/*TEST_F(ExtrudedSolidTest, AllEntitiesAreRead) {
	EXPECT_THAT(xpress_model->entities, Eq('Liebich'));
		
}*/

TEST_F(ExtrudedSolidTest, ImageIsSaved)
{
    // Arrange
    buw::Image4b image = renderer->captureImage();

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\extruded-solid.png").string(), image);

    // Assert
    EXPECT_NE(image,_background);
}

TEST_F(ExtrudedSolidTest, TopView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Top);
    buw::Image4b image = renderer->captureImage();

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\extruded-solid_top.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
}

TEST_F(ExtrudedSolidTest, FrontView)
{
	// Arrange
	renderer->setViewDirection(buw::eViewDirection::Front);
	buw::Image4b image = renderer->captureImage();

	 // Act
	buw::storeImage(boost::dll::program_location().parent_path().concat("\\extruded-solid_front.png").string(), image);

	// Assert
	EXPECT_NE(image, _background);
}

TEST_F(ExtrudedSolidTest, BottomView)
{
	// Arrange
	renderer->setViewDirection(buw::eViewDirection::Bottom);
	buw::Image4b image = renderer->captureImage();

	// Act
	buw::storeImage(boost::dll::program_location().parent_path().concat("\\extruded-solid_bottom.png").string(), image);

	// Assert
	EXPECT_NE(image, _background);
}

TEST_F(ExtrudedSolidTest, GivenNewImage_AfterHome_AreEqual)
{
	compareImageWithView("\\extruded-solid.png");
}

TEST_F(ExtrudedSolidTest, GivenNewImage_AfterHome_AreEqual_Top)
{
	renderer->setViewDirection(buw::eViewDirection::Top);
	compareImageWithView("\\extruded-solid_top.png");
}

TEST_F(ExtrudedSolidTest, GivenNewImage_AfterHome_AreEqual_Front)
{
	renderer->setViewDirection(buw::eViewDirection::Front);
	compareImageWithView("\\extruded-solid_front.png");
}

TEST_F(ExtrudedSolidTest, GivenNewImage_AfterHome_AreEqual_Bottom)
{
	renderer->setViewDirection(buw::eViewDirection::Bottom);
	compareImageWithView("\\extruded-solid_bottom.png");
}

