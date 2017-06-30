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

// visual studio
#pragma once
// unix
#ifndef RECURSIVECALLEXCEPTION_H
#define RECURSIVECALLEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

#include "CarveHeaders.h"

//#ifdef IFC4_READER
//#include "OpenInfraPlatform/Ifc2x3/model/Ifc4bject.h"
//
//using namespace BlueFramework::Ifc4;
//
//typedef Ifc4Entity IfcEntity;
//
//#endif
//
//#ifdef IFC2X3_READER
//#include "OpenInfraPlatform/Ifc2x3/model/Ifc2x3Object.h"
//
//using namespace OpenInfraPlatform::Ifc2x3;
//
//typedef Ifc2x3Entity IfcEntity;
//
//#endif

namespace BlueIfcViewer
{
	namespace IfcDataManagement
	{
		template <
			class IfcEntityT
		>
		class RecursiveCallException : public std::exception
		{
		public:
			RecursiveCallException(std::shared_ptr<IfcEntityT> item)
			{
				m_entity = item;
			}

			~RecursiveCallException() throw()
			{
			}

			const char* what() const throw()
			{
				std::stringstream strs;
				strs << "Ifc Entity with Id " << m_entity->getId() 
					<< " has been applied recursively.";
				return strs.str().c_str();
			}

			std::shared_ptr<IfcEntityT> m_entity;
		};

	}
}

#endif
