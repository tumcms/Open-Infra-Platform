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
#ifndef OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DLine_2eb8aad5_8420_4596_bced_22a63945a267_h
#define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DLine_2eb8aad5_8420_4596_bced_22a63945a267_h

#include "VerticalAlignmentElement2D.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

//! Line segment of a vertical alignment.
class BLUEINFRASTRUCTURE_API VerticalAlignmentElement2DLine : public VerticalAlignmentElement2D
{
public:
	//! Creates a vertical alignment line segment
	/*!
		\param[in] start	X coordinates describes the start station and the Y coordinate the corresponding height		
		\param[in] end		X coordinates describes the end station and the Y coordinate the corresponding height		
	*/
	VerticalAlignmentElement2DLine(const buw::Vector2d& start, const buw::Vector2d& end);

	virtual ~VerticalAlignmentElement2DLine();

	virtual buw::Vector2d					getPosition(const Stationing station) const override;

	virtual buw::Vector2d					getStartPosition() const override;

	virtual buw::Vector2d					getEndPosition() const override;

	virtual eVerticalAlignmentType			getAlignmentType() const override;

	virtual Stationing						getStartStation() const override;

	virtual Stationing						getEndStation() const override;

	virtual bool							genericQuery (const int id, void* result) const override;

	virtual double							getGradient() const;

private:
	buw::Vector2d start_;
	buw::Vector2d end_;
}; // end class VerticalAlignmentElement2DLine

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine;
}

#endif // end define OpenInfraPlatform_Infrastructure_VerticalAlignmentElement2DLine_2eb8aad5_8420_4596_bced_22a63945a267_h
