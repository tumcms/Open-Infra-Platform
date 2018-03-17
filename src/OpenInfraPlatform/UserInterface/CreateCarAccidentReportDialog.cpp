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

#include "CreateCarAccidentReportDialog.h"

#include "OpenInfraPlatform/DataManagement/Command/CreateAccidentReport.h"
#include "OpenInfraPlatform/DataManagement/Data.h"


OpenInfraPlatform::UserInterface::CreateCarAccidentReportDialog::CreateCarAccidentReportDialog(QWidget *parent /*= nullptr*/) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	ui_(new Ui::FormCreateCarAccidentReport)
{

	ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::CreateCarAccidentReportDialog::~CreateCarAccidentReportDialog()
{

}

void OpenInfraPlatform::UserInterface::CreateCarAccidentReportDialog::on_pushButtonOK_clicked()
{
	int index = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getSelectedAlignment();
	if (index == -1)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Please select an alignment first."));
		msgBox.exec();
		return;
	}

	if (OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel()) {
		buw::ReferenceCounted<buw::IAlignment3D> a = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getAlignmentModel()->getAlignments()[index];

		double station = ui_->lineEditStation->text().toDouble();
		buw::ReferenceCounted<buw::CreateAccidentReport> actionCreateCarAccident = std::make_shared<buw:: CreateAccidentReport>(a, station);
		OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(actionCreateCarAccident);
	}
	
	hide();
}

void OpenInfraPlatform::UserInterface::CreateCarAccidentReportDialog::on_pushButtonCancel_clicked()
{
	hide();
}


