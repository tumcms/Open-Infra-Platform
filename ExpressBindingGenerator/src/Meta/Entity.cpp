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

#include "Meta/Entity.h"

OpenInfraPlatform::ExpressBindingGenerator::Entity::Entity() {

}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

std::string Entity::getName() const {
	return name_;
}

void Entity::setName(const std::string& value) {
	name_ = value;
}

bool Entity::isAbstract() const { 
	return abstract_;
}

void Entity::setAbstract( const bool b ) { 
	abstract_ = b;
}

size_t Entity::getSubtypeCount() const {
	return subtypes_.size();
}

void Entity::addSubtype(const std::string& subtype) {
	subtypes_.push_back(subtype);
}

std::string Entity::getSubtypeByIndex(const size_t index) const {
	return subtypes_[index];
}

size_t Entity::getAttributeCount() const {
	return attributes_.size();
}

void Entity::addAttribute(const EntityAttribute& att)
{
	attributes_.push_back(att);
}

const EntityAttribute& Entity::getAttribute(const size_t index) const
{
	return attributes_[index];
}

const std::vector<EntityAttribute> Entity::getAttributes() const
{
	return attributes_;
}

void Entity::setParentEntity(const std::string& value) {
	parentEntity_ = value;
}

std::string Entity::getSupertype() const {
	return parentEntity_;
}

bool Entity::hasSupertype() const {
	return !parentEntity_.empty();
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END
