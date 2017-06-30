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

namespace OpenInfraPlatform
{
	namespace Data
	{
		struct terrainDescription
		{
			/*int noOfOctaves; 
			int noiseFrequency;
			int terrainSize;*/
			float tileSize;

			int lod;
			float roughness;
			float mean;
			float deviation;
		};
	} // end namespace Data
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::Data::terrainDescription;
}