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

#include <algorithm>

#include "CarveHeaders.h"
#include "RepresentationConverter.h"

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		class GeometrySettings;
		
		// IfcImporterUtil class with loadIfcProductsJob, convertIfcProduct, computeMeshsetsFromPolyhedrons.
		class IfcImporterUtil
		{
		public:
			IfcImporterUtil() {}
			~IfcImporterUtil() {}

			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT
			>

			static void convertIfcProduct(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape, 
				const std::shared_ptr<IfcUnitConverterT> unitConverter,
				const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT>> repConverter)
			{
				//#ifdef _DEBUG
				//				std::cout << "Info\t| IfcGeometryConverter.Importer.RepConverter: Converting IFC product " << product->classname() << " #" << product->getId() << std::endl;
				//#endif

				// get id of product
				const uint32_t productId = product->getId();

				double lengthFactor = unitConverter->getLengthInMeterFactor();
				carve::math::Matrix matProduct(carve::math::Matrix::IDENT());

				// check if there's any global object placement for this product
				// if yes, then apply the placement
				if (product->ObjectPlacement)
				{
					std::set<int> placementAlreadyApplied;
					PlacementConverterT<IfcEntityTypesT>::convertIfcObjectPlacement(product->ObjectPlacement,
						matProduct, lengthFactor,
						placementAlreadyApplied);
				}

				// error string
				std::stringstream strerr;

				// go through all representations of the product
				std::shared_ptr<typename IfcEntityTypesT::IfcProductRepresentation>& representation = product->Representation;
				// so evaluate its geometry
				for (auto& rep : representation->Representations)
				{
					// convert each shape of the represenation
					repConverter->convertIfcRepresentation(rep, matProduct, productShape, strerr);
				}

				IfcImporterUtil::computeMeshsetsFromPolyhedrons<IfcEntityTypesT, IfcUnitConverterT>(product, productShape, strerr, repConverter);

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

			// ***************************************
			// 3: Compute Meshsets from Polyhedrons
			// ***************************************
			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT
			>
			static void computeMeshsetsFromPolyhedrons(const std::shared_ptr<oip::EXPRESSEntity>& entity,
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
				std::stringstream& strerr,
				const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT>> repConverter)
			{
				// now examine the opening data of the product representation
				std::vector<shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> openingDatas;

				// check if the product is an ifcElement, if so, it may contain opening data
				shared_ptr<typename IfcEntityTypesT::IfcElement> element =
					dynamic_pointer_cast<typename IfcEntityTypesT::IfcElement>(entity);

				if (element)
				{
					// then collect opening data
					repConverter->convertOpenings(element, openingDatas, strerr);
				}

				// go through all shapes and convert them to meshsets
				for (auto& itemData : productShape->vec_item_data)
				{
					// convert closed polyhedrons to meshsets
					itemData->createMeshSetsFromClosedPolyhedrons();

					// if product is IfcElement, then subtract openings like windows, doors, etc.
					if (element)
					{
						repConverter->subtractOpenings(element, itemData, openingDatas, strerr);
					}

					// convert all open polyhedrons to meshsets
					for (auto& openPoly : itemData->open_polyhedrons)
					{

						if (openPoly->getVertexCount() < 3) { continue; }

						shared_ptr<carve::mesh::MeshSet<3>> openMeshset(openPoly->createMesh(carve::input::opts()));
						itemData->meshsets.push_back(openMeshset);
					}

					// convert all open or closed polyhedrons to meshsets
					for (auto& openClosedPoly : itemData->open_or_closed_polyhedrons)
					{

						if (openClosedPoly->getVertexCount() < 3) { continue; }

						shared_ptr<carve::mesh::MeshSet<3>> openMeshset(
							openClosedPoly->createMesh(carve::input::opts()));
						itemData->meshsets.push_back(openMeshset);
					}

					// simplify geometry of all meshsets
					for (auto& meshset : itemData->meshsets)
					{
						repConverter->getSolidConverter()->simplifyMesh(meshset);
					}
					// polylines are handled by rendering engine
				}

				productShape->computeAABB();
			}
		};

		template <
			class IfcEntityTypesT,
			class IfcUnitConverterT
		>

		// IfcImporterT class with readStepFile, collectGeometryData, getter and setter. 
		class IfcImporterT
		{
		public:
			IfcImporterT()
			{
				geomSettings = std::make_shared<GeometrySettings>();
				unitConverter = std::make_shared<IfcUnitConverterT>();
				repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT>>(geomSettings, unitConverter);
			}

			virtual ~IfcImporterT()
			{

			}
					

			bool collectGeometryData(std::shared_ptr<oip::EXPRESSModel> model) {
				auto project = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair) {return pair.second.classname() == "IFCPROJECT"; });

				if (project != model->entities.end()) {
					std::for_each(model->entities.begin(), model->entities.end(), [&shapeInputData, &model](std::pair<size_t, std::shared_ptr<oip::EXPRESSEntity>> &pair) {
						std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProduct>(pair.second);
						if (product) {
							// create new shape input data for product
							shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape = std::make_shared<ShapeInputDataT<IfcEntityTypesT>>();
							productShape->ifc_product = product;
							IfcImporterUtil::convertIfcProduct<IfcEntityTypesT, IfcUnitConverterT>(product, productShape, unitConverter, repConverter);
							shapeInputData.insert(std::make_pair<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>(pair.first, productShape));
						}
					});

				}
				else {
					return false;
				}
				return true;
			}

			// ***************************************
			// 3: Getter and Setter
			// ***************************************
					

			std::shared_ptr<GeometrySettings>& getGeomSettings() { return geomSettings; }
			std::shared_ptr<IfcUnitConverterT>& getUnitConverter() { return unitConverter; }
			std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& getShapeDatas() { return shapeInputData; }

		protected:

			std::shared_ptr<GeometrySettings>		geomSettings;
			std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT>> repConverter;
			std::shared_ptr<IfcUnitConverterT>		unitConverter;
			

			// shape input data of all products
			std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
		};
	}
}

#endif
