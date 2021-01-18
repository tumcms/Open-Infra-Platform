/*
    Copyright (c) 2018 Technical University of Munich
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
// visual studio
#pragma once
// unix
#ifndef GEOMETRYSETTINGS_H
#define GEOMETRYSETTINGS_H

#include "CarveHeaders.h"

#define GEOM_TOLERANCE  0.0000001
#ifdef _DEBUG
#define HALF_SPACE_BOX_SIZE 100
#else
	#define HALF_SPACE_BOX_SIZE 100
#endif


namespace OpenInfraPlatform
{
	namespace Core 
	{
		namespace IfcGeometryConverter {

			/*!	\brief Settings regarding tessellation and precision of geometries

			*/
			class GeometrySettings {
			public:
				//! Default constructor
				GeometrySettings();
				//! Default destructor
				~GeometrySettings();
				
				/*! Calculates the number of vertices needed for tessellation of an arc
				
				\param[in] dRadius		The radius of the arc
				\param[in] dArcStart	The angle where the arc begins [in radians]
				\param[in] dArcEnd		The angle where the arc stops [in radians]

				\sa getNumberOfVertices

				\return The number of vertices
				*/
				int getNumberOfVerticesForTessellation(const double dRadius, const double dArcStart, const double dArcEnd)
				{
					return getNumberOfVerticesForTessellation(dRadius, abs(dArcStart - dArcEnd));
				}
				
				/*! Calculates the number of vertices needed for tessellation of an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The number of vertices
				*/
				int getNumberOfVerticesForTessellation(const double dRadius, const double dArcExtent = 2. * M_PI)
				{
					// if radius is smaller then the precision of the model, it is a straight (curvature -> infinity)
					if (dRadius < getPrecision())
						return 2;

					// what's the biggest angle so that the precision still holds
					// that is, the maximum distance between the arc and the line between two points on the arc < precision
					double alpha = acos((dRadius - getTessellationPrecision()) / dRadius);

					// we need at least this many segments along the arc
					int numOfVertices = (int) ceil(dArcExtent / alpha);

					// return at least 2 (start & end)
					return carve::util::max_functor()(numOfVertices , 2);
				}

				/*! Calculates the arc segment length when tessellating an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The angular length of the segment [in radians]
				*/
				double getAngleLength(const double dRadius, const double dArcExtent = 2.0 * M_PI)
				{
					return dArcExtent / (double)(getNumberOfSegmentsForTessellation(dRadius, dArcExtent));
				}

				/*! Calculates the number of segments when tessellating an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The number of segments [in radians]
				*/
				int getNumberOfSegmentsForTessellation(const double dRadius, const double dArcExtent = 2.0 * M_PI)
				{
					return getNumberOfVerticesForTessellation(dRadius, dArcExtent) - 1;
				}

				/*! returns the precision of the model
				
				
				*/
				double getPrecision() const
				{
					return carve::EPSILON; //TODO remove constant and replace with content from IFC (i.e. introduce member, getter / setter)
				}
				
				/*! returns the tessellation precision of the model

				*/
				double getTessellationPrecision() const
				{
					return 0.01;
				}

				/*! \brief Normalizes given angle to lie within the specified interval.

				\param[in,out]	dAngle	The angle to be normalized.
				\param[in]		dMin	The lower edge of the interval (default = 0).
				\param[in]		dMax	The upper edge of the interval (default = 2*PI).

				\note The interval is increased to a minimum of \c dMin \c + \c 2*PI if needed.
				\note The borders are swaped to fulfil \c dMin \c < \c dMax.
				*/
				void normalizeAngle(double& dAngle, double dMin = 0., double dMax = M_TWOPI)
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
				/*!Compare two doubles for equality to the custom precision
				*param[in]    first      The first value
				*param[in]    second     The second value
				*param[in]    precision  Precision of model
				
				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const double first,const double second,const double precision) const
				{
					return abs(first - second) < precision;
				}

				/*!Compare two doubles for equality to the default precision
				*param[in]    first      The first value
				*param[in]    second     The second value

				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const double first, const double second) const
				{
					return areEqual(first, second, getPrecision());
				}

				/*!Compare two 2D vectors for equality to the default precision
				*param[in]    first      The first 2D-point of vector
				*param[in]    second     The second 2D-point of vector

				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second) const
				{
					return areEqual(first, second, getPrecision());
				}

				/*!Compare two 3D vectors for equality to the default precision
				*param[in]    first      The first 3D-point of vector
				*param[in]    second     The second 3D-point of vector

				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second) const
				{
					return areEqual(first, second, getPrecision());
				}

				/*!Compare two 2D vectors for equality to the custom precision
				*param[in]    first      The first 2D-point of vector
				*param[in]    second     The second 2D-point of vector
				*param[in]    precision  Precision of model

				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second,const double precision) const
				{
					return areEqual(first.x, second.x, precision) && areEqual(first.y, second.y, precision);
				}

				/*!Compare two 3D vectors for equality to the custom precision
				*param[in]    first      The first 3D-point of vector
				*param[in]    second     The second 3D-point of vector
				*param[in]    precision  Precision of model

				*return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second, const double precision) const
				{
					return areEqual(first.x, second.x, precision) && areEqual(first.y, second.y, precision) && areEqual(first.z, second.z, precision);
				}
						   
				carve::csg::CSG::CLASSIFY_TYPE getCSGtype() {
					return classify_type;
				}

			private:
				int	num_vertices_per_circle;
				int min_num_vertices_per_arc;

				double min_colinearity;
				double min_delta_v;
				double min_normal_angle;
				double min_length;
				carve::csg::CSG::CLASSIFY_TYPE classify_type;
			};
		}
	}
}

#endif

