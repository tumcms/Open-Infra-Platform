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

#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/GradientClearEffect.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

GradientClearEffect::GradientClearEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport) : Effect(renderSystem), viewport_(viewport) {

}

void GradientClearEffect::loadShader() {
	v_init();
}

void GradientClearEffect::toggleSnow() {
	snow_ = !snow_;
}

void GradientClearEffect::v_render() {
	if (pipelineState_) {
		std::chrono::nanoseconds current = std::chrono::high_resolution_clock::now().time_since_epoch();
		ShaderVariables buffer;
		long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(current - start_).count();
		float s = ms / 1000;
		s += (float)(ms % 1000) / 1000.0f;
		buffer.time = s;
		buffer.resolution = buw::Vector2f(1.0f, 1.0f);
		buffer.mouse = buw::Vector2f(0.5f, 0.5f);
		buffer.snow = snow_;

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(ShaderVariables);
		cbd.data = &buffer;
		constantBuffer_->uploadData(cbd);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();

		setPipelineState(pipelineState_);
		setConstantBuffer(constantBuffer_, "ShaderVariables");
		setRenderTarget(renderTarget, nullptr);
		setViewport(viewport_);
		draw(4);
	}
}

void GradientClearEffect::v_init() {
	try {
		buw::VertexLayout vertexLayout = buw::VertexPosition4Texture2::getVertexLayout();

        BLUE_LOG(trace) << "Before effectFilename.";
		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/GradientClearEffect.be";
		psd.pipelineStateName = "";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::TriangleStrip;
		psd.useDepth = false;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useMSAA = true;

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(ShaderVariables);
		cbd.data = nullptr;
		constantBuffer_ = renderSystem()->createConstantBuffer(cbd);
		start_ = std::chrono::high_resolution_clock::now().time_since_epoch();

		BLUE_LOG(trace) << "Before createPipelineState.";
		pipelineState_ = createPipelineState(psd);

		BLUE_LOG(trace) << "GradientQuad v_init end.";
	}
	catch (...) {
		pipelineState_ = nullptr;
		BLUE_LOG(trace) << "Creating gradient clear effect pipeline state failed.";
	}
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END