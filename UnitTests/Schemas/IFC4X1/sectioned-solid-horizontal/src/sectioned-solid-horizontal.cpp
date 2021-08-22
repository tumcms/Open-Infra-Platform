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

#include <EarlyBinding/IFC4X1/src/reader/IFC4X1Reader.h>
#include <namespace.h>

#include <IfcVisualTest.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

using namespace testing;


class SectionedSolidHorizontal : public IfcVisualTest {
protected:

	// Test standard values
	buw::Image4b _background = buw::Image4b(0, 0);

	virtual void SetUp() override {
                IfcVisualTest::SetUp();

		express_model = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename.string());

		importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>>();
		auto model = importer->collectData(express_model);

		_background = rendererIfc->captureImage();
		rendererIfc->setModel(model[0]);
	}

	virtual void TearDown() override {
		express_model.reset();
                IfcVisualTest::TearDown();
	}

	virtual std::string TestName() const { return "sectioned-solid-horizontal"; }
	virtual std::string Schema() const { return "IFC4x1"; }

	const boost::filesystem::path filename = dataPath("sectioned-solid-horizontal.ifc");

	std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
	buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
};

TEST_F(SectionedSolidHorizontal, AllEntitiesAreRead) {
	EXPECT_THAT(express_model->entities.size(), Eq(302));
}
/*
TEST_F(SectionedSolidHorizontal, IFCHasAnEssentialEntity) {
	auto result1 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSECTIONEDSOLIDHORIZONTAL"; });
	auto result2 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCARBITRARYCLOSEDPROFILEDEF"; });
	auto result3 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCINDEXEDPOLYCURVE"; });
	auto result4 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCPOLYLINE"; });
	auto result5 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCALIGNMENTCURVE"; });

	EXPECT_NE(result1, express_model->entities.end());
	EXPECT_NE(result2, express_model->entities.end());
	EXPECT_NE(result3, express_model->entities.end());
	EXPECT_NE(result4, express_model->entities.end());
	EXPECT_NE(result5, express_model->entities.end());
}

TEST_F(SectionedSolidHorizontal, CountEssentialEntities) {
	auto result1 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSECTIONEDSOLIDHORIZONTAL"; });
	auto result2 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCARBITRARYCLOSEDPROFILEDEF"; });
	auto result3 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCINDEXEDPOLYCURVE"; });
	
	EXPECT_EQ(result1, 16);
	EXPECT_EQ(result2, 49);
	EXPECT_EQ(result3, 49);
}
*/

TEST_F(SectionedSolidHorizontal ImageIsSaved)
{
	// Arrange
	buw::Image4b image = rendererIfc->captureImage();

	// Act
	buw::storeImage(testPath("sectioned-solid-horizontal.png").string(), image);

	// Assert
	EXPECT_NO_THROW(buw::loadImage4b(testPath("sectioned-solid-horizontal.png").string()));
}

TEST_F(SectionedSolidHorizontal, PlaneSurfaceViews)
{
	// Arrange
	const auto expected_front = buw::loadImage4b(dataPath("sectioned-solid-horizontal_front.png").string());
	const auto expected_top = buw::loadImage4b(dataPath("sectioned-solid-horizontal_top.png").string());
	const auto expected_bottom = buw::loadImage4b(dataPath("sectioned-solid-horizontal_bottom.png").string());
	const auto expected_left = buw::loadImage4b(dataPath("sectioned-solid-horizontal_left.png").string());
	const auto expected_right = buw::loadImage4b(dataPath("sectioned-solid-horizontal_right.png").string());
	const auto expected_back = buw::loadImage4b(dataPath("sectioned-solid-horizontal_back.png").string());

	// Act (Front)
	rendererIfc->setViewDirection(buw::eViewDirection::Front);
	buw::Image4b image_front = CaptureImage();
	// Act (Top)
	rendererIfc->setViewDirection(buw::eViewDirection::Top);
	buw::Image4b image_top = CaptureImage();
	// Act (Bottom)
	rendererIfc->setViewDirection(buw::eViewDirection::Bottom);
	buw::Image4b image_bottom = CaptureImage();
	// Act (Left)
	rendererIfc->setViewDirection(buw::eViewDirection::Left);
	buw::Image4b image_left = CaptureImage();
	// Act (Right)
	rendererIfc->setViewDirection(buw::eViewDirection::Right);
	buw::Image4b image_right = CaptureImage();
	// Act (Back)
	rendererIfc->setViewDirection(buw::eViewDirection::Back);
	buw::Image4b image_back = CaptureImage();

	// uncomment following lines to also save the screen shot
	/*
	buw::storeImage(testPath("sectioned-solid-horizontal_front.png").string(), image_front);
	buw::storeImage(testPath("sectioned-solid-horizontal_top.png").string(), image_top);
	buw::storeImage(testPath("sectioned-solid-horizontal_bottom.png").string(), image_bottom);
	buw::storeImage(testPath("sectioned-solid-horizontal_left.png").string(), image_left);
	buw::storeImage(testPath("sectioned-solid-horizontal_right.png").string(), image_right);
	buw::storeImage(testPath("sectioned-solid-horizontal_back.png").string(), image_back);
	*/

	// Assert
	EXPECT_EQ(image_front, expected_front);
	EXPECT_EQ(image_top, expected_top);
	EXPECT_EQ(image_bottom, expected_bottom);
	EXPECT_EQ(image_left, expected_left);
	EXPECT_EQ(image_right, expected_right);
	EXPECT_EQ(image_back, expected_back);
}

