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

#include <EarlyBinding/IFC4X3_RC4/src/reader/IFC4X3_RC4Reader.h>
#include <namespace.h>

#include <IfcVisualTest.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>

using namespace testing;

class Line : public IfcVisualTest {
protected:

	// Test standard values
	buw::Image4b _background = buw::Image4b(0, 0);

	virtual void SetUp() override {
                IfcVisualTest::SetUp();

		express_model = OpenInfraPlatform::IFC4X3_RC4::IFC4X3_RC4Reader::FromFile(filename.string());

		importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC4EntityTypes>>();
		auto model = importer->collectData(express_model);

		_background = rendererIfc->captureImage();
		rendererIfc->setModel(model[0]);
	}

	virtual void TearDown() override {
		express_model.reset();
                IfcVisualTest::TearDown();
	}

	virtual std::string TestName() const { return "line_100.0_inf_300_1_Meter"; }
	virtual std::string Schema() const { return "IFC4X3_RC4"; }

	const boost::filesystem::path filename = dataPath("line_100.0_inf_300_1_Meter.ifc");

	std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
	buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC4EntityTypes>> importer = nullptr;
};

TEST_F(Line, AllEntitiesAreRead) {
	EXPECT_THAT(express_model->entities.size(), Eq(73));
}

TEST_F(Line, IFCHasAnEssentialEntity) {
	auto result1 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto& pair) -> bool { return pair.second->classname() == "IFCCURVESEGMENT"; });
	auto result2 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto& pair) -> bool { return pair.second->classname() == "IFCALIGNMENTHORIZONTAL"; });
	auto result3 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto& pair) -> bool { return pair.second->classname() == "IFCALIGNMENTHORIZONTALSEGMENT"; });
	auto result4 = std::find_if(express_model->entities.begin(), express_model->entities.end(), [](auto& pair) -> bool { return pair.second->classname() == "IFCLINE"; });
	EXPECT_NE(result1, express_model->entities.end());
	EXPECT_NE(result2, express_model->entities.end());
	EXPECT_NE(result3, express_model->entities.end());
	EXPECT_NE(result4, express_model->entities.end());
}

TEST_F(Line, ImageIsSaved)
{
	// Arrange
	buw::Image4b image = rendererIfc->captureImage();

	// Act
	buw::storeImage(testPath("line_100.0_inf_300_1_Meter.png").string(), image);

	// Assert
	EXPECT_NO_THROW(buw::loadImage4b(testPath("line_100.0_inf_300_1_Meter.png").string()));
}

TEST_F(Line, PlaneSurfaceViews)
{
	// Arrange
	const auto expected_top = buw::loadImage4b(dataPath("line_100.0_inf_300_1_Meter_top.png").string());

	// Act (Top)
	rendererIfc->setViewDirection(buw::eViewDirection::Top);
	buw::Image4b image_top = CaptureImage();


	// uncomment following lines to also save the screen shot
	//buw::storeImage(testPath("line_100.0_inf_300_1_Meter_top.png").string(), image_top);

	// Assert
	EXPECT_EQ(image_top, expected_top);
}