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

#include "Schema.h"

using namespace std;

int yyparse();
extern FILE *yyin;
extern int line_num;

void yyerror(const char *s)
{
	cout << "Parse error!  Message: " << s << endl;
	cout << "Line number: " << line_num << endl;
	// might as well halt now:
	exit(-1);
}


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

Schema& Schema::getInstance() {
	static OpenInfraPlatform::ExpressBinding::Schema instance;
	return instance;
}

Schema & Schema::read(std::string filename)
{
	FILE *myfile = fopen(filename.data(), "r");
	
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while(!feof(yyin));

	return getInstance();
}

int Schema::getEntityCount() const {
	return static_cast<int>(entities_.size());
}

void Schema::addEntity(const Entity& entity) {
	entities_.push_back(entity);
}

Entity Schema::getEntityByIndex(int index) const {
	return entities_[index];
}

Entity Schema::getEntityByName(const std::string& name) const {
	for (int i = 0; i < entities_.size(); ++i) {
		if (entities_[i].getName() == name) {
			return entities_[i];
		}
	}

	throw std::runtime_error("Entity does not exist.");
}

bool OpenInfraPlatform::ExpressBinding::Schema::hasEntity(const std::string& name) const {
	for (int i = 0; i < entities_.size(); ++i) {
		if (entities_[i].getName() == name) {
			return true;
		}
	}

	return false;
}

std::vector<std::string> Schema::getSuperTypes(const Entity& entity) {
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

int Schema::getTypeCount() const {
	return static_cast<int>(types_.size());
}

Type Schema::getTypeByIndex(int index) const {
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

	std::string i = getTypeByName(name).getUnderlyingTypeName();

	return isIntegerType(i);
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

	std::string i = getTypeByName(realName).getUnderlyingTypeName();

	return isRealType(i);
}

bool Schema::isSelectType(const std::string& name) const {
	for (unsigned int i = 0; i < types_.size(); ++i) {
		if (types_[i].getName() == name) {
			return types_[i].isSelectType();
		}
	}

	throw std::runtime_error("Type does not exist.");
}

const Type& Schema::getTypeByName(const std::string& typeName) const {
	for (unsigned int i = 0; i < types_.size(); ++i) {
		if (types_[i].getName() == typeName) {
			return types_[i];
		}
	}

	throw std::runtime_error("Type does not exist.");
}

bool Schema::hasType(const std::string& typeName) const {
	for (unsigned int i = 0; i < types_.size(); ++i) {
		if (types_[i].getName() == typeName) {
			return true;
		}
	}

	return false;
}

std::vector<std::string> Schema::getAllEntityAttributesNames(const Entity& entity) {
	std::vector<std::string> result;

	auto superTypes = getSuperTypes(entity);

	for (int i = 0; i < superTypes.size(); ++i) {
		Entity x = getEntityByName(superTypes[i]);

		for (int ai = 0; ai < x.getAttributeCount(); ++ai) {
			result.push_back(x.getAttribute(ai).getName());
		}
	}

	for (int ai = 0; ai < entity.getAttributeCount(); ai++) {
		result.push_back(entity.getAttribute(ai).getName());
	}

	return result;
}

std::vector<EntityAttribute> Schema::getAllEntityAttributes(const Entity& entity) {
	std::vector<EntityAttribute> result;

	auto superTypes = getSuperTypes(entity);

	for (int i = 0; i < superTypes.size(); ++i) {
		Entity x = getEntityByName(superTypes[i]);

		for (int ai = 0; ai < x.getAttributeCount(); ++ai) {
			result.push_back(x.getAttribute(ai));
		}
	}

	for (int ai = 0; ai < entity.getAttributeCount(); ai++) {
		result.push_back(entity.getAttribute(ai));
	}

	return result;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
