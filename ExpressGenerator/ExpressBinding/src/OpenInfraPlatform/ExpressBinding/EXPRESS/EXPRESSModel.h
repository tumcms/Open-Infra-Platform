/*
    This file is part of Expresso, a simple early binding generator for EXPRESS.
	Copyright (c) 2016 Technical University of Munich
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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSModel_795d0e6a_aa9f_4804_a9ff_67beadbd82c2_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSModel_795d0e6a_aa9f_4804_a9ff_67beadbd82c2_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include "EXPRESSEntity.h"

#include <string>
#include <map>
#include <memory>
#include <algorithm>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class EXPRESSModel {
public:
	EXPRESSModel(const std::string &schema) : schema(schema) { };

	~EXPRESSModel() {
		if (!entities.empty()) {
			std::for_each(entities.begin(), entities.end(), [](auto& elem) {
				elem.second = nullptr;
			});
			entities.clear();
		}
	};

	const std::string schema;
	std::map<size_t, std::shared_ptr<EXPRESSEntity>> entities;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSModel_795d0e6a_aa9f_4804_a9ff_67beadbd82c2_h
