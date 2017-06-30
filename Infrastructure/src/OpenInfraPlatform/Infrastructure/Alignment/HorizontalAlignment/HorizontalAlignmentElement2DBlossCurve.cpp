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

#include "HorizontalAlignmentElement2DBlossCurve.h"
#include <BlueFramework/Core/Math/Matrix.h>
#include "../../Core/Line2.h"
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/assert.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

blossDescription::blossDescription() {
	startPosition = buw::Vector2d(0.0, 0.0);
	startDirection = 0.0;
	counterClockwise = true;
	entry = true;
	length = 500.0;
	radius = 100.0;
}

blossDescription::blossDescription(const buw::Vector2d startPosition,
	const double startDirection,
	const bool counterClockwise,
	const bool entry,
	const double length,
	const double radius) :
	startPosition(startPosition),
	startDirection(startDirection),
	counterClockwise(counterClockwise),
	entry(entry),
	length(length),
	radius(radius) {
}

HorizontalAlignmentElement2DBlossCurve::HorizontalAlignmentElement2DBlossCurve(const blossDescription& bd) :
	startPosition_(bd.startPosition),
	startDirection_(bd.startDirection),
	counterClockwise_(bd.counterClockwise),
	isEntry_(bd.entry),
	L(bd.length),
	R(bd.radius)
{
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getPosition(const double lerpParameter) const
{
	double startL = isEntry_ ? 0 : L;
	double endL = isEntry_ ? L : 0;

	double l = startL + (endL - startL) * lerpParameter;

	buw::Vector2d localOffset;
	localOffset = computeLocalPosition(l) - computeLocalPosition(startL);

	double angle = computeLocalT(startL);

	if (!isEntry_)
	{
		localOffset.x() *= -1;
		angle *= -1;
	}

	if (!counterClockwise_)
	{
		localOffset.y() *= -1;
		angle *= -1;
	}

	buw::Vector2d position;
	position = startPosition_ + buw::createRotationMatrix(startDirection_ - angle) * localOffset;

	return position;
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getTangent(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getNormal(const double lerpParameter) const
{
	throw buw::NotImplementedYetException("TODO");
}

double HorizontalAlignmentElement2DBlossCurve::getCurvature(const double lerpParameter) const
{
	double startL = isEntry_ ? 0 : L;
	double endL = isEntry_ ? L : 0;

	double l = startL + (endL - startL) * lerpParameter;
	return computeLocalC(l);
}

eHorizontalAlignmentType
HorizontalAlignmentElement2DBlossCurve::getAlignmentType() const
{
	return eHorizontalAlignmentType::Bloss;
}

bool HorizontalAlignmentElement2DBlossCurve::genericQuery(const int id, void* result) const
{
	switch (id) {
	case eAlignmentElementQueryId::StartPosition: *reinterpret_cast<buw::Vector2d*>(result) = getStartPosition(); break;
	case eAlignmentElementQueryId::EndPosition: *reinterpret_cast<buw::Vector2d*>(result) = getEndPosition(); break;
	case eAlignmentElementQueryId::PI: *reinterpret_cast<buw::Vector2d*>(result) = getPiPosition(); break;
	case eAlignmentElementQueryId::Clockwise: *reinterpret_cast<bool*>(result) = isClockwise(); break;
	case eAlignmentElementQueryId::Counterclockwise: *reinterpret_cast<bool*>(result) = isCounterClockwise(); break;
	case eAlignmentElementQueryId::Length: *reinterpret_cast<double*>(result) = getLength(); break;
	case eAlignmentElementQueryId::RadiusStart: *reinterpret_cast<double*>(result) = getStartRadius(); break;
	case eAlignmentElementQueryId::RadiusEnd: *reinterpret_cast<double*>(result) = getEndRadius(); break;
	case eAlignmentElementQueryId::AlignmentCurvatureStart:
	case eAlignmentElementQueryId::CurvatureStart: *reinterpret_cast<double*>(result) = getStartCurvature(); break;
	case eAlignmentElementQueryId::CurvatureEnd: *reinterpret_cast<double*>(result) = getEndCurvature(); break;
	case eAlignmentElementQueryId::AlignmentStartDirection1D: *reinterpret_cast<double*>(result) = getStartDirection(); break;
	default: BLUE_ASSERT(false, "Invalid id."); return false;
	}

	return true;
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getStartPosition() const
{
	return getPosition(0);
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getEndPosition() const
{
	return getPosition(1);
}

buw::Vector2d HorizontalAlignmentElement2DBlossCurve::getPiPosition() const {
	buw::Vector2d start = getStartPosition();
	buw::Vector2d end = getEndPosition();
	buw::Vector2d pi;

	buw::Line2d l1(start, start + buw::createRotationMatrix(getStartDirection()) * buw::Vector2d(1.0, 0));
	buw::Line2d l2(end, end + buw::createRotationMatrix(getEndDirection()) * buw::Vector2d(1.0, 0));

	buw::computeIntersection(l1, l2, pi);

	return pi;
}

double HorizontalAlignmentElement2DBlossCurve::getStartRadius() const {
	return 1 / getStartCurvature();
}

double HorizontalAlignmentElement2DBlossCurve::getEndRadius() const {
	return 1 / getEndCurvature();
}

double HorizontalAlignmentElement2DBlossCurve::getStartCurvature() const {
	return computeLocalC(isEntry_ ? 0 : L);
}

double HorizontalAlignmentElement2DBlossCurve::getEndCurvature() const {
	return computeLocalC(isEntry_ ? L : 0);
}

double HorizontalAlignmentElement2DBlossCurve::getStartDirection() const {
	return startDirection_;
}

double HorizontalAlignmentElement2DBlossCurve::getEndDirection() const {
	return startDirection_ + computeLocalT(L) * (counterClockwise_ ? 1 : -1);
}

double HorizontalAlignmentElement2DBlossCurve::getLength() const
{
	return L;
}

bool HorizontalAlignmentElement2DBlossCurve::isEntry() const {
	return isEntry_;
}

bool HorizontalAlignmentElement2DBlossCurve::isCounterClockwise() const {
	return counterClockwise_;
}

bool HorizontalAlignmentElement2DBlossCurve::isClockwise() const {
	return !counterClockwise_;
}

double HorizontalAlignmentElement2DBlossCurve::computeStartDirection(const buw::Vector2d& start, const buw::Vector2d& pi)
{
	return buw::calculateAngleBetweenVectors(buw::Vector2d(1, 0), buw::Vector2d(pi - start));
}
double HorizontalAlignmentElement2DBlossCurve::computeEndDirection(const buw::Vector2d& pi, const buw::Vector2d& end)
{
	return buw::calculateAngleBetweenVectors(buw::Vector2d(1, 0), buw::Vector2d(end - pi));
}
void HorizontalAlignmentElement2DBlossCurve::computeEntry(const double startRadius, const double endRadius, bool& entry, double& radius)
{
	bool startInf = startRadius == std::numeric_limits<double>::infinity();
	bool endInf = endRadius == std::numeric_limits<double>::infinity();
	assert(startInf != endInf);

	if (startInf)
	{
		entry = true;
		radius = endRadius;
		return;
	}
	else
	{
		entry = false;
		radius = startRadius;
		return;
	}
}


// calculated with matlab (docs/approxCurve.m)
// k = 3 * l ^ 2 / (R*L ^ 2) - 2 * l ^ 3 / (R*L ^ 3)
// [x, y, X, Y] = approxCurve(k, 4)
double HorizontalAlignmentElement2DBlossCurve::computeX(const double L, const double R, const double l)
{
	return  l - pow(l,7) / (14 * pow(L,4) * pow(R,2)) + pow(l,8) / (16 * pow(L,5) * pow(R,2)) - pow(l,9) / (72 * pow(L,6) * pow(R,2)) + pow(l,13) / (312 * pow(L,8) * pow(R,4)) - pow(l,14) / (168 * pow(L,9) * pow(R,4)) + pow(l,15) / (240 * pow(L,10) * pow(R,4)) - pow(l,16) / (768 * pow(L,11) * pow(R,4)) + pow(l,17) / (6528 * pow(L,12) * pow(R,4)) - pow(l,19) / (13680 * pow(L,12) * pow(R,6)) + pow(l,20) / (4800 * pow(L,13) * pow(R,6)) - pow(l,21) / (4032 * pow(L,14) * pow(R,6)) + pow(l,22) / (6336 * pow(L,15) * pow(R,6)) - pow(l,23) / (17664 * pow(L,16) * pow(R,6)) + pow(l,24) / (92160 * pow(L,17) * pow(R,6)) - pow(l,25) / (1152000 * pow(L,18) * pow(R,6));
}
double HorizontalAlignmentElement2DBlossCurve::computeY(const double L, const double R, const double l)
{
	return pow(l,4) / (4 * pow(L,2) * R) - pow(l,5) / (10 * pow(L,3) * R) - pow(l,10) / (60 * pow(L,6) * pow(R,3)) + pow(l,11) / (44 * pow(L,7) * pow(R,3)) - pow(l,12) / (96 * pow(L,8) * pow(R,3)) + pow(l,13) / (624 * pow(L,9) * pow(R,3)) + pow(l,16) / (1920 * pow(L,10) * pow(R,5)) - pow(l,17) / (816 * pow(L,11) * pow(R,5)) + pow(l,18) / (864 * pow(L,12) * pow(R,5)) - pow(l,19) / (1824 * pow(L,13) * pow(R,5)) + pow(l,20) / (7680 * pow(L,14) * pow(R,5)) - pow(l,21) / (80640 * pow(L,15) * pow(R,5)) - pow(l,22) / (110880 * pow(L,14) * pow(R,7)) + pow(l,23) / (33120 * pow(L,15) * pow(R,7)) - pow(l,24) / (23040 * pow(L,16) * pow(R,7)) + pow(l,25) / (28800 * pow(L,17) * pow(R,7)) - pow(l,26) / (59904 * pow(L,18) * pow(R,7)) + pow(l,27) / (207360 * pow(L,19) * pow(R,7)) - pow(l,28) / (1290240 * pow(L,20) * pow(R,7)) + pow(l,29) / (18708480 * pow(L,21) * pow(R,7));
}

double HorizontalAlignmentElement2DBlossCurve::computeT(const double L, const double R, const double l)
{
	return pow(l, 3) / (R * pow(L, 2)) - pow(l, 4) / (2 * R * pow(L, 3));
}
double HorizontalAlignmentElement2DBlossCurve::computeC(const double L, const double R, const double l)
{
	return 3 * pow(l, 2) / (R * pow(L, 2)) - 2 * pow(l, 3) / (R * pow(L, 3));
}


buw::Vector2d HorizontalAlignmentElement2DBlossCurve::computeLocalPosition(double l) const
{
	double X = computeX(L, R, l);
	double Y = computeY(L, R, l);

	return buw::Vector2d(X, Y);
}

double HorizontalAlignmentElement2DBlossCurve::computeLocalT(const double l) const
{
	return computeT(L, R, l);
}

double HorizontalAlignmentElement2DBlossCurve::computeLocalC(const double l) const
{
	return computeC(L, R, l);
}


OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END