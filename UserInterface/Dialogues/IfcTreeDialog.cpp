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

#include "IfcTreeDialog.h"
#include "IfcTreeModel.h"
#include "ui_IfcTreeDialog.h"
#include "DataManagement/General/Data.h"

OpenInfraPlatform::UserInterface::IfcTreeDialog::IfcTreeDialog(OpenInfraPlatform::UserInterface::View* view, QWidget *parent /*= nullptr*/) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	ui_(new Ui::IfcTreeDialog),
	view_(view)
{
	ui_->setupUi(this);
	//ui_->ifcTreeWidget->setAnimated(true);
	//ui_->ifcTreeView->setModel(new IfcTreeModel());
}

OpenInfraPlatform::UserInterface::IfcTreeDialog::~IfcTreeDialog()
{

}

void OpenInfraPlatform::UserInterface::IfcTreeDialog::show()
{
	//for first testing just get last model, later this will be changed to selecting the model need
	auto model = Core::DataManagement::DocumentManager::getInstance().getData().getLastModel();
	auto ifcModel = std::static_pointer_cast<OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel>(model);
	auto entities = ifcModel->getExpressModel();
	ui_->ifcTreeView->setAnimated(true);
	//ui_->ifcTreeView->setModel(new IfcTreeModel());
	((QDialog*)this)->show();
}


void OpenInfraPlatform::UserInterface::IfcTreeDialog::on_pushButtonClose_clicked()
{
	hide();
}
