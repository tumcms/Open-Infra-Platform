/*
    Copyright (c) 2020 Technical University of Munich
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

#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
#include "EarlyBinding\IFC2X3\src\reader/IFC2X3Reader.h"
#include "EarlyBinding\IFC2X3\src\EMTIFC2X3EntityTypes.h"
#include "EarlyBinding\IFC2X3\src\IFC2X3.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
#include "EarlyBinding\IFC4\src\reader/IFC4Reader.h"
#include "EarlyBinding\IFC4\src\EMTIFC4EntityTypes.h"
#include "EarlyBinding\IFC4\src\IFC4.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "EarlyBinding\IFC4X1\src\reader/IFC4X1Reader.h"
#include "EarlyBinding\IFC4X1\src\EMTIFC4X1EntityTypes.h"
#include "EarlyBinding\IFC4X1\src\IFC4X1.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "EarlyBinding\IFC4X3_RC1\src\reader/IFC4X3_RC1Reader.h"
#include "EarlyBinding\IFC4X3_RC1\src\EMTIFC4X3_RC1EntityTypes.h"
#include "EarlyBinding\IFC4X3_RC1\src\IFC4X3_RC1.h"
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
			
			template <>
			double PlacementConverterT<emt::IFC4X1EntityTypes>::convertRelativePlacement(
				const EXPRESSReference<emt::IFC4X1EntityTypes::IfcLinearPlacement>& linear_placement,
				std::vector<EXPRESSReference<emt::IFC4X1EntityTypes::IfcObjectPlacement>>& alreadyApplied
			) const
            {
				// no relative placement in IFC4x1
                return 0.;
            }
		#endif

        }
    }
}

