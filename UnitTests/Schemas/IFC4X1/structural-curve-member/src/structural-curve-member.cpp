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

#include <EarlyBinding/IFC4X1/src/reader/IFC4X1Reader.h>
#include <namespace.h>

#include <IfcVisualTest.h>

#include <IfcGeometryConverter/IfcImporterImpl.h>
#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>

using namespace testing;


class StructuralCurveMember : public IfcVisualTest {
protected:

	// Test standard values
	buw::Image4b _background = buw::Image4b(0, 0);

	virtual void SetUp() override {
                IfcVisualTest::SetUp();

		express_model = OpenInfraPlatform::IFC4X1::IFC4X1Reader::FromFile(filename.string());

		importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>>();
		model = importer->collectData(express_model);

		_background = renderer->captureImage();
		renderer->setModel(model);

	}

	virtual void TearDown() override {
		express_model.reset();
                IfcVisualTest::TearDown();
	}

	virtual std::string TestName() const { return "structural-curve-member"; }
	virtual std::string Schema() const { return "IFC4x1"; }

	const boost::filesystem::path filename = dataPath("structural-curve-member.ifc");

	std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
	buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
	buw::ReferenceCounted<oip::IfcModel> model = buw::makeReferenceCounted<oip::IfcModel>();
};

TEST_F(StructuralCurveMember, AllEntitiesAreRead) {
	EXPECT_THAT(express_model->entities.size(), Eq(188));
}

TEST_F(StructuralCurveMember, IFCHasAnEssentialEntity) {
	auto result1 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSTRUCTURALPOINTCONNECTION"; });
	auto result2 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSTRUCTURALCURVEMEMBER"; });
	auto result3 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSTRUCTURALANALYSISMODEL"; });
	auto result4 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCRELCONNECTSSTRUCTURALACTIVITY"; });
	auto result5 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCRELCONNECTSSTRUCTURALMEMBER"; });

	EXPECT_NE(result1, express_model->entities.end());
	EXPECT_NE(result2, express_model->entities.end());
	EXPECT_NE(result3, express_model->entities.end());
	EXPECT_NE(result4, express_model->entities.end());
	EXPECT_NE(result5, express_model->entities.end());
}

TEST_F(StructuralCurveMember, CountEssentialEntities) {
	auto result1 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSTRUCTURALPOINTCONNECTION"; });
	auto result2 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCSTRUCTURALCURVEMEMBER"; });
	auto result3 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCRELCONNECTSSTRUCTURALACTIVITY"; });
	auto result4 = std::count_if(express_model->entities.begin(), express_model->entities.end(), [](auto &pair) -> bool { return pair.second->classname() == "IFCRELCONNECTSSTRUCTURALMEMBER"; });

	EXPECT_EQ(result1, 4);
	EXPECT_EQ(result2, 3);
	EXPECT_EQ(result3, 10);
	EXPECT_EQ(result4, 6);
}


TEST_F(StructuralCurveMember, ImageIsSaved)
{
	// Arrange
	buw::Image4b image = renderer->captureImage();

	// Act
	buw::storeImage(testPath("structural-curve-member.png").string(), image);

	// Assert
	EXPECT_NO_THROW(buw::loadImage4b(testPath("structural-curve-member.png").string()));
}

TEST_F(StructuralCurveMember, PlaneSurfaceViews)
{
	// Arrange
	const auto expected_front = buw::loadImage4b(dataPath("structural-curve-member_front.png").string());
	const auto expected_top = buw::loadImage4b(dataPath("structural-curve-member_top.png").string());
	const auto expected_bottom = buw::loadImage4b(dataPath("structural-curve-member_bottom.png").string());
	const auto expected_left = buw::loadImage4b(dataPath("structural-curve-member_left.png").string());
	const auto expected_right = buw::loadImage4b(dataPath("structural-curve-member_right.png").string());
	const auto expected_back = buw::loadImage4b(dataPath("structural-curve-member_back.png").string());

	// Act (Front)
	renderer->setViewDirection(buw::eViewDirection::Front);
	buw::Image4b image_front = CaptureImage();
	// Act (Top)
	renderer->setViewDirection(buw::eViewDirection::Top);
	buw::Image4b image_top = CaptureImage();
	// Act (Bottom)
	renderer->setViewDirection(buw::eViewDirection::Bottom);
	buw::Image4b image_bottom = CaptureImage();
	// Act (Left)
	renderer->setViewDirection(buw::eViewDirection::Left);
	buw::Image4b image_left = CaptureImage();
	// Act (Right)
	renderer->setViewDirection(buw::eViewDirection::Right);
	buw::Image4b image_right = CaptureImage();
	// Act (Back)
	renderer->setViewDirection(buw::eViewDirection::Back);
	buw::Image4b image_back = CaptureImage();

	// uncomment following lines to also save the screen shot
	/*
	buw::storeImage(testPath("structural-curve-member_front.png").string(), image_front);
	buw::storeImage(testPath("structural-curve-member_top.png").string(), image_top);
	buw::storeImage(testPath("structural-curve-member_bottom.png").string(), image_bottom);
	buw::storeImage(testPath("structural-curve-member_left.png").string(), image_left);
	buw::storeImage(testPath("structural-curve-member_right.png").string(), image_right);
	buw::storeImage(testPath("structural-curve-member_back.png").string(), image_back);
	*/

	// Assert
	EXPECT_EQ(image_front, expected_front);
	EXPECT_EQ(image_top, expected_top);
	EXPECT_EQ(image_bottom, expected_bottom);
	EXPECT_EQ(image_left, expected_left);
	EXPECT_EQ(image_right, expected_right);
	EXPECT_EQ(image_back, expected_back);
}

