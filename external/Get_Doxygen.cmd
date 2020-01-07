//GetDoxygen

set dest=C:\thirdparty
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate http://doxygen.nl/files/doxygen-1.8.17.windows.bin.zip -O%cd%\doxygen-1.8.17.windows.bin.zip
7za.exe x %cd%\doxygen-1.8.17.windows.bin.zip -o%dest%
del %cd%\doxygen-1.8.17.windows.bin.zip
