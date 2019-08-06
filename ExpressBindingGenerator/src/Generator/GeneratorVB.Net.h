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

#include "Generator/Generator.h"
#include "Meta/Schema.h"
#include "General/namespace.h"
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class GeneratorVBNet : public Generator {
public:
	GeneratorVBNet() {
	}
	virtual ~GeneratorVBNet() {
	}

	void generate(std::ostream &out, OpenInfraPlatform::ExpressBindingGenerator::Schema &schema) {
		for (int i = 0; i < schema.getEntityCount(); i++) {
			auto &entity = schema.getEntityByIndex(i);

			std::stringstream ss;
			ss << earlyBindingDestination << "\\" << entity.getName() << ".vb";

			std::ofstream ofs(ss.str(), std::ofstream::out);

			ofs << "Class " << entity.getName() << std::endl;

			ofs << "End Class" << std::endl;
		}
	}

private:
	std::string earlyBindingDestination = "E:\\dev\\EarlyBindingVBNet_IFC4x1_Add1";
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(GeneratorVBNet)
