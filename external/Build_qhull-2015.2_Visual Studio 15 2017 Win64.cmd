set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/qhull/qhull/archive/master.zip -O%cd%\master.zip
7za.exe x %cd%\master.zip -o%dest%
%cmake_command% -DBUILD_STATIC_LIBS=ON -G"Visual Studio 15 2017 Win64" -H%dest%\qhull-master -B%dest%\qhull-master\build
del  %cd%\master.zip
C:
cd %dest%\qhull-master\build
%cmake_command% --build . --config Debug --target qhullstatic
%cmake_command% --build . --config Release --target qhullstatic
%cmake_command% --build . --config RelWithDebInfo --target qhullstatic