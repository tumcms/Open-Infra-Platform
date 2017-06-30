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

#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QLabel>

#include <QMouseEvent>


class screen : public QWidget
{

    Q_OBJECT

public:
    screen();

private:
    QLabel *label;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
Q_SIGNALS:
    void colorSelected(QColor color);
};

#endif // SCREEN_H
