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


#include "EXPRESSModel.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

EXPRESSModel::EXPRESSModel(const std::string &schema) 
: schema(schema) { };

EXPRESSModel::~EXPRESSModel() {
	if (!entities.empty()) {
		std::for_each(entities.begin(), entities.end(), [](auto& elem) {
			elem.second = nullptr;
		});
		entities.clear();
	}
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

