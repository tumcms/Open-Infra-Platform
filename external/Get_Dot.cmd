set dest=C:\thirdparty
if NOT [%1]==[] set dest=%~1

wget.exe --no-check-certificate https://graphviz.gitlab.io/_pages/Download/windows/graphviz-2.38.zip -O%cd%\graphviz-2.38.zip
7za.exe x %cd%\graphviz-2.38.zip -o%dest%
del %cd%\graphviz-2.38.zip

