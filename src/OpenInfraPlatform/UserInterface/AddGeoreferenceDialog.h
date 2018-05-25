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

#include "ui_AddGeoreferenceDialog.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/View.h"
//#include <BlueFramework/Engine/Camera/InfraCameraController.h>
#include <QDialog>
#include <boost/noncopyable.hpp>
#include <string>
#include <iostream>
#include <locale>
#include <algorithm>


using namespace OpenInfraPlatform::IfcAlignment1x1;
namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class AddGeoreferenceDialog : public QDialog
		{
			Q_OBJECT;
		public:
			//Initiates values in dialogue to values stored in data and calls QWidget::show()
			void show();
			//New functions AddGeoreference
			/*buttonBoxOkCancel

			pushButtonCheck
			doubleSpinBoxEasting
			doubleSpinBoxHeight
			doubleSpinBoxNorthing
			labelOutputAreaName
			spinBoxEPSG

			*/
			//Prüfen ob es schon einen bestehenden EPSG-Code für das Modell gibt
						
		private Q_SLOTS:
			void on_pushButtonCheck_clicked();
			void on_doubleSpinBoxEasting_valueChanged(double value);

			void on_doubleSpinBoxHeight_valueChanged(double value);
			void on_doubleSpinBoxNorthing_valueChanged(double value);

			//Checks whether EPSG code exists and outputs area label (with setText function)
			void on_spinBoxEPSG_valueChanged(int value);
			void on_pushButtonCancel_clicked();
			void on_pushButtonOk_clicked();

			
		public:
			//! Default constructor.
			AddGeoreferenceDialog(OpenInfraPlatform::UserInterface::View* view, QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~AddGeoreferenceDialog() {};

			double m_Eastings;
			double m_Northings;
			double m_OrthogonalHeight;
			QString m_Name;

		private:
			Ui::AddGeoreferenceDialog*	ui_;
			
			QTranslator*			translator_;
			OpenInfraPlatform::UserInterface::View* view_;
			//buw::ReferenceCounted<buw::InfraCameraController>	infraCameraController_;

		}; // end class AddGeoreference
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::AddGeoreferenceDialog;
} 
