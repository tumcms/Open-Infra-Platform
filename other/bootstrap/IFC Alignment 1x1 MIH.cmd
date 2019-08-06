IF EXIST "OIP Revision 1646" (
RMDIR /S /Q "OIP Revision 1646"
)

xcopy /y "C:\build\OpenInfraPlatform2\Release\OpenInfraPlatform.CommandLineUtilities.exe" "C:\Users\admin\Desktop\TUM Open Infra Platform_1646"

mkdir "OIP Revision 1646"
mkdir "OIP Revision 1646\E.1.1 Vertical Alignment"
mkdir "OIP Revision 1646\E.1.2 Horizontal Alignment"
mkdir "OIP Revision 1646\E.1.3 Terrain Surface"
mkdir "OIP Revision 1646\E.1.4 Terrain and Alignment"

REM E.1.1 Vertical Alignment
xcopy "images\vertical-alignment.png" "OIP Revision 1646\E.1.1 Vertical Alignment"
REM Vertical Alignment IFC Alignment 1x0
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision 1646\E.1.1 Vertical Alignment\vertical-alignment-IfcAlignment1x0.ifc" ^
-t "IfcAlignment1x0"
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision 1646\E.1.1 Vertical Alignment\vertical-alignment-IfcAlignment1x1.ifc" ^
-t "IfcAlignment1x1"
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\ParaAndCircCurve.xml" ^
-o "OIP Revision 1646\E.1.1 Vertical Alignment\vertical-alignment.xlsx" ^
-t "IfcAlignment1x0_XLSX"

REM E.1.2 Horizontal Alignment
xcopy "images\ex-horizontal-alignment.png" "OIP Revision 1646\E.1.2 Horizontal Alignment"
REM Horizontal Alignment IFC Alignment 1x0
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision 1646\E.1.2 Horizontal Alignment\horizontal-alignment-IfcAlignment1x0.ifc" ^
-t "IfcAlignment1x0"
REM Horizontal Alignment IFC Alignment 1x1
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision 1646\E.1.2 Horizontal Alignment\horizontal-alignment-IfcAlignment1x1.ifc" ^
-t "IfcAlignment1x1"
REM Horizontal Alignment IFC Alignment 1x0 Excel Report
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision 1646\E.1.2 Horizontal Alignment\ex-horizontal-alignment.xlsx" ^
-t "IfcAlignment1x0_XLSX"
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\debug.xml" ^
-o "OIP Revision 1646\E.1.2 Horizontal Alignment\ex-horizontal-alignment.svg" ^
-t "SVG"

REM E.1.3 Terrain Surface
xcopy "images\ex-terrain-surface.png" "OIP Revision 1646\E.1.4 Terrain and Alignment"
REM Terrain Surface IFC Alignment 1x0
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\LandXMLDemo.xml" ^
-o "OIP Revision 1646\E.1.3 Terrain Surface\terrain-surface-IfcAlignment1x0.ifc" ^
-t "IfcAlignment1x0"
REM Terrain Surface IFC Alignment 1x1
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\LandXMLDemo.xml" ^
-o "OIP Revision 1646\E.1.3 Terrain Surface\terrain-surface-IfcAlignment1x1.ifc" ^
-t "IfcAlignment1x1"
REM Terrain Surface IFC Alignment 1x0 Excel Report
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\Users\admin\OneDrive\dev\OpenInfraPlatfom\testdata\LandXML\AutoCAD Civil 3D\LandXMLDemo.xml" ^
-o "OIP Revision 1646\E.1.3 Terrain Surface\terrain-surface-IfcAlignment1x0.xlsx" ^
-t "IfcAlignment1x0_XLSX"

REME.1.4 Terrain and Alignment
xcopy "images\ex-terrain-alignment.png" "OIP Revision 1646\E.1.3 Terrain Surface"
REM Terrain Surface IFC Alignment 1x0
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision 1646\E.1.4 Terrain and Alignment\terrain-surface-IfcAlignment1x0.ifc" ^
-t "IfcAlignment1x0"
REM Terrain Surface IFC Alignment 1x1
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision 1646\E.1.4 Terrain and Alignment\terrain-surface-IfcAlignment1x1.ifc" ^
-t "IfcAlignment1x1"
REM Terrain Surface IFC Alignment 1x0 Excel Report
"C:\Users\admin\Desktop\TUM Open Infra Platform_1646\OpenInfraPlatform.CommandLineUtilities.exe" ^
-i "C:\dev\OpenInfraPlatform2\testdata\LandXML\Mainbruecke_Klingenberg.xml" ^
-o "OIP Revision 1646\E.1.4 Terrain and Alignment\terrain-surface-IfcAlignment1x0.xlsx" ^
-t "IfcAlignment1x0_XLSX"