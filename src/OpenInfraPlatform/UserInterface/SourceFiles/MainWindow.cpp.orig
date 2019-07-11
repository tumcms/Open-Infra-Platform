/*
    Copyright (c) 2018 Technical University of Munich
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

#include "OpenInfraPlatform/UserInterface/MainWindow.h"

#include "ColorPicker/colorpickerwidget.h"
#include "OpenInfraPlatform/Benchmark.h"
#include "OpenInfraPlatform/DataManagement/AsyncJob.h"
#include "OpenInfraPlatform/DataManagement/Command/CommandCreateClothoid.h"
#include "OpenInfraPlatform/DataManagement/Command/DeleteAlignment.h"
#include "OpenInfraPlatform/DataManagement/Command/DeleteSurface.h"
#include "OpenInfraPlatform/DataManagement/Command/SelectAlignment.h"

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DBlossCurve.h"
#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "OpenInfraPlatform/UserInterface/HelpBrowser.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/Effects/AlignmentEffect.h"
#include "OpenInfraPlatform/UserInterface/resource.h"
#include "OpenInfraPlatform/UserInterface/VectorTableModel.h"

#include "buw.OIPInfrastructure.h"
#include "ui_mainwindow.h"

#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>

#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QUuid>
#include <QMessageBox>

#include <boost/filesystem.hpp>

#include <fftw3.h>

#include <iostream>
#include <codecvt>
#include <shlobj.h>
#include <stdlib.h>

using convert_type = std::codecvt_utf8<wchar_t>;

OpenInfraPlatform::UserInterface::MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
    : BlueFramework::Application::UserInterface::MainWindowBase(&OpenInfraPlatform::DataManagement::DocumentManager::getInstance(), parent)
    , ui_(new Ui::MainWindow)
    , verticalAlignmentWindow_(nullptr)
    , curvatureWindow_(nullptr)
    , loaded_(false) {
	ui_->setupUi(this);
	variantEditor_ = new QtTreePropertyBrowser();

	variantManager_ = new QtVariantPropertyManager();

	propertyHorizontalAlignment_ = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId());
	propertyVerticalAlignment_ = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId());

	itemStartStation_ = variantManager_->addProperty(QVariant::Double);
	itemStartStation_->setValue(0);
	itemEndStation_ = variantManager_->addProperty(QVariant::Double);
	itemStartStation_->setValue(0);
	itemLength_ = variantManager_->addProperty(QVariant::Double);
	itemLength_->setValue(0);

	variantEditor_->setStyleSheet("");
	variantEditor_->setFactoryForManager(variantManager_, new QtVariantEditorFactory());
	variantEditor_->addProperty(itemStartStation_);
	variantEditor_->addProperty(itemEndStation_);
	variantEditor_->addProperty(itemLength_);
	variantEditor_->setPropertiesWithoutValueMarked(true);
	variantEditor_->setRootIsDecorated(false);
	variantEditor_->addProperty(propertyHorizontalAlignment_);
	variantEditor_->addProperty(propertyVerticalAlignment_);

	ui_->verticalLayoutAlignment->addWidget(variantEditor_);

	view_ = new View();
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, view_, Qt::Orientation::Horizontal);

	updateWindowTitle("Untitled");

	view_->getViewport()->getAlignmentEffect()->AlignmentSelectionChanged.connect(boost::bind(&MainWindow::on_comboBoxAlignment_currentIndexChanged, this, _1));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().Change.connect(boost::bind(&MainWindow::onChange, this));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().RedoStackChanged.connect(boost::bind(&MainWindow::updateActionRedo, this, _1));
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().UndoStackChanged.connect(boost::bind(&MainWindow::updateActionUndo, this, _1));

	OpenInfraPlatform::AsyncJob::getInstance().jobStarting.connect(boost::bind(&MainWindow::jobStarting, this));
	OpenInfraPlatform::AsyncJob::getInstance().jobRunning.connect(boost::bind(&MainWindow::jobRunning, this, _1, _2, _3));
	OpenInfraPlatform::AsyncJob::getInstance().jobFinishing.connect(boost::bind(&MainWindow::jobFinishing, this, _1, _2));
	OpenInfraPlatform::AsyncJob::getInstance().jobFinished.connect(boost::bind(&MainWindow::jobFinished, this, _1, _2));

	// Initialize dialogs
	ACA_ = new CreateArcClothoidArcDialog(this);
	ACA2_ = new CreateArcClothoidArcMeth2Dialog(this);
	ACCA_ = new CreateArcClothoidClothoidArcDialog(this);
	ACCA2_ = new CreateArcClothoidClothoidArcMeth2Dialog(this);
	createClothoidDialog2_ = new CreateClothoidDialog2(this);
	curvatureWindow_ = new CurvatureWindow(ui_->actionCurvature);
	exportExcelDialog_ = new ExportExcelDialog(this);
	exportIfcZipDialog_ = new ExportIfcZipDialog(this);
	exportIfcAlignment1x0Dialog_ = new ExportIfcAlignment1x0Dialog(this);
	exportIfcAlignment1x1Dialog_ = new ExportIfc4x1Dialog(this);
	generateTerrainDialog_ = new GenerateTerrainDialog(this);
	LAAAL_ = new CreateLineArcArcArcLineDialog(this);
	LAAL_ = new CreateLineArcArcLineDialog(this);
	LC_ = new CreateClothoidDialog(this);
	LCACL_ = new CreateLineClothoidArcClothoidLineDialog(this);
	LCCL_ = new CreateLineClothoidClothoidLineDialog(this);
	osmImportDialog_ = new OSMImportDialog(this);
	preferencesDialog_ = new PreferencesDialog(view_, this);
	verticalAlignmentWindow_ = new VerticalAlignmentWindow(ui_->actionVertical_alignment);
	XYZImportDialog_ = new XYZImportDialog(this);
	addGeoreferenceDialog_ = new AddGeoreferenceDialog(view_, this);
	showIFCtree_ = new ShowIFCtree(view_, this);
	updateRecentFileActions();

	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), ACA_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), ACA2_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), ACCA_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), ACCA2_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), LC_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), LCACL_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), LCCL_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), LAAL_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));
	connect(this, SIGNAL(sendPoints(std::vector<buw::Vector3d>, buw::Vector2d)), LAAAL_, SLOT(takePoints(std::vector<buw::Vector3d>, buw::Vector2d)));

	connect(&pcdUniformColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport(), &Viewport::updatePointCloudUniformColor);
	connect(&pcdUniformColorDialog_, &QColorDialog::colorSelected, view_->getViewport(), &Viewport::updatePointCloudUniformColor);

	connect(&pcdFilteredPointsColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport(), &Viewport::updatePointCloudFilteredPointsColor);
	connect(&pcdFilteredPointsColorDialog_, &QColorDialog::colorSelected, view_->getViewport(), &Viewport::updatePointCloudFilteredPointsColor);

	connect(&pcdSegmentedPointsColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport(), &Viewport::updatePointCloudSegmentedPointsColor);
	connect(&pcdSegmentedPointsColorDialog_, &QColorDialog::colorSelected, view_->getViewport(), &Viewport::updatePointCloudSegmentedPointsColor);

	connect(ui_->radioButtonRender2D, &QAbstractButton::toggled, view_->getViewport(), &Viewport::updatePointCloudProjectPoints);
	connect(ui_->radioButtonOriginal, &QAbstractButton::toggled, view_->getViewport(), &Viewport::updatePointCloudRenderOriginalCloud);

	connect(ui_->checkBoxShowSegmentedPoints, &QAbstractButton::clicked, view_->getViewport(), &Viewport::updatePointCloudShowSegmentedPoints);
	connect(ui_->checkBoxShowFilteredPoints, &QAbstractButton::clicked, view_->getViewport(), &Viewport::updatePointCloudShowFilteredPoints);

	connect(ui_->horizontalSliderRemoveDuplicatesThreshold, &QSlider::valueChanged, ui_->doubleSpinBoxRemoveDuplicatesThreshold, &QDoubleSpinBox::setValue);
	connect(ui_->horizontalSliderPercentileSegmentationKernelRadius, &QSlider::valueChanged, ui_->doubleSpinBoxPercentileSegmentationKernelRadius, &QDoubleSpinBox::setValue);

	// Add items to railway combo boxes.
	ui_->comboBoxFilterDensityMetric->addItem("kNN", QVariant(0));
	ui_->comboBoxFilterDensityMetric->addItem("2D", QVariant(1));
	ui_->comboBoxFilterDensityMetric->addItem("3D", QVariant(2));
	ui_->comboBoxFilterDensityMetric->setCurrentIndex(0);

	ui_->comboBoxRateOfChangeDimension->addItem("X", QVariant(0));
	ui_->comboBoxRateOfChangeDimension->addItem("Y", QVariant(1));
	ui_->comboBoxRateOfChangeDimension->addItem("Z", QVariant(2));
	ui_->comboBoxRateOfChangeDimension->setCurrentIndex(2);

	ui_->comboBoxFilterPositionDimension->addItem("X", QVariant(0));
	ui_->comboBoxFilterPositionDimension->addItem("Y", QVariant(1));
	ui_->comboBoxFilterPositionDimension->addItem("Z", QVariant(2));
	ui_->comboBoxFilterPositionDimension->setCurrentIndex(2);

	ui_->comboBoxInterpolationBase->addItem("Grid", QVariant(0));
	ui_->comboBoxInterpolationBase->addItem("Octree", QVariant(1));
	ui_->comboBoxInterpolationBase->setCurrentIndex(0);

	ui_->comboBoxInterpolationMethod->addItem("None", QVariant(0));
	ui_->comboBoxInterpolationMethod->addItem("Barycentric", QVariant(1));
	ui_->comboBoxInterpolationMethod->addItem("Linear", QVariant(2));
	ui_->comboBoxInterpolationMethod->setCurrentIndex(0);

	// Put the buttons into these groups to avoid auto toggeling etc.
	radioButtons2D3D_.addButton(ui_->radioButtonRender2D);
	radioButtons2D3D_.addButton(ui_->radioButtonRender3D);

	radioButtonsOriginalFiltered_.addButton(ui_->radioButtonOriginal);
	radioButtonsOriginalFiltered_.addButton(ui_->radioButtonFiltered);

	// Restore original situation.
	ui_->radioButtonOriginal->setChecked(true);
	ui_->radioButtonRender3D->setChecked(true);

	// Create the callback for the progress bar and connect the signals.
	callback_ = buw::makeReferenceCounted<OpenInfraPlatform::DataManagement::ProgressCallback>();
	//connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::activitySignal, ui_->progressBarPointCloudProcessing, &QProgressBar::setVisible);
	//connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::updateSignal, ui_->progressBarPointCloudProcessing, &QProgressBar::setValue);
	
	ui_->progressBarPointCloudProcessing->setVisible(false);


	// Make railways tab scrollable
	QScrollArea* scrollArea = new QScrollArea(this);
	QWidget* page = new QWidget(this);

	page->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	page->setLayout(ui_->verticalLayout_6);
	scrollArea->setWidget(page);
	scrollArea->setWidgetResizable(true);
	int idx = ui_->tabPointCloudProcessing->indexOf(ui_->tabRailways);
	ui_->tabPointCloudProcessing->removeTab(idx);
	ui_->tabPointCloudProcessing->addTab(scrollArea, tr("Railways"));

	//ui_->tabWidgetView->tabBar()->setContentsMargins(QMargins(0, 0, 100, 0));

#ifdef _DEBUG
	// Show debug menu only in debug mode

	QMenu* menuDebug = new QMenu("Debug");
	ui_->menuBar->addMenu(menuDebug);

	QAction* imageQualityBasedUnitTesting = menuDebug->addAction(tr("Image Quality Based Unit Testing"));
	QAction* actionGetCameraState = menuDebug->addAction(tr("Get Camera State"));
	QAction* actionShowMap = menuDebug->addAction(tr("Show/Hide Map"));
	QAction* actionReloadShader = menuDebug->addAction(tr("Reload shader"));
	QAction* actionAboutQt = menuDebug->addAction(tr("About Qt"));
	QAction* actionStoreGBuffer = menuDebug->addAction(tr("Store GBuffer"));
	QAction* actionCreateClothoid = menuDebug->addAction(tr("Create Clothoid"));
	QAction* actionShowVerticalAlignment3D = menuDebug->addAction(tr("Vertical alignment 3D"));
	QAction* actionLoadBridge = menuDebug->addAction(tr("Load Bridge"));
	QAction* actionPrecisionTest = menuDebug->addAction(tr("Precision Test"));

	QObject::connect(imageQualityBasedUnitTesting, &QAction::triggered, this, &MainWindow::ImageQualityBasedUnitTesting);
	QObject::connect(actionGetCameraState, &QAction::triggered, this, &MainWindow::actionGetCameraState);
	QObject::connect(actionShowMap, &QAction::triggered, this, &MainWindow::showMap);
	QObject::connect(actionReloadShader, &QAction::triggered, this, &MainWindow::reloadShader);
	QObject::connect(actionShowMap, &QAction::triggered, this, &MainWindow::showMap);
	QObject::connect(variantEditor_, &QtTreePropertyBrowser::currentItemChanged, this, &MainWindow::on_variantEditor_currentItemChanged);
	QObject::connect(actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
	QObject::connect(actionStoreGBuffer, &QAction::triggered, this, &MainWindow::storeGBuffer);
	QObject::connect(actionCreateClothoid, &QAction::triggered, this, &MainWindow::createClothoid);
	QObject::connect(actionShowVerticalAlignment3D, &QAction::triggered, this, &MainWindow::on_actionVertical_alignment_3D_triggered);
	QObject::connect(actionLoadBridge, &QAction::triggered, this, &MainWindow::on_actionLoad_Bridge);
	QObject::connect(actionPrecisionTest, &QAction::triggered, this, &MainWindow::on_actionPrecisionTest);

#endif

	ui_->tabMap->setVisible(false);

	Benchmark::getInstance().finishStartup();
	Benchmark::getInstance().print();

	// show data progress
	progressBar_ = new QProgressBar(ui_->statusBar);
	ui_->statusBar->addPermanentWidget(progressBar_);
	progressBar_->hide();
	

	progressDialog_ = new QProgressDialog(this);
	progressDialog_->setWindowTitle(tr("Please wait"));
	progressDialog_->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	progressDialog_->setMinimumWidth(500);
	progressDialog_->setAutoClose(false);
	progressDialog_->setAutoReset(false);
	progressDialog_->hide();
	QObject::connect(progressDialog_, SIGNAL(canceled()), this, SLOT(cancelJob()));
	QObject::disconnect(progressDialog_, SIGNAL(canceled()), progressDialog_, SLOT(cancel()));


	// Connect to the common progress dialog.
	connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::activitySignal, progressDialog_, &QProgressDialog::setEnabled);
	connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::activitySignal, progressDialog_, &QProgressDialog::setVisible);
	connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::activitySignal, progressDialog_, [&](bool value) {value ? progressDialog_->setRange(0, 100) : progressDialog_->setRange(0, 0); });
	connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::updateSignal, progressDialog_, &QProgressDialog::setValue);
	connect(callback_.get(), &OpenInfraPlatform::DataManagement::ProgressCallback::setMethodTitleSignal, progressDialog_, &QProgressDialog::setLabelText);

	ui_->doubleSpinBoxPointSize->setValue(3.0);
	on_doubleSpinBoxPointSize_valueChanged(3.0);

	retranslatePropertyBrowser();

	// check for updates
	updater = std::make_unique<QSimpleUpdater>(this);

	// set version and urls
	updater->setApplicationVersion(QApplication::applicationVersion());
	updater->setChangelogUrl(this->changeLogUrl);
	updater->setReferenceUrl(this->currentVersionUrl);
	updater->setDownloadUrl(this->installerUrl);
	updater->setSilent(true);

	connect(updater.get(), SIGNAL(checkingFinished()), this, SLOT(onCheckingFinished()));

	checkForUpdates();

	setAcceptDrops(true);
}

void OpenInfraPlatform::UserInterface::MainWindow::checkForUpdates() {
	updater->checkForUpdates();
}

void OpenInfraPlatform::UserInterface::MainWindow::onCheckingFinished() {
	/*
	if (updater->newerVersionAvailable())
	{
	    auto updateText = tr("There is a newer version (%1) available. Do you want to download?").arg(updater->latestVersion());
	    auto reply = QMessageBox::question(
	        this, //parent
	        tr("Update available"), //title
	        updateText, // text
	        QMessageBox::Yes | QMessageBox::No // stdbtn
	    );

	    if (reply == QMessageBox::Yes)
	    {
	        updater->downloadLatestVersion();
	    }
	}
	*/
}

