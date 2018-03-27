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

#include "buw.OIPInfrastructure.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

#include <QtXml>

#include <type_traits>
#include <tuple>
#include <algorithm>

class A {
public:
	A() = default;
	virtual const std::string classname() const { return "A"; }
};

class B : public A {
public:
	B() = default;
	virtual const std::string classname() const { return "B"; }
private:
	double b_;
};

class C : public A {
public:
	C() = default;
	virtual const std::string classname() const { return "B"; }
};

template<template<typename...> class TT, typename T>
struct is_instantiation_of : std::false_type {};

template<template<typename...> class TT, typename... Ts>
struct is_instantiation_of<TT, TT<Ts...>> : std::true_type {};

using namespace std;

namespace
{
	TEST(IfcOWL, Playground)
	{

		std::shared_ptr<A> a0 = std::shared_ptr<A>(new B());
		std::shared_ptr<A> a1 = std::shared_ptr<A>(new C());

		std::vector<std::shared_ptr<A>> vector = { a0, a1 };
		for(auto it: vector) {
			if(it->classname() == "B") {
				auto b = std::dynamic_pointer_cast<B>(it);
				std::cout << "This is being compiled (0)" << std::endl;
			}

			if(std::is_same<std::shared_ptr<B>, decltype(it)>::value) {
				auto b = std::dynamic_pointer_cast<B>(it);
				//static_assert(std::is_same<std::shared_ptr<B>, decltype(it)>::value, "This is being compiled (1).");
			}
		}
		//buw::ImportLandXml landXMLImporter("../../../../../../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		//buw::ImportLandXml landXMLImporter("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		//buw::ExportIfcOWL4x1(landXMLImporter.getAlignmentModel(), landXMLImporter.getDigitalElevationModel(), "export_ifcowl_test.ttl");
	}

	TEST(IfcOWL, Export)
	{	
		
		buw::ImportLandXml landXMLImporter("../../../../../../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		//buw::ImportLandXml landXMLImporter("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		buw::ExportIfcOWL4x1(landXMLImporter.getAlignmentModel(), landXMLImporter.getDigitalElevationModel(), "export_ifcowl_test.ttl");
	}
}