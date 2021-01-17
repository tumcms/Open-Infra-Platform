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
#ifndef IFC_IMPORTER_UTIL_IMPL_H
#define IFC_IMPORTER_UTIL_IMPL_H

#include <IfcGeometryConverter/IfcImporter.h>
#include "BlueFramework/Core/Diagnostics/log.h"

#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
#include "EarlyBinding\IFC2X3\src\EMTIFC2X3EntityTypes.h"
#include "EarlyBinding\IFC2X3\src\IFC2X3Entities.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
#include "EarlyBinding\IFC4\src\EMTIFC4EntityTypes.h"
#include "EarlyBinding\IFC4\src\IFC4Entities.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "EarlyBinding\IFC4X1\src\EMTIFC4X1EntityTypes.h"
#include "EarlyBinding\IFC4X1\src\IFC4X1Entities.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "EarlyBinding\IFC4X3_RC1\src\EMTIFC4X3_RC1EntityTypes.h"
#include "EarlyBinding\IFC4X3_RC1\src\IFC4X3_RC1Entities.h"
#endif


#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC2
#include "EarlyBinding\IFC4X3_RC2\src\EMTIFC4X3_RC2EntityTypes.h"
#include "EarlyBinding\IFC4X3_RC2\src\IFC4X3_RC2Entities.h"
#endif

#include "PlacementConverterImpl.h"

template <
	class IfcEntityTypesT
>
void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtilT<typename IfcEntityTypesT>::convertIfcProduct(
	const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
	std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
	const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>> repConverter)
{
	try
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
			//auto& objectPlacement_ptr = objectPlacement.lock();		// get std::shared_ptr used to construct the weak_ptr.
																	// OR auto& objectPlacement = optObjectPlacement.get();

			std::vector<EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>> placementAlreadyApplied;
			matProduct = repConverter->getPlacementConverter()->convertIfcObjectPlacement(
				objectPlacement,
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
				BLUE_LOG(trace) << "Processing IfcRepresentation " << rep->getErrorLog();
#endif
				repConverter->convertIfcRepresentation(rep, matProduct, productShape);
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcRepresentation " << rep->getErrorLog();
#endif
			}

			IfcImporterUtilT<IfcEntityTypesT>::computeMeshsetsFromPolyhedrons<IfcEntityTypesT>(product, productShape, strerr, repConverter);
#ifdef _DEBUG
			BLUE_LOG(trace) << "Processed IfcProductRepresentation #" << representation->getId();
#endif
		}

		if (repConverter->isOfType<typename IfcEntityTypesT::IfcLinearPositioningElement>(product)) {
			auto linposel = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcLinearPositioningElement>(product);
			std::shared_ptr<ItemData> itemData(new ItemData());
			productShape->vec_item_data.push_back(itemData);
			repConverter->convertIfcGeometricRepresentationItem(
				getIfcLinearPositioningElementAxis(linposel), 
				carve::math::Matrix::IDENT(), itemData);
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
	catch (const oip::UnhandledException& ex)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> unhandled error: " + std::string(ex.what());
	}
	catch (const oip::InconsistentGeometryException& ex)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> geometry error: " + std::string(ex.what());
	}
	catch (const oip::InconsistentModellingException& ex)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> modelling error: " + std::string(ex.what());
	}
	catch (const oip::ReferenceExpiredException& ex)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> reference error: " + std::string(ex.what());
	}
	catch (const std::exception& ex)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> general error: " + std::string(ex.what());
	}
	catch (...)
	{
		BLUE_LOG(warning) << product->getErrorLog() + " -> unknown error.";
		throw; // throw onwards
	}
}

//IFC4x3_RC1 specifics
#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
template <>
oip::EXPRESSReference<emt::IFC4X3_RC1EntityTypes::IfcGeometricRepresentationItem>
OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtilT<emt::IFC4X3_RC1EntityTypes>::getIfcLinearPositioningElementAxis(
	const oip::EXPRESSReference<emt::IFC4X3_RC1EntityTypes::IfcLinearPositioningElement>& linposel
);
#endif

// general implementation
template <
	class IfcEntityTypesT
>
oip::EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationItem>
OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterUtilT<typename IfcEntityTypesT>::getIfcLinearPositioningElementAxis(
	const oip::EXPRESSReference<typename IfcEntityTypesT::IfcLinearPositioningElement>& linposel
)
{
	// check input
	if( linposel.expired() )
		throw oip::ReferenceExpiredException(linposel);

	return linposel->Axis.as<typename IfcEntityTypesT::IfcGeometricRepresentationItem>();
}

#endif // IFC_IMPORTER_UTIL_IMPL_H
