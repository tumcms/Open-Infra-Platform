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
#ifndef OpenInfraPlatform_RoadXMLParser_70745c8f_e75e_40d8_94a8_ae27429bd59d_h
#define OpenInfraPlatform_RoadXMLParser_70745c8f_e75e_40d8_94a8_ae27429bd59d_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ImportRoadXML : public Import
		{
		public:
			ImportRoadXML(const std::string& filename);
		};
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ImportRoadXML;
}

#endif // end define OpenInfraPlatform_RoadXMLParser_70745c8f_e75e_40d8_94a8_ae27429bd59d_h
