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

#include <reader/IFC4X1Reader.h>
#include <namespace.h>

#include <VisualTest.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

using namespace testing;

class SurfaceModelTest : public VisualTest {
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

	virtual std::string TestName() const { return "surface-model"; }
	virtual std::string Schema() const { return "IFC4X1"; }

	const boost::filesystem::path filename = dataPath("surface-model.ifc");

    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
	
	void compareImageWithView(const std::string filename) {

	// Arrange
	const auto expected = buw::loadImage4b(testPath(filename).string());

	// Act
	const buw::Image4b image = renderer->captureImage();

	// Assert
	EXPECT_EQ(image, expected);

	// Annihilate
	}
};

TEST_F(SurfaceModelTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(55));
}

/*TEST_F(ExtrudedSolidTest, AllEntitiesAreRead) {
	EXPECT_THAT(xpress_model->entities, Eq('Liebich'));
		
}*/

TEST_F(SurfaceModelTest, ImageIsCaptured)
{
	// Arrange & Act
	buw::Image4b image = CaptureImage();

	// Assert
	EXPECT_NE(image, _background);
}

TEST_F(SurfaceModelTest, ImageIsSaved)
{
    // Arrange
    buw::Image4b image = CaptureImage();

    // Act
    buw::storeImage(testPath("surface-model.png").string(), image);

    // Assert
    EXPECT_NO_THROW(buw::loadImage4b(testPath("surface-model.png").string()));
}

TEST_F(SurfaceModelTest, TopView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Top);
    buw::Image4b image = renderer->captureImage();

    // Act
	buw::storeImage(testPath("surface-model_top.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
}

TEST_F(SurfaceModelTest, FrontView)
{
	// Arrange
	renderer->setViewDirection(buw::eViewDirection::Front);
	buw::Image4b image = renderer->captureImage();

	 // Act
	buw::storeImage(testPath("surface-model_front.png").string(), image);

	// Assert
	EXPECT_NE(image, _background);
}

TEST_F(SurfaceModelTest, BottomView)
{
	// Arrange
	renderer->setViewDirection(buw::eViewDirection::Bottom);
	buw::Image4b image = renderer->captureImage();

	// Act
	buw::storeImage(testPath("surface-model_bottom.png").string(), image);

	// Assert
	EXPECT_NE(image, _background);
}

TEST_F(SurfaceModelTest, GivenNewImage_AfterHome_AreEqual)
{
	compareImageWithView("surface-model.png");
}

TEST_F(SurfaceModelTest, GivenNewImage_AfterHome_AreEqual_Top)
{
	renderer->setViewDirection(buw::eViewDirection::Top);
	compareImageWithView("surface-model_top.png");
}

TEST_F(SurfaceModelTest, GivenNewImage_AfterHome_AreEqual_Front)
{
	renderer->setViewDirection(buw::eViewDirection::Front);
	compareImageWithView("surface-model_front.png");
}

TEST_F(SurfaceModelTest, GivenNewImage_AfterHome_AreEqual_Bottom)
{
	renderer->setViewDirection(buw::eViewDirection::Bottom);
	compareImageWithView("surface-model_bottom.png");
}

