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

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "EarlyBinding\IFC4X1\src\IFC4X1Entities.h"
#include "EarlyBinding\IFC4X1\src\EMTIFC4X1EntityTypes.h"
#endif

#include "PlacementConverter.h"
#include "PlacementConverterImpl.h"

namespace OpenInfraPlatform {
    namespace Core {
        namespace IfcGeometryConverter {

			// IFC 4x1 specifics
		#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
			template <>
			EXPRESSReference<emt::IFC4X1EntityTypes::IfcBoundedCurve> PlacementConverterT<emt::IFC4X1EntityTypes>::getCurveOfPlacement(
                const EXPRESSReference<emt::IFC4X1EntityTypes::IfcLinearPlacement>& linearPlacement
			) const
            {
				// check input
				if (linearPlacement.expired())
					throw oip::ReferenceExpiredException(linearPlacement);
				// check if correct type
				if (!linearPlacement->PlacementRelTo.isOfType<emt::IFC4X1EntityTypes::IfcBoundedCurve>())
					throw oip::InconsistentModellingException(linearPlacement, "Only a IfcBoundedCurve can be used as a reference curve.");
				// return the curve
                return linearPlacement->PlacementRelTo.as<emt::IFC4X1EntityTypes::IfcBoundedCurve>();
            }
		#endif

        }
    }
}

