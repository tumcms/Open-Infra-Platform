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

#include "IfcTreeModel.h"

#include <type_traits>
#include <cstdlib>
#include <memory>

#include <QStringList>
#include <QString>


OpenInfraPlatform::UserInterface::IfcTreeModel::IfcTreeModel(OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel, QObject *parent)
	: QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "Summary";
	rootItem = new IfcTreeItem(rootData);
	setupModelData(expressModel, rootItem);
}

OpenInfraPlatform::UserInterface::IfcTreeModel::~IfcTreeModel()
{
	delete rootItem;
}

int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<IfcTreeItem*>(parent.internalPointer())->columnCount();
	else
		return rootItem->columnCount();
}

//int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
//{
//	if (!parent.isValid())
//		return 1; //correct for testing?
//	else
//		return 3;
//}


QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	IfcTreeItem *item = static_cast<IfcTreeItem*>(index.internalPointer());

	return item->data(index.column());
}

QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	IfcTreeItem *parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());

	IfcTreeItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	IfcTreeItem *childItem = static_cast<IfcTreeItem*>(index.internalPointer());
	IfcTreeItem *parentItem = childItem->parentItem();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int OpenInfraPlatform::UserInterface::IfcTreeModel::rowCount(const QModelIndex &parent) const
{
	IfcTreeItem *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());

	return parentItem->childCount();
}

void OpenInfraPlatform::UserInterface::IfcTreeModel::setupModelData(const OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel, IfcTreeItem *parent)
{
	for (auto entity : expressModel->entities)
	{
		parent->appendChild(new IfcTreeItem(entity.second.get(), parent));
	}
}