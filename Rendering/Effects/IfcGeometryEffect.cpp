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

#include "IfcGeometryEffect.h"

#include <Resources/RenderResources.h>
#include <BlueFramework/Rasterizer/vertex.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN


IfcGeometryEffect::IfcGeometryEffect(buw::IRenderSystem * renderSystem,
                                     buw::ReferenceCounted<buw::IViewport> viewport,
                                     buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
                                     buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    :
    EffectBase(renderSystem),
    viewport_(viewport),
    depthStencilMSAA_(depthStencilMSAA),
    worldBuffer_(worldBuffer)
{
}

IfcGeometryEffect::~IfcGeometryEffect() {
    meshPipelineState_ = nullptr;
    polylinePipelineState_ = nullptr;
    meshVertexBuffer_ = nullptr;
    meshIndexBuffer_ = nullptr;
    polylineVertexBuffer_ = nullptr;
    polylineIndexBuffer_ = nullptr;
    worldBuffer_ = nullptr;
    viewport_ = nullptr;
    depthStencilMSAA_ = nullptr;
}

void IfcGeometryEffect::setIfcGeometryModel(buw::ReferenceCounted<Core::IfcGeometryConverter::IfcModel> ifcGeometryModel)
{
	ifcGeometryModel_ = ifcGeometryModel;
}

void IfcGeometryEffect::changeOffset( const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew )
{
	if (!ifcGeometryModel_)
		return;

    if(!ifcGeometryModel_->isEmpty()) {

		// reset
		if( meshVertexBuffer_ ) meshVertexBuffer_ = nullptr;
		if( meshIndexBuffer_)	meshIndexBuffer_ = nullptr;
		if( polylineVertexBuffer_)	polylineVertexBuffer_ = nullptr;
		if( polylineIndexBuffer_)	polylineIndexBuffer_ = nullptr;
		
		// tmp containers
		std::vector< VertexLayout > verticesMesh;
		std::vector< uint32_t > indicesMesh;
		std::vector< buw::Vector3f > verticesPoly;
		std::vector< uint32_t > indicesPoly;

		// process the data
		for( auto &geom : ifcGeometryModel_->geometries() )
		{
			if(!geom->meshDescription.isEmpty()) {

				std::vector< VertexLayout> vertices;
				vertices.reserve(geom->meshDescription.vertices.size());
				for (auto& vertex : geom->meshDescription.vertices)
				{
					VertexLayout vtx(vertex);
					vtx.position[0] += offsetNew.x();
					vtx.position[1] += offsetNew.y();
					vtx.position[2] += offsetNew.z();
					vertices.push_back( vtx );
				}

				const uint32_t verticesOffset = verticesMesh.size();
				verticesMesh.insert(verticesMesh.end(), vertices.begin(), vertices.end());

				const uint32_t indicesOffset = indicesMesh.size();
				indicesMesh.insert(indicesMesh.end(), geom->meshDescription.indices.begin(), geom->meshDescription.indices.end());
				std::for_each(indicesMesh.begin() + indicesOffset, indicesMesh.end(), [&verticesOffset](uint32_t& index) { index += verticesOffset; });
			}

			if(!geom->polylineDescription.isEmpty()) {

				std::vector< buw::Vector3f > vertices;
				vertices.reserve(geom->polylineDescription.vertices.size());
				for (auto& vertex : geom->polylineDescription.vertices)
				{
					vertices.push_back(vertex + offsetNew.cast<float>());
				}

				const uint32_t verticesOffset = verticesPoly.size();
				verticesPoly.insert(verticesPoly.end(), vertices.begin(), vertices.end());

				const uint32_t indicesOffset = indicesPoly.size();
				indicesPoly.insert(indicesPoly.end(), geom->polylineDescription.indices.begin(), geom->polylineDescription.indices.end());
				std::for_each(indicesPoly.begin() + indicesOffset, indicesPoly.end(), [&verticesOffset](uint32_t& index) { index += verticesOffset; });
			}
		}

		// upload data
		if( !verticesMesh.empty() )
		{
			// the descriptions
			buw::vertexBufferDescription vbdMesh;
			buw::indexBufferDescription ibdMesh;

			vbdMesh.data = verticesMesh.data();
			vbdMesh.vertexCount = verticesMesh.size();
			vbdMesh.vertexLayout = buw::VertexPosition3Color3Normal3::getVertexLayout();
			meshVertexBuffer_ = renderSystem()->createVertexBuffer(vbdMesh);

			BLUE_LOG(trace) << "Done creating IFC geometry meshes vertex buffer. Size:" << QString::number(verticesMesh.size()).toStdString();

			ibdMesh.data = &indicesMesh[0];
			ibdMesh.indexCount = indicesMesh.size();
			ibdMesh.format = buw::eIndexBufferFormat::UnsignedInt32;
			meshIndexBuffer_ = renderSystem()->createIndexBuffer(ibdMesh);
		}
		if (!verticesPoly.empty())
		{
			// the descriptions
			buw::vertexBufferDescription vbdPoly;
			buw::indexBufferDescription  ibdPoly;

			vbdPoly.data = verticesPoly.data();
			vbdPoly.vertexCount = verticesPoly.size();
			vbdPoly.vertexLayout = buw::VertexPosition3::getVertexLayout();
			polylineVertexBuffer_ = renderSystem()->createVertexBuffer(vbdPoly);

			BLUE_LOG(trace) << "Done creating IFC geometry polyline vertex buffer. Size:" << QString::number(verticesPoly.size()).toStdString();

			ibdPoly.data = &indicesPoly[0];
			ibdPoly.indexCount = indicesPoly.size();
			ibdPoly.format = buw::eIndexBufferFormat::UnsignedInt32;
			polylineIndexBuffer_ = renderSystem()->createIndexBuffer(ibdPoly);

		}

		valid_ = true;
    }
    else {
        valid_ = false;
    }
}

void IfcGeometryEffect::v_init()
{
    try {
        buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/IfcGeometryEffect.be";
		psd.pipelineStateName = "mesh";
        psd.vertexLayout = buw::VertexPosition3Color3Normal3::getVertexLayout();
        psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
        psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
        psd.useDepth = true;
        psd.useMSAA = true;

        meshPipelineState_ = createPipelineState(psd);

		psd.pipelineStateName = "polyline";
        psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
        psd.primitiveTopology = buw::ePrimitiveTopology::LineList;

        polylinePipelineState_ = createPipelineState(psd);
    }
    catch(...) {
        meshPipelineState_ = nullptr;
        polylinePipelineState_ = nullptr;
        meshVertexBuffer_ = nullptr;
        meshIndexBuffer_ = nullptr;
        polylineVertexBuffer_ = nullptr;
        polylineIndexBuffer_ = nullptr;       
    }
}

void IfcGeometryEffect::v_render()
{
	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
	setRenderTarget(renderTarget, depthStencilMSAA_);
	setViewport(viewport_);

    if(meshPipelineState_ && meshVertexBuffer_ && meshIndexBuffer_ && valid_) {
        setPipelineState(meshPipelineState_);
        setConstantBuffer(worldBuffer_, "WorldBuffer");
        setVertexBuffer(meshVertexBuffer_);
        setIndexBuffer(meshIndexBuffer_);
        drawIndexed(static_cast<UINT>(meshIndexBuffer_->getIndexCount()));
    }
    if(polylinePipelineState_ && polylineVertexBuffer_&& polylineIndexBuffer_ && valid_) {
        setPipelineState(polylinePipelineState_);
        setConstantBuffer(worldBuffer_, "WorldBuffer");
        setVertexBuffer(polylineVertexBuffer_);
        setIndexBuffer(polylineIndexBuffer_);
        drawIndexed(static_cast<UINT>(polylineIndexBuffer_->getIndexCount()));
    }
}

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END
