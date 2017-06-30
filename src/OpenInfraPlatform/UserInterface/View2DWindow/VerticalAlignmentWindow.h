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
#include "ui_VerticalAlignmentWindow.h"
#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/namespace.h"
#include <QDockWidget>
#include <boost/noncopyable.hpp>
#include <vector>
#include <tuple>

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_BEGIN

// Scene
class VerticalAlignmentScene : public Alignment2DScene
{
public:
	VerticalAlignmentScene(QObject *parent = 0);

	void setDigitalElevationModel(buw::ReferenceCounted<buw::DigitalElevationModel> model);

	void displayPoints(bool display);

	void loadSurfaceProfile();
	void clearSurfaceProfile();

protected:
	void v_configureColors(A2D_DrawState state) override;

	void v_drawAlignment(buw::ReferenceCounted<buw::Alignment2DBased3D> a,
		std::map<buw::eHorizontalAlignmentType, QPainterPath>& horizontalPainter,
		std::map<buw::eVerticalAlignmentType, QPainterPath>& verticalPainter) override;
	void v_drawDiagram(QPainterPath& diagPainter, QPainterPath& diagDashedPainter) override;

	void v_addPaths() override;

private:
	buw::ReferenceCounted<buw::DigitalElevationModel> model_;

	std::vector<std::tuple<int, buw::Vector2d, buw::Vector2d>> arcPoints_;
	std::vector<std::tuple<int, buw::Vector2d, buw::Vector2d, buw::Vector2d>> parabolaPoints_;

	bool displayPoints_;

	QPen	terrainPen;
	QPainterPath terrainPainter;

};
		
// Window
class VerticalAlignmentWindow : public QDockWidget
{
	Q_OBJECT;

public:
	VerticalAlignmentWindow(QAction* act);

	void setDifferentColorsForHorizontalAlignmentElements(const bool checked);
	void setDifferentColorsForVerticalAlignmentElements(const bool checked);

	void exportToFile();;

public Q_SLOTS:
	void on_loadSurfaceProfileButton_clicked();;

	void on_displayPointsCheckBox_clicked(bool checked);;

	void closeEvent(QCloseEvent *event);

private:
	void onChange();

private:
	Ui::VerticalAlignment*	ui_;
	QAction* action_;

	VerticalAlignmentScene* scene_;
}; 

OIP_NAMESPACE_OPENINFRAPLATFORM_UI_END

namespace buw
{
	using OpenInfraPlatform::UserInterface::VerticalAlignmentWindow;
}
