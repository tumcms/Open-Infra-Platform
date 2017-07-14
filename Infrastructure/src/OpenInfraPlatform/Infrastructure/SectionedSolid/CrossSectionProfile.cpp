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

#include "CrossSectionProfile.h"
#include <OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Types.h>
#include <OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h>
#include <OpenInfraPlatform/Infrastructure/Tessellation/Tessellation.h>
#include <BlueFramework/Core/Math/Vector.h>
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Exception.h>

#include <functional>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

namespace
{
	using OpenInfraPlatform::Infrastructure::SectionedSolid::CrossSectionProfile;
	typedef std::function<std::vector<std::shared_ptr<IfcAlignment1x1::IfcLengthMeasure>> const&(size_t const i)> PointSource;

	std::vector<CrossSectionProfile::Vertex> processLineStrip(
		PointSource const& pointSource,
		size_t const numPnts,
		bool const bRunsCCW)
	{
		buw::Vector2d prevPosition;
		buw::Vector2d nextPosition;
		std::vector<std::shared_ptr<IfcAlignment1x1::IfcLengthMeasure>> const* pNextPoint = nullptr;
		std::vector<CrossSectionProfile::Vertex> segment;
		for (size_t i = 0; i < numPnts && numPnts > 1; ++i)
		{
			// Validate data.
			bool const bIsFirst = (i == 0);
			bool const bIsLast = (i == numPnts - 1);
			auto const& point = pointSource(i);
			pNextPoint = bIsLast ? nullptr : &(pointSource(i + 1));
			if (point.size() != 2 || !point[0] || !point[1] ||
				(pNextPoint && (pNextPoint->size() != 2 || !(*pNextPoint)[0] || !(*pNextPoint)[1])))
			{
				BLUE_LOG(warning) << "Cross section profile data is corrupt.";
				continue;
			}

			// Get positions.
			buw::Vector2d const position(point[0]->m_value, point[1]->m_value);
			if (pNextPoint)
				nextPosition = buw::Vector2d((*pNextPoint)[0]->m_value, (*pNextPoint)[1]->m_value);

			// Compute the normal.
			buw::Vector2d normal;
			if (bIsFirst)
			{
				normal = buw::orthogonal(buw::Vector2d(nextPosition - position), !bRunsCCW).normalized();
			}
			else if (bIsLast)
			{
				normal = buw::orthogonal(buw::Vector2d(position - prevPosition), !bRunsCCW).normalized();
			}
			else
			{
				// Compute normal at half-angle.
				auto normal1 = buw::orthogonal(buw::Vector2d(position - prevPosition), !bRunsCCW).normalized();
				auto normal2 = buw::orthogonal(buw::Vector2d(nextPosition - position), !bRunsCCW).normalized();
				normal = (normal1 + normal2).normalized();
			}

			segment.push_back(CrossSectionProfile::Vertex(position, normal));
			prevPosition = position;
		}

		return segment;
	}

	// Returns two times the _signed_ polygon area.
	double computeGaussArea(PointSource const& pointSource, size_t const numPnts)
	{
		if(numPnts < 3)
			BLUE_LOG(warning) << "Cannot reliably determine polygon orientation of degenerated polygon.";

		// Using Gauss's area formula.
		double dArea = 0.0;
		for (size_t i = 0; i < numPnts; ++i)
		{
			auto const& p1 = pointSource(i);
			auto const& p2 = pointSource((i+1)%numPnts);
			if (p1.size() != 2 || !p1[0] || !p1[1] ||
				p2.size() != 2 || !p2[0] || !p2[1])
			{
				BLUE_LOG(warning) << "Point data is corrupt. Cannot reliably determine polygon orientation.";
				continue;
			}
			dArea += (p2[0]->m_value - p1[0]->m_value)*(p2[1]->m_value + p1[1]->m_value);
		}

		return dArea;
	}

	bool isCCW(PointSource const& pointSource, size_t const numPnts)
	{
		return computeGaussArea(pointSource, numPnts) <= 0.0;
	}

