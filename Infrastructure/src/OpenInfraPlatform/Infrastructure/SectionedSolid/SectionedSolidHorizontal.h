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

#ifndef __SECTIONEDSOLIDHORIZONTAL_H_B07F90B2FC3A4129BFEB2E08591E8DD3__
#define __SECTIONEDSOLIDHORIZONTAL_H_B07F90B2FC3A4129BFEB2E08591E8DD3__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include <OpenInfraPlatform/Infrastructure/Alignment/Alignment3DBased3D.h>
#include <OpenInfraPlatform/Infrastructure/CrossSection/CrossSectionStatic.h>

#include <memory>
#include <vector>
#include <utility>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API SectionedSolidHorizontal
{
public:
	typedef std::shared_ptr<Alignment3DBased3D> AnchorPoints; // The profile reference points.
	typedef std::vector<std::pair<buw::Vector2d, buw::Vector2d>> HorizTangentAndNormalVector; // Used to orient the 2D profiles in the 3D target space.
	typedef std::vector<std::shared_ptr<CrossSectionProfile>> ProfileVector; // Vector of profiles; one per reference point.

	explicit SectionedSolidHorizontal(
		AnchorPoints directrix,
		HorizTangentAndNormalVector const& tangentsAndNormals,
		ProfileVector const& profiles);
	virtual ~SectionedSolidHorizontal();

	AnchorPoints const& getAnchors() const;
	HorizTangentAndNormalVector const& getTangentsAndNormals() const;
	ProfileVector const& getProfiles() const;

private:
	AnchorPoints anchors;
	HorizTangentAndNormalVector tangentsAndNormals;
	ProfileVector profiles;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::SectionedSolidHorizontal;
}

#endif // __SECTIONEDSOLIDHORIZONTAL_H_B07F90B2FC3A4129BFEB2E08591E8DD3__
