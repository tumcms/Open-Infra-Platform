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

#include "VerticalAlignmentElement2DArc.h"
#include <BlueFramework/Core/assert.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

enum class eCircleIntersectionResult { NoIntersection, Coincident, TangentIntersection, TwoPointIntersection };

class Circle2 {
public:
	typedef buw::Vector2d Vector2d;

	Circle2(double radius, Vector2d& center) : radius_(radius), center_(center) {
	}

	Circle2(double radius, const Vector2d& center) : radius_(radius), center_(center) {
	}

	Circle2(double radius, double centerX, double centerY) : radius_(radius), center_(centerX, centerY) {
	}

	Vector2d getCenter() const {
		return center_;
	}
	double getRadius() const {
		return radius_;
	}

	eCircleIntersectionResult intersect(const Circle2& C2, Vector2d& i1, Vector2d& i2) {
		// distance between the centers
		double d = Vector2d(center_.x() - C2.center_.x(), center_.y() - C2.center_.y()).norm();

		// find number of solutions
		if (d > radius_ + C2.radius_) // circles are too far apart, no solution(s)
		{
			return eCircleIntersectionResult::NoIntersection;
		} else if (d == 0 && radius_ == C2.radius_) // circles coincide
		{
			return eCircleIntersectionResult::Coincident;
		}
		// one circle contains the other
		else if (d + std::min(radius_, C2.radius_) < std::max(radius_, C2.radius_)) {
			return eCircleIntersectionResult::NoIntersection;
		} else {
			double a = (radius_ * radius_ - C2.radius_ * C2.radius_ + d * d) / (2.0 * d);
			double h = sqrt(radius_ * radius_ - a * a);

			// find p2
			Vector2d p2(center_.x() + (a * (C2.center_.x() - center_.x())) / d, center_.y() + (a * (C2.center_.y() - center_.y())) / d);

			// find intersection points p3
			i1 = Vector2d(p2.x() + (h * (C2.center_.y() - center_.y()) / d), p2.y() - (h * (C2.center_.x() - center_.x()) / d));
			i2 = Vector2d(p2.x() - (h * (C2.center_.y() - center_.y()) / d), p2.y() + (h * (C2.center_.x() - center_.x()) / d));

			if (d == radius_ + C2.radius_)
				return eCircleIntersectionResult::TangentIntersection;
			return eCircleIntersectionResult::TwoPointIntersection;
		}
	}

	// Print circle
	friend std::ostream& operator<<(std::ostream& out, const Circle2& C) {
		out << "Center: " << C.getCenter() << ", r = " << C.getRadius();
		return out;
	}

private:
	// radius
	double radius_;
	// center
	Vector2d center_;
};



VerticalAlignmentElement2DArc::VerticalAlignmentElement2DArc(const buw::Vector2d& start,
                                                             const buw::Vector2d& end,
                                                             const double radius,
                                                             const double startGradient,
                                                             const bool isConvex)
    : start_(start), end_(end), radius_(radius), startGradient_(startGradient), isConvex_(isConvex) {
	BLUE_ASSERT(start.x() <= end.x(), "Invalid coordinates.");
	BLUE_ASSERT(radius >= 0, "Invalid radius.");
}

VerticalAlignmentElement2DArc::~VerticalAlignmentElement2DArc() {
}

bool VerticalAlignmentElement2DArc::genericQuery(const int id, void* result) const {
	switch (id) {
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = start_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = end_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius: *reinterpret_cast<double*>(result) = radius_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::IsConvex: *reinterpret_cast<bool*>(result) = isConvex_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradient: *reinterpret_cast<double*>(result) = startGradient_; break;
	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

eVerticalAlignmentType VerticalAlignmentElement2DArc::getAlignmentType() const {
	return eVerticalAlignmentType::Arc;
}

buw::Vector2d VerticalAlignmentElement2DArc::getCenter() const
{
	Circle2 c1(radius_, start_);
	Circle2 c2(radius_, end_);

	buw::Vector2d i1, i2;
	auto result = c1.intersect(c2, i1, i2);
	BLUE_ASSERT(result == eCircleIntersectionResult::TwoPointIntersection || result == eCircleIntersectionResult::TangentIntersection, "Invalid center point.");

	buw::Vector2d center = i1;

	if (!isConvex_) {
		if (i1.y() < i2.y())
			center = i1;
		else
			center = i2;
	} else {
		if (i1.y() > i2.y())
			center = i1;
		else
			center = i2;
	}

	return center;
}

double VerticalAlignmentElement2DArc::getRadius() const {
	return radius_;
}

double VerticalAlignmentElement2DArc::getCurvature() const {
	return 1.0 / getRadius() * (isConvex_ ? 1 : -1);
}

bool VerticalAlignmentElement2DArc::isConvex() const {
	return isConvex_;
}


Stationing VerticalAlignmentElement2DArc::getEndStation() const {
	return end_.x();
}

Stationing VerticalAlignmentElement2DArc::getStartStation() const {
	return start_.x();
}

buw::Vector2d VerticalAlignmentElement2DArc::getPosition(const Stationing station) const {
	BLUE_ASSERT(station >= getStartStation(), "Invalid station.");
	BLUE_ASSERT(station <= getEndStation(), "Invalid station.");

	buw::Vector2d const center = getCenter();
	double a = center.x();
	double b = center.y();
	double sqrtTmp = std::sqrt(radius_ * radius_ - (station - a) * (station - a));

	if (isConvex_)
		return buw::Vector2d(station, b - sqrtTmp);
	else
		return buw::Vector2d(station, b + sqrtTmp);
}

buw::Vector2d VerticalAlignmentElement2DArc::getStartPosition() const {
	return start_;
}

buw::Vector2d VerticalAlignmentElement2DArc::getEndPosition() const {
	return end_;
}

buw::Vector2d VerticalAlignmentElement2DArc::Rotate(const double angle, const buw::Vector2d& v) const {
	return buw::Vector2d(std::cos(angle) * v.x() - std::sin(angle) * v.y(), std::sin(angle) * v.x() + std::cos(angle) * v.y());
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END