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

#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloud.h"
#include "OpenInfraPlatform/Infrastructure/PointCloudProcessing/PointCloudSection.h"

#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <ccColorTypes.h>
#include <ccHObjectCaster.h>

#include <tuple>


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
		psd.fillMode = buw::eFillMode::Solid;
		psd.cullMode = buw::eCullMode::None;

		pipelineState_ = createPipelineState(psd);		
	}
	catch(...) {
		pipelineState_ = nullptr;
	}
}

void PointCloudEffect::drawPointsWithUniformColor(const bool checked)
{
	settings_.bUseUniformColor = checked;
	updateSettingsBuffer();
}

void PointCloudEffect::drawPointsWithUniformSize(const bool checked)
{
	settings_.bUseUniformPointSize = checked;
	updateSettingsBuffer();
}

void PointCloudEffect::show(const bool checked)
{
	bShow_ = checked;
}

void PointCloudEffect::showOriginalPointCloud(const bool checked)
{
	bShowOriginalPointCloud_ = checked;
}

void PointCloudEffect::showFilteredPointCloud(const bool checked)
{
	bShowFilteredPointCloud_ = checked;
}

void PointCloudEffect::showFilteredPoints(const bool checked)
{
	bShowFilteredPoints_ = checked;
}

void PointCloudEffect::showSegmentedPoints(const bool checked)
{
	bShowSegmentedPoints_ = checked;
}

void PointCloudEffect::setUniformColor(const buw::Vector4f & color)
{
	uniformColor_ = buw::Vector4f(color);
}

void PointCloudEffect::setFilteredColor(const buw::Vector4f & color)
{
	filteredColor_ = buw::Vector4f(color);
}

void PointCloudEffect::setSegmentedColor(const buw::Vector4f & color)
{
	segmentedColor_ = buw::Vector4f(color);
}

void PointCloudEffect::setPointSize(const float size)
{
	settings_.pointSize = size;
	updateSettingsBuffer();
}

void PointCloudEffect::setSectionLength(const float length)
{
	settings_.sectionLength = length;
	updateSettingsBuffer();
}

void PointCloudEffect::setProjectPoints(const bool checked)
{
	settings_.bProjectPoints = checked;
	updateSettingsBuffer();
}

void PointCloudEffect::setPointCloud(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::PointCloud> pointCloud, buw::Vector3d offset)
{
	buw::vertexBufferDescription vbd;
	vbd.vertexCount = pointCloud->size();
	vbd.vertexLayout = VertexTypePointCloud::getVertexLayout();
	
	std::vector<VertexTypePointCloud> vertices = std::vector<VertexTypePointCloud>(pointCloud->size());
	auto baseColor = ccColor::Rgbaf(255.0f, 255.0f, 255.0f, 255.0f);
	
#pragma omp parallel for
	for(int i = 0; i < pointCloud->size(); i++) {
		auto pos = pointCloud->getPoint(i);
		const ColorCompType* col = pointCloud->hasColors() ? pointCloud->getPointColor(i) : ccColor::FromRgbf(baseColor).rgb;
		// Swap Z and Y coordinate for rendering!
		vertices[i] = VertexTypePointCloud(buw::Vector3f(pos->x + offset.x(), pos->z + offset.z(), pos->y + offset.y()), buw::Vector4f((float)col[0], (float)col[1], (float)col[2], 255.0f)/255.0f);
	}
	
	vbd.data = vertices.data();
	vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);


	std::vector<uint32_t> remainingIndices, filteredIndices, segmentedIndices;
	std::tie(remainingIndices, filteredIndices, segmentedIndices) = pointCloud->getIndices();

	buw::indexBufferDescription ibd;
	ibd.indexCount = remainingIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = remainingIndices.data();

	indexBufferRemaining_ = renderSystem()->createIndexBuffer(ibd);

	ibd.indexCount = filteredIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = filteredIndices.data();

	indexBufferFiltered_ = renderSystem()->createIndexBuffer(ibd);

	settings_.mainAxis = buw::Vector4f(pointCloud->getMainAxis().x, pointCloud->getMainAxis().y, pointCloud->getMainAxis().z, 0.0f);
	settings_.sectionLength = (float) pointCloud->getSectionLength();	
}

void PointCloudEffect::v_init()
{
	loadShader();
	
	/*Create the settings buffer.*/
	settings_.positions[0] = buw::Vector4f(-0.5, 0.5, 0, 0);
	settings_.positions[1] = buw::Vector4f(0.5, 0.5, 0, 0);
	settings_.positions[2] = buw::Vector4f(-0.5, -0.5, 0, 0);
	settings_.positions[3] = buw::Vector4f(0.5, -0.5, 0, 0);
	settings_.color = uniformColor_;
	settings_.bUseUniformColor = false;
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
	setVertexBuffer(vertexBuffer_);

	if(bShow_) {

		settings_.color = uniformColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		if(bShowOriginalPointCloud_) {
			draw(static_cast<UINT>(vertexBuffer_->getVertexCount()));
		}
		else if(bShowFilteredPointCloud_) {
			setIndexBuffer(indexBufferRemaining_);
			drawIndexed(static_cast<UINT>(indexBufferRemaining_->getIndexCount()));
		}
	}

	if(bShowFilteredPoints_) {
		settings_.color = filteredColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		setIndexBuffer(indexBufferFiltered_);
		drawIndexed(static_cast<UINT>(indexBufferFiltered_->getIndexCount()));
	}

	if(bShowSegmentedPoints_) {
		settings_.color = segmentedColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		setIndexBuffer(indexBufferSegmented_);
		drawIndexed(static_cast<UINT>(indexBufferSegmented_->getIndexCount()));
	}
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