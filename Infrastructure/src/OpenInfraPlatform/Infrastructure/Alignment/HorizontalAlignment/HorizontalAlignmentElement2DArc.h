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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignment2DArc_c9b849d5_4ac6_41a1_b0f9_9067c70f948a_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignment2DArc_c9b849d5_4ac6_41a1_b0f9_9067c70f948a_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "HorizontalAlignmentElement2D.h"
#include "../../OIPInfrastructure.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DArc : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DArc(
		const buw::Vector2d& center,
		const buw::Vector2d& start,
		const buw::Vector2d& end,
		const bool clockWise);

	virtual ~HorizontalAlignmentElement2DArc();

	virtual buw::Vector2d getPosition(const double lerpParameter) const override;

	virtual buw::Vector2d getTangent(const double lerpParameter) const override;

	virtual buw::Vector2d getNormal(const double lerpParameter) const override;

	virtual buw::Vector2d getCenter() const { return center_; }

	virtual bool getClockWise() const { return clockWise_; }

	virtual buw::Vector2d getStartPosition() const override;

	virtual buw::Vector2d getEndPosition() const override;

	virtual double getLength() const;

	virtual bool genericQuery(const int id, void* result) const override;

	virtual eHorizontalAlignmentType getAlignmentType() const override;

	double getRadius() const;

	double getCurvature()	const { return 1 / getRadius() * (clockWise_ ? -1 : 1); }

private:
	buw::Vector2d Rotate(const double angle, const buw::Vector2d& v) const;
	buw::Vector2d Rotate(const double angle, const double x, const double y) const;

	buw::Vector2d		center_;
	buw::Vector2d		start_;
	buw::Vector2d		end_;
	bool			clockWise_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignment2DArc_c9b849d5_4ac6_41a1_b0f9_9067c70f948a_h
