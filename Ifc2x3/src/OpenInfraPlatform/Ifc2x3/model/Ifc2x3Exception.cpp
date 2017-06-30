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

#include "model/Ifc2x3Exception.h"

namespace OpenInfraPlatform
{
    namespace Ifc2x3
    {
        Ifc2x3Exception::Ifc2x3Exception( std::string reason )
        {
            m_reason = reason;
        }

        Ifc2x3Exception::Ifc2x3Exception( std::string reason, const char* function_name )
        {
            m_reason.append( function_name );
            m_reason.append( ": " );
            m_reason.append( reason );
        }

        Ifc2x3Exception::~Ifc2x3Exception() throw()
        {

        }

        const char* Ifc2x3Exception::what() const throw()
        {
            return m_reason.c_str();
        }
    } // end namespace Ifc2x3
} // end namespace OpenInfraPlatform