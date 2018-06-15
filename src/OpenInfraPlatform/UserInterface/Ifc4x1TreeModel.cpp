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

#include <type_traits>
#include <cstdlib>

OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>& entities)
	:
	QAbstractItemModel()
{
	data_ = entities;
	//was machen folgende?
	//data_._Get_data
	//data_._Parent
	//data_[4].get()


	//represent an imaginary parent of top-level items in the model:
	//QList<QVariant> rootData;
	//rootData << "Title" << "Summary";
	//rootItem = new TreeItem(rootData);
	//setupModelData(data.split(QString("\n")), rootItem);
}

QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::index(int row, int column, const QModelIndex & parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid())
		return this->createIndex(row, column, std::static_pointer_cast<void>(data_.find(row + 1)->second).get());
	else {
		//TODO: Return the index relative to the parent index!
		return this->createIndex(row, column, nullptr);
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
struct countRows {
	
	
};

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::rowCount(const QModelIndex & parent) const
{
	
	if (!parent.isValid())
		return data_.size();
	else {
		auto entity = data_.find(parent.row() + 1)->second;
		int rows = 0;
		OpenInfraPlatform::IfcAlignment1x1::castAndCall(entity, countRows{});
		return rows;
	}

	//Menge der Attribute des Objekts data_.size(index) oder data_[parent].size()?oder mit visit struct?
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::columnCount(const QModelIndex & parent) const
{
	if (!parent.isValid())
		return 1;
	else
		return 3;
}

QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	if (!index.parent().isValid())
		return QVariant(data_.find(index.row() + 1)->second->classname());
	else
		return QVariant("test");
	//return QVariant () data_.find(index) ;
}

bool OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row + count);
	endInsertRows();
	return true;
}

/*template <class T, class R, class E>
struct OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::my_type {
	T a;
	R b;
	E c;
	std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data_;
};



VISITABLE_STRUCT(OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::my_type, a, b, c, data_);



struct debug_printer {
	template <typename T>
	void operator()(const char * name, const T & value) {
		std::cerr << name << ": " << value << std::endl;
	}
};

void debug_print(const my_type & my_struct) {
	visit_struct::for_each(my_struct, debug_printer{});
}

visit_struct::get<i>(s);
visit_struct::field_count(s);
visit_struct::get_name<i>(s);
*/

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

