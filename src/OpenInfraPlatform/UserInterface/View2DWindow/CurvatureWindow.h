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

#pragma once

#include "Alignment2DScene.h"
#include <QDockWidget>
#include <boost/noncopyable.hpp>
#include "ui_CurvatureWindow.h"
#include "../../DataManagement/Data.h"
#include <vector>
#include "OpenInfraPlatform/namespace.h"

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

class CurvatureScene : public Alignment2DScene
{
public:
	CurvatureScene(QObject *parent = 0);

protected:
	void v_drawAlignment(buw::ReferenceCounted<buw::Alignment2DBased3D> a,
		std::map<buw::eHorizontalAlignmentType, QPainterPath>& horizontalPainter,
		std::map<buw::eVerticalAlignmentType, QPainterPath>& verticalPainter) override;
};

// Window
class CurvatureWindow : public QDockWidget
{
	Q_OBJECT;

public:
	CurvatureWindow(QAction* act);

	void setDifferentColorsForHorizontalAlignmentElements(bool checked);
	void setDifferentColorsForVerticalAlignmentElements(bool checked);

	void exportToFile();;

	void closeEvent(QCloseEvent *event);

private:
	void onChange();

private:
	Ui::Curvature*	ui_;
	QAction* action_;

	CurvatureScene* scene_;
}; 

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

namespace buw
{
	using OpenInfraPlatform::UserInterface::CurvatureWindow;
}
