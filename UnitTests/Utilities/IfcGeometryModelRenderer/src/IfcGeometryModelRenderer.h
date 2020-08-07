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



/*!
 * \brief Utility class to render \c IfcGeometryModel data without UI for automated unit tests.
 * 
 */
class IfcGeometryModelRenderer
{
public:
    /*!
     * \brief Constructs the renderer by injecting the rendering system. 
     * \param renderSystem
     */
    IfcGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem);

    /*!
     * \brief Releases all resources. 
     */
    virtual ~IfcGeometryModelRenderer();

    /*!
     * \brief Set the model to be rendered. 
     * \param model
     * \note This also moves the camera to it's default position.
     */
    void setModel(const std::shared_ptr<oip::IfcGeometryModel>& model);

    /*!
     * \brief Repaints and returns back buffer image.
     * \return Rendered back buffer image.
     */
    buw::Image4b captureImage();

    /*!
     * \brief Set the viewing angle.
     * \param direction
     */
    void setViewDirection(const buw::eViewDirection &direction);

protected:

    /*!
    * \brief Moves the camera such that it focuses on the model.
    */
    void fitViewToModel() const;

    /*!
    * \brief Clears the back buffer image and depth stencil.
    * \note Current clear color is RGBA(0,0,0,0).
    */
    void clearBackBuffer();

    /*!
     * \brief Renders the model and updates the front buffer so that the image is presented.
     */
    void repaint();

    /*!
     * \brief Updates the world buffer with camera matrices.
     */
    void updateWorldBuffer();

    /*!
     * \brief Copies the current back buffer texture content into the returned image.
     * \return Rendered back buffer image.
     */
    buw::Image4b getBackBufferImage() const;


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
    buw::ReferenceCounted<oip::IfcGeometryModel> model_ = nullptr;
};

#endif // IFCGEOMETRYMODELRENDERER_H
