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

#include "PreferencesDialog.h"

#include "OpenInfraPlatform/DataManagement/Data.h"
#include <BlueFramework/Engine/ViewCube/ViewCube.h>
#include <QColorDialog>
#include <QProgressDialog>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QFormLayout>
#include <QProgressBar>
#include <QEvent>

#include <QTranslator>

OpenInfraPlatform::UserInterface::PreferencesDialog::PreferencesDialog(OpenInfraPlatform::UserInterface::View* view, QWidget *parent /*= nullptr*/) :
	ui_(new Ui::PreferencesDialog),
	QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint),
	view_(view),
	translator_(new QTranslator()),
    faceColorDialog_(QColor("#666666"),nullptr),
    borderColorDialog_(QColor("#474747"), nullptr),
    textColorDialog_(QColor("#48b7e7"), nullptr),
    highlightColorDialog_(Qt::white, nullptr)
{
	ui_->setupUi(this);

	colorPickerWidget_ = new ColorPickerWidget(this);

	ui_->verticalLayout_2->insertWidget(1, colorPickerWidget_);

	QObject::connect(colorPickerWidget_,
		SIGNAL(colorChanged(QColor)),
		this,
		SLOT(clearColorChanged(QColor)));

	//infraCameraController_ = view_->getInfraCameraController();

	//ui_->doubleSpinBoxPanSpeed->setValue(infraCameraController_->getCamera()->movementVelocity_);// pan speed in spectator mode
	//ui_->doubleSpinBoxAnimationTime->setValue(infraCameraController_->getInterpolationTime());
	//ui_->doubleSpinBoxNearPlane->setValue(infraCameraController_->getCamera()->frustum().nearPlane());
	//ui_->doubleSpinBoxFarPlane->setValue(infraCameraController_->getCamera()->frustum().farPlane());


	ui_->comboBoxRenderSystem->addItem("Direct3D 12");
	ui_->comboBoxRenderSystem->addItem("Direct3D 11");
	//ui_->comboBoxRenderSystem->addItem("OpenGL 4.x");

	ui_->checkBoxMSAA->setEnabled(true);
	connect(ui_->comboBoxRenderSystem, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRenderSystem_currentIndexChanged(int)));
	connect(ui_->checkBoxMSAA, SIGNAL(clicked(bool)), this, SLOT(onCheckBoxMSAA_clicked(bool)));

	createLanguageMenu();
	connect(ui_->comboBoxLanguage, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onComboBoxLanguage_currentIndexChanged(const QString &)));

    connect(&faceColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateFaceColor);
    connect(&faceColorDialog_, &QColorDialog::colorSelected, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateFaceColor);

    connect(&borderColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateBorderColor);
    connect(&borderColorDialog_, &QColorDialog::colorSelected, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateBorderColor);

    connect(&textColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateTextColor);
    connect(&textColorDialog_, &QColorDialog::colorSelected, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateTextColor);

    connect(&highlightColorDialog_, &QColorDialog::currentColorChanged, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateHighlightColor);
    connect(&highlightColorDialog_, &QColorDialog::colorSelected, view_->getViewport()->getViewCube().get(), &buw::ViewCube::updateHighlightColor);

	{
		ui_->comboBoxRenderSystem->blockSignals(true);
		ui_->checkBoxMSAA->blockSignals(true);

		buw::eRenderAPI renderAPI;
		bool warp, msaa;
		view_->getViewportSettings(renderAPI, warp, msaa);

		ui_->comboBoxRenderSystem->setCurrentIndex((int)renderAPI);
		ui_->checkBoxMSAA->setChecked(msaa);

		ui_->comboBoxRenderSystem->blockSignals(false);
		ui_->checkBoxMSAA->blockSignals(false);
	}
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::clearColorChanged( const QColor &col )
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setClearColor(
		buw::Color3f(col.red() / 255.0f, col.green() / 255.0f, col.blue() / 255.0f)
	);
}

