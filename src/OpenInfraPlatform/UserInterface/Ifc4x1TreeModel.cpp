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

#include "Ifc4x1TreeModel.h"

OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>& entities)
	:
	QAbstractItemModel()
{
	data_ = entities;

	//represent an imaginary parent of top-level items in the model:
	//QList<QVariant> rootData;
	//rootData << "Title" << "Summary";
	//rootItem = new TreeItem(rootData);
	//setupModelData(data.split(QString("\n")), rootItem);
}

QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::index(int row, int column, const QModelIndex & parent) const
{	
	if(!hasIndex(row, column, parent))
		return QModelIndex();

	if(!parent.isValid())
		return this->createIndex(row, column, std::static_pointer_cast<void>(data_.find(row + 1)->second).get());
	else {
		//TODO: Return the index relative to the parent index!
		return QModelIndex();
	}
}

QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::parent(const QModelIndex & child) const
{
	//QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::parent(const QModelIndex &index) const
	//{
	//	if (!index.isValid())
	//		return QModelIndex();

	//	TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
	//	TreeItem *parentItem = childItem->parentItem();

	//	if (parentItem == rootItem)
	//		return QModelIndex();

	//	return createIndex(parentItem->row(), 0, parentItem);
	//}
	
	/*TreeItem *TreeItem::parentItem()
	{
		return m_parentItem;
	}
	/*for (auto it : data_) {
		  
		}
	return Q_INVOKABLE QModelIndex();*/
	return QModelIndex();
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::rowCount(const QModelIndex & parent) const
{
	if(!parent.isValid())
		return data_.size();
	else
		return 1;
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::columnCount(const QModelIndex & parent) const
{
	return 1;
}

QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();	

	return QVariant(data_.find(index.row()+1)->second->classname());
	//return QVariant () data_.find(index) ;
}



// from Qt documentation 
//TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
//{
//	parentItem_ = parent;
//	itemData_ = data;
//}
//TreeItem *TreeItem::child(int row)
//{
//	return childItems_.value(row);
//}