#include <QStringList>

#include "SimpleTreeItem.h"
#include <type_traits>
#include <cstdlib>

#include "SimpleTreeModel.h"
#include "OpenInfraPlatform/Infrastructure/Export/IfcAlignment1x1Caster.h"
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>

//OpenInfraPlatform::UserInterface::TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
OpenInfraPlatform::UserInterface::TreeItem::TreeItem(std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> &data, TreeItem * parent)
		: m_managedData(data), m_parentItem(parent), parser_()
{
	parser_.thisPtr = this;
}

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
}

OpenInfraPlatform::UserInterface::TreeItem *OpenInfraPlatform::UserInterface::TreeItem::parentItem()
{
	return m_parentItem;
}

void OpenInfraPlatform::UserInterface::TreeItem::setItemData(QList<QVariant> itemData)
{
	m_itemData = itemData;
}

void OpenInfraPlatform::UserInterface::TreeItem::createChildren()
{
		auto func = [&](auto item)->void {
			visit_struct::for_each(item, [&](const char* name, auto &value) {
				TreeItem* child;
				//if(std::is_base_of<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object, decltype(value)>::value) {
				//	child = new TreeItem(value, this);
				//}
				//else {
				//	child = new TreeItem(OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object(), this);
				//}
				std::shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Object> ptr = nullptr;
				child = new TreeItem(ptr, this);
				QList<QVariant> itemData;
				itemData << QVariant(name) << QVariant("") << QVariant(typeid(value).name());
				this->appendChild(child);
				});
		};

		auto parse = [&](auto item) {
			visit_struct::for_each(item, parser_);
		};

		if(m_managedData && m_managedData.get() != nullptr) {
			if(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(m_managedData))
				OpenInfraPlatform::IfcAlignment1x1::castToVisitableAndCall<decltype(parse), void>(std::dynamic_pointer_cast<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>(m_managedData), parse);
		}
}

int OpenInfraPlatform::UserInterface::TreeItem::row() const
{
	if(m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

	return 0;
}