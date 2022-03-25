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
#include "Exception\UnhandledException.h"
#include <QFileSystemModel>
#include <QTreeWidgetItem>

#include <filesystem>
#include <string>
#include <iostream>
#include <direct.h>

OpenInfraPlatform::UserInterface::IfcTreeDialog::IfcTreeDialog(QWidget *parent /*= nullptr*/) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	ui_(new Ui::IfcTreeDialog)
{
	ui_->setupUi(this);
}

OpenInfraPlatform::UserInterface::IfcTreeDialog::~IfcTreeDialog()
{

}

void OpenInfraPlatform::UserInterface::IfcTreeDialog::show()
{
	//testing treeview with contents of IFC file
	auto model = Core::DataManagement::DocumentManager::getInstance().getData().getLastModel();
	if (std::dynamic_pointer_cast<oip::IfcModel>(model))
	{
		auto ifcModel = std::static_pointer_cast<OpenInfraPlatform::Core::IfcGeometryConverter::IfcModel>(model);
		auto expressModelShared = ifcModel->getExpressModel();
		OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel = expressModelShared.get();
		IfcTreeModel *treeModel = new IfcTreeModel(expressModel);
		ui_->ifcTreeView->setModel(treeModel);
		((QDialog*)this)->show();
	}
	else
	{
		//only for now till the selected model is properly handled
		throw  oip::UnhandledException("Last model is not a IFC model");
	}
}


void OpenInfraPlatform::UserInterface::IfcTreeDialog::on_pushButtonClose_clicked()
{
	hide();
}
