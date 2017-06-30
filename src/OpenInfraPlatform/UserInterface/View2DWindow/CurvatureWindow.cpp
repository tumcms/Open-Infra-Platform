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

#include "CurvatureWindow.h"
#include "OpenInfraPlatform\Infrastructure\Alignment\HorizontalAlignment\HorizontalAlignmentElement2DLine.h"
#include "OpenInfraPlatform\Infrastructure\Alignment\HorizontalAlignment\HorizontalAlignmentElement2DArc.h"
#include "OpenInfraPlatform\Infrastructure\Alignment\HorizontalAlignment\HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform\Infrastructure\Alignment\HorizontalAlignment\HorizontalAlignmentElement2DBlossCurve.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneWheelEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QtSvg/QSvgGenerator>
#include <math.h>

OpenInfraPlatform::UserInterface::CurvatureScene::CurvatureScene(QObject *parent)
	: Alignment2DScene(parent)
{
	scalingX = 5;
	ratio = buw::Vector2d(200, 1);
	scalingY = scalingX * ratio.x() / ratio.y();
}

void OpenInfraPlatform::UserInterface::CurvatureScene::v_drawAlignment(
	buw::ReferenceCounted<buw::Alignment2DBased3D> a,
	std::map<buw::eHorizontalAlignmentType, QPainterPath>& horizontalPainter,
	std::map<buw::eVerticalAlignmentType, QPainterPath>& verticalPainter)
{
	buw::ReferenceCounted<buw::HorizontalAlignment2D> h = a->getHorizontalAlignment();
	buw::ReferenceCounted<buw::VerticalAlignment2D> v = a->getVerticalAlignment();

	bounds[0] = std::numeric_limits<double>().max();
	bounds[1] = std::numeric_limits<double>().min();
	bounds[2] = bounds[3] = 0;

	double lastX = h->getStartStation();


	for(int i=0; i<h->getAlignmentElementCount(); i++)
	{
		auto element = h->getAlignmentElementByIndex(i);
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line;
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DArc> arc;
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid;
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> bloss;

		buw::eHorizontalAlignmentType type = element->getAlignmentType();

		double sX, eX, sY, eY;
		switch(element->getAlignmentType())
		{
		case buw::eHorizontalAlignmentType::Line:
			line = std::static_pointer_cast<buw::HorizontalAlignmentElement2DLine>(element);
			sX = lastX;
			eX = line->getLength() + lastX;


			if (!differentColorsForHorizontalAlignmentElements_)
				type = buw::eHorizontalAlignmentType::Unknown;

			horizontalPainter[type].moveTo(sX, 0);
			horizontalPainter[type].lineTo(eX, 0);

			bounds[0] = std::min(bounds[0],sX);
			bounds[0] = std::min(bounds[0],eX);
			bounds[1] = std::max(bounds[1],sX);
			bounds[1] = std::max(bounds[1],eX);
			
			bounds[2] = std::min(bounds[2],0.0);
			bounds[3] = std::max(bounds[3],0.0);
			break;

		case buw::eHorizontalAlignmentType::Arc:
			arc = std::static_pointer_cast<buw::HorizontalAlignmentElement2DArc>(element);
			sX = lastX;
			eX = arc->getLength() + lastX;
			sY = arc->getCurvature();

			if (!differentColorsForHorizontalAlignmentElements_)
				type = buw::eHorizontalAlignmentType::Unknown;

			horizontalPainter[type].moveTo(sX, sY);
			horizontalPainter[type].lineTo(eX, sY);

			bounds[0] = std::min(bounds[0],sX);
			bounds[0] = std::min(bounds[0],eX);
			bounds[1] = std::max(bounds[1],sX);
			bounds[1] = std::max(bounds[1],eX);
			
			bounds[2] = std::min(bounds[2],sY);
			bounds[3] = std::max(bounds[3],sY);
			break;

		case buw::eHorizontalAlignmentType::Clothoid:
			clothoid = std::static_pointer_cast<buw::HorizontalAlignmentElement2DClothoid>(element);
			sX = lastX;
			eX = clothoid->getLength() + lastX;
			sY = clothoid->getStartCurvature() * (clothoid->isCounterClockwise() ? 1 : -1);
			eY = clothoid->getEndCurvature() * (clothoid->isCounterClockwise() ? 1 : -1);

			if (!differentColorsForHorizontalAlignmentElements_)
				type = buw::eHorizontalAlignmentType::Unknown;

			horizontalPainter[type].moveTo(sX, sY);
			horizontalPainter[type].lineTo(eX, eY);

			bounds[0] = std::min(bounds[0],sX);
			bounds[0] = std::min(bounds[0],eX);
			bounds[1] = std::max(bounds[1],sX);
			bounds[1] = std::max(bounds[1],eX);
			
			bounds[2] = std::min(bounds[2],sY);
			bounds[2] = std::min(bounds[2],eY);
			bounds[3] = std::max(bounds[3],sY);
			bounds[3] = std::max(bounds[3],eY);
			break;

		case buw::eHorizontalAlignmentType::Bloss:
			bloss = std::static_pointer_cast<buw::HorizontalAlignmentElement2DBlossCurve>(element);
			
			sX = lastX;
			sY = bloss->getStartCurvature() * (bloss->isCounterClockwise() ? 1 : -1);

			if (!differentColorsForHorizontalAlignmentElements_)
				type = buw::eHorizontalAlignmentType::Unknown;

			horizontalPainter[type].moveTo(sX, sY);

			for (double s = 0; s <= bloss->getLength(); s += 0.8)
			{				
				eX = s + lastX;
				eY = bloss->getCurvature(s / bloss->getLength()) * (bloss->isCounterClockwise() ? 1 : -1);
				
				horizontalPainter[type].lineTo(eX, eY);
			}

			

			bounds[0] = std::min(bounds[0], sX);
			bounds[0] = std::min(bounds[0], eX);
			bounds[1] = std::max(bounds[1], sX);
			bounds[1] = std::max(bounds[1], eX);

			bounds[2] = std::min(bounds[2], sY);
			bounds[2] = std::min(bounds[2], eY);
			bounds[3] = std::max(bounds[3], sY);
			bounds[3] = std::max(bounds[3], eY);
			break;

		default:
			eX = 0;
			break;
		}

		lastX = eX;
	}
}

