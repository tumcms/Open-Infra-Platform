/*
DONE:
Zoom via Mouse weehl


Todo:
Finish recent files
Zoom via Icon

herausfindne wie man in civil 3d einen querschnitt modelliert + dokumentieren
support für finnen liefern - genau beschreiben wie terrain daten geladne und gerender werden
fragen weleche programmiesprache finnen nutzen - zusmmnearbeit - api freigeben
-> konzentration auf digitales gelände model! open und save implementieren
view cube + icons
punktwolke
Skybox check box should be move to preferences

Dealbreaker:
- Deployment does not work - on some user pc the application does not run - no idea why.
  also better output of used GPU could help - does user gpu support DX11?
  need a testfile - really?


Toggle First Person View


File->Save einbauen 
File->Open

How to get more users?
- Support import of XYZ files.
- Support sketching
- Support cross sections
- Support RoadXML

- Background quad clear

Applicatoin should not crash when an invalid landxml file is loaded
It should be possible to select an alignment (hightlight it in 3d view)
It should be possible to delete an alignment (with redo and undo)

Professional Edition:
Handy App GPS Data
DGM Import


// remove: 	muh : IfcCartesianPoint;

Dealbreaker:
1) Nicht alle Klothiden funktionieren!
2) Implementen Docu schreiben im IfcBridge Style

Autodesk Infrastructure Modeler
http://www.cms.bgu.tum.de/publications/theses/vega_2013_ritter.pdf



Tasks/Todo:
- Support of LandXML Cross Sections
- Hightlight selected alignment
- gui für terrain daten!
- Clothide zeichnen
- Antialising!
- Es soll möglich sein ein horizontales alignment zu erstellen
- Alle möglichen LandXML Dateien sollen funktionieren
- andere IFC formate
- IfcProgrammingLanguage clothoide... http://partow.net/programming/exprtk/
- Man soll die farbe eines Alignments setzten können
- Spezialklothoide: Kreis, Kreis
- Höhenplan
- Open, Merge file
- Support different views: Horizontal Alignment, Vertical Alignment, 3D View, 3D Simulation/Abfahren mit autos...
- https://www.tu-braunschweig.de/isbs/lehre/lehrveranstaltungen/visualisierung
- Support of OpenGL
- Impoot von Terrain Mesh aus vermessungsamt...? : currentAlignment_
  HandyDaten, OpenStreetMaps
- Import von gebäuden aus vermessungsamt?
 - MONI: improt von terrain daten -> exprot als landxml - jede Datenbank anzapfen!
- Autos
- Bäume
-> 3D printer ? http://www.duesseldorf.de/planung/wettbew/orsoyerstr/index.shtml
- Smooth Shading für Terrain, Textur für Terrain - typical Terrain Shading...
- Automatische plazieren von verkehrszeichen
- Parallel creation of gfx resources for faster startup
- Wireframe overlay for terrain data
- EXPRESS parser
- Multiple Viewports: http://qt-project.org/forums/viewthread/3647
- Support space mouse
- Move to Qt 5.2.0 and Visual Studio x64 2013 http://qt-project.org/forums/viewthread/32508
- Create a doxygen documentation
- Add recent files in file menu
- http://podofo.sourceforge.net/about.html pdf export
- Fix all warnings! ;)
- Fix clothid bug!!!!!!!!!!
- Multiple Viewports
- Webbased!
- Implement cross sections
- Estimate costs, environmental footprint, whatever...
- Import/Export of OKSTRA Data
- Syntax Highlighting für STEP/EXPRESS files in VS2013
- multiple viewports
- Integrate a search to find specific alignments
- Selection of road segemets
- Add import/export for RoadXML
- Add support for Cross Sections
- Improve LandXML export
- Support exporting of SVG
- Create of horizontal alignment plans as LaTeX/Word document
- Import of geo data (digital elevation model)
- Support new transition curves (like Wienerbogen, Blossbogen, etc.)
- Support of OpenGL rendering
- Porting to Linux/MacOS/Andorid
- Improved Line rendering (as in Java3D)
- Implement navigation cube
- Improve user interface (Zoom, Pan, etc.) (small symbols in viewport)
- Validate LandXML files against XSD schema
- Improve Property Views for alignments
- Import of existing carrigeways from OpenStreet maps
- Creation of plan like: http://www.dfld.de/Andere/Hahn/PFV_(VerlaengerungLandebahn)/Verzeichnisse/b2.htm
- Ribbon: http://www.qtforum.org/article/38889/qt-stylesheet-custom-tab-widget.html
- Build Qt 5.1.1 with VS2013
- Improve GPU Detection (should be possible to detect all features that gpu-z detects) / BlueCore OpenSource machen
  suggest installation of a new graphics driver - if a newer is availablbe...
- Create a wix installer
- Porting HLSL to GLSL
- Create alignment test suite
- Parallel resource creation for faster startup
- Encrypt data and qt stylesheet
- Add menu icons for import/export
- Support of different languages (English, German, French, etc.)
- Improved antialising:
- texture for digital elevation model
- Landsat 7 ETM+ 

Interesting articles/links:

Blogs
http://road-design.blogspot.de/ (very intersting)

Antialising:
http://www.opengl.org/wiki/Multisampling
http://stackoverflow.com/questions/5321330/how-do-you-use-checkmultisamplequalitylevels-and-enable-multisampling

Qt
http://www.thomasmansencal.com/ UMBRA
http://qmlbook.org/index.html

Miscellaneous
http://www.liscad.com/liscad/digital_terrain_model.aspx
http://www.ics.com/technologies/qt-based-clients-google-apis#.UmBVpVC-2M4
https://code.google.com/p/qt-google-maps/source/browse/
http://www.autodesk.com/products/vehicle-tracking/overview
http://adndevblog.typepad.com/infrastructure/augusto-goncalves/
http://vterrain.org/Culture/Roads/
http://www.dgp.toronto.edu/~mccrae/projects/clothoid/sbim2008mccrae.pdf
http://www.geomensura.com/software/mensura-genius/road-design-0

Digital elevation model
http://de.wikipedia.org/wiki/Digitales_H%C3%B6henmodell
http://www.google.de/imgres?espv=210&es_sm=93&biw=1920&bih=1056&tbm=isch&tbnid=uHsrbC4IdIHInM:&imgrefurl=http://www.rssgmbh.de/projekte/naturgefahren/isviews.html&docid=-rnSyMIagjFpWM&imgurl=http://www.rssgmbh.de/typo3temp/pics/a4b8e81733.jpg&w=533&h=334&ei=xkNaUu_4LoXT0QW4lYCQCw&zoom=1&iact=hc&vpx=818&vpy=505&dur=911&hovh=178&hovw=284&tx=83&ty=141&page=1&tbnh=138&tbnw=214&start=0&ndsp=61&ved=1t:429,r:23,s:0,i:154
http://www.google.de/imgres?espv=210&es_sm=93&biw=1920&bih=1056&tbm=isch&tbnid=dEt7ekvkBcVAEM:&imgrefurl=http://www.singularch.de/VRML.htm&docid=kcoT7lZLH7jK1M&imgurl=http://www.singularch.de/images/dem/Bayern_vrml.jpg&w=280&h=203&ei=xkNaUu_4LoXT0QW4lYCQCw&zoom=1&iact=hc&vpx=203&vpy=513&dur=357&hovh=162&hovw=224&tx=190&ty=96&page=1&tbnh=138&tbnw=191&start=0&ndsp=61&ved=1t:429,r:19,s:0,i:137
http://developer.mapquest.com/web/products/open/map
http://pille.iwr.uni-heidelberg.de/~terrain02/dgm.html
http://www.kassoftware.co.uk/opendata.html
http://www.maps4free.de/forum/index.php?showtopic=71

Similar tools
http://www.allplan.net/cms/fileadmin/media/pdf/Allplan2011/Allplan_2011_Option_Gelaende.pdf
http://www.gicinc.org/about.htm Green Infrastructure Center

Civil 3D

Stratis
http://www.trimble.com/alignment/road-alignment.aspx
http://communities.bentley.com/products/road___site_design/f/5922.aspx
http://www.willemer.de/informatik/cpp/
http://www.akgsoftware.de/Modul-Pruefung-der-Linienfuehrung.967.0.html
http://www.card-1.com/produkt/anwendungen/strassenplanung/

Carlson Civil Suite
http://www.widemann.de/sites/default/files/prospekte/Plateia_100dpi.pdf
http://www.wenninger.de/caddy-classic-t.html

Updater
https://github.com/pypt/fervor

Drawing nice lines
http://gamedev.stackexchange.com/questions/46574/fastest-way-to-render-lines-with-aa-varying-thickness-in-directx
http://my.opera.com/Vorlath/blog/2008/08/13/d3d-variable-width-line-drawing-in-hardware
http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter22.html
http://lolengine.net/browser/trunk/tutorial/04_texture.lolfx?rev=2190
http://www.codeproject.com/Articles/199525/Drawing-nearly-perfect-2D-line-segments-in-OpenGL

Deploying Qt Applications on Linux and Windows
http://lemirep.wordpress.com/2013/06/01/deploying-qt-applications-on-linux-and-windows-3/#more-286

CPU Detection
http://libcpuid.sourceforge.net/documentation.html

*/

