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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_h
#define OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_h

#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
#include <stack>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

template<typename T>
void clear(std::stack<T>& stack) {
	while (!stack.empty()) {
		stack.pop();
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_h
