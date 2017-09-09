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

#ifndef __GIRDER_H_BBBFC8824A0E4CE4B432BE2C02B43E01__
#define __GIRDER_H_BBBFC8824A0E4CE4B432BE2C02B43E01__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include <OpenInfraPlatform/Infrastructure/SectionedSolid/SectionedSolidHorizontal.h>
#include <BlueFramework/Core/string.h>

#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API Girder
{
public:
	typedef std::vector<SectionedSolidHorizontal> SectionedSolidVector;

	explicit Girder(int const id, std::wstring const& name);
	virtual ~Girder();

	buw::String getName() const;
	void setName(std::wstring const& name);

	SectionedSolidVector const& getSectionedSolids() const;
	void addSectionedSolid(SectionedSolidHorizontal const& ssh);
	void addSectionedSolid(SectionedSolidVector const& sshs);

private:
	int const id;
	buw::String name;
	SectionedSolidVector sectionedSolids;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Girder;
}

#endif // __GIRDER_H_BBBFC8824A0E4CE4B432BE2C02B43E01__