#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QApplication>

#include "UserInterface/MainWindow.h"
#include "UserInterface/CodeEditorWindow.h"

#include "buw.BlueCore.h"

#include "fvupdater.h"

#include <sstream>

void compile();

#include <QDockWidget>

int main(int argc,char *argv[])
{
	std::ofstream logfile;
	logfile.open("log.txt");
	buw::LogManager::getInstance().addOutputStream(&logfile);

	// log file should be outputted in XML format
	buw::logMangerSettings settings;
	settings.outputAsXML = true;
	settings.colorConsoleOutput = true;
	buw::LogManager::getInstance().setSettings(settings);

	buw::LifetimeManager lm;

	if (buw::getBlueCoreRevisionVersion() < 1802)
	{
		BLUE_LOG_STREAM_EX("main", buw::eLogSeverityLevel::Error) << "Please switch to BlueFramework 0.4.1802 or newer!";
		system("pause");
	}

	if (buw::getBlueCoreRevisionVersion() != buw::VERSION_REVISION)
	{
		BLUE_LOG_STREAM_EX("main", buw::eLogSeverityLevel::Error) << "Invalid BlueCore DLL found!";
	}

	if (!true)
	{
		compile();
		return 0;
	}
	
	buw::LogManager::getInstance().LogCPUInfo();
	buw::LogManager::getInstance().LogOSInfo();
	buw::LogManager::getInstance().LogGPUInfo();

	QApplication application(argc,argv);

	QApplication::setApplicationName("TUM Open Infra Platform 2014");
	QApplication::setApplicationVersion("0.1.0");
	QApplication::setOrganizationName("Technische Universitaet Muenchen Chair of Computational Modeling and Simulation");
	QApplication::setOrganizationDomain("cms.bv.tum.de");
	
	// Set this to your own appcast URL, of course
	FvUpdater::sharedUpdater()->SetFeedURL("http://vertexwahn.de/BlueInfrastructureCenter/Appcast.xml");

	// Check for updates silently -- this will not block the initialization of
	// your application, just start a HTTP request and return immediately.
	FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

	std::string basePath = "Style/blueform.qss";//":Resources/Style/blueform.qss";//

	QFile styleSheet(basePath.c_str());

	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Unable to open stylesheet");
	}
	else
	{
		application.setStyleSheet(styleSheet.readAll());
	}

	// check if we are in beta phase
	QDate expirationDate(2014, 4, 1);
	if ( expirationDate < QDate::currentDate() )
	{
		QString desc = QString(
			"The Beta phase has ended. Please visit our website for a new version:<br/> <a href=\"https://www.cms.bgu.tum.de/de/component/content/article/31-forschung/projekte/397-tum-open-infra-platform\"><font color=\"#48B7E7\">http://www.cms.bgu.tum.de</font></a><br/>"
		);

		QMessageBox::information(nullptr, "Beta Phase ended", desc );

		return 0;
	}

	if (true)
	{
		try
		{
			BlueInfrastructureCenter::UserInterface::MainWindow mainWindow;
			mainWindow.setAttribute(Qt::WA_QuitOnClose);
			mainWindow.show();
			return application.exec();
		}
		catch (const buw::FileNotFoundException& e)
		{
			std::stringstream ss;
			ss << "An unexpected error occurred:\nCould not find file \"" << e.getFilename().c_str() << "\"";
			QMessageBox::information(nullptr,  QApplication::applicationName(), ss.str().c_str() );
		}
	}
	else
	{
		BlueInfrastructureCenter::UserInterface::CodeEditorWindow CodeEditor;
		CodeEditor.show();
		return application.exec();
	}
}
