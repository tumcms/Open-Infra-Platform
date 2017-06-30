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

#include "ExportIfcAlignment1x0Dialog.h"
#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/DataManagement/AsyncJob.h"
#include <QFileDialog>
#include <QUuid>

OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog::ExportIfcAlignment1x0Dialog(
QWidget *parent/* = nullptr*/) :
	ui_(new Ui::ExportP6AlignmentDialog),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog::~ExportIfcAlignment1x0Dialog()
{

}

void OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog::changeEvent(QEvent* evt)
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

void OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog::on_pushButtonExport_clicked()
{
	hide();

	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Save Document"),
		QDir::currentPath(),
		tr("IFC Alignment 1.0 (*.ifc);;Zip compressed IFC Alignment 1.0 (*.ifczip)")
	);

	if (!filename.isNull())
	{
		buw::ifcAlignmentExportDescription desc;
		desc.exportTerrain = ui_->checkBoxExportDigitalElevationModel->isChecked();
		desc.exportAlignment = ui_->checkBoxExportAlignment->isChecked();
		desc.useRadiansInsteadOfDegrees = true;

		if (ui_->comboBoxIfcSchemaVersion->currentText() == QString("IFC4x1"))
		{
			desc.schemaVersion = buw::eIfcSchemaVersion::IFC4x1;
		}

		if (ui_->comboBoxIfcSchemaVersion->currentText() == QString("IFC4"))
		{
			desc.schemaVersion = buw::eIfcSchemaVersion::IFC4;
		}

		if (ui_->comboBoxIfcSchemaVersion->currentText() == QString("IFC2x3"))
		{
			desc.schemaVersion = buw::eIfcSchemaVersion::IFC2x3;
		}

		if (ui_->comboBoxAngleMeasurement->currentText() == QString("Degree"))
		{
			desc.useRadiansInsteadOfDegrees = false;
		}

		desc.useFixedEntityIdForGeometry = ui_->checkBoxUseFixedEntityIdForGeometry->isChecked();
		desc.startId = ui_->lineEditStartId->text().toInt();
		
		if (filename.endsWith(".ifc")) 
		{
			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcAlignment1x0(
				desc,
				filename.toStdString()
			);
		}
		else if (filename.endsWith("zip"))
		{
			QUuid tempName = QUuid::createUuid();
			QString tempFilename = QDir::currentPath().append(QString("/").append(tempName.toString().append(".ifc")));

			OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcAlignment1x0(
				desc,
				tempFilename.toStdString()
			);

			OpenInfraPlatform::DataManagement::IfcZipper* ExportZipper = new OpenInfraPlatform::DataManagement::IfcZipper(nullptr, QString(filename.data()), tempFilename, DEFL);

			QObject::connect(&OpenInfraPlatform::AsyncJob::getInstance(), SIGNAL(finished()), ExportZipper, SLOT(start()));
			QObject::connect(ExportZipper, &OpenInfraPlatform::DataManagement::IfcZipper::finished, ExportZipper, &QObject::deleteLater);
		}
	}
}

void OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog::on_pushButtonCancel_clicked()
{
	hide();
}
