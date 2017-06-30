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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_6262fb3d_cc8b_4e19_8773_4ebe2ae1d7c5_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_6262fb3d_cc8b_4e19_8773_4ebe2ae1d7c5_h

#include "HorizontalAlignmentElement2D.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

struct BLUEINFRASTRUCTURE_API clothoidDescription {
	buw::Vector2d startPosition;
	double startDirection;
	double startCurvature;
	bool counterClockwise;
	double clothoidConstant;
	bool entry;
	double length;

	clothoidDescription();
	clothoidDescription(const buw::Vector2d startPosition,
	                    const double startDirection,
	                    const double startCurvature,
	                    const bool counterClockwise,
	                    const double clothoidConstant,
	                    const bool entry,
	                    const double length);
};

class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DClothoid : public HorizontalAlignmentElement2D {
public:
	HorizontalAlignmentElement2DClothoid(const clothoidDescription& cd);

	virtual eHorizontalAlignmentType getAlignmentType() const override;
	bool genericQuery(const int id, void* result) const override;

	buw::Vector2d getPosition(const double lerpParameter) const override;
	buw::Vector2d getTangent(const double lerpParameter) const override;
	buw::Vector2d getNormal(const double lerpParameter) const override;
	buw::Vector2d getStartPosition() const override;
	buw::Vector2d getEndPosition() const override;
	buw::Vector2d getPiPosition() const;

	double getStartRadius() const;
	double getEndRadius() const;

	double getStartCurvature() const;
	double getEndCurvature() const;

	double getStartDirection() const;
	double getEndDirection() const;

	double getClothoidConstant() const;
	double getLength() const override;

	bool isEntry() const;
	bool isCounterClockwise() const;
	bool isClockwise() const;

public:
	static double computeStartDirection(const buw::Vector2d& start, const buw::Vector2d& pi);
	static double computeEndDirection(const buw::Vector2d& pi, const buw::Vector2d& end);
	static double computeEntry(const double startCurvature, const double endCurvature);
	static double computeClothoidConstant(const double length, const double startCurvature, const double endCurvature);

	static double computeC(const double L, const double A);
	static double computeT(const double L, const double A);

	static double computeX(const double L, const double A);
	static double computeY(const double L, const double A);

private:
	buw::Vector2d computeLocalPosition(const double L) const;

private:
	buw::Vector2d startPosition_;
	double startDirection_;

	bool counterClockwise_;

	double clothoidConstant_;
	double startL_;
	double endL_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::clothoidDescription;
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DClothoid;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_6262fb3d_cc8b_4e19_8773_4ebe2ae1d7c5_h