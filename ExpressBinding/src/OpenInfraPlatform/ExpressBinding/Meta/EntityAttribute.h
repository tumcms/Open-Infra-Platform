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
#ifndef OpenInfraPlatform_ExpressBinding_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h
#define OpenInfraPlatform_ExpressBinding_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h

#include "OpenInfraPlatform/ExpressBinding/Meta/Type.h"
#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include "OpenInfraPlatform/ExpressBinding/memory.h"
#include <string>
#include <iostream>
#include <sstream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

enum class eCardinality { Undefined, Single, Vector, Vector2D, Vector3D };

enum class eEntityAttributeParamterType { Simple, TypeNamed, eGeneralizedType };

class IEntityAttributeType {
  public:
    virtual ~IEntityAttributeType() {}
    virtual std::string toString() const = 0;
    virtual eEntityAttributeParamterType getType() const = 0;
};

class EntityAttributeSimpleType : public IEntityAttributeType {
  public:
    eType type;

    std::string toString() const override {
        switch (type) {
        case OpenInfraPlatform::ExpressBinding::eType::Unknown:
            break;
        case OpenInfraPlatform::ExpressBinding::eType::Real:
            return "REAL";
        case OpenInfraPlatform::ExpressBinding::eType::Boolean:
            return "BOOLEAN";
        case OpenInfraPlatform::ExpressBinding::eType::Binary:
            return "BINARY";
        case OpenInfraPlatform::ExpressBinding::eType::Integer:
            return "INTEGER";
        case OpenInfraPlatform::ExpressBinding::eType::Number:
            return "NUMBER";
        case OpenInfraPlatform::ExpressBinding::eType::Logical:
            return "LOGICAL";
        case OpenInfraPlatform::ExpressBinding::eType::String:
            return "STRING";
        case OpenInfraPlatform::ExpressBinding::eType::Array:
            return "ARRAY";
        case OpenInfraPlatform::ExpressBinding::eType::List:
            return "LIST";
        case OpenInfraPlatform::ExpressBinding::eType::Set:
            return "SET";
        case OpenInfraPlatform::ExpressBinding::eType::Enumeration:
            break;
        case OpenInfraPlatform::ExpressBinding::eType::Select:
            break;
        default:
            break;
        }

        throw std::runtime_error("Unknown type");
    }

    virtual eEntityAttributeParamterType getType() const {
        return eEntityAttributeParamterType::Simple;
    }
};

class EntityAttributeTypeNamedType : public IEntityAttributeType {
  public:
    std::string name;

    std::string toString() const override { return name; }

    virtual eEntityAttributeParamterType getType() const {
        return eEntityAttributeParamterType::TypeNamed;
    }
};

enum class eEntityAttributeContainerType { Array, Bag, List, Set };

class EntityAttributeGeneralizedType : public IEntityAttributeType {
  public:
    std::string toString() const override {
        std::stringstream ss;

        if (containerType == eEntityAttributeContainerType::Bag) {
            ss << "Bag";
        } else if (containerType == eEntityAttributeContainerType::Set) {
            ss << "Set";
        } else if (containerType == eEntityAttributeContainerType::List) {
            ss << "List";
        } else if (containerType == eEntityAttributeContainerType::Array) {
            ss << "Array";
        } else {
            throw std::runtime_error("Unknown entity attribute type.");
            ss << "EntityAttributeGeneralizedType";
        }

        return ss.str();
    }

    virtual eEntityAttributeParamterType getType() const {
        return eEntityAttributeParamterType::eGeneralizedType;
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

    eEntityAttributeParamterType getParamterType() const {
        return type->getType();
    }
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

OIP_OPENINFRAPLATFORM_EXPRESSBINDING_EMBED_INTO_OIP_NAMESPACE(eEntityAttributeParamterType)
OIP_OPENINFRAPLATFORM_EXPRESSBINDING_EMBED_INTO_OIP_NAMESPACE(eEntityAttributeContainerType)
OIP_OPENINFRAPLATFORM_EXPRESSBINDING_EMBED_INTO_OIP_NAMESPACE(EntityAttributeGeneralizedType)
OIP_OPENINFRAPLATFORM_EXPRESSBINDING_EMBED_INTO_OIP_NAMESPACE(EntityAttribute)

#endif // end define OpenInfraPlatform_ExpressBinding_Attribute_24a8f899_6b19_457c_ba3a_cd3c13626752_h