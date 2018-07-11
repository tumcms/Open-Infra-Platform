#include <QStringList>

#include "SimpleTreeItem.h"
#include <type_traits>
#include <cstdlib>

#include "SimpleTreeModel.h"
#include "OpenInfraPlatform/Infrastructure/Export/IfcAlignment1x1Caster.h"

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>

//OpenInfraPlatform::UserInterface::TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
OpenInfraPlatform::UserInterface::TreeItem::TreeItem(std::pair<int, std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>&data, TreeItem *parent)
{
	m_parentItem = parent;
	m_managedData = data;
}

struct OpenInfraPlatform::UserInterface::TreeItem::getAttributeDescription {

	template <class T> typename std::enable_if<visit_struct::traits::is_visitable<T>::value && std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity, T>::value, void>::type
		operator()(T entity)
	{
		visit_struct::for_each(entity, [&](const char* name, const auto &value) {
			names_.push_back(name);
			typename_ = typeid(T).name(entity);
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

OpenInfraPlatform::UserInterface::TreeItem::~TreeItem()
{
	qDeleteAll(m_childItems);
}

void OpenInfraPlatform::UserInterface::TreeItem::appendChild(TreeItem *item)
{
	m_childItems.append(item);
}

OpenInfraPlatform::UserInterface::TreeItem *OpenInfraPlatform::UserInterface::TreeItem::child(int row)
{
	return m_childItems.value(row);
}

int OpenInfraPlatform::UserInterface::TreeItem::childCount() const
{
	return m_childItems.count();
}

int OpenInfraPlatform::UserInterface::TreeItem::columnCount() const
{
	return 3;
}

//QVariant OpenInfraPlatform::UserInterface::TreeItem::data(int column) const
QVariant OpenInfraPlatform::UserInterface::TreeItem::data(int column) const
{
	return m_itemData.value(column);
	//return m_itemData.second->classname;
	//auto attributes = getAttributeDescription();
	//
	//switch(column) {
	//case 0:
	//	return attributes.names_[row];
	//	break;
	//case 1:
	//	return attributes.value_[row];//data_.value(column);//value of the object
	//	break;
	//case 2:
	//	return attributes.typename_[row];//type of the object 
	//	break;
	//}
}

OpenInfraPlatform::UserInterface::TreeItem *OpenInfraPlatform::UserInterface::TreeItem::parentItem()
{
	return m_parentItem;
}

int OpenInfraPlatform::UserInterface::TreeItem::row() const
{
	if(m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

	return 0;
}