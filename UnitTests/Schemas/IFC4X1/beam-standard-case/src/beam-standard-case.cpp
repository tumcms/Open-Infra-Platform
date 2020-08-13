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
#include <VisualTest.h>

#include <buw.Engine.h>
#include <buw.ImageProcessing.h>

#include <IfcGeometryConverter/IfcImporterImpl.h>
#include <IfcGeometryConverter/ConverterBuw.h>

#include <boost/dll/runtime_symbol_info.hpp>

using namespace testing;


class BeamStandardCaseTest : public VisualTest {
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

    const boost::filesystem::path filename = boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\beam-standard-case\\Data\\beam-standard-case.ifc");

    const boost::filesystem::path baseImageFilename_ = boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4x1\\beam-standard-case\\Data\\beam-standard-case.png");


    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
};

TEST_F(BeamStandardCaseTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(29));
}

TEST_F(BeamStandardCaseTest, ImageIsSaved)
{
    // Arrange
    buw::Image4b image = renderer->captureImage();

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\beam-standard-case.png").string(), image);

    // Assert
    EXPECT_NE(image,_background);
}

TEST_F(BeamStandardCaseTest, TopView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Top);
    buw::Image4b image = renderer->captureImage();

    const auto expected = buw::loadImage4b(boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\beam-standard-case\\Data\\beam-standard-case.png").string());

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\beam-standard-case_top.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
    EXPECT_EQ(image, expected);
}

TEST_F(BeamStandardCaseTest, BottomView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Bottom);
    buw::Image4b image = renderer->captureImage();

    const auto expected = buw::loadImage4b(boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\beam-standard-case\\Data\\beam-standard-case_bottom.png").string());

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\beam-standard-case_bottom.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
    EXPECT_EQ(image, expected);
}

TEST_F(BeamStandardCaseTest, LeftView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Left);
    buw::Image4b image = renderer->captureImage();

    const auto expected = buw::loadImage4b(boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\beam-standard-case\\Data\\beam-standard-case_left.png").string());

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\beam-standard-case_left.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
    EXPECT_EQ(image, expected);
}

TEST_F(BeamStandardCaseTest, RightView)
{
    // Arrange
    renderer->setViewDirection(buw::eViewDirection::Right);
    buw::Image4b image = renderer->captureImage();

    const auto expected = buw::loadImage4b(boost::dll::program_location().parent_path().concat("\\UnitTests\\Schemas\\IFC4X1\\beam-standard-case\\Data\\beam-standard-case_right.png").string());

    // Act
    buw::storeImage(boost::dll::program_location().parent_path().concat("\\beam-standard-case_right.png").string(), image);

    // Assert
    EXPECT_NE(image, _background);
    EXPECT_EQ(image, expected);
}

TEST_F(BeamStandardCaseTest, GivenNewImage_AfterHome_AreEqual)
{
    // Arrange
    const auto expected = buw::loadImage4b(baseImageFilename_.string());

    // Act
    const buw::Image4b image = renderer->captureImage();

    // Assert
    EXPECT_EQ(image, expected);

    // Annihilate
}
