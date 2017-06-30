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

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		template <
			class IfcEntityTypesT
		>
		class UnhandledRepresentationException : public std::exception
		{
		public:
			UnhandledRepresentationException()
			{
			}
			UnhandledRepresentationException(std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem> item)
			{
				m_item = item;
			}

			~UnhandledRepresentationException() throw()
			{
			}

			const char* what() const throw()
			{
				return "Unhandled IFC Representation";
			}

			std::shared_ptr<typename IfcEntityTypesT::IfcRepresentationItem> m_item;
			//std::shared_ptr<typename IfcEntityTypesT::IfcAbstractSelect> m_select;
		};

		#ifdef _DEBUG

		class DebugBreakException : public std::exception
		{
		public:
			DebugBreakException( std::string reason ) { m_reason = reason; }
			~DebugBreakException() throw() {}
			virtual const char* what() const throw() { return m_reason.c_str(); }
			std::string m_reason;
		};

		#endif
	}
}

#endif

