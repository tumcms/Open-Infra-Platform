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

#pragma once
#ifndef OpenInfraPlatform_Data_AlignmentModel_6922ea21_8578_4afc_965a_b368145f716d_h
#define OpenInfraPlatform_Data_AlignmentModel_6922ea21_8578_4afc_965a_b368145f716d_h

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API AlignmentModel
{
public:
	AlignmentModel();

	virtual ~AlignmentModel();

	int getAlignmentCount() const;

	buw::ReferenceCounted<buw::IAlignment3D> getAlignment(const int index) const;

	buw::ReferenceCounted<buw::IAlignment3D> getAlignmentById(const int id) const;

	std::vector<buw::ReferenceCounted<buw::IAlignment3D>> getAlignments();

	void addAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment);

	void deleteAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment);

	static AlignmentModel* createFlatCopy(const AlignmentModel& src);

	buw::AxisAlignedBoundingBox3d getExtends() const;

	buw::AxisAlignedBoundingBox3d getVerticalAlignmentExtends();

private:				
	std::vector<buw::ReferenceCounted<buw::IAlignment3D>> alignments_;
}; // end class AlignmentModel

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::AlignmentModel;
}

#endif // end define OpenInfraPlatform_Data_AlignmentModel_6922ea21_8578_4afc_965a_b368145f716d_h
