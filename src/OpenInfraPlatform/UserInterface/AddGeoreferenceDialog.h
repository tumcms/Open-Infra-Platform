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
#include <iostream>


namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class AddGeoreferenceDialog : public QDialog
		{
			Q_OBJECT;

		private:
			//New functions AddGeoreference
			/*buttonBoxOkCancel
			pushButtonCheck
			doubleSpinBoxEasting
			doubleSpinBoxHeight
			doubleSpinBoxNorthing
			labelAreaName
			labelEPSG
			labelEasting
			*/




		public:
			//! Default constructor.
			AddGeoreferenceDialog(OpenInfraPlatform::UserInterface::View* view, QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~AddGeoreferenceDialog();

	

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
