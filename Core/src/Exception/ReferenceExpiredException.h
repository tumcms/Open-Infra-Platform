/*
Copyright (c) 2020 Technical University of Munich
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

#ifndef AD7D0227_733E_437B_80B4_1F4E948503BA
#define AD7D0227_733E_437B_80B4_1F4E948503BA

#pragma once

#include "namespace.h"

#include <exception>

#include <EXPRESS/EXPRESSReference.h>


OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN

class ReferenceExpiredException :
    public std::exception {
public:

    template <typename T>
    ReferenceExpiredException(const oip::EXPRESSReference<T>& item) noexcept
    {
        message_ = item.getErrorLog();
    }

    virtual char const* what() const override;

private:
    std::string message_;
    
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(ReferenceExpiredException);

#endif /* AD7D0227_733E_437B_80B4_1F4E948503BA */
