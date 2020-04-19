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

#include "CarveHeaders.h"
#include "RepresentationConverter.h"

#include "UnitConverter.h"

#include <boost/algorithm/string.hpp>

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
//				{
//					//#ifdef _DEBUG
//					//				std::cout << "Info\t| IfcGeometryConverter.Importer.RepConverter: Converting IFC product " << product->classname() << " #" << product->getId() << std::endl;
//					//#endif
//
//					// get id of product
//					const uint32_t productId = product->getId();
//
//					double lengthFactor = unitConverter->getLengthInMeterFactor();
//					carve::math::Matrix matProduct(carve::math::Matrix::IDENT());
//
//					// check if there's any global object placement for this product
//					// if yes, then apply the placement
//					if(product->ObjectPlacement) {
//						// decltype(x) returns the compile time type of x.
//						//decltype(product->ObjectPlacement)::type &objectPlacement = product->ObjectPlacement;
//
//						OpenInfraPlatform::EarlyBinding::EXPRESSReference<typename IfcEntityTypesT::IfcObjectPlacement>& objectPlacement = product->ObjectPlacement;
//
//						//auto& optObjectPlacement = product->ObjectPlacement;	// store optional<weak_ptr> product->ObjectPlacement in optObjectPlacement.
//						//auto& objectPlacement = *optObjectPlacement;			// extract weak_ptr from optional<weak_ptr> optObjectPlacement.
//						auto& objectPlacement_ptr = objectPlacement.lock();		// get std::shared_ptr used to construct the weak_ptr.
//																				// OR auto& objectPlacement = optObjectPlacement.get();
//
//						std::set<int> placementAlreadyApplied;
//						PlacementConverterT<IfcEntityTypesT>::convertIfcObjectPlacement(objectPlacement_ptr,
//							matProduct, lengthFactor,
//							placementAlreadyApplied);
//
//#ifdef _DEBUG
//						BLUE_LOG(trace) << "Processed IfcObjectPlacement #" << objectPlacement->getId();
//#endif
//					}
//
//					// error string
//					std::stringstream strerr;
//
//					// go through all representations of the product
//					if(product->Representation) {
//#ifdef _DEBUG
//						BLUE_LOG(trace) << "Processing IfcProductRepresentation #" << product->Representation->getId();
//#endif
//						OpenInfraPlatform::EarlyBinding::EXPRESSReference<typename IfcEntityTypesT::IfcProductRepresentation>& representation = product->Representation;
//						// so evaluate its geometry
//						for(EXPRESSReference<typename IfcEntityTypesT::IfcRepresentation>& rep : representation->Representations) {
//							// convert each shape of the represenation
//#ifdef _DEBUG
//							BLUE_LOG(trace) << "Processing IfcRepresentation #" << rep->getId();
//#endif
//							repConverter->convertIfcRepresentation(rep.lock(), matProduct, productShape, strerr);
//#ifdef _DEBUG
//							BLUE_LOG(trace) << "Processed IfcRepresentation #" << rep->getId();
//#endif
//						}
//
//						IfcImporterUtil::computeMeshsetsFromPolyhedrons<IfcEntityTypesT, IfcUnitConverterT>(product, productShape, strerr, repConverter);
//#ifdef _DEBUG
//						BLUE_LOG(trace) << "Processed IfcProductRepresentation #" << representation->getId();
//#endif
//					}
//
//					if (std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment>(product)) {
//						auto alignment = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcAlignment>(product);
//						std::shared_ptr<ItemData> itemData(new ItemData());
//						productShape->vec_item_data.push_back(itemData);
//						std::shared_ptr<typename IfcEntityTypesT::IfcGeometricRepresentationItem> axis = std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcGeometricRepresentationItem>(alignment->Axis.lock());
//						repConverter->convertIfcGeometricRepresentationItem(axis, carve::math::Matrix::IDENT(), itemData, strerr);
//					}
//
//#ifdef _DEBUG
//					if(strerr.tellp() <= 0) return;
//
//					std::stringstream ss;
//					ss << "log/" << "-" << product->classname()
//						<< "#" << product->getId() << ".txt";
//
//					std::ofstream debugLog(ss.str());
//					debugLog << strerr.str();
//					debugLog.close();
//#endif
//				}

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
						repConverter->convertOpenings(element, openingDatas, strerr);
					}

					// go through all shapes and convert them to meshsets
					for(auto& itemData : productShape->vec_item_data) {
						// convert closed polyhedrons to meshsets
						itemData->createMeshSetsFromClosedPolyhedrons();

						// if product is IfcElement, then subtract openings like windows, doors, etc.
						if(element) {
							repConverter->subtractOpenings(element, itemData, openingDatas, strerr);
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

						auto project = std::find_if(model->entities.begin(), model->entities.end(), [](auto pair) { return boost::algorithm::to_upper_copy(pair.second->classname())  == "IFCPROJECT"; });

						if(project != model->entities.end()) {

							// Set the unit conversion factors
							std::shared_ptr<typename IfcEntityTypesT::IfcProject> ifcproject =
								std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcProject>(project->second);
							unitConverter->setIfcProject(ifcproject);

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

					// ***************************************
					// 3: Getter and Setter
					// ***************************************


					std::shared_ptr<GeometrySettings>& getGeomSettings() { return geomSettings; }
					std::shared_ptr<UnitConverter<IfcEntityTypesT>>& getUnitConverter() { return unitConverter; }
					std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& getShapeDatas() { return shapeInputData; }

				protected:

					std::shared_ptr<GeometrySettings>							geomSettings;
					std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>>	repConverter;
					std::shared_ptr<UnitConverter<IfcEntityTypesT>>				unitConverter;


					// shape input data of all products
					std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>> shapeInputData;
			};
		}
	}

#endif

}

