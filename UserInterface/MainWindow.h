/*
    Copyright (c) 2021 Technical University of Munich
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
#ifndef Blueform_UserInterface_MainWindow_aa3f98a6_ba15_4416_ae66_87ca891307d9_h

#define Blueform_UserInterface_MainWindow_aa3f98a6_ba15_4416_ae66_87ca891307d9_h

#include "../UserInterface/ViewPanel/View.h"
#include "../UserInterface/Dialogues/LicenseAndCopyrightInformationDialog.h"
#include "DataManagement/General/Data.h"
#include "../UserInterface/Dialogues/PreferencesDialog.h"
#include "../Core/src/DataManagement/General/ProgressCallback.h"

//#include "../UserInterface/XYZImportDialog.h"
//#include "OpenInfraPlatform/UserInterface/ExportIfcAlignment1x0Dialog.h"
//#include "OpenInfraPlatform/UserInterface/ExportIfc4x1Dialog.h"
//#include "OpenInfraPlatform/UserInterface/ExportIfcZipDialog.h"
//#include "OpenInfraPlatform/UserInterface/ExportExcelDialog.h"
//#include "OpenInfraPlatform/UserInterface/GenerateTerrainDialog.h"
//#include "OpenInfraPlatform/UserInterface/AddGeoreferenceDialog.h"
//#include "OpenInfraPlatform/UserInterface/View2DWindow/VerticalAlignmentWindow.h"
//#include "OpenInfraPlatform/UserInterface/View2DWindow/CurvatureWindow.h"
//#include "OpenInfraPlatform/UserInterface/ShowIFCtree.h"
//#include "OpenInfraPlatform/UnitTesting/ImageTester.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateArcClothoidArcMeth2Dialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateArcClothoidClothoidArcMeth2Dialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateClothoidDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateClothoidDialog2.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateLineArcArcLineDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateLineArcArcArcLineDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateLineClothoidArcClothoidLineDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateLineClothoidClothoidLineDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateArcClothoidArcDialog.h"
//#include "OpenInfraPlatform/UserInterface/Tools/CreateArcClothoidClothoidArcDialog.h"
//#include "OpenInfraPlatform/UserInterface/CreateAccidentReportDialog.h"
//#include "OpenInfraPlatform/UserInterface/OSMImportDialog.h"
#include "../Core/src/SplineInterpretation/SplineInterpretation.h"

#include "qsimpleupdater.h"

#include <qcustomplot.h>

#include <BlueFramework/Application/UserInterface/MainWindow.h>
#include "../UserInterface/QtPropertyBrowser/qttreepropertybrowser.h"
#include "../UserInterface/QtPropertyBrowser/qtvariantproperty.h"
#include <QMenuBar>
#include <QProgressBar>
#include <QProgressDialog>
#include <QButtonGroup>
#include <QColorDialog>
#include <setjmp.h>

#include "../UserInterface/Dialogues/PrecisionTest.h"
#include <QDropEvent>
#include <qmimedata>

namespace Ui
{
	class MainWindow;
}

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		//! \class MainWindow
		//! \brief brief description
		class MainWindow : public BlueFramework::Application::UserInterface::MainWindowBase
		{
			Q_OBJECT;

			typedef OpenInfraPlatform::Core::DataManagement::ChangeFlag ChangeFlag;

		public:
			//! Default constructor.
			MainWindow(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~MainWindow();

			void showEvent(QShowEvent* event);
			//void updateAlignmentUI();
			//void updateAlignmentElementsUI();
			void emitPoints(QDialog*); // for the communication between menue/tools and MainWindow
			void storeGBuffer();
			virtual void changeEvent(QEvent* evt) override;

			void checkForUpdates();

		public Q_SLOTS:
			//void on_action3D_triggered();
			void on_actionAbout_triggered();

			//void on_actionAdvancedSVG_triggered();
			//void on_actionUsualSVG_triggered();

			//void on_actionAlignments_as_3D_Points_txt_triggered();
			void on_actionCheck_for_Updates_triggered();
			//void on_actionCreate_Alignment_Points_triggered(bool checked);
			//void on_actionCreate_Alignment_triggered();
			//void on_actionCreate_Arc_Clothoid_Arc_triggered();
			//void on_actionCreate_Arc_Clothoid_Arc2_triggered();
			//void on_actionCreate_Arc_Clothoid_Clothoid_Arc_triggered();
			//void on_actionCreate_Arc_Clothoid_Clothoid_Arc2_triggered();
			//void on_actionCreate_Line_Arc_Arc_Arc_Line_triggered();
			//void on_actionCreate_Line_Arc_Arc_Line_triggered();
			//void on_actionCreate_Line_Clothoid_Arc_Clothoid_Line_triggered();
			//void on_actionCreate_Line_Clothoid_Clothoid_Line_triggered();
			//void on_actionCreate_Line_Clothoid_triggered();
			//void on_actionCreateClothoid_triggered();
			void on_actionStroke_To_Alignment_triggered();
			//void on_actionCurvature_triggered();
			//void on_actionShow_IFC_tree_triggered();
			void on_actionExit_triggered();
			//void on_actionExport_Terrain_As_Heightmap_triggered();
			//void on_actionExportCurvature_triggered();
			//void on_actionExportIfcAlignment_triggered();
			//void on_actionExportIfcZip_triggered();
			//void on_actionExportIIfcRoad_triggered();
			//void on_actionExportVerticalAlignment_triggered();
			//void on_actionExportLandInfra_triggered();

			//void on_actionHorizontal_alignment_triggered();
			//void on_actionIfcAlignment_buildingSMART_P6_Excel_Comparison_triggered();
			//void on_actionImport_IFC_Alignment_1_0_triggered();
			//void on_actionIFC_Alignment_1_1_Export_triggered();

			void on_actionShow_License_and_Copyright_Information_triggered();
			void on_actionShow_Log_Folder_triggered();


			//void on_actionCreate_Accident_Report_triggered();
			//void on_actionImport_OSM_File_triggered();
			//void on_actionLandXML_triggered();
			//void on_actionLoad_Bridge();
			
			//void on_actionMerge_LAS_File_triggered();
			//void on_actionMerge_Mesh_triggered();
			//void on_actionMerge_XYZ_File_triggered();
			
			void on_actionNew_triggered();
			//void on_actionOkstra_triggered();
			//void on_actionOkstra_translated_triggered();
			//void on_actionOkstraOWL_triggered();
			//void on_actionifcOWL4x1Export_triggered();
			void on_actionOpen_triggered();
			//void on_actionPrecisionTest();
			void on_actionPreferences_triggered();
			void on_actionRedo_triggered();

			//void on_actionRoad_body_solid_triggered(bool checked);
			//void on_actionRoad_body_wireframe_triggered(bool checked);
			//void on_actionDraw_Road_Texture_triggered(bool checked);

			void on_actionSave_triggered();
			void on_actionSaveAs_triggered();
			//void on_actionShow_Cross_Section_triggered(bool checked);
			//void on_actionShow_Design_Cross_Section_triggered(bool checked);
			void on_actionShow_Help_triggered();
			void on_actionShow_Log_File_triggered();
			//void on_actionTerrain_Create_Terrain_from_Heightmap_triggered();
			//void on_actionTerrain_Generate_Random_Terrain_triggered();
			//void on_actionTerrain_Gradient_Ramp_triggered(bool checked);
			//void on_actionTerrain_Hide_triggered(bool checked);
			//void on_actionTerrain_Iso_Lines_triggered(bool checked);
			//void on_actionTerrain_Textured_triggered(bool checked);
			//void on_actionTerrain_Wireframe_triggered(bool checked);
			void on_actionUndo_triggered();
			//void on_actionVertical_alignment_3D_triggered();
			//void on_actionVertical_alignment_triggered();
			void on_actionViewport_as_screenshot_triggered();

			void on_actionZoomToOneObject_triggered(const std::shared_ptr<oip::IModel>& model, const oip::BBox & fullBBox, const oip::BBox & modelBBox);
			//void on_actionAdd_Georeference_triggered();

			//void on_checkBoxDifferentColorsForVerticalAlignmentElements_clicked(bool checked);
			//void on_checkBoxHighlightSelectedAlignmentSegment_clicked(bool checked);
			//void on_checkBoxShowDifferentAlignmentElements_clicked(bool checked);
			void on_checkBoxShowMap_clicked (bool checked);

			// Point Cloud
#ifdef OIP_WITH_POINT_CLOUD_PROCESSING

			void on_actionExportPointCloud_triggered();
			void on_actionMerge_LAS_File_triggered();
			void on_checkBoxUseUniformColor_clicked(bool checked);
			void on_checkBoxUseUniformSize_clicked(bool checked);

			void on_checkBoxShowPointCloud_clicked(bool checked);

			void on_pushButtonSelectUniformColor_clicked();
			void on_pushButtonSelectSegmentedPointsColor_clicked();
			void on_pushButtonSelectFilteredPointsColor_clicked();

			void on_pushButtonApplyDuplicateFilter_clicked();
			void on_pushButtonResetDuplicateFilter_clicked();

			void on_pushButtonApplyDensityFilter_clicked();
			void on_pushButtonResetDensityFilter_clicked();

			void on_pushButtonApplyPositionFilter_clicked();
			void on_pushButtonResetPositionFilter_clicked();

			void on_pushButtonApplyRelativeHeightFilter_clicked();
			void on_pushButtonResetRelativeHeightFilter_clicked();

			void on_pushButtonFilterOriginal_clicked();
			void on_pushButtonRestoreOriginal_clicked();

			void on_pushButtonExtractSegmentation_clicked();
			void on_pushButtonUndoSegmentation_clicked();

			void on_pushButtonApplyPercentileSegmentation_clicked();
			void on_pushButtonResetPercentileSegmentation_clicked();
			void on_doubleSpinBoxPercentileSegmentationKernelRadius_valueChanged(double value);

			void on_pushButtonComputePercentilesOnGrid_clicked();

			void on_pushButtonApplyRateOfChangeSegmentation_clicked();
			void on_pushButtonResetRateOfChangeSegmentation_clicked();
			
			void on_pushButtonComputeGrid_clicked();
			void on_pushButtonResetGrid_clicked();

			void on_pushButtonComputeChainage_clicked();
			void on_pushButtonResetChainage_clicked();

			void on_pushButtonApplySegmentRailways_clicked();
			void on_pushButtonResetSegmentRailways_clicked();

			void on_pushButtonComputeCenterlines_clicked();
			void on_pushButtonResetCenterlines_clicked();

			void on_pushButtonComputePairs_clicked();
			void on_pushButtonResetPairs_clicked();

			void on_pushButtonComputeCurvature_clicked();

			void on_pushButtonPlotAlignment_clicked();

			void on_doubleSpinBoxRemoveDuplicatesThreshold_valueChanged(double value);

			void on_pushButtonCalculateSections_clicked();
			void on_doubleSpinBoxSectionSize_valueChanged(double value);
			void on_horizontalSliderSectionSize_valueChanged(int value);

			void on_comboBoxAlignment_currentIndexChanged( int index );
			void on_doubleSpinBoxPointSize_valueChanged(double value);
			void on_horizontalSliderPointSize_sliderMoved(int value);

			void on_checkBoxShowSectionOOBB_clicked(bool checked);

			void on_spinBoxOctreeLevel_valueChanged(int value);
			void on_checkBoxShowOctree_clicked(bool checked);
#endif

			//void on_pushButtonDeleteSelectedAlignment_clicked();
			//void on_pushButtonDeleteSurface_clicked();
			//void on_variantEditor_currentItemChanged(QtBrowserItem * item);


			// Recent files
			void on_actionRecentFile1_triggered();
			void on_actionRecentFile2_triggered();
			void on_actionRecentFile3_triggered();
			void on_actionRecentFile4_triggered();
			void on_actionRecentFile5_triggered();
			void on_actionRecentFile6_triggered();
			void on_actionRecentFile7_triggered();
			void on_actionRecentFile8_triggered();
			void on_actionRecentFile9_triggered();
			void on_actionRecentFile10_triggered();
			void on_actionClearMenu_triggered();

			// Updater
			void onCheckingFinished();

		private:
			//void createClothoid();

			// Todo move recent files functionality to MainWindowBase
			void addToRecentFilesList(const QString &fileName);
			void updateRecentFileActions();
			QString strippedName(const QString &fullFileName);

		private Q_SLOTS:
			void actionGetCameraState();
			void showMap();
			void reloadShader();
			void cancelJob();
			void aboutQt();

		private:
			void jobStarting();
			void jobRunning(int id, float progress, const std::string& message);
			void jobFinishing(int id, bool completed);
			void jobFinished(int id, bool completed);

			//void prepareTest(int i);
			//void performTest(int i);

			void openRecentFileViaAction( QAction *actionRecentFile );

			void onChange();
			void onChange(ChangeFlag changeFlag);

			void updateActionUndo( unsigned int numberOfUndoActions );
			void updateActionRedo(unsigned int numberOfRedoActions);

			//void retranslatePropertyBrowser();
		private:
			// RegEx to parse the window title and capture the document state
			// RegEx matches "TUM Open Infra Platform YYYY - [Filename]", and captures "Filename"
			const QRegExp				titleRegex = QRegExp { "^TUM Open Infra Platform \\d{4} \\(.*\\)\\s+-\\s+\\[(.*)\\]$" };

			// URLs for QSimpleUpdater
			const QString				changeLogUrl { "http://oip.cms.bgu.tum.de/update/change_log.txt" };
			const QString				currentVersionUrl { "http://oip.cms.bgu.tum.de/update/current_version.txt" };
			const QString				installerUrl { "http://oip.cms.bgu.tum.de/update/TUM%20Open%20Infra%20Platform.msi" };

			std::unique_ptr<QSimpleUpdater> updater;

			QColorDialog				pcdUniformColorDialog_, pcdFilteredPointsColorDialog_, pcdSegmentedPointsColorDialog_;
			QButtonGroup				radioButtons2D3D_, radioButtonsOriginalFiltered_;
			buw::ReferenceCounted<OpenInfraPlatform::Core::DataManagement::ProgressCallback> callback_ = nullptr;

			// Dialogs
			//CreateArcClothoidArcDialog*					ACA_ = nullptr;
			//CreateArcClothoidArcMeth2Dialog*			ACA2_ = nullptr;
			//CreateArcClothoidClothoidArcDialog*			ACCA_ = nullptr;
			//CreateArcClothoidClothoidArcMeth2Dialog*	ACCA2_ = nullptr;
			//CreateClothoidDialog*						LC_ = nullptr;
			//CreateClothoidDialog2*						createClothoidDialog2_ = nullptr;
			//CreateLineArcArcArcLineDialog*				LAAAL_ = nullptr;
			//CreateLineArcArcLineDialog*					LAAL_ = nullptr;
			//CreateLineClothoidArcClothoidLineDialog*	LCACL_ = nullptr;
			//CreateLineClothoidClothoidLineDialog*		LCCL_ = nullptr;
			//CurvatureWindow*							curvatureWindow_ = nullptr;
			//ShowIFCtree*								showIFCtree_ = nullptr;
			//ExportExcelDialog*							exportExcelDialog_ = nullptr;
			//ExportIfcAlignment1x0Dialog*				exportIfcAlignment1x0Dialog_ = nullptr;
			//ExportIfc4x1Dialog*				exportIfcAlignment1x1Dialog_ = nullptr;
			//ExportIfcZipDialog*							exportIfcZipDialog_ = nullptr;
			//GenerateTerrainDialog*						generateTerrainDialog_ = nullptr;
			//OSMImportDialog*							osmImportDialog_ = nullptr;

			//VerticalAlignmentWindow*					verticalAlignmentWindow_ = nullptr;
			//XYZImportDialog*							XYZImportDialog_ = nullptr;
			//CreateAccidentReportDialog*					createAccidentReportDialog_ = nullptr;
			//AddGeoreferenceDialog*						addGeoreferenceDialog_ = nullptr;

			PreferencesDialog*							preferencesDialog_ = nullptr;
			QProgressDialog*							progressDialog_ = nullptr;
			LicenseAndCopyrightInformationDialog*		licenseAndCopyrightInformationDialog_ = nullptr;
			QProgressBar*								progressBar_;

			std::vector<QCustomPlot*>					plots_;
			
			int											inUnitTest_ = -1;

			View*										view_;
			Ui::MainWindow*  							ui_;

			bool										loaded_;

			PrecisionTest								precisionTest_;

			bool										translateOkstra_;

			// Model handling
			void updateModelsUI();

			// tree view of models
			QTreeWidget* modelsTreeWidget_;
			QTreeWidgetItem* modelsBBoxWidgetItem_;


		protected:
			void dropEvent(QDropEvent *ev);
			void dragEnterEvent(QDragEnterEvent *ev);

		Q_SIGNALS:
			void sendPoints(std::vector<buw::Vector3d> , buw::Vector2d); // for the communication with the tool-dialogs like CreateArcClothoidArcDialog
		}; // end class MainWindow
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

#endif // end define Blueform_UserInterface_MainWindow_aa3f98a6_ba15_4416_ae66_87ca891307d9_h
