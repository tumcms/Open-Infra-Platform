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
#ifndef OpenInfraPlatform_Infrastructure_LandXMLExport_ac000b42_148b_4277_8274_ce62d37978e1_h
#define OpenInfraPlatform_Infrastructure_LandXMLExport_ac000b42_148b_4277_8274_ce62d37978e1_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ExportLandXML : public Export
		{
		public:
			ExportLandXML(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);
		};

	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportLandXML;
}

#endif // end define OpenInfraPlatform_Infrastructure_LandXMLExport_ac000b42_148b_4277_8274_ce62d37978e1_h