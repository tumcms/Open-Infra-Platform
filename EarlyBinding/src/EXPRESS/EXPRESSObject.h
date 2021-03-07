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
#ifndef OpenInfraPlatform_EarlyBinding_EXPRESSObject_e357e824_9a04_46e0_8c91_43c528a6856f_h
#define OpenInfraPlatform_EarlyBinding_EXPRESSObject_e357e824_9a04_46e0_8c91_43c528a6856f_h

#include "../namespace.h"
#include "../earlybinding_api.h"

#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_BEGIN


OIP_EARLYBINDING_EXTERN
class
OIP_EARLYBINDING_API_EXPRESS
EXPRESSObject 
{
public:
	virtual const std::string classname() const = 0;
	virtual const std::string getStepParameter() const = 0;
	
	/*!
	\brief Simple access for error logging strings.

	\returns <classname> (<stepParameter>)
	*/
	virtual const std::string getErrorLog() const ;
};


OIP_NAMESPACE_OPENINFRAPLATFORM_EARLYBINDING_END

EMBED_EARLYBINDING_INTO_OIP_NAMESPACE(EXPRESSObject);

#endif // end define OpenInfraPlatform_EarlyBinding_EXPRESSIObject_e357e824_9a04_46e0_8c91_43c528a6856f_h
