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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_Generator_9e4cf4b5_a3ce_40a9_a7f6_9849bd896016_h
#define OpenInfraPlatform_ExpressBindingGenerator_Generator_9e4cf4b5_a3ce_40a9_a7f6_9849bd896016_h

#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
#include "OpenInfraPlatform/ExpressBindingGenerator/Meta/Schema.h"
#include <iostream>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class Generator {
  public:
    Generator() {}
    virtual ~Generator() {}

    virtual void generate(std::ostream &out, Schema &schema) = 0;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(Generator)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Generator_9e4cf4b5_a3ce_40a9_a7f6_9849bd896016_h
