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

#ifndef IFCTREEITEM_H
#define IFCTREEITEM_H

#include "EXPRESS/EXPRESSReference.h"
#include <QVariant>
#include <QList>


namespace OpenInfraPlatform {
	namespace UserInterface {

		class IfcTreeItem
		{
		//public:
		//	explicit IfcTreeItem(OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data, IfcTreeItem *parentItem);
		//	explicit IfcTreeItem();
		//	QString getIfcClassName() const;

		//private:
		//	QVector<IfcTreeItem*> childItems_;
		//	OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data_;
		//	std::vector<std::string> itemData_;
		//	IfcTreeItem *parentItem_;

		public:
			explicit IfcTreeItem(const QList<QVariant> &data, IfcTreeItem *parentItem = 0);
			explicit IfcTreeItem(OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data, IfcTreeItem *parentItem);
			~IfcTreeItem();

			void appendChild(IfcTreeItem *child);

			IfcTreeItem *child(int row);
			int childCount() const;
			int columnCount() const;
			QVariant data(int column) const;
			int row() const;
			IfcTreeItem *parentItem();

		private:
			QList<IfcTreeItem*> m_childItems;
			OpenInfraPlatform::EarlyBinding::EXPRESSEntity *data_;
			QList<QVariant> m_itemData;
			IfcTreeItem *m_parentItem;

			//struct getAttributeDescription;
		};
	}
}


#endif //IFCTREEITEM_H

namespace oip
{
	using OpenInfraPlatform::UserInterface::IfcTreeItem;
}