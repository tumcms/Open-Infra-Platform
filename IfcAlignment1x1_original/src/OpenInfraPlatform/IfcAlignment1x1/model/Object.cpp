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

#include "Exception.h"
#include "Object.h"

namespace OpenInfraPlatform
{
    namespace IfcAlignment1x1
    {
        IfcAlignment1x1Entity::IfcAlignment1x1Entity() : m_id(-1)
        {
        }
        IfcAlignment1x1Entity::IfcAlignment1x1Entity( int id ) : m_id(id)
        {
        }

        IfcAlignment1x1Entity::~IfcAlignment1x1Entity()
        {
        }
        void IfcAlignment1x1Entity::setId( int id )
        {
            m_id = id;
        }

        void IfcAlignment1x1Entity::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcAlignment1x1Entity> >& map )
        {
            throw IfcAlignment1x1Exception("IfcAlignment1x1Entity::readStepData(), this method should be overwritten");
        }
        void IfcAlignment1x1Entity::getStepLine( std::stringstream& stream ) const
        {
            throw IfcAlignment1x1Exception("IfcAlignment1x1Entity::getStepLine(), this method should be overwritten");
        }

        void IfcAlignment1x1Entity::getStepParameter( std::stringstream& stream, bool ) const
        {
            throw IfcAlignment1x1Exception("IfcAlignment1x1Entity::getStepParameter(), this method should be overwritten");
        }

        void IfcAlignment1x1Entity::setInverseCounterparts( shared_ptr<IfcAlignment1x1Entity> ptr_self )
        {
            throw IfcAlignment1x1Exception("IfcAlignment1x1Entity::setInverseCounterparts(), this method should be overwritten");
        }

        void IfcAlignment1x1Entity::unlinkSelf()
        {
            throw IfcAlignment1x1Exception("IfcAlignment1x1Entity::unlinkSelf(), this method should be overwritten");
        }
    } // end namespace IfcAlignment1x1
} // end namespace OpenInfraPlatform
