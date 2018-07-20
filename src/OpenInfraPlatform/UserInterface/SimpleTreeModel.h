#pragma once

#include <QAbstractItemModel>
#include <QString>
#include <QModelIndex>
#include <QVariant>

#include "SimpleTreeItem.h"

namespace OpenInfraPlatform {
	namespace UserInterface {

		class TreeModel : public QAbstractItemModel {
			Q_OBJECT;

		public:
			TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>> &data, QObject *parent = 0);
			//explicit TreeModel(const QString &data, QObject *parent = 0);
			~TreeModel();

			template <typename T> QVariant data(const QModelIndex &index, int role) const override
			{
				if(!index.isValid())
					return QVariant();

				if(role != Qt::DisplayRole)
					return QVariant();

				TreeItem<T> *item = static_cast<TreeItem<T>*>(index.internalPointer());				
				return item->data(index.column());

			}

			Qt::ItemFlags flags(const QModelIndex &index) const override;

			QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

			template <typename ParentT, typename ChildT> QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
			{
				if(!hasIndex(row, column, parent))
					return QModelIndex();

				TreeItem<ParentT> *parentItem;

				if(!parent.isValid())
					parentItem = rootItem;
				else
					parentItem = static_cast<TreeItem<ParentT>*>(parent.internalPointer());

				TreeItem<ChildT> *childItem = parentItem->child(row);
				if(childItem)
					return createIndex(row, column, childItem);
				else
					return QModelIndex();

			}

			template <typename ParentT, typename ChildT> QModelIndex parent(const QModelIndex &index) const override
			{
				if(!index.isValid())
					return QModelIndex();

				TreeItem<ChildT> *childItem = static_cast<TreeItem<ChildT>*>(index.internalPointer());
				TreeItem<ParentT> *parentItem = childItem->parentItem();

				if(parentItem == rootItem)
					return QModelIndex();

				return createIndex(parentItem->row(), 0, parentItem);
			}

			template <typename T> int rowCount(const QModelIndex &parent = QModelIndex()) const override
			{
				TreeItem<T> *parentItem;
				if(parent.column() > 0)
					return 0;

				if(!parent.isValid())
					parentItem = rootItem;
				else
					parentItem = static_cast<TreeItem<T>*>(parent.internalPointer());

				return parentItem->childCount();
			}

			template <typename T> int columnCount(const QModelIndex &parent = QModelIndex()) const override
			{
				if(parent.isValid())
					return static_cast<TreeItem<T>*>(parent.internalPointer())->columnCount();
				else
					return rootItem->columnCount();
			}

		private:
			//void setupModelData(const QStringList &lines, TreeItem *parent);

			TreeItem<QList<QVariant>> *rootItem;
			//std::vector<shared_ptr<TreeItem>> data_;
		};
	}
}
