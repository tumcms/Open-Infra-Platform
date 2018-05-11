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
#ifndef OpenInfraPlatform_Infrastructure_PointCloudProcessing_PointCloud_C6DADDAE_D1A5_4A99_A95F_2DD5667ED977_h
#define OpenInfraPlatform_Infrastructure_PointCloudProcessing_PointCloud_C6DADDAE_D1A5_4A99_A95F_2DD5667ED977_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"

#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloudProcessing.h"

#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/memory.h>

#include <ccPointCloud.h>
#include <FileIOFilter.h>
#include <tuple>

class CCLib::GenericProgressCallback;

namespace OpenInfraPlatform {
	namespace Infrastructure {

		class PointCloudSection;

		class BLUEINFRASTRUCTURE_API PointCloud : public ccPointCloud {
		public:

			// Dont use, prototype implementation.
			static buw::ReferenceCounted<PointCloud> FromFile(const char* filename);

			PointCloud() : ccPointCloud() { }

			PointCloud(QString name) : ccPointCloud(name) { }

			void computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			void computeGrid();

			void alignOnMainAxis();

			int flagDuplicatePoints(const double minDistance, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric, ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyLocalDensityFilter(LocalDensityFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyDuplicateFilter(DuplicateFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyPercentilesSegmentation(buw::PercentileSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyPercentilesOnGridSegmentation(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyRateOfChangeSegmentation(RateOfChangeSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int segmentRailways(buw::RailwaySegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int resetRailwaySegmentation();

			void removeNotSegmentedPoints();

			void removeFilteredPoints(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			void resetScalarField(const char* name);	

			const CCVector3 getMainAxis() const;

			const double getSectionLength() const;			

			const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> getIndices() const;

			template<typename F> void for_each(const F& function)
			{
				for(size_t i = 0; i < size(); i++)
					function(i);
			}

			std::vector<buw::ReferenceCounted<PointCloudSection>> getSections();

			buw::ReferenceCounted<CCLib::ReferenceCloud> subsample(size_t size);

		private:
			void computeMainAxis();

			void computeIndices();

			void init();


			const std::tuple<ScalarType, ScalarType> getScalarFieldMinAndMax(int idx) const;

			template<unsigned int N> Eigen::Matrix<double, 3, N> getEigenvectors() const
			{
				try {
					//Matrix which is capable of holding all points for PCA.
					Eigen::MatrixX3d points;
					points.resize(this->size(), 3);
					for(size_t i = 0; i < this->size(); i++) {
						auto pos = this->getPoint(i);
						points.row(i) = Eigen::Vector3d(pos->x, pos->y, pos->z);
					}

					//Do PCA to find the largest eigenvector -> main axis.
					Eigen::MatrixXd centered = points.rowwise() - points.colwise().mean();
					Eigen::MatrixXd cov = centered.adjoint() * centered;
					Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
					Eigen::Matrix<double, 3, N> vec = eig.eigenvectors().rightCols(N);
					return vec;
				}
				catch(buw::Exception e) {
					BLUE_LOG(warning) << "Exception in Eigenvector computation. " << e.what();
					return Eigen::Matrix<double, 3, N>();
				}
			}

		public:

		private:
			CCVector3 mainAxis_;
			std::vector<uint32_t> remainingIndices_, filteredIndices_, segmentedIndices_;
			std::vector<buw::ReferenceCounted<PointCloudSection>> sections_;
			std::map<std::pair<int, int>, std::vector<uint32_t>> grid_;
			buw::ReferenceCounted<CCLib::DgmOctree> octree_;
		};
	}
}

namespace buw {
	using OpenInfraPlatform::Infrastructure::PointCloud;
}

#endif