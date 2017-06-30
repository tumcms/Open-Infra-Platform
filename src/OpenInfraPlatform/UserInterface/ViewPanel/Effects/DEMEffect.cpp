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

#include "DEMEffect.h"

#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <buw.ImageProcessing.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

DEMEffect::DEMEffect(buw::IRenderSystem* renderSystem,
                     buw::ReferenceCounted<buw::IViewport> viewport,
                     buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
                     buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
                     buw::ReferenceCounted<buw::ITexture2D> depthStencil,
                     buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    : 
    Effect(renderSystem),
    viewport_(viewport),
    depthStencilMSAA_(depthStencilMSAA),
    pickBuffer_(pickBuffer),
    depthStencil_(depthStencil),
    worldBuffer_(worldBuffer)
{
}

void DEMEffect::setDEM(buw::ReferenceCounted<buw::DigitalElevationModel> dem, buw::Vector3d& offset) {
    settings_.maxHeight = dem->getMaximumHeight();
    settings_.minHeight = dem->getMinimumHeight();

	buw::VertexLayout vertexLayout = buw::VertexPosition3::getVertexLayout();

	std::vector<buw::VertexPosition3> vertices;
	std::vector<unsigned int> indices;
	int indexOffset = 0;

	for (const auto& surface : dem->getSurfaces()) {
		for (const auto& point : surface->getPoints()) {
			buw::Vector3f vertex = (point + offset).cast<float>();
			vertices.push_back(buw::VertexPosition3(vertex));
		}
		for (const auto& triangle : surface->getTriangeFaces()) {
			indices.push_back(indexOffset + triangle.x());
			indices.push_back(indexOffset + triangle.y());
			indices.push_back(indexOffset + triangle.z());
		}

		indexOffset += surface->getPointCount();
	}

	if (vertices.size() > 0) {
		buw::vertexBufferDescription vbd;
		vbd.data = &vertices[0];
		vbd.vertexCount = static_cast<int>(vertices.size());
		vbd.vertexLayout = vertexLayout;

		vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
	} else
		vertexBuffer_ = nullptr;

	if (indices.size() > 0) {
		buw::indexBufferDescription idb;
		idb.data = &indices[0];
		idb.indexCount = static_cast<int>(indices.size());
		idb.format = buw::eIndexBufferFormat::UnsignedInt32;

		indexBuffer_ = renderSystem()->createIndexBuffer(idb);
	} else
		indexBuffer_ = nullptr;
}

void DEMEffect::loadShader() {
	try {
		buw::VertexLayout vertexLayout = buw::VertexPosition3::getVertexLayout();

		buw::pipelineStateDescription psd;
		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/DEMEffect.be";
		psd.pipelineStateName = "default";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
		psd.renderTargetFormats = {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB};
		psd.useDepth = true;
		psd.useMSAA = true;

		psd.fillMode = buw::eFillMode::Solid;
		pipelineStateSolid_ = createPipelineState(psd);

		psd.fillMode = buw::eFillMode::Wireframe;
		pipelineStateWireframe_ = createPipelineState(psd);

		psd.pipelineStateName = "pick";
		psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
		psd.renderTargetFormats = { buw::eTextureFormat::R32_UnsignedInt };
		psd.useDepth = true;
		psd.fillMode = buw::eFillMode::Solid;
		psd.useMSAA = false;

		pipelineStatePick_ = createPipelineState(psd);

	} catch (...) {
		pipelineStateSolid_ = nullptr;
	}
}

void DEMEffect::v_init() {
	loadShader();

	// create constant buffer for shader variables
	settings_.bTerrainDisplayIsoLines = false;
	settings_.bTerrainTextured = false;
	settings_.bTerrainUseColorRamp = false;
	settings_.bSnow = false;

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(SettingsBuffer);
	cbd.data = &settings_;
	cbSettingsBuffer_ = renderSystem()->createConstantBuffer(cbd);

	// load terrain texture
	auto img1 = buw::loadImage4b("Data/terrain.jpg");

	buw::texture2DDescription td1;
	td1.width = img1.getWidth();
	td1.height = img1.getHeight();
	td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	td1.data = img1.getData();
    
	texture_ = renderSystem()->createTexture2D(td1, buw::eTextureBindType::SRV);

    auto img2 = buw::loadImage4b("Data/GradientRamp.png");

    buw::texture1DDescription td2;
    td2.width = img2.getWidth();
    td2.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
    td2.data = img2.getData();

    gradientRampTexture_ = renderSystem()->createTexture1D(td2, buw::eTextureBindType::SRV);

    buw::samplerStateDescription samplerStateDesc;
    samplerStateDesc.minificationFilter = buw::eFilter::Linear;
    samplerStateDesc.magnificationFilter = buw::eFilter::Linear;
    samplerStateDesc.mipLevelFilter = buw::eFilter::None;
    samplerStateDesc.textureAddressModeU = buw::eTextureAddressMode::Clamp;
    samplerStateDesc.textureAddressModeV = buw::eTextureAddressMode::Clamp;
    samplerStateDesc.textureAddressModeW = buw::eTextureAddressMode::Clamp;
    colorRampSampler_ = renderSystem()->createSampler(samplerStateDesc);
}

void DEMEffect::v_render() {
	if (bHideTerrain_) {
		return;
	}

	if (pipelineStateSolid_ && vertexBuffer_ && indexBuffer_) {
		updateSettingsBuffer(settings_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		
		if (bDrawTerrainWireframe_) {
			setPipelineState(pipelineStateWireframe_);
		} else {
			setPipelineState(pipelineStateSolid_);
		}

        setRenderTarget(renderTarget, depthStencilMSAA_);

        setViewport(viewport_);

		if (bTerrainTextured_ || settings_.bSnow == 1) {
			setSampler(buw::Singleton<RenderResources>::instance().getLinearSampler(), "sampler_");
			setTexture(texture_, "texDiffuseMap");
		}

        if(settings_.bTerrainUseColorRamp == true || true) {
            setSampler(colorRampSampler_, "colorRampSampler_");
            setTexture(gradientRampTexture_, "texGradientRamp");
        }
                
		setVertexBuffer(vertexBuffer_);
		setIndexBuffer(indexBuffer_);

		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setConstantBuffer(cbSettingsBuffer_, "SettingsBuffer");

		drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));

        //render to pick buffer and non multisampled depth stencil
        {
            setPipelineState(pipelineStatePick_);
            setRenderTarget(pickBuffer_, depthStencil_);
            setViewport(viewport_);

            setVertexBuffer(vertexBuffer_);
            setIndexBuffer(indexBuffer_);

            setConstantBuffer(worldBuffer_, "WorldBuffer");

            drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
        }
	}
}

void DEMEffect::updateSettingsBuffer(SettingsBuffer& buffer) {
	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(SettingsBuffer);
	cbd.data = &buffer;
	cbSettingsBuffer_->uploadData(cbd);
}

void DEMEffect::enableSnow(const bool checked) {
	settings_.bSnow = checked;

	updateSettingsBuffer(settings_);
}

void DEMEffect::enableTerrainColorRamp(const bool checked) {
	settings_.bTerrainUseColorRamp = checked;

	updateSettingsBuffer(settings_);
}

void DEMEffect::enableIsoLines(const bool checked) {
	settings_.bTerrainDisplayIsoLines = checked;

	updateSettingsBuffer(settings_);
}

void DEMEffect::enableTerrainTextured(const bool checked) {
	bTerrainTextured_ = checked;

	settings_.bTerrainTextured = checked;

	updateSettingsBuffer(settings_);
}

void DEMEffect::hideTerrain(const bool checked) {
	bHideTerrain_ = checked;
}

void DEMEffect::setDrawTerrainWireframe(const bool enable) {
	bDrawTerrainWireframe_ = enable;
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END