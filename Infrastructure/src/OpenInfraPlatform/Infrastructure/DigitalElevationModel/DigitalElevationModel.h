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
#ifndef OpenInfraPlatform_Infrastructure_DigitalElevationModel_8b94f7d0_a5fc_4ba4_ab63_f15df1bd6515_h
#define OpenInfraPlatform_Infrastructure_DigitalElevationModel_8b94f7d0_a5fc_4ba4_ab63_f15df1bd6515_h

#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/Surface.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <boost/noncopyable.hpp>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

//! A digital terrain model exists of a number of surfaces.
class BLUEINFRASTRUCTURE_API DigitalElevationModel {
public:
	static DigitalElevationModel* createFlatCopy(const DigitalElevationModel& src);

	DigitalElevationModel();

	virtual ~DigitalElevationModel();

	void addSurface(buw::ReferenceCounted<buw::Surface> surface);

	//! A digital terrain model can
	int getSurfaceCount() const;

	buw::ReferenceCounted<buw::Surface> getSurface(const int index) const;

	const std::vector<buw::ReferenceCounted<buw::Surface>>& getSurfaces() const;

	void getSurfacesExtend(buw::Vector3d& minimalPosition, buw::Vector3d& maximalPosition) const;

	buw::Vector3d getCenterPoint() const;

	std::vector<std::pair<double, double>> getSurfaceProfile(buw::ReferenceCounted<buw::IAlignment3D> a) const;
	double getHeightAtPosition(buw::Vector2d position) const;

	double getMinimumHeight() const;

	double getMaximumHeight() const;

	void deleteSurface(buw::ReferenceCounted<buw::Surface> s);

	void addBreakLine(const std::vector<buw::Vector3d>& breakLine);

	const std::vector<std::vector<buw::Vector3d>>& getBreakLines() const;

private:
	void updateMinMax(const buw::Vector3d& position, buw::Vector3d& minPos, buw::Vector3d& maxPos) const;

private:
	std::vector<buw::ReferenceCounted<buw::Surface>> surfaces_;
	std::vector<std::vector<buw::Vector3d>> breakLines_;
}; // end class DigitalElevationModel

BLUEINFRASTRUCTURE_API buw::ReferenceCounted<Surface> createSurfaceFromXYZPoints(const std::vector<buw::Vector3d>& positions);

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::DigitalElevationModel;
	using OpenInfraPlatform::Infrastructure::createSurfaceFromXYZPoints;
}

#endif // end define OpenInfraPlatform_Infrastructure_DigitalElevationModel_8b94f7d0_a5fc_4ba4_ab63_f15df1bd6515_h
