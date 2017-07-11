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

#include "SlabFieldModel.h"

#include <algorithm>
#include <stdexcept>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

SlabFieldModel::SlabFieldModel()
	: slabFieldElements_()
{
}

SlabFieldModel::~SlabFieldModel()
{
}

SlabFieldModel* SlabFieldModel::createFlatCopy(SlabFieldModel const& src)
{
	return new SlabFieldModel(src);
}

size_t SlabFieldModel::getItemCount() const
{
	return slabFieldElements_.size();
}

std::shared_ptr<SlabFieldElement> SlabFieldModel::getItem(size_t const index) const
{
	return slabFieldElements_[index];
}

std::shared_ptr<SlabFieldElement> SlabFieldModel::getItemById(size_t const id) const
{
	for (auto const& sfe : slabFieldElements_)
		if (sfe && (sfe->id == id)) return sfe;

	return nullptr;
}

std::vector<std::shared_ptr<SlabFieldElement>> const& SlabFieldModel::getAllItems() const
{
	return slabFieldElements_;
}

void SlabFieldModel::addItem(std::shared_ptr<SlabFieldElement> const& slabFieldElement)
{
	slabFieldElements_.push_back(slabFieldElement);
}

void SlabFieldModel::deleteItem(std::shared_ptr<SlabFieldElement> const& slabFieldElement)
{
	auto const& findIt = std::find(slabFieldElements_.begin(), slabFieldElements_.end(), slabFieldElement);
	if(findIt != slabFieldElements_.end())
		slabFieldElements_.erase(findIt);
	else
		throw std::runtime_error("Deletion of slab field element failed.");
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
