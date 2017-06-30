set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
set boost_root=C:/thirdparty/vs2015/x64/boost_1_63_0
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
if NOT [%3]==[] set boost_root=%~3
if [%1]==["--boost-root"] set boost_root=%~2
wget.exe --no-check-certificate https://github.com/libLAS/libLAS-1.6/archive/master.zip -O%cd%\master.zip
7za.exe x %cd%\master.zip -o%dest%
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
%cmake_command% -DBUILD_STATIC_LIBS=ON -DBOOST_ROOT=%boost_root% -G"Visual Studio 14 2015 Win64" -H%dest%\libLAS-1.6-master -B%dest%\libLAS-1.6-master\build
del %cd%\master.zip
C:
cd %dest%\libLAS-1.6-master\build
%cmake_command% --build . --config Debug --target liblas
%cmake_command% --build . --config Release --target liblas
%cmake_command% --build . --config RelWithDebInfo --target liblas
%cmake_command% --build . --config Debug --target liblas_c
%cmake_command% --build . --config Release --target liblas_c
%cmake_command% --build . --config RelWithDebInfo --target liblas_c