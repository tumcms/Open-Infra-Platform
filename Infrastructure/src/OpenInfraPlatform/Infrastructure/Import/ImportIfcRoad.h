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
#ifndef OpenInfraPlatform_Infrastructure_IfcRoadImport_793bf9e2_b78a_4b91_9fbf_7fe73a844d9f_h
#define OpenInfraPlatform_Infrastructure_IfcRoadImport_793bf9e2_b78a_4b91_9fbf_7fe73a844d9f_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ImportIfcRoad : public Import
		{
		public:
			//! Default constructor.
			ImportIfcRoad(const std::string& filename);

		private:
			class IfcRoadImportImpl;					// Forward declaration of internal class
			std::shared_ptr<IfcRoadImportImpl> impl_;	// Opaque pointer to implementation
		}; // end class IfcRoadImport
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ImportIfcRoad;
}

#endif // end define OpenInfraPlatform_Infrastructure_IfcRoadImport_793bf9e2_b78a_4b91_9fbf_7fe73a844d9f_h
