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
#ifndef OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_old_047b3c91_bdc8_4695_9532_c1a0eae908a3_h
#define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_old_047b3c91_bdc8_4695_9532_c1a0eae908a3_h

#include "HorizontalAlignmentElement2D.h"
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform {
	namespace Infrastructure {
		// The current clothid (OpenInfraPlatform::Infrastructure::Clothid) uses more than six paramters,
		// which should be avoided. For that reason this "power" clothoid has been introduced. It will
		// be renamed later on to clothoid and the old clothoid will be deleted.
		class BLUEINFRASTRUCTURE_API HorizontalAlignmentElement2DClothoid_old : public HorizontalAlignmentElement2D {
		public:
			// Ctor which supports LandXML
			HorizontalAlignmentElement2DClothoid_old(const buw::Vector2d& start,
			                                         const buw::Vector2d& end,
			                                         const buw::Vector2d& pi,
			                                         const double length,
			                                         const double radiusStart,
			                                         const double radiusEnd,
			                                         const bool clockwise);

			// Ctor which supports RoadXML
			HorizontalAlignmentElement2DClothoid_old(const buw::Vector2d& start,
			                                         const double direction,
			                                         const double startCurvature,
			                                         const double endCurvature,
			                                         const double length);

			buw::Vector2d getPosition(const double lerpParameter) const override;
			buw::Vector2d getTangent(const double lerpParameter) const override;
			buw::Vector2d getNormal(const double lerpParameter) const override;

			virtual buw::Vector2d getStartPosition() const override;

			virtual buw::Vector2d getEndPosition() const override;

			double getLength() const override;
			double getClothoidConstant() const;

			buw::radiand calculateStartTangentAngle() const;
			buw::radiand calculateEndTangentAngle() const;

			double calculateLongTangent() const;
			double calculateShortTangent() const;
			double calculateTotalX() const;
			double calculateTotalY() const;

			virtual eHorizontalAlignmentType getAlignmentType() const override;
			bool genericQuery(const int id, void* result) const override;

			double getStartCurvature() const;
			double getEndCurvature() const;

		public:
			static double computeX(const double L, const double A);
			static double computeY(const double L, const double A);

			// A = clothoid constant, L = length from start to end radius, isEntry = startCurvature < endCurvature
			static double computeEndRadius(const double A, const double L, const double radiusStart, const bool isEntry);

			static buw::Vector2d computeEndPoint(const buw::Vector2d& startPoint,
			                                     const buw::radiand startDirection,
			                                     const double segmentLenght,
			                                     const double startRadius,
			                                     const bool isCcw,
			                                     const bool isEntry,
			                                     const double clothoidConstant);

			static double computeEndDirection(const buw::radiand startDirection, const bool isCcw, const double turnedAngle);

			static double computeTurnedAngle(const double segmentLenght, double fullSpiralLength, const double clothoidConstant);

			static double computeFulllLength(const bool isEntry, const double& A, const double startRadius, const double& L);

			static double computeOriginProjection(const bool isEntry, const double segmentLenght, const double clothoidConstant, double fullSpiralLength);

			static double computeOriginOffset(const bool isEntry, const double segmentLenght, const double clothoidConstant, double fullSpiralLength, const bool isCcw);

			static double computeEndPointProjection(const bool isEntry, const double segmentLenght, const double clothoidConstant, double fullSpiralLength);

			static double computeOriginDirection(const bool isEntry,
			                                     const double startCurvature,
			                                     const double endCurvature,
			                                     const double startDirection,
			                                     const double endDirection,
			                                     const double fullSpiralLength,
			                                     const double clothoidConstant,
			                                     const bool isCcw);

			static double computeEndPointOffset(const bool isEntry, const double fullSpiralLength, const double clothoidConstant, const bool isCcw, const double segmentLength);

			static double computeOriginEasting(const double easting, const double originProjection, const double originDirection, const double originOffset);

			static double computeOriginNorthing(const double northing, const double originProjection, const double originDirection, const double originOffset);

			static double computeEndCurvature(const double radiusEnd);

		private:
			static double sgnEven(int x);

			buw::radiand calculateGlobalRotation() const;

		private:
			buw::Vector2d start_;
			buw::Vector2d end_;
			buw::Vector2d pi_;
			double length_;
			double startCurvature_;
			double endCurvature_;
			bool clockwise_;
		};
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
	using OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DClothoid_old;
}

#endif // end define OpenInfraPlatform_Infrastructure_HorizontalAlignmentElement2DClothoid_047b3c91_bdc8_4695_9532_c1a0eae908a3_h
