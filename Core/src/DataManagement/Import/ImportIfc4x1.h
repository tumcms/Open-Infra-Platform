/*
    Copyright (c) 2018 Technical University of Munich
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

#include "../Core/src/DataManagement/Import/Import.h"
#include <boost/noncopyable.hpp>

namespace OpenInfraPlatform {
    namespace Core {
        class /*BLUEINFRASTRUCTURE_API*/ ImportIfc4x1 : public Import {
        public:
            ImportIfc4x1(const std::string& filename);

        private:
            class ImportIfc4x1Impl;                  // Forward declaration of internal class
            std::shared_ptr<ImportIfc4x1Impl> impl_; // Opaque pointer to implementation
        };                                                    // end class IfcAlignmentImport
    }                                                         // end namespace Infrastructure
} // end namespace OpenInfraPlatform

namespace buw {
    using OpenInfraPlatform::Core::ImportIfc4x1;
}
