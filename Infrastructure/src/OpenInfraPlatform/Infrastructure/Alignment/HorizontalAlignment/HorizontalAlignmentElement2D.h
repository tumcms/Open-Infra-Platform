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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2D_caa66582_c89b_4106_849d_6b6bc21bc542_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2D_caa66582_c89b_4106_849d_6b6bc21bc542_h

#include "../../Core/IQueryable.h"
#include "../../OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <boost/noncopyable.hpp>
#include <buw.Core.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

enum class BLUEINFRASTRUCTURE_API eHorizontalAlignmentType { Line = 0, Arc = 1, Clothoid = 2, Bloss = 3, Unknown = 4 };

//! Get horizontal alignment type as string.
BLUEINFRASTRUCTURE_API std::string horizontalAlignmentTypeToString(const eHorizontalAlignmentType type);

//! A 2d horizontal (x,y) alignment element.
class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2D : public OpenInfraPlatform::Infrastructure::IQueryable {
public:
	//! Get a point on the alignment element.
	/*!
	    \param[in]	lerpParameter	A paramter of [0;1] where 0 corresponds to the start point and 1 to the end point.
	    \returns
	*/
	virtual buw::Vector2d getPosition(const double lerpParameter) const = 0;

	//! The tangent points into the direction of increasing parameter value.
	virtual buw::Vector2d getTangent(const double lerpParameter) const = 0;

	//! The normal points into the left perpendicular direction of the tangent.
	virtual buw::Vector2d getNormal(const double lerpParameter) const = 0;

	//! Should return the same value as getPosition(0.0)
	virtual buw::Vector2d getStartPosition() const = 0;

	//! Should return the same value as getPosition(1.0)
	virtual buw::Vector2d getEndPosition() const = 0;

	//! Determines the length of the element.
	virtual double getLength() const = 0;

	//! Determines the type of the horizontal alignment element.
	virtual eHorizontalAlignmentType getAlignmentType() const;

	//! A generic Query
	virtual bool genericQuery(const int /*id*/, void* /*result*/) const;
};

BLUEINFRASTRUCTURE_API std::ostream& operator<<(std::ostream& os, const eHorizontalAlignmentType hat);

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::horizontalAlignmentTypeToString;
	using OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType;
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2D;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2D_caa66582_c89b_4106_849d_6b6bc21bc542_h