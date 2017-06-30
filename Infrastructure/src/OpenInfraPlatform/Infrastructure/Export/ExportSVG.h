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
#ifndef OpenInfraPlatform_Infrastructure_SVGConverter_2e07ac2c_c8dd_46cb_a537_ae365e9b31d8_h
#define OpenInfraPlatform_Infrastructure_SVGConverter_2e07ac2c_c8dd_46cb_a537_ae365e9b31d8_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/Alignment2DBased3D.h"
#include <BlueFramework/ImageProcessing/color.h>
#include <BlueFramework/Core/Math/vector.h>
#include <boost/noncopyable.hpp>
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"

namespace OpenInfraPlatform
{
	namespace Infrastructure
	{
		//! SVG Exporter for alignments
		class BLUEINFRASTRUCTURE_API ExportSVG : public Export
		{
		public:
			ExportSVG(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);
			
		private:
			void addPath(FILE *fp, const buw::Vector2d& a, const buw::Vector2d& b, const buw::Vector2d& c);
			void outputToSVG(FILE *fp, buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment);
		}; // end class SVGExport
	} // end namespace Infrastructure
} // end namespace BlueFramework

namespace buw
{
	using OpenInfraPlatform::Infrastructure::ExportSVG;
}

#endif // end define OpenInfraPlatform_Infrastructure_SVGConverter_2e07ac2c_c8dd_46cb_a537_ae365e9b31d8_h
