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

#include "View.h"

#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include "BlueFramework/Rasterizer/util.h"


QIcon homeIcon, ghostSelectedIcon, ghostUnselectedIcon, snowSelectedIcon, snowUnselectedIcon;

OpenInfraPlatform::UserInterface::View::View() : QDockWidget(), // no parent
	viewport_(nullptr)
{
	//buw::renderWindowsDescription rwd =  buw::loadRenderWindowsSettings("Data/settings.xml");
	buw::eRenderAPI renderAPI;
	bool warp, msaa;
	if(buw::loadRenderSystemSettings("Data/settings.xml", renderAPI, warp, msaa))	
		createViewport(renderAPI, warp, msaa);
	else
		createViewport(buw::eRenderAPI::Direct3D11, false, true);

	QMenuBar* pMenuBar = new QMenuBar(nullptr);

	// view menu
	menuView_ = new QMenu(tr("View"));
	pMenuBar->addMenu(menuView_);
	
	
	actionTop_ = menuView_->addAction(tr("Top"));
	actionBottom_ = menuView_->addAction(tr("Bottom"));
	actionLeft_ = menuView_->addAction(tr("Left"));
	actionRight_ = menuView_->addAction(tr("Right"));
	actionFront_ = menuView_->addAction(tr("Front"));
	actionBack_ = menuView_->addAction(tr("Back"));
	
	menuView_->addSeparator();
	menuAxonometric_ = menuView_->addMenu(tr("Axonometric"));
	actionIsometric_ = menuAxonometric_->addAction(tr("Isometric"));

	// projection menu
	menuProjection_ = new QMenu(tr("Projection"));
	pMenuBar->addMenu(menuProjection_);

	actionPerspective_ = menuProjection_->addAction(tr("Perspective"));
	actionPerspective_->setCheckable(true);
	actionPerspective_->setChecked(true);
	actionOrthographic_ = menuProjection_->addAction(tr("Orthographic"));
	actionOrthographic_->setCheckable(true);

	// home menu
	homeAction_ = new QAction("", nullptr);
	homeAction_->setShortcut(QKeySequence(Qt::Key_H));

	homeIcon = QIcon("Data/home.ico");
	ghostSelectedIcon = QIcon("Data/ghost_selected.ico");
	ghostUnselectedIcon = QIcon("Data/ghost_unselected.ico");

    snowSelectedIcon = QIcon("Data/snow_selected.ico");
    snowUnselectedIcon = QIcon("Data/snow_unselected.ico");

	if (homeIcon.isNull() || ghostSelectedIcon.isNull() || ghostUnselectedIcon.isNull())
	{
		BLUE_LOG(warning) << "Could not load icon from.";
	}
	else
	{
		homeAction_->setIcon(homeIcon);
	}

	cameraGhostModeAction_ = new QAction("", nullptr);
	cameraGhostModeAction_->setShortcut(QKeySequence(Qt::Key_T));

    snowAction_ = new QAction("", nullptr);
    snowAction_->setIcon(snowUnselectedIcon);

	QMenuBar* rightBar = new QMenuBar();
	rightBar->setObjectName("transparent");

	rightBar->addAction(homeAction_);
	rightBar->addAction(cameraGhostModeAction_);

#if _DEBUG
	rightBar->addAction(snowAction_); // ignore date in Debug mode
#else
	QDateTime now = QDateTime::currentDateTime();
	if ((now.date().month() == 12 && now.date().day() >= 22) ||
		(now.date().month() == 1 && now.date().day() <= 10) /*|| true*/) {
		rightBar->addAction(snowAction_);
	}
#endif
		
	pMenuBar->setCornerWidget(rightBar);

	setTitleBarWidget(pMenuBar);

	cameraControlModeChanged();

	QObject::connect(homeAction_, &QAction::triggered, this, &View::on_home);
	QObject::connect(cameraGhostModeAction_, &QAction::triggered, this, &View::on_actionToggleCameraGhostMode);
    QObject::connect(snowAction_, &QAction::triggered, this, &View::on_actionToggleSnow);

	setFeatures(DockWidgetFeature::NoDockWidgetFeatures);

	QObject::connect(actionPerspective_, &QAction::triggered, this, &View::on_actionPerspective);
	QObject::connect(actionOrthographic_, &QAction::triggered, this, &View::on_actionOrthographic);
	QObject::connect(actionLeft_, &QAction::triggered, this, &View::on_actionLeft);
	QObject::connect(actionRight_, &QAction::triggered, this, &View::on_actionRight);
	QObject::connect(actionFront_, &QAction::triggered, this, &View::on_actionFront);
	QObject::connect(actionBack_, &QAction::triggered, this, &View::on_actionBack);
	QObject::connect(actionTop_, &QAction::triggered, this, &View::on_actionTop);
	QObject::connect(actionBottom_, &QAction::triggered, this, &View::on_actionBottom);
	QObject::connect(actionIsometric_, &QAction::triggered, this, &View::on_actionIsometric);

	BLUE_LOG(trace) << "End of View ctor";
}

