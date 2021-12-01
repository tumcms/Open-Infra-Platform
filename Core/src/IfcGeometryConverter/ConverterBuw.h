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

// visual studio
#pragma once
// unix
#ifndef CONVERTERBUW_H
#define CONVERTERBUW_H

#include <unordered_map>
#include <thread>
#include <mutex>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include "CarveHeaders.h"
#include "GeometryInputData.h"
#include "IfcGeometryModel.h"
#include <BBox.h>

#include "namespace.h"
#include "EXPRESS/EXPRESS.h"

/***********************************************************************************************/

typedef std::unordered_map<std::string, uint32_t> VertexMapTriangles;
typedef std::unordered_map<std::string, uint32_t> VertexMapLines;

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_BEGIN

			template <
				class IfcEntityTypesT
			>
				class ConverterBuwT {
				public:
					// static const float FullyOpaqueAlphaThreshold;
					// static const float FullyTransparentAlphaThreshold;

					ConverterBuwT() {}

					virtual ~ConverterBuwT() {}

					static bool insertFaceIntoBuffers(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product,
						const carve::mesh::Face<3>* face,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						// omit spaces & opening elements
						if (product.template isOfType<typename IfcEntityTypesT::IfcSpace>()
						 || product.template isOfType<typename IfcEntityTypesT::IfcFeatureElementSubtraction>()) {
							return false;//color.w() <= FullyOpaqueAlphaThreshold;
						}

						const int32_t numVertices = face->nVertices();

						if(numVertices > 4) {
							std::cout << "Error\t| Detected face with more than 4 vertices."
								<< " This is not handled by now" << std::endl;
							return false;
						}

						//determine color
						buw::Vector3f color = determineColorFromBaseTypes(product);
						//if (color.w() <= FullyTransparentAlphaThreshold) {
						//	return false; //skip fully transparent vertices
						//}

						// obtain vertices from face
						std::vector<buw::Vector3f> faceVertices;
						faceVertices.resize(numVertices);
						carve::mesh::Edge<3>* edge = face->edge;

						for(int i = 0; i < numVertices; ++i) {
							faceVertices[i] = buw::Vector3f(edge->v1()->v.x,
								edge->v1()->v.y,
								edge->v1()->v.z);
							edge = edge->next;
						}

						buw::Vector3f normal(face->plane.N.x, face->plane.N.y, face->plane.N.z);

						if(numVertices == 3) {
							VertexLayout v0, v1, v2;

							v0 = VertexLayout(faceVertices[0], color, normal);
							v1 = VertexLayout(faceVertices[1], color, normal);
							v2 = VertexLayout(faceVertices[2], color, normal);

							insertTriangleIntoBuffers(v0, v1, v2, vertices, indices);
						}

						else if(numVertices == 4) {
							VertexLayout v0, v1, v2, v3;

							v0 = VertexLayout(faceVertices[0], color, normal);
							v1 = VertexLayout(faceVertices[1], color, normal);
							v2 = VertexLayout(faceVertices[2], color, normal);
							v3 = VertexLayout(faceVertices[3], color, normal);

							insertQuadIntoBuffers(v0, v1, v2, v3, vertices, indices);
						}

						return true;//color.w() <= FullyOpaqueAlphaThreshold;
					}

					static bool insertTriangleIntoBuffers(const VertexLayout& vertexA,
						const VertexLayout& vertexB,
						const VertexLayout& vertexC,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						uint32_t indexOffset = vertices.size();

						vertices.push_back(vertexA);
						vertices.push_back(vertexB);
						vertices.push_back(vertexC);

						indices.push_back(indexOffset++);
						indices.push_back(indexOffset++);
						indices.push_back(indexOffset);

						return true;
					}

					static bool insertQuadIntoBuffers(const VertexLayout& vertexA,
						const VertexLayout& vertexB,
						const VertexLayout& vertexC,
						const VertexLayout& vertexD,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						insertTriangleIntoBuffers(vertexA, vertexB, vertexC, vertices, indices);
						insertTriangleIntoBuffers(vertexA, vertexC, vertexD, vertices, indices);

						return true;
					}

					static bool insertMeshIntoBuffers(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product,
						const carve::mesh::Mesh<3>* mesh,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						// walk through all faces of the mesh
						bool ret = false;
						for(const auto& face : mesh->faces) {
							if(face->nVertices() > 4) {
								std::cout << "Error\t| Detected face with more than 4 vertices -> "
									<< face->nVertices() << " This is not handled by now" << std::endl;
								continue;
							}

							ret |= insertFaceIntoBuffers(product, face, vertices, indices);
						}
						return ret;
					}

					static bool insertMeshSetIntoBuffers(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product,
						const carve::mesh::MeshSet<3>* meshSet,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						bool ret = false;
						if(!meshSet) {
							return ret;
						}

						// walk through all meshes of the mesh set
						for(const auto& mesh : meshSet->meshes) {
							ret |= insertMeshIntoBuffers(product, mesh, vertices, indices);
						}
						return ret;
					}

					static bool insertOpenMeshIntoBuffers(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product,
						const carve::input::PolyhedronData* polyData,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						const buw::Vector3f color(0, 1, 0);//, 1);
														   //if (color.w() <= FullyTransparentAlphaThreshold) {
														   //	return false; //skip fully transparent vertices
														   //}

						std::vector<buw::Vector3f> polyVertices;

						for(const auto& vertex : polyData->points) {
							polyVertices.push_back(buw::Vector3f(vertex.x, vertex.y, vertex.z));
						}

						int32_t indexOffset = vertices.size();

						// walk through all indices
						for(auto it = polyData->faceIndices.cbegin(); it != polyData->faceIndices.cend(); ++it) {
							const int32_t numIndices = *it;

							if(numIndices == 3) {
								VertexLayout v0, v1, v2;
								buw::Vector3f* pos0, *pos1, *pos2;

								++it;
								pos0 = &polyVertices.at(*it);
								++it;
								pos1 = &polyVertices.at(*it);
								++it;
								pos2 = &polyVertices.at(*it);

								const buw::Vector3f normal((pos2 - pos0) ^ (pos1 - pos0));

								v0 = VertexLayout::create(*pos0, color, normal);
								v1 = VertexLayout::create(*pos1, color, normal);
								v2 = VertexLayout::create(*pos2, color, normal);

								insertTriangleIntoBuffers(v0, v1, v2, vertices, indices);

							}
							else if(numIndices == 4) {
								VertexLayout v0, v1, v2, v3;
								buw::Vector3f* pos0, *pos1, *pos2, *pos3;

								++it;
								pos0 = &polyVertices.at(*it);
								++it;
								pos1 = &polyVertices.at(*it);
								++it;
								pos2 = &polyVertices.at(*it);
								++it;
								pos3 = &polyVertices.at(*it);

								const buw::Vector3f normal((pos2 - pos0) ^ (pos1 - pos0));

								v0 = VertexLayout::create(*pos0, color, normal);
								v1 = VertexLayout::create(*pos1, color, normal);
								v2 = VertexLayout::create(*pos2, color, normal);
								v3 = VertexLayout::create(*pos3, color, normal);

								insertQuadIntoBuffers(v0, v1, v2, v3, vertices, indices);
							}
							else {
								std::cout << "Error\t| Detected face with more than 4 vertices."
									<< " This is not handled by now" << std::endl;

								for(int32_t i = 0; i < numIndices; ++i) {
									++it;
								}
							}
						}
						return true; // color.w() <= FullyOpaqueAlphaThreshold;
					}

					static bool insertPolyhedronIntoBuffers(const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product,
						const carve::poly::Polyhedron* polyhedron,
						std::vector<VertexLayout>& vertices,
						std::vector<uint32_t>& indices)
					{
						return insertMeshSetIntoBuffers(product, carve::meshFromPolyhedron(polyhedron, -1), vertices, indices);
					}

					static bool insertPolylineIntoBuffers(const std::shared_ptr<carve::input::PolylineSetData> polylineData,
						std::vector<buw::Vector3f>& vertices,
						std::vector<uint32_t>& indices)
					{
						// check input
						if (polylineData->getVertexCount() < 1)
							return true; // nothing to add

						// temporary polyline vertex index to global index map
						std::map<uint32_t, uint32_t> indexMap;

						// obtain number of vertices in the polyline data
						const size_t vertexCount = polylineData->getVertexCount();
						size_t indexOffset = vertices.size();

						// create vertex buffer for polylines
						for(auto i = 0; i < vertexCount; ++i) {
							carve::geom3d::Vector position = polylineData->getVertex(i);
							buw::Vector3f vertex(position[0], position[1], position[2]);

							/*const std::string vKey = createVertexKeyLine(vertex);

							if (ConverterBuwUtil::vertexMapLines_.find(vKey) == ConverterBuwUtil::vertexMapLines_.end())
							{
							vertices.push_back(vertex);
							ConverterBuwUtil::vertexMapLines_.insert(std::pair<std::string, uint32_t>(vKey, indexOffset));
							indexMap[i] = indexOffset++;
							}
							else
							{
							indexMap[i] = ConverterBuwUtil::vertexMapLines_[vKey];
							}*/

							vertices.push_back(vertex);
							indexMap[i] = indexOffset++;
						}

						// create index buffer for line lists
						for(const auto& line : polylineData->polylines) {
							std::vector<int> pointIndexList = line.second;

							for(auto i = 0; i < pointIndexList.size() - 1; ++i) {
								auto index = indexMap[pointIndexList[i]];
								auto indexNext = indexMap[pointIndexList[i + 1]];

								indices.push_back(index);
								indices.push_back(indexNext);
							}
						}

						return true;
					}

					// convert mesh and polyline descriptions to triangles/lines for BlueFramework
					static void createTrianglesJob(const std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& tasks,
						int threadID, buw::ReferenceCounted<IfcModel>& ifcModel)
					{
						for(const auto& shapeData : tasks) {
							const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product = shapeData->getProduct();
							//					std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: Create triangles and polylines for entity " << product->classname() << " #" << product->getId() << std::endl;

							std::shared_ptr<GeometryDescription> geometry = std::make_shared<GeometryDescription>();
							geometry->reset();

							for(const auto& itemData : shapeData->getData()) {
								// data for triangles
								for(const auto& meshset : itemData->meshsets) {
									ConverterBuwT<IfcEntityTypesT>::insertMeshSetIntoBuffers(product, meshset.get(),
										geometry->meshDescription.vertices, geometry->meshDescription.indices);
								}

								// data for polylines
								for(const auto& polyline : itemData->polylines) {
									ConverterBuwT<IfcEntityTypesT>::insertPolylineIntoBuffers(polyline,
										geometry->polylineDescription.vertices, geometry->polylineDescription.indices);
								}
							}
							
							// if no geometry for this product
							if (geometry->isEmpty())
								continue;

							// update the BBox
							for (const auto& itemData : shapeData->getData()) {
								for (const auto& meshset : itemData->meshsets) {
									geometry->UpdateBBox(meshset->getAABB());
								}
								for (const auto& polyline : itemData->polylines) {
									for (const auto& pt : polyline->points)
										geometry->UpdateBBox(pt);
								}
							}
							// add to the model
							ifcModel->addGeometry(geometry);
						}
					}

				protected:

					static buw::Vector3f determineColorFromBaseTypes(
						const oip::EXPRESSReference<typename IfcEntityTypesT::IfcProduct>& product)
					{
						if(product.template isOfType<typename IfcEntityTypesT::IfcWindow>()) {
							return buw::Vector3f(0.1f, 0.6f, 1.0f);//, 0.4f);
						}

						// Balken
						else if(product.template isOfType<typename IfcEntityTypesT::IfcBeam>()
							|| product.template isOfType<typename IfcEntityTypesT::IfcColumn>()) {
							return buw::Vector3f(0.4f, 0.4f, 0.4f);//, 1.0f);
						}

						// ignore spaces!
						else if(product.template isOfType<typename IfcEntityTypesT::IfcSpace>()) {
							return buw::Vector3f(0.1f, 0.2f, 1.0f);//, 1.0f);
						}

						#if defined(OIP_MODULE_EARLYBINDING_IFC4X3_RC1)
						else if (product.template isOfType<typename IfcEntityTypesT::IfcGeotechnicalElement>()
							||   product.template isOfType<typename IfcEntityTypesT::IfcGeographicElement>()) {
							return buw::Vector3f(0.3f, 1.0f, 0.0f);//, 0.4f);
						} 
						#endif //OIP_MODULE_EARLYBINDING_IFC4X3_RC1

						else if(product.template isOfType<typename IfcEntityTypesT::IfcDoor>()) {
							return buw::Vector3f(0.8f, 0.6f, 0.2f);//, 0.5f);
						}

						else if(product.template isOfType<typename IfcEntityTypesT::IfcRoof>()) {
							return buw::Vector3f(0.6f, 0.15f, 0.15f);//, 1.0f);
						}

						else if(product.template isOfType<typename IfcEntityTypesT::IfcStair>()
							|| product.template isOfType<typename IfcEntityTypesT::IfcStairFlight>()) {
							return buw::Vector3f(0.8f, 0.4f, 0.4f);//, 1.0f);
						}

						else if(product.template isOfType<typename IfcEntityTypesT::IfcRamp>()
							|| product.template isOfType<typename IfcEntityTypesT::IfcRampFlight>()) {
							return buw::Vector3f(0.6f, 0.6f, 0.4f);//, 1.0f);
						}

						// Gelaender
						else if(product.template isOfType<typename IfcEntityTypesT::IfcRailing>()) {
							return buw::Vector3f(0.7f, 0.7f, 0.2f);//, 1.0f);
						}

						// Pile
						else if(product.template isOfType<typename IfcEntityTypesT::IfcPile>()) {
							return buw::Vector3f(0.15f, 0.7f, 0.0f);//, 1.0f);
						}

						// Moebel
						else if(product.template isOfType<typename IfcEntityTypesT::IfcFurnishingElement>()) {
							return buw::Vector3f(0.8f, 0.6f, 0.2f);//, 1.0f);
						}
						// Land
						else if(product.template isOfType<typename IfcEntityTypesT::IfcSite>()) {
							return buw::Vector3f(0.1f, 0.5f, 0.1f);//, 1.0f);
						}
						// Wasser/Gas Elemente
						else if(product.template isOfType<typename IfcEntityTypesT::IfcFlowTerminal>()
							|| product.template isOfType<typename IfcEntityTypesT::IfcDistributionFlowElement>()) {
							return buw::Vector3f(0.4f, 0.4f, 0.6f);//, 1.0f);
						}
						// Platte als Dach oder Gelaender?
						else if(product.template isOfType<typename IfcEntityTypesT::IfcSlab>()) {
							const oip::EXPRESSReference<typename IfcEntityTypesT::IfcSlab>& slab =
								product.template as<typename IfcEntityTypesT::IfcSlab>();

							if(slab->PredefinedType) {
								// Dach
								if(slab->PredefinedType == IfcEntityTypesT::IfcSlabTypeEnum::ENUM::ENUM_ROOF) {
									return buw::Vector3f(0.6f, 0.15f, 0.15f);//, 1.0f);
								}

								// Treppenabsatz
								else if(slab->PredefinedType == IfcEntityTypesT::IfcSlabTypeEnum::ENUM::ENUM_LANDING) {
									return buw::Vector3f(0.8f, 0.4f, 0.4f);//, 1.0f);
								}

								else if(slab->PredefinedType == IfcEntityTypesT::IfcSlabTypeEnum::ENUM::ENUM_FLOOR ||
									slab->PredefinedType == IfcEntityTypesT::IfcSlabTypeEnum::ENUM::ENUM_BASESLAB ||
									slab->PredefinedType == IfcEntityTypesT::IfcSlabTypeEnum::ENUM::ENUM_NOTDEFINED) {
									return buw::Vector3f(1.0f, 0.95f, 0.9f);//, 1.0f);
								}
							}
						}

						return buw::Vector3f(1, 1, 1);//, 1);
					}

					inline static std::string createVertexKeyTriangle(const VertexLayout& v)
					{
						return std::to_string(v.position[0]) + " " + std::to_string(v.position[1]) + " " + std::to_string(v.position[2]) + " "
							+ std::to_string(v.normal[0]) + " " + std::to_string(v.normal[1]) + " " + std::to_string(v.normal[2]);
					};

					inline static std::string createVertexKeyLine(const buw::Vector3f& v)
					{
						return std::to_string(v.x()) + " " + std::to_string(v.y()) + " " + std::to_string(v.z());
					};

			};

OIP_NAMESPACE_OPENINFRAPLATFORM_CORE_IFCGEOMETRYCONVERTER_END

EMBED_CORE_IFCGEOMETRYCONVERTER_INTO_OIP_NAMESPACE(ConverterBuwT)

#endif
