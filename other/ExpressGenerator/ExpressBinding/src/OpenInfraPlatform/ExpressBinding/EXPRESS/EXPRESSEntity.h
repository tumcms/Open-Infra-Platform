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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

class EXPRESSEntity {
public:
	const size_t getId() const {
		return m_id;
	}

	const std::string getStepParameter() const {
		return "#" + std::to_string(m_id);
	}

private:
	size_t m_id;
};


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSEntity_5fd9c3bc_1d26_4fef_994f_229551a1c3f8_h
