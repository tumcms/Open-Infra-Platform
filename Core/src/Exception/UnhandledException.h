// Copied and modified code from "IfcPlusPlus".
// This code is available under the OSGPL license. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

// More details can be found in README.md file in the root directory.

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
class UnhandledException : public std::exception
{
public:
	//! Constructor
	UnhandledException() noexcept
	{
	}
	//! Copy Constructor
	UnhandledException(const UnhandledException &other) noexcept
		: item_(other.item_)
	{
	}
	/*!
	\brief Constructor with the unhandled entity.				
	\param[in] item The entity that is not handled.
	*/
	UnhandledException(const std::shared_ptr<oip::EXPRESSObject> &item) noexcept
	{
		item_ = item;
	}
	/*!
				\brief Constructor with the unhandled entity.
				\param[in] item The entity that is not handled.
				*/
	template <typename T>
	UnhandledException(const oip::EXPRESSReference<typename T> &item) noexcept
	{
		item_ = item.lock();
	}
	//! Destructor
	~UnhandledException() throw()
	{
	}

	/*!
				\brief Returns what is not supported.
				\returns A message with the entity name.
				*/
	const char *what() const throw()
	{
		std::string s = item_->getErrorLog() + ": IFC Entity not supported.";
		return s.c_str();
	}

	std::shared_ptr<oip::EXPRESSObject> item_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_EXCEPTION_END

EMBED_CORE_EXCEPTION_INTO_OIP_NAMESPACE(UnhandledException)

#endif
