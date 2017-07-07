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
#ifndef OpenInfraPlatform_Infrastructure_crossSection_81825b1b_ad76_4ef0_9bf4_de97d2db4170_h
#define OpenInfraPlatform_Infrastructure_crossSection_81825b1b_ad76_4ef0_9bf4_de97d2db4170_h

#include "OpenInfraPlatform/Infrastructure/OIPInfrastructure.h"
#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/IfcAlignment1x1/IfcAlignment1x1Entities.h"
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/Math/Vector.h>
#include <BlueFramework/Core/memory.h>
#include <boost/noncopyable.hpp>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

struct BLUEINFRASTRUCTURE_API eDesignCrossSectionSide {
	enum Enum { left, right, none };
};

class BLUEINFRASTRUCTURE_API CrossSectionPoint {
public:
	CrossSectionPoint(){};
	virtual ~CrossSectionPoint(){};

	buw::Vector2d position;
	std::string code;
};

class BLUEINFRASTRUCTURE_API DesignCrossSectionProfile {
public:
	DesignCrossSectionProfile(){};
	virtual ~DesignCrossSectionProfile(){};

	std::string name;
	bool closedArea = false;
	std::vector<buw::ReferenceCounted<CrossSectionPoint>> crossSectionsPoints;
	eDesignCrossSectionSide side;
};

class BLUEINFRASTRUCTURE_API CrossSectionProfile {
public:
	CrossSectionProfile(){};
	CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcArbitraryClosedProfileDef> csp);
	CrossSectionProfile(std::shared_ptr<IfcAlignment1x1::IfcAsymmetricIShapeProfileDef> csp);
	virtual ~CrossSectionProfile(){};

	std::string name;
	std::vector<buw::Vector2d> pntList2D;
};

class BLUEINFRASTRUCTURE_API CrossSectionStatic {
public:
	CrossSectionStatic();
	virtual ~CrossSectionStatic(){};

	double stationing;
	void addCrossSectionProfile(buw::ReferenceCounted<CrossSectionProfile> csSurface);
	int getCrossSectionProfileCount();
	buw::ReferenceCounted<CrossSectionProfile> getCrossSectionProfile(const int index);

	void addDesignCrossSectionProfile(buw::ReferenceCounted<DesignCrossSectionProfile> csDesignSurface);
	int getDesignCrossSectionProfileCount();
	int getClosedDesignCrossSectionProfileCount();
	int getOpenDesignCrossSectionProfileCount();

	//! All design cross sections
	buw::ReferenceCounted<DesignCrossSectionProfile> getDesignCrossSectionProfile(const int index);

	//! Filtered cross sections. Only closed design cross sections
	buw::ReferenceCounted<DesignCrossSectionProfile> getClosedDesignCrossSectionProfile(const int index);

	//!  Filtered cross sections. Only open cross sections (ground, etc.).
	buw::ReferenceCounted<DesignCrossSectionProfile> getOpenDesignCrossSectionProfile(const int index);

	static bool smallerStation(const buw::ReferenceCounted<CrossSectionStatic>& a, const buw::ReferenceCounted<CrossSectionStatic>& b);

private:
	std::vector<buw::ReferenceCounted<CrossSectionProfile>> crossSectSurfaceList_;

	// Filtered lists
	std::vector<buw::ReferenceCounted<DesignCrossSectionProfile>> closedDesignCrossSectSurfaceList_;
	std::vector<buw::ReferenceCounted<DesignCrossSectionProfile>> openDesignCrossSectSurfaceList_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw {
	using OpenInfraPlatform::Infrastructure::eDesignCrossSectionSide;
	using OpenInfraPlatform::Infrastructure::CrossSectionPoint;
	using OpenInfraPlatform::Infrastructure::CrossSectionStatic;
	using OpenInfraPlatform::Infrastructure::CrossSectionProfile;
	using OpenInfraPlatform::Infrastructure::DesignCrossSectionProfile;
}

#endif // end define OpenInfraPlatform_Infrastructure_crossSection_81825b1b_ad76_4ef0_9bf4_de97d2db4170_h
