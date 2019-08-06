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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h

#include "OpenInfraPlatform/EarlyBinding/namespace.h"

#include "EXPRESSType.h"
#include "EXPRESSModel.h"

#include <string>
#include <algorithm>
#include <utility>

#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <array>

#include <initializer_list>
#include <type_traits>


#include <boost/preprocessor.hpp>


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN


template <typename ValueType, size_t MinCardinality, size_t MaxCardinality> class EXPRESSContainer : public std::vector<ValueType> {
	using base = std::vector<ValueType>;
public:
	typedef base UnderlyingType;

	using base::base;
	using base::operator=;

	EXPRESSContainer* operator->() { return this; }
	const EXPRESSContainer* const operator->() const { return this; }

	//virtual const std::string getStepParameter() const;
	virtual const std::string getStepParameter() const {
		std::vector<std::string> params;
		if (!(this->base::empty())) {
			std::for_each(this->base::begin(), this->base::end(), [&params](const ValueType& elem) {
				params.push_back(elem.getStepParameter());
				params.push_back(",");
			});
			params.pop_back();
		}
		std::string result = "(";
		if (!params.empty()) {
			std::for_each(params.begin(), params.end(), [&result](std::string elem) {
				result += elem;
			});
		}
		result.append(")");
		return result;
	}

	//static std::vector<ValueType> readStepData(const std::string& value, const std::shared_ptr<EXPRESSModel>& model);
	static std::vector<ValueType> readStepData(const std::string& value, const std::shared_ptr<EXPRESSModel>& model) {
		// Remove the parentheses
		auto paramvalue = value.substr(1, value.size() - 2);
	
		std::vector<ValueType> result;
	
		while (!paramvalue.empty()) {
			auto end = paramvalue.size() - 1;
			auto pos = paramvalue.find_first_of(',');
			if (pos < end) {
				ValueType type;
				type = ValueType::readStepData(paramvalue.substr(0, pos), model);
				result.push_back(type);
				paramvalue.erase(0, pos + 1);
			}
			else {
				ValueType type;
				type = ValueType::readStepData(paramvalue.substr(0, pos), model);
				result.push_back(type);
				paramvalue.clear();
				break;
			}
		}
	
		return result;
	}

	friend void swap(EXPRESSContainer& first, EXPRESSContainer& second)
	{		
		first.base::swap(second);
	}
};

template <size_t MinCardinality, size_t MaxCardinality, typename T> using LIST = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using SET = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using BAG = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using ARRAY = EXPRESSContainer<T, MinCardinality, MaxCardinality>;

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END



#define DEFINE_CONTAINERTYPE(name, containertype, min, max, valuetype)\
	class name : public EarlyBinding::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>, public EarlyBinding::EXPRESSType {\
	using base = EarlyBinding::EXPRESSContainer<containertype<valuetype>,valuetype,min,max>;\
	public:\
		typedef name type;\
		using base::base;\
		using base::operator=;\
		using base::operator containertype<valuetype>&;\
		name* operator->() { return this; }\
		const name* const operator->() const { return this; }\
		virtual name& operator=(const Optional<name> &other) { operator=(other.get_value_or(name())); return *this; };\
		virtual const std::string classname() const override { return #name; }\
		virtual const std::string getStepParameter() const override {return base::getStepParameter(); }\
	};


#define EXPAND(...) __VA_ARGS__

#define LISTTYPE std::vector
#define SETTYPE std::vector
#define BAGTYPE std::vector
#define ARRAYTYPE std::vector

#define LIST_MAXSIZE ULLONG_MAX
#define ARRAY_MAXSIZE ULLONG_MAX
#define SET_MAXSIZE ULLONG_MAX
#define BAG_MAXSIZE ULLONG_MAX


#endif // end define OpenInfraPlatform_ExpressBidning_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h
