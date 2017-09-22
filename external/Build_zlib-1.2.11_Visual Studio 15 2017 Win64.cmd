set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate http://zlib.net/zlib1211.zip -O%cd%\zlib-1.2.11.zip
7za.exe x %cd%\zlib-1.2.11.zip -o%dest%
del %cd%\zlib-1.2.11.zip
%cmake_command% -DBUILD_STATIC_LIBS=ON -G"Visual Studio 15 2017 Win64" -H%dest%\zlib-1.2.11 -B%dest%\zlib-1.2.11\build
C:
cd %dest%\zlib-1.2.11\build
%cmake_command% --build . --config Debug
%cmake_command% --build . --config Release
%cmake_command% --build . --config RelWithDebInfo
xcopy %dest%\zlib-1.2.11\build\zconf.h %dest%\zlib-1.2.11\zconf.h
