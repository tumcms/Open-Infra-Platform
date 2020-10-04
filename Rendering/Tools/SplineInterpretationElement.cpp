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
// double length;
// int indicator;
// std::pair<size_t, size_t> indices;

// CONSTRUCTOR
OpenInfraPlatform::UserInterface::SplineInterpretationElement::SplineInterpretationElement() {}

OpenInfraPlatform::UserInterface::SplineInterpretationElement::SplineInterpretationElement(
	double _length, 
	int _indicator, 
	std::pair<size_t, size_t> _indices)
{
	length = _length;
	indicator = _indicator;
	indices = _indices;
}


// PUBLIC FUNCTIONS WITH ACCESS TO VARIABLES
void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setLength(double newLength) throw(...){
	length = newLength; }

double OpenInfraPlatform::UserInterface::SplineInterpretationElement::getLength() const throw(...){
	return length; }

void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setindicator(int newIndicator) throw(...){
	indicator = newIndicator; }

int OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicator() const throw(...){
	return indicator; }


void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndices(size_t startIndice, size_t endIndice) throw(...){
	indices.first = startIndice;
	indices.second = endIndice; }

void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndicesStart(size_t startIndice) throw(...){
	indices.first = startIndice; }

void OpenInfraPlatform::UserInterface::SplineInterpretationElement::setIndicesEnd(size_t endIndice) throw(...){
	indices.second = endIndice; }

std::pair<size_t, size_t> OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndices() const throw(...){
	return indices; }

size_t OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicesStart() const throw(...){
	return indices.first; }

size_t OpenInfraPlatform::UserInterface::SplineInterpretationElement::getIndicesEnd() const throw(...){
	return indices.second; }


// PUBLIC FUNCTIONS

// PRIVATE FUNCTIONS