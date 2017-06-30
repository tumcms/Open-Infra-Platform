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

#include "HorizontalAlignmentElement2DClothoid_old.h"

#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/assert.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

HorizontalAlignmentElement2DClothoid_old::HorizontalAlignmentElement2DClothoid_old(const buw::Vector2d& start,
                                                                                   const buw::Vector2d& end,
                                                                                   const buw::Vector2d& pi,
                                                                                   const double length,
                                                                                   const double radiusStart,
                                                                                   const double radiusEnd,
                                                                                   const bool clockwise)
    : start_(start), end_(end), pi_(pi), length_(length), startCurvature_(1 / radiusStart), endCurvature_(1 / radiusEnd), clockwise_(clockwise) {
	// std::cout << "length=" << length << " dirStart=" << calculateStartTangentAngle() << " dirEnd=" << calculateEndTangentAngle() << " globalAngle=" << calculateGlobalRotation()
	// << std::endl;
	// std::cout << "length=" << length << " longTangent=" << calculateLongTangent() << " shortTangent=" << calculateShortTangent() << std::endl;
	// std::cout << "length=" << length << " totalX=" << calculateTotalX() << " totalY=" << calculateTotalY() << std::endl;
}

HorizontalAlignmentElement2DClothoid_old::HorizontalAlignmentElement2DClothoid_old(const buw::Vector2d& start,
                                                                                   const double direction,
                                                                                   const double startCurvature,
                                                                                   const double endCurvature,
                                                                                   const double length)
    : start_(start), startCurvature_(startCurvature), endCurvature_(endCurvature), length_(length), clockwise_(false) {
	// ToDo --------------------------------------------------------------------------------------------------
	// - Convert RoadXML Parameter into LandXML within this constructor
	// - Does not work yet!!!---------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------

	// get clothoid constant
	double A = getClothoidConstant();
	double signY = 1;

	// flip clothoid vertical if clockwise or endCurvature<startCurvature
	if ((clockwise_ && startCurvature < endCurvature) || (!clockwise_ && endCurvature < startCurvature))
		signY = -1;
	else
		signY = 1;

	// calculate length on clothoid at start- and endpoint
	double smallerLength = A * A * startCurvature;
	double greaterLength = A * A * endCurvature;

	// calculate clothoid end coordinates in local system
	double localEndX = computeX(greaterLength, A) - computeX(smallerLength, A);
	double localEndY = signY * (computeY(greaterLength, A) - computeY(smallerLength, A));

	// create rotation matrix from direction
	buw::Matrix22d rotation = buw::createRotationMatrix(direction);

	// rotate point
	buw::Vector2d tP = rotation * buw::Vector2d(localEndX, localEndY);

	// output global coordinates on clothoid intersection point
	if (startCurvature < endCurvature)
		end_ = tP + start;
	else if (endCurvature < startCurvature)
		end_ = start - tP;

	throw std::runtime_error("Not implemented yet."); // the above code does not work yet
}

