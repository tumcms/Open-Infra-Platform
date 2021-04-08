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

#include "InconsistentGeometryException.h"

//! Constructor
OpenInfraPlatform::Core::Exception::InconsistentGeometryException::InconsistentGeometryException() noexcept
{
}

//! Copy Constructor
OpenInfraPlatform::Core::Exception::InconsistentGeometryException::InconsistentGeometryException(
    const InconsistentGeometryException& other) noexcept : item_(other.item_), message_(other.message_)
{
	init();
}

/*!
\brief Constructor with the unhandled entity.
\param[in] item The entity that is not handled.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentGeometryException::InconsistentGeometryException(
    const std::shared_ptr<oip::EXPRESSObject>& item, const std::string& message) noexcept
{
    item_ = item;
    message_ = message;
	init();
}

/*!
\brief Constructor with just the message.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentGeometryException::InconsistentGeometryException(
	const std::string& message) noexcept
{
	item_ = nullptr;
	message_ = message;
	init();
}

//! Destructor
OpenInfraPlatform::Core::Exception::InconsistentGeometryException::~InconsistentGeometryException() noexcept
{
}


/*!
\brief Returns what is not supported.
\returns A message with the entity name and the \c message.
*/
const char* OpenInfraPlatform::Core::Exception::InconsistentGeometryException::what() const
{
    return what_.c_str();
}

/*!
\brief Initialises the return message (member \c what_)
*/
void OpenInfraPlatform::Core::Exception::InconsistentGeometryException::init() noexcept
{
	what_ = "";
	if (item_)
		what_ += "Geometry is inconsistent at " + item_->getErrorLog() + (message_.empty() ? "." : ": ");
	if (!message_.empty())
		what_ += message_;
	if (what_.back() != '.'
		&& what_.back() != '!')
		what_ += ".";
}
