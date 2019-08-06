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
#ifndef OpenInfraPlatform_ExpressBinding_Where_7F2C5498_08A3_4709_8C0D_5CECF364C50D_h
#define OpenInfraPlatform_ExpressBinding_Where_7F2C5498_08A3_4709_8C0D_5CECF364C50D_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename Type> class Where {
public:
	Where(const std::string &name, std::function<bool(const Type&)> impl) : name_(name), impl_(impl) {
	}

	~Where() {	}

	bool evaluate(const Type &obj) const {
		return impl_(obj);
	}

private:
	const std::string name_;
	const std::function<bool(const Type&)> impl_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END

#endif