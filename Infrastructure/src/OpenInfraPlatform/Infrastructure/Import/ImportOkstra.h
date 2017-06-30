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
#ifndef OpenInfraPlatform_Infrastructure_OkstraImport_10fa5edb_cffa_4650_b56c_4ff3c1851c8d_h
#define OpenInfraPlatform_Infrastructure_OkstraImport_10fa5edb_cffa_4650_b56c_4ff3c1851c8d_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"

#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ImportOkstra : public Import
		{
		public:
			//! Default constructor.
			ImportOkstra(const std::string& filename);

		private:
			class OkstraImportImpl;						// Forward declaration of internal class
			std::shared_ptr<OkstraImportImpl> impl_;	// Opaque pointer to implementation
		}; // end class OkstraImport

	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ImportOkstra;
}

#endif // end define OpenInfraPlatform_Infrastructure_OkstraImport_10fa5edb_cffa_4650_b56c_4ff3c1851c8d_h
