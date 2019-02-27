/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is free
    software; you can redistribute it and/or modify it under the terms
    of the GNU General Public License Version 3 as published by the Free
    Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Type.h"

#include <iostream>
#include <sstream>

#include <set>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

Type::Type() : name_("Unknown"), type_(eType::Unknown), containerType_("Unknown") {
}

std::string Type::getName() const {
	return name_;
}

void Type::setName(std::string val) {
	name_ = val;
}

eType Type::getType() const {
	return type_;
}

void Type::setType(eType val) {
	type_ = val;
}



std::string Type::getUnderlyingTypeName() const {
	std::string prefix = "ExpressBinding::";
	if (isSimpleType()) {
		if (type_ == eType::Real) {
			return prefix + "REAL";
		}

		if (type_ == eType::Binary) {
			return prefix + "BINARY";
		}

		if (type_ == eType::Boolean) {
			return prefix + "BOOLEAN";
		}

		if (type_ == eType::Integer) {
			return prefix + "INTEGER";
		}

		if (type_ == eType::String) {
			return prefix + "STRING";
		}

		if (type_ == eType::Logical) {
			return prefix + "LOGICAL";
		}

		if (type_ == eType::Number) {
			return prefix + "NUMBER";
		}

		throw std::runtime_error("Unknown basic type");
	}

	if (isEnumeration()) {
		std::stringstream ss;
		ss << "ENUMERATION OF(";

		for (int i = 0; i < types_.size(); ++i) {
			ss << types_[i];
		}

		return ss.str();
	}

	if (isList()) {
		std::stringstream ss;
		ss << "LIST [" << getContainerCardinalityMin() << ":" << getContainerCardinalityMax() << "] "
		   << "OF " << containerType_;
		return ss.str();
	}

	if (underlyingTypeName_ == "") {
		std::cout << this->getName() << std::endl;
	}

	return underlyingTypeName_;
}

void Type::setUnderlyingTypeName(const std::string& value) {
	underlyingTypeName_ = value;
}

std::string Type::getContainerType() const {
	std::string prefix = "ExpressBinding::";
	std::set<std::string> prefixedTypes = { "INTEGER","REAL","NUMBER","BOOLEAN","BINARY","LOGICAL","LIST","ARRAY","SET","BAG","STRING" };
	if (prefixedTypes.count(containerType_) > 0)
		return prefix + containerType_;
	else
		return containerType_;
}

void Type::setContainerType(const std::string& value) {
	containerType_ = value;
}

int Type::getContainerCardinalityMin() const {
	return containerCardinalityMin_;
}

void Type::setContainerCardinalityMin(int val) {
	containerCardinalityMin_ = val;
}

int Type::getContainerCardinalityMax() const {
	return containerCardinalityMax_;
}

void Type::setContainerCardinalityMax(int val) {
	containerCardinalityMax_ = val;
}

void Type::setTypes(const std::vector<std::string>& types) {
	types_ = types;
}

int OpenInfraPlatform::ExpressBinding::Type::getTypeCount() const {
	return static_cast<int>(types_.size());
}

std::vector<std::string> Type::getTypes() const {
	return types_;
}

std::string Type::getType(const int index) const {
	return types_[index];
}

bool Type::isSimpleType() const {
	if (type_ == eType::Real) {
		return true;
	}

	if (type_ == eType::Binary) {
		return true;
	}

	if (type_ == eType::Boolean) {
		return true;
	}

	if (type_ == eType::Integer) {
		return true;
	}

	if (type_ == eType::String) {
		return true;
	}

	if (type_ == eType::Logical) {
		return true;
	}

	if (type_ == eType::Number) {
		return true;
	}

	return false;
}

bool Type::isEnumeration() const {
	return type_ == eType::Enumeration;
}

bool Type::isArray() const {
	return type_ == eType::Array;
}

bool Type::isList() const {
	return type_ == eType::List;
}

bool Type::isSet() const {
	return type_ == eType::Set;
}

bool Type::isSelectType() const {
	return type_ == eType::Select;
}

bool Type::isDerivedType() const
{
	return !isSimpleType() && !isSelectType() && !isEnumeration() && !isContainerType();
}

std::string Type::getContainerTypeName() const
{
	if (isContainerType()) {
		switch (type_) {
		case eType::List: return "LIST";
		case eType::Array: return "ARRAY";
		case eType::Set: return "SET";
		}
	}
	else {
		return "BAG";
	}
	
}

std::string Type::getContainerTypeIdentifier() const
{
	std::string identifier = getContainerTypeName() + "," + std::to_string(getContainerCardinalityMin()) + "," + std::to_string(getContainerCardinalityMax()) + ",";
	return identifier + getContainerType();
}

bool Type::isContainerType() const
{
	return isList() || isArray() || isSet();
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
