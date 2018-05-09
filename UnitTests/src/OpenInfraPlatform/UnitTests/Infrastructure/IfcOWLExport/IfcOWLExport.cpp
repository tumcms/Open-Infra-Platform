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
#include <QString>

#include <type_traits>
#include <typeinfo>
//#include <typeindex>
#include <tuple>
#include <algorithm>
#include <visit_struct/visit_struct.hpp>

#include <boost/any.hpp>
#include <boost/type_index.hpp>

//#include "C:\Users\ga38fih\Downloads\Boost.DynamicAny-master\include\boost\dynamic_any.hpp"

#include <boost/preprocessor/comparison/equal.hpp>

class A {
public:
	A() = default;
	virtual const std::string classname() const { return "A"; }
	std::shared_ptr<int> a_;
};

VISITABLE_STRUCT(A, a_);


class C : public A {
public:
	C() = default;
	virtual const std::string classname() const override { return "B"; }
};

class B : public A {
public:
	B() :A() { numbers_ = std::vector<std::shared_ptr<C>>(0); }
	virtual const std::string classname() const override { return "B"; }
	double b_;
	std::vector<std::shared_ptr<C>> numbers_;
	std::shared_ptr<C> ptr_;
	C n_;

	operator C() { return C(); }
};

VISITABLE_STRUCT(B, a_, b_, numbers_, ptr_, n_);

class D : public A {
public:
	D() = default;
	D(B b) {}
	virtual const std::string classname() const override { return "D"; }

	B operator=(B other) { return B(); }
};


template<template<typename...> class TT, typename T>
struct is_instantiation_of : std::false_type {};

template<template<typename...> class TT, typename... Ts>
struct is_instantiation_of<TT, TT<Ts...>> : std::true_type {};


struct func {
public:
	template < class T,
		class = typename std::enable_if<is_instantiation_of<std::shared_ptr, T>::value>::type>
	void operator()(const char* name, T value) {
		std::cout << "Found double!" << std::endl;
	}
};

struct DerivedIfcEntityParser {
	template <typename T>
	void operator()(const char* name, std::shared_ptr<T> a_ptr)
	{
		std::cout << "Found pointer!" << std::endl;

	}

	template <typename T>
	void operator()(const char* name, std::vector<T> a_ptr)
	{
		std::cout << "Found vector!" << std::endl;
	}

	template <typename T>
	void operator()(const char* name, T t)
	{
		std::cout << "Found T!" << std::endl;
	}
};


//#define TYPE_2 decltype(B())
//#define TYPE_1 decltype(A())
//
//#include <boost/preprocessor/iteration/local.hpp>
//
//template <unsigned N> struct unrolled_dynamic_visitor {
//	template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F const& f)
//	{
//	}
//};
//
//#define GET_IFC_ENTITY_TYPE(N) TYPE_##N
//
//#define CREATE_SPECIALIZATION(n)\
//	template <> struct unrolled_dynamic_visitor<n> {\
//		template <typename F, typename P> static void castAndCall(std::shared_ptr<P> ptr, F const& f)\
//		{\
//			if(typeid(GET_IFC_ENTITY_TYPE(n)) == typeid(*(ptr.get()))) {\
//				GET_IFC_ENTITY_TYPE(n) entity = *(std::dynamic_pointer_cast<GET_IFC_ENTITY_TYPE(n)>(ptr)); \
//				f(entity); \
//			}\
//			else {\
//				unrolled_dynamic_visitor<n - 1>::castAndCall(ptr,f);\
//			}\
//		}\
//	};\
//
//
//#define BOOST_PP_LOCAL_MACRO(n)   CREATE_SPECIALIZATION(n)
//#define BOOST_PP_LOCAL_LIMITS (1, 2)
//#include BOOST_PP_LOCAL_ITERATE()

using namespace std;



