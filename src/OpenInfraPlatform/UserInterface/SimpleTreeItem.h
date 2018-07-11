#pragma once
#ifndef TREEITEM_H
#define TREEITEM_H


#include <QList>
#include <QVariant>
#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include "OpenInfraPlatform\IfcAlignment1x1\model\Model.h"

#include <visit_struct/visit_struct.hpp>

namespace OpenInfraPlatform {
	namespace UserInterface {
		class TreeItem {
		public:
			TreeItem(TreeItem* parent = nullptr);
			virtual ~TreeItem();

			virtual void createChildren();

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
			TreeItem *m_parentItem;
		};

		template <typename T> class TreeItemT : public TreeItem {
		public:
			TreeItemT(T data, TreeItem* parent) : TreeItem(parent)
			{
				m_managedData = data;
				
			}

			virtual void createChildren()
			{

			}

		private:
			T m_managedData;
		};		
	}
}

#endif // TREEITEM_H