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

#include "OpenInfraPlatform/Infrastructure/ProxyModel/ProxyModel.h"
#include <BlueFramework/Core/Math/vector.h>
#include <BlueFramework/Application/DataManagement/Command/ICommand.h>
#include <boost/noncopyable.hpp>
#include <vector>

namespace OpenInfraPlatform
{
	namespace DataManagement
	{
		namespace Command
		{
			class CreateCarAccident : public buw::ICommand
			{
			public:
				CreateCarAccident(const int selectedIndex, const double station);
				virtual ~CreateCarAccident();

				virtual void execute();
				virtual void unexecute();

			private:
				int selectedIndex_;
				double station_;
				int CarAccidentReportIndex_ = -1;
				buw::carAccidentDescription ca_;
			}; // end class SelectAlignment
		} // end namespace Action
	} // end namespace DataManagement
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::DataManagement::Command::CreateCarAccident;
}
