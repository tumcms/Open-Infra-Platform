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
#include <type_traits>
#include <cstdlib>

#include "Ifc4x1TreeItem.h"
#include "Ifc4x1TreeModel.h"
//#include "OpenInfraPlatform/Infrastructure/Export/IfcAlignment1x1Caster.h"

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>



OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::Ifc4x1TreeItem(std::map<size_t, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>> data, std::shared_ptr<Ifc4x1TreeItem> parentItem)
{
parentItem_ = parentItem;
data_ = data;
//auto attributes = getAttributeDescription();
//auto entity = data_.find(parent.row() + 1)->second; 
//OpenInfraPlatform::IfcAlignment1x1::castAndCall(entity, attributes);
//hier cast and call verwenden und den getattributedesciption struct übergeben
}

struct OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::getAttributeDescription {

	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
		operator()(T entity)
	{
		visit_struct::for_each(entity, [&](const char* name, const auto &value) {
			names_.push_back(name);
			typename_= typeid(T).name(entity);
			value_.push_back(value);
			
		});
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
		operator()(T& entity) const
	{
		std::string message = "Invalid function call. " + std::string(typeid(entity).name()) + " isn't a member of IfcAlignment1x1Entity.";
		throw buw::Exception(message.data());
	}

	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
	void operator()(OpenInfraPlatform::EarlyBinding::EXPRESSEntity& entity) const
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
	childItems_.clear();
}

void OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::appendChild(std::shared_ptr<Ifc4x1TreeItem> item)
{
	childItems_.append(item);
}

std::shared_ptr<OpenInfraPlatform::UserInterface::Ifc4x1TreeItem> OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::child(int row)
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
	auto attributes = getAttributeDescription();
	
	switch (column)
	{
	case 0:
		return attributes.names_[row];
		break;
	case 1:
		return attributes.value_[row];//data_.value(column);//value of the object
		break;
	case 2:
		return attributes.typename_[row];//type of the object 
		break;
	}

}

std::shared_ptr<OpenInfraPlatform::UserInterface::Ifc4x1TreeItem> OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::parentItem()
{
	if (parentItem_)
		return parentItem_;

	return std::shared_ptr<OpenInfraPlatform::UserInterface::Ifc4x1TreeItem>();
}

std::string OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::getIfcClassName()
{
	return std::string(data_.second->classname());
}


int OpenInfraPlatform::UserInterface::Ifc4x1TreeItem::row() const
{
//	if (parentItem_)
//		return parentItem_->childItems_.indexOf(const_cast<shared_ptr<Ifc4x1TreeItem>>(this));

	return 0;
}