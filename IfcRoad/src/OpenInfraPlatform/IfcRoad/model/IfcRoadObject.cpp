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

#include "IfcRoadException.h"
#include "IfcRoadObject.h"

namespace OpenInfraPlatform
{
    namespace IfcRoad
    {
        IfcRoadEntity::IfcRoadEntity() : m_id(-1)
        {
        }
        IfcRoadEntity::IfcRoadEntity( int id ) : m_id(id)
        {
        }

        IfcRoadEntity::~IfcRoadEntity()
        {
        }
        void IfcRoadEntity::setId( int id )
        {
            m_id = id;
        }

        void IfcRoadEntity::readStepData( std::vector<std::string>& args, const std::map<int,shared_ptr<IfcRoadEntity> >& map )
        {
            throw IfcRoadException("IfcAlignmentEntity::readStepData(), this method should be overwritten");
        }
        void IfcRoadEntity::getStepLine( std::stringstream& stream ) const
        {
            throw IfcRoadException("IfcAlignmentEntity::getStepLine(), this method should be overwritten");
        }

        void IfcRoadEntity::getStepParameter( std::stringstream& stream, bool ) const
        {
            throw IfcRoadException("IfcAlignmentEntity::getStepParameter(), this method should be overwritten");
        }

        void IfcRoadEntity::setInverseCounterparts( shared_ptr<IfcRoadEntity> ptr_self )
        {
            throw IfcRoadException("IfcAlignmentEntity::setInverseCounterparts(), this method should be overwritten");
        }

        void IfcRoadEntity::unlinkSelf()
        {
            throw IfcRoadException("IfcAlignmentEntity::unlinkSelf(), this method should be overwritten");
        }
    } // end namespace IfcRoad
} // end namespace OpenInfraPlatform