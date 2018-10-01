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

#include "types.hpp"
#include <string>

#include "gtest/gtest.h"


namespace {
	TEST(SkeletonPrototypeTest, Test)
	{
		EXPRESS::IFC4_Entities::IfcApplication x("safdsa", 'a', "");

		// This should not be allowed.
		IFC4_SKELETON::IfcApplication_Skelaton<EXPRESS::IFC4_Entities::IfcReal, IfcAbsorbedDoseMeasure, std::string> y(0.0, 1.2, "");

		// Using EXPRESS::IFC4_Entities::IfcReal::Value to acces the IfcApplication::ApplicationDeveloper should also not be possible.
		std::cout << x.return_data_member<EXPRESS::IFC4_Entities::IfcReal::Value>() << std::endl;
	}
}