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
#ifndef OpenInfraPlatform_UserInterface_CreateClothoidDialog2_a6a106b1_5ff0_4136_9549_b0f156cb9906_h
#define OpenInfraPlatform_UserInterface_CreateClothoidDialog2_a6a106b1_5ff0_4136_9549_b0f156cb9906_h

#include "OpenInfraPlatform/Infrastructure/Alignment/HorizontalAlignment/HorizontalAlignmentElement2DClothoid.h"
#include "ui_CreateClothoid2.h"
#include <QDialog>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class CreateClothoidDialog2 : public QDialog
		{
			Q_OBJECT;

		public:
			CreateClothoidDialog2(QWidget *parent = nullptr);

			virtual ~CreateClothoidDialog2();

		private Q_SLOTS:
			void on_pushButtonCreate_clicked();

			void on_pushButtonCancel_clicked();

		private:
			buw::clothoidDescription	cd_;
			Ui::CreateClothoid2*		ui_;
		}; // end class CreateClothoidDialog2
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::CreateClothoidDialog2;
}

#endif // end define OpenInfraPlatform_UserInterface_CreateClothoidDialog2_a6a106b1_5ff0_4136_9549_b0f156cb9906_h