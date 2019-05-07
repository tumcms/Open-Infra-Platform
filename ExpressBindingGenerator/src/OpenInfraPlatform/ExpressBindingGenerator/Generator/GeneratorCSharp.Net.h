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

#include "OpenInfraPlatform/ExpressBindingGenerator/Generator/Generator.h"
#include "OpenInfraPlatform/ExpressBindingGenerator/Meta/Schema.h"
#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
#include <iostream>
#include <map>
#include <cassert>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

std::string toUpper(const std::string &inputString);

class GeneratorCSharpNet : public Generator {
public:
	GeneratorCSharpNet() {
	}
	virtual ~GeneratorCSharpNet() {
	}

	void generate(std::ostream &out, OpenInfraPlatform::ExpressBindingGenerator::Schema &schema) {


		for (int i = 0; i < schema.getTypeCount(); i++) {
			auto &type = schema.getTypeByIndex(i);
			
			std::stringstream ssFilename;
			ssFilename << earlyBindingDestination << "\\" << type.getName() << ".cs";

			std::ofstream ofs(ssFilename.str(), std::ofstream::out);

			ofs << "class " << type.getName() << std::endl;

			ofs << "{" << std::endl;

		
			ofs << "    void getStepParameter(StreamWriter stream, bool is_select_type)" << std::endl;
			ofs << "    {" << std::endl;
			ofs << "	    if (is_select_type) { stream << \"" << toUpper(type.getName()) << "(\"; }" << std::endl;
			ofs << "    }" << std::endl;

			// attributes
			if (type.isSimpleType()) {
				ofs << "\t" << "public " << convertSimpleTypeToCPPType(schema, type.getUnderlyingTypeName()) << " m_value;" << std::endl;
			}

			ofs << "}" << std::endl;
		}

		for (int i = 0; i < schema.getEntityCount(); i++) {
			auto &entity = schema.getEntityByIndex(i);

			std::stringstream ssFilename;
			ssFilename << earlyBindingDestination << "\\" << entity.getName() << ".cs";

			std::ofstream ofs(ssFilename.str(), std::ofstream::out);

			ofs << "class " << entity.getName() << std::endl;

			ofs << "{" << std::endl;
			
			for (int i = 0; i < entity.getAttributeCount(); i++) {
				const EntityAttribute &att = entity.getAttribute(i);

				if (att.getParameterType() == eEntityAttributeParameterType::TypeNamed) {
					

					ofs << ident << "public " <<  att.type->toString() << " m_" << att.getName() << ";" << std::endl;
				}
				else if (att.getParameterType() == eEntityAttributeParameterType::eGeneralizedType) {
					auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(att.type);

					if (p->containerType == eEntityAttributeContainerType::List) {
						ofs << "\t"
							<< "\t"
							<< "\t"
							<< "List<";

						auto iterator = p->elementType;

						while (iterator->getType() == eEntityAttributeParameterType::eGeneralizedType) {
							auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
							ofs << "List<";

							iterator = p->elementType;
						}

						if (iterator->getType() == eEntityAttributeParameterType::TypeNamed) {
							out << iterator->toString();
						}

						iterator = p->elementType;

						while (iterator->getType() == eEntityAttributeParameterType::eGeneralizedType) {
							auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
							ofs << ">";

							iterator = p->elementType;
						}

						ofs << "> "
							<< " m_" << att.getName() << ";" << std::endl;
					}
					else if (p->containerType == eEntityAttributeContainerType::Set) {
						ofs << "\t"
							<< "\t"
							<< "\t"
							<< "std::vector<";

						if (p->elementType->getType() == eEntityAttributeParameterType::TypeNamed) {
							out << p->elementType->toString();
						}

						ofs << "> "
							<< " m_" << att.getName() << ";" << std::endl;
					}
					else if (p->containerType == eEntityAttributeContainerType::Array) {
						ofs << "\t"
							<< "\t"
							<< "\t"
							<< "std::vector<";

						if (p->elementType->getType() == eEntityAttributeParameterType::TypeNamed) {
							ofs << p->elementType->toString();
						}

						ofs << "> "
							<< " m_" << att.getName() << ";" << std::endl;
					}
					else {
						std::cout << "\t"
							<< "\t"
							<< "\t" << att.type->toString() << " m_" << att.getName() << ";" << std::endl;
						ofs << "\t"
							<< "\t"
							<< "\t" << att.type->toString() << " m_" << att.getName() << ";" << std::endl;
					}

				}
				else {
					ofs << "\t"
						<< "\t"
						<< "\t" << convertSimpleTypeToCPPType(schema, att.type->toString()) << " m_" << att.getName() << ";" << std::endl;
				}
			}







			ofs << "}" << std::endl;

			ofs.close();
		}
	}

private:
	std::string convertSimpleTypeToCPPType(Schema &schema, std::string simpleType) const {
		std::map<std::string, std::string> simpleTypeMapping;
		simpleTypeMapping.insert(std::make_pair("INTEGER", "int"));
		simpleTypeMapping.insert(std::make_pair("REAL", "double"));
		simpleTypeMapping.insert(std::make_pair("NUMBER", "int"));
		simpleTypeMapping.insert(std::make_pair("STRING", "std::string"));
		simpleTypeMapping.insert(std::make_pair("BOOLEAN", "bool"));
		simpleTypeMapping.insert(std::make_pair("LOGICAL", "bool"));
		simpleTypeMapping.insert(std::make_pair("BINARY", "const char*"));
		//simpleTypeMapping.insert(std::make_pair("IfcPositiveInteger", "int"));

		if (!simpleTypeMapping.count(simpleType))
		{
			std::cout << simpleType << std::endl;

			Type underlyingType = schema.getTypeByName(simpleType);
			while (!underlyingType.isSimpleType())
			{
				underlyingType = schema.getUnderlyingType(underlyingType.getName());
			}

			return convertSimpleTypeToCPPType(schema, underlyingType.getUnderlyingTypeName());
		}

		assert(simpleTypeMapping.count(simpleType));

		return simpleTypeMapping[simpleType];
	}


private:
	
	std::string ident = "    ";
	std::string earlyBindingDestination = "C:\\dev\\EarlyBindingCSharp";
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(GeneratorCSharpNet)
