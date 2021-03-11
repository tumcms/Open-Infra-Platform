/*
Copyright (c) 2021 Technical University of Munich
Chair of Computational Modeling and Simulation.

TUM Open Infra Platform is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Version 3
as published by the Free Software Foundation.

TUM Open Infra Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AD7D0227_733E_437B_80C7_1F4E948503BC
#define AD7D0227_733E_437B_80C7_1F4E948503BC

#pragma once

#include "namespace.h"

#include <exception>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN

class IfcPeekReaderException :
    public std::exception {
public:

    IfcPeekReaderException(const std::string& msg) noexcept
    {
        message_ = msg;
    }

    virtual char const* what() const override
    {
        return message_.data();
    }

private:
    std::string message_;
    
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(IfcPeekReaderException);

#endif /* AD7D0227_733E_437B_80C7_1F4E948503BC */
