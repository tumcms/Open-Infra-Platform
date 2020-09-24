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
#ifndef OpenInfraPlatform_PointCloudProcessing_PointCloudProcessing_PointCloud_C6DADDAE_D1A5_4A99_A95F_2DD5667ED977_h
#define OpenInfraPlatform_PointCloudProcessing_PointCloudProcessing_PointCloud_C6DADDAE_D1A5_4A99_A95F_2DD5667ED977_h

#include "namespace.h"

#include "Octree.h"
#include "PointCloudProcessing.h"

#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Core/memory.h>

#include <ccPointCloud.h>
#include <FileIOFilter.h>
#include <tuple>

#include <IModel.h>

class CCLib::GenericProgressCallback;

namespace OpenInfraPlatform {
	namespace PointCloudProcessing {

		class PointCloudSection;

		class BLUEINFRASTRUCTURE_API PointCloud : public ccPointCloud, public oip::IModel {
		public:
			static const QStringList GetSupportedExtensions();

			// Dont use, prototype implementation.
			static buw::ReferenceCounted<PointCloud> FromFile(const char* filename, bool init = false);

			PointCloud() : ccPointCloud(), octree_(std::make_shared<Octree>(this)) { }

			PointCloud(QString name) : ccPointCloud(name) { }

			PointCloud(PointCloud &other);

			virtual ~PointCloud();

			int add(const buw::ReferenceCounted<ccPointCloud> &other, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr, ColorCompType* color = nullptr);

			void computeSections(const float length, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			void computeChainage(ChainageComputationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);
						
			std::vector<std::pair<CCVector3, ScalarType>> getAllPointsAndScalarFieldValue(int index);

			void computeGrid(GridComputationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			void resetGrid();

			void alignOnMainAxis();

			int flagDuplicatePoints(const double minDistance, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int computeLocalDensity(CCLib::GeometricalAnalysisTools::Density metric, ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyLocalDensityFilter(LocalDensityFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyDuplicateFilter(DuplicateFilterDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyPositionFilter(const buw::PositionFilterDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyRelativeHeightWithGridFilter(const buw::RelativeHeightFilterDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int resetPositionFilter();

			int applyPercentilesSegmentation(buw::PercentileSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyPercentilesSegmentationHP(const buw::PercentileSegmentationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyPercentilesOnGridSegmentation(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			int applyRateOfChangeSegmentation(RateOfChangeSegmentationDescription desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			// ---------------------------------------------------------------------------------------------------------------------------------------------------
			// Centerline computation
			// ---------------------------------------------------------------------------------------------------------------------------------------------------

			int computeCenterlines(const buw::CenterlineComputationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);
			int resetCenterlines();
			
			// ---------------------------------------------------------------------------------------------------------------------------------------------------
			// Pair computation
			// ---------------------------------------------------------------------------------------------------------------------------------------------------

			// Computes the pairs for all sections and stores the result in 'o_pairs'.
			void computePairs(const buw::PairComputationDescription &desc, std::vector<std::pair<size_t, size_t>> &o_pairs, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);
			// Resets the pairs for all sections.
			int resetPairs();

			std::vector<buw::ReferenceCounted<CCLib::ReferenceCloud>> extractConnectedComponents(ScalarType kernelRadius, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);
			


			int computeCenterlineCurvature(const buw::CenterlineCurvatureComputationDescription &desc, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

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

			buw::ReferenceCounted<buw::Octree> getDGMOctree();

			buw::ReferenceCounted<CCLib::ReferenceCloud> subsample(size_t size);

			template<unsigned int N> Eigen::Matrix<double, 3, N> getEigenvectors() const
			{
				try {
					if(size() > 0) {
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
					else {
						return Eigen::Matrix<double, 3, N>();
					}
				}
				catch(buw::Exception e) {
					BLUE_LOG(warning) << "Exception in Eigenvector computation. " << e.what();
					return Eigen::Matrix<double, 3, N>();
				}
			}			
		
			// ---------------------------------------------------------------------------------------------------------------------------------------------------
			// Interface IModel implementation
			// ---------------------------------------------------------------------------------------------------------------------------------------------------
			
			virtual bool isEmpty() const override;

			virtual oip::BBox getExtent() override;

			virtual std::string getEPSGcode() const override;
			virtual void transformAllPoints(const std::string& newEPSGcode, std::function<std::tuple<double, double, double> const(double, double, double)>& transf) override;

			// ---------------------------------------------------------------------------------------------------------------------------------------------------

		private:
			void computeMainAxis();

			void computeIndices();
			
			void init();

			void computeChainageOctreeBased(buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);

			void computeChainageGridBased(Enums::eChainageComputationInterpolationMethod method, buw::ReferenceCounted<CCLib::GenericProgressCallback> callback = nullptr);


			const std::tuple<ScalarType, ScalarType> getScalarFieldMinAndMax(int idx) const;

			const std::tuple<size_t, size_t> getScalarFieldMinAndMaxIndex(int idx);
		public:

		private:
			CCVector3 mainAxis_;
			std::vector<uint32_t> remainingIndices_, filteredIndices_, segmentedIndices_;
			std::vector<buw::ReferenceCounted<PointCloudSection>> sections_;
			std::map<std::pair<int, int>, std::tuple<std::vector<uint32_t>, CCVector3, CCVector2>> grid_;
			buw::ReferenceCounted<Octree> octree_ = nullptr;
			bool bHasPairs_ = false, bHasCenterline_ = false;

			buw::CenterlineComputationDescription centerlineDescription_;
			static bool areFiltersInitialized_;
		};
	}
}

namespace buw {
	using OpenInfraPlatform::PointCloudProcessing::PointCloud;
}

#endif