double HorizontalAlignmentElement2DClothoid_old::getLength() const {
	return length_;
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::getPosition(const double lerpParameter) const {
	BLUE_ASSERT(startCurvature_ != endCurvature_, "Start curvature is equal to end curvature.");

	if (startCurvature_ == endCurvature_) {
		throw buw::Exception("Start curvature is equal to end curvature!");
	}

	// get clothoid constant
	double A = getClothoidConstant();
	double signY = 1;

	// flip clothoid vertical if clockwise or endCurvature<startCurvature
	if ((clockwise_ && startCurvature_ < endCurvature_) || (!clockwise_ && endCurvature_ < startCurvature_))
		signY = -1;
	else
		signY = 1;

	// calculate length on clothoid at start- and endpoint
	double smallerLength = A * A * startCurvature_;
	double greaterLength = A * A * endCurvature_;

	// calculate length on clothoid at interpolation point
	double currentLength = buw::lerp(smallerLength, greaterLength, lerpParameter);

	// calculate clothoid coordinates in local system
	double localX = computeX(currentLength, A) - computeX(smallerLength, A);
	double localY = signY * (computeY(currentLength, A) - computeY(smallerLength, A));

	// calculate the global rotation angle and create rotation matrix
	buw::Matrix22d rotation = buw::createRotationMatrix<double>(calculateGlobalRotation());

	// rotate point with global rotation angle
	buw::Vector2d tP = rotation * buw::Vector2d(localX, localY);

	// output global coordinates on clothoid intersection point
	if (startCurvature_ < endCurvature_)
		return tP + start_;
	else if (endCurvature_ < startCurvature_)
		return start_ - tP;
	else
		throw std::runtime_error("Invalid clothoid curvature.");
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::getTangent(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::getNormal(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

double HorizontalAlignmentElement2DClothoid_old::getClothoidConstant() const {
	double clothidConstant = 0;

	if (startCurvature_ < endCurvature_) // R1>R2
	{
		clothidConstant = std::sqrt(length_ / (endCurvature_ - startCurvature_));
	} else if (startCurvature_ > endCurvature_) // R1<R2
	{
		clothidConstant = std::sqrt(length_ / (startCurvature_ - endCurvature_));
	} else {
		throw buw::Exception("Invalid radius value!");
	}

	return clothidConstant;
}

buw::radiand HorizontalAlignmentElement2DClothoid_old::calculateStartTangentAngle() const {
	buw::Vector2d startTangent = pi_ - start_;

	if (startTangent == buw::Vector2d(0, 0))
		return 0.0; // Invalid vector

	// calculate angle to north (LandXML definition)
	return buw::calculateAngleBetweenVectors(buw::Vector2d(0, 1), startTangent);
}

buw::radiand HorizontalAlignmentElement2DClothoid_old::calculateEndTangentAngle() const {
	buw::Vector2d endTangent = end_ - pi_;

	if (endTangent == buw::Vector2d(0, 0))
		return 0.0; // Invalid vector

	// calculate angle to north (LandXML definition)
	return buw::calculateAngleBetweenVectors(buw::Vector2d(0, 1), endTangent);
}

double HorizontalAlignmentElement2DClothoid_old::calculateLongTangent() const {
	buw::Vector2d v1 = pi_ - start_;
	buw::Vector2d v2 = pi_ - end_;

	return std::max(v1.norm(), v2.norm());
}

double HorizontalAlignmentElement2DClothoid_old::calculateShortTangent() const {
	buw::Vector2d v1 = pi_ - start_;
	buw::Vector2d v2 = pi_ - end_;

	return std::min(v1.norm(), v2.norm());
}

double HorizontalAlignmentElement2DClothoid_old::calculateTotalX() const {
	// get clothoid constant
	double A = getClothoidConstant();

	// calculate length on clothoid at start- and endpoint
	double smallerLength = A * A * startCurvature_;
	double greaterLength = A * A * endCurvature_;

	// calculate clothoid x-coordinate in local system
	double localEndX = computeX(greaterLength, A) - computeX(smallerLength, A);

	return abs(localEndX);
}

double HorizontalAlignmentElement2DClothoid_old::calculateTotalY() const {
	// get clothoid constant
	double A = getClothoidConstant();

	// calculate length on clothoid at start- and endpoint
	double smallerLength = A * A * startCurvature_;
	double greaterLength = A * A * endCurvature_;

	// calculate clothoid y-coordinate in local system
	double localEndY = computeY(greaterLength, A) - computeY(smallerLength, A);

	return abs(localEndY);
}

OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType HorizontalAlignmentElement2DClothoid_old::getAlignmentType() const {
	return eHorizontalAlignmentType::Clothoid;
}

bool HorizontalAlignmentElement2DClothoid_old::genericQuery(const int id, void* result) const {
	switch (id) {
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = start_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = end_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI: *reinterpret_cast<buw::Vector2d*>(result) = pi_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise: *reinterpret_cast<bool*>(result) = clockwise_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise: *reinterpret_cast<bool*>(result) = !clockwise_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length: *reinterpret_cast<double*>(result) = length_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart: *reinterpret_cast<double*>(result) = 1.0 / startCurvature_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd: *reinterpret_cast<double*>(result) = 1.0 / endCurvature_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentCurvatureStart: *reinterpret_cast<double*>(result) = startCurvature_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureStart: *reinterpret_cast<double*>(result) = startCurvature_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd: *reinterpret_cast<double*>(result) = endCurvature_; break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant: *reinterpret_cast<double*>(result) = getClothoidConstant(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentStartDirection1D: {
		buw::Vector2d xAxis(1.0f, 0.0f);
		buw::Vector2d dir = pi_ - start_;
		double angle = buw::calculateAngleBetweenVectors(xAxis, dir);
		*reinterpret_cast<double*>(result) = angle;
	} break;
	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

double HorizontalAlignmentElement2DClothoid_old::sgnEven(int x) {
	if (x % 2 == 0)
		return 1.0;
	else
		return -1.0;
}

double HorizontalAlignmentElement2DClothoid_old::computeX(const double L, const double A) {
	double x = L;
	const int iterations = 5;

	for (int i = 1; i < iterations + 1; i++) {
		double sign = sgnEven(i);

		double L_exponent = 5 + (i - 1) * 4;
		double A_exponent = i * 4;
		double factor = buw::factorial(2 * i) * std::pow(2.0, 2 * i) * (5 + (i - 1) * 4);

		x += sign * std::pow(L, L_exponent) / (factor * std::pow(A, A_exponent));
	}

	return x;
}

double HorizontalAlignmentElement2DClothoid_old::computeY(const double L, const double A) {
	double y = 0;
	const int iterations = 5;

	for (int i = 0; i < iterations; i++) {
		double sign = sgnEven(i);

		double L_exponent = 3 + i * 4;
		double A_exponent = 2 + i * 4;
		double factor = buw::factorial(2 * i + 1) * std::pow(2.0, i * 2) * 2 * (A_exponent + 1);

		y += sign * std::pow(L, L_exponent) / (factor * std::pow(A, A_exponent));
	}

	return y;
}

buw::radiand HorizontalAlignmentElement2DClothoid_old::calculateGlobalRotation() const {
	// get clothoid constant
	double A = getClothoidConstant();

	double signY = 1;

	// flip clothoid vertical if clockwise or endCurvature<startCurvature
	if ((clockwise_ && startCurvature_ < endCurvature_) || (!clockwise_ && endCurvature_ < startCurvature_))
		signY = -1;
	else
		signY = 1;

	// calculate length on clothoid at start- and endpoint
	double smallerLength = A * A * startCurvature_;
	double greaterLength = A * A * endCurvature_;

	// calculate clothoid end coordinates in local system
	double localEndX = computeX(greaterLength, A) - computeX(smallerLength, A);
	double localEndY = signY * (computeY(greaterLength, A) - computeY(smallerLength, A));

	// transfer coordinates in global system
	buw::Vector2d calculatedEnd = buw::Vector2d(localEndX, localEndY) + start_;

	// calculate angle between expected StartEnd and calculated StartEnd vector
	double globalRotationAngle = buw::constantsd::pi() * 2 - buw::calculateAngleBetweenVectors(buw::Vector2d(end_ - start_), buw::Vector2d(calculatedEnd - start_));

	// rotate by 180° if endCurvature<startCurvature
	if (endCurvature_ < startCurvature_)
		globalRotationAngle -= buw::constantsd::pi();

	return globalRotationAngle;
}

double HorizontalAlignmentElement2DClothoid_old::computeEndRadius(const double clothoidConstant, const double segmentLength, const double radiusStart, const bool isEntry) {
	double radiusEnd = std::numeric_limits<double>::infinity();
	const double epsilon = 0.001;

	if (std::abs(clothoidConstant * clothoidConstant / segmentLength - radiusStart) > epsilon) {
		if (isEntry) {
			if (radiusStart != std::numeric_limits<double>::infinity()) {
				double Ls = clothoidConstant * clothoidConstant / radiusStart;

				return clothoidConstant * clothoidConstant / (Ls + segmentLength);
			} else
				return clothoidConstant * clothoidConstant / segmentLength;
		} else {
			if (radiusStart != std::numeric_limits<double>::infinity()) {
				if (isEntry) {
					double Ls = clothoidConstant * clothoidConstant / radiusStart;

					return clothoidConstant * clothoidConstant / (Ls + segmentLength);
				} else {
					double Ls = clothoidConstant * clothoidConstant / radiusStart;

					return clothoidConstant * clothoidConstant / (Ls - segmentLength);
				}
			} else {
				return clothoidConstant * clothoidConstant / segmentLength;
			}
		}
	}

	return radiusEnd;
}

buw::radiand computeTau(const double segmentLength, const double clothoidConstant) {
	const double& A = clothoidConstant;
	const double& L = segmentLength;

	return (L * L) / (2 * A * A);
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::computeEndPoint(const buw::Vector2d& startPoint,
                                                                        const buw::radiand startDirection,
                                                                        const double segmentLength,
                                                                        const double startRadius,
                                                                        const bool isCcw,
                                                                        const bool isEntry,
                                                                        const double clothoidConstant) {
	const double& A = clothoidConstant;
	const double& L = segmentLength;
	const bool clockwise = !isCcw;
	const double endRadius = computeEndRadius(A, L, startRadius, isEntry);

	double startCurvature = startRadius != std::numeric_limits<double>::infinity() ? 1.0 / startRadius : 0.0f;
	double endCurvature = endRadius != std::numeric_limits<double>::infinity() ? 1.0 / endRadius : 0.0f;

	double fullSpiralLength = computeFulllLength(isEntry, A, startRadius, L);
	double turnedAngle = computeTurnedAngle(segmentLength, fullSpiralLength, A);
	double endDirection = computeEndDirection(startDirection, isCcw, turnedAngle);
	double spiralOriginProjection = computeOriginProjection(isEntry, segmentLength, clothoidConstant, fullSpiralLength);
	double spiralOriginOffset = computeOriginOffset(isEntry, segmentLength, clothoidConstant, fullSpiralLength, isCcw);
	double endPointProjection = buw::HorizontalAlignmentElement2DClothoid_old::computeEndPointProjection(isEntry, segmentLength, clothoidConstant, fullSpiralLength);
	double spiralOriginDirection = computeOriginDirection(isEntry, startCurvature, endCurvature, startDirection, endDirection, fullSpiralLength, clothoidConstant, isCcw);
	double endPointOffset = computeEndPointOffset(isEntry, fullSpiralLength, clothoidConstant, isCcw, segmentLength);
	double originEasting = computeOriginEasting(startPoint.x(), spiralOriginProjection, spiralOriginDirection, spiralOriginOffset);
	double originNorthing = computeOriginNorthing(startPoint.y(), spiralOriginProjection, spiralOriginDirection, spiralOriginOffset);

	double endPoint_x = originEasting + endPointProjection * std::cos(spiralOriginDirection) - endPointOffset * std::sin(spiralOriginDirection);
	double endPoint_y = originNorthing + endPointProjection * std::sin(spiralOriginDirection) + endPointOffset * std::cos(spiralOriginDirection);

	return buw::Vector2d(endPoint_x, endPoint_y);
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::getStartPosition() const {
	return start_;
}

buw::Vector2d HorizontalAlignmentElement2DClothoid_old::getEndPosition() const {
	return end_;
}

double
HorizontalAlignmentElement2DClothoid_old::computeOriginNorthing(const double northing, const double originProjection, const double originDirection, const double originOffset) {
	return northing + originProjection * std::sin(originDirection) + originOffset * std::cos(originDirection);
}

double
HorizontalAlignmentElement2DClothoid_old::computeOriginEasting(const double easting, const double originProjection, const double originDirection, const double originOffset) {
	return easting + originProjection * std::cos(originDirection) - originOffset * std::sin(originDirection);
}

double HorizontalAlignmentElement2DClothoid_old::computeEndPointOffset(const bool isEntry,
                                                                       const double fullSpiralLength,
                                                                       const double clothoidConstant,
                                                                       const bool isCcw,
                                                                       const double segmentLength) {
	if (isEntry) {
		return computeY(fullSpiralLength, clothoidConstant) * (isCcw ? 1.0 : -1.0);
	} else {
		return computeY(fullSpiralLength - segmentLength, clothoidConstant) * (isCcw ? 1.0 : -1.0);
	}
}

double HorizontalAlignmentElement2DClothoid_old::computeOriginDirection(const bool isEntry,
                                                                        const double startCurvature,
                                                                        const double endCurvature,
                                                                        const double startDirection,
                                                                        const double endDirection,
                                                                        const double fullSpiralLength,
                                                                        const double clothoidConstant,
                                                                        const bool isCcw) {
	if (isEntry) {
		if (startCurvature == 0.0) {
			return startDirection;
		} else {
			return endDirection - fullSpiralLength * fullSpiralLength / (clothoidConstant * clothoidConstant * 2.0) * (isCcw ? 1.0 : -1.0);
		}
	} else {
		if (endCurvature == 0.0) {
			return endDirection;
		} else {
			return startDirection + fullSpiralLength * fullSpiralLength / (clothoidConstant * clothoidConstant * 2.0) * (isCcw ? 1.0 : -1.0);
		}
	}
}

double HorizontalAlignmentElement2DClothoid_old::computeEndPointProjection(const bool isEntry, const double segmentLenght, const double clothoidConstant, double fullSpiralLength) {
	if (isEntry) {
		return computeX(fullSpiralLength, clothoidConstant);
	} else {
		return -computeX(fullSpiralLength - segmentLenght, clothoidConstant);
	}
}

double HorizontalAlignmentElement2DClothoid_old::computeOriginOffset(const bool isEntry,
                                                                     const double segmentLenght,
                                                                     const double clothoidConstant,
                                                                     double fullSpiralLength,
                                                                     const bool isCcw) {
	if (isEntry) {
		return computeY(fullSpiralLength - segmentLenght, clothoidConstant) * (isCcw ? -1.0 : 1.0);
	} else {
		return computeY(fullSpiralLength, clothoidConstant) * (isCcw ? -1.0 : 1.0);
	}
}

double HorizontalAlignmentElement2DClothoid_old::computeOriginProjection(const bool isEntry, const double segmentLenght, const double clothoidConstant, double fullSpiralLength) {
	if (isEntry) {
		return -computeX(fullSpiralLength - segmentLenght, clothoidConstant);
	} else {
		return computeX(fullSpiralLength, clothoidConstant);
	}
}

double HorizontalAlignmentElement2DClothoid_old::computeFulllLength(const bool isEntry, const double& A, const double startRadius, const double& L) {
	double fullSpiralLength = 0.0;

	if (isEntry == false) {
		fullSpiralLength = A * A / startRadius;
	} else {
		if (isEntry == true) {
			BLUE_ASSERT(startRadius >= 0.0, "Invalid radius.");

			if (startRadius > 0) {
				fullSpiralLength = A * A / startRadius + L;
			} else {
				fullSpiralLength = L;
			}
		} else {
			fullSpiralLength = 0.0;
		}
	}

	return fullSpiralLength;
}

double HorizontalAlignmentElement2DClothoid_old::computeTurnedAngle(const double segmentLenght, double fullSpiralLength, const double clothoidConstant) {
	return segmentLenght * (2.0 * fullSpiralLength - segmentLenght) / (2.0 * clothoidConstant * clothoidConstant);
}

double HorizontalAlignmentElement2DClothoid_old::computeEndDirection(const buw::radiand startDirection, const bool isCcw, const double turnedAngle) {
	return startDirection + turnedAngle * (isCcw ? 1.0 : -1.0);
}

double HorizontalAlignmentElement2DClothoid_old::getEndCurvature() const {
	return endCurvature_ * (clockwise_ ? -1 : 1);
}

double HorizontalAlignmentElement2DClothoid_old::getStartCurvature() const {
	return startCurvature_ * (clockwise_ ? -1 : 1);
}

double HorizontalAlignmentElement2DClothoid_old::computeEndCurvature(const double radiusEnd) {
	double endCurvature = 0.0;

	if (radiusEnd != std::numeric_limits<double>::infinity()) {
		endCurvature = 1.0 / radiusEnd;
	} else {
		endCurvature = 0.0;
	}

	return endCurvature;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END