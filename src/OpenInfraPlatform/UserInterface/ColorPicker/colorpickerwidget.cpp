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

#include "colorpickerwidget.h"

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent, Qt::WindowTitleHint)
{
    ecran=0;
    colorTriangle = new QtColorTriangle(this);

    connect(colorTriangle, SIGNAL(colorChanged(QColor)), this, SLOT(colorChgd()));

    colorView = new ColorViewer(this);
    colorView->setColor(colorTriangle->color());
    connect(colorTriangle, SIGNAL(colorChanged(QColor)), colorView, SLOT(changeColor(QColor)));

    pushButtonPickColor = new QPushButton(tr("Pick a color"), this);
    connect(pushButtonPickColor, SIGNAL(released()), this, SLOT(pickMode()));

	connect(pushButtonPickColor, SIGNAL(clicked()), this, SLOT(on_pushButtonPickColor_clicked()));

    layout = new QGridLayout;
    layout->addWidget(  colorTriangle,  0, 0, 3, 2);
    layout->addWidget(  colorView,      0, 2, 2, 1);
    layout->addWidget(  pushButtonPickColor,      2, 2, 1, 1);

    setLayout(layout);
}

ColorPickerWidget::~ColorPickerWidget()
{
}

void ColorPickerWidget::pickMode()
{
    if(ecran!=0)
        delete ecran;
    ecran = new screen;
        connect( ecran, SIGNAL(colorSelected(QColor)), colorTriangle, SLOT(setColor(QColor)) );
}

void ColorPickerWidget::setColor(const QColor &col)
{
    colorView->setColor(col);
    colorTriangle->setColor(col);
}


void ColorPickerWidget::colorChgd()
{
    //Q_EMIT colorChanged(colorView->color());
}

void ColorPickerWidget::on_pushButtonPickColor_clicked()
{
	Q_EMIT colorChanged(colorView->color());
}
