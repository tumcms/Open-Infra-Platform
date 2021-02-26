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
#ifndef OpenInfraPlatform_UserInterface_VectorTableModel_77D1FC2A_E9AE_4EDD_93A2_FBDEDD7648F2_h
#define OpenInfraPlatform_UserInterface_VectorTableModel_77D1FC2A_E9AE_4EDD_93A2_FBDEDD7648F2_h

#include <QAbstractTableModel>
#include <BlueFramework/Core/Math/vector.h>


namespace OpenInfraPlatform {
	namespace UserInterface {
		class VectorTableModel : public QAbstractTableModel {
			Q_OBJECT;

		public:
			VectorTableModel(const Eigen::Matrix<double, 3, 3> &data) : QAbstractTableModel(), data_(data){	}

			virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
			virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
			virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

		private:
			Eigen::Matrix<double, 3, 3> data_;
		};
	}
}

#endif //endif define OpenInfraPlatform_UserInterface_VectorTableModel_77D1FC2A_E9AE_4EDD_93A2_FBDEDD7648F2_h
