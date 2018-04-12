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

		struct FilterDescription {
			bool bRemoveDuplicates = false, bApplyLocalDensityFiltering = false;
			float removeDuplicatesDistanceThreshold, localDensityFilteringMinDensityThreshold;
			CCLib::GeometricalAnalysisTools::Density eDensityMetric;
		};

		class PointCloud : public ccPointCloud
		{
		public:
			void computeSections(const float length);

		private:
			template<unsigned int N> Eigen::Matrix<double, 3, N> getEigenvectors()
			{
				//Matrix which is capable of holding all points for PCA.
				Eigen::MatrixX3d points;
				points.resize(this->size(), 3);
				for(size_t i = 0; i < this->size(); i++) {
					auto pos = this->getPoint(i);
					points.row(i) = Eigen::Vector3d(pos->x,pos->y,pos->z);
				}

				//Do PCA to find the largest eigenvector -> main axis.
				Eigen::MatrixXd centered = points.rowwise() - points.colwise().mean();
				Eigen::MatrixXd cov = centered.adjoint() * centered;
				Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
				Eigen::Matrix<double, 3, N> vec = eig.eigenvectors().rightCols(N);
				return vec;
			}


		// Public attributes
		public:
			std::vector<uint32_t>	remainingIndices3D, filteredIndices3D, segmentedIndices3D;
			std::vector<uint32_t>	remainingIndices2D, filteredIndices2D, segmentedIndices2D;

		// Private attributes
		private:

		};



		

		BLUEINFRASTRUCTURE_API void importLASPointCloud(const char* filename, PointCloud& pointCloud);
		BLUEINFRASTRUCTURE_API void importBINPointCloud(const char* filename, PointCloud& pointCloud);
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::importLASPointCloud;
	using OpenInfraPlatform::Infrastructure::importBINPointCloud;
	using OpenInfraPlatform::Infrastructure::LaserPoint;
	using OpenInfraPlatform::Infrastructure::PointCloud;
	using OpenInfraPlatform::Infrastructure::FilterDescription;
}

#endif // end define OpenInfraPlatform_Infrastructure_PointCloudProcessing_8b77c948_e060_457a_a3ef_7a546fad37c3_h
