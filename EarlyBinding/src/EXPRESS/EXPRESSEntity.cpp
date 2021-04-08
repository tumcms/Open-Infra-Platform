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

#include "EXPRESSEntity.h"


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

const size_t EXPRESSEntity::getId() const {
	return m_id;
}

void EXPRESSEntity::setId(size_t id) {
	m_id = id;
}

const std::string EXPRESSEntity::getStepParameter() const {
	return "#" + std::to_string(m_id);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

