/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016 Technical University of Munich
    Chair of Computational Modeling and Simulation.
    
    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.
    
    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include <BlueFramework/Core/memory.h>
#include <memory>
#include <vector>

namespace OpenInfraPlatform {
    namespace Infrastructure {

        class BLUEINFRASTRUCTURE_API ExportIfcOWL4x1 : public Export {
        public:
			ExportIfcOWL4x1(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

			virtual ~ExportIfcOWL4x1();

        
        private:
            class ExportIfcOWL4x1Impl;
            std::unique_ptr<ExportIfcOWL4x1Impl> impl_;
        }; // end class ExportOkstraOWL
    }      // end namespace Infrastructure
} // namespace OpenInfraPlatform

namespace buw {
    using OpenInfraPlatform::Infrastructure::ExportIfcOWL4x1;
}