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

#pragma once
#ifndef OpenInfraPlatform_ExpressBindingGenerator_GeneratorEcho_79d6d843_84b1_4c37_9051_6bdecceba109_h
#define OpenInfraPlatform_ExpressBindingGenerator_GeneratorEcho_79d6d843_84b1_4c37_9051_6bdecceba109_h

#include "Meta/Schema.h"
#include "Generator/Generator.h"
#include "General/namespace.h"
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class GeneratorEcho : public Generator {
  public:
    GeneratorEcho();
    virtual ~GeneratorEcho();

    void generate(std::ostream &out,
                  OpenInfraPlatform::ExpressBindingGenerator::Schema &schema);

  private:
    void generateEntities(OpenInfraPlatform::ExpressBindingGenerator::Schema &schema,
                          std::ostream &out);

    void generateTypes(OpenInfraPlatform::ExpressBindingGenerator::Schema &schema,
                       std::ostream &out);
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_EXPRESSBINDINGGENERATOR_INTO_OIP_NAMESPACE(GeneratorEcho)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_GeneratorEcho_79d6d843_84b1_4c37_9051_6bdecceba109_h