TEST_F(StructuralCurveMember, VertexViews)
{
	// Arrange
	const auto expected_front_left_bottom = buw::loadImage4b(dataPath("structural-curve-member_front_left_bottom.png").string());
	const auto expected_front_right_bottom = buw::loadImage4b(dataPath("structural-curve-member_front_right_bottom.png").string());
	const auto expected_top_left_front = buw::loadImage4b(dataPath("structural-curve-member_top_left_front.png").string());
	const auto expected_top_front_right = buw::loadImage4b(dataPath("structural-curve-member_top_front_right.png").string());
	const auto expected_top_left_back = buw::loadImage4b(dataPath("structural-curve-member_top_left_back.png").string());
	const auto expected_top_right_back = buw::loadImage4b(dataPath("structural-curve-member_top_right_back.png").string());
	const auto expected_back_left_bottom = buw::loadImage4b(dataPath("structural-curve-member_back_left_bottom.png").string());
	const auto expected_right_bottom_back = buw::loadImage4b(dataPath("structural-curve-member_right_bottom_back.png").string());

	// Act (FrontLeftBottom)
	renderer->setViewDirection(buw::eViewDirection::FrontLeftBottom);
	buw::Image4b image_front_left_bottom = CaptureImage();
	// Act (FrontRightBottom)
	renderer->setViewDirection(buw::eViewDirection::FrontRightBottom);
	buw::Image4b image_front_right_bottom = CaptureImage();
	// Act (TopLeftFront)
	renderer->setViewDirection(buw::eViewDirection::TopLeftFront);
	buw::Image4b image_top_left_front = CaptureImage();
	// Act (TopFrontRight)
	renderer->setViewDirection(buw::eViewDirection::TopFrontRight);
	buw::Image4b image_top_front_right = CaptureImage();
	// Act (TopLeftBack)
	renderer->setViewDirection(buw::eViewDirection::TopLeftBack);
	buw::Image4b image_top_left_back = CaptureImage();
	// Act (TopRightBack)
	renderer->setViewDirection(buw::eViewDirection::TopRightBack);
	buw::Image4b image_top_right_back = CaptureImage();
	// Act (BackLeftBottom)
	renderer->setViewDirection(buw::eViewDirection::BackLeftBottom);
	buw::Image4b image_back_left_bottom = CaptureImage();
	// Act (RightBottomBack)
	renderer->setViewDirection(buw::eViewDirection::RightBottomBack);
	buw::Image4b image_right_bottom_back = CaptureImage();

	// uncomment following lines to also save the screen shot
	/*
	buw::storeImage(testPath("structural-curve-member_front_left_bottom.png").string(), image_front_left_bottom);
	buw::storeImage(testPath("structural-curve-member_front_right_bottom.png").string(), image_front_right_bottom);
	buw::storeImage(testPath("structural-curve-member_top_left_front.png").string(), image_top_left_front);
	buw::storeImage(testPath("structural-curve-member_top_front_right.png").string(), image_top_front_right);
	buw::storeImage(testPath("structural-curve-member_top_left_back.png").string(), image_top_left_back);
	buw::storeImage(testPath("structural-curve-member_top_right_back.png").string(), image_top_right_back);
	buw::storeImage(testPath("structural-curve-member_back_left_bottom.png").string(), image_back_left_bottom);
	buw::storeImage(testPath("structural-curve-member_right_bottom_back.png").string(), image_right_bottom_back);
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


