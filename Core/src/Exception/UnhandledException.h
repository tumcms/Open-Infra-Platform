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

#pragma once
#ifndef UNHANDLED_REPRESENTATION_EXCEPTION_H
#define UNHANDLED_REPRESENTATION_EXCEPTION_H

#include <exception>
#include <string>

#include "namespace.h"

#include "EXPRESS\EXPRESSObject.h"
#include "EXPRESS\EXPRESSReference.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN

/*!
\brief Gets thrown if an IFC entity ot type is not supported by OIP.
*/
class UnhandledException : public std::exception {
public:
    //! Constructor
    UnhandledException() noexcept;
    //! Copy Constructor
    UnhandledException(const UnhandledException& other) noexcept;

    /*!
    \brief Constructor with the unhandled entity.
    \param[in] item The entity that is not handled.
    */
    UnhandledException(const std::shared_ptr<oip::EXPRESSObject>& item) noexcept;

    /*!
    \brief Constructor with the unhandled entity.
    \param[in] item The entity that is not handled.
    */
    template <typename T>
    UnhandledException(const oip::EXPRESSReference<typename T>& item) noexcept
    {
        item_ = item.lock();
    }

    //! Destructor
    ~UnhandledException() noexcept;

    /*!
    \brief Returns what is not supported.
    \returns A message with the entity name.
    */
    const char* what() const noexcept override;

    std::shared_ptr<oip::EXPRESSObject> item_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(UnhandledException)

#endif
