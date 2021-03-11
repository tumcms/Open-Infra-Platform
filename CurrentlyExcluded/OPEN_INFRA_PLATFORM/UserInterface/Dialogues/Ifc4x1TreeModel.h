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

#pragma once

#include "OpenInfraPlatform/IfcAlignment1x1/model/Object.h"
#include <QAbstractItemModel>
#include <type_traits>
#include <QModelIndex>
#include <QVariant>


namespace OpenInfraPlatform {
	namespace UserInterface {

		class Ifc4x1TreeItem;
		
		class Ifc4x1TreeModel : public QAbstractItemModel {

			Q_OBJECT;

		public:
			Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> >& entities);
			~Ifc4x1TreeModel();

		// Inherited from QAbstractItemModel
			virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
			virtual QModelIndex parent(const QModelIndex & child) const override;
			//virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
			//virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
			virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

		
		private:
			std::vector<shared_ptr<Ifc4x1TreeItem>> data_;		
		};

	}
}
