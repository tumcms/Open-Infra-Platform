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

#include "VectorTableModel.h"

int OpenInfraPlatform::UserInterface::VectorTableModel::rowCount(const QModelIndex & parent) const
{
	return 3;
}

int OpenInfraPlatform::UserInterface::VectorTableModel::columnCount(const QModelIndex & parent) const
{
	return 3;
}

QVariant OpenInfraPlatform::UserInterface::VectorTableModel::data(const QModelIndex & index, int role) const
{
	if(role == Qt::DisplayRole)
		return QVariant(QString::number(data_(index.row(), index.column())));
	else
		return QVariant();
}
