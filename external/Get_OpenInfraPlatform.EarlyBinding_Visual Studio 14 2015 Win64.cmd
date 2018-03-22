set dest=C:\thirdparty
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate http://oip.cms.bgu.tum.de/OpenInfraPlatform.EarlyBinding-1.0.0.0-win64-vs2015.zip -O%cd%\OpenInfraPlatform.EarlyBinding-1.0.0.0-win64-vs2015.zip
7za.exe x %cd%\OpenInfraPlatform.EarlyBinding-1.0.0.0-win64-vs2015.zip -o%dest%
del %cd%\OpenInfraPlatform.EarlyBinding-1.0.0.0-win64-vs2015.zip