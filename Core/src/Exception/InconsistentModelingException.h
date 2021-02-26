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
#ifndef INCONSISTENT_MODELING_EXCEPTION_H
#define INCONSISTENT_MODELING_EXCEPTION_H

#include <exception>
#include <string>

#include "namespace.h"

#include "EXPRESS\EXPRESSObject.h"
#include "EXPRESS\EXPRESSReference.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN

/*!
\brief Gets thrown if an there is a geometric error within an IFC entity.
*/
class InconsistentModellingException : public std::exception 
{
public:
	InconsistentModellingException() noexcept;
	InconsistentModellingException(const InconsistentModellingException& other) noexcept;
	virtual ~InconsistentModellingException() noexcept;

	InconsistentModellingException(const std::string& message) noexcept;
	InconsistentModellingException(const std::shared_ptr<oip::EXPRESSObject>& item, const std::string& message) noexcept;

    /*!
    \brief Constructor with the unhandled entity.
    \param[in] item The entity that is not handled.
	\param[in] message Optional message to further specify the exception.
	*/
    template <typename T>
	InconsistentModellingException(const oip::EXPRESSReference<typename T>& item, const std::string& message) noexcept
    {
        item_ = item.lock();
        message_ = message;
		buildFull();
    }

	void buildFull();
    const char* what() const override;

private:
    std::shared_ptr<oip::EXPRESSObject> item_;
	std::string message_;
	std::string fullMessage_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(InconsistentModellingException)

#endif
