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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DBlossCurve_6a1ff797_6cbb_4b12_9ea2_efa06bc54189_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DBlossCurve_6a1ff797_6cbb_4b12_9ea2_efa06bc54189_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "HorizontalAlignmentElement2D.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

struct BLUEINFRASTRUCTURE_API blossDescription {
	buw::Vector2d startPosition;
	double startDirection;
	bool counterClockwise;
	bool entry;
	double length;
	double radius;

	blossDescription();
	blossDescription(const buw::Vector2d startPosition,
		const double startDirection,
		const bool counterClockwise,
		const bool entry,
		const double length,
		const double radius);
};
class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DBlossCurve : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DBlossCurve(const blossDescription& bd);

	virtual ~HorizontalAlignmentElement2DBlossCurve() {}

	virtual eHorizontalAlignmentType getAlignmentType() const override;
	virtual bool genericQuery(const int id, void* result) const override;

	buw::Vector2d getPosition(const double lerpParameter) const override;
	buw::Vector2d getTangent(const double lerpParameter) const override;
	buw::Vector2d getNormal(const double lerpParameter) const override;
	double getCurvature(const double lerpParameter) const;

	buw::Vector2d getStartPosition() const override;
	buw::Vector2d getEndPosition() const override;
	buw::Vector2d getPiPosition() const;

	double getStartRadius() const;
	double getEndRadius() const;

	double getStartCurvature() const;
	double getEndCurvature() const;

	double getStartDirection() const;
	double getEndDirection() const;

	virtual double getLength() const override;

	bool isEntry() const;
	bool isCounterClockwise() const;
	bool isClockwise() const;

public:
	static double computeStartDirection(const buw::Vector2d& start, const buw::Vector2d& pi);
	static double computeEndDirection(const buw::Vector2d& pi, const buw::Vector2d& end);
	static void computeEntry(const double startRadius, const double endRadius, bool& entry, double& radius);

	static double computeX(const double L, const double R, const double l);
	static double computeY(const double L, const double R, const double l);
	static double computeT(const double L, const double R, const double l);
	static double computeC(const double L, const double R, const double l);

private:
	buw::Vector2d computeLocalPosition(const double l) const;
	double computeLocalT(const double l) const;
	double computeLocalC(const double l) const;

private:
	buw::Vector2d	startPosition_;
	double		startDirection_;

	bool		counterClockwise_;
	bool		isEntry_;

	double		R;
	double		L;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DBlossCurve;
	using OpenInfraPlatform::Infrastructure::blossDescription;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DBlossCurve_6a1ff797_6cbb_4b12_9ea2_efa06bc54189_h
