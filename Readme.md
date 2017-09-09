# TUM Open Infra Platform

## Info

`TUM Open Infra Platform`is a software for viewing and converting alignment data. Currently it offers partital support for LandXML, our IFC based Alignment proposal, IFC Alignment 1.0, IFC Alignment 1.1 (work in progress) and OKSTRA.

![Beta1_5_Windows8_1.png](screenshots/Beta1_5_Windows8_1.png)

## Building

### Buildng thirdparty libararies

OIP depence on several third party libaries such as zlib. The [percdems](http://bitbucket.org/Vertexwahn/percdems/src) contains several scirpts to build the different needed libraries. For instance, building zlib for Visual Studio 2015 x64 can be done using the following batch script on Windows:

```bash
wget.exe http://zlib.net/zlib1211.zip -OC:\thirdparty\vs2015\x64\zlib-1.2.11.zip
7za.exe x C:\thirdparty\vs2015\x64\zlib-1.2.11.zip -oC:\thirdparty\vs2015\x64
del C:\thirdparty\vs2015\x64\zlib-1.2.11.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
cmake -G"Visual Studio 14 2015 Win64" -HC:\thirdparty\vs2015\x64\zlib-1.2.11 -BC:\thirdparty\vs2015\x64\zlib-1.2.11\build
C:
cd C:\thirdparty\vs2015\x64\zlib-1.2.11\build
cmake --build . --config Debug
cmake --build . --config Release
cmake --build . --config RelWithDebInfo
mkdir C:\thirdparty\vs2015\x64\zlib-1.2.11\lib
mkdir C:\thirdparty\vs2015\x64\zlib-1.2.11\bin
copy Debug\zlibd.dll C:\thirdparty\vs2015\x64\zlib-1.2.11\bin\zlibd.dll
copy Debug\zlibd.exp C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibd.exp
copy Debug\zlibd.ilk C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibd.ilk
copy Debug\zlibd.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibd.lib
copy Debug\zlibd.pdb C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibd.pdb
copy Debug\zlibstaticd.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibstaticd.lib

REM copy RelWithDebInfo\zlib.dll C:\thirdparty\vs2015\x64\zlib-1.2.11\bin\zlib.dll
REM copy RelWithDebInfo\zlib.exp C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlib.exp
REM copy RelWithDebInfo\zlib.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlib.lib
REM copy RelWithDebInfo\zlibstatic.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibstatic.lib

copy Release\zlib.dll C:\thirdparty\vs2015\x64\zlib-1.2.11\bin\zlib.dll
copy Release\zlib.exp C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlib.exp
copy Release\zlib.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlib.lib
copy Release\zlibstatic.lib C:\thirdparty\vs2015\x64\zlib-1.2.11\lib\zlibstatic.lib
copy zconf.h C:\thirdparty\vs2015\x64\zlib-1.2.11\zconf.h
```

## License

Copyright (c) 2016 Technical University of Munich
Chair of Computational Modeling and Simulation.

TUM Open Infra Platform is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Version 3
as published by the Free Software Foundation.

TUM Open Infra Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

## Copyright notes
TUM Open Infra Platform uses several software libraries. The corresponding licenses can be found in the Licenses folder distributed with this source code:

* boost 1.63.0 (http://www.boost.org/) (*Boost Software License*) ({root_dir}/Licenses/boost.LICENSE_1_0.txt)
* Eigen 3.3.2 (http://eigen.tuxfamily.org/) (*MPL2*) ({root_dir}/Licenses/Eigen.COPYING.MPL2)
* Google Test 1.7.0 (https://github.com/google/googletest) (*BSD 3-Clause License*) ({root_dir}/Licenses/GoogleTest.LICENSE)
* Qt 5.8 (http://doc.qt.io/qt-5/lgpl.html) (LGPL version 3) ({root_dir}/Licenses/Qt.LGPL_version_3.txt)
* BlueFramwork3 (https://bitbucket.org/tumcms/blueframework3-public) (GPL v3 License) ({root_dir}/Licenses/BlueFramwork3.txt)

