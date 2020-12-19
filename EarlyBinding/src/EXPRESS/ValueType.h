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
#ifndef OpenInfraPlatform_EarlyBinding_ValueType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h
#define OpenInfraPlatform_EarlyBinding_ValueType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h

#include "EXPRESSOptional.h"
#include "EXPRESSContainer.h"
#include "EXPRESSType.h"

#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>


//#include <boost/preprocessor.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/algorithm/string.hpp>    

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T>
class
ValueType : public EXPRESSType 
{
//	static_assert(std::is_same<T,boost::logic::tribool>::value || std::is_integral<T>::value || std::is_same<T, std::string>::value || std::is_floating_point<T>::value || std::is_enum<T>::value, "EXPRESSType is undefined for template parameter type.");

public:
	typedef T UnderlyingType;
	typedef T element_type;

	ValueType() = default;
	ValueType(const ValueType& other) : m_value(other.m_value) {}
	ValueType(const T& value) : m_value(value) {}

	virtual ~ValueType() { }

	virtual const std::string getStepParameter() const override { return "unknown"; }

	static T readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>& model = nullptr) {
		if (value == "*") {
			//TODO : Implement behaviour
			return T();
		}
		else {
			return T::readStepData(value, model);
		}
	};

	virtual const std::string classname() const override { return typeid(T).name(); }

	virtual ValueType& operator=(const T& other) { m_value = other; return *this; }
	virtual ValueType& operator=(const ValueType& other) { m_value = other.m_value; return *this; }
	//virtual ValueType& operator=(const Optional<ValueType>& optional) { m_value = optional.get_value_or(T()); return *this; }
	
	virtual operator T&() { return std::ref(m_value); }
	virtual operator const T() const { return m_value; }

	virtual ValueType* operator->() { return this; }
	virtual const ValueType* const operator->() const { return this; }

protected:
	T m_value;

public:

	friend void swap(ValueType& first, ValueType& second)
	{
		using std::swap;
		swap(first.m_value, second.m_value);
	}
};

template <typename T> 
const bool operator==(const ValueType<T>& lhs, const ValueType<T>& rhs) 
{ return (T)lhs == (T)rhs; }

template <typename T>
const bool operator==(const ValueType<T>& lhs, const T rhs) 
{ return (T)lhs == (T)rhs; }

template <typename T>
const bool operator==(const T lhs, const ValueType<T>& rhs) 
{ return lhs == (T)rhs; }

template <typename T, typename V>
const bool operator==(const ValueType<T>& lhs, const V rhs) 
{ return(T)lhs == rhs; }


template <>
OIP_EARLYBINDING_API_EXPRESS
const std::string ValueType<double>::getStepParameter() const { return std::to_string(ValueType<double>::m_value); }

template <>
OIP_EARLYBINDING_API_EXPRESS
const std::string ValueType<int>::getStepParameter() const { return std::to_string(ValueType<int>::m_value); }

template <>
OIP_EARLYBINDING_API_EXPRESS
const std::string ValueType<bool>::getStepParameter() const { return std::to_string(ValueType<bool>::m_value); }

template <>
OIP_EARLYBINDING_API_EXPRESS
const std::string ValueType<std::string>::getStepParameter() const { return "'" + ValueType<std::string>::m_value + "'"; }

template <>
OIP_EARLYBINDING_API_EXPRESS
const std::string ValueType<boost::logic::tribool>::getStepParameter() const {
	switch (ValueType<boost::logic::tribool>::m_value.value) {
	case boost::logic::tribool::true_value: return "TRUE";
	case boost::logic::tribool::false_value: return "FALSE";
	case boost::logic::tribool::indeterminate_value: return "UNKNOWN";
	}
	return "ERROR";
}

template <>
OIP_EARLYBINDING_API_EXPRESS
double ValueType<double>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return 0.0;
	}
	else {
		return (stod(value));
	}
}

template <>
OIP_EARLYBINDING_API_EXPRESS
int ValueType<int>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return 0;
	}
	else {
		return (stoi(value));
	}
}

template <>
OIP_EARLYBINDING_API_EXPRESS
bool ValueType<bool>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return false;
	}
	else {
		std::string lower = boost::algorithm::to_lower_copy(value);
		return (lower == "true" || lower == ".t.");
	}
}

template <>
OIP_EARLYBINDING_API_EXPRESS
std::string ValueType<std::string>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value.at(0) == '\'') {
		return value.substr(1, value.length() - 2);
	}
	else {
		return value;
	}
}

template <>
OIP_EARLYBINDING_API_EXPRESS
boost::logic::tribool ValueType<boost::logic::tribool>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	std::string lower = boost::algorithm::to_lower_copy(value);
	if (value == "*") {
		//TODO : Implement behaviour
		return boost::logic::tribool(boost::logic::indeterminate);
	}
	else {
		if (lower == "true" || lower == ".t.") {
			return boost::logic::tribool::true_value;
		}
		else if (lower == "false" || lower == ".f.") {
			return boost::logic::tribool::false_value;
		}
		else {
			return boost::logic::tribool(boost::logic::indeterminate);
		}
	}
}

using REAL = ValueType<double>;
using INTEGER = ValueType<int>;
using STRING = ValueType<std::string>;
using BOOLEAN = ValueType<bool>;
using LOGICAL = ValueType<boost::logic::tribool>;
using BINARY = ValueType<int>;
using NUMBER = ValueType<double>;

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(REAL);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(INTEGER);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(STRING);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(BOOLEAN);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(LOGICAL);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(BINARY);
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(NUMBER);

#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h
