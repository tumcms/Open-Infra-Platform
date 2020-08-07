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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_Entity_ae022d70_8143_4f95_aec7_d51148a382a0_h
#define OpenInfraPlatform_ExpressBindingGenerator_Entity_ae022d70_8143_4f95_aec7_d51148a382a0_h

#include "Meta/EntityAttribute.h"
#include "General/namespace.h"
#include <vector>
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN


struct qualifiedAttribute {
	std::string groupQualifier;
	std::string attributeQualifier;
};

class Entity {
  public:
    Entity();
    virtual ~Entity() {}
    
    Entity( const Entity& other ) = default;
    Entity( Entity&& other ) = default;

    Entity& operator=( const Entity& other ) = default;

    std::string getName() const;

    void setName(const std::string &value);

    //---------------------------------------------------------------
    // Abstract
    //---------------------------------------------------------------

    bool isAbstract() const;

    void setAbstract( const bool b );

    //---------------------------------------------------------------
    // Supertypes
    //---------------------------------------------------------------

    void setParentEntity(const std::string &value);

    bool hasSupertype() const;

    std::string getSupertype() const;

    //---------------------------------------------------------------
    // Subtypes
    //---------------------------------------------------------------

	size_t getSubtypeCount() const;

    void addSubtype(const std::string &subtype);

    std::string getSubtypeByIndex(const size_t index) const;

    //---------------------------------------------------------------
    // Attributes
    //---------------------------------------------------------------

	size_t getAttributeCount() const;

    void addAttribute(const EntityAttribute &att);

    const EntityAttribute &getAttribute(const size_t index) const;

	const std::vector<EntityAttribute> getAttributes() const;

	//---------------------------------------------------------------
	// Qualified Attributes
	//---------------------------------------------------------------

	void addQualifiedAttribute(const std::string &groupQualifier, const std::string &attributeQualifier) {
		qualifiedAttribute qa;
		qa.groupQualifier = groupQualifier;
		qa.attributeQualifier = attributeQualifier;
		qualifiedAttributes_.push_back(qa);
	}

	void addQualifiedAttribute(const qualifiedAttribute& attribute) {
		qualifiedAttributes_.push_back(attribute);
	}

	size_t getQualifiedAttributeCount() const {
		return qualifiedAttributes_.size();
	}

	qualifiedAttribute getQualifiedAttributeByIndex(const size_t index) const {
		return qualifiedAttributes_[index];
	}

	bool hasQualifiedAttribute(const std::string& attributeQualifier) const {
		for (auto qa : qualifiedAttributes_)
			if (qa.attributeQualifier == attributeQualifier)
				return true;

		return false;
	}


  private:
    bool abstract_;
    std::string parentEntity_;
    std::string name_;
    std::vector<std::string> subtypes_;
    std::vector<EntityAttribute> attributes_;
	std::vector<qualifiedAttribute> qualifiedAttributes_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(Entity)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Entity_ae022d70_8143_4f95_aec7_d51148a382a0_h
