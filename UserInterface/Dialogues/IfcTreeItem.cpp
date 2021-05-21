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

#include "IfcTreeItem.h"
#include <QStringList>
#include <type_traits>
#include <cstdlib>
#include "Exception\UnhandledException.h"
#include "visit_struct\visit_struct.hpp"


OpenInfraPlatform::UserInterface::IfcTreeItem::IfcTreeItem(const std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>& data, const std::shared_ptr<IfcTreeItem>& parentItem)
{
	data_ = data;
	parentItem_ = parentItem;
	//itemData_.push_back(data_->getStepLine());
	itemData_.push_back(data_->classname());
}

OpenInfraPlatform::UserInterface::IfcTreeItem::IfcTreeItem()
{
	data_ = nullptr;
	parentItem_ = nullptr;
	std::string text = "Title";
	itemData_.push_back(text);
}

OpenInfraPlatform::UserInterface::IfcTreeItem::~IfcTreeItem()
{
	childItems_.clear();
	//qDeleteAll(childItems_);
}

void OpenInfraPlatform::UserInterface::IfcTreeItem::appendchild(std::shared_ptr<IfcTreeItem> child)
{
	childItems_.append(child);
}

std::shared_ptr<OpenInfraPlatform::UserInterface::IfcTreeItem> OpenInfraPlatform::UserInterface::IfcTreeItem::child(int row)
{
	if (row < 0 || row >= childItems_.size())
		throw oip::UnhandledException("Child index out of range (IfcTreeItem::child)");

	return childItems_.at(row);
}

int OpenInfraPlatform::UserInterface::IfcTreeItem::childCount() const
{
	int nrOfChilds = childItems_.count();
	return nrOfChilds;
}

int OpenInfraPlatform::UserInterface::IfcTreeItem::columnCount() const
{
	return itemData_.size();
}

QVariant OpenInfraPlatform::UserInterface::IfcTreeItem::data(int column) const
{
	if (column < 0 || column >= itemData_.size())
		return QVariant();
	return QString::fromStdString(itemData_.at(column));
}

//QVariant OpenInfraPlatform::UserInterface::IfcTreeItem::data(int column) const
//{
//	//auto attributes = getAttributeDescription()<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>(*data_);
//
//	//switch (column)
//	//{
//	//case 0:
//	//	return attributes.names_[row];
//	//	break;
//	//case 1:
//	//	return attributes.value_[row];
//	//	break;
//	//case 2:
//	//	return attributes.typename_[row];
//	//	break;
//	//}
//	
//	//return QVariant();
//	return getIfcClassName();
//}

int OpenInfraPlatform::UserInterface::IfcTreeItem::row()
{
	if (parentItem_)
	{	
		return parentItem_->childItems_.indexOf(shared_from_this());
	}
	return 0;
}

std::shared_ptr<OpenInfraPlatform::UserInterface::IfcTreeItem> OpenInfraPlatform::UserInterface::IfcTreeItem::parentItem()
{
	return parentItem_;

	//return std::shared_ptr<IfcTreeItem>(); //could be wrong
}

QString OpenInfraPlatform::UserInterface::IfcTreeItem::getIfcClassName() const
{
	std::string ifcClassName = data_->classname();
	return QString::fromStdString(ifcClassName);
}

//struct OpenInfraPlatform::UserInterface::IfcTreeItem::getAttributeDescription 
//{
//	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
//		operator()(T entity)
//	{
//		visit_struct::for_each(entity, [&](const char* name, const auto &value) {
//			names_.push_back(name);
//			typename_ = typeid(T).name(entity);
//			value_.push_back(value);
//		});
//	}
//
//	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
//	template <class T> typename std::enable_if<!std::is_base_of<OpenInfraPlatform::EarlyBinding::EXPRESSEntity, T>::value, void>::type
//		operator()(T& entity) const
//	{
//		std::string message = "Invalid function call. " + std::string(typeid(entity).name()) + " isn't a member of EXPRESSEntity.";
//		throw oip::UnhandledException(message);
//	}
//
//	//This is a dummy function which should never be called but is required by the compiler since it could theoretically be called. Throws exception.
//	void operator()(OpenInfraPlatform::EarlyBinding::EXPRESSEntity& entity) const
//	{
//		throw oip::UnhandledException("Invalid function call (IfcTreeItem::getAttributeDescription)");
//	}
//
//	std::vector<const char*> names_;
//	std::vector<const char*> typename_;
//	std::vector <QVariant> value_;
//};