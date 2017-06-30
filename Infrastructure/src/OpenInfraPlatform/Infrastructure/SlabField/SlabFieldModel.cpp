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
	: slabFields_()
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
	return slabFields_.size();
}

std::shared_ptr<SlabField> SlabFieldModel::getItem(size_t const index) const
{
	return slabFields_[index];
}

std::shared_ptr<SlabField> SlabFieldModel::getItemById(size_t const id) const
{
	// FGI TODO
	//for (auto const& sf : slabFields_)
	//	if (sf->id == id) return sf;

	return nullptr;
}

std::vector<std::shared_ptr<SlabField>> const& SlabFieldModel::getAllItems() const
{
	return slabFields_;
}

void SlabFieldModel::addItem(std::shared_ptr<SlabField> const& slabField)
{
	slabFields_.push_back(slabField);
}

void SlabFieldModel::deleteItem(std::shared_ptr<SlabField> const& slabField)
{
	auto const& findIt = std::find(slabFields_.begin(), slabFields_.end(), slabField);
	if(findIt != slabFields_.end())
		slabFields_.erase(findIt);
	else
		throw std::runtime_error("Deltion of slab field failed.");
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END
