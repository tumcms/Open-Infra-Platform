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

#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/UIElementsEffect.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

void UIElements::v_render() {
	setPipelineState(pipelineState_);
	setRenderTarget(renderSystem()->getBackBufferTarget(), depthStencil_);
	setViewport(viewport_);

	setConstantBuffer(worldBuffer_, "WorldBuffer");
	setConstantBuffer(viewportBuffer_, "ViewportBuffer");

	setVertexBuffer(vertexCacheLine_->vertexBuffer());
	draw(vertexCacheLine_->getSize());
}

void UIElements::v_init() {
	try {
		int width = renderSystem()->getBackBufferTarget()->width();
		int height = renderSystem()->getBackBufferTarget()->height();

		buw::viewportDescription vpd(std::min(width, 130), std::min(height, 130), std::max(width - 130, 0));
		viewport_ = renderSystem()->createViewport(vpd);

		buw::constantBufferDescription cbd2;
		cbd2.sizeInBytes = sizeof(ViewportBuffer);
		cbd2.data = nullptr;
		viewportBuffer_ = renderSystem()->createConstantBuffer(cbd2);

		vertexCacheLine_ = buw::makeReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color3Size1>>(renderSystem());

		float size = 1;
		buw::VertexPosition3Color3Size1 points[6] = {{buw::Vector3f(-size, 0, 0), buw::Vector3f(1, 0, 0), 1}, {buw::Vector3f(size, 0, 0), buw::Vector3f(1, 0, 0), 1},
		                                             {buw::Vector3f(0, -size, 0), buw::Vector3f(0, 1, 0), 1}, {buw::Vector3f(0, size, 0), buw::Vector3f(0, 1, 0), 1},
		                                             {buw::Vector3f(0, 0, -size), buw::Vector3f(0, 0, 1), 1}, {buw::Vector3f(0, 0, size), buw::Vector3f(0, 0, 1), 1}};

		vertexCacheLine_->drawLine(points[0], points[1]);
		vertexCacheLine_->drawLine(points[2], points[3]);
		vertexCacheLine_->drawLine(points[4], points[5]);

		vertexCacheLine_->flush();

		loadShader();

		BLUE_LOG(trace) << "UIElements v_init end.";
	} catch (...) {
		pipelineState_ = nullptr;
		BLUE_LOG(trace) << "Creating uielements effect pipeline state failed.";
	}
}

void UIElements::resize(const buw::viewportDescription& vpd) {
	int size = 130;
	viewport_->resize(buw::viewportDescription(std::min((int)vpd.width, size), std::min((int)vpd.height, size), 0, std::max((int)vpd.height - size, 0)));

	ViewportBuffer buffer = {size, size};

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(ViewportBuffer);
	cbd.data = &buffer;
	viewportBuffer_->uploadData(cbd);
}

void UIElements::loadShader() {
	buw::pipelineStateDescription psd;
	psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/UIElementsEffect.be";
	psd.pipelineStateName = "";
	psd.vertexLayout = vertexCacheLine_->vertexLayout();
	psd.primitiveTopology = vertexCacheLine_->topology();
	psd.renderTargetFormats = {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB};
	psd.useDepth = true;
	psd.useMSAA = true;

	BLUE_LOG(trace) << "Before createPipelineState.";
	pipelineState_ = createPipelineState(psd);
}

UIElements::UIElements(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::ITexture2D> depthStencil, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    : Effect(renderSystem), depthStencil_(depthStencil), worldBuffer_(worldBuffer) {
	viewport_ = nullptr;
	viewportBuffer_ = nullptr;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
