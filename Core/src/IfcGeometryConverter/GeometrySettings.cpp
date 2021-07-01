/*
    Copyright (c) 2021 Technical University of Munich
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

using namespace OpenInfraPlatform::Core::IfcGeometryConverter;

/**********************************************************************************************/

GeometrySettings::GeometrySettings()
{
	num_vertices_per_circle = 20; // default 20
	min_num_vertices_per_arc = 6; // default 6

	min_colinearity = 0.1; // default 0.1
	min_delta_v = 1.0; // default 1.0
	min_normal_angle = M_PI/180.0; // default M_PI / 180.0
	min_length = 0.0002; // default 0.0002

	classify_type = carve::csg::CSG::CLASSIFY_EDGE;
}

/**********************************************************************************************/

GeometrySettings::~GeometrySettings()
{
}

/**********************************************************************************************/

int GeometrySettings::getNumberOfVerticesForTessellation(const double dRadius, const double dArcStart, const double dArcEnd)
{
	return getNumberOfVerticesForTessellation(dRadius, abs(dArcStart - dArcEnd));
}

/**********************************************************************************************/

int GeometrySettings::getNumberOfVerticesForTessellation(const double dRadius, const double dArcExtent)  
{
	// if radius is smaller then the precision of the model, it is a straight (curvature -> infinity)
	if (dRadius < getPrecision())
		return 2;

	// what's the biggest angle so that the precision still holds
	// that is, the maximum distance between the arc and the line between two points on the arc < precision
	double alpha = acos((dRadius - getTessellationPrecision()) / dRadius);

	// we need at least this many segments along the arc
	int numOfVertices = (int)ceil(dArcExtent / alpha);

	// return at least 2 (start & end)
	return carve::util::max_functor()(numOfVertices, 2);
}

/**********************************************************************************************/

double GeometrySettings::getAngleLength(const double dRadius, const double dArcExtent)
{
	return dArcExtent / (double)(getNumberOfSegmentsForTessellation(dRadius, dArcExtent));
}

/**********************************************************************************************/

int GeometrySettings::getNumberOfSegmentsForTessellation(const double dRadius, const double dArcExtent)
{
	return getNumberOfVerticesForTessellation(dRadius, dArcExtent) - 1;
}

/**********************************************************************************************/

double GeometrySettings::getPrecision() const
{
	return carve::EPSILON; //TODO remove constant and replace with content from IFC (i.e. introduce member, getter / setter)
}

/**********************************************************************************************/

double GeometrySettings::getTessellationPrecision() const
{
	return 0.01;
}

/**********************************************************************************************/

void GeometrySettings::normalizeAngle(double& dAngle, double dMin, double dMax)
{
	if (dMax < dMin)
		std::swap(dMin, dMax);
	if (dMax - dMin < M_TWOPI)
		dMax = dMin + M_TWOPI;

	while (dAngle > dMax) {
		dAngle -= M_TWOPI;
	}
	while (dAngle < dMin) {
		dAngle += M_TWOPI;
	}
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const double first, const double second, const double precision) const
{
	return GeomUtils::areEqual(first, second, precision);
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const double first, const double second) const
{
	return areEqual(first, second, getPrecision());
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second) const
{
	return areEqual(first, second, getPrecision());
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second) const
{
	return areEqual(first, second, getPrecision());
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second, const double precision) const
{
	return areEqual(first.x, second.x, precision) && areEqual(first.y, second.y, precision);
}

/**********************************************************************************************/

bool GeometrySettings::areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second, const double precision) const
{
	return areEqual(first.x, second.x, precision) && areEqual(first.y, second.y, precision) && areEqual(first.z, second.z, precision);
}

/**********************************************************************************************/

carve::csg::CSG::CLASSIFY_TYPE GeometrySettings::getCSGtype() {
	return classify_type;
}