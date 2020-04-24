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


#pragma once
#ifndef A9B1C3A9_3605_4817_803A_F41F81E53C51
#define A9B1C3A9_3605_4817_803A_F41F81E53C51

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {

            #ifdef OIP_MODULE_EARLYBINDING_IFC4X1
            std::shared_ptr<emt::IFC4X1EntityTypes::IfcCurve> PlacementConverterT<emt::IFC4X1EntityTypes>::GetCurveOfPlacement(
				const std::shared_ptr<emt::IFC4X1EntityTypes::IfcLinearPlacement>& linearPlacement) 
			{
            	return linearPlacement->PlacementRelTo.lock();
            };
            #endif

			/*! \brief Gets the \c IfcCurve attribute from \c IfcLinearPlacement.

			There was a change moving from IFC4x1 to IFC4x2 in the naming of the attribute to \c IfcCurve.
			In IFC4x1, the attribute was named \c PlacementRelTo, starting in IFC4x2 it is named \c PlacementMeasuredAlong.

			\param[in]	linearPlacement		\c IfcLinearPlacement entity to interpret.

			\return		\c std::shared_ptr to \c IfcCurve that \c IfcLinearPlacement references.
			*/
			template<typename IfcEntityTypesT> 
			std::shared_ptr<typename IfcEntityTypesT::IfcCurve> PlacementConverterT<IfcEntityTypesT>::GetCurveOfPlacement(
				const std::shared_ptr<typename IfcEntityTypesT::IfcLinearPlacement>& linearPlacement) 
			{
				return linearPlacement->PlacementMeasuredAlong.lock();
			};
        }
    }
}

#endif /* A9B1C3A9_3605_4817_803A_F41F81E53C51 */
