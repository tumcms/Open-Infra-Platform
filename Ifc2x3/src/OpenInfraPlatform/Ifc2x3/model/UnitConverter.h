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

#include <map>
#include "shared_ptr.h"

namespace OpenInfraPlatform
{
    namespace Ifc2x3
    {
        class IfcProject;

        class UnitConverter
        {
        public:
            UnitConverter();
            void setIfcProject( shared_ptr<IfcProject> project);

            double getLengthInMeterFactor()
            {
                return m_length_unit_factor;
            }

            double getAngleInRadianFactor()
            {
                return m_plane_angle_factor;
            }

        private:
            std::map<int, double> m_prefix_map;
            double m_length_unit_factor;
            double m_plane_angle_factor;
        };
    } // end namespace Ifc2x3
} // end namespace OpenInfraPlatform