set dest=C:\thirdparty\sqlite3
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate https://www.sqlite.org/2020/sqlite-dll-win64-x64-3330000.zip -O%cd%\sqlite-dll-win64-x64-3330000.zip
wget.exe --no-check-certificate https://www.sqlite.org/2020/sqlite-amalgamation-3330000.zip -O%cd%\sqlite-amalgamation-3330000.zip

7za.exe x %cd%\sqlite-dll-win64-x64-3330000.zip -o%dest%
7za.exe x %cd%\sqlite-amalgamation-3330000.zip -o%dest%

del %cd%\sqlite-dll-win64-x64-3330000.zip
del %cd%\sqlite-amalgamation-3330000.zip






