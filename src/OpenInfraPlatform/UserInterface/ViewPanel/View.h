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
#ifndef OpenInfraPlatform_UserInterface_View_05741137_3101_4ec4_bf4b_61206b15ebce_h
#define OpenInfraPlatform_UserInterface_View_05741137_3101_4ec4_bf4b_61206b15ebce_h

#include "Viewport.h"
//#include "buw.BlueApplication.h"
#include "../../DataManagement/Data.h"

#include <QMenuBar>
#include <QDockWidget>
#include <QtWidgets/QVBoxLayout>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class View : public QDockWidget 
		{
			Q_OBJECT;

		public:
			View();

			virtual ~View();

			void createViewport(buw::eRenderAPI renderAPI, bool warp, bool msaa);
			void getViewportSettings(buw::eRenderAPI& renderAPI, bool& warp, bool& msaa);

			void enableBlueMap( const bool checked );

			void enableTerrainGradientRamp(const bool enable);

			void enableIsoLines(const bool enable);

			void enableDrawTerrainWireframe(const bool enable);

			void enableHideTerrain(const bool enable);

			void setView(eView viewType);

			void showCrossSection( const bool showCrossSection );
			void showDesignCrossSection( const bool showDesignCrossSection );
			void showRoadBodyWireframe(const bool connectCrossSections);
			void showRoadBodySolid(const bool solidCrossSections);
			void drawRoadTexture(const bool drawRoadTexture);

			void enableTerrainTextured( const bool enable );

			void enableCreatePoints( const bool enable );

			std::vector<buw::Vector3d> getAlignmentPoints();

			void setDifferentColorsForAlignmentElements( const bool checked );
			void setHighlightSelectedAlignmentSegment( const bool enable );

			void	setUseUniformPointColor(const bool useUniformColor);
			void	setUseUniformPointSize(const bool useUniformSize);
			void	setPointSize(const float size);

			buw::Vector3d getOffset() const;

			void saveAsScreenshot(const std::string& filename);

			buw::Vector2i getSize() const;
			void setViewportSize(const int width, const int height);

			int getViewportWidth() const;

			int getViewportHeight() const;

			void reloadShader();

			void storeGBuffer();

			void cameraControlModeChanged();

			void showFrameTimes(const bool show);

            Viewport* getViewport();           

			//---------------------------------------------------------------------------//
			// Camera Control
			//---------------------------------------------------------------------------//

			//void setInfraCameraController(buw::ReferenceCounted<buw::InfraCameraController> controller);
			//buw::ReferenceCounted<buw::InfraCameraController> getInfraCameraController() const;

			//void onViewCubeSelectionChanged(buw::eViewCubeOrientation::Enum state);

			void LoadBridge();

			virtual void changeEvent(QEvent* evt) override;

            void rotate(buw::Vector2f value);

		private:
			void retranslateView();

		private Q_SLOTS:
			void on_actionPerspective();
			void on_actionOrthographic();
			void on_actionLeft();
			void on_actionRight();
			void on_actionFront();
			void on_actionBack();
			void on_actionTop();
			void on_actionBottom();

			void on_actionIsometric();

			void on_home();
			void on_actionToggleCameraGhostMode();
            void on_actionToggleSnow();

		private:
			QMenu* menuView_;
			QMenu* menuAxonometric_;
			QMenu* menuProjection_;

			QAction* actionPerspective_;
			QAction* actionOrthographic_;

			QAction* actionLeft_;
			QAction* actionRight_;
			QAction* actionFront_;
			QAction* actionBack_;
			QAction* actionTop_;
			QAction* actionBottom_;

			QAction* actionIsometric_;

			QAction* cameraGhostModeAction_;
			QAction* homeAction_;
            QAction* snowAction_;

			Viewport*	viewport_;
			buw::eRenderAPI renderAPI_;
			bool forceWarpDevice_;
			bool enableMSAA_;
		}; // end class View
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	//using OpenInfraPlatform::UserInterface::View;
}

#endif // end define OpenInfraPlatform_UserInterface_View_05741137_3101_4ec4_bf4b_61206b15ebce_h
