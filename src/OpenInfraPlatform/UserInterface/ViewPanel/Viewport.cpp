/*
    Copyright (c) 2017 Technical University of Munich
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

#include "OpenInfraPlatform/UserInterface/ViewPanel/Viewport.h"

#include "OpenInfraPlatform/Benchmark.h"
#include "OpenInfraPlatform/DataManagement/Command/SelectAlignment.h"
#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/Infrastructure/Import/ImportLandXml.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/CoordinateSystem.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/AlignmentEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/GirderEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/SlabFieldEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/DEMEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/TrafficSignEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/GradientClearEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/UIElementsEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/IfcGeometryEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/SkyboxEffect.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/RenderResources.h"

#include <buw.Engine.h>
#include <buw.Rasterizer.h>
#include <QDir>
#include <QTimer>
#include <QtXml>
#include <QtXmlPatterns>
#include <iomanip>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

struct WorldBuffer {
	buw::Matrix44f viewProjection;
	buw::Matrix44f projection;
	buw::Matrix44f view;
	buw::Vector3f cam;
	buw::Matrix44f rotation;
};

Viewport::Viewport(const buw::eRenderAPI renderAPI, bool warp, bool msaa, QWidget* parent /*= nullptr*/) :
	QWidget(parent), 
	depthBuffer_(0, 0),
	pickIdImage_(1, 1),
	selectedAlignmentIndex_(0)
{
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);

	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change.connect(boost::bind(&Viewport::onChange, this));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Clear.connect(boost::bind(&Viewport::onClear, this));

	camera_ = buw::makeReferenceCounted<buw::Camera>();
	cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);

	camera_->frustum() = buw::CameraFrustum(width(), height(), 0.5f, 50000.f, buw::eProjectionType::Perspective);
	camera_->transformation().offset() = 15;
	camera_->transformation().yaw() = buw::constantsf::pi_over_4();

	depthBuffer_.resize(width(), height());

	buw::renderSystemDescription scd;
	scd.width = width();
	scd.height = height();
	scd.windowId = (void*)(winId());
	scd.forceWarpDevice = warp;
	scd.enableMSAA = msaa;
	scd.renderAPI = renderAPI;

	BLUE_LOG(trace) << "Creating render system";
	renderSystem_ = BlueFramework::Rasterizer::createRenderSystem(scd);

	std::string rsName = renderSystem_->getName();
	
	BLUE_LOG(trace) << "Creating viewport";
	viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

	createDepthStencil();

	buw::texture2DDescription pbTD;
	pbTD.width = width();
	pbTD.height = height();
	pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
	pbTD.data = nullptr;
	pbTD.isCpuReadable = true;
	pbTD.useMSAA = false;
	pickBuffer_ = renderSystem_->createTexture2D(pbTD, buw::eTextureBindType::RTV);

	buw::constantBufferDescription cbd1;
	cbd1.sizeInBytes = sizeof(WorldBuffer);
	cbd1.data = nullptr;
	worldBuffer_ = renderSystem_->createConstantBuffer(cbd1);

	buw::constantBufferDescription cbd2;
	cbd2.sizeInBytes = sizeof(ViewportBuffer);
	cbd2.data = nullptr;
	viewportBuffer_ = renderSystem_->createConstantBuffer(cbd2);

    buw::constantBufferDescription cbd3;
    cbd2.sizeInBytes = sizeof(UINT);
    cbd2.data = nullptr;
    pickIdBuffer_ = renderSystem_->createConstantBuffer(cbd2);

	viewCube_ = buw::makeReferenceCounted<buw::ViewCube>(renderSystem_, pickBuffer_, pickIdBuffer_, cameraController_);

	BLUE_LOG(trace) << "Creating effects (1)";
	gradientClearEffect_ = buw::makeReferenceCounted<GradientClearEffect>(renderSystem_.get(), viewport_);
    BLUE_LOG(trace) << "Creating effects (1.1)";
    gradientClearEffect_->init();

	BLUE_LOG(trace) << "Creating effects (2)";
	demEffect_ = buw::makeReferenceCounted<DEMEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, pickBuffer_, depthStencil_, worldBuffer_);
	demEffect_->init();

	BLUE_LOG(trace) << "Creating effects (3)";
	trafficSignEffect_ = buw::makeReferenceCounted<TrafficSignEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, pickBuffer_, depthStencil_, worldBuffer_);
	trafficSignEffect_->init();

	BLUE_LOG(trace) << "Creating effects (4)";
	alignmentEffect_ = buw::makeReferenceCounted<AlignmentEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, pickBuffer_, depthStencil_, worldBuffer_, viewportBuffer_, pickIdBuffer_);
	alignmentEffect_->init();

	BLUE_LOG(trace) << "Creating effects (5)";
	girderEffect_ = buw::makeReferenceCounted<GirderEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_, viewportBuffer_);
	girderEffect_->init();

	BLUE_LOG(trace) << "Creating effects (6)";
	slabFieldEffect_ = buw::makeReferenceCounted<SlabFieldEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_, viewportBuffer_);
	slabFieldEffect_->init();

	BLUE_LOG(trace) << "Creating effects (7)";
	uiElements_ = buw::makeReferenceCounted<UIElements>(renderSystem_.get(), depthStencilMSAA_, worldBuffer_);
	uiElements_->init();

    BLUE_LOG(trace) << "Creating IfcGeometry effects";
    ifcGeometryEffect_ = buw::makeReferenceCounted<IfcGeometryEffect>(renderSystem_.get(), viewport_, depthStencilMSAA_, worldBuffer_);
    ifcGeometryEffect_->init();

    BLUE_LOG(trace) << "Creating Skybox effect";
    skyboxEffect_ = buw::makeReferenceCounted<SkyboxEffect>(renderSystem_.get(), viewport_, worldBuffer_);
    skyboxEffect_->init();

	timer_ = new QTimer();
	timer_->setInterval(16);
	timer_->setSingleShot(false);
	connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));

	buw::Singleton<RenderResources>::instance().init(renderSystem_);

	lastTick_ = std::chrono::high_resolution_clock::now().time_since_epoch();
	timer_->start();

	BLUE_LOG(trace) << "End of Viewport ctor";
}

