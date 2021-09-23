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
#ifndef OpenInfraPlatform_IfcGeometryConverter_GeorefConverter_5F75E53B_DF06_4645_BDAA_F6585F55B2CF_h
#define OpenInfraPlatform_IfcGeometryConverter_GeorefConverter_5F75E53B_DF06_4645_BDAA_F6585F55B2CF_h

#include <map>
#include <memory>
#include <vector>

#include "EXPRESS/EXPRESSReference.h"
#include "BlueFramework/Core/Diagnostics/log.h"

#include <GeorefMetadata.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN

template <class IfcEntityTypesT>
using GeorefPair = std::pair<
	EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>,
	std::shared_ptr<oip::GeorefMetadata>> ;

/*! \brief Georeferencing conversion functionality

\param IfcEntityTypesT The IFC version specification.

*/
template <
	class IfcEntityTypesT
>
class GeoreferencingConverterT : public ConverterBaseT<IfcEntityTypesT>
{
public:
	//! Constructor
	GeoreferencingConverterT(
		std::shared_ptr<GeometrySettings> geomSettings, 
		std::shared_ptr<UnitConverter<IfcEntityTypesT>> unitConverter
	)
		: 
		ConverterBaseT<IfcEntityTypesT>(geomSettings, unitConverter)
	{
	}

	/*! \brief Initializes the georeferencing metadata from the IFC file.
	 *
	 * \param[in] model The IFC content.
	 */
	void init(std::shared_ptr<oip::EXPRESSModel> model) throw(...)
	{
		// try and find the georeferencing metadata
		auto georef = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair)
			{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateOperation>(pair.second) != nullptr; });
		if (georef != model->entities.end())
		{
			// interpret all
			do
			{
				// the interpreted data
				const auto georefMeta = convertGeoref(
					EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateOperation>::constructInstance(georef->first, model));

				// add to the parsed map
				georefMetadata_.push_back( georefMeta );
			} 
			while ((georef = std::find_if(++georef, model->entities.end(), [](auto pair)
			{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateOperation>(pair.second) != nullptr; }
			)) != model->entities.end());
		}

		// go also through all context
		auto context = model->entities.begin();

		// interpret all
		while ((context = std::find_if(context, model->entities.end(), [](auto pair)
			{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationContext>(pair.second) != nullptr; }
			)) != model->entities.end())
		{
			auto contextRef = EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>::constructInstance(context->first, model);
			// add empty to the parsed map - only if not yet present
			if (std::find_if(georefMetadata_.begin(), georefMetadata_.end(), [&contextRef](auto pair)
				{ return pair->first == contextRef; }) == georefMetadata_.end())
			{
				// handle subcontext
				if (contextRef.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>())
				{
					auto subcontext = contextRef.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>();

					if (std::find_if(georefMetadata_.begin(), georefMetadata_.end(), [&subcontext](auto pair)
						{ return pair->first == subcontext->ParentContext; }) != georefMetadata_.end())
					{
						context++;
						continue;
					}
				}
				
				// otherwise it doesn't have georef
				georefMetadata_.push_back( std::make_shared<GeorefPair<IfcEntityTypesT>>( 
					contextRef, nullptr ) );
			}

			context++;
		} 
	}
	
	bool isSameContext(
		const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& context,
		const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& contextTest
	) const noexcept(false)
	{
		if (context.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>())
			return isSameContext(
				context.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()->ParentContext, 
				contextTest);
		else if (contextTest.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>())
			return isSameContext(
				context, 
				contextTest.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()->ParentContext);
		else
			return context == contextTest;

	}


	std::vector<std::shared_ptr<GeorefPair<IfcEntityTypesT>>> getGeorefMetadata() noexcept(false) {
		return georefMetadata_;
	}
	const std::vector<std::shared_ptr<GeorefPair<IfcEntityTypesT>>>& getGeorefMetadata() const noexcept(false) {
		return georefMetadata_;
	}

	bool hasContext(
		const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& context
	) const noexcept(false)
	{
		if (context.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>())
		{
			// call recursively
			return hasContext(
				context.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()
				->ParentContext);
		}

		return std::find_if(getGeorefMetadata().begin(), getGeorefMetadata().end(), 
			[&context](const auto &el) -> bool { 
			return el->first == context; 
		}) != getGeorefMetadata().end();
	}

	bool hasGeorefContext(
		const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& context
	) const noexcept(false)
	{
		// check the parent context if it's a subcontext
		if (context.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>())
		{
			// call recursively
			return hasGeorefContext(
				context.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()
				->ParentContext);
		}

		// find the correct pair
		for (auto& el : getGeorefMetadata())
		{
			if (el->first == context)
			{
				return (el->second ? true : false);
			}
		}

		// otherwise 
		return false;
	}

	carve::math::Matrix getDefaultPlacement() const noexcept(false)
	{
		if (getGeorefMetadata().size() == 1 && getGeorefMetadata()[0]->second)
			return getGeorefMetadata()[0]->second->transformationMatrix();
		return carve::math::Matrix::IDENT();
	}

	carve::math::Matrix getContextPlacement(
		const EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext>& context
	) const noexcept(false)
	{
		// check the parent context if it's a subcontext
		if (context.template isOfType<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()) 
		{
			// call recursively
			return getContextPlacement(
				context.template as<typename IfcEntityTypesT::IfcGeometricRepresentationSubContext>()
				->ParentContext);
		}

		// find the correct pair
		for (auto& el : getGeorefMetadata())
		{
			if (el->first == context)
			{
				return (el->second ? el->second->transformationMatrix() : carve::math::Matrix::IDENT());
			}
		}

		// otherwise return default placement
		return getDefaultPlacement();
	}

