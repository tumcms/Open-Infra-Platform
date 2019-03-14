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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h

#include "OpenInfraPlatform/EarlyBinding/namespace.h"

#include "EXPRESSEntity.h"
#include "EXPRESSModel.h"

#include <memory>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T> class EXPRESSReference : public std::weak_ptr<T> {
	//static_assert(std::is_base_of<EXPRESSEntity, T>::value, "EXPRESSReference can only be specialized with class derived from EXPRESSEntity");
	using base = std::weak_ptr<T>;
public:
	typedef base UnderlyingType;

	EXPRESSReference() = default;
	EXPRESSReference(const EXPRESSReference& other) = default;
	~EXPRESSReference() { 
		this->base::reset();
		this->model.reset();
	}

	using base::base;
	using base::operator=;

	const std::string getStepParameter() const {
		return this->base::lock()->getStepParameter();
	}

	T* operator->() { return this->base::lock().operator->(); }
	const T* const operator->() const { return this->base::lock().operator->(); }

	static EXPRESSReference<T> readStepData(const std::string arg, const std::shared_ptr<EXPRESSModel>& model) {
		size_t refId = std::stoull(arg);
		EXPRESSReference<T> reference = std::dynamic_pointer_cast<T>(model->entities[refId]);
		reference.refId = refId;
		reference.model = model;
		return reference;
	}

	const std::string classname() const {
		return this->base::lock()->classname();
	}

	friend void swap(EXPRESSReference& first, EXPRESSReference& second)
	{		
		std::swap(first, second);
	}

private:
	size_t refId;
	std::weak_ptr<EXPRESSModel> model;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

template<typename T> using EXPRESSReference = OpenInfraPlatform::EarlyBinding::EXPRESSReference<T>;
#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h
