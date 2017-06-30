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
#include <BlueFramework/Core/Math/util.h>

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