Viewport::~Viewport() {

	disconnect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change.disconnect(boost::bind(&Viewport::onChange, this));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Clear.disconnect(boost::bind(&Viewport::onClear, this));

	buw::Singleton<RenderResources>::instance().release();
    activeEffects_.clear();

	delete timer_;
	timer_ = nullptr;

	uiElements_ = nullptr;
	slabFieldEffect_ = nullptr;
	girderEffect_ = nullptr;
	alignmentEffect_ = nullptr;
	trafficSignEffect_ = nullptr;
	demEffect_ = nullptr;
	gradientClearEffect_ = nullptr;
    skyboxEffect_ = nullptr;
    ifcGeometryEffect_ = nullptr;

	viewCube_ = nullptr;

	pickIdBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	worldBuffer_ = nullptr;
	pickBuffer_ = nullptr;

	depthStencil_ = nullptr;
	depthStencilMSAA_ = nullptr;

	viewport_ = nullptr;
	renderSystem_ = nullptr;
}

void Viewport::createDepthStencil() {
	buw::texture2DDescription dsvTD;
	dsvTD.width = width();
	dsvTD.height = height();
	dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	dsvTD.data = nullptr;
	dsvTD.isCpuReadable = false;
	dsvTD.useMSAA = true;
	depthStencilMSAA_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

	dsvTD.isCpuReadable = true;
	dsvTD.useMSAA = false;
	depthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);
}

void Viewport::resizeDepthStencil() {
	buw::texture2DDescription dsvTD;
	dsvTD.width = width();
	dsvTD.height = height();
	dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	dsvTD.data = nullptr;
	dsvTD.isCpuReadable = false;
	dsvTD.useMSAA = true;
	depthStencilMSAA_->resize(dsvTD);

	dsvTD.isCpuReadable = true;
	dsvTD.useMSAA = false;
	depthStencil_->resize(dsvTD);
}

