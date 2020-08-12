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

#include "Meta/Schema.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

Schema& Schema::getInstance() {
	static OpenInfraPlatform::ExpressBindingGenerator::Schema instance;
	return instance;
}

size_t Schema::getEntityCount() const {
	return entities_.size();
}

void Schema::addEntity(const Entity& entity) {
	entities_.push_back(entity);
}

Entity Schema::getEntityByIndex(size_t index) const {
	return entities_[index];
}

Entity Schema::getEntityByName(const std::string& name) const {
	for (const auto ent : entities_) 
		if (ent.getName() == name)
			return ent;

	throw std::runtime_error("Entity does not exist.");
}

bool OpenInfraPlatform::ExpressBindingGenerator::Schema::hasEntity(const std::string& name) const {
	for (const auto ent : entities_)
		if (ent.getName() == name)
			return true;

	return false;
}

std::vector<std::string> Schema::getSuperTypes(const Entity& entity) const {
	std::vector<std::string> result;

	Entity entityCopy = entity;
	Entity& currentEntity = entityCopy;

	while (currentEntity.hasSupertype()) {
		std::string supertype = currentEntity.getSupertype();

		result.push_back(supertype);

		currentEntity = getEntityByName(supertype);
	}

	std::reverse(result.begin(), result.end());

	return result;
}

void Schema::addType(Type type) {
	types_.push_back(type);
}

size_t Schema::getTypeCount() const {
	return types_.size();
}

Type Schema::getTypeByIndex(size_t index) const {
	return types_[index];
}

std::string Schema::getName() const {
	return name_;
}

void Schema::setName(const std::string& name) {
	name_ = name;
}

bool Schema::isIntegerType(const std::string& name) const {
	if (name == "") {
		return false;
	}

	if (name == "REAL") {
		return false;
	}

	if (name == "BINARY") {
		return false;
	}

	if (name == "BOOLEAN") {
		return false;
	}

	if (name == "INTEGER") {
		return true;
	}

	if (name == "STRING") {
		return false;
	}

	if (name == "LOGICAL") {
		return false;
	}

	if (name == "NUMBER") {
		return false;
	}

	if(hasType(name))
		return isIntegerType(getTypeByName(name).getUnderlyingTypeName());
	else
		return false;
}

bool Schema::isRealType(const std::string& realName) const {
	if (realName == "") {
		return false;
	}

	if (realName == "REAL") {
		return true;
	}

	if (realName == "BINARY") {
		return false;
	}

	if (realName == "BOOLEAN") {
		return false;
	}

	if (realName == "INTEGER") {
		return false;
	}

	if (realName == "STRING") {
		return false;
	}

	if (realName == "LOGICAL") {
		return false;
	}

	if (realName == "NUMBER") {
		return false;
	}

	if(hasType(realName))
		return isRealType(getTypeByName(realName).getUnderlyingTypeName());
	else
		return false;
}

bool Schema::isSelectType(const std::string& name) const {
	for (const auto typ : types_) 
		if (typ.getName() == name) 
			return typ.isSelectType();

	throw std::runtime_error("Type does not exist.");
}

Type Schema::getTypeByName(const std::string& name) const {
	for (const auto typ : types_)
		if (typ.getName() == name)
			return typ;

	throw std::runtime_error("Type does not exist.");
}

bool Schema::hasType(const std::string& name) const {
	for (const auto typ : types_)
		if (typ.getName() == name)
			return true;

	return false;
}

std::vector<std::string> Schema::getAllEntityAttributesNames(const Entity& entity, const bool includingInverse) const {
	std::vector<EntityAttribute> attributes = getAllEntityAttributes(entity, includingInverse);
	std::vector<std::string> result(attributes.size());
	std::transform(attributes.begin(), attributes.end(), result.begin(), [](const auto it) { return it.getName(); });
	return result;
}

std::vector<EntityAttribute> Schema::getAllEntityAttributes(const Entity& entity, const bool includingInverse) const {
	std::vector<EntityAttribute> result;

	auto superTypes = getSuperTypes(entity);

	for (const auto superType : superTypes) {
		Entity x = getEntityByName(superType);

		for (int ai = 0; ai < x.getAttributeCount(); ++ai) {
			if( includingInverse || !x.getAttribute(ai).isInverse() )
				result.push_back(x.getAttribute(ai));
		}
	}

	for (int ai = 0; ai < entity.getAttributeCount(); ai++) {
		if (includingInverse || !entity.getAttribute(ai).isInverse())
			result.push_back(entity.getAttribute(ai));
	}

	return result;
}

const bool Schema::isAbstract(const Entity & entity) const
{
	return getAllEntityAttributes(entity, false).size() == 0;
}

void Schema::linkInverses()
{
	for (auto ent : entities_)
	{
		for (auto attr : ent.getAttributes())
		{
			if (attr.isInverse())
			{
				if (attr.getInverses().empty())
					throw std::runtime_error("Inverse attribute was empty!");

				const std::string entity = attr.getInverses().front().first;
				for( auto it = entities_.begin(); it != entities_.end(); it++ )
				{
					if( it->getName() == entity )
				//	auto superTypes = getSuperTypes(*it);
				//	auto found = std::find(superTypes.begin(), superTypes.end(), inverseEntity);
				//	if( found != superTypes.end() )
						it->addInverseCounterpart(attr.getInverses().front().second, ent.getName(), attr.getName());
				}
			}
		}
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END
