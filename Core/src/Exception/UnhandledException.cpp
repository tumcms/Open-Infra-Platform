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

#include "UnhandledException.h"

//! Constructor
OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException() noexcept
	: item_(nullptr), message_("")
{
}

//! Copy Constructor
OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException(
    const UnhandledException& other) noexcept : item_(other.item_), message_(other.message_)
{
}

/*!
\brief Constructor with the unhandled entity.
\param[in] item The entity that is not handled.
*/
OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException(
    const std::shared_ptr<oip::EXPRESSObject>& item) noexcept
{
    item_ = item;
	message_ = item_->getErrorLog() + ": IFC Entity not supported.";
}

/*!
\brief Constructor with the arbitrary string.
\param[in] message The message.
*/
OpenInfraPlatform::Core::Exception::UnhandledException::UnhandledException(
	const std::string& message) noexcept
{
	message_ = message;
}

/*!
\brief Returns what is not supported.
\returns A message with the entity name.
*/
const char* OpenInfraPlatform::Core::Exception::UnhandledException::what() const noexcept
{
    return message_.c_str();
}