void Viewport::setDrawTerrainWireframe(const bool enable) {
	demEffect_->setDrawTerrainWireframe(enable);
	repaint();
}

void Viewport::setDifferentColorsForAlignmentElements(const bool checked) {
	alignmentEffect_->enableAlignmentColor(checked);
}

void OpenInfraPlatform::UserInterface::Viewport::setHighlightSelectedAlignmentSegment(const bool checked)
{
    alignmentEffect_->enableHighlightSelected(checked);
}

void Viewport::viewDirection(const buw::Vector3f& direction) {
	cameraController_->setViewDirection(direction);
}

void Viewport::setHideTerrain(const bool checked) {
	demEffect_->hideTerrain(checked);
	repaint();
}

void Viewport::enableTerrainTextured(const bool checked) {
	demEffect_->enableTerrainTextured(checked);
	repaint();
}

void OpenInfraPlatform::UserInterface::Viewport::enableRoadBodyTextured(const bool checked)
{
    alignmentEffect_->drawRoadBodyTextured(checked);
    repaint();
}

void Viewport::enableIsoLines(const bool checked) {
	demEffect_->enableIsoLines(checked);
	repaint();
}

void Viewport::enableTerrainGradientRamp(const bool checked) {
	demEffect_->enableTerrainColorRamp(checked);
	repaint();
}

void Viewport::showCrossSection(const bool showCrossSection) {
	alignmentEffect_->showCrossSections(showCrossSection);
}

void Viewport::showDesignCrossSection(const bool showDesignCrossSections) {
	alignmentEffect_->showDesignCrossSections(showDesignCrossSections);
}

void OpenInfraPlatform::UserInterface::Viewport::showRoadBodyWireframe(const bool connectCrossSections)
{
    alignmentEffect_->showRoadBodyWireframe(connectCrossSections);
}

void OpenInfraPlatform::UserInterface::Viewport::showRoadBodySolid(const bool checked)
{
    alignmentEffect_->showRoadBodySolid(checked);
}


buw::ReferenceCounted<buw::ViewCube> Viewport::getViewCube() {
	return viewCube_;
}

buw::ReferenceCounted<AlignmentEffect> OpenInfraPlatform::UserInterface::Viewport::getAlignmentEffect()
{
	return alignmentEffect_;
}

void Viewport::setView(eView type) {
	switch (type) {
	case eView::HorizontalAlignment: alignmentEffect_->drawFlattened(true); break;
	case eView::ThreeDimensional: alignmentEffect_->drawFlattened(false); break;
	default: alignmentEffect_->drawFlattened(false); break;
	}
	repaint();
}

void Viewport::saveAsScreenshot(const std::string& filename) {
	repaint();

	buw::Image4b backBufferImage(width(), height());
	buw::ReferenceCounted<buw::ITexture2D> backBuffer = renderSystem_->getBackBufferTarget();
	if (!backBuffer->isCPUReadable())
		backBuffer->makeCPUReadable();
	renderSystem_->downloadTexture(backBuffer, backBufferImage);
	buw::storeImage(filename, backBufferImage);
}

void Viewport::storeGBuffer() {
	repaint();

	buw::Image4b image(width(), height());
	buw::Image4b depthImage(width(), height());

	if (!QDir::current().exists("GBuffer"))
		QDir::current().mkdir("GBuffer");

	buw::ReferenceCounted<buw::ITexture2D> backBuffer = renderSystem_->getBackBufferTarget();

	if (!backBuffer->isCPUReadable())
		backBuffer->makeCPUReadable();

	renderSystem_->downloadTexture(backBuffer, image);
	buw::storeImage("GBuffer/backBuffer.png", image);
	buw::Image4b pickImage(width(), height());
	renderSystem_->downloadTexture(pickBuffer_, image);
	for (int row = 0; row < image.getHeight(); row++) {
		for (int col = 0; col < image.getWidth(); col++) {
			UINT id;
			buw::convertR32ToUINT32(&image.getPixelColor(col, row)[0], id);			
			buw::Color4b color = id > 0 ? buw::Color4b(buw::Color3b(255, 255, 255), 255): buw::Color4b(buw::Color3b(0, 0, 0), 255);
			pickImage.setPixelColor(col, row, color);
		}
	}
	buw::storeImage("GBuffer/pickBuffer.png", pickImage);

	if (!depthStencil_->isCPUReadable())
		depthStencil_->makeCPUReadable();

	renderSystem_->downloadTexture(depthStencil_, image);
	for (int row = 0; row < image.getHeight(); row++) {
		for (int col = 0; col < image.getWidth(); col++) {
			float depth;
			buw::convertD24ToF32(&image.getPixelColor(col, row)[0], depth);
			depth = 1.0f - depth;
			buw::Color4b color = buw::Color4b(depth * 255, depth * 255, depth * 255, 255);
			depthImage.setPixelColor(col, row, color);
		}
	}
	buw::storeImage("GBuffer/depthStencil.png", depthImage);
}

