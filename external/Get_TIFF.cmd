set dest=C:\thirdparty\
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate http://download.osgeo.org/pub/libtiff/tiff-4.1.0.zip -O%cd%\tiff-4.1.0.zip

7za.exe x %cd%\tiff-4.1.0.zip -o%dest%

del %cd%\tiff-4.1.0.zip 

