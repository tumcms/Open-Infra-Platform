/*
    Copyright (c) 2017 Technical University of Munich
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

#include "buw.OIPInfrastructure.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;

namespace
{
	TEST(Okstra, ExportImport)
	{
		buw::ImportLandXml LandXMLImporter("../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		
		buw::ExportOkstra OkstraExporter(
			2, 
			16,
			LandXMLImporter.getAlignmentModel(),
			LandXMLImporter.getDigitalElevationModel(), 
			"test.xml"
		);

		buw::ImportOkstra OkstraImporter("test.xml");

		int alignmentCount1 = LandXMLImporter.getAlignmentModel()->getAlignmentCount();
		int alignmentCount2 = OkstraImporter.getAlignmentModel()->getAlignmentCount();

		buw::ReferenceCounted<buw::Alignment2DBased3D> a1 = std::static_pointer_cast<buw::Alignment2DBased3D>(LandXMLImporter.getAlignmentModel()->getAlignment(0));
		int alignmentElementCount1 = a1->getHorizontalAlignment()->getAlignmentElementCount();

		buw::ReferenceCounted<buw::Alignment2DBased3D> a2 = std::static_pointer_cast<buw::Alignment2DBased3D>(OkstraImporter.getAlignmentModel()->getAlignment(0));
		int alignmentElementCount2 = a2->getHorizontalAlignment()->getAlignmentElementCount();

		EXPECT_EQ(alignmentCount1, alignmentCount2);
		EXPECT_EQ(alignmentElementCount1, alignmentElementCount2);
	}
}