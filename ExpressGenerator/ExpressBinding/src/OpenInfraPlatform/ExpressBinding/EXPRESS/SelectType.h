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
#ifndef OpenInfraPlatform_ExpressBinding_SelectType_10255db4_8b09_413b_9c43_ea39f1d63ced_h
#define OpenInfraPlatform_ExpressBinding_SelectType_10255db4_8b09_413b_9c43_ea39f1d63ced_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include "EXPRESSType.h"
#include "EXPRESSModel.h"
//#include "EXPRESSEntity.h"

#include <type_traits>

#include <boost/variant.hpp>
#include <boost/preprocessor.hpp>

#include <tuple>
#include <utility>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

#define SELECT_CAST_REF_OPERATOR(r, data, i, elem)\
	operator elem&() { return boost::get<elem>(*this); };

#define SELECT_CAST_CONST_OPERATOR(r, data, i, elem)\
	operator const elem() const { return boost::get<elem>(*this); };

#define CASE(r, data, i, elem) case i: return (V&) boost::get<elem>(*this);

#define GET_STEP_PARAMETER(r,data,i,elem) case i: param.append(boost::get<elem>(*this)->classname()).append("(").append(boost::get<elem>(*this)->getStepParameter()).append(")"); break;

#define ASSIGNMENT_OPERATOR(r,data,i,elem) BOOST_PP_CAT(data,&) operator=(const BOOST_PP_CAT(elem,&) other) { this->base::operator=(other); return *this; };

#define READ_STEP_DATA(r,select,i,elem) if(name == BOOST_PP_STRINGIZE(BOOST_PP_REMOVE_PARENS(elem))) return select(elem::type::readStepData(value.substr( value.find_first_of('(') + 1,  value.find_first_of(')') )));

#define OPERATOR_BOOL(r,data,i,elem) const bool operator==(const BOOST_PP_CAT(BOOST_PP_REMOVE_PARENS(elem),&) other) const { return (boost::get<elem>(*this)) == other; };

#define DEFINE_SELECTTYPE(select, seq)\
	class select : public boost::make_recursive_variant<BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(seq))>::type, public OpenInfraPlatform::ExpressBinding::EXPRESSType {\
		using base = boost::make_recursive_variant<BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(seq))>::type;\
		public:\
		select() = default;\
		using base::base;\
		BOOST_PP_SEQ_FOR_EACH_I(\
			SELECT_CAST_REF_OPERATOR,\
			,\
			seq\
		)\
		BOOST_PP_SEQ_FOR_EACH_I(\
			SELECT_CAST_CONST_OPERATOR,\
			,\
			seq\
		)\
		template <typename V> operator V&() {\
			switch(this->base::which()) {\
				BOOST_PP_SEQ_FOR_EACH_I(\
					CASE, \
					, \
					seq\
				)\
				default: return (V&) boost::get<BOOST_PP_SEQ_ELEM(0,seq)>(*this);\
			}\
		};\
		virtual const std::string getStepParameter() const override {\
			std::string param;\
			switch(this->base::which()) {\
				BOOST_PP_SEQ_FOR_EACH_I(\
					GET_STEP_PARAMETER, \
					, \
					seq\
				)\
				default: break;\
			}\
		return param;\
		}\
		virtual const std::string classname() const override { return #select; };\
		static select readStepData(const std::string& value) {\
			auto name = value.substr(0, value.find_first_of('('));\
			BOOST_PP_SEQ_FOR_EACH_I(\
				READ_STEP_DATA, \
				select, \
				seq\
			)\
			return select();\
		}\
		select* operator->() { return this; };\
		const select* const operator->() const { return this; };\
		typedef select type;\
	};


