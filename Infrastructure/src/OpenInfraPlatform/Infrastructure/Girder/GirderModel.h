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

#ifndef __GIRDERMODEL_H_C1012EE120474EE1BB91C246425C013C__
#define __GIRDERMODEL_H_C1012EE120474EE1BB91C246425C013C__

#include <OpenInfraPlatform/Infrastructure/namespace.h>
#include <OpenInfraPlatform/Infrastructure/OIPInfrastructure.h>
#include "Girder.h"

#include <memory>
#include <vector>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API GirderModel
{
public:
	explicit GirderModel();
	virtual ~GirderModel();

	static GirderModel* createFlatCopy(GirderModel const& src);

	size_t getItemCount() const;

	std::shared_ptr<Girder> getItem(size_t const index) const;
	std::shared_ptr<Girder> getItemById(size_t const id) const;
	std::vector<std::shared_ptr<Girder>> const& getAllItems() const;

	void addItem(std::shared_ptr<Girder> const& girder);
	void deleteItem(std::shared_ptr<Girder> const& girder);

private:
	std::vector<std::shared_ptr<Girder>> girders_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::GirderModel;
}

#endif // __GIRDERMODEL_H_C1012EE120474EE1BB91C246425C013C__
