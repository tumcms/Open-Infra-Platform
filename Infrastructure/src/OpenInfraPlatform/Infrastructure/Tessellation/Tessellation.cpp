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

#include <OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DLine.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DArc.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DLine.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DArc.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/VerticalAlignment/VerticalAlignmentElement2DParabola.h>

#include <BlueFramework/Core/Math/Vector.h>
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/Exception.h>

#include <cmath>
#include <vector>
#include <map>
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

	double getMaxAbsCurvature(std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable> segment)
	{
		auto const horizLine = std::dynamic_pointer_cast<OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DLine>(segment);
		auto const vertLine = std::dynamic_pointer_cast<OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DLine>(segment);
		auto const horizArc = std::dynamic_pointer_cast<OpenInfraPlatform::Infrastructure::HorizontalAlignmentElement2DArc>(segment);
		auto const vertArc = std::dynamic_pointer_cast<OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DArc>(segment);
		auto const vertParabola = std::dynamic_pointer_cast<OpenInfraPlatform::Infrastructure::VerticalAlignmentElement2DParabola>(segment);

		double dAbsCurvature = 0.0;
		if (horizLine || vertLine)
			return 0.0;
		else if (horizArc)
			return std::fabs(horizArc->getCurvature());
		else if (vertArc)
			return std::fabs(vertArc->getCurvature());
		else if (vertParabola)
			return std::fabs(vertParabola->getCurvature());
		else
			throw buw::NotImplementedYetException("Type is not yet implemented.");

		return 0.0;
	}

	std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable> getSegmentWithMaxCurvature(
		std::vector<std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable>> segments,
		double& dMaxCurvatureOut)
	{
		size_t const numSegments = segments.size();
		if (numSegments <= 0 || numSegments > 2) return nullptr;

		double dAbsCurvature1 = getMaxAbsCurvature(segments.front());
		if (numSegments == 1)
		{
			dMaxCurvatureOut = dAbsCurvature1;
			return segments.front();
		}
		double dAbsCurvature2 = getMaxAbsCurvature(segments.back());
		dMaxCurvatureOut = std::max(dAbsCurvature1, dAbsCurvature2);
		return dAbsCurvature1 >= dAbsCurvature2 ? segments.front() : segments.back();
	}
}

