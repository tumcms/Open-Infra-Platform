set dest=C:\thirdparty\
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate https://curl.haxx.se/download/curl-7.73.0.zip -O%cd%\curl-7.73.0.zip

7za.exe x %cd%\curl-7.73.0.zip -o%dest%

del %cd%\curl-7.73.0.zip 

