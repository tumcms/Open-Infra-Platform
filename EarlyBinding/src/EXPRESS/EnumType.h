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
#ifndef OpenInfraPlatform_EarlyBinding_EnumType_222b174c_10f8_447c_9363_6efd29177d6c_h
#define OpenInfraPlatform_EarlyBinding_EnumType_222b174c_10f8_447c_9363_6efd29177d6c_h

#include "../EarlyBinding/src/namespace.h"
#include "ValueType.h"
#include "EXPRESSModel.h"

//#include <boost/preprocessor.hpp>
#include <iostream>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <typename Enum, int Count> class EnumType : public ValueType<Enum> {
	using base = ValueType<Enum>;
public:
	typedef Enum ENUM;
	using base::base;
	using base::operator=;
	using base::operator->;
	
	//virtual ~EnumType() = 0;

	virtual const std::string getStepParameter() const override { return to_string(ValueType<Enum>::m_value); };

	static Enum readStepData(const std::string &arg, const std::shared_ptr<EXPRESSModel>& model = nullptr) {
		for (int i = 0; i < Count; i++) {
			Enum value = static_cast<Enum>(i);
			if (("." + arg + ".") == to_string(value)) {
				return value;
			}
		}
		return static_cast<Enum>(0);
	}

};

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

//#define DEFINE_ENUMTYPE(name, seq)\
//	ENUM_W_STR(name##Values, int, seq);\
//	class name : public OpenInfraPlatform::EarlyBinding::ValueType<name##Values> {\
//		using base = OpenInfraPlatform::EarlyBinding::ValueType<name##Values>;\
//		public:\
//			typedef name type;\
//			using base::base;\
//			using base::operator=;\
//			using base::operator->;\
//			virtual name& operator=(const Optional<name> &other) { this->m_value = other.get_value_or(name()); return *this; };\
//			virtual const std::string classname() const override { return #name; }\
//			const std::string name::getStepParameter() const { return "." + to_string(OpenInfraPlatform::EarlyBinding::ValueType<name##Values>::m_value) + "."; };\
//			static name##Values name::readStepData(const std::string &value) {\
//				auto from_string = [](const std::string &value)-> name##Values {\
//					BOOST_PP_SEQ_FOR_EACH(\
//						ENUMUTLS_FROM_STR_SWITCH_CASE,\
//						name##Values,\
//						seq)\
//					return name##Values::BOOST_PP_SEQ_HEAD(seq);\
//				};\
//		return from_string(value.substr(1, value.size() - 2));\
//		};\
//	};


#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSEnum_222b174c_10f8_447c_9363_6efd29177d6c_h
