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

#include "IfcTunnelException.h"
#include "IfcTunnelObject.h"

namespace OpenInfraPlatform
{
    namespace IfcTunnel
    {
        IfcTunnelEntity::IfcTunnelEntity() : m_id(-1)
        {
        }
        IfcTunnelEntity::IfcTunnelEntity( int id ) : m_id(id)
        {
        }

        IfcTunnelEntity::~IfcTunnelEntity()
        {
        }
        void IfcTunnelEntity::setId( int id )
        {
            m_id = id;
        }

        void IfcTunnelEntity::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcTunnelEntity> >& map )
        {
            throw IfcTunnelException("IfcTunnelEntity::readStepData(), this method should be overwritten");
        }
        void IfcTunnelEntity::getStepLine( std::stringstream& stream ) const
        {
            throw IfcTunnelException("IfcTunnelEntity::getStepLine(), this method should be overwritten");
        }

        void IfcTunnelEntity::getStepParameter( std::stringstream& stream, bool ) const
        {
            throw IfcTunnelException("IfcTunnelEntity::getStepParameter(), this method should be overwritten");
        }

        void IfcTunnelEntity::setInverseCounterparts( shared_ptr<IfcTunnelEntity> ptr_self )
        {
            throw IfcTunnelException("IfcTunnelEntity::setInverseCounterparts(), this method should be overwritten");
        }

        void IfcTunnelEntity::unlinkSelf()
        {
            throw IfcTunnelException("IfcTunnelEntity::unlinkSelf(), this method should be overwritten");
        }
    } // end namespace IfcTunnel
} // end namespace OpenInfraPlatform