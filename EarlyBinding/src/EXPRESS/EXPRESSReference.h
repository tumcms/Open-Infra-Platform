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

#include "../EarlyBinding/src/namespace.h"

//#include "EXPRESSEntity.h"
#include "EXPRESSObject.h"
#include "EXPRESSModel.h"

#include <memory>
#include <string>
#include <utility>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename T> class EXPRESSReference : public std::weak_ptr<T>, public EXPRESSObject {
	//static_assert(std::is_base_of<EXPRESSEntity, T>::value, "EXPRESSReference can only be specialized with class derived from EXPRESSEntity");
	using base = std::weak_ptr<T>;
public:
	typedef base UnderlyingType;

	EXPRESSReference() = default;

	EXPRESSReference(const EXPRESSReference& other)
        :
        base(other),
        refId{other.refId},
        model{other.model}
	{
	    
	}

	virtual ~EXPRESSReference() { 
		this->base::reset();
		this->model.reset();
	}

	using base::base;

	EXPRESSReference<T>& operator=(const EXPRESSReference<T>& other)
	{
		if (this == &other)
			return *this;

		refId = other.refId;
		model = other.model;

		if(this->base::expired() && !model.expired() && refId != 0 && model.lock()->entities.count(refId) > 0)
			this->base::operator=(std::dynamic_pointer_cast<T>(model.lock()->entities[refId]));
		
		return *this;
	}

	const std::shared_ptr<T> lock() const {
		return this->base::lock();
	}

	std::shared_ptr<T> lock() {
		if (!this->expired() && refId != 0) {
			return this->base::lock();
		}
		else if (this->base::expired() && !model.expired() && refId != 0 && model.lock()->entities.count(refId) > 0) {
			this->base::operator=(std::dynamic_pointer_cast<T>(model.lock()->entities[refId]));
			return this->base::lock();
		}
		else {
			return this->base::lock();
		}
	}

	const std::string getStepParameter() const override 
	{
		const std::shared_ptr<T> ptr = this->base::lock();
		return ptr.get()->getStepParameter();
		//return this->base::lock().get()->getStepParameter();
	}
	

	T* operator->() { return this->lock().operator->(); }
	const T* const operator->() const { return this->base::lock().operator->(); }

	operator const bool() const { 
		return this->base::lock().operator bool();
	}

	operator const bool() {
		return this->lock().operator bool();
	}

	static EXPRESSReference<T> readStepData(const std::string arg, const std::shared_ptr<EXPRESSModel>& model) 
	{
		if (arg == "*") {
			//TODO
			return EXPRESSReference<T>();
		}
		else {
			size_t refId = std::stoull(arg.substr(1, arg.size() - 1));
			return constructInstance(refId, model);
		}
	}

	static EXPRESSReference<T> constructInstance(const size_t refId, const std::shared_ptr<EXPRESSModel>& model)
	{
		EXPRESSReference<T> reference;
		if (model->entities.count(refId) > 0) {
			reference.base::operator=(std::dynamic_pointer_cast<T>(model->entities[refId]));
		}
		reference.refId = refId;
		reference.model = model;
		return reference;
	}

	const std::string classname() const override
	{
		const std::shared_ptr<T> ptr = this->base::lock();
		// Lock on this and return runtime classname or if empty construct T and return T.classname()
		if (ptr) {
			return ptr.get()->classname();
		}
		else {
			return "unknown";
		}
		//return this->base::lock().get()->classname();
	}
	

	friend void swap(EXPRESSReference& first, EXPRESSReference& second)
	{
		first.base::swap(second);
		std::swap(first.refId, second.refId);
		std::swap(first.model, second.model);
	}

	template <typename TTarget> EXPRESSReference<TTarget> as() {
		return EXPRESSReference<TTarget>(std::dynamic_pointer_cast<TTarget>(this->lock()));
	}

	template <typename TTarget> const EXPRESSReference<TTarget> as() const {
		return EXPRESSReference<TTarget>(std::dynamic_pointer_cast<TTarget>(this->lock()));
	}

	template <typename TTarget> bool isOfType() const {
		return std::dynamic_pointer_cast<TTarget>(this->lock()) != nullptr;
	}

    virtual const std::string getErrorLog() const override
	{
	    if(this->expired())
	        return "Reference with Id #" + std::to_string(this->refId) + " expired!";
	    else
	        return this->base::lock()->getErrorLog();
	}
	
private:
	size_t refId = 0;
	std::weak_ptr<EXPRESSModel> model;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

template<typename T> using EXPRESSReference = OpenInfraPlatform::EarlyBinding::EXPRESSReference<T>;
EMBED_INTO_OIP_NAMESPACE(EXPRESSReference);

#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h
