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

#include "Meta/EntityAttribute.h"

#include "Meta/Schema.h"


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

EntityAttribute::EntityAttribute(const std::string& name) {
	this->name = name;
}

EntityAttribute::EntityAttribute() {
	this->name = "";
}

std::string EntityAttribute::getName() const {
	return name;
}

bool EntityAttribute::isOptional() const {
	return optional;
}

bool EntityAttribute::isInverse() const {
	return inverse;
}

bool EntityAttribute::hasInverseCounterpart() const {
	return !isInverse() && !inverses.empty();
}

std::vector<std::tuple<std::string, std::string, std::string>> EntityAttribute::getInverses() const {
	return inverses;
}

void EntityAttribute::addInverseCounterpart(const std::string& entity, const std::string& attr, const std::string& mainEntity) {
	if( std::find_if(inverses.begin(), inverses.end(), [&](auto &el) { return std::template get<0>(el) == entity; }) == inverses.end() )
		inverses.push_back(std::tuple<std::string, std::string, std::string>(entity, attr, mainEntity));
}

const std::string EntityAttribute::toString(const Schema & schema) const {
	std::string typeName = type->toString();
	//std::string prefix = "ExpressBindingGenerator::";

	if (type->getType() == eEntityAttributeParameterType::TypeNamed || type->getType() == eEntityAttributeParameterType::Simple) {
		if (schema.hasType(typeName)) {
			if (type->getType() == eEntityAttributeParameterType::Simple) {
				//typeName = prefix + typeName;
			}
			if (isOptional())
				return "EXPRESSOptional<" + typeName + ">";
			else
				return typeName;
		}
		else if (schema.hasEntity(typeName)) {
			if (isOptional())
				return "EXPRESSOptional<EXPRESSReference<" + typeName + ">> ";
			else
				return "EXPRESSReference<" + typeName + ">";
		}
	}
	else {
		std::string attributeType;
		int dim = 0;
		auto elementType = type;
		while (elementType->getType() == eEntityAttributeParameterType::eGeneralizedType) {
			//attributeType.append("ExpressBindingGenerator::" + elementType->toString() + "<0," + elementType->toString() + "_MAXSIZE,");
			attributeType.append(elementType->toString() + "<0," + elementType->toString() + "_MAXSIZE,");
			dim++;
			elementType = std::static_pointer_cast<EntityAttributeGeneralizedType>(elementType)->elementType;
		}

		if (schema.hasEntity(elementType->toString()))
			attributeType.append("EXPRESSReference<" + elementType->toString() + ">");
		else
			attributeType.append(elementType->toString());

		while (dim > 0) {
			attributeType.append(">");
			dim--;
		}

		if (isOptional())
			return "EXPRESSOptional<" + attributeType + "> ";
		else
			return attributeType;
	}
	return typeName;
	//return prefix + typeName;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END


