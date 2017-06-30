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

// visual studio
#pragma once
// unix
#ifndef CONVERTERBUW_H
#define CONVERTERBUW_H

#include <unordered_map>
#include <thread>
#include <mutex>

//#include <buw.BlueEngine.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include "CarveHeaders.h"
#include "GeometryInputData.h"

/***********************************************************************************************/

typedef buw::VertexPosition3Color3Normal3 VertexLayout;
typedef std::unordered_map<std::string, uint32_t> VertexMapTriangles;
typedef std::unordered_map<std::string, uint32_t> VertexMapLines;

namespace OpenInfraPlatform
{
	namespace IfcGeometryConverter
	{
		struct IndexedMeshDescription
		{
			std::vector<uint32_t>		indices;
			std::vector<VertexLayout>	vertices;
            bool isEmpty() { return (indices.size() == 0 && vertices.size() == 0); };
		};

		struct PolylineDescription
		{
			std::vector<uint32_t>		indices;
			std::vector<buw::Vector3f>	vertices;
            bool isEmpty() { return (indices.size() == 0 && vertices.size() == 0); };
		};

		struct IfcGeometryModel
		{
			IndexedMeshDescription meshDescription_;
			PolylineDescription    polylineDescription_;
            bool isEmpty() { return (meshDescription_.isEmpty() && polylineDescription_.isEmpty()); };
		};


		class ConverterBuwUtil
		{
		public:
			ConverterBuwUtil() {}
			~ConverterBuwUtil() {}

			// static caches for vertices (for triangle and line geometry)
			//static VertexMapTriangles vertexMapTriangles_;
			//static VertexMapLines vertexMapLines_;
			static std::mutex s_geometryMutex;
		};

		template <
			class IfcEntityTypesT
		>
		class ConverterBuwT
		{	
		public:
			//static const float FullyOpaqueAlphaThreshold;
			//static const float FullyTransparentAlphaThreshold;

			ConverterBuwT() {}

			virtual ~ConverterBuwT() {}

