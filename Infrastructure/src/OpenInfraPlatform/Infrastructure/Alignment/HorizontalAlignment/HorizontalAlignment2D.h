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

#pragma once
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignment2D_fad49764_c3d4_45f4_8be4_8a6465f85631_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignment2D_fad49764_c3d4_45f4_8be4_8a6465f85631_h

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/types.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <boost/noncopyable.hpp>
#include <buw.Core.h>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

//! A connected line that describes a 2d alignment.
class BLUEINFRASTRUCTURE_API HorizontalAlignment2D {
public:
	HorizontalAlignment2D(const Stationing startStationing = 0.0);

	//! Computes the 2d position in the horizontal alignment given a stationing.
	buw::Vector2d getPosition(const Stationing station) const;

	//! The tangent points into the direction of increasing station value.
	buw::Vector2d getTangent(const Stationing station) const;

	//! The normal points into the left perpendicular direction of the tangent.
	buw::Vector2d getNormal(const Stationing station) const;

	int getAlignmentElementCount() const;

	//! Computes the length of the horizontal alignment
	double getLength() const;

	buw::ReferenceCounted<HorizontalAlignmentElement2D> getAlignmentElementByIndex(int index);

	//! Add an horizontal alignment segment.
	void addElement(buw::ReferenceCounted<HorizontalAlignmentElement2D> he);

	//! Start stationing of nth horizontal alignment element
	Stationing getStartStation(const int index = 0) const;

	//! End station of last horizontal alignment segment.
	Stationing getEndStation() const;

	//! station is assumed to be between [0;getLength]
	buw::ReferenceCounted<HorizontalAlignmentElement2D> getAlignmentElementByStationing(const Stationing station, double* lerpParameter = nullptr) const;

	bool hasSuccessor(buw::ReferenceCounted<HorizontalAlignmentElement2D> element);

	//! Get the successor element if it exists, otherwise nullptr.
	buw::ReferenceCounted<HorizontalAlignmentElement2D> getSuccessor(buw::ReferenceCounted<HorizontalAlignmentElement2D> element);

private:
	Stationing startStationing_;
	std::vector<buw::ReferenceCounted<HorizontalAlignmentElement2D>> horizontalElements_; // the order of the elements is important here
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::HorizontalAlignment2D;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignment2D_fad49764_c3d4_45f4_8be4_8a6465f85631_h