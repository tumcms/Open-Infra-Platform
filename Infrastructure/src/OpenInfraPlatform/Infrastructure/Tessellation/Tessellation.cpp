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

#include "Tessellation.h"

#include <OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h>

#include <BlueFramework/Core/Math/Vector.h>
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/Exception.h>

#include <cmath>
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

namespace
{
	void getUniformArcSampling(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		buw::Vector2d const& center,
		bool const bCCW,
		double const minSegCreaseRAD,
		size_t& numIntermediateStepsOut,
		double& angleDeltaOut)
	{
		if(minSegCreaseRAD >= M_PI)
			throw std::domain_error("The minimum segment crease angle must be in [0, Pi[.");

		// Total angle to rotate from start to end.
		auto const& startVec = start - center;
		auto const& endVec = end - center;
		double alpha = acos(startVec.dot(endVec) / (startVec.norm() * endVec.norm()));

		// We must determine whether to take the larger or the smaller angle. acos() will always
		// give us the principal value (smaller angle).
		buw::Matrix22d m;
		m.col(0) = startVec;
		m.col(1) = endVec;
		if ((buw::det(m) > 0.0) ^ bCCW) // In the special case that the determinant is zero, alpha is zero too.
		{
			alpha = 2 * M_PI - alpha;
			if (alpha >= 2 * M_PI) // Especially treats alpha == 2 * M_PI (when it was 0 before).
				alpha -= 2 * M_PI;
		}

		angleDeltaOut = M_PI - minSegCreaseRAD;
		numIntermediateStepsOut = int(ceil(alpha/angleDeltaOut)+0.1) - 1; // Minimum number of intermediate samples, that guarantees the given minimum segment crease angle.
		angleDeltaOut = alpha / (numIntermediateStepsOut+1); // Maximum rotation angle per sample, that guarantees the given minimum segment crease angle.
	}
}

namespace Tessellation
{
	std::vector<buw::Vector2d> tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		buw::Vector2d const& center,
		bool const bCCW,
		double const minSegCreaseRAD)
	{
		size_t numIntermediateSteps = 0;
		double alphaDelta = 0.0;
		getUniformArcSampling(start, end, center, bCCW, minSegCreaseRAD, numIntermediateSteps, alphaDelta);
		buw::Vector2d const& rotatingPointer = start-center;
		std::vector<buw::Vector2d> arc;
		arc.push_back(start);
		for (size_t i = 1; i <= numIntermediateSteps; ++i)
			arc.push_back(center + (buw::createRotationMatrix((bCCW ? alphaDelta : -alphaDelta) * i) * rotatingPointer));
		arc.push_back(end);
		return arc;
	}

	std::vector<buw::Vector2d> tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		double const radius,
		bool const bCCW,
		double const minSegCreaseRAD)
	{
		// There are two candidates for the center. We take the one, that results in a shorter arc length.
		buw::Vector2d const& middle = 0.5 * (start + end);
		buw::Vector2d const& startToEnd = end - start;
		buw::Vector2d const& centerDirection = buw::orthogonal(startToEnd, true).normalized();
		double const distanceMiddleToCenter = sqrt(radius*radius - (0.5 * startToEnd).squaredNorm());
		buw::Vector2d const& center1 = middle + distanceMiddleToCenter * centerDirection;
		buw::Vector2d const& center2 = middle - distanceMiddleToCenter * centerDirection;
		buw::Vector2d center = center1;
		buw::Matrix22d m;
		m.col(0) = start-center2;
		m.col(1) = end-center2;
		if ((buw::det(m) < 0.0) ^ bCCW) // In the special case that the determinant is zero, both center candidates coincide.
			center = center2;

		return tessellateArc(start, end, center, bCCW, minSegCreaseRAD);
	}

	void tessellate(
		double const dFrom,
		double const dTo,
		std::shared_ptr<buw::HorizontalAlignment2D> horiz,
		std::shared_ptr<buw::VerticalAlignment2D> vert,
		std::shared_ptr<buw::Alignment3DBased3D> alignmentOut,
		std::vector<std::pair<buw::Vector2d, buw::Vector2d>>* pHorizontalTangentsAndNormalsOut,
		std::function<buw::Vector3d(
			double /*dStation*/,
			std::shared_ptr<buw::HorizontalAlignment2D> /*same as horiz*/,
			std::shared_ptr<buw::VerticalAlignment2D> /*same as vert*/,
			std::pair<buw::Vector2d, buw::Vector2d>* /*optional pHorizontalTangentAndNormalOut*/)> const& evaluator,
		bool const bSkipFirst,
		bool const bSkipLast)
	{
		std::pair<buw::Vector2d, buw::Vector2d> horizontalTangentAndNormal;
		double dCurrentLength = 0.0;
		int const numElements = horiz->getAlignmentElementCount();
		for (int i = 0; i < numElements && dCurrentLength < dTo; ++i)
		{
			auto element = horiz->getAlignmentElementByIndex(i);
			double const dElementLength = element->getLength();
			if (dCurrentLength + dElementLength > dFrom)
			{
				switch (element->getAlignmentType())
				{
				case eHorizontalAlignmentType::Line:
					if (!bSkipFirst && // Skips the first overall sample.
						i == 0)        // Skip the first local segment sample to not repeat the last (if there was one) because the
						               // segments are directly connected to each other.
					{
						alignmentOut->addPoint(evaluator(std::max(dFrom, dCurrentLength), horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}
					if (!bSkipLast || i < (numElements-1)) // Skips the last overall sample.
					{
						alignmentOut->addPoint(evaluator(std::min(dTo, dCurrentLength + dElementLength), horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}
					break;
				case eHorizontalAlignmentType::Arc:
				{
					auto horizArc = std::static_pointer_cast<buw::HorizontalAlignmentElement2DArc>(element);
					double const dStart = std::max(dFrom, dCurrentLength);
					double const dStop = std::min(dTo, dCurrentLength + dElementLength);

					if (!bSkipFirst && // Skips the first overall sample.
						i == 0)        // Skip the first local segment sample to not repeat the last (if there was one) because the
									   // segments are directly connected to each other.
					{
						alignmentOut->addPoint(evaluator(dStart, horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}

					double const dRadius = horizArc->getRadius();
					size_t numIntermediateSteps = 0;
					double unused = 0.0;
					getUniformArcSampling(horiz->getPosition(dStart), horiz->getPosition(dStop), horizArc->getCenter(),
						!horizArc->getClockWise(), circleMaxSegErr2minSegCrease(dRadius, log10(dRadius+1.0)), numIntermediateSteps, unused);
					if (numIntermediateSteps > 0)
					{
						double const dArcLengthDelta = (dStop - dStart) / (numIntermediateSteps+1);
						for (size_t i = 1; i <= numIntermediateSteps; ++i)
						{
							alignmentOut->addPoint(evaluator(dStart + (i*dArcLengthDelta), horiz, vert, &horizontalTangentAndNormal));
							if (pHorizontalTangentsAndNormalsOut)
								pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
						}
					}

					if (!bSkipLast || i < (numElements - 1)) // Skips the last overall sample.
					{
						alignmentOut->addPoint(evaluator(dStop, horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}
				} break;
				case eHorizontalAlignmentType::Clothoid:
				case eHorizontalAlignmentType::Bloss:
				default:
					throw buw::NotImplementedYetException("Adaptive tessellation of this element type is not yet supported.");
				}
			}
			dCurrentLength += dElementLength;
		}
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
