/*
    Copyright (c) 2018 Technical University of Munich
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
#include <BlueFramework/Engine/ResourceManagment/download.h>
#include <reader/IFC2X3Reader.h>

namespace {
	TEST(Import, IFC2X3) {
		buw::loadWebResources("Data/resources.xml");

		auto filename = "Data/20190228201620_Svaleveien_8_Hus_A.ifc";
		auto expressModel = OpenInfraPlatform::IFC2X3::IFC2X3Reader::FromFile(filename);
	}
}
	