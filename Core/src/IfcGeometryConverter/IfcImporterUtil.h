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

#ifndef IFC_IMPORTER_UTIL_H
#define IFC_IMPORTER_UTIL_H

#include "EXPRESS/EXPRESS.h"

namespace OpenInfraPlatform 
{
	namespace Core 
	{
		namespace IfcGeometryConverter 
		{
			// IfcImporterUtilT class with loadIfcProductsJob, convertIfcProduct, computeMeshsetsFromPolyhedrons.
			template <typename IfcEntityTypesT>
			class IfcImporterUtilT {
			public:
				IfcImporterUtilT() {}
				~IfcImporterUtilT() {}

				static void convertIfcProduct(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> productShape,
					const std::shared_ptr<RepresentationConverterT<IfcEntityTypesT>> repConverter);

				static oip::EXPRESSReference<typename IfcEntityTypesT::IfcGeometricRepresentationItem> getIfcLinearPositioningElementAxis(
					const oip::EXPRESSReference<typename IfcEntityTypesT::IfcLinearPositioningElement>& linposel);

				// ***************************************
				// 3: Compute Meshsets from Polyhedrons
				// ***************************************
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
		}
	}
}

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(IfcImporterUtilT)

#endif

