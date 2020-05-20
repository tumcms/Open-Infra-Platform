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

#include "InconsistentModelingException.h"

//! Constructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException() noexcept
{
}

//! Copy Constructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
    const InconsistentModellingException& other) noexcept : item_(other.item_), message_(other.message_)
{
}

/*!
\brief Constructor with the unhandled entity.
\param[in] item The entity that is not handled.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
    const std::shared_ptr<oip::EXPRESSObject>& item, const std::string& message) noexcept
{
    item_ = item;
    message_ = message;
}

/*!
\brief Constructor with just the message.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
	const std::string& message) noexcept
{
	item_ = nullptr;
	message_ = message;
}

//! Destructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::~InconsistentModellingException() noexcept
{
}


/*!
\brief Returns what is not supported.
\returns A message with the entity name and the \c message.
*/
const char* OpenInfraPlatform::Core::Exception::InconsistentModellingException::what() const
{
	std::string s = "";
	if( item_ )
		s += "Modelling inconsistent at " + item_->getErrorLog() + (message_.empty() ? "." : ": ");
	if (!message_.empty())
		s += message_;
    return s.c_str();
}
