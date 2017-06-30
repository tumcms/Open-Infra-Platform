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
#ifndef OpenInfraPlatform_Infrastructure_IfcAlignmenBuildingSmartP6StepFileWriter_85a9dc90_3db8_49d4_a197_2ac34a429c2f_h
#define OpenInfraPlatform_Infrastructure_IfcAlignmenBuildingSmartP6StepFileWriter_85a9dc90_3db8_49d4_a197_2ac34a429c2f_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <BlueFramework/Core/memory.h>
#include <vector>
#include <memory>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		enum class eIfcSchemaVersion
		{
			IFC2x3,
			IFC4,
			IFC4x1
		};
		
		struct ifcAlignmentExportDescription
		{
			eIfcSchemaVersion schemaVersion = eIfcSchemaVersion::IFC4x1;
			bool exportTerrain = true;
			bool exportAlignment = true;
			bool useRadiansInsteadOfDegrees = true;
			bool useFixedEntityIdForGeometry = false;
			int startId = 4000;
			bool roundOffsetMapConversion = false;
		};

		class BLUEINFRASTRUCTURE_API ExportIfcAlignment1x0 : public Export
		{
		public:	
			ExportIfcAlignment1x0(const ifcAlignmentExportDescription& desc, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

			virtual ~ExportIfcAlignment1x0();

		private:
			class IfcAlignment1x0ExportImpl;						// Forward declaration of internal class
			buw::ReferenceCounted<IfcAlignment1x0ExportImpl> impl_;	// Opaque pointer to implementation
		}; // end class IfcAlignment1x0Export
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::eIfcSchemaVersion;
	using OpenInfraPlatform::Infrastructure::ExportIfcAlignment1x0;
	using OpenInfraPlatform::Infrastructure::ifcAlignmentExportDescription;
}

#endif // end define OpenInfraPlatform_Infrastructure_IfcAlignmenBuildingSmartP6StepFileWriter_85a9dc90_3db8_49d4_a197_2ac34a429c2f_h
