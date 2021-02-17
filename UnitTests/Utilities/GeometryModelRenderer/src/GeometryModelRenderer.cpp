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

#include "GeometryModelRenderer.h"

struct WorldBuffer
{
	buw::Matrix44f viewProjection;
	buw::Matrix44f projection;
	buw::Matrix44f view;
	buw::Vector3f cam;
	buw::Matrix44f rotation;
};

GeometryModelRenderer::GeometryModelRenderer(const buw::ReferenceCounted<buw::IRenderSystem>& renderSystem)
	: renderSystem_{ renderSystem }
{
	backBuffer_ = renderSystem_->getBackBufferTarget();
	backBuffer_->makeCPUReadable();

	width_ = backBuffer_->width();
	height_ = backBuffer_->height();

	camera_ = buw::makeReferenceCounted<buw::Camera>();
	cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);

	camera_->frustum() = buw::CameraFrustum(width_, height_, 0.5f, 50000.f, buw::eProjectionType::Perspective);
	camera_->transformation().offset() = 15;
	camera_->transformation().yaw() = buw::constantsf::pi_over_4();

	buw::texture2DDescription dsvTD;
	dsvTD.width = width_;
	dsvTD.height = height_;
	dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	dsvTD.data = nullptr;
	dsvTD.isCpuReadable = false;
	dsvTD.useMSAA = renderSystem_->getMSAAEnabled();
	depthStencilMSAA_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

	viewport_ = renderSystem_->createViewport(buw::viewportDescription(width_, height_));

	buw::constantBufferDescription cbd0;
	cbd0.sizeInBytes = sizeof(WorldBuffer);
	cbd0.data = nullptr;
	worldBuffer_ = renderSystem_->createConstantBuffer(cbd0);

	WorldBuffer world;
	world.viewProjection = camera_->viewProjectionMatrix();
	world.projection = camera_->frustum().projectionMatrix();
	world.view = camera_->transformation().viewMatrix();
	world.cam = (camera_->transformation().transformationMatrix() * buw::Vector4f(0, 0, 0, 1)).block<3, 1>(0, 0);
	world.rotation = camera_->transformation().rotationMatrix();

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(WorldBuffer);
	cbd.data = &world;
	worldBuffer_->uploadData(cbd);

	//create a GeometryEffect in Ifc and Off class constructor
}

GeometryModelRenderer::~GeometryModelRenderer()
{
	//model_.reset();
	//ifcGeometryEffect_.reset();
	worldBuffer_.reset();
	viewport_.reset();
	depthStencilMSAA_.reset();
	backBuffer_.reset();
	renderSystem_.reset();
	cameraController_.reset();
	camera_.reset();
}

void GeometryModelRenderer::clearBackBuffer()
{
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	renderSystem_->clearRenderTarget(backBuffer_, color);
	renderSystem_->clearDepthStencilView(depthStencilMSAA_);
}

void GeometryModelRenderer::repaint()
{
	clearBackBuffer();
	updateWorldBuffer();
	render();
	renderSystem_->present();

	//ifcGeometryEffect_->render();
}

void GeometryModelRenderer::fitViewToModel() const
{
	oip::BBox extent = getExtent();
	cameraController_->fitToView((extent.min() - extent.center()).cast<float>(), 
		(extent.max() - extent.center()).cast<float>());
		
    cameraController_->tick(1.0f);
    camera_->tick(1.0f);
}

void GeometryModelRenderer::updateWorldBuffer()
{
	WorldBuffer world;
	world.viewProjection = camera_->viewProjectionMatrix();
	world.projection = camera_->frustum().projectionMatrix();
	world.view = camera_->transformation().viewMatrix();
	world.cam = (camera_->transformation().transformationMatrix() * buw::Vector4f(0, 0, 0, 1)).block<3, 1>(0, 0);
	world.rotation = camera_->transformation().rotationMatrix();

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(WorldBuffer);
	cbd.data = &world;
	worldBuffer_->uploadData(cbd);
}

buw::Image4b GeometryModelRenderer::getBackBufferImage() const
{
	auto backBufferImage = buw::Image4b(width_, height_);
	renderSystem_->downloadTexture(backBuffer_, backBufferImage);
	return backBufferImage;
}

buw::Image4b GeometryModelRenderer::captureImage()
{
	repaint();
	return getBackBufferImage();
}

void GeometryModelRenderer::setViewDirection(const buw::eViewDirection& direction, const bool fitViewToModel)
{
	if (fitViewToModel)
		this->fitViewToModel();
	cameraController_->setViewDirection(buw::CameraController::getViewDirectionVector(direction));

	// Operation takes 0.5 seconds
	cameraController_->tick(1.0f);
	camera_->tick(1.0f);
}