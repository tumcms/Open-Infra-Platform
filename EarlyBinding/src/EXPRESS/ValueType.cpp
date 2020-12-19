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

#include "ValueType.h"  

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

template <> 
const std::string ValueType<double>::getStepParameter() const { 
	return std::to_string(ValueType<double>::m_value); 
}

template <> 
const std::string ValueType<int>::getStepParameter() const { 
	return std::to_string(ValueType<int>::m_value); 
}

template <> 
const std::string ValueType<bool>::getStepParameter() const { 
	return std::to_string(ValueType<bool>::m_value); 
}

template <> 
const std::string ValueType<std::string>::getStepParameter() const { 
	return "'" + ValueType<std::string>::m_value + "'"; 
}

template <> 
const std::string ValueType<boost::logic::tribool>::getStepParameter() const {
	switch (ValueType<boost::logic::tribool>::m_value.value) {
	case boost::logic::tribool::true_value: return "TRUE";
	case boost::logic::tribool::false_value: return "FALSE";
	case boost::logic::tribool::indeterminate_value: return "UNKNOWN";
	}
	return "ERROR";
}

template <>
double ValueType<double>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return 0.0;
	}
	else {
		return (stod(value));
	}
}

template <>
int ValueType<int>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return 0;
	}
	else {
		return (stoi(value));
	}
}

template <>
bool ValueType<bool>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value == "*") {
		//TODO : Implement behaviour
		return false;
	}
	else {
		std::string lower = boost::algorithm::to_lower_copy(value);
		return (lower == "true" || lower == ".t.");
	}
}

template <>
std::string ValueType<std::string>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	if (value.at(0) == '\'') {
		return value.substr(1, value.length() - 2);
	}
	else {
		return value;
	}
}

template <>
boost::logic::tribool ValueType<boost::logic::tribool>::readStepData(const std::string &value, const std::shared_ptr<EXPRESSModel>&) {
	std::string lower = boost::algorithm::to_lower_copy(value);
	if (value == "*") {
		//TODO : Implement behaviour
		return boost::logic::tribool(boost::logic::indeterminate);
	}
	else {
		if (lower == "true" || lower == ".t.") {
			return boost::logic::tribool::true_value;
		}
		else if (lower == "false" || lower == ".f.") {
			return boost::logic::tribool::false_value;
		}
		else {
			return boost::logic::tribool(boost::logic::indeterminate);
		}
	}
}


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

