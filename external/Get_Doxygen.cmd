set dest=C:\thirdparty\doxygen
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate http://doxygen.nl/files/doxygen-1.8.18.windows.x64.bin.zip -O%cd%\doxygen-1.8.18.windows.x64.bin.zip
7za.exe x %cd%\doxygen-1.8.18.windows.x64.bin.zip -o%dest%
del %cd%\doxygen-1.8.18.windows.x64.bin.zip

