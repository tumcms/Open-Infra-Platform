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

#include "VerticalAlignmentWindow.h"
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsTextItem>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QtSvg/QSvgGenerator>
#include <cmath>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

VerticalAlignmentScene::VerticalAlignmentScene(QObject* parent) : Alignment2DScene(parent), displayPoints_(false) {
	configureColors(A2D_DrawState::A2D_Draw);
}

void VerticalAlignmentScene::v_configureColors(A2D_DrawState state) {
	switch (state) {
	case A2D_DrawState::A2D_Draw: terrainPen = QPen(Qt::yellow); break;

	case A2D_DrawState::A2D_Print: terrainPen = QPen(Qt::darkYellow); break;
	}
	terrainPen.setWidth(1);
	terrainPen.setCosmetic(true);
}

void VerticalAlignmentScene::v_drawAlignment(buw::ReferenceCounted<buw::Alignment2DBased3D> a,
                                             std::map<buw::eHorizontalAlignmentType, QPainterPath>& horizontalPainter,
                                             std::map<buw::eVerticalAlignmentType, QPainterPath>& verticalPainter) {
	buw::ReferenceCounted<buw::HorizontalAlignment2D> h = a->getHorizontalAlignment();
	buw::ReferenceCounted<buw::VerticalAlignment2D> v = a->getVerticalAlignment();

	if (v != nullptr) {
		auto start = v->getPosition(v->getStartStation());
		auto end = v->getPosition(v->getEndStation());

		bounds[0] = bounds[1] = start.x();
		bounds[2] = bounds[3] = -start.y();

		double prevX = bounds[0], prevY = bounds[2];
		buw::eHorizontalAlignmentType lastType = buw::eHorizontalAlignmentType::Unknown;
		buw::eVerticalAlignmentType lastVerticalType = buw::eVerticalAlignmentType::Unknown;

		verticalPainter[lastVerticalType].moveTo(prevX, prevY);
		horizontalPainter[lastType].moveTo(prevX, prevY);

		for (double s = v->getStartStation(); s < v->getEndStation(); s += 0.8) {
			auto position = v->getPosition(s);
			double x = position.x();
			double y = -position.y();

			if (differentColorsForVerticalAlignmentElements_) {
				auto ve = v->getAlignmentElementByStationing(s);
				buw::eVerticalAlignmentType type = ve->getAlignmentType();

				if (ve != nullptr) {
					if (verticalPainter.find(type) == verticalPainter.end())
						verticalPainter[type] = QPainterPath();

					if (lastVerticalType != type)
						verticalPainter[type].moveTo(prevX, prevY);
					verticalPainter[type].lineTo(x, y);
				}

				lastVerticalType = type;
			} else if (differentColorsForHorizontalAlignmentElements_) {
				auto he = h->getAlignmentElementByStationing(s);
				buw::eHorizontalAlignmentType type = he->getAlignmentType();

				if (horizontalPainter.find(type) == horizontalPainter.end())
					horizontalPainter[type] = QPainterPath();

				if (lastType != type)
					horizontalPainter[type].moveTo(prevX, prevY);
				horizontalPainter[type].lineTo(x, y);

				lastType = type;
			} else {
				buw::eHorizontalAlignmentType type = buw::eHorizontalAlignmentType::Unknown;
				if (horizontalPainter.find(type) == horizontalPainter.end())
					horizontalPainter[type] = QPainterPath();

				horizontalPainter[type].lineTo(x, y);

				lastType = type;
			}

			bounds[0] = std::min(bounds[0], x);
			bounds[1] = std::max(bounds[1], x);
			bounds[2] = std::min(bounds[2], y);
			bounds[3] = std::max(bounds[3], y);

			prevX = x;
			prevY = y;
		}

		arcPoints_.clear();
		parabolaPoints_.clear();

		for (int ai = 0; ai < v->getAlignmentElementCount(); ai++) {
			auto ve = v->getAlignmentElementByIndex(ai);

			if (ve->getAlignmentType() == buw::eVerticalAlignmentType::Arc) {
				buw::Vector2d start;
				ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);

				buw::Vector2d end;
				ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);

				start[1] *= -1;
				end[1] *= -1;

				arcPoints_.push_back(std::make_tuple(ai, start, end));
			}
			if (ve->getAlignmentType() == buw::eVerticalAlignmentType::Parabola) {
				buw::Vector2d start;
				ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartPosition, &start);

				buw::Vector2d end;

				ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::EndPosition, &end);
				buw::Vector2d pvi;
				ve->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PVI, &pvi);

				// we invert here since the convex/concave definition in IFC has been changed...
				start[1] *= -1;
				end[1] *= -1;
				pvi[1] *= -1;

				parabolaPoints_.push_back(std::make_tuple(ai, start, end, pvi));
			}
		}
	}
}

