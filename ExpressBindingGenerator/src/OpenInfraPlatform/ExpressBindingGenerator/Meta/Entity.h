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

#include "OpenInfraPlatform/ExpressBindingGenerator/Meta/EntityAttribute.h"
#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
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

    std::string getName() const;

    void setName(const std::string &value);

    //---------------------------------------------------------------
    // Supertypes
    //---------------------------------------------------------------

    void setParentEntity(const std::string &value);

    bool hasSupertype() const;

    std::string getSupertype() const;

    //---------------------------------------------------------------
    // Subtypes
    //---------------------------------------------------------------

    int getSubtypeCount() const;

    void addSubtype(const std::string &subtype);

    std::string getSubtypeByIndex(const int index) const;

    //---------------------------------------------------------------
    // Attributes
    //---------------------------------------------------------------

    int getAttributeCount() const;

    void addAttribute(const EntityAttribute &att);

    const EntityAttribute &getAttribute(const int index) const;

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

	int getQualifiedAttributeCount() const {
		return static_cast<int>(qualifiedAttributes_.size());
	}

	qualifiedAttribute getQualifiedAttributeByIndex(const int index) const {
		return qualifiedAttributes_[index];
	}

	bool hasQualifiedAttribute(const std::string& attributeQualifier) const {
		for (int i = 0; i < qualifiedAttributes_.size(); ++i)
		{
			if (qualifiedAttributes_[i].attributeQualifier == attributeQualifier)
			{
				return true;
			}
		}

		return false;
	}


  private:
    std::string parentEntity_;
    std::string name_;
    std::vector<std::string> subtypes_;
    std::vector<EntityAttribute> attributes_;
	std::vector<qualifiedAttribute> qualifiedAttributes_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(Entity)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Entity_ae022d70_8143_4f95_aec7_d51148a382a0_h
