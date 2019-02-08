set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate http://zlib.net/zlib1211.zip -O%cd%\zlib-1.2.11.zip
7za.exe x %cd%\zlib-1.2.11.zip -o%cd%
del %cd%\zlib-1.2.11.zip
mkdir %dest%\zlib-1.2.11
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
%cmake_command% -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=%dest%\zlib-1.2.11 -G"Visual Studio 14 2015 Win64" -H%cd%\zlib-1.2.11 -B%cd%\zlib-1.2.11\build
C:
cd %cd%\zlib-1.2.11\build
%cmake_command% --build . --target INSTALL --config Release
%cmake_command% --build . --target INSTALL --config Debug
cd ../..
rmdir /Q /S  %cd%\zlib-1.2.11
