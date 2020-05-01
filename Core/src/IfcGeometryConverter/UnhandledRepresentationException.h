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

#include "CarveHeaders.h"

#include "EXPRESS/EXPRESSObject.h"

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {

			/*!
			\brief Gets thrown if an IFC entity ot type is not supported by OIP.
			*/
			class UnhandledException : public std::exception {
			public:
				//! Constructor
				UnhandledException() noexcept
				{
				}
				//! Copy Constructor
				UnhandledException(const UnhandledException& other) noexcept
					: item_(other.item_)
				{
				}
				/*!
				\brief Constructor with the unhandled entity.				
				\param[in] item The entity that is not handled.
				*/
				UnhandledException(const std::shared_ptr<oip::EXPRESSObject>& item) noexcept
				{
					item_ = item;
				}
				//! Destructor
				~UnhandledException() throw()
				{
				}
				
				/*!
				\brief Returns what is not supported.
				\returns A message with the entity name.
				*/
				const char* what() const throw()
				{
					std::string s = item_->getErrorLog() + ": Unhandled IFC Representation";
					return s.c_str();
				}

				std::shared_ptr<oip::EXPRESSObject> item_;
			};

//#ifdef _DEBUG
//
//			class DebugBreakException : public std::exception {
//			public:
//				DebugBreakException(std::string reason) { reason = reason; }
//				~DebugBreakException() throw() {}
//				virtual const char* what() const throw() { return reason.c_str(); }
//				std::string reason;
//			};
//
//#endif
		}
	}
}

#endif

