/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS
    Generator, a simple early binding generator for EXPRESS.
    Copyright (c) 2021 Technical University of Munich
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

#include "Generator/GeneratorEcho.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

GeneratorEcho::GeneratorEcho() {
}

GeneratorEcho::~GeneratorEcho() {
}

void GeneratorEcho::generate(std::ostream& out, Schema& schema) {
	out << "SCHEMA " << schema.getName() << ";" << std::endl << std::endl;

	generateTypes(schema, out);

	generateEntities(schema, out);

	out << "END_SCHEMA;";
}

void GeneratorEcho::generateEntities(Schema& schema, std::ostream& out) {
	for (int i = 0; i < schema.getEntityCount(); i++) {
		auto entity = oip::Schema::getInstance().getEntityByIndex(i);

		out << "ENTITY " << entity.getName() << std::endl;

		if (entity.hasSupertype()) {
			out << " SUBTYPE OF(" << entity.getSupertype() << ");" << std::endl;
		}

		for (int j = 0; j < entity.getAttributeCount(); j++) {
			const EntityAttribute& att = entity.getAttribute(j);

			out << "\t" << att.getName() << " : ";

			if (att.isOptional()) {
				out << "OPTIONAL";
			}

			out << " " << att.type->toString();

			out << ";" << std::endl;
		}

		if (entity.getSubtypeCount() > 0) {
			out << "\tSUBTYPE OF (";

			for (int k = 0; k < entity.getSubtypeCount(); k++) {
				out << entity.getSubtypeByIndex(k);
			}

			out << ")";
		}

		out << "END_ENTITY;" << std::endl << std::endl;
	}
}

void GeneratorEcho::generateTypes(Schema& schema, std::ostream& out) {
	for (int i = 0; i < schema.getTypeCount(); i++) {
		auto type = schema.getTypeByIndex(i);

		out << "TYPE " << type.getName();
		out << " = ";

		if (type.getType() == eType::Binary) {
			out << "BINARY";
		} else if (type.getType() == eType::Boolean) {
			out << "BOOLEAN";
		} else if (type.getType() == eType::Real) {
			out << "REAL";
		} else if (type.getType() == eType::Integer) {
			out << "INTEGER";
		} else if (type.getType() == eType::Number) {
			out << "NUMBER";
		} else if (type.getType() == eType::Logical) {
			out << "LOGICAL";
		} else if (type.getType() == eType::String) {
			out << "STRING";
		} else if (type.getType() == eType::List) {
			out << "LIST [" << type.getContainerCardinalityMin() << ":" << type.getContainerCardinalityMax() << "] OF "
			    << oip::Schema::getInstance().getTypeByIndex(i).getContainerType();

		} else if (type.getType() == eType::Array) {
			out << "ARRAY [" << type.getContainerCardinalityMin() << ":" << type.getContainerCardinalityMax() << "] OF "
			    << oip::Schema::getInstance().getTypeByIndex(i).getContainerType();
		} else if (type.getType() == eType::Set) {
			out << "SET [" << type.getContainerCardinalityMin() << ":" << type.getContainerCardinalityMax() << "] OF "
			    << oip::Schema::getInstance().getTypeByIndex(i).getContainerType();
		} else if (type.getType() == eType::Enumeration) {
			out << "ENUMERATION OF " << std::endl << "\t(";

			for (int j = 0; j < type.getTypes().size(); j++) {
				out << type.getTypes()[j];

				if (j + 1 < type.getTypes().size())
					out << std::endl << "\t,";
			}

			out << ")";
		} else if (type.getType() == eType::Select) {
			out << "SELECT " << std::endl << "\t(";

			for (int j = 0; j < type.getTypes().size(); j++) {
				out << type.getTypes()[j];

				if (j + 1 < type.getTypes().size())
					out << std::endl << "\t,";
			}

			out << ")";
		} else {
			out << type.getUnderlyingTypeName();
		}

		out << ";" << std::endl << "END_TYPE;" << std::endl << std::endl;
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END
