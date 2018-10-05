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
#include <boost/variant.hpp>

#include "gtest/gtest.h"



namespace Ifc {
	struct IfcReal {
		virtual boost::variant<float, double> getValue() = 0;
		virtual int getVersion() = 0;
				
	};

	struct IfcPerson {
		virtual std::string getFirstName() = 0;
		virtual std::string getLastName() = 0;
	};
}

namespace Ifc4 {
	struct IfcReal : public Ifc::IfcReal {

		IfcReal() = default;
		double value = 0.0;
		virtual boost::variant<float, double> getValue() { return (value); }
		virtual int getVersion() { return 4; }
	};

	struct IfcPerson : public Ifc::IfcPerson {
		IfcPerson() = default;
		std::string firstName;

		virtual std::string getFirstName() { return firstName; }
		virtual std::string getLastName() { throw std::exception("Member not supported"); }
	};
}

namespace Ifc5 {
	struct IfcReal : public Ifc::IfcReal {
		IfcReal() = default;
		float value = 0.0f;
		virtual boost::variant<float, double> getValue() { return boost::variant<float, double>(value); }
		//auto getValue() -> decltype(value) { return (value); }
	};

	struct IfcPerson : public Ifc::IfcPerson {
		IfcPerson() = default;
		std::string firstName, lastName;

		virtual std::string getFirstName() { return firstName; }
		virtual std::string getLastName() {	return lastName; }
	};
}

namespace {
	TEST(SkeletonPrototypeTest, Test)
	{
		EXPRESS::IFC4_Entities::IfcApplication x("safdsa", 'a', "blub");

		// Using IFcReal as parameter causes error
		EXPRESS::IFC4_Entities::IfcReal v(0.0);
		//IFC4_SKELETON::IfcApplication_Skelaton<EXPRESS::IFC4_Entities::IfcReal, IfcAbsorbedDoseMeasure, std::string> y(v, 1.2, "blub");

		//IFC3_SKELETON::IfcReal_Skelaton<double>a(1.0);
		// This should not be allowed. Skeleton class shouldnt be accessible in the final application -> not possible?
		IFC4_SKELETON::IfcApplication_Skelaton<double, IfcAbsorbedDoseMeasure, std::string> z(1.0, 1.2, "blub");

		// Using EXPRESS::IFC4_Entities::IfcReal::Value to acces the IfcApplication::ApplicationDeveloper should also not be possible.
		std::cout << x.return_data_member<EXPRESS::IFC4_Entities::IfcReal::Value>() << std::endl;

		Ifc::IfcReal &abstr = Ifc4::IfcReal();
		boost::variant<float, double> val = abstr.getValue();
		std::cout << abstr.getValue().type().name() << std::endl;
	}
}