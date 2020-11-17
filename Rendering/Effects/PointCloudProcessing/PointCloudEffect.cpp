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

#include "PointCloud.h"
#include "PointCloudSection.h"

#include "Resources/RenderResources.h"
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>
#include <ccColorTypes.h>
#include <ccHObjectCaster.h>

#include <tuple>


OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_BEGIN

typedef buw::VertexPosition3Color4 VertexTypePointCloud;


PointCloudEffect::PointCloudEffect(
	buw::IRenderSystem * renderSystem,
	buw::ReferenceCounted<buw::IViewport> viewport,
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA,
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: EffectBase(renderSystem), viewport_(viewport), worldBuffer_(worldBuffer), depthStencilMSAA_(depthStencilMSAA), viewportBuffer_(viewportBuffer)
{
}

PointCloudEffect::~PointCloudEffect()
{
	// Clear constant buffers.
	worldBuffer_ = nullptr;
	settingsBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	viewport_ = nullptr;

	//Clear vertex buffers.
	vertexBufferPointCloud_ = nullptr;
	vertexBufferOctree_ = nullptr;

	//Clear index buffers.
	indexBufferFiltered_ = nullptr;
	indexBufferOctree_ = nullptr;
	indexBufferRemaining_ = nullptr;
	indexBufferSegmented_ = nullptr;
	
	// Clear textures.
	depthStencilMSAA_ = nullptr;

	// Clear pipeline states.
	pipelineStatePointCloud_ = nullptr;
	pipelineStateOctree_ = nullptr;
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

		pipelineStatePointCloud_ = createPipelineState(psd);	

		psd.effectFilename = buw::Singleton<RenderResources>::instance().getResourceRootDir() + "/Shader/OctreeEffect.be";
		psd.pipelineStateName = "main";
		psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
		psd.primitiveTopology = buw::ePrimitiveTopology::LineList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;

		pipelineStateOctree_ = createPipelineState(psd);
	}
	catch(...) {
		pipelineStatePointCloud_ = nullptr;
		pipelineStateOctree_ = nullptr;
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


void PointCloudEffect::showFilteredPoints(const bool checked)
{
	bShowFilteredPoints_ = checked;
}

void PointCloudEffect::showSegmentedPoints(const bool checked)
{
	bShowSegmentedPoints_ = checked;
}

void PointCloudEffect::showOctree(const bool checked)
{
	bShowOctree_ = checked;
}

void PointCloudEffect::setOctreeLevel(const size_t level)
{
	octreeLevel_ = level;
	setOctree(pointCloud_->getDGMOctree(), getOffset());
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
	bProjectPoints_ = checked;
	settings_.bProjectPoints = bProjectPoints_;
	sectionsBoundingBoxEffect_->show(checked);
	updateSettingsBuffer();
}

void PointCloudEffect::updateIndexBuffers(const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> indices)
{
	std::vector<uint32_t> remainingIndices, filteredIndices, segmentedIndices;
	std::tie(remainingIndices, filteredIndices, segmentedIndices) = indices;
	

	buw::indexBufferDescription ibd;
	ibd.indexCount = remainingIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = remainingIndices.data();

	if(ibd.indexCount > 0)
		indexBufferRemaining_ = renderSystem()->createIndexBuffer(ibd);
	else
		indexBufferRemaining_ = nullptr;

	ibd.indexCount = filteredIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = filteredIndices.data();

	if(ibd.indexCount > 0)
		indexBufferFiltered_ = renderSystem()->createIndexBuffer(ibd);
	else
		indexBufferFiltered_ = nullptr;

	ibd.indexCount = segmentedIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = segmentedIndices.data();

	if(ibd.indexCount > 0)
		indexBufferSegmented_ = renderSystem()->createIndexBuffer(ibd);
	else
		indexBufferSegmented_ = nullptr;
}

void PointCloudEffect::setPointCloud(buw::ReferenceCounted<buw::PointCloud> pointCloud)
{
	pointCloud_ = pointCloud;
}

void PointCloudEffect::changeOffset(const buw::Vector3d& offsetOld, const buw::Vector3d& offsetNew)
{
	if (!pointCloud_)
		return;

	BLUE_LOG(trace) << "Start initializing GPU side buffers.";
	
	
	// Initialize the vector to hold our data and out base color.
	std::vector<VertexTypePointCloud> vertices = std::vector<VertexTypePointCloud>(pointCloud_->size());
	auto baseColor = ccColor::Rgbaf(0, 0, 0, 0);
		

//#pragma omp parallel for shared(pointCloud, vertices)
	for(long i = 0; i < pointCloud_->size(); i++) {
		auto pos = pointCloud_->getPoint(i);
		const ColorCompType* col = pointCloud_->rgbColors() ? pointCloud_->getPointColor(i).rgb : ccColor::FromRgbf(baseColor).rgb;
		// Swap Z and Y coordinate for rendering!
		vertices[i] = VertexTypePointCloud(buw::Vector3f(pos->x + offsetNew.x(), pos->z + offsetNew.z(), pos->y + offsetNew.y()), buw::Vector4f((float)col[0], (float)col[1], (float)col[2], 255.0f) / 255.0f);
	}
	
	
	buw::vertexBufferDescription vbd;
	vbd.vertexLayout = VertexTypePointCloud::getVertexLayout(); 
	vbd.vertexCount = vertices.size();
	vbd.data = vertices.data();
	vertexBufferPointCloud_ = renderSystem()->createVertexBuffer(vbd);
	BLUE_LOG(trace) << "Done creating point cloud vertex buffer. Size:" << QString::number(vertices.size()).toStdString();


	updateIndexBuffers(pointCloud_->getIndices());
		

	settings_.mainAxis = buw::Vector4f(pointCloud_->getMainAxis().x, pointCloud_->getMainAxis().y, pointCloud_->getMainAxis().z, 0.0f);
	settings_.sectionLength = (float) pointCloud_->getSectionLength();
	
	auto octree = pointCloud_->getDGMOctree();

	if(octree)
		setOctree(octree, offsetNew);

	setSections(pointCloud_->getSections(), offsetNew);

	BLUE_LOG(trace) << "Finished initializing GPU side buffers.";
}

void PointCloudEffect::setOctree(buw::ReferenceCounted<buw::Octree> octree, buw::Vector3d offset)
{
	// Create the octree vertex and index buffer.
	BLUE_LOG(trace) << "Start creating octree buffers.";

	std::vector<uint32_t> dgmOctreeCells;
	std::vector<buw::VertexPosition3> octreeVertices = std::vector<buw::VertexPosition3>();
	std::vector<uint32_t> octreeIndices = std::vector<uint32_t>();
	bool success = octree->getCellIndexes(octreeLevel_, dgmOctreeCells);

	for(long idx = 0; idx < dgmOctreeCells.size(); idx++) {
		auto cell = dgmOctreeCells[idx];
		auto code = octree->getCellCode(cell);

		//  Compute the cell position and center.
		Tuple3i cellpos;
		CCVector3 cellCenter;
		octree->getCellPos(code, octreeLevel_, cellpos, false);
		octree->computeCellCenter(cellpos, octreeLevel_, cellCenter);

		float cellSize = octree->getCellSize(octreeLevel_);
		buw::createBoundingBox(octreeVertices, octreeIndices, cellCenter.x + offset.x(), cellCenter.y + offset.y(), cellCenter.z + offset.z(), cellSize / 2.0f, cellSize / 2.0f, cellSize / 2.0f);
	}

	// Fill index buffer description and create index buffer.
	buw::indexBufferDescription ibd;
	ibd.indexCount = octreeIndices.size();
	ibd.data = octreeIndices.data();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	indexBufferOctree_ = renderSystem()->createIndexBuffer(ibd);

	BLUE_LOG(trace) << "indexBufferOctree_:" << indexBufferOctree_.get() << ". Index count:" << ibd.indexCount << ".";

	// Fill vertex buffer description and create vertex buffer.
	buw::vertexBufferDescription vbd;
	vbd.vertexCount = octreeVertices.size();
	vbd.vertexLayout = buw::VertexPosition3::getVertexLayout();
	vbd.data = octreeVertices.data();
	vertexBufferOctree_ = renderSystem()->createVertexBuffer(vbd);

	BLUE_LOG(trace) << "vertexBufferOctree_:" << vertexBufferOctree_.get() << ". Vertex count:" << vbd.vertexCount << ".";
	BLUE_LOG(trace) << "Done creating octree buffers.";
}

void PointCloudEffect::setSections(std::vector<buw::ReferenceCounted<buw::PointCloudSection>> sections, buw::Vector3d offset)
{
	if(sections.size() > 0) {
		std::vector<buw::VertexPosition3> sectionVertices = std::vector<buw::VertexPosition3>();
		std::vector<uint32_t> sectionIndices = std::vector<uint32_t>();

		for(long i = 0; i < sections.size(); i++) {
			auto section = sections[i];
			if(section->size() > 0) {
				CCVector3 min, max;
				section->getObjectOrientedBoundingBox(min, max);
				CCVector3 size = (max - min) / 2.0f;
				CCVector3 center = min + ((max - min) / 2.0f);
				center = section->computeCenter();
				size_t startIndex = sectionVertices.size();
				CCVector3 shiftedCenter = min + ((max - min) / 2.0f);
				//buw::createBoundingBox(sectionVertices, sectionIndices, center.x + offset.x(), center.y + offset.y(), center.z + offset.z(), size.x, size.y, size.z);
				buw::createBoundingBox(sectionVertices, sectionIndices, 0, 0, 0, size.x, size.y, size.z);
				size_t endIndex = sectionVertices.size();
				auto rotation = section->getOrientation();
				buw::Vector3f centerGlobal = buw::Vector3f(center.x + offset.x(), center.y + offset.y(), center.z + offset.z());
				for(startIndex; startIndex < endIndex; startIndex++) {
					auto newpos = buw::Vector3f(sectionVertices[startIndex].position.data) + buw::Vector3f(shiftedCenter.x, shiftedCenter.y, shiftedCenter.z);
					sectionVertices[startIndex] = buw::VertexPosition3((rotation.cast<float>() * newpos) + centerGlobal);
				}

			}
		}


		buw::indexBufferDescription ibd;
		ibd.indexCount = sectionIndices.size();
		ibd.data = sectionIndices.data();
		ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
		sectionsBoundingBoxEffect_->assignIndexBuffer(renderSystem()->createIndexBuffer(ibd));

		// Fill vertex buffer description and create vertex buffer.
		buw::vertexBufferDescription vbd;
		vbd.vertexCount = sectionVertices.size();
		vbd.vertexLayout = buw::VertexPosition3::getVertexLayout();
		vbd.data = sectionVertices.data();
		sectionsBoundingBoxEffect_->assignVertexBuffer(renderSystem()->createVertexBuffer(vbd));
	}
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
	
	setPipelineState(pipelineStatePointCloud_);
	setRenderTarget(renderTarget, depthStencilMSAA_);
	setViewport(viewport_);
	setConstantBuffer(worldBuffer_, "WorldBuffer");
	setConstantBuffer(viewportBuffer_, "ViewportBuffer");
	setVertexBuffer(vertexBufferPointCloud_);

	if(bShow_) {

		settings_.color = uniformColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		if(bShowOriginalPointCloud_) {
			draw(static_cast<UINT>(vertexBufferPointCloud_->getVertexCount()));
		}
		else {
			if(indexBufferRemaining_ && indexBufferRemaining_->getIndexCount() > 0) {
				setIndexBuffer(indexBufferRemaining_);
				drawIndexed(static_cast<UINT>(indexBufferRemaining_->getIndexCount()));
			}
		}
	}

	if(bShowFilteredPoints_) {
		settings_.color = filteredColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		if(indexBufferFiltered_ && indexBufferFiltered_->getIndexCount() > 0) {
			setIndexBuffer(indexBufferFiltered_);
			drawIndexed(static_cast<UINT>(indexBufferFiltered_->getIndexCount()));
		}
	}

	if(bShowSegmentedPoints_) {
		settings_.color = segmentedColor_;
		updateSettingsBuffer();
		setConstantBuffer(settingsBuffer_, "SettingsBuffer");

		if(indexBufferSegmented_ && indexBufferSegmented_->getIndexCount() > 0) {
			setIndexBuffer(indexBufferSegmented_);
			drawIndexed(static_cast<UINT>(indexBufferSegmented_->getIndexCount()));
		}
	}

	if(bShowOctree_) {
		setPipelineState(pipelineStateOctree_);
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setViewport(viewport_); 
		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setConstantBuffer(viewportBuffer_, "ViewportBuffer");
		setVertexBuffer(vertexBufferOctree_);
		setIndexBuffer(indexBufferOctree_);
		drawIndexed(static_cast<UINT>(indexBufferOctree_->getIndexCount()));		
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


OIP_NAMESPACE_OPENINFRAPLATFORM_RENDERING_END