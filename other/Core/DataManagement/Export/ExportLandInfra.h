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
#ifndef OpenInfraPlatform_Infrastructure_LandInfraExport_FF511FFA_0B59_4A95_87C1_E183FDA04456_h
#define OpenInfraPlatform_Infrastructure_LandInfraExport_FF511FFA_0B59_4A95_87C1_E183FDA04456_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"

namespace OpenInfraPlatform {
	namespace Infrastructure {
		class BLUEINFRASTRUCTURE_API ExportLandInfra : public Export {
		public:
			/*Exporter for data in LandInfra XML specification. Throws an exception if behaviour is undefined.*/
			ExportLandInfra(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);
		};
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
	using OpenInfraPlatform::Infrastructure::ExportLandInfra;
}
#endif //#define OpenInfraPlatform_Infrastructure_LandInfraExport_FF511FFA_0B59_4A95_87C1_E183FDA04456_h