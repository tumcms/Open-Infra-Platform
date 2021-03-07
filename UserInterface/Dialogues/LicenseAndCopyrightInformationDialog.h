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

#include "ui_LicenseAndCopyrightInformation.h"
#include <QDialog>
#include <iostream>

namespace OpenInfraPlatform
{
    namespace UserInterface
    {
        class LicenseAndCopyrightInformationDialog : public QDialog
        {
            Q_OBJECT;

        public:
            LicenseAndCopyrightInformationDialog(QWidget *parent = nullptr);

            //! Virtual destructor.
            virtual ~LicenseAndCopyrightInformationDialog();
					
        private Q_SLOTS:
			void on_pushButtonClose_clicked();

        private:
            Ui::LicenseAndCopyrightInformationDialog*	ui_;
        }; // end class ExportP6AlginmentDialog
    } // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
    using OpenInfraPlatform::UserInterface::LicenseAndCopyrightInformationDialog;
}
