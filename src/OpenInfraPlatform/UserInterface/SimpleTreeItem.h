#pragma once
#ifndef TREEITEM_H
#define TREEITEM_H


#include <QList>
#include <QVariant>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "OpenInfraPlatform\IfcAlignment1x1\model\Model.h"

namespace OpenInfraPlatform {
	namespace UserInterface {
		template <typename T> class TreeItem {
		public:
			//explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
			explicit TreeItem(T &data, TreeItem *parentItem = 0);
			
			~TreeItem();

			void appendChild(TreeItem *child);

			TreeItem *child(int row);
			int childCount() const;
			int columnCount() const;
			QVariant data(int column) const;
			int row() const;
			TreeItem *parentItem();

		private:
			QList<TreeItem*> m_childItems;
			QList<QVariant> m_itemData;

			T m_managedData;
			TreeItem *m_parentItem;
			struct getAttributeDescription;
		};
	}
}

#endif // TREEITEM_H