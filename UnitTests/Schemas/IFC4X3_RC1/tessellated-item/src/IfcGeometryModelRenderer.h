/*
    Copyright (c) 2020 Technical University of Munich
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

#pragma once
#ifndef IFCGEOMETRYMODELRENDERER_H
#define IFCGEOMETRYMODELRENDERER_H

#include <buw.Engine.h>

#include "IfcGeometryConverter/ConverterBuw.h"

#include <Effects/IfcGeometryEffect.h>

struct WorldBuffer {
    buw::Matrix44f viewProjection;
    buw::Matrix44f projection;
    buw::Matrix44f view;
    buw::Vector3f cam;
    buw::Matrix44f rotation;
};

class IfcGeometryModelRenderer
{
public:
    IfcGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem> &renderSystem);

    virtual ~IfcGeometryModelRenderer();

    void setModel(const std::shared_ptr<oip::IfcGeometryModel>& model);

    void clearBackBuffer();

    void repaint();

    buw::Image4b getBackBufferImage() const;

    buw::Image4b captureImage();


private:
    int width_ = 640;
    int height_ = 480;

    buw::ReferenceCounted<BlueFramework::Engine::Camera> camera_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Engine::CameraController> cameraController_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IRenderSystem> renderSystem_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IViewport> viewport_ = nullptr;
    buw::ReferenceCounted<OpenInfraPlatform::Rendering::IfcGeometryEffect> ifcGeometryEffect_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> depthStencilMSAA_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> worldBuffer_ = nullptr;
    buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> backBuffer_ = nullptr;
};

#endif // IFCGEOMETRYMODELRENDERER_H
