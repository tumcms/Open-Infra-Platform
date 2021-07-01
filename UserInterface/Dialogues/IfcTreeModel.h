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

#ifndef IFCTREEMODEL_H
#define IFCTREEMODEL_H

#include "IfcTreeItem.h"
#include "EXPRESS/EXPRESSEntity.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


namespace OpenInfraPlatform 
{
	namespace UserInterface 
	{

		class IfcTreeModel : public QAbstractItemModel 
		{
			Q_OBJECT;

		//public:
		//	explicit IfcTreeModel(OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel, QObject *parent = nullptr);
		//	~IfcTreeModel();

		////override from QAbstractItemModel
		//	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		//	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
		//	QModelIndex parent(const QModelIndex &index) const override;
		//	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		//	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
		//	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
		//	Qt::ItemFlags flags(const QModelIndex &index) const override;

		//private:
		//	void setupModelData(OpenInfraPlatform::EarlyBinding::EXPRESSModel *expressModel, IfcTreeItem *parent);

		//	IfcTreeItem *rootItem_;

		public:
			explicit IfcTreeModel(const QString &data, QObject *parent = nullptr);
			~IfcTreeModel();

			QVariant data(const QModelIndex &index, int role) const override;
			Qt::ItemFlags flags(const QModelIndex &index) const override;
			QVariant headerData(int section, Qt::Orientation orientation,
				int role = Qt::DisplayRole) const override;
			QModelIndex index(int row, int column,
				const QModelIndex &parent = QModelIndex()) const override;
			QModelIndex parent(const QModelIndex &index) const override;
			int rowCount(const QModelIndex &parent = QModelIndex()) const override;
			int columnCount(const QModelIndex &parent = QModelIndex()) const override;

		private:
			void setupModelData(const QStringList &lines, IfcTreeItem *parent);

			IfcTreeItem *rootItem;
		};

	}
}

#endif //TREEMODEL_H