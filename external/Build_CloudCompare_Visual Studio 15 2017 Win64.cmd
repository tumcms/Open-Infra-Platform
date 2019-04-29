set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/CloudCompare/CloudCompare/archive/master.zip -O%cd%\cc.zip
7za.exe x %cd%\cc.zip -o%dest%
del %cd%\cc.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
%cmake_command% -DCMAKE_PREFIX_PATH="C:/Qt/5.10.0/msvc2017_64/lib/cmake;C:/Qt/5.11.0/msvc2017_64/lib/cmake;C:/Qt/5.12.1/msvc2017_64/lib/cmake;C:/Qt/5.12.2/msvc2017_64/lib/cmake" -G"Visual Studio 15 2017 Win64" -H%dest%\CloudCompare-master -B%dest%\CloudCompare-master\build
C:
cd %dest%\CloudCompare-master\build
%cmake_command% --build . --config Debug
%cmake_command% --build . --config Release
%cmake_command% --build . --config RelWithDebInfo
