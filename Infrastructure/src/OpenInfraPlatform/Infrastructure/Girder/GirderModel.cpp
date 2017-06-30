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

#include "GirderModel.h"

#include <algorithm>
#include <stdexcept>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

GirderModel::GirderModel()
	: girders_()
{
}

GirderModel::~GirderModel()
{
}

GirderModel* GirderModel::createFlatCopy(GirderModel const& src)
{
	return new GirderModel(src);
}

size_t GirderModel::getItemCount() const
{
	return girders_.size();
}

std::shared_ptr<Girder> GirderModel::getItem(size_t const index) const
{
	return girders_[index];
}

std::shared_ptr<Girder> GirderModel::getItemById(size_t const id) const
{
	// FGI TODO
	//for (auto const& g : girders_)
	//	if (g->id == id) return g;

	return nullptr;
}

std::vector<std::shared_ptr<Girder>> const& GirderModel::getAllItems() const
{
	return girders_;
}

void GirderModel::addItem(std::shared_ptr<Girder> const& girder)
{
	girders_.push_back(girder);
}

void GirderModel::deleteItem(std::shared_ptr<Girder> const& girder)
{
	auto const& findIt = std::find(girders_.begin(), girders_.end(), girder);
	if(findIt != girders_.end())
		girders_.erase(findIt);
	else
		throw std::runtime_error("Deltion of girder failed.");
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
