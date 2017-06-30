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

#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "screen.h"

screen::screen()
{
    //label = new QLabel(this);
	/*
	QScreen *screen = QGuiApplication::primaryScreen();
    label->setPixmap(screen->grabWindow(QApplication::desktop()->winId()));
    label->move(0,0);
	*/
    //showFullScreen();
}


void screen::mousePressEvent(QMouseEvent *event)
{
  //  Q_EMIT colorSelected( label->pixmap()->toImage().pixel( event->pos() ) );
  //  close();
}
