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
#include "GeorefConverter.h"

#include "EXPRESS/EXPRESS.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN

			class GeometrySettings;

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

				/**
				 * \brief Interprets the data from the read-in IFC file.
				 *
				 * This is the main interpreting function. 
				 *
				 * \param[in] model The IFC content.
				 * \return If successful, a pointer to an \c IfcModel. Otherwise \c nullptr.
				 */
				std::shared_ptr<IfcModel> collectData(std::shared_ptr<oip::EXPRESSModel> expressModel)
				{
					auto ifcModel = std::make_shared<IfcModel>();
					try
					{
						// set the default units
						unitConverter->init(expressModel);

						// get the georeferencingmetadata from the file
						georefConverter->init(expressModel);

						// collect all geometries
						if (!collectGeometryData(expressModel))
							return ifcModel;

						auto converter = ConverterBuwT<IfcEntityTypesT>();
						if (!converter.createGeometryModel(ifcModel, shapeInputData))
							return ifcModel;

						return ifcModel;
					}
					catch (const oip::InconsistentModellingException& ex)
					{
						BLUE_LOG(warning) << "Inconsistent IFC moddelling: " << ex.what();
						return ifcModel;
					}
					catch (...)
					{
						BLUE_LOG(warning) << "Something went wrong while collecting data from the IFC file.";
						return ifcModel;
					}
					return ifcModel;
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
							
							try {
								for (auto& pair : model->entities) {
									std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProduct>(pair.second);
									if (product) {
#ifdef _DEBUG
										BLUE_LOG(trace) << "Converting IfcProduct #" << product->getId();
#endif
										// create new shape input data for product
										std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape = convertIfcProduct(product);
										productShape->ifc_product = product;
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

				/**
				 * \brief Converts all geometries of an \c IfcProduct to triangles and lines.
				 * 
				 * \param[in] product The product to be interpreted.
				 * \return A pointer to shape data.
				 */
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> convertIfcProduct(
					const EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product) const;
				
				/**
				 * \brief Computes meshes given \c ShapeInputDataT-s.
				 *
				 * \param[in] productShape The shape datas to be parsed.
				 */
				void computeMeshsetsFromPolyhedrons(
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape) const;
					
				// the converters
				std::shared_ptr<GeometrySettings>							geomSettings;
				std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>>	repConverter;
				std::shared_ptr<UnitConverter<IfcEntityTypesT>>				unitConverter;
				std::shared_ptr<GeoreferencingConverterT<IfcEntityTypesT>>	georefConverter;

				//! interpreted data of all products
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
			};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcImporterT)

#endif

