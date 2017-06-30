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

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define SPLASH_SCREEN
#endif

#include "OpenInfraPlatform/Benchmark.h"
#include "OpenInfraPlatform/UserInterface/CodeEditorWindow.h"
#include "OpenInfraPlatform/UserInterface/MainWindow.h"
#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Version.h>
#include <QApplication>
#include <QDockWidget>
#include <QMainWindow>
#include <QSplashScreen>
#include <QtCore>
#include <QtGui>
#include <sstream>
#include <sstream>
#include <string>

#include "version.h"

void compile();

QSplashScreen* g_splash = nullptr;

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <shlobj.h>
#include <codecvt>

using convert_type = std::codecvt_utf8<wchar_t>;


void SignalHandler(int signal) {
	printf("Signal %d", signal);
	throw buw::Exception("!Access Violation!");
}

int main(int argc, char* argv[]) {
	typedef void (*SignalHandlerPointer)(int);

	SignalHandlerPointer previousHandler;
	previousHandler = signal(SIGSEGV, SignalHandler);

	QApplication application(argc, argv);

	try {
		application.addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

		QApplication::setApplicationName("TUM Open Infra Platform 2017");
		QApplication::setApplicationVersion(OpenInfraPlatform::VERSION_STR.c_str());
		QApplication::setOrganizationName("Technische Universitaet Muenchen Chair of Computational Modeling and Simulation");
		QApplication::setOrganizationDomain("cms.bv.tum.de");
		QApplication::setWindowIcon(QIcon(":/images/icons/icon.ico"));

#ifdef SPLASH_SCREEN
		g_splash = new QSplashScreen();
		g_splash->setPixmap(QPixmap(":/images/splash.png"));
		g_splash->show();

		Qt::Alignment leftBottom = Qt::AlignLeft | Qt::AlignBottom;
		g_splash->showMessage("Starting application...", leftBottom, Qt::lightGray);
#endif
		wchar_t* localAppData = 0;
		SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

		std::wstringstream ss;
		ss << localAppData << L"/OpenInfraPlatform/";

		CoTaskMemFree(static_cast<void*>(localAppData));
		//setup converter
		std::wstring_convert<convert_type, wchar_t> converter;

		//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
		std::string converted_str = converter.to_bytes(ss.str());
		converted_str = "";
		buw::initializeLogSystem(converted_str, true, true);
			
		BLUE_LOG(trace) << "Initialized log system";

		// 		if (!true)
		// 		{
		// 			compile();
		// 			return 0;
		// 		}

		OpenInfraPlatform::Benchmark::getInstance().beginStartup();

		// check if we have an appropriate BlueFramework
		int patchNumber = 559;
		if (!buw::Version::isAtLeast(3, 0, patchNumber)) {
			BLUE_LOG(error) << "Please switch to BlueFramework 3.0." << patchNumber << " or newer (can be downloaded from vertexwahn.de/blueframework)!";
			system("pause");
		}

		if (buw::Version::getPatch() != BLUEFRAMEWORK_API_PATCH) {
			BLUE_LOG(error) 
				<< "Invalid BlueCore DLL found! Found DLL patch version " 
				<< buw::Version::getPatch() 
				<< " but header file is at " 
				<< BLUEFRAMEWORK_API_PATCH;
		}

		// Test our exception handling!
		//*(int *)0 = 0;// Baaaaaaad thing that should never happen
		// throw std::runtime_error("muh");

		std::string basePath = "Style/blueform.qss";

		QFile styleSheet(basePath.c_str());

		if (!styleSheet.open(QIODevice::ReadOnly)) {
			qWarning("Unable to open stylesheet");
		} else {
			application.setStyleSheet(styleSheet.readAll());
		}

		QTranslator translator;
		translator.load("English", "Data/translations");
		application.installTranslator(&translator);

		OpenInfraPlatform::UserInterface::MainWindow mainWindow;
		mainWindow.setAttribute(Qt::WA_QuitOnClose);
		mainWindow.show();

		// OpenInfraPlatform::UserInterface::CodeEditorWindow CodeEditor;
		// CodeEditor.show();
		// return application.exec();

		if (g_splash) {
			g_splash->hide();
			delete g_splash;
		}

		return application.exec();
	} catch (const buw::FileNotFoundException& e) {
		std::stringstream ss;
		ss << "An unexpected error occurred:\nCould not find file \"" << e.getFilename().c_str() << "\"";
		QMessageBox::information(nullptr, QApplication::applicationName(), ss.str().c_str());
	} catch (const buw::Exception& e) {
		std::stringstream ss;
		ss << "An unexpected error occurred:\n" << e.what() << "\"";
		QMessageBox::information(nullptr, QApplication::applicationName(), ss.str().c_str());
	} catch (...) {
		std::stringstream ss;
		ss << "An unexpected error occurred in logging catch block.";
		QMessageBox::information(nullptr, QApplication::applicationName(), ss.str().c_str());
		return -1;
	}
}
