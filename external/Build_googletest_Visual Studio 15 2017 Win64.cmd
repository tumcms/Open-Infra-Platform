set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/google/googletest/archive/master.zip -O%cd%\master.zip
7za.exe x  %cd%\master.zip -o%dest%
del %cd%\master.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.1\VC\vcvarsall.bat" amd64
C:
cd %dest%\googletest-master
%cmake_command% ^
-DBUILD_SHARED_LIBS=ON ^
-G "Visual Studio 15 2017 Win64" ^
-H%dest%\googletest-master ^
-B%dest%\googletest-master\build
cd %dest%\googletest-master\build
%cmake_command% --build . --config Debug
%cmake_command% --build . --config Release
%cmake_command% --build . --config RelWithDebInfo