void VerticalAlignmentScene::loadSurfaceProfile() {
	clearSurfaceProfile();

	auto alignment = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel();

	buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment->getAlignment(selectedAlignmentIndex_));

	auto profile = model_->getSurfaceProfile(a);

	bool reset = true;

	for (std::pair<double, double> sz : profile) {
		double x = std::get<0>(sz);
		double y = -std::get<1>(sz);
		if (y != 0) {
			if (reset)
				terrainPainter.moveTo(x, y);
			else
				terrainPainter.lineTo(x, y);
			reset = false;
		} else
			reset = true;
	}

	scale();
}

void VerticalAlignmentScene::v_drawDiagram(QPainterPath& diagPainter, QPainterPath& diagDashedPainter) {
	QString text;

	if (displayPoints_) {
		for (int i = 0; i < arcPoints_.size(); i++) {
			buw::Vector2d start, end;
			int ai = std::get<0>(arcPoints_[i]);
			start = std::get<1>(arcPoints_[i]);
			end = std::get<2>(arcPoints_[i]);

			text = "AA" + QString::number(ai + 1) + " (" + QString::number(start.x()) + "," + QString::number(-start.y()) + ")";
			
			auto startLabel = addText(text, diagramFont);
			startLabel->setPos(start.x() * scalingX, start.y() * scalingY - 25);
			startLabel->setDefaultTextColor(Qt::lightGray);

			diagDashedPainter.moveTo(start.x() * scalingX, start.y() * scalingY);
			diagDashedPainter.lineTo(start.x() * scalingX, bounds[3] * scalingY + 5);

			text = "AE" + QString::number(ai + 1) + " (" + QString::number(end.x()) + "," + QString::number(-end.y()) + ")";
			auto endLabel = addText(text, diagramFont);
			endLabel->setPos(end.x() * scalingX, end.y() * scalingY - 25);
			endLabel->setDefaultTextColor(Qt::red);

			diagDashedPainter.moveTo(end.x() * scalingX, end.y() * scalingY);
			diagDashedPainter.lineTo(end.x() * scalingX, bounds[3] * scalingY + 5);
		}
		for (int i = 0; i < parabolaPoints_.size(); i++) {
			buw::Vector2d start, end, pvi;
			int ai = std::get<0>(parabolaPoints_[i]);
			start = std::get<1>(parabolaPoints_[i]);
			end = std::get<2>(parabolaPoints_[i]);
			pvi = std::get<3>(parabolaPoints_[i]);

			text = "AA" + QString::number(ai + 1) + " (" + QString::number(start.x()) + "," + QString::number(-start.y()) + ")";
			
			auto startLabel = addText(text, diagramFont);
			startLabel->setPos(start.x() * scalingX, start.y() * scalingY - 25);
			startLabel->setDefaultTextColor(Qt::lightGray);

			diagDashedPainter.moveTo(start.x() * scalingX, start.y() * scalingY);
			diagDashedPainter.lineTo(start.x() * scalingX, bounds[3] * scalingY + 5);

			text = "AE" + QString::number(ai + 1) + " (" + QString::number(end.x()) + "," + QString::number(-end.y()) + ")";
			auto endLabel = addText(text, diagramFont);
			endLabel->setPos(end.x() * scalingX, end.y() * scalingY - 25);
			endLabel->setDefaultTextColor(Qt::lightGray);
			
			diagDashedPainter.moveTo(end.x() * scalingX, end.y() * scalingY);
			diagDashedPainter.lineTo(end.x() * scalingX, bounds[3] * scalingY + 5);

			text = "VB" + QString::number(ai + 1);
			
			auto pviLabel = addText(text, diagramFont);
			pviLabel->setPos(pvi.x() * scalingX, pvi.y() * scalingY - 25);
			pviLabel->setDefaultTextColor(Qt::lightGray);

			diagDashedPainter.moveTo(pvi.x() * scalingX, pvi.y() * scalingY);
			diagDashedPainter.lineTo(pvi.x() * scalingX, bounds[3] * scalingY + 5);
		}
	}
}

