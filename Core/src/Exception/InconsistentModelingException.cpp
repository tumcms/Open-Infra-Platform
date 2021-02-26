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

#include "InconsistentModelingException.h"

//! Constructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException() noexcept
	: item_(nullptr), message_(""), fullMessage_("")
{
	buildFull();
}

//! Copy Constructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
    const InconsistentModellingException& other) noexcept : item_(other.item_), message_(other.message_), fullMessage_(other.fullMessage_)
{
}

/*!
\brief Constructor with the unhandled entity.
\param[in] item The entity that is not handled.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
    const std::shared_ptr<oip::EXPRESSObject>& item, const std::string& message) noexcept
	: item_(item), message_(message), fullMessage_("")
{
	buildFull();
}

/*!
\brief Constructor with just the message.
\param[in] message Optional message to further specify the exception.
*/
OpenInfraPlatform::Core::Exception::InconsistentModellingException::InconsistentModellingException(
	const std::string& message) noexcept
	: item_(nullptr), message_(message), fullMessage_("")
{
	buildFull();
}

//! Destructor
OpenInfraPlatform::Core::Exception::InconsistentModellingException::~InconsistentModellingException() noexcept
{
}


/*!
\brief Builds the full error message.
*/
void OpenInfraPlatform::Core::Exception::InconsistentModellingException::buildFull()
{
	std::string s = "";
	if( item_ )
		s += "Modelling inconsistent at " + item_->getErrorLog() + (message_.empty() ? "." : ": ");
	if (!message_.empty())
		s += message_;
	fullMessage_ = s;
}

/*!
\brief Returns what is not supported.
\returns A message with the entity name and the \c message.
*/
const char* OpenInfraPlatform::Core::Exception::InconsistentModellingException::what() const
{
	return fullMessage_.c_str();
}
