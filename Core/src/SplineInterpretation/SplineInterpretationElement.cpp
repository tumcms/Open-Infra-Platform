/*
	Copyright (c) 2021 Technical University of Munich
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

#include "SplineInterpretationElement.h"

// PRIVATE VARIABLES (declared in header file)
// preset during element search
//double lengthBSpline_;
//int indicator_;
//std::pair<size_t, size_t> indices_;
//
// final element parameters
//std::string type_;
//carve::geom::vector<3> startpoint_;
//double direction_;
//double length_;
//
//double radius_;
//double angle_;
//int isCCW_; // = is counter clockwise
//carve::geom::vector<3> center_;
//
//double radiusClothoidStart_;
//double radiusClothoidEnd_;
//double clothoidparameterA_;

// CONSTRUCTOR
OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::SplineInterpretationElement() {}

OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::SplineInterpretationElement(
	double lengthBSpline,
	int indicator, 
	std::pair<size_t, size_t> indices)
{
	lengthBSpline_ = lengthBSpline;
	indicator_ = indicator;
	indices_ = indices;
}


// PUBLIC FUNCTIONS WITH ACCESS TO VARIABLES
void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setLengthBSpline(const double lengthBSpline) noexcept(true) {
	lengthBSpline_ = lengthBSpline; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getLengthBSpline() const noexcept(true) {
	return lengthBSpline_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setindicator(const int indicator) noexcept(true) {
	indicator_ = indicator; }

int OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicator() const noexcept(true) {
	return indicator_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndices(size_t startIndice, size_t endIndice) noexcept(true) {
	indices_.first = startIndice;
	indices_.second = endIndice; }

void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndicesStart(const size_t startIndice) noexcept(true) {
	indices_.first = startIndice; }

void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndicesEnd(const size_t endIndice) noexcept(true) {
	indices_.second = endIndice; }

std::pair<size_t, size_t> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndices() const noexcept(true) {
	return indices_; }

size_t OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicesStart() const noexcept(true) {
	return indices_.first; }

size_t OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicesEnd() const noexcept(true) {
	return indices_.second; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setType(const std::string type) noexcept(true) {
	type_ = type; }

std::string OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getType() const noexcept(true) {
	return type_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setStartpoint(const carve::geom::vector<3>& startpoint) noexcept(true) {
	startpoint_ = startpoint; }

carve::geom::vector<3> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getStartpoint() const noexcept(true) {
	return startpoint_;}


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setDirection(const double direction) noexcept(true) {
	direction_ = direction; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getDirection(bool inDegree) const noexcept(true) {
	return direction_ * (inDegree ? (180.0 / M_PI) : 1.0); }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setLength(const double length) noexcept(true) {
	length_ = length; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getLength() const noexcept(true) {
	return length_;}


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadius(const double radius) noexcept(true) {
	radius_ = radius; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadius() const noexcept(true) {
	return radius_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setAngle(const double angle) noexcept(true) {
	angle_ = angle; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getAngle(bool inDegree) const noexcept(true) {
	return angle_ * (inDegree ? (180.0 / M_PI) : 1.0); }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIsCCW(const int isCCW) noexcept(true) {
	isCCW_ = isCCW; }

bool OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIsCCW() const noexcept(true) {
	return isCCW_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setCenter(const carve::geom::vector<3>& center) noexcept(true) {
	center_ = center; }

carve::geom::vector<3> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getCenter() const noexcept(true) {
	return center_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadiusClothoidStart(const double radiusClothoidStart) noexcept(true) {
	radiusClothoidStart_ = radiusClothoidStart; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadiusClothoidStart() const noexcept(true) {
	return radiusClothoidStart_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadiusClothoidEnd(const double radiusClothoidEnd) noexcept(true) {
	radiusClothoidEnd_ = radiusClothoidEnd; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadiusClothoidEnd() const noexcept(true) {
	return radiusClothoidEnd_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setClothoidparameterA(const double clothoidparameter) noexcept(true) {
	clothoidparameterA_ = clothoidparameter; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getClothoidparameterA() const noexcept(true) {
	return clothoidparameterA_; }


// PUBLIC FUNCTIONS

// PRIVATE FUNCTIONS