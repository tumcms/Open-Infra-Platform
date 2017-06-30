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
#ifndef OpenInfraPlatform_DataManagement_Command_DeleteAlignment_e71eafc3_7af8_4609_8b13_a1d1312a59fa_h
#define OpenInfraPlatform_DataManagement_Command_DeleteAlignment_e71eafc3_7af8_4609_8b13_a1d1312a59fa_h

#include <BlueFramework/Core/memory.h>
#include "OpenInfraPlatform/Data/terrainDescription.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/IAlignment3D.h"
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
			class DeleteAlignment : public buw::ICommand
			{
			public:
				DeleteAlignment(buw::ReferenceCounted<buw::IAlignment3D> alignment);

				virtual ~DeleteAlignment();

				virtual void execute();

				virtual void unexecute();

			private:
				buw::ReferenceCounted<buw::IAlignment3D> alignment_;
			}; // end class DeleteAlignment
		} // end namespace Action
	} // end namespace DataManagement
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::DataManagement::Command::DeleteAlignment;
}

#endif // end define OpenInfraPlatform_DataManagement_Command_DeleteAlignment_e71eafc3_7af8_4609_8b13_a1d1312a59fa_h
