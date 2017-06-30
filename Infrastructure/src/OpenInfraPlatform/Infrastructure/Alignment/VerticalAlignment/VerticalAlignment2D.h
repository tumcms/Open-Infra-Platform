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
#ifndef OpenInfraPlatform_Infrastructure_VerticalAlignment2D_6e6b8d09_8c39_42b0_ac49_9cf8e13ca522_h
#define OpenInfraPlatform_Infrastructure_VerticalAlignment2D_6e6b8d09_8c39_42b0_ac49_9cf8e13ca522_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "VerticalAlignmentElement2D.h"
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/assert.h>
#include <BlueFramework/Core/memory.h>

#include <boost/noncopyable.hpp>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API VerticalAlignment2D : boost::noncopyable {
public:
	//! Computes the 2d position in the horizontal alignment given a stationing.
	buw::Vector2d getPosition(const Stationing station) const;

	int getAlignmentElementCount() const;

	buw::ReferenceCounted<VerticalAlignmentElement2D> getAlignmentElementByIndex(int index);

	Stationing getStartStation() const;

	Stationing getEndStation() const;

	void addElement(buw::ReferenceCounted<VerticalAlignmentElement2D> ve);

	buw::ReferenceCounted<VerticalAlignmentElement2D> getAlignmentElementByStationing(const Stationing station) const;

	bool hasElements() const;

private:
	std::vector<buw::ReferenceCounted<VerticalAlignmentElement2D>> verticalElements_; // the order of the elements is important here
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::VerticalAlignment2D;
}

#endif // end define OpenInfraPlatform_Infrastructure_VerticalAlignment2D_6e6b8d09_8c39_42b0_ac49_9cf8e13ca522_h
