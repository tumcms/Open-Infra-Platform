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

#include "ExportExcelDialog.h"
#include "buw.OIPInfrastructure.h"
#include "OpenInfraPlatform/DataManagement/Data.h"
#include <QFileDialog>
#include <QUuid>

OpenInfraPlatform::UserInterface::ExportExcelDialog::ExportExcelDialog(QWidget *parent /*= nullptr*/) :
ui_(new Ui::ExportExcelDialog),
QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::ExportExcelDialog::~ExportExcelDialog()
{
	
}

void OpenInfraPlatform::UserInterface::ExportExcelDialog::changeEvent(QEvent* evt)
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

void OpenInfraPlatform::UserInterface::ExportExcelDialog::on_pushButtonCancel_clicked()
{
	hide();
}

void OpenInfraPlatform::UserInterface::ExportExcelDialog::on_pushButtonExport_clicked()
{
	hide();

	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Save File"),
		QDir::currentPath(),
		tr("Excel Spreadsheet (*.xlsx)")
		);

	if (filename.isNull() == false)
	{
		DataManagement::DocumentManager::getInstance().getData().createExcelReport(filename.toStdString(), ui_->comboBoxAngleMeasurement->currentText() == QString("Degree"));
	}
}
