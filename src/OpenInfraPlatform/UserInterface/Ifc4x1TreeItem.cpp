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

#include <QStringList>
#include "Ifc4x1TreeItem.h"
#include "Ifc4x1TreeModel.h"

OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::Ifc4x1TreeItem(std::pair<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> data, Ifc4x1TreeItem * parentItem)
{
	parentItem_ = parentItem;
	data_ = data;
}

struct OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::getAttributeDescription {

	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T entity)
	{
		visit_struct::for_each(entity, [&](const char* name, const auto &value) {
			names_.push_back(name);
			typename_= typeid(T).name();
			value_.push_back(value);
			
		});
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
	std::vector<const char*> typename_;
	std::vector <QVariant> value_;

};

OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::~Ifc4x1TreeItem()
{
	qDeleteAll(childItems_);
}

void OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::appendChild(Ifc4x1TreeItem *item)
{
	childItems_.append(item);
}

OpenInfraPlatform::UserInterface::Ifc4x1TreeItem *OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::child(int row)
{
	return childItems_.value(row);
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::childCount() const
{
	return childItems_.count();
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::columnCount() const
{
	return 3;
}

QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::data(int column, int row) const
{
	switch (column)
		case 0:
			return QVariant names_[row];
			break;
		case 1:
			return value_[row];//data_.value(column);//value of the object
				break; 
		case 2:
			return type_[row];//type of the object 
				break;

}

OpenInfraPlatform::UserInterface::Ifc4x1TreeItem *OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::parentItem()
{
	if (parentItem_)
		return parentItem_;

	return 0;
}

int OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::row() const
{
	if (parentItem_)
		return parentItem_->childItems_.indexOf(const_cast<Ifc4x1TreeItem*>(this));

	return 0;
}