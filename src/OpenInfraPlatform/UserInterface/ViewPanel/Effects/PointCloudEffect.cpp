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
	bProjectPoints_ = checked;
	settings_.bProjectPoints = bProjectPoints_;
	updateSettingsBuffer();
}

void PointCloudEffect::updateIndexBuffers(const std::tuple<std::vector<uint32_t>, std::vector<uint32_t>, std::vector<uint32_t>> indices)
{
	std::vector<uint32_t> remainingIndices, filteredIndices, segmentedIndices;
	std::tie(remainingIndices, filteredIndices, segmentedIndices) = indices;

	// If we use a subsampled cloud, we're only interested in the indices which are in our subsampled cloud.
	if(bUseSubsampledCloud_) {
		std::vector<uint32_t> subsampledIndices = std::vector<uint32_t>(subsampledPointCloud_->size());

		// Get the real indices and store them to filter the other vectors.
#pragma omp parallel for
		for(long i = 0; i < subsampledIndices.size(); i++) {
			subsampledIndices[i] = subsampledPointCloud_->getPointGlobalIndex(i);
		}

		auto reduceToIntersection = [](std::vector<uint32_t> &vector, const std::vector<uint32_t> &filter) {
			auto end = std::remove_if(vector.begin(), vector.end(), [&](const uint32_t &elem)->bool { return std::find(filter.begin(), filter.end(), elem) == filter.end(); });
			vector.erase(end, vector.end());
		};

		auto threadRemainingIndices = std::thread(reduceToIntersection, remainingIndices, subsampledIndices);
		auto threadfilteredIndices = std::thread(reduceToIntersection, filteredIndices, subsampledIndices);
		auto threadSegmentedIndices = std::thread(reduceToIntersection, segmentedIndices, subsampledIndices);

		threadRemainingIndices.join();
		threadfilteredIndices.join();
		threadSegmentedIndices.join();
	}

	buw::indexBufferDescription ibd;
	ibd.indexCount = remainingIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = remainingIndices.data();

	if(ibd.indexCount > 0)
		indexBufferRemaining_ = renderSystem()->createIndexBuffer(ibd);

	ibd.indexCount = filteredIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = filteredIndices.data();

	if(ibd.indexCount > 0)
		indexBufferFiltered_ = renderSystem()->createIndexBuffer(ibd);

	ibd.indexCount = segmentedIndices.size();
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.data = segmentedIndices.data();

	if(ibd.indexCount > 0)
		indexBufferSegmented_ = renderSystem()->createIndexBuffer(ibd);
}

