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
#include "ExportSVG.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		//! SVG Exporter for alignments
		class BLUEINFRASTRUCTURE_API ExportSVGEAdvanced : public Export
		{
		public:
			ExportSVGEAdvanced(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

		private:
			void addPath(FILE *fp, const buw::Vector2d& a, const buw::Vector2d& b, const buw::Vector2d& c);
			void outputToSVG(FILE *fp, buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment);
		}; // end class SVGExportAdvanced
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportSVGEAdvanced;
}

