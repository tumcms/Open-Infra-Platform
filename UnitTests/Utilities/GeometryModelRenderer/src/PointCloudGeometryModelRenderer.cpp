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
#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
#include "PointCloudGeometryModelRenderer.h"
#include "Effects/UIElementsEffect.h"

PointCloudGeometryModelRenderer::PointCloudGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem)
	: GeometryModelRenderer::GeometryModelRenderer(renderSystem)
{
	oip::ViewportBuffer buffer = { 640, 480 };

	buw::constantBufferDescription cbd1;
	cbd1.sizeInBytes = sizeof(oip::ViewportBuffer);
	cbd1.data = &buffer;
	viewportBuffer_ = renderSystem_->createConstantBuffer(cbd1);

	pointCloudEffect_ = buw::makeReferenceCounted<oip::PointCloudEffect>
		(renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_, viewportBuffer_);
	pointCloudEffect_->init();

}

PointCloudGeometryModelRenderer::~PointCloudGeometryModelRenderer()
{
	model_.reset();
	pointCloudEffect_.reset();
}

void PointCloudGeometryModelRenderer::setModel(const std::shared_ptr<oip::PointCloud>& model)
{
	model_.reset();
	model_ = model;
	pointCloudEffect_->setPointCloud(model);

	pointCloudEffect_->setOffset(-model->getExtent().center());

	fitViewToModel();
}

oip::BBox PointCloudGeometryModelRenderer::getExtent() const
{
	return model_->getExtent();
}

void PointCloudGeometryModelRenderer::render()
{
	pointCloudEffect_->render();
}

#endif
