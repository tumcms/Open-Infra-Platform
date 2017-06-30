/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Benchmark.h"

#include <iostream>

OpenInfraPlatform::Benchmark::Benchmark()
{

}

OpenInfraPlatform::Benchmark::~Benchmark()
{

}

void OpenInfraPlatform::Benchmark::print()
{
	//pl_.print(std::cout);
}

void OpenInfraPlatform::Benchmark::finishStartup()
{
	//pl_.stop("Startup");
}

void OpenInfraPlatform::Benchmark::beginStartup()
{
	//pl_.start("Startup");
}

OpenInfraPlatform::Benchmark& OpenInfraPlatform::Benchmark::getInstance()
{
	static Benchmark instance;
	return instance;
}

void OpenInfraPlatform::Benchmark::start(const char* marker)
{
	//pl_.start(marker);
}

void OpenInfraPlatform::Benchmark::stop(const char* marker)
{
	//pl_.stop(marker);
}