//template<typename ...Args> class SelectType : public boost::variant<Args...> {
//	using base = boost::variant<Args...>;
//private:
//	class visitor_getStepParameter
//		: public boost::static_visitor<const std::string>
//	{
//	public:
//		template <typename T>
//		const std::string operator()(const T& operand) const
//		{
//			return operand.classname() + "(" + operand.getStepParameter() + ")";
//		}
//	};
//
//	template <typename V> class visitor_ref_cast
//		: public boost::static_visitor<V>
//	{
//	public:
//		template <typename T>
//		V& operator()(T& operand)
//		{
//			return operand.operator V&();
//		}
//	};
//
//	template <typename V> class visitor_const_ref_cast
//		: public boost::static_visitor<V>
//	{
//	public:
//		template <typename T>
//		const V& operator()(const T& operand) const
//		{
//			return operand.operator V&();
//		}
//	};
//
//	template <typename V> class visitor_const_cast
//		: public boost::static_visitor<V>
//	{
//	public:
//		template <typename T>
//		const V operator()(const T& operand) const
//		{
//			return operand.operator V();
//		}
//	};
//
//	template <typename V> class visitor_cast
//		: public boost::static_visitor<V>
//	{
//	public:
//		template <typename T>
//		V operator()(T& operand)
//		{
//			return (V)operand;
//		}
//	};
//
//	template<std::size_t I = 0, typename Function>
//	static inline typename std::enable_if<I == sizeof...(Args), void>::type
//	for_each(std::tuple<Args...> , Function) // Unused arguments are given no names.
//	{ }
//	
//	template<std::size_t I = 0, typename Function>
//	static inline typename std::enable_if<I < sizeof...(Args), void>::type
//		for_each(std::tuple<Args...> t, Function f)
//	{
//		f(std::get<I>(t));
//		for_each<I + 1, Function>(t, f);
//	}
//
//public:
//	
//	typedef base UnderlyingType;
//	using base::base;
//	using base::operator=;
//	virtual ~SelectType() {};
//
//	SelectType* operator->() { return this; };
//	const SelectType* const operator->() const { return this; };
//
//	//template <typename V> operator V() { return boost::apply_visitor(visitor_cast<V>(), *this); }
//	//template <typename V> explicit operator const V&() const & { return boost::apply_visitor(visitor_const_ref_cast<const V&>(), *this); }
//	//template <typename V> explicit operator V&() & { return boost::apply_visitor(visitor_ref_cast<V&>(), *this); }
//	//template <typename V> explicit operator const V() const { return boost::apply_visitor(visitor_const_cast<const V>(), *this); }
//
//	virtual const std::string getStepParameter() const {
//		return boost::apply_visitor(visitor_getStepParameter(), *this);
//	}
//
//	static base readStepData(const std::string& value, const std::shared_ptr<EXPRESSModel>& model) {
//		auto name = value.substr(0, value.find_first_of('('));
//		auto startpos = value.find_first_of('(') + 1;
//		auto arg = value.substr(startpos, value.find_first_of(')') - startpos);
//
//		std::tuple<Args...> variadicArgs = std::tuple<Args...>();
//		
//		base select;
//		//for_each(variadicArgs, [&select, &name, &arg, &model](auto type) {
//		//	if (name == type.classname()) {
//		//		type = decltype(type)::readStepData(arg, model);
//		//		select = type;
//		//	}
//		//});
//		return select;
//	}
//};


class visitor_getStepParameter
	: public boost::static_visitor<std::string>
{
public:
	template <typename T>
	const std::string operator()(const T& operand) const
	{
		return operand.classname() + "(" + operand.getStepParameter() + ")";
	}
};

template <typename ...Args> class SelectType : public ValueType<boost::variant<Args...>> {
	using base = ValueType<boost::variant<Args...>>;

	template<std::size_t I = 0, typename Function>
	static inline typename std::enable_if<I == sizeof...(Args), void>::type
		for_each(std::tuple<Args...>, Function) // Unused arguments are given no names.
	{ };
	
	template<std::size_t I = 0, typename Function>
	static inline typename std::enable_if<I < sizeof...(Args), void>::type
		for_each(std::tuple<Args...> t, Function f)
	{
		f(std::get<I>(t));
		for_each<I + 1, Function>(t, f);
	};

public:
	typedef boost::variant<Args...> Select;

	using base::base;
	using base::operator=;
	using base::operator->;

	template <class T> explicit operator T&() & {
		static_assert(boost::detail::variant::holds_element<Select, T >::value, "Cast to type is not defined.");
		return std::ref(boost::get<T>(base::m_value));
	}
	template <class T> explicit operator const T() const {
		static_assert(boost::detail::variant::holds_element<Select, T >::value, "Cast to type is not defined.");
		return boost::get<T>(base::m_value);
	}

	virtual const std::string getStepParameter() const {
		return boost::apply_visitor(visitor_getStepParameter(), base::m_value);
	}

	static Select readStepData(const std::string value, const std::shared_ptr<EXPRESSModel>& model) {
		auto name = value.substr(0, value.find_first_of('('));
		auto startpos = value.find_first_of('(') + 1;
		auto arg = value.substr(startpos, value.find_first_of(')') - startpos);

		std::tuple<Args...> variadicArgs = std::tuple<Args...>();
		
		Select select;
		SelectType::for_each(variadicArgs, [&select, &name, &arg, &model](auto type) {
			if (name == type.classname()) {
				type = decltype(type)::readStepData(arg, model);
				select = type;
			}
		});
		return select;
	}
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSSelect_10255db4_8b09_413b_9c43_ea39f1d63ced_h
