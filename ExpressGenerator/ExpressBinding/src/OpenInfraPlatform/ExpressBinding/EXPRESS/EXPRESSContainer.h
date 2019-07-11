/*
    This file is part of Expresso, a simple early binding generator for EXPRESS.
	Copyright (c) 2016 Technical University of Munich
	Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include <string>
#include <algorithm>

#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <array>

#include <initializer_list>
#include <type_traits>

#include <QString>
#include <QStringList>

#include <boost/preprocessor.hpp>



#define FORWARD_FUNCTION_TO_MEMBER(r, member, function) template<typename... Args> decltype(auto) function(Args&&... args) { return member.function(std::forward<Args>(args)...); };



OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename ContainerType, typename ValueType, int MinCardinality, int MaxCardinality> class EXPRESSContainer : public ContainerType {
private:
	//template<bool...> struct check;
	//template<bool... b> struct check<false, b...> : std::false_type {};
	//template<bool... b> struct check<true, b...> : check<b...> {};
	//template<> struct check<> : std::true_type {};

public:
	//template<typename ...Args> EXPRESSContainer(Args&&... arguments) {
	//	static_assert(check<std::is_convertible<Args, ValueType>::value...>::value, "Wrong Type.");
	//	static_assert(sizeof...(Args) >= MinCardinality && sizeof...(Args) <= MaxCardinality, "Wrong Size.");
	//
	//
	//}	

	std::string getStepParameter() {
		QStringList params;
		std::for_each(begin(), end(), [&params](ValueType elem) {
			params.append(QString(elem.getStepParameter().data()));
		});
		return "(" + params.join(',').toStdString() + ")";
	}
};

template <typename ContainerType, typename ValueType, int MinCardinality, int MaxCardinality> class EXPRESSContainer2 {
public:
	EXPRESSContainer2() = default;
	EXPRESSContainer2(const ContainerType &other) : data(other) {};
	EXPRESSContainer2(const std::initializer_list<ValueType> &other) : data(other) {};

	//Forward STL container functions to data member.
	#define STL_CONTAINER_FUNCTIONS (push_back,(pop_back,(front,(back,(begin,(end,(insert,BOOST_PP_NIL)))))))
	BOOST_PP_LIST_FOR_EACH(FORWARD_FUNCTION_TO_MEMBER, data, STL_CONTAINER_FUNCTIONS)
	#undef STL_CONTAINER_FUNCTIONS


	std::string getStepParameter() {
		QStringList params;
		std::for_each(data.begin(), data.end(), [&params](auto elem) {
			params.append(QString(elem.getStepParameter().data()));
		});
		return "(" + params.join(',').toStdString() + ")";
	}

	EXPRESSContainer2& operator=(const EXPRESSContainer2& other) = default;

private:
	ContainerType data = ContainerType();
};



//template <int MinCardinality, int MaxCardinality, typename T> using LIST = EXPRESSContainer<std::vector<T>, T, MinCardinality, MaxCardinality>;
//template <int MinCardinality, int MaxCardinality, typename T> using SET = EXPRESSContainer<std::set<T>, T, MinCardinality, MaxCardinality>;
//template <int MinCardinality, int MaxCardinality, typename T> using BAG = EXPRESSContainer<std::unordered_set<T>, T, MinCardinality, MaxCardinality>;

template <int MinCardinality, int MaxCardinality, typename T> using LIST = EXPRESSContainer2<std::vector<T>, T, MinCardinality, MaxCardinality>;
template <int MinCardinality, int MaxCardinality, typename T> using SET = EXPRESSContainer2<std::set<T>, T, MinCardinality, MaxCardinality>;
template <int MinCardinality, int MaxCardinality, typename T> using BAG = EXPRESSContainer2<std::unordered_set<T>, T, MinCardinality, MaxCardinality>;

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBidning_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h
