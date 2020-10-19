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

#ifndef AD7D0227_733E_437B_80C7_1F4E94856795
#define AD7D0227_733E_437B_80C7_1F4E94856795

#pragma once

#include "namespace.h"

#include <BlueFramework/Rasterizer/vertex.h>
#include "carve\aabb.hpp"

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_BEGIN

/*!
\brief Internal implementation of a bounding box.

This is a wrapper around the carve's aabb (axis-aligned bounding box).
*/
struct BBox : public carve::geom::aabb<3> {
    using base = carve::geom::aabb<3>;
public:
    //! constructor
	BBox() { reset(); }
    /*!
     * \brief updates the bounding box extent
     *
     * \param[in] x the x-coordinate of the point
     * \param[in] y the y-coordinate of the point
     * \param[in] z the z-coordinate of the point
     */
    void update(const float x, const float y, const float z)
    {
        if (isEmpty())
        {
            base::fit( carve::geom::VECTOR(x, y, z));
            isFirst = false;
        }
        else
            base::fit(carve::geom::VECTOR(x, y, z), base::min(), base::max());
    }
    /*!
     * \brief updates the bounding box extent
     *
     * \param[in] other the other bounding box to update self with
     */
    void update(const base& other)
    {
        if (other.isEmpty())
            update(other.pos.x, other.pos.y, other.pos.z);

        if (isEmpty())
        {
            base::operator=( other );
            isFirst = false;
        }
        else
            base::unionAABB( other );
    }
    //! resets the bounding box to zero
    void reset() { base::empty(); isFirst = true; }
    //! is the bounding box empty?
    bool isEmpty() { return isFirst && base::isEmpty(); }
    //! returns the min-max extents
    std::string toString() const {
        return "min: (" + std::to_string(min().x()) + ", " + std::to_string(min().y()) + ", " + std::to_string(min().z())
           + ") max: (" + std::to_string(max().x()) + ", " + std::to_string(max().y()) + ", " + std::to_string(max().z()) + ")";
    }
    //! returns the center point of the bounding box
    buw::Vector3d center() const { return buw::Vector3d( base::mid().x, base::mid().y, base::mid().z); }
    //! returns the smallest point of the bounding box
    buw::Vector3d min() const { return buw::Vector3d( base::min().x, base::min().y, base::min().z ); }
    //! returns the maximal point of the bounding box
    buw::Vector3d max() const { return buw::Vector3d( base::max().x, base::max().y, base::max().z ); }
    //! carve::geom::aabb doesn't have a "not set" value, but rather everything is 0,0,0 per default. This variable helps overcome this.
    bool isFirst = true;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_BASE_END

EMBED_BASE_INTO_OIP_NAMESPACE(BBox)

#endif /* AD7D0227_733E_437B_80C7_1F4E94856795 */
