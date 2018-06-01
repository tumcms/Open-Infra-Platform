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

namespace OpenInfraPlatform {
	namespace UserInterface {

		class Ifc4x1TreeModel : public QAbstractItemModel {
		public:
			Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> >& entities);
		// Geerbt über QAbstractItemModel
			virtual Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
			virtual Q_INVOKABLE QModelIndex parent(const QModelIndex & child) const override;
			virtual Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual Q_INVOKABLE int columnCount(const QModelIndex & parent = QModelIndex()) const override;
			virtual Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
		
		private:
			std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity> > data_;			
		};
	}
}
