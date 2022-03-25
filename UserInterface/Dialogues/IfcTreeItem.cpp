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


OpenInfraPlatform::UserInterface::IfcTreeItem::IfcTreeItem(OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data, IfcTreeItem *parentItem)
{
	data_ = data;
	parentItem_ = parentItem;
	//itemData_.push_back(data_->getStepLine());
	itemData_.push_back(QString::fromStdString(data_->classname()));
}

//OpenInfraPlatform::UserInterface::IfcTreeItem::IfcTreeItem(std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> &data, IfcTreeItem * parent)
//	: m_managedData(data), m_parentItem(parent), parser_()
//{
//	parser_.thisPtr = this;
//}

OpenInfraPlatform::UserInterface::IfcTreeItem::IfcTreeItem(const QList<QVariant> &data, IfcTreeItem *parent)
{
	parentItem_ = parent;
	itemData_ = data;
}

OpenInfraPlatform::UserInterface::IfcTreeItem::~IfcTreeItem()
{
	qDeleteAll(childItems_);
}

void OpenInfraPlatform::UserInterface::IfcTreeItem::appendChild(IfcTreeItem *child)
{
	childItems_.append(child);
}

OpenInfraPlatform::UserInterface::IfcTreeItem *OpenInfraPlatform::UserInterface::IfcTreeItem::child(int row)
{
	//if (row < 0 || row >= m_childItems.size())
	//	return nullptr;
	return childItems_.value(row); //QList provides default values in case row is out of range
}

int OpenInfraPlatform::UserInterface::IfcTreeItem::childCount() const
{
	return childItems_.count();
}

int OpenInfraPlatform::UserInterface::IfcTreeItem::columnCount() const
{
	return itemData_.count();
}

QVariant OpenInfraPlatform::UserInterface::IfcTreeItem::data(int column) const
{
	//if (column < 0 || column >= m_itemData.size())
	//	return QVariant();
    return itemData_.value(column); //QList provides default values in case row is out of range
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
//}

OpenInfraPlatform::UserInterface::IfcTreeItem *OpenInfraPlatform::UserInterface::IfcTreeItem::parentItem()
{
	return parentItem_;
}

int OpenInfraPlatform::UserInterface::IfcTreeItem::row() const
{
	if (parentItem_)
		return parentItem_->childItems_.indexOf(const_cast<IfcTreeItem*>(this));

	return 0;
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

//void OpenInfraPlatform::UserInterface::IfcTreeItem::createChildren()
//{
//	auto func = [&](auto item)->void {
//		visit_struct::for_each(item, [&](const char* name, auto &value) {
//			IfcTreeItem* child;
//			//if(std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object, decltype(value)>::value) {
//			//	child = new TreeItem(value, this);
//			//}
//			//else {
//			//	child = new TreeItem(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object(), this);
//			//}
//			std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSObject> ptr = nullptr;
//			child = new IfcTreeItem(ptr, this);
//			QList<QVariant> itemData;
//			itemData << QVariant(name) << QVariant("") << QVariant(typeid(value).name());
//			this->appendChild(child);
//		});
//	};
//
//	auto parse = [&](auto item) {
//		visit_struct::for_each(item, parser_);
//	};
//
//	if (m_managedData && m_managedData.get() != nullptr) {
//		if (std::dynamic_pointer_cast<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>(m_managedData)) {
//			//OpenInfraPlatform::IfcAlignment1x1::castToVisitableAndCall<decltype(parse), void>(std::dynamic_pointer_cast<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>(m_managedData), parse);
//		}
//	}
//}

//void OpenInfraPlatform::UserInterface::TreeItem::setItemData(QList<QVariant> itemData)
//{
//	itemData_ = itemData;
//}