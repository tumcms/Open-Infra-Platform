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

#include "OpenInfraPlatform/Infrastructure/namespace.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/TrafficSignModel.h"
#include "OpenInfraPlatform/Infrastructure/Girder/GirderModel.h"
#include "OpenInfraPlatform/Infrastructure/SlabField/SlabFieldModel.h"
#include <boost/noncopyable.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API Import : private boost::noncopyable
{
public:
	Import(const std::string& filename);

	buw::ReferenceCounted<buw::AlignmentModel>			getAlignmentModel();
	buw::ReferenceCounted<buw::DigitalElevationModel>	getDigitalElevationModel();
	buw::ReferenceCounted<buw::TrafficSignModel>		getTrafficSignModel();
	buw::ReferenceCounted<buw::GirderModel>				getGirderModel();
	buw::ReferenceCounted<buw::SlabFieldModel>			getSlabFieldModel();

protected:
	std::string											filename_;
	buw::ReferenceCounted<buw::AlignmentModel>			alignmentModel_;
	buw::ReferenceCounted<buw::DigitalElevationModel>	digitalElevationModel_;
	buw::ReferenceCounted<buw::TrafficSignModel>		trafficSignModel_;
	buw::ReferenceCounted<buw::GirderModel>				girderModel_;
	buw::ReferenceCounted<buw::SlabFieldModel>			slabFieldModel_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END

namespace buw
{
	using OpenInfraPlatform::Infrastructure::Import;
}
