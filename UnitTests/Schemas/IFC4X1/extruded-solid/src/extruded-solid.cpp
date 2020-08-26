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

	virtual std::string TestName() const { return "extruded-solid"; }
	virtual std::string Schema() const { return "IFC4X1"; }

	const boost::filesystem::path filename = dataPath("extruded-solid.ifc");

    std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
    buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X1EntityTypes>> importer = nullptr;
    buw::ReferenceCounted<oip::IfcGeometryModel> model = buw::makeReferenceCounted<oip::IfcGeometryModel>();
	
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
    buw::storeImage(testPath("extruded-solid.png").string(), image);

    // Assert
	EXPECT_NO_THROW(buw::loadImage4b(testPath("extruded-solid.png").string()));
}

{


}

{
	// Arrange


	// Assert
}

{
	// Arrange
	renderer->setViewDirection(buw::eViewDirection::Bottom);

	// Assert


}

{


