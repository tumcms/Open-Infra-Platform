/*
    This file is part of Expresso, a simple early binding generator for EXPRESS.
	Copyright (c) 2021 Technical University of Munich
	Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#ifndef OpenInfraPlatform_ExpressBindingGenerator_IRestrictible_134a78bc_1aca_41b3_99f8_d983d8d9e1c5_h
#define OpenInfraPlatform_ExpressBindingGenerator_IRestrictible_134a78bc_1aca_41b3_99f8_d983d8d9e1c5_h

#include "General/namespace.h"
#include "Meta/Where.h"

#include <vector>
#include <functional>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

template <typename Type> class IRestrictible {
public:
	bool check() const {
		bool result = true;
		for (auto rule : restrictions_) {
			result &= rule.evaluate(*((Type*)this));
		}
		return result;
	}

	void addWhereClause(const std::string &name, const std::function<bool(const Type&)> &impl) {
		restrictions_.push_back(Where<Type>(name, impl));
	}

private:
	std::vector<Where<Type>> restrictions_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_Restrictible_134a78bc_1aca_41b3_99f8_d983d8d9e1c5_h
