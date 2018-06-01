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

#include "Ifc4x1TreeModel.h"

OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::Ifc4x1TreeModel(std::map<int, shared_ptr<OpenInfraPlatform::IfcAlignment1x1::IfcAlignment1x1Entity>>& entities)
	:
	QAbstractItemModel()
{
	data_ = entities;
}

Q_INVOKABLE QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::index(int row, int column, const QModelIndex & parent) const
{	
	return this->createIndex(row, column, nullptr);
}

Q_INVOKABLE QModelIndex OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::parent(const QModelIndex & child) const
{
	for (auto it : data_) {
		  
		}
	return Q_INVOKABLE QModelIndex();
}

Q_INVOKABLE int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::rowCount(const QModelIndex & parent) const
{
	return data_.size();
}

Q_INVOKABLE int OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::columnCount(const QModelIndex & parent) const
{
	return 1;
}

Q_INVOKABLE QVariant OpenInfraPlatform::UserInterface::Ifc4x1TreeModel::data(const QModelIndex & index, int role) const
{
	return QVariant() data_.find(index);
}
