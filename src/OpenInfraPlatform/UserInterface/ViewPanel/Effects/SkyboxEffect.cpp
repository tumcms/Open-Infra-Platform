/*
    Copyright (c) 2016-2017 Technical University of Munich
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

#include "SkyboxEffect.h"

#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <boost/filesystem.hpp>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

SkyboxEffect::SkyboxEffect(buw::IRenderSystem * renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer)
    :
    Effect(renderSystem),
    viewport_(viewport),
    worldBuffer_(worldBuffer)
{
}

SkyboxEffect::~SkyboxEffect() {
    sampler_ = nullptr;
    texture_ = nullptr;
    viewport_ = nullptr;
    pipelineState_ = nullptr;
    vertexBuffer_ = nullptr;
}

void SkyboxEffect::v_init() {
    std::vector<buw::VertexPosition3Normal3Texture2> vertices;
    std::vector<unsigned int> indices;

    buw::createIndexedSphere(1, 180, 45, vertices, indices);
    buw::VertexLayout vertexLayout = buw::VertexPosition3Normal3Texture2::getVertexLayout();

    buw::vertexBufferDescription vbd;
    vbd.data = &vertices[0];
    vbd.vertexCount = static_cast<int>(vertices.size());
    vbd.vertexLayout = vertexLayout;
    vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);

    buw::indexBufferDescription ibd;
    ibd.data = &indices[0];
    ibd.indexCount = indices.size();
    ibd.format = buw::eIndexBufferFormat::UnsignedInt32;

    indexBuffer_ = renderSystem()->createIndexBuffer(ibd);
    buw::pipelineStateDescription psd;
	psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/SkyboxEffect.be";
	psd.pipelineStateName = "";
    psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
    psd.vertexLayout = vertexLayout;
    psd.useDepth = false;
    psd.useMSAA = true;
    psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
    pipelineState_ = createPipelineState(psd);

    buw::samplerStateDescription ssd = { buw::eFilter::Linear };
    sampler_ = renderSystem()->createSampler(ssd);

    // load texture
    auto img0 = buw::loadImage4b("Data/sky/right.png");
    auto img1 = buw::loadImage4b("Data/sky/left.png");
    auto img2 = buw::loadImage4b("Data/sky/top.png");
    auto img3 = buw::loadImage4b("Data/sky/bottom.png");
    auto img4 = buw::loadImage4b("Data/sky/front.png");
    auto img5 = buw::loadImage4b("Data/sky/back.png");

    buw::textureCubeDescription td1;
    td1.width = img1.getWidth();
    td1.height = img1.getHeight();
    td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;

    void* imageData[6];
    imageData[0] = img0.getData();
    imageData[1] = img1.getData();
    imageData[2] = img2.getData();
    imageData[3] = img3.getData();
    imageData[4] = img4.getData();
    imageData[5] = img5.getData();

    td1.data = (const void**)&imageData[0];

    texture_ = renderSystem()->createTextureCube(td1, buw::eTextureBindType::SRV);
}

void SkyboxEffect::v_render() {
    setViewport(viewport_);

    buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
    setRenderTarget(renderTarget, nullptr);

    setPipelineState(pipelineState_);
    setSampler(sampler_, "sampler_");
    setTexture(texture_, "texDiffuseMap");
    setConstantBuffer(worldBuffer_, "WorldBuffer");

    setVertexBuffer(vertexBuffer_);
    setIndexBuffer(indexBuffer_);
    drawIndexed(indexBuffer_->getIndexCount());
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END