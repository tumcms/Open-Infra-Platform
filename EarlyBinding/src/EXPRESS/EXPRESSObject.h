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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSObject_e357e824_9a04_46e0_8c91_43c528a6856f_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSObject_e357e824_9a04_46e0_8c91_43c528a6856f_h

#include "../EarlyBinding/src/namespace.h"

//#include "EXPRESSModel.h"

#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN

class EXPRESSObject {
public:
	virtual const std::string classname() const = 0;
	virtual const std::string getStepParameter() const = 0;

protected:
//	std::weak_ptr<EXPRESSModel> model;
};


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END
#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSIObject_e357e824_9a04_46e0_8c91_43c528a6856f_h
