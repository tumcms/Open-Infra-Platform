#include <QStringList>

#include "SimpleTreeItem.h"
#include <type_traits>
#include <cstdlib>

#include "SimpleTreeModel.h"

#include <BlueFramework\Core\Exception.h>
#include <BlueFramework\Core\memory.h>

//OpenInfraPlatform::UserInterface::TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)

OpenInfraPlatform::UserInterface::TreeItem::TreeItem(TreeItem * parent)
{
	m_parentItem = parent;
}

OpenInfraPlatform::UserInterface::TreeItem::~TreeItem()
{
	qDeleteAll(m_childItems);
}

void OpenInfraPlatform::UserInterface::TreeItem::createChildren()
{
	// Has no implementation in this class.
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

int OpenInfraPlatform::UserInterface::TreeItem::row() const
{
	if(m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

	return 0;
}