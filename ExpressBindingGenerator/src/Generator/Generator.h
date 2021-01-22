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

#include "General/namespace.h"
#include "Meta/Schema.h"
#include <iostream>

#include <chrono>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

class Generator {
  public:
    Generator() {}
    virtual ~Generator() {}

    virtual void generate(const Schema &schema) = 0;

    virtual std::string getRandomGUID() const
    {        
        boost::mt19937 ran;
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        ran.seed((uint32_t) time( &now)); // one should likely seed in a better way
        boost::uuids::basic_random_generator<boost::mt19937> gen(&ran);
        return boost::uuids::to_string(gen());
    }
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_EXPRESSBINDINGGENERATOR_INTO_OIP_NAMESPACE(Generator)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Generator_9e4cf4b5_a3ce_40a9_a7f6_9849bd896016_h
