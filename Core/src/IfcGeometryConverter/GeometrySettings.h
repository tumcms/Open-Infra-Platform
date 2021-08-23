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
#include "GeomUtils.h"

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
				int getNumberOfVerticesForTessellation(const double dRadius, const double dArcStart, const double dArcEnd);
				

				/*! Calculates the number of vertices needed for tessellation of an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The number of vertices
				*/
				int getNumberOfVerticesForTessellation(const double dRadius, const double dArcExtent = 2. * M_PI);
				

				/*! Calculates the arc segment length when tessellating an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The angular length of the segment [in radians]
				*/
				double getAngleLength(const double dRadius, const double dArcExtent = 2.0 * M_PI);
				

				/*! Calculates the number of segments when tessellating an arc

				\param[in] dRadius		The radius of the arc
				\param[in] dArcExtent	The angular extent of the arc [in radians] (default = full circle)

				\return The number of segments [in radians]
				*/
				int getNumberOfSegmentsForTessellation(const double dRadius, const double dArcExtent = 2.0 * M_PI);
				

				/*! returns the precision of the model
				
				
				*/
				double getPrecision() const;
				
				
				/*! returns the tessellation precision of the model

				*/
				double getTessellationPrecision() const;
				

				/*! \brief Normalizes given angle to lie within the specified interval.

				\param[in,out]	dAngle	The angle to be normalized.
				\param[in]		dMin	The lower edge of the interval (default = 0).
				\param[in]		dMax	The upper edge of the interval (default = 2*PI).

				\note The interval is increased to a minimum of \c dMin \c + \c 2*PI if needed.
				\note The borders are swaped to fulfil \c dMin \c < \c dMax.
				*/
				void normalizeAngle(double& dAngle, double dMin = 0., double dMax = M_TWOPI);
				

				/*!Compare two doubles for equality to the custom precision
				* \param[in]    first      The first value
				* \param[in]    second     The second value
				* \param[in]    precision  Precision of model
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const double first, const double second, const double precision) const;
				

				/*!Compare two doubles for equality to the default precision
				* \param[in]    first      The first value
				* \param[in]    second     The second value
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const double first, const double second) const;

				/*!Compare two 2D vectors for equality to the default precision
				* \param[in]    first      The first 2D-point of vector
				* \param[in]    second     The second 2D-point of vector
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second) const;

				/*!Compare two 3D vectors for equality to the default precision
				* \param[in]    first      The first 3D-point of vector
				* \param[in]    second     The second 3D-point of vector
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second) const;
				
				/*!Compare two 2D vectors for equality to the custom precision
				* \param[in]    first      The first 2D-point of vector
				* \param[in]    second     The second 2D-point of vector
				* \param[in]    precision  Precision of model
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const carve::geom::vector<2>& first, const  carve::geom::vector<2>& second, const double precision) const;

				/*!Compare two 3D vectors for equality to the custom precision
				* \param[in]    first      The first 3D-point of vector
				* \param[in]    second     The second 3D-point of vector
				* \param[in]    precision  Precision of model
				*
				* \return true, if the absolute difference is smaller than the precision. False otherwise
				*/
				bool areEqual(const  carve::geom::vector<3>& first, const  carve::geom::vector<3>& second, const double precision) const;
						   
				carve::csg::CSG::CLASSIFY_TYPE getCSGtype();

				/*! Calculates the number of segments when tessellating an curve

				\param[in] length		The length "l" of the lenght

				\return The number of segments 
				*/
				int getNumberOfTessellationSegmentsByLength(const double length)
				{
					// if length is smaller then the precision of the model, it is a straight (curvature -> infinity)
					if (length < getPrecision())
						return 1;
					// calculate number of segments points
					double newSegmentsOfLength = length / getPrecision();
					
					return (ceil(newSegmentsOfLength)-1);
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

