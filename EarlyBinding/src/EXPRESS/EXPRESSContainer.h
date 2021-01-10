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
#include <mutex>

#include <initializer_list>
#include <type_traits>


#include <boost/preprocessor.hpp>


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN


template <typename ValueType, size_t MinCardinality, size_t MaxCardinality>
class
EXPRESSContainer : public std::vector<ValueType> 
{
	using base = std::vector<ValueType>;
public:
	typedef base UnderlyingType;
	typedef ValueType element_type;

	using base::base;

	EXPRESSContainer& operator=(const EXPRESSContainer& other)
	{
		this->base::operator=(other);
		return *this;
	}

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
		// Loop over the rest
		std::string::iterator it = paramvalue.begin();
		size_t start = 0;
		// The result
		std::vector<ValueType> result;

		// Amount of open parenthesis
		size_t nOpenedParenthesis = 0;

		// Loop until the end
		while (it != paramvalue.end()) {

			// The current position of the iterator
			auto currentpos = std::distance(paramvalue.begin(), it);

			// Skip the content of string literal, if some parenthesis were open already
			// The content of the literal will get managed later in the recursion
			if (*it == '\''
				&& nOpenedParenthesis > 0)
			{
				auto pos = paramvalue.find_first_of('\'', currentpos + 1);
				it += pos - currentpos;
				continue;
			}

			// React according to the character in question
			switch (*it)
			{
			case ' ':
			{
				// ignore outside a string literal
				it++;
				continue;
			}
			case '(':
			{
				// count up
				nOpenedParenthesis++;
				// Remeber position, if first
				if (nOpenedParenthesis == 1)
					start = currentpos;
				it++;
				continue;
			}
			case ')':
			{
				// count down
				nOpenedParenthesis--;
			}
			} // end switch (*it)

			// Two cases:
			//  -> if it is just a simple container
			//       i.e. (aa,bb,cc) - the out-most parenthesis were already removed, so we are dealing with aa,bb,cc
			//       <start - our position>                                                                  x          (start = our position)
			//       or                                                                                         x
			//  -> or we have finished with one element within the container
			//       i.e. ((a,b),(c,d)) - again, the out-most parenthesis were removed already -> (a,b),(c,d)
			//       <start - our position>                                                       <   >
			//       or																					<   >
			if (nOpenedParenthesis == 0)
			{
				// check if it is a select type - need to account for that
				// e.g. #491= IFCINDEXEDPOLYCURVE(#545,(IFCLINEINDEX((1,2,3,4,1))),.F.);
				//    <from - to>                      <                         >
				// find the first comma that follows
				auto posEnd = paramvalue.find_first_of(',', currentpos + 1);
				auto posMid = paramvalue.find_first_of('(', currentpos + 1);
				// if none found -> take the end
				if (posEnd == std::string::npos)
					posEnd = paramvalue.size();
				// if '(' comes before ',' -> we have a case of SelectType
				if (posMid != std::string::npos && posMid < posEnd)
				{
					auto cntr = posMid;
					int countOpened = 1;
					bool brk = false;
					bool ignr = false;
					while (!brk && ++cntr < paramvalue.size())
					{
						if(ignr)
						{
							if (paramvalue.at(cntr) == '\'')
							{
								ignr = false;
							}

							continue;
						}

						switch (paramvalue.at(cntr))
						{
						case '\'':
						{
							ignr = true;
							break;
						}
						case ')':
						{
							if (--countOpened == 0)
								brk = true;
							break;
						}
						case '(':
						{
							countOpened++;
							break;
						}
						}
					}

					posEnd = paramvalue.find_first_of(',', cntr+1);
					// if none found -> take the end
					if (posEnd == std::string::npos)
						posEnd = paramvalue.size();
				}

				// Interpret the value
				ValueType type;
				std::string sub = paramvalue.substr(start, posEnd -start);
				type = ValueType::readStepData(sub, model);
				result.push_back(type);

				// Continue along the string, skip the sub
				auto len = posEnd - currentpos;
				// if we are in the middle of a list, count 1 more to skip the comma
				if ( it + len != paramvalue.end() )
					len += 1;
				// count up
				it += len;
				start += len;
				continue;
			}

			// go to next char
			it++;
		}

		return result;
	}

	friend void swap(EXPRESSContainer& first, EXPRESSContainer& second)
	{		
		first.base::swap(second);
	}

	// concurrent adding
	void parallel_push_back(const ValueType& element)
	{
		std::lock_guard<std::mutex> lockGuard(mtx);
		this->base::push_back(element);
	}

	// mutex to lock when concurrently adding
	std::mutex mtx;
};

template <size_t MinCardinality, size_t MaxCardinality, typename T> using LIST = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using SET = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using BAG = EXPRESSContainer<T, MinCardinality, MaxCardinality>;
template <size_t MinCardinality, size_t MaxCardinality, typename T> using ARRAY = EXPRESSContainer<T, MinCardinality, MaxCardinality>;

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END


EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(LIST)
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(SET)
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(BAG)
EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(ARRAY)

#define LIST_MAXSIZE ULLONG_MAX
#define ARRAY_MAXSIZE ULLONG_MAX
#define SET_MAXSIZE ULLONG_MAX
#define BAG_MAXSIZE ULLONG_MAX


#endif // end define OpenInfraPlatform_ExpressBidning_EXPRESSContainer_b030829d_7f85_44aa_87a3_e2a92f69bcfe_h
