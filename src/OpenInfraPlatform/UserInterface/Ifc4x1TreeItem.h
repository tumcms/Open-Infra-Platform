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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

class Ifc4x1TreeItem
{
public:
	explicit Ifc4x1TreeItem(std::pair<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data, Ifc4x1TreeItem *parentItem = 0);
	~Ifc4x1TreeItem();

	void appendChild(Ifc4x1TreeItem *child);

	Ifc4x1TreeItem *child(int row);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	Ifc4x1TreeItem *parentItem();

private:
	QList<Ifc4x1TreeItem*> childItems_;
	std::pair<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data_;
	Ifc4x1TreeItem *parentItem_;
};

#endif // TREEITEM_H
