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

#include "Ifc2x3Exception.h"
#include "Ifc2x3Object.h"

namespace OpenInfraPlatform
{
    namespace Ifc2x3
    {
        Ifc2x3Entity::Ifc2x3Entity() : m_id(-1)
        {
        }
        Ifc2x3Entity::Ifc2x3Entity( int id ) : m_id(id)
        {
        }

        Ifc2x3Entity::~Ifc2x3Entity()
        {
        }
        void Ifc2x3Entity::setId( int id )
        {
            m_id = id;
        }

        void Ifc2x3Entity::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<Ifc2x3Entity> >& map )
        {
            throw Ifc2x3Exception("Ifc2x3Entity::readStepData(), this method should be overwritten");
        }
        void Ifc2x3Entity::getStepLine( std::stringstream& stream ) const
        {
            throw Ifc2x3Exception("Ifc2x3Entity::getStepLine(), this method should be overwritten");
        }

        void Ifc2x3Entity::getStepParameter( std::stringstream& stream, bool ) const
        {
            throw Ifc2x3Exception("Ifc2x3Entity::getStepParameter(), this method should be overwritten");
        }

        void Ifc2x3Entity::setInverseCounterparts( shared_ptr<Ifc2x3Entity> ptr_self )
        {
            throw Ifc2x3Exception("Ifc2x3Entity::setInverseCounterparts(), this method should be overwritten");
        }

        void Ifc2x3Entity::unlinkSelf()
        {
            throw Ifc2x3Exception("Ifc2x3Entity::unlinkSelf(), this method should be overwritten");
        }
    } // end namespace Ifc2x3
} // end namespace OpenInfraPlatform