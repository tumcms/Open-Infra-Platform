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

#ifndef AD7D0227_733E_437B_80C7_1F4E94856895
#define AD7D0227_733E_437B_80C7_1F4E94856895

#pragma once

#include "namespace.h"
#include <string>
#include <map>
#include <carve/matrix.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_BEGIN

/*!
\brief Data storage for georeferencing metadata
*/
class GeorefMetadata {

public:
    //! constructor
    GeorefMetadata() { }
    //! destructor
    ~GeorefMetadata() { }

	//! code from the EPSG database
    std::string codeEPSG = "";

	//! additional meta values (like projection's epsg etc.)
	std::map<std::string, std::string> data;
	//! add another entry to data
	void addDataEntry(const std::string& key, const std::string& val) { data.insert(std::pair<std::string,std::string>(key, val)); }

	//! shift values (default = 0.)
	double x = 0.0, y = 0.0, z = 0.0;
	//! rotation angle around z-axis, in [rad] (default = 0.)
	double angle = 0.0;
	//! scale of axes (default = 1.)
	double scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
	//! the resulting transformation matrix
	carve::math::Matrix transformationMatrix()
	{
		return scale() * translation() * rotation();
	}

	carve::math::Matrix rotation()
	{
		return carve::math::Matrix(
			1.0, 0.0, 0.0, 0.0,
			0.0, cos(angle), sin(angle), 0.0,
			0.0, sin(angle), -cos(angle), 0.0,
			0.0, 0.0, 0.0, 1.0);
	}

	carve::math::Matrix translation()
	{
		return carve::math::Matrix(
			1.0, 0.0, 0.0, x,
			0.0, 1.0, 0.0, y,
			0.0, 0.0, 1.0, z,
			0.0, 0.0, 0.0, 1.0);
	}

	carve::math::Matrix scale()
	{
		return carve::math::Matrix(
			scaleX, 0.0,    0.0,    0.0,
			0.0,    scaleY, 0.0,    0.0,
			0.0,    0.0,    scaleZ, 0.0,
			0.0,    0.0,    0.0,    1.0);
	}


    
};

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_END

EMBED_BASE_INTO_OIP_NAMESPACE(GeorefMetadata)

#endif /* AD7D0227_733E_437B_80C7_1F4E94856895 */
