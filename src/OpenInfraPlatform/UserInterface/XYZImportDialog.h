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
#ifndef OpenInfraPlatform_UserInterface_XYZImport_38da791c_994f_450a_abc1_6676bdf555c4_h
#define OpenInfraPlatform_UserInterface_XYZImport_38da791c_994f_450a_abc1_6676bdf555c4_h

#include <QDialog>
#include <boost/noncopyable.hpp>
#include "ui_XYZImportDialog.h"

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		//! \class XYZImport
		//! \brief brief description
		class XYZImportDialog : public QDialog
		{
			Q_OBJECT;

		public:
			//! Default constructor.
			XYZImportDialog(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~XYZImportDialog();

		protected:
			virtual void changeEvent(QEvent* evt) override;

		private Q_SLOTS:
			void on_pushButtonBrowse_clicked();
			void on_pushButtonImport_clicked();

		private:
			Ui::XYZImportDialog*	ui_;
		}; // end class XYZImport
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::XYZImportDialog;
}

#endif // end define OpenInfraPlatform_UserInterface_XYZImport_38da791c_994f_450a_abc1_6676bdf555c4_h
