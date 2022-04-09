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

#include <namespace.h>

#include <PointCloudVisualTest.h>

//#include <PointCloudProcessing\src\PointCloud.h>


using namespace testing;


class CloudRoad : public PointCloudVisualTest
{
protected:

	// Test standard values
	buw::Image4b _background = buw::Image4b(0, 0);

	virtual void SetUp() override {
		PointCloudVisualTest::SetUp();
		std::string str = filename.string();
		const char* c = str.c_str();
		auto model = buw::PointCloud::FromFile(c, true);


		_background = rendererPointCloud->captureImage();
			rendererPointCloud->setModel(model);
	}

	virtual void TearDown() override {
		model.reset();
		PointCloudVisualTest::TearDown();
	}

	virtual std::string TestName() const { return "Cloud_Road"; }
	virtual std::string FileType() const { return "BIN"; }

	const boost::filesystem::path filename = dataPath("Cloud_Road.bin");
	buw::ReferenceCounted<oip::PointCloud> model = buw::makeReferenceCounted<oip::PointCloud>();
};

//TEST_F(CloudRoad, AllEdgesAndFacesRed)
//{
//	// check for the number of vertices 
//	// does not coincide with the number of vertices mentioned in the off file since some vertices are
//	// stored once for every triangle they are part of
//	EXPECT_THAT(model->geometry().vertices.size(), Eq(324));
//	// check for the number of indices (see comment for vertices)
//	EXPECT_THAT(model->geometry().indices.size(), Eq(324));
//}

TEST_F(CloudRoad, ImageIsSaved)
{
	// Arrange
	buw::Image4b image = rendererPointCloud->captureImage();

	// Act
    buw::storeImage(testPath("Cloud_Road.png").string(), image);

	// Assert
    EXPECT_NO_THROW(buw::loadImage4b(testPath("Cloud_Road.png").string()));
}

TEST_F(CloudRoad, PlaneSurfaceViews)
{
	// Arrange
    const auto expected_front = buw::loadImage4b(dataPath("Cloud_Road_front.png").string());
    const auto expected_top = buw::loadImage4b(dataPath("Cloud_Road_top.png").string());
    const auto expected_bottom = buw::loadImage4b(dataPath("Cloud_Road_bottom.png").string());
    const auto expected_left = buw::loadImage4b(dataPath("Cloud_Road_left.png").string());
    const auto expected_right = buw::loadImage4b(dataPath("Cloud_Road_right.png").string());
    const auto expected_back = buw::loadImage4b(dataPath("Cloud_Road_back.png").string());

	// Act (Front)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Front);
	buw::Image4b image_front = CaptureImage();
	// Act (Top)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Top);
	buw::Image4b image_top = CaptureImage();
	// Act (Bottom)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Bottom);
	buw::Image4b image_bottom = CaptureImage();
	// Act (Left)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Left);
	buw::Image4b image_left = CaptureImage();
	// Act (Right)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Right);
	buw::Image4b image_right = CaptureImage();
	// Act (Back)
	rendererPointCloud->setViewDirection(buw::eViewDirection::Back);
	buw::Image4b image_back = CaptureImage();

	// uncomment following lines to also save the screen shot

    //buw::storeImage(testPath("Cloud_Road_front.png").string(), image_front);
    //buw::storeImage(testPath("Cloud_Road_top.png").string(), image_top);
    //buw::storeImage(testPath("Cloud_Road_bottom.png").string(), image_bottom);
    //buw::storeImage(testPath("Cloud_Road_left.png").string(), image_left);
    //buw::storeImage(testPath("Cloud_Road_right.png").string(), image_right);
    //buw::storeImage(testPath("Cloud_Road_back.png").string(), image_back);


	// Assert
	EXPECT_EQ(image_front, expected_front);
	EXPECT_EQ(image_top, expected_top);
	EXPECT_EQ(image_bottom, expected_bottom);
	EXPECT_EQ(image_left, expected_left);
	EXPECT_EQ(image_right, expected_right);
	EXPECT_EQ(image_back, expected_back);
}

TEST_F(CloudRoad, VertexViews)
{
	// Arrange
    const auto expected_front_left_bottom = buw::loadImage4b(dataPath("Cloud_Road_front_left_bottom.png").string());
    const auto expected_front_right_bottom = buw::loadImage4b(dataPath("Cloud_Road_front_right_bottom.png").string());
    const auto expected_top_left_front = buw::loadImage4b(dataPath("Cloud_Road_top_left_front.png").string());
    const auto expected_top_front_right = buw::loadImage4b(dataPath("Cloud_Road_top_front_right.png").string());
    const auto expected_top_left_back = buw::loadImage4b(dataPath("Cloud_Road_top_left_back.png").string());
    const auto expected_top_right_back = buw::loadImage4b(dataPath("Cloud_Road_top_right_back.png").string());
    const auto expected_back_left_bottom = buw::loadImage4b(dataPath("Cloud_Road_back_left_bottom.png").string());
    const auto expected_right_bottom_back = buw::loadImage4b(dataPath("Cloud_Road_right_bottom_back.png").string());

	// Act (FrontLeftBottom)
	rendererPointCloud->setViewDirection(buw::eViewDirection::FrontLeftBottom);
	buw::Image4b image_front_left_bottom = CaptureImage();
	// Act (FrontRightBottom)
	rendererPointCloud->setViewDirection(buw::eViewDirection::FrontRightBottom);
	buw::Image4b image_front_right_bottom = CaptureImage();
	// Act (TopLeftFront)
	rendererPointCloud->setViewDirection(buw::eViewDirection::TopLeftFront);
	buw::Image4b image_top_left_front = CaptureImage();
	// Act (TopFrontRight)
	rendererPointCloud->setViewDirection(buw::eViewDirection::TopFrontRight);
	buw::Image4b image_top_front_right = CaptureImage();
	// Act (TopLeftBack)
	rendererPointCloud->setViewDirection(buw::eViewDirection::TopLeftBack);
	buw::Image4b image_top_left_back = CaptureImage();
	// Act (TopRightBack)
	rendererPointCloud->setViewDirection(buw::eViewDirection::TopRightBack);
	buw::Image4b image_top_right_back = CaptureImage();
	// Act (BackLeftBottom)
	rendererPointCloud->setViewDirection(buw::eViewDirection::BackLeftBottom);
	buw::Image4b image_back_left_bottom = CaptureImage();
	// Act (RightBottomBack)
	rendererPointCloud->setViewDirection(buw::eViewDirection::RightBottomBack);
	buw::Image4b image_right_bottom_back = CaptureImage();

	// uncomment following lines to also save the screen shot
	
   // buw::storeImage(testPath("Cloud_Road_front_left_bottom.png").string(), image_front_left_bottom);
   // buw::storeImage(testPath("Cloud_Road_front_right_bottom.png").string(), image_front_right_bottom);
   // buw::storeImage(testPath("Cloud_Road_top_left_front.png").string(), image_top_left_front);
   // buw::storeImage(testPath("Cloud_Road_top_front_right.png").string(), image_top_front_right);
   // buw::storeImage(testPath("Cloud_Road_top_left_back.png").string(), image_top_left_back);
   // buw::storeImage(testPath("Cloud_Road_top_right_back.png").string(), image_top_right_back);
   // buw::storeImage(testPath("Cloud_Road_back_left_bottom.png").string(), image_back_left_bottom);
   // buw::storeImage(testPath("Cloud_Road_right_bottom_back.png").string(), image_right_bottom_back);


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


