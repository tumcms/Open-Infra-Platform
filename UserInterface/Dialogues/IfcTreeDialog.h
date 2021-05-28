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

#include "ui_IfcTreeDialog.h"
#include "ViewPanel/View.h"

#include <QDialog>
#include <iostream>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class IfcTreeDialog : public QDialog
		{
			Q_OBJECT;

		public:
			IfcTreeDialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~IfcTreeDialog();

			void show();

		private Q_SLOTS:
			void on_pushButtonClose_clicked();

		private:
			Ui::IfcTreeDialog* ui_;
			OpenInfraPlatform::UserInterface::View* view_;
		}; // end class IfcTree
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace oip
{
	using OpenInfraPlatform::UserInterface::IfcTreeDialog;
}
