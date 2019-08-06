IF EXIST "OIP Revision XYZW" (
RMDIR /S /Q "OIP Revision XYZW"
)

mkdir "OIP Revision XYZW"
mkdir "OIP Revision XYZW\E.1.1 Vertical Alignment"
mkdir "OIP Revision XYZW\E.1.2 Horizontal Alignment"
mkdir "OIP Revision XYZW\E.1.3 Terrain Surface"
mkdir "OIP Revision XYZW\E.1.4 Terrain and Alignment"
REM mkdir "OIP Revision XYZW\E.1.5 Linear Placement"
mkdir "OIP Revision XYZW\E.1.6 Bloss Curve"

REM E.1.1 Vertical Alignment
xcopy "images\ex-vertical-alignment.png" "OIP Revision XYZW\E.1.1 Vertical Alignment"
REM Vertical Alignment IFC Alignment 1x0
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision XYZW\E.1.1 Vertical Alignment\ex-vertical-alignment-ifcalignment1x0.ifc" ^
-t "IfcAlignment1x0"
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision XYZW\E.1.1 Vertical Alignment\ex-vertical-alignment-ifcalignment1x1.ifc" ^
-t "IfcAlignment1x1"
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision XYZW\E.1.1 Vertical Alignment\ex-vertical-alignment.xlsx" ^
-t "IfcAlignment1x1_XLSX"

REM E.1.2 Horizontal Alignment
xcopy "images\ex-horizontal-alignment.png" "OIP Revision XYZW\E.1.2 Horizontal Alignment"
REM Horizontal Alignment IFC Alignment 1x0
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision XYZW\E.1.2 Horizontal Alignment\ex-horizontal-alignment-ifcalignment1x0.ifc" ^
-t "IfcAlignment1x0"
REM Horizontal Alignment IFC Alignment 1x1
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision XYZW\E.1.2 Horizontal Alignment\ex-horizontal-alignment-ifcalignment1x1.ifc" ^
-t "IfcAlignment1x1"
REM Horizontal Alignment IFC Alignment 1x0 Excel Report
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision XYZW\E.1.2 Horizontal Alignment\ex-horizontal-alignment.xlsx" ^
-t "IfcAlignment1x1_XLSX"
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision XYZW\E.1.2 Horizontal Alignment\ex-horizontal-alignment.svg" ^
-t "SVG"

REM E.1.3 Terrain Surface
xcopy "images\ex-terrain-surface.png" "OIP Revision XYZW\E.1.3 Terrain Surface"
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\LandXMLDemo.xml" ^
-o "OIP Revision XYZW\E.1.3 Terrain Surface\ex-terrain-surface-ifcalignment1x1.ifc" ^
-t "IfcAlignment1x1"

REM E.1.4 Terrain and Alignment
xcopy "images\ex-terrain-alignment.png" "OIP Revision XYZW\E.1.4 Terrain and Alignment"
REM Terrain Surface IFC Alignment 1x0
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision XYZW\E.1.4 Terrain and Alignment\terrain-and-alignment-ifcalignment1x0.ifc" ^
-t "IfcAlignment1x0"
REM Terrain Surface IFC Alignment 1x1
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision XYZW\E.1.4 Terrain and Alignment\terrain-and-alignment-ifcalignment1x1.ifc" ^
-t "IfcAlignment1x1"
REM Terrain Surface IFC Alignment 1x0 Excel Report
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision XYZW\E.1.4 Terrain and Alignment\terrain-and-alignment-ifcalignment1x0.xlsx" ^
-t "IfcAlignment1x1_XLSX"

REM E.1.6 Bloss Curve
xcopy "images\ex-bloss-curve.png" "OIP Revision XYZW\E.1.6 Bloss Curve"
"TUM Open Infra Platform_1935\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\bloss.xml" ^
-o "OIP Revision XYZW\E.1.6 Bloss Curve\ex-bloss-curve-alignment1x1.ifc" ^
-t "IfcAlignment1x1"