void VerticalAlignmentScene::v_addPaths() {
	addPath(scaledPainterPath(&terrainPainter, scalingX, scalingY), terrainPen, transparentBrush);
}

void VerticalAlignmentScene::setDigitalElevationModel(buw::ReferenceCounted<buw::DigitalElevationModel> model) {
	model_ = model;
}

void VerticalAlignmentScene::displayPoints(bool display) {
	displayPoints_ = display;
	scale();
}

void VerticalAlignmentScene::clearSurfaceProfile() {
	terrainPainter = QPainterPath();
}

// Window

VerticalAlignmentWindow::VerticalAlignmentWindow(QAction* act) : ui_(new Ui::VerticalAlignment()), action_(act), scene_(new VerticalAlignmentScene(this)), QDockWidget() {
	ui_->setupUi(this);
	ui_->verticalAlignmentView->setScene(scene_);

	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change.connect(boost::bind(&VerticalAlignmentWindow::onChange, this));
}

void VerticalAlignmentWindow::onChange() {
	auto& data = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData();
	auto alignmentModel = data.getAlignmentModel();
	auto elevationModel = data.getDigitalElevationModel();

	OpenInfraPlatform::DataManagement::ChangeFlag flag = data.getLatesChangeFlag();

	if (flag & OpenInfraPlatform::DataManagement::ChangeFlag::Preferences || flag & OpenInfraPlatform::DataManagement::ChangeFlag::AlignmentModel) {
		
		if (alignmentModel->getAlignmentCount() > 0)
			scene_->setAlignment(alignmentModel);
		else
			scene_->setAlignment(nullptr);
	}

	if (flag & OpenInfraPlatform::DataManagement::ChangeFlag::DigitalElevationModel) {
		scene_->setDigitalElevationModel(elevationModel);
	}

	if (flag & OpenInfraPlatform::DataManagement::ChangeFlag::Preferences || flag & OpenInfraPlatform::DataManagement::ChangeFlag::SelectedAlignmentIndex) {
		int index = data.getSelectedAlignment();
		if (index >= 0) {
			if (scene_) {
				scene_->clearSurfaceProfile();
				scene_->setSelectedAlignment(index);
				scene_->fit(1000);
			}

			QString name = "";
			if (alignmentModel->getAlignmentCount() > 0)
				name = QString::fromStdWString(alignmentModel->getAlignment(index)->getName().toWStdString());

			setWindowTitle("Vertical Alignment - " + name);
		}
	}
}

void VerticalAlignmentWindow::setDifferentColorsForHorizontalAlignmentElements(const bool checked) {
	if (scene_)
		scene_->setDifferentColorsForHorizontalAlignmentElements(checked);
}

void VerticalAlignmentWindow::setDifferentColorsForVerticalAlignmentElements(const bool checked) {
	if (scene_)
		scene_->setDifferentColorsForVerticalAlignmentElements(checked);
}

void VerticalAlignmentWindow::on_loadSurfaceProfileButton_clicked() {
	scene_->loadSurfaceProfile();
}

void VerticalAlignmentWindow::on_displayPointsCheckBox_clicked(bool checked) {
	scene_->displayPoints(checked);
}

void VerticalAlignmentWindow::closeEvent(QCloseEvent* event) {
	if (action_)
		action_->setChecked(false);
}

void VerticalAlignmentWindow::exportToFile() {
	scene_->exportToFile(this);
}

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END