void OpenInfraPlatform::UserInterface::MainWindow::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);

	if (!loaded_) {
		loaded_ = true;
		// "testdata/LandXML/CityCad/Sito_Tie.xml"
		// "testdata/Okstra/entwurf_s_achse-1_g_l_1014/Entwurf_S_Achse-1_G_L_1014.xml"
		bool testBlossCurve = false;
		if (!testBlossCurve) {
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		} else {
			double L = 20;
			double R = 5;

			{
				buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();
				buw::ReferenceCounted<buw::HorizontalAlignment2D> halignment = buw::makeReferenceCounted<buw::HorizontalAlignment2D>();

				buw::clothoidDescription cd;
				cd.clothoidConstant = sqrt(L * R);
				cd.counterClockwise = true;
				cd.entry = true;
				cd.length = L;
				cd.startCurvature = 0;
				cd.startDirection = 0;
				cd.startPosition = buw::Vector2d(0, 0);

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid> clothoid = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DClothoid>(cd);
				halignment->addElement(clothoid);

				alignment->setHorizontalAlignment(halignment);

				OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(alignment);
			}
			{
				/*buw::ReferenceCounted<buw::Alignment2DBased3D> alignment = buw::makeReferenceCounted<buw::Alignment2DBased3D>();
				buw::ReferenceCounted<buw::HorizontalAlignment2D> halignment = buw::makeReferenceCounted<buw::HorizontalAlignment2D>();

				buw::ReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve> bloss = buw::makeReferenceCounted<buw::HorizontalAlignmentElement2DBlossCurve>(R, L);
				halignment->addElement(bloss);

				alignment->setHorizontalAlignment(halignment);


				OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(alignment);*/
			}
		}
	}
}

OpenInfraPlatform::UserInterface::MainWindow::~MainWindow() {
	// todo:L consider using smart pointers here
	buw::safeDelete(exportExcelDialog_);
	buw::safeDelete(createClothoidDialog2_);
	buw::safeDelete(exportIfcAlignment1x0Dialog_);
	buw::safeDelete(exportIfcAlignment1x1Dialog_);
	buw::safeDelete(XYZImportDialog_);
	buw::safeDelete(preferencesDialog_);
	buw::safeDelete(generateTerrainDialog_);
	buw::safeDelete(LAAL_);
	buw::safeDelete(LAAAL_);
	buw::safeDelete(ACA_);
	buw::safeDelete(ACCA_);
	buw::safeDelete(LCCL_);
	buw::safeDelete(LCACL_);
	buw::safeDelete(LC_);
	buw::safeDelete(ACA2_);
	buw::safeDelete(ACCA2_);
	buw::safeDelete(verticalAlignmentWindow_);
	buw::safeDelete(curvatureWindow_);
	buw::safeDelete(ui_);

	plots_.clear();
}

void OpenInfraPlatform::UserInterface::MainWindow::storeGBuffer() {
	view_->storeGBuffer();
}