			static bool insertFaceIntoBuffers(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				const carve::mesh::Face<3>* face,
				std::vector<VertexLayout>& vertices,
				std::vector<uint32_t>& indices)
			{
				const int32_t numVertices = face->nVertices();

				if (numVertices > 4)
				{
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

				for (int i = 0; i < numVertices; ++i)
				{
					faceVertices[i] = buw::Vector3f(edge->v1()->v.x,
						edge->v1()->v.y,
						edge->v1()->v.z);
					edge = edge->next;
				}

				buw::Vector3f normal(face->plane.N.x, face->plane.N.y, face->plane.N.z);

				// omit spaces
				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcSpace>(product))
				{
					return false;//color.w() <= FullyOpaqueAlphaThreshold;
				}

				if (numVertices == 3)
				{
					VertexLayout v0, v1, v2;

					v0 = VertexLayout(faceVertices[0], color, normal);
					v1 = VertexLayout(faceVertices[1], color, normal);
					v2 = VertexLayout(faceVertices[2], color, normal);

					insertTriangleIntoBuffers(v0, v1, v2, vertices, indices);
				}

				else if (numVertices == 4)
				{
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

			static bool insertMeshIntoBuffers(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				const carve::mesh::Mesh<3>* mesh,
				std::vector<VertexLayout>& vertices,
				std::vector<uint32_t>& indices)
			{
				// walk through all faces of the mesh
				bool ret = false;
				for (const auto& face : mesh->faces)
				{
					if (face->nVertices() > 4)
					{
						std::cout << "Error\t| Detected face with more than 4 vertices -> "
							<< face->nVertices() << " This is not handled by now" << std::endl;
						continue;
					}

					ret |= insertFaceIntoBuffers(product, face, vertices, indices);
				}
				return ret;
			}

			static bool insertMeshSetIntoBuffers(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				const carve::mesh::MeshSet<3>* meshSet,
				std::vector<VertexLayout>& vertices,
				std::vector<uint32_t>& indices)
			{
				bool ret = false;
				if (!meshSet)
				{
					return ret;
				}

				// walk through all meshes of the mesh set
				for (const auto& mesh : meshSet->meshes)
				{
					ret |= insertMeshIntoBuffers(product, mesh, vertices, indices);
				}
				return ret;
			}

			static bool insertOpenMeshIntoBuffers(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				const carve::input::PolyhedronData* polyData,
				std::vector<VertexLayout>& vertices,
				std::vector<uint32_t>& indices)
			{
				const buw::Vector3f color(0, 1, 0);//, 1);
				//if (color.w() <= FullyTransparentAlphaThreshold) {
				//	return false; //skip fully transparent vertices
				//}

				std::vector<buw::Vector3f> polyVertices;

				for (const auto& vertex : polyData->points)
				{
					polyVertices.push_back(buw::Vector3f(vertex.x, vertex.y, vertex.z));
				}

				int32_t indexOffset = vertices.size();

				// walk through all indices
				for (auto it = polyData->faceIndices.cbegin(); it != polyData->faceIndices.cend(); ++it)
				{
					const int32_t numIndices = *it;

					if (numIndices == 3)
					{
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
					else if (numIndices == 4)
					{
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
					else
					{
						std::cout << "Error\t| Detected face with more than 4 vertices."
							<< " This is not handled by now" << std::endl;

						for (int32_t i = 0; i < numIndices; ++i)
						{
							++it;
						}
					}
				}
				return true; // color.w() <= FullyOpaqueAlphaThreshold;
			}

			static bool insertPolyhedronIntoBuffers(const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product,
				const carve::poly::Polyhedron* polyhedron,
				std::vector<VertexLayout>& vertices,
				std::vector<uint32_t>& indices)
			{
				std::shared_ptr<carve::mesh::MeshSet<3>> meshSet(carve::meshFromPolyhedron(polyhedron, -1));
				bool ret = false;
				for (const auto& mesh : meshSet->meshes)
				{
					ret |= insertMeshIntoBuffers(product, mesh, vertices, indices);
				}
				return ret;
			}

			static bool insertPolylineIntoBuffers(const std::shared_ptr<carve::input::PolylineSetData> polylineData,
				std::vector<buw::Vector3f>& vertices,
				std::vector<uint32_t>& indices)
			{
				// global offset of inserted vertices
				const uint32_t vertexOffset = vertices.size();

				// temporary polyline vertex index to global index map
				std::map<uint32_t, uint32_t> indexMap;
				
				// obtain number of vertices in the polyline data
				const size_t vertexCount = polylineData->getVertexCount();
				size_t indexOffset = vertices.size();

				// create vertex buffer for polylines
				for (auto i = 0; i < vertexCount; ++i)
				{
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
				for (const auto& line : polylineData->polylines)
				{
					std::vector<int> pointIndexList = line.second;

					for (auto i = 0; i < pointIndexList.size() - 1; ++i)
					{
						auto index = indexMap[pointIndexList[i]];
						auto indexNext = indexMap[pointIndexList[i + 1]];

						indices.push_back(index);
						indices.push_back(indexNext);
					}
				}

				return true;
			}

			static bool createGeometryModel(buw::ReferenceCounted<IfcGeometryModel> ifcGeometryModel,
				std::map<int, std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& shapeDatas)
			{
				std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: Create geometry model from meshsets for BlueFramework API" << std::endl;
				//! NOTE (mk): Could be optimized if we omit cache building and just add triangles (with redundant vertices)

				// clear all descriptions
				auto& meshDescription = ifcGeometryModel->meshDescription_;
				meshDescription.vertices.clear();
				meshDescription.indices.clear();

				auto& polylineDescription = ifcGeometryModel->polylineDescription_;
				polylineDescription.vertices.clear();
				polylineDescription.indices.clear();

				// obtain maximum number of threads supported by machine
				const unsigned int maxNumThreads = std::thread::hardware_concurrency();

				// gather tasks for all threads
				std::vector<std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>> tasks(maxNumThreads);

				uint32_t counter = 0;
				for (auto it = shapeDatas.begin(); it != shapeDatas.end(); ++it)
				{
					std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>> shapeData = it->second;
					tasks[counter % maxNumThreads].push_back(shapeData);
					counter++;
				}

				// create threads and start creation job
				std::vector<std::thread> threads(maxNumThreads);
				// every thread gets its local triangle/polyline pool
				for (unsigned int k = 0; k < maxNumThreads; ++k)
				{
					threads[k] = std::thread(&ConverterBuwT<IfcEntityTypesT>::createTrianglesJob, tasks[k], k, &meshDescription, &polylineDescription);
				}

				// wait for all threads to be finished
				for (unsigned int l = 0; l < maxNumThreads; ++l)
				{
					threads[l].join();
				}

				std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: IFC model ready to be rendered" << std::endl;
				return true;
			}

			// convert mesh and polyline descriptions to triangles/lines for BlueFramework
			static void createTrianglesJob(const std::vector<std::shared_ptr<ShapeInputDataT<IfcEntityTypesT>>>& tasks, 
				int threadID, IndexedMeshDescription* meshDesc, PolylineDescription* polyDesc)
			{
//#ifdef _DEBUG
//				std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: Starting thread " << threadID << " to create triangles and polylines" << std::endl;
//#endif
				IndexedMeshDescription threadMeshDesc;
				PolylineDescription threadLineDesc;
				threadMeshDesc.vertices.clear();
				threadMeshDesc.indices.clear();
				threadLineDesc.vertices.clear();
				threadLineDesc.indices.clear();


				for (const auto& shapeData : tasks)
				{
					const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product = shapeData->ifc_product;

//#ifdef _DEBUG
//					std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: Create triangles and polylines for entity " << product->classname() << " #" << product->getId() << std::endl;
//#endif

					for (const auto& itemData : shapeData->vec_item_data)
					{
						// data for triangles
						for (const auto& meshset : itemData->meshsets)
						{
							ConverterBuwT<IfcEntityTypesT>::insertMeshSetIntoBuffers(product, meshset.get(),
								threadMeshDesc.vertices, threadMeshDesc.indices);
						}

						// data for polylines
						for (const auto& polyline : itemData->polylines)
						{
							ConverterBuwT<IfcEntityTypesT>::insertPolylineIntoBuffers(polyline,
								threadLineDesc.vertices, threadLineDesc.indices);
						}
					}
				}

				ConverterBuwUtil::s_geometryMutex.lock();

				const uint64_t globalIndexOffsetMesh = meshDesc->vertices.size();
				const uint64_t globalIndexOffsetLines = polyDesc->vertices.size();

				std::for_each(threadMeshDesc.indices.begin(), threadMeshDesc.indices.end(),
					[&](uint32_t& index) { index += globalIndexOffsetMesh; });
				std::for_each(threadLineDesc.indices.begin(), threadLineDesc.indices.end(),
					[&](uint32_t& index) { index += globalIndexOffsetLines; });

				meshDesc->vertices.insert(meshDesc->vertices.end(), threadMeshDesc.vertices.begin(), threadMeshDesc.vertices.end());
				meshDesc->indices.insert(meshDesc->indices.end(), threadMeshDesc.indices.begin(), threadMeshDesc.indices.end());
				polyDesc->vertices.insert(polyDesc->vertices.end(), threadLineDesc.vertices.begin(), threadLineDesc.vertices.end());
				polyDesc->indices.insert(polyDesc->indices.end(), threadLineDesc.indices.begin(), threadLineDesc.indices.end());
				
				ConverterBuwUtil::s_geometryMutex.unlock();
//#ifdef _DEBUG
//				std::cout << "Info\t| IfcGeometryConverter.ConverterBuw: Finished thread " << threadID << std::endl;
//#endif
			}

		protected:

			static buw::Vector3f determineColorFromBaseTypes(
				const std::shared_ptr<typename IfcEntityTypesT::IfcProduct>& product)
			{
				if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcWindow>(product))
				{
					return buw::Vector3f(0.1f, 0.6f, 1.0f);//, 0.4f);
				}

				// Balken
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcBeam>(product)
					|| dynamic_pointer_cast<typename IfcEntityTypesT::IfcColumn>(product))
				{
					return buw::Vector3f(0.4f, 0.4f, 0.4f);//, 1.0f);
				}

				// ignore spaces!
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcSpace>(product))
				{
					return buw::Vector3f(0.1f, 0.2f, 1.0f);//, 1.0f);
				}

				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcDoor>(product))
				{
					return buw::Vector3f(0.8f, 0.6f, 0.2f);//, 0.5f);
				}

				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcRoof>(product))
				{
					return buw::Vector3f(0.6f, 0.15f, 0.15f);//, 1.0f);
				}

				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcStair>(product)
					|| dynamic_pointer_cast<typename IfcEntityTypesT::IfcStairFlight>(product))
				{
					return buw::Vector3f(0.8f, 0.4f, 0.4f);//, 1.0f);
				}

				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcRamp>(product)
					|| dynamic_pointer_cast<typename IfcEntityTypesT::IfcRampFlight>(product))
				{
					return buw::Vector3f(0.6f, 0.6f, 0.4f);//, 1.0f);
				}

