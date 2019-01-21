set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/google/googletest/archive/release-1.8.0.zip -O%cd%\release-1.8.0.zip
7za.exe x  %cd%\release-1.8.0.zip -o%cd%
del %cd%\release-1.8.0.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64

C:
cd %cd%\googletest-release-1.8.0
%cmake_command% ^
-DBUILD_SHARED_LIBS=ON ^
-DCMAKE_INSTALL_PREFIX=%dest%\googletest-release-1.8.0 ^
-G "Visual Studio 15 2017 Win64" ^
-H%cd% ^
-B%cd%\build
cd build

%cmake_command% --build . --target INSTALL --config Release
%cmake_command% --build . --target INSTALL --config Debug
cd ../..
rmdir /Q /S  %cd%\googletest-release-1.8.0