	bool isCCW(
		std::vector<std::shared_ptr<IfcAlignment1x1::IfcSegmentIndexSelect>> const& segs,
		std::shared_ptr<IfcAlignment1x1::IfcCartesianPointList2D> points)
	{
		double dArea = 0.0;
		for (auto seg : segs)
		{
			if (!seg) continue;
			if (std::dynamic_pointer_cast<IfcAlignment1x1::IfcLineIndex>(seg))
			{
				auto lineSegment = std::static_pointer_cast<IfcAlignment1x1::IfcLineIndex>(seg);
				dArea += computeGaussArea(
					[&points, &lineSegment](size_t const i)->std::vector<std::shared_ptr<IfcAlignment1x1::IfcLengthMeasure>> const& {return points->m_CoordList[lineSegment->m_vec[i]-1];},
					lineSegment->m_vec.size());
			}
			else if (std::dynamic_pointer_cast<IfcAlignment1x1::IfcArcIndex>(seg))
			{
				throw buw::NotImplementedYetException("Arc segments not yet implemented.");
			}
			else
			{
				throw buw::Exception("Unknown segment type.");
			}
		}

		return dArea <= 0.0;
	}

	std::vector<CrossSectionProfile::Vertex> getLinearSegment(
		buw::Vector2d const& p1,
		buw::Vector2d const& p2,
		buw::Vector2d const& n,
		buw::Matrix22d const& rotation,
		buw::Vector2d const& translation,
		bool const bTransformFirstPoint = false)
	{
		std::vector<CrossSectionProfile::Vertex> segment;
		segment.push_back(CrossSectionProfile::Vertex(bTransformFirstPoint ? rotation * (p1 + translation) : p1, rotation * n));
		segment.push_back(CrossSectionProfile::Vertex(rotation * (p2 + translation), rotation * n));
		return segment;
	}
}

