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

#ifndef __SLABFIELDMODEL_H_4F964D8615F44A9E980A0017774D2FB8__
#define __SLABFIELDMODEL_H_4F964D8615F44A9E980A0017774D2FB8__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include "SlabFieldElement.h"

#include <memory>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API SlabFieldModel
{
public:
	explicit SlabFieldModel();
	virtual ~SlabFieldModel();

	static SlabFieldModel* createFlatCopy(SlabFieldModel const& src);

	size_t getItemCount() const;

	std::shared_ptr<SlabFieldElement> getItem(size_t const index) const;
	std::shared_ptr<SlabFieldElement> getItemById(size_t const id) const;
	std::vector<std::shared_ptr<SlabFieldElement>> const& getAllItems() const;

	void addItem(std::shared_ptr<SlabFieldElement> const& slabFieldElement);
	void deleteItem(std::shared_ptr<SlabFieldElement> const& slabFieldElement);

private:
	std::vector<std::shared_ptr<SlabFieldElement>> slabFieldElements_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::SlabFieldModel;
}

#endif // __SLABFIELDMODEL_H_4F964D8615F44A9E980A0017774D2FB8__
