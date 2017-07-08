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
#ifndef OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h
#define OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h

#include "OpenInfraPlatform/Infrastructure/Import/Import.h"


namespace OpenInfraPlatform {
	namespace Infrastructure {
		class BLUEINFRASTRUCTURE_API ImportLandInfra : public Import
		{
		public:
			ImportLandInfra(const std::string& filename);

		private:
			static const bool validateHeader(const QString &header);
		};

	} // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
	using OpenInfraPlatform::Infrastructure::ImportLandInfra;
}

#endif // end define OpenInfraPlatform_Infrastructure_ImportLandInfra_2fec77f9_05A4_4BC0_A9A5_B0EF4AC7778A_h
