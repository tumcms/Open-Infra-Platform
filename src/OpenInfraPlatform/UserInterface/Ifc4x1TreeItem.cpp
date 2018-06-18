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

#include "Ifc4x1TreeItem.h"

Ifc4x1TreeItem::Ifc4x1TreeItem(std::pair<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data; , TreeItem *parent)
{
	parentItem_ = parent;
	data_ = data;
}

Ifc4x1TreeItem::~Ifc4x1TreeItem()
{
	qDeleteAll(childItems_);
}

void Ifc4x1TreeItem::appendChild(Ifc4x1TreeItem *item)
{
	childItems_.append(item);
}

Ifc4x1TreeItem *Ifc4x1TreeItem::child(int row)
{
	return childItems_.value(row);
}

int Ifc4x1TreeItem::childCount() const
{
	return childItems_.count();
}

int Ifc4x1TreeItem::columnCount() const
{
	return m_itemData.count();
}

QVariant Ifc4x1TreeItem::data(int column) const
{
	return m_itemData.value(column);
}

Ifc4x1TreeItem *Ifc4x1TreeItem::parentItem()
{
	return m_parentItem;
}

int Ifc4x1TreeItem::row() const
{
	if (m_parentItem)
		return m_parentItem->childItems_.indexOf(const_cast<Ifc4x1TreeItem*>(this));

	return 0;
}