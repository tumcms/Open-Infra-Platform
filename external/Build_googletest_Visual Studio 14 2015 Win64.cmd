set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/google/googletest/archive/master.zip -O%cd%\master.zip
7za.exe x  %cd%\master.zip -o%cd%
del %cd%\master.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
C:
cd %cd%\googletest-master
%cmake_command% ^
-DBUILD_SHARED_LIBS=ON ^
-DCMAKE_INSTALL_PREFIX=%dest%\googletest ^
-G "Visual Studio 14 2015 Win64" ^
-H%cd% ^
-B%cd%\build
cd %cd%\build
%cmake_command% --build . --target INSTALL --config Debug
%cmake_command% --build . --target INSTALL --config Release

cd ../..
rmdir /Q /S .\googletest-master