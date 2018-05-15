/*
    Copyright (c) 2018 Technical University of Munich
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
#ifndef OpenInfraPlatform_Infrastructure_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h
#define OpenInfraPlatform_Infrastructure_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"

#include <BlueFramework/ImageProcessing/color.h>
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include <vector>
#include <boost/noncopyable.hpp>

#include <ccHObject.h>
#include <ccPointCloud.h>
#include <GeometricalAnalysisTools.h>


namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct LaserPoint
		{
			buw::Vector3d position;
			buw::Vector3f color;
		};

		enum ePointCloudFilterDimension {
			None,
			Volume3D,
			Sections2D
		};

		struct DuplicateFilterDescription {
			ePointCloudFilterDimension dim;
			double minDistance = 0.0;			
		};

		struct LocalDensityFilterDescription {
			ePointCloudFilterDimension dim;
			float minThreshold, kernelRadius;
			CCLib::GeometricalAnalysisTools::Density density;
		};

		struct PositionFilterDescription {
			int dimension;
			double minValue, maxValue;
		};

		struct RateOfChangeSegmentationDescription {
			int dim;
			float maxNeighbourDistance;
			float maxRateOfChangeThreshold;
		};

		struct PercentileSegmentationDescription {
			float minThreshold, maxThreshold, kernelRadius;
			double lowerPercentile, upperPercentile;
		};

		struct CenterlineComputationDescription {
			int minSegmentPoints;
			float minSegmentLength, maxDistance, centerlineDensity;

			CenterlineComputationDescription() = default;
		};

		struct CenterlineCurvatureComputationDescription {
			int centerlineIndex, numPointsForPCA, curvatureStepSize, numPointsForMeanCurvature;			
		};

		struct RailwaySegmentationDescription {
			int minSegmentPoints, numPointsForPCA, curvatureStepSize, numPointsForMeanCurvature;
			float distanceForPCA, minSegmentLength, centerlinePointDistance;
		};

		//BLUEINFRASTRUCTURE_API void importLASPointCloud(const char* filename, PointCloud& pointCloud);
		//BLUEINFRASTRUCTURE_API void importBINPointCloud(const char* filename, PointCloud& pointCloud);
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	//using OpenInfraPlatform::Infrastructure::importLASPointCloud;
	//using OpenInfraPlatform::Infrastructure::importBINPointCloud;
	using OpenInfraPlatform::Infrastructure::LaserPoint;
	using OpenInfraPlatform::Infrastructure::ePointCloudFilterDimension;
	using OpenInfraPlatform::Infrastructure::DuplicateFilterDescription;
	using OpenInfraPlatform::Infrastructure::LocalDensityFilterDescription;
	using OpenInfraPlatform::Infrastructure::PositionFilterDescription;
	using OpenInfraPlatform::Infrastructure::RateOfChangeSegmentationDescription;
	using OpenInfraPlatform::Infrastructure::PercentileSegmentationDescription;
	using OpenInfraPlatform::Infrastructure::RailwaySegmentationDescription;
	using OpenInfraPlatform::Infrastructure::CenterlineComputationDescription;
	using OpenInfraPlatform::Infrastructure::CenterlineCurvatureComputationDescription;
}

#endif // end define OpenInfraPlatform_Infrastructure_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h
