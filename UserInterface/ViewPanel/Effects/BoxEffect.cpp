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

#include "BoxEffect.h"


#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>

#include <tuple>


OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN


BoxEffect::BoxEffect(buw::IRenderSystem * renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer, buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: buw::Effect(renderSystem), viewport_(viewport), worldBuffer_(worldBuffer), depthStencilMSAA_(depthStencilMSAA), viewportBuffer_(viewportBuffer)
{
}

BoxEffect::~BoxEffect()
{
	worldBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	vertexBuffer_ = nullptr;
	indexBuffer_ = nullptr;
	depthStencilMSAA_ = nullptr;
	pipelineState_ = nullptr;
	viewport_ = nullptr;
}

void BoxEffect::loadShader()
{
	try {		
		/*Create the pipeline state.*/
		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/BoxEffect.be";
		psd.pipelineStateName = "main";
		psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
		psd.primitiveTopology = buw::ePrimitiveTopology::LineList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;
		psd.fillMode = buw::eFillMode::Solid;
		psd.cullMode = buw::eCullMode::None;
		pipelineState_ = createPipelineState(psd);
	}
	catch(...) {
		pipelineState_ = nullptr;
	}
}


void BoxEffect::show(const bool checked)
{
	bShow_ = checked;
}

void BoxEffect::assignVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer)
{
	vertexBuffer_ = vertexBuffer;
}

void BoxEffect::assignIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer)
{
	indexBuffer_ = indexBuffer;
}


void BoxEffect::v_init()
{
	loadShader();	
}

void BoxEffect::v_render()
{
	if(bShow_) {
		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();

		setPipelineState(pipelineState_);
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setViewport(viewport_);
		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setConstantBuffer(viewportBuffer_, "ViewportBuffer");
		setVertexBuffer(vertexBuffer_);
		setIndexBuffer(indexBuffer_);
		drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END