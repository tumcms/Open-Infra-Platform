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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <memory>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename T> class EXPRESSReference : public std::weak_ptr<T> {
public:
	std::string getStepParameter() {
		return this->lock()->getStepParameter();
	}
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSReference_c5a3045b_df30_4a77_aeea_3a16cde5c141_h
