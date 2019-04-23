REM @echo off
REM Stop the messages

SETLOCAL ENABLEEXTENSIONS
SET me=%~n0

REM Okstra Library downloads batch file
REM  Markic 22.03.2017

REM Get the libraries from the official website
REM  www.okstra.de

REM When new version is posted, correct the Release number
SET version=20161209

REM Input parameters check
SET ppath=%~f1
IF %~f1x==x SET ppath="C:\thirdparty\vs2015\x64"

SET pathDownload=%ppath%\downloads
IF NOT EXIST %pathDownload% MKDIR %pathDownload%
SET pathOklabi=%ppath%\oklabi_%version%
IF NOT EXIST %pathOklabi% MKDIR %pathOklabi%
SET urlOklabi=http://www.okstra.de/oklabi/Release-%version%/Oklabi

REM The resources
REM  Ressourcen für die Nutzung mit der OKSTRA®-Klassenbibliothek. Darin sind die Fachbedeutungslisten und die Schemadatenbank mit enthalten. 
wget.exe %urlOklabi%/Ressourcen/Ressourcen.zip  -O%pathDownload%\Ressourcen.zip
7za.exe x %pathDownload%\Ressourcen.zip -o%pathOklabi% -y > nul

REM Binaries
REM  Version 1.3.0.45   Diese Archive richtet sich an Nutzer der nativen C++ Schnittstelle.
REM  Die Archive enthalten die DLL- und LIB-Dateien für Windows unterschieden nach verschiedenen Versionen der Entwicklungsumgebung sowie für 32 und 64 Bit Plattformen.
REM  Bitte beachten Sie: Zur Zeit werden die Microsoft-Entwicklungsumgebungen "Visual Studio 2008", "Visual Studio 2010", "Visual Studio 2012", "Visual Studio 2013" und "Visual Studio 2015" unterstützt. 
REM    Die Headerdateien sind unabhängig von der Version der Entwicklungsumgebung und liegen in mehreren Verzeichnissen im Ordner Bibliothek und stehen auch zum Download bereit. 
REM    Beachten Sie auch, dass bei Benutzung der Bibliotheken die Laufzeitumgebungen gegebenenfalls aktualisiert werden müssen. Die benötigten Redistributable Pakete für Visual Studio finden Sie bei Microsoft.
REM  Bei den Compiler-Einstellungen für die Codegenerierung richten Sie bitte folgende Parameter ein:
REM      Enable C++ Exceptions: Yes With SEH Exceptions (/EHa)
REM      Runtime Library: Multi-threaded DLL (/MD)
REM  Die Präprozessor-Variable "_DEBUG" darf nicht gesetzt sein, verwenden Sie statt dessen bitte "NDEBUG".  
wget.exe %urlOklabi%/Bibliothek/Kern-C++.zip  -O%pathDownload%\Kern-C++.zip
7za.exe x %pathDownload%\Kern-C++.zip -o%pathOklabi% -y > nul
wget.exe %urlOklabi%/Bibliothek/Util.zip  -O%pathDownload%\Util.zip
7za.exe x %pathDownload%\Util.zip -o%pathOklabi% -y > nul

REM Quellen
REM  Für Programmierer, die unmittelbar auf der C++ Schicht der Klassenbibliothek aufsetzen wollen, sind diese Archive notwendig. 
REM  Die Verzeichnisse, in welche diese Archive entpackt wurden, sind in der genutzten Entwicklungsumgebung in den include-Pfad einzustellen.
REM  In der Kern-Komponente stecken die eigentlichen OKLABI-Schnittstellen und die Dienst-Komponente mit einigen Hilfsmittel für die Programmierung. 
REM  In der Util-Komponente befinden sich die Schnittstellen zur Einbindung von Java- und CREM-Interface-Objekten (z.B. Protokollant), 
REM    da man aus technischen Gründen für die Kommunikation über die Sprachgrenzen hinweg spezielle C++-Varianten dieser Objekte braucht. 
wget.exe %urlOklabi%/Bibliothek//Windows/VS2015-Lib64.zip  -O%pathDownload%\VS2015-Lib64.zip
7za.exe x %pathDownload%\VS2015-Lib64.zip -o%pathOklabi% -y > nul
REM copy the contents of VS2015-Lib64 to its parent folder and remove the folder itself
ROBOCOPY %pathOklabi%\VS2015-Lib64\ %pathOklabi%\ /e
RD /S /Q %pathOklabi%\VS2015-Lib64

REM delete the temporary downloads folder
RD /S /Q %pathDownload%

REM Finished