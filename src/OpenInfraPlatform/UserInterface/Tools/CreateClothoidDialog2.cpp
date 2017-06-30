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

#include "CreateClothoidDialog2.h"

#include "OpenInfraPlatform/DataManagement/Data.h"
#include "OpenInfraPlatform/DataManagement/Command/CommandCreateClothoid.h"

OpenInfraPlatform::UserInterface::CreateClothoidDialog2::CreateClothoidDialog2(QWidget *parent /*= nullptr*/) :
ui_(new Ui::CreateClothoid2),
QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui_->setupUi(this);

	ui_->lineEditStartPointX->setText(QString::number(cd_.startPosition.x()));
	ui_->lineEditStartPointY->setText(QString::number(cd_.startPosition.y()));
	ui_->lineEditStartDirection->setText(QString::number(cd_.startDirection));
	ui_->lineEditStartCurvature->setText(QString::number(cd_.startCurvature));
	ui_->checkCounterClockwise->setChecked(cd_.counterClockwise);
	ui_->lineEditClothoidConstant->setText(QString::number(cd_.clothoidConstant));
	ui_->checkBoxIsEntry->setChecked(cd_.entry);
	ui_->lineEditLength->setText(QString::number(cd_.length));
}

OpenInfraPlatform::UserInterface::CreateClothoidDialog2::~CreateClothoidDialog2()
{

}

void OpenInfraPlatform::UserInterface::CreateClothoidDialog2::on_pushButtonCreate_clicked()
{
	cd_.startPosition.x() = ui_->lineEditStartPointX->text().toDouble();
	cd_.startPosition.y() = ui_->lineEditStartPointY->text().toDouble();
	cd_.startDirection = ui_->lineEditStartDirection->text().toDouble();
	cd_.startCurvature = ui_->lineEditStartCurvature->text().toDouble();
	cd_.counterClockwise = ui_->checkCounterClockwise->isChecked();
	cd_.clothoidConstant = ui_->lineEditClothoidConstant->text().toDouble();
	cd_.entry = ui_->checkBoxIsEntry->isChecked();
	cd_.length = ui_->lineEditLength->text().toDouble();

	buw::ReferenceCounted<buw::CommandCreateClothoid> cmdCreateClothoid = std::make_shared<buw::CommandCreateClothoid>(cd_);
	OpenInfraPlatform::DataManagement::DocumentManager::getInstance().execute(cmdCreateClothoid);

	hide();
}

void OpenInfraPlatform::UserInterface::CreateClothoidDialog2::on_pushButtonCancel_clicked()
{
	hide();
}
