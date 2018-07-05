#include <QStringList>

#include "SimpleTreeItem.h"

OpenInfraPlatform::UserInterface::TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
	m_parentItem = parent;
	m_itemData = data;
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
	return m_itemData.count();
}

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