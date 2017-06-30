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
#ifndef OpenInfraPlatform_Infrastructure_IfcRoadStepFileWriter_h
#define OpenInfraPlatform_Infrastructure_IfcRoadStepFileWriter_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <BlueFramework/Core/memory.h>
#include <vector>
#include <memory>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		struct IfcRoadExportDescription
		{
			bool exportTerrain = true;
			bool exportAlignment = true;
			bool useRadiansInsteadOfDegrees = true;
		};

		class BLUEINFRASTRUCTURE_API ExportIfcRoad : public Export
		{
		public:
			ExportIfcRoad(const IfcRoadExportDescription& desc, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

			virtual ~ExportIfcRoad();

		private:
			class IfcRoadExportImpl;					// Forward declaration of internal class
			buw::ReferenceCounted<IfcRoadExportImpl> impl_;	// Opaque pointer to implementation
		}; // end class IfcAlignmenBuildingSmartP6StepFileWriter
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportIfcRoad;
	using OpenInfraPlatform::Infrastructure::IfcRoadExportDescription;
}

#endif // end define OpenInfraPlatform_Infrastructure_IfcRoadStepFileWriter_h
