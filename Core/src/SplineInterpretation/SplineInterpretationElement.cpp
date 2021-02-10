/*
	Copyright (c) 2020 Technical University of Munich
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

// PRIVATE VARIABLES
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
void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setLengthBSpline(double lengthBSpline){
	lengthBSpline_ = lengthBSpline; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getLengthBSpline() const{
	return lengthBSpline_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setindicator(int indicator){
	indicator_ = indicator; }

int OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicator() const{
	return indicator_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndices(size_t startIndice, size_t endIndice){
	indices_.first = startIndice;
	indices_.second = endIndice; }

void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndicesStart(size_t startIndice){
	indices_.first = startIndice; }

void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIndicesEnd(size_t endIndice){
	indices_.second = endIndice; }

std::pair<size_t, size_t> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndices() const{
	return indices_; }

size_t OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicesStart() const{
	return indices_.first; }

size_t OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIndicesEnd() const{
	return indices_.second; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setType(std::string type){
	type_ = type; }

std::string OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getType() const {
	return type_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setStartpoint(carve::geom::vector<3> startpoint) {
	startpoint_ = startpoint; }

carve::geom::vector<3> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getStartpoint() const {
	return startpoint_;}


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setDirection(double direction) {
	direction_ = direction; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getDirection() const {
	return direction_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setLength(double length) {
	length_ = length; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getLength() const {
	return length_;}


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadius(double radius) {
	radius_ = radius; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadius() const {
	return radius_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setAngle(double angle) {
	angle_ = angle; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getAngle() const {
	return angle_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setIsCCW(int isCCW) {
	isCCW_ = isCCW; }

int OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getIsCCW() const {
	return isCCW_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setCenter(carve::geom::vector<3> center) {
	center_ = center; }

carve::geom::vector<3> OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getCenter() const {
	return center_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadiusClothoidStart(double radiusClothoidStart) {
	radiusClothoidStart_ = radiusClothoidStart; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadiusClothoidStart() const {
	return radiusClothoidStart_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setRadiusClothoidEnd(double radiusClothoidEnd) {
	radiusClothoidEnd_ = radiusClothoidEnd; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getRadiusClothoidEnd() const {
	return radiusClothoidEnd_; }


void OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::setClothoidparameterA(double clothoidparameter) {
	clothoidparameterA_ = clothoidparameter; }

double OpenInfraPlatform::Core::SplineInterpretation::SplineInterpretationElement::getClothoidparameterA() const {
	return clothoidparameterA_; }


// PUBLIC FUNCTIONS

// PRIVATE FUNCTIONS