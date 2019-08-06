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

#include "Export.h"

OpenInfraPlatform::Infrastructure::Export::Export(buw::ReferenceCounted<buw::AlignmentModel> am,
                                                  buw::ReferenceCounted<buw::DigitalElevationModel> dem,
                                                  buw::ReferenceCounted<buw::ProxyModel> pm,
                                                  const std::string& filename)
    : alignmentModel_(am), digitalElevationModel_(dem), proxyModel_(pm), filename_(filename) {
}

OpenInfraPlatform::Infrastructure::Export::Export(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename)
    : alignmentModel_(am), digitalElevationModel_(dem), proxyModel_(nullptr), filename_(filename) {
}
