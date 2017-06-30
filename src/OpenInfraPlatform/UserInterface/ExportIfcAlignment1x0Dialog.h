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
#ifndef OpenInfraPlatform_UserInterface_ExportP6AlginmentDialog_84f19553_085c_4888_88c3_3ffee5176b52_h
#define OpenInfraPlatform_UserInterface_ExportP6AlginmentDialog_84f19553_085c_4888_88c3_3ffee5176b52_h

#include "ui_ExportIfcAlignmentDialog.h"
#include "OpenInfraPlatform/DataManagement/IfcZipper.h"
#include <QDialog>
#include <iostream>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class ExportIfcAlignment1x0Dialog : public QDialog
		{
			Q_OBJECT;

		public:
			ExportIfcAlignment1x0Dialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~ExportIfcAlignment1x0Dialog();

		protected:
			virtual void changeEvent(QEvent* evt) override;

		private Q_SLOTS:
			void on_pushButtonCancel_clicked();

			void on_pushButtonExport_clicked();

		private:
			Ui::ExportP6AlignmentDialog*	ui_;
		}; // end class ExportP6AlginmentDialog
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::ExportIfcAlignment1x0Dialog;
}

#endif // end define OpenInfraPlatform_UserInterface_ExportP6AlginmentDialog_84f19553_085c_4888_88c3_3ffee5176b52_h
