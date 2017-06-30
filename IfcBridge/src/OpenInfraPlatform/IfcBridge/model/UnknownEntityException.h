// Copied and modified code from "IfcPlusPlus" library.
// This library is available under the OpenSceneGraph Public License. Original copyright notice:

/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and / or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* OpenSceneGraph Public License for more details.
*/

/* This file has been automatically generated using the TUM Open Infra Platform
Early Binding EXPRESS Generator. Any changes to this file my be lost in the future. */

#pragma once

#include <exception>
#include <string>

namespace OpenInfraPlatform
{
    namespace IfcBridge
    {
        class UnknownEntityException : public std::exception
        {
        public:
            UnknownEntityException( std::string keyword )
            {
                m_keyword = keyword;
            }
            ~UnknownEntityException() throw() {}
            virtual const char* what() const throw()
            {
                return m_keyword.c_str();
            }
            std::string m_keyword;
        };
    } // end namespace IfcBridge
} // end namespace OpenInfraPlatform