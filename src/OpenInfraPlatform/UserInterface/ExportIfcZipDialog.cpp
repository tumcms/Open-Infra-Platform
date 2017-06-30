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

#include "OpenInfraPlatform/UserInterface/ExportIfcZipDialog.h"
#include <QFileDialog>
#include <quuid.h>
#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/DataManagement/AsyncJob.h"

#define DEFL 0
#define INFL 1

#include "ui_ExportIfcZipDialog.h"

OpenInfraPlatform::UserInterface::ExportIfcZipDialog::ExportIfcZipDialog(
	QWidget *parent/* = nullptr*/) :
ui_(new Ui::ExportIfcZipDialog),
QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::ExportIfcZipDialog::~ExportIfcZipDialog()
{

}

void OpenInfraPlatform::UserInterface::ExportIfcZipDialog::on_pushButtonExport_clicked()
{
	hide();

	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Save Document"),
		QDir::currentPath(),
		tr("Zip compressed IfcAlignment BuildingSmart P6 Step File (*.ifczip)"));

	QUuid tempName = QUuid::createUuid();
	QString tempFilename = QDir::currentPath().append(QString("/").append(tempName.toString().append(".ifc")));

	if (!filename.isNull())
	{
		buw::ifcAlignmentExportDescription desc;
		desc.exportTerrain = ui_->checkBoxExportDigitalElevationModel->isChecked();
		desc.exportAlignment = ui_->checkBoxExportAlignment->isChecked();
		desc.useRadiansInsteadOfDegrees = true;

		if (ui_->comboBoxAngleMeasurement->currentText() == QString("Degree"))
		{
			desc.useRadiansInsteadOfDegrees = false;
		}

		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().exportIfcAlignment1x0(
			desc,
			tempFilename.toStdString());

		zipper = new OpenInfraPlatform::DataManagement::IfcZipper(this, filename,tempFilename, DEFL);		
		connect(zipper, &OpenInfraPlatform::DataManagement::IfcZipper::finished, zipper, &QObject::deleteLater);
		connect(&OpenInfraPlatform::AsyncJob::getInstance(), SIGNAL(finished()), zipper, SLOT(start()));		
	}
}

void OpenInfraPlatform::UserInterface::ExportIfcZipDialog::on_pushButtonCancel_clicked()
{
	hide();
}