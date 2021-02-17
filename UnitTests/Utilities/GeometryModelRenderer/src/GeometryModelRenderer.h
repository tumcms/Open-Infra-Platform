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

#pragma once
#ifndef GEOMETRYMODELRENDERER_H
#define GEOMETRYMODELRENDERER_H

#include <buw.Engine.h>

#include "OffConverter/OffModel.h"
#include "IfcGeometryConverter/IfcGeometryModel.h"

/*!
 * \brief Utility class to render \c GeometryModel data without UI for automated unit tests.
 *
 */
class GeometryModelRenderer
{
public:
	/*!
	 * \brief Constructs the renderer by injecting the rendering system.
	 * \param renderSystem
	 */
	GeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem);

	/*!
	 * \brief Releases all resources.
	 */
	virtual ~GeometryModelRenderer();

	/*!
	 * \brief Set the model to be rendered.
	 * \param model
	 * \note This also moves the camera to it's default position.
	 */
	//virtual void setModel(const std::shared_ptr<oip::IfcModel>& model);
	//virtual void setModel(const std::shared_ptr<oip::OffModel>& model);

	/*!
	 * \brief Repaints and returns back buffer image.
	 * \return Rendered back buffer image.
	 */
	buw::Image4b captureImage();

	/*!
	 * \brief Set the viewing angle.
	 * \param direction The direction flag denoting the viewing angle.
	 * \param fitViewToModel Should the model be fit to the view (true, default), or just the view rotated without changing the scale (false)?
	 */
	void setViewDirection(const buw::eViewDirection &direction, const bool fitViewToModel = true);

	virtual oip::BBox getExtent() const = 0;

protected:

	/*!
	* \brief Moves the camera such that the whole model is to be seen.
	*/
	virtual void fitViewToModel() const;

	/*!
	* \brief Clears the back buffer image and depth stencil.
	* \note Current clear color is RGBA(0,0,0,0).
	*/
	void clearBackBuffer();

	/*!
	 * \brief Renders the model and updates the front buffer so that the image is presented.
	 */
	void repaint();
	
	virtual void render() = 0;

	/*!
	 * \brief Updates the world buffer with camera matrices.
	 */
	void updateWorldBuffer();

	/*!
	 * \brief Copies the current back buffer texture content into the returned image.
	 * \return Rendered back buffer image.
	 */
	buw::Image4b getBackBufferImage() const;


	int width_ = 640;
	int height_ = 480;

	buw::ReferenceCounted<BlueFramework::Engine::Camera> camera_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Engine::CameraController> cameraController_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::IRenderSystem> renderSystem_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::IViewport> viewport_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> depthStencilMSAA_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> worldBuffer_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> backBuffer_ = nullptr;
};

#endif // IFCGEOMETRYMODELRENDERER_H