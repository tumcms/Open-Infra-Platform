set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/google/googletest/archive/release-1.8.0.zip -O%cd%\release-1.8.0.zip
7za.exe x  %cd%\release-1.8.0.zip -o%dest%
del %cd%\release-1.8.0.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
C:
cd %dest%\googletest-release-1.8.0
%cmake_command% ^
-DBUILD_SHARED_LIBS=ON ^
-G "Visual Studio 14 2015 Win64" ^
-H%dest%\googletest-release-1.8.0 ^
-B%dest%\googletest-release-1.8.0\build
cd %dest%\googletest-release-1.8.0\build
%cmake_command% --build . --config Debug
%cmake_command% --build . --config Release
%cmake_command% --build . --config RelWithDebInfo