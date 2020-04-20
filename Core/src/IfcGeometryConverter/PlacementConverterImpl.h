#pragma once
#ifndef A9B1C3A9_3605_4817_803A_F41F81E53C51
#define A9B1C3A9_3605_4817_803A_F41F81E53C51

namespace OpenInfraPlatform {
	namespace Core {
		namespace IfcGeometryConverter {

            #ifdef OIP_MODULE_EARLYBINDING_IFC4X1
            std::shared_ptr<emt::IFC4X1EntityTypes::IfcCurve> PlacementConverterT<emt::IFC4X1EntityTypes>::GetRelativePlacement(const std::shared_ptr<emt::IFC4X1EntityTypes::IfcLinearPlacement>& linearPlacement) {
            	return linearPlacement->PlacementRelTo.lock();
            };
            #endif

			template<typename IfcEntityTypesT> std::shared_ptr<typename IfcEntityTypesT::IfcCurve> PlacementConverterT<IfcEntityTypesT>::GetRelativePlacement(const std::shared_ptr<typename IfcEntityTypesT::IfcLinearPlacement>& linearPlacement) {
				return linearPlacement->PlacementMeasuredAlong.lock();
			};
        }
    }
}

#endif /* A9B1C3A9_3605_4817_803A_F41F81E53C51 */