void Viewport::setClearColor(const buw::Color3f& color) {
}

buw::Vector2i Viewport::getSize() const {
	return buw::Vector2i(width(), height());
}

void Viewport::goHome() {
	cameraController_->fitToView(minExtend_, maxExtend_);
}

void Viewport::toggleSnow() {
	snow_ = !snow_;
	gradientClearEffect_->toggleSnow();
	demEffect_->enableSnow(snow_);
}

void Viewport::leaveEvent(QEvent* event) {
	viewCube_->mouseMove(0, 0);
}

void Viewport::toggleCameraMode() {
	auto mode = getCameraMode();

	if (mode == buw::CameraController::eState::Orbiting) {
		setCameraMode(buw::CameraController::eState::Free);
	}
	else {
		setCameraMode(buw::CameraController::eState::Orbiting);
	}
}
void Viewport::setCameraMode(buw::CameraController::eState mode) {
	cameraController_->setState(mode);
}
buw::CameraController::eState Viewport::getCameraMode() const {
	return cameraController_->getState();
}

void Viewport::paintEvent(QPaintEvent* paintEvent) {
	// clear
	clearColor_ = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getClearColor();

	float color[] = {clearColor_.red(), clearColor_.green(), clearColor_.blue(), 0.0f};

	renderSystem_->clearRenderTargets({renderSystem_->getBackBufferTarget(), pickBuffer_}, color);
	renderSystem_->clearDepthStencilView(depthStencilMSAA_);
	renderSystem_->clearDepthStencilView(depthStencil_);

	updateWorldBuffer();

    if(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().isGradientClearEnabled())
        gradientClearEffect_->render();

    if(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().isSkyboxEnabled())
        skyboxEffect_->render();

	if (OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().isShowReferenceCoordinateSystemEnabled())
		uiElements_->render();

    for(auto effect : activeEffects_)
        effect->render();

	if (OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().isViewCubeEnabled())
		viewCube_->render();    

	renderSystem_->present();

	renderSystem_->downloadTexture(depthStencil_, depthBuffer_, 0, 0);
}

void Viewport::resizeEvent(QResizeEvent*) {
	if (renderSystem_) {
		renderSystem_->resize(width(), height());

		resizeDepthStencil();

		buw::texture2DDescription pbTD;
		pbTD.width = width();
		pbTD.height = height();
		pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
		pbTD.data = nullptr;
		pbTD.isCpuReadable = true;
		pbTD.useMSAA = false;
		pickBuffer_->resize(pbTD);

		buw::viewportDescription vpd = buw::viewportDescription(width(), height());
		viewport_->resize(vpd);
		viewCube_->resize(vpd);
		uiElements_->resize(vpd);

		camera_->frustum().width(width());
		camera_->frustum().height(height());

		depthBuffer_.resize(width(), height());

		ViewportBuffer buffer = {width(), height()};

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(ViewportBuffer);
		cbd.data = &buffer;
		viewportBuffer_->uploadData(cbd);
	}
}

void Viewport::repositionCamera() {
	if (cameraController_->getState() == buw::CameraController::eState::Orbiting) {
		auto color = depthBuffer_.getPixelColor(width() / 2, height() / 2);
		float d;
		buw::convertD24ToF32(&color, d);

		if (d < 1) {
			camera_->setOffset(d);
		}
	}
}

