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
#ifndef OpenInfraPlatform_DataManagement_Command_CommandCreateClothoid_557621de_8335_4102_9720_222fc2fe780e_h
#define OpenInfraPlatform_DataManagement_Command_CommandCreateClothoid_557621de_8335_4102_9720_222fc2fe780e_h

#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
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
			class CommandCreateClothoid : public buw::ICommand
			{
			public:
				CommandCreateClothoid(const buw::clothoidDescription& cd);

				virtual ~CommandCreateClothoid();

				void execute() override;

				void unexecute() override;

			private:
				buw::clothoidDescription							cd_;
				buw::ReferenceCounted<buw::Alignment2DBased3D>		alignment_;
			}; // end class CommandCreateClothoid
		} // end namespace Command
	} // end namespace DataManagement
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::DataManagement::Command::CommandCreateClothoid;
}

#endif // end define OpenInfraPlatform_DataManagement_Command_CommandCreateClothoid_557621de_8335_4102_9720_222fc2fe780e_h