OpenInfraPlatform::UserInterface::View::~View()
{
	delete viewport_;
}


void OpenInfraPlatform::UserInterface::View::createViewport(const buw::eRenderAPI renderAPI, bool warp, bool msaa)
{
	setWidget(nullptr);

	if (viewport_)
		delete viewport_;

	renderAPI_ = renderAPI;
	forceWarpDevice_ = warp;
	enableMSAA_ = msaa;

	viewport_ = new Viewport(renderAPI_, forceWarpDevice_, enableMSAA_, this);
	setWidget(viewport_);

	viewport_->resize(width(), height());
	viewport_->onChange((DataManagement::ChangeFlag)~0);
}


void OpenInfraPlatform::UserInterface::View::getViewportSettings(buw::eRenderAPI& renderAPI, bool& warp, bool& msaa)
{
	renderAPI = renderAPI_;
	warp = forceWarpDevice_;
	msaa = enableMSAA_;
}

void OpenInfraPlatform::UserInterface::View::changeEvent(QEvent* evt)
{
	if (evt->type() == QEvent::LanguageChange)
	{
		retranslateView();
	}
	else
	{
		// remember to call base class implementation
		QDockWidget::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::View::retranslateView()
{
	menuView_->setTitle(tr("View"));

	actionTop_->setText(tr("Top"));
	actionBottom_->setText(tr("Bottom"));
	actionLeft_->setText(tr("Left"));
	actionRight_->setText(tr("Right"));
	actionFront_->setText(tr("Front"));
	actionBack_->setText(tr("Back"));

	menuAxonometric_->setTitle(tr("Axonometric"));
	actionIsometric_->setText(tr("Isometric"));

	menuProjection_->setTitle(tr("Projection"));

	actionPerspective_->setText(tr("Perspective"));
	actionOrthographic_->setText(tr("Orthographic"));
}

void OpenInfraPlatform::UserInterface::View::rotate(buw::Vector2f value)
{
    //viewport_->getInfraCameraController()->rotate(value);
}

void OpenInfraPlatform::UserInterface::View::on_actionIsometric()
{
	//viewport_->viewDirection(buw::Vector3f(1, 1, 1));
}

void OpenInfraPlatform::UserInterface::View::on_actionBottom()
{
	viewport_->viewDirection(buw::Vector3f(0, -1, 0));
}

void OpenInfraPlatform::UserInterface::View::on_actionTop()
{
	viewport_->viewDirection(buw::Vector3f(0, 1, 0));
}

void OpenInfraPlatform::UserInterface::View::on_actionBack()
{
	viewport_->viewDirection(buw::Vector3f(0, 0, -1));
}

void OpenInfraPlatform::UserInterface::View::on_actionFront()
{
	viewport_->viewDirection(buw::Vector3f(0, 0, 1));
}

void OpenInfraPlatform::UserInterface::View::on_actionRight()
{
	viewport_->viewDirection(buw::Vector3f(1, 0, 0));
}

void OpenInfraPlatform::UserInterface::View::on_actionLeft()
{
	viewport_->viewDirection(buw::Vector3f(-1, 0, 0));
}

void OpenInfraPlatform::UserInterface::View::on_actionOrthographic()
{
	actionPerspective_->setChecked(false);
	actionOrthographic_->setChecked(true);
	//viewport_->setProjectionType(buw::eProjectionType::Orthographic);
}

void OpenInfraPlatform::UserInterface::View::on_actionPerspective()
{
	actionPerspective_->setChecked(true);
	actionOrthographic_->setChecked(false);
	//viewport_->setProjectionType(buw::eProjectionType::Perspective);
}

int OpenInfraPlatform::UserInterface::View::getViewportHeight() const
{
	return viewport_->height();
}

int OpenInfraPlatform::UserInterface::View::getViewportWidth() const
{
	return viewport_->width();
}

buw::Vector2i OpenInfraPlatform::UserInterface::View::getSize() const
{
	return viewport_->getSize();
}

void OpenInfraPlatform::UserInterface::View::setViewportSize(const int width, const int height)
{
	viewport_->resize(width, height);
}

void OpenInfraPlatform::UserInterface::View::saveAsScreenshot( const std::string& filename )
{
	viewport_->saveAsScreenshot(filename);
}

buw::Vector3d OpenInfraPlatform::UserInterface::View::getOffset() const
{
	return buw::Vector3d(); //viewport_->getOffset();
}

void OpenInfraPlatform::UserInterface::View::setDifferentColorsForAlignmentElements( const bool checked )
{
	viewport_->setDifferentColorsForAlignmentElements(checked);
}

void OpenInfraPlatform::UserInterface::View::setHighlightSelectedAlignmentSegment( const bool enable )
{
	viewport_->setHighlightSelectedAlignmentSegment(enable);
}

void OpenInfraPlatform::UserInterface::View::setUseUniformPointColor(const bool useUniformColor)
{
	//viewport_->setUseUniformPointColor(useUniformColor);
}

void OpenInfraPlatform::UserInterface::View::setUseUniformPointSize(const bool useUniformSize)
{
	//viewport_->setUseUniformPointSize(useUniformSize);
}

void OpenInfraPlatform::UserInterface::View::setPointSize(const float pointSize)
{
	//viewport_->setPointSize(pointSize);
}


std::vector<buw::Vector3d> OpenInfraPlatform::UserInterface::View::getAlignmentPoints()
{
	return std::vector<buw::Vector3d>(); // viewport_->getAlignmentPoints();
}

void OpenInfraPlatform::UserInterface::View::enableCreatePoints( const bool enable )
{
	//viewport_->enableCreatePoints(enable);
}

void OpenInfraPlatform::UserInterface::View::enableTerrainTextured( const bool enable )
{
	viewport_->enableTerrainTextured( enable );
}

void OpenInfraPlatform::UserInterface::View::enableTerrainGradientRamp(const bool enable)
{
	viewport_->enableTerrainGradientRamp(enable);
}

void OpenInfraPlatform::UserInterface::View::enableIsoLines(const bool enable)
{
	viewport_->enableIsoLines(enable);
}

void OpenInfraPlatform::UserInterface::View::showCrossSection( const bool showCrossSection )
{
	viewport_->showCrossSection(showCrossSection);
}

void OpenInfraPlatform::UserInterface::View::showDesignCrossSection(const bool showDesignCrossSection)
{
	viewport_->showDesignCrossSection(showDesignCrossSection);
}

void OpenInfraPlatform::UserInterface::View::showRoadBodyWireframe(const bool connectCrossSections)
{
	viewport_->showRoadBodyWireframe(connectCrossSections);
}

void OpenInfraPlatform::UserInterface::View::showRoadBodySolid(const bool solidCrossSections)
{
	viewport_->showRoadBodySolid(solidCrossSections);
}

void OpenInfraPlatform::UserInterface::View::drawRoadTexture(const bool drawRoadTexture)
{
	viewport_->enableRoadBodyTextured(drawRoadTexture);
}

void OpenInfraPlatform::UserInterface::View::setView( eView viewType )
{
	viewport_->setView(viewType);
}

void OpenInfraPlatform::UserInterface::View::enableHideTerrain( const bool enable )
{
	viewport_->setHideTerrain(enable);
}

void OpenInfraPlatform::UserInterface::View::storeGBuffer()
{
	viewport_->storeGBuffer();
}

void OpenInfraPlatform::UserInterface::View::enableDrawTerrainWireframe( const bool enable )
{
	viewport_->setDrawTerrainWireframe(enable);
}

void OpenInfraPlatform::UserInterface::View::enableBlueMap( const bool checked )
{
	//setWidget(viewport_->enableBlueMap( checked ));
}

//void OpenInfraPlatform::UserInterface::View::onViewCubeSelectionChanged(buw::eViewCubeOrientation::Enum state)
//{
//	switch (state)
//	{
//	case BlueFramework::Engine::eViewCubeOrientation::Unselected:
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopLeftFrontView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, 1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopFrontView:
//		{
//			viewport_->viewDirection(buw::Vector3f(0, 1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopFrontRightView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, 1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontLeftView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, 0, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontView:
//		{
//			on_actionFront();
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontRightView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, 0, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontLeftBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, -1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(0, -1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::FrontRightBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, -1, 1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopRightView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, 1, 0));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopRightBackView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, 1, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::RightView:
//		{
//			on_actionRight();
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::RightBackView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, 0, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::RightBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, -1, 0));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::RightBottomBackView:
//		{
//			viewport_->viewDirection(buw::Vector3f(1, -1, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopBackView:
//		{
//			viewport_->viewDirection(buw::Vector3f(0, 1, -1));			
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopLeftBackView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, 1, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::BackView:
//		{
//			on_actionBack();
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::BackLeftView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, 0, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::BackBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(0, -1, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::BackLeftBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, -1, -1));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopLeftView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, 1, 0));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::LeftView:
//		{
//			on_actionLeft();
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::LeftBottomView:
//		{
//			viewport_->viewDirection(buw::Vector3f(-1, -1, 0));
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::TopView:
//		{
//			on_actionTop();
//		}
//		break;
//	case BlueFramework::Engine::eViewCubeOrientation::BottomView:
//		{
//			on_actionBottom();
//		}
//		break;
//	default:
//		break;
//	}
//}