				// Geländer
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcRailing>(product))
				{
					return buw::Vector3f(0.7f, 0.7f, 0.2f);//, 1.0f);
				}

				// Geländer
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcPile>(product))
				{
					return buw::Vector3f(0.15f, 0.7f, 0.0f);//, 1.0f);
				}

				// Möbel
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcFurnishingElement>(product))
				{
					return buw::Vector3f(0.8f, 0.6f, 0.2f);//, 1.0f);
				}
				// Land
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcSite>(product))
				{
					return buw::Vector3f(0.1f, 0.5f, 0.1f);//, 1.0f);
				}
				// Wasser/Gas Elemente
				else if (dynamic_pointer_cast<typename IfcEntityTypesT::IfcFlowTerminal>(product)
					|| dynamic_pointer_cast<typename IfcEntityTypesT::IfcDistributionFlowElement>(product))
				{
					return buw::Vector3f(0.4f, 0.4f, 0.6f);//, 1.0f);
				}
				// Platte als Dach oder Geländer?
				else if (std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSlab>(product))
				{
					const std::shared_ptr<typename IfcEntityTypesT::IfcSlab>& slab = 
						std::dynamic_pointer_cast<typename IfcEntityTypesT::IfcSlab>(product);

					if (slab->m_PredefinedType)
					{
						// Dach
						if (slab->m_PredefinedType->m_enum == IfcEntityTypesT::IfcSlabTypeEnum::ENUM_ROOF)
						{
							return buw::Vector3f(0.6f, 0.15f, 0.15f);//, 1.0f);
						}

						// Treppenabsatz
						else if (slab->m_PredefinedType->m_enum == IfcEntityTypesT::IfcSlabTypeEnum::ENUM_LANDING)
						{
							return buw::Vector3f(0.8f, 0.4f, 0.4f);//, 1.0f);
						}

						else if (slab->m_PredefinedType->m_enum == IfcEntityTypesT::IfcSlabTypeEnum::ENUM_FLOOR ||
							slab->m_PredefinedType->m_enum == IfcEntityTypesT::IfcSlabTypeEnum::ENUM_BASESLAB ||
							slab->m_PredefinedType->m_enum == IfcEntityTypesT::IfcSlabTypeEnum::ENUM_NOTDEFINED)
						{
							return buw::Vector3f(1.0f, 0.95f, 0.9f);//, 1.0f);
						}
					}
				}

				return buw::Vector3f(1, 1, 1);//, 1);
			}

			inline static std::string createVertexKeyTriangle(const VertexLayout& v)
			{
				return std::to_string(v.position.x()) + " " + std::to_string(v.position.y()) + " " + std::to_string(v.position.z()) + " "
					+ std::to_string(v.normal.x()) + " " + std::to_string(v.normal.y()) + " " + std::to_string(v.normal.z());
			};

			inline static std::string createVertexKeyLine(const buw::Vector3f& v)
			{
				return std::to_string(v.x()) + " " + std::to_string(v.y()) + " " + std::to_string(v.z());
			};

		};
	}
}

#endif
