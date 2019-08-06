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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <utility>
#include <iostream>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename T> class EXPRESSOptional : public boost::optional<T> {
public:
	// Constructors

	EXPRESSOptional() : boost::optional<T>() {};
	EXPRESSOptional(const T& obj) : boost::optional<T>(obj) { };

	// Assignment Operators

	using boost::optional<T>::operator=;
	T& operator=(const T& other) { boost::optional<T>::operator=(other); };
	EXPRESSOptional& operator= (const EXPRESSOptional& other) = default;

	// Cast Operators
	//using boost::optional<T>::operator T&;
	operator T&() { return this->get(); }

	// Functions

	std::string getStepParameter() {
		if (is_initialized()) {
			return this->get().getStepParameter();
		}
		else {
			return "$";
		}
	}
};

template <class T> class EXPRESSOptional2 : public T {
public:
	//template<typename ...Args> EXPRESSOptional2(Args... args) { data_.emplace(std::forward<Args>(args)...); };

	EXPRESSOptional2() :T() { data_ = *this; };

	EXPRESSOptional2(const EXPRESSOptional2& other) {
		*this = other;
		data_ = *this;
	};

	EXPRESSOptional2(EXPRESSOptional2&& other) {
		*this = other;
		data_ = *this;
	};

	EXPRESSOptional2(const T& other) {
		*this = other;
		data_ = *this;
	};

	EXPRESSOptional2(T&& other) {
		*this = other;
		data_ = *this;
	};

	using T::operator=;

private:
	//EXPRESSOptional2() = default;
	boost::optional<T> data_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h
