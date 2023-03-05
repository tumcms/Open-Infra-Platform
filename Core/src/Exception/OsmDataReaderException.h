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

#pragma once

#ifndef OSMDATAREADEREXCEPTION_H
#define OSMDATAREADEREXCEPTION_H

#include "namespace.h"

#include <exception>
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_BEGIN

class OsmReaderException : public std::exception
{
public:

	OsmReaderException(const std::string& msg) noexcept
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

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(OsmReaderException);

#endif // !OSMDATAREADEREXCEPTION_H
