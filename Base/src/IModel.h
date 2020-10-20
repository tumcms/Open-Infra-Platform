/*
Copyright (c) 2020 Technical University of Munich
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

#ifndef AD7D0227_733E_437B_80C7_1F4E94856789
#define AD7D0227_733E_437B_80C7_1F4E94856789

#pragma once

#include "namespace.h"
#include "BBox.h"
#include "GeorefMetadata.h"
#include <string>

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_BEGIN

class IModel {
public:

    virtual ~IModel() {}

	#pragma region Interface valid

	// is the model filled with data?
	virtual bool isEmpty() const = 0;

	#pragma endregion

	#pragma region Interface bounding box

    // consumed by the rendering procedures in viewport
    virtual oip::BBox     getExtent() = 0;

	#pragma endregion Interface bounding box

	#pragma region Interface georeferencing

    // needed for correct correlation between multiple models
    // also to determine if a transformation would be needed
	// the function should return empty string if unknown
    virtual GeorefMetadata getGeorefMetadata() const = 0;

	// change the georeferencing coordinate reference system to the \c newGeorefMetadata
	// function takes three coordinate values and returns three transformed coordinates
    virtual void transformAllPoints(const GeorefMetadata& newGeorefMetadata, std::function<std::tuple<double,double,double> const(double,double,double)>& transf) = 0;

	#pragma endregion Interface georeferencing

	#pragma region Interface data source

	// where does the data come from?
	// e.g. filename, URL, etc.
	virtual std::string getSource() const = 0;

	#pragma endregion Interface data source

};

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_END

EMBED_BASE_INTO_OIP_NAMESPACE(IModel)

#endif /* AD7D0227_733E_437B_80C7_1F4E94856789 */

