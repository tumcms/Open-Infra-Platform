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


OpenInfraPlatform::UserInterface::IfcTreeModel::IfcTreeModel(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSModel> expressModel, QObject *parent)
	: QAbstractItemModel(parent)
{
	//rootItem_ = std::make_shared<IfcTreeItem>(expressModel->entities.find(1)->second, nullptr); //make ifcProject the root item 
	//std::string text = "Title";
	rootItem_ = std::make_shared<IfcTreeItem>();
	setupModelData(expressModel, rootItem_);
}

OpenInfraPlatform::UserInterface::IfcTreeModel::~IfcTreeModel()
{
	
}

QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	std::shared_ptr<IfcTreeItem> parentItemShared;

	if (!parent.isValid())
		parentItemShared = rootItem_;
		//return this->createIndex(row, column, nullptr);
	else
	{
		IfcTreeItem *parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());
		std::shared_ptr<IfcTreeItem> parentTemp(parentItem);
		parentItemShared = parentTemp;
	}

	std::shared_ptr<IfcTreeItem> childItemShared = parentItemShared->child(row);
	IfcTreeItem *childItem = childItemShared.get();
	if (childItem)
		return createIndex(row, column, childItem);
	return QModelIndex();
}

QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	return rootItem_->data(section);
}

QModelIndex OpenInfraPlatform::UserInterface::IfcTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	IfcTreeItem *childItem = static_cast<IfcTreeItem*>(index.internalPointer());
	std::shared_ptr<IfcTreeItem> childItemShared(childItem);
	std::shared_ptr<IfcTreeItem> parentItemShared = childItem->parentItem();
	IfcTreeItem *parentItem = parentItemShared.get();

	if (parentItemShared == rootItem_)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int OpenInfraPlatform::UserInterface::IfcTreeModel::rowCount(const QModelIndex &parent) const
{
	//normal pointer is needed for parent.internalPoiter() and shared_ptr is needed to compare with rootitem_
	std::shared_ptr<IfcTreeItem> parentItemShared;
	IfcTreeItem *parentItem = parentItemShared.get();

	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
	{
		parentItemShared = rootItem_;
		parentItem = parentItemShared.get();
	}
	else
		parentItem = static_cast<IfcTreeItem*>(parent.internalPointer());
	
	int nrOfRows = parentItem->childCount();
	return nrOfRows;
}

int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<IfcTreeItem*>(parent.internalPointer())->columnCount();
	return rootItem_->columnCount();
}

//int OpenInfraPlatform::UserInterface::IfcTreeModel::columnCount(const QModelIndex &parent) const
//{
//	if (!parent.isValid())
//		return 1; //correct for testing?
//	else
//		return 3;
//}

Qt::ItemFlags OpenInfraPlatform::UserInterface::IfcTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return QAbstractItemModel::flags(index);
}

QVariant OpenInfraPlatform::UserInterface::IfcTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	IfcTreeItem *item = static_cast<IfcTreeItem*>(index.internalPointer());

	return item->data(index.column());
}

void OpenInfraPlatform::UserInterface::IfcTreeModel::setupModelData(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSModel> expressModel, std::shared_ptr<IfcTreeItem> parent)
{
	//auto entities = expressModel->entities;

	//for (int i = 0; i < 10; i++)
	//{
	//	std::shared_ptr<IfcTreeItem> item = std::make_shared<IfcTreeItem>(entities.find(i)->second, parent);
	//	parent->appendchild(item);
	//}

	for (const auto& entity : expressModel->entities)
	{
		parent->appendchild(std::make_shared<IfcTreeItem>(entity.second, parent));
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