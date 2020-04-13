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

#include "IfcImporter.h"
#include "BlueFramework/Core/Diagnostics/log.h"

#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
#include "EMTIFC2X3EntityTypes.h"
#include "IFC2X3Entities.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
#include "EMTIFC4EntityTypes.h"
#include "IFC4Entities.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "EMTIFC4X1EntityTypes.h"
#include "IFC4X1Entities.h"
#endif

template <
	class IfcEntityTypesT
>
static void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtil::convertIfcProduct(
	const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
	std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
	const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>> repConverter)
{
	//#ifdef _DEBUG
	//				std::cout << "Info\t| IfcGeometryConverter.Importer.RepConverter: Converting IFC product " << product->classname() << " #" << product->getId() << std::endl;
	//#endif

	// get id of product
	const uint32_t productId = product->getId();

	carve::math::Matrix matProduct(carve::math::Matrix::IDENT());

	// check if there's any global object placement for this product
	// if yes, then apply the placement
	if (product->ObjectPlacement) {
		// decltype(x) returns the compile time type of x.
		//decltype(product->ObjectPlacement)::type &objectPlacement = product->ObjectPlacement;

		OpenInfraPlatform::EarlyBinding::EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>& objectPlacement = product->ObjectPlacement;

		//auto& optObjectPlacement = product->ObjectPlacement;	// store optional<weak_ptr> product->ObjectPlacement in optObjectPlacement.
		//auto& objectPlacement = *optObjectPlacement;			// extract weak_ptr from optional<weak_ptr> optObjectPlacement.
		auto& objectPlacement_ptr = objectPlacement.lock();		// get std::shared_ptr used to construct the weak_ptr.
																// OR auto& objectPlacement = optObjectPlacement.get();

		std::set<int> placementAlreadyApplied;
		repConverter->getPlacementConverter()->convertIfcObjectPlacement(
			objectPlacement_ptr,
			matProduct,
			placementAlreadyApplied);

#ifdef _DEBUG
		BLUE_LOG(trace) << "Processed IfcObjectPlacement #" << objectPlacement->getId();
#endif
	}

	// error string
	std::stringstream strerr;

	// go through all representations of the product
	if (product->Representation) {
#ifdef _DEBUG
		BLUE_LOG(trace) << "Processing IfcProductRepresentation #" << product->Representation->getId();
#endif
		OpenInfraPlatform::EarlyBinding::EXPRESSReference<typename IfcEntityTypesT::IfcProductRepresentation>& representation = product->Representation;
		// so evaluate its geometry
		for (EXPRESSReference<typename IfcEntityTypesT::IfcRepresentation>& rep : representation->Representations) {
			// convert each shape of the represenation
#ifdef _DEBUG
			BLUE_LOG(trace) << "Processing IfcRepresentation #" << rep->getId();
#endif
			repConverter->convertIfcRepresentation(rep.lock(), matProduct, productShape, strerr);
#ifdef _DEBUG
			BLUE_LOG(trace) << "Processed IfcRepresentation #" << rep->getId();
#endif
		}

		IfcImporterUtil::computeMeshsetsFromPolyhedrons<IfcEntityTypesT>(product, productShape, strerr, repConverter);
#ifdef _DEBUG
		BLUE_LOG(trace) << "Processed IfcProductRepresentation #" << representation->getId();
#endif
	}

	if (std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment>(product)) {
		auto alignment = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment>(product);
		std::shared_ptr<ItemData> itemData(new ItemData());
		productShape->vec_item_data.push_back(itemData);
		std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem> axis = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(alignment->Axis.lock());
		repConverter->convertIfcGeometricRepresentationItem(axis, carve::math::Matrix::IDENT(), itemData, strerr);
	}

#ifdef _DEBUG
	if (strerr.tellp() <= 0) return;

	std::stringstream ss;
	ss << "log/" << "-" << product->classname()
		<< "#" << product->getId() << ".txt";

	std::ofstream debugLog(ss.str());
	debugLog << strerr.str();
	debugLog.close();
#endif
}

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
template void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtil::convertIfcProduct<emt::IFC4X1EntityTypes>(
	const std::shared_ptr<typename emt::IFC4X1EntityTypes::IfcProduct>& product,
	std::shared_ptr<ShapeInputDataT<emt::IFC4X1EntityTypes>> productShape,
	const std::shared_ptr<RepresentationConverterT<emt::IFC4X1EntityTypes>> repConverter);
#endif

//#ifdef OIP_MODULE_EARLYBINDING_IFC4
//template void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtil::convertIfcProduct<emt::IFC4EntityTypes>(const std::shared_ptr<typename emt::IFC4EntityTypes::IfcProduct>& product,
//	std::shared_ptr<ShapeInputDataT<emt::IFC4EntityTypes>> productShape,
//	const std::shared_ptr<RepresentationConverterT<emt::IFC4EntityTypes>> repConverter);
//#endif

//#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
//template void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtil::convertIfcProduct<emt::IFC2X3EntityTypes>(const std::shared_ptr<typename emt::IFC2X3EntityTypes::IfcProduct>& product,
//	std::shared_ptr<ShapeInputDataT<emt::IFC2X3EntityTypes>> productShape,
//	const std::shared_ptr<RepresentationConverterT<emt::IFC2X3EntityTypes>> repConverter);
//#endif