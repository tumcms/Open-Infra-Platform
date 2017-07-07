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

#include "CrossSectionStatic.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Types.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1EntityEnums.h"
#include <OpenInfraPlatform/Infrastructure/Tessellation/Tessellation.h>
#include <BlueFramework/Core/Math/util.h>
#include <BlueFramework/Core/Math/Matrix.h>
#include <BlueFramework/Core/Diagnostics/log.h>

OpenInfraPlatform::Infrastructure::CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcArbitraryClosedProfileDef> csp)
	: name(csp->m_ProfileName ? csp->m_ProfileName->m_value : "")
	, pntList2D()
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
			for (auto const& point : points->m_CoordList)
			{
				if (point.size() != 2 || !point[0] || !point[1])
				{
					BLUE_LOG(warning) << "Cross section profile data is corrupt.";
					continue;
				}
				pntList2D.push_back(buw::Vector2d(point[0]->m_value, point[1]->m_value));
			}
		}
		else
		{
			for (auto segment : curve->m_Segments)
			{
				if (!segment) continue;
				if (std::dynamic_pointer_cast<IfcAlignment1x1::IfcLineIndex>(segment))
				{
					auto lineSegment = std::static_pointer_cast<IfcAlignment1x1::IfcLineIndex>(segment);
					for (int i : lineSegment->m_vec)
					{
						auto const& point = points->m_CoordList[i];
						if (point.size() != 2 || !point[0] || !point[1])
						{
							BLUE_LOG(warning) << "Cross section profile data is corrupt.";
							continue;
						}
						pntList2D.push_back(buw::Vector2d(point[0]->m_value, point[1]->m_value));
					}
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

OpenInfraPlatform::Infrastructure::CrossSectionProfile::CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcAsymmetricIShapeProfileDef> csp)
	: name(csp->m_ProfileName ? csp->m_ProfileName->m_value : "")
	, pntList2D()
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
	if(csp->m_BottomFlangeEdgeRadius && csp->m_BottomFlangeEdgeRadius->m_value > 0.0)
		BLUE_LOG(warning) << "BottomFlangeEdgeRadius not supported";
	if(csp->m_TopFlangeEdgeRadius && csp->m_TopFlangeEdgeRadius->m_value > 0.0)
		BLUE_LOG(warning) << "TopFlangeEdgeRadius not supported";
	if(csp->m_BottomFlangeSlope && csp->m_BottomFlangeSlope->m_value > 0.0)
		BLUE_LOG(warning) << "BottomFlangeSlope not supported";
	if(csp->m_TopFlangeSlope && csp->m_TopFlangeSlope->m_value > 0.0)
		BLUE_LOG(warning) << "TopFlangeSlope not supported";

	// Right side (except first point)...
	pntList2D.push_back(rotation * (buw::Vector2d(-bottomWidth_2, -height_2) + translation));
	pntList2D.push_back(rotation * (buw::Vector2d(bottomWidth_2, -height_2) + translation));
	pntList2D.push_back(rotation * (buw::Vector2d(bottomWidth_2, -height_2+bottomThickness) + translation));
	if (bottomFilletRadius > 0.0)
	{
		std::vector<buw::Vector2d> const& arc = Tessellation::tessellateArc(
			rotation * (buw::Vector2d(webThickness_2 + bottomFilletRadius, -height_2 + bottomThickness) + translation),
			rotation * (buw::Vector2d(webThickness_2, -height_2 + bottomThickness + bottomFilletRadius) + translation),
			bottomFilletRadius,
			false);
		pntList2D.insert(pntList2D.end(), arc.begin(), arc.end());
	}
	else
	{
		pntList2D.push_back(rotation * (buw::Vector2d(webThickness_2, -height_2+bottomThickness) + translation));
	}
	if (topFilletRadius > 0.0)
	{
		std::vector<buw::Vector2d> const& arc = Tessellation::tessellateArc(
			rotation * (buw::Vector2d(webThickness_2, height_2-topThickness-topFilletRadius) + translation),
			rotation * (buw::Vector2d(webThickness_2+topFilletRadius, height_2-topThickness) + translation),
			topFilletRadius,
			false);
		pntList2D.insert(pntList2D.end(), arc.begin(), arc.end());
	}
	else
	{
		pntList2D.push_back(rotation * (buw::Vector2d(webThickness_2, height_2-topThickness) + translation));
	}
	pntList2D.push_back(rotation * (buw::Vector2d(topWidth_2, height_2-topThickness) + translation));
	pntList2D.push_back(rotation * (buw::Vector2d(topWidth_2, height_2) + translation));
	// Left side...
	pntList2D.push_back(rotation * (buw::Vector2d(-topWidth_2, height_2) + translation));
	pntList2D.push_back(rotation * (buw::Vector2d(-topWidth_2, height_2-topThickness) + translation));
	if (topFilletRadius > 0.0)
	{
		std::vector<buw::Vector2d> const& arc = Tessellation::tessellateArc(
			rotation * (buw::Vector2d(-webThickness_2-topFilletRadius, height_2-topThickness) + translation),
			rotation * (buw::Vector2d(-webThickness_2, height_2-topThickness-topFilletRadius) + translation),
			topFilletRadius,
			false);
		pntList2D.insert(pntList2D.end(), arc.begin(), arc.end());
	}
	else
	{
		pntList2D.push_back(rotation * (buw::Vector2d(-webThickness_2, height_2-topThickness) + translation));
	}
	if (bottomFilletRadius > 0.0)
	{
		std::vector<buw::Vector2d> const& arc = Tessellation::tessellateArc(
			rotation * (buw::Vector2d(-webThickness_2, -height_2+bottomThickness+bottomFilletRadius) + translation),
			rotation * (buw::Vector2d(-webThickness_2-bottomFilletRadius, -height_2+bottomThickness) + translation),
			bottomFilletRadius,
			false);
		pntList2D.insert(pntList2D.end(), arc.begin(), arc.end());
	}
	else
	{
		pntList2D.push_back(rotation * (buw::Vector2d(-webThickness_2, -height_2+bottomThickness) + translation));
	}
	pntList2D.push_back(rotation * (buw::Vector2d(-bottomWidth_2, -height_2+bottomThickness) + translation));
	pntList2D.push_back(pntList2D.front()); // Close curve.
}

// ---------------------------------------------------------------------------------------------------------------------------
// Cross section methods
// ---------------------------------------------------------------------------------------------------------------------------
void OpenInfraPlatform::Infrastructure::CrossSectionStatic::addCrossSectionProfile(buw::ReferenceCounted<buw::CrossSectionProfile> csSurface)
{
	crossSectSurfaceList_.push_back(csSurface);
}

int OpenInfraPlatform::Infrastructure::CrossSectionStatic::getCrossSectionProfileCount()
{
	return static_cast<int>(crossSectSurfaceList_.size());
}

buw::ReferenceCounted<buw::CrossSectionProfile> OpenInfraPlatform::Infrastructure::CrossSectionStatic::getCrossSectionProfile(const int index)
{
	return crossSectSurfaceList_[index];
}

// ---------------------------------------------------------------------------------------------------------------------------
// Design cross section methods
// ---------------------------------------------------------------------------------------------------------------------------
void OpenInfraPlatform::Infrastructure::CrossSectionStatic::addDesignCrossSectionProfile(buw::ReferenceCounted<DesignCrossSectionProfile> csDesignSurface)
{
	if(csDesignSurface->closedArea)
	{ 
		closedDesignCrossSectSurfaceList_.push_back(csDesignSurface);
	}
	else
	{
		if(csDesignSurface->crossSectionsPoints.size()==2)
		{
			if(buw::round((csDesignSurface->crossSectionsPoints[1]->position-csDesignSurface->crossSectionsPoints[0]->position).norm(),5)!=0.0)
				openDesignCrossSectSurfaceList_.push_back(csDesignSurface);
		}
		else
		{ 
			openDesignCrossSectSurfaceList_.push_back(csDesignSurface);
		}
	}
}

int OpenInfraPlatform::Infrastructure::CrossSectionStatic::getDesignCrossSectionProfileCount()
{
	return static_cast<int>((closedDesignCrossSectSurfaceList_.size()+openDesignCrossSectSurfaceList_.size()));
}

buw::ReferenceCounted<buw::DesignCrossSectionProfile> OpenInfraPlatform::Infrastructure::CrossSectionStatic::getDesignCrossSectionProfile(const int index)
{
	if(index<closedDesignCrossSectSurfaceList_.size()) 
		return closedDesignCrossSectSurfaceList_[index];
	else 
		return openDesignCrossSectSurfaceList_[index-closedDesignCrossSectSurfaceList_.size()];
}

// ---------------------------------------------------------------------------------------------------------------------------
// Closed design cross section methods
// ---------------------------------------------------------------------------------------------------------------------------
int OpenInfraPlatform::Infrastructure::CrossSectionStatic::getClosedDesignCrossSectionProfileCount()
{
	return static_cast<int>(closedDesignCrossSectSurfaceList_.size());
}

buw::ReferenceCounted<buw::DesignCrossSectionProfile> OpenInfraPlatform::Infrastructure::CrossSectionStatic::getClosedDesignCrossSectionProfile(const int index)
{
	return closedDesignCrossSectSurfaceList_[index];
}


// ---------------------------------------------------------------------------------------------------------------------------
// Open design cross section methods
// ---------------------------------------------------------------------------------------------------------------------------
int OpenInfraPlatform::Infrastructure::CrossSectionStatic::getOpenDesignCrossSectionProfileCount()
{
	return static_cast<int>(openDesignCrossSectSurfaceList_.size());
}

buw::ReferenceCounted<buw::DesignCrossSectionProfile> OpenInfraPlatform::Infrastructure::CrossSectionStatic::getOpenDesignCrossSectionProfile(const int index)
{
	return openDesignCrossSectSurfaceList_[index];
}

bool OpenInfraPlatform::Infrastructure::CrossSectionStatic::smallerStation(const buw::ReferenceCounted<CrossSectionStatic>& a, const buw::ReferenceCounted<CrossSectionStatic>& b)
{
	return a->stationing < b->stationing;
}

OpenInfraPlatform::Infrastructure::CrossSectionStatic::CrossSectionStatic()
{

}
