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
#ifndef OpenInfraPlatform_Infrastructure_OSMImport_cb390352_9e34_4971_a173_eab046fe8eec_h
#define OpenInfraPlatform_Infrastructure_OSMImport_cb390352_9e34_4971_a173_eab046fe8eec_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		class BLUEINFRASTRUCTURE_API ImportOSM : public Import
		{
		public:
			ImportOSM(const std::string& filename);
			ImportOSM(const std::string& filename, const std::vector<std::string>& filter, int mode);
			
			static std::vector<std::string> getDefaultFilter();
			static std::vector<std::string> getModeNames();
		}; // end class OSMImport
	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ImportOSM;
}

#endif // end define OpenInfraPlatform_Infrastructure_OSMImport_cb390352_9e34_4971_a173_eab046fe8eec_h
