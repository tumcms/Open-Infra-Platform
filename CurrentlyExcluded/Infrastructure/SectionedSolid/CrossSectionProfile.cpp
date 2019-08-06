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

#include "CrossSectionProfile.h"

#include <IFC4X1.h>

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
	typedef std::function<std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const&(size_t const i)> PointSource;

	std::vector<CrossSectionProfile::Vertex> processLineStrip(
		PointSource const& pointSource,
		size_t const numPnts,
		bool const bRunsCCW)
	{
		buw::Vector2d prevPosition;
		buw::Vector2d nextPosition;
		std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const* pNextPoint = nullptr;
		std::vector<CrossSectionProfile::Vertex> segment;
		for (size_t i = 0; i < numPnts && numPnts > 1; ++i)
		{
			// Validate data.
			bool const bIsFirst = (i == 0);
			bool const bIsLast = (i == numPnts - 1);
			auto const& point = pointSource(i);
			pNextPoint = bIsLast ? nullptr : &(pointSource(i + 1));
			if (                        point.size() != 2 || !point[0]         || !point[1]          ||
				  (pNextPoint && (pNextPoint->size() != 2 || !(*pNextPoint)[0] || !(*pNextPoint)[1]))
				)
			{
				BLUE_LOG(warning) << "Cross section profile data is corrupt.";
				continue;
			}

			// Get positions.
			buw::Vector2d const position(point[0], point[1]);
			if (pNextPoint)
				nextPosition = buw::Vector2d((*pNextPoint)[0], (*pNextPoint)[1]);

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
				auto normal1 = buw::orthogonal(buw::Vector2d(position - prevPosition), !bRunsCCW).normalized();
				auto normal2 = buw::orthogonal(buw::Vector2d(nextPosition - position), !bRunsCCW).normalized();

				auto angle = buw::calculateAngleBetweenVectors(normal1, normal2);
				if (std::abs(angle) < 0.05) // < 2 degrees -> the angle is small enough for a continuous transition between the two surfaces
				{
					// Compute normal at half-angle.
					normal = (normal1 + normal2).normalized();
					// Add the segment, so that the number of segments stays the same
					segment.push_back(CrossSectionProfile::Vertex(position, normal));
				}
				else
				{
					// add the normal of the previous surface
					segment.push_back(CrossSectionProfile::Vertex(position, normal1));
					// add the normal of the next surface
					normal = normal2;
				}
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
			dArea += (p2[0] - p1[0])*(p2[1] + p1[1]);
		}

		return dArea;
	}

	bool isCCW(PointSource const& pointSource, size_t const numPnts)
	{
		return computeGaussArea(pointSource, numPnts) <= 0.0;
	}

	bool isCCW(
		std::vector<std::shared_ptr<IFC4X1::IfcSegmentIndexSelect>> const& segs,
		std::shared_ptr<IFC4X1::IfcCartesianPointList2D> points)
	{
		double dArea = 0.0;
		for (auto seg : segs)
		{
			if (!seg) continue;
			if (std::dynamic_pointer_cast<IFC4X1::IfcLineIndex>(seg))
			{
				auto lineSegment = std::static_pointer_cast<IFC4X1::IfcLineIndex>(seg);
				dArea += computeGaussArea(
					[&points, &lineSegment](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {return points->m_CoordList[lineSegment->m_vec[i]-1];},
					lineSegment->m_vec.size());
			}
			else if (std::dynamic_pointer_cast<IFC4X1::IfcArcIndex>(seg))
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

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IFC4X1::IfcArbitraryClosedProfileDef> csp)
		: segments()
	{
		if (!csp->m_OuterCurve)
			throw buw::Exception("Empty curve.");

		std::vector<std::vector<CrossSectionProfile::Vertex>> outerCurve;

		switch (csp->m_OuterCurve->m_entity_enum)
		{
		case IFC4X1::IFCINDEXEDPOLYCURVE:
		{
			auto curve = std::static_pointer_cast<IFC4X1::IfcIndexedPolyCurve>(csp->m_OuterCurve);
			if (!curve->m_Points)
				throw buw::Exception("Empty curve.");
			if (curve->m_Points->m_entity_enum != IFC4X1::IFCCARTESIANPOINTLIST2D)
				throw buw::Exception("Profile curve must be 2D.");
			auto points = std::static_pointer_cast<IFC4X1::IfcCartesianPointList2D>(curve->m_Points);

			// if Segments = empty -> all the points are connected using simple lines
			if (curve->m_Segments.empty())
			{
				auto const& pointSource = [&points](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {
					return points->m_CoordList[i];
				};
				outerCurve.push_back(processLineStrip(
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
					if (std::dynamic_pointer_cast<IFC4X1::IfcLineIndex>(segment))
					{
						auto lineSegment = std::static_pointer_cast<IFC4X1::IfcLineIndex>(segment);
						outerCurve.push_back(processLineStrip(
							[&points, &lineSegment](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {return points->m_CoordList[lineSegment->m_vec[i]-1];},
							lineSegment->m_vec.size(),
							bIsCCW));
					}
					else if (std::dynamic_pointer_cast<IFC4X1::IfcArcIndex>(segment))
					{
						auto arcSegment = std::static_pointer_cast<IFC4X1::IfcArcIndex>(segment);
						throw buw::NotImplementedYetException("Arc segments not yet implemented.");
					}
					else
					{
						throw buw::Exception("Unknown segment type.");
					}
				}
			}
		} break;
		case IFC4X1::IFCPOLYLINE:
		{
			auto curve = std::static_pointer_cast<IFC4X1::IfcPolyline>(csp->m_OuterCurve);
			if (curve->m_Points.size() == 0)
				throw buw::Exception("Empty polyline.");

			// translate from 3d to 2d (polyline have as x = 0.0)
			std::vector<std::shared_ptr<IFC4X1::IfcCartesianPoint>> points2d;
			if (curve->m_Points[0]->m_Coordinates.size() == 2)
				points2d = curve->m_Points;
			// translate from 3d to 2d (polyline have as x = 0.0)
			else if (curve->m_Points[0]->m_Coordinates.size() == 3)
				for (auto point : curve->m_Points)
				{
					std::shared_ptr<IFC4X1::IfcCartesianPoint> p(new IFC4X1::IfcCartesianPoint());
					p->m_Coordinates.push_back(point->m_Coordinates[1]);
					p->m_Coordinates.push_back(point->m_Coordinates[2]);
					points2d.push_back(p);
				}
			else
				throw buw::Exception("Polyline points' coordinates number not supported.");
			auto const& pointSource = [&points2d](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {
				return points2d[i]->m_Coordinates;
			};

			outerCurve.push_back(processLineStrip(
				pointSource,
				curve->m_Points.size(),
				isCCW(pointSource, curve->m_Points.size())));
		} break;
		default:
			throw buw::NotImplementedYetException("Unimplemented profile curve type.");
		}

		segments.push_back(outerCurve);

		if (csp->m_entity_enum == IFC4X1::IFCARBITRARYPROFILEDEFWITHVOIDS )
		{
			auto const& profile = std::static_pointer_cast<IFC4X1::IfcArbitraryProfileDefWithVoids>(csp);

			for (auto& _innerCurve : profile->m_InnerCurves)
			{
				std::vector<std::vector<CrossSectionProfile::Vertex>> innerCurve;
				switch (_innerCurve->m_entity_enum)
				{
				case IFC4X1::IFCPOLYLINE:
				{
					auto curve = std::static_pointer_cast<IFC4X1::IfcPolyline>(_innerCurve);
					if (curve->m_Points.size() == 0)
						throw buw::Exception("Empty polyline.");

					std::vector<std::shared_ptr<IFC4X1::IfcCartesianPoint>> points2d;
					if (curve->m_Points[0]->m_Coordinates.size() == 2)
						points2d = curve->m_Points;
					// translate from 3d to 2d (polyline have as x = 0.0)
					else if (curve->m_Points[0]->m_Coordinates.size() == 3)
						for (auto point : curve->m_Points)
						{
							std::shared_ptr<IFC4X1::IfcCartesianPoint> p(new IFC4X1::IfcCartesianPoint());
							p->m_Coordinates.push_back(point->m_Coordinates[1]);
							p->m_Coordinates.push_back(point->m_Coordinates[2]);
							points2d.push_back(p);
						}
					else
						throw buw::Exception("Polyline points' coordinates number not supported.");
					auto const& pointSource = [&points2d](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {
						return points2d[i]->m_Coordinates;
					};

					innerCurve.push_back(processLineStrip(
						pointSource,
						curve->m_Points.size(),
						!isCCW(pointSource, curve->m_Points.size())));
				} break;
				default:
					throw buw::NotImplementedYetException("Unimplemented profile curve type.");
				}
				segments.push_back(innerCurve);
			}

		}
	}

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IFC4X1::IfcAsymmetricIShapeProfileDef> csp)
		: segments()
	{
		std::vector<std::vector<CrossSectionProfile::Vertex>> outerCurve;

		// Get the local profile transformation (IfcParameterizedProfileDef).
		buw::Vector2d translation(0.0, 0.0);
		buw::Matrix22d rotation = buw::Matrix22d::Identity();
		if (csp->m_Position)
		{
			if (csp->m_Position->m_Location && csp->m_Position->m_Location->m_Coordinates.size() == 2)
			{
				auto const& coords = csp->m_Position->m_Location->m_Coordinates;
				double const x = (coords[0] ? coords[0] : 0.0);
				double const y = (coords[1] ? coords[1] : 0.0);
				translation[0] = x;
				translation[1] = y;
			}
			if (csp->m_Position->m_RefDirection && csp->m_Position->m_RefDirection->m_DirectionRatios.size() == 2)
			{
				auto const& xAxisDirection = csp->m_Position->m_RefDirection->m_DirectionRatios;
				if (xAxisDirection[0] && xAxisDirection[1])
				{
					rotation = buw::createRotationMatrix(buw::Vector2d(xAxisDirection[0], xAxisDirection[1]));
				}
			}
		}

		// Compute the profile curve, adjusted by the local transformation.
		// Construction starts at the lower left corner and goes CCW.
		if (!csp->m_OverallDepth || !csp->m_BottomFlangeWidth || !csp->m_TopFlangeWidth
			|| !csp->m_WebThickness || !csp->m_TopFlangeThickness || !csp->m_BottomFlangeThickness)
			throw buw::Exception("Mandatory profile attribute missing.");
		double const topWidth_2 = csp->m_TopFlangeWidth / 2.0;
		double const bottomWidth_2 = csp->m_BottomFlangeWidth / 2.0;
		double const height_2 = csp->m_OverallDepth / 2.0;
		double const topThickness = csp->m_TopFlangeThickness;
		double const bottomThickness = csp->m_BottomFlangeThickness;
		double const webThickness_2 = csp->m_WebThickness / 2.0;
		// Optionals:
		double const bottomFilletRadius = csp->m_BottomFlangeFilletRadius ? csp->m_BottomFlangeFilletRadius : -1.0;
		double const topFilletRadius = csp->m_TopFlangeFilletRadius ? csp->m_TopFlangeFilletRadius : -1.0;
		// Not documented well enough to be supported:
		if (csp->m_BottomFlangeEdgeRadius && csp->m_BottomFlangeEdgeRadius > 0.0)
			BLUE_LOG(warning) << "BottomFlangeEdgeRadius not supported";
		if (csp->m_TopFlangeEdgeRadius && csp->m_TopFlangeEdgeRadius > 0.0)
			BLUE_LOG(warning) << "TopFlangeEdgeRadius not supported";
		if (csp->m_BottomFlangeSlope && csp->m_BottomFlangeSlope > 0.0)
			BLUE_LOG(warning) << "BottomFlangeSlope not supported";
		if (csp->m_TopFlangeSlope && csp->m_TopFlangeSlope > 0.0)
			BLUE_LOG(warning) << "TopFlangeSlope not supported";

		// Right side (except first point)...
		outerCurve.push_back(getLinearSegment(buw::Vector2d(-bottomWidth_2, -height_2), buw::Vector2d(bottomWidth_2, -height_2),
			buw::Vector2d(0.0, -1.0), rotation, translation, true));
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(bottomWidth_2, -height_2 + bottomThickness),
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
			segment.push_back(Vertex(outerCurve.back().back().position, rotation * buw::Vector2d(0.0, 1.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			outerCurve.push_back(segment);
		}
		else
		{
			outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(webThickness_2, -height_2 + bottomThickness),
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
			segment.push_back(Vertex(outerCurve.back().back().position, rotation * buw::Vector2d(1.0, 0.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			outerCurve.push_back(segment);
		}
		else
		{
			outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(webThickness_2, height_2 - topThickness),
				buw::Vector2d(1.0, 0.0), rotation, translation));
		}
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(topWidth_2, height_2 - topThickness),
			buw::Vector2d(0.0, -1.0), rotation, translation));
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(topWidth_2, height_2),
			buw::Vector2d(1.0, 0.0), rotation, translation));
		// Left side...
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-topWidth_2, height_2),
			buw::Vector2d(0.0, 1.0), rotation, translation));
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-topWidth_2, height_2 - topThickness),
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
			segment.push_back(Vertex(outerCurve.back().back().position, rotation * buw::Vector2d(0.0, -1.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			outerCurve.push_back(segment);
		}
		else
		{
			outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-webThickness_2, height_2 - topThickness),
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
			segment.push_back(Vertex(outerCurve.back().back().position, rotation * buw::Vector2d(-1.0, 0.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			outerCurve.push_back(segment);
		}
		else
		{
			outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-webThickness_2, -height_2 + bottomThickness),
				buw::Vector2d(-1.0, 0.0), rotation, translation));
		}
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-bottomWidth_2, -height_2 + bottomThickness),
			buw::Vector2d(0.0, 1.0), rotation, translation));
		outerCurve.push_back(getLinearSegment(outerCurve.back().back().position, buw::Vector2d(-bottomWidth_2, -height_2),
			buw::Vector2d(-1.0, 0.0), rotation, translation));

		segments.push_back(outerCurve);
	}

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IFC4X1::IfcCircleProfileDef> csp)
		: segments()
	{
		std::vector<std::vector<CrossSectionProfile::Vertex>> outerCurve;
		double r = csp->m_Radius;

		std::vector<buw::Vector2d> points;
		points.push_back(buw::Vector2d( r,  0));
		points.push_back(buw::Vector2d( 0,  r));
		points.push_back(buw::Vector2d(-r,  0));
		points.push_back(buw::Vector2d( 0, -r));
		points.push_back(buw::Vector2d(r, 0));
		for( auto p = points.begin(), pprev = p++; p != points.end(); ++p, ++pprev )
		{
			std::vector<buw::Vector2d> positions;
			std::vector<buw::Vector2d> normals;
			Tessellation::tessellateArc(
				*pprev,
				*p,
				buw::Vector2d(0, 0),
				false,
				positions,
				&normals);
			std::vector<CrossSectionProfile::Vertex> segment;
			//segment.push_back(Vertex(outerCurve.back().back().position, rotation * buw::Vector2d(0.0, 1.0)));
			for (auto positionsIt = positions.begin(), normalsIt = normals.begin(); positionsIt != positions.end(); ++positionsIt, ++normalsIt)
				segment.push_back(Vertex(*positionsIt, *normalsIt));
			outerCurve.push_back(segment);
		}
		segments.push_back(outerCurve);
	}

	CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IFC4X1::IfcRectangleProfileDef> csp)
		: segments()
	{
		std::vector<std::vector<CrossSectionProfile::Vertex>> outerCurve;
		std::vector<std::shared_ptr<IFC4X1::IfcCartesianPoint>> points2d;
		
		std::shared_ptr<IFC4X1::IfcLengthMeasure> left (std::make_shared < IFC4X1::IfcLengthMeasure>(-0.5 * csp->m_XDim));
		std::shared_ptr<IFC4X1::IfcLengthMeasure> right(std::make_shared < IFC4X1::IfcLengthMeasure>( 0.5 * csp->m_XDim));
		std::shared_ptr<IFC4X1::IfcLengthMeasure> down (std::make_shared < IFC4X1::IfcLengthMeasure>(-0.5 * csp->m_YDim));
		std::shared_ptr<IFC4X1::IfcLengthMeasure> top  (std::make_shared < IFC4X1::IfcLengthMeasure>( 0.5 * csp->m_YDim));

		std::shared_ptr<IFC4X1::IfcCartesianPoint> LD(new IFC4X1::IfcCartesianPoint());
		LD->m_Coordinates.push_back(left);
		LD->m_Coordinates.push_back(down);
		points2d.push_back(LD);
		std::shared_ptr<IFC4X1::IfcCartesianPoint> LT(new IFC4X1::IfcCartesianPoint());
		LT->m_Coordinates.push_back(left);
		LT->m_Coordinates.push_back(top);
		points2d.push_back(LT);
		std::shared_ptr<IFC4X1::IfcCartesianPoint> RT(new IFC4X1::IfcCartesianPoint());
		RT->m_Coordinates.push_back(right);
		RT->m_Coordinates.push_back(top);
		points2d.push_back(RT);
		std::shared_ptr<IFC4X1::IfcCartesianPoint> RD(new IFC4X1::IfcCartesianPoint());
		RD->m_Coordinates.push_back(right);
		RD->m_Coordinates.push_back(down);
		points2d.push_back(RD);
		points2d.push_back(LD);


		auto const& pointSource = [&points2d](size_t const i)->std::vector<std::shared_ptr<IFC4X1::IfcLengthMeasure>> const& {
			return points2d[i]->m_Coordinates;
		};
		
		outerCurve.push_back(processLineStrip(
			pointSource,
			5,
			isCCW(pointSource, 5)));

		segments.push_back(outerCurve);
	}

	CrossSectionProfile::~CrossSectionProfile()
	{
	}

}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
