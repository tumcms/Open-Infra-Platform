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

#pragma once
#ifndef OpenInfraPlatform_ExpressBindingGenerator_Schema_344294e5_aaf8_4f53_b817_db5ca43e2d80_h
#define OpenInfraPlatform_ExpressBindingGenerator_Schema_344294e5_aaf8_4f53_b817_db5ca43e2d80_h

#include "General/namespace.h"
#include "Meta/Entity.h"
#include "Meta/EntityAttribute.h"
#include "Meta/Type.h"
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class Schema {
  public:
    static Schema &getInstance();

    //---------------------------------------------------------------
    // Entities
    //---------------------------------------------------------------

    // Total count of entities
    int getEntityCount() const;

    void addEntity(const Entity &entity);

    Entity getEntityByIndex(int index) const;

    Entity getEntityByName(const std::string &name) const;
	
	bool hasEntity(const std::string &name) const;

    std::vector<std::string> getAllEntityAttributesNames(const Entity &entity, const bool includingInverse);

    std::vector<EntityAttribute> getAllEntityAttributes(const Entity &entity, const bool includingInverse) const;

	const bool isAbstract(const Entity &entity) const;

    //---------------------------------------------------------------
    // Types
    //---------------------------------------------------------------

    void addType(Type type);

    int getTypeCount() const;

    Type getTypeByIndex(int index) const;

    const Type &getTypeByName(const std::string &typeName) const;
	const Type &getUnderlyingType(const std::string &name) const {
		return getTypeByName(getTypeByName(name).getUnderlyingTypeName());
	}

	bool hasType(const std::string &typeName) const;

	bool isRealType(const std::string& name) const;
	bool isIntegerType(const std::string& name) const;
	bool isSelectType(const std::string& name) const;
    //---------------------------------------------------------------
    // Supertypes
    //---------------------------------------------------------------
	
    // Collects all super types of the corresponding entity
    std::vector<std::string> getSuperTypes(const Entity &entity) const;

    //---------------------------------------------------------------
    // Schema
    //---------------------------------------------------------------

    std::string getName() const;
    void setName(const std::string &name);

    std::vector<Entity> entities_;
    std::vector<Type> types_;
    std::string name_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(Schema)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Schema_344294e5_aaf8_4f53_b817_db5ca43e2d80_h