OpenInfraPlatform::UserInterface::PreferencesDialog::~PreferencesDialog()
{
	delete colorPickerWidget_;
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::changeEvent(QEvent* evt) 
{
	if (evt->type() == QEvent::LanguageChange)
	{
		ui_->retranslateUi(this);
	}
	else
	{
		QWidget::changeEvent(evt);
	}
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxGradientClear_clicked( bool checked )
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().enableGradientClear(checked);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowGrid_clicked( bool checked )
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().enableDrawGrid(checked);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowReferenceCoordinateSystem_clicked( bool checked )
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().enableShowReferenceCoordinateSystem(checked);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxSkybox_clicked( bool checked )
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().enableSkybox(checked);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxAlignmentLineWidth_valueChanged(double i)
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setAlignmentLineWidth(i);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowFrameTimes_clicked(bool checked)
{
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().setShowFrameTimes(checked);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxAnimationTime_valueChanged(double value)
{
	//infraCameraController_->setInterpolationTime(value);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxPanSpeed_valueChanged(double value)  // pan speed in spectator mode
{
	//infraCameraController_->getCamera()->movementVelocity_=value;
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxNearPlane_valueChanged(double value)
{
	//infraCameraController_->getCamera()->frustum().nearPlane(value);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxFarPlane_valueChanged(double value)
{
	//infraCameraController_->getCamera()->frustum().farPlane(value);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::onComboBoxRenderSystem_currentIndexChanged(int)
{
	updateRenderSystem();
}
void OpenInfraPlatform::UserInterface::PreferencesDialog::onCheckBoxMSAA_clicked(bool)
{
	updateRenderSystem();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::onComboBoxLanguage_currentIndexChanged(const QString& text)
{
	static const QString qmPath = "Data/translations";
	
	qApp->removeTranslator(translator_);

	if (translator_->load(text, qmPath))
	{	
		qApp->installTranslator(translator_);		
	}
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::createLanguageMenu()
{
	auto translationDir = QDir("Data/translations", "*.qm");
	for (auto f : translationDir.entryInfoList(QDir::Files))
	{
		ui_->comboBoxLanguage->addItem(f.baseName());
	}

	// just use English as default
	// b/c the above sorts alphabetically, thus text and lang do not match
	ui_->comboBoxLanguage->setCurrentText("English");
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::updateRenderSystem()
{
	bool msaa = ui_->checkBoxMSAA->isChecked();
	buw::eRenderAPI renderAPI;

	renderAPI = (buw::eRenderAPI)ui_->comboBoxRenderSystem->currentIndex();
	view_->createViewport(renderAPI, false, msaa);
}


void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxBoundHeight_valueChanged(double value)
{
	auto viewCube = view_->getViewport()->getViewCube();
	auto desc = viewCube->getDescription();
	desc.outerBoundHeight = value;
	desc.innerBoundHeight = value;
	desc.boundHeight = value;
	viewCube->setDescription(desc);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxOuterBoundWidth_valueChanged(double value)
{
	auto viewCube = view_->getViewport()->getViewCube();
	auto desc = viewCube->getDescription();
	desc.outerBoundWidth = value;
	viewCube->setDescription(desc);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxInnerBoundWidth_valueChanged(double value)
{
	auto viewCube = view_->getViewport()->getViewCube();
	auto desc = viewCube->getDescription();
	desc.innerBoundWidth = value;
	viewCube->setDescription(desc);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_doubleSpinBoxSize_valueChanged(double value)
{
    view_->getViewport()->getViewCube()->updateSize(value);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButton_Export_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
                       this,
                       tr("Save File"),
                       QDir::currentPath(),
                       tr("JavaScript Object Notation File (*.json);"));

    view_->getViewport()->getViewCube()->getDescription().saveToFile(filename);
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButton_Import_clicked(QString filename)
{
    if(filename == nullptr) {
        filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Document"),
            QDir::currentPath(),
            tr("Open ViewCube configuration file (*.json);"));
    }
    auto viewCube = view_->getViewport()->getViewCube();
    viewCube->setDescription(viewCube->loadDescription(filename.toStdString()));
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButtonFaceColor_clicked()
{
    faceColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButtonBorderColor_clicked()
{
    borderColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButtonHighlightColor_clicked()
{
    highlightColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_pushButtonTextColor_clicked()
{
    textColorDialog_.show();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_radioButtonLegacy_toggled(bool value)
{
    
    //view_->getViewport()->setUseLegacy(value);
    
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_radioButtonTextured_toggled(bool value)
{
   /* if (value) {
        std::string path = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getViewCubeData().getTexturedViewCubeFilename();
        if (path == "") {
            useTextured = true;
        }
        else {            
            if (useTextured == false) {
                on_pushButton_Import_clicked(QString(path.data()));
                useTextured = true;
            }
        }
    }*/
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_radioButtonStandard_toggled(bool value)
{
    /*if (value) {
        if (OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getViewCubeData().getTexturedViewCubeFilename() != "" && useTextured) {
            std::string path = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getViewCubeData().getViewCubeFilename();
            on_pushButton_Import_clicked(QString(path.data()));
        }

        useTextured = false;*/

        
        //view_->getViewport()->setShowViewCube(ui_->checkBoxShowViewCube->isChecked());
        //view_->getViewport()->setShowCompass(ui_->checkBoxShowCompass->isChecked());
        //view_->getViewport()->setShowRotationArrows(ui_->checkBoxShowRotationArrows->isChecked());
        
    //}
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowViewCube_clicked(bool checked)
{
    OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().showViewCube(checked);
    view_->getViewport()->repaint();
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowCompass_clicked(bool checked)
{
   
    //view_->getViewport()->setShowCompass(checked);
    
}

void OpenInfraPlatform::UserInterface::PreferencesDialog::on_checkBoxShowRotationArrows_clicked(bool checked)
{
    
    //view_->getViewport()->setShowRotationArrows(checked);
    
}