void Viewport::mousePressEvent(QMouseEvent* event) {
	if (event->buttons()) {
		buw::Vector2f mouse(event->x(), event->y());
		lastMousePos_ = mouse;
		viewCube_->mousePress();
        int alignmentId = alignmentEffect_->getAlignmentId(currentPickId_);
        if(alignmentId != DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment() && alignmentId != -1) {
			buw::ReferenceCounted<buw::SelectAlignment> actionSelectAlignment = std::make_shared<buw::SelectAlignment>(alignmentId);
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(actionSelectAlignment);
		}
		repositionCamera();
	}
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
	renderSystem_->downloadTexture(pickBuffer_, pickIdImage_, event->x(), event->y());
	unsigned int* id = (unsigned int*)&pickIdImage_.getPixelColor(0, 0)[0];
	currentPickId_ = *id;
	viewCube_->setPickId(currentPickId_);

	if (event->buttons()) {
		buw::Vector2f mouse(event->x(), event->y());

		buw::Vector2f m = buw::Vector2f(mouse.x() / width() * 2 - 1, 1 - mouse.y() / height() * 2);

		buw::Vector2f l = buw::Vector2f(lastMousePos_.x() / width() * 2 - 1, 1 - lastMousePos_.y() / height() * 2);

		buw::Vector2f delta = l - m;

		bool rotateCameraIfLeftMouseButtonDownAndGhostModeEnabled = (cameraController_->getState() == buw::CameraController::eState::Free) & Qt::LeftButton;
		bool rotateCameraIfLeftMouseButtonDownAndAltKeyPressed = event->buttons() & Qt::LeftButton && event->modifiers() & Qt::ALT;
		bool rotateCamera = rotateCameraIfLeftMouseButtonDownAndGhostModeEnabled || rotateCameraIfLeftMouseButtonDownAndAltKeyPressed;

		if (rotateCamera) {
			camera_->rotateCamera(buw::Vector3f(-delta.x(), delta.y(), 0));
		} else if (event->buttons() & Qt::RightButton) {
			float d = 1;
			if (lastMousePos_.x() >= 0 && lastMousePos_.x() < width() && lastMousePos_.y() >= 0 && lastMousePos_.y() < height()) {
				auto color = depthBuffer_.getPixelColor(lastMousePos_.x(), lastMousePos_.y());
				buw::convertD24ToF32(&color, d);
			}

			if (d < 1) {
				buw::Vector3f screenPos(l.x(), l.y(), d);
				camera_->panCameraScreen(delta, screenPos);
			} else
				camera_->panCameraWorld(delta);
		}

		lastMousePos_ = mouse;
	}
}

void Viewport::wheelEvent(QWheelEvent* event) {
	repositionCamera();

	float factor = pow(1.1, event->delta() / -120.f);
	cameraController_->handleWheel(factor);

	QWidget::wheelEvent(event);
}

const std::map<int, buw::CameraController::eKey> keyMap = {
  {Qt::Key_W, buw::CameraController::eKey::MoveForward}, {Qt::Key_S, buw::CameraController::eKey::MoveBackward}, {Qt::Key_D, buw::CameraController::eKey::MoveRight},
  {Qt::Key_A, buw::CameraController::eKey::MoveLeft},    {Qt::Key_Q, buw::CameraController::eKey::MoveUp},       {Qt::Key_E, buw::CameraController::eKey::MoveDown},
  {Qt::Key_1, buw::CameraController::eKey::ViewForward}, {Qt::Key_3, buw::CameraController::eKey::ViewBackward}, {Qt::Key_4, buw::CameraController::eKey::ViewRight},
  {Qt::Key_6, buw::CameraController::eKey::ViewLeft},    {Qt::Key_7, buw::CameraController::eKey::ViewUp},       {Qt::Key_9, buw::CameraController::eKey::ViewDown},
};

