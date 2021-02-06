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

#include <EarlyBinding\IFC4X3_RC1\src\reader\IFC4X3_RC1Reader.h>
#include <namespace.h>

#include <VisualTest.h>

#include <IfcGeometryConverter/ConverterBuw.h>
#include <IfcGeometryConverter/IfcImporter.h>
#include <IfcGeometryConverter/IfcImporterImpl.h>


using namespace testing;

class BasinFacetedBrepTest : public VisualTest {
protected:
	// Test standard values
	buw::Image4b _background = buw::Image4b(0, 0);

	virtual void SetUp() override {
		VisualTest::SetUp();

		express_model = OpenInfraPlatform::IFC4X3_RC1::IFC4X3_RC1Reader::FromFile(filename.string());

		importer = buw::makeReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>>();
		model = importer->collectData(express_model);

		_background = CaptureImage();
		renderer->setModel(model);

	}

	virtual void TearDown() override {
		express_model.reset();
		VisualTest::TearDown();
	}

	virtual std::string TestName() const { return "basin-faceted-brep"; }
	virtual std::string Schema() const { return "IFC4X3_RC1"; }

	const boost::filesystem::path filename = dataPath("basin-faceted-brep.ifc");

	const boost::filesystem::path baseImageFilename_ = dataPath("basin-faceted-brep.png");


	std::shared_ptr<oip::EXPRESSModel> express_model = nullptr;
	buw::ReferenceCounted<oip::IfcImporterT<emt::IFC4X3_RC1EntityTypes>> importer = nullptr;
	buw::ReferenceCounted<oip::IfcModel> model = buw::makeReferenceCounted<oip::IfcModel>();

};

TEST_F(BasinFacetedBrepTest, AllEntitiesAreRead) {
    EXPECT_THAT(express_model->entities.size(), Eq(31));
}
