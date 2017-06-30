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
#ifndef OpenInfraPlatform_UserInterface_ExportIfcZipDialog
#define OpenInfraPlatform_UserInterface_ExportIfcZipDialog

#include <ui_ExportIfczipDialog.h>
#include <QDialog>
#include "OpenInfraPlatform/DataManagement/IfcZipper.h"
#include <iostream>


namespace OpenInfraPlatform {
	namespace UserInterface {
		class ExportIfcZipDialog : public QDialog {
			Q_OBJECT;
		public:
			ExportIfcZipDialog(QWidget *parent = nullptr);			
			virtual ~ExportIfcZipDialog();
			OpenInfraPlatform::DataManagement::IfcZipper* zipper;

			

		private Q_SLOTS:
		void on_pushButtonCancel_clicked();
		void on_pushButtonExport_clicked();

		private:
			Ui::ExportIfcZipDialog* ui_;
		};
	}
}

namespace buw
{
	using OpenInfraPlatform::UserInterface::ExportIfcZipDialog;
}

#endif