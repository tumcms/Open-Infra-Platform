set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"

wget.exe http://fftw.org/fftw-3.3.8.tar.gz -O%cd%\fftw-3.3.8.tar.gz
7za.exe x %cd%\fftw-3.3.8.tar.gz -o%cd%\fftw-3.3.8.tar
7za.exe x %cd%\fftw-3.3.8.tar -o%dest%\fftw-3.3.8\src
del %cd%\fftw-3.3.8.tar.gz
rmdir /Q /S  %cd%\fftw-3.3.8.tar
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
C:
cd %dest%\fftw-3.3.8\src\fftw-3.3.8
mkdir %dest%\fftw-3.3.8\src\fftw-3.3.8\build

%cmake_command% ^
-DBUILD_SHARED_LIBS=OFF ^
-DCMAKE_INSTALL_PREFIX=%dest%\fftw-3.3.8 ^
-G "Visual Studio 14 2015 Win64" ^
-H%dest%\fftw-3.3.8\src\fftw-3.3.8 ^
-B%dest%\fftw-3.3.8\src\fftw-3.3.8\build

cd %dest%\fftw-3.3.8\src\fftw-3.3.8\build
%cmake_command% --build . --target INSTALL --config Release
cd %dest%
rmdir /Q /S %dest%\fftw-3.3.8\src