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

			/*! \brief The IFC importer class.
			 *
			 * This class calls other converters correspondingly.
			 * This should be used as an entry point to the IFC converter functionalities.
			 *
			 * \param IfcEntityTypesT The IFC version templates
			 */
			template <
				class IfcEntityTypesT
			>
			class IfcImporterT 
			{
			public:
				//! constructor
				IfcImporterT();

				//! destructor
				virtual ~IfcImporterT()	{}

				//! getter for shape data
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> getShapeDatas() const { return shapeInputData; }
				//! getter for georeferencing metadata
				std::map<int, oip::GeorefMetadata> getGeorefMetadata() const { return georefMetadata; }

				/**
				 * \brief Interprets the data from the read-in IFC file.
				 *
				 * This is the main interpreting function. 
				 * It sets the member variables with the interpreted data to be given to the renderer, UI or whatever.
				 *
				 * \param[in] model The IFC content.
				 * \return true, if successful. false, otherwise.
				 */
				bool collectData(std::shared_ptr<oip::EXPRESSModel> model)
				{
					try
					{
						// set the default units
						setUnits(model);

						// get the georeferencingmetadata from the file
						setGeoref(model);

						// collect all geometries
						return collectGeometryData(model);
					}
					catch (const oip::InconsistentModellingException& ex)
					{
						BLUE_LOG(warning) << "Inconsistent IFC moddelling: " << ex.what();
						return false;
					}
					catch (...)
					{
						BLUE_LOG(warning) << "Something went wrong while collecting data from the IFC file.";
						return false;
					}
					return true;
				}

			private:
					/**
					 * \brief Interprets the data from the read-in IFC file.
					 *
					 * This is the main interpreting function.
					 * It sets the member variables with the interpreted data to be given to the renderer, UI or whatever.
					 *
					 * \param[in] model The IFC content.
					 * \return true, if successful. false, otherwise.
					 */
					bool collectGeometryData(std::shared_ptr<oip::EXPRESSModel> model)
					{
						BLUE_LOG(info) << "Importing geometry from express model.";

						auto project = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair) 
							{ return boost::algorithm::to_upper_copy(pair.second->classname())  == "IFCPROJECT"; });

						if(project != model->entities.end()) {
							
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
										convertIfcProduct<IfcEntityTypesT>(product, productShape);
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

				/*! \brief Sets the units from the IFC file.
				 *
				 * \param[in] model The IFC content.
				 */
				void setUnits(std::shared_ptr<oip::EXPRESSModel> model) throw(...)
				{
					// Set the unit conversion factors
					auto units = std::find_if(model->entities.begin(), model->entities.end(),
						[](const auto& pair) { return pair.second->classname() == "IFCUNITASSIGNMENT"; });
					if ( units == model->entities.end() )
						throw oip::InconsistentModellingException("Default units are not defined.");
					// tell the unit converter about the project's units
					unitConverter->setIfcUnits(std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcUnitAssignment>(units->second));
				}

				/*! \brief Sets the georeferencing metadata from the IFC file.
				 *
				 * \param[in] model The IFC content.
				 */
				void setGeoref(std::shared_ptr<oip::EXPRESSModel> model) throw(...)
				{
					//ENTITY IfcCoordinateOperation
					//	ABSTRACT SUPERTYPE OF(IfcMapConversion);
					//  SourceCRS: IfcCoordinateReferenceSystemSelect;
					//  TargetCRS: IfcCoordinateReferenceSystem;
					//END_ENTITY;
					// try and find the georeferencing metadata
					auto georef = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair)
						{ return std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcCoordinateOperation>(pair.second) != nullptr; });
					if (georef == model->entities.end())
						return; // no georeferencing specified

					//ENTITY IfcMapConversion
					//	SUBTYPE OF(IfcCoordinateOperation);
					//  Eastings: IfcLengthMeasure;
					//  Northings: IfcLengthMeasure;
					//  OrthogonalHeight: IfcLengthMeasure;
					//  XAxisAbscissa: OPTIONAL IfcReal;
					//  XAxisOrdinate: OPTIONAL IfcReal;
					//  Scale: OPTIONAL IfcReal;
					//END_ENTITY;

					//const oip::EXPRESSReference<typename IfcEntityTypesT::IfcCoordinateReferenceSystem> crs;
					//georefMetadata.codeEPSG = crs->Name;
					//if (crs.isOfType<typename IfcEntityTypesT::IfcProjectedCRS>())
					//{
					//}
				}

				/**
				 * \brief Converts all geometries of an \c IfcProduct to triangles and lines.
				 * 
				 * \param[in] product 
				 * \param[inout] productShape
				 * 
				 * \note
				 */
				void convertIfcProduct(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape);
					
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

