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

#include "Alignment2DScene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneWheelEvent>
#include <QDesktopWidget>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QtSvg/QSvgGenerator>
#include <math.h>

OpenInfraPlatform::UserInterface::Alignment2DScene::Alignment2DScene(QObject *parent)
	: QGraphicsScene(parent),
transparentBrush(Qt::transparent),
differentColorsForHorizontalAlignmentElements_(false),
differentColorsForVerticalAlignmentElements_(false),
selectedAlignmentIndex_(0)
{
	scalingX = 5;
	ratio = buw::Vector2d(10, 1);
	scalingY = scalingX * ratio.x() / ratio.y();

	configureColors(A2D_DrawState::A2D_Draw);
	
	diagramFont.setPixelSize(15);
	diagramFont.setBold(false);
	diagramFont.setFamily("Calibri");
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::configureColors(const A2D_DrawState state)
{
	switch(state)
	{
	case A2D_DrawState::A2D_Draw:

		horizontalPens[buw::eHorizontalAlignmentType::Line] = QPen(QColor(144, 238, 144));
		horizontalPens[buw::eHorizontalAlignmentType::Arc] = QPen(QColor(255, 0, 0));
		horizontalPens[buw::eHorizontalAlignmentType::Clothoid] = QPen(QColor(255, 255,0));
		horizontalPens[buw::eHorizontalAlignmentType::Bloss] = QPen(QColor(139, 35, 35));
		horizontalPens[buw::eHorizontalAlignmentType::Unknown] = QPen(Qt::white);

		verticalPens[buw::eVerticalAlignmentType::Line] = QPen(QColor(41,129,237));
		verticalPens[buw::eVerticalAlignmentType::Arc] = QPen(QColor(100,170,255));
		verticalPens[buw::eVerticalAlignmentType::Parabola] = QPen(QColor(0,86,191));
		verticalPens[buw::eVerticalAlignmentType::Unknown] = QPen(Qt::white);

		diagramPen = QPen(Qt::lightGray);
		diagramDashedPen = QPen(Qt::lightGray);
		diagramFontColor = QColor(Qt::lightGray);
		break;

	case A2D_DrawState::A2D_Print:
		horizontalPens[buw::eHorizontalAlignmentType::Line] = QPen(Qt::black);
		horizontalPens[buw::eHorizontalAlignmentType::Arc] = QPen(Qt::black);
		horizontalPens[buw::eHorizontalAlignmentType::Clothoid] = QPen(Qt::black);
		horizontalPens[buw::eHorizontalAlignmentType::Bloss] = QPen(Qt::black);
		horizontalPens[buw::eHorizontalAlignmentType::Unknown] = QPen(Qt::black);

		verticalPens[buw::eVerticalAlignmentType::Line] = QPen(Qt::black);
		verticalPens[buw::eVerticalAlignmentType::Arc] = QPen(Qt::black);
		verticalPens[buw::eVerticalAlignmentType::Parabola] = QPen(Qt::black);
		verticalPens[buw::eVerticalAlignmentType::Unknown] = QPen(Qt::black);

		diagramPen = QPen(Qt::black);
		diagramDashedPen = QPen(Qt::black);
		diagramFontColor = QColor(Qt::black);
		break;
	}

	diagramDashedPen.setStyle(Qt::DashLine);

	for (auto& entry : horizontalPens)
	{
		entry.second.setWidth(2);
		entry.second.setCosmetic(true);
	}
	for (auto& entry : verticalPens)
	{
		entry.second.setWidth(2);
		entry.second.setCosmetic(true);
	}

	diagramPen.setWidth(1);
	diagramDashedPen.setWidth(1);
	diagramPen.setCosmetic(true);
	diagramDashedPen.setCosmetic(true);

	v_configureColors(state);

	scale();
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::drawAlignmentScene()
{
	horizontalPainter.clear();
	verticalPainter.clear();

	if (!alignment_)
		return;

	if (alignment_->getAlignment(selectedAlignmentIndex_)->getType() == buw::e3DAlignmentType::e2DBased)
	{
		buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(alignment_->getAlignment(selectedAlignmentIndex_));

		v_drawAlignment(a, horizontalPainter, verticalPainter);
	}

	scale();
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::drawDiagram(QPainterPath& diagPainter, QPainterPath& diagDashedPainter)
{
	QString text;

	int width = 80;

	drawAxis(diagPainter, bounds[3] * scalingY, bounds[0], bounds[1], scalingX, 120);

	drawAxis(diagPainter, bounds[0] * scalingX, bounds[2], bounds[3], scalingY, 80, false, true);

	// Ratio
	text = QString::number(ratio.x()) + " : " + QString::number(ratio.y());
	auto ratioLabel = addText(text, diagramFont);
	ratioLabel->setPos(bounds[0] * scalingX, bounds[2] * scalingY - 20);
	ratioLabel->setDefaultTextColor(diagramFontColor);

	v_drawDiagram(diagPainter, diagDashedPainter);
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::drawAxis(
	QPainterPath& diagPainter, 
	double at, 
	double from, 
	double to, 
	double scaling, 
	double desiredStepSize, 
	bool doubleLine /*= true*/, 
	bool vertical /*= false*/)
{
#define A(X) if(!vertical) { a = X;}else{ b = X;}
#define B(Y) if(!vertical) { b = Y;}else{ a = Y;}

	if(to - from == 0)
		return;

	QString text;
	int width = 40;
	double a, b;
	int sign = vertical ? -1 : 1;
	
	A(from * scaling);
	B(at + 10 * sign);
	diagPainter.moveTo(a,b);

	A(to * scaling);
	B(at + 10 * sign);
	diagPainter.lineTo(a,b);

	if(doubleLine)
	{
		A(from * scaling);
		B(at + (width + 10) * sign);
		diagPainter.moveTo(a,b);

		A(to * scaling)
		B(at + (width + 10) * sign);
		diagPainter.lineTo(a,b);
	}

	std::vector<double> drawStaions;
	drawStaions.push_back(from);
	drawStaions.push_back(to);

	// calculate stations to draw
	{
		double size = (to - from) * scaling;
		int count = size / desiredStepSize;
		count = std::min(count, 10);

		if(count != 0)
		{
			double stepSize = size / count;
			double step = stepSize / scaling;

			double allowedsteps[4] = { 1, 2.5, 5.0, 10.0};
			double dimension = 100000;
			while(step / dimension < 1)
			{
				dimension /= 10;
			}

			double min =  std::numeric_limits<double>().max();
			int index;
			for(int i=0; i<4; i++)
			{
				allowedsteps[i] *= dimension;
				double diff = std::abs(allowedsteps[i] - step);
				if(diff < min)
				{
					min = diff;
					index = i;
				}
			}

			step = allowedsteps[index];

			for(double s = (int)(from/step) * step; s < to; s+= step)
			{
				double spacing;
				if(vertical)
					spacing = (QFontMetrics(diagramFont).height() + 2 ) / scalingY;
				else
					spacing = (QFontMetrics(diagramFont).width("0+000") + 2) / scalingX;

				if(	abs(drawStaions[0] - s) > spacing && abs(drawStaions[1] - s) > spacing )
					drawStaions.push_back(s);
			}
		}
	}

	for(double x : drawStaions)
	{
		double X = x * scaling;
		A(X); 
		B(at + 10 * sign);
		diagPainter.moveTo(a,b);

		A(X);
		B(at + (width + 10) * sign);
		diagPainter.lineTo(a,b);
					
		auto stationLabel = vertical ? v_labelY(sign * x) : v_labelX(sign * x);

		double offsetX = 0;
		double offsetY = 0;
		if(!vertical)
		{
			offsetX = QFontMetrics(diagramFont).width(stationLabel->toPlainText()) / 2;
			offsetY = - width;
		}
		else
		{
			offsetX = 10 + QFontMetrics(diagramFont).width(stationLabel->toPlainText());
			offsetY = QFontMetrics(diagramFont).height() + 4;
		}

		A(X);
		B(at + 10 * sign);
		stationLabel->setPos(a - offsetX, b - offsetY);
		stationLabel->setDefaultTextColor(diagramFontColor);
	}

#undef B
#undef A
}


void OpenInfraPlatform::UserInterface::Alignment2DScene::scale()
{	
	QPainterPath diagPainter, diagDashedPainter;

	clear();

	drawDiagram(diagPainter, diagDashedPainter);	
	
	addPath(diagPainter, diagramPen, transparentBrush);
	addPath(diagDashedPainter, diagramDashedPen, transparentBrush);

	addPaths();

	setSceneRect(
		bounds[0] * scalingX - 150,
		bounds[2] * scalingY - 50, 
		bounds[1] * scalingX - bounds[0] * scalingX + 200, 
		bounds[3] * scalingY - bounds[2] * scalingY + 200);
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::addPaths()
{
	DWORD t1 = GetTickCount();

	for (auto entry : horizontalPainter)
	{
		addPath(scaledPainterPath(&entry.second, scalingX, scalingY), horizontalPens[entry.first], transparentBrush);
	}
	for (auto entry : verticalPainter)
	{
		addPath(scaledPainterPath(&entry.second, scalingX, scalingY), verticalPens[entry.first], transparentBrush);
	}

	v_addPaths();
	DWORD t2 = GetTickCount();

	DWORD overhead = t2 - t1;
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	/*scaleY = 200;
	scaleX = 10;
	drawAlignment();*/
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::wheelEvent(QGraphicsSceneWheelEvent* mouseEvent)
{
	if(mouseEvent->modifiers() != Qt::ControlModifier)
	{
		double scaling = 1;

		if(mouseEvent->delta() > 0)
			scaling = 1.1;
		else
			scaling = 1/ 1.1;

		scalingX *= scaling;
		scalingY *= scaling;
	}
	else
	{
		double max = std::max(ratio.x(), ratio.y());
		double dimension = 1;
		while(dimension*20 <= max)
		{
			dimension *= 10;
		}

		if(mouseEvent->delta() < 0)
		{
			if(ratio.x() > ratio.y())
				ratio[0] -= dimension;
			else
				ratio[1] += dimension;
		}
		else
		{
			if(ratio.x() >= ratio.y())
				ratio[0] += dimension;
			else
				ratio[1] -= dimension;
		}

		scalingY = scalingX * ratio.x() / ratio.y();
	}

	scale();
}

QPainterPath OpenInfraPlatform::UserInterface::Alignment2DScene::scaledPainterPath(QPainterPath* path, double sX, double sY)
{
	QPainterPath copy;
	for(int i=0; i<path->elementCount(); i++)
	{
		qreal x = path->elementAt(i).x;
		qreal y = path->elementAt(i).y;

		if(path->elementAt(i).isLineTo())
			copy.lineTo(x * sX, y * sY);
		else if(path->elementAt(i).isMoveTo())
			copy.moveTo(x * sX, y * sY);
	}

	return copy;
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::exportToFile(QWidget* parent)
{
	QString filter;
	QString fn = QFileDialog::getSaveFileName(parent, tr("Save Vertical Alignment as..."), QString(), tr("PNG File (*.png);; JPG File (*.jpg);; PDF File (*.pdf);; SVG File (*.svg)"), &filter);
	if(fn.isEmpty())
		return;

	if(filter == "PNG File (*.png)" || filter == "JPG File (*.jpg)")
	{
		QImage image(sceneRect().size().toSize(), QImage::Format::Format_ARGB32);
		image.fill(Qt::darkGray);

		QPainter painter(&image);
		painter.setRenderHints(QPainter::Antialiasing);
		render(&painter);
		image.save(fn);
	}
	else
	{
		QPrinter printer;
		QSvgGenerator svgGen;

		QPaintDevice* device;
		if(filter == "PDF File (*.pdf)")
		{
			printer.setResolution(QPrinter::HighResolution);
			printer.setPageSize( QPrinter::A4 );
			printer.setOrientation( QPrinter::Landscape );
			printer.setOutputFormat( QPrinter::PdfFormat );
			printer.setOutputFileName(fn);

			device = &printer;
		}
		else if(filter == "SVG File (*.svg)")
		{
			QRectF rect = sceneRect(); 

			svgGen.setFileName(fn);
			svgGen.setSize(QSize(rect.width(),rect.height()));
			svgGen.setViewBox(QRect(0,0,rect.width(),rect.height()));
			svgGen.setTitle("Vertical Alignment");			
			
			device = &svgGen;
		}
		else
		{
			return;
		}

		QPainter painter(device);

		configureColors(A2D_DrawState::A2D_Print);
		render(&painter);
		configureColors(A2D_DrawState::A2D_Draw);
	}
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::setAlignment(buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::AlignmentModel> alignment)
{
	alignment_ = alignment;
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::setSelectedAlignment(int index)
{
	selectedAlignmentIndex_ = index;
	drawAlignmentScene();
}

int OpenInfraPlatform::UserInterface::Alignment2DScene::getSelectedAlignment()
{
	return selectedAlignmentIndex_;
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::setDifferentColorsForHorizontalAlignmentElements(const bool checked)
{
	differentColorsForHorizontalAlignmentElements_ = checked;
	configureColors(A2D_DrawState::A2D_Draw);
	drawAlignmentScene();
	scale();
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::setDifferentColorsForVerticalAlignmentElements(const bool checked)
{
	differentColorsForVerticalAlignmentElements_ = checked;
	configureColors(A2D_DrawState::A2D_Draw);
	drawAlignmentScene();
	scale();
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::setScalingRatio(double x, double y)
{
	scalingY = scalingX * y / x;
	scale();
}

void OpenInfraPlatform::UserInterface::Alignment2DScene::fit(double width)
{
	if (!alignment_)
	{
		scalingX = 1;
		scalingY = 1;
		scale();
		return;
	}

	double start = alignment_->getAlignments()[selectedAlignmentIndex_]->getStartStation();
	double end = alignment_->getAlignments()[selectedAlignmentIndex_]->getEndStation();
	double length = end - start;

	scalingX = width / length;
	scalingY = scalingX * ratio.x() / ratio.y();
	scale();
}

QGraphicsTextItem* OpenInfraPlatform::UserInterface::Alignment2DScene::v_labelX(double value)
{
	int kilometer = value / 1000;
	int meter = value - kilometer * 1000;

	QString text;
	QString qsign = meter >= 0 ? "+" : "-";
	if (meter / 100 == 0)
		qsign += "0";
	if (meter / 10 == 0)
		qsign += "0";
	text = QString::number(kilometer) + qsign + QString::number(std::abs(meter));
	return addText(text, diagramFont);
}

QGraphicsTextItem* OpenInfraPlatform::UserInterface::Alignment2DScene::v_labelY(double value)
{
	return addText(QString::number(value, 'f', 3), diagramFont);
}
