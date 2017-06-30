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

#include "UserInterface/BridgeGeneratorWindow.h"
#include "buw.BlueCore.h"

BLUE_DROP_COMPILER_LEVEL_TO_3
#include <QtGui>
#include <QtCore>
#include <QLabel>
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
BLUE_RESTORE_COMPILER_WARNING_LEVEL

int main(int argc,char *argv[])
{
	std::ofstream logfile;
	logfile.open("log.txt");
	buw::LogManager::getInstance().addOutputStream(&logfile);

	buw::LifetimeManager lm;

	// log file should be outputted in XML format
	buw::logMangerSettings settings;
	settings.outputAsXML = true;
	settings.colorConsoleOutput = true;
	buw::LogManager::getInstance().setSettings(settings);
	buw::LogManager::getInstance().LogCPUInfo();
	buw::LogManager::getInstance().LogOSInfo();
	buw::LogManager::getInstance().LogGPUInfo();
		
	QApplication application(argc,argv);
	std::string basePath = "Style/blueform.qss";

	QFile styleSheet(basePath.c_str());

 	if (!styleSheet.open(QIODevice::ReadOnly))
 	{
 		qWarning("Unable to open stylesheet");
 	}
 	else
 	{
 		application.setStyleSheet(styleSheet.readAll());
 	}

	BlueIfcBridgeViewer::UserInterface::BridgeGeneratorWindow bgw;
	bgw.show();

	return application.exec();
}
