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

#ifdef OIP_MODULE_EARLYBINDING_IFC2X3
#include "reader/IFC2X3Reader.h"
#include "EMTIFC2X3EntityTypes.h"
#include "IFC2X3.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4
#include "reader/IFC4Reader.h"
#include "EMTIFC4EntityTypes.h"
#include "IFC4.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X1
#include "reader/IFC4X1Reader.h"
#include "EMTIFC4X1EntityTypes.h"
#include "IFC4X1.h"
#endif

#ifdef OIP_MODULE_EARLYBINDING_IFC4X3_RC1
#include "reader/IFC4X3_RC1Reader.h"
#include "EMTIFC4X3_RC1EntityTypes.h"
#include "IFC4X3_RC1.h"
#endif

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
			Ifc4x1TreeModel(std::map<size_t, std::shared_ptr<OpenInfraPlatform::EarlyBinding::EXPRESSEntity>>& entities);
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
