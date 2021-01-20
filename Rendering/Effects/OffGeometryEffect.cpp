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

#include "OffGeometryEffect.h"


#include "../Resources/RenderResources.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>

#include <tuple>


OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN


OffGeometryEffect::OffGeometryEffect(buw::IRenderSystem * renderSystem, 
									 buw::ReferenceCounted<buw::IViewport> viewport, 
									 buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA, 
									 buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
	: 
	EffectBase(renderSystem), 
	viewport_(viewport), 
	worldBuffer_(worldBuffer), 
	depthStencilMSAA_(depthStencilMSAA)
{
}

OffGeometryEffect::~OffGeometryEffect()
{
	worldBuffer_ = nullptr;
	vertexBuffer_ = nullptr;
	indexBuffer_ = nullptr;
	depthStencilMSAA_ = nullptr;
	pipelineState_ = nullptr;
	viewport_ = nullptr;
}

void OffGeometryEffect::setOffModel(buw::ReferenceCounted<Core::OffConverter::OffModel> offModel)
{
	offModel_ = offModel;
}

void OffGeometryEffect::changeOffset(const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew)
{
	if (!offModel_->isEmpty()) {

		//reset 
		if (vertexBuffer_) vertexBuffer_.reset();
		if (indexBuffer_) indexBuffer_.reset();

		//tmp containers
		std::vector<buw::Vector3d> verticesMesh;
		std::vector<uint32_t> indicesMesh;

		//process the data
		if (!offModel_->geometry().isEmpty())
		{
			std::vector<buw::Vector3d> vertices;
			vertices.reserve(offModel_->geometry().vertices.size());
			std::transform(offModel_->geometry().vertices.begin(),
				offModel_->geometry().vertices.end(),
				vertices.begin(),
				[offsetNew](buw::Vector3d a) {return a + offsetNew; });
		}

		//upload data 
		if (!verticesMesh.empty())
		{
			//descriptions
			buw::vertexBufferDescription vbd;
			buw::indexBufferDescription ibd;

			vbd.data = verticesMesh.data();
			vbd.vertexCount = verticesMesh.size();
			vbd.vertexLayout = buw::VertexPosition3::getVertexLayout();
			vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);

			BLUE_LOG(trace) << "Done creating OFF geometry vertex buffer. Size:" << QString::number(verticesMesh.size()).toStdString();

			ibd.data = &indicesMesh[0];
			ibd.indexCount = indicesMesh.size();
			ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
			indexBuffer_ = renderSystem()->createIndexBuffer(ibd);
		}
	}
	else {
		throw std::exception("The given OFFModel is empty!");
	}

}

void OffGeometryEffect::v_init()
{
	try {
		/*Create the pipeline state.*/
		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/OffGeometryEffect.be";
		psd.pipelineStateName = "main";
		psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
		psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;
		pipelineState_ = createPipelineState(psd);
	}
	catch (...) {
		pipelineState_ = nullptr;
		vertexBuffer_ = nullptr;
		indexBuffer_ = nullptr;
	}
}

void OffGeometryEffect::v_render()
{
	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();

	if (pipelineState_ && vertexBuffer_ && indexBuffer_)
	{
		setPipelineState(pipelineState_);
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setViewport(viewport_);
		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setVertexBuffer(vertexBuffer_);
		setIndexBuffer(indexBuffer_);
		drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END