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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSType_13ae9fe1_2b22_4812_b3bc_747f6d941fab_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSType_13ae9fe1_2b22_4812_b3bc_747f6d941fab_h

#include "OpenInfraPlatform/EarlyBinding/namespace.h"

#include "EXPRESSObject.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

class EXPRESSType : public EXPRESSObject {
public:
	virtual const std::string classname() const = 0;
	virtual const std::string getStepParameter() const = 0;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END
#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSType_13ae9fe1_2b22_4812_b3bc_747f6d941fab_h
