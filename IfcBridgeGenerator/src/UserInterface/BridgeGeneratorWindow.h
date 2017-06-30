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

#include <iostream>

BLUE_DROP_COMPILER_LEVEL_TO_3
#include <QtGui>
#include <QMainWindow>
BLUE_RESTORE_COMPILER_WARNING_LEVEL

namespace Ui 
{
	class BridgeGeneratorWindow;
}

namespace BlueIfcBridgeViewer
{
	namespace UserInterface
	{
		//! \class MainWindow
		//! \brief brief description
		class BridgeGeneratorWindow : public QMainWindow
		{
			Q_OBJECT

		public:
			//! Default constructor.
			BridgeGeneratorWindow(QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~BridgeGeneratorWindow()
			{

			}

		public Q_SLOTS:
			void on_pushButtonSaveAs_clicked();

		private:
		

			

		private:
			Ui::BridgeGeneratorWindow *ui_;
		}; // end class MainWindow
	}
}