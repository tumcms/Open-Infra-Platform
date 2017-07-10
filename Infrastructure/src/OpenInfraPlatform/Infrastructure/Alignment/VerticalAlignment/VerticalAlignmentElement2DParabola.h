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
#ifndef OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DParabola_1baa2c37_9c65_41b6_b72d_b35640918a7c_h
#define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DParabola_1baa2c37_9c65_41b6_b72d_b35640918a7c_h

#include "VerticalAlignmentElement2D.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

//! Parabola as a vertical alignment segment.
class BLUEINFRASTRUCTURE_API VerticalAlignmentElement2DParabola : public VerticalAlignmentElement2D
{
public:
	VerticalAlignmentElement2DParabola(const buw::Vector2d& start, 
		const buw::Vector2d& end,
		const double startGradient,
		const double endGradient);

	virtual ~VerticalAlignmentElement2DParabola();

	virtual buw::Vector2d					getPosition(const Stationing station) const;

	buw::Vector2d							getStartPosition() const override;

	buw::Vector2d							getEndPosition() const override;

	//! Determines the type of the horizontal alignment element.
	virtual eVerticalAlignmentType			getAlignmentType() const;

	virtual Stationing						getStartStation() const override;

	virtual Stationing						getEndStation() const override;

	virtual bool							genericQuery(const int id, void* result) const override;

	double									getStartGradient() const;

	double									getEndGradient() const;

	//! y=ax^2+bx+c
	void									getParameters(double& a, double& b, double& c) const;

	double									getFocalLength() const;

	//! Convex stands for a valley and concave for a crest.
	bool									isConvex() const;

	double									getGradient(const double x) const;

	double									getCurvature() const;

private:
	buw::Vector2d	start_;
	buw::Vector2d	end_;
	double			startGradient_;	// As Plane Angle Measure
	double			endGradient_;
}; // end class VerticalAlignmentElement2DParabola

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola;
}

#endif // end define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DParabola_1baa2c37_9c65_41b6_b72d_b35640918a7c_h
