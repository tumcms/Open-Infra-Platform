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

#include "AlignmentModel.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

AlignmentModel::AlignmentModel()
{

}

AlignmentModel::~AlignmentModel()
{

}

buw::AxisAlignedBoundingBox3d AlignmentModel::getExtends() const
{
	// we run along along all alignments an determine the corresponding position
	// this my seem stupid at first glance, but in this way we have not to introduce
	// additional methods in the 2D alignment element class.
	if (alignments_.size() == 0)
	{
		return buw::AxisAlignedBoundingBox3d();
	}

	buw::Vector3d min_ = alignments_[0]->getPosition(0);
	buw::Vector3d max_ = alignments_[0]->getPosition(0);

	for (int i = 0; i < alignments_.size(); i++)
	{
		for (double s = alignments_[i]->getStartStation(); s < alignments_[i]->getEndStation(); s += 1.0)
		{
			auto p = alignments_[i]->getPosition(s);
			min_ = buw::minimizedVector(min_, p);
			max_ = buw::maximizedVector(max_, p);
		}
	}

	return buw::AxisAlignedBoundingBox3d(min_, max_);
}

void AlignmentModel::deleteAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment)
{
	auto iterator = std::find(alignments_.begin(), alignments_.end(), alignment);

	BLUE_ASSERT(iterator != alignments_.end(), "Invalid alignment");

	if (iterator != alignments_.end())
	{
		alignments_.erase(iterator);
	}
	else
	{
		throw std::runtime_error("Deltion of alignment failed.");
	}
}

void AlignmentModel::addAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment)
{
	alignments_.push_back(alignment);
}

std::vector<buw::ReferenceCounted<buw::IAlignment3D>> AlignmentModel::getAlignments()
{
	return alignments_;
}

buw::ReferenceCounted<buw::IAlignment3D> AlignmentModel::getAlignment(const int index) const
{
	return alignments_[index];
}

buw::ReferenceCounted<buw::IAlignment3D> AlignmentModel::getAlignmentById(const int id) const {
	if (alignments_.size() == 0)
	{
		return nullptr;
	}

	for (int i = 0; i < alignments_.size(); ++i) {
		if (alignments_[i]->getType() == buw::e3DAlignmentType::e2DBased) {
			buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignments_[i]);
			if (a->getId() == id)
				return a;
		}

	}

	return nullptr;
}

int AlignmentModel::getAlignmentCount() const
{
	return static_cast<int>(alignments_.size());
}

buw::AxisAlignedBoundingBox3d buw::AlignmentModel::getVerticalAlignmentExtends()
{
	buw::AxisAlignedBoundingBox3d b;

	bool firstFound = true;

	for (int i = 0; i < alignments_.size(); i++)
	{
		if (alignments_[i]->getType() == buw::e3DAlignmentType::e2DBased)
		{
			buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignments_[i]);

			if (firstFound)
			{
				firstFound = false;
				b = a->getVerticalAlignmentExtends();
			}
			else
			{
				auto u = buw::minimizedVector( b.getMinimum(), a->getVerticalAlignmentExtends().getMinimum() );
				auto v = buw::minimizedVector( b.getMaximum(), a->getVerticalAlignmentExtends().getMaximum() );
				b.setMinimum(u);
				b.setMaximum(v);
			}
		}
	}

	return b;
}

buw::AlignmentModel* buw::AlignmentModel::createFlatCopy(const AlignmentModel& src)
{
	return new AlignmentModel(src);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END