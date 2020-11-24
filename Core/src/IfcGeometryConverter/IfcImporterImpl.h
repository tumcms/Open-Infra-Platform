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
#ifndef IFCIMPORTERIMPL_H
#define IFCIMPORTERIMPL_H

#include <IfcGeometryConverter/IfcImporter.h>
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

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "EMTIFC4X3_RC1EntityTypes.h"
#include "IFC4X3_RC1Entities.h"
#endif

#include "namespace.h"
#include "PlacementConverterImpl.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN

template <
	class IfcEntityTypesT
>
IfcImporterT<IfcEntityTypesT>::IfcImporterT<IfcEntityTypesT>()
{
	geomSettings = std::make_shared<GeometrySettings>();
	unitConverter = std::make_shared<UnitConverter<IfcEntityTypesT>>();
	repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT>>(geomSettings, unitConverter);
}

template <
	class IfcEntityTypesT
>
void IfcImporterT<IfcEntityTypesT>::convertIfcProduct(
	const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
	std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape
) const
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
				BLUE_LOG(trace) << "Processing IfcRepresentation #" << rep->getId();
#endif
				repConverter->convertIfcRepresentation(rep, matProduct, productShape);
#ifdef _DEBUG
				BLUE_LOG(trace) << "Processed IfcRepresentation #" << rep->getId();
#endif
			}

			IfcImporterUtil::computeMeshsetsFromPolyhedrons<IfcEntityTypesT>(product, productShape, strerr, repConverter);
#ifdef _DEBUG
			BLUE_LOG(trace) << "Processed IfcProductRepresentation #" << representation->getId();
#endif
		}

		if (repConverter->isOfType<typename IfcEntityTypesT::IfcAlignment>(product)) {
			auto alignment = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment>(product);
			std::shared_ptr<ItemData> itemData(new ItemData());
			productShape->vec_item_data.push_back(itemData);
			repConverter->convertIfcGeometricRepresentationItem(
				alignment->Axis.as<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(), 
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

template <
	class IfcEntityTypesT
>
std::shared_ptr<oip::GeorefMetadata> OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<IfcEntityTypesT>::convertGeoref(
	const EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateOperation> coordOper
) const throw(...)
{
	// check input
	if (coordOper.expired())
		throw oip::ReferenceExpiredException(coordOper);

	//ENTITY IfcCoordinateOperation
	//	ABSTRACT SUPERTYPE OF(IfcMapConversion);
	//  SourceCRS: IfcCoordinateReferenceSystemSelect;
	//  TargetCRS: IfcCoordinateReferenceSystem;
	//END_ENTITY;

		// the interpreted data
	std::shared_ptr<oip::GeorefMetadata> georefMeta = std::make_shared<oip::GeorefMetadata>();

	// get the CoordinateRereferenceSystem
	const oip::EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem> crs = coordOper->TargetCRS;
	convertCRS(coordOper->TargetCRS);

	// get the GeometricContext
	switch (coordOper->SourceCRS.which())
	{
	case 0: // IfcCoordinateReferenceSystem
	{
		throw oip::UnhandledException(mapConv->getErrorLog() + ": We don't handle another IfcCoordinateReferenceSystem as SourceCRS.");
	}
	case 1: // IfcGeometricRepresentationContext
	{

		break;
	}
	default:
		throw oip::UnhandledException(coordOper->SourceCRS.getErrorLog());
	}

	// IfcMapConversion
	if (coordOper.isOfType<typename IfcEntityTypesT::IfcMapConversion>())
	{
		//ENTITY IfcMapConversion
		//	SUBTYPE OF(IfcCoordinateOperation);
		//  Eastings: IfcLengthMeasure;
		//  Northings: IfcLengthMeasure;
		//  OrthogonalHeight: IfcLengthMeasure;
		//  XAxisAbscissa: OPTIONAL IfcReal;
		//  XAxisOrdinate: OPTIONAL IfcReal;
		//  Scale: OPTIONAL IfcReal;
		//END_ENTITY;

		EXPRESSReference<typename IfcEntityTypesT::IfcMapConversion> mapConv
			= coordOper.as<typename IfcEntityTypesT::IfcMapConversion>();


	}

	return georefMeta;


}



template <
	class IfcEntityTypesT
>
void OpenInfraPlatform::Core::IfcGeometryConverter::IfcImporterT<IfcEntityTypesT>::convertCRS(
	const EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem> crs,
	std::shared_ptr<oip::GeorefMetadata> georefMeta
) const throw(...)
{
	// check input
	if (crs.expired())
		throw oip::ReferenceExpiredException(crs);

	// EPSG code
	georefMeta->codeEPSG = crs->Name;

	// description (could be WKT)
	if( crs->Description )
		georefMeta->data.add("Description", crs->Description);

	if (crs->GeodeticDatum)
		georefMeta->data.add("Geodetic Datum", crs->GeodeticDatum);

	if (crs->GeodeticDatum)
		georefMeta->data.add("Vertical Datum", crs->VerticalDatum);

	if (crs.isOfType<typename IfcEntityTypesT::IfcProjectedCRS>())
	{
		auto projectedCRS = crs.as<typename IfcEntityTypesT::IfcProjectedCRS>();

		if (projectedCRS->MapProjection)
			georefMeta->data.add("Map Projection", projectedCRS->MapProjection);
		if( projectedCRS->MapZone )
			georefMeta->data.add("Map Zone", projectedCRS->MapZone );
		if (projectedCRS->MapUnit)
		{
			double factor = unitConverter->convertUnit(projectedCRS->MapUnit);
			std::string factorString;
			factorString.Format("%d", factor);
			georefMeta->data.add("Map Unit Factor to meters", factor);
		}
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END

#endif // IFCIMPORTERIMPL_H
