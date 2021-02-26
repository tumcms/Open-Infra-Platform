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
#ifndef A9B1C3A9_3605_4817_803A_F41F81E53C51
#define A9B1C3A9_3605_4817_803A_F41F81E53C51

namespace OpenInfraPlatform {
    namespace Core {
        namespace IfcGeometryConverter {

			// IFC 4x1 specifics
		#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
			template <>
            EXPRESSReference<emt::IFC4X1EntityTypes::IfcBoundedCurve> PlacementConverterT<emt::IFC4X1EntityTypes>::getCurveOfPlacement(
                const EXPRESSReference<emt::IFC4X1EntityTypes::IfcLinearPlacement>& linearPlacement
			) const;
		#endif

            /*! \brief Gets the \c IfcCurve attribute from \c IfcLinearPlacement.

            There was a change moving from IFC4x1 to IFC4x2 in the naming of the attribute to \c IfcCurve.
            In IFC4x1, the attribute was named \c PlacementRelTo, starting in IFC4x2 it is named \c PlacementMeasuredAlong.

            \param[in]	linearPlacement		\c IfcLinearPlacement entity that has the curve reference.

            \return		\c IfcBoundedCurve that \c IfcLinearPlacement references.
            */
            template<typename IfcEntityTypesT>
            EXPRESSReference<typename IfcEntityTypesT::IfcBoundedCurve> PlacementConverterT<IfcEntityTypesT>::getCurveOfPlacement(
                const EXPRESSReference<typename IfcEntityTypesT::IfcLinearPlacement>& linearPlacement
			) const
            {
				// check input
				if (linearPlacement.expired())
					throw oip::ReferenceExpiredException(linearPlacement);
				// check if correct type
				if (!linearPlacement->PlacementMeasuredAlong.template isOfType<typename IfcEntityTypesT::IfcBoundedCurve>())
					throw oip::InconsistentModellingException(linearPlacement, "Only IfcBoundedCurve can be a base curve for IfcLinearPlacement.");
				// return the curve
                return linearPlacement->PlacementMeasuredAlong.template as<typename IfcEntityTypesT::IfcBoundedCurve>();
            };

        }
    }
}

#endif /* A9B1C3A9_3605_4817_803A_F41F81E53C51 */