namespace SectionedSolid
{

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcArbitraryClosedProfileDef> csp)
		: segments()
	{
		if (!csp->m_OuterCurve)
			throw buw::Exception("Empty curve.");
		switch (csp->m_OuterCurve->m_entity_enum)
		{
		case IfcAlignment1x1::IFCINDEXEDPOLYCURVE:
		{
			auto curve = std::static_pointer_cast<IfcAlignment1x1::IfcIndexedPolyCurve>(csp->m_OuterCurve);
			if (!curve->m_Points)
				throw buw::Exception("Empty curve.");
			if (curve->m_Points->m_entity_enum != IfcAlignment1x1::IFCCARTESIANPOINTLIST2D)
				throw buw::Exception("Profile curve must be 2D.");
			auto points = std::static_pointer_cast<IfcAlignment1x1::IfcCartesianPointList2D>(curve->m_Points);
			if (curve->m_Segments.empty())
			{
				auto const& pointSource = [&points](size_t const i)->std::vector<std::shared_ptr<IfcAlignment1x1::IfcLengthMeasure>> const& {
					return points->m_CoordList[i];
				};
				segments.push_back(processLineStrip(
					pointSource,
					points->m_CoordList.size(),
					isCCW(pointSource, points->m_CoordList.size())));
			}
			else
			{
				bool const bIsCCW = isCCW(curve->m_Segments, points);
				for (auto segment : curve->m_Segments)
				{
					if (!segment) continue;
					if (std::dynamic_pointer_cast<IfcAlignment1x1::IfcLineIndex>(segment))
					{
						auto lineSegment = std::static_pointer_cast<IfcAlignment1x1::IfcLineIndex>(segment);
						segments.push_back(processLineStrip(
							[&points, &lineSegment](size_t const i)->std::vector<std::shared_ptr<IfcAlignment1x1::IfcLengthMeasure>> const& {return points->m_CoordList[lineSegment->m_vec[i]-1];},
							lineSegment->m_vec.size(),
							bIsCCW));
					}
					else if (std::dynamic_pointer_cast<IfcAlignment1x1::IfcArcIndex>(segment))
					{
						auto arcSegment = std::static_pointer_cast<IfcAlignment1x1::IfcArcIndex>(segment);
						throw buw::NotImplementedYetException("Arc segments not yet implemented.");
					}
					else
					{
						throw buw::Exception("Unknown segment type.");
					}
				}
			}
		} break;
		default:
			throw buw::NotImplementedYetException("Unimplemented profile curve type.");
		}
	}

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcAsymmetricIShapeProfileDef> csp)
		: segments()
	{
		// Get the local profile transformation (IfcParameterizedProfileDef).
		buw::Vector2d translation(0.0, 0.0);
		buw::Matrix22d rotation = buw::Matrix22d::Identity();
		if (csp->m_Position)
		{
			if (csp->m_Position->m_Location && csp->m_Position->m_Location->m_Coordinates.size() == 2)
			{
				auto const& coords = csp->m_Position->m_Location->m_Coordinates;
				double const x = (coords[0] ? coords[0]->m_value : 0.0);
				double const y = (coords[1] ? coords[1]->m_value : 0.0);
				translation[0] = x;
				translation[1] = y;
			}
			if (csp->m_Position->m_RefDirection && csp->m_Position->m_RefDirection->m_DirectionRatios.size() == 2)
			{
				auto const& xAxisDirection = csp->m_Position->m_RefDirection->m_DirectionRatios;
				if (xAxisDirection[0] && xAxisDirection[1])
				{
					rotation = buw::createRotationMatrix(buw::Vector2d(xAxisDirection[0]->m_value, xAxisDirection[1]->m_value));
				}
			}
		}

		// Compute the profile curve, adjusted by the local transformation.
		// Construction starts at the lower left corner and goes CCW.
		if (!csp->m_OverallDepth || !csp->m_BottomFlangeWidth || !csp->m_TopFlangeWidth
			|| !csp->m_WebThickness || !csp->m_TopFlangeThickness || !csp->m_BottomFlangeThickness)
			throw buw::Exception("Mandatory profile attribute missing.");
		double const topWidth_2 = csp->m_TopFlangeWidth->m_value / 2.0;
		double const bottomWidth_2 = csp->m_BottomFlangeWidth->m_value / 2.0;
		double const height_2 = csp->m_OverallDepth->m_value / 2.0;
		double const topThickness = csp->m_TopFlangeThickness->m_value;
		double const bottomThickness = csp->m_BottomFlangeThickness->m_value;
		double const webThickness_2 = csp->m_WebThickness->m_value / 2.0;
		// Optionals:
		double const bottomFilletRadius = csp->m_BottomFlangeFilletRadius ? csp->m_BottomFlangeFilletRadius->m_value : -1.0;
		double const topFilletRadius = csp->m_TopFlangeFilletRadius ? csp->m_TopFlangeFilletRadius->m_value : -1.0;
		// Not documented well enough to be supported:
		if (csp->m_BottomFlangeEdgeRadius && csp->m_BottomFlangeEdgeRadius->m_value > 0.0)
			BLUE_LOG(warning) << "BottomFlangeEdgeRadius not supported";
		if (csp->m_TopFlangeEdgeRadius && csp->m_TopFlangeEdgeRadius->m_value > 0.0)
			BLUE_LOG(warning) << "TopFlangeEdgeRadius not supported";
		if (csp->m_BottomFlangeSlope && csp->m_BottomFlangeSlope->m_value > 0.0)
			BLUE_LOG(warning) << "BottomFlangeSlope not supported";
		if (csp->m_TopFlangeSlope && csp->m_TopFlangeSlope->m_value > 0.0)
			BLUE_LOG(warning) << "TopFlangeSlope not supported";

		// Right side (except first point)...
		segments.push_back(getLinearSegment(buw::Vector2d(-bottomWidth_2, -height_2), buw::Vector2d(bottomWidth_2, -height_2),
			buw::Vector2d(0.0, -1.0), rotation, translation, true));
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(bottomWidth_2, -height_2 + bottomThickness),
			buw::Vector2d(1.0, 0.0), rotation, translation));
		if (bottomFilletRadius > 0.0)
		{
			std::vector<buw::Vector2d> positions;
			std::vector<buw::Vector2d> normals;
			Tessellation::tessellateArc(
				rotation * (buw::Vector2d(webThickness_2 + bottomFilletRadius, -height_2 + bottomThickness) + translation),
				rotation * (buw::Vector2d(webThickness_2, -height_2 + bottomThickness + bottomFilletRadius) + translation),
				bottomFilletRadius,
				false,
				positions,
				&normals);
			std::vector<CrossSectionProfile::Vertex> segment;
			segment.push_back(Vertex(segments.back().back().position, rotation * buw::Vector2d(0.0, 1.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			segments.push_back(segment);
		}
		else
		{
			segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(webThickness_2, -height_2 + bottomThickness),
				buw::Vector2d(0.0, 1.0), rotation, translation));
		}
		if (topFilletRadius > 0.0)
		{
			std::vector<buw::Vector2d> positions;
			std::vector<buw::Vector2d> normals;
			Tessellation::tessellateArc(
				rotation * (buw::Vector2d(webThickness_2, height_2 - topThickness - topFilletRadius) + translation),
				rotation * (buw::Vector2d(webThickness_2 + topFilletRadius, height_2 - topThickness) + translation),
				topFilletRadius,
				false,
				positions,
				&normals);
			std::vector<CrossSectionProfile::Vertex> segment;
			segment.push_back(Vertex(segments.back().back().position, rotation * buw::Vector2d(1.0, 0.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			segments.push_back(segment);
		}
		else
		{
			segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(webThickness_2, height_2 - topThickness),
				buw::Vector2d(1.0, 0.0), rotation, translation));
		}
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(topWidth_2, height_2 - topThickness),
			buw::Vector2d(0.0, -1.0), rotation, translation));
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(topWidth_2, height_2),
			buw::Vector2d(1.0, 0.0), rotation, translation));
		// Left side...
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-topWidth_2, height_2),
			buw::Vector2d(0.0, 1.0), rotation, translation));
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-topWidth_2, height_2 - topThickness),
			buw::Vector2d(-1.0, 0.0), rotation, translation));
		if (topFilletRadius > 0.0)
		{
			std::vector<buw::Vector2d> positions;
			std::vector<buw::Vector2d> normals;
			Tessellation::tessellateArc(
				rotation * (buw::Vector2d(-webThickness_2 - topFilletRadius, height_2 - topThickness) + translation),
				rotation * (buw::Vector2d(-webThickness_2, height_2 - topThickness - topFilletRadius) + translation),
				topFilletRadius,
				false,
				positions,
				&normals);
			std::vector<CrossSectionProfile::Vertex> segment;
			segment.push_back(Vertex(segments.back().back().position, rotation * buw::Vector2d(0.0, -1.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			segments.push_back(segment);
		}
		else
		{
			segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-webThickness_2, height_2 - topThickness),
				buw::Vector2d(0.0, -1.0), rotation, translation));
		}
		if (bottomFilletRadius > 0.0)
		{
			std::vector<buw::Vector2d> positions;
			std::vector<buw::Vector2d> normals;
			Tessellation::tessellateArc(
				rotation * (buw::Vector2d(-webThickness_2, -height_2 + bottomThickness + bottomFilletRadius) + translation),
				rotation * (buw::Vector2d(-webThickness_2 - bottomFilletRadius, -height_2 + bottomThickness) + translation),
				bottomFilletRadius,
				false,
				positions,
				&normals);
			std::vector<CrossSectionProfile::Vertex> segment;
			segment.push_back(Vertex(segments.back().back().position, rotation * buw::Vector2d(-1.0, 0.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			segments.push_back(segment);
		}
		else
		{
			segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-webThickness_2, -height_2 + bottomThickness),
				buw::Vector2d(-1.0, 0.0), rotation, translation));
		}
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-bottomWidth_2, -height_2 + bottomThickness),
			buw::Vector2d(0.0, 1.0), rotation, translation));
		segments.push_back(getLinearSegment(segments.back().back().position, buw::Vector2d(-bottomWidth_2, -height_2),
			buw::Vector2d(-1.0, 0.0), rotation, translation));
	}

	CrossSectionProfile::~CrossSectionProfile()
	{
	}

}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