void Viewport::keyPressEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		if (keyMap.find(event->key()) != keyMap.end()) {
			buw::CameraController::eKey key = keyMap.at(event->key());
			cameraController_->handleKeyDown(key);
		}
	}
}
void Viewport::keyReleaseEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		if (keyMap.find(event->key()) != keyMap.end()) {
			buw::CameraController::eKey key = keyMap.at(event->key());
			cameraController_->handleKeyUp(key);
		}
	}
}

void Viewport::updateWorldBuffer() {
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

void Viewport::tick() {
	std::chrono::nanoseconds current = std::chrono::high_resolution_clock::now().time_since_epoch();
	float delta = (float)((current - lastTick_).count() * std::chrono::nanoseconds::period::num / (double)std::chrono::nanoseconds::period::den);

	cameraController_->tick(delta);
	camera_->tick(delta);

	repaint();

	lastTick_ = current;
}

void Viewport::onChange() {
	auto& data = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData();

	onChange(data.getLatesChangeFlag());
}

void Viewport::onChange(ChangeFlag changeFlag) {
	auto& data = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData();
	auto dem = data.getDigitalElevationModel();
	auto alignment = data.getAlignmentModel();
	auto trafficSignModel = data.getTrafficSignModel();
	auto girderModel = data.getGirderModel();
	auto slabFieldModel = data.getSlabFieldModel();
    auto ifcGeometryModel = data.getIfcGeometryModel();

	buw::Vector3d min, max;
	min = buw::Vector3d(-1, -1, -1);
	max = buw::Vector3d(1, 1, 1);

	if (dem && dem->getSurfaceCount() > 0)
		dem->getSurfacesExtend(min, max);
	else if (alignment && alignment->getAlignmentCount() > 0) {
		auto bb = alignment->getExtends();
		min = bb.getMinimum();
		max = bb.getMaximum();
	}

	buw::Vector3d offset = (min + max) / -2.f;
	minExtend_ = (min + offset).cast<float>();
	maxExtend_ = (max + offset).cast<float>();

	minExtend_ = buw::Vector3f(minExtend_.x(), minExtend_.z(), minExtend_.y());
	maxExtend_ = buw::Vector3f(maxExtend_.x(), maxExtend_.z(), maxExtend_.y());
	buw::Vector3d offset_data = data.getOffset();

    if(changeFlag & ChangeFlag::DigitalElevationModel && dem) {
        demEffect_->setDEM(dem, offset);
        activeEffects_.push_back(demEffect_);
    }

    if(changeFlag & ChangeFlag::AlignmentModel && alignment) {
        alignmentEffect_->setAlignment(alignment, offset);
        activeEffects_.push_back(alignmentEffect_);
    }

    if(changeFlag & ChangeFlag::IfcGeometry && ifcGeometryModel) {
        ifcGeometryEffect_->setIfcGeometryModel(ifcGeometryModel, offset);
        activeEffects_.push_back(ifcGeometryEffect_);
    }

    if(changeFlag & ChangeFlag::TrafficModel && trafficSignModel) {
        trafficSignEffect_->setData(alignment, offset, trafficSignModel);
        activeEffects_.push_back(trafficSignEffect_);
    }

	if(changeFlag & ChangeFlag::GirderModel && girderModel) {
        girderEffect_->setData(girderModel, offset);
        activeEffects_.push_back(girderEffect_);
    }

	if(changeFlag & ChangeFlag::SlabFieldModel && slabFieldModel) {
        slabFieldEffect_->setData(slabFieldModel, offset);
        activeEffects_.push_back(slabFieldEffect_);
    }

    if(changeFlag & ChangeFlag::SelectedAlignmentIndex && alignment) {
        selectedAlignmentIndex_ = data.getSelectedAlignment();
        alignmentEffect_->setCurrentSelectedAlignment(selectedAlignmentIndex_);
    }

    if(changeFlag & ChangeFlag::Preferences) {
        //TODO
    }
}

void Viewport::onClear() {
    activeEffects_.clear();
}

void Viewport::reloadShader() {
	slabFieldEffect_->loadShader();
	girderEffect_->loadShader();
	alignmentEffect_->loadShader();
	demEffect_->loadShader();
	gradientClearEffect_->loadShader();
	uiElements_->loadShader();
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END