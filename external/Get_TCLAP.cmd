set dest=C:\thirdparty
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate https://sourceforge.net/projects/tclap/files/tclap-1.2.2.tar.gz -O%cd%\tclap-1.2.2.tar.gz
7za.exe x %cd%\tclap-1.2.2.tar.gz -o%cd%
7za.exe x %cd%\tclap-1.2.2.tar -o%dest%

del %cd%\tclap-1.2.2.tar.gz
del %cd%\tclap-1.2.2.tar