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

#include "MainWindow.h"

#include "ColorPicker/colorpickerwidget.h"
#include "UnitTesting/Benchmark.h"
#include "DataManagement/General/AsyncJob.h"


#include "Dialogues/HelpBrowser.h"
#include "Dialogues/resource.h"
#include "Dialogues/VectorTableModel.h"

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

//#include <fftw3.h>

#include <iostream>
#include <codecvt>
#include <shlobj.h>
#include <stdlib.h>

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
#include <PointCloudProcessing.h>
#include <PointCloud.h>
#endif
using convert_type = std::codecvt_utf8<wchar_t>;

OpenInfraPlatform::UserInterface::MainWindow::MainWindow(QWidget* parent /*= nullptr*/)
    : BlueFramework::Application::UserInterface::MainWindowBase(&OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance(), parent)
    , ui_(new Ui::MainWindow)
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

	OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().Change.connect(boost::bind(&MainWindow::onChange, this));
	OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().RedoStackChanged.connect(boost::bind(&MainWindow::updateActionRedo, this, _1));
	OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().UndoStackChanged.connect(boost::bind(&MainWindow::updateActionUndo, this, _1));

	OpenInfraPlatform::AsyncJob::getInstance().jobStarting.connect(boost::bind(&MainWindow::jobStarting, this));
	OpenInfraPlatform::AsyncJob::getInstance().jobRunning.connect(boost::bind(&MainWindow::jobRunning, this, _1, _2, _3));
	OpenInfraPlatform::AsyncJob::getInstance().jobFinishing.connect(boost::bind(&MainWindow::jobFinishing, this, _1, _2));
	OpenInfraPlatform::AsyncJob::getInstance().jobFinished.connect(boost::bind(&MainWindow::jobFinished, this, _1, _2));

	
	preferencesDialog_ = new PreferencesDialog(view_, this);
	
	updateRecentFileActions();
	
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
	callback_ = buw::makeReferenceCounted<OpenInfraPlatform::Core::DataManagement::ProgressCallback>();
	//connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::activitySignal, ui_->progressBarPointCloudProcessing, &QProgressBar::setVisible);
	//connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::updateSignal, ui_->progressBarPointCloudProcessing, &QProgressBar::setValue);
	
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

	//QObject::connect(imageQualityBasedUnitTesting, &QAction::triggered, this, &MainWindow::ImageQualityBasedUnitTesting);
	QObject::connect(actionGetCameraState, &QAction::triggered, this, &MainWindow::actionGetCameraState);
	QObject::connect(actionShowMap, &QAction::triggered, this, &MainWindow::showMap);
	QObject::connect(actionReloadShader, &QAction::triggered, this, &MainWindow::reloadShader);
	QObject::connect(actionShowMap, &QAction::triggered, this, &MainWindow::showMap);
	//QObject::connect(variantEditor_, &QtTreePropertyBrowser::currentItemChanged, this, &MainWindow::on_variantEditor_currentItemChanged);
	QObject::connect(actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
	QObject::connect(actionStoreGBuffer, &QAction::triggered, this, &MainWindow::storeGBuffer);
	//QObject::connect(actionCreateClothoid, &QAction::triggered, this, &MainWindow::createClothoid);
	//QObject::connect(actionShowVerticalAlignment3D, &QAction::triggered, this, &MainWindow::on_actionVertical_alignment_3D_triggered);
	//QObject::connect(actionLoadBridge, &QAction::triggered, this, &MainWindow::on_actionLoad_Bridge);
	//QObject::connect(actionPrecisionTest, &QAction::triggered, this, &MainWindow::on_actionPrecisionTest);

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
	//progressDialog_->setAutoClose(false);
	//progressDialog_->setAutoReset(false);
	//progressDialog_->hide();
	progressDialog_->setValue(progressDialog_->maximum());

	QObject::connect(progressDialog_, SIGNAL(canceled()), this, SLOT(cancelJob()));
	QObject::disconnect(progressDialog_, SIGNAL(canceled()), progressDialog_, SLOT(cancel()));

	// Connect to the common progress dialog.
	connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::activitySignal, progressDialog_, &QProgressDialog::setEnabled);
	connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::activitySignal, progressDialog_, &QProgressDialog::setVisible);
	connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::activitySignal, progressDialog_, [&](bool value) {value ? progressDialog_->setRange(0, 100) : progressDialog_->setRange(0, 0); });
	connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::updateSignal, progressDialog_, &QProgressDialog::setValue);
	connect(callback_.get(), &OpenInfraPlatform::Core::DataManagement::ProgressCallback::setMethodTitleSignal, progressDialog_, &QProgressDialog::setLabelText);

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
	ui_->doubleSpinBoxPointSize->setValue(3.0);
	on_doubleSpinBoxPointSize_valueChanged(3.0);
