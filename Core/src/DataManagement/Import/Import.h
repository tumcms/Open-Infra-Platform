/*
    Copyright (c) 2018 Technical University of Munich
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

#include "DataManagement/General/Data.h"
#include "DataManagement/General/namespace.h"
#include <boost/noncopyable.hpp>

//#include "OpenInfraPlatform/Infrastructure/Alignment/AlignmentModel.h"
//#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/DigitalElevationModel.h"
//#include "OpenInfraPlatform/Infrastructure/ProxyModel/ProxyModel.h"
//#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/TrafficSignModel.h"
//#include "OpenInfraPlatform/Infrastructure/Girder/GirderModel.h"
//#include "OpenInfraPlatform/Infrastructure/SlabField/SlabFieldModel.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_BEGIN
//OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

class BLUEINFRASTRUCTURE_API Import : private boost::noncopyable {
public:
	Import(const std::string& filename);

	buw::ReferenceCounted<buw::AlignmentModel> getAlignmentModel();
	buw::ReferenceCounted<buw::DigitalElevationModel> getDigitalElevationModel();
	buw::ReferenceCounted<buw::TrafficSignModel> getTrafficSignModel();
	buw::ReferenceCounted<buw::GirderModel> getGirderModel();
	buw::ReferenceCounted<buw::SlabFieldModel> getSlabFieldModel();
	buw::ReferenceCounted<buw::ProxyModel> getProxyModel();

protected:
	std::string filename_;
	buw::ReferenceCounted<buw::AlignmentModel> alignmentModel_;
	buw::ReferenceCounted<buw::DigitalElevationModel> digitalElevationModel_;
	buw::ReferenceCounted<buw::TrafficSignModel> trafficSignModel_;
	buw::ReferenceCounted<buw::GirderModel> girderModel_;
	buw::ReferenceCounted<buw::SlabFieldModel> slabFieldModel_;
	buw::ReferenceCounted<buw::ProxyModel> proxyModel_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_END

namespace buw {
	using OpenInfraPlatform::Core::Import;
}
