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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignment2DLine_6356618d_c005_40ac_87db_2712e4daa8b6_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignment2DLine_6356618d_c005_40ac_87db_2712e4daa8b6_h

#include "../../OIPInfrastructure.h"
#include "HorizontalAlignmentElement2D.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DLine : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DLine(const buw::Vector2d& start, const buw::Vector2d& end);

	virtual buw::Vector2d getPosition(const double lerpParameter) const override;

	virtual buw::Vector2d getTangent(const double lerpParameter) const override;

	virtual buw::Vector2d getNormal(const double lerpParameter) const override;

	virtual buw::Vector2d getStartPosition() const override;

	virtual buw::Vector2d getEndPosition() const override;

	virtual double getLength() const override;

	virtual eHorizontalAlignmentType getAlignmentType() const override;
	virtual bool genericQuery(const int id, void* result) const override;

private:
	buw::radiand getStartGradientAsPlaneAngle() const;

private:
	buw::Vector2d start_;
	buw::Vector2d end_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DLine;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignment2DLine_6356618d_c005_40ac_87db_2712e4daa8b6_h
