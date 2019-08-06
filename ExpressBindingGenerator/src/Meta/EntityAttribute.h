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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h
#define OpenInfraPlatform_ExpressBindingGenerator_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h

#include "Meta/Type.h"
#include "General/namespace.h"
#include "General/memory.h"

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class Schema;

enum class eCardinality { Undefined, Single, Vector, Vector2D, Vector3D };

enum class eEntityAttributeParameterType { Simple, TypeNamed, eGeneralizedType };

class IEntityAttributeType {
  public:
    virtual ~IEntityAttributeType() {}
    virtual std::string toString() const = 0;
    virtual eEntityAttributeParameterType getType() const = 0;
};

class EntityAttributeSimpleType : public IEntityAttributeType {
  public:
    eType type;

	int width_spec = 0; // width_spec of 0 means that there is no width spec for the simple attribute

    std::string toString() const override {
		//std::string prefix = "ExpressBindingGenerator::";
		std::string underlyingType;
        switch (type) {
        case OpenInfraPlatform::ExpressBindingGenerator::eType::Unknown:
            break;
        case OpenInfraPlatform::ExpressBindingGenerator::eType::Real:
			underlyingType = "REAL";
			break;
        case OpenInfraPlatform::ExpressBindingGenerator::eType::Boolean:
			underlyingType = "BOOLEAN";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Binary:
			underlyingType = "BINARY";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Integer:
			underlyingType = "INTEGER";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Number:
			underlyingType = "NUMBER";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Logical:
			underlyingType = "LOGICAL";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::String:
			underlyingType = "STRING";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Array:
			underlyingType = "ARRAY";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::List:
			underlyingType = "LIST";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Set:
			underlyingType = "SET";
			break;
		case OpenInfraPlatform::ExpressBindingGenerator::eType::Enumeration:
            break;
        case OpenInfraPlatform::ExpressBindingGenerator::eType::Select:
            break;
        default:
            break;
        }
		return underlyingType;

        throw std::runtime_error("Unknown type");
    }

    virtual eEntityAttributeParameterType getType() const {
        return eEntityAttributeParameterType::Simple;
    }
};

class EntityAttributeTypeNamedType : public IEntityAttributeType {
  public:
    std::string name;

    std::string toString() const override { return name; }

    virtual eEntityAttributeParameterType getType() const {
        return eEntityAttributeParameterType::TypeNamed;
    }
};

enum class eEntityAttributeContainerType { Array, Bag, List, Set };

class EntityAttributeGeneralizedType : public IEntityAttributeType {
  public:
    std::string toString() const override {
        std::stringstream ss;
		//ss << "ExpressBindingGenerator::";
        if (containerType == eEntityAttributeContainerType::Bag) {
            ss << "BAG";
        } else if (containerType == eEntityAttributeContainerType::Set) {
            ss << "SET";
        } else if (containerType == eEntityAttributeContainerType::List) {
            ss << "LIST";
        } else if (containerType == eEntityAttributeContainerType::Array) {
            ss << "ARRAY";
        } else {
            throw std::runtime_error("Unknown entity attribute type.");
            ss << "EntityAttributeGeneralizedType";
        }

        return ss.str();
    }

    virtual eEntityAttributeParameterType getType() const {
        return eEntityAttributeParameterType::eGeneralizedType;
    }

    eEntityAttributeContainerType containerType;

    ReferenceCounted<IEntityAttributeType> elementType;
};

class EntityAttribute {
  public:
    EntityAttribute();
    EntityAttribute(const std::string &name);

    std::string getName() const;
    bool isOptional() const;

    std::string name;
    eCardinality cardinality;
    bool optional;

    ReferenceCounted<IEntityAttributeType> type;

    eEntityAttributeParameterType getParameterType() const {
        return type->getType();
    }

	const std::string toString(const Schema& schema) const;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(eEntityAttributeParameterType)
EMBED_INTO_OIP_NAMESPACE(eEntityAttributeContainerType)
EMBED_INTO_OIP_NAMESPACE(EntityAttributeGeneralizedType)
EMBED_INTO_OIP_NAMESPACE(EntityAttribute)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h
