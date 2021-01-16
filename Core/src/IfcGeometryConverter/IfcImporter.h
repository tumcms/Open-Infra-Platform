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

#ifndef IFC_IMPORTER_H
#define IFC_IMPORTER_H

#include <thread>
#include <mutex>
#include <memory>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "namespace.h"
#include "CarveHeaders.h"
#include "RepresentationConverter.h"
#include "UnitConverter.h"
#include "IfcImporterUtil.h"

#include <GeorefMetadata.h>

#include "EXPRESS/EXPRESS.h"

namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{
			class GeometrySettings;

			template <
				class IfcEntityTypesT
			>
				// IfcImporterT class with readStepFile, collectGeometryData, getter and setter. 
			class IfcImporterT 
			{
				public:
					IfcImporterT()
					{
						geomSettings = std::make_shared<GeometrySettings>();
						unitConverter = std::make_shared<UnitConverter<IfcEntityTypesT>>();
						repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT>>(geomSettings, unitConverter);
					}

					virtual ~IfcImporterT()
					{

					}


					bool collectGeometryData(std::shared_ptr<oip::EXPRESSModel> model)
					{
						BLUE_LOG(info) << "Importing geometry from express model.";

						auto project = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair) 
							{ return boost::algorithm::to_upper_copy(pair.second->classname())  == "IFCPROJECT"; });

						if(project != model->entities.end()) {

							// Set the unit conversion factors
							oip::EXPRESSReference<typename IfcEntityTypesT::IfcProject> ifcproject(project->second, model);
							setIfcProject(ifcproject);

							// try and find the georeferencing metadata
							auto georef = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair)
								{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>(pair.second) != nullptr; });
							if (georef != model->entities.end() )
								setGeoref(oip::EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>(georef->second, model));

							//std::for_each(model->entities.begin(), model->entities.end(), [this, &model](std::pair<size_t, std::shared_ptr<oip::EXPRESSEntity>> &pair) {
							//	std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProduct>(pair.second);
							//	if (product) {
							//		// create new shape input data for product
							//		std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape = std::make_shared<ShapeInputDataT<IfcEntityTypesT>>();
							//		productShape->ifc_product = product;
							//		IfcImporterUtil::convertIfcProduct<IfcEntityTypesT, IfcUnitConverterT>(product, productShape, unitConverter, repConverter);
							//		shapeInputData.insert(std::make_pair<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>(pair.first, productShape));
							//	}
							//});
							try {
								for (auto& pair : model->entities) {
									std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProduct>(pair.second);
									if (product) {
#ifdef _DEBUG
										BLUE_LOG(trace) << "Converting IfcProduct #" << product->getId();
#endif
										// create new shape input data for product
										std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape = std::make_shared<ShapeInputDataT<IfcEntityTypesT>>();
										productShape->ifc_product = product;
										IfcImporterUtilT<IfcEntityTypesT>::convertIfcProduct(product, productShape, repConverter);
										shapeInputData.insert(std::pair<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>(pair.first, productShape));
									}
								}
							}
							catch (std::exception e) {
								BLUE_LOG(warning) << "Failed collecting geometry data. Abort. " << e.what();
								return false;
							}
						}
						else {
							BLUE_LOG(warning) << "No IfcProject found in model.";
							return false;
						}
						BLUE_LOG(info) << "Imported geometry from express model.";
						return true;
					}

					/*! \brief Sets the common values from \c IfcProject.

					Sets the units and georeferencing.

					\param[in] project A pointer to the \c IfcProject entity within the IFC model.
					*/
					void setIfcProject(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProject>& project)
					{
						// tell the unit converter about the project's units
						unitConverter->setIfcProject(project);

						// get the georeferencing metadata
						//TODO when inverse are covered
						//setGeoref(crs);
					}


					void setGeoref(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>& crs)
					{
						georefMetadata.codeEPSG = crs->Name;

						if (crs.isOfType<typename IfcEntityTypesT::IfcProjectedCRS>())
						{
						}
					}


					// ***************************************
					// 3: Getter and Setter
					// ***************************************


					std::shared_ptr<GeometrySettings>& getGeomSettings() { return geomSettings; }
					std::shared_ptr<UnitConverter<IfcEntityTypesT>>& getUnitConverter() { return unitConverter; }
					std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& getShapeDatas() { return shapeInputData; }
					oip::GeorefMetadata getGeorefMetadata() { return georefMetadata; }

				protected:

					std::shared_ptr<GeometrySettings>							geomSettings;
					std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>>	repConverter;
					std::shared_ptr<UnitConverter<IfcEntityTypesT>>				unitConverter;

					// georef metadata
					oip::GeorefMetadata georefMetadata;

					// shape input data of all products
					std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
			};
		}
	}
}

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcImporterT)

#endif

