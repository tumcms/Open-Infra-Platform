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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h

#include "OpenInfraPlatform/EarlyBinding/namespace.h"

#include "EXPRESSModel.h"

#include <utility>
#include <iostream>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T> class EXPRESSOptional : public boost::optional<T> {
	using base = boost::optional<T>;
	typedef typename T::UnderlyingType ForwardType;
public:
	// Constructors

	EXPRESSOptional() = default;
	EXPRESSOptional(const EXPRESSOptional &other) = default;
	//EXPRESSOptional(const T& obj) : boost::optional<T>(obj) { };
	using base::base;
	//using base::operator=;
	//template <typename V> explicit EXPRESSOptional(const V obj) : boost::optional<T>() { this->emplace(obj); }

	virtual ~EXPRESSOptional() { }

	// Assignment Operators

	// = default
	EXPRESSOptional& operator= (const ForwardType& other) { this->base::emplace(other); return *this; }

	EXPRESSOptional& operator= (const EXPRESSOptional& other) { base::operator=(other.get_value_or(T())); return *this; };

	// boost::optional<T>::operator=

	//EXPRESSOptional& operator=(const  boost::optional<T>& other) { boost::optional<T>::operator=(other); return *this; };

	//  boost::optional<T>::operator=(other)
		
	//EXPRESSOptional& operator=(const T other) { boost::optional<T>::operator=(other); return *this; };

	EXPRESSOptional& operator=(const T& other) { boost::optional<T>::operator=(other); return *this; };

	//EXPRESSOptional& operator=(const T& other) { is_initialized() ? this->emplace(other) : *this = EXPRESSOptional(other); return *this; };

	//using boost::optional<T>::operator=;

	//template <typename V> EXPRESSOptional& operator=(const V& other) { this->emplace(other); return *this; }

	// Cast Operators

	//template <typename V> operator V&() & { return (V&) this->get(); }

	operator ForwardType &() { return this->base::get().operator ForwardType&(); }
	operator const ForwardType () const { return this->base::get().operator const ForwardType(); }
	
	//operator typename T::UnderlyingType &() { return (typename T::UnderlyingType&) this->base::get_value_or(T()); }

	operator T&() & { return this->get(); }
	operator const T() const { return this->get(); }

	auto operator->() -> decltype(this->get().T::operator->()) { return this->is_initialized() ? this->get().T::operator->() : nullptr; }

	
	// Functions

	const std::string getStepParameter() const {
		if (this->is_initialized()) {
			return this->get().getStepParameter();
		}
		else {
			return "$";
		}
	}

	static EXPRESSOptional readStepData(const std::string& value, const std::shared_ptr<EXPRESSModel>& model) {
		EXPRESSOptional opt;
		T val;
		if (value != "$") {
			val = T::readStepData(value, model);
			opt = val;
		}
		return opt;
	}

	friend void swap(EXPRESSOptional& first, EXPRESSOptional& second)
	{
		using boost::swap;
		first.base::swap(second);
	}

	typedef T type;
};

template <typename T> const bool operator==(const EXPRESSOptional<T>& lhs, const EXPRESSOptional<T>& rhs) { return !lhs || !rhs ? false : (T)lhs == (T)rhs; }
template <typename T> const bool operator==(const EXPRESSOptional<T>& lhs, const T& rhs) { return !lhs ? false : (T)lhs == (T)rhs; }
template <typename T> const bool operator==(const T& lhs, const EXPRESSOptional<T>& rhs) { return !rhs ? false : lhs == (T)rhs; }
template <typename T, typename V> const bool operator==(const EXPRESSOptional<T>& lhs, const V& rhs) { return !lhs ? false : (T)lhs == rhs; }

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

template <typename T> using Optional = OpenInfraPlatform::EarlyBinding::EXPRESSOptional<T>;

template <typename T> class Optional2 : public T {
public:
	Optional2() = default;
	Optional2(const Optional2 &obj) = default;
	Optional2(const T& obj) : T(obj) { valid_ = true; }

	Optional2& operator=(const Optional2& rhs) = default;
	Optional2& operator=(const T& rhs) { this->T::operator=(rhs); valid_ = true; return *this; }

private:
	bool valid_ = false;
};

#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSOptional_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_h
