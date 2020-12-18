/*
Copyright (c) 2021 Technical University of Munich
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
#ifndef OFFREADER_H
#define OFFREADER_H

#include <thread>
#include <string>

#include "namespace.h"
#include "OffModel.h"

namespace OpenInfraPlatform
{
	namespace Core
	{
		namespace OffConverter
		{
			class OffReader
			{
			public:
				explicit OffReader();
				virtual ~OffReader();

				static std::shared_ptr<OffModel> readFile(const std::string& filename);
			};
		}
	}
}

EMBED_CORE_OFFCONVERTER_INTO_OIP_NAMESPACE(OffReader)

#endif //OFFREADER_H