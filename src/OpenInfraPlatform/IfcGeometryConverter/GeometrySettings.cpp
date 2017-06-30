/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
 *
 * - modified by Michael Kern, September 2014
*/

#include "GeometrySettings.h"

using namespace OpenInfraPlatform::IfcGeometryConverter;

/**********************************************************************************************/

GeometrySettings::GeometrySettings()
{
	m_num_vertices_per_circle = 20; // default 20
	m_min_num_vertices_per_arc = 6; // default 6

	m_min_colinearity = 0.1; // default 0.1
	m_min_delta_v = 1.0; // default 1.0
	m_min_normal_angle = M_PI/180.0; // default M_PI / 180.0
	m_min_length = 0.0002; // default 0.0002

	m_classify_type = carve::csg::CSG::CLASSIFY_EDGE;
}

/**********************************************************************************************/

GeometrySettings::~GeometrySettings()
{
}

/**********************************************************************************************/
