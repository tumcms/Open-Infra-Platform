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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <string>
#include <utility>
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename T> class EXPRESSType {
	static_assert(std::is_integral<T>::value || std::is_same<T, std::string>::value || std::is_floating_point<T>::value, "EXPRESSType is undefined for template parameter type.");

public:
	EXPRESSType() = default;
	EXPRESSType(const EXPRESSType& other) : m_value(other.m_value) {};
	EXPRESSType(const T& value) : m_value(value) {};

	std::string getStepParameter() const {		
		return std::to_string(m_value);
	}

	EXPRESSType& operator=(const EXPRESSType& other) = default;
	EXPRESSType& operator=(const T& other) { m_value = other; return *this; }

	operator T&() { return std::ref(m_value); }

	bool operator==(const EXPRESSType& other) { return m_value == other.m_value; }
	bool operator==(const T& other) { return m_value == other; }	

	friend std::ostream& operator<<(std::ostream &out, const EXPRESSType& obj) { out << obj.m_value; return out; }
	friend std::istream& operator>>(std::istream &in, EXPRESSType& obj) { in >> obj.m_value; return in; }
	
private:
	T m_value;
};

template <typename T> bool operator==(const EXPRESSType<T>& lhs, const EXPRESSType<T>& rhs) { return ((T&)lhs) == ((T&)rhs); };
template <typename T> bool operator==(const EXPRESSType<T>& lhs, const T& rhs) { return ((T&)lhs) == rhs; };
template <typename T> bool operator==(const T& lhs, const EXPRESSType<T>& rhs) { return lhs == ((T&)rhs); };


std::string EXPRESSType<std::string>::getStepParameter() const {
	return EXPRESSType<std::string>::m_value;
};



using REAL = EXPRESSType<double>;
using INTEGER = EXPRESSType<int>;
using STRING = EXPRESSType<std::string>;
using BOOLEAN = EXPRESSType<bool>;


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSType_102447dd_302a_4c8f_bf0d_7515bbdcfc1c_h
