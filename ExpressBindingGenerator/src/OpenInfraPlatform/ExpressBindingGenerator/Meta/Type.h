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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_Type_26f5189f_bcf1_4fc1_96c7_2c4f5f03378b_h
#define OpenInfraPlatform_ExpressBindingGenerator_Type_26f5189f_bcf1_4fc1_96c7_2c4f5f03378b_h

#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
#include <string>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

enum class eType {
	Unknown,
	Real,
	Boolean,
	Binary,
	Integer,
	Number,
	Logical,
	String,
	Array,
	List,
	Set,
	Enumeration,
	Select
};

class Type {
public:
	Type();

	std::string getName() const;
	void setName(std::string val);

	eType getType() const;
	void setType(eType val);

	std::string getUnderlyingTypeName() const;
	void setUnderlyingTypeName(const std::string& value);

	// Container
	std::string getContainerType() const;
	void setContainerType(const std::string& value);

	int getContainerCardinalityMin() const;
	void setContainerCardinalityMin(int val);
		
	int getContainerCardinalityMax() const;
	void setContainerCardinalityMax(int val);
	
	// Enumeration or SelectType
	void setTypes(const std::vector<std::string>& types);

	int getTypeCount() const;

	std::vector<std::string> getTypes() const;

	std::string Type::getType(const int index) const;

	//! check if this type is a simple type (Real)
	bool isSimpleType() const;

	bool isEnumeration() const;

	bool isArray() const;

	bool isList() const;

	bool isSet() const;

	bool isSelectType() const;

	bool isDerivedType() const;

	std::string getContainerTypeName() const;

	std::string getContainerTypeIdentifier() const;

	bool isContainerType() const;
		
private:
	// Simple types
	std::string name_;
	eType	type_;

	// User defined types
	std::string underlyingTypeName_;
			
	// Container (list, array) types
	std::string containerType_;
	int	containerCardinalityMin_;
	int	containerCardinalityMax_;

	// Enums
	std::vector<std::string> types_;	
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(eType)
EMBED_INTO_OIP_NAMESPACE(Type)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Type_26f5189f_bcf1_4fc1_96c7_2c4f5f03378b_h
