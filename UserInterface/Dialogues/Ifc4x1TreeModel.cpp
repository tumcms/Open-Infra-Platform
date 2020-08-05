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
#include "OpenInfraPlatform/Infrastructure/Export/IfcAlignment1x1Caster.h"
#include "Ifc4x1TreeItem.h"

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>


#include <type_traits>
#include <cstdlib>
#include <QStringList>

OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>& entities)
	:
	QAbstractItemModel()
{
	for (auto it : entities) {
		shared_ptr<Ifc4x1TreeItem> item = std::make_shared<Ifc4x1TreeItem>(it);
		data_.push_back(item);
	
	}
}

OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::~Ifc4x1TreeModel()
{
	data_.clear();
}

QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::index(int row, int column, const QModelIndex & parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid())
		return this->createIndex(row, column, nullptr);
	else {
		return this->createIndex(row, column, nullptr);
		
	}

	//from Qt documentation
	
	shared_ptr<Ifc4x1TreeItem> parentItem;
	if (!parent.isValid())
		parentItem = nullptr;
	//else
	//	parentItem = static_cast<shared_ptr<Ifc4x1TreeItem>>(parent.internalPointer());

	shared_ptr<Ifc4x1TreeItem> childItem = parentItem->child(row);
	//if (childItem)
		//return createIndex(row, column, childItem);
	//else
		return QModelIndex();
}


QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::parent(const QModelIndex & child) const
{
	if(child.internalPointer() != nullptr) {
		return this->createIndex(0, 0, nullptr);
	}
	else {
		return QModelIndex();
	}

	//from Qt documentation
	//shared_ptr<Ifc4x1TreeItem> childItem = static_cast<shared_ptr<Ifc4x1TreeItem>>(child.internalPointer());
	//shared_ptr<Ifc4x1TreeItem> parentItem = childItem->parentItem();

	//if (parentItem==nullptr)
	//	return QModelIndex();

//	return createIndex(parentItem->row(), 0, parentItem);
}


//int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::rowCount(const QModelIndex & parent) const
//{	
//	if (!parent.isValid())
//		return data_.size();
//	else {
//		auto entity = data_.find(parent.row() + 1)->second;
//		auto counter = countRows {};
//		OpenInfraPlatform::IfcAlignment1x1::castToDerivedAndCall<countRows, void>(entity, counter);
//		return counter.rows_;
//	}
//
//	//Menge der Attribute des Objekts data_.size(index) oder data_[parent].size()?oder mit visit struct?
//	//würde das hier auch mit childCount() gehen?
//}
	

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::columnCount(const QModelIndex & parent) const
{
	if (!parent.isValid())
		return 1;
	else
		return 3;
}


//QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::data(const QModelIndex & index, int role) const
//{
//	if (!index.isValid())
//		return QVariant();
//
//	if (role != Qt::DisplayRole)
//		return QVariant();
//
//	if (!index.parent().isValid())
//		return QVariant(data_[index.row()]->getIfcClassName().data());
//	else {
//		
//		auto ptr = std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(buw::claimOwnership(index.internalPointer()));
//		auto name = getName();
//		OpenInfraPlatform::IfcAlignment1x1::castToDerivedAndCall<getName, void>(ptr, name);
//		return QVariant(name.names_[index.row()]);
//	}
//}

bool OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row + count);
	
	endInsertRows();
	return true;
}