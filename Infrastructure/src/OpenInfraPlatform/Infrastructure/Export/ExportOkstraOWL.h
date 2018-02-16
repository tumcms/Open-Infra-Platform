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
#ifndef BlueFramework_Infrastructure_ExportOkstraOWL_594bf14b_3698_4efb_b616_150c601319ae_h
#define BlueFramework_Infrastructure_ExportOkstraOWL_594bf14b_3698_4efb_b616_150c601319ae_h

#include "OpenInfraPlatform/Infrastructure/Export/Export.h"
#include <BlueFramework/Core/memory.h>
#include <memory>
#include <vector>

namespace OpenInfraPlatform {
    namespace Infrastructure {

        class BLUEINFRASTRUCTURE_API ExportOkstraOWL : public Export {
        public:
            ExportOkstraOWL(buw::ReferenceCounted<buw::AlignmentModel> am, buw::ReferenceCounted<buw::DigitalElevationModel> dem, const std::string& filename);

            virtual ~ExportOkstraOWL();

        
        private:
            class ExportOkstraOWLImpl;
            std::unique_ptr<ExportOkstraOWLImpl> impl_;
        }; // end class ExportOkstraOWL
    }      // end namespace Infrastructure
} // namespace OpenInfraPlatform

namespace buw {
    using OpenInfraPlatform::Infrastructure::ExportOkstraOWL;
}

#endif // end define BlueFramework_Infrastructure_ExportOkstraOWL_594bf14b_3698_4efb_b616_150c601319ae_h
