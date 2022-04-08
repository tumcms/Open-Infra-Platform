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

#include "PointCloudGeometryModelRenderer.h"

PointCloudGeometryModelRenderer::PointCloudGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem)
	: GeometryModelRenderer::GeometryModelRenderer(renderSystem)
{
	pointCloudGeometryEffect_ = buw::makeReferenceCounted<oip::PointCloudEffect>(
		renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_);
	pointCloudGeometryEffect_->init();
}

PointCloudGeometryModelRenderer::~PointCloudGeometryModelRenderer()
{
	model_.reset();
	pointCloudGeometryEffect_.reset();
}

void PointCloudGeometryModelRenderer::setModel(const std::shared_ptr<oip::PointCloud>& model)
{
	model_.reset();
	model_ = model;
	pointCloudGeometryEffect_->setPointCloud(model);

	pointCloudGeometryEffect_->setOffset(-model->getExtent().center());

	fitViewToModel();
}

oip::BBox PointCloudGeometryModelRenderer::getExtent() const
{
	return model_->getExtent();
}

void PointCloudGeometryModelRenderer::render()
{
	pointCloudGeometryEffect_->render();
}