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
#ifndef OpenInfraPlatform_ExpressBindingGenerator_memory_9d568a15_99c8_4646_8ceb_4cfa042569f1_h
#define OpenInfraPlatform_ExpressBindingGenerator_memory_9d568a15_99c8_4646_8ceb_4cfa042569f1_h

#include "OpenInfraPlatform/ExpressBindingGenerator/namespace.h"
#include <memory>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

template<typename T>
using ReferenceCounted = std::shared_ptr<T>;

template <typename T, typename... Args>
ReferenceCounted<T> makeReferenceCounted(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

EMBED_INTO_OIP_NAMESPACE(ReferenceCounted)

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_memory_9d568a15_99c8_4646_8ceb_4cfa042569f1_h
