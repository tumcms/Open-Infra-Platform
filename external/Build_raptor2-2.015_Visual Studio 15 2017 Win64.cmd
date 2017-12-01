set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"

if exist %dest%\vcpkg-master\installed\x64-windows\lib\libxml2.lib (
	if exist %dest%\vcpkg-master\installed\x64-windows\lib\libxslt.lib (
		if exist %dest%\vcpkg-master\installed\x64-windows\lib\libexslt.lib (
			echo "Found all libraries, building raptor!"
			goto buildRaptor
		)
	)
)

call :downloadVcpkg
goto buildRaptor

::Build libxml2 and libxslt
:downloadVcpkg
set CDIR=%cd%
wget.exe --no-check-certificate https://github.com/Microsoft/vcpkg/archive/master.zip -O%cd%\vcpkg-master.zip
7za.exe x  %cd%\vcpkg-master.zip -o%dest%
del %cd%\vcpkg-master.zip
C:
cd %dest%\vcpkg-master
call "bootstrap-vcpkg.bat"
vcpkg install libxml2:x64-windows
vcpkg install libxslt:x64-windows
cd %CDIR%
exit /b

::download raptor
:downloadRaptor2
wget.exe --no-check-certificate http://download.librdf.org/source/raptor2-2.0.15.tar.gz -O%cd%\raptor2-2.0.15.tar.gz
7za.exe x  %cd%\raptor2-2.0.15.tar.gz -o%cd%
7za.exe x  %cd%\raptor2-2.0.15.tar -o%dest%
del %cd%\raptor2-2.0.15.tar.gz
del %cd%\raptor2-2.0.15.tar
exit /b


::Now we want to build raptor itself
:buildRaptor
SET "VCPKG_CMAKE_TOOLCHAIN_FILE=%dest%\vcpkg-master\scripts\buildsystems\vcpkg.cmake"


call :downloadRaptor2
C:
cd %dest%\raptor2-2.0.15


::We have to do some modifications on some files so we try
::to search and replace

call :FindReplace "ADD_DEFINITIONS(-DHAVE_CONFIG_H)" "ADD_DEFINITIONS(-DHAVE_CONFIG_H -DYY_NO_UNISTD_H)" CMakeLists.txt
cd src
call :FindReplace "ADD_LIBRARY(raptor2" "ADD_LIBRARY(raptor2 raptor_escaped.c sort_r.c raptor_ntriples.c" CMakeLists.txt
cd ..

::Build raptor2
%cmake_command% ^
-DCMAKE_TOOLCHAIN_FILE=%VCPKG_CMAKE_TOOLCHAIN_FILE% ^
-G"Visual Studio 15 2017 Win64" ^
-H%dest%\raptor2-2.0.15 ^
-B%dest%\raptor2-2.0.15\build

cd %dest%\raptor2-2.0.15\build
%cmake_command% --build . --config Debug
%cmake_command% --build . --config Release
%cmake_command% --build . --config RelWithDebInfo
exit

::Method to find a string in a file and replace it in place

:FindReplace <findstr> <replstr> <file>
setlocal
@echo off
set tmp="%temp%\tmp.txt"
If not exist %temp%\_.vbs call :MakeReplace
for /f "tokens=*" %%a in ('dir "%3" /s /b /a-d /on') do (
  for /f "usebackq" %%b in (`Findstr /mic:"%~1" "%%a"`) do (
    echo(&Echo Replacing "%~1" with "%~2" in file %%~nxa
    <%%a cscript //nologo %temp%\_.vbs "%~1" "%~2">%tmp%
    if exist %tmp% move /Y %tmp% "%%~dpnxa">nul
  )
)
del %temp%\_.vbs
@echo on
exit /b

:MakeReplace
>%temp%\_.vbs echo with Wscript
>>%temp%\_.vbs echo set args=.arguments
>>%temp%\_.vbs echo .StdOut.Write _
>>%temp%\_.vbs echo Replace(.StdIn.ReadAll,args(0),args(1),1,-1,1)
>>%temp%\_.vbs echo end with