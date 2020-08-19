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

class TessellatedItem4x1Test : public VisualTest {
    protected:

    // Test standard values
    buw::Image4b _background = buw::Image4b(0, 0);

    virtual void SetUp() override {
        VisualTest::SetUp();

        express_model = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename.string());

        importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>>();
        importer->collectGeometryData(express_model);
        oip::ConverterBuwT<emt::IFC4X1EntityTypes>::createGeometryModel(model, importer->getShapeDatas());

        _background = CaptureImage();
        renderer->setModel(model);

    }

    virtual void TearDown() override {
        express_model.reset();
        VisualTest::TearDown();
    }

    virtual std::string TestName() const { return "tessellated-item"; }
    virtual std::string Schema() const { return "IFC4X1"; }

    const boost::filesystem::path filename = dataPath("tessellated-item.ifc");

    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
};

TEST_F(TessellatedItem4x1Test, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(29));
}

TEST_F(TessellatedItem4x1Test, ImageIsCaptured)
{
    // Arrange & Act
    buw::Image4b image = CaptureImage();

    // Assert
    EXPECT_NE(image,_background);
}

TEST_F(TessellatedItem4x1Test, ImageIsSaved)
{
	// Arrange & Act
	buw::Image4b image = CaptureImage();

	// Act
	buw::storeImage(testPath("tessellated-item.png").string(), image);

	// Assert
	EXPECT_NO_THROW(buw::loadImage4b(testPath("tessellated-item.png").string()));
}

TEST_F(TessellatedItem4x1Test, TopView)
{
    // Arrange
    const auto expected = buw::loadImage4b(dataPath("tessellated-item_top.png").string());

    // Act
    renderer->setViewDirection(buw::eViewDirection::Top);
    buw::Image4b image = CaptureImage();

    // uncomment the following line to also save the screen shot
    //buw::storeImage(testPath("tessellated-item_top.png").string(), image);

    // Assert
    EXPECT_EQ(image, expected);
}

TEST_F(TessellatedItem4x1Test, GivenNewImage_AfterHome_AreEqual)
{
    // Arrange
    const auto expected = buw::loadImage4b(dataPath("tessellated-item.png").string());

    // Act
    const buw::Image4b image = CaptureImage();

    // Assert
    EXPECT_EQ(image, expected);

    // Annihilate
}
