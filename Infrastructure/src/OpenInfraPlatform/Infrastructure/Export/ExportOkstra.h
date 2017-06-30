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
#ifndef OpenInfraPlatform_Infrastructure_OkstraExport_37e91449_2c4b_4ad1_8308_5c5c876098c9_h
#define OpenInfraPlatform_Infrastructure_OkstraExport_37e91449_2c4b_4ad1_8308_5c5c876098c9_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"

#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ExportOkstra : public Export
		{
		public:
			//! Default constructor.
			ExportOkstra(int majorVersion, int minorVersion, buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

			//! Virtual destructor.
			virtual ~ExportOkstra();

		private:
			class OkstraExportImpl;
			std::shared_ptr<OkstraExportImpl> impl_;

		}; // end class OkstraExport
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportOkstra;
}

#endif // end define OpenInfraPlatform_Infrastructure_OkstraExport_37e91449_2c4b_4ad1_8308_5c5c876098c9_h
