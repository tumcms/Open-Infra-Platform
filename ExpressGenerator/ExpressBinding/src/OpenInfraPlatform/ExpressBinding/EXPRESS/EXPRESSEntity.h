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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include "EXPRESSObject.h"

#include <tuple>
#include <utility>


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN


class EXPRESSEntity : public EXPRESSObject {
public:
	const size_t getId() const {
		return m_id;
	}

	void setId(size_t id) {
		m_id = id;
	}

	virtual const std::string getStepParameter() const override {
		return "#" + std::to_string(m_id);
	}

	virtual const std::string classname() const = 0;

	virtual const std::string getStepLine() const = 0;

	//template <typename EntityType> static EntityType readStepData(const std::string& args, const std::shared_ptr<EXPRESSModel>& model) {
	//	/*
	//	ExpressBinding::for_each(this->getAttributes(),[this,&stepLine](auto attr) {
	//	stepLine.append(attr.getStepParameter()).append(',');
	//	});
	//	*/
	//	EntityType entity = EntityType();
	//	for_each(entity.getAttributes(), [&args, &model](auto& attr) {
	//		attr = decltype(attr)::readStepData(args);
	//	});
	//	return entity;
	//}
protected:
	//template<std::size_t I = 0, typename FuncT, typename... Tp>
	//typename std::enable_if<I == sizeof...(Tp), void>::type
	//	for_each(std::tuple<Tp...> , FuncT) // Unused arguments are given no names.
	//{ }
	//
	//template<std::size_t I = 0, typename FuncT, typename... Tp>
	//typename std::enable_if < I < sizeof...(Tp), void>::type
	//	for_each(std::tuple<Tp...> t, FuncT f)
	//{
	//	f(std::get<I>(t));
	//	for_each<I + 1, FuncT, Tp...>(t, f);
	//}

protected:
	size_t m_id;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

//using ENTITY = OpenInfraPlatform::ExpressBinding::EXPRESSEntity;

//#define EXPAND(...) __VA_ARGS__
//
//#define ATTRIBUTE(type, name) EXPAND(type) BOOST_PP_CAT(name,;)
//
//#define DEFINE_ATTRIBUTE(r, data, i, elem) BOOST_PP_SEQ_ELEM(0, EXPAND(elem)) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1,elem),data)
//
//#define DEFINE_SUPERTYPE(r, data, i, elem) BOOST_PP_LPAREN data elem BOOST_PP_RPAREN
//
//#define DEFINE_ENTITY(entity, supertype, ... )\
//	class entity : public supertype {\
//	public:\
//		virtual const std::string classname() const override {return #entity ; };\
//		virtual const std::string getStepLine() const override {\
//			return "";\
//		}; \
//		\
//		/* Attributes */\
//		__VA_ARGS__ \
//	};
//BOOST_PP_REMOVE_PARENS(BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_FOR_EACH_I(DEFINE_SUPERTYPE, public, BOOST_PP_TUPLE_TO_SEQ(supertypes))))

#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h
