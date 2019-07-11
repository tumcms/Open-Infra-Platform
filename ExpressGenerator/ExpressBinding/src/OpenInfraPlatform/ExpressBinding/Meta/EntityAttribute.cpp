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

#include "EntityAttribute.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

EntityAttribute::EntityAttribute(const std::string& name) {
	this->name = name;
	this->cardinality = eCardinality::Undefined;
}

EntityAttribute::EntityAttribute() {
	this->name = "";
	this->cardinality = eCardinality::Undefined;
}

std::string EntityAttribute::getName() const {
	return name;
}

bool EntityAttribute::isOptional() const {
	return optional;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END


