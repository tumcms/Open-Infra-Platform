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

#include "HorizontalAlignmentElement2DClothoid.h"
#include "../../Core/Line2.h"
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/assert.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

clothoidDescription::clothoidDescription() {
	startPosition = buw::Vector2d(0.0, 0.0);
	startDirection = 0.0;
	startCurvature = 0.0;
	counterClockwise = true;
	clothoidConstant = 200;
	entry = true;
	length = 500.0;
}

clothoidDescription::clothoidDescription(const buw::Vector2d startPosition,
                                         const double startDirection,
                                         const double startCurvature,
                                         const bool counterClockwise,
                                         const double clothoidConstant,
                                         const bool entry,
                                         const double length) {
	this->startPosition = startPosition;
	this->startDirection = startDirection;
	this->startCurvature = startCurvature;
	this->counterClockwise = counterClockwise;
	this->clothoidConstant = clothoidConstant;
	this->entry = entry;
	this->length = length;
}

HorizontalAlignmentElement2DClothoid::HorizontalAlignmentElement2DClothoid(const clothoidDescription& cd)
    : startPosition_(cd.startPosition), startDirection_(cd.startDirection), counterClockwise_(cd.counterClockwise), clothoidConstant_(cd.clothoidConstant) {
	startL_ = clothoidConstant_ * clothoidConstant_ * cd.startCurvature;
	if (cd.entry)
		endL_ = startL_ + cd.length;
	else
		endL_ = buw::max(startL_ - cd.length, 0.0);
}

OpenInfraPlatform::Infrastructure::eHorizontalAlignmentType HorizontalAlignmentElement2DClothoid::getAlignmentType() const {
	return eHorizontalAlignmentType::Clothoid;
}

