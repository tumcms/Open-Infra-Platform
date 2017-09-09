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

#include "HorizontalAlignmentElement2DLine.h"
#include <BlueFramework/Core/assert.h>

#include <utility>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

bool HorizontalAlignmentElement2DLine::genericQuery(const int id, void* result) const {
	switch (id) {
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = start_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = end_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradientAsPlaneAngleMeasure: *reinterpret_cast<double*>(result) = getStartGradientAsPlaneAngle(); break;
	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

eHorizontalAlignmentType HorizontalAlignmentElement2DLine::getAlignmentType() const {
	return eHorizontalAlignmentType::Line;
}

buw::Vector2d HorizontalAlignmentElement2DLine::getPosition(const double lerpParameter) const {
	return buw::lerp(start_, end_, lerpParameter);
}

buw::Vector2d HorizontalAlignmentElement2DLine::getTangent(const double /*lerpParameter*/) const
{
	return (end_ - start_).normalized();
}

buw::Vector2d HorizontalAlignmentElement2DLine::getNormal(const double lerpParameter) const
{
	// Rotate the tangent by 90 degrees CCW to get the normal.
	return buw::orthogonal(getTangent(lerpParameter), true);
}

double HorizontalAlignmentElement2DLine::getLength() const {
	return (start_ - end_).norm();
}

HorizontalAlignmentElement2DLine::HorizontalAlignmentElement2DLine(const buw::Vector2d& start, const buw::Vector2d& end) : start_(start), end_(end) {
	// BLUE_ASSERT(start != end, "Start == End");	// Warning. Unusual!
}

buw::radiand HorizontalAlignmentElement2DLine::getStartGradientAsPlaneAngle() const {
	buw::Vector2d startDirection = end_ - start_;
	buw::Vector2d xAxis = buw::Vector2d(1.0, 0.0);
	buw::radiand angle = buw::calculateAngleBetweenVectors(startDirection, xAxis);
	return angle;
}

buw::Vector2d HorizontalAlignmentElement2DLine::getStartPosition() const {
	return start_;
}

buw::Vector2d HorizontalAlignmentElement2DLine::getEndPosition() const {
	return end_;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END