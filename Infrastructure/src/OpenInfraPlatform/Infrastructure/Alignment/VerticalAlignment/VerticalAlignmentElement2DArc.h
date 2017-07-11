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
#ifndef OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DArc_fcff559c_c158_423f_9873_3ffb1e0b280e_h
#define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DArc_fcff559c_c158_423f_9873_3ffb1e0b280e_h

#include "VerticalAlignmentElement2D.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class VerticalAlignmentElement2DArc : public VerticalAlignmentElement2D
{
public:

	VerticalAlignmentElement2DArc(
		const buw::Vector2d& start,
		const buw::Vector2d& end,
		const double radius,
		const double startGradient,
		const bool isConvex);

	virtual ~VerticalAlignmentElement2DArc();

	virtual buw::Vector2d				getPosition(const Stationing station) const override;

	virtual buw::Vector2d				getStartPosition() const override;

	virtual buw::Vector2d				getEndPosition() const override;

	virtual Stationing					getStartStation() const override;

	virtual Stationing					getEndStation() const override;

	virtual eVerticalAlignmentType		getAlignmentType() const override;

	buw::Vector2d getCenter() const;

	double getRadius() const;

	double getCurvature() const;

	bool isConvex() const;

	//! A generic Query
	virtual bool						genericQuery(const int id, void* result) const;

private:
	buw::Vector2d Rotate(const double angle, const buw::Vector2d& v) const;

private:
	double			startGradient_;
	buw::Vector2d	start_;
	buw::Vector2d	end_;
	double			radius_;
	bool            isConvex_;
}; // end class VerticalAlignmentElement2DArc

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DArc;
}

#endif // end define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DArc_fcff559c_c158_423f_9873_3ffb1e0b280e_h