#endif

	//retranslatePropertyBrowser();

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
	
}

void OpenInfraPlatform::UserInterface::MainWindow::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
}

OpenInfraPlatform::UserInterface::MainWindow::~MainWindow() {

	// todo:L consider using smart pointers here	
	buw::safeDelete(preferencesDialog_);
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

		//retranslatePropertyBrowser();
	} else {
		// remember to call base class implementation
		QMainWindow::changeEvent(evt);
	}
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
				OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().clear();
				OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().import(DropName);
				addToRecentFilesList(OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().recentFileName);
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



//---------------------------------------------------------------------------//
// Recent files
//---------------------------------------------------------------------------//

void OpenInfraPlatform::UserInterface::MainWindow::on_actionExit_triggered() {
	close();
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

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
void OpenInfraPlatform::UserInterface::MainWindow::on_actionExportPointCloud_triggered()
{
	if(OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud().get() != nullptr) {
		QString filename = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::currentPath(), tr("*.bin;;*.las"));
		if(!filename.isNull()) {
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().exportPointCloud(filename.toStdString());
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
#endif

void OpenInfraPlatform::UserInterface::MainWindow::onChange() {
	onChange(OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getLatesChangeFlag());
}

void OpenInfraPlatform::UserInterface::MainWindow::onChange(ChangeFlag changeFlag) {
	
#ifdef OIP_WITH_POINT_CLOUD_PROCESSING
	if(changeFlag & ChangeFlag::PointCloud) {
		auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
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
#endif
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

void OpenInfraPlatform::UserInterface::MainWindow::on_actionOpen_triggered() {
	try {
		handle_actionOpen_triggered();
		addToRecentFilesList(OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().recentFileName);
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
	progressBar_->hide();
	progressDialog_->hide();

	if (inUnitTest_ >= 0) {
		//performTest(inUnitTest_);
		//prepareTest(inUnitTest_ + 1);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::cancelJob() {
	OpenInfraPlatform::AsyncJob::getInstance().cancelJob();
	progressDialog_->setLabelText("Canceling");
	progressDialog_->setDisabled(true);
}

void OpenInfraPlatform::UserInterface::MainWindow::actionGetCameraState() {
	/*
	auto cameraController = view_->getInfraCameraController();
	auto camera = cameraController->getCamera();

	std::ostream& out = std::cout;

	auto pos = camera->getPosition(buw::InfraCamera::CAMERA);
	auto rot = camera->getRotation();
	out << "camera->setPosition(" << pos.x() << ", " << pos.y() << ", " << pos.z() << ", buw::InfraCamera::CAMERA);" << std::endl;
	out << "camera->setRotation(" << rot.x() << ", " << rot.y() << ");" << std::endl;
	*/
}

#ifdef OIP_WITH_POINT_CLOUD_PROCESSING

void OpenInfraPlatform::UserInterface::MainWindow::on_actionMerge_LAS_File_triggered() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::currentPath(), tr("LAS cloud (*.las)"));

	if (!filename.isNull()) {
		//TODO
		//OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().importLAS(filename.toStdString());
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		// Initialize the filter parameters.
		buw::DuplicateFilterDescription desc;
		desc.dim = ui_->radioButtonRender3D->isChecked() ?
			OpenInfraPlatform::PointCloudProcessing::Enums::ePointCloudFilterDimension::Volume3D :
			OpenInfraPlatform::PointCloudProcessing::Enums::ePointCloudFilterDimension::Sections2D;
		desc.minDistance = ui_->doubleSpinBoxRemoveDuplicatesThreshold->value() / 1000.0;

		// Apply the filter and pass the callback for updating the UI, then update the indices for rendering.
		pointCloud->applyDuplicateFilter(desc, callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetDuplicateFilter_clicked()
{
	// Get the point cloud and reset the scalar field called "Duplicate" which holds the labeling for duplicates.
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->resetScalarField("Duplicate");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyDensityFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		// Initialize the filter parameters
		buw::LocalDensityFilterDescription desc;
		desc.dim = ui_->radioButtonRender3D->isChecked() ?
			OpenInfraPlatform::PointCloudProcessing::Enums::ePointCloudFilterDimension::Volume3D :
			OpenInfraPlatform::PointCloudProcessing::Enums::ePointCloudFilterDimension::Sections2D;
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->resetScalarField("Density");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyPositionFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::PositionFilterDescription desc;
		desc.minValue = ui_->doubleSpinBoxFilterPositionMin->value();
		desc.maxValue = ui_->doubleSpinBoxFilterPositionMax->value();
		desc.dimension = ui_->comboBoxFilterPositionDimension->currentData().toInt();

		if (pointCloud->applyPositionFilter(desc, callback_) == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetPositionFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		if (pointCloud->resetPositionFilter() == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyRelativeHeightFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::RelativeHeightFilterDescription desc;
		desc.lowerBound = ui_->doubleSpinBoxFilterHeightLowerBound->value();
		desc.upperBound = ui_->doubleSpinBoxFilterHeightUpperBound->value();

		if (pointCloud->applyRelativeHeightWithGridFilter(desc, callback_) == 0) {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetRelativeHeightFilter_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		if (pointCloud->resetPositionFilter() == 0) {
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

	if (dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		if (pointCloud) {
			pointCloud->removeFilteredPoints(callback_);
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
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
	if (dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().import(pointCloud->getName().toStdString());
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

	if (dialog.exec() == QMessageBox::StandardButton::Yes) {
		auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
		if (pointCloud) {
			pointCloud->removeNotSegmentedPoints();
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonUndoSegmentation_clicked()
{
	on_pushButtonRestoreOriginal_clicked();
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyPercentileSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->applyPercentilesOnGridSegmentation(callback_);
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplyRateOfChangeSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::RateOfChangeSegmentationDescription desc;
		desc.dim = ui_->comboBoxRateOfChangeDimension->currentData().toInt();
		desc.maxNeighbourDistance = ui_->doubleSpinBoxRateOfChangeNeighbourDistance->value();
		desc.maxRateOfChangeThreshold = ui_->doubleSpinBoxRateOfChangeMaxDiff->value();
		int err = pointCloud->applyRateOfChangeSegmentation(desc, callback_);
		if (err != 0) {
			BLUE_LOG(warning) << "Rate of change segmentation failed. Error Code: " << err;
		}
		else {
			view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetRateOfChangeSegmentation_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->resetScalarField("SegmentedRateOfChange");
		view_->getViewport()->setPointCloudIndices(pointCloud->getIndices());
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeGrid_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::GridComputationDescription desc;
		desc.size = ui_->spinBoxGridSize->value();
		desc.kernelRadius = ui_->doubleSpinBoxGridKernelRadius->value();
		pointCloud->computeGrid(desc, callback_);
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetGrid_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->resetGrid();
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeChainage_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::ChainageComputationDescription desc;
		desc.base = (PointCloudProcessing::Enums::eChainageComputationBase) ui_->comboBoxInterpolationBase->currentData().toInt();
		desc.bUseInterpolation = ui_->checkBoxInterpolation->isChecked();
		desc.interpolation = (PointCloudProcessing::Enums::eChainageComputationInterpolationMethod) ui_->comboBoxInterpolationMethod->currentData().toInt();
		desc.bUseSmoothing = ui_->checkBoxSmoothing->isChecked();
		desc.sigma = ui_->doubleSpinBoxSmoothingSigma->value();
		desc.sigmaSF = ui_->doubleSpinBoxSmoothingSigmaSF->value();

		pointCloud->computeChainage(desc, callback_);

	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetChainage_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud)
		pointCloud->resetScalarField("Chainage");
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonApplySegmentRailways_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
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
		//	OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
		//}
		//else if(numAlignments == 0) {
		//	OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		BLUE_LOG(info) << "Resetting railway segmentation.";
		if (pointCloud->resetRailwaySegmentation() == 0) {
			ui_->pushButtonComputeCurvature->setDisabled(true);
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();

	if (pointCloud) {

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
		if (numAlignments > 0) {

			ui_->pushButtonComputeCurvature->setEnabled(true);

			// Clear the combo boxes for plotting since we only want to plot the stuff from the latest computations.
			ui_->comboBoxShowAlignment->clear();
			ui_->comboBoxComputeCurvature->clear();
			ui_->comboBoxPlotSelectAlignment->clear();

			// Add the indices to the combo boxes.
			for (int idx = 0; idx < numAlignments; idx++) {
				ui_->comboBoxShowAlignment->addItem(QString::number(idx), QVariant(QString::number(idx)));
				ui_->comboBoxComputeCurvature->addItem(QString::number(idx), QVariant(QString::number(idx)));
			}

			ui_->comboBoxShowAlignment->addItem("All", QVariant(QString::number(-1)));
			ui_->comboBoxComputeCurvature->addItem("All", QVariant(QString::number(-1)));

			// Set the default index to 0.
			ui_->comboBoxShowAlignment->setCurrentIndex(ui_->comboBoxShowAlignment->count() - 1);
			ui_->comboBoxComputeCurvature->setCurrentIndex(ui_->comboBoxComputeCurvature->count() - 1);
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
		}
		else
			BLUE_LOG(warning) << "Computing centerlines failed.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetCenterlines_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		ui_->comboBoxShowAlignment->clear();
		ui_->comboBoxComputeCurvature->clear();
		ui_->comboBoxPlotSelectAlignment->clear();

		if (pointCloud->resetCenterlines() == 0) {
			ui_->pushButtonComputeCurvature->setDisabled(true);
			OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
		}
		else
			BLUE_LOG(warning) << "Resetting centerlines failed.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputePairs_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
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
		OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
	}
	else {
		BLUE_LOG(trace) << "No point cloud available.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonResetPairs_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->resetPairs();
		OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
	}
	else {
		BLUE_LOG(trace) << "No point cloud available.";
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonComputeCurvature_clicked()
{
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		buw::CenterlineCurvatureComputationDescription desc;
		desc.bearingComputationSegmentLength = ui_->doubleSpinBoxDistanceForPCA->value();
		desc.curvatureStepSize = ui_->spinBoxCurvatureStepSize->value();
		desc.numPointsForMeanCurvature = ui_->spinBoxNumPointsForMeanCurvature->value();
		desc.numPointsForMedianCurvature = ui_->spinBoxNumPointsForMedianCurvature->value();
		desc.numPointsForMeanBearing = ui_->spinBoxNumPointsForMeanBearing->value();
		desc.numPointsForMedianBearing = ui_->spinBoxNumPointsForMedianBearing->value();
		QString comboBoxComputeCurvatureData = ui_->comboBoxComputeCurvature->currentData().toString();

		if (comboBoxComputeCurvatureData == "All")
			desc.centerlineIndex = -1;
		else
			desc.centerlineIndex = comboBoxComputeCurvatureData.toInt();

		//desc.centerlineIndex = ui_->comboBoxComputeCurvature->currentData().toString().toInt();
		if (pointCloud->computeCenterlineCurvature(desc, callback_) == 0) {
			if (desc.centerlineIndex != -1)
				ui_->comboBoxPlotSelectAlignment->addItem(QString::number(desc.centerlineIndex), QVariant(QString::number(desc.centerlineIndex)));
			else {
				ui_->comboBoxPlotSelectAlignment->clear();
				for (size_t i = 0; i < ui_->comboBoxComputeCurvature->count() - 1; i++)
					ui_->comboBoxPlotSelectAlignment->addItem(QString::number(i), QVariant(QString::number(i)));
			}
		}
	}
}

void OpenInfraPlatform::UserInterface::MainWindow::on_pushButtonPlotAlignment_clicked()
{
	// Get the file to read.
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::currentPath(), tr("*.txt"));

	if (!filename.isEmpty()) {
		QVector<double> chainages, curvatures, bearings, deltaCurvatures;

		QFile inputFile(filename);
		if (inputFile.open(QIODevice::ReadOnly)) {
			QTextStream in(&inputFile);
			while (!in.atEnd()) {
				QString line = in.readLine();
				QStringList tokens = line.split('\t');
				chainages.append(tokens[0].toDouble());
				curvatures.append(tokens[1].toDouble());
				bearings.append(tokens[2].toDouble());
				if (tokens.size() > 3)
					deltaCurvatures.append(tokens[3].toDouble());
			}
			inputFile.close();
		}

		bool plotFourierTransform = false;
#ifdef OIP_WITH_FFTW
		if (plotFourierTransform) {
			int numReal = bearings.size();
			int numComplex = (std::floor((numReal / 2)) + 1);

			double* bearingsRaw = fftw_alloc_real(numReal);
			fftw_complex* bearingsFFT = fftw_alloc_complex(numComplex);

			fftw_plan plan = fftw_plan_dft_r2c_1d(numReal, bearingsRaw, bearingsFFT, FFTW_ESTIMATE);
			std::memcpy(bearingsRaw, bearings.data(), numReal);

			fftw_execute(plan);

			QVector<double> fftReal;
			for (size_t i = 1; i < numComplex; i++)
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

			for (size_t i = 0; i < numReal / 2 - 2; i++) {
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
#endif

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

		if (deltaCurvatures.size() > 0) {
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		pointCloud->computeSections(100.0 / ui_->horizontalSliderSectionSize->value(), callback_);
		view_->getViewport()->updatePointCloudSectionLength(100.0 / ui_->horizontalSliderSectionSize->value());
		OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().pushChange(OpenInfraPlatform::Core::DataManagement::ChangeFlag::PointCloud);
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

void OpenInfraPlatform::UserInterface::MainWindow::on_comboBoxAlignment_currentIndexChanged(int index)
{
	//TODO
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
	auto pointCloud = OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().getPointCloud();
	if (pointCloud) {
		auto sections = pointCloud->getSections();
		if (!sections.empty()) {
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

			if (dialog.exec() == QMessageBox::StandardButton::Yes) {
				on_pushButtonCalculateSections_clicked();

				sections = pointCloud->getSections();
				if (!sections.empty()) {
					view_->getViewport()->setShowSectionOOBB(checked);
				}
			}
		}
	}
}

#endif

void OpenInfraPlatform::UserInterface::MainWindow::openRecentFileViaAction(QAction* actionRecentFile) {
	std::string fileName = actionRecentFile->text().toUtf8().constData();
	fileName = fileName.substr(4, fileName.length());

	if (boost::filesystem::exists(fileName)) {
		OpenInfraPlatform::Core::DataManagement::DocumentManager::getInstance().getData().import(fileName);
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


//---------------------------------------------------------------------------//
// Debugging
//---------------------------------------------------------------------------//

void OpenInfraPlatform::UserInterface::MainWindow::reloadShader() {
	view_->reloadShader();
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




template <template<typename T> class Container, typename T> Container<T> linspace(const T& min, const T& max, const size_t& N)
{
	T stepSize = (max - min) / (N - 1);
	Container<T> result;
	for(size_t i = 0; i < N; i++)
		result.push_back(min + i * stepSize);
	return result;
}