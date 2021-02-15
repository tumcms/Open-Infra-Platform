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

#include "IfcGeometryModelRenderer.h"


IfcGeometryModelRenderer::IfcGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem)
    : GeometryModelRenderer(renderSystem)
{
    ifcGeometryEffect_ = buw::makeReferenceCounted<oip::IfcGeometryEffect>(
        renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_);
    ifcGeometryEffect_->init();
}

IfcGeometryModelRenderer::~IfcGeometryModelRenderer()
{
    model_.reset();
    ifcGeometryEffect_.reset();
}

void IfcGeometryModelRenderer::fitViewToModel() const
{
	cameraController_->fitToView((model_->getExtent().min() - model_->getExtent().center()).cast<float>(), 
		(model_->getExtent().max() - model_->getExtent().center()).cast<float>());
		
    cameraController_->tick(1.0f);
    camera_->tick(1.0f);
}

void IfcGeometryModelRenderer::setModel(const std::shared_ptr<oip::IfcModel>& model)
{
    model_.reset();
    model_ = model;
	ifcGeometryEffect_->setIfcGeometryModel(model);

	ifcGeometryEffect_->setOffset(-model->getExtent().center());
	
    fitViewToModel();
}

void IfcGeometryModelRenderer::repaint()
{
    clearBackBuffer();
    updateWorldBuffer();
    ifcGeometryEffect_->render();
    renderSystem_->present();
}