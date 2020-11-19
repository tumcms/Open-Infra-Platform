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

#include "CarveHeaders.h"
#include "RepresentationConverter.h"
#include "UnitConverter.h"

#include <GeorefMetadata.h>

#include "EXPRESS/EXPRESS.h"

namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{
			class GeometrySettings;

			// IfcImporterUtil class with loadIfcProductsJob, convertIfcProduct, computeMeshsetsFromPolyhedrons.
			class IfcImporterUtil {
			public:
				IfcImporterUtil() {}
				~IfcImporterUtil() {}

				template <
					class IfcEntityTypesT
				>
					static void convertIfcProduct(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
						std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
						const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>> repConverter);

				// ***************************************
				// 3: Compute Meshsets from Polyhedrons
				// ***************************************
				template <
					class IfcEntityTypesT
				>
					static void computeMeshsetsFromPolyhedrons(const std::shared_ptr<oip::EXPRESSEntity>& entity,
						std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
						std::stringstream& strerr,
						const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>> repConverter)
				{
					// now examine the opening data of the product representation
					std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> openingDatas;

					// check if the product is an ifcElement, if so, it may contain opening data
					std::shared_ptr<typename IfcEntityTypesT::IfcElement> element =
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcElement>(entity);

					if(element) {
						// then collect opening data
						repConverter->convertOpenings(element, openingDatas);
					}

					// go through all shapes and convert them to meshsets
					for(auto& itemData : productShape->vec_item_data) {
						// convert closed polyhedrons to meshsets
						itemData->createMeshSetsFromClosedPolyhedrons();

						// if product is IfcElement, then subtract openings like windows, doors, etc.
						if(element) {
							repConverter->subtractOpenings(element, itemData, openingDatas);
						}

						// convert all open polyhedrons to meshsets
						for(auto& openPoly : itemData->open_polyhedrons) {

							if(openPoly->getVertexCount() < 3) { continue; }

							std::shared_ptr<carve::mesh::MeshSet<3>> openMeshset(openPoly->createMesh(carve::input::opts()));
							itemData->meshsets.push_back(openMeshset);
						}

						// convert all open or closed polyhedrons to meshsets
						for(auto& openClosedPoly : itemData->open_or_closed_polyhedrons) {

							if(openClosedPoly->getVertexCount() < 3) { continue; }

							std::shared_ptr<carve::mesh::MeshSet<3>> openMeshset(
								openClosedPoly->createMesh(carve::input::opts()));
							itemData->meshsets.push_back(openMeshset);
						}

						// simplify geometry of all meshsets
						for(auto& meshset : itemData->meshsets) {
							repConverter->getSolidConverter()->simplifyMesh(meshset);
						}
						// polylines are handled by rendering engine
					}

					productShape->computeAABB();
				}
			};

			template <
				class IfcEntityTypesT
			>
				// IfcImporterT class with readStepFile, collectGeometryData, getter and setter. 
			class IfcImporterT 
			{
			public:
				//! constructor
				IfcImporterT();

				//! destructor
				virtual ~IfcImporterT()	{}

				//! getter for shape data
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& getShapeDatas() const { return shapeInputData; }
				//! getter for georeferencing metadata
				std::map<int, oip::GeorefMetadata> getGeorefMetadata() const { return georefMetadata; }


					bool collectGeometryData(std::shared_ptr<oip::EXPRESSModel> model)
					{
						BLUE_LOG(info) << "Importing geometry from express model.";

						auto project = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair) 
							{ return boost::algorithm::to_upper_copy(pair.second->classname())  == "IFCPROJECT"; });

						if(project != model->entities.end()) {

							// Set the unit conversion factors
							oip::EXPRESSReference<typename IfcEntityTypesT::IfcProject> ifcproject =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProject>(project->second);
							setIfcProject(ifcproject);

							// try and find the georeferencing metadata
							auto georef = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair)
								{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>(pair.second) != nullptr; });
							if (georef != model->entities.end() )
								setGeoref(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateReferenceSystem>(georef->second));

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
										IfcImporterUtil::convertIfcProduct<IfcEntityTypesT>(product, productShape, repConverter);
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

					
				std::shared_ptr<GeometrySettings>							geomSettings;
				std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>>	repConverter;
				std::shared_ptr<UnitConverter<IfcEntityTypesT>>				unitConverter;

				//! georefeferencing metadata
				std::map<int, oip::GeorefMetadata> georefMetadata;

				//! shape input data of all products
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
			};
		}
	}
}

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcImporterT)

#endif

