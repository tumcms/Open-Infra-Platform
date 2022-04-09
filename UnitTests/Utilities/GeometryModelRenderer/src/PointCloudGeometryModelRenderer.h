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
#ifndef POINTCLOUDGEOMETRYMODELRENDERER_H
#define POINTCLOUDGEOMETRYMODELRENDERER_H

#include <buw.Engine.h>

#include "GeometryModelRenderer.h"

#include <Effects/PointCloudProcessing/PointCloudEffect.h>

/*!
 * \brief Utility class to render \c PointCloudGeometryModelRenderer data without UI for automated unit tests.
 *
 */
class PointCloudGeometryModelRenderer : public GeometryModelRenderer
{
public:
public:
	/*!
	 * \brief Constructs the renderer by injecting the rendering system.
	 * \param renderSystem
	 */
	PointCloudGeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem);

	/*!
	 * \brief Releases all resources.
	 */
	 virtual ~PointCloudGeometryModelRenderer();

	/*!
	 * \brief Set the model to be rendered.
	 * \param model
	 * \note This also moves the camera to it's default position.
	 */
	void setModel(const std::shared_ptr<oip::PointCloud>& model);

protected:
	/*!
	 * \brief Returns the extent of the loaded off model.
	 */
	virtual oip::BBox getExtent() const override;

	/*!
	 * \brief Renders the OffGeometryEffect.
	 */
	virtual void render() override;

private:
	buw::ReferenceCounted<oip::PointCloud> model_ = nullptr;
	buw::ReferenceCounted<OpenInfraPlatform::Rendering::PointCloudEffect> pointCloudGeometryEffect_ = nullptr;
	buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> viewportBuffer_ = nullptr;
};

#endif // POINTCLOUDGEOMETRYMODELRENDERER_H