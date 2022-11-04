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
#ifndef IFCPEEKSTEPREADER_H
#define IFCPEEKSTEPREADER_H

#include <string>

namespace OpenInfraPlatform
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{
			class IfcPeekStepReader 
			{
			public:
				explicit IfcPeekStepReader();
				virtual ~IfcPeekStepReader();

				//TODO: Have this amended by cmake configure file
				enum class IfcSchema : short { IFC2X3, IFC4, IFC4X1, IFC4X3_RC1, IFC4X3_RC4, IFC4X3 };
				static std::pair<std::string, IfcSchema> parseIfcHeader(const std::string& filename);
			};
		}
	}
}

#endif
