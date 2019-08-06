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
#ifndef OpenInfraPlatform_ExpressBinding_EXPRESSSelect_10255db4_8b09_413b_9c43_ea39f1d63ced_h
#define OpenInfraPlatform_ExpressBinding_EXPRESSSelect_10255db4_8b09_413b_9c43_ea39f1d63ced_h

#include "OpenInfraPlatform/ExpressBinding/namespace.h"

#include <boost/variant.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_BEGIN

template <typename ...Args> class EXPRESSSelect : public boost::variant<Args...> {
	using base_type = boost::variant<Args...>;
public:
	using base_type::base_type;
	using base_type::operator=;
};

 //template <typename ...Args> using EXPRESSSelect = boost::variant<Args...>;

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDING_END
#endif // end define OpenInfraPlatform_ExpressBinding_EXPRESSSelect_10255db4_8b09_413b_9c43_ea39f1d63ced_h
