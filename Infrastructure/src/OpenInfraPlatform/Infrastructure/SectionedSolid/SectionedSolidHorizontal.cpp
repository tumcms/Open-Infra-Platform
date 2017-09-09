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

#include "SectionedSolidHorizontal.h"

#include <BlueFramework/Core/Exception.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

SectionedSolidHorizontal::SectionedSolidHorizontal(
	AnchorPoints directrix,
	HorizTangentAndNormalVector const& tangentsAndNormals,
	ProfileVector const& profiles)
	: anchors(directrix)
	, tangentsAndNormals(tangentsAndNormals)
	, profiles(profiles)
{
	if (anchors->getNumPoints() != tangentsAndNormals.size() || anchors->getNumPoints() != profiles.size())
		throw buw::Exception("Mismatch between number of profile positions/tangents and normals/profiles.");
}

SectionedSolidHorizontal::~SectionedSolidHorizontal()
{
}

SectionedSolidHorizontal::AnchorPoints const& SectionedSolidHorizontal::getAnchors() const
{
	return anchors;
}

SectionedSolidHorizontal::HorizTangentAndNormalVector const& SectionedSolidHorizontal::getTangentsAndNormals() const
{
	return tangentsAndNormals;
}

SectionedSolidHorizontal::ProfileVector const& SectionedSolidHorizontal::getProfiles() const
{
	return profiles;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
