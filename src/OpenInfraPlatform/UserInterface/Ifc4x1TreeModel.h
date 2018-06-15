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

#pragma once

#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include <QAbstractItemModel>
#include <type_traits>

namespace OpenInfraPlatform {
	namespace UserInterface {

		class Ifc4x1TreeModel : public QAbstractItemModel {

			Q_OBJECT;

		public:
			//explicit TreeModel(const QString &data, QObject *parent = 0); from Qt documentation
			//~TreeModel(); from Qt documentation
			Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> >& entities);
		// Geerbt über QAbstractItemModel
			virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
			virtual QModelIndex parent(const QModelIndex & child) const override;
			virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
			virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

		
		private:
			std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data_;
			
			struct countRows;
			struct getName;

		
		//private:
			//void setupModelData(const QStringList &lines, TreeItem *parent);

			//TreeItem *rootItem;
		};


		//from Qt documentation http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
		class TreeItem
		{
		public:
			explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
			//~TreeItem();

			//void appendChild(TreeItem *child);

			TreeItem *child(int row);
			//int childCount() const;
			//int columnCount() const;
			//QVariant data(int column) const;
			//int row() const;
			//TreeItem *parentItem();

		private:
			QList<TreeItem*> childItems_;
			QList<QVariant> itemData_;
			TreeItem *parentItem_;
		};
	}
}