void OpenInfraPlatform::UserInterface::MainWindow::changeEvent(QEvent* evt) {
	if (evt->type() == QEvent::LanguageChange) {
		int pos = -1;

		std::string newTitle;

		// check if there is a match
		if ((pos = titleRegex.indexIn(this->windowTitle())) != -1) {
			// translate the matched string
			newTitle = tr(titleRegex.cap(1).toStdString().c_str()).toStdString();
		}

		// retranslate designer form (single inheritance approach)
		ui_->retranslateUi(this);

		if (pos != -1) {
			// update the title after it was overwritten by the normal translation call and if there was a match
			updateWindowTitle(newTitle);
		}

		retranslatePropertyBrowser();
	} else {
		// remember to call base class implementation
		QMainWindow::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::retranslatePropertyBrowser() {
	// attention: this function just works if R1>R2
	itemStartStation_->setPropertyName(tr("Start Station"));
	itemEndStation_->setPropertyName(tr("End Station"));
	itemLength_->setPropertyName(tr("Length [m]"));

	propertyHorizontalAlignment_->setPropertyName(tr("Horizontal Alignment"));
	propertyVerticalAlignment_->setPropertyName(tr("Vertical Alignment"));
	variantEditor_->translateHeader();
	on_comboBoxAlignment_currentIndexChanged(DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment());
}

void OpenInfraPlatform::UserInterface::MainWindow::dropEvent(QDropEvent* ev) {
	try {
		QStringList filePathList;
		if (ev->mimeData()->hasUrls()) {
			Q_FOREACH(QUrl url, ev->mimeData()->urls()) { filePathList << url.toLocalFile(); }
		}

		if (filePathList.size() > 0) {
			std::string DropName = filePathList[0].toStdString();

			if (boost::filesystem::exists(DropName)) {
				OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().clear();
				OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import(DropName);
				addToRecentFilesList(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().recentFileName);
				updateRecentFileActions();

				boost::filesystem::path p(DropName.c_str());
				updateWindowTitle(p.filename().string());
			}
			else {
				QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot import the dropped file. File does not exist."));
			}
		}
		else {
			QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot open the dropped file."));
		}
	}
	catch (const buw::Exception& exception) {
		QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot open the dropped file."));
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::dragEnterEvent(QDragEnterEvent* ev) {
	ev->accept();
}

void OpenInfraPlatform::UserInterface::MainWindow::emitPoints(QDialog* toolDialog) {
	toolDialog->setModal(true); // toolDialog gets total attetion, therefore the user can not draw points while toolDialog is open
	toolDialog->show();         // this happens: 1. toolDialog is shown 2. Offset and AlignmentPoints are deleted from screen and send to toolDialog
	std::vector<buw::Vector3d> viewPoints = view_->getAlignmentPoints(); // 3. user presses "Generate" in toolDialog 4. something is drawn on the sreen
	buw::Vector2d viewOffset = view_->getOffset().block<2, 1>(0, 0);
	Q_EMIT sendPoints(viewPoints, viewOffset);
}
void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Arc_Clothoid_Arc_triggered() {
	emitPoints(ACA_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Arc_Clothoid_Arc2_triggered() {
	emitPoints(ACA2_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Arc_Clothoid_Clothoid_Arc2_triggered() {
	emitPoints(ACCA2_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Arc_Clothoid_Clothoid_Arc_triggered() {
	emitPoints(ACCA_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Line_Clothoid_triggered() {
	emitPoints(LC_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Line_Clothoid_Arc_Clothoid_Line_triggered() {
	emitPoints(LCACL_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Line_Clothoid_Clothoid_Line_triggered() {
	emitPoints(LCCL_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Line_Arc_Arc_Line_triggered() {
	emitPoints(LAAL_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Line_Arc_Arc_Arc_Line_triggered() {
	emitPoints(LAAAL_);
}

void OpenInfraPlatform::UserInterface::MainWindow::createClothoid() {
	buw::Vector2d startPoint(0.0, 0.0);
	double L = 100;
	double A = 60;
	double R = A * A / L;
	buw::Vector2d endPoint;
	endPoint.x() = buw::HorizontalAlignmentElement2DClothoid::computeX(L, A);
	endPoint.y() = buw::HorizontalAlignmentElement2DClothoid::computeY(L, A);
	double radiusStart = std::numeric_limits<double>::infinity();
	double radiusEnd = R;
	bool clockwise = false;
	buw::Vector2d startDir = buw::createRotationMatrix<double>(0.0) * buw::Vector2d(1.0, 0.0);
	double tau = L / 2 * R;
	buw::Vector2d endDir = buw::createRotationMatrix<double>(tau) * buw::Vector2d(1.0, 0.0);
	buw::Line2d line1(startPoint, startPoint + startDir);
	buw::Line2d line2(endPoint, endPoint - endDir);
	buw::Vector2d pi;
	auto PI = buw::computeIntersection(line1, line2, pi);
	buw::ReferenceCounted<buw::HorizontalAlignmentElement2DClothoid_old> c =
	  std::make_shared<buw::HorizontalAlignmentElement2DClothoid_old>(startPoint, endPoint, pi, L, radiusStart, radiusEnd, clockwise);
	buw::ReferenceCounted<buw::HorizontalAlignment2D> horizontalAlignment = std::make_shared<buw::HorizontalAlignment2D>();
	horizontalAlignment->addElement(c);
	buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::make_shared<buw::Alignment2DBased3D>(horizontalAlignment);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().addAlignment(a);
}

//---------------------------------------------------------------------------//
// Recent files
//---------------------------------------------------------------------------//

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExit_triggered() {
	close();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionImport_OSM_File_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "OpenStreetMap (*.osm)");

	if (!filename.isNull()) {
		osmImportDialog_->setFilename(filename.toStdString());
		int r = osmImportDialog_->exec();

		if (r == QDialog::Accepted)
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().importOSM(
			  filename.toStdString(), osmImportDialog_->getFilterList(), osmImportDialog_->getMode());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile1_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile1);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile2_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile2);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile3_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile3);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile4_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile4);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile5_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile5);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile6_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile6);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile7_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile7);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile8_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile8);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile9_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile9);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRecentFile10_triggered() {
	openRecentFileViaAction(ui_->actionRecentFile10);
}

void OpenInfraPlatform::UserInterface::MainWindow::addToRecentFilesList(const QString& fileName) {
	const int MaxRecentFiles = 10;

	if (fileName.isEmpty())
		return;

	setWindowFilePath(fileName);

	QSettings settings;
	QStringList files = settings.value("recentFileList").toStringList();
	files.removeAll(fileName);
	files.prepend(fileName);
	while (files.size() > MaxRecentFiles)
		files.removeLast();

	settings.setValue("recentFileList", files);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionClearMenu_triggered() {
	QSettings settings;
	QStringList files = settings.value("recentFileList").toStringList();
	files.clear();
	settings.setValue("recentFileList", files);

	ui_->actionRecentFile1->setVisible(false);
	ui_->actionRecentFile2->setVisible(false);
	ui_->actionRecentFile3->setVisible(false);
	ui_->actionRecentFile4->setVisible(false);
	ui_->actionRecentFile5->setVisible(false);
	ui_->actionRecentFile6->setVisible(false);
	ui_->actionRecentFile7->setVisible(false);
	ui_->actionRecentFile8->setVisible(false);
	ui_->actionRecentFile9->setVisible(false);
	ui_->actionRecentFile10->setVisible(false);
}

//---------------------------------------------------------------------------//
// Other
//---------------------------------------------------------------------------//
void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportIIfcRoad_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("IfcRoad Step File (*.ifc);;Zip compressed IfcRoad Step File (*.ifczip)"));

	if (!filename.isNull()) {
		if (filename.endsWith(".ifc")) {
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcRoadTUMProposal(filename.toStdString());
		}

		else if (filename.endsWith("zip")) {
			QUuid id = QUuid::createUuid();
			QString tempFilename = QDir::currentPath().append(QString("/").append(id.toString().append(".ifc")));

			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcRoadTUMProposal(tempFilename.toStdString());

			OpenInfraPlatform::DataManagement::IfcZipper* ExportZipper = new OpenInfraPlatform::DataManagement::IfcZipper(nullptr, QString(filename.data()), tempFilename, DEFL);

			QObject::connect(&OpenInfraPlatform::AsyncJob::getInstance(), SIGNAL(finished()), ExportZipper, SLOT(start()));
			QObject::connect(ExportZipper, &OpenInfraPlatform::DataManagement::IfcZipper::finished, ExportZipper, &QObject::deleteLater);
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportIfcAlignment_triggered() {
	exportIfcAlignment1x0Dialog_->show();
}

/*new*/
void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportIfcZip_triggered() {
	exportIfcZipDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionAbout_triggered() {
	QString head, desc;

	head = tr("<h2><b>TUM Open Infra Platform 2018</b><br/></h2>");

	const QString copyright(tr("Copyright &copy; 2018"));

	desc = QString(
	         "Version %2<br/>%1<br/>Technische Universit&auml;t M&uuml;nchen<br/>"
	         "Faculty of Civil, Geo and Environmental Engineering<br/>"
	         "Chair of Computational Modeling and Simulation<br/><br/>"
	         "Website: <a href=\"http://www.cms.bgu.tum.de/oip\"><font color=\"#48B7E7\">http://www.cms.bgu.tum.de/oip</font></a><br/>"
	         "Please submit your bug reports or support requests to our repository <a href=\"https://bitbucket.org/tumcms/openinfraplatform\"><font "
	         "color=\"#48B7E7\">https://bitbucket.org/tumcms/openinfraplatform</font></a><br/><br/>")
	         .arg(copyright, updater->installedVersion());

	QMessageBox::about(this, tr("About TUM Open Infra Platform 2018"), head + desc);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionHorizontal_alignment_triggered() {
	ui_->actionHorizontal_alignment->setChecked(true);
	ui_->actionShow_Cross_Section->setEnabled(false);
	ui_->action3D->setChecked(false);

	view_->setView(eView::HorizontalAlignment);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionVertical_alignment_3D_triggered() {
	ui_->actionHorizontal_alignment->setChecked(false);
	ui_->actionShow_Cross_Section->setEnabled(false);
	ui_->action3D->setChecked(false);

	view_->enableHideTerrain(true);
	ui_->actionTerrain_Hide->setChecked(true);
	view_->setView(eView::VerticalAlignment);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_action3D_triggered() {
	ui_->actionHorizontal_alignment->setChecked(false);
	ui_->actionShow_Cross_Section->setEnabled(true);
	ui_->action3D->setChecked(true);

	view_->setView(eView::ThreeDimensional);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionVertical_alignment_triggered() {
	ui_->actionVertical_alignment->setChecked(true);
	verticalAlignmentWindow_->show();
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, verticalAlignmentWindow_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCurvature_triggered() {
	ui_->actionCurvature->setChecked(true);
	curvatureWindow_->show();
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, curvatureWindow_);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_IFC_tree_triggered()
{
	showIFCtree_->show();
}


void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Hide_triggered(bool checked) {
	view_->enableHideTerrain(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Wireframe_triggered(bool checked) {
	view_->enableDrawTerrainWireframe(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Textured_triggered(bool checked) {
	view_->enableTerrainTextured(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Gradient_Ramp_triggered(bool checked) {
	view_->enableTerrainGradientRamp(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Iso_Lines_triggered(bool checked) {
	view_->enableIsoLines(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionMerge_XYZ_File_triggered() {
	XYZImportDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Generate_Random_Terrain_triggered() {
	generateTerrainDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionTerrain_Create_Terrain_from_Heightmap_triggered() {
	QString openFile =
	  QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Portable Network Graphics (*.png);;Bitmap (*.bmp);;JPEG (*.jpg);;TIFF (*.tif)"));

	if (openFile.isNull() == false) {
		std::string filename = openFile.toUtf8().constData();

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().createTerrainFromHeightMap(filename);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_Cross_Section_triggered(bool checked) {
	view_->showCrossSection(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_Design_Cross_Section_triggered(bool checked) {
	view_->showDesignCrossSection(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRoad_body_wireframe_triggered(bool checked) {
	view_->showRoadBodyWireframe(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRoad_body_solid_triggered(bool checked) {
	view_->showRoadBodySolid(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionDraw_Road_Texture_triggered(bool checked) {
	view_->drawRoadTexture(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportVerticalAlignment_triggered() {
	verticalAlignmentWindow_->exportToFile();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportLandInfra_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("LandInfra (*.xml)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportLandInfra(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportPointCloud_triggered()
{
	if(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud().get() != nullptr) {
		QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("*.bin;;*.las"));
		if(!filename.isNull()) {
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportPointCloud(filename.toStdString());
		}
	}
	else {
		QMessageBox dialog;
		dialog.setStandardButtons(QMessageBox::StandardButton::Ok);
		dialog.setIcon(QMessageBox::Icon::Warning);
		dialog.setText("No Point Cloud to export available.");
		dialog.setWindowTitle(tr("Disclaimer"));
		dialog.setWindowFlags(((Qt::Dialog) | (Qt::MSWindowsFixedSizeDialogHint)));
		dialog.exec();
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportCurvature_triggered() {
	curvatureWindow_->exportToFile();
}

void OpenInfraPlatform::UserInterface::MainWindow::updateAlignmentUI() {
	buw::ReferenceCounted<buw::AlignmentModel> am = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel();

	ui_->comboBoxAlignment->clear();
	for (int i = 0; i < am->getAlignmentCount(); i++) {
		buw::ReferenceCounted<buw::IAlignment3D> alignment = am->getAlignment(i);

		ui_->comboBoxAlignment->addItem(alignment->getName().toCString());
	}

	if (am->getAlignmentCount() > 0) {
		if (am->getAlignment(0)->getType() == buw::e3DAlignmentType::e2DBased) {
			buw::ReferenceCounted<buw::Alignment2DBased3D> a = std::static_pointer_cast<buw::Alignment2DBased3D>(am->getAlignment(0));

			buw::ReferenceCounted<buw::Alignment2DBased3D> currentAlignment = a;

			itemStartStation_->setValue(currentAlignment->getStartStation());
			itemEndStation_->setValue(currentAlignment->getEndStation());
			itemLength_->setValue(currentAlignment->getLength());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::updateAlignmentElementsUI() {
	int index = DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment();

	// clear horizontal alignment properties
	propertyHorizontalAlignment_->subProperties().clear();

	// clear vertical alignment properties
	propertyVerticalAlignment_->subProperties().clear();

	buw::ReferenceCounted<buw::AlignmentModel> am = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel();

	if (am->getAlignmentCount() > index && index >= 0) {
		if (am->getAlignment(index)->getType() != buw::e3DAlignmentType::e2DBased) {
			buw::ReferenceCounted<buw::Alignment3DBased3D> currentAlignment = std::static_pointer_cast<buw::Alignment3DBased3D>(am->getAlignment(index));

			itemStartStation_->setValue(currentAlignment->getStartStation());
			itemEndStation_->setValue(currentAlignment->getEndStation());
			itemLength_->setValue(currentAlignment->getLength());
			ui_->comboBoxAlignment->setCurrentIndex(index);

			return;
		}

		buw::ReferenceCounted<buw::Alignment2DBased3D> currentAlignment = std::static_pointer_cast<buw::Alignment2DBased3D>(am->getAlignment(index));

		itemStartStation_->setValue(currentAlignment->getStartStation());
		itemEndStation_->setValue(currentAlignment->getEndStation());
		itemLength_->setValue(currentAlignment->getLength());
		ui_->comboBoxAlignment->setCurrentIndex(index);

		if (currentAlignment->hasVerticalAlignment()) {
			for (int k = 0; k < currentAlignment->getVerticalAlignment()->getAlignmentElementCount(); k++) {
				auto va = currentAlignment->getVerticalAlignment()->getAlignmentElementByIndex(k);
				std::string type = buw::verticalAlignmentTypeToString(va->getAlignmentType());

				auto itemVerticalAlignment = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(), tr("Vertical Alignment (%1)").arg(type.c_str()));

				propertyVerticalAlignment_->addSubProperty(itemVerticalAlignment);

				auto start = va->getStartPosition();
				auto end = va->getEndPosition();

				double length = end.x() - start.x();

				// start position
				auto itemStart = variantManager_->addProperty(QVariant::PointF, tr("Start"));
				itemStart->setValue(QPointF(start.x(), start.y()));
				itemStart->setAttribute(QLatin1String("decimals"), 4);
				itemVerticalAlignment->addSubProperty(itemStart);

				// end position
				auto itemEnd = variantManager_->addProperty(QVariant::PointF, tr("End"));
				itemEnd->setValue(QPointF(end.x(), end.y()));
				itemEnd->setAttribute(QLatin1String("decimals"), 4);
				itemVerticalAlignment->addSubProperty(itemEnd);

				// length
				auto itemLength = variantManager_->addProperty(QVariant::Double, tr("Length [m]"));
				itemLength->setValue(length);
				itemVerticalAlignment->addSubProperty(itemLength);

				// start gradient
				double startGradient = 0;
				va->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::StartGradient, &startGradient);
				auto itemStartGradient = variantManager_->addProperty(QVariant::Double, tr("Start gradient"));
				itemStartGradient->setValue(startGradient);
				itemVerticalAlignment->addSubProperty(itemStartGradient);
			}
		}

		for (int k = 0; k < currentAlignment->getHorizontalAlignment()->getAlignmentElementCount(); k++) {
			// current alignment segment
			auto ha = currentAlignment->getHorizontalAlignment()->getAlignmentElementByIndex(k);
			std::string type = buw::horizontalAlignmentTypeToString(ha->getAlignmentType());

			auto itemHorizontalAlignment = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(), tr("Horizontal Alignment (%1)").arg(tr(type.c_str())));

			propertyHorizontalAlignment_->addSubProperty(itemHorizontalAlignment);

			auto horizontalElement = currentAlignment->getHorizontalAlignment()->getAlignmentElementByIndex(k);
			auto start = horizontalElement->getStartPosition();
			auto end = horizontalElement->getEndPosition();

			// start position
			auto itemStart = variantManager_->addProperty(QVariant::PointF, tr("Start"));
			itemStart->setValue(QPointF(start.x(), start.y()));
			itemStart->setAttribute(QLatin1String("decimals"), 4);
			itemHorizontalAlignment->addSubProperty(itemStart);

			// end position
			auto itemEnd = variantManager_->addProperty(QVariant::PointF, tr("End"));
			itemEnd->setValue(QPointF(end.x(), end.y()));
			itemEnd->setAttribute(QLatin1String("decimals"), 4);
			itemHorizontalAlignment->addSubProperty(itemEnd);

			// length
			auto itemLength = variantManager_->addProperty(QVariant::Double, tr("Length [m]"));
			itemLength->setValue(ha->getLength());
			itemHorizontalAlignment->addSubProperty(itemLength);

			switch (ha->getAlignmentType()) {
			case buw::eHorizontalAlignmentType::Arc: {
				double radius = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Radius, &radius);
				auto itemRadius = variantManager_->addProperty(QVariant::Double, tr("Radius [m]"));
				itemRadius->setValue(radius);
				itemHorizontalAlignment->addSubProperty(itemRadius);

				bool ccw = true;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise, &ccw);
				auto itemCCW = variantManager_->addProperty(QVariant::Bool, tr("Counterclockwise"));
				itemCCW->setValue(ccw);
				itemHorizontalAlignment->addSubProperty(itemCCW);
			} break;

			case buw::eHorizontalAlignmentType::Clothoid: {
				// ClothoidConstant
				double clothoidConstant = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::ClothoidConstant, &clothoidConstant);
				auto itemClothoidConstant = variantManager_->addProperty(QVariant::Double, tr("Clothoid constant (A) [m�]"));
				itemClothoidConstant->setValue(clothoidConstant);
				itemHorizontalAlignment->addSubProperty(itemClothoidConstant);

				// Radius Start
				double RadiusStart = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &RadiusStart);

				if (buw::isInfinite(RadiusStart)) {
					auto itemRadiusStart = variantManager_->addProperty(QVariant::String, tr("Radius Start [m]"));
					itemRadiusStart->setValue(QVariant(tr("infinite")));
					itemHorizontalAlignment->addSubProperty(itemRadiusStart);
				} else {
					auto itemRadiusStart = variantManager_->addProperty(QVariant::Double, tr("Radius Start [m]"));
					itemRadiusStart->setValue(RadiusStart);
					itemHorizontalAlignment->addSubProperty(itemRadiusStart);
				}

				// Radius End
				double RadiusEnd = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &RadiusEnd);

				if (buw::isInfinite(RadiusEnd)) {
					auto itemRadiusEnd = variantManager_->addProperty(QVariant::String, tr("Radius End [m]"));
					itemRadiusEnd->setValue(tr("infinite"));
					itemHorizontalAlignment->addSubProperty(itemRadiusEnd);
				} else {
					auto itemRadiusEnd = variantManager_->addProperty(QVariant::Double, tr("Radius End [m]"));
					itemRadiusEnd->setValue(RadiusEnd);
					itemHorizontalAlignment->addSubProperty(itemRadiusEnd);
				}

				bool ccw = true;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise, &ccw);
				auto itemCCW = variantManager_->addProperty(QVariant::Bool, tr("Counterclockwise"));
				itemCCW->setValue(ccw);
				itemHorizontalAlignment->addSubProperty(itemCCW);

				// PI
				buw::Vector2d pointOfIntersection;
				bool hasPI = ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pointOfIntersection);
				auto itemPI = variantManager_->addProperty(QVariant::PointF, tr("Point of Intersection"));
				itemPI->setValue(QPointF(pointOfIntersection.x(), pointOfIntersection.y()));
				itemPI->setAttribute(QLatin1String("decimals"), 4);
				itemHorizontalAlignment->addSubProperty(itemPI);
			} break;

			case buw::eHorizontalAlignmentType::Bloss: {
				// Radius Start
				double RadiusStart = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusStart, &RadiusStart);

				if (buw::isInfinite(RadiusStart)) {
					auto itemRadiusStart = variantManager_->addProperty(QVariant::String, tr("Radius Start [m]"));
					itemRadiusStart->setValue(QVariant(tr("infinite")));
					itemHorizontalAlignment->addSubProperty(itemRadiusStart);
				} else {
					auto itemRadiusStart = variantManager_->addProperty(QVariant::Double, tr("Radius Start [m]"));
					itemRadiusStart->setValue(RadiusStart);
					itemHorizontalAlignment->addSubProperty(itemRadiusStart);
				}

				// Radius End
				double RadiusEnd = 0;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::RadiusEnd, &RadiusEnd);

				if (buw::isInfinite(RadiusEnd)) {
					auto itemRadiusEnd = variantManager_->addProperty(QVariant::String, tr("Radius End [m]"));
					itemRadiusEnd->setValue(tr("infinite"));
					itemHorizontalAlignment->addSubProperty(itemRadiusEnd);
				} else {
					auto itemRadiusEnd = variantManager_->addProperty(QVariant::Double, tr("Radius End [m]"));
					itemRadiusEnd->setValue(RadiusEnd);
					itemHorizontalAlignment->addSubProperty(itemRadiusEnd);
				}

				bool ccw = true;
				ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::Counterclockwise, &ccw);
				auto itemCCW = variantManager_->addProperty(QVariant::Bool, tr("Counterclockwise"));
				itemCCW->setValue(ccw);
				itemHorizontalAlignment->addSubProperty(itemCCW);

				// PI
				buw::Vector2d pointOfIntersection;
				bool hasPI = ha->genericQuery(OpenInfraPlatform::Infrastructure::eAlignmentElementQueryId::PI, &pointOfIntersection);
				auto itemPI = variantManager_->addProperty(QVariant::PointF, tr("Point of Intersection"));
				itemPI->setValue(QPointF(pointOfIntersection.x(), pointOfIntersection.y()));
				itemPI->setAttribute(QLatin1String("decimals"), 4);
				itemHorizontalAlignment->addSubProperty(itemPI);
			} break;

			default: break;
			}
		}
	} else {
		itemStartStation_->setValue(0);
		itemEndStation_->setValue(0);
		itemLength_->setValue(0);

		while (propertyHorizontalAlignment_->subProperties().size() > 0) {
			propertyHorizontalAlignment_->removeSubProperty(propertyHorizontalAlignment_->subProperties()[0]);
		}

		while (propertyVerticalAlignment_->subProperties().size() > 0) {
			propertyVerticalAlignment_->removeSubProperty(propertyVerticalAlignment_->subProperties()[0]);
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::onChange() {
	onChange(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getLatesChangeFlag());
}

void OpenInfraPlatform::UserInterface::MainWindow::onChange(ChangeFlag changeFlag) {
	if (changeFlag & ChangeFlag::AlignmentModel)
		updateAlignmentUI();
	if (changeFlag & ChangeFlag::AlignmentModel || changeFlag & ChangeFlag::Preferences || changeFlag & ChangeFlag::SelectedAlignmentIndex)
		updateAlignmentElementsUI();

	if (changeFlag & ChangeFlag::DigitalElevationModel) {
		buw::ReferenceCounted<buw::DigitalElevationModel> dem = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getDigitalElevationModel();

		ui_->comboBoxSurfaces->clear();
		for (int i = 0; i < dem->getSurfaceCount(); i++) {
			buw::ReferenceCounted<buw::Surface> surface = dem->getSurface(i);

			ui_->comboBoxSurfaces->addItem(surface->getName());
		}
	}

	if (changeFlag & ChangeFlag::ProxyModel) {
		buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::ProxyModel> pm = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();

		if (pm->hasIfc4x1Data()) {
			for (auto it = pm->getIfc4x1Data().begin(); it != pm->getIfc4x1Data().end(); ++it) {
				ui_->listWidgetProxies->addItem(it->second->classname());
			}

			ui_->listWidgetProxies->addItem("muh");
		}
	}

	if(changeFlag & ChangeFlag::PointCloud) {
		auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		if(pointCloud) {
			auto eigenvectorsView = new OpenInfraPlatform::UserInterface::VectorTableModel(pointCloud->getEigenvectors<3>());			
			ui_->tableViewEigenmatrix->setModel(eigenvectorsView);

			Eigen::Matrix<double, 3, 3> boundingBox = Eigen::Matrix<double, 3, 3>();
			CCVector3 min, max;
			pointCloud->getBoundingBox(min, max);
			CCVector3 bbCenter = 0.5 *(min + max);

			boundingBox.row(0) = Eigen::Vector3d(min.x, min.y, min.z).transpose();
			boundingBox.row(1) = Eigen::Vector3d(max.x, max.y, max.z).transpose();
			boundingBox.row(2) = Eigen::Vector3d(bbCenter.x, bbCenter.y, bbCenter.z).transpose();

			auto boundingBoxView = new OpenInfraPlatform::UserInterface::VectorTableModel(boundingBox);
			ui_->tableViewBoundingBox->setModel(boundingBoxView);

			ui_->labelPointCloudSizeValue->setText(QString::number(pointCloud->size()));
			ui_->labelPointCloudSectionsValue->setText(QString::number(pointCloud->getSections().size()));
		}
	}

}

void OpenInfraPlatform::UserInterface::MainWindow::on_comboBoxAlignment_currentIndexChanged(int index) {
	if (index != DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment() && index != -1) {
		buw::ReferenceCounted<buw::SelectAlignment> actionSelectAlignment = std::make_shared<buw::SelectAlignment>(index);
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(actionSelectAlignment);
	}
	if (ui_->comboBoxAlignment->currentIndex() != index) {
		ui_->comboBoxAlignment->setCurrentIndex(index);
		ui_->comboBoxAlignment->update();
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionLandXML_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("LandXML (*.xml)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportLandXML(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxHighlightSelectedAlignmentSegment_clicked(bool checked) {
	view_->setHighlightSelectedAlignmentSegment(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionAdvancedSVG_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("Scalable Vector Graphics (*.svg)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportSVGAdvanced(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionUsualSVG_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("Scalable Vector Graphics (*.svg)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportSVG(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCheck_for_Updates_triggered() {
	checkForUpdates();
	if (!updater->newerVersionAvailable()) {
		QMessageBox::information(this, tr("No updates available"), tr("You already have the newest version!"), QMessageBox::Ok);
	}
	// FvUpdater::sharedUpdater()->CheckForUpdatesNotSilent();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionPreferences_triggered() {
	preferencesDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionAdd_Georeference_triggered() {
	addGeoreferenceDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxShowMap_clicked(bool checked) {
	view_->enableMap(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionViewport_as_screenshot_triggered() {
	QString filename =
	  QFileDialog::getSaveFileName(this, tr("Save Screenshot"), QDir::currentPath(), tr("Portable Network Graphics (*.png);;Bitmap (*.bmp);;JPEG (*.jpg);;TIFF (*.tif)"));

	if (!filename.isNull()) {
		view_->saveAsScreenshot(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::updateRecentFileActions() {
	int MaxRecentFiles = 10;
	QSettings settings;
	QStringList files = settings.value("recentFileList").toStringList();

	int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

	// buw::LogManager::getInstance().Log(files.join(" ").toStdString());

	// Updating the recent files list
	for (int i = 0; i < numRecentFiles; i++) {
		if (i == 0) {
			ui_->actionRecentFile1->setVisible(true);
			ui_->actionRecentFile1->setText(QString("1 - ") + files[i]);
		}
		if (i == 1) {
			ui_->actionRecentFile2->setVisible(true);
			ui_->actionRecentFile2->setText(QString("2 - ") + files[i]);
		}
		if (i == 2) {
			ui_->actionRecentFile3->setVisible(true);
			ui_->actionRecentFile3->setText(QString("3 - ") + files[i]);
		}
		if (i == 3) {
			ui_->actionRecentFile4->setVisible(true);
			ui_->actionRecentFile4->setText(QString("4 - ") + files[i]);
		}
		if (i == 4) {
			ui_->actionRecentFile5->setVisible(true);
			ui_->actionRecentFile5->setText(QString("5 - ") + files[i]);
		}
		if (i == 5) {
			ui_->actionRecentFile6->setVisible(true);
			ui_->actionRecentFile6->setText(QString("6 - ") + files[i]);
		}
		if (i == 6) {
			ui_->actionRecentFile7->setVisible(true);
			ui_->actionRecentFile7->setText(QString("7 - ") + files[i]);
		}
		if (i == 7) {
			ui_->actionRecentFile8->setVisible(true);
			ui_->actionRecentFile8->setText(QString("8 - ") + files[i]);
		}
		if (i == 8) {
			ui_->actionRecentFile9->setVisible(true);
			ui_->actionRecentFile9->setText(QString("9 - ") + files[i]);
		}
		if (i == 9) {
			ui_->actionRecentFile10->setVisible(true);
			ui_->actionRecentFile10->setText(QString("10 - ") + files[i]);
		}
	}
}

QString OpenInfraPlatform::UserInterface::MainWindow::strippedName(const QString& fullFileName) {
	return QFileInfo(fullFileName).fileName();
}

void OpenInfraPlatform::UserInterface::MainWindow::ImageQualityBasedUnitTesting() {
	prepareTest(0);
}

void OpenInfraPlatform::UserInterface::MainWindow::prepareTest(int i) {
	inUnitTest_ = i;

	switch (i) {
	case 0:
		//--------------------------------------------------------------------------
		// testdata/LandXML/Ji/B15n_Data/B15n.xml
		// --------------------------------------------------------------------------

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/B15n_Data/B15n.xml");
		break;

	case 1:
		//--------------------------------------------------------------------------
		// testdata/LandXML/Mainbruecke_Klingenberg.xml
		// --------------------------------------------------------------------------

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		break;

	case 2:

		// ###############################################################################################################################
		// testdata/LandXML/LandXMLDemo.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/AutoCAD Civil 3D/LandXMLDemo.xml");
		break;

	case 3:
		// ###############################################################################################################################
		// testdata/LandXML/ProVI/002LR.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/ProVI/002LR.xml");
		break;

	case 4:
		// ###############################################################################################################################
		// testdata/LandXML/AutoCAD Civil 3D/debug.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/AutoCAD Civil 3D/debug.xml");
		break;

	case 5:
		// ###############################################################################################################################
		// testdata/LandXML/HbfMhfZweiteStammstrecke/HbfMhfZweiteStammstrecke.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/HbfMhfZweiteStammstrecke/HbfMhfZweiteStammstrecke.xml");
		break;

	case 6:
		// ###############################################################################################################################
		// testdata/LandXML/HbfMhfZweiteStammstrecke/2teStammstreckeBeide.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/HbfMhfZweiteStammstrecke/2teStammstreckeBeide.xml");
		break;

	case 7:
		// ###############################################################################################################################
		// testdata/LandXML/CityCad/Sito_Tie.xml"
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/CityCad/Sito_Tie.xml");
		break;

	case 8:
		// ###############################################################################################################################
		// testdata/LandXML/RIB STRATIS/BAB_A6.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/RIB STRATIS/BAB_A6.xml");
		break;

	case 9:
		// ###############################################################################################################################
		// testdata/LandXML/RIB STRATIS/St2237-Sulzkirchen.xml
		// ###############################################################################################################################

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/RIB STRATIS/St2237-Sulzkirchen.xml");
		break;

	case 10:
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("testdata/LandXML/Mainbruecke_Klingenberg.xml");
		break;

		//// export Oktra
		// case 11:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstra("Mainbruecke_Klingenberg_OKSTRA_export_1_13.xml", "1.013");
		//	break;

		// case 12:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstra("Mainbruecke_Klingenberg_OKSTRA_export_1_14.xml", "1.014");
		//	break;

		// case 13:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstra("Mainbruecke_Klingenberg_OKSTRA_export_1_13.cte", "1.013");
		//	break;

		// case 14:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstra("Mainbruecke_Klingenberg_OKSTRA_export_1_14.cte", "1.014");
		//	break;

		//// import Okstra
		// case 15:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("Mainbruecke_Klingenberg_OKSTRA_export_1_13.xml");
		//	break;

		// case 16:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("Mainbruecke_Klingenberg_OKSTRA_export_1_14.xml");
		//	break;

		// case 17:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("Mainbruecke_Klingenberg_OKSTRA_export_1_13.cte");
		//	break;

		// case 18:
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import("Mainbruecke_Klingenberg_OKSTRA_export_1_14.cte");
		//	break;

	case 11:
		// ###############################################################################################################################
		// add future tests here
		// ###############################################################################################################################

		// test finished
		if (tester_.didAllTestSucceed()) {
			BLUE_LOG(warning) << "All unit test succeeded.";
		} else {
			BLUE_LOG(error) << "A unit test failed.";
		}

		tester_.writeTestHomepage();

		system("test_report.html");
	default: inUnitTest_ = -1;
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::performTest(int i) {
	// buw::testDescription td;

	// view_->setViewportSize(650, 453);

	// buw::ReferenceCounted<buw::InfraCameraController> controller = view_->getInfraCameraController();
	// buw::ReferenceCounted<buw::InfraCamera> camera = controller->getCamera();
	// camera->setTargetDistance(0, buw::InfraCamera::CAMERA);

	// switch (i)
	//{
	// case 0:
	//{
	//	// todo implement Camera Controller and fix ImageQualityBasedUnitTesting

	//	/*buw::ZoomInputController zic(9.17751f);
	//	zic.setWindowSize( view__->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(10.1539, -4.112, 0));
	//	pic.setWindowSize( view__->getSize() );
	//	buw::Arcballf arcBall(view__->getSize());
	//	buw::quaternionf q(0.241491, 0.204704, 0.0054324, 0.948551);
	//	arcBall.setCurrentQuaternion(q);

	//	view__->setZoomInputController(zic);
	//	view__->setPanInputController(pic);*/

	//	camera->setPosition(-11.4155, 2.26471, -0.161588, buw::InfraCamera::CAMERA);

	//	actionGetCameraState();
	//}

	//	view_->saveAsScreenshot("B15n_solid.png");

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("B15n_wireframe.png");

	//	view_->enableHideTerrain(true);
	//	view_->saveAsScreenshot("B15n_hide.png");

	//	view_->showCrossSection(true);
	//	view_->saveAsScreenshot("B15n_crossSection.png");

	//	view_->showDesignCrossSection(true);
	//	view_->saveAsScreenshot("B15n_designCrossSection.png");

	//	view_->connectCrossSections(true);
	//	view_->saveAsScreenshot("B15n_roadBody_wireframe.png");

	//	view_->doSolidCrossSections(true);
	//	view_->saveAsScreenshot("B15n_roadBody_solid.png");

	//	// solid
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_solid.png";
	//	td.screenshotImageFilename = "B15n_solid.png";
	//	td.differenceImageFilename = "B15n_solid_diff.png";
	//	tester_.createTest(td);

	//	// wireframe
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_wireframe.png";
	//	td.screenshotImageFilename = "B15n_wireframe.png";
	//	td.differenceImageFilename = "B15n_wireframe_diff.png";
	//	tester_.createTest(td);

	//	// crossSection
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_crossSection.png";
	//	td.screenshotImageFilename = "B15n_crossSection.png";
	//	td.differenceImageFilename = "B15n_crossSection_diff.png";
	//	tester_.createTest(td);

	//	// designCrossSection
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_designCrossSection.png";
	//	td.screenshotImageFilename = "B15n_designCrossSection.png";
	//	td.differenceImageFilename = "B15n_designCrossSection_diff.png";
	//	tester_.createTest(td);

	//	// roadBody_wireframe
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_roadBody_wireframe.png";
	//	td.screenshotImageFilename = "B15n_roadBody_wireframe.png";
	//	td.differenceImageFilename = "B15n_roadBody_wireframe_diff.png";
	//	tester_.createTest(td);

	//	// roadBody_solid
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_roadBody_solid.png";
	//	td.screenshotImageFilename = "B15n_roadBody_solid.png";
	//	td.differenceImageFilename = "B15n_roadBody_solid_diff.png";
	//	tester_.createTest(td);

	//	{
	//		/*buw::ZoomInputController zic(10.1972f);
	//		zic.setWindowSize( view__->getSize() );
	//		buw::PanInputController pic(buw::Vector3f(11.7991, 1.08442, 0));
	//		pic.setWindowSize( view__->getSize() );
	//		buw::Arcballf arcBall(view__->getSize());
	//		buw::quaternionf q(0.0747937, 0.350785, 0.0886735, 0.929243);
	//		arcBall.setCurrentQuaternion(q);

	//		view__->setZoomInputController(zic);
	//		view__->setPanInputController(pic);*/

	//		camera->setPosition(-9.95493, 0.188848, -2.98082, buw::InfraCamera::CAMERA);
	//		camera->setRotation(-0.602219, -0.198517);
	//	}

	//	view_->drawRoadTexture(true);
	//	view_->saveAsScreenshot("B15n_roadBody_texture.png");

	//	// roadBody_texture
	//	td.LandXMLFile = "testdata/LandXML/B15n_Data/B15n.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/B15n_roadBody_texture.png";
	//	td.screenshotImageFilename = "B15n_roadBody_texture.png";
	//	td.differenceImageFilename = "B15n_roadBody_texture_diff.png";
	//	tester_.createTest(td);

	//	view_->enableHideTerrain(false);
	//	view_->enableDrawTerrainWireframe(false);
	//	view_->showCrossSection(false);
	//	view_->showDesignCrossSection(false);
	//	view_->connectCrossSections(false);
	//	view_->doSolidCrossSections(false);
	//	view_->drawRoadTexture(false);
	//	break;

	// case 1:
	//{
	//	/*buw::ZoomInputController zic(1.59441f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(0, 0, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.353553, 0.353553, 0.146447, 0.853553);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);
	//}

	//	view_->setHighlightDifferentAlignmentElements(true);
	//	view_->setView(eView::HorizontalAlignment);

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_wireframe.png");

	//	view_->enableDrawTerrainWireframe(false);
	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/Mainbruecke_Klingenberg_wireframe.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_wireframe.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_wireframe_diff.png";
	//	tester_.createTest(td);

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/Mainbruecke_Klingenberg_solid.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_solid.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_solid_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 2:
	//{
	//	/*buw::ZoomInputController zic(0.6561f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(0, 0, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.382683, 0, 0, 0.92388);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(1.14259, 8.25856, 10.3035, buw::InfraCamera::CAMERA);
	//	camera->setRotation(0, -0.785398);
	//}

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("LandXMLDemo_wireframe.png");

	//	view_->enableDrawTerrainWireframe(false);
	//	view_->saveAsScreenshot("LandXMLDemo_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/LandXMLDemo.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/LandXMLDemo_wireframe.png";
	//	td.screenshotImageFilename = "LandXMLDemo_wireframe.png";
	//	td.differenceImageFilename = "LandXMLDemo_wireframe_diff.png";
	//	tester_.createTest(td);

	//	td.LandXMLFile = "testdata/LandXML/LandXMLDemo.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/LandXMLDemo_solid.png";
	//	td.screenshotImageFilename = "LandXMLDemo_solid.png";
	//	td.differenceImageFilename = "LandXMLDemo_solid_diff.png";
	//	tester_.createTest(td);
	//	break;
	// case 3:
	//{
	//	/*buw::ZoomInputController zic(4.75327f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(6.2592, 3.99767, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.524936, 0.434153, 0.358105, 0.638525);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(-6.46104, 1.31923, -4.42941, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-1.32624, -1.28056);
	//}

	//	view_->saveAsScreenshot("LR_highlight.png");

	//	td.LandXMLFile = "testdata/LandXML/ProVI/002LR.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/LR_highlight.png";
	//	td.screenshotImageFilename = "LR_highlight.png";
	//	td.differenceImageFilename = "LR_highlight_diff.png";
	//	tester_.createTest(td);

	//	{
	//		/*buw::ZoomInputController zic(1.72f);
	//		zic.setWindowSize( view_->getSize() );
	//		buw::PanInputController pic(buw::Vector3f(-7.43867, 1.64686, 0));
	//		pic.setWindowSize( view_->getSize() );
	//		buw::Arcballf arcBall(view_->getSize());
	//		buw::quaternionf q(0.707107, 0, 0, 0.707107);
	//		arcBall.setCurrentQuaternion(q);

	//		view_->setZoomInputController(zic);
	//		view_->setPanInputController(pic);*/

	//		camera->setPosition(8.5536, 4.06355, 2.05648, buw::InfraCamera::CAMERA);
	//		camera->setRotation(0, -1.5708);
	//	}

	//	view_->saveAsScreenshot("LR_highlight1.png");

	//	td.LandXMLFile = "testdata/LandXML/ProVI/002LR.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/LR_highlight1.png";
	//	td.screenshotImageFilename = "LR_highlight1.png";
	//	td.differenceImageFilename = "LR_highlight1_diff.png";
	//	tester_.createTest(td);

	//	{
	//		/*buw::ZoomInputController zic(5.68f);
	//		zic.setWindowSize( view_->getSize() );
	//		buw::PanInputController pic(buw::Vector3f(-16.1039, 8.09029, 0));
	//		pic.setWindowSize( view_->getSize() );
	//		buw::Arcballf arcBall(view_->getSize());
	//		buw::quaternionf q(0.707107, 0, 0, 0.707107);
	//		arcBall.setCurrentQuaternion(q);

	//		view_->setZoomInputController(zic);
	//		view_->setPanInputController(pic);*/

	//		camera->setPosition(15.9367, 1.72737, 8.01137, buw::InfraCamera::CAMERA);
	//		camera->setRotation(0, -1.5708);
	//	}

	//	view_->saveAsScreenshot("LR_highlight2.png");

	//	td.LandXMLFile = "testdata/LandXML/ProVI/002LR.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/LR_highlight2.png";
	//	td.screenshotImageFilename = "LR_highlight2.png";
	//	td.differenceImageFilename = "LR_highlight2_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 4:
	//{
	//	/*buw::ZoomInputController zic(0.2235f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(0.0848, 0.544186, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.707107, 0, 0, 0.707107);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(0, 41.4423, -1.8115e-006, buw::InfraCamera::CAMERA);
	//	camera->setRotation(0, -1.5708);
	//}

	//	view_->saveAsScreenshot("debug_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/AutoCAD Civil 3D/debug.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/debug_solid.png";
	//	td.screenshotImageFilename = "debug_solid.png";
	//	td.differenceImageFilename = "debug_solid_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 5:
	//{
	//	/*buw::ZoomInputController zic(0.4635f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(0.0848, 0.544186, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.707107, 0, 0, 0.707107);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(0, 20.986, -9.17325e-007, buw::InfraCamera::CAMERA);
	//	camera->setRotation(0, -1.5708);
	//}

	//	view_->saveAsScreenshot("HbfMhfZweiteStammstrecke_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/HbfMhfZweiteStammstrecke/HbfMhfZweiteStammstrecke.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/HbfMhfZweiteStammstrecke_solid.png";
	//	td.screenshotImageFilename = "HbfMhfZweiteStammstrecke_solid.png";
	//	td.differenceImageFilename = "HbfMhfZweiteStammstrecke_solid_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 6:
	//{
	//	/*buw::ZoomInputController zic(0.325793f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(-54.2547, 7.44686, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.707107, 0, 0, 0.707107);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(48.6722, 38.1715, 8.81073, buw::InfraCamera::CAMERA);
	//	camera->setRotation(0, -1.5708);
	//}

	//	view_->saveAsScreenshot("2teStammstreckeBeide_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/HbfMhfZweiteStammstrecke/2teStammstreckeBeide.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/2teStammstreckeBeide_solid.png";
	//	td.screenshotImageFilename = "2teStammstreckeBeide_solid.png";
	//	td.differenceImageFilename = "2teStammstreckeBeide_solid_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 7:
	//{
	//	/*buw::ZoomInputController zic(5.26349925994873f);
	//	buw::PanInputController pic(buw::Vector3f(0.0848000049591064f, 0.544185996055603f,0.0f));
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.101465873420238, 0.832729339599609f, 0.117100700736046f, 0.531558096408844f);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(-5.05528, 0.0531676, -0.724832, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-1.73223, -0.0722984);
	//}

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("Sito_Tie_wireframe.png");
	//	view_->repaint();

	//	view_->enableDrawTerrainWireframe(false);
	//	view_->saveAsScreenshot("Sito_Tie_solid.png");
	//	view_->repaint();

	//	td.LandXMLFile = "testdata/LandXML/CityCad/Sito_Tie.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/Sito_Tie_wireframe.png";
	//	td.screenshotImageFilename = "Sito_Tie_wireframe.png";
	//	td.differenceImageFilename = "Sito_Tie_wireframe_diff.png";
	//	tester_.createTest(td);

	//	td.LandXMLFile = "testdata/LandXML/CityCad/Sito_Tie.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/Sito_Tie_solid.png";
	//	td.screenshotImageFilename = "Sito_Tie_solid.png";
	//	td.differenceImageFilename = "Sito_Tie_solid_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 8:
	//{
	//	/*buw::ZoomInputController zic(0.0618648f);
	//	zic.setWindowSize( view_->getSize() );
	//	buw::PanInputController pic(buw::Vector3f(0, 0, 0));
	//	pic.setWindowSize( view_->getSize() );
	//	buw::Arcballf arcBall(view_->getSize());
	//	buw::quaternionf q(0.357112, -0.0255371, 0.00388029, 0.933704);
	//	arcBall.setCurrentQuaternion(q);

	//	view_->setZoomInputController(zic);
	//	view_->setPanInputController(pic);*/

	//	camera->setPosition(-32.6753, 116.124, 120.469, buw::InfraCamera::CAMERA);
	//	camera->setRotation(0.263894, -0.785398);
	//}

	//	view_->saveAsScreenshot("BAB_A6_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/RIB STRATIS/BAB_A6.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/BAB_A6_solid.png";
	//	td.screenshotImageFilename = "BAB_A6_solid.png";
	//	td.differenceImageFilename = "BAB_A6_solid_diff.png";
	//	tester_.createTest(td);

	//	{
	//		/*buw::ZoomInputController zic(0.253603f);
	//		zic.setWindowSize( view_->getSize() );
	//		buw::PanInputController pic(buw::Vector3f(-42.7497, -9.97028, 0));
	//		pic.setWindowSize( view_->getSize() );
	//		buw::Arcballf arcBall(view_->getSize());
	//		buw::quaternionf q(0.357112, -0.0255371, 0.00388029, 0.933704);
	//		arcBall.setCurrentQuaternion(q);

	//		view_->setZoomInputController(zic);
	//		view_->setPanInputController(pic);*/

	//		camera->setPosition(-24.4327, 23.6264, 45.2104, buw::InfraCamera::CAMERA);
	//		camera->setRotation(-0.101497, -0.562088);
	//	}

	//	view_->saveAsScreenshot("BAB_A6_solid2.png");

	//	td.LandXMLFile = "testdata/LandXML/RIB STRATIS/BAB_A6.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/BAB_A6_solid2.png";
	//	td.screenshotImageFilename = "BAB_A6_solid2.png";
	//	td.differenceImageFilename = "BAB_A6_solid2_diff.png";
	//	tester_.createTest(td);

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("BAB_A6_wireframe.png");

	//	td.LandXMLFile = "testdata/LandXML/RIB STRATIS/BAB_A6.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/BAB_A6_wireframe.png";
	//	td.screenshotImageFilename = "BAB_A6_wireframe.png";
	//	td.differenceImageFilename = "BAB_A6_wireframe_diff.png";
	//	tester_.createTest(td);
	//	break;

	// case 9:
	//	{
	//		/*buw::ZoomInputController zic(0.297273f);
	//		zic.setWindowSize( view_->getSize() );
	//		buw::PanInputController pic(buw::Vector3f(-5.8896, 0.218605, 0));
	//		pic.setWindowSize( view_->getSize() );
	//		buw::Arcballf arcBall(view_->getSize());
	//		buw::quaternionf q(0.553946, -0.0107373, 0.0469264, 0.831159);
	//		arcBall.setCurrentQuaternion(q);

	//		view_->setZoomInputController(zic);
	//		view_->setPanInputController(pic);*/

	//		camera->setPosition(4.91942, 22.8379, 21.5173, buw::InfraCamera::CAMERA);
	//		camera->setRotation(-0.0067665, -0.832903);
	//	}

	//	view_->enableDrawTerrainWireframe(false);
	//	view_->saveAsScreenshot("St2237-Sulzkirchen_solid.png");

	//	td.LandXMLFile = "testdata/LandXML/RIB STRATIS/St2237-Sulzkirchen.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/St2237-Sulzkirchen_solid.png";
	//	td.screenshotImageFilename = "St2237-Sulzkirchen_solid.png";
	//	td.differenceImageFilename = "St2237-Sulzkirchen_solid_diff.png";
	//	tester_.createTest(td);

	//	view_->enableDrawTerrainWireframe(true);
	//	view_->saveAsScreenshot("St2237-Sulzkirchen_wireframe.png");

	//	td.LandXMLFile = "testdata/LandXML/RIB STRATIS/St2237-Sulzkirchen.xml";
	//	td.referenceImageFilename = "UnitTesting/ReferenceImages/St2237-Sulzkirchen_wireframe.png";
	//	td.screenshotImageFilename = "St2237-Sulzkirchen_wireframe.png";
	//	td.differenceImageFilename = "St2237-Sulzkirchen_wireframe_diff.png";
	//	tester_.createTest(td);
	//	break;
	// case 10:
	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);

	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_ref_okstra.png");
	//	break;

	// case 15:
	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);

	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_okstra_1_13_XML.png");

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "Mainbruecke_Klingenberg_ref_okstra.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_okstra_1_13_XML.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_okstra_diff_1_13_XML.png";
	//	tester_.createTest(td);
	//	break;
	// case 16:
	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);

	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_okstra_1_14_XML.png");

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "Mainbruecke_Klingenberg_ref_okstra.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_okstra_1_14_XML.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_okstra_diff_1_14_XML.png";
	//	tester_.createTest(td);
	//	break;
	// case 17:
	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);

	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_okstra_1_13_CTE.png");

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "Mainbruecke_Klingenberg_ref_okstra.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_okstra_1_13_CTE.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_okstra_diff_1_13_CTE.png";
	//	tester_.createTest(td);
	//	break;
	// case 18:
	//	camera->setPosition(-2.22567, 3.94321, 3.06439, buw::InfraCamera::CAMERA);
	//	camera->setRotation(-0.433057, -0.975246);

	//	view_->saveAsScreenshot("Mainbruecke_Klingenberg_okstra_1_14_CTE.png");

	//	td.LandXMLFile = "testdata/LandXML/Mainbruecke_Klingenberg.xml";
	//	td.referenceImageFilename = "Mainbruecke_Klingenberg_ref_okstra.png";
	//	td.screenshotImageFilename = "Mainbruecke_Klingenberg_okstra_1_14_CTE.png";
	//	td.differenceImageFilename = "Mainbruecke_Klingenberg_okstra_diff_1_14_CTE.png";
	//	tester_.createTest(td);
	//	break;
	// default:
	//	break;
	//}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionOpen_triggered() {
	try {
		handle_actionOpen_triggered();
		addToRecentFilesList(OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().recentFileName);
		updateRecentFileActions();
	} catch (const buw::Exception& exception) {
		QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot open the selected file."));
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionNew_triggered() {
	handle_actionNew_triggered();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionSave_triggered() {
	handle_actionSave_triggered();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionSaveAs_triggered() {
	handle_actionSaveAs_triggered();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionUndo_triggered() {
	handle_actionUndo_triggered();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionRedo_triggered() {
	handle_actionRedo_triggered();
}

// void OpenInfraPlatform::UserInterface::MainWindow::on_actionImport_triggered()
// {
// 	try
// 	{
// 		handle_actionImport_triggered();
// 	}
// 	catch (const buw::Exception& exception)
// 	{
// 		QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot import the selected file."));
// 	}
// }

void OpenInfraPlatform::UserInterface::MainWindow::jobStarting() {
	progressDialog_->setDisabled(false);
	progressDialog_->setModal(true);
	progressDialog_->setRange(0, 0);
	progressDialog_->setLabelText("");
	progressDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::jobRunning(int id, float progress, const std::string& message) {
	if (progress > 0) {
		progressDialog_->setRange(0, 1000);
		progressDialog_->setValue((int)(progress * 1000));
	}

	progressDialog_->setLabelText(message.c_str());
}

void OpenInfraPlatform::UserInterface::MainWindow::jobFinishing(int id, bool completed) {
#ifdef BLUE_DEBUG
	progressDialog_->setLabelText(QString("magic in progress..."));
#else
	progressDialog_->setLabelText(QString("finishing up..."));
#endif // DEBUG

	progressDialog_->setRange(0, 1);
	progressDialog_->setValue(1);
	progressDialog_->repaint();
}

void OpenInfraPlatform::UserInterface::MainWindow::jobFinished(int id, bool comepleted) {
	// progressBar_->hide();
	progressDialog_->hide();

	if (inUnitTest_ >= 0) {
		performTest(inUnitTest_);
		prepareTest(inUnitTest_ + 1);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::cancelJob() {
	OpenInfraPlatform::AsyncJob::getInstance().cancelJob();
	progressDialog_->setLabelText("Canceling");
	progressDialog_->setDisabled(true);
}

void OpenInfraPlatform::UserInterface::MainWindow::actionGetCameraState() {
	/*auto cameraController = view_->getInfraCameraController();
	auto camera = cameraController->getCamera();

	std::ostream& out = std::cout;

	auto pos = camera->getPosition(buw::InfraCamera::CAMERA);
	auto rot = camera->getRotation();
	out << "camera->setPosition(" << pos.x() << ", " << pos.y() << ", " << pos.z() << ", buw::InfraCamera::CAMERA);" << std::endl;
	out << "camera->setRotation(" << rot.x() << ", " << rot.y() << ");" << std::endl;*/
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionMerge_LAS_File_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::currentPath(), tr("LAS cloud (*.las)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().importLAS(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::openRecentFileViaAction(QAction* actionRecentFile) {
	std::string fileName = actionRecentFile->text().toUtf8().constData();
	fileName = fileName.substr(4, fileName.length());

	if (boost::filesystem::exists(fileName)) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import(fileName);
		addToRecentFilesList(fileName.c_str());
		updateRecentFileActions();
		boost::filesystem::path p(fileName.c_str());
		updateWindowTitle(p.filename().string());
	} else {
		QMessageBox::warning(this, QApplication::applicationName(), tr("Cannot import the selected file. File does not exist."));
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::showMap() {
	static bool checked = false;
	checked = !checked;
	view_->enableMap(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_variantEditor_currentItemChanged(QtBrowserItem* item) {
	// std::cout << "Selected a Qt BrowserItem." << std::endl;
}

//---------------------------------------------------------------------------//
// Debugging
//---------------------------------------------------------------------------//

void OpenInfraPlatform::UserInterface::MainWindow::reloadShader() {
	view_->reloadShader();
}

//---------------------------------------------------------------------------//
// Create alignment
//---------------------------------------------------------------------------//

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Alignment_Points_triggered(bool checked) {
	view_->enableCreatePoints(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Alignment_triggered() {
	buw::Vector2d offset = view_->getOffset().block<2, 1>(0, 0);

	auto points = view_->getAlignmentPoints();

	if (points.size() <= 1) {
		return;
	}

	if (points.size() == 2) {
		buw::Vector2d A = points[0].block<2, 1>(0, 0);
		buw::Vector2d B = points[1].block<2, 1>(0, 0);

		// create horizontal alignment
		buw::Vector2d start = buw::Vector2d(points[0].x(), points[0].y()) + offset;
		buw::Vector2d end = buw::Vector2d(points[1].x(), points[1].y()) + offset;
		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start, end);
		buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();
		ha->addElement(line);
		make3DLine(ha);
		return;
	}

	buw::Vector2d A = points[0].block<2, 1>(0, 0);
	buw::Vector2d B = points[1].block<2, 1>(0, 0);
	buw::Vector2d C = points[2].block<2, 1>(0, 0);

	buw::ReferenceCounted<buw::HorizontalAlignment2D> ha = std::make_shared<buw::HorizontalAlignment2D>();

	// double angle = buw::calculateAngleBetweenVectors( A-B, C-B );

	for (int i = 0; i < points.size() - 1; i++) {
		buw::Vector2d start = buw::Vector2d(points[i + 0].x(), points[i + 0].y()) + offset;
		buw::Vector2d end = buw::Vector2d(points[i + 1].x(), points[i + 1].y()) + offset;

		buw::ReferenceCounted<buw::HorizontalAlignmentElement2DLine> line = std::make_shared<buw::HorizontalAlignmentElement2DLine>(start, end);
		ha->addElement(line);
	}
	make3DLine(ha);
}
void OpenInfraPlatform::UserInterface::MainWindow::aboutQt() {
	QMessageBox::aboutQt(this);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_Help_triggered() {
	HelpBrowser::showPage("index.html");
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_Log_File_triggered() {
	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	std::wstringstream ss;
	ss << localAppData << L"/OpenInfraPlatform/";

	CoTaskMemFree(static_cast<void*>(localAppData));
	// setup converter
	std::wstring_convert<convert_type, wchar_t> converter;

	// use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::wstring filename = L"log.txt";

#ifndef _DEBUG
	filename = ss.str().append(L"log.txt");
#endif

	ShellExecute(0, 0, filename.c_str(), 0, 0, SW_SHOW);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionOkstra_triggered() {
	QString version;
	QString filename = QFileDialog::getSaveFileName(
	  this,
	  tr("Save Document"),
	  QDir::currentPath(),
	  tr("OKSTRA 2.017 (*.xml);;OKSTRA 2.016 (*.xml);;OKSTRA 1.014 (*.xml);; OKSTRA 1.013 (*.xml);; OKSTRA 1.014 (*.cte);; OKSTRA 1.013 (*.cte);; "), // tr("OKSTRA 2.016 (*.xml);;
	                                                                                                                                                  // OKSTRA 1.014 (*.xml);;
	                                                                                                                                                  // OKSTRA 1.013 (*.xml);;
	                                                                                                                                                  // OKSTRA 2.016 (*.cte);;
	                                                                                                                                                  // OKSTRA 1.014 (*.cte);;
	                                                                                                                                                  // OKSTRA 1.013 (*.cte)"),
	  &version);

	if (!filename.isNull()) {
		version = version.split(" ")[1];
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstra(filename.toStdString(), version.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionOkstra_translated_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("OKSTRA 2.017 (*.xml);;"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstraTranslated(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionifcOWL4x1Export_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("Turtle (*.ttl);;RDF/XML-ABBREV (*.rdf);; All files (*.*)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcOWL4x1(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionOkstraOWL_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("Turtle (*.ttl);;RDF/XML-ABBREV (*.rdf);; All files (*.*)"));

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportOkstraOWL(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_spinBoxOctreeLevel_valueChanged(int value)
{
	view_->getViewport()->setOctreeLevel(value);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxShowOctree_clicked(bool checked)
{
	view_->getViewport()->setShowOctree(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonDeleteSelectedAlignment_clicked() {
	int index = ui_->comboBoxAlignment->currentIndex();

	buw::ReferenceCounted<buw::AlignmentModel> am = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel();

	if (am->getAlignmentCount() > index && index >= 0) {
		buw::ReferenceCounted<buw::IAlignment3D> a = am->getAlignment(index);

		buw::ReferenceCounted<buw::DeleteAlignment> actionDeleteAlignment = std::make_shared<buw::DeleteAlignment>(a);
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(actionDeleteAlignment);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonDeleteSurface_clicked() {
	int index = ui_->comboBoxSurfaces->currentIndex();

	buw::ReferenceCounted<buw::DigitalElevationModel> dem = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getDigitalElevationModel();

	if (dem->getSurfaceCount() > index && index >= 0) {
		buw::ReferenceCounted<buw::Surface> s = dem->getSurface(index);

		buw::ReferenceCounted<buw::DeleteSurface> actionDeleteSurface = std::make_shared<buw::DeleteSurface>(s);
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(actionDeleteSurface);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::updateActionUndo(unsigned int numberOfUndoActions) {
	if (numberOfUndoActions > 0) {
		ui_->actionUndo->setEnabled(true);
	} else {
		ui_->actionUndo->setEnabled(false);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::updateActionRedo(unsigned int numberOfRedoActions) {
	if (numberOfRedoActions > 0) {
		ui_->actionRedo->setEnabled(true);
	} else {
		ui_->actionRedo->setEnabled(false);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExport_Terrain_As_Heightmap_triggered() {
	QString openFile =
	  QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("Portable Network Graphics (*.png);;Bitmap (*.bmp);;JPEG (*.jpg);;TIFF (*.tif)"));

	if (openFile.isNull() == false) {
		buw::ReferenceCounted<OpenInfraPlatform::Infrastructure::DigitalElevationModel> dem =
		  OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getDigitalElevationModel();

		buw::Vector3d tmin, tmax;
		dem->getSurfacesExtend(tmin, tmax);

		float width = tmax.x() - tmin.x();
		float depth = tmax.y() - tmin.y();

		float aspect = depth / width;

		buw::ReferenceCounted<buw::Image3b> img = std::make_shared<buw::Image3b>(256, 256 * aspect);

		double minHeight = 1000000000;
		double maxHeight = 0;

		for (int y = 0; y < img->getHeight(); y++) {
			for (int x = 0; x < img->getWidth(); x++) {
				buw::Vector2d postiton = buw::Vector2d(x / static_cast<float>(img->getWidth()) * width + tmin.x(), y / static_cast<float>(img->getHeight()) * depth + tmin.y());

				double dHeight = dem->getHeightAtPosition(postiton) / 128.0;

				if (dHeight > maxHeight) {
					maxHeight = dHeight;
				}

				if (dHeight < minHeight) {
					minHeight = dHeight;
				}

				int height = std::max(0, std::min(255, static_cast<int>(255 * dHeight)));
				buw::Color3b c(height, height, height);
				img->setPixelColor(x, y, c);
			}
		}

		std::cout << minHeight << std::endl;
		std::cout << maxHeight << std::endl;

		buw::storeImage(openFile.toStdString().c_str(), *img.get());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionIfcAlignment_buildingSMART_P6_Excel_Comparison_triggered() {
	exportExcelDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_License_and_Copyright_Information_triggered() {
	if (licenseAndCopyrightInformationDialog_ == nullptr) {
		licenseAndCopyrightInformationDialog_ = new LicenseAndCopyrightInformationDialog(this);
	}

	licenseAndCopyrightInformationDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionShow_Log_Folder_triggered() {
	// TODO: Find a way to do this with pure Qt or move it at least to an own
	// function that can be reused by on_actionShow_Log_File_triggered
	wchar_t* localAppData = 0;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

	QString path = QDir::toNativeSeparators(QString::fromWCharArray(localAppData) + "/OpenInfraPlatform");
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionImport_IFC_Alignment_1_0_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "IFC Alignment 1.0 (*.ifc)");

	if (!filename.isNull()) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().importIfcAlignment1_0(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionAlignments_as_3D_Points_txt_triggered() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("Normal text file (*.txt)"));

	if (filename.isNull() == false) {
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().export3DAlignmentAsTextfile(filename.toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxShowDifferentAlignmentElements_clicked(bool checked) {
	view_->setDifferentColorsForAlignmentElements(checked);
	verticalAlignmentWindow_->setDifferentColorsForHorizontalAlignmentElements(checked);
	curvatureWindow_->setDifferentColorsForHorizontalAlignmentElements(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxDifferentColorsForVerticalAlignmentElements_clicked(bool checked) {
	verticalAlignmentWindow_->setDifferentColorsForVerticalAlignmentElements(checked);
	curvatureWindow_->setDifferentColorsForVerticalAlignmentElements(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxUseUniformColor_clicked(bool checked) {
	view_->setUseUniformPointColor(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxUseUniformSize_clicked(bool checked) {
	view_->setUseUniformPointSize(checked);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxShowPointCloud_clicked(bool checked)
{
	view_->setShowPointCloud(checked);
}


void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonSelectUniformColor_clicked()
{
	pcdUniformColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonSelectFilteredPointsColor_clicked()
{
	pcdFilteredPointsColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyDuplicateFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		// Initialize the filter parameters.
		buw::DuplicateFilterDescription desc;
		desc.dim = ui_->radioButtonRender3D->isChecked() ? 
			OpenInfraPlatform::Infrastructure::Enums::ePointCloudFilterDimension::Volume3D :
			OpenInfraPlatform::Infrastructure::Enums::ePointCloudFilterDimension::Sections2D;
		desc.minDistance = ui_->doubleSpinBoxRemoveDuplicatesThreshold->value() / 1000.0;

		// Apply the filter and pass the callback for updating the UI, then update the indices for rendering.
		pointCloud->applyDuplicateFilter(desc, callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetDuplicateFilter_clicked()
{
	// Get the point cloud and reset the scalar field called "Duplicate" which holds the labeling for duplicates.
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetScalarField("Duplicate");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyDensityFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		// Initialize the filter parameters
		buw::LocalDensityFilterDescription desc;
		desc.dim = ui_->radioButtonRender3D->isChecked() ?
			OpenInfraPlatform::Infrastructure::Enums::ePointCloudFilterDimension::Volume3D :
			OpenInfraPlatform::Infrastructure::Enums::ePointCloudFilterDimension::Sections2D;
		desc.kernelRadius = (float)(ui_->doubleSpinBoxFilterDensityKernelRadius->value()) / 100.0f;
		desc.minThreshold = ui_->doubleSpinBoxFilterDensityThreshold->value();
		desc.density = CCLib::GeometricalAnalysisTools::Density(ui_->comboBoxFilterDensityMetric->currentData().toInt());

		// Apply the filter and pass the callback for updating the UI, then update the indices for rendering.
		int err = pointCloud->applyLocalDensityFilter(desc, callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetDensityFilter_clicked()
{
	// Get the point cloud and reset the scalar field called "Density" which holds the labeling for points which have a density below the minimum threshold.
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetScalarField("Density");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyPositionFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::PositionFilterDescription desc;
		desc.minValue = ui_->doubleSpinBoxFilterPositionMin->value();
		desc.maxValue = ui_->doubleSpinBoxFilterPositionMax->value();
		desc.dimension = ui_->comboBoxFilterPositionDimension->currentData().toInt();

		if(pointCloud->applyPositionFilter(desc, callback_) == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		} 
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetPositionFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		if(pointCloud->resetPositionFilter() == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyRelativeHeightFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::RelativeHeightFilterDescription desc;
		desc.lowerBound = ui_->doubleSpinBoxFilterHeightLowerBound->value();
		desc.upperBound = ui_->doubleSpinBoxFilterHeightUpperBound->value();

		if(pointCloud->applyRelativeHeightWithGridFilter(desc, callback_) == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetRelativeHeightFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		if(pointCloud->resetPositionFilter() == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonFilterOriginal_clicked()
{
	QMessageBox dialog;	
	dialog.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
	dialog.setIcon(QMessageBox::Icon::Question);
	dialog.setText("This will remove the filtered points from the cloud and can only be undone by reloading the original file.\nDo you want to continue?");
	dialog.setWindowTitle(tr("Disclaimer"));
	dialog.setWindowFlags(((Qt::Dialog) | (Qt::MSWindowsFixedSizeDialogHint)));

	if(dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		if(pointCloud) {
			pointCloud->removeFilteredPoints(callback_);
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonRestoreOriginal_clicked()
{
	QMessageBox dialog;
	dialog.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
	dialog.setIcon(QMessageBox::Icon::Question);
	dialog.setText("This will load the original file and discard all unsaved changes.\nDo you want to continue?");
	dialog.setWindowTitle(tr("Disclaimer"));
	dialog.setWindowFlags(((Qt::Dialog) | (Qt::MSWindowsFixedSizeDialogHint)));
	if(dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().import(pointCloud->getName().toStdString());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonExtractSegmentation_clicked()
{
	QMessageBox dialog;
	dialog.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
	dialog.setIcon(QMessageBox::Icon::Question);
	dialog.setText("This will extract the segmented points from the cloud and can not be reversed.\nDo you want to continue?");
	dialog.setWindowTitle(tr("Disclaimer"));
	dialog.setWindowFlags(((Qt::Dialog) | (Qt::MSWindowsFixedSizeDialogHint)));

	if(dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		if(pointCloud) {
			pointCloud->removeNotSegmentedPoints();
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonUndoSegmentation_clicked()
{
	on_pushButtonRestoreOriginal_clicked();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyPercentileSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::PercentileSegmentationDescription desc;
		desc.kernelRadius = ui_->doubleSpinBoxPercentileSegmentationKernelRadius->value() / 100.0f;
		desc.lowerPercentile = ui_->doubleSpinBoxPercentileSegmentationLowerBound->value() / 100.0;
		desc.upperPercentile = ui_->doubleSpinBoxPercentileSegmentationUpperBound->value() / 100.0;
		desc.minThreshold = ui_->doubleSpinBoxPercentileSegmentationMinThreshold->value() / 100.0f;
		desc.maxThreshold = ui_->doubleSpinBoxPercentileSegmentationMaxThreshold->value() / 100.0f;

		pointCloud->applyPercentilesSegmentationHP(desc, callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetPercentileSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetScalarField("SegmentedPercentile");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_doubleSpinBoxPercentileSegmentationKernelRadius_valueChanged(double value)
{
	ui_->horizontalSliderPercentileSegmentationKernelRadius->blockSignals(true);
	ui_->horizontalSliderPercentileSegmentationKernelRadius->setValue(value);
	ui_->horizontalSliderPercentileSegmentationKernelRadius->blockSignals(false);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputePercentilesOnGrid_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->applyPercentilesOnGridSegmentation(callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyRateOfChangeSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::RateOfChangeSegmentationDescription desc;
		desc.dim = ui_->comboBoxRateOfChangeDimension->currentData().toInt();
		desc.maxNeighbourDistance = ui_->doubleSpinBoxRateOfChangeNeighbourDistance->value();
		desc.maxRateOfChangeThreshold = ui_->doubleSpinBoxRateOfChangeMaxDiff->value();
		int err = pointCloud->applyRateOfChangeSegmentation(desc, callback_);
		if(err != 0) {
			BLUE_LOG(warning) << "Rate of change segmentation failed. Error Code: " << err;
		}
		else {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetRateOfChangeSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetScalarField("SegmentedRateOfChange");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeGrid_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::GridComputationDescription desc;
		desc.size = ui_->spinBoxGridSize->value();
		desc.kernelRadius = ui_->doubleSpinBoxGridKernelRadius->value();
		pointCloud->computeGrid(desc, callback_);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetGrid_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetGrid();
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeChainage_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::ChainageComputationDescription desc;
		desc.base = (Infrastructure::Enums::eChainageComputationBase) ui_->comboBoxInterpolationBase->currentData().toInt();
		desc.bUseInterpolation = ui_->checkBoxInterpolation->isChecked();
		desc.interpolation = (Infrastructure::Enums::eChainageComputationInterpolationMethod) ui_->comboBoxInterpolationMethod->currentData().toInt();
		desc.bUseSmoothing = ui_->checkBoxSmoothing->isChecked();
		desc.sigma = ui_->doubleSpinBoxSmoothingSigma->value();
		desc.sigmaSF = ui_->doubleSpinBoxSmoothingSigmaSF->value();

		pointCloud->computeChainage(desc, callback_);

	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetChainage_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud)
		pointCloud->resetScalarField("Chainage");
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplySegmentRailways_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		//buw::RailwaySegmentationDescription desc;
		//desc.distanceForPCA = ui_->doubleSpinBoxDistanceForPCA->value();
		//desc.numPointsForPCA = ui_->spinBoxNumPointsForPCA->value();
		//desc.centerlinePointDistance = ui_->doubleSpinBoxDistanceForPCA->value() / (float)ui_->spinBoxNumPointsForPCA->value();
		//desc.minSegmentPoints = ui_->spinBoxMinSegmentPoints->value();
		//desc.minSegmentLength = ui_->doubleSpinBoxMinSegmentLength->value();
		//desc.curvatureStepSize = ui_->spinBoxCurvatureStepSize->value();
		//desc.numPointsForMeanCurvature = ui_->spinBoxNumPointsForMeanCurvature->value();
		//
		//
		//int numAlignments = pointCloud->segmentRailways(desc, callback_);
		//if(numAlignments > 0) {
		//	for(int idx = 0; idx < numAlignments; idx++) {
		//		ui_->comboBoxPlotSelectAlignment->addItem(QString::number(idx), QVariant(QString::number(idx)));
		//	}
		//	ui_->pushButtonComputeCurvature->setEnabled(true);
		//	ui_->pushButtonPlotAlignment->setEnabled(true);
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		//}
		//else if(numAlignments == 0) {
		//	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		//	BLUE_LOG(info) << "No railways detected.";
		//}
		//else {
		//	BLUE_LOG(warning) << "Error in railway segmentation occurred. Code: " << numAlignments;
		//	on_pushButtonResetSegmentRailways_clicked();
		//}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetSegmentRailways_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		BLUE_LOG(info) << "Resetting railway segmentation.";
		if(pointCloud->resetRailwaySegmentation() == 0) {
			ui_->pushButtonComputeCurvature->setDisabled(true);
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		}
		else {
			BLUE_LOG(warning) << "Resetting railway segmentation failed.";
		}
		// Clear our plotting combo box since we only want to plot the latest results.
		ui_->comboBoxPlotSelectAlignment->clear();
		ui_->pushButtonPlotAlignment->setDisabled(true);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeCenterlines_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	
	if(pointCloud) {

		buw::CenterlineComputationDescription desc;		
		desc.filterDuplicates = ui_->checkBoxCenterpointsApplyDuplicateFilter->isChecked();
		desc.duplicateDistance = ui_->doubleSpinBoxCenterpointsDuplicateDistance->value();

		desc.filterDensity = ui_->checkBoxCenterpointsApplyDensityFilter->isChecked();
		desc.densityKernelRadius = ui_->doubleSpinBoxCenterpointsDensityFilterKernelRadius->value();
		desc.densityThreshold = ui_->spinBoxCenterpointsDensityThreshold->value();

		desc.sortingFarDistance = ui_->doubleSpinBoxSortingFarDistance->value();
		desc.sortingCloseDistance = ui_->doubleSpinBoxCenterlineMaxDistance->value();
		desc.sortingCloseRatio = ui_->doubleSpinBoxSortingNearRatio->value();
		desc.sortingFarRatio = ui_->doubleSpinBoxSortingFarRatio->value();

		desc.fuseCenterlines = ui_->checkBoxFuseCenterlines->isChecked();
		desc.fuseCenterlinesFarDistance = ui_->doubleSpinBoxFuseCenterlinesFarDistance->value();
		desc.fuseCenterlinesFarRatio = ui_->doubleSpinBoxFuseCenterlinesFarRatio->value();
		desc.fuseCenterlinesCloseDistance = ui_->doubleSpinBoxFuseCenterlinesNearDistance->value();
		desc.fuseCenterlinesCloseRatio = ui_->doubleSpinBoxFuseCenterlinesNearRatio->value();

		desc.fuseAlignments = ui_->checkBoxFuseAlignments->isChecked();
		desc.fuseAlignmentsFarDistance = ui_->doubleSpinBoxFuseAlignmentsFarDistance->value();
		desc.fuseAlignmentsFarRatio = ui_->doubleSpinBoxFuseAlignmentsFarRatio->value();
		desc.fuseAlignmentsCloseDistance = ui_->doubleSpinBoxFuseAlignmentsNearDistance->value();
		desc.fuseAlignmentsCloseRatio = ui_->doubleSpinBoxFuseAlignmentsNearRatio->value();

		desc.centerlineSmoothing = ui_->checkBoxCenterlineSmoothing->isChecked();
		desc.centerlineDensity = ui_->doubleSpinBoxCenterlineDensity->value() / 1000.0; // convert from millimeter to meter.

		desc.centerlineSampling = ui_->checkBoxCenterlineSampling->isChecked();
		desc.samplingLengthForPCA = ui_->doubleSpinBoxSamplingLengthForPCA->value();
		desc.samplingStepSize = ui_->doubleSpinBoxSamplingStepSize->value() / 1000.0; // convert from millimeter to meter.

		desc.minCenterlinePoints = ui_->spinBoxCenterlinesMinNumPoints->value();
		desc.minCenterlineLength = ui_->doubleSpinBoxCenterlinesMinLength->value();

		desc.minSegmentPoints = ui_->spinBoxMinSegmentPoints->value();
		desc.minSegmentLength = ui_->doubleSpinBoxMinSegmentLength->value();

		int numAlignments = pointCloud->computeCenterlines(desc, callback_);
		if(numAlignments > 0) {
	
			ui_->pushButtonComputeCurvature->setEnabled(true);
	
			// Clear the combo boxes for plotting since we only want to plot the stuff from the latest computations.
			ui_->comboBoxShowAlignment->clear();
			ui_->comboBoxComputeCurvature->clear();
			ui_->comboBoxPlotSelectAlignment->clear();
	
			// Add the indices to the combo boxes.
			for(int idx = 0; idx < numAlignments; idx++) {
				ui_->comboBoxShowAlignment->addItem(QString::number(idx), QVariant(QString::number(idx)));
				ui_->comboBoxComputeCurvature->addItem(QString::number(idx), QVariant(QString::number(idx)));
			}
	
			ui_->comboBoxShowAlignment->addItem("All", QVariant(QString::number(-1)));
			ui_->comboBoxComputeCurvature->addItem("All", QVariant(QString::number(-1)));
	
			// Set the default index to 0.
			ui_->comboBoxShowAlignment->setCurrentIndex(ui_->comboBoxShowAlignment->count() - 1);
			ui_->comboBoxComputeCurvature->setCurrentIndex(ui_->comboBoxComputeCurvature->count() - 1);
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		}
		else
			BLUE_LOG(warning) << "Computing centerlines failed.";		
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetCenterlines_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		ui_->comboBoxShowAlignment->clear();
		ui_->comboBoxComputeCurvature->clear();
		ui_->comboBoxPlotSelectAlignment->clear();

		if(pointCloud->resetCenterlines() == 0) {
			ui_->pushButtonComputeCurvature->setDisabled(true);
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
		}
		else
			BLUE_LOG(warning) << "Resetting centerlines failed.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputePairs_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::PairComputationDescription desc;
		desc.maxError = ui_->doubleSpinBoxPairsMaxError->value();
		desc.maxElevationChange = ui_->doubleSpinBoxPairsMaxElevationDiff->value();
		desc.pointProximityDistance = ui_->doubleSpinBoxPairsPointProximity->value();

		desc.applyDensityFilter = ui_->checkBoxPairsApplyDensityFilter->isChecked();
		desc.localDensityKernelRadius = ui_->doubleSpinBoxPairsDensityFilterKernelRadius->value();
		desc.localDensityThreshold = ui_->spinBoxPairsDensityFilterThreshold->value();

		desc.applyClusterFilter = ui_->checkBoxPairsApplyClusterFilter->isChecked();
		desc.clusterDistance2D = ui_->doubleSpinBoxPairsClusterDistance->value() / 100.0; //Divide by 100 to scale to meters.
		desc.clusterHeightRange = ui_->doubleSpinBoxClusterHeightRange->value();
		desc.clusterHeightTreshold = ui_->doubleSpinBoxClusterHeightThreshold->value();

		pointCloud->computePairs(desc, std::vector<std::pair<size_t, size_t>>(), callback_);
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
	}
	else {
		BLUE_LOG(trace) << "No point cloud available.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetPairs_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->resetPairs();
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
	}
	else {
		BLUE_LOG(trace) << "No point cloud available.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeCurvature_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		buw::CenterlineCurvatureComputationDescription desc;
		desc.bearingComputationSegmentLength = ui_->doubleSpinBoxDistanceForPCA->value();
		desc.curvatureStepSize = ui_->spinBoxCurvatureStepSize->value();
		desc.numPointsForMeanCurvature = ui_->spinBoxNumPointsForMeanCurvature->value();
		desc.numPointsForMedianCurvature = ui_->spinBoxNumPointsForMedianCurvature->value();
		desc.numPointsForMeanBearing = ui_->spinBoxNumPointsForMeanBearing->value();
		desc.numPointsForMedianBearing = ui_->spinBoxNumPointsForMedianBearing->value();
		QString comboBoxComputeCurvatureData = ui_->comboBoxComputeCurvature->currentData().toString();

		if(comboBoxComputeCurvatureData == "All")
			desc.centerlineIndex = -1;
		else
			desc.centerlineIndex = comboBoxComputeCurvatureData.toInt();

		//desc.centerlineIndex = ui_->comboBoxComputeCurvature->currentData().toString().toInt();
		if(pointCloud->computeCenterlineCurvature(desc, callback_) == 0) {
			if(desc.centerlineIndex != -1)
				ui_->comboBoxPlotSelectAlignment->addItem(QString::number(desc.centerlineIndex), QVariant(QString::number(desc.centerlineIndex)));
			else {
				ui_->comboBoxPlotSelectAlignment->clear();
				for(size_t i = 0; i < ui_->comboBoxComputeCurvature->count() - 1; i++)
					ui_->comboBoxPlotSelectAlignment->addItem(QString::number(i), QVariant(QString::number(i)));
			}
		}
	}
}

template <template<typename T> class Container, typename T> Container<T> linspace(const T& min, const T& max, const size_t& N)
{
	T stepSize = (max - min) / (N - 1);
	Container<T> result;
	for(size_t i = 0; i < N; i++)
		result.push_back(min + i * stepSize);
	return result;
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonPlotAlignment_clicked()
{	
	// Get the file to read.
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::currentPath(), tr("*.txt"));

	if(!filename.isEmpty()) {
		QVector<double> chainages, curvatures, bearings, deltaCurvatures;

		QFile inputFile(filename);
		if(inputFile.open(QIODevice::ReadOnly)) {
			QTextStream in(&inputFile);
			while(!in.atEnd()) {
				QString line = in.readLine();
				QStringList tokens = line.split('\t');
				chainages.append(tokens[0].toDouble());
				curvatures.append(tokens[1].toDouble());
				bearings.append(tokens[2].toDouble());
				if(tokens.size() > 3)
					deltaCurvatures.append(tokens[3].toDouble());
			}
			inputFile.close();
		}

		bool plotFourierTransform = false;

		if(plotFourierTransform) {
			int numReal = bearings.size();
			int numComplex = (std::floor((numReal / 2)) + 1);

			double* bearingsRaw = fftw_alloc_real(numReal);
			fftw_complex* bearingsFFT = fftw_alloc_complex(numComplex);

			fftw_plan plan = fftw_plan_dft_r2c_1d(numReal, bearingsRaw, bearingsFFT, FFTW_ESTIMATE);
			std::memcpy(bearingsRaw, bearings.data(), numReal);

			fftw_execute(plan);

			QVector<double> fftReal;
			for(size_t i = 1; i < numComplex; i++)
				fftReal.append(bearingsFFT[i][0]);

			fftw_free(bearingsRaw);
			fftw_free(bearingsFFT);
			fftw_destroy_plan(plan);

			fftw_cleanup();


			// Create plot for bearing.
			QCustomPlot* customPlotFFT = new QCustomPlot(nullptr);

			// TODO: Fix memory leak!
			//connect(customPlotBearing, &QCustomPlot::close, customPlotBearing, &QObject::deleteLater);

			customPlotFFT->resize(400, 400);
			customPlotFFT->setInteraction(QCP::iRangeDrag, true);

			// Set window title
			customPlotFFT->setWindowTitle(filename);

			// create graph and assign data to it:
			customPlotFFT->addGraph(customPlotFFT->xAxis, customPlotFFT->yAxis);
			customPlotFFT->setInteraction(QCP::iRangeZoom);
			customPlotFFT->setInteraction(QCP::iRangeDrag);
			QVector<double> freq;

			for(size_t i = 0; i < numReal / 2 - 2; i++) {
				freq.append((20.0 * i) / numReal);
			}

			customPlotFFT->graph(0)->setData(freq, fftReal);
			customPlotFFT->graph(0)->setPen(QPen(Qt::green));

			// give the axes some labels:
			customPlotFFT->xAxis->setLabel("Frequency");
			customPlotFFT->yAxis->setLabel("Amplitude");


			// set axes ranges, so we see all data:
			customPlotFFT->xAxis->setRange(freq.first(), freq.last());
			customPlotFFT->yAxis->rescale();

			customPlotFFT->replot();
			customPlotFFT->show();
			plots_.push_back(customPlotFFT);
		}

		// Create plot for bearing.
		QCustomPlot* customPlotBearing = new QCustomPlot(nullptr);

		// TODO: Fix memory leak!
		//connect(customPlotBearing, &QCustomPlot::close, customPlotBearing, &QObject::deleteLater);

		customPlotBearing->resize(400, 400);
		customPlotBearing->setInteraction(QCP::iRangeDrag, true);

		// Set window title
		customPlotBearing->setWindowTitle(filename);

		// create graph and assign data to it:
		customPlotBearing->addGraph(customPlotBearing->xAxis, customPlotBearing->yAxis);
		customPlotBearing->setInteraction(QCP::iRangeZoom);
		customPlotBearing->setInteraction(QCP::iRangeDrag);
		customPlotBearing->graph(0)->setData(chainages, bearings);
		customPlotBearing->graph(0)->setPen(QPen(Qt::blue));

		// give the axes some labels:
		customPlotBearing->xAxis->setLabel("Chainage");
		customPlotBearing->yAxis->setLabel("Bearing");


		// set axes ranges, so we see all data:
		customPlotBearing->xAxis->setRange(chainages.first(), chainages.last());
		customPlotBearing->yAxis->rescale();

		customPlotBearing->replot();
		customPlotBearing->show();
		plots_.push_back(customPlotBearing);

		// Create plot for bearing.
		QCustomPlot* customPlotCurvature = new QCustomPlot(nullptr);

		// TODO: Fix memory leak!
		//connect(customPlotCurvature, &QCustomPlot::close, customPlotCurvature, &QObject::deleteLater);

		customPlotCurvature->resize(400, 400);
		customPlotCurvature->setInteraction(QCP::iRangeDrag, true);

		// Set window title
		customPlotCurvature->setWindowTitle(filename);

		// create graph and assign data to it:
		customPlotCurvature->addGraph(customPlotCurvature->xAxis, customPlotCurvature->yAxis);
		customPlotCurvature->setInteraction(QCP::iRangeZoom);
		customPlotCurvature->setInteraction(QCP::iRangeDrag);
		customPlotCurvature->graph(0)->setData(chainages, curvatures);
		customPlotCurvature->graph(0)->setPen(QPen(Qt::red));

		// give the axes some labels:
		customPlotCurvature->xAxis->setLabel("Chainage");
		customPlotCurvature->yAxis->setLabel("Curvature");


		// set axes ranges, so we see all data:
		customPlotCurvature->xAxis->setRange(chainages.first(), chainages.last());
		customPlotCurvature->yAxis->rescale();

		customPlotCurvature->replot();
		customPlotCurvature->show();
		plots_.push_back(customPlotCurvature);

		if(deltaCurvatures.size() > 0) {
			// Create plot for delta curvature.
			QCustomPlot* customPlotDeltaCurvature = new QCustomPlot(nullptr);

			// TODO: Fix memory leak!
			//connect(customPlotCurvature, &QCustomPlot::close, customPlotCurvature, &QObject::deleteLater);

			customPlotDeltaCurvature->resize(400, 400);
			customPlotDeltaCurvature->setInteraction(QCP::iRangeDrag, true);

			// Set window title
			customPlotDeltaCurvature->setWindowTitle(filename);

			// create graph and assign data to it:
			customPlotDeltaCurvature->addGraph(customPlotDeltaCurvature->xAxis, customPlotDeltaCurvature->yAxis);
			customPlotDeltaCurvature->setInteraction(QCP::iRangeZoom);
			customPlotDeltaCurvature->setInteraction(QCP::iRangeDrag);
			customPlotDeltaCurvature->graph(0)->setData(chainages, deltaCurvatures);
			customPlotDeltaCurvature->graph(0)->setPen(QPen(Qt::green));

			// give the axes some labels:
			customPlotDeltaCurvature->xAxis->setLabel("Chainage");
			customPlotDeltaCurvature->yAxis->setLabel("dCurvature");


			// set axes ranges, so we see all data:
			customPlotDeltaCurvature->xAxis->setRange(chainages.first(), chainages.last());
			customPlotDeltaCurvature->yAxis->rescale();

			customPlotDeltaCurvature->replot();
			customPlotDeltaCurvature->show();
			plots_.push_back(customPlotDeltaCurvature);

		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_doubleSpinBoxRemoveDuplicatesThreshold_valueChanged(double value)
{
	ui_->horizontalSliderRemoveDuplicatesThreshold->blockSignals(true);
	ui_->horizontalSliderRemoveDuplicatesThreshold->setValue(value);
	ui_->horizontalSliderRemoveDuplicatesThreshold->blockSignals(false);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonCalculateSections_clicked()
{
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		pointCloud->computeSections(100.0 / ui_->horizontalSliderSectionSize->value(), callback_);
		view_->getViewport()->updatePointCloudSectionLength(100.0 / ui_->horizontalSliderSectionSize->value());
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::DataManagement::ChangeFlag::PointCloud);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_doubleSpinBoxSectionSize_valueChanged(double value)
{

	ui_->horizontalSliderSectionSize->blockSignals(true);
	ui_->horizontalSliderSectionSize->setValue(value);
	ui_->horizontalSliderSectionSize->blockSignals(false);

	//if(ui_->checkBoxPreview->checkState() == Qt::CheckState::Checked)
	//	view_->getViewport()->updatePointCloudSectionLength(100.0 / ui_->doubleSpinBoxSectionSize->value());

}

void OpenInfraPlatform::UserInterface::MainWindow::on_horizontalSliderSectionSize_valueChanged(int value)
{
	ui_->doubleSpinBoxSectionSize->blockSignals(true);
	ui_->doubleSpinBoxSectionSize->setValue(value);
	ui_->doubleSpinBoxSectionSize->blockSignals(false);

	//if(ui_->checkBoxPreview->checkState() == Qt::CheckState::Checked)
	//	view_->getViewport()->updatePointCloudSectionLength(100.0 / ui_->horizontalSliderSectionSize->value());
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonSelectSegmentedPointsColor_clicked()
{
	pcdSegmentedPointsColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_doubleSpinBoxPointSize_valueChanged(double value) {
	double spinRange = ui_->doubleSpinBoxPointSize->maximum() - ui_->doubleSpinBoxPointSize->minimum();
	int sliderRange = ui_->horizontalSliderPointSize->maximum() - ui_->horizontalSliderPointSize->minimum();
	int sliderVal = value * sliderRange / spinRange + ui_->horizontalSliderPointSize->minimum();

	ui_->horizontalSliderPointSize->blockSignals(true);
	ui_->horizontalSliderPointSize->setValue(sliderVal);
	ui_->horizontalSliderPointSize->blockSignals(false);

	view_->setPointSize((float)value);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_horizontalSliderPointSize_sliderMoved(int value) {
	double spinRange = ui_->doubleSpinBoxPointSize->maximum() - ui_->doubleSpinBoxPointSize->minimum();
	int sliderRange = ui_->horizontalSliderPointSize->maximum() - ui_->horizontalSliderPointSize->minimum();
	double spinVal = value * spinRange / sliderRange + ui_->doubleSpinBoxPointSize->minimum();

	ui_->doubleSpinBoxPointSize->blockSignals(true);
	ui_->doubleSpinBoxPointSize->setValue(spinVal);
	ui_->doubleSpinBoxPointSize->blockSignals(false);

	view_->setPointSize((float)spinVal);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_checkBoxShowSectionOOBB_clicked(bool checked) {
	auto pointCloud = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if(pointCloud) {
		auto sections = pointCloud->getSections();
		if(!sections.empty()) {
			view_->getViewport()->setShowSectionOOBB(checked);
		}
		else {
			// Open dialog and ask if sections should be computed.
			QMessageBox dialog;
			dialog.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
			dialog.setIcon(QMessageBox::Icon::Question);
			dialog.setText("No sections found. Do you want to compute sections now?");
			dialog.setWindowTitle(tr("Disclaimer"));
			dialog.setWindowFlags(((Qt::Dialog) | (Qt::MSWindowsFixedSizeDialogHint)));

			if(dialog.exec() == QMessageBox::StandardButton::Yes) {
				on_pushButtonCalculateSections_clicked();
				
				sections = pointCloud->getSections();
				if(!sections.empty()) {
					view_->getViewport()->setShowSectionOOBB(checked);
				}
			}
		}
	}			
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionLoad_Bridge() {
	view_->LoadBridge();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionPrecisionTest() {
	bool ok = false;
	int iterations = QInputDialog::getInt(this, "Precision Test", "Number of Iterations", 5, 1, 100, 1, &ok);

	if (ok)
		precisionTest_.startTest(iterations);
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionMerge_Mesh_triggered() {
	QString openFile = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("OBJ (*.obj)"));

	if (openFile.isNull() == false) {
		std::string filename = openFile.toUtf8().constData();

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().createTerrainFromMesh(filename);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreateClothoid_triggered() {
	createClothoidDialog2_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionIFC_Alignment_1_1_Export_triggered() {
	exportIfcAlignment1x1Dialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionCreate_Accident_Report_triggered() {
	if (createAccidentReportDialog_ == nullptr) {
		createAccidentReportDialog_ = new CreateAccidentReportDialog(this);
	}

	createAccidentReportDialog_->show();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_actionFilterIfcModel_triggered()
{
}
