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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSOptionalImpl_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_g
#define OpenInfraPlatform_EarlyBinding_EXPRESSOptionalImpl_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_g

#include "EXPRESSOptional.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T> EXPRESSOptional<T>& EXPRESSOptional<T>::operator= (ForwardType other) {
	boost::optional<T>::operator=(other);
	return *this;
}

template <typename T> EXPRESSOptional<T>& EXPRESSOptional<T>::operator=(const T& other) { boost::optional<T>::operator=(other); return *this; };

template <typename T> const std::string EXPRESSOptional<T>::classname() const {
	if (this->is_initialized()) {
		return this->get().classname();
	}
	else {
		return "uninitialized";
	}
}


template <typename T> const std::string EXPRESSOptional<T>::getStepParameter() const {
	if (this->is_initialized()) {
		return this->get().getStepParameter();
	}
	else {
		return "$";
	}
}

template <typename T> EXPRESSOptional<T> EXPRESSOptional<T>::readStepData(const std::string& value, const std::shared_ptr<EXPRESSModel>& model) {
	EXPRESSOptional opt;
	T val;
	if (value != "$") {
		val = T::readStepData(value, model);
		opt = val;
	}
	return opt;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSOptionalImpl_76c70f6e_bab2_48da_b2bc_9434b6adf3dc_g
