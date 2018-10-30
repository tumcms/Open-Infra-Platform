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
#include "boost/variant.hpp"
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using std::string;
using std::array;
using boost::variant;
using namespace std;

class IfcLabel {};
class IfcText {};
class IfcAppliedValueSelect {};
class IfcMEasureWithUnit {};
class IfcDate {};

struct IfcAppliedValue_Common {
	std::string supername;
	int size;
	double another_common_type;

	//Common member methods
	void process() {}
	void unified_space_func() {};

};

namespace IFC1 {
	struct IfcAppliedValue {
		IfcLabel Name;
		IfcText description;
		IfcAppliedValueSelect AppliedValue;
		IfcDate ApplicableDate;
	};
};

namespace IFC2 {
	struct IfcAppliedValue {
		float b;
		string c;
		vector<int> k;
	};
};

namespace IFC3 {
	struct IfcAppliedValue {
		char a;
		double c;
	};
};


enum IFC_1 {
	IF_1 = 0
};

enum IFC_2 {
	IF_2 = 1

};

enum IFC_3 {
	IF_3 = 2
};

struct IfcAppliedValue : public IfcAppliedValue_Common {
	//This setup is crucial for proper initialization.
	//Otherwise test case gives error
	IfcAppliedValue()
	{
		dict[0] = IFC1::IfcAppliedValue();
		dict[1] = IFC2::IfcAppliedValue();
		dict[2] = IFC3::IfcAppliedValue();
	}

	IfcAppliedValue(IFC1::IfcAppliedValue &other)
	{
		dict[0] = other;
	}

	IFC1::IfcAppliedValue & operator[] (const IFC_1 & key)
	{
		return boost::get<IFC1::IfcAppliedValue>(dict[key]);
	}

	IFC2::IfcAppliedValue & operator[] (const IFC_2 & key)
	{
		return boost::get<IFC2::IfcAppliedValue>(dict[key]);
	}

	IFC3::IfcAppliedValue & operator[] (const IFC_3 & key)
	{
		return boost::get<IFC3::IfcAppliedValue>(dict[key]);
	}

	const IFC1::IfcAppliedValue & operator [] (IFC_1 & key) const
	{
		return boost::get< IFC1::IfcAppliedValue >(dict[key]);
	}

	const IFC2::IfcAppliedValue & operator[] (const IFC_2 & key) const
	{
		return boost::get<IFC2::IfcAppliedValue>(dict[key]);
	}

	const IFC3::IfcAppliedValue & operator[] (const IFC_3 & key) const
	{
		return boost::get<IFC3::IfcAppliedValue>(dict[key]);
	}


private:
	constexpr static int SIZE = 3;
	std::array <boost::variant<IFC1::IfcAppliedValue, IFC2::IfcAppliedValue, IFC3::IfcAppliedValue>, SIZE> dict;

};

void test(IfcAppliedValue obj)
{
	// Unified Interface Calls
	// Everything that is shared among all specs can be gathered under the common struct.
	obj.size;
	obj.supername;
	obj.process();
	obj.unified_space_func();

	// Schema specific calls
	obj[IF_1].AppliedValue;
	obj[IF_1].Name;

	obj[IF_2].c = "Hello World!";
	obj[IF_2].b = 0.1231;
	obj[IF_2].k = vector<int>(10);

	obj[IF_3].c = 123231.2342421;
	obj[IF_3].a = 'c';

	boost::variant<int, string> trial_1;
	boost::variant<int, string> trial_2;
	trial_1 = 3;
	trial_2 = "Hello World!";

	// Gives a compiler error, boost::get<>(trial_1) is necessary.
	// That means schema specific info
	// Thus unified interface not possible via boost::variant<>()
	//int numm = trial_1
	int numm = boost::get<int>(trial_1); // Okay
										 //Error in the below line
										 // string title = trial_2;
	string title = boost::get<string>(trial_2); // Okay
}

void test2(const IfcAppliedValue & obj)
{
	// Unified interface
	cout << obj.size << endl;
	cout << obj.another_common_type << endl;
	cout << obj.supername << endl;

	//IFC specific access.
	cout << obj[IF_2].c << endl;
	cout << obj[IF_2].b << endl;
	cout << obj[IF_2].k[0] << endl;
	cout << obj[IF_3].a << endl;
}

namespace {
	TEST(SkeletonPrototypeTest, Test)
	{
		IFC1::IfcAppliedValue obj;
		IfcAppliedValue other = IfcAppliedValue(obj);
		other.size = 5;
		other[IF_2].b = 1.2f;
	}
}