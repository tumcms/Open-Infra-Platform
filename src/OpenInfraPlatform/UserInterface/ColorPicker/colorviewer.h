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

#ifndef COLORVIEWER_H
#define COLORVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class ColorViewer : public QWidget
{
    Q_OBJECT

public:
    ColorViewer(QWidget *parent = 0);
    ~ColorViewer();

    void setPen(const QPen &pen);
    QPen pen() const;

    void setColor(const QColor &color);
    QColor color() const;

public Q_SLOTS:
    void changeColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPen actualPen;
    QBrush actualBrush;
    QColor actualColor;
};

#endif // COLORVIEWER_H
