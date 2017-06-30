/*
    Copyright (c) 2017 Technical University of Munich
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
#ifndef OpenInfraPlatform_UserInterface_ExportExcelDialog_84eafb57_f094_44d1_8067_add4302b6b7e_h
#define OpenInfraPlatform_UserInterface_ExportExcelDialog_84eafb57_f094_44d1_8067_add4302b6b7e_h

#include "ui_ExportExcel.h"
#include <QDialog>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class ExportExcelDialog : public QDialog
		{
			Q_OBJECT;

		public:
			ExportExcelDialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~ExportExcelDialog();

		protected:
			virtual void changeEvent(QEvent* evt) override;

		private Q_SLOTS:
			void on_pushButtonCancel_clicked();

			void on_pushButtonExport_clicked();

		private:
			Ui::ExportExcelDialog*	ui_;
		}; // end class ExportExcelDialog
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::ExportExcelDialog;
}

#endif // end define OpenInfraPlatform_UserInterface_ExportExcelDialog_84eafb57_f094_44d1_8067_add4302b6b7e_h
