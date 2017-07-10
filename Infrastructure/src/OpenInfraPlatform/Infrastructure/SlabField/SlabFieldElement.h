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

#ifndef __SLABFIELDELEMENT_H_4E0E43F3630D4764A9CD2FA6214EF8A6__
#define __SLABFIELDELEMENT_H_4E0E43F3630D4764A9CD2FA6214EF8A6__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include <OpenInfraPlatform/Infrastructure/SectionedSolid/SectionedSolidHorizontal.h>
#include <BlueFramework/Core/string.h>

#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API SlabFieldElement
{
public:
	typedef std::vector<SectionedSolidHorizontal> SectionedSolidVector;

	buw::String getName() const;
	void setName(std::wstring const& name);

	SectionedSolidVector const& getSectionedSolids() const;
	void addSectionedSolid(SectionedSolidHorizontal const& ssh);
	void addSectionedSolid(SectionedSolidVector const& sshs);

	int const id;

protected:
	explicit SlabFieldElement(int const id, std::wstring const& name);
	virtual ~SlabFieldElement();

private:
	buw::String name;
	SectionedSolidVector sectionedSolids;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::SlabFieldElement;
}

#endif // __SLABFIELDELEMENT_H_4E0E43F3630D4764A9CD2FA6214EF8A6__
