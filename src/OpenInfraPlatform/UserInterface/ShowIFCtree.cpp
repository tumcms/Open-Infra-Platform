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

#include "ShowIFCtree.h"
#include "Ifc4x1TreeModel.h"
#include "OpenInfraPlatform/DataManagement/Data.h"

OpenInfraPlatform::UserInterface::ShowIFCtree::ShowIFCtree(OpenInfraPlatform::UserInterface::View * view, QWidget * parent)
	:ui_(new Ui::ShowIFCtree),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	view_(view)
{
	ui_->setupUi(this);
	ui_->treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
	ui_->treeView->setAutoExpandDelay(-1);
	QObject::connect(ui_->treeView, &QTreeView::activated, this, &ShowIFCtree::on_treeView_expanded);
}

void OpenInfraPlatform::UserInterface::ShowIFCtree::on_treeView_expanded(const QModelIndex &index)
{
	if (true)
		std::printf("blub");
}


void OpenInfraPlatform::UserInterface::ShowIFCtree::show()
{
	auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	auto entities = proxyModel->getIfc4x1Data();
	ui_->treeView->setModel(new Ifc4x1TreeModel(entities));


	((QDialog*)this)->show();
}