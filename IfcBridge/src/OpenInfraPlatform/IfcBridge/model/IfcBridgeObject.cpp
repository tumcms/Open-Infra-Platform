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

#include "IfcBridgeException.h"
#include "IfcBridgeObject.h"

namespace OpenInfraPlatform
{
    namespace IfcBridge
    {
        IfcBridgeEntity::IfcBridgeEntity() : m_id(-1)
        {
        }
        IfcBridgeEntity::IfcBridgeEntity( int id ) : m_id(id)
        {
        }

        IfcBridgeEntity::~IfcBridgeEntity()
        {
        }
        void IfcBridgeEntity::setId( int id )
        {
            m_id = id;
        }

        void IfcBridgeEntity::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcBridgeEntity> >& map )
        {
            throw IfcBridgeException("IfcBridgeEntity::readStepData(), this method should be overwritten");
        }
        void IfcBridgeEntity::getStepLine( std::stringstream& stream ) const
        {
            throw IfcBridgeException("IfcBridgeEntity::getStepLine(), this method should be overwritten");
        }

        void IfcBridgeEntity::getStepParameter( std::stringstream& stream, bool ) const
        {
            throw IfcBridgeException("IfcBridgeEntity::getStepParameter(), this method should be overwritten");
        }

        void IfcBridgeEntity::setInverseCounterparts( shared_ptr<IfcBridgeEntity> ptr_self )
        {
            throw IfcBridgeException("IfcBridgeEntity::setInverseCounterparts(), this method should be overwritten");
        }

        void IfcBridgeEntity::unlinkSelf()
        {
            throw IfcBridgeException("IfcBridgeEntity::unlinkSelf(), this method should be overwritten");
        }
    } // end namespace IfcBridge
} // end namespace OpenInfraPlatform