void PointCloudEffect::setPointCloud(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::PointCloud> pointCloud, buw::Vector3d offset)
{
	BLUE_LOG(trace) << "Start initializing GPU side buffers.";
	buw::vertexBufferDescription vbd;
	vbd.vertexLayout = VertexTypePointCloud::getVertexLayout();
	
	// Initialize the vector to hold our data and out base color.
	std::vector<VertexTypePointCloud> vertices = std::vector<VertexTypePointCloud>(pointCloud->size());
	auto baseColor = ccColor::Rgbaf(255.0f, 255.0f, 255.0f, 255.0f);
	
	// If the cloud is too large to be held in gpu memory, subsample the cloud. We require 32 bytes per point due to 16 byte alignment on gpu.
	size_t vbDataByteSize = pointCloud->size() * 32;
	size_t vbMaxCapacity = 2 * 1024 * 1024 * 32;
	bUseSubsampledCloud_ = false;
	subsampledPointCloud_ = nullptr;
	size_t vbNumPoints = pointCloud->size();

	// If we would need more than 4GiB, we subsample the cloud. TODO: Make gpu memory amount queryable.
	if(vbDataByteSize > (2 * 1024 * 1024 * 1024)) {
		BLUE_LOG(warning) << "Not enough GPU memory available. Using a subsampled point cloud with " << QString::number(vbMaxCapacity).toStdString() << " points.";
		subsampledPointCloud_ = pointCloud->subsample(vbMaxCapacity);
		bUseSubsampledCloud_ = true;
		vbNumPoints = subsampledPointCloud_->size();
	}

#pragma omp parallel for
	for(long ii = 0; ii < vbNumPoints; ii++) {
		size_t i;
		if(bUseSubsampledCloud_)
			i = subsampledPointCloud_->getPointGlobalIndex(ii);
		else
			i = ii;

		auto pos = pointCloud->getPoint(i);
		const ColorCompType* col = pointCloud->rgbColors() ? pointCloud->getPointColor(i) : ccColor::FromRgbf(baseColor).rgb;
		// Swap Z and Y coordinate for rendering!
		vertices[i] = VertexTypePointCloud(buw::Vector3f(pos->x + offset.x(), pos->z + offset.z(), pos->y + offset.y()), buw::Vector4f((float)col[0], (float)col[1], (float)col[2], 255.0f) / 255.0f);
	}
	
	vbd.vertexCount = vbNumPoints;
	vbd.data = vertices.data();
	vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
	BLUE_LOG(trace) << "Done creating vertex buffer.";

	std::vector<uint32_t> remainingIndices = std::vector<uint32_t>(), filteredIndices = std::vector<uint32_t>(), segmentedIndices = std::vector<uint32_t>();

	// If we use a subsampled cloud, we're only interested in the indices which are in our subsampled cloud.
	if(bUseSubsampledCloud_) {
		bool filtered = false, segmented = false;

#pragma omp parallel shared(filtered,segmented)
		{
			std::vector<uint32_t> remainingIndicesLocal = std::vector<uint32_t>(), filteredIndicesLocal = std::vector<uint32_t>(), segmentedIndicesLocal = std::vector<uint32_t>();


#pragma omp single
			// Let one thread check if we have a filtered scalar field, if yes, set it as readable field.
			{
				int idx_filtered = pointCloud->getScalarFieldIndexByName("Filtered");
				if(idx_filtered != -1) {
					pointCloud->setCurrentOutScalarField(idx_filtered);
					filtered = true;
				}				
			}

			if(filtered) {
				// If we have a filter, we have to split and read the scalar value to insert our points.
#pragma omp for
				for(long i = 0; i < subsampledPointCloud_->size(); i++) {
					if(subsampledPointCloud_->getPointScalarValue(i) > 0) {
						filteredIndicesLocal.push_back(subsampledPointCloud_->getPointGlobalIndex(i));
					}
					else {
						remainingIndicesLocal.push_back(subsampledPointCloud_->getPointGlobalIndex(i));
					}
				}
			}
			else {
#pragma omp for
				for(long i = 0; i < subsampledPointCloud_->size(); i++) {
					remainingIndicesLocal.push_back(subsampledPointCloud_->getPointGlobalIndex(i));
				}
			}
#pragma omp barrier

#pragma omp single
			// Let one thread check if we have a segmented scalar field, if yes, set it as readable field.
			{
				int idx_segmented = pointCloud->getScalarFieldIndexByName("Segmented");
				if(idx_segmented != -1) {
					pointCloud->setCurrentOutScalarField(idx_segmented);
					segmented = true;
				}
			}

			if(segmented) {
#pragma omp for
				for(long i = 0; i < subsampledPointCloud_->size(); i++) {
					if(subsampledPointCloud_->getPointScalarValue(i) > 0) {
						segmentedIndicesLocal.push_back(subsampledPointCloud_->getPointGlobalIndex(i));
					}
				}
#pragma omp barrier
			}

#pragma omp critical
			{
				remainingIndices.insert(remainingIndices.end(), remainingIndicesLocal.begin(), remainingIndicesLocal.end());
				filteredIndices.insert(filteredIndices.end(), filteredIndicesLocal.begin(), filteredIndicesLocal.end());
				segmentedIndices.insert(segmentedIndices.end(), segmentedIndicesLocal.begin(), segmentedIndicesLocal.end());
			}

		}

		{
			// Get the real indices and store them to filter the other vectors.


			//auto reduceToIntersection = [](std::vector<uint32_t> &vector, const std::vector<uint32_t> &filter) {
			//	auto end = std::remove_if(vector.begin(), vector.end(), [&](const uint32_t &elem)->bool { return std::find(filter.begin(), filter.end(), elem) == filter.end(); });
			//	vector.erase(end, vector.end());
			//};
			//
			//auto threadRemainingIndices = std::thread(reduceToIntersection, remainingIndices, subsampledIndices);
			//auto threadFilteredIndices = std::thread(reduceToIntersection, filteredIndices, subsampledIndices);
			//auto threadSegmentedIndices = std::thread(reduceToIntersection, segmentedIndices, subsampledIndices);
			//
			//threadRemainingIndices.join();
			//threadFilteredIndices.join();
			//threadSegmentedIndices.join();
		}
	}
	else {
		std::tie(remainingIndices, filteredIndices, segmentedIndices) = pointCloud->getIndices();
	}

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

	BLUE_LOG(trace) << "Done creating index buffers.";

	settings_.mainAxis = buw::Vector4f(pointCloud->getMainAxis().x, pointCloud->getMainAxis().y, pointCloud->getMainAxis().z, 0.0f);
	settings_.sectionLength = (float) pointCloud->getSectionLength();

	BLUE_LOG(trace) << "Finished initializing GPU side buffers.";
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
	BLUE_LOG(trace) << "Start rendering.";
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
		else {
			if(indexBufferRemaining_ && indexBufferRemaining_->getIndexCount()) {
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
	BLUE_LOG(trace) << "Done rendering.";
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