#pragma once

#include <QAbstractItemModel>
#include <QString>
#include <QModelIndex>
#include <QVariant>

#include "IfcTreeItem.h"


namespace OpenInfraPlatform {
	namespace UserInterface {

		class IfcTreeModel : public QAbstractItemModel {
			Q_OBJECT;

		private:
			IfcTreeItemBase *rootItem;

		public:
			template <typename T> IfcTreeModel(std::map<int, shared_ptr<T>> &data, QObject *parent = 0)
				: QAbstractItemModel(parent)
			{
				std::shared_ptr<T> ptr = nullptr;
				rootItem = new IfcTreeItem<T>(ptr, nullptr);

				for (auto entity : data) {
					IfcTreeItem<T>* child = new IfcTreeItem<T>(entity.second, rootItem);
					QList<QVariant> itemData;
					itemData << QVariant(entity.first) << QVariant(entity.second->classname()) << QVariant("");
					child->setItemData(itemData);
					child->createChildren();
					rootItem->appendChild(child);
				}

			}

			~IfcTreeModel()
			{
				delete rootItem;
			}

			QVariant data(const QModelIndex &index, int role) const override
			{
				if (!index.isValid())
					return QVariant();

				if (role != Qt::DisplayRole)
					return QVariant();

				IfcTreeItemBase *item = static_cast<IfcTreeItemBase*>(index.internalPointer());
				return item->data(index.column());

			}

			Qt::ItemFlags flags(const QModelIndex &index) const override
			{
				if (!index.isValid())
					return 0;

				return QAbstractItemModel::flags(index);
			}

			QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
			{
				if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
					return QVariant(QString::number(section));

				return QVariant();
			}

			QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
			{
				if (!hasIndex(row, column, parent))
					return QModelIndex();

				IfcTreeItemBase *parentItem;

				if (!parent.isValid())
					parentItem = rootItem;
				else
					parentItem = static_cast<IfcTreeItemBase*>(parent.internalPointer());

				IfcTreeItemBase *childItem = parentItem->child(row);
				if (childItem)
					return createIndex(row, column, childItem);
				else
					return QModelIndex();

			}

			QModelIndex parent(const QModelIndex &index) const override
			{
				if (!index.isValid())
					return QModelIndex();

				IfcTreeItemBase *childItem = static_cast<IfcTreeItemBase*>(index.internalPointer());
				IfcTreeItemBase *parentItem = childItem->parentItem();

				if (parentItem == rootItem)
					return QModelIndex();

				return createIndex(parentItem->row(), 0, parentItem);
			}

			int rowCount(const QModelIndex &parent = QModelIndex()) const override
			{
				IfcTreeItemBase *parentItem;
				if (parent.column() > 0)
					return 0;

				if (!parent.isValid())
					parentItem = rootItem;
				else
					parentItem = static_cast<IfcTreeItemBase*>(parent.internalPointer());

				return parentItem->childCount();
			}

			int columnCount(const QModelIndex &parent = QModelIndex()) const override
			{
				if (parent.isValid())
					return static_cast<IfcTreeItemBase*>(parent.internalPointer())->columnCount();
				else
					return rootItem->columnCount();
			}

		
		};
	}
}
