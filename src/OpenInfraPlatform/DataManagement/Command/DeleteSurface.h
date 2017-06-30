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
#ifndef OpenInfraPlatform_DataManagement_Command_DeleteSurface_8481e70d_b71a_4983_bef4_224c6281e73a_h
#define OpenInfraPlatform_DataManagement_Command_DeleteSurface_8481e70d_b71a_4983_bef4_224c6281e73a_h

#include "OpenInfraPlatform/Data/terrainDescription.h"
#include "OpenInfraPlatform/Infrastructure/DigitalElevationModel/Surface.h"
#include <BlueFramework/Application/DataManagement/Command/ICommand.h>
#include <BlueFramework/Core/Math/vector.h>
#include <boost/noncopyable.hpp>
#include <vector>

namespace OpenInfraPlatform
{
	namespace DataManagement
	{
		namespace Command
		{
			class DeleteSurface : public buw::ICommand
			{
			public:
				DeleteSurface(buw::ReferenceCounted<buw::Surface> surface);

				virtual ~DeleteSurface();

				//! Execute action.
				virtual void execute();

				//! Undo action 
				virtual void unexecute();

			private:
				buw::ReferenceCounted<buw::Surface> surface_;

			}; // end class DeleteSurface
		} // end namespace Command
	} // end namespace DataManagement
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::DataManagement::Command::DeleteSurface;
}

#endif // end define OpenInfraPlatform_DataManagement_Command_DeleteSurface_8481e70d_b71a_4983_bef4_224c6281e73a_h
