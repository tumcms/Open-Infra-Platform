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
//int isCCW_; // = is counter clockwise
//carve::geom::vector<3> center_;
//
//double radiusClothoidStart_;
//double radiusClothoidEnd_;
//double clothoidparameterA_;

// CONSTRUCTOR
OpenInfraPlatform::UserInterface::SplineInterpretationElement::SplineInterpretationElement() {}

OpenInfraPlatform::UserInterface::SplineInterpretationElement::SplineInterpretationElement(
	double lengthBSpline,
	int indicator, 
	std::pair<size_t, size_t> indices)
{
	lengthBSpline_ = lengthBSpline;
	indicator_ = indicator;
	indices_ = indices;
}


// PUBLIC FUNCTIONS WITH ACCESS TO VARIABLES
void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setLengthBSpline(double lengthBSpline){
	lengthBSpline_ = lengthBSpline; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getLengthBSpline() const{
	return lengthBSpline_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setindicator(int indicator){
	indicator_ = indicator; }

int OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicator() const{
	return indicator_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndices(size_t startIndice, size_t endIndice){
	indices_.first = startIndice;
	indices_.second = endIndice; }

void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndicesStart(size_t startIndice){
	indices_.first = startIndice; }

void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndicesEnd(size_t endIndice){
	indices_.second = endIndice; }

std::pair<size_t, size_t> OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndices() const{
	return indices_; }

size_t OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicesStart() const{
	return indices_.first; }

size_t OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicesEnd() const{
	return indices_.second; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setType(std::string type){
	type_ = type; }

std::string OpenInfraPlatform::UserInterface::SplineInterpretationElement::getType() const {
	return type_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setStartpoint(carve::geom::vector<3> startpoint) {
	startpoint_ = startpoint; }

carve::geom::vector<3> OpenInfraPlatform::UserInterface::SplineInterpretationElement::getStartpoint() const {
	return startpoint_;}


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setDirection(double direction) {
	direction_ = direction; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getDirection() const {
	return direction_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setLength(double length) {
	length_ = length; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getLength() const {
	return length_;}


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setRadius(double radius) {
	radius_ = radius; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getRadius() const {
	return radius_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIsCCW(int isCCW) {
	isCCW_ = isCCW; }

int OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIsCCW() const {
	return isCCW_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setCenter(carve::geom::vector<3> center) {
	center_ = center; }

carve::geom::vector<3> OpenInfraPlatform::UserInterface::SplineInterpretationElement::getCenter() const {
	return center_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setRadiusClothoidStart(double radiusClothoidStart) {
	radiusClothoidStart_ = radiusClothoidStart; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getRadiusClothoidStart() const {
	return radiusClothoidStart_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setRadiusClothoidEnd(double radiusClothoidEnd) {
	radiusClothoidEnd_ = radiusClothoidEnd; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getRadiusClothoidEnd() const {
	return radiusClothoidEnd_; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setClothoidparameterA(double clothoidparameter) {
	clothoidparameterA_ = clothoidparameter; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getClothoidparameterA() const {
	return clothoidparameterA_; }


// PUBLIC FUNCTIONS

// PRIVATE FUNCTIONS