private:

	std::shared_ptr<GeorefPair<IfcEntityTypesT>> convertGeoref(
		const EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateOperation>& coordOper
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

		// get the CoordinateRereferenceSystem
		std::shared_ptr<oip::GeorefMetadata> georefMeta = convertCRS(coordOper->TargetCRS);
		// the used GeometricRepresentationContext->ID
		EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationContext> geomContext;

		// get the GeometricContext
		switch (coordOper->SourceCRS.which())
		{
		case 0: // IfcCoordinateReferenceSystem
		{
			throw oip::UnhandledException(coordOper->getErrorLog() + ": We don't handle another IfcCoordinateReferenceSystem as SourceCRS.");
		}
		case 1: // IfcGeometricRepresentationContext
		{
			geomContext = coordOper->SourceCRS.template get<1>();
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

			georefMeta->x = mapConv->Eastings;
			georefMeta->y = mapConv->Northings;
			georefMeta->z = mapConv->OrthogonalHeight;

			// calculate rotation angle
			carve::geom::vector<2> xDir = carve::geom::VECTOR(0., 0.);
			if (mapConv->XAxisAbscissa)
				xDir[0] = mapConv->XAxisAbscissa;
			if (mapConv->XAxisOrdinate)
				xDir[1] = mapConv->XAxisOrdinate;

			double angle = std::atan2(xDir[1], xDir[0]);
			georefMeta->angle = angle;

			if( mapConv->Scale )
			{
				georefMeta->scaleX *= mapConv->Scale;
				georefMeta->scaleY *= mapConv->Scale;
			}
		}

		return std::make_shared<GeorefPair<IfcEntityTypesT>>(geomContext, georefMeta);
	}

	std::shared_ptr<oip::GeorefMetadata> convertCRS(
		const EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>& crs
	) const throw(...)	
	{
		// check input
		if (crs.expired())
			throw oip::ReferenceExpiredException(crs);

		// the interpreted data
		std::shared_ptr<oip::GeorefMetadata> georefMeta = std::make_shared<oip::GeorefMetadata>();

		// EPSG code
		georefMeta->codeEPSG = crs->Name;

		// description (could be WKT) //TODO WKT interpretation
		if( crs->Description )
			georefMeta->addDataEntry( "Description", crs->Description.get());

		if (crs->GeodeticDatum)
			georefMeta->addDataEntry( "Geodetic Datum", crs->GeodeticDatum.get() );

		if (crs->VerticalDatum)
			georefMeta->addDataEntry( "Vertical Datum", crs->VerticalDatum.get());

		if (crs.isOfType<typename IfcEntityTypesT::IfcProjectedCRS>())
		{
			auto projectedCRS = crs.as<typename IfcEntityTypesT::IfcProjectedCRS>();

			if (projectedCRS->MapProjection)
				georefMeta->addDataEntry( "Map Projection", projectedCRS->MapProjection.get());
			if( projectedCRS->MapZone )
				georefMeta->addDataEntry( "Map Zone", projectedCRS->MapZone.get());
			if (projectedCRS->MapUnit)
			{
				double factor = this->UnitConvert()->convertUnit(projectedCRS->MapUnit);
				georefMeta->scaleX *= factor;
				georefMeta->scaleY *= factor;
				georefMeta->scaleZ *= factor;
				georefMeta->addDataEntry( "Map Unit Factor to meters", std::to_string(factor) );
			}
		}

		return georefMeta;
	}


	//! georefeferencing metadata (first = pointer to IfcGeometricRepresentationContext; second = interpreted GeorefMetadata (may be null))
	std::vector<std::shared_ptr<GeorefPair<IfcEntityTypesT>>> georefMetadata_;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(GeoreferencingConverterT)
EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(GeorefPair)

#endif // defined(OpenInfraPlatform_IfcGeometryConverter_GeorefConverter_5F75E53B_DF06_4645_BDAA_F6585F55B2CF_h)
