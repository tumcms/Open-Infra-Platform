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

#include "OffGeometryModelRenderer.h"

OffGeometryModelRenderer::OffGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem) 
	: GeometryModelRenderer::GeometryModelRenderer(renderSystem)
{
	offGeometryEffect_ = buw::makeReferenceCounted<oip::OffGeometryEffect>(
		renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_);
	offGeometryEffect_->init();
}

OffGeometryModelRenderer::~OffGeometryModelRenderer()
{
	model_.reset();
	offGeometryEffect_.reset();
}

//void OffGeometryModelRenderer::setModel(const std::shared_ptr<oip::OffModel>& model) 
//{
//	model_.reset();
//	model_ = model;
//	offGeometryEffect_->setOffModel(model);
//
//	offGeometryEffect_->setOffset(-model->getExtent().center());
//
//	fitViewToModel();
//}

void OffGeometryModelRenderer::fitViewToModel() const
{
	cameraController_->fitToView((model_->getExtent().min() - model_->getExtent().center()).cast<float>(),
		(model_->getExtent().max() - model_->getExtent().center()).cast<float>());

	cameraController_->tick(1.0f);
	camera_->tick(1.0f);
}

void OffGeometryModelRenderer::repaint()
{
	clearBackBuffer();
	updateWorldBuffer();
	offGeometryEffect_->render();
	renderSystem_->present();
}