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

#include "UserInterface/TunnelGenerator.h"

#include <QtCore>
#include <QMainWindow>

int main(int argc, char *argv[])
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

	QApplication application(argc, argv);
	std::string basePath = "Style/appleseed_mod.qss";

	QFile styleSheet(basePath.c_str());

	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Unable to open stylesheet");
	}
	else
	{
		application.setStyleSheet(styleSheet.readAll());
	}

	UserInterface::TunnelGenerator tg;
	tg.show();

	return application.exec();
}
