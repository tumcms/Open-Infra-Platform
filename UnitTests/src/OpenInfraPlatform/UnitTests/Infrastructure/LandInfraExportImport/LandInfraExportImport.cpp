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

#include <QtXml>

#define __EXPORT


using namespace std;

namespace
{
#ifdef __IMPORT
	TEST(LandInfra, Import)
	{
		buw::ImportLandInfra landInfraImporter("../../../../../../testdata/LandInfra/complete_alignment_example_20170321_pxs.xml");
		int alignments = landInfraImporter.getAlignmentModel()->getAlignmentCount();		
	}
#endif

#ifdef __EXPORT
	TEST(LandInfra, Export)
	{
		buw::ImportLandXml landXMLImporter("../../../../../../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		buw::ExportLandInfra(landXMLImporter.getAlignmentModel(), landXMLImporter.getDigitalElevationModel(), "export_landinfra_test.xml");
	}
#endif
}