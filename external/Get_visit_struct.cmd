set dest=C:\thirdparty
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
wget.exe --no-check-certificate https://github.com/cbeck88/visit_struct/archive/master.zip -O%cd%\master.zip
7za.exe x %cd%\master.zip -o%dest%
del  %cd%\master.zip