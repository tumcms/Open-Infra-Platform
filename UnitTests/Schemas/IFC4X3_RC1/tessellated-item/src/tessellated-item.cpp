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

#include <EarlyBinding\IFC4X3_RC1\src\reader\IFC4X3_RC1Reader.h>
#include <namespace.h>

#include <IfcVisualTest.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

using namespace testing;

class TessellatedItemTest : public IfcVisualTest {
    protected:

    // Test standard values
    buw::Image4b _background = buw::Image4b(0, 0);

    virtual void SetUp() override {
        IfcVisualTest::SetUp();

        express_model = OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader::FromFile(filename.string());

        importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>>(); 
		model = importer->collectData(express_model);

        _background = CaptureImage();
        renderer->setModel(model);

    }

    virtual void TearDown() override {
        express_model.reset();
        IfcVisualTest::TearDown();
    }

	virtual std::string TestName() const { return "tessellated-item"; }
	virtual std::string Schema() const { return "IFC4X3_RC1"; }

    const boost::filesystem::path filename = dataPath("tessellated-item.ifc");

    const boost::filesystem::path baseImageFilename_ = dataPath("tessellated-item.png");


    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcModel> model = buw::makeReferenceCounted<oip::IfcModel>();
};

TEST_F(TessellatedItemTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(29));
}

TEST_F(TessellatedItemTest, ImageIsSaved)
{
    // Arrange
    buw::Image4b image = CaptureImage();

    // Act
    buw::storeImage(testPath("tessellated-item.png").string(), image);

    // Assert
    EXPECT_NE(image,_background);
}

TEST_F(TessellatedItemTest, TopView)
{
    // Arrange
	const auto expected = buw::loadImage4b(dataPath("tessellated-item_top.png").string());

    // Act
	renderer->setViewDirection(buw::eViewDirection::Top);
    buw::Image4b image = CaptureImage();

	// uncomment the following line to also save the screen shot
    //buw::storeImage(testPath("\\tessellated-item_top.png").string(), image);

    // Assert
    EXPECT_EQ(image, expected);
}

TEST_F(TessellatedItemTest, GivenNewImage_AfterHome_AreEqual)
{
    // Arrange
    const auto expected = buw::loadImage4b(baseImageFilename_.string());

    // Act
    const buw::Image4b image = CaptureImage();

    // Assert
    EXPECT_EQ(image, expected);

    // Annihilate
}
