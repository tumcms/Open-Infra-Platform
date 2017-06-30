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

#include "../model/shared_ptr.h"
#include "IfcTunnelReader.h"

namespace OpenInfraPlatform
{
    namespace IfcTunnel
    {
        class IfcStepReader : public IfcTunnelReader
        {
        public:
            IfcStepReader();
            ~IfcStepReader();
            void readStreamHeader( std::string& in, shared_ptr<IfcTunnelModel> model );
            void readStreamData( std::string& in, std::map<int,shared_ptr<IfcTunnelEntity> >& map );
            void splitIntoStepLines( std::string& read_in, std::vector<std::string>& step_lines );
            void readStepLines( const std::vector<std::string>& step_lines, std::vector<shared_ptr<IfcTunnelEntity> >& target_entity_map );
            void readEntityArguments( const std::vector<shared_ptr<IfcTunnelEntity> >& vec_entities, const std::map<int,shared_ptr<IfcTunnelEntity> > map_entities );
        };
    } // end namespace IfcTunnel
} // end namespace OpenInfraPlatform