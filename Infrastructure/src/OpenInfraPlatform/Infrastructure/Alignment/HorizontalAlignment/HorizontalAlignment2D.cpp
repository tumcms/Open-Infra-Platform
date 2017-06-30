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

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignment2D.h"
#include <BlueFramework/Core/assert.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

HorizontalAlignment2D::HorizontalAlignment2D(const Stationing startStationing /*= 0.0*/) : startStationing_(startStationing) {
}

buw::ReferenceCounted<HorizontalAlignmentElement2D> HorizontalAlignment2D::getAlignmentElementByStationing(const Stationing station, double* lerpParameter /*= nullptr*/) const {
	if (horizontalElements_.size() == 0) {
		return nullptr;
	}

	// If station is out of range return nullptr
	if (station < getStartStation() || station > getEndStation()) {
		// std::cout << "invalid station" << std::endl;

		if (station < getStartStation()) {
			// first alignment
			return horizontalElements_[0];
		}

		if (station > getEndStation()) {
			// last alignment
			return horizontalElements_[horizontalElements_.size() - 1];
		}

		return nullptr;
	}

	double currentStationT3 = startStationing_;
	double previousStationT1 = 0;

	for (buw::ReferenceCounted<HorizontalAlignmentElement2D> a : horizontalElements_) {
		previousStationT1 = currentStationT3;
		currentStationT3 += a->getLength();

		if (currentStationT3 >= station) {
			if (lerpParameter) {
				*lerpParameter = ((station - previousStationT1) / (currentStationT3 - previousStationT1));

				BLUE_ASSERT(*lerpParameter >= 0.0, "Invalid value.");
				BLUE_ASSERT(*lerpParameter <= 1.0, "Invalid value.");
			}

			return a;
		}
	}

	return nullptr;
}

Stationing HorizontalAlignment2D::getEndStation() const {
	return startStationing_ + getLength();
}

Stationing HorizontalAlignment2D::getStartStation(const int index /*= 0*/) const {
	BLUE_ASSERT(index >= 0, "Invalid index.");
	BLUE_ASSERT(index < horizontalElements_.size(), "Invalid index.");

	Stationing s = startStationing_;

	for (int i = 0; i < index; i++) {
		s += horizontalElements_[i]->getLength();
	}

	return s;
}

void HorizontalAlignment2D::addElement(buw::ReferenceCounted<HorizontalAlignmentElement2D> he) {
	horizontalElements_.push_back(he);
}

buw::ReferenceCounted<HorizontalAlignmentElement2D> HorizontalAlignment2D::getAlignmentElementByIndex(int index) {
	BLUE_ASSERT(index >= 0, "Invalid index.");
	BLUE_ASSERT(index < horizontalElements_.size(), "Invalid index.");
	return horizontalElements_[index];
}

double HorizontalAlignment2D::getLength() const {
	double sum = 0;

	for (buw::ReferenceCounted<HorizontalAlignmentElement2D> a : horizontalElements_) {
		sum += a->getLength();
	}

	return sum;
}

int HorizontalAlignment2D::getAlignmentElementCount() const {
	return static_cast<int>(horizontalElements_.size());
}

buw::Vector2d HorizontalAlignment2D::getPosition(const Stationing station) const {
	double s = station;

	double lerpScalar = 0.0;
	buw::ReferenceCounted<HorizontalAlignmentElement2D> a = getAlignmentElementByStationing(s, &lerpScalar);

	BLUE_ASSERT(lerpScalar >= 0.0, "Invalid lerp paramter.");
	BLUE_ASSERT(lerpScalar <= 1.0, "Invalid lerp paramter.");

	BLUE_ASSERT(a != nullptr, "Invalid alignment element.");
	return a->getPosition(lerpScalar);
}

buw::Vector2d HorizontalAlignment2D::getTangent(const Stationing station) const
{
	double lerpScalar = 0.0;
	buw::ReferenceCounted<HorizontalAlignmentElement2D> a = getAlignmentElementByStationing(station, &lerpScalar);

	BLUE_ASSERT(lerpScalar >= 0.0, "Invalid lerp paramter.");
	BLUE_ASSERT(lerpScalar <= 1.0, "Invalid lerp paramter.");

	BLUE_ASSERT(a != nullptr, "Invalid alignment element.");
	return a->getTangent(lerpScalar);
}

buw::Vector2d HorizontalAlignment2D::getNormal(const Stationing station) const
{
	double lerpScalar = 0.0;
	buw::ReferenceCounted<HorizontalAlignmentElement2D> a = getAlignmentElementByStationing(station, &lerpScalar);

	BLUE_ASSERT(lerpScalar >= 0.0, "Invalid lerp paramter.");
	BLUE_ASSERT(lerpScalar <= 1.0, "Invalid lerp paramter.");

	BLUE_ASSERT(a != nullptr, "Invalid alignment element.");
	return a->getNormal(lerpScalar);
}

bool HorizontalAlignment2D::hasSuccessor(buw::ReferenceCounted<HorizontalAlignmentElement2D> element) {
	for (int i = 0; i < horizontalElements_.size(); i++) {
		if (element == horizontalElements_[i]) {
			return true;
		}
	}

	return false;
}

buw::ReferenceCounted<HorizontalAlignmentElement2D> HorizontalAlignment2D::getSuccessor(buw::ReferenceCounted<HorizontalAlignmentElement2D> element) {
	for (int i = 0; i < horizontalElements_.size(); i++) {
		if (element == horizontalElements_[i]) {
			return horizontalElements_[i];
		}
	}
	return nullptr;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END