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
#ifndef OpenInfraPlatform_PointCloudProcessing_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h
#define OpenInfraPlatform_PointCloudProcessing_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h

#include "namespace.h"

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
	namespace PointCloudProcessing
	{
		namespace Enums {
			enum ePointCloudFilterDimension {
				NoDimension,
				Volume3D,
				Sections2D
			};

			enum eChainageComputationBase {
				Grid = 0,
				Octree = 1
			};

			enum eChainageComputationInterpolationMethod {
				NoInterpolation = 0,
				Barycentric = 1,
				Linear = 2
			};
		}

		struct LaserPoint
		{
			buw::Vector3d position;
			buw::Vector3f color;
		};
		struct GridComputationDescription {
			int size = 1;
			float kernelRadius = 100.0f;

			// Auto generated using 'GridComputationDescription() = default;'.
			GridComputationDescription() = default;
		};

		struct ChainageComputationDescription {
			bool bUseSmoothing = true, bUseInterpolation = true;

			Enums::eChainageComputationBase base;
			Enums::eChainageComputationInterpolationMethod interpolation;

			float sigma = 1.0f , sigmaSF = -1.0f;

			// Auto generated using 'ChainageComputationDescription() = default;'.
			ChainageComputationDescription() = default;
		};

		struct DuplicateFilterDescription {
			Enums::ePointCloudFilterDimension dim;
			double minDistance = 0.0;			
		};

		struct LocalDensityFilterDescription {
			Enums::ePointCloudFilterDimension dim;
			float minThreshold, kernelRadius;
			CCLib::GeometricalAnalysisTools::Density density;
		};

		struct PositionFilterDescription {
			int dimension;
			double minValue, maxValue;
		};

		struct RelativeHeightFilterDescription {
			double lowerBound = 0.5, upperBound = 0.5;

			// Auto generated using 'RelativeHeightFilterDescription() = default;'.
			RelativeHeightFilterDescription() = default;
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
			int minSegmentPoints = 1000;
			float minSegmentLength = 10.0f,  centerlineDensity = 0.1f;

			int minCenterlinePoints = 10;
			float minCenterlineLength = 0.1f;

			float sortingCloseDistance = 0.15f, sortingFarDistance = 0.7f;
			float sortingCloseRatio = 0.8f, sortingFarRatio = 0.9f;

			bool fuseCenterlines = true;
			float fuseCenterlinesCloseDistance = 0.15f;
			float fuseCenterlinesFarDistance = 0.7f;
			float fuseCenterlinesCloseRatio = 0.8f;
			float fuseCenterlinesFarRatio = 0.9f;

			bool fuseAlignments = false;
			float fuseAlignmentsCloseDistance = 0.15f;
			float fuseAlignmentsFarDistance = 0.7f;
			float fuseAlignmentsCloseRatio = 0.8f;
			float fuseAlignmentsFarRatio = 0.9f;

			bool centerlineSmoothing = false;

			bool centerlineSampling = false;
			float samplingStepSize = 0.1f;
			float samplingLengthForPCA = 1.0f;

			bool filterDuplicates = true, filterDensity = true;
			float duplicateDistance = 0.002f;
			float densityKernelRadius = 0.1f;
			int densityThreshold = 15;

			// Auto generated using 'CenterlineComputationDescription() = default;'.
			CenterlineComputationDescription() = default;
		};

		struct CenterlineCurvatureComputationDescription {
			int centerlineIndex,  curvatureStepSize, numPointsForMeanCurvature, numPointsForMedianCurvature, numPointsForMeanBearing, numPointsForMedianBearing;
			double bearingComputationSegmentLength;

			// Auto generated using 'CenterlineCurvatureComputationDescription() = default;'.
			CenterlineCurvatureComputationDescription() = default;
		};

		struct RailwaySegmentationDescription {
			int minSegmentPoints, numPointsForPCA, curvatureStepSize, numPointsForMeanCurvature;
			float distanceForPCA, minSegmentLength, centerlinePointDistance;
		};

		struct PairComputationDescription {
			bool includeNextSection = true;

			float maxElevationChange = 0.2f;
			float maxError = 0.01f;
			float pointProximityDistance = 0.1f;

			bool applyDensityFilter = true;
			float localDensityKernelRadius = 0.067f / 2.0f; //head width is 0.067m = 6.7cm
			size_t localDensityThreshold = 15;

			bool applyClusterFilter = true;
			float clusterDistance2D = 0.15f;
			float clusterHeightTreshold = 0.05f;
			float clusterHeightRange = 0.05f;

			// Auto generated using 'PairComputationDescription() = default;'.
			PairComputationDescription() = default;
		};

		std::array<double, 4> fitHarmonicOscilation(const std::vector<double> &x, const std::vector<double> &y);

		//BLUEINFRASTRUCTURE_API void importLASPointCloud(const char* filename, PointCloud& pointCloud);
		//BLUEINFRASTRUCTURE_API void importBINPointCloud(const char* filename, PointCloud& pointCloud);
	} // end namespace PointCloudProcessing
} // end namespace BlueFramework

namespace buw
{
	//using OpenInfraPlatform::PointCloudProcessing::importLASPointCloud;
	//using OpenInfraPlatform::PointCloudProcessing::importBINPointCloud;
	using OpenInfraPlatform::PointCloudProcessing::LaserPoint;
	using OpenInfraPlatform::PointCloudProcessing::DuplicateFilterDescription;
	using OpenInfraPlatform::PointCloudProcessing::LocalDensityFilterDescription;
	using OpenInfraPlatform::PointCloudProcessing::PositionFilterDescription;
	using OpenInfraPlatform::PointCloudProcessing::RelativeHeightFilterDescription;
	using OpenInfraPlatform::PointCloudProcessing::RateOfChangeSegmentationDescription;
	using OpenInfraPlatform::PointCloudProcessing::PercentileSegmentationDescription;
	using OpenInfraPlatform::PointCloudProcessing::RailwaySegmentationDescription;
	using OpenInfraPlatform::PointCloudProcessing::CenterlineComputationDescription;
	using OpenInfraPlatform::PointCloudProcessing::CenterlineCurvatureComputationDescription;
	using OpenInfraPlatform::PointCloudProcessing::GridComputationDescription;
	using OpenInfraPlatform::PointCloudProcessing::ChainageComputationDescription;
	using OpenInfraPlatform::PointCloudProcessing::PairComputationDescription;
}

#endif // end define OpenInfraPlatform_PointCloudProcessing_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h