TEST_F(SectionedSolidHorizontal, VertexViews)
{
	// Arrange
	const auto expected_front_left_bottom = buw::loadImage4b(dataPath("sectioned-solid-horizontal_front_left_bottom.png").string());
	const auto expected_front_right_bottom = buw::loadImage4b(dataPath("sectioned-solid-horizontal_front_right_bottom.png").string());
	const auto expected_top_left_front = buw::loadImage4b(dataPath("sectioned-solid-horizontal_top_left_front.png").string());
	const auto expected_top_front_right = buw::loadImage4b(dataPath("sectioned-solid-horizontal_top_front_right.png").string());
	const auto expected_top_left_back = buw::loadImage4b(dataPath("sectioned-solid-horizontal_top_left_back.png").string());
	const auto expected_top_right_back = buw::loadImage4b(dataPath("sectioned-solid-horizontal_top_right_back.png").string());
	const auto expected_back_left_bottom = buw::loadImage4b(dataPath("sectioned-solid-horizontal_back_left_bottom.png").string());
	const auto expected_right_bottom_back = buw::loadImage4b(dataPath("sectioned-solid-horizontal_right_bottom_back.png").string());

	// Act (FrontLeftBottom)
	rendererIfc->setViewDirection(buw::eViewDirection::FrontLeftBottom);
	buw::Image4b image_front_left_bottom = CaptureImage();
	// Act (FrontRightBottom)
	rendererIfc->setViewDirection(buw::eViewDirection::FrontRightBottom);
	buw::Image4b image_front_right_bottom = CaptureImage();
	// Act (TopLeftFront)
	rendererIfc->setViewDirection(buw::eViewDirection::TopLeftFront);
	buw::Image4b image_top_left_front = CaptureImage();
	// Act (TopFrontRight)
	rendererIfc->setViewDirection(buw::eViewDirection::TopFrontRight);
	buw::Image4b image_top_front_right = CaptureImage();
	// Act (TopLeftBack)
	rendererIfc->setViewDirection(buw::eViewDirection::TopLeftBack);
	buw::Image4b image_top_left_back = CaptureImage();
	// Act (TopRightBack)
	rendererIfc->setViewDirection(buw::eViewDirection::TopRightBack);
	buw::Image4b image_top_right_back = CaptureImage();
	// Act (BackLeftBottom)
	rendererIfc->setViewDirection(buw::eViewDirection::BackLeftBottom);
	buw::Image4b image_back_left_bottom = CaptureImage();
	// Act (RightBottomBack)
	rendererIfc->setViewDirection(buw::eViewDirection::RightBottomBack);
	buw::Image4b image_right_bottom_back = CaptureImage();

	// uncomment following lines to also save the screen shot
	/*
	buw::storeImage(testPath("sectioned-solid-horizontal_front_left_bottom.png").string(), image_front_left_bottom);
	buw::storeImage(testPath("sectioned-solid-horizontal_front_right_bottom.png").string(), image_front_right_bottom);
	buw::storeImage(testPath("sectioned-solid-horizontal_top_left_front.png").string(), image_top_left_front);
	buw::storeImage(testPath("sectioned-solid-horizontal_top_front_right.png").string(), image_top_front_right);
	buw::storeImage(testPath("sectioned-solid-horizontal_top_left_back.png").string(), image_top_left_back);
	buw::storeImage(testPath("sectioned-solid-horizontal_top_right_back.png").string(), image_top_right_back);
	buw::storeImage(testPath("sectioned-solid-horizontal_back_left_bottom.png").string(), image_back_left_bottom);
	buw::storeImage(testPath("sectioned-solid-horizontal_right_bottom_back.png").string(), image_right_bottom_back);
	*/

	// Assert
	EXPECT_EQ(image_front_left_bottom, expected_front_left_bottom);
	EXPECT_EQ(image_front_right_bottom, expected_front_right_bottom);
	EXPECT_EQ(image_top_left_front, expected_top_left_front);
	EXPECT_EQ(image_top_front_right, expected_top_front_right);
	EXPECT_EQ(image_top_left_back, expected_top_left_back);
	EXPECT_EQ(image_top_right_back, expected_top_right_back);
	EXPECT_EQ(image_back_left_bottom, expected_back_left_bottom);
	EXPECT_EQ(image_right_bottom_back, expected_right_bottom_back);
}


