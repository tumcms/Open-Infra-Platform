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

#include "PointCloudEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <BlueFramework/Rasterizer/vertex.h>


OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

typedef buw::VertexPosition3Color4 VertexTypePointCloud;


PointCloudEffect::PointCloudEffect(
	buw::IRenderSystem * renderSystem,
	buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: buw::Effect(renderSystem), viewport_(viewport), worldBuffer_(worldBuffer), depthStencilMSAA_(depthStencilMSAA), viewportBuffer_(viewportBuffer)
{

}

PointCloudEffect::~PointCloudEffect()
{
	worldBuffer_ = nullptr;
	settingsBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	vertexBuffer_ = nullptr;
	depthStencilMSAA_ = nullptr;
	pipelineState_ = nullptr;
	viewport_ = nullptr;
}

void PointCloudEffect::loadShader()
{
	try {
		/*Retrieve the vertexLayout from the vertex type.*/
		auto vertexLayout = VertexTypePointCloud::getVertexLayout();

		std::string effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/PointCloudEffect.be";

		/*Create the pipeline state.*/
		buw::pipelineStateDescription psd;
		psd.effectFilename = effectFilename;
		psd.pipelineStateName = "main";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::PointList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;

		pipelineState_ = createPipelineState(psd);		
	}
	catch(...) {
		pipelineState_ = nullptr;
	}
}

void PointCloudEffect::drawPointsColored(const bool colored)
{
	settings_.bDrawColored = colored;
	updateSettingsBuffer();
}

void PointCloudEffect::setPointSize(const float size)
{
	settings_.pointSize = size;
	updateSettingsBuffer();
}

void PointCloudEffect::setPointCloud(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::PointCloud> pointCloud, buw::Vector3d offset)
{
	buw::vertexBufferDescription vbd;
	vbd.vertexCount = pointCloud->points.size();
	vbd.vertexLayout = VertexTypePointCloud::getVertexLayout();
	
	std::vector<VertexTypePointCloud> vertices = std::vector<VertexTypePointCloud>(pointCloud->points.size());

#pragma omp parallel for
	for(int i = 0; i < pointCloud->points.size(); i++) {
		auto vertex = pointCloud->points[i];
		buw::Vector3f pos = (vertex.position + offset).cast<float>();
		buw::Vector4f col = buw::Vector4f(vertex.color.x(), vertex.color.y(), vertex.color.z(), 1.0f);
		vertices[i] = VertexTypePointCloud(buw::Vector3f(pos.x(),pos.z(),pos.y()), col);
	}
	vbd.data = vertices.data();

	vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);	
}

void PointCloudEffect::v_init()
{
	loadShader();
	
	/*Create the settings buffer.*/
	settings_.positions[0] = buw::Vector4f(-0.5, 0.5, 0, 0);
	settings_.positions[1] = buw::Vector4f(0.5, 0.5, 0, 0);
	settings_.positions[2] = buw::Vector4f(-0.5, -0.5, 0, 0);
	settings_.positions[3] = buw::Vector4f(0.5, -0.5, 0, 0);
	settings_.bDrawColored = true;
	settings_.bUseUniformPointSize = false;
	settings_.pointSize = 3.0f;

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(SettingsBuffer);
	cbd.data = &settings_;

	settingsBuffer_ = renderSystem()->createConstantBuffer(cbd);
	
}

void PointCloudEffect::v_render()
{
	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
	setRenderTarget(renderTarget, depthStencilMSAA_);
	setViewport(viewport_);
	setPipelineState(pipelineState_);
	setConstantBuffer(worldBuffer_, "WorldBuffer");
	setConstantBuffer(viewportBuffer_, "ViewportBuffer");
	setConstantBuffer(settingsBuffer_, "SettingsBuffer");

	setVertexBuffer(vertexBuffer_);
	draw(static_cast<UINT>(vertexBuffer_->getVertexCount()));
}

void PointCloudEffect::updateSettingsBuffer()
{
	settings_.positions[0] = buw::Vector4f(-0.5, 0.5, 0, 0);
	settings_.positions[1] = buw::Vector4f(0.5, 0.5, 0, 0);
	settings_.positions[2] = buw::Vector4f(-0.5, -0.5, 0, 0);
	settings_.positions[3] = buw::Vector4f(0.5, -0.5, 0, 0);

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(SettingsBuffer);
	cbd.data = &settings_;

	settingsBuffer_->uploadData(cbd);
}


OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END