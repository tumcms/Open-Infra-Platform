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

#include "OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignment2D.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

buw::ReferenceCounted<VerticalAlignmentElement2D> VerticalAlignment2D::getAlignmentElementByStationing(const Stationing station) const {
	if (verticalElements_.size() == 0) {
		return nullptr;
	}

	for (int i = 0; i < verticalElements_.size(); i++) {
		if (station >= verticalElements_[i]->getStartStation() && station < verticalElements_[i]->getEndStation()) {
			return verticalElements_[i];
		}
	}

	return nullptr;
}

void VerticalAlignment2D::addElement(buw::ReferenceCounted<VerticalAlignmentElement2D> ve) {
	verticalElements_.push_back(ve);
}

Stationing VerticalAlignment2D::getEndStation() const {
	if (verticalElements_.size() == 0) {
		return 0;
	}
	return verticalElements_[verticalElements_.size() - 1]->getEndStation();
}

Stationing VerticalAlignment2D::getStartStation() const {
	if (verticalElements_.size() == 0) {
		return 0;
	}
	return verticalElements_[0]->getStartStation();
}

buw::ReferenceCounted<VerticalAlignmentElement2D> OpenInfraPlatform::Infrastructure::VerticalAlignment2D::getAlignmentElementByIndex(int index) {
	BLUE_ASSERT(index >= 0, "Invalid index.");
	BLUE_ASSERT(index < verticalElements_.size(), "Invalid index.");
	return verticalElements_[index];
}

int VerticalAlignment2D::getAlignmentElementCount() const {
	return static_cast<int>(verticalElements_.size());
}

buw::Vector2d VerticalAlignment2D::getPosition(const Stationing station) const {
	buw::ReferenceCounted<VerticalAlignmentElement2D> v = getAlignmentElementByStationing(station);

	if (v == nullptr) {
		return buw::Vector2d(station, 0);
	}

	return v->getPosition(station);
}

bool VerticalAlignment2D::hasElements() const {
	return verticalElements_.size() > 0;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END