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
	 * \return An array of pointers to an \c IfcModel. Could be empty, though!
	 */
	std::vector<std::shared_ptr<IfcModel>> collectData(std::shared_ptr<oip::EXPRESSModel> expressModel)
	{
		std::vector<std::shared_ptr<IfcModel>> models;
		try
		{
			// set the default units
			unitConverter->init(expressModel);

			// get the georeferencingmetadata from the file
			georefConverter->init(expressModel);

			// collect all geometries
			if (!collectGeometryData(expressModel))
				return models;

			// loop through all georeferencing
			// produce a separate IfcModel for each
			for (const auto& georef : georefConverter->getGeorefMetadata())
			{
				auto ifcModel = createGeometryModel(georef, shapeInputData);
				if( !ifcModel->isEmpty() )
					models.push_back(ifcModel);
			}

			// some models do not have georeferencing to a context assigned
			// add all those elements as a separate IFcModel
			auto ifcModel = createGeometryModel(nullptr, shapeInputData);
			if (!ifcModel->isEmpty())
				models.push_back(ifcModel);

			//store a pointer to the express model in the in the ifc model (used for the tree viewer)
			for (auto& model : models)
			{
				model->setExpressModel(expressModel);
			}

			return models;
		}
		catch (const oip::InconsistentModellingException& ex)
		{
			BLUE_LOG(warning) << "Inconsistent IFC moddelling: " << ex.what();
			return models;
		}
		catch (const std::invalid_argument& ex)
		{
			BLUE_LOG(error) << "Invalid argument exception: " << ex.what();
			return models;
		}
		catch (...)
		{
			BLUE_LOG(warning) << "Something went wrong while collecting data from the IFC file.";
			return models;
		}
		return models;
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
					oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct> product =
						oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>::constructInstance(pair.first, model);
					if (product) {
						#ifdef _DEBUG
						BLUE_LOG(trace) << "Converting " << product->getErrorLog();
						#endif
						// create new shape input data for product
						const auto& productShape = convertIfcProduct(product);
						std::copy(productShape.begin(), productShape.end(), std::back_inserter(shapeInputData) );
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
	 * \return An array of pointers to shape data.
	 */
	std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> convertIfcProduct(
		const EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product) const;
				
	/**
	 * \brief Computes meshes given \c ShapeInputDataT-s.
	 *
	 * \param[in] productShape The shape datas to be parsed.
	 */
	void computeMeshsetsFromPolyhedrons(
		std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape) const;
					
	std::shared_ptr<IfcModel> createGeometryModel(
		const std::shared_ptr<oip::GeorefPair<IfcEntityTypesT>>& georef,
		const std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& shapeDatas)
	{
		// clear all descriptions
		std::shared_ptr<oip::IfcModel> ifcModel = std::make_shared<oip::IfcModel>();
		if( georef && georef->second )
			ifcModel->setGeoref(*(georef->second));

		// obtain maximum number of threads supported by machine
		const unsigned int maxNumThreads = std::thread::hardware_concurrency();

		// split up tasks for all threads
		std::vector<std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>> tasks(maxNumThreads);
		uint32_t counter = 0;
		for (auto it = shapeDatas.begin(); it != shapeDatas.end(); ++it) {
			std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> shapeData = *it;
			// only add if it's the same georef (that is, if there; otherwise only add those that do not have georef context)
			if(    ( georef &&  georefConverter->isSameContext(georef->first, shapeData->getContext()))
				|| (!georef && !georefConverter->hasContext(shapeData->getContext())) )
			{
				tasks[counter % maxNumThreads].push_back(shapeData);
				counter++;
			}
		}

		// create threads and start creation job
		std::vector<std::thread> threads(maxNumThreads);
		// every thread gets its local triangle/polyline pool
		for (unsigned int k = 0; k < maxNumThreads; ++k) {
			threads[k] = std::thread(&ConverterBuwT<IfcEntityTypesT>::createTrianglesJob, tasks[k], k, ifcModel);
		}

		// wait for all threads to be finished
		for (unsigned int l = 0; l < maxNumThreads; ++l) {
			threads[l].join();
		}

		return ifcModel;
	}

	// the converters
	std::shared_ptr<GeometrySettings>							geomSettings;
	std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>>	repConverter;
	std::shared_ptr<UnitConverter<IfcEntityTypesT>>				unitConverter;
	std::shared_ptr<GeoreferencingConverterT<IfcEntityTypesT>>	georefConverter;

	//! interpreted data of all products
	std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcImporterT)

#endif

