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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSAttribute_eb5c701d_2fe1_4b79_8d0b_d1767b93fe17_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSAttribute_eb5c701d_2fe1_4b79_8d0b_d1767b93fe17_h

#include "../EarlyBinding/src/namespace.h"

#include "OpenInfraPlatform/EarlyBinding/EXPRESS/EXPRESSOptional.h"
#include "OpenInfraPlatform/EarlyBinding/EXPRESS/EXPRESSType.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T> class EXPRESSAttribute {
public:
	EXPRESSAttribute() = default;

	EXPRESSAttribute& operator=(const EXPRESSAttribute& other) = default;
	EXPRESSAttribute& operator=(const T& other) { attr = other; return *this; }

	operator T&() { return std::ref(attr); }
	template <typename V> operator V&() { return (V&)attr; }

	T* operator->() { return &attr; }

	bool operator==(const T& other) { return attr == other; }

	bool is_initialized() const { return true; }
	std::string getStepParameter() { return attr.getStepParameter(); }
private:
	T attr;
};

template <typename T> class EXPRESSAttribute<EXPRESSOptional<T>> {
public:
	EXPRESSAttribute() = default;

	EXPRESSAttribute& operator=(const EXPRESSAttribute& other) = default;
	EXPRESSAttribute& operator=(const EXPRESSOptional<T>& other) { attr = other.get(); return *this; }
	EXPRESSAttribute& operator=(const T& other) { attr = other; return *this; }
	template <typename V> EXPRESSAttribute& operator=(const V& other) { attr.emplace(other); return *this; }


	operator T&() { return attr.get(); }
	template <typename V> operator V&() { return (V&) attr.get(); }

	T* operator->() { return attr.get_ptr(); }

	bool operator==(const T& other) { return attr == other; }

	bool is_initialized() const { return attr.is_initialized(); }
	std::string getStepParameter() { return attr.is_initialized() ? attr.getStepParameter() : "$"; }

private:
	EXPRESSOptional<T> attr;
};

template <typename T> class EXPRESSAttribute<ValueType<T>> {
public:
	EXPRESSAttribute() = default;

	EXPRESSAttribute& operator=(const EXPRESSAttribute& other) = default;
	EXPRESSAttribute& operator=(const ValueType<T>& other) { attr = other.get(); return *this; }
	EXPRESSAttribute& operator=(const T& other) { attr = other; return *this; }

	operator T&() { return attr; }
	template <typename V> operator V&() { return (V&)attr; }

	T* operator->() { return &((T&)attr); }

	bool operator==(const T& other) { return attr == other; }
	template<typename V> bool operator==(const V& other) { return attr == other; }

	bool is_initialized() const { return true; }
	std::string getStepParameter() { return attr.getStepParameter(); }

private:
	ValueType<T> attr;
};


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END
#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSAttribute_eb5c701d_2fe1_4b79_8d0b_d1767b93fe17_h
