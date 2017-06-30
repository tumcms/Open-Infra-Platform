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

#include "HorizontalAlignmentElement2DArc.h"
#include <BlueFramework/Core/assert.h>

#include <utility>

OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::HorizontalAlignmentElement2DArc(const buw::Vector2d& center,
                                                                                                    const buw::Vector2d& start,
                                                                                                    const buw::Vector2d& end,
                                                                                                    const bool clockWise)
    : center_(center), start_(start), end_(end), clockWise_(clockWise) {
}

OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::~HorizontalAlignmentElement2DArc() {
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::Rotate(const double angle, const double x, const double y) const {
	return buw::Vector2d(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y);
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::Rotate(const double angle, const buw::Vector2d& v) const {
	return Rotate(angle, v.x(), v.y());
}

bool OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::genericQuery(const int id, void* result) const {
	switch (id) {
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = start_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = end_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Center: *reinterpret_cast<buw::Vector2d*>(result) = center_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius: *reinterpret_cast<double*>(result) = getRadius(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise: *reinterpret_cast<bool*>(result) = clockWise_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise: *reinterpret_cast<bool*>(result) = !clockWise_; break;

	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getAlignmentType() const {
	return eHorizontalAlignmentType::Arc;
}

double OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getRadius() const {
	return (center_ - start_).norm();
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getPosition(const double lerpParameter) const {
	// std::cout << "lerpParameter from getPos Arc: " << lerpParameter << std::endl;
	BLUE_ASSERT(lerpParameter >= 0.0, "Invalid lerp paramter.");
	BLUE_ASSERT(lerpParameter <= 1.0, "Invalid lerp paramter.");

	buw::Vector2d v1 = start_ - center_;
	buw::Vector2d v2 = end_ - center_;

	double alpha = 0;

	if (clockWise_)
		alpha = buw::calculateAngleBetweenVectors(v2, v1) * lerpParameter;
	else
		alpha = buw::calculateAngleBetweenVectors(v1, v2) * lerpParameter;

	if (clockWise_)
		v2 = Rotate(-alpha, v1);
	else
		v2 = Rotate(alpha, v1);

	return center_ + v2;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getTangent(const double lerpParameter) const
{
	buw::Vector2d tangent = getNormal(lerpParameter);

	// Rotate the normal by 90 degrees CW to get the tangent.
	// The tanget must point into the direction of increasing parameter value.

	// Swap coordinates.
	std::swap(tangent[0], tangent[1]);

	// Flip the respective sign.
	bool const bFlipSecondCoord = (tangent[0] < 0.0 ^ tangent[1] < 0.0);
	tangent[bFlipSecondCoord] = -tangent[bFlipSecondCoord];

	return tangent;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getNormal(const double lerpParameter) const
{
	buw::Vector2d const& normal = (getPosition(lerpParameter) - center_).normalized();
	return clockWise_ ? normal : -normal;
}

double OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getLength() const {
	auto radius = getRadius();

	buw::Vector2d v1 = start_ - center_;
	buw::Vector2d v2 = end_ - center_;

	double angleInRad = 0;

	if (clockWise_)
		angleInRad = buw::calculateAngleBetweenVectors(v2, v1);
	else
		angleInRad = buw::calculateAngleBetweenVectors(v1, v2);

	return buw::constantsd::pi() * radius * (buw::radianToDegree(angleInRad) / 180.0);
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getStartPosition() const {
	return start_;
}

buw::Vector2d OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc::getEndPosition() const {
	return end_;
}
