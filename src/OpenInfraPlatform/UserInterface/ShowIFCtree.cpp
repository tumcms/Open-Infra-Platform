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
//#include "Ifc4x1TreeModel.h"
#include "OpenInfraPlatform/DataManagement/Data.h"
#include "SimpleTreeModel.h"

OpenInfraPlatform::UserInterface::ShowIFCtree::ShowIFCtree(OpenInfraPlatform::UserInterface::View * view, QWidget * parent)
	:ui_(new Ui::ShowIFCtree),
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	view_(view)
{
	ui_->setupUi(this);
	ui_->treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
	ui_->treeView->setAutoExpandDelay(-1);
	QObject::connect(ui_->treeView, &QTreeView::expanded, this, &ShowIFCtree::on_treeView_expanded);
}

void OpenInfraPlatform::UserInterface::ShowIFCtree::on_treeView_expanded(const QModelIndex &index)
{
	auto model = ui_->treeView->model();
	model->insertRows(0, model->rowCount(index), index);
}


void OpenInfraPlatform::UserInterface::ShowIFCtree::show()
{
	auto proxyModel = OpenInfraPlatform::DataManagement::DocumentManager::getInstance().getData().getProxyModel();
	auto entities = proxyModel->getIfc4x1Data();
	ui_->treeView->setModel(new SimpleTreeModel(entities)); //Don't forget to change back to Ifc4x1TreeModel

	Q_INIT_RESOURCE(simpletreemodel);

	//QApplication app(argc, argv);

	QFile file("C:\Users\ga87jis\Documents/default.txt");
	file.open(QIODevice::ReadOnly);
	TreeModel model(file.readAll());
	file.close();

	QTreeView view;
	view.setModel(&model);
	view.setWindowTitle(QObject::tr("Simple Tree Model"));
	view.show();
	//return app.exec();

	((QDialog*)this)->show();

}