//void OpenInfraPlatform::UserInterface::CurvatureScene::drawDiagram(QPainterPath& diagPainter)
//{
//	QString text;
//
//	// X-Axis
//	int width = 50;
//	
//	diagPainter.moveTo(bounds[0], bounds[3] + 10);
//	diagPainter.lineTo(bounds[1] + 20, bounds[3] + 10);
//
//	diagPainter.moveTo(bounds[0], 0);
//	diagPainter.lineTo(bounds[1] + 20, 0);
//
//	int stepX = getBestStep(bounds[1] - bounds[0], 1, 100, 15);
//
//	for(double x = (int)(bounds[0] / stepX) * stepX; x<=bounds[1] + 20; x+= stepX)
//	{
//		int kilometer = (double)(x / 1000 / scalingX);
//		int meter = (double)(x / scalingX) - kilometer * 1000;
//		diagPainter.moveTo(x, bounds[3] + 10);
//		diagPainter.lineTo(x, bounds[3] + 10 + width);
//
//		
//		QString sign = meter >= 0? "+" : "-";
//		if(meter / 100 == 0)
//			sign += "0";
//		if(meter / 10 == 0)
//			sign += "0";
//		text = QString::number(kilometer) + sign + QString::number(std::abs(meter));
//		auto stationLabel = addText(text, diagramFont);
//		stationLabel->setPos(x + 3, bounds[3] + 20 );
//		stationLabel->setDefaultTextColor(diagramFontColor);
//	}
//
//
//	// Y-Axis
//	diagPainter.moveTo(bounds[0] - 20, bounds[3] + 20);
//	diagPainter.lineTo(bounds[0] - 20, bounds[2] - 20);
//
//	double stepY = getBestStep(bounds[3] - bounds[2], 1, 50, 5);
//
//	for(double y = (int)(bounds[3] / stepY) * stepY; y>=bounds[2] - 20; y-= stepY)
//	{
//		diagPainter.moveTo(bounds[0] - 20, y);
//		diagPainter.lineTo(bounds[0] - 20 - width,  y);
//
//		text = QString::number(-y / scalingY, 'f',2);
//		auto stationLabel = addText(text, diagramFont);
//		stationLabel->setPos(bounds[0]  - 20 - width, y - QFontMetrics(diagramFont).height() - 4);
//		stationLabel->setDefaultTextColor(diagramFontColor);
//	}
//
//	// Scaling
//
//	text = getRatio(scalingY / scalingX, 1);
//	auto ratioLabel = addText(text, diagramFont);
//	ratioLabel->setPos(bounds[0], bounds[2] - 20);
//	ratioLabel->setDefaultTextColor(diagramFontColor);
//}


OpenInfraPlatform::UserInterface::CurvatureWindow::CurvatureWindow(QAction* act) 
	: ui_(new Ui::Curvature),
	action_(act),
	scene_(new CurvatureScene(this)),
	QDockWidget()
{
	ui_->setupUi(this);
    ui_->curvatureView->setScene(scene_);

	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change.connect(boost::bind(&CurvatureWindow::onChange, this));
}

void OpenInfraPlatform::UserInterface::CurvatureWindow::onChange()
{
	auto& data = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData();
	auto alignmentModel = data.getAlignmentModel();
	auto elevationModel = data.getDigitalElevationModel();

	OpenInfraPlatform::DataManagement::ChangeFlag flag = data.getLatesChangeFlag();

	if (flag & OpenInfraPlatform::DataManagement::ChangeFlag::Preferences || 
		flag & OpenInfraPlatform::DataManagement::ChangeFlag::AlignmentModel)
	{
		if (alignmentModel->getAlignmentCount() > 0)
			scene_->setAlignment(alignmentModel);
		else
			scene_->setAlignment(nullptr);
	}

	if ((flag & OpenInfraPlatform::DataManagement::ChangeFlag::Preferences) ||
		(flag & OpenInfraPlatform::DataManagement::ChangeFlag::SelectedAlignmentIndex))
	{
		int index = data.getSelectedAlignment();
		if (index >= 0)
		{
			if (scene_)
			{
				scene_->setSelectedAlignment(index);
				scene_->fit(1000);
			}

			QString name = "";
			if (alignmentModel->getAlignmentCount() > 0)
				name = QString::fromStdWString(alignmentModel->getAlignment(index)->getName().toWStdString());
				
			setWindowTitle("Curvature - " + name);			
		}
	}
}


void OpenInfraPlatform::UserInterface::CurvatureWindow::setDifferentColorsForHorizontalAlignmentElements(bool checked)
{
	if(scene_)
		scene_->setDifferentColorsForHorizontalAlignmentElements(checked);
}

void OpenInfraPlatform::UserInterface::CurvatureWindow::setDifferentColorsForVerticalAlignmentElements(const bool checked)
{
	if (scene_)
		scene_->setDifferentColorsForVerticalAlignmentElements(checked);
}

void OpenInfraPlatform::UserInterface::CurvatureWindow::exportToFile()
{
	scene_->exportToFile(this);
}

void OpenInfraPlatform::UserInterface::CurvatureWindow::closeEvent(QCloseEvent *event)
{
	if (action_)
		action_->setChecked(false);
}