namespace
{
	/*
	TEST(Preprocessor, Constructor)
	{
		//std::shared_ptr<A> b = std::shared_ptr<A>(new B());
		//
		//auto myGenericLambda = [](auto elem) {
		//	visit_struct::for_each(elem, DerivedIfcEntityParser {});
		//};
		//
		//std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> entity = std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(new OpenInfraPlatform::IfcAlignment1x1::IfcPerson());
		//unrolled_dynamic_visitor<2>::castAndCall(b, myGenericLambda);
		//std::shared_ptr<A> a_ptr = std::shared_ptr<A>(&CREATE(0));
		//const std::type_info& t = (typeid(A));

		
	}
	*/
	/*
	TEST(Deprecated, boost_dynamic_any)
	{
		std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> entity_ptr;
		std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcPerson> person_ptr = std::make_shared<OpenInfraPlatform::IfcAlignment1x1::IfcPerson>();
		
		OpenInfraPlatform::IfcAlignment1x1::IfcPerson person = *person_ptr;
		boost::dynamic_any person_any = boost::dynamic_any(person_ptr);


		//Try to figure out how to cast pointers

		std::shared_ptr<B> b_ptr = std::make_shared<B>();
		B b = *b_ptr;
		boost::dynamic_any b_ptr_any = b_ptr;
		boost::dynamic_any b_any = boost::dynamic_any(b);

		A a = boost::dynamic_any_cast<A>(b_any);
		
		std::shared_ptr<A> a_ptr = std::static_pointer_cast<B>(b_ptr);


		//fails
		//std::common_type<std::shared_ptr<boost::dynamic_any>, std::shared_ptr<C>, std::shared_ptr<B>>::type parent;

		//fails
		//std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> entity = boost::dynamic_any_cast<std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>(person_any);
	}

	TEST(Deprecated, Playground)
	{

		std::shared_ptr<A> a0 = std::shared_ptr<A>(new B());
		std::shared_ptr<A> a1 = std::shared_ptr<A>(new B());

		std::vector<std::shared_ptr<A>> vector = { a0, a1 };
		for(auto it: vector) {
			if(it->classname() == "B") {
				auto b = std::dynamic_pointer_cast<B>(it);
				//std::cout << "This is being compiled (0)" << std::endl;								

				visit_struct::for_each(*b,
					[](const char* name, auto value_auto) {

					boost::dynamic_any value = value_auto;

					void* test = &value_auto;

					decltype(value_auto) reconstructed = boost::dynamic_any_cast<decltype(value_auto)>(value);

					if(std::string(value.type().name()) == std::string(typeid(double).name())) {
						double typed_val = boost::dynamic_any_cast<double>(value);
						std::cout << "value: " << typed_val << std::endl;
					}
					else if(QString(value.type().name()).startsWith("class std::vector<")) {
						std::vector<std::shared_ptr<C>> vec = boost::dynamic_any_cast<std::vector<std::shared_ptr<C>>>(value);

						std::cout << "length: " << vec.size() << std::endl;
					}
					else if(QString(value.type().name()).startsWith("class std::shared_ptr<")) {

					}
					else if(QString(value.type().name()).startsWith("class C")) {
						A c = boost::dynamic_any_cast<A>(value);
						std::cout << c.classname() << std::endl;
					}

				});
			}

			if(std::is_same<std::shared_ptr<B>, decltype(it)>::value) {
				auto b = std::dynamic_pointer_cast<B>(it);
				//static_assert(std::is_same<std::shared_ptr<B>, decltype(it)>::value, "This is being compiled (1).");
			}
		}

		visit_struct::for_each(B(), DerivedIfcEntityParser {});

	}*/

	TEST(IfcOWL, Export)
	{	
		
		buw::ImportLandXml landXMLImporter("../../../../../../testdata/LandXML/Mainbruecke_Klingenberg.xml");
		//buw::ImportLandXml landXMLImporter("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		buw::ExportIfcAlignment1x1(buw::ifcAlignmentExportDescription(), landXMLImporter.getAlignmentModel(), landXMLImporter.getDigitalElevationModel(), "export_ifcowl_test.ifc");
		buw::ExportIfcOWL4x1(landXMLImporter.getAlignmentModel(), landXMLImporter.getDigitalElevationModel(), "export_ifcowl_test.ttl");
	}
}