OpenInfraPlatform::UserInterface::Viewport* OpenInfraPlatform::UserInterface::View::getViewport()
{
    return viewport_;
}

//void OpenInfraPlatform::UserInterface::View::setInfraCameraController(buw::ReferenceCounted<buw::InfraCameraController> controller)
//{
//	viewport_->setInfraCameraController(controller);
//}
//
//buw::ReferenceCounted<buw::InfraCameraController> OpenInfraPlatform::UserInterface::View::getInfraCameraController() const
//{
//	return viewport_->getInfraCameraController();
//}


void OpenInfraPlatform::UserInterface::View::reloadShader()
{
	viewport_->reloadShader();
}

void OpenInfraPlatform::UserInterface::View::on_home()
{
	viewport_->goHome();
	cameraControlModeChanged();
}

void OpenInfraPlatform::UserInterface::View::on_actionToggleCameraGhostMode()
{
	viewport_->toggleCameraMode();
	cameraControlModeChanged();
}

void OpenInfraPlatform::UserInterface::View::on_actionToggleSnow()
{
    viewport_->toggleSnow();
    viewport_->repaint();
    if(snowSelectedIcon.isDetached())
        snowAction_->setIcon(snowSelectedIcon);
    else
        snowAction_->setIcon(snowUnselectedIcon);
}


void OpenInfraPlatform::UserInterface::View::cameraControlModeChanged()
{
	if(viewport_->getCameraMode() == buw::CameraController::eState::Free)
		cameraGhostModeAction_->setIcon(ghostSelectedIcon);
	else
		cameraGhostModeAction_->setIcon(ghostUnselectedIcon);
}

void OpenInfraPlatform::UserInterface::View::showFrameTimes(const bool show)
{
	//viewport_->showFrameTimes(show);
}

void OpenInfraPlatform::UserInterface::View::LoadBridge()
{
	//viewport_->LoadBridge();
}
