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

#include "XYZImportDialog.h"

#include "OpenInfraPlatform/DataManagement/Data.h"

#include "OpenInfraPlatform/DataManagement/Command/ImportXYZ.h"


OpenInfraPlatform::UserInterface::XYZImportDialog::XYZImportDialog( QWidget *parent /*= nullptr*/ ) :
    ui_(new Ui::XYZImportDialog),
    QDialog(parent, Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
    ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::XYZImportDialog::~XYZImportDialog()
{

}

void OpenInfraPlatform::UserInterface::XYZImportDialog::changeEvent(QEvent* evt) 
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

void OpenInfraPlatform::UserInterface::XYZImportDialog::on_pushButtonBrowse_clicked()
{
    QString openFile = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::currentPath(),tr("XYZ Files (*.xyz);;Text files (*.txt)"));
    std::string utf8_text_file = openFile.toUtf8().constData();

    ui_->lineEdit->setText(openFile);
}

void OpenInfraPlatform::UserInterface::XYZImportDialog::on_pushButtonImport_clicked()
{

	bool useRestriction = ui_->restrict_radioButton->isChecked();
	buw::Vector2d start = buw::Vector2d::Ones() * std::numeric_limits<double>::min();
	buw::Vector2d end = buw::Vector2d::Ones() * std::numeric_limits<double>::max();

	if (useRestriction)
	{
		start.x() = ui_->startX_LineEdit->text().toDouble();
		start.y() = ui_->startY_LineEdit->text().toDouble();

		end.x() = ui_->endX_LineEdit->text().toDouble();
		end.y() = ui_->endY_LineEdit->text().toDouble();
	}

	std::string filename = ui_->lineEdit->text().toUtf8().constData();

	buw::ReferenceCounted<buw::ImportXYZ> ia = std::make_shared<buw::ImportXYZ>(filename, start, end);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(ia);

	hide();
	
}

