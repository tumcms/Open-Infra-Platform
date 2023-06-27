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

#include "HttpTreeModel.h"

OpenInfraPlatform::UserInterface::HttpTreeModel::HttpTreeModel(QWidget* parent /*=nullptr*/)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	setupUi(this);
}


OpenInfraPlatform::UserInterface::HttpTreeModel::~HttpTreeModel()
{

}


void OpenInfraPlatform::UserInterface::HttpTreeModel::on_selectBtn_clicked()
{
	// get the tree item index position
	QModelIndex selectedModel = this->httpWidget->currentIndex();
	// handle case if child item selected
	if (!selectedModel.parent().isValid())
		position_ = selectedModel.row();
	else
		position_ = selectedModel.parent().row();

	this->accept();
}


void OpenInfraPlatform::UserInterface::HttpTreeModel::buildTreeModel(const QJsonArray& data)
{
	// set columns
	this->httpWidget->setColumnCount(2);

	// column headers
	this->httpWidget->setHeaderLabels(QStringList() << "Tag" << "Description");

	// create root and child tree items for each data option
	for (QJsonArray::const_iterator it = data.begin(); it != data.end(); ++it)
		addTreeRoot(it->toObject());
}


void OpenInfraPlatform::UserInterface::HttpTreeModel::addTreeRoot(const QJsonObject& rootObject)
{
	// if "osm_type" = "node" -> skip
	if (rootObject.value("osm_type").toString() != "node") {

		// istantiate tree item
		QTreeWidgetItem* rootItem = new QTreeWidgetItem(this->httpWidget);

		// set root name and description
		rootItem->setText(0, rootObject.value("category").toString());
		rootItem->setText(1, rootObject.value("type").toString());

		// add child for root (five top address details and postcode) [Nominatim]
		addTreeChild(rootItem, rootObject.value("address").toObject());
	}
}


void OpenInfraPlatform::UserInterface::HttpTreeModel::addTreeChild(QTreeWidgetItem* parent, const QJsonObject& childObject)
{
	// set child name and description
	for (QJsonObject::const_iterator it = childObject.begin(); it != childObject.end(); ++it)
	{
		// istantiate tree item
		QTreeWidgetItem* childItem = new QTreeWidgetItem();
		// set child properties
		childItem->setText(0, it.key());
		childItem->setText(1, it.value().toString());
		parent->addChild(childItem);
	}
}