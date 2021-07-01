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
//
//OpenInfraPlatform::UserInterface::IfcTreeModel::~IfcTreeModel()
//{
//	delete rootItem_;
//}
//
//QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::index(int row, int column, const QModelIndex &parent) const
//{
//	if (!hasIndex(row, column, parent))
//		return QModelIndex();
//
//	IfcTreeItem* parentItem;
//
//	if (!parent.isValid())
//		parentItem = rootItem_;
//		//return this->createIndex(row, column, nullptr);
//	else
//		parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());
//
//	IfcTreeItem *childItem = parentItem->child(row);
//	if (childItem)
//	{
//		auto n = createIndex(row, column, childItem);
//		return n;
//	}
//		//return createIndex(row, column, childItem);
//	return QModelIndex();
//}
//
//QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::headerData(int section, Qt::Orientation orientation,
//	int role) const
//{
//	return rootItem_->data(section);
//}
//
//QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::parent(const QModelIndex &index) const
//{
//	if (!index.isValid())
//		return QModelIndex();
//
//	IfcTreeItem *child = static_cast<IfcTreeItem*>(index.internalPointer());
//	IfcTreeItem *parentItem = child->parentItem();
//
//	if (parentItem == rootItem_)
//		return QModelIndex(); 
//
//	return createIndex(parentItem->row(), 0, parentItem);
//}
//
//int OpenInfraPlatform::UserInterface::IfcTreeModel::rowCount(const QModelIndex &parent) const
//{
//	IfcTreeItem *parentItem;
//
//	if (parent.column() > 0)
//		return 0;
//
//	if (!parent.isValid())
//		parentItem = rootItem_;
//	else
//		parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());
//	
//	int nrOfRows = parentItem->childCount();
//	return nrOfRows;
//}
//
//int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
//{
//	if (parent.isValid())
//		return static_cast<IfcTreeItem*>(parent.internalPointer())->columnCount();
//	int nrOfColumns = rootItem_->columnCount();
//	return nrOfColumns;
//}

//int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
//{
//	if (!parent.isValid())
//		return 1; //correct for testing?
//	else
//		return 3;
//}

//Qt::ItemFlags OpenInfraPlatform::UserInterface::IfcTreeModel::flags(const QModelIndex &index) const
//{
//	if (!index.isValid())
//		return Qt::NoItemFlags;
//
//	return QAbstractItemModel::flags(index);
//}
//
//QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::data(const QModelIndex &index, int role) const
//{
//	if (!index.isValid())
//		return QVariant();
//
//	IfcTreeItem *item = static_cast<IfcTreeItem*>(index.internalPointer());
//
//	return item->data(index.column());
//}
//
void OpenInfraPlatform::UserInterface::IfcTreeModel::setupModelData(const OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel, IfcTreeItem *parent)
{
	//auto entities = expressModel->entities;

	//for (int i = 0; i < 10; i++)
	//{
	//	IfcTreeItem *item = new IfcTreeItem(entities.find(i)->second.get(), parent);
	//	parent->appendChild(item);
	//}

	for (auto entity : expressModel->entities)
	{
		parent->appendChild(new IfcTreeItem(entity.second.get(), parent));
	}

	//for (int i = 3; i < 4; i++)
	//{
	//	std::shared_ptr<IfcTreeItem> item1 = std::make_shared<IfcTreeItem>(entities.find(i)->second, parent);
	//	parent->appendchild(item1);
	//	std::shared_ptr<IfcTreeItem> item2 = std::make_shared<IfcTreeItem>(entities.find(i + 1)->second, parent);
	//	parent->appendchild(item2);
	//	std::shared_ptr<IfcTreeItem> item3 = std::make_shared<IfcTreeItem>(entities.find(i + 2)->second, parent);
	//	parent->appendchild(item3);
	//}
	//for (auto entity : entities)
	//{
	//	IfcTreeItem *item = new IfcTreeItem(entity.second);
	//	std::shared_ptr<IfcTreeItem> itemShared(item);
	//	rootItem_->appendchild(itemShared);
	//}
}

//OpenInfraPlatform::UserInterface::IfcTreeModel::IfcTreeModel(const QString &data, QObject *parent)
//	: QAbstractItemModel(parent)
//{
//	QList<QVariant> rootData;
//	rootData << "Title" << "Summary";
//	rootItem = new IfcTreeItem(rootData);
//	setupModelData(data.split(QString("\n")), rootItem);
//}

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

QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	IfcTreeItem *item = static_cast<IfcTreeItem*>(index.internalPointer());

	return item->data(index.column());
}

//Qt::ItemFlags OpenInfraPlatform::UserInterface::IfcTreeModel::flags(const QModelIndex &index) const
//{
//	if (!index.isValid())
//		return 0;
//
//	return QAbstractItemModel::flags(index);
//}

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

//void OpenInfraPlatform::UserInterface::IfcTreeModel::setupModelData(const QStringList &lines, IfcTreeItem *parent)
//{
//	QList<IfcTreeItem*> parents;
//	QList<int> indentations;
//	parents << parent;
//	indentations << 0;
//
//	int number = 0;
//
//	while (number < lines.count()) {
//		int position = 0;
//		while (position < lines[number].length()) {
//			if (lines[number].at(position) != ' ')
//				break;
//			position++;
//		}
//
//		QString lineData = lines[number].mid(position).trimmed();
//
//		if (!lineData.isEmpty()) {
//			// Read the column data from the rest of the line.
//			QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
//			QList<QVariant> columnData;
//			for (int column = 0; column < columnStrings.count(); ++column)
//				columnData << columnStrings[column];
//
//			if (position > indentations.last()) {
//				// The last child of the current parent is now the new parent
//				// unless the current parent has no children.
//
//				if (parents.last()->childCount() > 0) {
//					parents << parents.last()->child(parents.last()->childCount() - 1);
//					indentations << position;
//				}
//			}
//			else {
//				while (position < indentations.last() && parents.count() > 0) {
//					parents.pop_back();
//					indentations.pop_back();
//				}
//			}
//
//			// Append a new item to the current parent's list of children.
//			parents.last()->appendChild(new IfcTreeItem(columnData, parents.last()));
//		}
//
//		++number;
//	}
//}