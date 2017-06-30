/*
    Copyright (c) 2017 Technical University of Munich
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

#include "CarveHeaders.h"
#include "RepresentationConverter.h"

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		class GeometrySettings;

		class IfcImporterUtil
		{
		public:
			IfcImporterUtil() {}
			~IfcImporterUtil() {}

			static std::mutex s_productMutex;

			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT,
				class IfcEntityT,
				class IfcExceptionT
			>
			static void loadIfcProductsJob(const std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProduct>>& tasks, 
				const int threadID,
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>* shapeInputData,
				const std::shared_ptr<IfcUnitConverterT> unitConverter,
				const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>> repConverter)
			{
				//#ifdef _DEBUG
				//				std::cout << "Info\t| Starting thread " << threadID << " to import IFC products" << std::endl;
				//#endif
				for (auto it = tasks.begin(); it != tasks.end(); ++it)
				{
					std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product = *it;

					const uint32_t entityID = product->getId();

					// create new shape input data for product
					shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape(new ShapeInputDataT<IfcEntityTypesT>());
					productShape->ifc_product = product;

					// convert ifc product info to shape data
					try
					{
						IfcImporterUtil::convertIfcProduct<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT, IfcExceptionT>(product, productShape, unitConverter, repConverter);
					}
					catch (IfcExceptionT& e)
					{
#ifdef _DEBUG
						std::cerr << "Error\t| " << e.what() << std::endl;
#endif
						continue;
					}
					catch (std::exception& e)
					{
#ifdef _DEBUG
						std::cerr << "Error\t| " << e.what() << std::endl;
#endif
						continue;
					}
					catch (carve::exception& e)
					{
#ifdef _DEBUG
						std::cerr << "Error\t| " << e.str() << std::endl;
#endif
						continue;
					}

					if (productShape->vec_item_data.size() > 0)
					{
						// enter critical section
						s_productMutex.lock();

						// insert shape data into global shape datas
						shapeInputData->insert(std::make_pair(entityID, productShape));

						s_productMutex.unlock();
					}
				}
				//#ifdef _DEBUG
				//				std::cout << "Info\t| Finished thread " << threadID << std::endl;
				//#endif
			}

			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT,
				class IfcEntityT,
				class IfcExceptionT
			>
			static void convertIfcProduct(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape, 
				const std::shared_ptr<IfcUnitConverterT> unitConverter,
				const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>> repConverter)
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
				if (product->m_ObjectPlacement)
				{
					std::set<int> placementAlreadyApplied;
					PlacementConverterT<IfcEntityTypesT>::convertIfcObjectPlacement(product->m_ObjectPlacement,
						matProduct, lengthFactor,
						placementAlreadyApplied);
				}

				// error string
				std::stringstream strerr;

				// go through all representations of the product
				std::shared_ptr<typename IfcEntityTypesT::IfcProductRepresentation>& representation = product->m_Representation;
				// so evaluate its geometry
				for (auto& rep : representation->m_Representations)
				{
					// convert each shape of the represenation
					repConverter->convertIfcRepresentation(rep, matProduct, productShape, strerr);
				}

				IfcImporterUtil::computeMeshsetsFromPolyhedrons<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT, IfcExceptionT>(product, productShape, strerr, repConverter);

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

			template <
				class IfcEntityTypesT,
				class IfcUnitConverterT,
				class IfcEntityT,
				class IfcExceptionT
			>
			static void computeMeshsetsFromPolyhedrons(const std::shared_ptr<IfcEntityT>& entity,
				std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
				std::stringstream& strerr,
				const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>> repConverter)
			{
				// now examine the opening data of the product representation
				std::vector<shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> openingDatas;

				// check if the prodcut is an ifcElement, then it may contain opening data
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
			class IfcUnitConverterT,
			class IfcModelT,
			class IfcStepReaderT,
			class IfcExceptionT,
			class IfcEntityT
		>
		class IfcImporterT
		{
		public:
			IfcImporterT()
			: m_progress(0.0f)
			{
				m_ifcModel = std::make_shared<IfcModelT>();
				m_geomSettings = std::make_shared<GeometrySettings>();
				m_unitConverter = std::make_shared<IfcUnitConverterT>();
				m_repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>>(m_geomSettings, m_unitConverter);
				m_ifcStepReader = std::make_shared<IfcStepReaderT>();
			}

			virtual ~IfcImporterT()
			{

			}

			bool readStepFile(const char* filename)
			{
				const unsigned found = std::string(filename).find_last_of("/\\");
				m_filename = std::string(filename).substr(found + 1);

				// parse step file *.ifc or *.stp
				std::string name(filename);
				std::string extension = name.substr(name.find_last_of(".") + 1);

				if (extension != "ifc" && extension != "stp")
				{
					std::cout << "Error:\t| Extension of step file is not supported" << std::endl;
					return false;
				}

				std::ifstream file(filename);
				if (!file.is_open())
				{
					std::cout << "Error:\t| Could not open file: " << filename << std::endl;
					return false;
				}

				file.seekg(0, std::ios::end);
				uint64_t fileSize = static_cast<uint64_t>(file.tellg());
				file.seekg(0, std::ios::beg);

				std::string buffer(fileSize, '\0');

				std::cout << "Info\t| IfcGeometryConverter.Importer: Loading IFC step file" << std::endl;
				file.read(&buffer[0], fileSize);

				file.close();

				// create a new ifc model, so clear the current model
				m_ifcModel->clearIfcModel();

				try
				{
					std::cout << "Info\t| IfcGeometryConverter.Importer.StepReader: Reading IFC header" << std::endl;
					// read the header of the step file
					m_ifcStepReader->readStreamHeader(buffer, m_ifcModel);
				}
				catch (IfcExceptionT& e)
				{
					std::cerr << "Exception\t| " << e.what() << std::endl;
					return false;
				}

				m_version = m_ifcModel->getFileSchema();

				std::cout << "Info\t| IfcGeometryConverter.Importer.StepReader: Detected scheme version: " << m_version << std::endl;
				std::cout << "Info\t| IfcGeometryConverter.Importer.StepReader: Parsing step file for entities" << std::endl;

				std::map< int, shared_ptr<IfcEntityT>> ifcMap;

				try
				{
					// read the stream data and convert the entities into a map
					m_ifcStepReader->readStreamData(buffer, ifcMap);
				}
				catch (...)//IfcException& e)
				{
					//std::cerr << "Exception\t| " << e.what() << std::endl;
				}

				std::cout << "Info\t| IfcGeometryConverter.Importer: Create corresponding IFC model" << std::endl;
				m_products.clear();
				m_products.reserve(ifcMap.size());

				// add the parsed entities into the model
				for (auto it = ifcMap.begin(); it != ifcMap.end(); ++it)
				{
					shared_ptr<IfcEntityT>& entity = it->second;
					try
					{
						m_ifcModel->insertEntity(entity);
					}
					catch (IfcExceptionT& e)
					{
						std::cout << e.what() << std::endl;
						return false;
					}

					std::shared_ptr<typename IfcEntityTypesT::IfcProduct> product =
						dynamic_pointer_cast<typename IfcEntityTypesT::IfcProduct>(entity);

					// if there are any IFC products, try to extract their geometry
					if (product)
					{
						// if product is a substraction element, 
						// continue as geometry will be created in subtract openings
						if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcFeatureElementSubtraction>(product))
						{
							continue;
						}

						// if product has no representations, then omit it
						if (!product->m_Representation)
						{
#ifdef _DEBUG
							std::cout << "Warning\t| IfcGeometryConverter.Importer: This product has no representations: " << product->classname()
								<< "  #" << product->getId() << std::endl;
#endif
							continue;
						}

						m_products.push_back(product);
					}
				}

				std::cout << "Info\t| IfcGeometryConverter.Importer: Resolve inverse attributes" << std::endl;
				m_ifcModel->resolveInverseAttributes();
				m_ifcModel->updateCache();

				// set unit converter and create new representation converter
				m_unitConverter = m_ifcModel->getUnitConverter();
				m_repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>>(m_geomSettings, m_unitConverter);

				return true;
			}

			

			bool collectGeometryData()
			{
				// first get the ifc project
				shared_ptr<typename IfcEntityTypesT::IfcProject> project = m_ifcModel->getIfcProject();

				if (!project)
				{
					std::cerr << "Warning\t| No standard/valid IFC project in loaded IFC model. Geometry cannot be imported" << std::endl;
					return false;
				}

				std::cout << "Info\t| IfcGeometryConverter.Importer: Collecting geometry data of all IFC products" << std::endl;

				// clear all shape input data and cache
				m_shapeInputData.clear();
				m_repConverter->getProfileCache()->clearProfileCache();

				// geometry settings
				double length_to_meter_factor = m_ifcModel->getUnitConverter()->getLengthInMeterFactor();
				carve::setEpsilon(1.4901161193847656e-08*length_to_meter_factor);

				const std::map<int, shared_ptr<IfcEntityT>>& map = m_ifcModel->getMapIfcObjects();

				// gather tasks for all possible tasks
				const unsigned int maxNumThreads = std::thread::hardware_concurrency();
				//std::cout << "CPU THREADS: " << maxNumThreads << std::endl;

				std::vector<std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProduct>>> tasks(maxNumThreads);
				
				for (unsigned int n = 0; n < maxNumThreads; ++n)
				{
					tasks[n].reserve(m_products.size() / maxNumThreads + 1);
				}

				for (auto m = 0; m < m_products.size(); ++m)
				{
					tasks[m % maxNumThreads].push_back(m_products[m]);
				}

				// create threads and start them
				std::vector<std::thread> threads(maxNumThreads);

				for (unsigned int o = 0; o < maxNumThreads; ++o)
				{
					threads[o] = std::thread(&IfcImporterUtil::loadIfcProductsJob<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT, IfcExceptionT>, tasks[o], o,
						&m_shapeInputData, m_unitConverter, m_repConverter);
				}

				// wait for all threads to be finished
				for (unsigned int l = 0; l < maxNumThreads; ++l)
				{
					threads[l].join();
				}

				return true;
			}

			// getter and setter
			void setIfcModel(std::shared_ptr<IfcModelT> model)
			{
				if (m_ifcModel)
				{
					m_ifcModel->clearIfcModel();
				}

				m_ifcModel = model;
				m_unitConverter = m_ifcModel->getUnitConverter();
				m_repConverter = std::make_shared<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>>(m_geomSettings, m_unitConverter);
			}

			const std::string& getIfcVersion() const { return m_version; }

			std::shared_ptr<IfcModelT>& getIfcModel() { return m_ifcModel; }
			std::shared_ptr<GeometrySettings>& getGeomSettings() { return m_geomSettings; }
			std::shared_ptr<IfcUnitConverterT>& getUnitConverter() { return m_unitConverter; }
			std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& getShapeDatas() { return m_shapeInputData; }

		protected:

			std::shared_ptr<IfcModelT>				m_ifcModel;
			std::shared_ptr<IfcStepReaderT>			m_ifcStepReader;
			std::shared_ptr<GeometrySettings>		m_geomSettings;
			std::shared_ptr<RepresentationConverterT<IfcEntityTypesT, IfcUnitConverterT, IfcEntityT>> m_repConverter;
			std::vector<std::shared_ptr<typename IfcEntityTypesT::IfcProduct>> m_products;
			std::shared_ptr<IfcUnitConverterT>		m_unitConverter;
			std::string								m_filename;
			std::string								m_version;

			float									m_progress;

			// shape input data of all products
			std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> m_shapeInputData;
		};
	}
}

#endif