namespace Tessellation
{
	void tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		buw::Vector2d const& center,
		bool const bCCW,
		std::vector<buw::Vector2d>& positionsOut,
		std::vector<buw::Vector2d>* normalsOut,
		double const minSegCreaseRAD)
	{
		size_t numIntermediateSteps = 0;
		double alphaDelta = 0.0;
		getUniformArcSampling(start, end, center, bCCW, minSegCreaseRAD, numIntermediateSteps, alphaDelta);
		buw::Vector2d const& rotatingPointer = start-center;
		positionsOut.push_back(start);
		if (normalsOut) normalsOut->push_back(rotatingPointer.normalized());
		for (size_t i = 1; i <= numIntermediateSteps; ++i)
		{
			buw::Vector2d const& rotatedPointer = (buw::createRotationMatrix((bCCW ? alphaDelta : -alphaDelta) * i) * rotatingPointer);
			positionsOut.push_back(center + rotatedPointer);
			if (normalsOut) normalsOut->push_back(rotatedPointer.normalized());
		}
		positionsOut.push_back(end);
		if (normalsOut) normalsOut->push_back((end-center).normalized());
	}

	void tessellateArc(
		buw::Vector2d const& start,
		buw::Vector2d const& end,
		double const radius,
		bool const bCCW,
		std::vector<buw::Vector2d>& positionsOut,
		std::vector<buw::Vector2d>* normalsOut,
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

		return tessellateArc(start, end, center, bCCW, positionsOut, normalsOut, minSegCreaseRAD);
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
		std::map<double, std::vector<std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable>>> segmentJoints;

		// Collect relevant horizontal alignment elements and their starting positions.
		double dCurrentLength = 0.0;
		int const numHorizElements = horiz->getAlignmentElementCount();
		for (int i = 0; i < numHorizElements && dCurrentLength < dTo; ++i)
		{
			auto element = horiz->getAlignmentElementByIndex(i);
			double const dElementLength = element->getLength();
			if (dCurrentLength + dElementLength > dFrom)
			{
				std::vector<std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable>> elemVec;
				elemVec.push_back(element);
				segmentJoints[std::max(dFrom, dCurrentLength)] = elemVec;
			}
			dCurrentLength += dElementLength;
		}

		// Collect relevant vertical alignment elements and their starting positions.
		dCurrentLength = 0.0;
		int const numVertElements = vert->getAlignmentElementCount();
		for (int i = 0; i < numVertElements && dCurrentLength < dTo; ++i)
		{
			auto element = vert->getAlignmentElementByIndex(i);
			double const dElementLength = element->getEndStation() - element->getStartStation();
			if (dCurrentLength + dElementLength > dFrom)
			{
				double const key = std::max(dFrom, dCurrentLength);
				auto findIt = segmentJoints.find(key);
				if (findIt == segmentJoints.end())
				{
					std::vector<std::shared_ptr<OpenInfraPlatform::Infrastructure::IQueryable>> elemVec;
					elemVec.push_back(element);
					segmentJoints[key] = elemVec;
				}
				else
				{
					findIt->second.push_back(element);
				}
			}
			dCurrentLength += dElementLength;
		}

		// Now iterate the elements and tessellate them.
		double const LN_BASE = log(1000);
		std::pair<buw::Vector2d, buw::Vector2d> horizontalTangentAndNormal;
		auto const firstIt = segmentJoints.begin();
		auto const lastIt = --segmentJoints.end();
		for (auto it = firstIt; it != segmentJoints.end(); ++it)
		{
			auto nextIt(it); ++nextIt;
			double const dLocalFrom = it->first;
			double const dLocalTo = (nextIt != segmentJoints.end() ? nextIt->first : dTo);
			double dMaxCurvature = 0.0;
			auto const& seg = getSegmentWithMaxCurvature(it->second, dMaxCurvature);

			if (!bSkipFirst && // Skips the first overall sample.
				it == firstIt) // Skip the first local segment sample to not repeat the last (if there was one) because the
                               // segments are directly connected to each other.
			{
				alignmentOut->addPoint(evaluator(dLocalFrom, horiz, vert, &horizontalTangentAndNormal));
				if (pHorizontalTangentsAndNormalsOut)
					pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
			}

			auto const horizLine = std::dynamic_pointer_cast<HorizontalAlignmentElement2DLine>(seg);
			auto const vertLine = std::dynamic_pointer_cast<VerticalAlignmentElement2DLine>(seg);
			auto const horizArc = std::dynamic_pointer_cast<HorizontalAlignmentElement2DArc>(seg);
			auto const vertArc = std::dynamic_pointer_cast<VerticalAlignmentElement2DArc>(seg);
			auto const vertParabola = std::dynamic_pointer_cast<VerticalAlignmentElement2DParabola>(seg);

			if (horizLine || vertLine)
			{
				// Nothing to do!
			}
			else if (horizArc || vertArc)
			{
				double const dRadius = (horizArc ? horizArc->getRadius() : vertArc->getRadius());
				buw::Vector2d const startPos = (horizArc ? horiz->getPosition(dLocalFrom) : vert->getPosition(dLocalFrom));
				buw::Vector2d const stopPos = (horizArc ? horiz->getPosition(dLocalTo) : vert->getPosition(dLocalTo));
				buw::Vector2d const centerPos = (horizArc ? horizArc->getCenter() : vertArc->getCenter());
				bool const bCCW = (horizArc ? !horizArc->getClockWise() : vertArc->isConvex());
				size_t numIntermediateSteps = 0;
				double unused = 0.0;
				getUniformArcSampling(startPos, stopPos, centerPos, bCCW, circleMaxSegErr2minSegCrease(dRadius, log1p(dRadius) / LN_BASE),
					numIntermediateSteps, unused);
				if (numIntermediateSteps > 0)
				{
					double const dArcLengthDelta = (dLocalTo - dLocalFrom) / (numIntermediateSteps + 1);
					for (size_t i = 1; i <= numIntermediateSteps; ++i)
					{
						alignmentOut->addPoint(evaluator(dLocalFrom + (i*dArcLengthDelta), horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}
				}
			}
			else if (vertParabola)
			{
				// We sample the parabola equidistantly (uniformly) as if it was a circle. Surely this is suboptimal.
				double const dRadius = 1.0 / dMaxCurvature;
				double const dMaxSegError = log1p(dRadius) / LN_BASE;

				// Let r be the radius, e the max segment error and x the maximum step length on the arc, then
				// (r-e)/r = 1-(e/r) =>
				// acos(1-(e/r)) / 2*Pi = 0.5*x / 2*Pi*r   <=>   x = 2*r*acos(1-(e/r))
				double dMaxStepSize = 2 * dRadius * acos(1.0 - (dMaxSegError / dRadius));

				// Uniformly distribute the step size.
				size_t const numIntermediateSteps = int(ceil((dLocalTo - dLocalFrom) / dMaxStepSize) + 0.1) - 1;
				if (numIntermediateSteps > 0)
				{
					dMaxStepSize = (dLocalTo - dLocalFrom) / (numIntermediateSteps + 1);
					for (size_t i = 1; i <= numIntermediateSteps; ++i)
					{
						alignmentOut->addPoint(evaluator(dLocalFrom + (i*dMaxStepSize), horiz, vert, &horizontalTangentAndNormal));
						if (pHorizontalTangentsAndNormalsOut)
							pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
					}
				}
			}
			else
				throw buw::NotImplementedYetException("Adaptive tessellation of this element type is not yet supported.");

			if (!bSkipLast || it != lastIt) // Skips the last overall sample.
			{
				alignmentOut->addPoint(evaluator(dLocalTo, horiz, vert, &horizontalTangentAndNormal));
				if (pHorizontalTangentsAndNormalsOut)
					pHorizontalTangentsAndNormalsOut->push_back(horizontalTangentAndNormal);
			}
		}
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
