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

#include "Import.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_BEGIN

Import::Import(const std::string& filename) : filename_(filename) {
	alignmentModel_ = buw::makeReferenceCounted<buw::AlignmentModel>();
	digitalElevationModel_ = buw::makeReferenceCounted<buw::DigitalElevationModel>();
	trafficSignModel_ = buw::makeReferenceCounted<buw::TrafficSignModel>();
	girderModel_ = buw::makeReferenceCounted<buw::GirderModel>();
	slabFieldModel_ = buw::makeReferenceCounted<buw::SlabFieldModel>();
}
buw::ReferenceCounted<buw::AlignmentModel> Import::getAlignmentModel() {
	return alignmentModel_;
}
buw::ReferenceCounted<buw::DigitalElevationModel> Import::getDigitalElevationModel() {
	return digitalElevationModel_;
}

buw::ReferenceCounted<buw::TrafficSignModel> Import::getTrafficSignModel() {
	return trafficSignModel_;
}

buw::ReferenceCounted<buw::GirderModel> Import::getGirderModel() {
	return girderModel_;
}

buw::ReferenceCounted<buw::SlabFieldModel> Import::getSlabFieldModel() {
	return slabFieldModel_;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_INFRASTRUCTURE_END