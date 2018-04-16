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

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include "OpenInfraPlatform/Infrastructure/Export/ExportIfcAlignment1x0.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <BlueFramework/Core/memory.h>
#include <vector>
#include <memory>

namespace OpenInfraPlatform {
	namespace Infrastructure {
		void BLUEINFRASTRUCTURE_API exportIfcAlignment1x1(
			buw::ReferenceCounted<buw::AlignmentModel> am,
			buw::ReferenceCounted<buw::DigitalElevationModel> dem,
			const std::string& filename);

		class BLUEINFRASTRUCTURE_API ExportIfc4x1 : public Export {
		public:
			ExportIfc4x1(const ifcAlignmentExportDescription& desc,
				buw::ReferenceCounted<buw::AlignmentModel> am,
				buw::ReferenceCounted<buw::DigitalElevationModel> dem,
				const std::string& filename);

			virtual ~ExportIfc4x1();
			buw::ReferenceCounted<IfcAlignment1x1::IfcAlignment1x1Model> getIfcAlignment1x1Model() const;

		private:
			class IfcAlignment1x1ExportImpl;						// Forward declaration of internal class
			buw::ReferenceCounted<IfcAlignment1x1ExportImpl> impl_;	// Opaque pointer to implementation
		}; // end class IfcAlignment1x1Export
	}
}

namespace buw {
	using OpenInfraPlatform::Infrastructure::exportIfcAlignment1x1;
	using OpenInfraPlatform::Infrastructure::ExportIfc4x1;
}