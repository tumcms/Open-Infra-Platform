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

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>


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
		return this->createIndex(row, column, nullptr);
	else {
		return this->createIndex(row, column, std::static_pointer_cast<void>(data_.find(parent.row() + 1)->second).get());
	}
}

QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::parent(const QModelIndex & child) const
{
	if(child.internalPointer() != nullptr) {
		return this->createIndex(((OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity*) child.internalPointer())->getId() - 1, 0, nullptr);
	}
	else {
		return QModelIndex();
	}
}

struct OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::countRows
{
	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
	operator()(T entity)
	{
		rows_ = visit_struct::field_count(entity);
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
	{
		std::string message = "Invalid function call. " + std::string(typeid(entity).name()) + " isn't a member of IfcAlignment1x1Entity.";
		throw buw::Exception(message.data());
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	void operator()(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity& entity) const
	{
		std::string message = "Invalid function call.";
		throw buw::Exception(message.data());
	}

	size_t rows_ = 0;
};

int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::rowCount(const QModelIndex & parent) const
{	
	if (!parent.isValid())
		return data_.size();
	else {
		auto entity = data_.find(parent.row() + 1)->second;
		auto counter = countRows {};
		OpenInfraPlatform::IfcAlignment1x1::castAndCall<countRows, void>(entity, counter);
		return counter.rows_;
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

struct OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::getName {
		
	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T entity)
	{
		visit_struct::for_each(entity, [&](const char* name, const auto &value) {names_.push_back(name); });
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T& entity) const
	{
		std::string message = "Invalid function call. " + std::string(typeid(entity).name()) + " isn't a member of IfcAlignment1x1Entity.";
		throw buw::Exception(message.data());
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	void operator()(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity& entity) const
	{
		std::string message = "Invalid function call.";
		throw buw::Exception(message.data());
	}

	std::vector<const char*> names_;
};


QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	if (!index.parent().isValid())
		return QVariant(data_.find(index.row() + 1)->second->classname());
	else {
		auto ptr = std::static_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(buw::claimOwnership(index.internalPointer()));
		auto name = getName();
		OpenInfraPlatform::IfcAlignment1x1::castAndCall<getName, void>(ptr, name);
		return QVariant(name.names_[index.row()]);
	}
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