bool HorizontalAlignmentElement2DClothoid::genericQuery(const int id, void* result) const {
	switch (id) {
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = getStartPosition(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = getEndPosition(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI: *reinterpret_cast<buw::Vector2d*>(result) = getPiPosition(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Clockwise: *reinterpret_cast<bool*>(result) = isClockwise(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise: *reinterpret_cast<bool*>(result) = isCounterClockwise(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Length: *reinterpret_cast<double*>(result) = getLength(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart: *reinterpret_cast<double*>(result) = getStartRadius(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd: *reinterpret_cast<double*>(result) = getEndRadius(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentCurvatureStart:
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureStart: *reinterpret_cast<double*>(result) = getStartCurvature(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::CurvatureEnd: *reinterpret_cast<double*>(result) = getEndCurvature(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant: *reinterpret_cast<double*>(result) = getClothoidConstant(); break;
	case OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::AlignmentStartDirection1D: *reinterpret_cast<double*>(result) = getStartDirection(); break;
	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getPosition(const double lerpParameter) const {
	buw::Vector2d localPosition, localOffset;

	double L = startL_ + (endL_ - startL_) * lerpParameter;

	localPosition = computeLocalPosition(L);

	double angle;

	buw::Vector2d position;
	angle = computeT(startL_, clothoidConstant_);
	localOffset = localPosition - computeLocalPosition(startL_);

	if (!isEntry()) {
		angle *= -1;
		localOffset.x() *= -1;
	}

	if (!counterClockwise_) {
		angle *= -1;
		localOffset.y() *= -1;
	}

	position = startPosition_ + buw::createRotationMatrix(startDirection_ - angle) * localOffset;

	return position;
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getTangent(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getNormal(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::computeLocalPosition(const double L) const {
	buw::Vector2d localPosition;
	localPosition.x() = computeX(L, clothoidConstant_);
	localPosition.y() = computeY(L, clothoidConstant_);

	return localPosition;
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getStartPosition() const {
	return getPosition(0);
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getEndPosition() const {
	return getPosition(1);
}

buw::Vector2d HorizontalAlignmentElement2DClothoid::getPiPosition() const {
	buw::Vector2d start = getStartPosition();
	buw::Vector2d end = getEndPosition();
	buw::Vector2d pi;

	buw::Line2d l1(start, start + buw::createRotationMatrix(getStartDirection()) * buw::Vector2d(1.0, 0));
	buw::Line2d l2(end, end + buw::createRotationMatrix(getEndDirection()) * buw::Vector2d(1.0, 0));

	buw::computeIntersection(l1, l2, pi);

	return pi;
}

double HorizontalAlignmentElement2DClothoid::getStartRadius() const {
	return 1 / getStartCurvature();
}

double HorizontalAlignmentElement2DClothoid::getEndRadius() const {
	return 1 / getEndCurvature();
}

double HorizontalAlignmentElement2DClothoid::getStartCurvature() const {
	return computeC(startL_, clothoidConstant_); // *(counterClockwise_ ? 1 : -1);
}

double HorizontalAlignmentElement2DClothoid::getEndCurvature() const {
	return computeC(endL_, clothoidConstant_); // * (counterClockwise_ ? 1 : -1);
}

double HorizontalAlignmentElement2DClothoid::getStartDirection() const {
	return startDirection_;
}

double HorizontalAlignmentElement2DClothoid::getEndDirection() const {
	return startDirection_ + (computeT(endL_, clothoidConstant_) - computeT(startL_, clothoidConstant_)) * (counterClockwise_ ? 1 : -1) * (isEntry() ? 1 : -1);
}

double HorizontalAlignmentElement2DClothoid::getClothoidConstant() const {
	return clothoidConstant_;
}

double HorizontalAlignmentElement2DClothoid::getLength() const {
	return abs(endL_ - startL_);
}

bool HorizontalAlignmentElement2DClothoid::isEntry() const {
	return startL_ < endL_;
}

bool HorizontalAlignmentElement2DClothoid::isCounterClockwise() const {
	return counterClockwise_;
}

bool HorizontalAlignmentElement2DClothoid::isClockwise() const {
	return !counterClockwise_;
}

double HorizontalAlignmentElement2DClothoid::computeC(const double L, const double A) {
	return L / (A * A);
}

double HorizontalAlignmentElement2DClothoid::computeT(const double L, const double A) {
	return L * L / (2 * A * A);
}

double HorizontalAlignmentElement2DClothoid::computeX(const double L, const double A) {
	double x = L;
	const int iterations = 5;

	for (int i = 1; i < iterations + 1; i++) {
		double sign = i % 2 == 0 ? 1 : -1;

		double L_exponent = 5 + (i - 1) * 4;
		double A_exponent = i * 4;
		double factor = buw::factorial(2 * i) * std::pow(2.0, 2 * i) * (5 + (i - 1) * 4);

		x += sign * std::pow(L, L_exponent) / (factor * std::pow(A, A_exponent));
	}

	return x;
}

double HorizontalAlignmentElement2DClothoid::computeY(const double L, const double A) {
	double y = 0;
	const int iterations = 5;

	for (int i = 0; i < iterations; i++) {
		double sign = i % 2 == 0 ? 1 : -1;

		double L_exponent = 3 + i * 4;
		double A_exponent = 2 + i * 4;
		double factor = buw::factorial(2 * i + 1) * std::pow(2.0, i * 2) * 2 * (A_exponent + 1);

		y += sign * std::pow(L, L_exponent) / (factor * std::pow(A, A_exponent));
	}

	return y;
}

double HorizontalAlignmentElement2DClothoid::computeStartDirection(const buw::Vector2d& start, const buw::Vector2d& pi) {
	return buw::calculateAngleBetweenVectors(buw::Vector2d(1, 0), buw::Vector2d(pi - start));
}

double HorizontalAlignmentElement2DClothoid::computeEndDirection(const buw::Vector2d& pi, const buw::Vector2d& end) {
	return buw::calculateAngleBetweenVectors(buw::Vector2d(1, 0), buw::Vector2d(end - pi));
}

double HorizontalAlignmentElement2DClothoid::computeEntry(const double startCurvature, const double endCurvature) {
	return startCurvature < endCurvature;
}

double HorizontalAlignmentElement2DClothoid::computeClothoidConstant(const double length, const double startCurvature, const double endCurvature) {
	if (computeEntry(startCurvature, endCurvature))
		return sqrt(length / (endCurvature - startCurvature));
	else
		return sqrt(length / (startCurvature - endCurvature));
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END